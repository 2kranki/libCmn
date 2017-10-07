// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                Node Entry (nodeEntry) Header
//****************************************************************
/*
 * Program
 *			Node Entry (nodeEntry)
 * Purpose
 *			A node entry is a node but with connective pointers
 *          or properties which allow the node entry to be used
 *          in other container objects such as Hashes, Lists,
 *          Graphs and Trees.
 *
 * Remarks
 *	1.      The child index is simply a synonym for the right index and
 *          the sibling index is a synonym for the left index.
 *
 * History
 *	08/29/2016 Generated
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
#include        <node.h>


#ifndef         NODEENTRY_H
#define         NODEENTRY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // NODEENTRY_DATA is defined in node.h
    
    typedef struct nodeEntry_vtbl_s	{
        NODE_VTBL       iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeEntry_object.c.
        // Properties:
        // NodeEntry Properties:
        uint32_t        (*pGetLeft)(NODEENTRY_DATA *this);
        bool            (*pSetLeft)(NODEENTRY_DATA *this, uint32_t value);
        uint32_t        (*pGetParent)(NODEENTRY_DATA *this);
        bool            (*pSetParent)(NODEENTRY_DATA *this, uint32_t value);
        uint32_t        (*pGetRight)(NODEENTRY_DATA *this);
        bool            (*pSetRight)(NODEENTRY_DATA *this, uint32_t value);
        
        
        // Methods:
        //bool        (*pIsEnabled)(NODEENTRY_DATA *);
    } NODEENTRY_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to nodeEntry object if successful, otherwise OBJ_NIL.
     */
    NODEENTRY_DATA * nodeEntry_Alloc(
        void
    );
    
    
    NODEENTRY_DATA * nodeEntry_New(
        NODE_DATA       *pNode
    );
    
    
    NODEENTRY_DATA *     nodeEntry_NewWithUTF8AndClass(
        const
        char            *pName,
        int32_t         cls,
        OBJ_ID          pData
    );
    
    
    NODEENTRY_DATA * nodeEntry_NewWithUTF8Con(
        const
        char            *pName,
        OBJ_ID          pData
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        nodeEntry_getChild(
        NODEENTRY_DATA  *this
    );
    
    bool            nodeEntry_setChild(
        NODEENTRY_DATA  *this,
        uint32_t        value
    );
    
    
    // Class is used to categorize the node with some kind of
    // identification if needed.
    int32_t         nodeEntry_getClass(
        NODEENTRY_DATA  *this
    );
    
    bool            nodeEntry_setClass(
        NODEENTRY_DATA  *this,
        int32_t         value
    );
    
    
    OBJ_ID          nodeEntry_getData(
        NODEENTRY_DATA  *this
    );
    
    bool            nodeEntry_setData(
        NODEENTRY_DATA  *this,
        OBJ_ID          pValue
    );
    
    
    uint32_t        nodeEntry_getIndex(
        NODEENTRY_DATA  *this
    );
    
    bool            nodeEntry_setIndex(
        NODEENTRY_DATA  *this,
        uint32_t        value
    );
    
    
    uint32_t        nodeEntry_getLeft(
        NODEENTRY_DATA  *this
    );
    
    bool            nodeEntry_setLeft(
        NODEENTRY_DATA  *this,
        uint32_t        value
    );
    
    
    uint32_t        nodeEntry_getMiddle(
        NODEENTRY_DATA  *this
    );
    
    bool            nodeEntry_setMiddle(
        NODEENTRY_DATA  *this,
        uint32_t        value
    );
    
    
    uint16_t        nodeEntry_getMisc(
        NODEENTRY_DATA  *this
    );
    
    
    NODE_DATA *     nodeEntry_getNode(
        NODEENTRY_DATA  *this
    );
    
    
    uint32_t        nodeEntry_getParent(
        NODEENTRY_DATA  *this
    );
    
    bool            nodeEntry_setParent(
        NODEENTRY_DATA  *this,
        uint32_t        value
    );
    
    
    NODEARRAY_DATA * nodeEntry_getProperties(
        NODEENTRY_DATA  *this
    );
    
    
    uint32_t        nodeEntry_getRight(
        NODEENTRY_DATA  *this
    );
    
    bool            nodeEntry_setRight(
        NODEENTRY_DATA  *this,
        uint32_t        value
    );
    
    
    uint32_t        nodeEntry_getSibling(
        NODEENTRY_DATA  *this
    );
    
    bool            nodeEntry_setSibling(
        NODEENTRY_DATA  *this,
        uint32_t        value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    NODEENTRY_DATA * nodeEntry_Init(
        NODEENTRY_DATA  *this,
        NODE_DATA       *pNode
    );


    NODEENTRY_DATA * nodeEntry_InitWithUTF8(
        NODEENTRY_DATA  *this,
        const
        char            *pName,
        OBJ_ID          pData
    );
    
    
    NODEENTRY_DATA * nodeEntry_InitWithUTF8Con(
        NODEENTRY_DATA  *this,
        const
        char            *pName,
        OBJ_ID          pData
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = nodeEntry_ToDebugString(pObj,4);
     @endcode
     @param     this    nodeEntry object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    nodeEntry_ToDebugString(
        NODEENTRY_DATA  *this,
        int             indent
    );
    
    
    bool        nodeEntry_Visited(
        NODEENTRY_DATA	*this
    );
    
    
    bool        nodeEntry_VisitedSet(
        NODEENTRY_DATA	*this,
        bool            fValue
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEENTRY_H */

