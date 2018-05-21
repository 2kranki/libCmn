// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   wav.c
 *	Generated 11/23/2015 06:58:45
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
#include <wav_internal.h>
#include <stdint.h>
#include <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    
    //		Internal 4-place Sine Table
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
        10000															//  090
    };
    
    
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    int16_t         swap_int16(
        int16_t         value
    );
    
    static
    int32_t         swap_int32(
        int32_t         value
    );
#endif

    
    bool            wav_AddChannelData(
        WAV_DATA		*this,
        int32_t         data
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !wav_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        switch (this->header.waveFormat.wBitsPerSample) {
            case 8:
                u8Array_AppendData(this->pFrames, data & 0xFF);
                break;
                
            case 16:
                u8Array_AppendData(this->pFrames, data & 0xFF);
                u8Array_AppendData(this->pFrames, (data >> 8) & 0xFF);
                break;
                
            case 24:
                u8Array_AppendData(this->pFrames, data & 0xFF);
                u8Array_AppendData(this->pFrames, (data >> 8) & 0xFF);
                u8Array_AppendData(this->pFrames, (data >> 16) & 0xFF);
                break;
                
            case 32:
                u8Array_AppendData(this->pFrames, data & 0xFF);
                u8Array_AppendData(this->pFrames, (data >> 8) & 0xFF);
                u8Array_AppendData(this->pFrames, (data >> 16) & 0xFF);
                u8Array_AppendData(this->pFrames, (data >> 24) & 0xFF);
                break;
                
            default:
                DEBUG_BREAK();
                break;
        }
        return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    bool            wav_AddFrame(
        WAV_DATA		*this,
        int32_t         left,
        int32_t         right
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !wav_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        switch (this->header.waveFormat.nChannels) {
            case 1:     // Mono
                wav_AddChannelData(this, left);
                break;
                
            case 2:     // Stereo
                wav_AddChannelData(this, left);
                wav_AddChannelData(this, right);
                break;
                
            default:
                break;
        }
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    // Only swaps if computer is big endian.
#ifdef XYZZY
    static
    int16_t         swap_int16(
        int16_t         value
    )
    {
        int             i = 1;
        
        if (1 == (int)*((unsigned char *)&i)) {
            return value;
        }
        return (value << 8) | ((value >> 8) & 0xFF);
    }



    // Only swaps if computer is big endian.
    static
    int32_t         swap_int32(
        int32_t         value
    )
    {
        int             i = 1;
        
        if (1 == (int)*((unsigned char *)&i)) {
            return value;
        }
        value = ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0xFF00FF );
        return (value << 16) | ((value >> 16) & 0xFFFF);
    }
#endif

    
    
    
    
    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    WAV_DATA *      wav_Alloc(
    )
    {
        WAV_DATA        *this;
        uint32_t        cbSize = sizeof(WAV_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    WAV_DATA *      wav_New(
    )
    {
        WAV_DATA        *this;
        
        this = wav_Alloc( );
        if (this) {
            this = wav_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    U8ARRAY_DATA *  wav_getArray(
        WAV_DATA        *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !wav_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        //return cbp->pArray;
        return 0;
    }
    
    
    bool            wav_setArray(
        WAV_DATA        *this,
        U8ARRAY_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !wav_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        //if (this->pArray) {
            //obj_Release(this->pArray);
        //}
        //this->pArray = pValue;
        
        return true;
    }
    
    
    
    ERESULT         wav_getLastErrorCode(
        WAV_DATA        *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !wav_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        //return cbp->priority;
        return 0;
    }
    
    
    
    
    uint16_t        wav_getPriority(
        WAV_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !wav_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            wav_setPriority(
        WAV_DATA        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !wav_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    uint32_t        wav_getSize(
        WAV_DATA        *this
    )
    {
#ifdef NDEBUG
#else
        if( !wav_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return( 0 );
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                   A p p e n d  S i l e n c e
    //---------------------------------------------------------------
    
    ERESULT         wav_AppendSilence(
        WAV_DATA		*this,
        uint32_t        nMilli
    )
    {
        uint64_t        nGross;
        int32_t         data = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !wav_Validate( this ) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        nGross = this->header.waveFormat.nSamplesPerSec * nMilli;
        nGross = nGross / 1000;
        if (this->header.waveFormat.wBitsPerSample < 9) {
            nGross = 128;
        }
        
        if (this->header.waveFormat.wBitsPerSample) {
            data = 128;
        }
        else {
            data = 0;
        }

        while (nGross--) {
            wav_AddFrame(this, data, data);
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                   A p p e n d  S i n e  W a v e
    //---------------------------------------------------------------
    
    ERESULT         wav_AppendSineWave(
        WAV_DATA		*this,
        uint16_t		cFreq,              // Frequency (20Hz..20,000Hz)
        uint32_t		nMilli              // Number of Milliseconds
    )
    {
        uint32_t        cycleSize = 0;      // Number of Frames in a Cycle
        uint64_t        nGross;
        uint64_t        nCycles;
        uint32_t		i = 0;
        uint32_t		j = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !wav_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (20 > cFreq) || (20000 < cFreq) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        cycleSize = (this->header.waveFormat.nSamplesPerSec + (cFreq - 1)) / cFreq;
        nGross = this->header.waveFormat.nSamplesPerSec * nMilli;
        nGross = nGross / 1000;
        nCycles = (nGross + (cycleSize - 1)) / cycleSize;
        
        // Generate the Sine Wave.
        for( i=0; i<nCycles; ++i ) {
            for( j=0; j<cycleSize; ++j ) {
                int32_t			deg;
                int32_t			r;
                deg = ((360 * j) + cycleSize - 1) / cycleSize;
                r = ( deg >= 180 ? deg - 180 : deg );
                r = ( r > 90 ? 180 - r : r );
                r = sineTable[ r ];
                if( deg > 180 )
                    r = -r;
                r = (INT16_MAX * r) / 10000L;
                if (this->header.waveFormat.wBitsPerSample < 9) {
                    r = (r + 32768) / 256;
                }
                wav_AddFrame(this, r, r);
            }
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    

    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            wav_Dealloc(
        OBJ_ID          objId
    )
    {
        WAV_DATA        *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !wav_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        //if (this->pArray) {
            //obj_Release(this->pArray);
            //cbp->pArray = OBJ_NIL;
        //}

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    WAV_DATA *      wav_Init(
        WAV_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(WAV_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (WAV_DATA *)obj_Init( this, cbSize, OBJ_IDENT_WAV );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_WAV);
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&wav_Vtbl);
        
        //cbp->stackSize = obj_getMisc1(cbp);
        //cbp->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !wav_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            wav_IsEnabled(
        WAV_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !wav_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(this))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     wav_ToDebugString(
        WAV_DATA        *this,
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
                     "{%p(wav) side=%d ",
                     this,
                     wav_getSize(this)
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->toDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->toDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf( str, sizeof(str), " %p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            wav_Validate(
        WAV_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if(this) {
            if ( obj_IsKindOf(this,OBJ_IDENT_WAV) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(WAV_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                   W r i t e  T o  F i l e
    //---------------------------------------------------------------
    
    ERESULT         wav_WriteToFile(
        WAV_DATA		*this,
        PATH_DATA       *pPath
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !wav_Validate( this ) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        // Return to caller.
        this->eRc = ERESULT_NOT_IMPLEMENTED;
        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


