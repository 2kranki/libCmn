// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   u32Array.c
 *	Generated 08/07/2015 09:47:23
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
#include    <u32Array_internal.h>
#include    <File.h>
#include    <Path_internal.h>
#include    <stdio.h>



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

    U32ARRAY_DATA * u32Array_Alloc(
    )
    {
        U32ARRAY_DATA   *this;
        uint32_t        cbSize = sizeof(U32ARRAY_DATA);
        
        this = obj_Alloc( cbSize );
        
        return this;
    }



    U32ARRAY_DATA * u32Array_New(
    )
    {
        U32ARRAY_DATA    *this;
        
        this = u32Array_Alloc( );
        this = u32Array_Init(this);
        
        return this;
    }
    
    
    U32ARRAY_DATA * u32Array_NewWithSize(
        uint32_t        size
    )
    {
        ERESULT         eRc;
        U32ARRAY_DATA    *this;

        this = u32Array_New( );
        if (this) {
            eRc = array_AppendSpacing((ARRAY_DATA *)this, size);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }

        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  B i g  E n d i a n
    //---------------------------------------------------------------

    bool            u32Array_setBigEndian(
        U32ARRAY_DATA   *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        obj_FlagSet(this, U32ARRAY_FLAG_BIGENDIAN, value);
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          D a t a
    //---------------------------------------------------------------

    uint32_t *      u32Array_getData(
        U32ARRAY_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return array_Ptr((ARRAY_DATA *)this, 1);
    }
    
    
    
    //---------------------------------------------------------------
    //                          S i z e
    //---------------------------------------------------------------

    uint32_t        u32Array_getSize(
        U32ARRAY_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return array_getSize((ARRAY_DATA *)this);
    }



    //---------------------------------------------------------------
    //                          U s e r
    //---------------------------------------------------------------

    void *          u32Array_getUser(
        U32ARRAY_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        return this->pUser;
    }


    bool            u32Array_setUser(
        U32ARRAY_DATA   *this,
        void            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pUser = pValue;

        return true;
    }





    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         u32Array_AppendData(
        U32ARRAY_DATA	*this,
        uint32_t        data
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
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
    
    
    ERESULT         u32Array_AppendFile(
        U32ARRAY_DATA	*this,
        PATH_DATA       *pPath
    )
    {
        int64_t         size = 0;
        int             chr;
        FILE            *pFile;
        uint32_t        data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        size = File_SizeA(Path_getData(pPath));
        if (-1 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }
        if (0 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        pFile = fopen(Path_getData(pPath), "rb");
        if (NULL == pFile) {
            return ERESULT_FILE_NOT_FOUND;
        }
        while ( !feof(pFile) ) {
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, U32ARRAY_FLAG_BIGENDIAN)) {
                data = (chr & 0xFF) << 24;
            }
            else {
                data = chr & 0xFF;
            }
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, U32ARRAY_FLAG_BIGENDIAN)) {
                data |= (chr & 0xFF) << 16;
            }
            else {
                data |= (chr & 0xFF) << 8;
            }
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, U32ARRAY_FLAG_BIGENDIAN)) {
                data = (chr & 0xFF) << 8;
            }
            else {
                data |= (chr & 0xFF) << 16;
            }
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, U32ARRAY_FLAG_BIGENDIAN)) {
                data = (chr & 0xFF);
            }
            else {
                data |= (chr & 0xFF) << 24;
            }
            u32Array_AppendData(this, data);
        }
        fclose(pFile);
        pFile = NULL;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                         A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         u32Array_Assign(
        U32ARRAY_DATA	*this,
        U32ARRAY_DATA	*pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
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
    //                         C o p y
    //---------------------------------------------------------------
    
    U32ARRAY_DATA * u32Array_Copy(
        U32ARRAY_DATA	*this
    )
    {
        U32ARRAY_DATA	*pOther;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = u32Array_New();
        if (pOther) {
            eRc = u32Array_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            u32Array_Dealloc(
        OBJ_ID          objId
    )
    {
        U32ARRAY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
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
    
    uint32_t         u32Array_Delete(
        U32ARRAY_DATA	*this,
        uint32_t        index
    )
    {
        uint32_t        data = 0;
        uint32_t        *pData;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
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
    
    
    ERESULT             u32Array_DeleteAll(
        U32ARRAY_DATA    *this
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        eRc = array_Truncate((ARRAY_DATA *)this, 0);

        // Return to caller.
        return eRc;
    }


    uint32_t         u32Array_DeleteFirst(
        U32ARRAY_DATA	*this
    )
    {
        uint32_t        data = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = u32Array_Delete(this, 1);
        
        // Return to caller.
        return data;
    }
    
    
    uint32_t         u32Array_DeleteLast(
        U32ARRAY_DATA	*this
    )
    {
        uint32_t        data = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = u32Array_Delete(this, array_getSize((ARRAY_DATA *)this));
        
        // Return to caller.
        return data;
    }
    
    
    
    //---------------------------------------------------------------
    //                         G e t
    //---------------------------------------------------------------
    
    uint32_t         u32Array_Get(
        U32ARRAY_DATA	*this,
        uint32_t        index
    )
    {
        uint32_t        data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
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
    
    
    uint32_t        u32Array_GetFirst(
        U32ARRAY_DATA	*this
    )
    {
        uint32_t        data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = u32Array_Get(this, 1);
        
        return data;
    }
    
    
    uint32_t         u32Array_GetLast(
        U32ARRAY_DATA	*this
    )
    {
        uint32_t        data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = u32Array_Get(this, array_getSize((ARRAY_DATA *)this));
        
        return data;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    U32ARRAY_DATA *   u32Array_Init(
        U32ARRAY_DATA     *this
    )
    {
        uint16_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (U32ARRAY_DATA *)array_Init((ARRAY_DATA *)this);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        array_setElemSize((ARRAY_DATA *)this, 4);
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);   // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&u32Array_Vtbl);

    #ifdef NDEBUG
    #else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "u32Array::offsetof(eRc) = %lu\n", offsetof(U32ARRAY_DATA,eRc));
        //fprintf(stderr, "u32Array::sizeof(U32ARRAY_DATA) = %lu\n", sizeof(U32ARRAY_DATA));
#endif
        //BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(U32ARRAY_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         u32Array_InsertData(
        U32ARRAY_DATA   *this,
        uint32_t        index,
        uint32_t        data
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
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
    //                        M e r g e
    //---------------------------------------------------------------
    
    U32ARRAY_DATA * u32Array_Merge(
        U32ARRAY_DATA   *this,
        U32ARRAY_DATA   *pOther
    )
    {
        U32ARRAY_DATA   *pNew;
        U32ARRAY_DATA   *pNew2;
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        j;
        uint32_t        jMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if( !u32Array_Validate(pOther) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pNew = u32Array_Copy(this);
        if (OBJ_NIL == pNew) {
            return OBJ_NIL;
        }
        eRc = u32Array_SortAscending(pNew);
        if (ERESULT_FAILED(eRc)) {
            obj_Release(pNew);
            return OBJ_NIL;
        }
        iMax = u32Array_getSize(pNew);

        pNew2 = u32Array_Copy(pOther);
        if (OBJ_NIL == pNew2) {
            obj_Release(pNew);
            return OBJ_NIL;
        }
        eRc = u32Array_SortAscending(pNew);
        if (ERESULT_FAILED(eRc)) {
            obj_Release(pNew);
            obj_Release(pNew2);
            return OBJ_NIL;
        }
        jMax = u32Array_getSize(pNew2);

        i = 0;
        j = 0;
        while (j < jMax) {
            while ((i < u32Array_getSize(pNew)) &&(u32Array_Get(pNew, i+1) < u32Array_Get(pNew2, j+1))) {
                ++i;
            }
            if (i == u32Array_getSize(pNew)) {
                u32Array_AppendData(pNew, u32Array_Get(pNew2, j+1));
                ++j;
                continue;
            }
            if (u32Array_Get(pNew, i+1) == u32Array_Get(pNew2, j+1)) {
                ++j;
                continue;
            }
            // u32Array_Get(pNew, i+1) > u32Array_Get(pNew2, j+1)
            u32Array_InsertData(pNew, i+1, u32Array_Get(pNew2, j+1));
            ++j;
        }
        obj_Release(pNew2);
        pNew2 = OBJ_NIL;
        
        return pNew;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P o p
    //---------------------------------------------------------------

    uint32_t        u32Array_Pop(
        U32ARRAY_DATA   *this
    )
    {
        //ERESULT         eRc;
        uint32_t        data = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        data = u32Array_Delete(this, array_getSize((ARRAY_DATA *)this));

        // Return to caller.
        return data;
    }



    //---------------------------------------------------------------
    //                          P u s h
    //---------------------------------------------------------------

    ERESULT         u32Array_Push(
        U32ARRAY_DATA   *this,
        uint32_t        data
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
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
     void        *pMethod = array_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode
     @param     objId   OBJTEST object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
     for OBJ_QUERYINFO_TYPE_METHOD, this field points to a
     character string which represents the method name without
     the object name, "array", prefix,
     for OBJ_QUERYINFO_TYPE_PTR, this field contains the
     address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
     OBJ_QUERYINFO_TYPE_INFO: info pointer,
     OBJ_QUERYINFO_TYPE_METHOD: method pointer,
     OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          u32Array_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        U32ARRAY_DATA   *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
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
                        if (str_Compare("Delete", (char *)pStr) == 0) {
                            return u32Array_Delete;
                        }
                        break;
                        
                    case 'I':
                        if (str_Compare("InsertData", (char *)pStr) == 0) {
                            return u32Array_InsertData;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return u32Array_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == u32Array_ToDebugString)
                    return "ToDebugString";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                            S e t
    //---------------------------------------------------------------
    
    ERESULT         u32Array_SetData(
        U32ARRAY_DATA   *this,
        uint32_t        index,
        uint32_t        data
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (index && (index <= array_getSize((ARRAY_DATA *)this)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        *((uint32_t *)array_Ptr((ARRAY_DATA *)this, index)) = data;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S o r t
    //---------------------------------------------------------------
    
    ERESULT         u32Array_SortAscending(
        U32ARRAY_DATA   *this
    )
    {
        uint32_t        i;
        uint32_t        j;
        uint32_t        size = array_getSize((ARRAY_DATA *)this);
        uint32_t        *pJ0;
        uint32_t        *pJ1;
        uint32_t        wrk;

        /*      Insertion Sort from Wikipedia
         *
         *  for i = 1 to length(A)
         *      j = i
         *      while j > 0 and A[j-1] > A[j]
         *          swap A[j] and A[j-1]
         *          j = j - 1
         *      end while
         *  end for
         *
         *  NOTE:   indexing is relative to zero.
         *          adjust as necessary.
         */
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (array_getSize((ARRAY_DATA *)this) < 2) {
            return ERESULT_SUCCESS;
        }
        
        for (i=1; i<size; ++i) {
            j = i;
            while (j > 0) {
                pJ0 = (uint32_t *)array_Ptr((ARRAY_DATA *)this, j);
                pJ1 = (uint32_t *)array_Ptr((ARRAY_DATA *)this, j+1);
                if (*pJ0 > *pJ1)
                    ;
                else
                    break;
                wrk = *pJ0;
                *pJ0 = *pJ1;
                *pJ1 = wrk;
                j = j - 1;
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     u32Array_ToDebugString(
        U32ARRAY_DATA   *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        int             jMax;
        ASTR_DATA       *pStr;
        uint32_t        *pData;
        
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
                     "{%p(token) size=%d data=[",
                     this,
                     array_getSize((ARRAY_DATA *)this)
                     );
        AStr_AppendA(pStr, str);

        jMax = array_getSize((ARRAY_DATA *)this);
        pData = array_Ptr((ARRAY_DATA *)this, 1);
        if (jMax) {
            for (j=0; j<(jMax-1); ++j) {
                snprintf( str, sizeof(str), "%d,", *pData++ );
                AStr_AppendA(pStr, str);
            }
            snprintf( str, sizeof(str), "%d", *pData );
            AStr_AppendA(pStr, str);
        }
        
        j = snprintf( str, sizeof(str), "] %p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            u32Array_Validate(
        U32ARRAY_DATA   *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_U32ARRAY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(U32ARRAY_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                  W r i t e  T o  F i l e
    //---------------------------------------------------------------
    
    ERESULT         u32Array_WriteToFile(
        U32ARRAY_DATA   *this,
        PATH_DATA       *pPath
    )
    {
        FILE            *pFile;
        uint32_t        index = 0;
        uint32_t        size;
        uint32_t        *pData;
        uint32_t        data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !Path_Validate(pPath) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pData = (uint32_t *)array_getData((ARRAY_DATA *)this);
        size = array_getSize((ARRAY_DATA *)this);
        pFile = fopen(Path_getData(pPath), "w");
        if (NULL == pFile) {
            return ERESULT_OPEN_ERROR;
        }
        while ( index < size ) {
            data = pData[index++];
            if (obj_Flag(this, U32ARRAY_FLAG_BIGENDIAN)) {
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
    
    
    
    //---------------------------------------------------------------
    //                         Z e r o
    //---------------------------------------------------------------

    ERESULT         u32Array_Zero(
        U32ARRAY_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        *pData;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (array_getSize((ARRAY_DATA *)this)) {
            pData = ((uint32_t *)array_Ptr((ARRAY_DATA *)this, 1));
            memset(pData, 0, (array_getSize((ARRAY_DATA *)this) * sizeof(uint32_t)));
        }

        return eRc;
    }



    
#ifdef	__cplusplus
}
#endif


