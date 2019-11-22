// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODETEST Console Transmit Task (NodeTest) Header
//****************************************************************
/*
 * Program
 *			Separate NodeTest (NodeTest)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate NodeTest to run things without complications
 *          of interfering with the main NodeTest. A NodeTest may be 
 *          called a NodeTest on other O/S's.
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
#include        <NodeBase.h>


#ifndef         NODETEST_H
#define         NODETEST_H


//#define   NODETEST_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodeTest_data_s	NODETEST_DATA;            // Inherits from OBJ
    typedef struct NodeTest_class_data_s NODETEST_CLASS_DATA;   // Inherits from OBJ

    typedef struct NodeTest_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeTest_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODETEST_DATA *);
    } NODETEST_VTBL;

    typedef struct NodeTest_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeTest_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODETEST_DATA *);
    } NODETEST_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODETEST_SINGLETON
    NODETEST_DATA * NodeTest_Shared (
        void
    );

    bool            NodeTest_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeTest object if successful, otherwise OBJ_NIL.
     */
    NODETEST_DATA * NodeTest_Alloc (
        void
    );
    
    
    OBJ_ID          NodeTest_Class (
        void
    );
    
    
    NODETEST_DATA * NodeTest_New (
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
                | string            // Name of the Test program
                ;
     object_Hash:
            "name"  : string        // Name of the Test program
                    ;
            "deps"  : '[' deps ']'
                    ;
                ;
            "srcs"  : '[' source files ']'
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
     
     @param     pNode   JSON Input Node to be searched and parsed
     @param     ppBase  Test Node to be filled in with the data or released.
     @return    If successful, OBJ_NIL is returned and a new Test Node
                is returned in ppBase, otherwise a new ERESULT_DATA error
                object is returned.
     @warning   The ERESULT_DATA error object must be released.
     */
    ERESULT_DATA *  NodeTest_Parse(
        NODE_DATA       *pNode,
        NODETEST_DATA   **ppBase
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: (Optional) Required Computer Architecture(s)
     */
    ASTRCARRAY_DATA * NodeTest_getArches (
        NODETEST_DATA   *this
    );

    bool             NodeTest_setArches (
        NODETEST_DATA   *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Source Dependencies, zero or more file paths that
        compilation depends on.
    */
    ASTRCARRAY_DATA * NodeTest_getDeps (
        NODETEST_DATA   *this
    );

    bool            NodeTest_setDeps (
        NODETEST_DATA   *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Test program file name including file extension
     */
    ASTRC_DATA *    NodeTest_getName (
        NODETEST_DATA   *this
    );

    bool            NodeTest_setName (
        NODETEST_DATA   *this,
        ASTRC_DATA      *pValue
    );


    NODE_DATA *     NodeTest_getNode (
        NODETEST_DATA   *this
    );


    NODEBASE_DATA * NodeTest_getNodeBase (
        NODETEST_DATA   *this
    );


    /*! Property: (Optional) Required Operating System(s)
     */
    ASTRCARRAY_DATA * NodeTest_getOSs (
        NODETEST_DATA   *this
    );

    bool            NodeTest_setOSs (
        NODETEST_DATA   *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Extra Sources, zero or more file paths that
        are needed to compile with Name property.
    */
    ASTRCARRAY_DATA * NodeTest_getSrcs (
        NODETEST_DATA   *this
    );

    bool            NodeTest_setSrcs (
        NODETEST_DATA   *this,
        ASTRCARRAY_DATA *pValue
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
    ERESULT_DATA *  NodeTest_AppendDeps (
        NODETEST_DATA   *this,
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
    ERESULT_DATA *  NodeTest_AppendSrcs (
        NODETEST_DATA   *this,
        ASTR_DATA       *pStr
    );


    NODETEST_DATA * NodeTest_Init (
        NODETEST_DATA   *this
    );


    ERESULT_DATA *  NodeTest_SortArrays (
        NODETEST_DATA   *this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeTest_ToDebugString(this,4);
     @endcode 
     @param     this    NODETEST object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    NodeTest_ToDebugString (
        NODETEST_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODETEST_H */

