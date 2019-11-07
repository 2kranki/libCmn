// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODEOBJ Console Transmit Task (NodeObj) Header
//****************************************************************
/*
 * Program
 *			Separate NodeObj (NodeObj)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate NodeObj to run things without complications
 *          of interfering with the main NodeObj. A NodeObj may be 
 *          called a NodeObj on other O/S's.
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
    NODEOBJ_DATA *     NodeObj_Shared (
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
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: Source Dependencies, zero or more file paths that
        compilation depends on.
    */
    ASTRARRAY_DATA * NodeObj_getDeps (
        NODEOBJ_DATA    *this
    );

    bool            NodeObj_setDeps (
        NODEOBJ_DATA    *this,
        ASTRARRAY_DATA  *pValue
    );


    /*! Property: Test program file name including file extension
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


    /*! Property: (Optional) Required Computer Architecture
     */
    ASTR_DATA *     NodeObj_getReqArch (
        NODEOBJ_DATA    *this
    );

    bool            NodeObj_setReqArch (
        NODEOBJ_DATA    *this,
        ASTR_DATA       *pValue
    );


    /*! Property: (Optional) Required Operating System
     */
    ASTR_DATA *     NodeObj_getReqOS (
        NODEOBJ_DATA    *this
    );

    bool            NodeObj_setReqOS (
        NODEOBJ_DATA    *this,
        ASTR_DATA       *pValue
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

