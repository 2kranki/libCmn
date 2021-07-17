// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   CsvRcd.c
 *  Generated 07/16/2021 23:40:28
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
#include        <CsvRcd_internal.h>
#include        <ascii.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    bool            CsvRcd_ParseLineEnd(
        CSVRCD_DATA     *this
    );
    static
    W32STR_DATA *   CsvRcd_ParseField(
        CSVRCD_DATA     *this
    );
    static
    W32ARRAY_DATA * CsvRcd_ParseRcd(
        CSVRCD_DATA     *this
    );
    static
    bool            CsvRcd_ParseSEP(
        CSVRCD_DATA     *this
    );
    static
    W32STR_DATA *   CsvRcd_ParseStringEscaped(
        CSVRCD_DATA     *this
    );
    static
    W32STR_DATA *   CsvRcd_ParseStringNonEscaped(
        CSVRCD_DATA     *this
    );
    static
    W32CHR_T        CsvRcd_ParseTEXTDATA(
        CSVRCD_DATA     *this
    );
    static
    bool            CsvRcd_ParseWS(
        CSVRCD_DATA     *this
    );



    static
    bool            CsvRcd_ParseAddError(
        CSVRCD_DATA     *this,
        ASTR_DATA       *pError
    )
    {

        if (OBJ_NIL == this->pErrors) {
            this->pErrors = AStrArray_New();
            if (OBJ_NIL == this->pErrors) {
                return false;
            }
        }

        if (pError) {
            AStrArray_AppendStr(this->pErrors, pError, NULL);
            return true;
        }

        return false;
    }



    // Look for <cr>[<lf>] or <lf>[<cr>] and discard
    // if found, but return true.
    static
    bool            CsvRcd_ParseLineEnd(
        CSVRCD_DATA     *this
    )
    {
        W32CHR_T        chr1;
        W32CHR_T        chr2;

        // Validate the input parameters.
        if (this->pChr == this->pEnd)
            return true;
        if (0 == *this->pChr)
            return true;

        chr1 = *this->pChr;
        chr2 = *(this->pChr + 1);
        if (chr1 == this->lineEnd1) {
            this->pChr++; this->col++;
            if (chr2 == this->lineEnd2) {
                this->pChr++; this->col++;
            }
            return true;
        } else if (chr1 == this->lineEnd2) {
            this->pChr++; this->col++;
            if (chr2 == this->lineEnd1) {
                this->pChr++; this->col++;
            }
            return true;
        }

        return false;
    }



    static
    W32STR_DATA *   CsvRcd_ParseField(
        CSVRCD_DATA     *this
    )
    {
        W32STR_DATA     *pStr = OBJ_NIL;
        bool            fRc;

        // Validate the input parameters.
        if (this->pChr == this->pEnd)
            return OBJ_NIL;
        if (0 == *this->pChr)
            return OBJ_NIL;

        CsvRcd_ParseWS(this);
        pStr = CsvRcd_ParseStringEscaped(this);
        if (OBJ_NIL == pStr) {
            pStr = CsvRcd_ParseStringNonEscaped(this);
        }
        fRc = CsvRcd_ParseSEP(this);
        if (!fRc) {
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        return pStr;
    }



    static
    W32ARRAY_DATA * CsvRcd_ParseRcd(
        CSVRCD_DATA     *this
    )
    {
        ERESULT         eRc;
        W32ARRAY_DATA   *pRecord = OBJ_NIL;
        W32STR_DATA     *pStr;
        uint32_t        size;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (OBJ_NIL == this->pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        this->pChr = (W32CHR_T *)W32Str_getData(this->pStr);
        size = W32Str_getLength(this->pStr);
        this->pEnd = this->pChr + size;
        if (this->pChr == this->pEnd)
            return OBJ_NIL;
        if (0 == *this->pChr)
            return OBJ_NIL;

        pStr = CsvRcd_ParseField(this);
        if (pStr == OBJ_NIL) {
            return OBJ_NIL;
        }

        pRecord = W32Array_New();
        if (pRecord == OBJ_NIL) {
            return OBJ_NIL;
        }

        eRc = W32Array_AppendStr(pRecord, pStr, NULL);
        if (ERESULT_FAILED(eRc)) {
            obj_Release(pRecord);
            return OBJ_NIL;
        }
        obj_Release(pStr);
        pStr = OBJ_NIL;

        for (;;) {
            pStr = CsvRcd_ParseField(this);
            if (pStr == OBJ_NIL) {
                break;
            }
            eRc = W32Array_AppendStr(pRecord, pStr, NULL);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pRecord);
                return OBJ_NIL;
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;

            if (CsvRcd_ParseLineEnd(this))
                break;
        }

        return pRecord;
    }


    // Scan field terminator.
    static
    bool            CsvRcd_ParseSEP(
        CSVRCD_DATA     *this
    )
    {
        W32CHR_T        chr;

        // Validate the input parameters.
        if (this->pChr == this->pEnd)
            return false;
        if (0 == *this->pChr)
            return true;

        CsvRcd_ParseWS(this);

        chr = *this->pChr;
        if (chr == this->fieldSeparator) {
            this->pChr++; this->col++;
            return true;
        } else if (chr == this->lineEnd1) {
            this->pChr++; this->col++;
            return true;
        } else if (chr == this->lineEnd2) {
            this->pChr++; this->col++;
            return true;
        } else if (chr == 0) {
            this->pChr++; this->col++;
            return true;
        }

        return false;
    }



    static
    W32STR_DATA *   CsvRcd_ParseStringEscaped(
        CSVRCD_DATA     *this
    )
    {
        W32CHR_T        chr;
        W32STR_DATA     *pStr = OBJ_NIL;

        // Validate the input parameters.
        if (this->pChr == this->pEnd)
            return OBJ_NIL;
        if (0 == *this->pChr)
            return OBJ_NIL;

        chr = *this->pChr;
        if (chr == '"') {
            this->pChr++; this->col++;
        } else {
            return pStr;
        }
        pStr = W32Str_New();
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }

        for (;;) {
            if (this->pChr == this->pEnd)
                return OBJ_NIL;
            if (0 == *this->pChr)
                return OBJ_NIL;

            chr = CsvRcd_ParseTEXTDATA(this);
            if (chr) {
                W32Str_AppendCharW32(pStr, 1, chr);
                this->pChr++; this->col++;
                continue;
            }

            chr = *this->pChr;
            if (chr == '"') {
                chr = *(this->pChr + 1);
                if (chr == '"') {
                    W32Str_AppendCharW32(pStr, 1, '"');
                    this->pChr++; this->col++;
                }
                else {
                    break;
                }
            }
            else if (chr == this->fieldSeparator) {
                W32Str_AppendCharW32(pStr, 1, this->fieldSeparator);
                this->pChr++; this->col++;
            }
            else if ((chr == '\f') || (chr == '\n') || (chr == '\r') || (chr == '\t')) {
                W32Str_AppendCharW32(pStr, 1, chr);
                this->pChr++; this->col++;
            }
            else if (chr == '\\') {
                chr = *(this->pChr + 1);
                if (chr == '"') {
                    W32Str_AppendCharW32(pStr, 1, '"');
                    this->pChr++; this->col++;
                }
                else {
                    W32Str_AppendCharW32(pStr, 1, '\\');
                    this->pChr++; this->col++;
                }
            }
            else {
                ASTR_DATA           *pError = AStr_New();
                AStr_AppendPrint(
                                 pError,
                                 "Illegal char in Escaped String at col %d\n",
                                 this->col
                );
                CsvRcd_ParseAddError(this, pError);
                obj_Release(pError);
                obj_Release(pStr);
                pStr = OBJ_NIL;
                break;
            }
        }

        chr = *this->pChr;
        if (chr == '"') {
            this->pChr++; this->col++;
        } else {
            ASTR_DATA           *pError = AStr_New();
            AStr_AppendPrint(
                             pError,
                             "Illegal terminator in Escaped String at col %d\n",
                             this->col
            );
            CsvRcd_ParseAddError(this, pError);
            obj_Release(pError);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        return pStr;
    }



    static
    W32STR_DATA *   CsvRcd_ParseStringNonEscaped(
        CSVRCD_DATA     *this
    )
    {
        ERESULT         eRc;
        W32STR_DATA     *pStr = OBJ_NIL;
        W32CHR_T        chr;

        // Validate the input parameters.
        if (this->pChr == this->pEnd)
            return OBJ_NIL;
        if (0 == *this->pChr)
            return OBJ_NIL;
        pStr = W32Str_New();
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }

        for (;;) {
            if (this->pChr == this->pEnd)
                break;
            if (0 == *this->pChr)
                break;

            chr = *this->pChr;
            if (chr == this->fieldSeparator) {
                break;
            } else if ((chr == this->lineEnd1) || (chr == this->lineEnd2)) {
                break;
            }
            eRc = W32Str_AppendCharW32(pStr, 1, chr);
            this->pChr++; this->col++;
        }
        eRc = W32Str_Trim(pStr);

        return pStr;
    }



    static
    W32CHR_T        CsvRcd_ParseTEXTDATA(
        CSVRCD_DATA     *this
    )
    {
        W32CHR_T        chr;

        // Validate the input parameters.
        if (this->pChr == this->pEnd)
            return 0;
        if (0 == *this->pChr)
            return 0;

        chr = *this->pChr;
        if ((chr == this->fieldSeparator) || (chr == '"')) {
            return 0;
        } else if ((chr == this->lineEnd1) || (chr == this->lineEnd2)) {
            return 0;
        } else if( (chr >= ' ') && (chr < ASCII_DEL) )
            ;
        else if (chr > 128)
            ;
        else
            return 0;

        return chr;
    }



    // Parse White-space
    static
    bool            CsvRcd_ParseWS(
        CSVRCD_DATA     *this
    )
    {
        W32CHR_T        chr;
        bool            fRc = false;

        // Validate the input parameters.
        if (this->pChr == this->pEnd)
            return false;
        if (0 == *this->pChr)
            return false;

        chr = *this->pChr;
        while (((chr == ' ') || (chr == '\f') || (chr == '\t'))
               && !(
                    (chr == this->fieldSeparator)
                    || (chr == this->lineEnd1)
                    || (chr == this->lineEnd2)
                    )
               ) {
            fRc = true;
            this->pChr++; this->col++;
            if (this->pChr == this->pEnd) {
                break;
            }
            if (0 == *this->pChr)
                break;
            chr = *this->pChr;
        }

        return fRc;
    }






    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    CSVRCD_DATA *     CsvRcd_Alloc (
        void
    )
    {
        CSVRCD_DATA       *this;
        uint32_t        cbSize = sizeof(CSVRCD_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    CSVRCD_DATA *     CsvRcd_New (
        void
    )
    {
        CSVRCD_DATA       *this;
        
        this = CsvRcd_Alloc( );
        if (this) {
            this = CsvRcd_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                    E r r o r s
    //---------------------------------------------------------------

    ASTRARRAY_DATA * CsvRcd_getErrors (
        CSVRCD_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pErrors;
    }


    bool            CsvRcd_setErrors (
        CSVRCD_DATA     *this,
        ASTRARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pErrors) {
            obj_Release(this->pErrors);
        }
        this->pErrors = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        CsvRcd_getPriority (
        CSVRCD_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            CsvRcd_setPriority (
        CSVRCD_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
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
    
    uint32_t        CsvRcd_getSize (
        CSVRCD_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    W32STR_DATA *   CsvRcd_getStr (
        CSVRCD_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool            CsvRcd_setStr (
        CSVRCD_DATA     *this,
        W32STR_DATA     *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  CsvRcd_getSuperVtbl (
        CSVRCD_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = CsvRcd_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another CSVRCD object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         CsvRcd_Assign (
        CSVRCD_DATA       *this,
        CSVRCD_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!CsvRcd_Validate(pOther)) {
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
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
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
    int             CsvRcd_Compare (
        CSVRCD_DATA     *this,
        CSVRCD_DATA     *pOther
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
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!CsvRcd_Validate(pOther)) {
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
        CsvRcd      *pCopy = CsvRcd_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a CSVRCD object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    CSVRCD_DATA *     CsvRcd_Copy (
        CSVRCD_DATA       *this
    )
    {
        CSVRCD_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef CSVRCD_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = CsvRcd_New( );
        if (pOther) {
            eRc = CsvRcd_Assign(this, pOther);
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

    void            CsvRcd_Dealloc (
        OBJ_ID          objId
    )
    {
        CSVRCD_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((CSVRCD_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        CsvRcd_setStr(this, OBJ_NIL);

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
        CsvRcd      *pDeepCopy = CsvRcd_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a CSVRCD object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    CSVRCD_DATA *     CsvRcd_DeepyCopy (
        CSVRCD_DATA       *this
    )
    {
        CSVRCD_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = CsvRcd_New( );
        if (pOther) {
            eRc = CsvRcd_Assign(this, pOther);
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
    ERESULT         CsvRcd_Disable (
        CSVRCD_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
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
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         CsvRcd_Enable (
        CSVRCD_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
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
    //                          I n i t
    //---------------------------------------------------------------

    CSVRCD_DATA *   CsvRcd_Init (
        CSVRCD_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(CSVRCD_DATA);
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
        // in the OBJ_INFO at the end of CsvRcd_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_CSVRCD);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&CsvRcd_Vtbl);
#ifdef  CSVRCD_JSON_SUPPORT
        JsonIn_RegisterClass(CsvRcd_Class());
#endif
        
        this->fieldSeparator = ',';
        this->lineEnd1 = '\r';
        this->lineEnd2 = '\n';
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
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "CsvRcd::sizeof(CSVRCD_DATA) = %lu\n", 
                sizeof(CSVRCD_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(CSVRCD_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         CsvRcd_IsEnabled (
        CSVRCD_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
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
    //                      P a r s e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    W32ARRAY_DATA * CsvRcd_Parse (
        CSVRCD_DATA     *this,
        W32STR_DATA     *pLine
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        W32ARRAY_DATA   *pArray = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        CsvRcd_setStr(this, pLine);
        pArray = CsvRcd_ParseRcd(this);
        if (this->pErrors) {
            obj_Release(pArray);
            pArray = OBJ_NIL;
        }
        CsvRcd_setStr(this, OBJ_NIL);

        // Return to caller.
        return pArray;
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
        void        *pMethod = CsvRcd_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "CsvRcd", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          CsvRcd_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        CSVRCD_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(CSVRCD_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)CsvRcd_Class();
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
                            return CsvRcd_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return CsvRcd_Enable;
                        }
                        break;

                    case 'P':
#ifdef  CSVRCD_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return CsvRcd_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return CsvRcd_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return CsvRcd_ToDebugString;
                        }
#ifdef  CSVRCD_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return CsvRcd_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return CsvRcd_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == CsvRcd_ToDebugString)
                    return "ToDebugString";
#ifdef  CSVRCD_JSON_SUPPORT
                if (pData == CsvRcd_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = CsvRcd_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     CsvRcd_ToDebugString (
        CSVRCD_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!CsvRcd_Validate(this)) {
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
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    CsvRcd_getSize(this),
                    obj_getRetainCount(this)
            );

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
    bool            CsvRcd_Validate (
        CSVRCD_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_CSVRCD))
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


        if (!(obj_getSize(this) >= sizeof(CSVRCD_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


