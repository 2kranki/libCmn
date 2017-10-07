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
    
    
    NODEHASH_DATA * nodeHash_New(
        uint16_t        cHash           // [in] Hash Table Size
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

    /* Add() adds the node if it is not already in the hash.
     */
    ERESULT         nodeHash_Add(
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    );


    /*!
     Copy the hash. Any element of the Hash that has a copy method
     will have that used to create a new object. Otherwise, the object
     is just retained and added to the new hash.
     @return    If successful, return a new hash table that must be released
                otherwise return OBJ_NIL.
     */
    NODEHASH_DATA * nodeHash_Copy(
        NODEHASH_DATA	*this
    );
    
    
    ERESULT         nodeHash_Delete(
        NODEHASH_DATA	*this,
        const
        char            *pName
    );


    ERESULT         nodeHash_FindA(
        NODEHASH_DATA	*this,
        const
        char            *pName,
        NODE_DATA       **ppNode
    );
    
    
    ERESULT         nodeHash_FindW(
        NODEHASH_DATA	*this,
        const
        int32_t         *pName,
        NODE_DATA       **ppNode
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


    // Returns a array of all nodes in the hash
    // sorted by name in ascending order.
    ERESULT         nodeHash_Nodes(
        NODEHASH_DATA	*this,
        NODEARRAY_DATA  **ppKeys
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
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEHASH_H */

