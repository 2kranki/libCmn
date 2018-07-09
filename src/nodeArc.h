// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Node Graph Arc (nodeArc) Header
//****************************************************************
/*
 * Program
 *			Node Graph Arc (nodeArc)
 * Purpose
 *			An Node Arc is used to show the relationship between
 *          two nodes in a graph.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	07/14/2016 Generated
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


#ifndef         NODEARC_H
#define         NODEARC_H 1



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************



    typedef struct nodeArc_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeArc_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEARC_DATA *);
    } NODEARC_VTBL;



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
     @return:   pointer to nodeArc object if successful, otherwise OBJ_NIL.
     */
    NODEARC_DATA *  nodeArc_Alloc(
        void
    );
    
    
    NODEARC_DATA *  nodeArc_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            nodeArc_getAdjacent(
        NODEARC_DATA    *this
    );
    
    bool            nodeArc_setAdjacent(
        NODEARC_DATA    *this,
        bool            fValue
    );
    
    
    NODELINK_DATA * nodeArc_getInNode(
        NODEARC_DATA    *this
    );

    bool            nodeArc_setInNode(
        NODEARC_DATA    *this,
        NODELINK_DATA   *pValue
    );
    
    
    NODELINK_DATA * nodeArc_getOutNode(
        NODEARC_DATA    *this
    );
    
    bool            nodeArc_setOutNode(
        NODEARC_DATA    *this,
        NODELINK_DATA   *pValue
    );
    
    
    uint32_t        nodeArc_getWeight(
        NODEARC_DATA    *this
    );
    
    bool            nodeArc_setWeight(
        NODEARC_DATA    *this,
        uint32_t        value
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    NODEARC_DATA *  nodeArc_Init(
        NODEARC_DATA    *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = nodeArc_ToDebugString(pObj,4);
     @endcode
     @param     this    nodeArc object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     nodeArc_ToDebugString(
        NODEARC_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEARC_H */

