// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   szBT_internal.h
 *	Generated 02/25/2020 10:00:27
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




#include        <szBT.h>
#include        <Blocks_internal.h>
#include        <JsonIn.h>
#include        <rbt_tree.h>


#ifndef SZBT_INTERNAL_H
#define	SZBT_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif


    //      Node Record Descriptor
#pragma pack(push, 1)
    typedef struct  szBT_record_s {
        // RBT_NODE must be first field in this struct.
        RBT_NODE        node;
        uint32_t        unique;
        //char            *pNameA;              // Use node.key
        //void            *pData;               // Use node.value
    } SZBT_RECORD;
#pragma pack(pop)



#pragma pack(push, 1)
    typedef struct  szBT_find_s {
        uint32_t        unique;
        SZBT_RECORD     *pRecord;
    } SZBT_FIND;
#pragma pack(pop)



#pragma pack(push, 1)
    typedef struct  nodeBT_visit_s {
        SZBT_RECORD     *pRecord;       // Current Record
        P_ERESULT_EXIT3 pScan;
        OBJ_ID          pObj;           // Used as first parameter of scan method
        void            *pArg3;
    } NODEBT_VISIT;
#pragma pack(pop)





    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct szBT_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    BLOCKS_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    RBT_TREE        tree;
    SZBT_RECORD     *pRoot;
    uint32_t        size;            // maximum number of elements
    uint32_t        unique;

    // Record Deletion Exit
    P_ERESULT_EXIT3 pDeleteExit;
    OBJ_ID          pDeleteObj;      // Used as first parameter of pDelete
    //                              // second parameter is key and third is data

};
#pragma pack(pop)

    extern
    struct szBT_class_data_s  szBT_ClassObj;

    extern
    const
    SZBT_VTBL         szBT_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SZBT_SINGLETON
    SZBT_DATA *     szBT_getSingleton (
        void
    );

    bool            szBT_setSingleton (
     SZBT_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  szBT_getSuperVtbl (
        SZBT_DATA     *this
    );


    RBT_TREE *      szBT_getTree (
        SZBT_DATA       *this
    );


    ERESULT         szBT_Assign (
        SZBT_DATA    *this,
        SZBT_DATA    *pOther
    );


    SZBT_DATA *     szBT_Copy (
        SZBT_DATA     *this
    );


    void            szBT_Dealloc (
        OBJ_ID          objId
    );


#ifdef  SZBT_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SZBT_DATA *       szBT_ParseJsonObject (
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
    ERESULT         szBT_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SZBT_DATA     *pObject
    );
#endif


    void *          szBT_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SZBT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = szBT_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     szBT_ToJson (
        SZBT_DATA      *this
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
    ERESULT         szBT_ToJsonFields (
        SZBT_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			szBT_Validate (
        SZBT_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SZBT_INTERNAL_H */

