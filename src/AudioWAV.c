// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   AudioWAV.c
 *  Generated 06/28/2020 10:02:20
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
#include        <AudioWAV_internal.h>
#include        <trace.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    //              Internal 4-place Sine Table
    //     All numbers should be divided by 10000 to get the proper value.
    //     Table is from data in "Modern Plane Trigonometry", William L. Hart,
    //    D.C. Heath and Company, 1961.
    static
    const
    uint16_t        sineTable[91] = {                               // Degrees
        0,  175,  349,  523,  698,  872, 1045, 1219, 1392, 1564,    //     000-009
        1736, 1908, 2079, 2250, 2419, 2588, 2756, 2924, 3090, 3256,    //     010-019
        3420, 3584, 3746, 3907, 4067, 4226, 4384, 4540, 4695, 4848,    //     020-029
        5000, 5150, 5299, 5446, 5592, 5736, 5878, 6018, 6157, 6293,    //     030-039
        6428, 6561, 6691, 6820, 6947, 7071, 7193, 7314, 7431, 7547,    //  040-049
        7660, 7771, 7880, 7986, 8090, 8192, 8290, 8387, 8480, 8572,    //     050-059
        8660, 8746, 8829, 8910, 8988, 9063, 9135, 9205, 9272, 9336,    //     060-069
        9397, 9455, 9511, 9563, 9613, 9659, 9703, 9744, 9781, 9816,    //     070-079
        9848, 9877, 9903, 9925, 9945, 9962, 9976, 9986, 9994, 9998,    //     080-089
        10000                                                        //  090
    };





 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    uint16_t        AudioWAV_getSilenceChar (
        AUDIOWAV_DATA   *this
    )
    {
        uint16_t        data = 0;

        if (this->header.waveFormat.wBitsPerSample < 9) {
            data = 128;
        }
        else {
            data = 0;
        }

        return data;
    }



    bool            AudioWAV_AddChannelData (
        AUDIOWAV_DATA    *this,
        int16_t         channel,
        int32_t         data
    )
    {
        uint32_t        index;

        // Do initialization.
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

        // Return to caller.
        return true;
    }



    bool            AudioWAV_AddFrame (
        AUDIOWAV_DATA   *this,
        int32_t         leftFront,
        int32_t         rightFront,
        int32_t         center,
        int32_t         leftRear,
        int32_t         rightRear,
        int32_t         surround
    )
    {

        switch (this->header.waveFormat.nChannels) {
            case 1:     // Mono
                AudioWAV_AddChannelData(this, 0, leftFront);
                break;

            case 2:     // Stereo
                AudioWAV_AddChannelData(this, 0, leftFront);
                AudioWAV_AddChannelData(this, 1, rightFront);
                break;

            case 3:
                AudioWAV_AddChannelData(this, 0, leftFront);
                AudioWAV_AddChannelData(this, 1, rightFront);
                AudioWAV_AddChannelData(this, 2, center);
                break;

            case 4:     // Quad Stereo
                AudioWAV_AddChannelData(this, 0, leftFront);
                AudioWAV_AddChannelData(this, 1, rightFront);
                AudioWAV_AddChannelData(this, 2, leftRear);
                AudioWAV_AddChannelData(this, 3, rightRear);
                break;

            case 6:
                AudioWAV_AddChannelData(this, 0, leftFront);
                AudioWAV_AddChannelData(this, 1, leftRear);
                AudioWAV_AddChannelData(this, 2, center);
                AudioWAV_AddChannelData(this, 3, rightFront);
                AudioWAV_AddChannelData(this, 4, rightRear);
                AudioWAV_AddChannelData(this, 5, surround);
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

    AUDIOWAV_DATA *     AudioWAV_Alloc (
        void
    )
    {
        AUDIOWAV_DATA       *this;
        uint32_t        cbSize = sizeof(AUDIOWAV_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    AUDIOWAV_DATA * AudioWAV_New (
        void
    )
    {
        AUDIOWAV_DATA   *this;
        
        this = AudioWAV_Alloc( );
        if (this) {
            this = AudioWAV_Init(this);
        } 
        return this;
    }


    AUDIOWAV_DATA * AudioWAV_NewWithParms (
        uint8_t         numberOfChannels,
        uint32_t        samplesPerSecond,   // Normally 11025, 22050, 44100
        uint16_t        sampleSize          // Normally 8, 16, or 32
    )
    {
        AUDIOWAV_DATA   *this;
        ERESULT         eRc;

        this = AudioWAV_New( );
        if (this) {
            eRc = AudioWAV_Setup(this, numberOfChannels, samplesPerSecond, sampleSize);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                    F r a m e s
    //---------------------------------------------------------------

    U8ARRAY_DATA *  AudioWAV_getFrames (
        AUDIOWAV_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pFrames;
    }


    bool            AudioWAV_setFrames (
        AUDIOWAV_DATA   *this,
        U8ARRAY_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
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



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------

    uint16_t        AudioWAV_getNumberOfChannels (
        AUDIOWAV_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->header.waveFormat.nChannels;
    }


    bool            AudioWAV_setNumberOfChannels (
        AUDIOWAV_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->header.waveFormat.nChannels = value;

        return true;
    }



    //---------------------------------------------------------------
    //                  S a m p l e s  p e r  S e c o n d
    //---------------------------------------------------------------

    uint32_t        AudioWAV_getSamplesPerSec (
        AUDIOWAV_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->header.waveFormat.nSamplesPerSec;
    }


    bool            AudioWAV_setSamplesPerSec (
        AUDIOWAV_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->header.waveFormat.nSamplesPerSec = value;

        return true;
    }



    //---------------------------------------------------------------
    //                    S a m p l e  S i z e
    //---------------------------------------------------------------
    
    uint16_t        AudioWAV_getSampleSize (
        AUDIOWAV_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->header.waveFormat.wBitsPerSample;
    }


    bool            AudioWAV_setSampleSize (
        AUDIOWAV_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->header.waveFormat.wBitsPerSample = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        AudioWAV_getSize (
        AUDIOWAV_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  AudioWAV_getSuperVtbl (
        AUDIOWAV_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                   A p p e n d  F r a m e
    //---------------------------------------------------------------

    ERESULT         AudioWAV_AppendFrame (
        AUDIOWAV_DATA   *this,
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
        if( !AudioWAV_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (OBJ_NIL == this->pFrames) {
            this->pFrames = u8Array_New();
            if (OBJ_NIL == this->pFrames) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }

        fRc =   AudioWAV_AddFrame(
                                  this,
                                  leftFront,
                                  rightFront,
                                  center,
                                  leftRear,
                                  rightRear,
                                  surround
                );
        if (!fRc) {
            return ERESULT_GENERAL_FAILURE;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                   A p p e n d  S i l e n c e
    //---------------------------------------------------------------

    ERESULT         AudioWAV_AppendSilence (
        AUDIOWAV_DATA   *this,
        uint32_t        nMilli
    )
    {
        uint64_t        nGross;
        int32_t         data = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !AudioWAV_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (OBJ_NIL == this->pFrames) {
            this->pFrames = u8Array_New();
            if (OBJ_NIL == this->pFrames) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }

        nGross = this->header.waveFormat.nSamplesPerSec * nMilli;
        nGross = nGross / 1000;

        data = AudioWAV_getSilenceChar(this);

        while (nGross--) {
            AudioWAV_AddFrame(this, data, data, data, data, data, data);
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                   A p p e n d  S i n e  W a v e
    //---------------------------------------------------------------

    ERESULT         AudioWAV_AppendSineWave (
        AUDIOWAV_DATA    *this,
        uint16_t        cFreq,              // Frequency (20Hz..20,000Hz)
        uint32_t        nMilli              // Number of Milliseconds
    )
    {
        uint32_t        cycleSize = 0;      // Number of Frames in a Cycle
        uint64_t        nGross;
        uint64_t        nCycles;
        uint32_t        i = 0;
        uint32_t        j = 0;
        uint16_t        silence;
        int32_t         *pWave = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !AudioWAV_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (20 > cFreq) || (20000 < cFreq) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (OBJ_NIL == this->pFrames) {
            this->pFrames = u8Array_New();
            if (OBJ_NIL == this->pFrames) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        cycleSize = (this->header.waveFormat.nSamplesPerSec + (cFreq - 1)) / cFreq;
        nGross = (this->header.waveFormat.nSamplesPerSec * nMilli) / 1000;
        nCycles = (nGross + (cycleSize - 1)) / cycleSize;
        silence = AudioWAV_getSilenceChar(this);

        pWave = mem_Malloc(cycleSize * sizeof(int32_t));
        if (pWave == NULL) {
            return ERESULT_OUT_OF_MEMORY;
        }
        for( j=0; j<cycleSize; ++j ) {
            int32_t         deg;
            uint32_t        index;
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
                AudioWAV_AddFrame(
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
        return ERESULT_SUCCESS;
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
        ERESULT eRc = AudioWAV_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another AUDIOWAV object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         AudioWAV_Assign (
        AUDIOWAV_DATA       *this,
        AUDIOWAV_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!AudioWAV_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

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
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         AudioWAV_Compare (
        AUDIOWAV_DATA     *this,
        AUDIOWAV_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!AudioWAV_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        AudioWAV      *pCopy = AudioWAV_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a AUDIOWAV object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    AUDIOWAV_DATA *     AudioWAV_Copy (
        AUDIOWAV_DATA       *this
    )
    {
        AUDIOWAV_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef AUDIOWAV_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = AudioWAV_New( );
        if (pOther) {
            eRc = AudioWAV_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            AudioWAV_Dealloc (
        OBJ_ID          objId
    )
    {
        AUDIOWAV_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((AUDIOWAV_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        AudioWAV_setFrames(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        AudioWAV      *pDeepCopy = AudioWAV_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a AUDIOWAV object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    AUDIOWAV_DATA *     AudioWAV_DeepyCopy (
        AUDIOWAV_DATA       *this
    )
    {
        AUDIOWAV_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = AudioWAV_New( );
        if (pOther) {
            eRc = AudioWAV_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         AudioWAV_Disable (
        AUDIOWAV_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         AudioWAV_Enable (
        AUDIOWAV_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    AUDIOWAV_DATA *   AudioWAV_Init (
        AUDIOWAV_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(AUDIOWAV_DATA);
        //ERESULT         eRc;
        
        if (OBJ_NIL == this) {
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_AUDIOWAV);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&AudioWAV_Vtbl);
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "AudioWAV::sizeof(AUDIOWAV_DATA) = %lu\n", 
                sizeof(AUDIOWAV_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(AUDIOWAV_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         AudioWAV_IsEnabled (
        AUDIOWAV_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = AudioWAV_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "AudioWAV", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          AudioWAV_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        AUDIOWAV_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(AUDIOWAV_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)AudioWAV_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return AudioWAV_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return AudioWAV_Enable;
                        }
                        break;

                    case 'P':
#ifdef  AUDIOWAV_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return AudioWAV_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return AudioWAV_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return AudioWAV_ToDebugString;
                        }
#ifdef  AUDIOWAV_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return AudioWAV_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return AudioWAV_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == AudioWAV_ToDebugString)
                    return "ToDebugString";
#ifdef  AUDIOWAV_JSON_SUPPORT
                if (pData == AudioWAV_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e t u p
    //---------------------------------------------------------------

    ERESULT         AudioWAV_Setup (
        AUDIOWAV_DATA   *this,
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
        if( !AudioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if ((numberOfChannels == 1) || (numberOfChannels == 2)) {
        }
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if ((samplesPerSecond == 11025) || (samplesPerSecond == 22050)
            || (samplesPerSecond == 44100)) {
        }
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if ((sampleSize == 8) || (sampleSize == 16) || (sampleSize == 32)) {
        }
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
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
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = AudioWAV_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     AudioWAV_ToDebugString (
        AUDIOWAV_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioWAV_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    AudioWAV_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            ASTR_DATA       *pWrkStr = OBJ_NIL;
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            AudioWAV_Validate (
        AUDIOWAV_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_AUDIOWAV))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(AUDIOWAV_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                    W r i t e  T o  F i l e
    //---------------------------------------------------------------

    ERESULT         AudioWAV_WriteToFile (
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
        if( !AudioWAV_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        size = u8Array_getSize(this->pFrames);

        pOutput = fbso_New(pPath);
        if (pOutput == OBJ_NIL) {
            return ERESULT_GENERAL_FAILURE;
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
        return ERESULT_SUCCESS;
    }




    
#ifdef  __cplusplus
}
#endif


