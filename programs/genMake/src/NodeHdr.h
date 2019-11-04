// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODEHDR Console Transmit Task (NodeHdr) Header
//****************************************************************
/*
 * Program
 *			Separate NodeHdr (NodeHdr)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate NodeHdr to run things without complications
 *          of interfering with the main NodeHdr. A NodeHdr may be 
 *          called a NodeHdr on other O/S's.
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
#include        <NodeBase.h>
#include        <AStr.h>


#ifndef         NODEHDR_H
#define         NODEHDR_H


//#define   NODEHDR_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodeHdr_data_s	NODEHDR_DATA;            // Inherits from OBJ
    typedef struct NodeHdr_class_data_s NODEHDR_CLASS_DATA;   // Inherits from OBJ

    typedef struct NodeHdr_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeHdr_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEHDR_DATA *);
    } NODEHDR_VTBL;

    typedef struct NodeHdr_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeHdr_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEHDR_DATA *);
    } NODEHDR_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEHDR_SINGLETON
    NODEHDR_DATA *     NodeHdr_Shared (
        void
    );

    bool            NodeHdr_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeHdr object if successful, otherwise OBJ_NIL.
     */
    NODEHDR_DATA *  NodeHdr_Alloc (
        void
    );
    
    
    OBJ_ID          NodeHdr_Class (
        void
    );
    
    
    NODEHDR_DATA *  NodeHdr_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: Source Dependencies, zero or more file paths that
        compilation depends on.
    */
    ASTRARRAY_DATA * NodeHdr_getDeps (
        NODEHDR_DATA    *this
    );

    bool            NodeHdr_setDeps (
        NODEHDR_DATA    *this,
        ASTRARRAY_DATA  *pValue
    );


    /*! Property: Test program file name including file extension
     */
    ASTR_DATA *     NodeHdr_getName (
        NODEHDR_DATA    *this
    );

    bool            NodeHdr_setName (
        NODEHDR_DATA    *this,
        ASTR_DATA       *pValue
    );


    NODE_DATA *     NodeHdr_getNode (
        NODEHDR_DATA    *this
    );


    NODEBASE_DATA * NodeHdr_getNodeBase (
        NODEHDR_DATA    *this
    );


    /*! Property: (Optional) Required Computer Architecture
     */
    ASTR_DATA *     NodeHdr_getReqArch (
        NODEHDR_DATA    *this
    );

    bool            NodeHdr_setReqArch (
        NODEHDR_DATA    *this,
        ASTR_DATA       *pValue
    );


    /*! Property: (Optional) Required Operating System
     */
    ASTR_DATA *     NodeHdr_getReqOS (
        NODEHDR_DATA    *this
    );

    bool            NodeHdr_setReqOS (
        NODEHDR_DATA    *this,
        ASTR_DATA       *pValue
    );


    /*! Property: Extra Sources, zero or more file paths that
        are needed to compile with Name property.
    */
    ASTRARRAY_DATA * NodeHdr_getSrcs (
        NODEHDR_DATA    *this
    );

    bool            NodeHdr_setSrcs (
        NODEHDR_DATA    *this,
        ASTRARRAY_DATA  *pValue
    );





    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT             NodeHdr_Disable (
        NODEHDR_DATA		*this
    );


    ERESULT             NodeHdr_Enable (
        NODEHDR_DATA		*this
    );

   
    NODEHDR_DATA *   NodeHdr_Init (
        NODEHDR_DATA     *this
    );


    ERESULT     NodeHdr_IsEnabled (
        NODEHDR_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeHdr_ToDebugString(this,4);
     @endcode 
     @param     this    NODEHDR object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    NodeHdr_ToDebugString (
        NODEHDR_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEHDR_H */

