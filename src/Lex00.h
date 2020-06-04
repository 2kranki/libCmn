// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//         Lexical Scanner 00 - C Trigraphs (Lex00) Header
//****************************************************************
/*
 * Program
 *          Lexical Scanner 00 - C Trigraphs (Lex00)
 * Purpose
 *          This object serves as a filter to convert all C
 *          trigraphs back into normal C letters. Most source
 *          tokens are just passed through this. When a trigraph
 *          is recognized, it is converted into one token from
 *          three input tokens.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  05/30/2020 Generated and merged logic from pplex1
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


#ifndef         LEX00_H
#define         LEX00_H


//#define   LEX00_IS_IMMUTABLE     1
//#define   LEX00_JSON_SUPPORT     1
//#define   LEX00_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Lex00_data_s  LEX00_DATA;                // Inherits from Lex
    typedef struct Lex00_class_data_s LEX00_CLASS_DATA;     // Inherits from OBJ

    typedef struct Lex00_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Lex00_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEX00_DATA *);
    } LEX00_VTBL;

    typedef struct Lex00_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Lex00_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEX00_DATA *);
    } LEX00_CLASS_VTBL;


    // The following defines the flags for the scanner. The first eigth flags
    // should be reserved for this object. Inheriting object may use the rest.
    // These flags are used with the Flags property:
    typedef enum Lex00_Flags_e {
        LEX00_FLAG_UNKNOWN=0,
        LEX00_FLAG_NL=0x00800000,                   /* ON: Pass NLs as a separate token
                                                       OFF: Ignore NLs
                                                     */
        LEX00_FLAG_WS=0x00400000,                   /* ON: Pass White-space as a separate
                                                            token
                                                       OFF: Ignore White-Space
                                                     */
    } LEX00_FLAGS;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  LEX00_SINGLETON
    LEX00_DATA *    Lex00_Shared (
        void
    );

    void            Lex00_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Lex00 object if successful, otherwise OBJ_NIL.
     */
    LEX00_DATA *    Lex00_Alloc (
        void
    );
    
    
    OBJ_ID          Lex00_Class (
        void
    );
    
    
    LEX00_DATA *    Lex00_New (
        void
    );
    
    
#ifdef  LEX00_JSON_SUPPORT
    LEX00_DATA *   Lex00_NewFromJsonString (
        ASTR_DATA       *pString
    );

    LEX00_DATA *   Lex00_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            Lex00_getReturnNL(
        LEX00_DATA      *this
    );

    bool            Lex00_setReturnNL(
        LEX00_DATA      *this,
        bool            value
    );


    bool            Lex00_getReturnWS(
        LEX00_DATA      *this
    );

    bool            Lex00_setReturnWS(
        LEX00_DATA      *this,
        bool            value
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     Lex00_Disable (
        LEX00_DATA       *this
    );


    ERESULT     Lex00_Enable (
        LEX00_DATA       *this
    );

   
    LEX00_DATA *   Lex00_Init (
        LEX00_DATA     *this
    );


    ERESULT     Lex00_IsEnabled (
        LEX00_DATA       *this
    );
    
 
#ifdef  LEX00_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Lex00_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Lex00_ToJson (
        LEX00_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Lex00_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Lex00_ToDebugString (
        LEX00_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* LEX00_H */

