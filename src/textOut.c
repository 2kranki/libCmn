// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   textOut.c
 *	Generated 12/08/2017 10:18:28
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
#include <textOut_internal.h>
#include <utf8.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            textOut_task_body(
        void            *pData
    )
    {
        //TEXTOUT_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TEXTOUT_DATA *  textOut_Alloc(
    )
    {
        TEXTOUT_DATA    *this;
        uint32_t        cbSize = sizeof(TEXTOUT_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TEXTOUT_DATA *  textOut_New(
    )
    {
        TEXTOUT_DATA    *this;
        
        this = textOut_Alloc( );
        if (this) {
            this = textOut_Init(this);
        } 
        return this;
    }


    TEXTOUT_DATA *  textOut_NewAStr(
    )
    {
        TEXTOUT_DATA    *this;
        
        this = textOut_Alloc( );
        if (this) {
            this = textOut_Init(this);
            if (this) {
                this->pStr = AStr_New( );
                if (this->pStr) {
                    this->type = TEXTOUT_TYPE_ASTR;
                }
                else {
                    obj_Release(this);
                    this = OBJ_NIL;
                }
           }
       }
        return this;
    }
    
    
    TEXTOUT_DATA *  textOut_NewFromPath(
        PATH_DATA       *pPath
    )
    {
        TEXTOUT_DATA    *this;
        ERESULT         eRc;
        
        this = textOut_Alloc( );
        if (this) {
            this = textOut_Init(this);
            if (this) {
                eRc = textOut_SetupPath(this, pPath);
                if (ERESULT_FAILED(eRc)) {
                    obj_Release(this);
                    this = OBJ_NIL;
                }
            }
        }
        return this;
    }
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          F i l e
    //---------------------------------------------------------------
    
    FILE *          textOut_getFile(
        TEXTOUT_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->pFile;
    }
    
    
    bool            textOut_setFile(
        TEXTOUT_DATA    *this,
        FILE            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pFile = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          O f f s e t
    //---------------------------------------------------------------
    
    uint16_t        textOut_getOffset(
        TEXTOUT_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->offset;
    }
    
    
    bool            textOut_setOffset(
        TEXTOUT_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->offset = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                 O f f s e t  C h a r
    //---------------------------------------------------------------
    
    char            textOut_getOffsetChr(
        TEXTOUT_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->offsetChr;
    }
    
    
    bool            textOut_setOffsetChr(
        TEXTOUT_DATA    *this,
        char            value
    )
    {
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->offsetChr = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        textOut_getPriority(
        TEXTOUT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            textOut_setPriority(
        TEXTOUT_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
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
    
    uint32_t        textOut_getSize(
        TEXTOUT_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * textOut_getStr(
        TEXTOUT_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        textOut_setStr(
        TEXTOUT_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  textOut_getSuperVtbl(
        TEXTOUT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          T a b  S i z e
    //---------------------------------------------------------------
    
    uint16_t        textOut_getTabSize(
        TEXTOUT_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->tabSize;
    }
    
    
    bool            textOut_setTabSize(
        TEXTOUT_DATA    *this,
        uint16_t        value
                                        )
    {
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->tabSize = value;
        this->fTabify = 1;
        
        return true;
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
     @code 
        ERESULT eRc = textOut__Assign(this,pOther);
     @endcode 
     @param     this    TEXTOUT object pointer
     @param     pOther  a pointer to another TEXTOUT object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         textOut_Assign(
        TEXTOUT_DATA	*this,
        TEXTOUT_DATA    *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !textOut_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
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
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        textOut      *pCopy = textOut_Copy(this);
     @endcode 
     @param     this    TEXTOUT object pointer
     @return    If successful, a TEXTOUT object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the TEXTOUT object.
     */
    TEXTOUT_DATA *     textOut_Copy(
        TEXTOUT_DATA       *this
    )
    {
        TEXTOUT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = textOut_New( );
        if (pOther) {
            eRc = textOut_Assign(this, pOther);
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

    void            textOut_Dealloc(
        OBJ_ID          objId
    )
    {
        TEXTOUT_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((TEXTOUT_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        textOut_setStr(this, OBJ_NIL);
        if (this->type == TEXTOUT_TYPE_FILE_CLOSE) {
            fclose(this->pFile);
            this->pFile = NULL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         textOut_Disable(
        TEXTOUT_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !textOut_Validate(this) ) {
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

    ERESULT         textOut_Enable(
        TEXTOUT_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !textOut_Validate(this) ) {
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
    //                          I n i t
    //---------------------------------------------------------------

    TEXTOUT_DATA *   textOut_Init(
        TEXTOUT_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(TEXTOUT_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_TEXTOUT);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_TEXTOUT);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&textOut_Vtbl);
        
    #ifdef NDEBUG
    #else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "textOut::sizeof(TEXTOUT_DATA) = %lu\n", sizeof(TEXTOUT_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(TEXTOUT_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          P r i n t
    //---------------------------------------------------------------
    
    ERESULT         textOut_Print(
        TEXTOUT_DATA    *this,
        const
        char            *pFormat,
        ...
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        char            str[256];
        int             size;
        va_list         arg_ptr;
        char            *pStr = NULL;
        char            *pWrk = NULL;
        W32CHR_T        chr;
        int             len;
        bool            fAlloc = false;

        // Do Initialization.
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        va_start( arg_ptr, pFormat );
        str[0] = '\0';
        size = vsnprintf( str, sizeof(str), pFormat, arg_ptr );
        va_end( arg_ptr );
        if (size >= sizeof(str)) {
            ++size;
            pStr = (char *)mem_Malloc(size);
            if( pStr == NULL ) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
            va_start( arg_ptr, pFormat );
            size = vsnprintf( pStr, size, pFormat, arg_ptr );
            va_end( arg_ptr );
            pWrk = pStr;
            fAlloc = true;
        }
        else {
            pWrk = str;
        }
        if (pWrk) {
            while (*pWrk) {
                len = utf8_Utf8ToW32(pWrk, &chr);
                if (len < 0) {
                    eRc = ERESULT_DATA_ERROR;
                    break;
                }
                eRc = textOut_Putwc(this, chr);
                if (ERESULT_FAILED(eRc)) {
                    break;
                }
                pWrk += len;
            }
        }
        if (fAlloc) {
            mem_Free(pStr);
            pStr = NULL;
        }

        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       P u t  S t r i n g
    //---------------------------------------------------------------
    
    ERESULT             textOut_PutA(
        TEXTOUT_DATA        *this,
        const
        char                *pStrA
    )
    {
        ERESULT             eRc = ERESULT_INVALID_PARAMETER;
        W32CHR_T            chr;
        int                 len;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if(!textOut_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pStrA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        while (*pStrA) {
            len = utf8_Utf8ToW32(pStrA, &chr);
            if (len < 0) {
                eRc = ERESULT_DATA_ERROR;
                break;
            }
            eRc = textOut_Putwc(this, chr);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            pStrA += len;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       P u t  C h a r
    //---------------------------------------------------------------
    
    ERESULT         textOut_Putc(
        TEXTOUT_DATA    *this,
        const
        char            chr
    )
    {
        ERESULT         eRc;
        int             iRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        switch (this->type) {
                
            case TEXTOUT_TYPE_ASTR:
                eRc = AStr_AppendCharW32(this->pStr, chr);
                break;
                
            case TEXTOUT_TYPE_FILE:
            case TEXTOUT_TYPE_FILE_CLOSE:
                iRc = putc(chr, this->pFile);
                eRc = ERESULT_SUCCESS;
                if (iRc == EOF) {
                    eRc = ERESULT_WRITE_ERROR;
                }
                break;
                
            default:
                eRc = ERESULT_GENERAL_FAILURE;
                break;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         textOut_Putwc(
        TEXTOUT_DATA    *this,
        const
        W32CHR_T        chr
    )
    {
        ERESULT         eRc;
        int             iRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        switch (this->type) {

            case TEXTOUT_TYPE_ASTR:
                eRc = AStr_AppendCharW32(this->pStr, chr);
                break;

            case TEXTOUT_TYPE_FILE:
            case TEXTOUT_TYPE_FILE_CLOSE:
                if (chr < 128) {
                    iRc = putc(chr, this->pFile);
                }
                else {
                    iRc = putw(chr, this->pFile);
                }
                eRc = ERESULT_SUCCESS;
               if (iRc == EOF) {
                    eRc = ERESULT_WRITE_ERROR;
                }
                break;
                
            default:
                eRc = ERESULT_GENERAL_FAILURE;
                break;
        }
        
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
        void        *pMethod = textOut_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "textOut", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          textOut_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        TEXTOUT_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
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
                            return textOut_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return textOut_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return textOut_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return textOut_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == textOut_ToDebugString)
                    return "ToDebugString";
                if (pData == textOut_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       S e t u p
    //---------------------------------------------------------------
    
    ERESULT             textOut_SetupFile(
        TEXTOUT_DATA        *this,
        FILE                *pFile,
        bool                fClose
    )
    {
        ERESULT             eRc = ERESULT_INVALID_PARAMETER;
        W32CHR_T            chr;
        int                 len;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if(!textOut_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(NULL == pFile) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (0 == this->type)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
#endif

        this->pFile = pFile;
        this->type = fClose ? TEXTOUT_TYPE_FILE_CLOSE: TEXTOUT_TYPE_FILE;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT             textOut_SetupPath(
        TEXTOUT_DATA        *this,
        PATH_DATA           *pPath
    )
    {
        ERESULT             eRc = ERESULT_INVALID_PARAMETER;
        FILE                *pFile = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if(!textOut_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (0 == this->type)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
#endif
        
        pFile = fopen(path_getData(pPath), "w");
        if (NULL == pFile) {
            DEBUG_BREAK();
            return ERESULT_OPEN_ERROR;
        }
        
        this->pFile = pFile;
        this->type = TEXTOUT_TYPE_FILE_CLOSE;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    

    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = textOut_ToDebugString(this,4);
     @endcode 
     @param     this    TEXTOUT object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     textOut_ToDebugString(
        TEXTOUT_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = textOut_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) type=%d\n",
                    this,
                    pInfo->pClassName,
                    this->type
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
    
    
    
    ASTR_DATA *     textOut_ToJSON(
        TEXTOUT_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !textOut_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        eRc =   AStr_AppendPrint(
                    pStr,
                    "{\"objectType\":\"%s\"",
                    pInfo->pClassName
                );
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            textOut_Validate(
        TEXTOUT_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_TEXTOUT) )
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


        if( !(obj_getSize(this) >= sizeof(TEXTOUT_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


