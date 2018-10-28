// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          DISKS Console Transmit Task (disks) Header
//****************************************************************
/*
 * Program
 *			Separate disks (disks)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate disks to run things without complications
 *          of interfering with the main disks. A disks may be 
 *          called a disks on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	10/27/2018 Generated
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


#ifndef         DISKS_H
#define         DISKS_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct disks_data_s	DISKS_DATA;    // Inherits from OBJ.

    typedef struct disks_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in disks_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DISKS_DATA *);
    } DISKS_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to disks object if successful, otherwise OBJ_NIL.
     */
    DISKS_DATA *     disks_Alloc(
        void
    );
    
    
    OBJ_ID          disks_Class(
        void
    );
    
    
    DISKS_DATA *     disks_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     disks_Disable(
        DISKS_DATA		*this
    );


    ERESULT     disks_Enable(
        DISKS_DATA		*this
    );

   
    DISKS_DATA *   disks_Init(
        DISKS_DATA     *this
    );


    ERESULT     disks_IsEnabled(
        DISKS_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = disks_ToDebugString(this,4);
     @endcode 
     @param     this    DISKS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    disks_ToDebugString(
        DISKS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DISKS_H */

