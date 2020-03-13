// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          False (False) Header
//****************************************************************
/*
 * Program
 *			False (False)
 * Purpose
 *          This object represents the value, "false", where ever
 *          it is needed such as in processing json.
 *
 * Remarks
 *	1.      None
 *
 * History
 *  11/12/2015 Generated
 *	03/11/2020 Regenerated
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


#ifndef         FALSE_H
#define         FALSE_H


//#define   FALSE_IS_IMMUTABLE     1
#define   FALSE_JSON_SUPPORT     1
//#define   FALSE_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct False_data_s	FALSE_DATA;            // Inherits from OBJ
    typedef struct False_class_data_s FALSE_CLASS_DATA;   // Inherits from OBJ

    typedef struct False_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in False_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(FALSE_DATA *);
    } FALSE_VTBL;

    typedef struct False_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in False_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(FALSE_DATA *);
    } FALSE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  FALSE_SINGLETON
    FALSE_DATA *    False_Shared (
        void
    );

    void            False_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to False object if successful, otherwise OBJ_NIL.
     */
    FALSE_DATA *    False_Alloc (
        void
    );
    
    
    OBJ_ID          False_Class (
        void
    );
    
    
    FALSE_DATA *    False_New (
        void
    );
    
    
#ifdef  FALSE_JSON_SUPPORT
    FALSE_DATA *    False_NewFromJsonString (
        ASTR_DATA       *pString
    );

    FALSE_DATA *    False_NewFromJsonStringA (
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

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = False_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another FALSE object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT     False_Assign (
        FALSE_DATA  *this,
        FALSE_DATA  *pOther
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         False_Compare (
        FALSE_DATA     *this,
        FALSE_DATA     *pOther
    );

   
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        False      *pCopy = False_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a FALSE object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    FALSE_DATA *     False_Copy (
        FALSE_DATA       *this
    );


    FALSE_DATA *   False_Init (
        FALSE_DATA     *this
    );


#ifdef  FALSE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = False_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     False_ToJson (
        FALSE_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = False_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    False_ToDebugString (
        FALSE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* FALSE_H */

