// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   AudioCW_internal.h
 *  Generated 06/28/2020 10:01:55
 *
 * Notes:
 *  --  N/A
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




#include        <AudioCW.h>
#include        <AudioWAV.h>
#include        <JsonIn.h>


#ifndef AUDIOCW_INTERNAL_H
#define AUDIOCW_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct AudioCW_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    AUDIOWAV_DATA   *pWave;
    int32_t         lastChar;
    uint16_t        freq;
    uint16_t        rsvd16;

    // CW Timing Data
    uint16_t        wpmChar;                // Character Speed in Wpm
    uint16_t        wpmText;                // Text Speed in Wpm
    uint16_t        timeDit;                // Dit Time in Milliseconds
    uint16_t        timeDah;                // Dit Time in Milliseconds
    //                                        //        Dah Time is 3 * TimeDit
    uint16_t        timeFrn;                // Farnsworth Time in Milliseconds
    uint16_t        timeIcg;                // Inter-Character Gap Time in Milliseconds
    uint16_t        timeIdg;                // Inter-Dit Gap Time in Milliseconds
    uint16_t        timeIwg;                // Inter-Word Gap Time in Milliseconds

};
#pragma pack(pop)

    extern
    struct AudioCW_class_data_s  AudioCW_ClassObj;

    extern
    const
    AUDIOCW_VTBL         AudioCW_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  AUDIOCW_SINGLETON
    AUDIOCW_DATA *     AudioCW_getSingleton (
        void
    );

    bool            AudioCW_setSingleton (
     AUDIOCW_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  AudioCW_getSuperVtbl (
        AUDIOCW_DATA     *this
    );


    ERESULT         AudioCW_Assign (
        AUDIOCW_DATA    *this,
        AUDIOCW_DATA    *pOther
    );


    AUDIOCW_DATA *       AudioCW_Copy (
        AUDIOCW_DATA     *this
    );


    void            AudioCW_Dealloc (
        OBJ_ID          objId
    );


#ifdef  AUDIOCW_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    AUDIOCW_DATA *       AudioCW_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         AudioCW_ParseJsonFields (
        JSONIN_DATA     *pParser,
        AUDIOCW_DATA     *pObject
    );
#endif


    void *          AudioCW_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  AUDIOCW_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = AudioCW_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     AudioCW_ToJson (
        AUDIOCW_DATA      *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         AudioCW_ToJsonFields (
        AUDIOCW_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            AudioCW_Validate (
        AUDIOCW_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* AUDIOCW_INTERNAL_H */

