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

#ifndef __RB_TREE_H__
#define __RB_TREE_H__ 1

#include        <cmn_defs.h>
#include        <stdio.h>
#include        <stdint.h>
#include        <stddef.h>
#include        <stdlib.h>

#ifndef RB_ITER_MAX_HEIGHT
#define RB_ITER_MAX_HEIGHT 64 // Tallest allowable tree to iterate
#endif



typedef struct rbt_node_s RBT_NODE;
typedef struct rbt_tree_s RBT_TREE;
typedef struct rbt_iter_s RBT_ITER;

typedef int  (*rbt_node_cmp_f) (RBT_TREE *this, RBT_NODE *a, RBT_NODE *b);
typedef void (*rbt_node_f)     (RBT_TREE *this, RBT_NODE *node);


// These colors must remain the values that they are
// because C uses 0 and 1 as values of logical comparison
// and ! (not).  For instance, in C, !RBTREE_BLACK == RBTREE_RED.
// The same goes for RBT_LEFT and RBT_RIGHT.
//
struct rbt_node_s {
    int             color;        // Color red (1), black (0)
#define RBT_BLACK   0
#define RBT_RED     1
    RBT_NODE        *pLink[2];    // Link left [0] and right [1]
#define RBT_LEFT    0
#define RBT_RIGHT   1
    void            *pKey;
    void            *pValue;
};


struct rbt_tree_s {
    RBT_NODE            *pRoot;
    int                 (*pCmp)(void *, void *);
    uint32_t            size;
    uint32_t            dataSize;
    
    RBT_NODE *          (*pNodeAlloc)(OBJ_ID);
    void                (*pNodeFree)(OBJ_ID, RBT_NODE *);
    OBJ_ID              pObjAllocFree;
    
};


struct rbt_iter_s {
    RBT_TREE        *tree;
    RBT_NODE        *node;                      // Current node
    RBT_NODE        *path[RB_ITER_MAX_HEIGHT];  // Traversal path
    size_t          top;                        // Top of stack
};



int             rbt_node_cmp_ptr_cb     (RBT_TREE *this, void *pKeyA, void *pKeyB);
void            rbt_node_dealloc_cb     (RBT_TREE *this, RBT_NODE *node);


RBT_NODE *      rbt_NodeNew             (RBT_TREE *this, void *pKey, void *pValue);
RBT_NODE *      rbt_NodeInit            (RBT_TREE *, RBT_NODE *, void *, void *);
RBT_NODE *      rbt_NodeDealloc         (RBT_TREE *this, RBT_NODE *pNode);
int             rbt_IsNodeRed           (RBT_NODE *pNode);

uint32_t        rbt_getSize             (RBT_TREE *this);
RBT_NODE *      rbt_getRoot             (RBT_TREE *this);


RBT_TREE *      rbt_Alloc               (void);
int             rbt_Delete              (RBT_TREE *this, void *pKey);
void            rbt_DeleteAll           (RBT_TREE *this);
void *          rbt_Find                (RBT_TREE *this, void *pKey);
RBT_NODE        *rbt_FindNode           (RBT_TREE *this, RBT_NODE *pNode);
RBT_TREE *      rbt_Init (
    RBT_TREE        *pTree,
    int             (*pCmp)(void *, void *),
    uint32_t        dataSize,
    RBT_NODE *      (*pNodeAlloc)(OBJ_ID),
    void            (*pNodeFree)(OBJ_ID, RBT_NODE *),
    OBJ_ID          pObjAllocFree
);
bool            rbt_Insert              (RBT_TREE *this, void *pKey, void *pValue);
bool            rbt_InsertNode          (RBT_TREE *this, RBT_NODE *pNode);


void            rbt_DumpTree            (RBT_TREE *this);
int             rbt_VerifyTree          (RBT_TREE *this, RBT_NODE *pNode);

RBT_ITER *      rbt_iter_alloc          (void);
RBT_ITER *      rbt_iter_init           (RBT_ITER *this, RBT_TREE *pTree);
RBT_ITER *      rbt_iter_create         (RBT_TREE *pTree);
void            rbt_iter_dealloc        (RBT_ITER *this);
void           *rbt_iter_first          (RBT_ITER *this);
void           *rbt_iter_last           (RBT_ITER *this);
void           *rbt_iter_next           (RBT_ITER *this);
void           *rbt_iter_prev           (RBT_ITER *this);





ERESULT         rbt_VisitNodeInRecurse (
    RBT_TREE        *this,
    RBT_NODE        *pRecord,
    P_ERESULT_EXIT3 pScan,          // Second parameter is RBT_NODE. Return ERESULT_*
    //                              // error to terminate scan.
    OBJ_ID          pObj,           // Used as first parameter of scan method
    void            *pArg3          // Used as third parameter of scan method
);


ERESULT         rbt_VisitNodePostRecurse (
    RBT_TREE        *this,
    RBT_NODE        *pRecord,
    P_ERESULT_EXIT3 pScan,          // Second parameter is RBT_NODE. Return ERESULT_*
    //                              // error to terminate scan.
    OBJ_ID          pObj,           // Used as first parameter of scan method
    void            *pArg3          // Used as third parameter of scan method
);


ERESULT         rbt_VisitNodePreRecurse (
    RBT_TREE        *this,
    RBT_NODE        *pRecord,
    P_ERESULT_EXIT3 pScan,          // Second parameter is RBT_NODE. Return ERESULT_*
    //                              // error to terminate scan.
    OBJ_ID          pObj,           // Used as first parameter of scan method
    void            *pArg3          // Used as third parameter of scan method
);


#endif
