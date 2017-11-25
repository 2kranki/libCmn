// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   audioWAV.c
 *	Generated 09/19/2016 20:13:13
 *
 */

 
/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include "audioWAV_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    
    //              Internal 4-place Sine Table
    // 	All numbers should be divided by 10000 to get the proper value.
    // 	Table is from data in "Modern Plane Trigonometry", William L. Hart,
    //	D.C. Heath and Company, 1961.
    static
    const
    uint16_t        sineTable[91] = {                               // Degrees
        0,  175,  349,  523,  698,  872, 1045, 1219, 1392, 1564,	// 	000-009
        1736, 1908, 2079, 2250, 2419, 2588, 2756, 2924, 3090, 3256,	// 	010-019
        3420, 3584, 3746, 3907, 4067, 4226, 4384, 4540, 4695, 4848,	// 	020-029
        5000, 5150, 5299, 5446, 5592, 5736, 5878, 6018, 6157, 6293,	// 	030-039
        6428, 6561, 6691, 6820, 6947, 7071, 7193, 7314, 7431, 7547,	//  040-049
        7660, 7771, 7880, 7986, 8090, 8192, 8290, 8387, 8480, 8572,	// 	050-059
        8660, 8746, 8829, 8910, 8988, 9063, 9135, 9205, 9272, 9336,	// 	060-069
        9397, 9455, 9511, 9563, 9613, 9659, 9703, 9744, 9781, 9816,	// 	070-079
        9848, 9877, 9903, 9925, 9945, 9962, 9976, 9986, 9994, 9998,	// 	080-089
        10000														//  090
    };
    
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    uint16_t        audioWAV_getSilenceChar(
        AUDIOWAV_DATA   *this
    )
    {
        uint16_t        data = 0;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (this->header.waveFormat.wBitsPerSample < 9) {
            data = 128;
        }
        else {
            data = 0;
        }
        
        return data;
    }
    
    
    
    bool            audioWAV_AddChannelData(
        AUDIOWAV_DATA	*this,
        int16_t         channel,
        int32_t         data
    )
    {
        uint32_t        index;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !audioWAV_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        index = this->cFrames * this->header.waveFormat.nBlockAlign;
        
        switch (this->header.waveFormat.wBitsPerSample) {
            case 8:
                index += (channel * 1) + 1;
                u8Array_PutU8(this->pFrames, index, data);
                break;
                
            case 16:
                index += (channel * 2) + 1;
                u8Array_PutU16(this->pFrames, index, data);
                break;
                
            case 24:
                index += (channel * 3) + 1;
                u8Array_PutU24(this->pFrames, index, data);
                break;
                
            case 32:
                index += (channel * 4) + 1;
                u8Array_PutU32(this->pFrames, index, data);
                break;
                
            default:
                DEBUG_BREAK();
                break;
        }
        return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    bool            audioWAV_AddFrame(
        AUDIOWAV_DATA   *this,
        int32_t         leftFront,
        int32_t         rightFront,
        int32_t         center,
        int32_t         leftRear,
        int32_t         rightRear,
        int32_t         surround
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !audioWAV_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        switch (this->header.waveFormat.nChannels) {
            case 1:     // Mono
                audioWAV_AddChannelData(this, 0, leftFront);
                break;
                
            case 2:     // Stereo
                audioWAV_AddChannelData(this, 0, leftFront);
                audioWAV_AddChannelData(this, 1, rightFront);
                break;
                
            case 3:
                audioWAV_AddChannelData(this, 0, leftFront);
                audioWAV_AddChannelData(this, 1, rightFront);
                audioWAV_AddChannelData(this, 2, center);
                break;
                
            case 4:     // Quad Stereo
                audioWAV_AddChannelData(this, 0, leftFront);
                audioWAV_AddChannelData(this, 1, rightFront);
                audioWAV_AddChannelData(this, 2, leftRear);
                audioWAV_AddChannelData(this, 3, rightRear);
                break;
                
            case 6:
                audioWAV_AddChannelData(this, 0, leftFront);
                audioWAV_AddChannelData(this, 1, leftRear);
                audioWAV_AddChannelData(this, 2, center);
                audioWAV_AddChannelData(this, 3, rightFront);
                audioWAV_AddChannelData(this, 4, rightRear);
                audioWAV_AddChannelData(this, 5, surround);
                break;
                
            default:
                break;
        }
        ++this->cFrames;
        
        // Return to caller.
        return true;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    AUDIOWAV_DATA *     audioWAV_Alloc(
    )
    {
        AUDIOWAV_DATA       *this;
        uint32_t        cbSize = sizeof(AUDIOWAV_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    AUDIOWAV_DATA *     audioWAV_New(
        uint8_t         numberOfChannels,
        uint32_t        samplesPerSecond,   // Normally 11025, 22050, 44100
        uint16_t        sampleSize          // Normally 8, 16, or 32
    )
    {
        AUDIOWAV_DATA       *this;
        
        this = audioWAV_Alloc( );
        if (this) {
            this = audioWAV_Init(this, numberOfChannels, samplesPerSecond, sampleSize);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    U8ARRAY_DATA *  audioWAV_getFrames(
        AUDIOWAV_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pFrames;
    }
    
    
    bool            audioWAV_setFrames(
        AUDIOWAV_DATA   *this,
        U8ARRAY_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pFrames) {
            obj_Release(this->pFrames);
        }
        this->pFrames = pValue;
        
        return true;
    }
    
    
    
    ERESULT         audioWAV_getLastError(
        AUDIOWAV_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        return this->eRc;
    }



    uint16_t        audioWAV_getNumberOfChannels(
        AUDIOWAV_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->header.waveFormat.nChannels;
    }
    
    
    
    uint32_t        audioWAV_getSamplesPerSec(
        AUDIOWAV_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->header.waveFormat.nSamplesPerSec;
    }



    uint16_t        audioWAV_getSampleSize(
        AUDIOWAV_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->header.waveFormat.wBitsPerSample;
    }
    
    
    
    uint32_t        audioWAV_getSize(
        AUDIOWAV_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return 0;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                   A p p e n d  F r a m e
    //---------------------------------------------------------------
    
    ERESULT         audioWAV_AppendFrame(
        AUDIOWAV_DATA	*this,
        int32_t         leftFront,
        int32_t         rightFront,
        int32_t         center,
        int32_t         leftRear,
        int32_t         rightRear,
        int32_t         surround
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !audioWAV_Validate( this ) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        fRc =   audioWAV_AddFrame(
                                  this,
                                  leftFront,
                                  rightFront,
                                  center,
                                  leftRear,
                                  rightRear,
                                  surround
                );
        if (!fRc) {
            this->eRc = ERESULT_GENERAL_FAILURE;
            return this->eRc;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                   A p p e n d  S i l e n c e
    //---------------------------------------------------------------
    
    ERESULT         audioWAV_AppendSilence(
        AUDIOWAV_DATA	*this,
        uint32_t        nMilli
    )
    {
        uint64_t        nGross;
        int32_t         data = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !audioWAV_Validate( this ) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        nGross = this->header.waveFormat.nSamplesPerSec * nMilli;
        nGross = nGross / 1000;
        
        data = audioWAV_getSilenceChar(this);
        
        while (nGross--) {
            audioWAV_AddFrame(this, data, data, data, data, data, data);
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                   A p p e n d  S i n e  W a v e
    //---------------------------------------------------------------
    
    ERESULT         audioWAV_AppendSineWave(
        AUDIOWAV_DATA	*this,
        uint16_t		cFreq,              // Frequency (20Hz..20,000Hz)
        uint32_t		nMilli              // Number of Milliseconds
    )
    {
        uint32_t        cycleSize = 0;      // Number of Frames in a Cycle
        uint64_t        nGross;
        uint64_t        nCycles;
        uint32_t		i = 0;
        uint32_t		j = 0;
        uint16_t        silence;
        int32_t         *pWave = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !audioWAV_Validate( this ) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( (20 > cFreq) || (20000 < cFreq) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
#endif
        cycleSize = (this->header.waveFormat.nSamplesPerSec + (cFreq - 1)) / cFreq;
        nGross = (this->header.waveFormat.nSamplesPerSec * nMilli) / 1000;
        nCycles = (nGross + (cycleSize - 1)) / cycleSize;
        silence = audioWAV_getSilenceChar(this);
        
        pWave = mem_Malloc(cycleSize * sizeof(int32_t));
        if (pWave == NULL) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return this->eRc;
        }
        for( j=0; j<cycleSize; ++j ) {
            int32_t			deg;
            uint32_t		index;
            int16_t         sine;
            int64_t         data;
            deg = ((360 * j) + cycleSize - 1) / cycleSize; // Figure out degree for a cycle.
            // The full sinewave is:
            //      0 - 90          increasing as in the table
            //      91 - 180        decreasing as in the table reversed
            //      181 - 270       negative decreasing as in negative table entry
            //      271 - 360       negative increasing as in negative reversed table
            //      0, 180, 360     are zero crossover points
            //      most positive   90
            //      most negative   270
            BREAK_TRUE(((deg < 0) || (deg > 360)));
            
            // Find sine component from table.
            // (sineTable is limited to 0 - 90 degrees).
            index = ( deg >= 180 ? deg - 180 : deg );   // Translate degree to first 180 degrees.
            index = ( index > 90 ? 180 - index : index );   // Now limit to 0 - 90 degrees.
                                                            // > 90, uses table backwards.
            BREAK_TRUE(((index < 0) || (index > 90)));
            sine = sineTable[index];
            if( deg > 180 ) {                       // Adjust for negative part of sine
                sine = -sine;                       // wave.
            }
            // Note: sine must be scaled down by 10,000.
            
            if (this->header.waveFormat.wBitsPerSample > 24) {
                data = ((9223372036854775807LL - 1) / 10000L) * sine; // Scale for 32 bit PCM.
            }
            else if (this->header.waveFormat.wBitsPerSample > 16) {
                data = ((2147483647L - 1) * sine) / 10000L;        // Scale for 24 bit PCM.
            }
            if (this->header.waveFormat.wBitsPerSample > 8) {
                data = ((32768 - 1) * sine) / 10000L;        // Scale for 16 bit PCM.
            }
            else {
                data = (((128 - 1) * sine) / 10000L) + 128;  // Scale for 8 bit PCM.
            }
            pWave[j] = (int32_t)data;
        }
        
        
        
        // Generate the Sine Wave.
        for( i=0; i<nCycles; ++i ) {
            for( j=0; j<cycleSize; ++j ) {
                audioWAV_AddFrame(
                                  this,
                                  pWave[j],
                                  pWave[j],
                                  pWave[j],
                                  pWave[j],
                                  pWave[j],
                                  silence
                );
            }
        }
        
        mem_Free(pWave);
        pWave = NULL;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = audioWAV__Assign(this,pOther);
     @endcode
     @param     this    AUDIOWAV object pointer
     @param     pOther  a pointer to another AUDIOWAV object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         audioWAV_Assign(
        AUDIOWAV_DATA		*this,
        AUDIOWAV_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( !audioWAV_Validate(pOther) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        //goto eom;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        this->eRc = ERESULT_NOT_IMPLEMENTED; // <-- Remove this!
    //eom:
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        audioWAV      *pCopy = audioWAV_Copy(this);
     @endcode
     @param     this    AUDIOWAV object pointer
     @return    If successful, a AUDIOWAV object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the AUDIOWAV object.
     */
    AUDIOWAV_DATA *     audioWAV_Copy(
        AUDIOWAV_DATA       *this
    )
    {
        AUDIOWAV_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther =    audioWAV_New(
                            this->header.waveFormat.nChannels,
                            this->header.waveFormat.nSamplesPerSec,
                            this->header.waveFormat.wBitsPerSample
                    );
        if (pOther) {
            eRc = audioWAV_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        this->eRc = ERESULT_SUCCESS;
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            audioWAV_Dealloc(
        OBJ_ID          objId
    )
    {
        AUDIOWAV_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((AUDIOWAV_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        audioWAV_setFrames(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         audioWAV_Disable(
        AUDIOWAV_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return this->eRc;
        }
    #ifdef NDEBUG
    #else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }



    //---------------------------------------------------------------
    //                          F o r m a t
    //---------------------------------------------------------------

    ERESULT         audioWAV_FormatSet(
        AUDIOWAV_DATA	*this,
        uint8_t         numberOfChannels,
        uint32_t        samplesPerSecond,   // Normally 11025, 22050, 44100
        uint16_t        sampleSize          // Normally 8, 16, or 32
    )
    {
        uint32_t        nBlockAlign;
        uint32_t        work;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
    #endif
        if ((numberOfChannels == 1) || (numberOfChannels == 2)) {
        }
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
        if ((samplesPerSecond == 11025) || (samplesPerSecond == 22050)
            || (samplesPerSecond == 44100)) {
        }
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
        if ((sampleSize == 8) || (sampleSize == 16) || (sampleSize == 32)) {
        }
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
        nBlockAlign = (numberOfChannels * ((sampleSize + 8-1) / 8));
        
        // Format the Header information.
        memmove(this->header.riff.tagName, "RIFF", 4);
        this->header.riff.length = sizeof(PCM_WAVE_HEADER) - sizeof(PCM_CHUNK);
        //this->header.riff.length += (this->m_SampleNum * this->m_SampleSize);
        memmove(this->header.waveId, "WAVE", 4);
        memmove(this->header.waveFormat.formatChunk.tagName, "fmt ", 4);
        work = sizeof(PCM_WAVE_FORMAT) - sizeof(PCM_CHUNK);
        this->header.waveFormat.formatChunk.length = sizeof(PCM_WAVE_FORMAT) - sizeof(PCM_CHUNK);
        this->header.waveFormat.wFormatTag = 1;         // PCM FORMAT
        this->header.waveFormat.nChannels = numberOfChannels;
        this->header.waveFormat.nSamplesPerSec = samplesPerSecond;
        this->header.waveFormat.wBitsPerSample = sampleSize;
        this->header.waveFormat.nAvgBytesPerSec = nBlockAlign * samplesPerSecond;
        this->header.waveFormat.nBlockAlign = nBlockAlign;
        memmove(this->header.dataChunk.tagName, "data", 4);
        this->header.dataChunk.length = 0;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    AUDIOWAV_DATA * audioWAV_Init(
        AUDIOWAV_DATA   *this,
        uint8_t         numberOfChannels,
        uint32_t        samplesPerSecond,   // Normally 11025, 22050, 44100
        uint16_t        sampleSize          // Normally 8, 16, or 32
    )
    {
        uint32_t        cbSize = sizeof(AUDIOWAV_DATA);

        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        if ((numberOfChannels == 1) || (numberOfChannels == 2)) {
        }
        else {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        if ((samplesPerSecond == 11025) || (samplesPerSecond == 22050)
            || (samplesPerSecond == 44100)) {
        }
        else {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        if ((sampleSize == 8) || (sampleSize == 16) || (sampleSize == 32)) {
        }
        else {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_AUDIOWAV);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_AUDIOWAV);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&audioWAV_Vtbl);
        
        audioWAV_FormatSet(this, numberOfChannels, samplesPerSecond, sampleSize);
        this->pFrames = u8Array_New();

    #ifdef NDEBUG
    #else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->pFrames);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = audioWAV_ToDebugString(this,4);
     @endcode
     @param     this    AUDIOWAV object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     audioWAV_ToDebugString(
        AUDIOWAV_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(audioWAV) size=%d\n",
                     this,
                     audioWAV_getSize(this)
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(audioWAV)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            audioWAV_Validate(
        AUDIOWAV_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_AUDIOWAV) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(AUDIOWAV_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                    W r i t e  T o  F i l e
    //---------------------------------------------------------------
    
    ERESULT         audioWAV_WriteToFile(
        AUDIOWAV_DATA   *this,
        PATH_DATA       *pPath
    )
    {
        FBSO_DATA       *pOutput = OBJ_NIL;
        uint32_t        size;
        uint32_t        work;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !audioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        size = u8Array_getSize(this->pFrames);
        
        pOutput = fbso_New(pPath);
        if (pOutput == OBJ_NIL) {
            this->eRc = ERESULT_GENERAL_FAILURE;
            return this->eRc;
        }
        fbso_setBigEndian(pOutput, false);
        
        // Write the RIFF Chunk.
        fbso_Print(pOutput, "RIFF");
        work = size + this->header.riff.length;
        fbso_PutU32(pOutput, work);
        fbso_Print(pOutput, "WAVE");
        
        // Write the PCM Format.
        fbso_Print(pOutput, "fmt ");
        fbso_PutU32(pOutput, this->header.waveFormat.formatChunk.length);
        fbso_PutU16(pOutput, this->header.waveFormat.wFormatTag);
        fbso_PutU16(pOutput, this->header.waveFormat.nChannels);
        fbso_PutU32(pOutput, this->header.waveFormat.nSamplesPerSec);
        fbso_PutU32(pOutput, this->header.waveFormat.nAvgBytesPerSec);
        fbso_PutU16(pOutput, this->header.waveFormat.nBlockAlign);
        fbso_PutU16(pOutput, this->header.waveFormat.wBitsPerSample);

        // Write the Data.
        fbso_Print(pOutput, "data");
        fbso_PutU32(pOutput, size);
        for (work=0; work<size; ++work) {
            uint8_t         data = 0;
            eRc = u8Array_GetU8(this->pFrames, work+1, &data);
            fbso_PutU8(pOutput, data);
        }

        obj_Release(pOutput);
        pOutput = OBJ_NIL;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


