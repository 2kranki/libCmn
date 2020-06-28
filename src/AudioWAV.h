// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  WAV File Audio (AudioWAV) Header
//****************************************************************
/*
 * Program
 *          WAV File Audio (AudioWAV)
 * Purpose
 *          This object provides support for wav audio files.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  09/19/2016 Generated
 *  06/28/2020 Regenerated and updated to new naming convention
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


#ifndef         AUDIOWAV_H
#define         AUDIOWAV_H


//#define   AUDIOWAV_IS_IMMUTABLE     1
//#define   AUDIOWAV_JSON_SUPPORT     1
//#define   AUDIOWAV_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct AudioWAV_data_s  AUDIOWAV_DATA;            // Inherits from OBJ
    typedef struct AudioWAV_class_data_s AUDIOWAV_CLASS_DATA;   // Inherits from OBJ

    typedef struct AudioWAV_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in AudioWAV_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(AUDIOWAV_DATA *);
    } AUDIOWAV_VTBL;

    typedef struct AudioWAV_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in AudioWAV_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(AUDIOWAV_DATA *);
    } AUDIOWAV_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  AUDIOWAV_SINGLETON
    AUDIOWAV_DATA * AudioWAV_Shared (
        void
    );

    void            AudioWAV_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to AudioWAV object if successful, otherwise OBJ_NIL.
     */
    AUDIOWAV_DATA * AudioWAV_Alloc (
        void
    );
    
    
    OBJ_ID          AudioWAV_Class (
        void
    );
    
    
    AUDIOWAV_DATA * AudioWAV_New (
        void
    );
    
    AUDIOWAV_DATA * AudioWAV_NewWithParms (
        uint8_t         numberOfChannels,
        uint32_t        samplesPerSecond,   // Normally 11025, 22050, 44100
        uint16_t        sampleSize          // Normally 8, 16, or 32
    );


#ifdef  AUDIOWAV_JSON_SUPPORT
    AUDIOWAV_DATA * AudioWAV_NewFromJsonString (
        ASTR_DATA       *pString
    );

    AUDIOWAV_DATA * AudioWAV_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        AudioWAV_getNumberOfChannels (
        AUDIOWAV_DATA   *this
    );


    uint32_t        AudioWAV_getSamplesPerSec (
        AUDIOWAV_DATA   *this
    );


    uint16_t        AudioWAV_getSampleSize (
        AUDIOWAV_DATA   *this
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         AudioWAV_Append (
        AUDIOWAV_DATA   *this,
        AUDIOWAV_DATA   *pOther
    );


    ERESULT         AudioWAV_AppendFrame (
        AUDIOWAV_DATA   *this,
        int32_t         leftFront,
        int32_t         rightFront,
        int32_t         center,
        int32_t         leftRear,
        int32_t         rightRear,
        int32_t         surround
    );


    ERESULT         AudioWAV_AppendSilence (
        AUDIOWAV_DATA   *this,
        uint32_t        nMilli              // Number of Milliseconds
    );


    ERESULT         AudioWAV_AppendSineWave (
        AUDIOWAV_DATA   *this,
        uint16_t        cFreq,              // Frequency (20Hz..20,000Hz)
        uint32_t        cMilli              // Number of Milliseconds
    );


    AUDIOWAV_DATA * AudioWAV_Init (
        AUDIOWAV_DATA   *this
    );


    ERESULT         AudioWAV_Setup (
        AUDIOWAV_DATA   *this,
        uint8_t         numberOfChannels,
        uint32_t        samplesPerSecond,   // Normally 11025, 22050, 44100
        uint16_t        sampleSize          // Normally 8, 16, or 32
    );
    
 
#ifdef  AUDIOWAV_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = AudioWAV_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     AudioWAV_ToJson (
        AUDIOWAV_DATA   *this
    );
#endif


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
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     AudioWAV_ToDebugString (
        AUDIOWAV_DATA     *this,
        int             indent
    );
    
    
    ERESULT         AudioWAV_WriteToFile (
        AUDIOWAV_DATA   *this,
        PATH_DATA       *pPath
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* AUDIOWAV_H */

