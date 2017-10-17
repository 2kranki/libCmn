// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   path.c
 *	Generated 06/09/2015 13:02:46
 *
 * Created on December 30, 2014
 */

//TODO: Normalize a pathname by collapsing redundant separators
//      and up-level references so that A//B, A/B/, A/./B and
//      A/foo/../B all become A/B
//TODO: Return the canonical path of the specified filename,
//      eliminating any symbolic links encountered in the path
 
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

#ifdef __APPLE__
#   define _DARWIN_FEATURE_64_BIT_INODE /**/
#endif


/* Header File Inclusion */
#include    <path_internal.h>
#include    <file.h>
#include    <utf8.h>



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

    PATH_DATA *     path_Alloc(
    )
    {
        PATH_DATA       *cbp;
        uint32_t        cbSize = sizeof(PATH_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    PATH_DATA *     path_NewA(
        const
        char            *pStr
    )
    {
        PATH_DATA       *this;
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == pStr) {
            return OBJ_NIL;
        }
        
        this = path_Alloc( );
        this = path_Init(this);
        if (this) {
            if (pStr && utf8_StrLenA(pStr)) {
                eRc = AStr_AppendA((ASTR_DATA *)this, pStr);
                if (ERESULT_HAS_FAILED(eRc)) {
                    obj_Release(this);
                    this = OBJ_NIL;
                }
            }
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    PATH_DATA *     path_NewFromAStr(
        ASTR_DATA       *pStr
    )
    {
        PATH_DATA       *this;
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == pStr) {
            return OBJ_NIL;
        }
        
        this = path_Alloc( );
        this = path_Init(this);
        if (this) {
            eRc = AStr_Append((ASTR_DATA *)this, pStr);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return this;
    }
    
    
    PATH_DATA *     path_NewFromCurrentDirectory(
    )
    {
        PATH_DATA       *this =  OBJ_NIL;
        char            data[512];
        uint32_t        len;
        char            *pBuffer = NULL;
        
        // Do initialization.
#ifdef __MACOSX_ENV__
        pBuffer = getcwd(data, sizeof(data));
#endif
        if (NULL == pBuffer)
            ;
        else {
            len = (uint32_t)strlen(data);
            if (len) {
                this = path_NewA(data);
            }
        }
        
        // Return to caller.
        return this;
    }
    

    
    PATH_DATA *     path_NewFromEnv(
        const
        char            *pStr
    )
    {
        PATH_DATA       *cbp =  OBJ_NIL;
        char            *pData;
        size_t          len;
        
        // Do initialization.
        if (NULL == pStr) {
            return cbp;
        }
        
        pData = getenv(pStr);
        if (NULL == pData)
            ;
        else {
            len = strlen(pData);
            if (len) {
                cbp = path_NewA(pData);
            }
        }
        
        // Return to caller.
        return( cbp );
    }
    
    
    
    PATH_DATA *     path_NewFromWStr(
        WSTR_DATA       *pStr
    )
    {
        PATH_DATA       *cbp;
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == pStr) {
            return OBJ_NIL;
        }
        
        cbp = path_Alloc( );
        cbp = path_Init(cbp);
        if (cbp) {
            eRc = AStr_AppendStrW((ASTR_DATA *)cbp, pStr);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(cbp);
                cbp = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return( cbp );
    }
    
    
    
    PATH_DATA *     path_NewW(
        uint32_t        len,
        const
        int32_t         *pStr
    )
    {
        PATH_DATA       *cbp;
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == pStr) {
            return OBJ_NIL;
        }
        
        cbp = path_Alloc( );
        cbp = path_Init(cbp);
        if (cbp) {
            eRc = AStr_AppendW((ASTR_DATA *)cbp, len, pStr);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(cbp);
                cbp = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return( cbp );
    }
    
    
    
    

    
    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    const
    char *          path_getData(
        PATH_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return AStr_getData((ASTR_DATA *)this);
    }
    


    ASTR_DATA *     path_getAStr(
        PATH_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return (ASTR_DATA *)this;
    }
    
    
    
    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                 A p p e n d  D i r
    //---------------------------------------------------------------
    
    ERESULT         path_AppendDir(
        PATH_DATA		*this,
        ASTR_DATA       *pDir
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pDir) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = path_AppendFileName(this, pDir);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         path_AppendDirA(
        PATH_DATA		*this,
        const
        char            *pDirA
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pDirA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = path_AppendFileNameA(this, pDirA);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                 A p p e n d  E x t A
    //---------------------------------------------------------------
    
    ERESULT         path_AppendExtA(
        PATH_DATA		*cbp,
        const
        char            *pExt
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pExt) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
 
        if (*pExt == '.')
            ;
        else {
            eRc = AStr_AppendA((ASTR_DATA *)cbp, ".");
            if (ERESULT_HAS_FAILED(eRc)) {
                return eRc;
            }
        }
        eRc = AStr_AppendA((ASTR_DATA *)cbp, pExt);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }
        
        eRc = path_Clean(cbp);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                 A p p e n d  F i l e  N a m e
    //---------------------------------------------------------------
    
    ERESULT         path_AppendFileName(
        PATH_DATA		*cbp,
        ASTR_DATA       *pFileName
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pFileName) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = AStr_AppendA((ASTR_DATA *)cbp, "/");
        if (ERESULT_HAS_FAILED(eRc)) {
            (void)AStr_Truncate((ASTR_DATA *)cbp, 0);
            return eRc;
        }
        
        eRc = AStr_Append((ASTR_DATA *)cbp, pFileName);
        if (ERESULT_HAS_FAILED(eRc)) {
            (void)AStr_Truncate((ASTR_DATA *)cbp, 0);
            return eRc;
        }
        
        eRc = path_Clean(cbp);
        if (ERESULT_HAS_FAILED(eRc)) {
            (void)AStr_Truncate((ASTR_DATA *)cbp, 0);
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    ERESULT         path_AppendFileNameA(
        PATH_DATA		*cbp,
        const
        char            *pFileNameA
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pFileNameA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = AStr_AppendA((ASTR_DATA *)cbp, "/");
        if (ERESULT_HAS_FAILED(eRc)) {
            (void)AStr_Truncate((ASTR_DATA *)cbp, 0);
            return eRc;
        }
        
        eRc = AStr_AppendA((ASTR_DATA *)cbp, pFileNameA);
        if (ERESULT_HAS_FAILED(eRc)) {
            (void)AStr_Truncate((ASTR_DATA *)cbp, 0);
            return eRc;
        }
        
        eRc = path_Clean(cbp);
        if (ERESULT_HAS_FAILED(eRc)) {
            (void)AStr_Truncate((ASTR_DATA *)cbp, 0);
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C l e a n
    //---------------------------------------------------------------
    
    ERESULT         path_Clean(
        PATH_DATA		*this
    )
    {
        ERESULT         eRc;
        uint32_t        i;
#ifdef FUTURE_OPTION
        uint32_t        j;
#endif
        int32_t         chr1;
        int32_t         chr2;
        int32_t         chr3;
        char            *pszHome;
#ifdef FUTURE_OPTION
        bool            fMore = true;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (0 == AStr_getLength((ASTR_DATA *)this)) {
            return ERESULT_SUCCESSFUL_COMPLETION;
        }
        
        if ((AStr_getLength((ASTR_DATA *)this)) >= 1) {
            chr1 = AStr_CharGetW((ASTR_DATA *)this, 1);
            if( chr1 == '~' ) {
                pszHome = getenv("HOME");
                if (pszHome && (str_LengthA(pszHome) > 1)) {
                    eRc = AStr_Remove((ASTR_DATA *)this, 1, 1);
                    if (ERESULT_IS_SUCCESSFUL(eRc)) {
                        AStr_InsertA((ASTR_DATA *)this, 1, pszHome);
                    }
                }
                else {
                    pszHome = getenv("HOMEDRIVE");
                    if (pszHome && (str_LengthA(pszHome) > 1)) {
                        const
                        char            *pszPath;
                        pszPath = getenv("HOMEDRIVE");
                    }
                    
                }
            }
        }
        
        for (i=0; i<AStr_getLength((ASTR_DATA *)this); ++i) {
            if ((AStr_getLength((ASTR_DATA *)this) - i) >= 2) {
                chr1 = AStr_CharGetW((ASTR_DATA *)this, i+1);
                chr2 = AStr_CharGetW((ASTR_DATA *)this, i+2);
                if( (chr1 == '/') && (chr2 == '/') ) {
                    eRc = AStr_Remove((ASTR_DATA *)this, (i + 1), 1 );
                    if (ERESULT_HAS_FAILED(eRc)) {
                        ;
                    }
                    continue;
                }
            }
            if ((AStr_getLength((ASTR_DATA *)this) - i) >= 3) {
                chr1 = AStr_CharGetW((ASTR_DATA *)this, i+1);
                chr2 = AStr_CharGetW((ASTR_DATA *)this, i+2);
                chr3 = AStr_CharGetW((ASTR_DATA *)this, i+3);
                if( (chr1 == '/') && (chr2 == '.') && (chr3 == '/') ) {
                    eRc = AStr_Remove((ASTR_DATA *)this, (i + 1), 2 );
                    if (ERESULT_HAS_FAILED(eRc)) {
                        ;
                    }
                    continue;
                }
            }
        }
        
        i = AStr_getLength((ASTR_DATA *)this);
        if (i >= 3) {
            chr1 = AStr_CharGetW((ASTR_DATA *)this, i-2);
            chr2 = AStr_CharGetW((ASTR_DATA *)this, i-1);
            chr3 = AStr_CharGetW((ASTR_DATA *)this, i);
            if( (chr1 == '/') && (chr2 == '.') && (chr3 == '/') ) {
                eRc = AStr_Remove((ASTR_DATA *)this, (i - 2), 2 );
                if (ERESULT_HAS_FAILED(eRc)) {
                    ;
                }
            }
        }

        for (;;) {
            i = AStr_getLength((ASTR_DATA *)this);
            chr1 = AStr_CharGetW((ASTR_DATA *)this, i);
            if ((chr1 == '/') && (i > 1)) {
                eRc = AStr_Remove((ASTR_DATA *)this, i, 1 );
                if (ERESULT_HAS_FAILED(eRc)) {
                    ;
                }
            }
            else
                break;
        }
        
#ifdef FUTURE_OPTION
        // Expand Environment variables.
        while (fMore) {
            fMore = false;
            for (i=0; i<AStr_getLength((ASTR_DATA *)this); ++i) {
                if ((AStr_getLength((ASTR_DATA *)this) - i) >= 3) {
                    chr1 = AStr_CharGetW((ASTR_DATA *)this, i+1);
                    chr2 = AStr_CharGetW((ASTR_DATA *)this, i+2);
                    if( (chr1 == '$') && (chr2 == '{') ) {
                        ASTR_DATA       *pName = AStr_New();
                        if (OBJ_NIL == pName) {
                            return ERESULT_INVALID_DATA;
                        }
                        for (j=i+2; j<AStr_getLength((ASTR_DATA *)this); ++j) {
                            chr1 = AStr_CharGetW((ASTR_DATA *)this, j+1);
                            if( chr1 == '}' ) {
                                fMore = true;
                                break;
                            }
                        }
                        if (fMore) {
                            
                            eRc =   pwr2Array_Delete(
                                                     (PWR2ARRAY_DATA *)this,
                                                     (i + 1),
                                                     (j - i)
                                    );
                        }
                        else {
                            return ERESULT_INVALID_DATA;
                        }
                        eRc =   pwr2Array_Delete(
                                                 (PWR2ARRAY_DATA *)this,
                                                 (i + 1),
                                                 1
                                                 );
                        if (ERESULT_HAS_FAILED(eRc)) {
                            ;
                        }
                        continue;
                    }
                }
            }
        }
#endif
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                       C o m p a r e
    //---------------------------------------------------------------
    
    ERESULT         path_Compare(
        PATH_DATA		*cbp,
        PATH_DATA       *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = AStr_Compare( (ASTR_DATA *)cbp, (ASTR_DATA *)pOther );
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         path_CompareA(
        PATH_DATA		*this,
        const
        char            *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = AStr_CompareA( (ASTR_DATA *)this, pOther );
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         path_CompareRightA(
        PATH_DATA		*this,
        const
        char            *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = AStr_CompareRightA((ASTR_DATA *)this, pOther);
        
        // Return to caller.
        return eRc;
    }
    
    
   
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    PATH_DATA *   path_Copy(
        PATH_DATA       *this
    )
    {
        PATH_DATA       *pOther;
        
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = path_NewA(path_getData(this));
        
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                 C r e a t e  E m p t y
    //---------------------------------------------------------------
    
    ERESULT         path_CreateEmpty(
        PATH_DATA		*this
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = path_IsExisting(this);
        if (eRc == ERESULT_SUCCESS) {
            return ERESULT_FILE_ALREADY_EXISTS;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       C S t r i n g A
    //---------------------------------------------------------------
    
    char *          path_CStringA(
        PATH_DATA		*cbp
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate( cbp ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        // Return to caller.
        return AStr_CStringA((ASTR_DATA *)cbp, NULL);
    }
    
    
    
    //---------------------------------------------------------------
    //                          D a t e s
    //---------------------------------------------------------------
    
    ERESULT         path_DateLastUpdated(
       PATH_DATA        *this,
       DATETIME_DATA    **ppDate
    )
    {
        char            *pStr = NULL;
#ifdef __MACOSX_ENV__
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;
        DATETIME_DATA   *pTime = OBJ_NIL;
        
        // Do initialization.
        if (ppDate) {
            *ppDate = pTime;
        }
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pStr = (char *)AStr_getData((ASTR_DATA *)this);
#ifdef __MACOSX_ENV__
        iRc = stat(pStr, &statBuffer);
        if (0 == iRc) {
            pTime = dateTime_NewFromTimeT(statBuffer.st_mtimespec.tv_sec);
            if (pTime) {
                eRc = ERESULT_SUCCESS;
                if (ppDate) {
                    *ppDate = pTime;
                }
            }
            else {
                eRc = ERESULT_GENERAL_FAILURE;
            }
        }
        else
            eRc = ERESULT_PATH_NOT_FOUND;
#endif
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            path_Dealloc(
        OBJ_ID          objId
    )
    {
        PATH_DATA       *cbp = objId;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !path_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        AStr_Dealloc( objId );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                       F i l e  S i z e
    //---------------------------------------------------------------
    
    ERESULT         path_FileSize(
        PATH_DATA       *this,
        int64_t         *pFileSize
    )
    {
        char            *pStr = NULL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pStr = (char *)AStr_getData((ASTR_DATA *)this);
        if (pStr) {
            eRc = file_SizeA(pStr, pFileSize);
        }
        else
            eRc = ERESULT_DATA_ERROR;
        
        // Return to caller.
        return eRc;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PATH_DATA *     path_Init(
        PATH_DATA      *this
    )
    {
        uint16_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (PATH_DATA *)AStr_Init( (ASTR_DATA *)this );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_PATH);
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&path_Vtbl);
        
    #ifdef NDEBUG
    #else
        if( !path_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s D i r
    //---------------------------------------------------------------
    
    ERESULT         path_IsDir(
        PATH_DATA		*cbp
    )
    {
        char            *pStr = NULL;
#ifdef __MACOSX_ENV__
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pStr = (char *)AStr_getData((ASTR_DATA *)cbp);
#ifdef __MACOSX_ENV__
        iRc = stat(pStr, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFDIR) {
                eRc = ERESULT_SUCCESS;
            }
            else
                eRc = ERESULT_FAILURE_FALSE;
        }
        else
            eRc = ERESULT_PATH_NOT_FOUND;
#endif
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s E x i s t i n g
    //---------------------------------------------------------------
    
    ERESULT         path_IsExisting(
        PATH_DATA		*cbp
    )
    {
        const
        char            *pStr = NULL;
#ifdef __MACOSX_ENV__
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pStr = AStr_getData((ASTR_DATA *)cbp);
#ifdef __MACOSX_ENV__
        iRc = stat(pStr, &statBuffer);
        if (0 == iRc) {
            eRc = ERESULT_SUCCESS;
        }
        else
            eRc = ERESULT_PATH_NOT_FOUND;
#endif
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s F i l e
    //---------------------------------------------------------------
    
    ERESULT         path_IsFile(
        PATH_DATA		*cbp
    )
    {
        const
        char            *pStr = NULL;
#ifdef __MACOSX_ENV__
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pStr = AStr_getData((ASTR_DATA *)cbp);
#ifdef __MACOSX_ENV__
        iRc = stat(pStr, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFREG) {
                eRc = ERESULT_SUCCESSFUL_COMPLETION;
            }
            else
                eRc = ERESULT_FAILURE_FALSE;
        }
        else
            eRc = ERESULT_PATH_NOT_FOUND;
#endif
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s L i n k
    //---------------------------------------------------------------
    
    ERESULT         path_IsLink(
        PATH_DATA		*cbp
    )
    {
        const
        char            *pStr = NULL;
#ifdef __MACOSX_ENV__
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pStr = AStr_getData((ASTR_DATA *)cbp);
#ifdef __MACOSX_ENV__
        iRc = stat(pStr, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFLNK) {
                eRc = ERESULT_SUCCESS;
            }
            else
                eRc = ERESULT_FAILURE_FALSE;
        }
        else
            eRc = ERESULT_PATH_NOT_FOUND;
#endif
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     M a k e  F i l e
    //---------------------------------------------------------------
    
    ERESULT         path_MakeFile(
        PATH_DATA		*cbp,
        ASTR_DATA       *pFileName,
        ASTR_DATA       *pFileExt
    )
    {
        ERESULT         eRc;
        int32_t         chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = AStr_Truncate((ASTR_DATA *)cbp, 0);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }
        
        if (pFileName) {
            eRc = AStr_Append((ASTR_DATA *)cbp, pFileName);
            if (ERESULT_HAS_FAILED(eRc)) {
                (void)AStr_Truncate((ASTR_DATA *)cbp, 0);
                return eRc;
            }
        }
        
        if (pFileExt) {
            chr = AStr_CharGetW(pFileExt, 1);
            if (chr == '.')
                ;
            else {
                eRc = AStr_AppendA((ASTR_DATA *)cbp, ".");
                if (ERESULT_HAS_FAILED(eRc)) {
                    (void)AStr_Truncate((ASTR_DATA *)cbp, 0);
                    return eRc;
                }
            }
            eRc = AStr_Append((ASTR_DATA *)cbp, pFileExt);
            if (ERESULT_HAS_FAILED(eRc)) {
                (void)AStr_Truncate((ASTR_DATA *)cbp, 0);
                return eRc;
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                     M a k e  P a t h
    //---------------------------------------------------------------
    
    ERESULT         path_MakePath(
        PATH_DATA		*this,
        ASTR_DATA       *pDrive,
        PATH_DATA       *pDir,
        PATH_DATA       *pFileName
        )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = AStr_Truncate((ASTR_DATA *)this, 0);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }
        
        if (pDrive) {
            eRc = AStr_Append((ASTR_DATA *)this, pDrive);
            if (ERESULT_HAS_FAILED(eRc)) {
                (void)AStr_Truncate((ASTR_DATA *)this, 0);
                return eRc;
            }
            eRc = AStr_AppendA((ASTR_DATA *)this, ":");
            if (ERESULT_HAS_FAILED(eRc)) {
                (void)AStr_Truncate((ASTR_DATA *)this, 0);
                return eRc;
            }
        }
        
        if (pDir) {
            eRc = AStr_Append((ASTR_DATA *)this, (ASTR_DATA *)pDir);
            if (ERESULT_HAS_FAILED(eRc)) {
                (void)AStr_Truncate((ASTR_DATA *)this, 0);
                return eRc;
            }
            eRc = AStr_AppendA((ASTR_DATA *)this, "/");
            if (ERESULT_HAS_FAILED(eRc)) {
                (void)AStr_Truncate((ASTR_DATA *)this, 0);
                return eRc;
            }
        }
        
        if (pFileName) {
            eRc = AStr_Append((ASTR_DATA *)this, (ASTR_DATA *)pFileName);
            if (ERESULT_HAS_FAILED(eRc)) {
                (void)AStr_Truncate((ASTR_DATA *)this, 0);
                return eRc;
            }
        }
        
        eRc = path_Clean(this);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          M a t c h
    //---------------------------------------------------------------
    
    ERESULT         path_MatchA(
        PATH_DATA       *this,
        const
        char            *pPattern
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc =   AStr_MatchA((ASTR_DATA *)this, pPattern);
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     S p l i t  F i l e
    //---------------------------------------------------------------
    
    ERESULT         path_SplitFile(
        PATH_DATA		*cbp,
        ASTR_DATA       **ppFileName,
        ASTR_DATA       **ppFileExt
    )
    {
        ERESULT         eRc;
        uint32_t        index2;
        uint32_t        begin = 1;
        uint32_t        end;
        uint32_t        begDir = 1;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        index2 = 0;
        eRc = AStr_CharFindPrevW((ASTR_DATA *)cbp, &index2, '.');
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            begin = begDir;
            end = index2 - 1;
            if (ppFileName) {
                if (begin <= end) {
                    eRc =   AStr_Mid(
                                    (ASTR_DATA *)cbp,
                                    begin,
                                    (end - begin + 1),
                                    ppFileName
                            );
                }
                else {
                    *ppFileName = OBJ_NIL;
                }
            }
            begin = index2 + 1;
            end = AStr_getLength((ASTR_DATA *)cbp);
            if (ppFileExt) {
                if (begin <= end) {
                    eRc =   AStr_Mid(
                                      (ASTR_DATA *)cbp,
                                      begin,
                                      (end - begin + 1),
                                      ppFileExt
                            );
                }
                else {
                    *ppFileExt = OBJ_NIL;
                }
            }
        }
        else {
            if (ppFileName) {
                begin = begDir;
                end = AStr_getLength((ASTR_DATA *)cbp);
                if (begin <= end) {
                    eRc =   AStr_Mid(
                                    (ASTR_DATA *)cbp,
                                    begin,
                                    (end - begin + 1),
                                    ppFileName
                            );
                }
                else {
                    *ppFileName = OBJ_NIL;
                }
            }
            if (ppFileExt) {
                *ppFileExt = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                     S p l i t  P a t h
    //---------------------------------------------------------------
    
    ERESULT         path_SplitPath(
        PATH_DATA		*this,
        ASTR_DATA       **ppDrive,
        PATH_DATA       **ppDir,
        PATH_DATA       **ppFileName
    )
    {
        ERESULT         eRc;
        uint32_t        index;
        uint32_t        begin = 1;
        uint32_t        end;
        uint32_t        begDir = 1;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        index = 0;
        eRc = AStr_CharFindNextW((ASTR_DATA *)this, &index, ':');
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            begin = 1;
            end = index - 1;
            if (ppDrive) {
                if (begin <= end) {
                    if (ppDrive) {
                        eRc =   AStr_Mid(
                                    (ASTR_DATA *)this,
                                    begin,
                                    (end - begin + 1),
                                    ppDrive
                                );
                        BREAK_FAILED(eRc);
                    }
                }
                else {
                    if (ppDrive) {
                        *ppDrive = OBJ_NIL;
                    }
                }
            }
            begDir = index + 1;
        }
        else {
            if (ppDrive) {
                *ppDrive = OBJ_NIL;
            }
        }
        
        index = 0;
        eRc = AStr_CharFindPrevW((ASTR_DATA *)this, &index, '/');
        if (ERESULT_IS_SUCCESSFUL(eRc)) {     // *** Directory is present ***
            if (ppDir) {
                *ppDir = OBJ_NIL;
                begin = begDir;
                end = index - 1;
                if (begin <= end) {
                    ASTR_DATA      *pStr = OBJ_NIL;
                    if (ppDir) {
                        eRc =   AStr_Mid(
                                        (ASTR_DATA *)this,
                                        begin,
                                        (end -  begin + 1),
                                        &pStr
                                );
                        BREAK_FAILED(eRc);
                        *ppDir = path_NewFromAStr(pStr);
                        path_Clean(*ppDir);
                        obj_Release(pStr);
                    }
                }
                else if (begin == index) {
                    if (ppDir) {
                        *ppDir = path_NewA("/");
                    }
                }
            }
            begDir = index + 1;
        }
        else {                          // *** NO Directory is present ***
            if (ppDir) {
                *ppDir = OBJ_NIL;
            }
        }
        
        if (ppFileName) {
            *ppFileName = OBJ_NIL;
            begin = begDir;
            end = AStr_getLength((ASTR_DATA *)this);
            if (begin <= end) {
                ASTR_DATA      *pStr;
                if (ppFileName) {
                    eRc = AStr_Right((ASTR_DATA *)this, (end - begin + 1), &pStr);
                    if (ERESULT_IS_SUCCESSFUL(eRc)) {
                        *ppFileName = path_NewFromAStr(pStr);
                        path_Clean(*ppFileName);
                        obj_Release(pStr);
                    }
                }
            }
        }
    
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      T o  B a s h
    //---------------------------------------------------------------
    
    ERESULT         path_ToBash(
        PATH_DATA		*this,
        ASTR_DATA       **ppAStr
    )
    {
        uint32_t        i;
        uint32_t        lenStr;
        int32_t         chr;
        ASTR_DATA       *pStr = AStr_New();
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == ppAStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (OBJ_NIL == pStr) {
            eRc = ERESULT_MEMORY_EXCEEDED;
            goto eom;
        }
        
        // Get data length needed.
        lenStr = AStr_getLength((ASTR_DATA *)this);
        if (0 == lenStr) {
            return ERESULT_BAD_LENGTH;
        }
        for (i=0; i<lenStr; ++i) {
            chr = AStr_CharGetW((ASTR_DATA *)this, i+1);
            if (chr == ' ') {
                AStr_AppendCharA(pStr, '\\');
                AStr_AppendCharA(pStr, chr);
            }
            else {
                AStr_AppendCharA(pStr, chr);
            }
        }
        
        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        if (ppAStr) {
            *ppAStr = pStr;
        }
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     path_ToDebugString(
        PATH_DATA       *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(path) \n",
                     this
                     );
        AStr_AppendA(pStr, str);
        
        pWrkStr = AStr_ToDebugString((ASTR_DATA *)this, indent+3 );
        AStr_Append(pStr, pWrkStr);
        obj_Release(pWrkStr);
        
        j = snprintf( str, sizeof(str), " %p(path)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      T o  W i n
    //---------------------------------------------------------------
    
    ERESULT         path_ToWin(
        PATH_DATA		*this,
        ASTR_DATA       **ppAStr
    )
    {
        uint32_t        i;
        uint32_t        lenStr;
        int32_t         chr;
        ASTR_DATA       *pStr = AStr_New();
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == ppAStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (OBJ_NIL == pStr) {
            eRc = ERESULT_MEMORY_EXCEEDED;
            goto eom;
        }
        
        // Get data length needed.
        lenStr = AStr_getLength((ASTR_DATA *)this);
        if (0 == lenStr) {
            return ERESULT_BAD_LENGTH;
        }
        for (i=0; i<lenStr; ++i) {
            chr = AStr_CharGetW((ASTR_DATA *)this, i+1);
            if (chr == '/') {
                AStr_AppendCharA(pStr, '\\');
            }
            else {
                AStr_AppendCharA(pStr, chr);
            }
        }
        
        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        if (ppAStr) {
            *ppAStr = pStr;
        }
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            path_Validate(
        PATH_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp, OBJ_IDENT_PATH) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(PATH_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


