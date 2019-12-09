// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODERTN Console Transmit Task (NodeRtn) Header
//****************************************************************
/*
 * Program
 *			Separate NodeRtn (NodeRtn)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate NodeRtn to run things without complications
 *          of interfering with the main NodeRtn. A NodeRtn may be 
 *          called a NodeRtn on other O/S's.
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
#include        <NodeTest.h>


#ifndef         NODERTN_H
#define         NODERTN_H


//#define   NODERTN_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodeRtn_data_s	NODERTN_DATA;            // Inherits from OBJ
    typedef struct NodeRtn_class_data_s NODERTN_CLASS_DATA;   // Inherits from OBJ

    typedef struct NodeRtn_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeRtn_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODERTN_DATA *);
    } NODERTN_VTBL;

    typedef struct NodeRtn_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeRtn_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODERTN_DATA *);
    } NODERTN_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODERTN_SINGLETON
    NODERTN_DATA *  NodeRtn_Shared (
        void
    );

    bool            NodeRtn_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeRtn object if successful, otherwise OBJ_NIL.
     */
    NODERTN_DATA *  NodeRtn_Alloc (
        void
    );
    
    
    OBJ_ID          NodeRtn_Class (
        void
    );
    
    
    NODERTN_DATA *  NodeRtn_New (
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
    ERESULT_DATA *  NodeRtn_Parse(
        NODE_DATA       *pNode,
        NODERTN_DATA    **ppBase
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: (Optional) Required Computer Architecture(s)
     */
    ASTRCARRAY_DATA * NodeRtn_getArches (
        NODERTN_DATA    *this
    );

    bool             NodeRtn_setArches (
        NODERTN_DATA    *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Source Dependencies, zero or more file paths that
        compilation depends on.
    */
    ASTRCARRAY_DATA * NodeRtn_getDeps (
        NODERTN_DATA    *this
    );

    bool            NodeRtn_setDeps (
        NODERTN_DATA    *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Test program file name including file extension
     */
    ASTRC_DATA *    NodeRtn_getName (
        NODERTN_DATA    *this
    );

    bool            NodeRtn_setName (
        NODERTN_DATA    *this,
        ASTRC_DATA      *pValue
    );


    NODE_DATA *     NodeRtn_getNode (
        NODERTN_DATA    *this
    );


    NODEBASE_DATA * NodeRtn_getNodeBase (
        NODERTN_DATA    *this
    );


    /*! Property: (Optional) Required Operating System(s)
     */
    ASTRCARRAY_DATA * NodeRtn_getOSs (
        NODERTN_DATA    *this
    );

    bool            NodeRtn_setOSs (
        NODERTN_DATA    *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Extra Sources, zero or more file paths that
        are needed to compile with Name property.
    */
    ASTRCARRAY_DATA * NodeRtn_getSrcs (
        NODERTN_DATA    *this
    );

    bool            NodeRtn_setSrcs (
        NODERTN_DATA    *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Optional Test Node
    */
    NODETEST_DATA * NodeRtn_getTest (
        NODERTN_DATA    *this
    );

    bool            NodeRtn_setTest (
        NODERTN_DATA    *this,
        NODETEST_DATA   *pValue
    );




    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Append a string to the dependencies list.
     @param     this    object pointer
     @param     pStr    string pointer
     @return    If successful, OBJ_NIL is returne, otherwise a new
                ERESULT_DATA error object is returned.
     @warning   The ERESULT_DATA error object must be released.
     */
    ERESULT_DATA *  NodeRtn_AppendDeps (
        NODERTN_DATA    *this,
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
    ERESULT_DATA *  NodeRtn_AppendSrcs (
        NODERTN_DATA    *this,
        ASTR_DATA       *pStr
    );


    NODERTN_DATA *  NodeRtn_Init (
        NODERTN_DATA    *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeRtn_ToDebugString(this,4);
     @endcode 
     @param     this    NODERTN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    NodeRtn_ToDebugString (
        NODERTN_DATA    *this,
        int             indent
    );
    
    
    ASTR_DATA *    NodeRtn_ToString (
        NODERTN_DATA    *this
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* NODERTN_H */

