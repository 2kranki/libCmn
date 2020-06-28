// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  C Lexical Scanner (Lex02) Header
//****************************************************************
/*
 * Program
 *          C Lexical Scanner (Lex02)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate Lex02 to run things without complications
 *          of interfering with the main Lex02. A Lex02 may be 
 *          called a Lex02 on other O/S's.
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


#ifndef         LEX02_H
#define         LEX02_H


//#define   LEX02_IS_IMMUTABLE     1
//#define   LEX02_JSON_SUPPORT     1
//#define   LEX02_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Lex02_data_s  LEX02_DATA;            // Inherits from OBJ
    typedef struct Lex02_class_data_s LEX02_CLASS_DATA;   // Inherits from OBJ

    typedef struct Lex02_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Lex02_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEX02_DATA *);
    } LEX02_VTBL;

    typedef struct Lex02_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Lex02_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEX02_DATA *);
    } LEX02_CLASS_VTBL;


    // The first eight flags are reserved for Lex.
    typedef enum Lex02_Flags_e {
        LEX02_FLAG_RETURN_CM=0x00800000,            // Comments
        LEX02_FLAG_RETURN_NL=0x00400000,            // New-Line
        LEX02_FLAG_RETURN_WS=0x00200000,            // White-Space excluding New-Lines
    } LEX02_FLAGS;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  LEX02_SINGLETON
    LEX02_DATA *     Lex02_Shared (
        void
    );

    void            Lex02_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Lex02 object if successful, otherwise OBJ_NIL.
     */
    LEX02_DATA *     Lex02_Alloc (
        void
    );
    
    
    OBJ_ID          Lex02_Class (
        void
    );
    
    
    LEX02_DATA *     Lex02_New (
        void
    );
    
    
#ifdef  LEX02_JSON_SUPPORT
    LEX02_DATA *   Lex02_NewFromJsonString (
        ASTR_DATA       *pString
    );

    LEX02_DATA *   Lex02_NewFromJsonStringA (
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

    ERESULT     Lex02_Disable (
        LEX02_DATA       *this
    );


    ERESULT     Lex02_Enable (
        LEX02_DATA       *this
    );

   
    LEX02_DATA *   Lex02_Init (
        LEX02_DATA     *this
    );


    ERESULT     Lex02_IsEnabled (
        LEX02_DATA       *this
    );
    
 
#ifdef  LEX02_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Lex02_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Lex02_ToJson (
        LEX02_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Lex02_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Lex02_ToDebugString (
        LEX02_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* LEX02_H */

