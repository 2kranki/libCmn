// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   dirEntry.c
 *	Generated 06/23/2015 20:03:11
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
#include    <dirEntry_internal.h>
#include    <misc.h>



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

    DIRENTRY_DATA *     dirEntry_Alloc(
    )
    {
        DIRENTRY_DATA   *cbp;
        uint32_t        cbSize = sizeof(DIRENTRY_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    DIRENTRY_DATA * dirEntry_NewA(
        PATH_DATA       *pDir,
        const
        char            *pNameStr,
        uint8_t         type
    )
    {
        DIRENTRY_DATA   *cbp;
        ASTR_DATA       *pName;
        
        pName = AStr_NewA(pNameStr);
        if (OBJ_NIL == pName) {
            return OBJ_NIL;
        }
        
        cbp = dirEntry_Alloc();
        cbp = dirEntry_Init(cbp);
        if (OBJ_NIL == cbp) {
            return cbp;
        }
        
        (void)dirEntry_setDir(cbp, pDir);
        (void)dirEntry_setName(cbp, pName);
        (void)dirEntry_setType(cbp, type);

        obj_Release(pName);
        pName = OBJ_NIL;
        
        // Return to caller.
        return( cbp );
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  C r e a t i o n  T i m e
    //---------------------------------------------------------------
    
    DATETIME_DATA * dirEntry_getCreationTime(
        DIRENTRY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pCreationTime;
    }
    
    bool            dirEntry_setCreationTime(
        DIRENTRY_DATA   *this,
        DATETIME_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
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
    
    
    
    PATH_DATA *     dirEntry_getDir(
        DIRENTRY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pDir;
    }
    
    bool            dirEntry_setDir(
        DIRENTRY_DATA   *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pDir) {
            obj_Release(this->pDir);
        }
        this->pDir = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //               G e n e r a t i o n  N u m b e r
    //---------------------------------------------------------------
    
    uint32_t        dirEntry_getGenerationNumber(
        DIRENTRY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->genNum;
    }
    
    bool            dirEntry_setGenerationNumber(
        DIRENTRY_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->genNum = value;
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //      L a s t  D a t a  M o d i f i c a t i o n  T i m e
    //---------------------------------------------------------------
    
    DATETIME_DATA * dirEntry_getModifiedTime(
        DIRENTRY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pModifiedTime;
    }
    
    bool            dirEntry_setModifiedTime(
        DIRENTRY_DATA   *this,
        DATETIME_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
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
    
    
    
    ASTR_DATA *     dirEntry_getName(
        DIRENTRY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pName;
    }
    
    bool            dirEntry_setName(
        DIRENTRY_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pName) {
            obj_Release(this->pName);
        }
        this->pName = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //      L a s t  D a t a  M o d i f i c a t i o n  T i m e
    //---------------------------------------------------------------
    
    DATETIME_DATA * dirEntry_getStatusChangeTime(
        DIRENTRY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pStatusChangeTime;
    }
    
    bool            dirEntry_setStatusChangeTime(
        DIRENTRY_DATA   *this,
        DATETIME_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
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
    //                             T y p e
    //---------------------------------------------------------------
    
    uint8_t         dirEntry_getType(
        DIRENTRY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->type;
    }

    bool            dirEntry_setType(
        DIRENTRY_DATA   *this,
        uint8_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->type = value;
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
     ERESULT eRc = dirEntry_Assign(this,pOther);
     @endcode
     @param     this    DIRENTRY object pointer
     @param     pOther  a pointer to another DIRENTRY object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         dirEntry_Assign(
        DIRENTRY_DATA   *this,
        DIRENTRY_DATA   *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !dirEntry_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Release objects and areas in other object.
        if (pOther->pDir) {
            obj_Release(pOther->pDir);
            pOther->pDir = OBJ_NIL;
        }
        if (pOther->pName) {
            obj_Release(pOther->pName);
            pOther->pName = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pDir) {
            if (obj_getVtbl(this->pDir)->pCopy) {
                pOther->pDir = obj_getVtbl(this->pDir)->pCopy(this->pDir);
            }
            else {
                obj_Retain(this->pDir);
                pOther->pDir = this->pDir;
            }
        }
        if (this->pName) {
            if (obj_getVtbl(this->pName)->pCopy) {
                pOther->pName = obj_getVtbl(this->pName)->pCopy(this->pName);
            }
            else {
                obj_Retain(this->pName);
                pOther->pName = this->pName;
            }
        }

        // Copy other data from this object to other.
        pOther->type = this->type;
#if     defined(__MACOSX_ENV__) || defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        pOther->fileSize = this->fileSize;
#endif
        pOther->attr = this->attr;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       C o m p a r e
    //---------------------------------------------------------------
    
    ERESULT         dirEntry_Compare(
        DIRENTRY_DATA   *this,
        DIRENTRY_DATA   *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int32_t         i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !dirEntry_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if( (this->pName) && (OBJ_NIL == pOther->pName) ) {
            DEBUG_BREAK();
            return ERESULT_SUCCESS_GREATER_THAN;
        }
        if( (OBJ_NIL == this->pName) && (OBJ_NIL == pOther->pName) ) {
            DEBUG_BREAK();
            return ERESULT_SUCCESS;
        }
        if( (OBJ_NIL == this->pName) && (pOther->pName) ) {
            DEBUG_BREAK();
            return ERESULT_SUCCESS_LESS_THAN;
        }

        eRc = AStr_Compare(this->pName, pOther->pName);
        
        // Return to caller.
        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
     DIRENTRY_DATA      *pCopy = dirEntry_Copy(this);
     @endcode
     @param     this    DIRENTRY object pointer
     @return    If successful, a DIRENTRY object which must be released,
                 otherwise OBJ_NIL.
     @warning   Remember to release the returned the DIRENTRY object.
     */
    DIRENTRY_DATA * dirEntry_Copy(
        DIRENTRY_DATA   *this
    )
    {
        DIRENTRY_DATA   *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = dirEntry_Alloc( );
        pOther = dirEntry_Init(pOther);
        if (pOther) {
            eRc = dirEntry_Assign(this, pOther);
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

    void            dirEntry_Dealloc(
        OBJ_ID          objId
    )
    {
        DIRENTRY_DATA   *this = objId;

        // Do initialization.
        if (OBJ_NIL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        (void)dirEntry_setDir(this, OBJ_NIL);
        (void)dirEntry_setName(this, OBJ_NIL);
        (void)dirEntry_setCreationTime(this, OBJ_NIL);
        (void)dirEntry_setModifiedTime(this, OBJ_NIL);
        (void)dirEntry_setStatusChangeTime(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    DIRENTRY_DATA *   dirEntry_Init(
        DIRENTRY_DATA       *this
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_DIRENTRY );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&dirEntry_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);

    #ifdef NDEBUG
    #else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //              G e t  A l l  D a t a
    //---------------------------------------------------------------
    
    ERESULT         dirEntry_GetAllData(
        DIRENTRY_DATA   *this
    )
    {
        const
        char            *pStr = NULL;
#if     defined(__MACOSX_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;
        DATETIME_DATA   *pTime = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == this->pDir ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if( OBJ_NIL == this->pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pPath = path_Copy(this->pDir);
        path_AppendFileName(pPath, this->pName);
        pStr = path_getData(pPath);
        if (pStr) {
#if     defined(__MACOSX_ENV__)
            iRc = stat(pStr, &statBuffer);
            if (0 == iRc) {
                pTime = dateTime_NewFromTimeT(statBuffer.st_birthtimespec.tv_sec);
                dirEntry_setCreationTime(this, pTime);
                obj_Release(pTime);
                pTime = OBJ_NIL;
                pTime = dateTime_NewFromTimeT(statBuffer.st_mtimespec.tv_sec);
                dirEntry_setModifiedTime(this, pTime);
                obj_Release(pTime);
                pTime = OBJ_NIL;
                this->userID = statBuffer.st_uid;
                this->groupID = statBuffer.st_gid;
                this->genNum = statBuffer.st_gen;
                this->fileSize = statBuffer.st_size;
            }
            else {
                eRc = ERESULT_PATH_NOT_FOUND;
            }
#endif
            pStr = NULL;
        }
        else {
            eRc = ERESULT_DATA_ERROR;
        }
        obj_Release(pPath);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          M a t c h
    //---------------------------------------------------------------
    
    ERESULT         dirEntry_MatchA(
        DIRENTRY_DATA   *this,
        const
        char            *pPattern
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc =   AStr_MatchA(this->pName, pPattern);
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          dirEntry_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    )
    {
        DIRENTRY_DATA   *this = objId;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
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
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return dirEntry_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pStr);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = dirEntry_ToDebugString(this, 4);
     @endcode:
     @param:    this    DIRENTRY object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     dirEntry_ToDebugString(
        DIRENTRY_DATA   *this,
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
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(dirEntry)\n",
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
        
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(dirEntry)}\n", this);
        AStr_AppendA(pStr, str);
        
        //dirEntry_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            dirEntry_Validate(
        DIRENTRY_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_DIRENTRY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(DIRENTRY_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


