// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          A Generic Node with Properties (Node) Header
//****************************************************************
/*
 * Program
 *			A Generic Node with Properties (Node)
 * Purpose
 *              This object provides a data structure for named
 *              data. So, a name is required while data is optional.
 *              It may have extra properties attached to it.
 *              The properties are lazily added. So, if you don't
 *              use them. You do not pay much for it in memory usage.
 *
 *              The required name can only be entered when the Node is
 *              created and should not be changed after that time.
 *
 *              If you need it, the 'other' property is available
 *              for use. For instance, you might use it to point to
 *              a symbol table entry when the Node represents a
 *              portion of a parsed program.
 *
 * Remarks
 *  1.          To keep the same terminology as Knuth, we use the
 *              left index as the child index in a multi-way tree
 *              and the right index becomes the sibling index.
 *  2.          The object's misc2 field is being used by the Name
 *              object.
 *
 * History
 *  06/30/2015  Generated
 *  11/25/2016  Removed children property redefining Node to simply
 *              be named data. Node structuring was moved to NodeATree,
 *              NodeGraph, NodeList, NodeMatrix and NodeTree.
 *  02/18/2018  Chaged Node's child and sibling indices to left and
 *              right indices respectively which mirrors Knuth's
 *              definition and is frankly more eloquent.
 *	01/12/2020 Regenerated
 *
 * References
 *  --      Donald Knuth, "The Art of Computer Programming - Fundamental
 *          Algorithms (Vol 1, 3rd Edition)", 1997, Addison Wesley
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
#include        <Name.h>
#include        <Visitor.h>


#ifndef         NODE_H
#define         NODE_H


#define   NODE_JSON_SUPPORT 1
//#define   NODE_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Node_data_s	NODE_DATA;            // Inherits from OBJ
    typedef struct Node_class_data_s NODE_CLASS_DATA;   // Inherits from OBJ

    // Directly Associated objects
    typedef struct NodeArray_data_s         NODEARRAY_DATA;
    typedef struct NodeArray_class_data_s   NODEARRAY_CLASS_DATA;
    typedef struct NodeBT_data_s            NODEBT_DATA;
    typedef struct NodeBT_class_data_s      NODEBT_CLASS_DATA;
    typedef struct NodeEnum_data_s          NODEENUM_DATA;
    typedef struct NodeEnum_class_data_s    NODEENUM_CLASS_DATA;
    typedef struct NodeHash_data_s          NODEHASH_DATA;
    typedef struct NodeHash_class_data_s    NODEHASH_CLASS_DATA;
    typedef struct NodeLink_data_s          NODELINK_DATA;
    typedef struct NodeLink_class_data_s    NODELINK_CLASS_DATA;
    typedef struct NodeList_data_s          NODELIST_DATA;
    typedef struct NodeList_class_data_s    NODELIST_CLASS_DATA;
    typedef struct NodeScan_data_s          NODESCAN_DATA;
    typedef struct NodeScan_class_data_s    NODESCAN_CLASS_DATA;
    typedef struct NodeTree_data_s          NODETREE_DATA;
    typedef struct NodeTree_class_data_s    NODETREE_CLASS_DATA;

    typedef struct Node_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Node_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODE_DATA *);
    } NODE_VTBL;

    typedef struct Node_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Node_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODE_DATA *);
    } NODE_CLASS_VTBL;


    // Some predefined Node Classes
    typedef enum Node_Classes_e {
        NODE_CLASS_UNKNOWN=0,
        NODE_CLASS_ROOT=1,
        NODE_CLASS_ANY,                 // Used for scanning and accepting any other class
        //                              // accept any class other than unknown
        NODE_CLASS_KLEENE,              // Used for scanning and accepting any other class
        //                              // accept 0 or more classes
        NODE_CLASS_INTEGER,
        NODE_CLASS_STRING,
        NODE_CLASS_OPEN,                // Open/Down Node for Tree Linerization
        NODE_CLASS_CLOSE,               // Close/Up Node for Tree Linerization
        NODE_CLASS_USER=32              // First User defined class
    } NODE_CLASSES;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODE_SINGLETON
    NODE_DATA *     Node_Shared (
        void
    );

    void            Node_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Node object if successful, otherwise OBJ_NIL.
     */
    NODE_DATA *     Node_Alloc (
        void
    );
    
    
    OBJ_ID          Node_Class (
        void
    );
    
    
    NODE_DATA *     Node_New (
        void
    );
    
    
    const
    char *          Node_FindClassDescription(
        int             class
    );


    int             Node_FindClassInteger(
        const
        char            *pDesc
    );


    NODE_DATA *     Node_NewFromJsonString(
        ASTR_DATA       *pString
    );

    NODE_DATA *     Node_NewFromJsonStringA(
        const
        char            *pString
    );


    NODE_DATA *     Node_NewWithAStr(
        ASTR_DATA       *pName,
        OBJ_ID          pData
    );



    NODE_DATA *     Node_NewWithInt(
        int64_t         ident,
        OBJ_ID          pData
    );


    NODE_DATA *     Node_NewWithUTF8AndClass(
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    );


    NODE_DATA *     Node_NewWithUTF8ConAndClass(
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    );




    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     Accept method is meant to be used with the visitor pattern. However,
     it can be used for other things as needed.
     */
    bool            Node_setAcceptMethod(
        NODE_DATA       *this,
        ERESULT         (*pAccept)(NODE_DATA *, OBJ_ID)
    );


    /*!
     Class property is used to categorize the Node with some kind of
     identification if needed.
     */
    int32_t         Node_getClass(
        NODE_DATA       *this
    );

    bool            Node_setClass(
        NODE_DATA       *this,
        int32_t         value
    );


    OBJ_ID          Node_getData(
        NODE_DATA       *this
    );

    bool            Node_setData(
        NODE_DATA       *this,
        OBJ_ID          pValue
    );


    OBJ_ID          Node_getExtra(
        NODE_DATA       *this
    );

    bool            Node_setExtra(
        NODE_DATA       *this,
        OBJ_ID          pValue
    );


    uint32_t        Node_getHash(
        NODE_DATA       *this
    );


    /*!
     Misc can optionally be used as needed. Be aware that
     NodeTree_VisitBreadthFirst uses this field if it is
     executed.
     */
    uint32_t        Node_getMisc (
        NODE_DATA       *this
    );

    bool            Node_setMisc (
        NODE_DATA       *this,
        uint32_t        value
    );


    /*!
     Misc1 and Misc2 may be used as needed.
     */
    uint16_t        Node_getMisc1(
        NODE_DATA       *this
    );

    bool            Node_setMisc1(
        NODE_DATA       *this,
        uint16_t        value
    );


    uint16_t        Node_getMisc2(
        NODE_DATA       *this
    );

    bool            Node_setMisc2(
        NODE_DATA       *this,
        uint16_t        value
    );


    NAME_DATA *     Node_getName (
        NODE_DATA       *this
    );


    /*!
     @return    If successful, an non-zero integer which is derived from
                the Node's Name object, otherwise 0.
     */
    uint64_t        Node_getNameInt(
        NODE_DATA       *this
    );

    /*!
     @return    If successful, an Name object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     Node_getNameStr(
        NODE_DATA       *this
    );

    /*!
     @return    If successful, a UTF-8 string which must be freed
                with mem_Free(), otherwise NULL.
     */
    char *          Node_getNameUTF8(
        NODE_DATA       *this
    );


    /*!
     Can be used to attach any other object to this Node.
     */
    OBJ_ID          Node_getOther(
        NODE_DATA       *this
    );

    bool            Node_setOther(
        NODE_DATA       *this,
        OBJ_ID          pValue
    );


    NODEBT_DATA *   Node_getProperties(
        NODE_DATA       *this
    );


    /*!
     @property  Type is user defined and optional.
     */
    int32_t         Node_getType(
        NODE_DATA       *this
    );

    bool            Node_setType(
        NODE_DATA       *this,
        int32_t         value
    );


    /*!
     @property  Unique is normally used as an auxiliary
     index for this object.  However, it can be user
     defined and optional if its container does not
     need it.
     */
    uint32_t        Node_getUnique(
        NODE_DATA       *this
    );

    bool            Node_setUnique(
        NODE_DATA       *this,
        uint32_t        value
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Accept a Visitor object's request by building the appropriate
     method name, query visitor to get the actual method and last
     call that method. The method name that is built is "Visit_Node_"
     and the type concatentated in hexadecimal (ie 8 hex chars).
     @result    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Node_Accept(
        NODE_DATA       *this,
        VISITOR_DATA    *pVisitor
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = Node_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another NODE object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Node_Assign (
        NODE_DATA       *this,
        NODE_DATA       *pOther
    );


    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Node_Compare (
        NODE_DATA       *this,
        NODE_DATA       *pOther
    );

    int             Node_CompareA(
        NODE_DATA       *this,
        int32_t         cls,
        const
        char            *pNameA
    );


     /*!
      Copy the current object creating a new object.
      Example:
      @code
         Node      *pCopy = Node_Copy(this);
      @endcode
      @param     this    object pointer
      @return    If successful, a NODE object which must be
                 released, otherwise OBJ_NIL.
      @warning   Remember to release the returned object.
      */
     NODE_DATA *     Node_Copy (
         NODE_DATA       *this
     );


    /*!
     Create a new Node Array from the data for this Node if that
     data is a Node Array or a Node Hash.
     @result    If successful, a new NodeArray that contains the
                contents of the Data property's Node array or
                Node hash. Otherwise, OBJ_NIL and the Last Error
                property contains an ERESULT_* error.
     @warning   Remember to release the returned object.
     */
    NODEARRAY_DATA * Node_DataToArray(
        NODE_DATA       *this
    );


    /*!
     Create a hash for the name value. The name value is always
     converted to a UTF-8 string and then that is hashed.
     @param     this    object pointer
     @return    Hash Code
     */
    uint32_t        Node_Hash (
        NODE_DATA       *this
    );


    NODE_DATA *     Node_Init (
        NODE_DATA       *this
    );


    /*!
     Create a new Node Array from the data for this Node if that
     data is a Node Array or a Node Hash.
     @result    If successful, a new NodeArray that contains the
                contents of the Data property's Node array or
                Node hash. Otherwise, OBJ_NIL and the Last Error
                property contains an ERESULT_* error.
     @warning   Remember to release the returned object.
     */
    NODEARRAY_DATA * Node_JsonDataToArray(
        NODE_DATA       *this
    );


    OBJ_ID          Node_PropertyA (
        NODE_DATA       *this,
        const
        char            *pName
    );


    ERESULT         Node_PropertyAddA (
        NODE_DATA        *this,
        const
        char            *pNameA,
        OBJ_ID          pData
    );


    uint32_t        Node_PropertyCount (
        NODE_DATA        *this
    );


    NODEARRAY_DATA * Node_Properties (
        NODE_DATA       *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Node_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Node_ToDebugString (
        NODE_DATA       *this,
        int             indent
    );
    
    
    /*!
     Attempt to convert the Node's name and data to a string if possible separated by ':'.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                data parameter in string form, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object when you are done
                with it.
     */
    ASTR_DATA *     Node_ToString(
        NODE_DATA       *this
    );


    /*!
     Convert the Data Object to a string if possible and return it.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                data parameter in string form, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object when you are done
                with it.
     */
    ASTR_DATA *     Node_ToString_Data(
        NODE_DATA       *this
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* NODE_H */

