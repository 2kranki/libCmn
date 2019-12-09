// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODELIB Console Transmit Task (NodeLib) Header
//****************************************************************
/*
 * Program
 *			Separate NodeLib (NodeLib)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate NodeLib to run things without complications
 *          of interfering with the main NodeLib. A NodeLib may be 
 *          called a NodeLib on other O/S's.
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
#include        <Dict.h>
#include        <NodeBase.h>


#ifndef         NODELIB_H
#define         NODELIB_H


//#define   NODELIB_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodeLib_data_s	NODELIB_DATA;            // Inherits from OBJ
    typedef struct NodeLib_class_data_s NODELIB_CLASS_DATA;   // Inherits from OBJ

    typedef struct NodeLib_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeLib_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODELIB_DATA *);
    } NODELIB_VTBL;

    typedef struct NodeLib_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeLib_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODELIB_DATA *);
    } NODELIB_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODELIB_SINGLETON
    NODELIB_DATA *  NodeLib_Shared (
        void
    );

    bool            NodeLib_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeLib object if successful, otherwise OBJ_NIL.
     */
    NODELIB_DATA *  NodeLib_Alloc (
        void
    );
    
    
    OBJ_ID          NodeLib_Class (
        void
    );
    
    
    NODELIB_DATA *  NodeLib_New (
        void
    );
    
    
    /*!
     Parse the header portion of definition file and set up its components.
     Node Grammar:
        header  : "library" ':' '{' components '}'
                ;
        components
                : "name" ':' string
                | "deps" ':' deps       // Library Dependencies
                | "libdir" ':' string   // Path to where object library will be created
                | "objdir" ':' string   // Path to where temporary object files will be
                                        // created
                ;
     deps       : "null"
                | '[' string* ']'       // Library dependencies as needed for gcc/clang
                ;
     Note: See ParseObject() for definition of objectNode.
     
     @param     pNode   Node Pointer w/data being hash node
     @param     ppBase  Returned Object Pointer area
     @return    If successful, a NodePgm object in ppBase which must be released con-
                taining the description and OBJ_NIL, otherwise an ERESULT_DATA object
                which must be also be released.
     @warning   Remember to release the returned NodePgm or ERESULT_DATA object.
     */
    ERESULT_DATA *  NodeLib_Parse (
        NODE_DATA       *pNode,
        NODELIB_DATA    **ppBase
    );




    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: (Optional) Required Computer Architecture(s)
     */
    ASTRCARRAY_DATA * NodeLib_getArches (
        NODELIB_DATA    *this
    );

    bool             NodeLib_setArches (
        NODELIB_DATA    *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Lib Dependencies, zero or more library names without
        the "lib" prefix that compilation depends on.
    */
    ASTRCARRAY_DATA * NodeLib_getDeps (
        NODELIB_DATA    *this
    );

    bool            NodeLib_setDeps (
        NODELIB_DATA    *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Headers
    */
    ASTRCARRAY_DATA * NodeLib_getHdrs (
        NODELIB_DATA    *this
    );

    bool            NodeLib_setHdrs (
        NODELIB_DATA    *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Test program file name including file extension
     */
    ASTRC_DATA *    NodeLib_getName (
        NODELIB_DATA    *this
    );

    bool            NodeLib_setName (
        NODELIB_DATA    *this,
        ASTRC_DATA      *pValue
    );


    NODE_DATA *     NodeLib_getNode (
        NODELIB_DATA    *this
    );


    NODEBASE_DATA * NodeLib_getNodeBase (
        NODELIB_DATA    *this
    );


    /*! Property: (Optional) Required Operating System(s)
     */
    ASTRCARRAY_DATA * NodeLib_getOSs (
        NODELIB_DATA    *this
    );

    bool            NodeLib_setOSs (
        NODELIB_DATA    *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Extra Sources, zero or more file paths that
        are needed to compile with Name property.
    */
    ASTRCARRAY_DATA * NodeLib_getSrcs (
        NODELIB_DATA    *this
    );

    bool            NodeLib_setSrcs (
        NODELIB_DATA    *this,
        ASTRCARRAY_DATA *pValue
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Generate the Makefile beginning in macOS.
     @param     this    object pointer
     @param     pDict   dictionary pointer
     @return    If successful, an AStr which must be released.
                Otherwise, OBJ_NIL.
     */
    ASTR_DATA *     NodeLib_GenMacBegin (
        NODELIB_DATA    *this,
        DICT_DATA       *pDict
    );


    ASTR_DATA *     NodeLib_GenMacEnd (
        NODELIB_DATA    *this,
        DICT_DATA       *pDict
    );


    NODELIB_DATA *   NodeLib_Init (
        NODELIB_DATA    *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeLib_ToDebugString(this,4);
     @endcode 
     @param     this    NODELIB object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeLib_ToDebugString (
        NODELIB_DATA    *this,
        int             indent
    );
    
    
    ASTR_DATA *    NodeLib_ToString (
        NODELIB_DATA    *this
    );

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODELIB_H */

