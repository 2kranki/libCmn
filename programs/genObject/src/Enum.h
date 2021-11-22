// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Enum Item (Enum) Header
//****************************************************************
/*
 * Program
 *          Enum Item (Enum)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate Enum to run things without complications
 *          of interfering with the main Enum. A Enum may be 
 *          called a Enum on other O/S's.
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


#ifndef         ENUM_H
#define         ENUM_H


//#define   ENUM_IS_IMMUTABLE     1
#define   ENUM_JSON_SUPPORT       1
//#define   ENUM_SINGLETON        1
//#define       ENUM_MSGS   1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Enum_data_s  ENUM_DATA;          // Inherits from ENUM
    typedef struct Enum_class_data_s ENUM_CLASS_DATA;  // Inherits from OBJ

    typedef struct Enum_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //Enum_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Enum_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ENUM_DATA *);
    } ENUM_VTBL;

    typedef struct Enum_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Enum_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ENUM_DATA *);
    } ENUM_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  ENUM_SINGLETON
    ENUM_DATA *     Enum_Shared (
        void
    );

    void            Enum_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Enum object if successful, otherwise OBJ_NIL.
     */
    ENUM_DATA *     Enum_Alloc (
        void
    );
    
    
    OBJ_ID          Enum_Class (
        void
    );
    
    
    ENUM_DATA *     Enum_New (
        void
    );
    
    
#ifdef  ENUM_JSON_SUPPORT
    ENUM_DATA *   Enum_NewFromJsonString (
        ASTR_DATA       *pString
    );

    ENUM_DATA *   Enum_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef ENUM_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            Enum_setMsgs (
        ENUM_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     Enum_Disable (
        ENUM_DATA       *this
    );


    ERESULT     Enum_Enable (
        ENUM_DATA       *this
    );

   
    ENUM_DATA *   Enum_Init (
        ENUM_DATA     *this
    );


    ERESULT     Enum_IsEnabled (
        ENUM_DATA       *this
    );
    
 
#ifdef  ENUM_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Enum_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Enum_ToJson (
        ENUM_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Enum_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Enum_ToDebugString (
        ENUM_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* ENUM_H */

