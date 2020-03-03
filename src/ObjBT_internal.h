// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   ObjBT_internal.h
 *	Generated 03/01/2020 21:30:29
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




#include        <ObjBT.h>
#include        <Blocks_internal.h>
#include        <JsonIn.h>
#include        <rbt_tree.h>


#ifndef OBJBT_INTERNAL_H
#define	OBJBT_INTERNAL_H





#ifdef	__cplusplus
extern "C" {
#endif



    //      Node Record Descriptor
#pragma pack(push, 1)
    typedef struct  ObjBT_record_s {
        // RBT_NODE must be first field in this struct.
        RBT_NODE        node;
        uint32_t        unique;
        //char            *pNameA;              // Use node.key
        //void            *pData;               // Use node.value
    } OBJBT_RECORD;
#pragma pack(pop)



#pragma pack(push, 1)
    typedef struct  ObjBT_find_s {
        uint32_t        unique;
        OBJBT_RECORD    *pRecord;
    } OBJBT_FIND;
#pragma pack(pop)



#pragma pack(push, 1)
    typedef struct  ObjBT_visit_s {
        OBJBT_RECORD    *pRecord;       // Current Record
        P_ERESULT_EXIT3 pScan;
        OBJ_ID          pObj;           // Used as first parameter of scan method
        void            *pArg3;
    } OBJBT_VISIT;
#pragma pack(pop)




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct ObjBT_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    BLOCKS_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    RBT_TREE        tree;
    OBJBT_RECORD    *pRoot;
    uint32_t        size;            // maximum number of elements
    uint32_t        unique;

};
#pragma pack(pop)

    extern
    struct ObjBT_class_data_s  ObjBT_ClassObj;

    extern
    const
    OBJBT_VTBL         ObjBT_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OBJBT_SINGLETON
    OBJBT_DATA *     ObjBT_getSingleton (
        void
    );

    bool            ObjBT_setSingleton (
     OBJBT_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  ObjBT_getSuperVtbl (
        OBJBT_DATA     *this
    );


    ERESULT         ObjBT_Assign (
        OBJBT_DATA    *this,
        OBJBT_DATA    *pOther
    );


    OBJBT_DATA *       ObjBT_Copy (
        OBJBT_DATA     *this
    );


    void            ObjBT_Dealloc (
        OBJ_ID          objId
    );


#ifdef  OBJBT_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    OBJBT_DATA *       ObjBT_ParseJsonObject (
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
    ERESULT         ObjBT_ParseJsonFields (
        JSONIN_DATA     *pParser,
        OBJBT_DATA     *pObject
    );
#endif


    void *          ObjBT_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  OBJBT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ObjBT_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjBT_ToJson (
        OBJBT_DATA      *this
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
    ERESULT         ObjBT_ToJsonFields (
        OBJBT_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			ObjBT_Validate (
        OBJBT_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OBJBT_INTERNAL_H */

