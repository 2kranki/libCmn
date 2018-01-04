// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Node Container (node) Header
//****************************************************************
/*
 * Program
 *				Node Container (node)
 * Purpose
 *				This object provides a data structure for named
 *              data. So, a name is required while data is optional.
 *              It may have extra properties attached to it.
 *              The properties are lazily added. So, if you don't 
 *              use them. You do not pay much for it in memory usage.
 *
 *              The required name can only be entered when the node is
 *              created and should not be changed after that time.
 *
 *              If you need it, the 'other' property is available
 *              for use. For instance, you might use it to point to
 *              a symbol table entry when the node represents a 
 *              portion of a parsed program.
 *
 * Remarks
 *	1.          None
 *
 * History
 *	06/30/2015  Generated
 *  11/25/2016  Removed children property redefining node to simply
 *              be named data. Node structuring was moved to NodeATree,
 *              NodeGraph, NodeList, NodeMatrix and NodeTree.
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
#include        <name.h>
#include        <AStr.h>


#ifndef         NODE_H
#define         NODE_H 1



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct node_data_s          NODE_DATA;
    typedef struct nodeArc_data_s       NODEARC_DATA;
    typedef struct nodeArray_data_s     NODEARRAY_DATA;
    typedef struct nodeATree_data_s     NODEATREE_DATA;
    typedef struct nodeEntry_data_s     NODEENTRY_DATA;
    typedef struct nodeGraph_data_s     NODEGRAPH_DATA;
    typedef struct nodeHash_data_s      NODEHASH_DATA;
    typedef struct nodeList_data_s      NODELIST_DATA;
    typedef struct nodeMatrix_data_s	NODEMATRIX_DATA;
    typedef struct nodeScan_data_s      NODESCAN_DATA;
    typedef struct nodeTree_data_s      NODETREE_DATA;

    // Some predefined Node Classes
    typedef enum node_classes_e {
        NODE_CLASS_UNKNOWN=0,
        NODE_CLASS_ROOT,
        NODE_CLASS_INTEGER,
        NODE_CLASS_STRING,
        NODE_CLASS_OPEN,                // Open/Down Node for Tree Linerization
        NODE_CLASS_CLOSE,               // Close/Up Node for Tree Linerization
        NODE_CLASS_USER=1024            // First User defined class
    } NODE_CLASSES;

    typedef struct node_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        // Properties:
        int32_t         (*pGetClass)(NODE_DATA *this);
        bool            (*pSetClass)(NODE_DATA *this,int32_t value);
        OBJ_ID          (*pGetData)(NODE_DATA *this);
        bool            (*pSetData)(NODE_DATA *this,OBJ_ID pValue);
        uint16_t        (*pGetMisc)(NODE_DATA *this);
        bool            (*pSetMisc)(NODE_DATA *this,uint16_t value);
        NAME_DATA *     (*pGetName)(NODE_DATA *this);
        OBJ_ID          (*pGetOther)(NODE_DATA *this);
        bool            (*pSetOther)(NODE_DATA *this,OBJ_ID pValue);
        // Methods:
        ERESULT         (*pCompare)(NODE_DATA *this, NODE_DATA *pOther);
        NODE_DATA *     (*pProperty)(NODE_DATA *this, const char *pName);
        ERESULT         (*pPropertyAdd)(NODE_DATA *this, NODE_DATA *pData);
        uint16_t        (*pPropertyCount)(NODE_DATA	*this);
        NODEARRAY_DATA * (*pProperties)(NODE_DATA *this);
    } NODE_VTBL;
    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    NODE_DATA *     node_Alloc(
        void
    );
    
    
    const
    char *          node_FindClassDescription(
        int             class
    );
    
    
    NODE_DATA *     node_NewFromJSONString(
        ASTR_DATA       *pString
    );
    
    NODE_DATA *     node_NewFromJSONStringA(
        const
        char            *pString
    );
    
    
    NODE_DATA *     node_NewWithInt(
        int64_t         ident,
        OBJ_ID          pData
    );
    
    
    NODE_DATA *     node_NewWithUTF8(
        const
        char            *pName,
        OBJ_ID          pData
    );
    
    
    NODE_DATA *     node_NewWithUTF8AndClass(
        const
        char            *pName,
        int32_t         cls,
        OBJ_ID          pData
    );
    
    
    NODE_DATA *     node_NewWithUTF8Con(
        const
        char            *pName,
        OBJ_ID          pData
    );
    
    
    NODE_DATA *     node_NewWithUTF8ConAndClass(
        const
        char            *pName,
        int32_t         cls,
        OBJ_ID          pData
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    // Class is used to categorize the node with some kind of
    // identification if needed.
    int32_t         node_getClass(
        NODE_DATA       *this
    );
    
    bool            node_setClass(
        NODE_DATA       *this,
        int32_t         value
    );
    
    
    OBJ_ID          node_getData(
        NODE_DATA       *this
    );
    
    bool            node_setData(
        NODE_DATA       *this,
        OBJ_ID          pValue
    );
    

    OBJ_ID          node_getExtra(
        NODE_DATA       *this
    );
    
    bool            node_setExtra(
        NODE_DATA       *this,
        OBJ_ID          pValue
    );
    
    
    uint32_t        node_getHash(
        NODE_DATA       *this
    );
    
    
    uint32_t        node_getIndex(
        NODE_DATA       *this
    );
    
    bool            node_setIndex(
        NODE_DATA       *this,
        uint32_t        value
    );
    
    
    // Misc can be used as needed.
    uint16_t        node_getMisc(
        NODE_DATA       *this
    );
    
    bool            node_setMisc(
        NODE_DATA       *this,
        uint16_t        value
    );
    
    
    /*!
     @return    If successful, an Name object which must be released,
                otherwise OBJ_NIL.
     */
    NAME_DATA *     node_getName(
        NODE_DATA       *this
    );
    
    uint64_t        node_getNameInt(
        NODE_DATA       *this
    );
    
    /*!
     @return    If successful, a UTF-8 string which must be freed
                with mem_Free(), otherwise OBJ_NIL.
     */
    const
    char *          node_getNameUTF8(
        NODE_DATA       *this
    );

    
    OBJ_ID          node_getOther(
        NODE_DATA       *this
    );
    
    bool            node_setOther(
        NODE_DATA       *this,
        OBJ_ID          pValue
    );
    
    
    NODEARRAY_DATA * node_getProperties(
        NODE_DATA       *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Compare this node to the other node.
     @result
                 ERESULT_SUCCESS_EQUAL if this == other,
                 ERESULT_SUCCESS_LESS_THAN if this < other
                 or ERESULT_SUCCESS_GREATER_THAN if this > other.
     */
    ERESULT         node_Compare(
        NODE_DATA		*this,
        NODE_DATA       *pOther
    );
    
    
    /*!
     Create a new Node Array from the data for this node if that
     data is a Node Array or a Node Hash.
     @result    If successful, a new nodeArray that contains the
                contents of the Data property's node array or
                node hash. Otherwise, OBJ_NIL and the Last Error
                property contains an ERESULT_* error.
     @warning   Remember to release the returned object.
     */
    NODEARRAY_DATA * node_DataToArray(
        NODE_DATA       *this
    );
    
    
    NODE_DATA *     node_InitWithInt(
        NODE_DATA       *this,
        int64_t         ident,
        OBJ_ID          pData
    );
    
    
    NODE_DATA *     node_InitWithName(
        NODE_DATA       *this,
        NAME_DATA       *pName,         // Retained, not copied
        OBJ_ID          pData
    );
    
    
    NODE_DATA *     node_InitWithUTF8(
        NODE_DATA       *this,
        const
        char            *pName,
        OBJ_ID          pData
    );


    NODE_DATA *     node_InitWithUTF8Con(
        NODE_DATA       *this,
        const
        char            *pName,
        OBJ_ID          pData
    );
    
    
    NODEARRAY_DATA * node_DataToArray(
        NODE_DATA       *this
    );
    
    
    NODE_DATA *     node_Property(
        NODE_DATA       *this,
        const
        char            *pName
    );
    

    ERESULT         node_PropertyAdd(
        NODE_DATA		*this,
        NODE_DATA       *pData
    );
    
    
    uint16_t        node_PropertyCount(
        NODE_DATA		*this
    );
    
    
    NODEARRAY_DATA * node_Properties(
        NODE_DATA       *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = node_ToDebugString(this,4);
     @endcode
     @param     this    NODE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object when you are done
                with it.
     */
    ASTR_DATA *     node_ToDebugString(
        NODE_DATA       *this,
        int             indent
    );
    
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* NODE_H */

