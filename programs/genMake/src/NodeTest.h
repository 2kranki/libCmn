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
    NODETEST_DATA *     NodeTest_Shared (
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
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: Source Dependencies, zero or more file paths that
        compilation depends on.
    */
    ASTRARRAY_DATA * NodeTest_getDeps (
        NODETEST_DATA   *this
    );

    bool            NodeTest_setDeps (
        NODETEST_DATA   *this,
        ASTRARRAY_DATA  *pValue
    );


    /*! Property: Test program file name including file extension
     */
    ASTR_DATA *     NodeTest_getName (
        NODETEST_DATA   *this
    );

    bool            NodeTest_setName (
        NODETEST_DATA   *this,
        ASTR_DATA       *pValue
    );


    NODE_DATA *     NodeTest_getNode (
        NODETEST_DATA   *this
    );


    NODEBASE_DATA * NodeTest_getNodeBase (
        NODETEST_DATA   *this
    );


    /*! Property: (Optional) Required Computer Architecture
     */
    ASTR_DATA *     NodeTest_getReqArch (
        NODETEST_DATA   *this
    );

    bool            NodeTest_setReqArch (
        NODETEST_DATA   *this,
        ASTR_DATA       *pValue
    );


    /*! Property: (Optional) Required Operating System
     */
    ASTR_DATA *     NodeTest_getReqOS (
        NODETEST_DATA   *this
    );

    bool            NodeTest_setReqOS (
        NODETEST_DATA   *this,
        ASTR_DATA       *pValue
    );


    /*! Property: Extra Sources, zero or more file paths that
        are needed to compile with Name property.
    */
    ASTRARRAY_DATA * NodeTest_getSrcs (
        NODETEST_DATA   *this
    );

    bool            NodeTest_setSrcs (
        NODETEST_DATA   *this,
        ASTRARRAY_DATA  *pValue
    );





//---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Append a string to the dependencies list.
     @param     this    object pointer
     @param     pStr    string pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NodeTest_AppendDeps (
        NODETEST_DATA   *this,
        ASTR_DATA       *pStr
    );


    /*!
     Append a string to the sources list.
     @param     this    object pointer
     @param     pStr    string pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NodeTest_AppendSrcs (
        NODETEST_DATA   *this,
        ASTR_DATA       *pStr
    );


    ERESULT         NodeTest_Disable (
        NODETEST_DATA	*this
    );


    ERESULT         NodeTest_Enable (
        NODETEST_DATA	*this
    );

   
    NODETEST_DATA * NodeTest_Init (
        NODETEST_DATA   *this
    );


    ERESULT     NodeTest_IsEnabled (
        NODETEST_DATA		*this
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

