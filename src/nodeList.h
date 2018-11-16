// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Node List (nodeList) Header
//****************************************************************
/*
 * Program
 *			List of Nodes (nodeList)
 * Purpose
 *			This object provides a hash table keyed by the
 *          node name with the node as the data.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal nodeList. A testing unit simply calls
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
#include        <nodeArray.h>
#include        <enum.h>


#ifndef         NODELIST_H
#define         NODELIST_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************



    // Prime numbers for hash table sizes within 16 bits
    // (Maximum size is 65535)
    typedef enum nodeList_table_size_e {
        NODELIST_TABLE_SIZE_XXXXXSMALL = 5,
        NODELIST_TABLE_SIZE_XXXXSMALL = 17,
        NODELIST_TABLE_SIZE_XXXSMALL = 31,
        NODELIST_TABLE_SIZE_XXSMALL = 61,
        NODELIST_TABLE_SIZE_XSMALL = 127,
        NODELIST_TABLE_SIZE_SMALL = 257,
        NODELIST_TABLE_SIZE_MEDIUM = 2053,
        NODELIST_TABLE_SIZE_LARGE  = 4099,
        NODELIST_TABLE_SIZE_XLARGE = 16411
    } NODELIST_TABLE_SIZE;
    

    // NODELIST_DATA is defined in node.h

    typedef struct nodeList_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        // Properties:
        // Methods:
    } NODELIST_VTBL;
    
    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    NODELIST_DATA * nodeList_Alloc(
        void
    );
    
    
    NODELIST_DATA * nodeList_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            nodeList_getOrdered(
        NODELIST_DATA   *this
    );
    
    bool            nodeList_setOrdered(
        NODELIST_DATA   *this,
        bool            fValue
    );

    
    /* Size() returns the current number of used entries.
     * Returns:
     *		Current Number of Entries in Table
     */
    uint32_t        nodeList_getSize(
        NODELIST_DATA   *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         nodeList_Add2Head(
        NODELIST_DATA   *this,
        NODE_DATA       *pNode
    );


    ERESULT         nodeList_Add2Tail(
        NODELIST_DATA   *this,
        NODE_DATA       *pNode
    );
    
    
    NODELIST_DATA * nodeList_Copy(
        NODELIST_DATA	*this
    );
    
    
    // Deletes first entry in list that matches the name.
    ERESULT         nodeList_Delete(
        NODELIST_DATA	*this,
        int32_t         cls,
        const
        char            *pName
    );


    ERESULT         nodeList_DeleteHead(
        NODELIST_DATA	*this
    );
    
    
    ERESULT         nodeList_DeleteTail(
        NODELIST_DATA	*this
    );
    
    
    /*! Create an enumerator for the list.
     @return    If successful, an ENUM object is returned.  Otherwise,
     OBJ_NIL.
     @warning   Remember to release the returned ENUM object.
     */
    ENUM_DATA *     nodeList_Enum(
        NODELIST_DATA  *this
    );
    
    
    NODE_DATA *     nodeList_FindA(
        NODELIST_DATA	*this,
        int32_t         cls,
        const
        char            *pName
    );
    
    
    /*!
     Scan the list applying the given routine to each member of the
     list.  Second parameter to the Scan routine is the actual node
     address. Halt the scan if an error return code is returned
     by the scan routine.
     @param     this    Object Pointer
     @param     pScan   Scan Routine Address
     @param     pObj    First Parameter for the Scan Routine (optional)
     @param     pArg3   Third Parameter for the Scan Routine (optional)
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         nodeList_ForEach(
        NODELIST_DATA	*this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );
    
    
    NODE_DATA *     nodeList_Get(
        NODELIST_DATA   *this,
        uint32_t        index
    );
    
    
    NODELIST_DATA * nodeList_Init(
        NODELIST_DATA   *this
    );


    /*!
     Return an array of all nodes in the graph sorted by name in
     ascending order.
     @param     this    Object Pointer
     @return    NodeArray object pointer which must be released if
                successful.  Otherwise, OBJ_NIL and object's error
                code is set to the specific error.
     @warning   Remember to release the returned object.
     */
    NODEARRAY_DATA * nodeList_Nodes(
        NODELIST_DATA   *this
    );
    
    
    /*!
     Sort the list in ascending sequence.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         nodeList_SortAscending(
        NODELIST_DATA   *this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     nodeList_ToDebugString(
        NODELIST_DATA   *this,
        int             indent
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* NODELIST_H */

