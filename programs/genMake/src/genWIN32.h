// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          GENWIN32 Console Transmit Task (genWIN32) Header
//****************************************************************
/*
 * Program
 *			Separate genWIN32 (genWIN32)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate genWIN32 to run things without complications
 *          of interfering with the main genWIN32. A genWIN32 may be 
 *          called a genWIN32 on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/18/2018 Generated
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
#include        <genBase.h>
#include        <AStr.h>


#ifndef         GENWIN32_H
#define         GENWIN32_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct genWIN32_data_s	GENWIN32_DATA;    // Inherits from OBJ.

    typedef struct genWIN32_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in genWIN32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GENWIN32_DATA *);
    } GENWIN32_VTBL;



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
     @return    pointer to genWIN32 object if successful, otherwise OBJ_NIL.
     */
    GENWIN32_DATA *     genWIN32_Alloc(
        void
    );
    
    
    OBJ_ID              genWIN32_Class(
        void
    );
    
    
    GENWIN32_DATA *     genWIN32_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    GENBASE_DATA *  genWIN32_getBase(
        GENWIN32_DATA   *this
    );
    
    bool            genWIN32_setBase(
        GENWIN32_DATA   *this,
        GENBASE_DATA    *pValue
    );
    
    
    ERESULT     genWIN32_getLastError(
        GENWIN32_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     genWIN32_Disable(
        GENWIN32_DATA		*this
    );


    ERESULT     genWIN32_Enable(
        GENWIN32_DATA		*this
    );

   
    GENWIN32_DATA *   genWIN32_Init(
        GENWIN32_DATA     *this
    );


    ERESULT     genWIN32_IsEnabled(
        GENWIN32_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = genWIN32_ToDebugString(this,4);
     @endcode 
     @param     this    GENWIN32 object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    genWIN32_ToDebugString(
        GENWIN32_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* GENWIN32_H */

