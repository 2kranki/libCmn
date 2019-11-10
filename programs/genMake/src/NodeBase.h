// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODEBASE Console Transmit Task (NodeBase) Header
//****************************************************************
/*
 * Program
 *			Separate NodeBase (NodeBase)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate NodeBase to run things without complications
 *          of interfering with the main NodeBase. A NodeBase may be 
 *          called a NodeBase on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/03/2019 Generated
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





#include        <genMake.h>
#include        <node.h>
#include        <AStr.h>


#ifndef         NODEBASE_H
#define         NODEBASE_H


//#define   NODEBASE_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodeBase_data_s	NODEBASE_DATA;            // Inherits from OBJ
    typedef struct NodeBase_class_data_s NODEBASE_CLASS_DATA;   // Inherits from OBJ

    typedef struct NodeBase_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeBase_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEBASE_DATA *);
    } NODEBASE_VTBL;

    typedef struct NodeBase_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeBase_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEBASE_DATA *);
    } NODEBASE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEBASE_SINGLETON
    NODEBASE_DATA *     NodeBase_Shared (
        void
    );

    bool            NodeBase_SharedReset (
        void
    );
#endif


    /*!
     Given an node array of strings accumulate them into the given
     ASTR array.
     @param     pNodes      Node array object pointer
     @param     pArray      String array object pointer (Where strings are to be
                            accumulated)
     @return    If successful, a OBJ_NIL, otherwise an ERESULT Error object which
                must be released.
     @warning   Remember to release the Error object if present.
     */
    ERESULT_DATA *  NodeBase_AccumStrings(
        NODEARRAY_DATA  *pNodes,
        ASTRARRAY_DATA  *pArray
    );


    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeBase object if successful, otherwise OBJ_NIL.
     */
    NODEBASE_DATA *     NodeBase_Alloc (
        void
    );
    
    
    OBJ_ID              NodeBase_Class (
        void
    );
    
    
    NODEBASE_DATA *     NodeBase_New (
        void
    );


    /*!
     Dependencies and Extra Source files are common to several
     different type, so, we parse them here and accumulate
     them in the given node, ppBase. If an object_hash is found,
     it is optionally returned in ppHash so that other elements
     could be parsed off.
     
     Node Grammar:
     objectData : '{' object_Hash '}'
                | '[' deps ']'      // Accumulate the source dependencies.
                | "null"            // Ignored
                | "false"           // ppBase is released and success is returned.
                | "true"            // Ignored
                ;
     object_Hash:
            "deps"  : '[' deps ']'
                    ;
            // Generate JSON object compile or not
            "json"      : "true"
                        | "null"    // Same as "true"
                        | "false" (default)
                        ;
            // Optional Name
            "name"      :   string
                        ;
            // Required Architecture (ie X86, MIPS, ARM, etc)
            "reqArch"   :   string
                        ;
            // Required Operating System (ie linux, macos, win64, etc)
            "reqOS"     :   string
                        ;
     // Additional Dependency Files must be in the same directory
     // as the primary file that it is associated with.
     deps       : dependencies_file_name [',' deps]
                ;
     // Additional Source Files must be in the same directory
     // as the primary file that it is associated with.
     srcs       : source_file_name [',' srcs]
                ;
     @param     pNode   JSON Input Node, "hash", to be searched and parsed
     @param     ppBase  Base Node to be filled in with the data or released.
     @param     ppHash  Hash Node if found
     @return    If successful, OBJ_NIL is returne, otherwise a new
                ERESULT_DATA error object is returned.
     @warning   The ERESULT_DATA error object must be released.
     */
    ERESULT_DATA *  NodeBase_Parse(
        NODE_DATA       *pNode,
        NODEBASE_DATA   **ppBase,
        NODEHASH_DATA   **ppHash
    );


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: (Optional) Required Computer Architecture(s)
     */
    ASTRARRAY_DATA *    NodeBase_getArches (
            NODEBASE_DATA       *this
    );

    bool                NodeBase_setArches (
            NODEBASE_DATA       *this,
            ASTRARRAY_DATA      *pValue
    );


    /*! Property: Source Dependencies, zero or more file paths that
        compilation depends on.
    */
    ASTRARRAY_DATA *    NodeBase_getDeps (
            NODEBASE_DATA       *this
    );

    bool                NodeBase_setDeps (
            NODEBASE_DATA       *this,
            ASTRARRAY_DATA      *pValue
    );


    /*! Property: Test program file name
     */
    ASTR_DATA *         NodeBase_getName (
            NODEBASE_DATA       *this
    );

    bool                NodeBase_setName (
            NODEBASE_DATA       *this,
            ASTR_DATA           *pValue
    );


    NODE_DATA *         NodeBase_getNode (
            NODEBASE_DATA       *this
    );


    /*! Property: (Optional) Required Operating System(s)
     */
    ASTRARRAY_DATA *    NodeBase_getOSs (
            NODEBASE_DATA       *this
    );

    bool                NodeBase_setOSs (
            NODEBASE_DATA       *this,
            ASTRARRAY_DATA      *pValue
    );


    /*! Property: Extra Sources, zero or more file paths that
        are needed to compile with Name property.
    */
    ASTRARRAY_DATA *    NodeBase_getSrcs (
            NODEBASE_DATA       *this
    );

    bool                NodeBase_setSrcs (
            NODEBASE_DATA       *this,
            ASTRARRAY_DATA      *pValue
    );


    /*! Property: file name suffix
     */
    ASTR_DATA *         NodeBase_getSuffix (
            NODEBASE_DATA       *this
    );

    bool                NodeBase_setSuffix (
            NODEBASE_DATA       *this,
            ASTR_DATA           *pValue
    );




    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Append a string to the architeture list.
     @param     this    object pointer
     @param     pStr    string pointer
     @return    If successful, OBJ_NIL is returne, otherwise a new
                ERESULT_DATA error object is returned.
     @warning   The ERESULT_DATA error object must be released.
     */
    ERESULT_DATA *  NodeBase_AppendArches (
        NODEBASE_DATA   *this,
        ASTR_DATA       *pStr
    );


    /*!
     Append a string to the dependencies list.
     @param     this    object pointer
     @param     pStr    string pointer
     @return    If successful, OBJ_NIL is returne, otherwise a new
                ERESULT_DATA error object is returned.
     @warning   The ERESULT_DATA error object must be released.
     */
    ERESULT_DATA *  NodeBase_AppendDeps (
        NODEBASE_DATA   *this,
        ASTR_DATA       *pStr
    );


    /*!
     Append a string to the OS list.
     @param     this    object pointer
     @param     pStr    string pointer
     @return    If successful, OBJ_NIL is returne, otherwise a new
                ERESULT_DATA error object is returned.
     @warning   The ERESULT_DATA error object must be released.
     */
    ERESULT_DATA *  NodeBase_AppendOSs (
        NODEBASE_DATA   *this,
        ASTR_DATA       *pStr
    );


    /*!
     Append a string to the sources list.
     @param     this    object pointer
     @param     pStr    string pointer
     @return    If successful, OBJ_NIL is returne, otherwise a new
                ERESULT_DATA error object is returned.
     @warning   The ERESULT_DATA error object must be released.
     */
    ERESULT_DATA *  NodeBase_AppendSrcs (
        NODEBASE_DATA   *this,
        ASTR_DATA       *pStr
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = NodeBase_Assign(this,pOther);
     @endcode
     @param     this    NODEBASE object pointer
     @param     pOther  a pointer to another NODEBASE object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         NodeBase_Assign (
        NODEBASE_DATA   *this,
        NODEBASE_DATA   *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        NodeBase      *pCopy = NodeBase_Copy(this);
     @endcode
     @param     this    NODEBASE object pointer
     @return    If successful, a NODEBASE object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODEBASE_DATA * NodeBase_Copy (
        NODEBASE_DATA   *this
    );


    NODEBASE_DATA * NodeBase_Init (
        NODEBASE_DATA   *this
    );


    ERESULT_DATA *  NodeBase_SortArrays (
        NODEBASE_DATA   *this
    );


    ASTR_DATA *     NodeBase_ToString (
        NODEBASE_DATA   *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeBase_ToDebugString(this,4);
     @endcode 
     @param     this    NODEBASE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    NodeBase_ToDebugString (
        NODEBASE_DATA   *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEBASE_H */

