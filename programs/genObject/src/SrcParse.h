// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          JSON Input Source Parser (SrcParse) Header
//****************************************************************
/*
 * Program
 *			JSON Input Source Parser (SrcParse)
 * Purpose
 *			This object parses the JSON input building a node tree.
 *			It also provides the routines to parse the node tree
 *			creating specific node type like NodeObj for the various
 *			node definitions.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	08/19/2019 Generated
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





#include        <genObject_defs.h>
#include        <AStr.h>
#include        <NodeClass.h>
#include        <NodeArray.h>


#ifndef         SRCPARSE_H
#define         SRCPARSE_H


//#define   SRCPARSE_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SrcParse_data_s	SRCPARSE_DATA;            // Inherits from OBJ
    typedef struct SrcParse_class_data_s SRCPARSE_CLASS_DATA;   // Inherits from OBJ

    typedef struct SrcParse_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcParse_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCPARSE_DATA *);
    } SRCPARSE_VTBL;

    typedef struct SrcParse_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcParse_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCPARSE_DATA *);
    } SRCPARSE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SRCPARSE_SINGLETON
    SRCPARSE_DATA * SrcParse_Shared (
        void
    );

    bool            SrcParse_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to srcParse object if successful, otherwise OBJ_NIL.
     */
    SRCPARSE_DATA * SrcParse_Alloc (
        void
    );
    
    
    OBJ_ID          SrcParse_Class (
        void
    );
    
    
    SRCPARSE_DATA * SrcParse_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef XYZZY
    /*! Property: Lib
     Lib contains the Library data
     */
    NODELIB_DATA *  SrcParse_getLib (
        SRCPARSE_DATA   *this
    );

    bool            SrcParse_setLib (
        SRCPARSE_DATA   *this,
        NODELIB_DATA    *pValue
    );
#endif


    /*! Property: Nodes
     Nodes contains the raw nodes parsed from a JSON input.
     */
    NODE_DATA *     SrcParse_getNodes (
        SRCPARSE_DATA   *this
    );

    bool            SrcParse_setNodes (
        SRCPARSE_DATA   *this,
        NODE_DATA       *pValue
    );


    /*! Property: Objects
     Objects contains the accumulated NodeObj's which were parsed by
     ParseObject() or ParseObjects().
     */
    NODEARRAY_DATA * SrcParse_getObjs (
        SRCPARSE_DATA   *this
    );

    bool            SrcParse_setObjs (
        SRCPARSE_DATA   *this,
        NODEARRAY_DATA  *pValue
    );


#ifdef XYZZY
    /*! Property: Pgm
     Pgm contains the Program data
     */
    NODEPGM_DATA *  SrcParse_getPgm (
        SRCPARSE_DATA   *this
    );

    bool            SrcParse_setPgm (
        SRCPARSE_DATA   *this,
        NODEPGM_DATA    *pValue
    );
#endif


#ifdef XYZZY
    /*! Property: Routines
     Routines contains the accumulated NodeRtn's which were parsed by
     ParseRoutine() or ParseRoutines().
     */
    NODEARRAY_DATA * SrcParse_getRtns (
        SRCPARSE_DATA   *this
    );

    bool            SrcParse_setRtns (
        SRCPARSE_DATA   *this,
        NODEARRAY_DATA  *pValue
    );
#endif


#ifdef XYZZY
    /*! Property: Tests
     Tests contains the accumulated NodeTest's which were parsed by
     ParseTest() or ParseTests().
     */
    NODEARRAY_DATA * SrcParse_getTests (
        SRCPARSE_DATA   *this
    );

    bool            SrcParse_setTests (
        SRCPARSE_DATA   *this,
        NODEARRAY_DATA  *pValue
    );
#endif



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    SRCPARSE_DATA * SrcParse_Init (
        SRCPARSE_DATA   *this
    );


    /*!
     Parse the given file path into a JSON Node structure,
     store it for further processing and perform some cursory
     checks on the structure.
     @param     this    object pointer
     @param     pPath   Path object pointer (required)
     @return    If successful, OBJ_NIL.  Otherwise, an ERESULT_DATA *
                error message.
     */
    ERESULT_DATA *  SrcParse_ParseJsonFile (
        SRCPARSE_DATA   *this,
        PATH_DATA       *pPath
    );
    
    /*!
     Parse the given string into a JSON Node structure, store
     it for further processing and perform some cursory checks
     on the structure.
     @param     this    object pointer
     @param     pStrA   String pointer (required)
     @return    If successful, OBJ_NIL.  Otherwise, an ERESULT_DATA *
                error message.
     */
    ERESULT_DATA *  SrcParse_ParseJsonStr (
        SRCPARSE_DATA   *this,
        const
        char            *pStrA
    );
    
#ifdef XYZZY
    /*!
     Parse the header portion of definition file and set up its components.
     Node Grammar:
        header  : "library" ':' '{' components '}'
                ;
        components
                : "name" ':' string
                | "deps" ':' deps
                | "libdir" ':' string   // Path to where object library will be created
                | "objdir" ':' string   // Path to where temporary object files will be
                                        // created
                ;
     deps       : "null"
                | '[' string* ']'       // Library dependencies as needed for gcc/clang
                ;
     @param     this    Object Pointer
     @param     pNode   Node that has Hash as data
     @return    If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ERESULT_DATA *  SrcParse_ParseLibrary (
        SRCPARSE_DATA   *this,
        NODE_DATA       *pNode
    );
#endif
    
    
    ERESULT_DATA *  SrcParse_ParseNodes (
        SRCPARSE_DATA   *this
    );


    /*!
     Parse an object and generate its components. An object consists
     of two routines, object and object_object, an optional JSON routine
     and an optional test program.
     Node Grammar:
     object     : '{' object_Hash '}'
                ;
     
     object_Hash:
            "name"  : string            // Object Name - Required
                    ;
            // The following are optional:
            "arch"  : '[' arches ']'    // Optional
                    ;
            "os"    : '[' oss ']'       // Optional
                    ;
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
                    | '[' source_dependencies ']'
                    | '{' test_Hash '}'
                    ;
                ;
     test_Hash  :
            "name"  : string            // Object Name - Optional
                    ;
            "deps"  : '[' deps ']'
                    ;
            "srcs"  : '[' source files ']'
                    ;
            "arch"  : '[' arches ']'    // Optional
                    ;
            "os"    : '[' oss ']'       // Optional
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
     arches     :   "X86"
                |   "X86_64"
                |   "MIPS"
                |   "ARM"
                ;
     oss        :   "linux"
                |   "macos"
                |   "win32"
                |   "win64"
                ;

     @param     this    Object Pointer
     @param     pNode   Object Node Pointer
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ERESULT_DATA *  SrcParse_ParseObject (
        SRCPARSE_DATA   *this,
        NODE_DATA       *pNode
    );
    
    
    /*!
     Parse objects and generate its components. Objects are found in
     an array. The objects are translated to NodeObj's and accumulated
     in an objArray found in the property Objs.
     Node Grammar:
     objects     : '{' objects_Hash '}'
                 ;
     object_Hash :
                    objectNode (',' object_Hash)
                 ;
     Note: See ParseObject() for definition of objectNode.
     @param     this    Object Pointer
     @param     pNode   Node Pointer for Array
     @return    If successful, OBJ_NIL. Otherwsie, an NODEARRAY_DATA object which must be released containing
                an array of routine/test nodes, otherwise OBJ_NIL.
     @warning   Remember to release the returned Array object.
     */
#ifdef XYZZY
    ERESULT_DATA *  SrcParse_ParseObjects (
        SRCPARSE_DATA   *this,
        NODE_DATA       *pNode
    );
#endif
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SrcParse_ToDebugString(this,4);
     @endcode 
     @param     this    SRCPARSE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcParse_ToDebugString (
        SRCPARSE_DATA   *this,
        int             indent
    );
    
    
    ASTR_DATA *     SrcParse_ToString (
        SRCPARSE_DATA   *this
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* SRCPARSE_H */

