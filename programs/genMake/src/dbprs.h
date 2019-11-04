// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          JSON Database Parser (dbprs) Header
//****************************************************************
/*
 * Program
 *			JSON Database Parser (dbprs)
 * Purpose
 *			This object parses the JSON Database and its component
 *          sections.  It then calls the appropriate generation
 *          routines to generate the output.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	09/04/2018 Generated
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
#include        <genBase.h>
#include        <jsonIn.h>
#include        <node.h>


#ifndef         DBPRS_H
#define         DBPRS_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct dbprs_data_s	DBPRS_DATA;    // Inherits from OBJ.

    typedef struct dbprs_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in dbprs_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DBPRS_DATA *);
    } DBPRS_VTBL;



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
     @return    pointer to dbprs object if successful, otherwise OBJ_NIL.
     */
    DBPRS_DATA *    dbprs_Alloc(
        void
    );
    
    
    OBJ_ID          dbprs_Class(
        void
    );
    
    
    DBPRS_DATA *    dbprs_New(
        void
    );
    

    DBPRS_DATA *    dbprs_NewWithDictAndGen(
        NODEHASH_DATA   *pDict,
        GENBASE_DATA    *pGen
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NODEHASH_DATA * dbprs_getDict(
        DBPRS_DATA      *this
    );
    
    bool            dbprs_setDict(
        DBPRS_DATA      *this,
        NODEHASH_DATA   *pValue
    );

    
    GENBASE_DATA *  dbprs_getGen(
        DBPRS_DATA     *this
    );
    
    bool            dbprs_setGen(
        DBPRS_DATA      *this,
        GENBASE_DATA    *pValue
    );

    
    JSONIN_DATA *   dbprs_getJson(
        DBPRS_DATA     *this
    );
    
    bool            dbprs_setJson(
        DBPRS_DATA      *this,
        JSONIN_DATA     *pValue
    );

    
    NODE_DATA *     dbprs_getNodes(
        DBPRS_DATA     *this
    );
    
    bool            dbprs_setNodes(
        DBPRS_DATA      *this,
        NODE_DATA       *pValue
    );
    

    ASTR_DATA *     dbprs_getStr(
        DBPRS_DATA     *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         dbprs_Finalize(
        DBPRS_DATA      *this
    );
    
    
    DBPRS_DATA *    dbprs_Init(
        DBPRS_DATA     *this
    );


    /*!
     Parse the given file into a JSON Node structure and
     perform some cursory checks on the structure.
     @param     this    object pointer
     @param     pPath   File Path of UTF-8 file to be parsed
     @param     ppNodes Converted Nodes object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         dbprs_InputFileToJSON(
        DBPRS_DATA      *this,
        PATH_DATA       *pPath,
        NODE_DATA       **ppNodes
    );
    
    /*!
     Parse the given string into a JSON Node structure and
     perform some cursory checks on the structure.
     @param     this    object pointer
     @param     pStr    UTF-8 String to be parsed
     @param     ppNodes Converted Nodes object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         dbprs_InputStrToJSON(
        DBPRS_DATA      *this,
        const
        char            *pStr,
        NODE_DATA       **ppNodes
    );
    
    
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
     Note: See ParseObject() for definition of objectNode.
     @param     this    Object Pointer
     @param     pHash   Node Hash Pointer whose data is an array or a hash
     @return    If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ERESULT         dbprs_ParseLibrary(
        DBPRS_DATA      *this,
        NODEHASH_DATA   *pHash
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
                | "null"
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

     @param     this    Object Pointer
     @param     pNode   Object Node Pointer
     @param     ppNodes Output Object Node Array Pointer of RTN and TST Nodes
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ERESULT         dbprs_ParseObject(
        DBPRS_DATA      *this,
        NODE_DATA       *pNode,
        NODEARRAY_DATA  **ppNodes
    );
    
    
    /*!
     Parse objects and generate its components
     Node Grammar:
     objects     : '{' objects_Hash '}'
                 ;
     object_Hash :
                    objectNode (',' object_Hash)
                 ;
     Note: See ParseObject() for definition of objectNode.
     @param     this    Object Pointer
     @param     pHash   Node Hash Pointer
     @param     ppArray Pointer to return area for an array of routine/test nodes
     @return    If successful, an NODEARRAY_DATA object which must be released containing
                an array of routine/test nodes, otherwise OBJ_NIL.
     @warning   Remember to release the returned Array object.
     */
    ERESULT         dbprs_ParseObjects(
        DBPRS_DATA      *this,
        NODEHASH_DATA   *pHash,
        NODEARRAY_DATA  **ppArray
    );
    
    
    /*!
     Parse the header portion of definition file and set up its components.
     Node Grammar:
     header  : "program" ':' '{' components '}'
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
     Note: See ParseObject() for definition of objectNode.
     @param     this    Object Pointer
     @param     pHash   Node Hash Pointer
     @return    If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ERESULT         dbprs_ParseProgram(
        DBPRS_DATA      *this,
        NODEHASH_DATA   *pHash
    );
    
    
    /*!
     Parse a routine and generate its components
     Node Grammar:
     object     : string                // Object's Name
                | node ':' objectData   // Node's Name == Object's Name
                ;
     
     objectData : '{' object_Hash '}'
                | '[' deps ']'
                | "null"
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
            "srcs"  : '[' deps ']'
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
     
     @param     this    Object Pointer
     @param     pNode   Object Node Pointer
     @return    If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ERESULT         dbprs_ParseRoutine(
        DBPRS_DATA      *this,
        NODE_DATA       *pNode,
        NODEARRAY_DATA  **ppNodes
    );
    
    
    /*!
     Parse an object and generate its components
     Node Grammar:
     objects     : '{' objects_Hash '}'
                 | '[' objects_Array ']'
                 ;
     object_Hash : objectNode (',' object_Hash)
                 ;
     object_Array: stringNode (',' object_Array)
                 ;
     Note: See ParseObject() for definition of objectNode.
     @param     this    Object Pointer
     @param     pArray  Node Array Pointer
     @return    If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ERESULT         dbprs_ParseRoutines(
        DBPRS_DATA      *this,
        NODEARRAY_DATA  *pArray
    );
    
    
    /*!
     Parse an object and generate its components
     Node Grammar:
     testNode   : string
                | hash
                ;
     hash       : '{' elements '}'
                ;
     elements   : "name" ':' string         // Required
                | "srcDeps" : array_of_file_names
                | "srcs"  : '[' file_names ']'
                ;
     @param     this    Object Pointer
     @param     pNode   Object Node Pointer
     @return    If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ERESULT         dbprs_ParseTest(
        DBPRS_DATA      *this,
        NODE_DATA       *pNode,
        ASTR_DATA       *pName          // Base Name for Test
    );
    
    
    /*!
     Parse an object and generate its components
     Node Grammar:
     tests      : '[' objects_Array ']'
                ;
     object_Array: testNode*
                ;
     Note: See ParseTest() for definition of testNode.
     @param     this    Object Pointer
     @param     pArray  Node Array Pointer
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ERESULT         dbprs_ParseTests(
        DBPRS_DATA      *this,
        NODEARRAY_DATA  *pArray
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = dbprs_ToDebugString(this,4);
     @endcode 
     @param     this    Object Pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    dbprs_ToDebugString(
        DBPRS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DBPRS_H */

