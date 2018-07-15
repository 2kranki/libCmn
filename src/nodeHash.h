// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Node Hash (nodeHash) Header
//****************************************************************
/*
 * Program
 *			Hash Table of Nodes (nodeHash)
 * Purpose
 *			This object provides a hash table keyed by the
 *          node name with a pointer to the node as the data.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal nodeHash. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	07/22/2015 Generated
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





#include        <cmn_defs.h>
#include        <node.h>


#ifndef         NODEHASH_H
#define         NODEHASH_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************



    // Prime numbers for hash table sizes within 16 bits
    // (Maximum size is 65535)
    typedef enum nodeHash_table_size_e {
        NODEHASH_TABLE_SIZE_XXXXXSMALL = 5,
        NODEHASH_TABLE_SIZE_XXXXSMALL = 17,
        NODEHASH_TABLE_SIZE_XXXSMALL = 31,
        NODEHASH_TABLE_SIZE_XXSMALL = 61,
        NODEHASH_TABLE_SIZE_XSMALL = 127,
        NODEHASH_TABLE_SIZE_SMALL = 257,
        NODEHASH_TABLE_SIZE_MEDIUM = 2053,
        NODEHASH_TABLE_SIZE_LARGE  = 4099,
        NODEHASH_TABLE_SIZE_XLARGE = 16411
    } NODEHASH_TABLE_SIZE;
    

    // NODEHASH_DATA is defined in node.h
    
    typedef struct nodeHash_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        // Properties:
        // Methods:
    } NODEHASH_VTBL;
    
    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    NODEHASH_DATA * nodeHash_Alloc(
        void
    );
    
    
    OBJ_ID          nodeHash_Class(
        void
    );
    
    
    NODEHASH_DATA * nodeHash_New(
        uint16_t        cHash           // [in] Hash Table Size
    );
    
    
    ERESULT         nodeHash_NewFromJSONString(
        ASTR_DATA       *pString,
        NODEHASH_DATA   **ppData
    );
    
    
    ERESULT         nodeHash_NewFromJSONStringA(
        const
        char            *pString,
        NODEHASH_DATA   **ppData
    );
    
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /* Size() returns the current number of used entries.
     * Returns:
     *		Current Number of Entries in the Hash
     */
    uint32_t        nodeHash_getSize(
        NODEHASH_DATA   *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the given node to the Hash. If duplicates are not allowed, then
     the node's name must not exist in the Hash.  Otherwise, the node will
     be added to the head of the Hash list effectively blocking access to
     other nodes with the same name.  The A versions creates a node from
     the data given before trying to add it to the Hash.
     @param     this    Object Pointer
     @param     pNode   Data Object Pointer
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
                error code is returned.
     */
    ERESULT         nodeHash_Add(
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    );

    ERESULT         nodeHash_AddA(
        NODEHASH_DATA   *this,
        const
        char            *pName,
        int32_t         cls,
        OBJ_ID          pData
    );
    

    /*!
     Add the given node to the Hash if it is not in the Hash. If it already
     exists, then replace it with the new node.  The A version creates a
     node from the data given before trying to add it to the Hash.
     @param     this    Object Pointer
     @param     pNode   Data Object Pointer
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
                error code is returned.
     */
    ERESULT         nodeHash_AddUpdate(
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    );
    
    ERESULT         nodeHash_AddUpdateA(
        NODEHASH_DATA    *this,
        const
        char            *pName,
        int32_t         cls,
        OBJ_ID          pData
    );
    

    /*!
     Copy the hash. Any element of the Hash that has a copy method
     will have that used to create a new object. Otherwise, the object
     is just retained and added to the new hash.
     @param     this    Object Pointer
     @return    If successful, return a new hash table that must be released
                otherwise return OBJ_NIL.
     */
    NODEHASH_DATA * nodeHash_Copy(
        NODEHASH_DATA	*this
    );
    
    
    NODEHASH_DATA * nodeHash_DeepCopy(
        NODEHASH_DATA    *this
    );
    
    
    ERESULT         nodeHash_Delete(
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    );
    
    ERESULT         nodeHash_DeleteA(
        NODEHASH_DATA	*this,
        const
        char            *pName
    );

    ERESULT         nodeHash_DeleteName(
        NODEHASH_DATA   *this,
        NAME_DATA       *pName
    );
    

    NODE_DATA *     nodeHash_Find(
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    );
    
    NODE_DATA *     nodeHash_FindA(
        NODEHASH_DATA	*this,
        const
        char            *pName
    );
    
    NODE_DATA *     nodeHash_FindName(
        NODEHASH_DATA   *this,
        NAME_DATA       *pName
    );

    
    ERESULT         nodeHash_ForEach(
        NODEHASH_DATA	*this,
        P_VOIDEXIT2_BE  pScan,
        OBJ_ID          pObj            // Used as first parameter of scan method
    );
    
    
    NODEHASH_DATA * nodeHash_Init(
        NODEHASH_DATA   *this,
        uint16_t        cHash           // [in] Hash Table Size
    );


    /*!
     Return an array of all nodes in the hash sorted by name in
     ascending order.
     @param     this    Object Pointer
     @return    NodeArray object pointer which must be released if
                successful.  Otherwise, OBJ_NIL and object's error
                code is set to the specific error.
     @warning   Remember to release the returned object.
     */
    NODEARRAY_DATA * nodeHash_Nodes(
        NODEHASH_DATA	*this
    );
    
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
     // Return a method pointer for a string or NULL if not found.
     void        *pMethod = nodeHash_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a
                        character string which represents the method name without
                        the object name, "nodeHash", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          nodeHash_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     nodeHash_ToDebugString(
        NODEHASH_DATA	*this,
        int             indent
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it in JSON format.
     @return    If successful, an AStr object which must be released,
     otherwise OBJ_NIL.
     */
    ASTR_DATA *     nodeHash_ToJSON(
        NODEHASH_DATA   *this
    );
    
    

    
    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEHASH_H */

