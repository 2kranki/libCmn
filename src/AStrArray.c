// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   AStrArray.c
 *	Copied from NodeArray 09/25/2015
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
#include "AStrArray_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    ASTRARRAY_DATA *     AStrArray_Alloc(
    )
    {
        ASTRARRAY_DATA       *this;
        uint32_t        cbSize = sizeof(ASTRARRAY_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ASTRARRAY_DATA *     AStrArray_New(
    )
    {
        ASTRARRAY_DATA       *this;
        
        // Do initialization.
        
        this = AStrArray_Alloc( );
        if (this) {
            this = AStrArray_Init(this);
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    OBJARRAY_DATA *  AStrArray_getArray(
        ASTRARRAY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pArray;
    }
    
    
    bool            AStrArray_setArray(
        ASTRARRAY_DATA  *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pArray) {
            obj_Release(this->pArray);
        }
        this->pArray = pValue;
        
        return true;
    }
    
    
    
    uint32_t        AStrArray_getSize(
        ASTRARRAY_DATA  *this
    )
    {
        uint32_t        i = 0;
        
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (this->pArray) {
            i = objArray_getSize(this->pArray);
        }
        return i;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         AStrArray_AppendStr(
        ASTRARRAY_DATA	*this,
        ASTR_DATA       *pObject,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (OBJ_NIL == this->pArray) {
            this->pArray = objArray_New();
            if (OBJ_NIL == this->pArray) {
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        eRc = objArray_AppendObj(this->pArray, pObject, pIndex);
        
        // Return to caller.
        return eRc;
    }

    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            AStrArray_Dealloc(
        OBJ_ID          objId
    )
    {
        ASTRARRAY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pArray) {
            obj_Release(this->pArray);
            this->pArray = OBJ_NIL;
        }

        obj_setVtbl(this, (OBJ_IUNKNOWN *)this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                        D e l e t e
    //---------------------------------------------------------------
    
    ASTR_DATA *     AStrArray_DeleteFirst(
        ASTRARRAY_DATA	*this
    )
    {
        ASTR_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_DeleteFirst(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    ASTR_DATA *     AStrArray_DeleteLast(
        ASTRARRAY_DATA	*this
    )
    {
        ASTR_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_DeleteLast(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                        G e t
    //---------------------------------------------------------------
    
    ASTR_DATA *     AStrArray_Get(
        ASTRARRAY_DATA	*this,
        uint32_t        index       // Relative to 1
    )
    {
        ASTR_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_Get(this->pArray,index);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    ASTR_DATA *     AStrArray_GetFirst(
        ASTRARRAY_DATA	*this
    )
    {
        ASTR_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_GetFirst(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    ASTR_DATA *     AStrArray_GetLast(
        ASTRARRAY_DATA	*this
    )
    {
        ASTR_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_GetLast(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ASTRARRAY_DATA * AStrArray_Init(
        ASTRARRAY_DATA  *this
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_NODEARRAY );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&AStrArray_Vtbl);
        
        //this->stackSize = obj_getMisc1(cbp);

    #ifdef NDEBUG
    #else
        if( !AStrArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         AStrArray_InsertStr(
        ASTRARRAY_DATA	*this,
        uint32_t        index,
        ASTR_DATA       *pObject
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (OBJ_NIL == this->pArray) {
            this->pArray = objArray_New();
            if (OBJ_NIL == this->pArray) {
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        eRc = objArray_InsertObj(this->pArray, index, pObject);
        
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
     void        *pMethod = node_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode
     @param     objId   OBJTEST object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
     for OBJ_QUERYINFO_TYPE_METHOD, this field points to a
     character string which represents the method name without
     the object name, "node", prefix,
     for OBJ_QUERYINFO_TYPE_PTR, this field contains the
     address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
     OBJ_QUERYINFO_TYPE_INFO: info pointer,
     OBJ_QUERYINFO_TYPE_METHOD: method pointer,
     OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          AStrArray_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        ASTRARRAY_DATA  *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
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
                        
#ifdef XYZZY
                    case 'A':
                        if (str_Compare("Accept", (char *)pStr) == 0) {
                            return node_Accept;
                        }
                        break;
#endif
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return AStrArray_ToDebugString;
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
    //                         S o r t
    //---------------------------------------------------------------
    
    ERESULT         AStrArray_SortAscending(
        ASTRARRAY_DATA	*this
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        eRc = objArray_SortAscending(this->pArray, (OBJ_COMPARE)&AStr_Compare);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = AStrArray_ToDebugString(this, 4);
     @endcode
     @param     this    ASTRARRAY_DATA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     AStrArray_ToDebugString(
        ASTRARRAY_DATA  *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pInfo = AStrArray_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                               pStr,
                               "{%p(%s) size=%d\n",
                               this,
                               pInfo->pClassName,
                               AStrArray_getSize(this)
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
    bool            AStrArray_Validate(
        ASTRARRAY_DATA      *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_ASTRARRAY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(ASTRARRAY_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


