// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// Monetary Amounts based on 64-bit Signed Integer (Money64) Header
//****************************************************************
/*
 * Program
 *          Monetary Amounts based on 64-bit Signed Integer (Money64)
 * Purpose
 *          This object provides support for a monetary amount based
 *          a 64-bit Signed Integer number.  Internally, the amount
 *          is assumed to have 4 decimal places which seems sufficient
 *          for most monetary systems of the world and transactions.
 *
 *          Great care is taken to eliminate as much rounding error
 *          as possible and overflow is indicated on all operations.
 *
 *          int64_t maximum value is 9223372036854775807. So, our
 *          maximum that we can support is $899,999,999,999,999.9999.
 *          All amounts must be handled by this object since the
 *          internal amount is simply an integer without any decimal
 *          point.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  05/29/2021 Generated
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


#ifndef         MONEY64_H
#define         MONEY64_H


//#define   MONEY64_IS_IMMUTABLE     1
#define   MONEY64_JSON_SUPPORT       1
//#define   MONEY64_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Money64_data_s  MONEY64_DATA;            // Inherits from OBJ
    typedef struct Money64_class_data_s MONEY64_CLASS_DATA;   // Inherits from OBJ

    typedef struct Money64_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Money64_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MONEY64_DATA *);
    } MONEY64_VTBL;

    typedef struct Money64_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Money64_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MONEY64_DATA *);
    } MONEY64_CLASS_VTBL;

    typedef enum Money64_Types_e {
        MONEY64_TYPE_UNKNOWN=0,         // Defaults to US Dollar
        MONEY64_TYPE_USDOLLAR,
    } MONEY64_TYPES;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  MONEY64_SINGLETON
    MONEY64_DATA *  Money64_Shared (
        void
    );

    void            Money64_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Money64 object if successful, otherwise OBJ_NIL.
     */
    MONEY64_DATA *  Money64_Alloc (
        void
    );
    
    
    OBJ_ID          Money64_Class (
        void
    );
    
    
    MONEY64_DATA *  Money64_New (
        void
    );
    
    
#ifdef  MONEY64_JSON_SUPPORT
    MONEY64_DATA *  Money64_NewFromJsonString (
        ASTR_DATA       *pString
    );

    MONEY64_DATA *  Money64_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     @property  Amount  the monetary amount assumed to have 4 decimal places.
                        So, $1.00 would be 10000.
     @warning   Remember that this is assumed to have 4 decimal (not binary)
                places.
     */
    uint64_t        Money64_getAmount (
        MONEY64_DATA    *this
    );

    bool            Money64_setAmount (
        MONEY64_DATA    *this,
        uint64_t        value
    );


    /*!
     @property  Max     the maximum amount that can be held by a Money64
                        object. Remember that this number includes the
                        4 decimal places.
     */
    int64_t         Money64_getMax (
        MONEY64_DATA    *this
    );


    /*!
     @property  Min     the smallest amount that can be held by a Money64
                        object. Remember that this number includes the
                        4 decimal places.
     */
    int64_t         Money64_getMin (
        MONEY64_DATA    *this
    );


    /*!
     @property  Type    the type of the monetary amount stored
                        See MONEY64_TYPES above.
     */
    uint16_t        Money64_getType (
        MONEY64_DATA     *this
    );

    bool            Money64_setType (
        MONEY64_DATA    *this,
        uint16_t        value
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add Other's amount to this amount.
     @param     this    object pointer
     @param     pOther  object pointer
     @return    if successful, ERESULT_SUCCESS.  ERESULT_OVERFLOW if
                the addition overflows. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Money64_Add (
        MONEY64_DATA    *this,
        MONEY64_DATA    *pOther
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = Money64_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another MONEY64 object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Money64_Assign (
        MONEY64_DATA       *this,
        MONEY64_DATA     *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        Money64      *pCopy = Money64_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a MONEY64 object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    MONEY64_DATA *  Money64_Copy (
        MONEY64_DATA    *this
    );


    /*!
     Divide this amount by Other's amount with underflow checking.
     @param     this    object pointer
     @param     pOther  object pointer
     @return    if successful, ERESULT_SUCCESS.  ERESULT_OVERFLOW if
                the addition overflows. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Money64_Div (
        MONEY64_DATA    *this,
        MONEY64_DATA    *pOther
    );


    /*!
     Convert from an AStr to a monetary amount.
     ['(' | '<'] ['$'] [-] [nnn [',']]+ n+ ['.' n+] ['-'] [')' | '>']
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     @warning   this replaces the prior amount.
     */
    ERESULT         Money64_FromAStr (
        MONEY64_DATA    *this,
        ASTR_DATA       *pStr
    );


    MONEY64_DATA *  Money64_Init (
        MONEY64_DATA    *this
    );


    /*!
     Multiply this amount by Other's amount with overflow checking.
     A multiplication will cause 8 decimal places. So, this method
     will round the last 4 decimal placees to meet the standard of
     4 decimal places.
     @param     this    object pointer
     @param     pOther  object pointer
     @return    if successful, ERESULT_SUCCESS.  ERESULT_OVERFLOW if
                the addition overflows. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Money64_Mul (
        MONEY64_DATA    *this,
        MONEY64_DATA    *pOther
    );


    /*!
     Divide this amount by Other's amount with underflow checking
     and return the remainder of the division.
     @param     this    object pointer
     @param     pOther  object pointer
     @return    if successful, ERESULT_SUCCESS.  ERESULT_OVERFLOW if
                the addition overflows. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Money64_Rem (
        MONEY64_DATA    *this,
        MONEY64_DATA    *pOther
    );


#ifdef  MONEY64_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Money64_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Money64_ToJson (
        MONEY64_DATA   *this
    );
#endif


    /*!
     Create a string from the number in the form: ('-' | ' ') nnn,nnn,nnn.nnnn
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Money64_ToAStr (
        MONEY64_DATA    *this
    );


    /*!
     Create a string from the number in the form: ('-' | ' ') nnn,nnn,nnn.nn rounding
     up the thousandths of cents.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Money64_ToAStrDec2 (
        MONEY64_DATA    *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Money64_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Money64_ToDebugString (
        MONEY64_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* MONEY64_H */

