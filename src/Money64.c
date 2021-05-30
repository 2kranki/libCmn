// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Money64.c
 *  Generated 05/29/2021 13:57:23
 *
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include        <Money64_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            Money64_task_body (
        void            *pData
    )
    {
        //MONEY64_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    MONEY64_DATA *     Money64_Alloc (
        void
    )
    {
        MONEY64_DATA       *this;
        uint32_t        cbSize = sizeof(MONEY64_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    MONEY64_DATA *     Money64_New (
        void
    )
    {
        MONEY64_DATA       *this;
        
        this = Money64_Alloc( );
        if (this) {
            this = Money64_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A m o u n t
    //---------------------------------------------------------------

    uint64_t        Money64_getAmount (
        MONEY64_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->amt;
    }


    bool            Money64_setAmount (
        MONEY64_DATA    *this,
        uint64_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->amt = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          M a x
    //---------------------------------------------------------------

    int64_t         Money64_getMax (
        MONEY64_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 8999999999999999999;
    }



    //---------------------------------------------------------------
    //                          M i n
    //---------------------------------------------------------------

    int64_t         Money64_getMin (
        MONEY64_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return -8999999999999999999;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Money64_getPriority (
        MONEY64_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Money64_setPriority (
        MONEY64_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Money64_getSize (
        MONEY64_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * Money64_getStr (
        MONEY64_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        Money64_setStr (
        MONEY64_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Money64_getSuperVtbl (
        MONEY64_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          T y p e
    //---------------------------------------------------------------

    uint16_t        Money64_getType (
        MONEY64_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->type;
    }


    bool            Money64_setType (
        MONEY64_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->type = value;

        return true;
    }





    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A d d
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
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Money64_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        fRc = __builtin_saddll_overflow(this->amt, pOther->amt, &this->amt);
        if (fRc)
            eRc = ERESULT_OVERFLOW;
        if (this->amt < 0) {
            if (this->amt < Money64_getMin(this))
                eRc = ERESULT_OVERFLOW;
        } else {
            if (this->amt > Money64_getMax(this))
                eRc = ERESULT_OVERFLOW;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
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
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Money64_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        pOther->type    = this->type;
        pOther->amt     = this->amt;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Money64_Compare (
        MONEY64_DATA     *this,
        MONEY64_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Money64_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
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
    )
    {
        MONEY64_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef MONEY64_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Money64_New( );
        if (pOther) {
            eRc = Money64_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            Money64_Dealloc (
        OBJ_ID          objId
    )
    {
        MONEY64_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((MONEY64_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Money64_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Money64      *pDeepCopy = Money64_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a MONEY64 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    MONEY64_DATA *     Money64_DeepyCopy (
        MONEY64_DATA       *this
    )
    {
        MONEY64_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Money64_New( );
        if (pOther) {
            eRc = Money64_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Money64_Disable (
        MONEY64_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          D i v
    //---------------------------------------------------------------

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
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int128_t        amt;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Money64_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        amt = this->amt * 10000;    // Expand to 8 decimal places.
        amt /= pOther->amt;
        this->amt = (int64_t)amt;
        if (amt < 0) {
            if (amt < Money64_getMin(this))
                eRc = ERESULT_OVERFLOW;
        } else {
            if (amt > Money64_getMax(this))
                eRc = ERESULT_OVERFLOW;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Money64_Enable (
        MONEY64_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      F r o m  A S t r
    //---------------------------------------------------------------

    /*!
     Convert from an AStr to a monetary amount.
     ['(' | '<'] ['$'] [-] [nnn [',']]+ n+ ['.' n+] ['-'] [')' | '>']
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Money64_FromAStr (
        MONEY64_DATA    *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        int64_t         sign = 1;
        int64_t         amt = 0;
        int64_t         dec = 0;
        int             cDecShift = 4;
        int64_t         result = 0;
        int             i = 0;
        W32CHR_T        chr;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (0 == AStr_getSize(pStr)) {
            return ERESULT_INVALID_FORMAT;
        }

        chr = AStr_CharGetW32(pStr, i+1);
        if (('(' == chr) || ('<' == chr)) {
            sign = -1;
            i++;
        }
        if (i == AStr_getSize(pStr)) {
            return ERESULT_INVALID_FORMAT;
        }

        chr = AStr_CharGetW32(pStr, i+1);
        if ('$' == chr) {
            i++;
        }
        if (i == AStr_getSize(pStr)) {
            return ERESULT_INVALID_FORMAT;
        }

        chr = AStr_CharGetW32(pStr, i+1);
        if ('-' == chr) {
            sign = -1;
            i++;
        } else if ('+' == chr) {
            i++;
        }
        if (i == AStr_getSize(pStr)) {
            return ERESULT_INVALID_FORMAT;
        }

        for (;;) {
            chr = AStr_CharGetW32(pStr, i+1);
            if ((chr >= '0') && (chr <= '9')) {
                fRc = __builtin_smulll_overflow(amt, 10, &amt);
                if (fRc) {
                    return ERESULT_OVERFLOW;
                }
                fRc = __builtin_saddll_overflow(amt, (chr - '0'), &amt);
                if (fRc) {
                    return ERESULT_OVERFLOW;
                }
                i++;
            } else if (',' == chr) {
                i++;
            } else {
                break;
            }
            if (i == AStr_getSize(pStr)) {
                break;
            }
        }

        if (i < AStr_getSize(pStr)) {
            chr = AStr_CharGetW32(pStr, i+1);
            if ('.' == chr) {
                i++;
                for (;;) {
                    chr = AStr_CharGetW32(pStr, i+1);
                    if ((chr >= '0') && (chr <= '9')) {
                        fRc = __builtin_smulll_overflow(dec, 10, &dec);
                        if (fRc) {
                            return ERESULT_OVERFLOW;
                        }
                        fRc = __builtin_saddll_overflow(dec, (chr - '0'), &dec);
                        if (fRc) {
                            return ERESULT_OVERFLOW;
                        }
                        i++;
                        cDecShift--;
                    } else {
                        if (cDecShift < 0)
                            return ERESULT_INVALID_FORMAT;
                        while (cDecShift > 0) {
                            fRc = __builtin_smulll_overflow(dec, 10, &dec);
                            if (fRc) {
                                return ERESULT_OVERFLOW;
                            }
                            cDecShift--;
                        }
                        break;
                    }
                    if (i == AStr_getSize(pStr)) {
                        if (cDecShift < 0)
                            return ERESULT_INVALID_FORMAT;
                        while (cDecShift > 0) {
                            fRc = __builtin_smulll_overflow(dec, 10, &dec);
                            if (fRc) {
                                return ERESULT_OVERFLOW;
                            }
                            cDecShift--;
                        }
                        break;
                    }
                }
            }
        }
        if (i < AStr_getSize(pStr)) {
            chr = AStr_CharGetW32(pStr, i+1);
            if ('-' == chr) {
                sign = -1;
                i++;
            }
        }
        if (i < AStr_getSize(pStr)) {
            chr = AStr_CharGetW32(pStr, i+1);
            if ((')' == chr) || (')' == chr)) {
                i++;
            }
        }

        fRc = __builtin_smulll_overflow(amt, 10000, &result);
        if (fRc) {
            return ERESULT_OVERFLOW;
        }
        fRc = __builtin_saddll_overflow(result, dec, &result);
        if (fRc) {
            return ERESULT_OVERFLOW;
        }
        fRc = __builtin_smulll_overflow(result, sign, &result);
        if (fRc) {
            return ERESULT_OVERFLOW;
        }
        this->amt = result;

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    MONEY64_DATA *   Money64_Init (
        MONEY64_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(MONEY64_DATA);
        //ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of Money64_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_MONEY64);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Money64_Vtbl);
#ifdef  MONEY64_JSON_SUPPORT
        JsonIn_RegisterClass(Money64_Class());
#endif

        this->type = MONEY64_TYPE_USD;      // Default
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Money64::sizeof(MONEY64_DATA) = %lu\n", 
                sizeof(MONEY64_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(MONEY64_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Money64_IsEnabled (
        MONEY64_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                          M u l
    //---------------------------------------------------------------

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
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int128_t        amt;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Money64_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        amt = this->amt;
        amt *= pOther->amt;
        // This now gives us 8 decimal places where we only want 4.
        // So, we will round and shift.
        amt += 5555;
        amt /= 10000;
        this->amt = (int64_t)amt;
        if (amt < 0) {
            if (amt < Money64_getMin(this))
                eRc = ERESULT_OVERFLOW;
        } else {
            if (amt > Money64_getMax(this))
                eRc = ERESULT_OVERFLOW;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = Money64_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Money64", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Money64_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MONEY64_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(MONEY64_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Money64_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return Money64_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Money64_Enable;
                        }
                        break;

                    case 'P':
#ifdef  MONEY64_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Money64_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Money64_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Money64_ToDebugString;
                        }
#ifdef  MONEY64_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Money64_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Money64_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Money64_ToDebugString)
                    return "ToDebugString";
#ifdef  MONEY64_JSON_SUPPORT
                if (pData == Money64_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e m
    //---------------------------------------------------------------

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
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int128_t        amt;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Money64_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        amt = this->amt * 10000;    // Expand to 8 decimal places.
        amt %= pOther->amt;
        this->amt = (int64_t)amt;
        if (amt < 0) {
            if (amt < Money64_getMin(this))
                eRc = ERESULT_OVERFLOW;
        } else {
            if (amt > Money64_getMax(this))
                eRc = ERESULT_OVERFLOW;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                     S u b t r a c t
    //---------------------------------------------------------------

    /*!
     Subtract Other's amount to this amount.
     @param     this    object pointer
     @param     pOther  object pointer
     @return    if successful, ERESULT_SUCCESS.  ERESULT_OVERFLOW if
                the subtraction underflows. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Money64_Sub (
        MONEY64_DATA    *this,
        MONEY64_DATA    *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Money64_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        fRc = __builtin_ssubll_overflow(this->amt, pOther->amt, &this->amt);
        if (fRc)
            eRc = ERESULT_OVERFLOW;
        if (this->amt < 0) {
            if (this->amt < Money64_getMin(this))
                eRc = ERESULT_OVERFLOW;
        } else {
            if (this->amt > Money64_getMax(this))
                eRc = ERESULT_OVERFLOW;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     Money64_ToAStr (
        MONEY64_DATA    *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrkStr;
        //uint32_t        i;
        //uint32_t        j;
        int64_t         amt;
        int64_t         dec;
        char            sign = ' ';
        int             i;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->amt < 0) {
            sign = '-';
            amt = this->amt * -1;
        } else {
            amt = this->amt;
        }
        dec = amt % 10000;
        //dec += 55;                  // Round up to cents
        amt = amt / 10000;

        pWrkStr = AStr_NewFromPrint("%d", amt);
        if (amt > 1000) {
            i = AStr_getSize(pWrkStr);
            eRc = AStr_CharInsertW32(pWrkStr, i-2, ',');
        }
        if (amt > 1000000) {
            i = AStr_getSize(pWrkStr);
            eRc = AStr_CharInsertW32(pWrkStr, i-6, ',');
        }
        if (amt > 1000000000) {
            i = AStr_getSize(pWrkStr);
            eRc = AStr_CharInsertW32(pWrkStr, i-10, ',');
        }
        if (amt > 1000000000000) {
            i = AStr_getSize(pWrkStr);
            eRc = AStr_CharInsertW32(pWrkStr, i-14, ',');
        }
        pStr = AStr_NewFromPrint("%c%s.%04d", sign, AStr_getData(pWrkStr), dec);
        obj_Release(pWrkStr);
        pWrkStr = OBJ_NIL;

        return pStr;
    }


    ASTR_DATA *     Money64_ToAStrDec2 (
        MONEY64_DATA    *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrkStr;
        //uint32_t        i;
        //uint32_t        j;
        int64_t         amt;
        int64_t         dec;
        char            sign = ' ';
        int             i;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->amt < 0) {
            sign = '-';
            amt = this->amt * -1;
        } else {
            amt = this->amt;
        }
        dec = amt % 10000;
        dec = (dec + 55) / 100;             // Round up to cents
        amt = amt / 10000;

        pWrkStr = AStr_NewFromPrint("%d", amt);
        if (amt > 1000) {
            i = AStr_getSize(pWrkStr);
            eRc = AStr_CharInsertW32(pWrkStr, i-2, ',');
        }
        if (amt > 1000000) {
            i = AStr_getSize(pWrkStr);
            eRc = AStr_CharInsertW32(pWrkStr, i-6, ',');
        }
        if (amt > 1000000000) {
            i = AStr_getSize(pWrkStr);
            eRc = AStr_CharInsertW32(pWrkStr, i-10, ',');
        }
        if (amt > 1000000000000) {
            i = AStr_getSize(pWrkStr);
            eRc = AStr_CharInsertW32(pWrkStr, i-14, ',');
        }
        pStr = AStr_NewFromPrint("%c%s.%02d", sign, AStr_getData(pWrkStr), dec);
        obj_Release(pWrkStr);
        pWrkStr = OBJ_NIL;

        return pStr;
    }


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
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Money64_ToDebugString (
        MONEY64_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Money64_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        pWrkStr = Money64_ToAStr(this);
        if (pWrkStr) {
            eRc = AStr_AppendPrint(
                        pStr,
                        "{%p(%s) amt=%s retain=%d\n",
                        this,
                        pInfo->pClassName,
                        AStr_getData(pWrkStr),
                        obj_getRetainCount(this)
                );
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
        }

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    

    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            Money64_Validate (
        MONEY64_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_MONEY64))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(MONEY64_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


