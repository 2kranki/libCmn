// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODERTNA Console Transmit Task (NodeRtnA) Header
//****************************************************************
/*
 * Program
 *			Separate NodeRtnA (NodeRtnA)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate NodeRtnA to run things without complications
 *          of interfering with the main NodeRtnA. A NodeRtnA may be 
 *          called a NodeRtnA on other O/S's.
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
#include        <NodeBase.h>
#include        <AStr.h>


#ifndef         NODERTNA_H
#define         NODERTNA_H


//#define   NODERTNA_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodeRtnA_data_s	NODERTNA_DATA;            // Inherits from OBJ
    typedef struct NodeRtnA_class_data_s NODERTNA_CLASS_DATA;   // Inherits from OBJ

    typedef struct NodeRtnA_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeRtnA_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODERTNA_DATA *);
    } NODERTNA_VTBL;

    typedef struct NodeRtnA_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeRtnA_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODERTNA_DATA *);
    } NODERTNA_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODERTNA_SINGLETON
    NODERTNA_DATA * NodeRtnA_Shared (
        void
    );

    bool            NodeRtnA_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeRtnA object if successful, otherwise OBJ_NIL.
     */
    NODERTNA_DATA * NodeRtnA_Alloc (
        void
    );
    
    
    OBJ_ID          NodeRtnA_Class (
        void
    );
    
    
    NODERTNA_DATA * NodeRtnA_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: (Optional) Required Computer Architecture(s)
     */
    ASTRCARRAY_DATA * NodeRtnA_getArches (
        NODERTNA_DATA   *this
    );

    bool             NodeRtnA_setArches (
        NODERTNA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Source Dependencies, zero or more file paths that
        compilation depends on.
    */
    ASTRCARRAY_DATA * NodeRtnA_getDeps (
        NODERTNA_DATA   *this
    );

    bool            NodeRtnA_setDeps (
        NODERTNA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Test program file name including file extension
     */
    ASTRC_DATA *    NodeRtnA_getName (
        NODERTNA_DATA   *this
    );

    bool            NodeRtnA_setName (
        NODERTNA_DATA   *this,
        ASTRC_DATA      *pValue
    );


    NODE_DATA *     NodeRtnA_getNode (
        NODERTNA_DATA   *this
    );


    NODEBASE_DATA * NodeRtnA_getNodeBase (
        NODERTNA_DATA   *this
    );


    /*! Property: (Optional) Required Operating System(s)
     */
    ASTRCARRAY_DATA * NodeRtnA_getOSs (
        NODERTNA_DATA   *this
    );

    bool            NodeRtnA_setOSs (
        NODERTNA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    );


    /*! Property: Extra Sources, zero or more file paths that
        are needed to compile with Name property.
    */
    ASTRCARRAY_DATA * NodeRtnA_getSrcs (
        NODERTNA_DATA   *this
    );

    bool            NodeRtnA_setSrcs (
        NODERTNA_DATA   *this,
        ASTRCARRAY_DATA *pValue
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    NODERTNA_DATA *   NodeRtnA_Init (
        NODERTNA_DATA     *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeRtnA_ToDebugString(this,4);
     @endcode 
     @param     this    NODERTNA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    NodeRtnA_ToDebugString (
        NODERTNA_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODERTNA_H */

