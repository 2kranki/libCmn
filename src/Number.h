// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Number (Number) Header
//****************************************************************
/*
 * Program
 *          Number (Number)
 * Purpose
 *          This object provides an object to hold a number of
 *          varying sizes.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  10/22/2015 Generated
 *  05/23/2020 Regenerated
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


#ifndef         NUMBER_H
#define         NUMBER_H


//#define   NUMBER_IS_IMMUTABLE     1
#define   NUMBER_JSON_SUPPORT       1
//#define   NUMBER_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Number_data_s  NUMBER_DATA;            // Inherits from OBJ
    typedef struct Number_class_data_s NUMBER_CLASS_DATA;   // Inherits from OBJ

    typedef struct Number_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Number_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NUMBER_DATA *);
    } NUMBER_VTBL;

    typedef struct Number_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Number_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NUMBER_DATA *);
    } NUMBER_CLASS_VTBL;


    typedef enum Number_type_e {
        NUMBER_TYPE_UNKNOWN=0,
#if defined(__MACOSX_ENV__)  || defined(__MACOS64_ENV__)
        NUMBER_TYPE_FLOAT,          // Float or Double
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        NUMBER_TYPE_FLOAT,          // Float or Double
#endif
        NUMBER_TYPE_INT16,          // int16_t
        NUMBER_TYPE_INT32,          // int32_t
        NUMBER_TYPE_INT64,          // int64_t
        NUMBER_TYPE_UINT16,         // uint16_t
        NUMBER_TYPE_UINT32,         // uint32_t
        NUMBER_TYPE_UINT64,         // uint64_t
    } NUMBER_TYPE;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NUMBER_SINGLETON
    NUMBER_DATA *   Number_Shared (
        void
    );

    void            Number_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Number object if successful, otherwise OBJ_NIL.
     */
    NUMBER_DATA *   Number_Alloc (
        void
    );
    
    
    OBJ_ID          Number_Class (
        void
    );
    
    
    NUMBER_DATA *   Number_New (
        void
    );
    
    
    NUMBER_DATA *   Number_NewA(
        const
        char            *pStr
    );


    NUMBER_DATA *   Number_NewInt16(
        int16_t         value
    );


    NUMBER_DATA *   Number_NewInt32(
        int32_t         value
    );


    NUMBER_DATA *   Number_NewInt64(
        int64_t         value
    );


    NUMBER_DATA *   Number_NewUint16(
        uint16_t        value
    );


    NUMBER_DATA *   Number_NewUint32(
        uint32_t        value
    );


    NUMBER_DATA *   Number_NewUint64(
        uint64_t        value
    );


#ifdef  NUMBER_JSON_SUPPORT
    NUMBER_DATA *   Number_NewFromJsonString (
        ASTR_DATA       *pString
    );

    NUMBER_DATA *   Number_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        Number_getType(
        NUMBER_DATA     *this
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
        ERESULT eRc = Number_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another NUMBER object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Number_Assign (
        NUMBER_DATA     *this,
        NUMBER_DATA     *pOther
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         Number_Compare (
        NUMBER_DATA     *this,
        NUMBER_DATA     *pOther
    );

    ERESULT         Number_CompareA(
        NUMBER_DATA     *this,
        const
        char            *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        Number      *pCopy = Number_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a NUMBER object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NUMBER_DATA *     Number_Copy (
        NUMBER_DATA       *this
    );


    double          Number_Float(
        NUMBER_DATA     *this
    );


    int16_t         Number_I16(
        NUMBER_DATA     *this
    );


    int32_t         Number_I32(
        NUMBER_DATA     *this
    );


    int64_t         Number_I64(
        NUMBER_DATA     *this
    );


    NUMBER_DATA *   Number_Init (
        NUMBER_DATA     *this
    );


    ERESULT         Number_IsEnabled (
        NUMBER_DATA     *this
    );
    
 
#ifdef  NUMBER_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Number_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Number_ToJson (
        NUMBER_DATA     *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Number_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Number_ToDebugString (
        NUMBER_DATA     *this,
        int             indent
    );
    
    
    uint16_t        Number_U16(
        NUMBER_DATA     *this
    );


    uint32_t        Number_U32(
        NUMBER_DATA     *this
    );


    uint64_t        Number_U64(
        NUMBER_DATA     *this
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* NUMBER_H */

