// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   dir.c
 *	Generated 06/22/2015 17:14:45
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

#ifdef __APPLE__
#   define _DARWIN_FEATURE_64_BIT_INODE /**/
#endif


/* Header File Inclusion */
#include    <dir_internal.h>
#include    <ObjEnum_internal.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    bool            enumScanner(
        void            *pObj,
        DIRENTRY_DATA   *pDir
    )
    {
        ERESULT         eRc;
        OBJENUM_DATA    *pEnum = (OBJENUM_DATA *)pObj;
        DIRENTRY_DATA   *pEntry;
        
        pEntry = DirEntry_Copy(pDir);
        if (pEntry) {
            eRc = ObjEnum_AppendObj(pEnum, pEntry);
            if (ERESULT_FAILED(eRc)) {
                return false;
            }
            obj_Release(pEntry);
            //pEntry = OBJ_NIL;
        }
        else {
            return false;
        }
        
        return true;
    }

    
    
    static
    bool            scan_rm(
        void            *pObj,
        DIRENTRY_DATA   *pEntry
    )
    {
        //DIR_DATA        *this = pObj;
        //ERESULT         eRc;
        
        
        return true;
    }
    
    
    


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    DIR_DATA *     dir_Alloc(
    )
    {
        DIR_DATA        *this;
        uint32_t        cbSize = sizeof(DIR_DATA);
        
        // Do initialization.
        
        this = obj_Alloc(cbSize);
        
        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    //                       I s D i r A
    //---------------------------------------------------------------
    
    ERESULT         dir_IsDirA(
        const
        char            *pPath
    )
    {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;
        
        if (NULL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pPath, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFDIR) {
                eRc = ERESULT_SUCCESS;
            }
            else
                eRc = ERESULT_FAILURE_FALSE;
        }
        else {
            eRc = ERESULT_PATH_NOT_FOUND;
        }
#endif
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s E x i s t i n g A
    //---------------------------------------------------------------
    
    ERESULT         dir_IsExistingA(
        const
        char            *pPath
    )
    {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;
        
        if (NULL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pPath, &statBuffer);
        if (0 == iRc) {
            eRc = ERESULT_SUCCESS;
        }
        else {
            eRc = ERESULT_PATH_NOT_FOUND;
        }
#endif
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s F i l e A
    //---------------------------------------------------------------
    
    ERESULT         dir_IsFileA(
        const
        char            *pPath
    )
    {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;
        
        if (NULL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pPath, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFREG) {
                eRc = ERESULT_SUCCESS;
            }
            else {
                eRc = ERESULT_FAILURE_FALSE;
            }
        }
        else {
            eRc = ERESULT_PATH_NOT_FOUND;
        }
#endif
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s L i n k A
    //---------------------------------------------------------------
    
    ERESULT         dir_IsLinkA(
        const
        char            *pPath
    )
    {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;
        
        if (NULL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pPath, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFLNK) {
                eRc = ERESULT_SUCCESS;
            }
            else {
                eRc = ERESULT_FAILURE_FALSE;
            }
        }
        else {
            eRc = ERESULT_PATH_NOT_FOUND;
        }
#endif
        
        // Return to caller.
        return eRc;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        dir_getPriority(
        DIR_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dir_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            dir_setPriority(
        DIR_DATA        *cbp,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !dir_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    uint32_t        dir_getSize(
        DIR_DATA        *this
    )
    {
#ifdef NDEBUG
#else
        if( !dir_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return( 0 );
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            dir_Dealloc(
        OBJ_ID          objId
    )
    {
        DIR_DATA        *this = objId;
        //bool            fRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !dir_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        //fRc = dir_Disable( cbp );

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                       E n u m  D i r
    //---------------------------------------------------------------
    
    OBJENUM_DATA *  dir_EnumDir(
        DIR_DATA        *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;
        OBJENUM_DATA    *pEnum = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !dir_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pEnum = ObjEnum_New();
        if( OBJ_NIL == pEnum ) {
            return OBJ_NIL;
        }
        
        eRc = dir_ScanDir(this, pPath, &enumScanner, pEnum);
        if (ERESULT_FAILED(eRc)) {
            obj_Release(pEnum);
            pEnum = OBJ_NIL;
            return OBJ_NIL;
        }
        
        eRc = ObjEnum_SortAscending(pEnum);
        
        // Return to caller.
        return pEnum;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    DIR_DATA *      dir_Init(
        DIR_DATA        *this
    )
    {
        uint32_t        cbSize = sizeof(DIR_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, cbSize, OBJ_IDENT_DIR );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_FAT12); // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&dir_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);

    #ifdef NDEBUG
    #else
        if( !dir_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(sizeof(DIR_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s D i r
    //---------------------------------------------------------------
    
    ERESULT         dir_IsDir(
        DIR_DATA		*this,
        PATH_DATA       *pPath
    )
    {
        char            *pStr = NULL;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dir_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pPath ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pStr = AStr_CStringA((ASTR_DATA *)pPath, NULL);
        if (pStr) {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
            iRc = stat(pStr, &statBuffer);
            if (0 == iRc) {
                if ((statBuffer.st_mode & S_IFMT) == S_IFDIR) {
                    eRc = ERESULT_SUCCESS;
                }
                else
                    eRc = ERESULT_FAILURE_FALSE;
            }
            else {
                eRc = ERESULT_PATH_NOT_FOUND;
            }
#endif
            mem_Free(pStr);
            pStr = NULL;
        }
        else {
            eRc = ERESULT_DATA_ERROR;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       M a k e D i r
    //---------------------------------------------------------------
    
    ERESULT         dir_MakeDir(
        DIR_DATA		*this,
        PATH_DATA       *pPath,
        uint16_t        mode
    )
    {
        char            *pStr = NULL;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        int             iRc;
#endif
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dir_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pPath ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = path_IsExisting(pPath);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            return ERESULT_PATH_ALREADY_EXISTS;
        }
        
        pStr = AStr_CStringA((ASTR_DATA *)pPath, NULL);
        if (pStr) {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
            iRc = mkdir(pStr, mode);
            if (0 == iRc) {
                eRc = ERESULT_SUCCESS;
            }
            else {
                eRc = ERESULT_CANNOT_MAKE_DIRECTORY;
            }
#endif
            mem_Free(pStr);
            pStr = NULL;
        }
        else {
            eRc = ERESULT_DATA_ERROR;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       S c a n D i r
    //---------------------------------------------------------------
    
    ERESULT         dir_ScanDir(
        DIR_DATA		*this,
        PATH_DATA       *pPath,
        bool            (*pScanner)(void *, DIRENTRY_DATA *),
        void            *pObject
    )
    {
        ERESULT         eRc;
        char            *pDirA;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct dirent   *pDirent;
        DIR             *pDirectory;
        bool            fRc;
#endif
        ASTR_DATA       *pDrive = OBJ_NIL;
        PATH_DATA       *pDir = OBJ_NIL;
        PATH_DATA       *pFileName = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !dir_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pPath) || !(OBJ_IDENT_PATH == obj_getType(pPath)) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if( NULL == pScanner ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = path_IsDir(pPath);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_PATH_NOT_FOUND;
        }
        
        eRc = path_SplitPath(pPath, &pDrive, &pDir, OBJ_NIL);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_PATH_NOT_FOUND;
        }

#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        pDirA = AStr_CStringA((ASTR_DATA *)pPath, NULL);
        if (pDirA) {
            pDirectory = opendir(pDirA);
            mem_Free(pDirA);
            pDirA = NULL;
            if (NULL == pDirectory) {
                return ERESULT_PATH_NOT_FOUND;
            }
        }
        else {
            return ERESULT_GENERAL_FAILURE;
        }
        
        while ((pDirent = readdir(pDirectory)) != NULL) {
            DIRENTRY_DATA   *pEntry;
            if ((pDirent->d_namlen == 1) && (0 == strcmp(".", pDirent->d_name))) {
                continue;
            }
            if ((pDirent->d_namlen == 2) && (0 == strcmp("..", pDirent->d_name))) {
                continue;
            }

            pFileName = path_NewA(pDirent->d_name);
            if (OBJ_NIL == pFileName) {
                DEBUG_BREAK();
                closedir(pDirectory);
                return ERESULT_OUT_OF_MEMORY;
            }
            pEntry = DirEntry_NewWithData(pDrive, pDir, pFileName, pDirent->d_type);
            if( OBJ_NIL == pEntry ) {
                DEBUG_BREAK();
                closedir(pDirectory);
                return ERESULT_INVALID_PARAMETER;
            }
            obj_Release(pFileName);
            pFileName = OBJ_NIL;

            fRc = (*pScanner)(pObject, pEntry);
            obj_Release(pEntry);
            pEntry = OBJ_NIL;
            if (!fRc) {
                break;
            }
        }
        
        if (EOF == closedir(pDirectory)) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
            obj_Release(pDir);
            pDir = OBJ_NIL;
            return ERESULT_GENERAL_FAILURE;
        }
        
#endif
        
        // Return to caller.
        obj_Release(pDrive);
        pDrive = OBJ_NIL;
        obj_Release(pDir);
        pDir = OBJ_NIL;
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     dir_ToDebugString(
        DIR_DATA        *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY
        ASTR_DATA       *pWrkStr;
#endif
        
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
                     "{%p(dir) ",
                     this
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
        
        j = snprintf(str, sizeof(str), " %p(dir)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            dir_Validate(
        DIR_DATA      *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_DIR) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(DIR_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


