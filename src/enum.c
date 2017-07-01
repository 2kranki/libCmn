// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   enum.c
 *	Generated 06/30/2017 09:01:13
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
#include <enum_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    ERESULT         enum_ExpandArray(
        ENUM_DATA       *this,
        uint32_t        num
    )
    {
        void            *pWork;
        uint32_t        oldMax;
        uint32_t        cbSize;
        uint16_t        elemSize = sizeof(uint8_t *);
        
        // Do initialization.
        if( this == NULL ) {
            return ERESULT_INVALID_OBJECT;
        }
        if (num < this->max) {
            enum_setLastError(this, ERESULT_SUCCESS);
            return ERESULT_SUCCESS;
        }
        
        // Expand the Array.
        oldMax = this->max;
        if (0 == oldMax) {
            oldMax = 1;
        }
        this->max = oldMax << 1;             // max *= 2
        while (num > this->max) {
            this->max = this->max << 1;
        }
        cbSize = this->max * elemSize;
        pWork = (void *)mem_Malloc( cbSize );
        if( NULL == pWork ) {
            this->max = oldMax;
            enum_setLastError(this, ERESULT_INSUFFICIENT_MEMORY);
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        // Copy the old entries into the new array.
        if( this->ppArray == NULL )
            ;
        else {
            memmove( pWork, this->ppArray, (oldMax * elemSize) );
            mem_Free(this->ppArray);
            // this->ppArray = NULL;
        }
        this->ppArray = pWork;
        memset(&this->ppArray[oldMax], 0, ((this->max - oldMax) * elemSize));
        
        // Return to caller.
        enum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    ENUM_DATA *     enum_Alloc(
    )
    {
        ENUM_DATA       *this;
        uint32_t        cbSize = sizeof(ENUM_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ENUM_DATA *     enum_New(
    )
    {
        ENUM_DATA       *this;
        
        this = enum_Alloc( );
        if (this) {
            this = enum_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         enum_getLastError(
        ENUM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            enum_setLastError(
        ENUM_DATA       *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        enum_getPriority(
        ENUM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        enum_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            enum_setPriority(
        ENUM_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        enum_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        enum_getSize(
        ENUM_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        enum_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         enum_Append(
        ENUM_DATA       *this,
        void            *pObject,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pObject) {
            DEBUG_BREAK();
            enum_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        ++this->size;
        while (this->size > this->max) {
            eRc = enum_ExpandArray(this, this->size);
            if (ERESULT_HAS_FAILED(eRc)) {
                DEBUG_BREAK();
                return eRc;
            }
        }
        this->ppArray[this->size - 1] = (uint8_t *)pObject;
        if (pIndex) {
            *pIndex = this->size;
        }
        
        enum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code:
        ERESULT eRc = enum__Assign(this,pOther);
     @endcode:
     @param:    this    ENUM object pointer
     @param:    pOther  a pointer to another ENUM object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         enum_Assign(
        ENUM_DATA       *this,
        ENUM_DATA       *pOther
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !enum_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        if (pOther->ppArray) {
            mem_Free(pOther->ppArray);
            pOther->ppArray = OBJ_NIL;
            pOther->max = 0;
            pOther->size = 0;
            pOther->current = 0;
        }

        while (this->max > pOther->max) {
            eRc = enum_ExpandArray(pOther, this->max);
            if (ERESULT_HAS_FAILED(eRc)) {
                DEBUG_BREAK();
                return eRc;
            }
        }
        if (this->size < this->max) {
        }
        else {
            enum_setLastError(this, ERESULT_INVALID_POINTER);
            return ERESULT_INVALID_POINTER;
        }
        
        // Create a copy of objects and areas in this object placing
        // them in other.
        for (i=0; i<this->size; ++i) {
            pOther->ppArray[i] = this->ppArray[i];
        }
        pOther->size = this->size;

        // Return to caller.
        enum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        enum      *pCopy = enum_Copy(this);
     @endcode:
     @param:    this    ENUM object pointer
     @return:   If successful, a ENUM object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the ENUM object.
     */
    ENUM_DATA *     enum_Copy(
        ENUM_DATA       *this
    )
    {
        ENUM_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = enum_New( );
        if (pOther) {
            eRc = enum_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        enum_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            enum_Dealloc(
        OBJ_ID          objId
    )
    {
        ENUM_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->ppArray) {
            mem_Free(this->ppArray);
            this->ppArray = NULL;
            this->max = 0;
            this->size = 0;
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         enum_Disable(
        ENUM_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            enum_setLastError(this, ERESULT_INVALID_OBJECT);
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return enum_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        enum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         enum_Enable(
        ENUM_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        enum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ENUM_DATA *   enum_Init(
        ENUM_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(ENUM_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_ENUM);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_ENUM);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&enum_Vtbl);
        
        enum_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(ENUM_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         enum_IsEnabled(
        ENUM_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            enum_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        enum_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                          N e x t
    //---------------------------------------------------------------
    
    ERESULT         enum_Next(
        ENUM_DATA       *this,
        uint32_t        cElems,
        void            **ppArray,
        uint32_t        *pReturnAmt
    )
    {
        uint32_t        count = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == ppArray) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == this->ppArray) {
            DEBUG_BREAK();
            return ERESULT_INVALID_POINTER;
        }
#endif
        
        if (this->current < this->size) {
        }
        else {
            if (pReturnAmt) {
                *pReturnAmt = 0;
            }
            return ERESULT_OUT_OF_RANGE;
        }

        for( ;; ) {
            if( count < cElems )
                ;
            else
                break;
            if( this->current < this->size )
                ;
            else
                break;
            if( NULL == this->ppArray[this->current] )
                ;
            else {
                ppArray[count] = this->ppArray[this->current];
                ++count;
            }
            ++this->current;
        }
        
        if (pReturnAmt) {
            *pReturnAmt = count;
        }
        enum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          enum_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    )
    {
        ENUM_DATA   *this = objId;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return enum_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Ensable", (char *)pStr) == 0) {
                            return enum_Enable;
                        }
                        break;

                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pStr);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e s e t
    //---------------------------------------------------------------
    
    ERESULT         enum_Reset(
        ENUM_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        this->current = 0;
        
        // Return to caller.
        enum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S k i p
    //---------------------------------------------------------------
    
    ERESULT         enum_Skip(
        ENUM_DATA       *this,
        uint32_t        cElems
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        this->current += cElems;
        
        // Return to caller.
        enum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = enum_ToDebugString(this,4);
     @endcode:
     @param:    this    ENUM object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     enum_ToDebugString(
        ENUM_DATA       *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !enum_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(enum) size=%d\n",
                     this,
                     enum_getSize(this)
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
        j = snprintf(str, sizeof(str), " %p(enum)}\n", this);
        AStr_AppendA(pStr, str);
        
        enum_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            enum_Validate(
        ENUM_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_ENUM) )
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


        if( !(obj_getSize(this) >= sizeof(ENUM_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


