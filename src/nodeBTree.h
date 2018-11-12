// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Binary Tree of Nodes (nodeBTree) Header
//****************************************************************
/*
 * Program
 *			Binary Tree of Nodes (nodeBTree)
 * Purpose
 *			This object provides support for a binary tree of nodes.
 * Remarks
 *	1.      None
 *
 * History
 *	11/12/2018 Generated
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
#include        <nodeLink.h>


#ifndef         NODEBTREE_H
#define         NODEBTREE_H


//#define   NODEBTREE_SINGLETON    1

#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************



    typedef struct nodeBTree_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeBTree_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEBTREE_DATA *);
    } NODEBTREE_VTBL;

    typedef struct nodeBTree_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeBTree_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEBTREE_DATA *);
    } NODEBTREE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEBTREE_SINGLETON
    NODEBTREE_DATA *     nodeBTree_Shared(
        void
    );

    bool            nodeBTree_SharedReset(
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to nodeBTree object if successful, otherwise OBJ_NIL.
     */
    NODEBTREE_DATA * nodeBTree_Alloc(
        void
    );
    
    
    OBJ_ID          nodeBTree_Class(
        void
    );
    
    
    NODEBTREE_DATA * nodeBTree_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         nodeBTree_Disable(
        NODEBTREE_DATA  *this
    );


    ERESULT         nodeBTree_Enable(
        NODEBTREE_DATA	*this
    );

   
    NODEBTREE_DATA * nodeBTree_Init(
        NODEBTREE_DATA  *this
    );


    ERESULT         nodeBTree_IsEnabled(
        NODEBTREE_DATA	*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = nodeBTree_ToDebugString(this,4);
     @endcode 
     @param     this    NODEBTREE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    nodeBTree_ToDebugString(
        NODEBTREE_DATA  *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEBTREE_H */

