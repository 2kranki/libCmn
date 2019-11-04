// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODEPGM Console Transmit Task (NodePgm) Header
//****************************************************************
/*
 * Program
 *			Separate NodePgm (NodePgm)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate NodePgm to run things without complications
 *          of interfering with the main NodePgm. A NodePgm may be 
 *          called a NodePgm on other O/S's.
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


#ifndef         NODEPGM_H
#define         NODEPGM_H


//#define   NODEPGM_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodePgm_data_s	NODEPGM_DATA;            // Inherits from OBJ
    typedef struct NodePgm_class_data_s NODEPGM_CLASS_DATA;   // Inherits from OBJ

    typedef struct NodePgm_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodePgm_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEPGM_DATA *);
    } NODEPGM_VTBL;

    typedef struct NodePgm_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodePgm_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEPGM_DATA *);
    } NODEPGM_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEPGM_SINGLETON
    NODEPGM_DATA *     NodePgm_Shared (
        void
    );

    bool            NodePgm_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodePgm object if successful, otherwise OBJ_NIL.
     */
    NODEPGM_DATA *     NodePgm_Alloc (
        void
    );
    
    
    OBJ_ID          NodePgm_Class (
        void
    );
    
    
    NODEPGM_DATA *     NodePgm_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     NodePgm_Disable (
        NODEPGM_DATA		*this
    );


    ERESULT     NodePgm_Enable (
        NODEPGM_DATA		*this
    );

   
    NODEPGM_DATA *   NodePgm_Init (
        NODEPGM_DATA     *this
    );


    ERESULT     NodePgm_IsEnabled (
        NODEPGM_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodePgm_ToDebugString(this,4);
     @endcode 
     @param     this    NODEPGM object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    NodePgm_ToDebugString (
        NODEPGM_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEPGM_H */

