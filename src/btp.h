//********************************************************************
//                        Hash Table (btp)
//********************************************************************

// vi: nu:noai:ts=4:sw=4

/*
 * Program
 *				NUL-Terminated String Hash Table (BTP)
 * Purpose
 *				"A 'binary tree' is a finite set of elements that is
 *              either empty or is partitioned into three disjoint
 *              subsets. The first subset contains a single element
 *              called the 'root' of the tree. The other two subsets
 *              are themselves binary trees, called the left and
 *              right subtrees of the original tree. A left or right
 *              subtree can be empty. Each element of the a binary
 *              tree is called a 'node' of the tree."
 *
 *              "If A is the root of a binary tree and B is the root
 *              of its left or right subtree, then A is said to be
 *              the 'father' of B and B is said to be the left or
 *              right 'son' of A. A node that has no sons is called
 *              a 'leaf'. If every nonleaf node in a binary tree has
 *              nonempty left and right subtrees, the tree is termed
 *              a 'strictly binary tree'. A 'complete binary tree'
 *              of depth 'd' is the strctly binary tree all of whose
 *              leaves are at level 'd'."
 *
 *              "A 'binary search tree' is a binary tree that all
 *              elements in the left subtree of a node n are less
 *              than the contents of node n, and all of the elements
 *              in the right subtree of n are greater than or equal
 *              to the conents of n."
 *
 *              btp provides a set of functions to create and use a
 *              "Binary Search Tree" where each node consists of some
 *              form of data with a comparison routine that can pro-
 *              vide for ordering the tree. The comparison routine
 *              must be able to compare two objects and return 0 if
 *              they are equal, -1 if the first object is less than
 *              table for keys of szString. Internal nodes are 
 *              blocked to limit memory fragmentation and the
 *              maximum hash table size is 65535. The overall
 *              size can grow bigger since it would be 65535
 *              chains of nodes.
 *
 *              Internally, support for generic binary trees is
 *              supported. However, node structure is required
 *              for this. So, it is not an external feature.
 * Remarks
 *	1.			All keys must be unique within the table.	
 * References
 *		"Data Structures and Algorithms", Alfred V. Aho et al,
 *			Addison-Wesley, 1985
 *		"Data Structures using C", Aaron M. Tenenbaum et al,
 *			Prentice-Hall, 1990
 *		"Programs and Data Structures in C", Leendert Ammeraal,
 *			John Wiley & Sons, 1987
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



#ifndef         BTP_H
#define         BTP_H	1



#ifdef	__cplusplus
extern	"C" {
#endif
    


    /****************************************************************
    * * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
    ****************************************************************/


    typedef struct btp_data_s  BTP_DATA;
    typedef struct btp_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        // Properties:
        // Methods:
    } BTP_VTBL;
    
    
    typedef int (*P_BTP_COMPARE)(const void *pKey1, const void *pKey2);

    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    BTP_DATA *      btp_Alloc(
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------
    
    bool			btp_setCompare(
        BTP_DATA        *this,
        P_BTP_COMPARE   pCompare
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
    /* Add() creates a new node and adds it to the hash table if the
     * supplied key does not exist in the table.
     */
    bool            btp_Add(
        BTP_DATA        *this,
        void			*pData
    );


    /* Count() returns the current number of used entries.
     * Returns:
     *		Current Number of Entries in Table
     */
    uint32_t        btp_Count(
        BTP_DATA		*this
    );


    /* Delete() deletes an active entry and sets it up for re-use
     * on the next Add operation.
     * Returns:
     *		TRUE	= Entry successfully deleted.
     *		FALSE	= Entry could not be deleted.
     */
    bool            btp_Delete(
        BTP_DATA        *this,
        const
        void            *pData
    );


    const
    void *          btp_Find(
        BTP_DATA        *this,
        const
        void            *pData
    );
    
    
    BTP_DATA *      btp_Init(
        BTP_DATA        *this,
        P_BTP_COMPARE   pCompare
    );


    bool			btp_VisitPreorder(
        BTP_DATA        *this,
        bool            (*pVisit)(BTP_DATA *this, const void *pData)
    );


    bool			btp_VisitInorder(
        BTP_DATA        *this,
        bool            (*pVisit)(BTP_DATA *this, const void *pData)
    );
    
    
    bool			btp_VisitPostorder(
        BTP_DATA        *this,
        bool            (*pVisit)(BTP_DATA *this, const void *pData)
    );
    
    
#ifdef	__cplusplus
};
#endif




#endif
