/****************************************************************
 *      Binary Table Manager (BTP) Support Subroutines         *
 ****************************************************************/

// vi: nu:noai:ts=4:sw=4

/*
 * Program
 *              Binary Table Manager (BTP) Subroutines
 * Purpose
 *              See BTP.H.
 * Todo List
 *  ---         Add HASH_Sort() with a comparison exit routine which
 *              points at the Data associated with an Entry.
 *  ---         Add routines to provide a doubly-linked list capability.
 *              See LLD.h for details.
 * Remarks
 *  1.          The data array is referenced relative to one, but
 *              each reference is internally adjusted to be relative
 *              to zero.
 *  2.          Using void pointers internally really caused havoc with
 *              the compilers, so internally we used BYTE as the data
 *              type just to keep the compilers happy.
 *              to zero.
 * History
 *              See HASH.H.
 * References
 *              See HASH.H.
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




/****************************************************************
* * * * * * * * * * * *  data definitions   * * * * * * * * * * *
****************************************************************/

/* Header File Inclusion */
#include        <stdbool.h>
#include        <stdint.h>
#include        <stdlib.h>
#include        <string.h>
#include        "btp_internal.h"
#include        "mem.h"
#include        "str.h"



/* Internal Subroutine Definitions
 */



/****************************************************************
* * * * * * * * * * *  Internal Subroutines * * * * * * * * * * *
****************************************************************/


/* Expand the current Pointer Array by Inc entries.
 */
static
bool            btp_AddBlock(
    BTP_DATA        *cbp
)
{
    BTP_BLOCK       *pBlock;
	uint32_t        i;
    
	// Do initialization.
    if ( NULL == cbp->pDeletedHead )
        ;
    else {
        return true;
    }
    
	// Get a new block.
	pBlock = (BTP_BLOCK *)mem_Malloc( cbp->bufferSize );
	if( NULL == pBlock ) {
		return false;
	}
    pBlock->pNext = cbp->pBlocks;
    cbp->pBlocks = pBlock;
    
    // Now chain the entries to the Deleted chain.
    for (i=0; i<cbp->nodesPerBlock; ++i) {
        pBlock->node[i].pParent = cbp->pDeletedHead;
        cbp->pDeletedHead = &pBlock->node[i];
    }
    
	// Return to caller.
	return true;
}



BTP_NODE *      btp_BrotherNode(
    BTP_DATA        *cbp,
    BTP_NODE        *pNode
)
{
    
    if (pNode && pNode->pParent) {
        if (pNode->pParent->pLeft == pNode) {
            return pNode->pParent->pRight;
        }
        else {
            return pNode->pParent->pLeft;
        }
    }
    
	// Return to caller.
	return NULL;
}



bool            btp_DeleteNode(
    BTP_DATA        *cbp,
    BTP_NODE        *pNode
)
{

    if (pNode) {
        mem_Free(pNode);
        pNode = NULL;
    }
    else
        return false;
    
	// Return to caller.
	return true;
}



BTP_NODE *      btp_FindNode(
    BTP_DATA        *cbp,
    const
    void            *pData
)
{
    BTP_NODE        *pNode = cbp->pTree;
    int             iRc;
    
    while (pNode) {
        iRc = (*cbp->pCompare)(pData,pNode->pData);
        if (0 == iRc) {
            break;
        }
        if (iRc < 0) {
            pNode = pNode->pLeft;
        }
        else {
            pNode = pNode->pRight;
        }
    }
    
	// Return to caller.
	return pNode;
}



bool            btp_IsLeft(
    BTP_DATA        *cbp,
    BTP_NODE        *pNode
)
{
    
	if( pNode && pNode->pParent && (pNode->pParent->pLeft == pNode) ) {
		return true;
    }
    
	// Return to caller.
	return false;
}



bool            btp_IsRight(
    BTP_DATA        *cbp,
    BTP_NODE        *pNode
)
{
    
	if( pNode && pNode->pParent && (pNode->pParent->pRight == pNode) ) {
		return true;
    }
    
	// Return to caller.
	return false;
}



BTP_NODE *      btp_MakeNode(
    BTP_DATA        *cbp,
    const
    void            *pData
)
{
    BTP_NODE        *pNode;

    if (NULL == cbp->pDeletedHead) {
        if (!btp_AddBlock(cbp)) {
            return NULL;
        }
    }
    pNode = cbp->pDeletedHead;
    cbp->pDeletedHead = pNode->pParent;

    pNode->pData = pData;
    pNode->pLeft = NULL;
    pNode->pParent = NULL;
    pNode->pRight = NULL;
    pNode->unique = ++cbp->unique;
    
	// Return to caller.
	return pNode;
}



//----------------------------------------------------------
//                 R o t a t e  L e f t
//----------------------------------------------------------

// Rotate the given subtree rooted at p left one node.
bool            btp_RotateLeft(
    BTP_DATA        *cbp,
    BTP_NODE        *pNode
)
{
    BTP_NODE        *pLeftTree;
    BTP_NODE        *pParent;
    BTP_NODE        *pRight;
    
	if( pNode && pNode->pRight )
		;
	else
		return false;
    
	// Point to all nodes necessary to do the rotation.
	pRight = pNode->pRight;
	pParent = pNode->pParent;
	pLeftTree = pNode->pRight;
	while( pLeftTree->pLeft )
		pLeftTree = pLeftTree->pLeft;
    
	// Chain the right child to the node's parent.
	if( pParent ) {
		if( pParent->pLeft == pNode )
			pParent->pLeft = pRight;
		if( pParent->pRight == pNode )
			pParent->pRight = pRight;
	}
	else
		cbp->pTree = pRight;
	pRight->pParent = pNode->pParent;
	pNode->pRight = NULL;
    
	/* Now add the node after the left-most node of the
	 * node's right child.
	 */
	pLeftTree->pLeft = pNode;
	pNode->pParent = pLeftTree;
    
    
	// Return to caller.
	return true;
}



//----------------------------------------------------------
//                 R o t a t e  R i g h t
//----------------------------------------------------------

// Rotate the given subtree rooted at p right one node.
bool            btp_RotateRight(
    BTP_DATA        *cbp,
    BTP_NODE        *pNode
)
{
    BTP_NODE        *pLeft;
    BTP_NODE        *pParent;
    BTP_NODE        *pRightTree;
    
	if( pNode && pNode->pLeft )
		;
	else
		return false;
    
	/* Point to all nodes necessary to do the rotation.
	 */
	pLeft = pNode->pLeft;
	pParent = pNode->pParent;
	pRightTree = pNode->pLeft;
	while( pRightTree->pRight )
		pRightTree = pRightTree->pRight;
    
	/* Chain the left child to the node's parent.
	 */
	if( pParent ) {
		if( pParent->pLeft == pNode )
			pParent->pLeft = pLeft;
		if( pParent->pRight == pNode )
			pParent->pRight = pLeft;
	}
	else {
		cbp->pTree = pLeft;
    }
	pLeft->pParent = pNode->pParent;
	pNode->pLeft = NULL;
    
	/* Now add the node after the right-most node of the
	 * node's left child.
	 */
	pRightTree->pRight = pNode;
	pNode->pParent = pRightTree;
    
	// Return to caller.
	return true;
}



BTP_NODE *      btp_SetLeftNode(
    BTP_DATA        *cbp,
    BTP_NODE        *pNode,
    const
    void            *pData
)
{
    BTP_NODE        *pNew;

    if (pNode && (NULL == pNode->pLeft)) {
        pNew = btp_MakeNode(cbp, pData);
        pNode->pLeft = pNew;
        pNew->pParent = pNode;
        return pNew;
    }
    
	// Return to caller.
	return NULL;
}



BTP_NODE *      btp_SetRightNode(
    BTP_DATA        *cbp,
    BTP_NODE        *pNode,
    const
    void            *pData
    )
{
    BTP_NODE        *pNew;
    
    if (pNode && (NULL == pNode->pRight)) {
        pNew = btp_MakeNode(cbp, pData);
        pNode->pRight = pNew;
        pNew->pParent = pNode;
        return pNew;
    }
    
	// Return to caller.
	return NULL;
}



bool			btp_VisitNodePostorderRecursive(
    BTP_DATA        *cbp,
    BTP_NODE        *pNode,
    bool            (*pVisitNode)(BTP_DATA *cbp, BTP_NODE *pNode)
)
{
    bool            fRc = true;
    
	if (pNode) {
        fRc = btp_VisitNodePostorderRecursive(cbp,pNode->pLeft,pVisitNode);
        if (!fRc) {
            return false;
        }            
        fRc = btp_VisitNodePostorderRecursive(cbp,pNode->pRight,pVisitNode);
        if (!fRc) {
            return false;
        }            
        fRc = (*pVisitNode)(cbp, pNode);
        if (!fRc) {
            return false;
        }
    }
    
	// Return to caller.
	return true;
}



// Recursive form of Preorder Traverse
bool			btp_VisitNodePreorderRecursive(
    BTP_DATA        *cbp,
    BTP_NODE        *pNode,
    bool            (*pVisitNode)(BTP_DATA *cbp, BTP_NODE *pNode)
)
{
    bool            fRc = true;
    
	if (pNode) {
        fRc = (*pVisitNode)(cbp, pNode);
        if (!fRc) {
            return false;
        }
        fRc = btp_VisitNodePreorderRecursive(cbp,pNode->pLeft,pVisitNode);
        if (!fRc) {
            return false;
        }
        fRc = btp_VisitNodePreorderRecursive(cbp,pNode->pRight,pVisitNode);
        if (!fRc) {
            return false;
        }            
    }
    
	// Return to caller.
	return true;
}





/****************************************************************
* * * * * * * * * * *  External Subroutines   * * * * * * * * * *
****************************************************************/



//===============================================================
//                   C l a s s  M e t h o d s
//===============================================================


BTP_DATA *      btp_Alloc(
)
{
    BTP_DATA        *cbp;
    
    // Do initialization.
    
    cbp = obj_Alloc( sizeof(BTP_DATA) );
    
    // Return to caller.
    return( cbp );
}





//===============================================================
//                    P r o p e r t i e s
//===============================================================

bool			btp_setCompare(
    BTP_DATA		*cbp,
    int             (*pCompare)(const void *pData1, const void *pData2)
)
{
    
#ifdef NDEBUG
#else
    if( !btp_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
    if (NULL == pCompare) {
        DEBUG_BREAK();
        return false;
    }
#endif

    cbp->pCompare = pCompare;
    
    return true;
}





//===============================================================
//                    M e t h o d s
//===============================================================


//----------------------------------------------------------
//                          A d d
//----------------------------------------------------------

bool            btp_Add(
    BTP_DATA        *cbp,
    void			*pData
)
{
    BTP_NODE        *pNode;
    BTP_NODE        *pNew;
    int             iRc;

#ifdef NDEBUG
#else
    if( !btp_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
    if (NULL == cbp->pCompare) {
        return false;
    }
#endif

    if (btp_FindNode(cbp, pData)) {
        return false;
    }
    
    if (NULL == cbp->pTree) {
        cbp->pTree = btp_MakeNode(cbp, pData);
        ++cbp->num;
        return true;
    }

	// Search tree to find entry, add it if not there.
	for( pNode=cbp->pTree;; ) {
		iRc = (*cbp->pCompare)( pData, pNode->pData );
		if( 0 == iRc ) {
			cbp->pCur = NULL;
			return false;
		}
		if( iRc < 0 ) {
			if( pNode->pLeft )
				pNode = pNode->pLeft;
			else
				break;
		}
		else
			if( pNode->pRight )
				pNode = pNode->pRight;
			else
				break;
	}
    
	// Insert the node according to the last comparison.
    pNew = btp_MakeNode(cbp, pData);
	if( iRc > 0 )
		pNode->pRight = pNew;
	else
		pNode->pLeft  = pNew;
	pNode->pParent  = pNew;
    cbp->pCur = pNew;
    ++cbp->num;
    
	// Return to caller.
	return true;
}




//----------------------------------------------------------
//                      C o u n t
//----------------------------------------------------------

uint32_t        btp_Count(
	BTP_DATA     *cbp
)
{
#ifdef NDEBUG
#else
    if( !btp_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
	return( cbp->num );
}



//---------------------------------------------------------------
//                          D e a l l o c
//---------------------------------------------------------------

void            btp_Dealloc(
    OBJ_ID          objId
)
{
    BTP_DATA     *cbp = objId;
    BTP_BLOCK       *pBlock;
    BTP_BLOCK       *pBlockNext;
    
	// Do initialization.
    if (NULL == cbp) {
        return;
    }
#ifdef NDEBUG
#else
	if( !btp_Validate( cbp ) ) {
        DEBUG_BREAK();
		return;
    }
#endif
    
    pBlock = cbp->pBlocks;
    while (pBlock) {
        pBlockNext = pBlock->pNext;
        mem_Free(pBlock);
        pBlock = pBlockNext;
    }
    
    obj_Dealloc(cbp);
	cbp = NULL;
    
	// Return to caller.
}




//----------------------------------------------------------
//					  D e l e t e
//----------------------------------------------------------

bool            btp_Delete(
	BTP_DATA        *cbp,
    const
    void            *pData
)
{
    BTP_NODE        *pNode;
    //BTP_NODE        *pNodePrev;
    //int             iRc;

	// Do initialization.
#ifdef NDEBUG
#else
    if( !btp_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif

    pNode = btp_FindNode(cbp, pData);
    if (NULL == pNode) {
        return false;
    }
        
	// Return to caller.
	return false;
}



//----------------------------------------------------------
//                        F i n d
//----------------------------------------------------------

const
void *          btp_Find(
    BTP_DATA        *cbp,
    const
    void            *pData
)
{
    BTP_NODE        *pNode;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if( !btp_Validate( cbp ) ) {
        DEBUG_BREAK();
        return NULL;
    }
#endif

    pNode = btp_FindNode(cbp, pData);
    cbp->pCur = pNode;
    
	// Return to caller.
	return (pNode ? pNode->pData : NULL);
}



//----------------------------------------------------------
//                        F i r s t 
//----------------------------------------------------------

const
void *          btp_First(
    BTP_DATA        *cbp
)
{
    BTP_NODE        *pNode;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if( !btp_Validate( cbp ) ) {
        DEBUG_BREAK();
        return NULL;
    }
#endif
    
    pNode = cbp->pTree;
	while( pNode && pNode->pLeft ) {
		pNode = pNode->pLeft;
    }
    cbp->pCur = pNode;
    
	// Return to caller.
	return (pNode ? pNode->pData : NULL);
}



//----------------------------------------------------------
//						  I n i t
//----------------------------------------------------------

BTP_DATA *      btp_Init(
    BTP_DATA        *this,
    P_BTP_COMPARE   pCompare
)
{
    uint16_t        cbSize = sizeof(BTP_DATA);
    
	// Validate the input parameters.
    if (NULL == this) {
        return NULL;
    }
    
	// Initialize the control block.
    this = obj_Init( this, cbSize, OBJ_IDENT_BTP );
    if (NULL == this) {
        return NULL;
    }
    this->pSuperVtbl = obj_getVtbl(this);
    obj_setVtbl(this, (OBJ_IUNKNOWN *)&btp_Vtbl);

    this->pCompare = pCompare;
    cbSize = 4096;
    this->bufferSize = cbSize;
    cbSize -= sizeof(BTP_BLOCK);
    cbSize /= sizeof(BTP_NODE);
    this->nodesPerBlock = cbSize;
    
#ifdef NDEBUG
#else
    if( !btp_Validate(this) ) {
        DEBUG_BREAK();
        return false;
    }
#endif
    
	// Return to caller.
	return( this );
}



//----------------------------------------------------------
//                        L a s t
//----------------------------------------------------------

const
void *          btp_Last(
    BTP_DATA        *cbp
)
{
    BTP_NODE        *pNode;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if( !btp_Validate( cbp ) ) {
        DEBUG_BREAK();
        return NULL;
    }
#endif
    
    pNode = cbp->pTree;
	while( pNode && pNode->pRight ) {
		pNode = pNode->pRight;
    }
    cbp->pCur = pNode;
    
	// Return to caller.
	return (pNode ? pNode->pData : NULL);
}



//----------------------------------------------------------
//                        N e x t
//----------------------------------------------------------

const
void *          btp_Next(
    BTP_DATA        *cbp
)
{
    BTP_NODE        *pNode;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if( !btp_Validate( cbp ) ) {
        DEBUG_BREAK();
        return NULL;
    }
#endif
    
    pNode = cbp->pCur;
    if (NULL == pNode) {
        return NULL;
    }
    
	// If we have a right-child, then go right and then
	// left-most.
	if( pNode->pRight ) {
		pNode = pNode->pRight;
		while( pNode->pLeft )
			pNode = pNode->pLeft;
		goto exit00;
	}
    
	// Back up to parent.
	if( pNode->pParent ) {
		if( pNode->pParent->pLeft == pNode ) {
			pNode = pNode->pParent;
			goto exit00;
		}
		else if( pNode->pParent->pRight == pNode ) {
			while( pNode == pNode->pParent->pRight ) {
				pNode = pNode->pParent;
				if( pNode && pNode->pParent )
					;
				else
					break;
			}
			pNode = pNode->pParent;
			goto exit00;
		}
	}
	else
		pNode = NULL;
    
    
	// Return to caller.
exit00:
    cbp->pCur = pNode;
	return (pNode ? pNode->pData : NULL);
}



//----------------------------------------------------------
//                      V a l i d a t e
//----------------------------------------------------------

#ifdef NDEBUG
#else
bool			btp_Validate(
    BTP_DATA     *cbp
)
{
    
	// Do initialization.
    
	if( obj_IsKindOf(cbp, OBJ_IDENT_BTP) )
		;
	else
		return false;
	if( !(obj_getSize(cbp) >= sizeof(BTP_DATA)) )
		return false;
    
	// Return to caller.
	return true;
}
#endif



//----------------------------------------------------------
//                 V i s i t  P r e o r d e r
//----------------------------------------------------------

/* "To traverse a nonempty binary tree in preorder (or Depth-
 * First Order), we perform the following operations:
 *  1. Visit the root.
 *  2. Traverse the left subtree in preorder.
 *  3. Traverse the right subtree in preorder.
 * In preorder, a node is visited only when it is reached on 
 * the way down the tree.
 */
bool			btp_VisitPreorder(
    BTP_DATA        *cbp,
    bool            (*pVisit)(BTP_DATA *cbp, const void *pData)
)
{
    
	// Return to caller.
	return true;
}



//----------------------------------------------------------
//                 V i s i t  I n o r d e r
//----------------------------------------------------------

/* To Traverse a nonempty binary tree in inorder (or symmetric
 * order):
 *  1. Traverse the left subtree in inorder.
 *  2. Visit the root.
 *  3. Traverse the right subtree in inorder.
 * If a binary search tree is traversed in inorder (left, root,
 * right) and the contents of each node are printed as the node
 * is visited, the listing will be in ascending sequence.
 * When node(p) is reached from a left son, its right subtree
 * must still be traversed; therefore the algorithm proceeds to
 * right(p). When node(p) is reached from its right son, both its
 * subtrees have been traversed and the algorithm backs up fur-
 * ther to father(p).
 * In inorder traversal, a note is visited when its left son
 * is recognized as NULL or when it is readched after backing
 * up from its left son.
 */
bool			btp_VisitInorder(
    BTP_DATA        *cbp,
    bool            (*pVisit)(BTP_DATA *cbp, const void *pData)
)
{
    BTP_NODE        *pNode;
    BTP_NODE        *pParent;
    bool            fRc;
    
	// Do initialization.
    pParent = NULL;
    pNode = cbp->pTree;
    
    do {
        // Traverse left son chain.
        while (pNode) {
            pParent = pNode;
            pNode = pNode->pLeft;
        }
        // Visit leftmost child.
        if (pParent) {
            fRc = (*pVisit)(cbp,pParent->pData);
            if (!fRc) {
                return false;
            }
            pNode = pParent->pRight;    // Look into right tree.
        }
        while (pParent && (NULL == pNode)) {
            /* Node(pFather) has no right son. Back up until a left son
             * or the tree root is encountered.
             */
            do {
                pNode = pParent;
                pParent = pNode->pParent;
            } while (!btp_IsLeft(cbp,pNode) && pParent);
            if (pParent) {
                fRc = (*pVisit)(cbp,pParent->pData);
                if (!fRc) {
                    return false;
                }
                pNode = pParent->pRight;
            }
        }
        
    } while (pParent);
    
	// Return to caller.
	return true;
}



//----------------------------------------------------------
//                 V i s i t  P o s t o r d e r
//----------------------------------------------------------

/* To Traverse a nonempty binary tree in postorder:
 *  1. Traverse the left subtree in postorder.
 *  2. Traverse the right subtree in postorder.
 *  3. Visit the root.
 * In postorder, a node is visited only when its right son is
 * recognized as NULL or when it is reached after backing up
 * from its right son.
 */
bool			btp_VisitPostorder(
    BTP_DATA        *cbp,
    bool            (*pVisit)(BTP_DATA *cbp, const void *pData)
)
{
    BTP_NODE        *pNode;
    BTP_NODE        *pParent;
    bool            fRc;
    
	// Do initialization.
    pNode = cbp->pTree;
    pParent = NULL;
    
    do {
        // Descend the left son chain.
        while (pNode) {
            pParent = pNode;
            pNode = pNode->pLeft;
        }
        // Descend the right son chain.
        while (pNode) {
            pParent = pNode;
            pNode = pNode->pRight;
        }
        // Node does not have right son.
        if ( pParent && (NULL == pParent->pRight)) {
            fRc = (*pVisit)(cbp, pParent->pData);
            if (!fRc) {
                return false;
            }
            pNode = pParent->pRight;
        }
        while (pParent && (NULL == pNode)) {
            /* Node(pFather) has no right son. Back up until a right son
             * or the tree root is encountered.
             */
            do {
                pNode = pParent;
                pParent = pNode->pParent;
                if (pParent) {
                    fRc = (*pVisit)(cbp, pParent->pData);
                    if (!fRc) {
                        return false;
                    }
                }
            } while (!btp_IsRight(cbp, pNode) && pParent);
        }
        
    } while (pParent);

	// Return to caller.
	return true;
}







