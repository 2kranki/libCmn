// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          HASH32 Console Transmit Task (hash32) Header
//****************************************************************
/*
 * Program
 *			Separate hash32 (hash32)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate hash32 to run things without complications
 *          of interfering with the main hash32. A hash32 may be 
 *          called a hash32 on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	01/12/2019 Generated
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


#ifndef         HASH32_H
#define         HASH32_H


//#define   HASH32_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct hash32_data_s	HASH32_DATA;            // Inherits from OBJ
    typedef struct hash32_class_data_s HASH32_CLASS_DATA;   // Inherits from OBJ

    typedef struct hash32_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in hash32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(HASH32_DATA *);
    } HASH32_VTBL;

    typedef struct hash32_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in hash32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(HASH32_DATA *);
    } HASH32_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  HASH32_SINGLETON
    HASH32_DATA *     hash32_Shared (
        void
    );

    bool            hash32_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to hash32 object if successful, otherwise OBJ_NIL.
     */
    HASH32_DATA *     hash32_Alloc (
        void
    );
    
    
    OBJ_ID          hash32_Class (
        void
    );
    
    
    HASH32_DATA *     hash32_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     hash32_Disable (
        HASH32_DATA		*this
    );


    ERESULT     hash32_Enable (
        HASH32_DATA		*this
    );

   
    HASH32_DATA *   hash32_Init (
        HASH32_DATA     *this
    );


    ERESULT     hash32_IsEnabled (
        HASH32_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = hash32_ToDebugString(this,4);
     @endcode 
     @param     this    HASH32 object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    hash32_ToDebugString (
        HASH32_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* HASH32_H */

