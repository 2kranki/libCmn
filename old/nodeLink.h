// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODELINK Console Transmit Task (nodeLink) Header
//****************************************************************
/*
 * Program
 *			Separate nodeLink (nodeLink)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate nodeLink to run things without complications
 *          of interfering with the main nodeLink. A nodeLink may be 
 *          called a nodeLink on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	06/30/2018 Generated
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


#ifndef         NODELINK_H
#define         NODELINK_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

    // Below defined in node.h
    //typedef struct nodeLink_data_s	NODELINK_DATA;    // Inherits from Node.

    typedef struct nodeLink_vtbl_s	{
        NODE_VTBL       iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeLink_object.c.
        // Properties:
        // Methods:
        uint32_t        (*pGetIndex)(NODELINK_DATA *this);
        bool            (*pSetIndex)(NODELINK_DATA *this, uint32_t value);
        uint32_t        (*pGetLeftLink)(NODELINK_DATA *this);
        bool            (*pSetLeftLink)(NODELINK_DATA *this, uint32_t value);
        uint32_t        (*pGetLeftThread)(NODELINK_DATA *this);
        bool            (*pSetLeftThread)(NODELINK_DATA *this, uint32_t value);
        uint32_t        (*pGetMiddle)(NODELINK_DATA *this);
        bool            (*pSetMiddle)(NODELINK_DATA *this, uint32_t value);
        uint32_t        (*pGetParent)(NODELINK_DATA *this);
        bool            (*pSetParent)(NODELINK_DATA *this, uint32_t value);
        uint32_t        (*pGetRightLink)(NODELINK_DATA *this);
        bool            (*pSetRightLink)(NODELINK_DATA *this, uint32_t value);
        uint32_t        (*pGetRightThread)(NODELINK_DATA *this);
        bool            (*pSetRightThread)(NODELINK_DATA *this, uint32_t value);
    } NODELINK_VTBL;



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
     @return    pointer to nodeLink object if successful, otherwise OBJ_NIL.
     */
    NODELINK_DATA * nodeLink_Alloc(
        void
    );
    
    
    OBJ_ID          nodeLink_Class(
        void
    );
    
    
    NODELINK_DATA * nodeLink_New(
        void
    );
    
    NODELINK_DATA * nodeLink_NewWithUTF8AndClass(
        int32_t         cls,
        const
        char            *pName,
        OBJ_ID          pData
    );
    

    NODELINK_DATA * nodeLink_NewWithUTF8ConAndClass(
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    int16_t         nodeLink_getBalance(
        NODELINK_DATA   *this
    );
    
    bool            nodeLink_setBalance(
        NODELINK_DATA   *this,
        int16_t         value
    );

    
    /*!
     Child index property is used to point to the next child node
     if needed.  Note that this uses the Left index internally.
     */
    uint32_t        nodeLink_getChild(
        NODELINK_DATA   *this
    );
    
    bool            nodeLink_setChild(
        NODELINK_DATA   *this,
        uint32_t        value
    );
    
    
    int32_t         nodeLink_getClass(
        NODELINK_DATA   *this
    );
    
    
    OBJ_ID          nodeLink_getData(
        NODELINK_DATA   *this
    );
    
    
    OBJ_ID          nodeLink_getExtra(
        NODELINK_DATA   *this
    );
    
    
    /*!
     From index property is used to point to the "From" node
     if needed.  Note that this uses the Left index internally.
     */
    uint32_t        nodeLink_getFrom(
        NODELINK_DATA   *this
    );
    
    bool            nodeLink_setFrom(
        NODELINK_DATA   *this,
        uint32_t        value
    );
    
    
    uint32_t        nodeLink_getHash(
        NODELINK_DATA   *this
    );
    
    
    uint32_t        nodeLink_getIndex(
        NODELINK_DATA   *this
    );
    
    bool            nodeLink_setIndex(
        NODELINK_DATA   *this,
        uint32_t        value
    );
    

    uint32_t        nodeLink_getLeftLink(
        NODELINK_DATA   *this
    );

    bool            nodeLink_setLeftLink(
        NODELINK_DATA   *this,
        uint32_t        value
    );
    
    
    uint32_t        nodeLink_getLeftThread(
        NODELINK_DATA   *this
    );
    
    bool            nodeLink_setLeftThread(
        NODELINK_DATA   *this,
        uint32_t        value
    );
    
    
    uint32_t        nodeLink_getMiddle(
        NODELINK_DATA   *this
    );
    
    bool            nodeLink_setMiddle(
        NODELINK_DATA   *this,
        uint32_t        value
    );
    
    
    uint16_t        nodeLink_getMisc1(
        NODELINK_DATA   *this
    );
    
    bool            nodeLink_setMisc1(
        NODELINK_DATA   *this,
        uint16_t        value
    );
    

    NAME_DATA *     nodeLink_getName(
        NODELINK_DATA   *this
    );

    
    /*!
     @return    If successful, a UTF-8 string which must be freed
                with mem_Free(), otherwise NULL.
     */
    char *          nodeLink_getNameUTF8(
        NODELINK_DATA   *this
    );
    

    NODE_DATA *     nodeLink_getNode(
        NODELINK_DATA   *this
    );


    OBJ_ID          nodeLink_getOther(
        NODELINK_DATA   *this
    );
    
    
    uint32_t        nodeLink_getParent(
        NODELINK_DATA   *this
    );
    
    bool            nodeLink_setParent(
        NODELINK_DATA   *this,
        uint32_t        value
    );
    
    
    bool            nodeLink_getRightChild(
        NODELINK_DATA   *this
    );
    
    bool            nodeLink_setRightChild(
        NODELINK_DATA   *this,
        bool            fValue
    );

    
    uint32_t        nodeLink_getRightLink(
        NODELINK_DATA   *this
    );
    
    bool            nodeLink_setRightLink(
        NODELINK_DATA   *this,
        uint32_t        value
    );
    
    
    uint32_t        nodeLink_getRightThread(
        NODELINK_DATA   *this
    );
    
    bool            nodeLink_setRightThread(
        NODELINK_DATA   *this,
        uint32_t        value
    );
    
    
    /*!
     Sibling index property is used to point to the next Sibling node
     if needed.  Note that this uses the Left index internally.
     */
    uint32_t        nodeLink_getSibling(
        NODELINK_DATA   *this
    );
    
    bool            nodeLink_setSibling(
        NODELINK_DATA   *this,
        uint32_t        value
    );
    
    
    /*!
     To index property is used to point to the "To" node
     if needed.  Note that this uses the Right index internally.
     */
    uint32_t        nodeLink_getTo(
        NODELINK_DATA   *this
    );
    
    bool            nodeLink_setTo(
        NODELINK_DATA   *this,
        uint32_t        value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Compare this node's class to the other node's class. If they are equal,
     then compare the name.  So, this compares the name within class.
     @result
     ERESULT_SUCCESS_EQUAL if this == other,
     ERESULT_SUCCESS_LESS_THAN if this < other
     or ERESULT_SUCCESS_GREATER_THAN if this > other.
     */
    ERESULT         nodeLink_Compare(
        NODELINK_DATA   *this,
        NODELINK_DATA   *pOther
    );
    
    
    /*!
     Compare this node's name to a character string.
     @result
     ERESULT_SUCCESS_EQUAL if this == pName,
     ERESULT_SUCCESS_LESS_THAN if this < pName
     or ERESULT_SUCCESS_GREATER_THAN if this > pName.
     */
    ERESULT         nodeLink_CompareA(
        NODELINK_DATA   *this,
        int32_t         cls,
        const
        char            *pName
    );
    
    
    NODELINK_DATA *   nodeLink_Init(
        NODELINK_DATA     *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = nodeLink_ToDebugString(this,4);
     @endcode 
     @param     this    NODELINK object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    nodeLink_ToDebugString(
        NODELINK_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODELINK_H */

