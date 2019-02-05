// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   symEntry_internal.h
 *	Generated 11/04/2018 21:12:53
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




#include        <symEntry.h>
#include        <jsonIn.h>
#include        <nodeLink_internal.h>


#ifndef SYMENTRY_INTERNAL_H
#define	SYMENTRY_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

    typedef enum sym_primitive_e {
        SYM_PRIMITIVE_UNDEFINED=0,
        SYM_PRIMITIVE_INT8,
        SYM_PRIMITIVE_UINT8,
        SYM_PRIMITIVE_INT16,
        SYM_PRIMITIVE_UINT16,
        SYM_PRIMITIVE_INT32,
        SYM_PRIMITIVE_UINT32,
        SYM_PRIMITIVE_INT64,
        SYM_PRIMITIVE_UINT64,
        SYM_PRIMITIVE_INT128,
        SYM_PRIMITIVE_UINT128,
        SYM_PRIMITIVE_INT256,
        SYM_PRIMITIVE_UINT256,
        SYM_PRIMITIVE_CHAR,
        SYM_PRIMITIVE_CHAR_SIGNED,
        SYM_PRIMITIVE_CHAR_UNSIGNED,
        SYM_PRIMITIVE_FUNCTION,
        SYM_PRIMITIVE_INT,
        SYM_PRIMITIVE_INT_SIGNED,
        SYM_PRIMITIVE_INT_UNSIGNED,
        SYM_PRIMITIVE_SHORT,
        SYM_PRIMITIVE_SHORT_SIGNED,       // ????
        SYM_PRIMITIVE_SHORT_UNSIGNED,
        SYM_PRIMITIVE_LONG,
        SYM_PRIMITIVE_LONG_SIGNED,       // ????
        SYM_PRIMITIVE_LONG_UNSIGNED,
        SYM_PRIMITIVE_LONGLONG,
        SYM_PRIMITIVE_LONGLONG_SIGNED,       // ????
        SYM_PRIMITIVE_LONGLONG_UNSIGNED,
        SYM_PRIMITIVE_STRUCT,
        SYM_PRIMITIVE_UNION,
        SYM_PRIMITIVE_VOID,
    } SYM_PRIMITIVE;
    
    
    typedef enum sym_storage_e {
        SYM_STORAGE_UNDEFINED=0,
        SYM_STORAGE_AUTO,           // Auto allocated local identifiers
        SYM_STORAGE_EXTERN,
        SYM_STORAGE_LOCAL,
        SYM_STORAGE_MEMBER,                 // ???
        SYM_STORAGE_PUBLIC,
        SYM_STORAGE_SPROTO,                 // ???
        SYM_STORAGE_STATIC,         // static identifiers in global context
        SYM_STORAGE_STATIC_LOCAL,   // static identifiers in local context
        SYM_STORAGE_STRUCT,
    } SYM_STORAGE;
    
    
    typedef enum sym_reloc_e {
        SYM_RELOC_UNDEFINED=0,
        SYM_RELOC_ABSOLUTE,
        SYM_RELOC_RELOCATABLE,
    } SYM_RELOC;
    
    
    typedef struct sym_entry_s {
        uint16_t        cbSize;             // Control Block Size in bytes
        uint16_t        flags;
        uint32_t        hash;
        uint32_t        token;              // unique token for name
        char            name[128];
        int32_t         cls;                // User Defined Class
        int32_t         type;               // See SYM_TYPE
        uint32_t        prim;               // See SYM_PRIMITIVE;
        uint32_t        size;               // Data Size in Bytes
        uint16_t        ptr;                // Pointer level
        uint16_t        align;              // Required Storage Alignment
        //                                  // (0 == None)
        uint16_t        reloc;
        int16_t         level;
        uint16_t        dup;                // Duplication Factor
        uint16_t        len;
        //uint16_t        rsvd16;
        uint32_t        section;
        uint32_t        value;
        uint32_t        idxHashNext;        // Hash Index Chain
        uint32_t        idxHashPrev;
        uint32_t        idxScopeNext;
        uint32_t        idxScopePrev;
        uint32_t        idxParent;
        uint32_t        idxChildHead;       // Child Chain
        uint32_t        idxChildTail;
        uint32_t        idxSibHead;         // Sibling Chain
        uint32_t        idxSibTail;
        uint32_t        attr;               // symAttr Index
    } SYM_ENTRY;
    
    
    
    
    
    
#pragma pack(push, 1)
struct symEntry_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    NODELINK_DATA   super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    SYM_ENTRY       entry;

};
#pragma pack(pop)

    extern
    struct symEntry_class_data_s  symEntry_ClassObj;

    extern
    const
    SYMENTRY_VTBL         symEntry_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SYMENTRY_SINGLETON
    SYMENTRY_DATA * symEntry_getSingleton(
        void
    );

    bool            symEntry_setSingleton(
     SYMENTRY_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            symEntry_setClass (
        SYMENTRY_DATA   *this,
        int32_t         value
    );
    
    
    bool            symEntry_setLevel (
        SYMENTRY_DATA   *this,
        int16_t         value
    );
    
    
    bool            symEntry_setNameA (
        SYMENTRY_DATA   *this,
        const
        char            *pValue
    );
    
    
    OBJ_IUNKNOWN *  symEntry_getSuperVtbl (
        SYMENTRY_DATA   *this
    );


    void            symEntry_Dealloc (
        OBJ_ID          objId
    );


    SYMENTRY_DATA *       symEntry_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          symEntry_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     symEntry_ToJSON (
        SYMENTRY_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			symEntry_Validate (
        SYMENTRY_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SYMENTRY_INTERNAL_H */

