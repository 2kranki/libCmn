// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Sect_internal.h
 *  Generated 12/27/2020 14:58:15
 *
 * Notes:
 *  --  N/A
 *
 * Todo:
 *  --  Debug information (see DWARF specification???)
 *  --  Relocation information
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




#include        <Sect.h>
#include        <JsonIn.h>
#include        <Node_internal.h>


#ifndef SECT_INTERNAL_H
#define SECT_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Sect_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    char            ident;
    char            type;
    uint8_t         rsvd8_1;
    uint8_t         rsvd8_2;
    uint32_t        section;        // Section Identifier (Used in Symbols)
    uint32_t        esid;           // Internal Identifier
    uint32_t        addr;           // virtual address
    uint32_t        len;            // section length ???
    uint32_t        offset;         // offset of what ???
    ASTR_DATA       *pName;
    U8ARRAY_DATA    *pData;
    SYMS_DATA       *pExterns;
    SYMS_DATA       *pPublics;
    //???_DATA        *pReloc;        // Relocation Dictionary
    //???_DATA        *pReloc;        // Debug Data (see DWARF specification???)

};
#pragma pack(pop)

    extern
    struct Sect_class_data_s  Sect_ClassObj;

    extern
    const
    SECT_VTBL         Sect_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SECT_SINGLETON
    SECT_DATA *     Sect_getSingleton (
        void
    );

    bool            Sect_setSingleton (
     SECT_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_DATA *      Sect_getSuper (
        SECT_DATA       *this
    );


    OBJ_IUNKNOWN *  Sect_getSuperVtbl (
        SECT_DATA     *this
    );


    ERESULT         Sect_Assign (
        SECT_DATA    *this,
        SECT_DATA    *pOther
    );


    SECT_DATA *       Sect_Copy (
        SECT_DATA     *this
    );


    void            Sect_Dealloc (
        OBJ_ID          objId
    );


#ifdef  SECT_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SECT_DATA *       Sect_ParseJsonObject (
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
    ERESULT         Sect_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SECT_DATA     *pObject
    );
#endif


    void *          Sect_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SECT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Sect_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Sect_ToJson (
        SECT_DATA      *this
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
    ERESULT         Sect_ToJsonFields (
        SECT_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            Sect_Validate (
        SECT_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* SECT_INTERNAL_H */

