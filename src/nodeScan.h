// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Node Scanner (nodeScan) Header
//****************************************************************
/*
 * Program
 *			Node Scanner (nodeScan)
 * Purpose
 *			This object supports scanning a NodeTree that was con-
 *          verted to a NodeArray with up/down members. See 
 *          nodeTree_ToLinearizationPost or nodeTree_ToLinearizationPre.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal nodeScan. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	10/16/2015 Generated
 */







#include        <cmn_defs.h>
#include        <node.h>
#include        <AStr.h>


#ifndef         NODESCAN_H
#define         NODESCAN_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct nodeScan_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        // Properties:
        // Methods:
    } NODESCAN_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    NODESCAN_DATA *     nodeScan_Alloc(
    );
    
    
    NODESCAN_DATA * nodeScan_NewFromArray(
        NODEARRAY_DATA  *pArray     // Tree converted to array with up/down members.
    );
    
    
    // Convert the tree to a preorder array and
    // create a scanner from that.
    NODESCAN_DATA * nodeScan_NewFromTree(
        NODETREE_DATA   *pTree
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NODEARRAY_DATA * nodeScan_getArray(
        NODESCAN_DATA    *this
    );
    
    bool            nodeScan_setArray(
        NODESCAN_DATA   *this,
        NODEARRAY_DATA  *pValue
    );
    
    
    uint32_t        nodeScan_getIndex(
        NODESCAN_DATA   *this
    );
    
    bool            nodeScan_setIndex(
        NODESCAN_DATA   *this,
        uint32_t        value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    NODESCAN_DATA * nodeScan_Init(
        NODESCAN_DATA   *this
    );

    NODESCAN_DATA * nodeScan_InitArray(
        NODESCAN_DATA   *this,
        NODEARRAY_DATA  *pValue
    );
    

    NODE_DATA *     nodeScan_InputAdvance(
        NODESCAN_DATA	*this,
        uint16_t        numChrs
    );

    
    NODE_DATA *     nodeScan_InputLookAhead(
        NODESCAN_DATA   *this,
        uint16_t        num
    );

    
    NODE_DATA *     nodeScan_MatchName(
        NODESCAN_DATA	*this,
        char            *pStr
    );

    
    NODE_DATA *     nodeScan_MatchClass(
        NODESCAN_DATA	*this,
        int32_t         cls
    );

    
    NODE_DATA *     nodeScan_MatchClasses(
        NODESCAN_DATA   *this,
        int32_t         *pSet
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     nodeScan_ToDebugString(
        NODESCAN_DATA   *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODESCAN_H */

