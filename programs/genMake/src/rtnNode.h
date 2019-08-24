// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          RTNNODE Console Transmit Task (rtnNode) Header
//****************************************************************
/*
 * Program
 *			Separate rtnNode (rtnNode)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate rtnNode to run things without complications
 *          of interfering with the main rtnNode. A rtnNode may be 
 *          called a rtnNode on other O/S's.
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





#include        <genMake.h>
#include        <AStr.h>


#ifndef         RTNNODE_H
#define         RTNNODE_H


//#define   RTNNODE_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct rtnNode_data_s	RTNNODE_DATA;            // Inherits from OBJ
    typedef struct rtnNode_class_data_s RTNNODE_CLASS_DATA;   // Inherits from OBJ

    typedef struct rtnNode_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in rtnNode_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(RTNNODE_DATA *);
    } RTNNODE_VTBL;

    typedef struct rtnNode_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in rtnNode_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(RTNNODE_DATA *);
    } RTNNODE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  RTNNODE_SINGLETON
    RTNNODE_DATA *     rtnNode_Shared (
        void
    );

    bool            rtnNode_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to rtnNode object if successful, otherwise OBJ_NIL.
     */
    RTNNODE_DATA *     rtnNode_Alloc (
        void
    );
    
    
    OBJ_ID          rtnNode_Class (
        void
    );
    
    
    RTNNODE_DATA *     rtnNode_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     rtnNode_Disable (
        RTNNODE_DATA		*this
    );


    ERESULT     rtnNode_Enable (
        RTNNODE_DATA		*this
    );

   
    RTNNODE_DATA *   rtnNode_Init (
        RTNNODE_DATA     *this
    );


    ERESULT     rtnNode_IsEnabled (
        RTNNODE_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = rtnNode_ToDebugString(this,4);
     @endcode 
     @param     this    RTNNODE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    rtnNode_ToDebugString (
        RTNNODE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* RTNNODE_H */

