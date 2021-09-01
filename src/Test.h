// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Test Object Framework (Test) Header
//****************************************************************
/*
 * Program
 *          Test Object Framework (Test)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate Test to run things without complications
 *          of interfering with the main Test. A Test may be 
 *          called a Test on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  08/29/2021 Generated
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


#ifndef         TEST_H
#define         TEST_H


//#define   TEST_IS_IMMUTABLE     1
//#define   TEST_JSON_SUPPORT     1
//#define   TEST_SINGLETON        1


#define TestExec(name, test, setup, teardown)\
    pTestNameA = name;\
    eRc = Test_Exec(pTest, pTestNameA, test, setup, teardown);\
    if (ERESULT_FAILED(eRc)) {\
        fprintf(stderr, "Test: %s failed!\n\n\n", name);\
        exit(200);\
    }
#define TestForFail(error)\
    Test_ForFail(this, eRc, error, __FILE__, __LINE__)
#define TestForFalse(test, error)\
    Test_ForFalse(this, test, error, __FILE__, __LINE__)
#define TestForNotNull(test, error)\
    Test_ForNotNull(this, test, error, __FILE__, __LINE__)
#define TestForNull(test, error)\
    Test_ForNull(this, test, error, __FILE__, __LINE__)
#define TestForSuccess(error)\
    Test_ForSucess(this, eRc, error, __FILE__, __LINE__)
#define TestForTrue(test, error)\
    Test_ForTrue(this, test, error, __FILE__, __LINE__)



#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Test_data_s  TEST_DATA;            // Inherits from OBJ
    typedef struct Test_class_data_s TEST_CLASS_DATA;   // Inherits from OBJ

    typedef struct Test_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Test_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TEST_DATA *);
    } TEST_VTBL;

    typedef struct Test_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Test_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TEST_DATA *);
    } TEST_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  TEST_SINGLETON
    TEST_DATA *     Test_Shared (
        void
    );

    void            Test_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Test object if successful, otherwise OBJ_NIL.
     */
    TEST_DATA *     Test_Alloc (
        void
    );
    
    
    OBJ_ID          Test_Class (
        void
    );
    
    
    TEST_DATA *     Test_New (
        void
    );
    
    
#ifdef  TEST_JSON_SUPPORT
    TEST_DATA *     Test_NewFromJsonString (
        ASTR_DATA       *pString
    );

    TEST_DATA *     Test_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            Test_getAllowInt3 (
        TEST_DATA       *this
    );

    bool            Test_setAllowInt3 (
        TEST_DATA       *this,
        bool            fValue
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         Test_Exec (
        TEST_DATA       *this,
        const
        char            *pNameA,
        ERESULT         (*pExec)(TEST_DATA *, const char *),
        ERESULT         (*pSetup)(TEST_DATA *),
        ERESULT         (*pTearDown)(TEST_DATA *)
    );


    ERESULT         Test_ForFalse (
        TEST_DATA       *this,
        bool            fValue,
        const
        char            *pErrorA,
        const
        char            *pFilePathA,
        size_t          iLine
    );


    ERESULT         Test_ForNotNull (
        TEST_DATA       *this,
        void            *pValue,
        const
        char            *pErrorA,
        const
        char            *pFilePathA,
        size_t          iLine
    );


    ERESULT         Test_ForNull (
        TEST_DATA       *this,
        void            *pValue,
        const
        char            *pErrorA,
        const
        char            *pFilePathA,
        size_t          iLine
    );


    ERESULT         Test_ForTrue (
        TEST_DATA       *this,
        bool            fValue,
        const
        char            *pErrorA,
        const
        char            *pFilePathA,
        size_t          iLine
    );


    TEST_DATA *     Test_Init (
        TEST_DATA       *this
    );


    ERESULT         Test_IsEnabled (
        TEST_DATA       *this
    );
    
 
    /*!
     Setup for an execution.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Test_Setup (
        TEST_DATA       *this
    );


    /*!
     Tera down from an execution.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Test_TearDown (
        TEST_DATA       *this
    );


#ifdef  TEST_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Test_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Test_ToJson (
        TEST_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Test_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Test_ToDebugString (
        TEST_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* TEST_H */

