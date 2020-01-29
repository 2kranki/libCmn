// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          DATETIME Console Transmit Task (DateTime) Header
//****************************************************************
/*
 * Program
 *			Separate DateTime (DateTime)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate DateTime to run things without complications
 *          of interfering with the main DateTime. A DateTime may be 
 *          called a DateTime on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	01/29/2020 Generated
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


#ifndef         DATETIME_H
#define         DATETIME_H


//#define   DATETIME_IS_IMMUTABLE     1
//#define   DATETIME_JSON_SUPPORT     1
//#define   DATETIME_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct DateTime_data_s	DATETIME_DATA;            // Inherits from OBJ
    typedef struct DateTime_class_data_s DATETIME_CLASS_DATA;   // Inherits from OBJ

    typedef struct DateTime_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in DateTime_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DATETIME_DATA *);
    } DATETIME_VTBL;

    typedef struct DateTime_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in DateTime_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DATETIME_DATA *);
    } DATETIME_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  DATETIME_SINGLETON
    DATETIME_DATA *     DateTime_Shared (
        void
    );

    void            DateTime_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to DateTime object if successful, otherwise OBJ_NIL.
     */
    DATETIME_DATA *     DateTime_Alloc (
        void
    );
    
    
    OBJ_ID          DateTime_Class (
        void
    );
    
    
    DATETIME_DATA *     DateTime_New (
        void
    );
    
    
#ifdef  DATETIME_JSON_SUPPORT
    DATETIME_DATA *   DateTime_NewFromJsonString(
        ASTR_DATA       *pString
    );

    DATETIME_DATA *   DateTime_NewFromJsonStringA(
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     DateTime_Disable (
        DATETIME_DATA		*this
    );


    ERESULT     DateTime_Enable (
        DATETIME_DATA		*this
    );

   
    DATETIME_DATA *   DateTime_Init (
        DATETIME_DATA     *this
    );


    ERESULT     DateTime_IsEnabled (
        DATETIME_DATA		*this
    );
    
 
#ifdef  DATETIME_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = DateTime_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     DateTime_ToJson(
        DATETIME_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = DateTime_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    DateTime_ToDebugString (
        DATETIME_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DATETIME_H */

