// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   W32StrC.c
 *	Generated 01/23/2020 22:22:04
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
#include        <W32StrC_internal.h>
#include        <crc.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      F r e e  L i n e
    //---------------------------------------------------------------

    bool            W32StrC_FreeLine(
        W32STRC_DATA    *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (this->pArray) {
            if (obj_Flag(this, W32STRC_FLAG_MALLOC)) {
                mem_Free((void *)this->pArray);
                obj_FlagOff(this, W32STRC_FLAG_MALLOC);
            }
            this->pArray = NULL;
            this->len = 0;
        }

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          S e t u p
    //---------------------------------------------------------------

    bool            W32StrC_SetupA(
        W32STRC_DATA    *this,
        const
        char            *pStrA
    )
    {
        uint32_t        i;
        W32CHR_T        *pInsert;
        W32CHR_T        chr;
        uint32_t        len;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        W32StrC_FreeLine(this);
        len = (uint32_t)utf8_StrLenA(pStrA);

        // Create the new string from this one.
        this->pArray = mem_Malloc((len + 1) * sizeof(W32CHR_T));
        if (NULL == this->pArray) {
            DEBUG_BREAK();
            return false;
        }
        obj_FlagOn(this, W32STRC_FLAG_MALLOC);

        // Move in the data.
        pInsert = (W32CHR_T *)this->pArray;
        for (i=0; i<len; ++i) {
            chr = utf8_Utf8ToW32_Scan(&pStrA);
            *pInsert++ = chr;
        }
        *pInsert = '\0';
        this->len = len;
        W32StrC_Reset(this);

        // Return to caller.
        return true;
    }


    bool            W32StrC_SetupW32(
        W32STRC_DATA    *this,
        uint32_t        len,
        const
        W32CHR_T        *pStrW32
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        W32StrC_FreeLine(this);
        if (0 == len) {
            len = (uint32_t)utf8_StrLenW32(pStrW32);
        }

        // Create the new string from this one.
        this->pArray = mem_Malloc((len + 1) * sizeof(W32CHR_T));
        if (NULL == this->pArray) {
            DEBUG_BREAK();
            return false;
        }
        obj_FlagOn(this, W32STRC_FLAG_MALLOC);

        // Move in the data.
        memmove((W32CHR_T *)this->pArray, pStrW32, ((len + 1) * sizeof(W32CHR_T)));
        this->len = len;
        W32StrC_Reset(this);

        // Return to caller.
        return true;
    }



    bool            W32StrC_SetupW32Con(
        W32STRC_DATA    *this,
        uint32_t        len,
        const
        W32CHR_T        *pStrW32
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        W32StrC_FreeLine(this);
        if (0 == len) {
            len = (uint32_t)utf8_StrLenW32(pStrW32);
        }

        this->pArray = pStrW32;
        this->len = len;
        W32StrC_Reset(this);

        // Return to caller.
        return true;
    }





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    W32STRC_DATA *  W32StrC_Alloc (
        void
    )
    {
        W32STRC_DATA    *this;
        uint32_t        cbSize = sizeof(W32STRC_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    W32STRC_DATA *  W32StrC_New (
        void
    )
    {
        W32STRC_DATA    *this;
        
        this = W32StrC_Alloc( );
        if (this) {
            this = W32StrC_Init(this);
        } 
        return this;
    }


    W32STRC_DATA *  W32StrC_NewA (
        const
        char            *pStrA
    )
    {
        W32STRC_DATA    *this;
        bool            fRc;

        this = W32StrC_New( );
        if (this) {
            fRc = W32StrC_SetupA(this, pStrA);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    W32STRC_DATA *   W32StrC_NewConW32 (
        const
        W32CHR_T        *pStrW32
    )
    {
        W32STRC_DATA    *this;

        this = W32StrC_New( );
        if (this && pStrW32) {
            this->pArray = (W32CHR_T *)pStrW32;
            this->len = (uint32_t)utf8_StrLenW32(pStrW32);
        }
        return( this );
    }


    W32STRC_DATA *  W32StrC_NewW32 (
        const
        W32CHR_T        *pStrW32
    )
    {
        W32STRC_DATA    *this;
        bool            fRc;

        this = W32StrC_New( );
        if (this) {
            fRc = W32StrC_SetupW32(this, 0, pStrW32);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return( this );
    }


    W32STRC_DATA *  W32StrC_NewFromW32 (
        uint32_t        len,
        const
        W32CHR_T        *pStrW32
    )
    {
        W32STRC_DATA    *this;
        bool            fRc;

        this = W32StrC_New( );
        if (this) {
            fRc = W32StrC_SetupW32(this, len, pStrW32);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return( this );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                           C R C
    //---------------------------------------------------------------

    uint32_t        W32StrC_getCrcIEEE(
        W32STRC_DATA    *this
    )
    {
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        crc = 0;
#ifdef NDEBUG
#else
        if( !W32StrC_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        pCrc = crc_New(CRC_TYPE_IEEE_32);
        crc =   crc_AccumBlock(
                        pCrc,
                        (this->len * sizeof(W32CHR_T)),
                        (const uint8_t *)this->pArray
                 );
        obj_Release(pCrc);
        pCrc = OBJ_NIL;

        return  crc;
    }



    //---------------------------------------------------------------
    //                           D a t a
    //---------------------------------------------------------------

    const
    W32CHR_T *      W32StrC_getData (
        W32STRC_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pArray;
    }


    //---------------------------------------------------------------
    //                      L e n g t h
    //---------------------------------------------------------------

    uint32_t        W32StrC_getLength(
        W32STRC_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !W32StrC_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->len;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        W32StrC_getSize (
        W32STRC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->len;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  W32StrC_getSuperVtbl (
        W32STRC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
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
    //                      A d v a n c e
    //---------------------------------------------------------------

    void            W32StrC_Advance (
        W32STRC_DATA    *this,
        int32_t         offset
    )
    {
        //ERESULT         eRc;
        uint32_t        amt;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return;
        }
#endif

        amt = obj_getMisc(this);
        amt += offset;
        obj_setMisc(this, amt);

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
        ERESULT eRc = W32StrC_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another W32STRC object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         W32StrC_Assign (
        W32STRC_DATA	*this,
        W32STRC_DATA    *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!W32StrC_Validate(pOther)) {
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
        W32StrC_FreeLine(pOther);

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pArray) {
            W32StrC_SetupW32(pOther, 0, this->pArray);
        }

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    int             W32StrC_Compare (
        W32STRC_DATA     *this,
        W32STRC_DATA     *pOther
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        int             i = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!W32StrC_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        i = W32Str_Cmp(this->pArray, pOther->pArray);

        return i;
    }
    
   
    int             W32StrC_CompareA (
        W32STRC_DATA    *this,
        const
        char            *pString
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        const
        W32CHR_T        *pStr1;
        W32CHR_T        chr2;
        int             i = -1;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate( this ) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (NULL == pString) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        pStr1 = this->pArray;
        for( ;; ) {
            chr2 = utf8_Utf8ToW32_Scan(&pString);
            if( *pStr1 )
                ;
            else {
                if( chr2 )
                    //eRc = ERESULT_SUCCESS_LESS_THAN;
                    i = -1;
                break;
            }
            if( chr2 )
                ;
            else {
                if( *pStr1 )
                    //eRc = ERESULT_SUCCESS_GREATER_THAN;
                    i = 1;
                break;
            }
            i = *pStr1 - chr2;
            if( i ) {
                break;
            }
            ++pStr1;
        }
        if (i < 0)
            i = -1;
        else if (i > 0)
            i = 1;

        // Return to caller.
        return i;
    }


    int             W32StrC_CompareW32 (
        W32STRC_DATA    *this,
        const
        W32CHR_T        *pString
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        int             i = -1;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate( this ) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -1;
        }
#endif

        i = W32Str_Cmp(this->pArray, pString);

        // Return to caller.
        return i;
    }




    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        W32StrC      *pCopy = W32StrC_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a W32STRC object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    W32STRC_DATA *     W32StrC_Copy (
        W32STRC_DATA       *this
    )
    {
        W32STRC_DATA       *pOther = OBJ_NIL;
#ifdef W32STRC_IS_CONSTANT
#else
        ERESULT         eRc;
#endif

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef W32STRC_IS_CONSTANT
        obj_Retain(this);
        pOther = this;
#else
        pOther = W32StrC_New( );
        if (pOther) {
            eRc = W32StrC_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif

        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            W32StrC_Dealloc (
        OBJ_ID          objId
    )
    {
        W32STRC_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((W32STRC_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        W32StrC_FreeLine(this);

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
        W32StrC      *pDeepCopy = W32StrC_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a W32STRC object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    W32STRC_DATA *     W32StrC_DeepyCopy (
        W32STRC_DATA       *this
    )
    {
        W32STRC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = W32StrC_New( );
        if (pOther) {
            eRc = W32StrC_Assign(this, pOther);
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
    ERESULT         W32StrC_Disable (
        W32STRC_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
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
    ERESULT         W32StrC_Enable (
        W32STRC_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------

    uint32_t        W32StrC_Hash(
        W32STRC_DATA    *this
    )
    {
        uint32_t        hash = 0;

#ifdef NDEBUG
#else
        if( !W32StrC_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        if (this->pArray) {
            hash = str_HashW32(this->pArray, NULL);
        }

        return hash;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    W32STRC_DATA *   W32StrC_Init (
        W32STRC_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(W32STRC_DATA);
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_W32STRC);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&W32StrC_Vtbl);
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
        fprintf(
                stderr, 
                "W32StrC::sizeof(W32STRC_DATA) = %lu\n", 
                sizeof(W32STRC_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(W32STRC_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         W32StrC_IsEnabled (
        W32STRC_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
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
    //                       L e f t
    //---------------------------------------------------------------

    W32STRC_DATA *  W32StrC_Left(
        W32STRC_DATA    *this,
        uint32_t        len
    )
    {
        W32STRC_DATA    *pNewStr = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (len == 0) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        // Create the new string from this one.
        pNewStr = W32StrC_Mid(this, 1, len);

        // Return to caller.
        return pNewStr;
    }



    //---------------------------------------------------------------
    //                       L o o k  A h e a d
    //---------------------------------------------------------------

    W32CHR_T        W32StrC_LookAhead(
        W32STRC_DATA    *this,
        uint32_t        offset              // Relative to 1
    )
    {
        //ERESULT         eRc;
        uint32_t        amt = 0;
        W32CHR_T        chr = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        amt = obj_getMisc(this);
        amt += offset - 1;
        if (amt < W32StrC_getLength(this))
            chr = this->pArray[amt];

        return chr;
    }



    //---------------------------------------------------------------
    //                          M a t c h
    //---------------------------------------------------------------

    bool            W32StrC_MatchChr(
        W32STRC_DATA    *this,
        W32CHR_T        chr
    )
    {
        int32_t         index;
        bool            fMatch = true;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        index = obj_getMisc(this);
        if (index < W32StrC_getLength(this))
            ;
        else {
            return false;
        }

        if (chr == this->pArray[index])
            ;
        else {
            fMatch = false;
        }

        if (fMatch) {
            obj_setMisc(this, index+1);
        }

        return fMatch;
    }


    bool            W32StrC_MatchStrA(
        W32STRC_DATA    *this,
        const
        char            *pStrA
    )
    {
        W32CHR_T        chr;
        int32_t         index;
        int32_t         len = 0;
        bool            fMatch = true;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        index = obj_getMisc(this);
        if (index < W32StrC_getLength(this))
            ;
        else {
            return false;
        }

        for (;;) {
            chr = utf8_Utf8ToW32_Scan( &pStrA );
            if (chr == '\0') {
                if (len)
                    break;
                else {
                    fMatch = false;
                }
                break;
            }
            if (chr == this->pArray[index]) {
                ++index;
                ++len;
            }
            else {
                fMatch = false;
                break;
            }
        }

        if (fMatch) {
            obj_setMisc(this, index);
        }

        return fMatch;
    }



    //---------------------------------------------------------------
    //                       M i d
    //---------------------------------------------------------------

    W32STRC_DATA *  W32StrC_Mid(
        W32STRC_DATA    *this,
        uint32_t        offset,            /* Relative to 1 */
        uint32_t        len
    )
    {
        W32STRC_DATA    *pNewStr = OBJ_NIL;
        uint32_t        lenStr = W32StrC_getLength(this);
        W32CHR_T        *pArray;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (offset > lenStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (len == 0) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((0 == lenStr) || ((offset + len - 1) > lenStr)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        // Create the new string from this one.
        pNewStr = W32StrC_New();
        pArray = mem_Malloc((len + 1) * sizeof(W32CHR_T));
        if (NULL == pArray) {
            DEBUG_BREAK();
            obj_Release(pNewStr);
            return OBJ_NIL;
        }
        memmove(pArray, &this->pArray[offset-1], (len * sizeof(W32CHR_T)));
        pArray[len] = 0;
        pNewStr->pArray = pArray;
        pNewStr->len = len;
        obj_FlagOn(pNewStr, W32STRC_FLAG_MALLOC);

        // Return to caller.
        return pNewStr;
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
        void        *pMethod = W32StrC_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "W32StrC", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          W32StrC_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        W32STRC_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(W32STRC_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)W32StrC_Class();
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
                            return W32StrC_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return W32StrC_Enable;
                        }
                        break;

                    case 'P':
#ifdef  W32STRC_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return W32StrC_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return W32StrC_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return W32StrC_ToDebugString;
                        }
#ifdef  W32STRC_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return W32StrC_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return W32StrC_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == W32StrC_ToDebugString)
                    return "ToDebugString";
#ifdef  W32STRC_JSON_SUPPORT
                if (pData == W32StrC_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e s e t
    //---------------------------------------------------------------

    void            W32StrC_Reset (
        W32STRC_DATA    *this
    )
    {
        //ERESULT         eRc;
        uint32_t        amt = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return;
        }
#endif

        obj_setMisc(this, amt);

    }



    //---------------------------------------------------------------
    //                       R i g h t
    //---------------------------------------------------------------

    W32STRC_DATA *  W32StrC_Right(
        W32STRC_DATA    *this,
        uint32_t        len
    )
    {
        W32STRC_DATA    *pNewStr = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((len == 0) || (len > this->len)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        // Create the new string from this one.
        pNewStr = W32StrC_Mid(this, (this->len - len + 1), len);

        // Return to caller.
        return pNewStr;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = W32StrC_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32StrC_ToDebugString (
        W32STRC_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32StrC_Validate(this)) {
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
                    W32StrC_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
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
    bool            W32StrC_Validate (
        W32STRC_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_W32STRC))
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


        if (!(obj_getSize(this) >= sizeof(W32STRC_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


