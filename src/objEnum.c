// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   objEnum.c
 *	Generated 10/15/2017 09:38:35
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
#include <objEnum_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            objEnum_task_body(
        void            *pData
    )
    {
        //OBJENUM_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJENUM_DATA *     objEnum_Alloc(
    )
    {
        OBJENUM_DATA    *this;
        uint32_t        cbSize = sizeof(OBJENUM_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJENUM_DATA *     objEnum_New(
    )
    {
        OBJENUM_DATA       *this;
        
        this = objEnum_Alloc( );
        if (this) {
            this = objEnum_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A r r a y
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * objEnum_getArray(
        OBJENUM_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        objEnum_setLastError(this, ERESULT_SUCCESS);
        return this->pArray;
    }
    
    
    bool            objEnum_setArray(
        OBJENUM_DATA    *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pArray) {
            obj_Release(this->pArray);
        }
        this->pArray = pValue;
        
        objEnum_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         objEnum_getLastError(
        OBJENUM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            objEnum_setLastError(
        OBJENUM_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        objEnum_getPriority(
        OBJENUM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        objEnum_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            objEnum_setPriority(
        OBJENUM_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        objEnum_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        objEnum_getSize(
        OBJENUM_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        objEnum_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         objEnum_Append(
        OBJENUM_DATA    *this,
        OBJ_ID          pObject
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pObject) {
            DEBUG_BREAK();
            objEnum_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            objEnum_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_GENERAL_FAILURE;
        }
#endif
        
        eRc = objArray_AppendObj(this->pArray, pObject, NULL);
        
        objEnum_setLastError(this, eRc);
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
        ERESULT eRc = objEnum__Assign(this,pOther);
     @endcode
     @param     this    OBJENUM object pointer
     @param     pOther  a pointer to another OBJENUM object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         objEnum_Assign(
        OBJENUM_DATA	*this,
        OBJENUM_DATA    *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !objEnum_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
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

        // Copy other data from this object to other.
        pOther->current = this->current;
        
        //goto eom;

        // Return to caller.
        objEnum_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        objEnum_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return objEnum_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        objEnum      *pCopy = objEnum_Copy(this);
     @endcode
     @param     this    OBJENUM object pointer
     @return    If successful, a OBJENUM object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the OBJENUM object.
     */
    OBJENUM_DATA *  objEnum_Copy(
        OBJENUM_DATA    *this
    )
    {
        OBJENUM_DATA    *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = objEnum_New( );
        if (pOther) {
            eRc = objEnum_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        objEnum_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            objEnum_Dealloc(
        OBJ_ID          objId
    )
    {
        OBJENUM_DATA    *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return;
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
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         objEnum_Disable(
        OBJENUM_DATA	*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            objEnum_setLastError(this, ERESULT_INVALID_OBJECT);
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return objEnum_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        objEnum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         objEnum_Enable(
        OBJENUM_DATA	*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        objEnum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJENUM_DATA *   objEnum_Init(
        OBJENUM_DATA     *this
    )
    {
        uint32_t        cbSize = sizeof(OBJENUM_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_OBJENUM);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_OBJENUM);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&objEnum_Vtbl);
        
        objEnum_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "offsetof(eRc) = %lu\n", offsetof(OBJENUM_DATA,eRc));
        //fprintf(stderr, "sizeof(OBJENUM_DATA) = %lu\n", sizeof(OBJENUM_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(OBJENUM_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         objEnum_IsEnabled(
        OBJENUM_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            objEnum_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        objEnum_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L o o k  A h e a d
    //---------------------------------------------------------------
    
    ERESULT         objEnum_LookAhead(
        OBJENUM_DATA    *this,
        uint32_t        offset,
        void            **ppObject
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            //objEnum_setLastError(this, ERESULT_INVALID_OBJECT);
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == ppObject) {
            DEBUG_BREAK();
            objEnum_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (obj_Flag(this, OBJENUM_SORTED))
            ;
        else {
            eRc = objArray_SortAscending(this->pArray, NULL);
            obj_FlagOn(this, OBJENUM_SORTED);
        }
        
        if ((this->current + offset) < objArray_getSize(this->pArray)) {
        }
        else {
            objEnum_setLastError(this, ERESULT_OUT_OF_RANGE);
            return ERESULT_OUT_OF_RANGE;
        }
        
        *ppObject = objArray_Get(this->pArray, (this->current + offset + 1));
        
        objEnum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          N e x t
    //---------------------------------------------------------------
    
    ERESULT         objEnum_Next(
        OBJENUM_DATA    *this,
        uint32_t        cElems,
        OBJ_ID          *ppArray,
        uint32_t        *pReturnAmt
    )
    {
        ERESULT         eRc;
        uint32_t        count = 0;
        OBJ_ID          pObj;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == ppArray) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (obj_Flag(this, OBJENUM_SORTED))
            ;
        else {
            eRc = objArray_SortAscending(this->pArray, NULL);
            obj_FlagOn(this, OBJENUM_SORTED);
        }
        
        if (this->current < objArray_getSize(this->pArray)) {
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
            if( this->current < objArray_getSize(this->pArray) )
                ;
            else
                break;
            pObj = objArray_Get(this->pArray, (this->current + 1));
            if( OBJ_NIL == pObj )
                ;
            else {
                ppArray[count] = pObj;
                ++count;
            }
            this->current += 1;
        }
        
        if (pReturnAmt) {
            *pReturnAmt = count;
        }
        objEnum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          objEnum_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJENUM_DATA    *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
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
                            return objEnum_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return objEnum_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return objEnum_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return objEnum_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      R e m a i n i n g
    //---------------------------------------------------------------
    
    uint32_t        objEnum_Remaining(
        OBJENUM_DATA    *this
    )
    {
        uint32_t        count = 0;
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        count = objArray_getSize(this->pArray) - this->current;
        
        // Return to caller.
        objEnum_setLastError(this, ERESULT_SUCCESS);
        return count;
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e s e t
    //---------------------------------------------------------------
    
    ERESULT         objEnum_Reset(
        OBJENUM_DATA    *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        this->current = 0;
        
        // Return to caller.
        objEnum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S k i p
    //---------------------------------------------------------------
    
    ERESULT         objEnum_Skip(
        OBJENUM_DATA    *this,
        uint32_t        cElems
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        this->current += cElems;
        
        // Return to caller.
        objEnum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = objEnum_ToDebugString(this,4);
     @endcode:
     @param:    this    OBJENUM object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     objEnum_ToDebugString(
        OBJENUM_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(objEnum) size=%d\n",
                     this,
                     objEnum_getSize(this)
            );
        AStr_AppendA(pStr, str);

        if (this->pArray) {
            if (((OBJ_DATA *)(this->pArray))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pArray))->pVtbl->pToDebugString(
                                                    this->pArray,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(objEnum)}\n", this);
        AStr_AppendA(pStr, str);
        
        objEnum_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     objEnum_ToJSON(
        OBJENUM_DATA      *this
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !objEnum_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{\"objectType\":\"%s\"",
                     pInfo->pClassName
                     );
        AStr_AppendA(pStr, str);
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            objEnum_Validate(
        OBJENUM_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_OBJENUM) )
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


        if( !(obj_getSize(this) >= sizeof(OBJENUM_DATA)) ) {
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


