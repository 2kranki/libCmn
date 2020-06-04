// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Lex07 (Lex07) Header
//****************************************************************
/*
 * Program
 *          Lex07 (Lex07)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate Lex07 to run things without complications
 *          of interfering with the main Lex07. A Lex07 may be 
 *          called a Lex07 on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  05/30/2020 Generated
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
#include        <Lex.h>


#ifndef         LEX07_H
#define         LEX07_H


//#define   LEX07_IS_IMMUTABLE     1
//#define   LEX07_JSON_SUPPORT     1
//#define   LEX07_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Lex07_data_s  LEX07_DATA;            // Inherits from OBJ
    typedef struct Lex07_class_data_s LEX07_CLASS_DATA;   // Inherits from OBJ

    typedef struct Lex07_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Lex07_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEX07_DATA *);
    } LEX07_VTBL;

    typedef struct Lex07_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Lex07_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEX07_DATA *);
    } LEX07_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  LEX07_SINGLETON
    LEX07_DATA *     Lex07_Shared (
        void
    );

    void            Lex07_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Lex07 object if successful, otherwise OBJ_NIL.
     */
    LEX07_DATA *     Lex07_Alloc (
        void
    );
    
    
    OBJ_ID          Lex07_Class (
        void
    );
    
    
    LEX07_DATA *     Lex07_New (
        void
    );
    
    
#ifdef  LEX07_JSON_SUPPORT
    LEX07_DATA *   Lex07_NewFromJsonString (
        ASTR_DATA       *pString
    );

    LEX07_DATA *   Lex07_NewFromJsonStringA (
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

    ERESULT     Lex07_Disable (
        LEX07_DATA       *this
    );


    ERESULT     Lex07_Enable (
        LEX07_DATA       *this
    );

   
    LEX07_DATA *   Lex07_Init (
        LEX07_DATA     *this
    );


    ERESULT     Lex07_IsEnabled (
        LEX07_DATA       *this
    );
    
 
#ifdef  LEX07_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Lex07_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Lex07_ToJson (
        LEX07_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Lex07_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Lex07_ToDebugString (
        LEX07_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* LEX07_H */

