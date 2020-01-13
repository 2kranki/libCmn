// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   audioCW_internal.h
 *	Generated 09/19/2016 20:11:01
 *
 * Notes:
 *  --	N/A
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



#include    <audioCW.h>
#include    <audioWAV.h>


#ifndef AUDIOCW_INTERNAL_H
#define	AUDIOCW_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct audioCW_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    
    // CW Timing Data
    uint16_t        wpmChar;				// Character Speed in Wpm
    uint16_t		wpmText;				// Text Speed in Wpm
    uint16_t		timeDit;				// Dit Time in Milliseconds
    uint16_t		timeDah;				// Dit Time in Milliseconds
    //										//		Dah Time is 3 * TimeDit
    uint16_t		timeFrn;				// Farnsworth Time in Milliseconds
    uint16_t		timeIcg;				// Inter-Character Gap Time in Milliseconds
    uint16_t		timeIdg;				// Inter-Dit Gap Time in Milliseconds
    uint16_t		timeIwg;				// Inter-Word Gap Time in Milliseconds
    
    AUDIOWAV_DATA   *pWave;
    int32_t         lastChar;
    uint16_t		freq;
    
};
#pragma pack(pop)

    extern
    const
    struct audioCW_class_data_s  audioCW_ClassObj;

    extern
    const
    AUDIOCW_VTBL    audioCW_Vtbl;


    // Internal Functions
    void            audioCW_Dealloc(
        OBJ_ID          objId
    );



#ifdef NDEBUG
#else
    bool			audioCW_Validate(
        AUDIOCW_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* AUDIOCW_INTERNAL_H */

