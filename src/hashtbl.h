// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Hash Table Base (hashtbl) Header
//****************************************************************
/*
 * Program
 *			Hash Table Base (hashtbl)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate hashtbl to run things without complications
 *          of interfering with the main hashtbl. A hashtbl may be 
 *          called a hashtbl on other O/S's.
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


#ifndef         HASHTBL_H
#define         HASHTBL_H


//#define   HASHTBL_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct hashtbl_data_s	HASHTBL_DATA;            // Inherits from OBJ
    typedef struct hashtbl_class_data_s HASHTBL_CLASS_DATA;   // Inherits from OBJ

    typedef struct hashtbl_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in hashtbl_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(HASHTBL_DATA *);
    } HASHTBL_VTBL;

    typedef struct hashtbl_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in hashtbl_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(HASHTBL_DATA *);
    } HASHTBL_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  HASHTBL_SINGLETON
    HASHTBL_DATA *     hashtbl_Shared (
        void
    );

    bool            hashtbl_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to hashtbl object if successful, otherwise OBJ_NIL.
     */
    HASHTBL_DATA *     hashtbl_Alloc (
        void
    );
    
    
    OBJ_ID          hashtbl_Class (
        void
    );
    
    
    HASHTBL_DATA *     hashtbl_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     hashtbl_Disable (
        HASHTBL_DATA		*this
    );


    ERESULT     hashtbl_Enable (
        HASHTBL_DATA		*this
    );

   
    HASHTBL_DATA *   hashtbl_Init (
        HASHTBL_DATA     *this
    );


    ERESULT     hashtbl_IsEnabled (
        HASHTBL_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = hashtbl_ToDebugString(this,4);
     @endcode 
     @param     this    HASHTBL object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    hashtbl_ToDebugString (
        HASHTBL_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* HASHTBL_H */

