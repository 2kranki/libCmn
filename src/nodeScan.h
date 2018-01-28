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
 *	1.      Many ideas for this object were taken from PCCTS, a public domain
 *          parser generator.
 *
 * History
 *	10/16/2015 Generated
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
        void
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
    
    
    NODE_DATA *     nodeScan_getCloseNode(
        NODESCAN_DATA   *this
    );
    
    
    uint32_t        nodeScan_getIndex(
        NODESCAN_DATA   *this
    );
    
    bool            nodeScan_setIndex(
        NODESCAN_DATA   *this,
        uint32_t        value
    );
    
    
    ERESULT         nodeScan_getLastError(
        NODESCAN_DATA   *this
    );
    
    
    NODE_DATA *     nodeScan_getOpenNode(
        NODESCAN_DATA   *this
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
    
    
    NODE_DATA *     nodeScan_ScanF(
        NODESCAN_DATA   *this,
        char     *pTemplate,
        ...
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return    If successful, an AStr object which must be released,
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

