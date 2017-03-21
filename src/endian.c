// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   endian.c
 *	Generated 10/25/2016 14:29:27
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
#include "endian_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    static
    ENDIAN_DATA     singleton = {{0}};
    static
    ENDIAN_DATA     *pShared = OBJ_NIL;


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            endian_task_body(
        void            *pData
    )
    {
        //ENDIAN_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    ENDIAN_DATA *     endian_Alloc(
    )
    {
        ENDIAN_DATA       *this = &singleton;
        uint32_t        cbSize = sizeof(ENDIAN_DATA);
        
        // Do initialization.
        
        //this = obj_Alloc( cbSize );
        memset(this, 0, cbSize);
        
        // Return to caller.
        return this;
    }



    ENDIAN_DATA *     endian_New(
    )
    {
        
        if (pShared == OBJ_NIL) {
            pShared = endian_Alloc( );
            if (pShared) {
                pShared = endian_Init(pShared);
            }
        }
        return pShared;
    }



    ENDIAN_DATA *    endian_Shared(
    )
    {
        return endian_New();
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         endian_getLastError(
        ENDIAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !endian_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }



    uint16_t        endian_getPriority(
        ENDIAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !endian_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        this->eRc = ERESULT_SUCCESS;
        //return this->priority;
        return 0;
    }

    bool            endian_setPriority(
        ENDIAN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !endian_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        this->eRc = ERESULT_SUCCESS;
        return true;
    }



    uint32_t        endian_getSize(
        ENDIAN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !endian_Validate(this) ) {
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
        ERESULT eRc = endian__Assign(this,pOther);
     @endcode:
     @param:    this    ENDIAN object pointer
     @param:    pOther  a pointer to another ENDIAN object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         endian_Assign(
        ENDIAN_DATA		*this,
        ENDIAN_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( !endian_Validate(pOther) ) {
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
        endian      *pCopy = endian_Copy(this);
     @endcode:
     @param:    this    ENDIAN object pointer
     @return:   If successful, a ENDIAN object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the ENDIAN object.
     */
    ENDIAN_DATA *     endian_Copy(
        ENDIAN_DATA       *this
    )
    {
        ENDIAN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = endian_New( );
        if (pOther) {
            eRc = endian_Assign(this, pOther);
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

    void            endian_Dealloc(
        OBJ_ID          objId
    )
    {
        ENDIAN_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !endian_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((ENDIAN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
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

    ERESULT         endian_Disable(
        ENDIAN_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return this->eRc;
        }
    #ifdef NDEBUG
    #else
        if( !endian_Validate(this) ) {
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

    ERESULT         endian_Enable(
        ENDIAN_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !endian_Validate(this) ) {
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
    //                       G e t U 1 6
    //---------------------------------------------------------------
    
    uint16_t        endian_GetU16Big(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    )
    {
        uint16_t        value = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        value |= ((*pValue++ & 0xFF) << 8);
        value |= (*pValue++ & 0xFF);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return value;
    }
    
    
    uint16_t        endian_GetU16Little(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    )
    {
        uint16_t        value = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        value |= (*pValue++ & 0xFF);
        value |= ((*pValue++ & 0xFF) << 8);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return value;
    }
    

    
    //---------------------------------------------------------------
    //                       G e t U 2 4
    //---------------------------------------------------------------
    
    uint32_t        endian_GetU24Big(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    )
    {
        uint32_t        value = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        value |= ((*pValue++ & 0xFF) << 16);
        value |= ((*pValue++ & 0xFF) << 8);
        value |= (*pValue++ & 0xFF);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return value;
    }
    
    
    uint32_t        endian_GetU24Little(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    )
    {
        uint32_t        value = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        value |= (*pValue++ & 0xFF);
        value |= ((*pValue++ & 0xFF) << 8);
        value |= ((*pValue++ & 0xFF) << 16);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return value;
    }
    
    
    
    //---------------------------------------------------------------
    //                       G e t U 3 2
    //---------------------------------------------------------------
    
    uint32_t        endian_GetU32Big(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    )
    {
        uint32_t        value = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        value |= ((*pValue++ & 0xFF) << 24);
        value |= ((*pValue++ & 0xFF) << 16);
        value |= ((*pValue++ & 0xFF) << 8);
        value |= (*pValue++ & 0xFF);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return value;
    }
    
    
    uint32_t        endian_GetU32Little(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    )
    {
        uint32_t        value = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        value |= (*pValue++ & 0xFF);
        value |= ((*pValue++ & 0xFF) << 8);
        value |= ((*pValue++ & 0xFF) << 16);
        value |= ((*pValue++ & 0xFF) << 24);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return value;
    }
    
    
    
    //---------------------------------------------------------------
    //                       G e t U 6 4
    //---------------------------------------------------------------
    
    uint64_t        endian_GetU64Big(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    )
    {
        uint64_t        value = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        value |= ((uint64_t)(*pValue++ & 0xFF) << 56);
        value |= ((uint64_t)(*pValue++ & 0xFF) << 48);
        value |= ((uint64_t)(*pValue++ & 0xFF) << 40);
        value |= ((uint64_t)(*pValue++ & 0xFF) << 32);
        value |= ((*pValue++ & 0xFF) << 24);
        value |= ((*pValue++ & 0xFF) << 16);
        value |= ((*pValue++ & 0xFF) << 8);
        value |= (*pValue++ & 0xFF);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return value;
    }
    
    
    uint64_t        endian_GetU64Little(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    )
    {
        uint64_t        value = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        value |= (*pValue++ & 0xFF);
        value |= ((*pValue++ & 0xFF) << 8);
        value |= ((*pValue++ & 0xFF) << 16);
        value |= ((*pValue++ & 0xFF) << 24);
        value |= ((uint64_t)(*pValue++ & 0xFF) << 32);
        value |= ((uint64_t)(*pValue++ & 0xFF) << 40);
        value |= ((uint64_t)(*pValue++ & 0xFF) << 48);
        value |= ((uint64_t)(*pValue++ & 0xFF) << 56);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return value;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ENDIAN_DATA *   endian_Init(
        ENDIAN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(ENDIAN_DATA);
        uint16_t        num16 = 258;    // 0x0102
        uint8_t         *pByte = (uint8_t *)&num16;
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_ENDIAN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_ENDIAN);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&endian_Vtbl);

        if (*pByte == 0x02) {
            this->fLittle = true;
        }
        else {
            this->fLittle = false;
        }

    #ifdef NDEBUG
    #else
        if( !endian_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       P u t U 1 6
    //---------------------------------------------------------------
    
    ERESULT         endian_PutU16Big(
        ENDIAN_DATA     *this,
        uint16_t        value,          // In
        uint8_t         *pValue         // Out 2-Byte output area
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        *pValue++ = (value >> 8) & 0xFF;
        *pValue++ = value & 0xFF;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    ERESULT         endian_PutU16Little(
        ENDIAN_DATA     *this,
        uint16_t        value,          // In
        uint8_t         *pValue         // Out 2-Byte output area
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        *pValue++ = value & 0xFF;
        *pValue++ = (value >> 8) & 0xFF;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       P u t U 2 4
    //---------------------------------------------------------------
    
    ERESULT         endian_PutU24Big(
        ENDIAN_DATA     *this,
        uint32_t        value,          // In
        uint8_t         *pValue         // Out 4-Byte output area
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        *pValue++ = (value >> 16) & 0xFF;
        *pValue++ = (value >> 8) & 0xFF;
        *pValue++ = value & 0xFF;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    ERESULT         endian_PutU24Little(
        ENDIAN_DATA     *this,
        uint32_t        value,          // In
        uint8_t         *pValue         // Out 4-Byte output area
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        *pValue++ = value & 0xFF;
        *pValue++ = (value >> 8) & 0xFF;
        *pValue++ = (value >> 16) & 0xFF;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       P u t U 3 2
    //---------------------------------------------------------------
    
    ERESULT         endian_PutU32Big(
        ENDIAN_DATA     *this,
        uint32_t        value,          // In
        uint8_t         *pValue         // Out 4-Byte output area
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        *pValue++ = (value >> 24) & 0xFF;
        *pValue++ = (value >> 16) & 0xFF;
        *pValue++ = (value >> 8) & 0xFF;
        *pValue++ = value & 0xFF;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    ERESULT         endian_PutU32Little(
        ENDIAN_DATA     *this,
        uint32_t        value,          // In
        uint8_t         *pValue         // Out 4-Byte output area
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        *pValue++ = value & 0xFF;
        *pValue++ = (value >> 8) & 0xFF;
        *pValue++ = (value >> 16) & 0xFF;
        *pValue++ = (value >> 24) & 0xFF;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       P u t U 6 4
    //---------------------------------------------------------------
    
    ERESULT         endian_PutU64Big(
        ENDIAN_DATA     *this,
        uint64_t        value,          // In
        uint8_t         *pValue         // Out 8-Byte output area
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        *pValue++ = (value >> 56) & 0xFF;
        *pValue++ = (value >> 48) & 0xFF;
        *pValue++ = (value >> 40) & 0xFF;
        *pValue++ = (value >> 32) & 0xFF;
        *pValue++ = (value >> 24) & 0xFF;
        *pValue++ = (value >> 16) & 0xFF;
        *pValue++ = (value >> 8) & 0xFF;
        *pValue++ = value & 0xFF;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    ERESULT         endian_PutU64Little(
        ENDIAN_DATA     *this,
        uint64_t        value,          // In
        uint8_t         *pValue         // Out 8-Byte output area
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !endian_Validate( this ) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        *pValue++ = value & 0xFF;
        *pValue++ = (value >> 8) & 0xFF;
        *pValue++ = (value >> 16) & 0xFF;
        *pValue++ = (value >> 24) & 0xFF;
        *pValue++ = (value >> 32) & 0xFF;
        *pValue++ = (value >> 40) & 0xFF;
        *pValue++ = (value >> 48) & 0xFF;
        *pValue++ = (value >> 56) & 0xFF;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = endian_ToDebugString(this,4);
     @endcode:
     @param:    this    ENDIAN object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     endian_ToDebugString(
        ENDIAN_DATA      *this,
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
                     "{%p(endian) machine==%s-endian \n",
                     this,
                     this->fLittle ? "Little" : "Big"
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
        j = snprintf(str, sizeof(str), " %p(endian)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            endian_Validate(
        ENDIAN_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_ENDIAN) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(ENDIAN_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


