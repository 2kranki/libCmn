// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   symAttr_internal.h
 *	Generated 02/02/2018 10:14:55
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




#include    <symAttr.h>
#include    <value.h>


#ifndef SYMATTR_INTERNAL_H
#define	SYMATTR_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif


    
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
        SYM_PRIMITIVE_SHORT_SIGNED,
        SYM_PRIMITIVE_SHORT_UNSIGNED,
        SYM_PRIMITIVE_LONG,
        SYM_PRIMITIVE_LONG_SIGNED,
        SYM_PRIMITIVE_LONG_UNSIGNED,
        SYM_PRIMITIVE_LONGLONG,
        SYM_PRIMITIVE_LONGLONG_SIGNED,       
        SYM_PRIMITIVE_LONGLONG_UNSIGNED,
        SYM_PRIMITIVE_STRUCT,
        SYM_PRIMITIVE_UNION,
        SYM_PRIMITIVE_VOID
    } SYM_PRIMITIVE;
    
    
    typedef enum sym_storage_e {
        SYM_STORAGE_UNDEFINED=0,
        SYM_STORAGE_AUTO,           // Auto allocated local identifiers
        SYM_STORAGE_EXTERN,
        SYM_STORAGE_LOCAL,
        SYM_STORAGE_MEMBER,         // ???
        SYM_STORAGE_PUBLIC,
        SYM_STORAGE_SPROTO,         // ???
        SYM_STORAGE_STATIC,         // static identifiers in global context
        SYM_STORAGE_STATIC_LOCAL,   // static identifiers in local context
        SYM_STORAGE_STRUCT
    } SYM_STORAGE;
    
    
    typedef enum sym_type_e {
        SYM_TYPE_UNDEFINED=0,
        SYM_TYPE_ARRAY,
        SYM_TYPE_CONSTANT,
        SYM_TYPE_FUNCTION,
        SYM_TYPE_MACRO,
        SYM_TYPE_STRUCT,
        SYM_TYPE_UNION,
        SYM_TYPE_VARIABLE
    } SYM_TYPE;
    
    

    typedef struct sym_attr_s {
        uint16_t        cbSize;             // Control Block Size in bytes
        uint16_t        flags;
        uint32_t        nameHash;
        char            name[129];          // Name with trailing NUL
        char            genName[65];        // Generated External Name with trailing NUL
        uint32_t        nameToken;          // szTbl Token for name
        int32_t         cls;                // User Defined Class
        int32_t         type;               // See SYM_TYPE
        uint32_t        prim;               // See SYM_PRIMITIVE;
        uint32_t        size;               // Data Size in Bytes
        uint32_t        ptr;                // Pointer level (1 per *)
        union {
            uint32_t        misc[4];            // Set Overall Size.
            struct {
                uint32_t        value;
            } constantType;
            struct {
                uint32_t        offset;
            } fieldType;
            struct {
                uint32_t        addr;
            } functionType;
            struct {
                uint32_t        idxKeyHead;         // Keyword Parameters Chain
                uint32_t        idxKeyTail;
                uint32_t        idxPosHead;         // Positional Parameters Chain
                uint32_t        idxPosTail;
            } macroType;
            struct {
                uint32_t        addr;
                uint16_t        baseType;
                uint16_t        storageClass;
            } variableType;
        };
    } SYM_ATTR;
    
    
    
    

    


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct symAttr_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        reserved;
    ASTR_DATA       *pStr;
    SYM_ATTR        attr;

    volatile
    int32_t         numRead;
    // WARNING - 'elems' must be last element of this structure!
    uint32_t        elems[0];

};
#pragma pack(pop)

    extern
    const
    struct symAttr_class_data_s  symAttr_ClassObj;

    extern
    const
    SYMATTR_VTBL         symAttr_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  symAttr_getSuperVtbl(
        SYMATTR_DATA     *this
    );


    void            symAttr_Dealloc(
        OBJ_ID          objId
    );


    void *          symAttr_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     symAttr_ToJSON(
        SYMATTR_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			symAttr_Validate(
        SYMATTR_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SYMATTR_INTERNAL_H */

