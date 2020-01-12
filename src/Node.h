// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODE Console Transmit Task (Node) Header
//****************************************************************
/*
 * Program
 *			Separate Node (Node)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate Node to run things without complications
 *          of interfering with the main Node. A Node may be 
 *          called a Node on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	01/12/2020 Generated
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





#include        <cmn_defs.h>
#include        <AStr.h>


#ifndef         NODE_H
#define         NODE_H


//#define   NODE_JSON_SUPPORT 1
//#define   NODE_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Node_data_s	NODE_DATA;            // Inherits from OBJ
    typedef struct Node_class_data_s NODE_CLASS_DATA;   // Inherits from OBJ

    typedef struct Node_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Node_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODE_DATA *);
    } NODE_VTBL;

    typedef struct Node_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Node_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODE_DATA *);
    } NODE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODE_SINGLETON
    NODE_DATA *     Node_Shared (
        void
    );

    void            Node_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Node object if successful, otherwise OBJ_NIL.
     */
    NODE_DATA *     Node_Alloc (
        void
    );
    
    
    OBJ_ID          Node_Class (
        void
    );
    
    
    NODE_DATA *     Node_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     Node_Disable (
        NODE_DATA		*this
    );


    ERESULT     Node_Enable (
        NODE_DATA		*this
    );

   
    NODE_DATA *   Node_Init (
        NODE_DATA     *this
    );


    ERESULT     Node_IsEnabled (
        NODE_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Node_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Node_ToDebugString (
        NODE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODE_H */

