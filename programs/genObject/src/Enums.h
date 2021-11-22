// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Enum File Generation (Enums) Header
//****************************************************************
/*
 * Program
 *          Enum File Generation (Enums)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate Enums to run things without complications
 *          of interfering with the main Enums. A Enums may be 
 *          called a Enums on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  11/21/2021 Generated
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





#include        <genObject_defs.h>
#include        <AStr.h>


#ifndef         ENUMS_H
#define         ENUMS_H


//#define   ENUMS_IS_IMMUTABLE     1
#define   ENUMS_JSON_SUPPORT       1
//#define   ENUMS_SINGLETON        1
//#define       ENUMS_MSGS   1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Enums_data_s  ENUMS_DATA;          // Inherits from ENUMS
    typedef struct Enums_class_data_s ENUMS_CLASS_DATA;  // Inherits from OBJ

    typedef struct Enums_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //Enums_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Enums_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ENUMS_DATA *);
    } ENUMS_VTBL;

    typedef struct Enums_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Enums_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ENUMS_DATA *);
    } ENUMS_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  ENUMS_SINGLETON
    ENUMS_DATA *     Enums_Shared (
        void
    );

    void            Enums_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Enums object if successful, otherwise OBJ_NIL.
     */
    ENUMS_DATA *     Enums_Alloc (
        void
    );
    
    
    OBJ_ID          Enums_Class (
        void
    );
    
    
    ENUMS_DATA *     Enums_New (
        void
    );
    
    
#ifdef  ENUMS_JSON_SUPPORT
    ENUMS_DATA *   Enums_NewFromJsonString (
        ASTR_DATA       *pString
    );

    ENUMS_DATA *   Enums_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef ENUMS_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            Enums_setMsgs (
        ENUMS_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     Enums_Disable (
        ENUMS_DATA       *this
    );


    ERESULT     Enums_Enable (
        ENUMS_DATA       *this
    );

   
    ENUMS_DATA *   Enums_Init (
        ENUMS_DATA     *this
    );


    ERESULT     Enums_IsEnabled (
        ENUMS_DATA       *this
    );
    
 
#ifdef  ENUMS_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Enums_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Enums_ToJson (
        ENUMS_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Enums_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Enums_ToDebugString (
        ENUMS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* ENUMS_H */

