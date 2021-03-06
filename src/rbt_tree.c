// vi:nu:et:sts=4 ts=4 sw=4
//
// Based on Julienne Walker's <http://eternallyconfuzzled.com/> rb_tree
// implementation.
//
// Modified by Mirek Rusin <http://github.com/mirek/rb_tree>.
//
// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>
//


#include        <rbt_tree.h>




// rb_node

RBT_NODE *      rbt_NodeInit (
    RBT_TREE        *this,
    RBT_NODE        *pNode,
    void            *pKey,
    void            *pValue
)
{
    if (pNode) {
        pNode->color = RBT_RED;
        pNode->pLink[RBT_LEFT] = NULL;
        pNode->pLink[RBT_RIGHT] = NULL;
        pNode->pKey = pKey;
        pNode->pValue = pValue;
    }
    
    return pNode;
}



RBT_NODE *      rbt_NodeNew (
    RBT_TREE        *this,
    void            *pKey,
    void            *pValue
)
{
    RBT_NODE        *pNode;
    
    pNode = this->pNodeAlloc(this->pObjAllocFree, NULL);
    if (pNode) {
        rbt_NodeInit(this, pNode, pKey, pValue);
    }
    return pNode;
}



RBT_NODE *      rbt_NodeDealloc (
    RBT_TREE        *this,
    RBT_NODE        *pNode
)
{
    if (pNode) {
        this->pNodeFree(this->pObjAllocFree, pNode);
        pNode = NULL;
    }
    return pNode;
}



int             rbt_IsNodeRed (
    RBT_NODE        *pNode
)
{
    int             fColor = 0;
    
    if (pNode) {
        fColor = (pNode->color == RBT_RED ? 1 : 0);
    }
    
    return fColor;
}



static
RBT_NODE *          rbt_NodeRotate (
    RBT_NODE            *this,
    int                 dir
)
{
    RBT_NODE            *result = NULL;
    
    if (this) {
        result = this->pLink[!dir];
        this->pLink[!dir] = result->pLink[dir];
        result->pLink[dir] = this;
        this->color = RBT_RED;
        result->color = RBT_BLACK;
    }
    
    return result;
}


static
RBT_NODE *          rbt_NodeRotate2 (
    RBT_NODE            *this,
    int                 dir
)
{
    RBT_NODE            *result = NULL;
    
    if (this) {
        this->pLink[!dir] = rbt_NodeRotate(this->pLink[!dir], !dir);
        result = rbt_NodeRotate(this, dir);
    }
    
    return result;
}




// rb_tree

RBT_TREE *      rbt_Alloc(
)
{
    return mem_Malloc(sizeof(RBT_TREE));
}



RBT_TREE *      rbt_Init(
    RBT_TREE        *pTree,
    int             (*pCmp)(void *, void *),
    uint32_t        dataSize,
    RBT_NODE *      (*pNodeAlloc)(OBJ_ID, uint32_t *),
    void            (*pNodeFree)(OBJ_ID, RBT_NODE *),
    OBJ_ID          pObjAllocFree
) 
{
    if (pTree) {
        pTree->pRoot = NULL;
        pTree->size = 0;
        pTree->pCmp = pCmp;
        pTree->dataSize = dataSize;
        pTree->pNodeAlloc = pNodeAlloc;
        pTree->pNodeFree = pNodeFree;
        pTree->pObjAllocFree = pObjAllocFree;
    }
    return pTree;
}



void            rbt_DeleteAll(
    RBT_TREE        *this
)
{
    
    if (this) {
        RBT_NODE        *pNode = this->pRoot;
        RBT_NODE        *pSave = NULL;
        
        // Rotate away the left links so that
        // we can treat this like the destruction
        // of a linked list
        while (pNode) {
            if (pNode->pLink[RBT_LEFT] == NULL) {
                // No left links, just kill the node and move on
                pSave = pNode->pLink[RBT_RIGHT];
                this->pNodeFree(this->pObjAllocFree, pNode);
                pNode = NULL;
            } else {
                // Rotate away the left link and check again
                pSave = pNode->pLink[RBT_LEFT];
                pNode->pLink[RBT_LEFT] = pSave->pLink[RBT_RIGHT];
                pSave->pLink[RBT_RIGHT] = pNode;
            }
            pNode = pSave;
        }
        this->pRoot = NULL;
    }
}



void *          rbt_Find (
    RBT_TREE        *this,
    void            *pKey
)
{
    RBT_NODE        *pNodeCurrent = NULL;
    int             cmp = 0;
    
    if (this) {
        pNodeCurrent = this->pRoot;
        while (pNodeCurrent) {
            cmp = this->pCmp(pNodeCurrent->pKey, pKey);
            if (cmp) {
                
                // If the tree supports duplicates, they should be
                // chained to the right subtree for this to work
                pNodeCurrent = pNodeCurrent->pLink[cmp < 0];
            } else {
                break;
            }
        }
    }
    
    return pNodeCurrent ? pNodeCurrent->pValue : NULL;
}



RBT_NODE *      rbt_FindNode (
    RBT_TREE        *this,
    RBT_NODE        *pNode
)
{
    RBT_NODE        *pNodeCurrent = NULL;
    int             cmp = 0;

    if (this) {
        pNodeCurrent = this->pRoot;
        while (pNodeCurrent) {
            if ((cmp = this->pCmp(pNodeCurrent->pKey, pNode->pKey))) {

                // If the tree supports duplicates, they should be
                // chained to the right subtree for this to work
                pNodeCurrent = pNodeCurrent->pLink[cmp < 0];
            } else {
                break;
            }
        }
    }
    
    return pNodeCurrent;
}



// Creates (malloc'ates) node then inserts it.
bool            rbt_Insert(
    RBT_TREE        *this, 
    void            *pKey,
    void            *pValue
) 
{
    RBT_NODE        *pNode;

    pNode = rbt_NodeNew(this, pKey, pValue);

    return rbt_InsertNode(this, pNode);
}



// Returns 1 on success, 0 otherwise.
bool                rbt_InsertNode(
    RBT_TREE            *this,
    RBT_NODE            *node
) 
{

    if (this && node) {
        if (this->pRoot == NULL) {
            this->pRoot = node;
        }
        else {
            RBT_NODE head = { 0 }; // False tree root
            RBT_NODE *g, *t;       // Grandparent & parent
            RBT_NODE *p, *q;       // Iterator & parent
            int dir = 0, last = 0;

            // Set up our helpers
            t = &head;
            g = p = NULL;
            q = t->pLink[RBT_RIGHT] = this->pRoot;

            // Search down the tree for a place to insert
            while (true) {
                if (q == NULL) {

                    // Insert node at the first null link.
                    p->pLink[dir] = q = node;
                } else if (rbt_IsNodeRed(q->pLink[RBT_LEFT]) && rbt_IsNodeRed(q->pLink[RBT_RIGHT])) {
                
                    // Simple red violation: color flip
                    q->color = RBT_RED;
                    q->pLink[RBT_LEFT]->color = RBT_BLACK;
                    q->pLink[RBT_RIGHT]->color = RBT_BLACK;
                }

                if (rbt_IsNodeRed(q) && rbt_IsNodeRed(p)) {

                    // Hard red violation: rotations necessary
                    int dir2 = t->pLink[RBT_RIGHT] == g;
                    if (q == p->pLink[last]) {
                        t->pLink[dir2] = rbt_NodeRotate(g, !last);
                    } else {
                        t->pLink[dir2] = rbt_NodeRotate2(g, !last);
                    }
                }
          
                // Stop working if we inserted a node. This
                // check also disallows duplicates in the tree
                if (this->pCmp(q->pKey, node->pKey) == 0) {
                    break;
                }

                last = dir;
                dir = this->pCmp(q->pKey, node->pKey) < 0;

                // Move the helpers down
                if (g != NULL) {
                    t = g;
                }

                g = p;
                p = q;
                q = q->pLink[dir];
            }

            // Update the root (it may be different)
            this->pRoot = head.pLink[RBT_RIGHT];
        }

        // Make the root black for simplified logic
        this->pRoot->color = RBT_BLACK;
        ++this->size;
    }
    
    return true;
}



// Returns 1 if the value was removed, 0 otherwise. Optional node callback
// can be provided to dealloc node and/or user data. Use rb_tree_Node_dealloc
// default callback to deallocate node created by rb_tree_insert(...).
int         rbt_Delete (
    RBT_TREE    *this,
    void        *pKey
)
{
    if (this->pRoot != NULL) {
        RBT_NODE head = {0}; // False tree root
        RBT_NODE node = { .pKey = pKey }; // Value wrapper node
        RBT_NODE *q, *p, *g; // Helpers
        RBT_NODE *f = NULL;  // Found item
        int dir = 1;

        // Set up our helpers
        q = &head;
        g = p = NULL;
        q->pLink[RBT_RIGHT] = this->pRoot;
    
        // Search and push a red node down
        // to fix red violations as we go
        while (q->pLink[dir] != NULL) {
            int last = dir;

            // Move the helpers down
            g = p;
            p = q;
            q = q->pLink[dir];
            dir = this->pCmp(q->pKey, (&node)->pKey) < 0;
      
            // Save the node with matching value and keep
            // going; we'll do removal tasks at the end
            if (this->pCmp(q->pKey, (&node)->pKey) == 0) {
                f = q;
            }

            // Push the red node down with rotations and color flips
            if (!rbt_IsNodeRed(q) && !rbt_IsNodeRed(q->pLink[dir])) {
                if (rbt_IsNodeRed(q->pLink[!dir])) {
                    p = p->pLink[last] = rbt_NodeRotate(q, dir);
                } else if (!rbt_IsNodeRed(q->pLink[!dir])) {
                    RBT_NODE *s = p->pLink[!last];
                    if (s) {
                        if (!rbt_IsNodeRed(s->pLink[!last]) && !rbt_IsNodeRed(s->pLink[last])) {

                            // Color flip
                            p->color = RBT_BLACK;
                            s->color = RBT_RED;
                            q->color = RBT_RED;
                        } else {
                            int dir2 = g->pLink[RBT_RIGHT] == p;
                            if (rbt_IsNodeRed(s->pLink[last])) {
                                g->pLink[dir2] = rbt_NodeRotate2(p, last);
                            } else if (rbt_IsNodeRed(s->pLink[!last])) {
                                g->pLink[dir2] = rbt_NodeRotate(p, last);
                            }
                            
                            // Ensure correct coloring
                            q->color = g->pLink[dir2]->color = RBT_RED;
                            g->pLink[dir2]->pLink[RBT_LEFT]->color = RBT_BLACK;
                            g->pLink[dir2]->pLink[RBT_RIGHT]->color = RBT_BLACK;
                        }
                    }
                }
            }
        }

        // Replace and remove the saved node
        if (f) {
            void *tmp = f->pKey;
            f->pKey = q->pKey;
            q->pKey = tmp;
            tmp = f->pValue;
            f->pValue = q->pValue;
            q->pValue = tmp;

            p->pLink[p->pLink[RBT_RIGHT] == q] = q->pLink[q->pLink[RBT_LEFT] == NULL];
            
            rbt_NodeDealloc(this, q);
            q = NULL;
        }

        // Update the root (it may be different)
        this->pRoot = head.pLink[RBT_RIGHT];

        // Make the root black for simplified logic
        if (this->pRoot != NULL) {
            this->pRoot->color = RBT_BLACK;
        }

        --this->size;
    }
    return 1;
}




RBT_NODE *      rbt_getRoot (
    RBT_TREE        *this
)
{
    RBT_NODE        *pRoot = NULL;
    
    if (this) {
        pRoot = this->pRoot;
    }
    
    return pRoot;
}



uint32_t        rbt_getSize (
    RBT_TREE        *this
)
{
    uint32_t        result = 0;
    
    if (this) {
        result = this->size;
    }
    
    return result;
}



// rb_iter

RBT_ITER *
rbt_iter_alloc () {
    return malloc(sizeof(RBT_ITER));
}



RBT_ITER *      rbt_iter_init(
    RBT_ITER        *this,
    RBT_TREE        *pTree
)
{
    if (this) {
        //this->tree = NULL;
        this->tree = pTree;
        this->node = NULL;
        this->top = 0;
    }
    return this;
}



RBT_ITER *      rbt_iter_create (
    RBT_TREE        *pTree
)
{
    return rbt_iter_init(rbt_iter_alloc(), pTree);
}


void            rbt_iter_dealloc (
    RBT_ITER        *this
) 
{
    if (this) {
        free(this);
    }
}



// Internal function, init traversal object, dir determines whether
// to begin traversal at the smallest or largest valued node.
static
void *          rbt_iter_start(RBT_ITER *this, int dir)
{
    void            *result = NULL;
    if (this) {
        this->node = this->tree->pRoot;
        this->top = 0;

        // Save the path for later selfersal
        if (this->node != NULL) {
            while (this->node->pLink[dir] != NULL) {
                this->path[this->top++] = this->node;
                this->node = this->node->pLink[dir];
            }
        }

        result = this->node == NULL ? NULL : this->node->pKey;
    }
    return result;
}



// Traverse a red black tree in the user-specified direction (0 asc, 1 desc)
static 
void *          rbt_iter_move (
    RBT_ITER        *this,
    int             dir
)
{
    if (this->node->pLink[dir] != NULL) {

        // Continue down this branch
        this->path[this->top++] = this->node;
        this->node = this->node->pLink[dir];
        while ( this->node->pLink[!dir] != NULL ) {
            this->path[this->top++] = this->node;
            this->node = this->node->pLink[!dir];
        }
    } else {
        
        // Move to the next branch
        RBT_NODE *last = NULL;
        do {
            if (this->top == 0) {
                this->node = NULL;
                break;
            }
            last = this->node;
            this->node = this->path[--this->top];
        } while (last == this->node->pLink[dir]);
    }
    return this->node == NULL ? NULL : this->node->pKey;
}

void *          rbt_iter_first (
    RBT_ITER        *this
)
{
    return rbt_iter_start(this, RBT_LEFT);
}

void *          rbt_iter_last (
    RBT_ITER        *this
)
{
    return rbt_iter_start(this, RBT_RIGHT);
}

void *          rbt_iter_next (
    RBT_ITER        *this
)
{
    return rbt_iter_move(this, RBT_RIGHT);
}

void *          rbt_iter_prev (RBT_ITER *this) {
    return rbt_iter_move(this, RBT_LEFT);
}





void            rbt_DumpTreeNode (
    RBT_TREE        *this,
    RBT_NODE        *pNode
)
{
    
    if (pNode->pLink[RBT_LEFT])
        rbt_DumpTreeNode(this, pNode->pLink[RBT_LEFT]);
    fprintf(
            stderr,
            "\t %p  L=%p R=%p %s   %p:%p\n",
            pNode,
            pNode->pLink[RBT_LEFT],
            pNode->pLink[RBT_RIGHT],
            pNode->color ? "red" : "black",
            pNode->pKey,
            pNode->pValue
    );
    if (pNode->pLink[RBT_RIGHT])
        rbt_DumpTreeNode(this, pNode->pLink[RBT_RIGHT]);
}


void            rbt_DumpTree (RBT_TREE *this)
{
    fprintf(stderr, "In-order Tree Dump of %d Nodes\n", this->size);
    rbt_DumpTreeNode(this, this->pRoot);
    fprintf(stderr, "\n\n\n");
}



int                 rbt_VerifyTree (
    RBT_TREE            *this,
    RBT_NODE            *pNode
)
{
    int                 lh;
    int                 rh;
    int                 cmp;
    
    if ( pNode == NULL )
        return 1;
    else {
        RBT_NODE *ln = pNode->pLink[RBT_LEFT];
        RBT_NODE *rn = pNode->pLink[RBT_RIGHT];
        
        /* Consecutive red links */
        if (rbt_IsNodeRed(pNode)) {
            if (rbt_IsNodeRed(ln) || rbt_IsNodeRed(rn)) {
                rbt_DumpTree(this);
                DEBUG_BREAK();
                fprintf(stderr, "ERROR - Red violation\n\n");
                return 0;
            }
        }
        
        lh = rbt_VerifyTree(this, ln);
        rh = rbt_VerifyTree(this, rn);
        
        /* Invalid binary search tree */
        if ( ln != NULL && (cmp = this->pCmp(ln->pKey, pNode->pKey)) >= 0 )
        {
            rbt_DumpTree(this);
            DEBUG_BREAK();
            fprintf(stderr, "ERROR - Binary tree left node violation\n\n" );
            return 0;
        }
        if ( rn != NULL && (cmp = this->pCmp(rn->pKey, pNode->pKey)) <= 0)
        {
            rbt_DumpTree(this);
            DEBUG_BREAK();
            fprintf(stderr, "ERROR - Binary tree right node violation\n\n" );
            return 0;
        }

        /* Black height mismatch */
        if ( lh != 0 && rh != 0 && lh != rh ) {
            rbt_DumpTree(this);
            DEBUG_BREAK();
            fprintf(stderr, "ERROR - Black violation\n\n" );
            return 0;
        }
        
        /* Only count black links */
        if ( lh != 0 && rh != 0 )
            return rbt_IsNodeRed (pNode) ? lh : lh + 1;
        else
            return 0;
    }
}



//---------------------------------------------------------------
//                  V i s i t  N o d e s
//---------------------------------------------------------------

/*! Visit all the nodes from the given node and below in the Tree
 using a Pre-order traversal.
 */
ERESULT         rbt_VisitNodeInRecurse (
    RBT_TREE        *this,
    RBT_NODE        *pRecord,
    P_ERESULT_EXIT3 pScan,
    OBJ_ID          pObj,            // Used as first parameter of scan method
    void            *pArg3
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RBT_NODE        *pWork;
    
    if (pRecord) {
        pWork = pRecord->pLink[RBT_LEFT];
        if (pWork) {
            eRc = rbt_VisitNodeInRecurse(this, pWork, pScan, pObj, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
        }
        eRc = pScan(pObj, pRecord, pArg3);
        if (ERESULT_FAILED(eRc))
            return eRc;
        pWork = pRecord->pLink[RBT_RIGHT];
        if (pWork) {
            eRc = rbt_VisitNodeInRecurse(this, pWork, pScan, pObj, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
        }
    }
    
    return eRc;
}


/*! Visit all the nodes from the given node and below in the Tree
 using a Post-order traversal.
 */
ERESULT         rbt_VisitNodePostRecurse (
    RBT_TREE        *this,
    RBT_NODE        *pRecord,
    P_ERESULT_EXIT3 pScan,
    OBJ_ID          pObj,            // Used as first parameter of scan method
    void            *pArg3
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RBT_NODE        *pWork;
    
    if (pRecord) {
        pWork = pRecord->pLink[RBT_LEFT];
        if (pWork) {
            eRc = rbt_VisitNodePostRecurse(this, pWork, pScan, pObj, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
        }
        pWork = pRecord->pLink[RBT_RIGHT];
        if (pWork) {
            eRc = rbt_VisitNodePostRecurse(this, pWork, pScan, pObj, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
        }
        eRc = pScan(pObj, pRecord, pArg3);
        if (ERESULT_FAILED(eRc))
            return eRc;
    }
    
    return eRc;
}


/*! Visit all the nodes from the given node and below in the Tree
 using a Pre-order traversal.
 */
ERESULT         rbt_VisitNodePreRecurse (
    RBT_TREE        *this,
    RBT_NODE        *pRecord,
    P_ERESULT_EXIT3 pScan,
    OBJ_ID          pObj,            // Used as first parameter of scan method
    void            *pArg3
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RBT_NODE        *pWork;
    
    if (pRecord) {
        eRc = pScan(pObj, pRecord, pArg3);
        if (ERESULT_FAILED(eRc))
            return eRc;
        pWork = pRecord->pLink[RBT_LEFT];
        if (pWork) {
            eRc = rbt_VisitNodePreRecurse(this, pWork, pScan, pObj, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
        }
        pWork = pRecord->pLink[RBT_RIGHT];
        if (pWork) {
            eRc = rbt_VisitNodePreRecurse(this, pWork, pScan, pObj, pArg3);
            if (ERESULT_FAILED(eRc))
                return eRc;
        }
    }
    
    return eRc;
}







