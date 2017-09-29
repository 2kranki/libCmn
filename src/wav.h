// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          WAV File Read/Write (wav) Header
//****************************************************************
/*
 * Program
 *			WAV File Read/Write (wav)
 * Purpose
 *			This object provides support to create wav audio files.
 *
 *          The binary data within the file is in little endian
 *          order. Therefore, we must be careful in processing
 *          it.
 *
 * Remarks
 *	1.      The largest bits per ?? supported is 32 bits.
 *
 * History
 *	11/23/2015 Generated
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





#include        <cmn_defs.h>
#include        <AStr.h>


#ifndef         WAV_H
#define         WAV_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct wav_data_s	WAV_DATA;

    typedef struct wav_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in table_object.c.
    } WAV_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the wav including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    WAV_DATA *     wav_Alloc(
        void
    );
    
    
    WAV_DATA *     wav_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         wav_getLastError(
        WAV_DATA        *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         wav_Append(
        WAV_DATA		*this,
        WAV_DATA		*pOther
    );


    ERESULT         wav_AppendSilence(
        WAV_DATA		*this,
        uint32_t		nMilli              // Number of Milliseconds
    );
    
    
    ERESULT         wav_AppendSineWave(
        WAV_DATA		*this,
        uint16_t		cFreq,              // Frequency (20Hz..20,000Hz)
        uint32_t		cMilli              // Number of Milliseconds
    );
    
    
    WAV_DATA *      wav_Copy(
        WAV_DATA        *this
    );
    
    
    WAV_DATA *      wav_Init(
        WAV_DATA        *this
    );


    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     wav_ToDebugString(
        WAV_DATA        *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* WAV_H */

