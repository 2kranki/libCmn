// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   DirEntry.c
 *	Generated 01/28/2020 23:55:59
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
#include        <DirEntry_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
    ERESULT         DirEntry_CompleteFromStat (
        DIRENTRY_DATA   *this,
        struct stat     *pStatBuffer
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        DATETIME_DATA   *pTime = OBJ_NIL;

        // Do initialization.

        pTime = DateTime_NewFromTimeT(pStatBuffer->st_birthtimespec.tv_sec);
        DirEntry_setCreationTime(this, pTime);
        obj_Release(pTime);
        pTime = OBJ_NIL;
        pTime = DateTime_NewFromTimeT(pStatBuffer->st_mtimespec.tv_sec);
        DirEntry_setModifiedTime(this, pTime);
        obj_Release(pTime);
        pTime = OBJ_NIL;
        this->attr = pStatBuffer->st_mode;      //TODO: mode translate to generic flags
        //                                      // that we define
        this->userID = pStatBuffer->st_uid;
        this->groupID = pStatBuffer->st_gid;
        this->genNum = pStatBuffer->st_gen;
        this->fileSize = pStatBuffer->st_size;

        // Return to caller.
        return eRc;
    }
#endif





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    DIRENTRY_DATA *     DirEntry_Alloc (
        void
    )
    {
        DIRENTRY_DATA       *this;
        uint32_t        cbSize = sizeof(DIRENTRY_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    DIRENTRY_DATA *     DirEntry_New (
        void
    )
    {
        DIRENTRY_DATA       *this;
        
        this = DirEntry_Alloc( );
        if (this) {
            this = DirEntry_Init(this);
        } 
        return this;
    }



    DIRENTRY_DATA * DirEntry_NewA (
        const
        char            *pPathA,
        uint8_t         type
    )
    {
        ERESULT         eRc;
        DIRENTRY_DATA   *this;
        PATH_DATA       *pPath  = OBJ_NIL;

        this = DirEntry_New();
        if (OBJ_NIL == this) {
            return this;
        }

        pPath = Path_NewA(pPathA);
        if (OBJ_NIL == pPath) {
            obj_Release(this);
            return OBJ_NIL;
        }
        eRc = Path_Clean(pPath);
        this->pFullPath = pPath;
        this->type = type;

        // Return to caller.
        return this;
    }



    DIRENTRY_DATA * DirEntry_NewPathA_Stat (
        const
        char            *pPathA
    )
    {
        ERESULT         eRc;
        DIRENTRY_DATA   *this;
        PATH_DATA       *pPath  = OBJ_NIL;

        this = DirEntry_New();
        if (OBJ_NIL == this) {
            return this;
        }

        pPath = Path_NewA(pPathA);
        if (OBJ_NIL == pPath) {
            obj_Release(this);
            return OBJ_NIL;
        }
        eRc = Path_Clean(pPath);
        this->pFullPath = pPath;
        eRc = DirEntry_Complete(this);

        // Return to caller.
        return this;
    }



    DIRENTRY_DATA * DirEntry_NewWithData (
        ASTR_DATA       *pDrive,
        PATH_DATA       *pDir,
        PATH_DATA       *pFileName,         // includes file extension
        uint8_t         type
    )
    {
        ERESULT         eRc;
        DIRENTRY_DATA   *this;
        PATH_DATA       *pPath  = OBJ_NIL;

        this = DirEntry_New();
        if (OBJ_NIL == this) {
            return this;
        }

        pPath = Path_New( );
        if (pPath) {
            eRc = Path_MakePath(pPath, pDrive, pDir, pFileName);
            if (!ERESULT_FAILED(eRc)) {
                if (type == DIRENTRY_TYPE_DIR) {
                    if (AStr_CharGetLastW32(Path_getAStr(pPath)) == '/')
                        ;
                    else {
                        eRc = AStr_AppendA(Path_getAStr(pPath), "/");
                    }
                }
                eRc = Path_Clean(pPath);
                DirEntry_setFullPath(this, pPath);
            }
            obj_Release(pPath);
            pPath = OBJ_NIL;
        } else {
            obj_Release(this);
            return OBJ_NIL;
        }
        this->type = type;

        // Return to caller.
        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  C r e a t i o n  T i m e
    //---------------------------------------------------------------

    DATETIME_DATA * DirEntry_getCreationTime (
        DIRENTRY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pCreationTime;
    }

    bool            DirEntry_setCreationTime (
        DIRENTRY_DATA   *this,
        DATETIME_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pCreationTime) {
            obj_Release(this->pCreationTime);
        }
        this->pCreationTime = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //          E x t e n d e d  A t t r i b u t e s  S i z e
    //---------------------------------------------------------------

    uint32_t        DirEntry_getEASize (
        DIRENTRY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->eaSize;
    }


    bool            DirEntry_setEASize (
        DIRENTRY_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->eaSize = value;
        return true;
    }



    //---------------------------------------------------------------
    //                      F u l l  P a t h
    //---------------------------------------------------------------

    PATH_DATA *     DirEntry_getFullPath (
        DIRENTRY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pFullPath;
    }

    bool            DirEntry_setFullPath (
        DIRENTRY_DATA   *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pFullPath) {
            obj_Release(this->pFullPath);
        }
        this->pFullPath = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //               G e n e r a t i o n  N u m b e r
    //---------------------------------------------------------------

    uint32_t        DirEntry_getGenerationNumber (
        DIRENTRY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->genNum;
    }

    bool            DirEntry_setGenerationNumber (
        DIRENTRY_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->genNum = value;
        return true;
    }



    //---------------------------------------------------------------
    //               G r o u p  I d e n t i f i e r
    //---------------------------------------------------------------

    uint32_t        DirEntry_getGroupID (
        DIRENTRY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->groupID;
    }

    bool            DirEntry_setGroupID (
        DIRENTRY_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->groupID = value;
        return true;
    }



    //---------------------------------------------------------------
    //      L a s t  D a t a  M o d i f i c a t i o n  T i m e
    //---------------------------------------------------------------

    DATETIME_DATA * DirEntry_getModifiedTime (
        DIRENTRY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pModifiedTime;
    }

    bool            DirEntry_setModifiedTime (
        DIRENTRY_DATA   *this,
        DATETIME_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pModifiedTime) {
            obj_Release(this->pModifiedTime);
        }
        this->pModifiedTime = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //             N e x t  L i n k e d  D i r / F i l e
    //---------------------------------------------------------------

    DIRENTRY_DATA * DirEntry_getNext (
        DIRENTRY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pNext;
    }

    bool            DirEntry_setNext (
        DIRENTRY_DATA   *this,
        DIRENTRY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pNext) {
            obj_Release(this->pNext);
        }
        this->pNext = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                  S h o r t  F i l e  N a m e
    //---------------------------------------------------------------

    ASTR_DATA *     DirEntry_getShortName (
        DIRENTRY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pShortName;
    }

    bool            DirEntry_setShortName (
        DIRENTRY_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pShortName) {
            obj_Release(this->pShortName);
        }
        this->pShortName = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        DirEntry_getSize (
        DIRENTRY_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //      L a s t  S t a t u s  C h a n g e  T i m e
    //---------------------------------------------------------------

    DATETIME_DATA * DirEntry_getStatusChangeTime (
        DIRENTRY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pStatusChangeTime;
    }

    bool            DirEntry_setStatusChangeTime (
        DIRENTRY_DATA   *this,
        DATETIME_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pStatusChangeTime) {
            obj_Release(this->pStatusChangeTime);
        }
        this->pStatusChangeTime = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  DirEntry_getSuperVtbl (
        DIRENTRY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                             T y p e
    //---------------------------------------------------------------

    uint16_t        DirEntry_getType (
        DIRENTRY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->type;
    }

    bool            DirEntry_setType (
        DIRENTRY_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->type = value;
        return true;
    }



    //---------------------------------------------------------------
    //               U s e r  I d e n t i f i e r
    //---------------------------------------------------------------

    uint32_t        DirEntry_getUserID (
        DIRENTRY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->userID;
    }

    bool            DirEntry_setUserID (
        DIRENTRY_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->userID = value;
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
        ERESULT eRc = DirEntry_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another DIRENTRY object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         DirEntry_Assign (
        DIRENTRY_DATA		*this,
        DIRENTRY_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!DirEntry_Validate(pOther)) {
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
        (void)DirEntry_setFullPath(pOther, OBJ_NIL);
        (void)DirEntry_setNext(pOther, OBJ_NIL);
        (void)DirEntry_setShortName(pOther, OBJ_NIL);
        (void)DirEntry_setCreationTime(pOther, OBJ_NIL);
        (void)DirEntry_setModifiedTime(pOther, OBJ_NIL);
        (void)DirEntry_setStatusChangeTime(pOther, OBJ_NIL);

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pFullPath) {
            if (obj_getVtbl(this->pFullPath)->pCopy) {
                pOther->pFullPath = obj_getVtbl(this->pFullPath)->pCopy(this->pFullPath);
            }
            else {
                obj_Retain(this->pFullPath);
                pOther->pFullPath = this->pFullPath;
            }
        }
        if (this->pNext) {
            if (obj_getVtbl(this->pNext)->pCopy) {
                pOther->pNext = obj_getVtbl(this->pNext)->pCopy(this->pNext);
            }
            else {
                obj_Retain(this->pNext);
                pOther->pNext = this->pNext;
            }
        }
        if (this->pShortName) {
            if (obj_getVtbl(this->pShortName)->pCopy) {
                pOther->pShortName = obj_getVtbl(this->pShortName)->pCopy(this->pShortName);
            }
            else {
                obj_Retain(this->pShortName);
                pOther->pShortName = this->pShortName;
            }
        }
        if (this->pCreationTime) {
            if (obj_getVtbl(this->pCreationTime)->pCopy) {
                pOther->pCreationTime =
                        obj_getVtbl(this->pCreationTime)->pCopy(this->pCreationTime);
            }
            else {
                obj_Retain(this->pCreationTime);
                pOther->pCreationTime = this->pCreationTime;
            }
        }
        if (this->pModifiedTime) {
            if (obj_getVtbl(this->pModifiedTime)->pCopy) {
                pOther->pModifiedTime =
                        obj_getVtbl(this->pModifiedTime)->pCopy(this->pModifiedTime);
            }
            else {
                obj_Retain(this->pModifiedTime);
                pOther->pModifiedTime = this->pModifiedTime;
            }
        }
        if (this->pStatusChangeTime) {
            if (obj_getVtbl(this->pStatusChangeTime)->pCopy) {
                pOther->pStatusChangeTime =
                    obj_getVtbl(this->pStatusChangeTime)->pCopy(this->pStatusChangeTime);
            }
            else {
                obj_Retain(this->pStatusChangeTime);
                pOther->pStatusChangeTime = this->pStatusChangeTime;
            }
        }

        // Copy other data from this object to other.
        pOther->type     = this->type;
        pOther->fCompleted = this->fCompleted;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        pOther->fileSize = this->fileSize;
#endif
#if     defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        pOther->fileSize = this->fileSize;
#endif
        pOther->attr     = this->attr;
        pOther->userID   = this->userID;
        pOther->groupID  = this->groupID;
        pOther->genNum   = this->genNum;
        pOther->eaSize   = this->eaSize;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
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
    int             DirEntry_Compare (
        DIRENTRY_DATA   *this,
        DIRENTRY_DATA   *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!DirEntry_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        if( (this->type > pOther->type) ) {
            return 1;
        }
        if( (this->type < pOther->type) ) {
            return -1;
        }
        // Types are equal.


        iRc = Path_Compare(this->pFullPath, pOther->pFullPath);

        return iRc;
    }
    
   
    int             DirEntry_CompareFullPaths (
        DIRENTRY_DATA   *this,
        DIRENTRY_DATA   *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!DirEntry_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        iRc = Path_Compare(this->pFullPath, pOther->pFullPath);

        return iRc;
    }



    //---------------------------------------------------------------
    //                      C o m p l e t e
    //---------------------------------------------------------------

    ERESULT         DirEntry_Complete (
        DIRENTRY_DATA   *this
    )
    {
        const
        char            *pStrA = NULL;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
        DIRENTRY_DATA   *pNext = OBJ_NIL;
#endif
#if     defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#endif
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == this->pFullPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if (this->fCompleted) {
            return eRc;
        }
        pStrA = Path_getData(DirEntry_getFullPath(this));
        if (pStrA) {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
            iRc = lstat(pStrA, &statBuffer);
            if (0 == iRc) {
                eRc = DirEntry_CompleteFromStat(this, &statBuffer);

                // See "man 5 dir" and "man 3 stat" for details of d_type. d_type is
                // S_IFMT portion of st_mode.
                // Recurse though the links to get to the end point adding more
                // Directory Entries to the list as needed.
                pNext = this;
                while ((statBuffer.st_mode & S_IFMT) == S_IFLNK) {
                    char            linkDataA[512];
                    ssize_t         len;
                    DIRENTRY_DATA   *pEntry = OBJ_NIL;
                    uint16_t        type;

                    len =   readlink(
                                   pStrA,
                                   linkDataA, sizeof(linkDataA)-1
                            );
                    if (len >= 0) {
                        linkDataA[len] = '\0';
                        iRc = lstat(linkDataA, &statBuffer);
                        if (-1 == iRc) {
                            break;
                        }
                        // Convert mode S_FMT to dirent::d_type and save.
                        type = (statBuffer.st_mode & S_IFMT) >> 12;
                        pEntry = DirEntry_NewA(linkDataA, type);
                        if (pEntry) {
                            eRc = DirEntry_CompleteFromStat(pEntry, &statBuffer);
                            BREAK_NOT_NULL(pNext->pNext);
                            pNext->pNext = pEntry;
                            pNext = pEntry;
                            pStrA = Path_getData(DirEntry_getFullPath(pNext));
                        }
                        else
                            break;
                    }
                }
                this->fCompleted = 1;
            }
            else {
                eRc = ERESULT_PATH_NOT_FOUND;
            }
#endif
#if     defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#endif
            pStrA = NULL;
        }
        else {
            eRc = ERESULT_DATA_ERROR;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                         C o p y
    //---------------------------------------------------------------

    /*!
     Copy the current object creating a new object.
     Example:
     @code
        DirEntry      *pDeepCopy = DirEntry_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a DIRENTRY object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    DIRENTRY_DATA *     DirEntry_Copy (
        DIRENTRY_DATA       *this
    )
    {
        DIRENTRY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pOther = DirEntry_New( );
        if (pOther) {
            eRc = DirEntry_Assign(this, pOther);
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

    void            DirEntry_Dealloc (
        OBJ_ID          objId
    )
    {
        DIRENTRY_DATA   *this = objId;
        //ERESULT         eRc;
        DIRENTRY_DATA   *pNext;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((DIRENTRY_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pNext) {
            for( pNext=this->pNext; pNext; pNext=pNext->pNext)
                (void)DirEntry_setNext(pNext, OBJ_NIL);
        }

        (void)DirEntry_setNext(this, OBJ_NIL);
        (void)DirEntry_setFullPath(this, OBJ_NIL);
        (void)DirEntry_setShortName(this, OBJ_NIL);
        (void)DirEntry_setCreationTime(this, OBJ_NIL);
        (void)DirEntry_setModifiedTime(this, OBJ_NIL);
        (void)DirEntry_setStatusChangeTime(this, OBJ_NIL);

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

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         DirEntry_Disable (
        DIRENTRY_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
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
    ERESULT         DirEntry_Enable (
        DIRENTRY_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
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

    DIRENTRY_DATA *   DirEntry_Init (
        DIRENTRY_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(DIRENTRY_DATA);
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_DIRENTRY);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&DirEntry_Vtbl);
        
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
        if (!DirEntry_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
        fprintf(
                stderr, 
                "DirEntry::sizeof(DIRENTRY_DATA) = %lu\n", 
                sizeof(DIRENTRY_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(DIRENTRY_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s D i r
    //---------------------------------------------------------------
    
    bool            DirEntry_IsDir (
        DIRENTRY_DATA   *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        DIRENTRY_DATA   *pNext;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return false;
        }
#endif

        for(pNext=this; pNext->pNext; pNext=pNext->pNext)
            ;
        
        if (DIRENTRY_TYPE_DIR == pNext->type) {
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------

    ERESULT         DirEntry_IsEnabled (
        DIRENTRY_DATA        *this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
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



    //---------------------------------------------------------------
    //                          M a t c h
    //---------------------------------------------------------------

    ERESULT         DirEntry_MatchA (
        DIRENTRY_DATA   *this,
        const
        char            *pPattern
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc =   AStr_MatchA((ASTR_DATA *)this->pFullPath, pPattern);

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
        void        *pMethod = DirEntry_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "DirEntry", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          DirEntry_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        DIRENTRY_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(DIRENTRY_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)DirEntry_Class();
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
                            return DirEntry_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return DirEntry_Enable;
                        }
                        break;

#ifdef  DIRENTRY_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return DirEntry_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return DirEntry_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return DirEntry_ToDebugString;
                        }
#ifdef  DIRENTRY_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return DirEntry_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == DirEntry_ToDebugString)
                    return "ToDebugString";
#ifdef  DIRENTRY_JSON_SUPPORT
                if (pData == DirEntry_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          T a r g e t
    //---------------------------------------------------------------

    DIRENTRY_DATA * DirEntry_Target (
        DIRENTRY_DATA   *this
    )
    {
        //ERESULT         eRc;
        DIRENTRY_DATA   *pNext;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return false;
        }
#endif

        for( pNext=this; pNext->pNext; pNext=pNext->pNext)
            ;

        // Return to caller.
        return pNext;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = DirEntry_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     DirEntry_ToDebugString (
        DIRENTRY_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!DirEntry_Validate(this)) {
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
                    DirEntry_getSize(this),
                    obj_getRetainCount(this)
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
    bool            DirEntry_Validate (
        DIRENTRY_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_DIRENTRY))
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


        if (!(obj_getSize(this) >= sizeof(DIRENTRY_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


