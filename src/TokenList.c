// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   TokenList.c
 *	Generated 01/02/2020 15:56:31
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
#include        <TokenList_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            TokenList_task_body (
        void            *pData
    )
    {
        //TOKENLIST_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TOKENLIST_DATA *     TokenList_Alloc (
        void
    )
    {
        TOKENLIST_DATA       *this;
        uint32_t        cbSize = sizeof(TOKENLIST_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TOKENLIST_DATA *     TokenList_New (
        void
    )
    {
        TOKENLIST_DATA       *this;
        
        this = TokenList_Alloc( );
        if (this) {
            this = TokenList_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          L i s t
    //---------------------------------------------------------------

    OBJLIST_DATA *  TokenList_getList (
        TOKENLIST_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TokenList_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (OBJLIST_DATA *)this;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        TokenList_getPriority (
        TOKENLIST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TokenList_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            TokenList_setPriority (
        TOKENLIST_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!TokenList_Validate(this)) {
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
    
    uint32_t        TokenList_getSize (
        TOKENLIST_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!TokenList_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return ObjList_getSize(TokenList_getList(this));
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  TokenList_getSuperVtbl (
        TOKENLIST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TokenList_Validate(this)) {
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
    //                          A d d
    //---------------------------------------------------------------

    ERESULT         TokenList_Add2Head (
        TOKENLIST_DATA  *this,
        TOKEN_DATA      *pToken
    )
    {
        ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !TokenList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pToken) || !obj_IsKindOf(pToken,OBJ_IDENT_TOKEN) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
    #endif

        eRc = ObjList_Add2Head(TokenList_getList(this), pToken);

        // Return to caller.
        return eRc;
    }


    ERESULT         TokenList_Add2Tail (
        TOKENLIST_DATA  *this,
        TOKEN_DATA      *pToken
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TokenList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pToken) || !obj_IsKindOf(pToken,OBJ_IDENT_TOKEN) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = ObjList_Add2Tail(TokenList_getList(this), pToken);

        // Return to caller.
        return eRc;
    }



    //----------------------------------------------------------
    //                      A p p e n d
    //----------------------------------------------------------

    ERESULT         TokenList_Append (
        TOKENLIST_DATA  *this,
        TOKENLIST_DATA  *pOther
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TokenList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !TokenList_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = ObjList_Append(TokenList_getList(this), TokenList_getList(pOther));

        // Return to caller.
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
        ERESULT eRc = TokenList_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another TOKENLIST object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         TokenList_Assign (
        TOKENLIST_DATA	*this,
        TOKENLIST_DATA  *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TokenList_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!TokenList_Validate(pOther)) {
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
        eRc = ObjList_Assign(TokenList_getList(this), TokenList_getList(pOther));

        //goto eom;

        // Return to caller.
        //eRc = ERESULT_SUCCESS;
    eom:
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
    int             TokenList_Compare (
        TOKENLIST_DATA  *this,
        TOKENLIST_DATA  *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!TokenList_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!TokenList_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
#endif

        return iRc;
    }

   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        TokenList      *pCopy = TokenList_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TOKENLIST object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TOKENLIST_DATA * TokenList_Copy (
        TOKENLIST_DATA  *this
    )
    {
        TOKENLIST_DATA  *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TokenList_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = TokenList_New( );
        if (pOther) {
            eRc = TokenList_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            TokenList_Dealloc (
        OBJ_ID          objId
    )
    {
        TOKENLIST_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!TokenList_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------

    ERESULT         TokenList_DeleteAll(
        TOKENLIST_DATA    *this
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TokenList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = ObjList_DeleteAll(TokenList_getList(this));

        // Return to caller.
        return eRc;
    }


    ERESULT         TokenList_DeleteHead(
        TOKENLIST_DATA    *this
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TokenList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = ObjList_DeleteHead(TokenList_getList(this));

        // Return to caller.
        return eRc;
    }


    ERESULT         TokenList_DeleteTail(
        TOKENLIST_DATA    *this
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TokenList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = ObjList_DeleteTail(TokenList_getList(this));

        // Return to caller.
        return eRc;
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
    ERESULT         TokenList_Disable (
        TOKENLIST_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!TokenList_Validate(this)) {
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
    ERESULT         TokenList_Enable (
        TOKENLIST_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!TokenList_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //----------------------------------------------------------
    //                        E n u m
    //----------------------------------------------------------

    OBJENUM_DATA *  TokenList_Enum(
        TOKENLIST_DATA  *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TokenList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        // Return to caller.
        return ObjList_Enum(TokenList_getList(this));
    }



    //---------------------------------------------------------------
    //                          H e a d
    //---------------------------------------------------------------

    TOKEN_DATA *    TokenList_Head(
        TOKENLIST_DATA  *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TokenList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        // Return to caller.
        return (TOKEN_DATA *)ObjList_Head(TokenList_getList(this));
    }



    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------

    TOKEN_DATA *    TokenList_Index(
        TOKENLIST_DATA  *this,
        int32_t         index                    // (relative to 1)
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if(!TokenList_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        // Return to caller.
        return (TOKEN_DATA *)ObjList_Index(TokenList_getList(this), index);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    TOKENLIST_DATA *   TokenList_Init (
        TOKENLIST_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(TOKENLIST_DATA);
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

        this = (OBJ_ID)ObjList_Init((OBJLIST_DATA *)this);      // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_TOKENLIST);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&TokenList_Vtbl);
        JsonIn_RegisterClass(SrcLoc_Class());
        JsonIn_RegisterClass(Token_Class());
        JsonIn_RegisterClass(TokenList_Class());

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
        if (!TokenList_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "TokenList::sizeof(TOKENLIST_DATA) = %lu\n", sizeof(TOKENLIST_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(TOKENLIST_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         TokenList_IsEnabled (
        TOKENLIST_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TokenList_Validate(this)) {
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
    
    
    
    //----------------------------------------------------------
    //                  P r e p e n d
    //----------------------------------------------------------

    ERESULT         TokenList_Prepend(
        TOKENLIST_DATA  *this,
        TOKENLIST_DATA  *pOther
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TokenList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !TokenList_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = ObjList_Prepend(TokenList_getList(this), TokenList_getList(pOther));

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
        void        *pMethod = TokenList_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "TokenList", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          TokenList_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        TOKENLIST_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!TokenList_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TOKENLIST_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)TokenList_Class();
                break;
                
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'S':
                    if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                        return &this->pSuperVtbl;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return TokenList_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return TokenList_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return TokenList_ToDebugString;
                        }
#ifdef  TOKENLIST_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return TokenList_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == TokenList_ToDebugString)
                    return "ToDebugString";
#ifdef  TOKENLIST_JSON_SUPPORT
                if (pData == TokenList_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          T a i l
    //---------------------------------------------------------------

    TOKEN_DATA *    TokenList_Tail(
        TOKENLIST_DATA  *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TokenList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        // Return to caller.
        return (TOKEN_DATA *)ObjList_Tail(TokenList_getList(this));
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = TokenList_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     TokenList_ToDebugString (
        TOKENLIST_DATA  *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TokenList_Validate(this)) {
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
                    TokenList_getSize(this),
                    obj_getRetainCount(this)
            );

        pWrkStr = ObjList_ToDebugString(TokenList_getList(this), indent+3);
        if (pWrkStr) {
            AStr_Append(pStr, pWrkStr);
            obj_Release(pWrkStr);
        }

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
    bool            TokenList_Validate (
        TOKENLIST_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_TOKENLIST))
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


        if (!(obj_getSize(this) >= sizeof(TOKENLIST_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


