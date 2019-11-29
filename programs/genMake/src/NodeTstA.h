// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODETSTA Console Transmit Task (NodeTstA) Header
//****************************************************************
/*
 * Program
 *			Separate NodeTstA (NodeTstA)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate NodeTstA to run things without complications
 *          of interfering with the main NodeTstA. A NodeTstA may be 
 *          called a NodeTstA on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/10/2019 Generated
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


#ifndef         NODETSTA_H
#define         NODETSTA_H


//#define   NODETSTA_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodeTstA_data_s	NODETSTA_DATA;            // Inherits from OBJ
    typedef struct NodeTstA_class_data_s NODETSTA_CLASS_DATA;   // Inherits from OBJ

    typedef struct NodeTstA_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeTstA_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODETSTA_DATA *);
    } NODETSTA_VTBL;

    typedef struct NodeTstA_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeTstA_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODETSTA_DATA *);
    } NODETSTA_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODETSTA_SINGLETON
    NODETSTA_DATA *     NodeTstA_Shared (
        void
    );

    bool            NodeTstA_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeTstA object if successful, otherwise OBJ_NIL.
     */
    NODETSTA_DATA * NodeTstA_Alloc (
        void
    );
    
    
    OBJ_ID          NodeTstA_Class (
        void
    );
    
    
    NODETSTA_DATA * NodeTstA_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: (Optional) Required Computer Architecture(s)
     */
    ASTRCARRAY_DATA * NodeTstA_getArches (
        NODETSTA_DATA   *this
    );

    bool             NodeTstA_setArches (
        NODETSTA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Source Dependencies, zero or more file paths that
        compilation depends on.
    */
    ASTRCARRAY_DATA * NodeTstA_getDeps (
        NODETSTA_DATA   *this
    );

    bool            NodeTstA_setDeps (
        NODETSTA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Test program file name including file extension
     */
    ASTRC_DATA *    NodeTstA_getName (
        NODETSTA_DATA   *this
    );

    bool            NodeTstA_setName (
        NODETSTA_DATA   *this,
        ASTRC_DATA      *pValue
    );


    NODE_DATA *     NodeTstA_getNode (
        NODETSTA_DATA   *this
    );


    NODEBASE_DATA * NodeTstA_getNodeBase (
        NODETSTA_DATA   *this
    );


    /*! Property: (Optional) Required Operating System(s)
     */
    ASTRCARRAY_DATA * NodeTstA_getOSs (
        NODETSTA_DATA   *this
    );

    bool            NodeTstA_setOSs (
        NODETSTA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Extra Sources, zero or more file paths that
        are needed to compile with Name property.
    */
    ASTRCARRAY_DATA * NodeTstA_getSrcs (
        NODETSTA_DATA   *this
    );

    bool            NodeTstA_setSrcs (
        NODETSTA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: file name suffix (optional)
        The optional file extension suffix to be used with name.
     */
    ASTRC_DATA *    NodeTstA_getSuffix (
        NODETSTA_DATA   *this
    );

    bool            NodeTstA_setSuffix (
        NODETSTA_DATA   *this,
        ASTRC_DATA      *pValue
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Check that the included constraints are met. If a constraint was
     not specified on the original definition, then it will not be
     checked. If one or more constraints of one tyoe were specified
     then we do check to see if the specified value matches any defined.
     @param     this    object pointer
     @param     pArch   Optional Architecture String Constraint
     @param     pOS     Optional Operating System String Constraint
     @return    if all constraints are met, ERESULT_SUCCESS.  Otherwise,
                an ERESULT_* error code.
     */
    ERESULT             NodeTstA_CheckContraints (
            NODETSTA_DATA   *this,
            const
            char            *pArch,
            const
            char            *pOS
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         NodeTstA_Compare (
        NODETSTA_DATA     *this,
        NODETSTA_DATA     *pOther
    );


    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NodeTstA_Disable (
        NODETSTA_DATA   *this
    );


    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NodeTstA_Enable (
        NODETSTA_DATA   *this
    );


    NODETSTA_DATA * NodeTstA_Init (
        NODETSTA_DATA   *this
    );


    ERESULT         NodeTstA_IsEnabled (
        NODETSTA_DATA   *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeTstA_ToDebugString(this,4);
     @endcode 
     @param     this    NODETSTA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    NodeTstA_ToDebugString (
        NODETSTA_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODETSTA_H */

