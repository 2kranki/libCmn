// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  True (True) Header
//****************************************************************
/*
 * Program
 *			True (True)
 * Purpose
 *			This object represents the value, "true", where ever
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


#ifndef         TRUE_H
#define         TRUE_H


//#define   TRUE_IS_IMMUTABLE     1
#define   TRUE_JSON_SUPPORT     1
//#define   TRUE_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct True_data_s	TRUE_DATA;            // Inherits from OBJ
    typedef struct True_class_data_s TRUE_CLASS_DATA;   // Inherits from OBJ

    typedef struct True_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in True_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TRUE_DATA *);
    } TRUE_VTBL;

    typedef struct True_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in True_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TRUE_DATA *);
    } TRUE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  TRUE_SINGLETON
    TRUE_DATA *     True_Shared (
        void
    );

    void            True_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to True object if successful, otherwise OBJ_NIL.
     */
    TRUE_DATA *     True_Alloc (
        void
    );
    
    
    OBJ_ID          True_Class (
        void
    );
    
    
    TRUE_DATA *     True_New (
        void
    );
    
    
#ifdef  TRUE_JSON_SUPPORT
    TRUE_DATA *   True_NewFromJsonString (
        ASTR_DATA       *pString
    );

    TRUE_DATA *   True_NewFromJsonStringA (
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
        ERESULT eRc = True_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another TRUE object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         True_Assign (
        TRUE_DATA       *this,
        TRUE_DATA       *pOther
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         True_Compare (
        TRUE_DATA       *this,
        TRUE_DATA       *pOther
    );

   
     /*!
      Copy the current object creating a new object.
      Example:
      @code
         True      *pCopy = True_Copy(this);
      @endcode
      @param     this    object pointer
      @return    If successful, a TRUE object which must be
                 released, otherwise OBJ_NIL.
      @warning   Remember to release the returned object.
      */
     TRUE_DATA *     True_Copy (
         TRUE_DATA       *this
    );


    TRUE_DATA *     True_Init (
        TRUE_DATA       *this
    );


#ifdef  TRUE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = True_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     True_ToJson (
        TRUE_DATA       *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = True_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     True_ToDebugString (
        TRUE_DATA       *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* TRUE_H */

