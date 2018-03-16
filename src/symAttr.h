// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SYMATTR Console Transmit Task (symAttr) Header
//****************************************************************
/*
 * Program
 *			Separate symAttr (symAttr)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate symAttr to run things without complications
 *          of interfering with the main symAttr. A symAttr may be 
 *          called a symAttr on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	02/02/2018 Generated
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
#include        <visitor.h>


#ifndef         SYMATTR_H
#define         SYMATTR_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct symAttr_data_s	SYMATTR_DATA;    // Inherits from OBJ.

    typedef struct symAttr_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in symAttr_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SYMATTR_DATA *);
    } SYMATTR_VTBL;



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
     @return    pointer to symAttr object if successful, otherwise OBJ_NIL.
     */
    SYMATTR_DATA *  symAttr_Alloc(
        void
    );
    
    
    OBJ_ID          symAttr_Class(
        void
    );
    
    
    SYMATTR_DATA *  symAttr_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    int32_t         symAttr_getClass(
        SYMATTR_DATA    *this
    );
    
    bool            symAttr_setClass(
        SYMATTR_DATA    *this,
        int32_t         value
    );
    
    
    ERESULT         symAttr_getLastError(
        SYMATTR_DATA    *this
    );


    int32_t         symAttr_getType(
        SYMATTR_DATA    *this
    );
    
    bool            symAttr_setType(
        SYMATTR_DATA    *this,
        int32_t         value
    );
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     symAttr_Disable(
        SYMATTR_DATA		*this
    );


    ERESULT     symAttr_Enable(
        SYMATTR_DATA		*this
    );

   
    SYMATTR_DATA *   symAttr_Init(
        SYMATTR_DATA     *this
    );


    ERESULT     symAttr_IsEnabled(
        SYMATTR_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = symAttr_ToDebugString(this,4);
     @endcode 
     @param     this    SYMATTR object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    symAttr_ToDebugString(
        SYMATTR_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SYMATTR_H */

