// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          GENWIN64 Console Transmit Task (genWIN64) Header
//****************************************************************
/*
 * Program
 *			Separate genWIN64 (genWIN64)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate genWIN64 to run things without complications
 *          of interfering with the main genWIN64. A genWIN64 may be 
 *          called a genWIN64 on other O/S's.
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


#ifndef         GENWIN64_H
#define         GENWIN64_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct genWIN64_data_s	GENWIN64_DATA;    // Inherits from OBJ.

    typedef struct genWIN64_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in genWIN64_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GENWIN64_DATA *);
    } GENWIN64_VTBL;



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
     @return    pointer to genWIN64 object if successful, otherwise OBJ_NIL.
     */
    GENWIN64_DATA *     genWIN64_Alloc(
        void
    );
    
    
    OBJ_ID              genWIN64_Class(
        void
    );
    
    
    GENWIN64_DATA *     genWIN64_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    GENBASE_DATA *  genWIN64_getBase(
        GENWIN64_DATA   *this
    );
    
    bool            genWIN64_setBase(
        GENWIN64_DATA   *this,
        GENBASE_DATA    *pValue
    );
    
    
    ERESULT     genWIN64_getLastError(
        GENWIN64_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     genWIN64_Disable(
        GENWIN64_DATA		*this
    );


    ERESULT     genWIN64_Enable(
        GENWIN64_DATA		*this
    );

   
    GENWIN64_DATA *   genWIN64_Init(
        GENWIN64_DATA     *this
    );


    ERESULT     genWIN64_IsEnabled(
        GENWIN64_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = genWIN64_ToDebugString(this,4);
     @endcode 
     @param     this    GENWIN64 object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    genWIN64_ToDebugString(
        GENWIN64_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* GENWIN64_H */

