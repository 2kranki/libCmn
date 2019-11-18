// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Object Node (NodeObj) Header
//****************************************************************
/*
 * Program
 *			Object Node (NodeObj)
 * Purpose
 *			An Object Node contains the information to generate an
 *          object's various makefile parameters. An object consists
 *          two header files, object routines file, an object's
 *          class routines file, and a test program file. These
 *          correlate to the following file names:
 *
 *              <name>.h
 *              <name>_internal.h
 *              <name>.c
 *              <name>_object.c
 *              <name>_test.c           // Optional
 *              <name>_json.c           // Optional
 *
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
#include        <AStr.h>
#include        <NodeHdr.h>
#include        <NodeRtn.h>
#include        <NodeTest.h>


#ifndef         NODEOBJ_H
#define         NODEOBJ_H


//#define   NODEOBJ_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodeObj_data_s	NODEOBJ_DATA;
    // Inherits from NodeBase
    typedef struct NodeObj_class_data_s NODEOBJ_CLASS_DATA;   // Inherits from OBJ

    typedef struct NodeObj_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeObj_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEOBJ_DATA *);
    } NODEOBJ_VTBL;

    typedef struct NodeObj_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeObj_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEOBJ_DATA *);
    } NODEOBJ_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEOBJ_SINGLETON
    NODEOBJ_DATA *  NodeObj_Shared (
        void
    );

    bool            NodeObj_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeObj object if successful, otherwise OBJ_NIL.
     */
    NODEOBJ_DATA *  NodeObj_Alloc (
        void
    );
    
    
    OBJ_ID          NodeObj_Class (
        void
    );
    
    
    NODEOBJ_DATA *  NodeObj_New (
        void
    );
    
    
    /*!
     Parse an object and generate its components. An object consists
     of two routines, object and object_object, an optional JSON routine
     and an optional test program.
     Node Grammar:
     object     : string                // Object's Name
                | node ':' objectData   // Node's Name == Object's Name
                ;
     
     objectData : '{' object_Hash '}'
                | '[' deps ']'
                ;
     object_Hash:
            "deps"  : '[' deps ']'
                    ;
            // Generate JSON object compile or not
            "json"  : "true"
                    | "null"    // Same as "true"
                    | "false" (default)
                    ;
            // Generate Test compile and execution or not
            // (optionally with extra compilation source files)
            "test"  : "true" (default)
                    | "false"
                    | '[' source files ']'
                    | '{' test_Hash '}'
                    ;
                ;
     test_Hash  :
            "deps"  : '[' deps ']'
                    ;
            "srcs"  : '[' source files ']'
                    ;
                ;
     // Additional Dependency Files must be in the same directory
     // as the primary file that it is associated with.
     deps       : dependencies_file_name [',' deps]
                ;
     // Additional Source Files must be in the same directory
     // as the primary file that it is associated with.
     srcs       : source_file_name [',' srcs]
                ;

     @param     pNode   JSON Input Node to be searced and parsed. This node
                        should the one that has as its name that of the object.
     @param     ppBase  Object Node pointer which will be filled in.
     @return    If successful, OBJ_NIL is returne, otherwise a new
                ERESULT_DATA error object is returned.
     @warning   The ERESULT_DATA error object must be released.
     */
    ERESULT_DATA *  NodeObj_Parse(
        NODE_DATA       *pNode,
        NODEOBJ_DATA    **ppBase
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: (Optional) Required Computer Architecture(s)
     */
    ASTRARRAY_DATA * NodeObj_getArches (
        NODEOBJ_DATA    *this
    );

    bool             NodeObj_setArches (
        NODEOBJ_DATA    *this,
        ASTRARRAY_DATA  *pValue
    );


    /*! Property: Source Dependencies, zero or more file paths that
        compilation depends on.
    */
    ASTRARRAY_DATA * NodeObj_getDeps (
        NODEOBJ_DATA    *this
    );

    bool             NodeObj_setDeps (
        NODEOBJ_DATA    *this,
        ASTRARRAY_DATA  *pValue
    );


    /*! Property: Optional JSON file name
     */
    NODERTN_DATA *  NodeObj_getJson (
        NODEOBJ_DATA    *this
    );

    bool            NodeObj_setJson (
        NODEOBJ_DATA    *this,
        NODERTN_DATA    *pValue
    );


    /*! Property: object file name
     */
    ASTR_DATA *     NodeObj_getName (
        NODEOBJ_DATA    *this
    );

    bool            NodeObj_setName (
        NODEOBJ_DATA    *this,
        ASTR_DATA       *pValue
    );


    NODE_DATA *     NodeObj_getNode (
        NODEOBJ_DATA    *this
    );


    NODEBASE_DATA * NodeObj_getNodeBase (
        NODEOBJ_DATA    *this
    );


    /*! Property: (Optional) Required Operating System(s)
     */
    ASTRARRAY_DATA * NodeObj_getOSs (
        NODEOBJ_DATA    *this
    );

    bool            NodeObj_setOSs (
        NODEOBJ_DATA    *this,
        ASTRARRAY_DATA  *pValue
    );


    /*! Property: Extra Sources, zero or more file paths that
        are needed to compile with Name property.
    */
    ASTRARRAY_DATA * NodeObj_getSrcs (
        NODEOBJ_DATA    *this
    );

    bool            NodeObj_setSrcs (
        NODEOBJ_DATA    *this,
        ASTRARRAY_DATA  *pValue
    );


    /*! Property: Optional test program file name
     */
    NODETEST_DATA * NodeObj_getTest (
        NODEOBJ_DATA    *this
    );

    bool            NodeObj_setTest (
        NODEOBJ_DATA    *this,
        NODETEST_DATA   *pValue
    );




    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Append a string to the dependencies.
     @param     this    object pointer
     @param     pStr    string pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT_DATA *  NodeObj_AppendDeps (
        NODEOBJ_DATA    *this,
        ASTR_DATA       *pStr
    );


    ERESULT_DATA *  NodeObj_AppendSrcs (
        NODEOBJ_DATA    *this,
        ASTR_DATA       *pStr
    );

   
    NODEOBJ_DATA *  NodeObj_Init (
        NODEOBJ_DATA    *this
    );


    ERESULT_DATA *  NodeObj_SortArrays (
        NODEOBJ_DATA    *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeObj_ToDebugString(this,4);
     @endcode 
     @param     this    NODEOBJ object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    NodeObj_ToDebugString (
        NODEOBJ_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEOBJ_H */

