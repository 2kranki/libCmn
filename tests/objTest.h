// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          OBJTEST Console Transmit Task (objTest) Header
//****************************************************************
/*
 * Program
 *			Separate objTest (objTest)
 * Purpose
 *			This object is used for testing only.  The methods
 *          and functionality were needed by the regression
 *          testing system.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/01/2017 Generated
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





#include        <test_defs.h>
#include        <AStr.h>
#include        <number.h>
#include        <path.h>


#ifndef         OBJTEST_H
#define         OBJTEST_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

#ifdef XYZZY
    typedef enum obj_idents_test_e {
        OBJ_IDENT_OBJTEST=OBJ_IDENT_USER_ENTRIES,
        OBJ_IDENT_OBJTEST_CLASS
    } OBJ_IDENTS_TEST;
#endif
    
    typedef struct objTest_data_s	OBJTEST_DATA;    // Inherits from OBJ.

    typedef struct objTest_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in objTest_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJTEST_DATA *);
    } OBJTEST_VTBL;



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
     @return    pointer to objTest object if successful, otherwise OBJ_NIL.
     */
    OBJTEST_DATA * objTest_Alloc(
        void
    );
    
    
    OBJTEST_DATA * objTest_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            objTest_getArchive(
        OBJTEST_DATA    *this
    );

    
    NUMBER_DATA *   objTest_getArgLength(
        OBJTEST_DATA    *this
    );

    
    PATH_DATA *     objTest_getInPath(
        OBJTEST_DATA    *this
    );


    ERESULT         objTest_getLastError(
        OBJTEST_DATA	*this
    );


    PATH_DATA *     objTest_getOutPath(
        OBJTEST_DATA    *this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    OBJTEST_DATA *   objTest_Init(
        OBJTEST_DATA     *this
    );


    ERESULT         objTest_TestMethod01(
        OBJTEST_DATA    *this,
        OBJ_ID          pData
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = objTest_ToDebugString(this,4);
     @endcode 
     @param     this    OBJTEST object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     objTest_ToDebugString(
        OBJTEST_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJTEST_H */

