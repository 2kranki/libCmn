// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Static String with Data (szData) Header
//****************************************************************
/*
 * Program
 *			Static String with Data (szData)
 * Purpose
 *			This object provides support to tie specific data to
 *          a static string.  This object can be used with object
 *          collections such as objArray and objHash.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	02/07/2018 Generated
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


#ifndef         SZDATA_H
#define         SZDATA_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct szData_data_s	SZDATA_DATA;    // Inherits from OBJ.

    typedef struct szData_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in szData_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SZDATA_DATA *);
    } SZDATA_VTBL;



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
     @return    pointer to szData object if successful, otherwise OBJ_NIL.
     */
    SZDATA_DATA *     szData_Alloc(
        void
    );
    
    
    OBJ_ID          szData_Class(
        void
    );
    
    
    SZDATA_DATA *     szData_NewA(
        const
        char            *pName
    );
    
    
    SZDATA_DATA *   szData_NewFromJSONString(
        ASTR_DATA       *pString
    );
    
    SZDATA_DATA *   szData_NewFromJSONStringA(
        const
        char            *pString
    );
    
    
    /*!
     Create a new szData object from an szTbl token.
     @param     token   a valid token from the global szTbl
     @return    If successful, a valid szData object otherwise OBJ_NIL
     */
    SZDATA_DATA *   szData_NewFromToken(
        uint32_t        token
    );
    
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    // Class is used to categorize the string with some kind of
    // identification if needed.
    int32_t         szData_getClass(
        SZDATA_DATA     *this
    );
    
    bool            szData_setClass(
        SZDATA_DATA     *this,
        int32_t         value
    );
    
    
    OBJ_ID          szData_getData(
        SZDATA_DATA     *this
    );
    
    bool            szData_setData(
        SZDATA_DATA     *this,
        OBJ_ID          pValue
    );
    
    
    ERESULT     szData_getLastError(
        SZDATA_DATA		*this
    );


    const
    char *          szData_getString(
        SZDATA_DATA     *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
     ERESULT eRc = szData__Assign(this,pOther);
     @endcode
     @param     this    SZDATA object pointer
     @param     pOther  a pointer to another SZDATA object
     @return    If successful, ERESULT_SUCCESS otherwise an
     ERESULT_* error
     */
    ERESULT         szData_Assign(
        SZDATA_DATA     *this,
        SZDATA_DATA     *pOther
    );
    
    
    /*!
     Compare the names of the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if name == other
                ERESULT_SUCCESS_LESS_THAN if name < other
                ERESULT_SUCCESS_GREATER_THAN if name > other
     */
    ERESULT         szData_Compare(
        SZDATA_DATA     *this,
        SZDATA_DATA     *pOther
    );
    
    /*!
     Compare the name to the provided string.
     @return    ERESULT_SUCCESS_EQUAL if name == other
                ERESULT_SUCCESS_LESS_THAN if name < other
                ERESULT_SUCCESS_GREATER_THAN if name > other
     */
    ERESULT         szData_CompareA(
        SZDATA_DATA     *this,
        const
        char            *pOther
    );

    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
     szData      *pCopy = szData_Copy(this);
     @endcode
     @param     this    SZDATA object pointer
     @return    If successful, a SZDATA object which must be released,
     otherwise OBJ_NIL.
     @warning  Remember to release the returned the SZDATA object.
     */
    SZDATA_DATA *   szData_Copy(
        SZDATA_DATA     *this
    );
    
    
    uint32_t        szData_Hash(
        SZDATA_DATA     *this
    );
    
    
    SZDATA_DATA *   szData_Init(
        SZDATA_DATA     *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = szData_ToDebugString(this,4);
     @endcode 
     @param     this    SZDATA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    szData_ToDebugString(
        SZDATA_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SZDATA_H */

