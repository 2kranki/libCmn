// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  A Good Test Object (Test01) Header
//****************************************************************
/*
 * Program
 *          A Good Test Object (Test01)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate Test01 to run things without complications
 *          of interfering with the main Test01. A Test01 may be 
 *          called a Test01 on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  11/26/2021 Generated
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


#ifndef         TEST01_H
#define         TEST01_H


//#define   _IS_IMMUTABLE     1
#define   _JSON_SUPPORT       1
//#define   _SINGLETON        1
//#define       TEST01_MSGS   1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Test01_data_s  TEST01_DATA;          // Inherits from OBJ
    typedef struct Test01_class_data_s TEST01_CLASS_DATA;  // Inherits from OBJ

    typedef struct Test01_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //Test01_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Test01_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TEST01_DATA *);
    } TEST01_VTBL;

    typedef struct Test01_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Test01_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TEST01_DATA *);
    } TEST01_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  TEST01_SINGLETON
    TEST01_DATA *     Test01_Shared (
        void
    );

    void            Test01_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Test01 object if successful, otherwise OBJ_NIL.
     */
    TEST01_DATA *     Test01_Alloc (
        void
    );
    
    
    OBJ_ID          Test01_Class (
        void
    );
    
    
    TEST01_DATA *     Test01_New (
        void
    );
    
    
#ifdef  TEST01_JSON_SUPPORT
    TEST01_DATA *   Test01_NewFromJsonString (
        ASTR_DATA       *pString
    );

    TEST01_DATA *   Test01_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef TEST01_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            Test01_setMsgs (
        TEST01_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     Test01_Disable (
        TEST01_DATA       *this
    );


    ERESULT     Test01_Enable (
        TEST01_DATA       *this
    );

   
    TEST01_DATA *   Test01_Init (
        TEST01_DATA     *this
    );


    ERESULT     Test01_IsEnabled (
        TEST01_DATA       *this
    );
    
 
#ifdef  TEST01_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Test01_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Test01_ToJson (
        TEST01_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Test01_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Test01_ToDebugString (
        TEST01_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* TEST01_H */

