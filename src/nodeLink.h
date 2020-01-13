// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          A Node with Integer Links (NodeLink) Header
//****************************************************************
/*
 * Program
 *			A Node with Integer Links
 * Purpose
 *			This object provides a regular node with additional
 *          integer links that allow it to be easily used in lists,
 *          trees, etc.  Integer links allow the data to be written
 *          to disk.
 *
 * Remarks
 *	1.      This object uses OBJ_FLAG_USER5..OBJ_FLAG_USER7 internally.
 *
 * History
 *  06/30/2018 Generated
 *	01/12/2020 Regenerated
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
#include        <Node.h>


#ifndef         NODELINK_H
#define         NODELINK_H


#define   NODELINK_JSON_SUPPORT 1
//#define   NODELINK_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    //typedef struct NodeLink_data_s	NODELINK_DATA;            // Inherits from OBJ
    //typedef struct NodeLink_class_data_s NODELINK_CLASS_DATA;   // Inherits from OBJ

    typedef struct NodeLink_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeLink_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODELINK_DATA *);
    } NODELINK_VTBL;

    typedef struct NodeLink_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeLink_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODELINK_DATA *);
    } NODELINK_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODELINK_SINGLETON
    NODELINK_DATA * NodeLink_Shared (
        void
    );

    void            NodeLink_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeLink object if successful, otherwise OBJ_NIL.
     */
    NODELINK_DATA * NodeLink_Alloc (
        void
    );
    
    
    OBJ_ID          NodeLink_Class (
        void
    );
    
    
    NODELINK_DATA * NodeLink_New (
        void
    );
    
    
    NODELINK_DATA * NodeLink_NewWithUTF8AndClass(
        int32_t         cls,
        const
        char            *pName,
        OBJ_ID          pData
    );


    NODELINK_DATA * NodeLink_NewWithUTF8ConAndClass(
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    );


    NODELINK_DATA *   NodeLink_NewFromJsonString(
        ASTR_DATA       *pString
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    int16_t         NodeLink_getBalance(
        NODELINK_DATA   *this
    );

    bool            NodeLink_setBalance(
        NODELINK_DATA   *this,
        int16_t         value
    );


    /*!
     Child index property is used to point to the next child node
     if needed.  Note that this uses the Left index internally.
     */
    uint32_t        NodeLink_getChild(
        NODELINK_DATA   *this
    );

    bool            NodeLink_setChild(
        NODELINK_DATA   *this,
        uint32_t        value
    );


    int32_t         NodeLink_getClass(
        NODELINK_DATA   *this
    );


    OBJ_ID          NodeLink_getData(
        NODELINK_DATA   *this
    );


    OBJ_ID          NodeLink_getExtra(
        NODELINK_DATA   *this
    );


    /*!
     From index property is used to point to the "From" node
     if needed.  Note that this uses the Left index internally.
     */
    uint32_t        NodeLink_getFrom(
        NODELINK_DATA   *this
    );

    bool            NodeLink_setFrom(
        NODELINK_DATA   *this,
        uint32_t        value
    );


    uint32_t        NodeLink_getHash(
        NODELINK_DATA   *this
    );


    uint32_t        NodeLink_getIndex(
        NODELINK_DATA   *this
    );

    bool            NodeLink_setIndex(
        NODELINK_DATA   *this,
        uint32_t        value
    );


    uint32_t        NodeLink_getLeftLink(
        NODELINK_DATA   *this
    );

    bool            NodeLink_setLeftLink(
        NODELINK_DATA   *this,
        uint32_t        value
    );


    uint32_t        NodeLink_getLeftThread(
        NODELINK_DATA   *this
    );

    bool            NodeLink_setLeftThread(
        NODELINK_DATA   *this,
        uint32_t        value
    );


    uint32_t        NodeLink_getMiddle(
        NODELINK_DATA   *this
    );

    bool            NodeLink_setMiddle(
        NODELINK_DATA   *this,
        uint32_t        value
    );


    uint16_t        NodeLink_getMisc1(
        NODELINK_DATA   *this
    );

    bool            NodeLink_setMisc1(
        NODELINK_DATA   *this,
        uint16_t        value
    );


    NAME_DATA *     NodeLink_getName(
        NODELINK_DATA   *this
    );


    /*!
     @return    If successful, a UTF-8 string which must be freed
                with mem_Free(), otherwise NULL.
     */
    char *          NodeLink_getNameUTF8(
        NODELINK_DATA   *this
    );


    NODE_DATA *     NodeLink_getNode(
        NODELINK_DATA   *this
    );


    OBJ_ID          NodeLink_getOther(
        NODELINK_DATA   *this
    );


    uint32_t        NodeLink_getParent(
        NODELINK_DATA   *this
    );

    bool            NodeLink_setParent(
        NODELINK_DATA   *this,
        uint32_t        value
    );


    bool            NodeLink_getRightChild(
        NODELINK_DATA   *this
    );

    bool            NodeLink_setRightChild(
        NODELINK_DATA   *this,
        bool            fValue
    );


    uint32_t        NodeLink_getRightLink(
        NODELINK_DATA   *this
    );

    bool            NodeLink_setRightLink(
        NODELINK_DATA   *this,
        uint32_t        value
    );


    uint32_t        NodeLink_getRightThread(
        NODELINK_DATA   *this
    );

    bool            NodeLink_setRightThread(
        NODELINK_DATA   *this,
        uint32_t        value
    );


    /*!
     Sibling index property is used to point to the next Sibling node
     if needed.  Note that this uses the Left index internally.
     */
    uint32_t        NodeLink_getSibling(
        NODELINK_DATA   *this
    );

    bool            NodeLink_setSibling(
        NODELINK_DATA   *this,
        uint32_t        value
    );


    /*!
     To index property is used to point to the "To" node
     if needed.  Note that this uses the Right index internally.
     */
    uint32_t        NodeLink_getTo(
        NODELINK_DATA   *this
    );

    bool            NodeLink_setTo(
        NODELINK_DATA   *this,
        uint32_t        value
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = NodeLink_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another NODELINK object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         NodeLink_Assign (
        NODELINK_DATA   *this,
        NODELINK_DATA   *pOther
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         NodeLink_Compare (
        NODELINK_DATA   *this,
        NODELINK_DATA   *pOther
    );

    ERESULT         NodeLink_CompareA(
        NODELINK_DATA   *this,
        int32_t         cls,
        const
        char            *pName
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        NodeLink      *pCopy = NodeLink_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a NODELINK object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODELINK_DATA * NodeLink_Copy (
        NODELINK_DATA   *this
    );


    NODELINK_DATA * NodeLink_Init (
        NODELINK_DATA   *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeLink_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    NodeLink_ToDebugString (
        NODELINK_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODELINK_H */

