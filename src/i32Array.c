// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   i32Array.c
 *	Generated 01/20/2018 22:51:51
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
#include    <i32Array_internal.h>
#include    <file.h>
#include    <path_internal.h>
#include    <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif

    
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            i32Array_task_body(
        void            *pData
    )
    {
        //I32ARRAY_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    I32ARRAY_DATA * i32Array_Alloc(
    )
    {
        I32ARRAY_DATA   *this;
        uint32_t        cbSize = sizeof(I32ARRAY_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    I32ARRAY_DATA *     i32Array_New(
    )
    {
        I32ARRAY_DATA       *this;
        
        this = i32Array_Alloc( );
        if (this) {
            this = i32Array_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      B i g  E n d i a n
    //---------------------------------------------------------------
    
    bool            i32Array_setBigEndian(
        I32ARRAY_DATA   *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        obj_FlagSet(this, I32ARRAY_FLAG_BIGENDIAN, value);
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                           D a t a
    //---------------------------------------------------------------
    
    int32_t *       i32Array_getData(
        I32ARRAY_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return array_Ptr((ARRAY_DATA *)this, 1);
    }
    
    
    
    //---------------------------------------------------------------
    //                           S i z e
    //---------------------------------------------------------------
    
    uint32_t        i32Array_getSize(
        I32ARRAY_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return array_getSize((ARRAY_DATA *)this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  i32Array_getSuperVtbl(
        I32ARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        //i32Array_setLastError(this, ERESULT_SUCCESS);
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         i32Array_AppendData(
        I32ARRAY_DATA   *this,
        int32_t         data
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc =   array_InsertData(
                                 (ARRAY_DATA *)this,
                                 (array_getSize((ARRAY_DATA *)this) + 1),
                                 1,
                                 &data
                );
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         i32Array_AppendFile(
        I32ARRAY_DATA   *this,
        PATH_DATA       *pPath
    )
    {
        int64_t         size = 0;
        int             chr;
        FILE            *pFile;
        int32_t         data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        size = file_SizeA(path_getData(pPath));
        if (-1 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }
        if (0 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        pFile = fopen(path_getData(pPath), "rb");
        if (NULL == pFile) {
            return ERESULT_FILE_NOT_FOUND;
        }
        while ( !feof(pFile) ) {
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, I32ARRAY_FLAG_BIGENDIAN)) {
                data = (chr & 0xFF) << 24;
            }
            else {
                data = chr & 0xFF;
            }
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, I32ARRAY_FLAG_BIGENDIAN)) {
                data |= (chr & 0xFF) << 16;
            }
            else {
                data |= (chr & 0xFF) << 8;
            }
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, I32ARRAY_FLAG_BIGENDIAN)) {
                data = (chr & 0xFF) << 8;
            }
            else {
                data |= (chr & 0xFF) << 16;
            }
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, I32ARRAY_FLAG_BIGENDIAN)) {
                data = (chr & 0xFF);
            }
            else {
                data |= (chr & 0xFF) << 24;
            }
            i32Array_AppendData(this, data);
        }
        fclose(pFile);
        pFile = NULL;
        
        // Return to caller.
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
     @code 
        ERESULT eRc = i32Array__Assign(this,pOther);
     @endcode 
     @param     this    I32ARRAY object pointer
     @param     pOther  a pointer to another I32ARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         i32Array_Assign(
        I32ARRAY_DATA	*this,
        I32ARRAY_DATA   *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !i32Array_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = array_Assign((ARRAY_DATA *)this, (ARRAY_DATA *)pOther);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        i32Array      *pCopy = i32Array_Copy(this);
     @endcode 
     @param     this    I32ARRAY object pointer
     @return    If successful, a I32ARRAY object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the I32ARRAY object.
     */
    I32ARRAY_DATA *     i32Array_Copy(
        I32ARRAY_DATA       *this
    )
    {
        I32ARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = i32Array_New( );
        if (pOther) {
            eRc = i32Array_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            i32Array_Dealloc(
        OBJ_ID          objId
    )
    {
        I32ARRAY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
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
    
    int32_t         i32Array_Delete(
        I32ARRAY_DATA   *this,
        uint32_t        index
    )
    {
        int32_t         data = 0;
        uint32_t        *pData;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if ((index > 0) && (index <= array_getSize((ARRAY_DATA *)this)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        pData = array_Ptr((ARRAY_DATA *)this, index);
        if (pData) {
            data = *pData;
            eRc = array_Delete((ARRAY_DATA *)this, index, 1);
            if (ERESULT_HAS_FAILED(eRc)) {
                return 0;
            }
        }
        
        // Return to caller.
        return data;
    }
    
    
    int32_t         i32Array_DeleteFirst(
        I32ARRAY_DATA   *this
    )
    {
        int32_t         data = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = i32Array_Delete(this, 1);
        
        // Return to caller.
        return data;
    }
    
    
    int32_t         i32Array_DeleteLast(
        I32ARRAY_DATA   *this
    )
    {
        int32_t         data = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = i32Array_Delete(this, array_getSize((ARRAY_DATA *)this));
        
        // Return to caller.
        return data;
    }
    
    
    
    //---------------------------------------------------------------
    //                         G e t
    //---------------------------------------------------------------
    
    int32_t         i32Array_Get(
        I32ARRAY_DATA   *this,
        uint32_t        index
    )
    {
        int32_t         data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if ((index > 0) && (index <= array_getSize((ARRAY_DATA *)this)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = *((uint32_t *)array_Ptr((ARRAY_DATA *)this, index));
        
        return data;
    }
    
    
    int32_t         i32Array_GetFirst(
        I32ARRAY_DATA   *this
    )
    {
        int32_t         data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = i32Array_Get(this, 1);
        
        return data;
    }
    
    
    int32_t         i32Array_GetLast(
        I32ARRAY_DATA   *this
    )
    {
        int32_t         data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = i32Array_Get(this, array_getSize((ARRAY_DATA *)this));
        
        return data;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    I32ARRAY_DATA *   i32Array_Init(
        I32ARRAY_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(I32ARRAY_DATA);
        
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

        this = (OBJ_ID)array_Init((ARRAY_DATA *)this);      // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_I32ARRAY);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        array_setElemSize((ARRAY_DATA *)this, 4);
        obj_setSize(this, cbSize);                          // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_I32ARRAY);     // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&i32Array_Vtbl);
        
    #ifdef NDEBUG
    #else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "i32Array::offsetof(eRc) = %lu\n", offsetof(I32ARRAY_DATA,eRc));
        //fprintf(stderr, "i32Array::sizeof(I32ARRAY_DATA) = %lu\n", sizeof(I32ARRAY_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(I32ARRAY_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         i32Array_InsertData(
        I32ARRAY_DATA   *this,
        uint32_t        index,
        int32_t         data
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((index > 0) && (index <= array_getSize((ARRAY_DATA *)this)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        eRc = array_InsertData((ARRAY_DATA *)this, index, 1, &data);
        
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
        void        *pMethod = i32Array_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "i32Array", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          i32Array_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        I32ARRAY_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)i32Array_Class();
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
                    
#ifdef XYZZY
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return i32Array_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return i32Array_Enable;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return i32Array_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return i32Array_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == i32Array_ToDebugString)
                    return "ToDebugString";
                if (pData == i32Array_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                            S e t
    //---------------------------------------------------------------
    
    ERESULT         i32Array_SetData(
        I32ARRAY_DATA   *this,
        uint32_t        index,
        int32_t         data
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((index > 0) && (index <= array_getSize((ARRAY_DATA *)this)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        *((int32_t *)array_Ptr((ARRAY_DATA *)this, index)) = data;
        
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
        ASTR_DATA      *pDesc = i32Array_ToDebugString(this,4);
     @endcode 
     @param     this    I32ARRAY object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     i32Array_ToDebugString(
        I32ARRAY_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        int             j;
        int             jMax;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        int32_t         *pData;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = i32Array_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d ",
                    this,
                    pInfo->pClassName,
                    i32Array_getSize(this)
            );

        jMax = array_getSize((ARRAY_DATA *)this);
        pData = array_Ptr((ARRAY_DATA *)this, 1);
        if (jMax) {
            for (j=0; j<(jMax-1); ++j) {
                AStr_AppendPrint(pStr, "%d,", *pData++);
            }
            AStr_AppendPrint(pStr, "%d\n", *pData++);
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
        
        //i32Array_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     i32Array_ToJSON(
        I32ARRAY_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
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
        
        //i32Array_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            i32Array_Validate(
        I32ARRAY_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_I32ARRAY) )
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


        if( !(obj_getSize(this) >= sizeof(I32ARRAY_DATA)) ) {
            //this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        //this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                  W r i t e  T o  F i l e
    //---------------------------------------------------------------
    
    ERESULT         i32Array_WriteToFile(
        I32ARRAY_DATA   *this,
        PATH_DATA       *pPath
    )
    {
        FILE            *pFile;
        uint32_t        index = 0;
        uint32_t        size;
        int32_t         *pData;
        int32_t         data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !i32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !path_Validate(pPath) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pData = (int32_t *)array_getData((ARRAY_DATA *)this);
        size = array_getSize((ARRAY_DATA *)this);
        pFile = fopen(path_getData(pPath), "w");
        if (NULL == pFile) {
            return ERESULT_OPEN_ERROR;
        }
        while ( size-- ) {
            data = *pData++;
            if (obj_Flag(this, I32ARRAY_FLAG_BIGENDIAN)) {
                fputc(((data >> 24) & 0xFF), pFile);
                fputc(((data >> 16) & 0xFF), pFile);
                fputc(((data >> 8) & 0xFF), pFile);
                fputc((data & 0xFF), pFile);
            }
            else {
                fputc((data & 0xFF), pFile);
                fputc(((data >> 8) & 0xFF), pFile);
                fputc(((data >> 16) & 0xFF), pFile);
                fputc(((data >> 24) & 0xFF), pFile);
            }
        }
        fclose(pFile);
        pFile = NULL;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    

    
#ifdef	__cplusplus
}
#endif


