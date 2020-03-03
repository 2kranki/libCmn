// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Sym_internal.h
 *	Generated 02/22/2020 20:18:12
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




#include        <Sym.h>
#include        <JsonIn.h>


#ifndef SYM_INTERNAL_H
#define	SYM_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif



#pragma pack(push, 1)
    typedef struct sym_entry_s {
        uint16_t        Flags;
        #define SYM_ABS     0x8000              // Absolute value
        #define SYM_REL     0x4000              // Relocatable value
        // Note: Abs or Rel may not be valid in initial passes.
        uint32_t        Hash;               // Hash Code for name
#define SYM_ENTRY_NAME_MAX  64
        char            Name[64];           // NUL-terminated name
        uint32_t        Token;              // unique token for name
        int32_t         Cls;                // User Defined Class
        int32_t         Type;               // See SYM_TYPE
        uint16_t        Prim;               // See SYM_PRIMITIVE;
        uint16_t        Len;                // Data Length in Bytes
        uint16_t        Dup;                // Duplication Factor
        uint16_t        Align;              // Required Storage Alignment
        //                                  //  0 == None (same as 1)
        //                                  //  1 == Byte Boundary
        //                                  //  2 == 16 Bit Boundary
        //                                  //  4 == 32 Bit Boundary
        //                                  //  8 == 64 Bit Boundary
        //                                  // 16 == 128 Bit Boundary
        uint16_t        Scale;
        int32_t         Value;
    } SYM_ENTRY;
#pragma pack(pop)



    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Sym_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    SYM_ENTRY       entry;

};
#pragma pack(pop)

    extern
    struct Sym_class_data_s  Sym_ClassObj;

    extern
    const
    SYM_VTBL         Sym_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SYM_SINGLETON
    SYM_DATA *      Sym_getSingleton (
        void
    );

    bool            Sym_setSingleton (
     SYM_DATA           *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    SYM_ENTRY *     Sym_getEntry (
        SYM_DATA        *this
    );


    bool            Sym_setNameA (
        SYM_DATA        *this,
        const
        char            *pValue
    );


    OBJ_IUNKNOWN *  Sym_getSuperVtbl (
        SYM_DATA        *this
    );


    ERESULT         Sym_Assign (
        SYM_DATA        *this,
        SYM_DATA        *pOther
    );


    SYM_DATA *      Sym_Copy (
        SYM_DATA        *this
    );


    void            Sym_Dealloc (
        OBJ_ID          objId
    );


#ifdef  SYM_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SYM_DATA *       Sym_ParseJsonObject (
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
    ERESULT         Sym_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SYM_DATA     *pObject
    );
#endif


    void *          Sym_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SYM_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Sym_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Sym_ToJson (
        SYM_DATA      *this
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
    ERESULT         Sym_ToJsonFields (
        SYM_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			Sym_Validate (
        SYM_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SYM_INTERNAL_H */

