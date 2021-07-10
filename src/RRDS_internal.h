// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   RRDS_internal.h
 *  Generated 07/10/2021 09:44:02
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




#include        <RRDS.h>
#include        <fileio.h>
#include        <JsonIn.h>
#include        <lru_internal.h>


#ifndef RRDS_INTERNAL_H
#define RRDS_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct RRDS_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    LRU_DATA        *pLRU;
    FILEIO_DATA     *pIO;
    uint16_t        recordSize;     // Real Record Size including Record Terminators
    uint16_t        reqSize;        // Requested Record Size without optional
    //                              // terminators included
    uint16_t        cLRU;
    uint16_t        cHash;
    uint8_t         recordTerm;     // Record Terminator (see enum RRDS_rcd_trm_e)
    uint8_t         fillChar;
    uint8_t         rsvd8[2];
    uint32_t        cRecords;

};
#pragma pack(pop)

    extern
    struct RRDS_class_data_s  RRDS_ClassObj;

    extern
    const
    RRDS_VTBL         RRDS_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  RRDS_SINGLETON
    RRDS_DATA *     RRDS_getSingleton (
        void
    );

    bool            RRDS_setSingleton (
     RRDS_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            RRDS_setFileIO (
        RRDS_DATA       *this,
        OBJ_ID          pValue
    );


    OBJ_IUNKNOWN *  RRDS_getSuperVtbl (
        RRDS_DATA       *this
    );


    ERESULT         RRDS_Assign (
        RRDS_DATA       *this,
        RRDS_DATA       *pOther
    );


    RRDS_DATA *     RRDS_Copy (
        RRDS_DATA       *this
    );


    void            RRDS_Dealloc (
        OBJ_ID          objId
    );


#ifdef  RRDS_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    RRDS_DATA *     RRDS_ParseJsonObject (
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
    ERESULT         RRDS_ParseJsonFields (
        JSONIN_DATA     *pParser,
        RRDS_DATA       *pObject
    );
#endif


    void *          RRDS_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  RRDS_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = RRDS_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RRDS_ToJson (
        RRDS_DATA       *this
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
    ERESULT         RRDS_ToJsonFields (
        RRDS_DATA       *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            RRDS_Validate (
        RRDS_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* RRDS_INTERNAL_H */

