// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Opcodes_internal.h
 *	Generated 02/27/2020 16:46:25
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




#include        <Opcodes.h>
#include        <JsonIn.h>
#include        <Opcode_internal.h>
#include        <szBT.h>


#ifndef OPCODES_INTERNAL_H
#define	OPCODES_INTERNAL_H





#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Opcodes_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    SZBT_DATA       *pTree;

};
#pragma pack(pop)

    extern
    struct Opcodes_class_data_s  Opcodes_ClassObj;

    extern
    const
    OPCODES_VTBL         Opcodes_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OPCODES_SINGLETON
    OPCODES_DATA *  Opcodes_getSingleton (
        void
    );

    bool            Opcodes_setSingleton (
     OPCODES_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Opcodes_getSuperVtbl (
        OPCODES_DATA     *this
    );


    SZBT_DATA *     Opcodes_getTree (
        OPCODES_DATA    *this
    );


    ERESULT         Opcodes_Assign (
        OPCODES_DATA    *this,
        OPCODES_DATA    *pOther
    );


    OPCODES_DATA *       Opcodes_Copy (
        OPCODES_DATA     *this
    );


    void            Opcodes_Dealloc (
        OBJ_ID          objId
    );


#ifdef  OPCODES_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    OPCODES_DATA *       Opcodes_ParseJsonObject (
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
    ERESULT         Opcodes_ParseJsonFields (
        JSONIN_DATA     *pParser,
        OPCODES_DATA     *pObject
    );
#endif


    void *          Opcodes_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  OPCODES_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Opcodes_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Opcodes_ToJson (
        OPCODES_DATA      *this
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
    ERESULT         Opcodes_ToJsonFields (
        OPCODES_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			Opcodes_Validate (
        OPCODES_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OPCODES_INTERNAL_H */

