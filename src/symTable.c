// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   symTable.c
 *	Generated 03/27/2017 21:41:31
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
#include    <symTable_internal.h>
#include    <objEnum_internal.h>



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

    SYMTABLE_DATA * symTable_Alloc(
    )
    {
        SYMTABLE_DATA   *this;
        uint32_t        cbSize = sizeof(SYMTABLE_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SYMTABLE_DATA * symTable_New(
        uint16_t        cHash       // [in] Hash Table Size
    )
    {
        SYMTABLE_DATA   *this;
        
        this = symTable_Alloc( );
        if (this) {
            this = symTable_Init(this, cHash);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        symTable_getPriority(
        SYMTABLE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !symTable_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        obj_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            symTable_setPriority(
        SYMTABLE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !symTable_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        symTable_getSize(
        SYMTABLE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !symTable_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        obj_setLastError(this, ERESULT_SUCCESS);
        return objHash_getSize(this->pEntries);
    }




    
    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //----------------------------------------------------------
    //                          A d d
    //----------------------------------------------------------
    
    ERESULT         symTable_AddEntry(
        SYMTABLE_DATA   *this,
        OBJ_ID          pObject
    )
    {
        ERESULT         eRc;
        
#ifdef NDEBUG
#else
        if( !symTable_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pObject) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = objHash_Add(this->pEntries, pObject, NULL);
        
        // Return to caller.
        obj_setLastError(this, eRc);
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
     @code:
        ERESULT eRc = symTable__Assign(this,pOther);
     @endcode:
     @param     this    SYMTABLE object pointer
     @param     pOther  a pointer to another SYMTABLE object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         symTable_Assign(
        SYMTABLE_DATA		*this,
        SYMTABLE_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !symTable_Validate(this) ) {
            DEBUG_BREAK();
            return obj_getLastError(this);
        }
        if( !symTable_Validate(pOther) ) {
            DEBUG_BREAK();
            return obj_getLastError(pOther);
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
        
        //goto eom;

        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
    //eom:
        //FIXME: Implement the assignment.        
        obj_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return obj_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        symTable      *pCopy = symTable_Copy(this);
     @endcode
     @param     this    SYMTABLE object pointer
     @return    If successful, a SYMTABLE object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the SYMTABLE object.
     */
    SYMTABLE_DATA *     symTable_Copy(
        SYMTABLE_DATA       *this
    )
    {
        SYMTABLE_DATA       *pOther = OBJ_NIL;
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !symTable_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef XYZZY                    //FIXME: old hash stuff, replace with objHash
        pOther = symTable_New(this->cHash);
        if (pOther) {
            eRc = symTable_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        //obj_Release(pOther);
        obj_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            symTable_Dealloc(
        OBJ_ID          objId
    )
    {
        SYMTABLE_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !symTable_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if(this->pEntries) {
            obj_Release(this->pEntries);
            this->pEntries = OBJ_NIL;
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //----------------------------------------------------------
    //                      D e l e t e
    //----------------------------------------------------------
    
    OBJ_ID          symTable_DeleteEntry(
        SYMTABLE_DATA   *this,
        OBJ_ID          pObject
    )
    {
        OBJ_ID          pReturn = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !symTable_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pReturn = objHash_Delete(this->pEntries, pObject);
        
        // Return to caller.
        obj_setLastError(this, objHash_getLastError(this->pEntries));
        return pReturn;
    }
    
    
    ERESULT         symTable_DeleteAllEntries(
        SYMTABLE_DATA   *this
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !symTable_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = objHash_DeleteAll(this->pEntries);
        
        // Return to caller.
        obj_setLastError(this, eRc);
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      E n u m
    //---------------------------------------------------------------
    
    OBJENUM_DATA *  symTable_Enum(
        SYMTABLE_DATA   *this
    )
    {
        OBJENUM_DATA    *pEnum = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == this) {
            return pEnum;
        }
#ifdef NDEBUG
#else
        if( !symTable_Validate(this) ) {
            DEBUG_BREAK();
            return pEnum;
        }
#endif
        
        pEnum = objHash_Enum(this->pEntries);
        if (OBJ_NIL == pEnum) {
            eRc = ERESULT_OUT_OF_MEMORY;
            obj_setLastError(this, eRc);
            return OBJ_NIL;
        }
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return pEnum;
    }
    
    
    
    //----------------------------------------------------------
    //                        F i n d
    //----------------------------------------------------------
    
    OBJ_ID          symTable_Find(
        SYMTABLE_DATA   *this,
        OBJ_ID          pObject
    )
    {
        OBJ_ID          pReturn = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !symTable_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pReturn = objHash_Find(this->pEntries, pObject);
        
        // Return to caller.
        obj_setLastError(this, objHash_getLastError(this->pEntries));
        return pReturn;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SYMTABLE_DATA * symTable_Init(
        SYMTABLE_DATA   *this,
        uint16_t        cHash       // [in] Hash Table Size
    )
    {
        uint32_t        cbSize = sizeof(SYMTABLE_DATA);

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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SYMTABLE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_SYMTABLE);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&symTable_Vtbl);
        
        obj_setLastError(this, ERESULT_GENERAL_FAILURE);

        this->pEntries = objHash_New(cHash);
        if (OBJ_NIL == this->pEntries) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        objHash_setDuplicates(this->pEntries, true);

    #ifdef NDEBUG
    #else
        if( !symTable_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          symTable_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SYMTABLE_DATA   *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !symTable_Validate(this) ) {
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
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return hex_Disable;
                        }
                        break;
                        
                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return hex_Enable;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return hex_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return hex_ToJSON;
                        }
                        break;
#endif
                        
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
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = symTable_ToDebugString(this,4);
     @endcode
     @param     this    SYMTABLE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     symTable_ToDebugString(
        SYMTABLE_DATA      *this,
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
        if( !symTable_Validate(this) ) {
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
                     "{%p(symTable) size=%d\n",
                     this,
                     symTable_getSize(this)
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
        j = snprintf(str, sizeof(str), " %p(symTable)}\n", this);
        AStr_AppendA(pStr, str);
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            symTable_Validate(
        SYMTABLE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_SYMTABLE) )
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


        if( !(obj_getSize(this) >= sizeof(SYMTABLE_DATA)) ) {
            obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return false;
        }

        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


