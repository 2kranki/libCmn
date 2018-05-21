// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   u12Array.c
 *	Generated 10/08/2016 21:04:05
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
#include "u12Array_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef NOT_NEEDED_YET
    static
    uint32_t        u12Array_OffsetOf(
        U12ARRAY_DATA   *this,
        uint32_t        index
    )
    {
        uint32_t        offset = 0;
        
        offset = ((index - 1) * 3) >> 1;
   
        return offset;
    }
#endif



    
    
    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    U12ARRAY_DATA *     u12Array_Alloc(
    )
    {
        U12ARRAY_DATA   *this;
        uint32_t        cbSize = sizeof(U12ARRAY_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    U12ARRAY_DATA *     u12Array_New(
    )
    {
        U12ARRAY_DATA       *this;
        
        this = u12Array_Alloc( );
        if (this) {
            this = u12Array_Init(this);
        } 
        return this;
    }



    U12ARRAY_DATA *     u12Array_NewFromData(
        uint32_t            cBuffer,
        uint8_t             *pBuffer
    )
    {
        U12ARRAY_DATA       *this = OBJ_NIL;
        ERESULT             eRc;
        
        if (cBuffer && ((cBuffer % 3) == 0) && pBuffer) {
            this = u12Array_Alloc( );
            if (this) {
                this = u12Array_Init(this);
                if (this) {
                    eRc = array_Expand(this->pArray, cBuffer);
                    if (ERESULT_FAILED(eRc)) {
                        obj_Release(this);
                        this = OBJ_NIL;
                    }
                    memmove(array_getData(this->pArray), pBuffer, cBuffer);
                }
            }
        }
        return this;
    }
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         u12Array_getLastError(
        U12ARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !u12Array_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }



    uint32_t        u12Array_getSize(
        U12ARRAY_DATA   *this
    )
    {
        uint32_t        size;
#ifdef NDEBUG
#else
        if( !u12Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        size = (array_getSize(this->pArray) / 3) * 2;
        
        this->eRc = ERESULT_SUCCESS;
        return size;
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
        ERESULT eRc = u12Array__Assign(this,pOther);
     @endcode:
     @param:    this    U12ARRAY object pointer
     @param:    pOther  a pointer to another U12ARRAY object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         u12Array_Assign(
        U12ARRAY_DATA		*this,
        U12ARRAY_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u12Array_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( !u12Array_Validate(pOther) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        // Release objects and areas in other object.
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
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
        u12Array      *pCopy = u12Array_Copy(this);
     @endcode:
     @param:    this    U12ARRAY object pointer
     @return:   If successful, a U12ARRAY object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the U12ARRAY object.
     */
    U12ARRAY_DATA *     u12Array_Copy(
        U12ARRAY_DATA       *this
    )
    {
        U12ARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u12Array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = u12Array_New( );
        if (pOther) {
            eRc = u12Array_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            u12Array_Dealloc(
        OBJ_ID          objId
    )
    {
        U12ARRAY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !u12Array_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((U12ARRAY_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pArray) {
            obj_Release(this->pArray);
            this->pArray = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------
    
    uint16_t        u12Array_Find(
        U12ARRAY_DATA   *this,
        uint16_t        value
    )
    {
        uint32_t        i;
        uint32_t        size = u12Array_getSize(this);
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u12Array_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        for (i=0; i<size; ++i) {
            if (value == u12Array_Get(this, i+1)) {
                break;
            }
        }
        if (i == size) {
            DEBUG_BREAK();
            this->eRc = ERESULT_DATA_MISSING;
            return 0xFFFF;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return i+1;
    }
    
    
    
    //---------------------------------------------------------------
    //                          G e t
    //---------------------------------------------------------------

    uint16_t        u12Array_Get(
        U12ARRAY_DATA	*this,
        uint32_t        index
    )
    {
        ERESULT         eRc;
        uint32_t        offset;         // in bytes
        uint16_t        entry;
        uint8_t         *pData;
        
#ifdef NDEBUG
#else
        if( !u12Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0xFFFF;
        }
        if (index == 0) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0xFFFF;
        }
#endif
        --index;
        
        // Index according to even or odd index numbers. Each 3 bytes
        // in the array contain two 12-bit entries as 4-bit entities:
        //      e1 e2 | o2 e0 | o0 o1
        // where 'e' is even addressed cluster number and 'o' is odd
        // addressed cluster number.
        offset = (3 * index) / 2;
        eRc = array_Expand(this->pArray, (offset + 2));
        if (ERESULT_FAILED(eRc)) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return 0xFFFF;
        }
        pData = array_Ptr(this->pArray, (offset + 1));
        if (NULL == pData) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0xFFFF;
        }
        if (index & 1) {
            entry  =  (*pData & 0xF0) >> 4;
            entry |=  ((*(pData+1) & 0xFF) << 4);
        }
        else {
            entry  =  (*(pData+1) & 0x0F) << 8;
            entry |= *pData;
        }
        
        this->eRc = ERESULT_SUCCESS;
        return entry;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    U12ARRAY_DATA *   u12Array_Init(
        U12ARRAY_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(U12ARRAY_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_U12ARRAY);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_U12ARRAY);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&u12Array_Vtbl);
        
        this->pArray = array_New(1);

    #ifdef NDEBUG
    #else
        if( !u12Array_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->pArray);
        BREAK_NOT_BOUNDARY4(sizeof(U12ARRAY_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          P u t
    //---------------------------------------------------------------
    
    ERESULT         u12Array_Put(
        U12ARRAY_DATA   *this,
        const
        uint32_t        index,
        const
        uint16_t        value
    )
    {
        ERESULT         eRc;
        uint32_t        offset;         // in bytes
        uint8_t         *pData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u12Array_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if (index == 0) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        // Index according to even or odd cluster numbers. Each 3 bytes
        // in the FAT contain two 12-bit entries as 4-bit entities:
        //      e1 e2 | o2 e0 | o0 o1
        // where e is even addressed cluster number and o is odd addressed
        // cluster number.
        offset = (3 * (index - 1)) / 2;
        eRc = array_Expand(this->pArray, (offset + 2));
        if (ERESULT_FAILED(eRc)) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return ERESULT_OUT_OF_MEMORY;
        }
        pData = array_Ptr(this->pArray, (offset + 1));
        if (NULL == pData) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return ERESULT_INVALID_PARAMETER;
        }
        if ((index - 1) & 1) {    // odd
            *pData = (*pData & 0x0F) | ((value & 0x000F) << 4);
            *(pData + 1) = (value & 0x0FF0) >> 4;
        }
        else {                      // even
            *pData = (value & 0x00FF);
            *(pData + 1) = (*(pData + 1) & 0xF0) | ((value & 0x0F00) >> 8);
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = u12Array_ToDebugString(this,4);
     @endcode:
     @param:    this    U12ARRAY object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     u12Array_ToDebugString(
        U12ARRAY_DATA      *this,
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
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(u12Array) size=%d\n",
                     this,
                     u12Array_getSize(this)
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
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(u12Array)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            u12Array_Validate(
        U12ARRAY_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_U12ARRAY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(U12ARRAY_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


