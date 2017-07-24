// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   hex.c
 *	Generated 10/08/2016 09:17:56
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
#include "hex_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    static
    const
    char            *pHexChr = "0123456789ABCDEF";
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //****************************************************************
    // 		HexDigit - Add a Character to the output
    //****************************************************************
    
    uint32_t        hex_putBytes16Obj(
        HEX_DATA        *this,
        bool            f64,
        uint64_t        offset,
        uint32_t        cData,
        const
        void            *pData,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    )
    {
        uint32_t            i;
        uint32_t            j;
        char                wrkChr;
        uint32_t            len = 0;
        bool                fRc;
        
        // Do initialization.
        if( 0 == cData )
            return 0;
        if( (NULL == pPutChar) )
            return 0;
        if( cData > 16 )
            cData = 16;
        
        //  Display the line.
        if (f64) {
            len += hex_putU64Obj( this, offset, pObject, pPutChar );
        }
        else {
            len += hex_putU32Obj( this, (uint32_t)offset, pObject, pPutChar );
        }
        fRc = pPutChar(pObject, ' ');
        if (fRc) {
            ++len;
        }
        for( i=0; i<4; i++ ) {
            fRc = pPutChar(pObject, ' ');
            if (fRc) {
                ++len;
            }
            for( j=0; j<4; j++ ) {
                if( (4*i+j) < cData ) {
                    len +=  hex_putU8Obj(
                                    this,
                                    ((uint8_t *)pData)[(4*i)+j],
                                    pObject,
                                    pPutChar
                            );
                }
                else {
                    fRc = pPutChar(pObject, ' ');
                    if (fRc) {
                        ++len;
                    }
                    fRc = pPutChar(pObject, ' ');
                    if (fRc) {
                        ++len;
                    }
                }
            }
        }
        fRc = pPutChar(pObject, ' ');
        if (fRc) {
            ++len;
        }
        fRc = pPutChar(pObject, ' ');
        if (fRc) {
            ++len;
        }
        fRc = pPutChar(pObject, '*');
        if (fRc) {
            ++len;
        }
        for( i=0; i<16; i++ ) {
            wrkChr = (char)((uint8_t)((uint8_t *)pData)[i] & 0x7F);
            if (wrkChr == 0x7F)
                wrkChr = '.';
            if (wrkChr < ' ')
                wrkChr = '.';
            if( i < cData ) {
                fRc = pPutChar(pObject, wrkChr);
                if (fRc) {
                    ++len;
                }
            }
            else {
                fRc = pPutChar(pObject, ' ');
                if (fRc) {
                    ++len;
                }
            }
        }
        fRc = pPutChar(pObject, '*');
        if (fRc) {
            ++len;
        }
        
        // Return to caller.
        return len;
    }
    
    
    bool            hex_putChar(
        HEX_DATA        *this,
        uint8_t         data
    )
    {
        
        // Do initialization.
        if (*this->pLen > 0) {
            **this->ppBuffer = data;
            ++*this->ppBuffer;
            --*this->pLen;
            return true;
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    uint32_t        hex_putDigit(
        HEX_DATA        *this,
        uint8_t         input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    )
    {
        uint32_t        len = 0;
        char        	WrkChr;
        bool            fRc;
        
        // Do initialization.
        
        // Print the Number.
        WrkChr = (char)(input & 0x0F);
        WrkChr = pHexChr[(int)WrkChr];
        //    WrkChr = (char)( WrkChr < 10 ? WrkChr + '0' : WrkChr + 'A' - 10 );
        fRc = pPutChar(pObject, WrkChr);
        if (fRc) {
            ++len;
        }
        
        // Return to caller.
        return len;
    }
    
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    HEX_DATA *     hex_Alloc(
    )
    {
        HEX_DATA       *this;
        uint32_t        cbSize = sizeof(HEX_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    HEX_DATA *     hex_New(
    )
    {
        HEX_DATA       *this;
        
        this = hex_Alloc( );
        if (this) {
            this = hex_Init(this);
        } 
        return this;
    }



    char            hex_DigitToChrA(
        int             value
    )
    {
        char            chr = '?';
        
        if ((value >= 0) && (value < 16)) {
            chr = pHexChr[value];
        }
        
        return chr;
    }
    
    
    
    int             hex_DigitToIntA(
        const
        char            chr
    )
    {
        int             value = -1;
        
        if( (chr >= 'A') && (chr <= 'F') )
            value = chr - 'A' + 10;
        else if( (chr >= 'a') && (chr <= 'f') )
            value = chr - 'a' + 10;
        else if( (chr >= '0') && (chr <= '9') )
            value = chr - '0';
        
        return value;
    }
    
    
    
    //---------------------------------------------------------------
    //                     S c a n  H e x
    //---------------------------------------------------------------
    
    bool            hex_ScanUint32A(
        uint32_t        cLen,
        const
        char            *pInputBuffer,
        uint32_t        *pAmount
    )
    {
        bool            fRc = true;
        uint32_t		amt = 0;
        char			chr;
        
        // Do initialization.
        if( cLen == 0 )
            cLen = 9;
        if( NULL == pAmount )
            return false;
        *pAmount = 0;
        if( NULL == pInputBuffer )
            return false;
        
        for( ;; ) {
            chr = *pInputBuffer;
            if( (0 == chr) || (0 == cLen) )
                break;
            if( chr == ' ' ) {
                ++pInputBuffer;
                --cLen;
                continue;
            }
            else
                break;
        }
        
        if( (0 == chr) || (0 == cLen) )
            ;
        else {
            for( ;; ) {
                chr = *pInputBuffer;
                if( (0 == cLen) )
                    break;
                if( (chr >= 'A') && (chr <= 'F') )
                    chr = chr - 'A' + 10;
                else if( (chr >= 'a') && (chr <= 'f') )
                    chr = chr - 'a' + 10;
                else if( (chr >= '0') && (chr <= '9') )
                    chr = chr - '0';
                else
                    break;
                amt <<= 4;
                amt += chr;
                ++pInputBuffer;
                --cLen;
            }
        }
        
        // Return to caller.
        fRc = true;
        *pAmount = amt;
        return fRc;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         hex_getLastError(
        HEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !hex_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }



    uint16_t        hex_getPriority(
        HEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !hex_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        this->eRc = ERESULT_SUCCESS;
        //return this->priority;
        return 0;
    }

    bool            hex_setPriority(
        HEX_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !hex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        this->eRc = ERESULT_SUCCESS;
        return true;
    }



    uint32_t        hex_getSize(
        HEX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !hex_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        this->eRc = ERESULT_SUCCESS;
        return 0;
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
     @code:
        ERESULT eRc = hex__Assign(this,pOther);
     @endcode:
     @param:    this    HEX object pointer
     @param:    pOther  a pointer to another HEX object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         hex_Assign(
        HEX_DATA		*this,
        HEX_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !hex_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( !hex_Validate(pOther) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

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
        
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        //goto eom;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        this->eRc = ERESULT_NOT_IMPLEMENTED; // <-- Remove this!
    //eom:
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        hex      *pCopy = hex_Copy(this);
     @endcode:
     @param:    this    HEX object pointer
     @return:   If successful, a HEX object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the HEX object.
     */
    HEX_DATA *     hex_Copy(
        HEX_DATA       *this
    )
    {
        HEX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !hex_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = hex_New( );
        if (pOther) {
            eRc = hex_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        this->eRc = ERESULT_SUCCESS;
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            hex_Dealloc(
        OBJ_ID          objId
    )
    {
        HEX_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !hex_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((HEX_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         hex_Disable(
        HEX_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return this->eRc;
        }
    #ifdef NDEBUG
    #else
        if( !hex_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         hex_Enable(
        HEX_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !hex_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    HEX_DATA *   hex_Init(
        HEX_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(HEX_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_HEX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_HEX);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&hex_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !hex_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         hex_IsEnabled(
        HEX_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !hex_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            this->eRc = ERESULT_SUCCESS_TRUE;
            return this->eRc;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS_FALSE;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     P u t  1 6  B y t e s
    //---------------------------------------------------------------
    
    uint32_t        hex_put16Bytes_32(
        HEX_DATA		*this,
        uint32_t        offset,
        uint32_t        cData,
        const
        uint8_t         *pData,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // Ascii representation of digit stored
        //                                  // at ptr and ptr is advanced
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        
        // Print the byte.
        this->pLen = pLen;
        this->ppBuffer = ppBuffer;
        len = hex_putBytes16Obj(this, false, offset, cData, pData, this, (void *)hex_putChar );
        
        // Return to caller.
        return len;
    }
    
    
    uint32_t        hex_put16BytesObj_32(
        HEX_DATA		*this,
        uint32_t        offset,
        uint32_t        cData,
        const
        uint8_t         *pData,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        
        // Print the bytes.
        len = hex_putBytes16Obj(this, false, offset, cData, pData, pObject,  pPutChar);
        
        // Return to caller.
        return len;
    }
    
    
    uint32_t        hex_put16Bytes_64(
        HEX_DATA		*this,
        uint64_t        offset,
        uint32_t        cData,
        const
        uint8_t         *pData,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // Ascii representation of digit stored
        //                                  // at ptr and ptr is advanced
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        
        // Print the byte.
        this->pLen = pLen;
        this->ppBuffer = ppBuffer;
        len = hex_putBytes16Obj(this, true, offset, cData, pData, this, (void *)hex_putChar );
        
        // Return to caller.
        return len;
    }
    
    
    uint32_t        hex_put16BytesObj_64(
        HEX_DATA		*this,
        uint64_t        offset,
        uint32_t        cData,
        const
        uint8_t         *pData,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        
        // Print the bytes.
        len = hex_putBytes16Obj(this, true, offset, cData, pData, pObject,  pPutChar);
        
        // Return to caller.
        return len;
    }
    
    
    
    //---------------------------------------------------------------
    //                     P u t  U 8
    //---------------------------------------------------------------
    
    uint32_t        hex_putU8A(
        HEX_DATA		*this,
        uint8_t	        input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // Ascii representation of digit stored
        //                                  // at ptr and ptr is advanced
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        
        // Print the byte.
        this->pLen = pLen;
        this->ppBuffer = ppBuffer;
        len = hex_putU8Obj( this, input, this, (void *)hex_putChar );
        
        // Return to caller.
        return len;
    }
    
    
    uint32_t        hex_putU8Obj(
        HEX_DATA		*this,
        uint8_t	        input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        
        // Print the byte.
        len += hex_putDigit( this, (uint8_t)(input >> 4), pObject, pPutChar );
        len += hex_putDigit( this, input, pObject, pPutChar );
        
        // Return to caller.
        return len;
    }
    
    
    
    //---------------------------------------------------------------
    //                     P u t  U 1 6
    //---------------------------------------------------------------
    
    uint32_t        hex_putU16A(
        HEX_DATA		*this,
        uint16_t	    input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // Ascii representation of digit stored
        //                                  // at ptr and ptr is advanced
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        if (pLen && (*pLen < 4)) {
            return 0;
        }
        
        // Print the byte.
        this->pLen = pLen;
        this->ppBuffer = ppBuffer;
        len = hex_putU16Obj( this, input, this, (void *)hex_putChar );
        
        // Return to caller.
        return len;
    }
    
    
    uint32_t        hex_putU16Obj(
        HEX_DATA		*this,
        uint16_t	    input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        
        // Print the byte.
        len += hex_putDigit( this, (uint8_t)(input >> 12), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 8), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 4), pObject, pPutChar );
        len += hex_putDigit( this, input, pObject, pPutChar );
        
        // Return to caller.
        return len;
    }
    
    
    
    //---------------------------------------------------------------
    //                     P u t  U 2 4
    //---------------------------------------------------------------
    
    uint32_t        hex_putU24A(
        HEX_DATA		*this,
        uint32_t	    input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // Ascii representation of digit stored
        //                                  // at ptr and ptr is advanced
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        if (pLen && (*pLen < 6)) {
            return 0;
        }
        
        // Print the byte.
        this->pLen = pLen;
        this->ppBuffer = ppBuffer;
        len = hex_putU24Obj( this, input, this, (void *)hex_putChar );
        
        // Return to caller.
        return len;
    }
    
    
    uint32_t        hex_putU24Obj(
        HEX_DATA		*this,
        uint32_t	    input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        
        // Print the byte.
        len += hex_putDigit( this, (uint8_t)(input >> 20), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 16), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 12), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 8), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 4), pObject, pPutChar );
        len += hex_putDigit( this, input, pObject, pPutChar );
        
        // Return to caller.
        return len;
    }
    
    
    
    //---------------------------------------------------------------
    //                     P u t  U 3 2
    //---------------------------------------------------------------
    
    uint32_t        hex_putU32A(
        HEX_DATA		*this,
        uint32_t	    input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // Ascii representation of digit stored
        //                                  // at ptr and ptr is advanced
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        if (pLen && (*pLen < 8)) {
            return 0;
        }
        
        // Print the byte.
        this->pLen = pLen;
        this->ppBuffer = ppBuffer;
        len = hex_putU32Obj( this, input, this, (void *)hex_putChar );
        
        // Return to caller.
        return len;
    }
    
    
    uint32_t        hex_putU32Obj(
        HEX_DATA		*this,
        uint32_t	    input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        
        // Print the byte.
        len += hex_putDigit( this, (uint8_t)(input >> 28), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 24), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 20), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 16), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 12), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 8), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 4), pObject, pPutChar );
        len += hex_putDigit( this, input, pObject, pPutChar );
        
        // Return to caller.
        return len;
    }
    
    
    
    //---------------------------------------------------------------
    //                     P u t  U 6 4 A
    //---------------------------------------------------------------
    
    uint32_t        hex_putU64A(
        HEX_DATA		*this,
        uint64_t	    input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // Ascii representation of digit stored
        //                                  // at ptr and ptr is advanced
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        if (pLen && (*pLen < 16)) {
            return 0;
        }
        
        // Print the byte.
        this->pLen = pLen;
        this->ppBuffer = ppBuffer;
        len = hex_putU64Obj( this, input, this, (void *)hex_putChar );
        
        // Return to caller.
        return len;
    }
    
    
    uint32_t        hex_putU64Obj(
        HEX_DATA		*this,
        uint64_t	    input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        
        // Print the byte.
        len += hex_putDigit( this, (uint8_t)(input >> 60), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 56), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 52), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 48), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 44), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 40), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 36), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 32), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 28), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 24), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 20), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 16), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 12), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 8), pObject, pPutChar );
        len += hex_putDigit( this, (uint8_t)(input >> 4), pObject, pPutChar );
        len += hex_putDigit( this, input, pObject, pPutChar );
        
        // Return to caller.
        return len;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = hex_ToDebugString(this,4);
     @endcode:
     @param:    this    HEX object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     hex_ToDebugString(
        HEX_DATA        *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(hex) size=%d\n",
                     this,
                     hex_getSize(this)
            );
        AStr_AppendA(pStr, str);

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
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(hex)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            hex_Validate(
        HEX_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_HEX) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(HEX_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


