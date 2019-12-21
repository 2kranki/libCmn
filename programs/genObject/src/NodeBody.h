// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODEBODY Console Transmit Task (NodeBody) Header
//****************************************************************
/*
 * Program
 *			Separate NodeBody (NodeBody)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate NodeBody to run things without complications
 *          of interfering with the main NodeBody. A NodeBody may be 
 *          called a NodeBody on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/18/2019 Generated
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





#include        <genObject.h>
#include        <AStr.h>


#ifndef         NODEBODY_H
#define         NODEBODY_H


//#define   NODEBODY_JSON_SUPPORT 1
//#define   NODEBODY_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodeBody_data_s	NODEBODY_DATA;            // Inherits from OBJ
    typedef struct NodeBody_class_data_s NODEBODY_CLASS_DATA;   // Inherits from OBJ

    typedef struct NodeBody_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeBody_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEBODY_DATA *);
    } NODEBODY_VTBL;

    typedef struct NodeBody_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeBody_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEBODY_DATA *);
    } NODEBODY_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEBODY_SINGLETON
    NODEBODY_DATA *     NodeBody_Shared (
        void
    );

    bool            NodeBody_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeBody object if successful, otherwise OBJ_NIL.
     */
    NODEBODY_DATA *     NodeBody_Alloc (
        void
    );
    
    
    OBJ_ID          NodeBody_Class (
        void
    );
    
    
    NODEBODY_DATA *     NodeBody_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     NodeBody_Disable (
        NODEBODY_DATA		*this
    );


    ERESULT     NodeBody_Enable (
        NODEBODY_DATA		*this
    );

   
    NODEBODY_DATA *   NodeBody_Init (
        NODEBODY_DATA     *this
    );


    ERESULT     NodeBody_IsEnabled (
        NODEBODY_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeBody_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    NodeBody_ToDebugString (
        NODEBODY_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEBODY_H */

