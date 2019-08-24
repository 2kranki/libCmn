// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          HDRNODE Console Transmit Task (hdrNode) Header
//****************************************************************
/*
 * Program
 *			Separate hdrNode (hdrNode)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate hdrNode to run things without complications
 *          of interfering with the main hdrNode. A hdrNode may be 
 *          called a hdrNode on other O/S's.
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


#ifndef         HDRNODE_H
#define         HDRNODE_H


//#define   HDRNODE_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct hdrNode_data_s	HDRNODE_DATA;            // Inherits from OBJ
    typedef struct hdrNode_class_data_s HDRNODE_CLASS_DATA;   // Inherits from OBJ

    typedef struct hdrNode_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in hdrNode_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(HDRNODE_DATA *);
    } HDRNODE_VTBL;

    typedef struct hdrNode_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in hdrNode_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(HDRNODE_DATA *);
    } HDRNODE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  HDRNODE_SINGLETON
    HDRNODE_DATA *     hdrNode_Shared (
        void
    );

    bool            hdrNode_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to hdrNode object if successful, otherwise OBJ_NIL.
     */
    HDRNODE_DATA *     hdrNode_Alloc (
        void
    );
    
    
    OBJ_ID          hdrNode_Class (
        void
    );
    
    
    HDRNODE_DATA *     hdrNode_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     hdrNode_Disable (
        HDRNODE_DATA		*this
    );


    ERESULT     hdrNode_Enable (
        HDRNODE_DATA		*this
    );

   
    HDRNODE_DATA *   hdrNode_Init (
        HDRNODE_DATA     *this
    );


    ERESULT     hdrNode_IsEnabled (
        HDRNODE_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = hdrNode_ToDebugString(this,4);
     @endcode 
     @param     this    HDRNODE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    hdrNode_ToDebugString (
        HDRNODE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* HDRNODE_H */

