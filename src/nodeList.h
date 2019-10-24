// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          List of Nodes (nodeList) Header
//****************************************************************
/*
 * Program
 *			List of Nodes (nodeList)
 * Purpose
 *          This object provides a hash table keyed by the
 *          node name with the node as the data.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/23/2018 Regenerated and old object merged in. This new
 *          object uses objList for its foundation.
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
#include        <nodeArray.h>
#include        <nodeEnum.h>


#ifndef         NODELIST_H
#define         NODELIST_H


//#define   NODELIST_SINGLETON    1

#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct nodeList_data_s	NODELIST_DATA;              // Inherits from OBJLIST
    typedef struct nodeList_class_data_s NODELIST_CLASS_DATA;   // Inherits from OBJ

    typedef struct nodeList_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeList_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODELIST_DATA *);
    } NODELIST_VTBL;

    typedef struct nodeList_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeList_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODELIST_DATA *);
    } NODELIST_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODELIST_SINGLETON
    NODELIST_DATA *     nodeList_Shared(
        void
    );

    bool            nodeList_SharedReset(
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to nodeList object if successful, otherwise OBJ_NIL.
     */
    NODELIST_DATA * nodeList_Alloc(
        void
    );
    
    
    OBJ_ID          nodeList_Class(
        void
    );
    
    
    NODELIST_DATA * nodeList_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     Ordered property when set causes the list to be kept in sorted
     order.
     */
    bool            nodeList_getOrdered(
        NODELIST_DATA   *this
    );
    
    bool            nodeList_setOrdered(
        NODELIST_DATA   *this,
        bool            fValue
    );

    
    /*!
     Size property is the numbers of objects on the list.
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
    
    ERESULT         nodeList_Add2HeadA(
        NODELIST_DATA   *this,
        int32_t         cls,
        const
        char            *pName,
        OBJ_ID          pData
    );
    
    ERESULT         nodeList_Add2Tail(
        NODELIST_DATA   *this,
        NODE_DATA       *pNode
    );
    
    ERESULT         nodeList_Add2TailA(
        NODELIST_DATA   *this,
        int32_t         cls,
        const
        char            *pName,
        OBJ_ID          pData
    );
    

    NODELIST_DATA * nodeList_Copy(
        NODELIST_DATA    *this
    );
    
    
    // Deletes first entry in list that matches the name.
    ERESULT         nodeList_DeleteA (
        NODELIST_DATA   *this,
        int32_t         cls,
        const
        char            *pName
    );
    
    
    ERESULT         nodeList_DeleteHead (
        NODELIST_DATA    *this
    );
    
    
    ERESULT         nodeList_DeleteTail (
        NODELIST_DATA    *this
    );
    
    
    /*! Create an enumerator for the list.
     @return    If successful, an ENUM object is returned.  Otherwise,
     OBJ_NIL.
     @warning   Remember to release the returned ENUM object.
     */
    NODEENUM_DATA * nodeList_Enum(
        NODELIST_DATA   *this
    );
    
    
    NODE_DATA *     nodeList_FindA (
        NODELIST_DATA   *this,
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
        NODELIST_DATA   *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );
    
    
    NODE_DATA *     nodeList_Index(
        NODELIST_DATA   *this,
        uint32_t        index
    );
    
    
    NODELIST_DATA *   nodeList_Init(
        NODELIST_DATA     *this
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
     Sort the list by Name in ascending sequence.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
     error.
     */
    ERESULT         nodeList_SortAscending(
        NODELIST_DATA   *this
    );
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = nodeList_ToDebugString(this,4);
     @endcode 
     @param     this    NODELIST object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    nodeList_ToDebugString(
        NODELIST_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODELIST_H */

