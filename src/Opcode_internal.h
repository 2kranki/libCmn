// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Opcode_internal.h
 *	Generated 02/27/2020 14:36:27
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




#include        <Opcode.h>
#include        <JsonIn.h>


#ifndef OPCODE_INTERNAL_H
#define	OPCODE_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Opcode_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    OPCODE_ENTRY    entry;
    const
    char *          (*pFeatureDesc) (uint16_t);
    uint16_t        (*pFeatureValue) (const char *);
    const
    char *          (*pInterruptDesc) (uint16_t);
    uint16_t        (*pInterruptValue) (const char *);
    const
    char *          (*pTypeDesc) (uint16_t);
    uint16_t        (*pTypeValue) (const char *);

    ERESULT         (*pExec)(OBJ_ID, OBJ_ID);
    OBJ_ID          pObjExec;
    ERESULT         (*pPrs)(OBJ_ID, OBJ_ID);
    OBJ_ID          pObjPrs;

};
#pragma pack(pop)

    extern
    struct Opcode_class_data_s  Opcode_ClassObj;

    extern
    const
    OPCODE_VTBL         Opcode_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OPCODE_SINGLETON
    OPCODE_DATA *   Opcode_getSingleton (
        void
    );

    bool            Opcode_setSingleton (
     OPCODE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            Opcode_setEntry (
        OPCODE_DATA     *this,
        OPCODE_ENTRY    *pEntry
    );


    bool            Opcode_setNameA (
        OPCODE_DATA     *this,
        const
        char            *pValue
    );


    OBJ_IUNKNOWN *  Opcode_getSuperVtbl (
        OPCODE_DATA     *this
    );


    ERESULT         Opcode_Assign (
        OPCODE_DATA    *this,
        OPCODE_DATA    *pOther
    );


    OPCODE_DATA *       Opcode_Copy (
        OPCODE_DATA     *this
    );


    void            Opcode_Dealloc (
        OBJ_ID          objId
    );


#ifdef  OPCODE_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    OPCODE_DATA *   Opcode_ParseJsonObject (
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
    ERESULT         Opcode_ParseJsonFields (
        JSONIN_DATA     *pParser,
        OPCODE_DATA     *pObject
    );
#endif


    void *          Opcode_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  OPCODE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Opcode_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Opcode_ToJson (
        OPCODE_DATA      *this
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
    ERESULT         Opcode_ToJsonFields (
        OPCODE_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			Opcode_Validate (
        OPCODE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OPCODE_INTERNAL_H */

