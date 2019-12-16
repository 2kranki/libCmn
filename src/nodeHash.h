// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Hash Table of Nodes (nodeHash) Header
//****************************************************************
/*
 * Program
 *			Hash Table of Nodes (nodeHash)
 * Purpose
 *          This object provides a hash table keyed by the
 *          node name with a pointer to the node as the data.
 *
 * Remarks
 *    1.    Nodes are stored within the hash by their name.  If the
 *          nodes are created for use in JSON, parser or equivalent
 *          environments, then their data will also be nodes and not
 *          the direct data.
 *
 *          The data nodes will have names of "array", "false", "hash",
 *          "integer", "null", "string" or "true" generally.  The node's
 *          data object will be the actual data such as:
 *                  "array"     == nodeArray object
 *                  "false"     == false object
 *                  "hash"      == nodeHash object
 *                  "integer"   == AStr object which can be converted with AStr_ToInt64
 *                  "null"      == null object
 *                  "string"    == AStr object
 *                  "true"      == true object
 *          Therefore, you have a structure like:
 *              node:
 *                  name:   node name
 *                  data:   data node object
 *                      name:   See above. (ie "array", "false", ...)
 *                      data:   actual data object as above (ie nodeArray, false, ...)
 *
 * History
 *	11/27/2018 Generated
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
#include        <AStr.h>
#include        <blocks.h>
#include        <node.h>
#include        <nodeArray.h>
#include        <NodeEnum.h>


#ifndef         NODEHASH_H
#define         NODEHASH_H


//#define   NODEHASH_SINGLETON    1

#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct nodeHash_data_s	NODEHASH_DATA;            // Inherits from OBJ
    typedef struct nodeHash_class_data_s NODEHASH_CLASS_DATA;   // Inherits from OBJ

    typedef struct nodeHash_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeHash_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEHASH_DATA *);
    } NODEHASH_VTBL;

    typedef struct nodeHash_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeHash_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEHASH_DATA *);
    } NODEHASH_CLASS_VTBL;



    // Prime numbers for hash table sizes within 16 bits
    // (Maximum size is 65535)
    typedef enum nodeHash_table_size_e {
        NODEHASH_TABLE_SIZE_XSMALL   = 5,
        NODEHASH_TABLE_SIZE_SMALL    = 17,
        NODEHASH_TABLE_SIZE_MEDIUM   = 31,
        NODEHASH_TABLE_SIZE_LARGE    = 61,
        NODEHASH_TABLE_SIZE_XLARGE   = 127,
        NODEHASH_TABLE_SIZE_XXLARGE  = 257,
        NODEHASH_TABLE_SIZE_XXXLARGE = 2053
    } NODEHASH_TABLE_SIZE;
    
    
    

    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEHASH_SINGLETON
    NODEHASH_DATA *  nodeHash_Shared(
        void
    );

    bool            nodeHash_SharedReset(
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to nodeHash object if successful, otherwise OBJ_NIL.
     */
    NODEHASH_DATA * nodeHash_Alloc(
        void
    );
    
    
    OBJ_ID          nodeHash_Class(
        void
    );
    
    
    NODEHASH_DATA * nodeHash_New(
        void
    );
    
    NODEHASH_DATA * nodeHash_NewWithSize (
        uint16_t        cHash       // [in] Hash Table Size
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

    /*! property:   the underlying object.
     */
    BLOCKS_DATA *   nodeHash_getBlocks (
        NODEHASH_DATA   *this
    );


    /*! Size() returns the current number of used entries.
        @return     Current Number of Entries in the Hash
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
    ERESULT         nodeHash_Add (
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    );
    
    ERESULT         nodeHash_AddA (
        NODEHASH_DATA   *this,
        int32_t         cls,
        const
        char            *pName,             // UTF-8
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
    ERESULT         nodeHash_AddUpdate (
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    );
    
    ERESULT         nodeHash_AddUpdateA (
        NODEHASH_DATA   *this,
        int32_t         cls,
        const
        char            *pName,
        OBJ_ID          pData
    );
    
    
    /*! Calculate certain statistics about the hash table.
     @param     this        object pointer
     @param     pNumBuckets Number of Hash Buckets in Index
     @param     pNumEmpty   Number of Empty Hash Buckets
     @param     pNumMax     Maximum Number of nodes in any one Hash Bucket
     @param     pNumAvg     Average Number of nodes in Hash Buckets that
                            have nodes
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         nodeHash_CalcHashStats(
        NODEHASH_DATA   *this,
        uint32_t        *pNumBuckets,   // Number of Hash Buckets
        uint32_t        *pNumEmpty,     // Number of Empty Hash Buckets
        uint32_t        *pNumMax,       // Maximum Number in any one Hash Bucket
        uint32_t        *pNumAvg        // Average Number in each Hash Bucket
    );
    
    
    ERESULT         nodeHash_Delete (
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    );
    
    ERESULT         nodeHash_DeleteA (
        NODEHASH_DATA   *this,
        int32_t         cls,
        const
        char            *pName
    );

    
    /*!
     Substitute environment variables into the current string using a BASH-like
     syntax.  Variable names should have the syntax of:
     '$' '{'[a..zA..Z_][a..zA..Z0..9_]* '}'
     or
     '$'[A..Za..z_][A..Za..z0..9_]*
     Substitutions are not rescanned after insertion.
     @param     this    object pointer
     @return    ERESULT_SUCCESS if successful.  Otherwise, an ERESULT_* error code
     is returned.
     */
    ERESULT         nodeHash_ExpandVars(
        NODEHASH_DATA   *this,
        ASTR_DATA       *pStr
    );
    
    
    NODE_DATA *     nodeHash_Find (
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    );
    
    NODE_DATA *     nodeHash_FindA (
        NODEHASH_DATA   *this,
        int32_t         cls,
        const
        char            *pName
    );
    
    /*!
     Find a named node array in the hash as structured in Remark #1 above.
     @param     this    Object Pointer
     @param     pSectionA Name of integer value (required)
     @param     ppArray Pointer to a node array pointer where data is to be returned if
                ERESULT_SUCCESS is returned.
     @return    If successful, ERESULT_SUCCESS and a node array pointer in *ppArray
                if ppArray is non-null.  Otherwise, ERESULT_* error code.
     */
    ERESULT         nodeHash_FindArrayNodeInHashA (
        NODEHASH_DATA    *this,
        const
        char            *pSectionA,
        NODEARRAY_DATA  **ppArray
    );
    
    
    /*!
     Find a named integer value in the hash as structured in Remark #1 above.
     @param     this    Object Pointer
     @param     pSectionA Name of integer value (required)
     @param     pInt    integer pointer where data is to be returned too if
                succesful ERESULT is returned.
     @return    If successful, ERESULT_SUCCESS and an integer value in *pInt
                if pInt is non-null, otherwise, an ERESULT_* error code.
     */
    ERESULT         nodeHash_FindIntegerNodeInHashA(
        NODEHASH_DATA   *this,
        const
        char            *pSectionA,
        int64_t         *pInt
    );
    
    
    /*!
     Find a named node in the hash as structured in Remark #1 above.
     @param     this    Object Pointer
     @param     pSectionA Name of Node to be looked for
     @param     pTypeA  Name of Data Node ("array", "false", "hash",
                "integer", "null", "string" or "true")
     @param     ppData  Pointer to Data Object Pointer to be returned if
                ERESULT_SUCCESS is returned.
     @return    If successful, ERESULT_SUCCESS and the actual data object
                pointer in *ppData if ppData is non-null.  Otherwise,
                an ERESULT_* error code.
     @note      See Remark #1 above.
     */
    ERESULT         nodeHash_FindNodeInHashA (
        NODEHASH_DATA   *this,
        const
        char            *pSectionA,
        const
        char            *pTypeA,
        OBJ_ID          *ppData
    );
    
    
    /*!
     Find a named string value in the Hash as structured in Remark #1.
     @param     this    Object Pointer
     @param     pSectionA Name of integer value (required)
     @param     ppStr   Pointer to a string pointer to be returned if
                ERESULT_SUCCESS is returned and this pointer
                is non-null.
     @return    If successful, ERESULT_SUCCESS and an sting value in *ppStr
                if ppStr is non-null. Otherwise, an ERESULT_* error code.
     @note      See Remark #1 above.
     */
    ERESULT         nodeHash_FindStringNodeInHashA (
        NODEHASH_DATA   *this,
        const
        char            *pSectionA,
        ASTR_DATA       **ppStr
    );
    
    
    /*!
     Scan all nodes in the hash in no particular order.
     @param     this    Object Pointer
     @param     pScan   Method to be executed for each node (required),
                        second parameter when called is the node pointer
     @param     pObj    First parameter of the pScan Method when called
     @param     pArg3   Third parameter of the pScan Method when called
     @return    If successful, ERESULT_SUCCESS and an sting value in *ppStr
                if ppStr is non-null. Otherwise, an ERESULT_* error code.
     @note      See Remark #1 above.
     */
    ERESULT         nodeHash_ForEach (
        NODEHASH_DATA   *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,           // First parameter of scan method
        //                              // Second parameter of scan method,
        //                              // the node pointer (NODE_DATA *)
        void            *pArg3          // Third parameter of scan method
    );
    
    
    NODEHASH_DATA * nodeHash_Init (
        NODEHASH_DATA   *this,
        uint16_t        cHash       // [in] Hash Table Size
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
    NODEARRAY_DATA * nodeHash_Nodes (
        NODEHASH_DATA    *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = nodeHash_ToDebugString(this,4);
     @endcode 
     @param     this    NODEHASH object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    nodeHash_ToDebugString (
        NODEHASH_DATA   *this,
        int             indent
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it in JSON format.
     @return    If successful, an AStr object which must be released,
     otherwise OBJ_NIL.
     */
    ASTR_DATA *     nodeHash_ToJSON (
        NODEHASH_DATA   *this
    );
    
    
    ASTR_DATA *     nodeHash_ToString(
        NODEHASH_DATA   *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = nodeHash_ToDebugString(this,4);
     @endcode
     @param     this    NODEHASH object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     nodeHash_ToDebugString(
        NODEHASH_DATA   *this,
        int             indent
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEHASH_H */

