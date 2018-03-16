// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   symEntry.c
 *	Generated 03/27/2017 21:41:19
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
#include "symEntry_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            symEntry_task_body(
        void            *pData
    )
    {
        //SYMENTRY_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SYMENTRY_DATA *     symEntry_Alloc(
    )
    {
        SYMENTRY_DATA       *this;
        uint32_t            cbSize = sizeof(SYMENTRY_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SYMENTRY_DATA *     symEntry_NewA(
        const
        char                *pName,
        int32_t             class
    )
    {
        SYMENTRY_DATA       *this;
        
        this = symEntry_Alloc( );
        if (this) {
            this = symEntry_Init(this);
            if (this) {
                if (pName) {
                    symEntry_setName(this, pName);
                }
                symEntry_setClass(this, class);
            }
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A t t r
    //---------------------------------------------------------------
    
    SYMATTR_DATA *  symEntry_getAttr(
        SYMENTRY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        this->eRc = ERESULT_SUCCESS;
        return this->pAttr;
    }
    
    
    bool        symEntry_setAttr(
        SYMENTRY_DATA   *this,
        SYMATTR_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pAttr) {
            obj_Release(this->pAttr);
        }
        this->pAttr = pValue;
        
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C l a s s
    //---------------------------------------------------------------
    
    int32_t         symEntry_getClass(
        SYMENTRY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        if (NULL == this->pEntry) {
            DEBUG_BREAK();
            symEntry_setLastError(this, ERESULT_DATA_MISSING);
            return -1;
        }
        
        return this->pEntry->cls;
    }
    
    
    bool            symEntry_setClass(
        SYMENTRY_DATA   *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (NULL == this->pEntry) {
            DEBUG_BREAK();
            symEntry_setLastError(this, ERESULT_DATA_MISSING);
            return -1;
        }
        
        this->pEntry->cls = value;
        
        symEntry_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------
    
    uint32_t        symEntry_getHash(
        SYMENTRY_DATA   *this
    )
    {
        uint32_t        hash = 0;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        if (NULL == this->pEntry) {
            DEBUG_BREAK();
            symEntry_setLastError(this, ERESULT_DATA_MISSING);
            return -1;
        }
        
        hash = szTbl_TokenToHash(OBJ_NIL, this->pEntry->nameToken);

        symEntry_setLastError(this, ERESULT_SUCCESS);
        return hash;
    }
    
    
    ERESULT         symEntry_getLastError(
        SYMENTRY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            symEntry_setLastError(
        SYMENTRY_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                          N a m e
    //---------------------------------------------------------------
    
    const
    char *          symEntry_getName(
        SYMENTRY_DATA   *this
    )
    {
        const
        char            *pStr = NULL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        if (NULL == this->pEntry) {
            DEBUG_BREAK();
            symEntry_setLastError(this, ERESULT_DATA_MISSING);
            return NULL;
        }

        pStr = szTbl_TokenToString(OBJ_NIL, this->pEntry->nameToken);
        
        symEntry_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    bool            symEntry_setName(
        SYMENTRY_DATA   *this,
        const
        char            *pValue
    )
    {
        uint32_t        token;
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (NULL == this->pEntry) {
            DEBUG_BREAK();
            symEntry_setLastError(this, ERESULT_DATA_MISSING);
            return NULL;
        }

        token = szTbl_StringToToken(OBJ_NIL, pValue);
        this->pEntry->nameToken = token;
        
        symEntry_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    uint32_t        symEntry_getSize(
        SYMENTRY_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        symEntry_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }
    
    
    
    //---------------------------------------------------------------
    //                          T o k e n
    //---------------------------------------------------------------
    
    uint32_t        symEntry_getToken(
        SYMENTRY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        if (NULL == this->pEntry) {
            DEBUG_BREAK();
            symEntry_setLastError(this, ERESULT_DATA_MISSING);
            return -1;
        }
        
        return this->pEntry->nameToken;
    }
    
    
    bool            symEntry_setToken(
        SYMENTRY_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (NULL == this->pEntry) {
            DEBUG_BREAK();
            symEntry_setLastError(this, ERESULT_DATA_MISSING);
            return -1;
        }
        
        this->pEntry->nameToken = value;
        
        symEntry_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          T y p e
    //---------------------------------------------------------------
    
    int32_t         symEntry_getType(
        SYMENTRY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        if (NULL == this->pEntry) {
            DEBUG_BREAK();
            symEntry_setLastError(this, ERESULT_DATA_MISSING);
            return -1;
        }
        
        return this->pEntry->type;
    }
    
    
    bool            symEntry_setType(
        SYMENTRY_DATA   *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (NULL == this->pEntry) {
            DEBUG_BREAK();
            symEntry_setLastError(this, ERESULT_DATA_MISSING);
            return -1;
        }
        
        this->pEntry->type = value;
        
        symEntry_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        A c c e p t
    //---------------------------------------------------------------
    
    ERESULT         symEntry_Accept(
        SYMENTRY_DATA    *this,
        VISITOR_DATA     *pVisitor
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        ERESULT         (*pMethod)(VISITOR_DATA *this, SYMENTRY_DATA *pObj) = NULL;
        const
        OBJ_IUNKNOWN    *pVtbl;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !symEntry_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pVisitor ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pStr = AStr_NewA("Visit_symEntry_");
        if (OBJ_NIL == pStr) {
            return ERESULT_OUT_OF_MEMORY;
        }
        AStr_AppendHex32(pStr, this->pEntry->type);
        
        pVtbl = obj_getVtbl(pVisitor);
        if (pVtbl && pVtbl->pQueryInfo) {
            pMethod =   pVtbl->pQueryInfo(
                                          pVisitor,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          (void *)AStr_getData(pStr)
                                          );
        }
        
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        if (NULL == pMethod) {
            DEBUG_BREAK();
            return ERESULT_INVALID_FUNCTION;
        }
        
        eRc = pMethod(pVisitor, this);
        
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
        ERESULT eRc = symEntry__Assign(this,pOther);
     @endcode
     @param     this    SYMENTRY object pointer
     @param     pOther  a pointer to another SYMENTRY object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         symEntry_Assign(
        SYMENTRY_DATA		*this,
        SYMENTRY_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return symEntry_getLastError(this);
        }
        if( !symEntry_Validate(pOther) ) {
            DEBUG_BREAK();
            return symEntry_getLastError(pOther);
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
        symEntry_setLastError(this, ERESULT_SUCCESS);
    //eom:
        //FIXME: Implement the assignment.        
        symEntry_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return symEntry_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        symEntry      *pCopy = symEntry_Copy(this);
     @endcode
     @param     this    SYMENTRY object pointer
     @return    If successful, a SYMENTRY object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the SYMENTRY object.
     */
    SYMENTRY_DATA *     symEntry_Copy(
        SYMENTRY_DATA       *this
    )
    {
        SYMENTRY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        //FIXME: pOther = symEntry_New(symEntry_getName(this), symEntry_getData(this));
        if (pOther) {
            eRc = symEntry_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        symEntry_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            symEntry_Dealloc(
        OBJ_ID          objId
    )
    {
        SYMENTRY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SYMENTRY_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pEntry) {
            mem_Free(this->pEntry);
            this->pEntry = NULL;
        }
        symEntry_setAttr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         symEntry_Disable(
        SYMENTRY_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            symEntry_setLastError(this, ERESULT_INVALID_OBJECT);
            return symEntry_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return symEntry_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        symEntry_setLastError(this, ERESULT_SUCCESS);
        return symEntry_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         symEntry_Enable(
        SYMENTRY_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return symEntry_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        symEntry_setLastError(this, ERESULT_SUCCESS);
        return symEntry_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SYMENTRY_DATA *   symEntry_Init(
        SYMENTRY_DATA   *this
    )
    {
        uint32_t        cbSize = sizeof(SYMENTRY_DATA);
        
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

        //this = (OBJ_ID)node_Init((NODE_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SYMENTRY);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_SYMENTRY);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&symEntry_Vtbl);
        
        symEntry_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        this->pEntry = mem_Calloc(1, sizeof(SYM_ENTRY));

    #ifdef NDEBUG
    #else
        if( !symEntry_Validate(this) ) {
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
    
    ERESULT         symEntry_IsEnabled(
        SYMENTRY_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            return symEntry_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            symEntry_setLastError(this, ERESULT_SUCCESS_TRUE);
            return symEntry_getLastError(this);
        }
        
        // Return to caller.
        symEntry_setLastError(this, ERESULT_SUCCESS_FALSE);
        return symEntry_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          symEntry_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SYMENTRY_DATA   *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
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
                        
                    case 'A':
                        if (str_Compare("Accept", (char *)pStr) == 0) {
                            return symEntry_Accept;
                        }
                        break;
                        
#ifdef XYZZY
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return symEntry_Disable;
                        }
                        break;
                        
                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return symEntry_Enable;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return symEntry_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return symEntry_ToJSON;
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
     @code:
        ASTR_DATA      *pDesc = symEntry_ToDebugString(this,4);
     @endcode:
     @param:    this    SYMENTRY object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     symEntry_ToDebugString(
        SYMENTRY_DATA      *this,
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
        if( !symEntry_Validate(this) ) {
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
                     "{%p(symEntry) type=%d\n",
                     this,
                     symEntry_getType(this)
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
        j = snprintf(str, sizeof(str), " %p(symEntry)}\n", this);
        AStr_AppendA(pStr, str);
        
        symEntry_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            symEntry_Validate(
        SYMENTRY_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_SYMENTRY) )
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


        if( !(obj_getSize(this) >= sizeof(SYMENTRY_DATA)) ) {
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


