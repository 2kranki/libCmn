// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Path.c
 *	Generated 01/29/2020 13:19:38
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
#include        <Path_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
    const
    char        *pPathSep = "/";
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    const
    char        *pPathSep = "\\";
#endif



 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    void            Path_AppendSep (
        PATH_DATA       *this
    )
    {
        if (AStr_CharGetLastW32(Path_getAStr(this)) == *pPathSep)
            ;
        else {
            AStr_AppendA(Path_getAStr(this), pPathSep);
        }
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PATH_DATA *     Path_Alloc (
        void
    )
    {
        PATH_DATA       *this;
        uint32_t        cbSize = sizeof(PATH_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    PATH_DATA *     Path_New (
        void
    )
    {
        PATH_DATA       *this;
        
        this = Path_Alloc( );
        if (this) {
            this = Path_Init(this);
        } 
        return this;
    }



    PATH_DATA *     Path_NewA(
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

        this = Path_Alloc( );
        this = Path_Init(this);
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



    PATH_DATA *     Path_NewFromAStr(
        ASTR_DATA       *pStr
    )
    {
        PATH_DATA       *this;
        ERESULT         eRc;

        // Do initialization.
        if (NULL == pStr) {
            return OBJ_NIL;
        }

        this = Path_Alloc( );
        this = Path_Init(this);
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


    PATH_DATA *     Path_NewFromCurrentDirectory(
    )
    {
        PATH_DATA       *this =  OBJ_NIL;
        char            data[512];
        uint32_t        len;
        char            *pBuffer = NULL;

        // Do initialization.
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        pBuffer = getcwd(data, sizeof(data));
#endif
        if (NULL == pBuffer)
            ;
        else {
            len = (uint32_t)strlen(data);
            if (len) {
                this = Path_NewA(data);
                if (this) {
                    Path_AppendSep(this);
                }
            }
        }

        // Return to caller.
        return this;
    }



    PATH_DATA *     Path_NewFromDirExt(
        ASTR_DATA       *pFilePath,
        ASTR_DATA       *pFileExt
    )
    {
        PATH_DATA       *this =  OBJ_NIL;
        ERESULT         eRc;

        // Do initialization.
        this = Path_Alloc( );
        this = Path_Init(this);
        if (OBJ_NIL == this) {
            return this;
        }

        eRc = Path_MakeFile(this, pFilePath, pFileExt);
        if (ERESULT_FAILED(eRc)) {
            obj_Release(this);
            this = OBJ_NIL;
        }

        // Return to caller.
        return this;
    }



    PATH_DATA *     Path_NewFromDriveDirFilename(
        ASTR_DATA       *pDrive,
        PATH_DATA       *pDir,
        PATH_DATA       *pFileName      // includes file extension
    )
    {
        PATH_DATA       *this =  OBJ_NIL;
        ERESULT         eRc;
        //char            *pData;
        //size_t          len;

        // Do initialization.
        this = Path_Alloc( );
        this = Path_Init(this);
        if (OBJ_NIL == this) {
            return this;
        }

        eRc = Path_MakePath(this, pDrive, pDir, pFileName);
        if (ERESULT_FAILED(eRc)) {
            obj_Release(this);
            this = OBJ_NIL;
        }

        // Return to caller.
        return this;
    }



    PATH_DATA *     Path_NewFromEnv(
        const
        char            *pStr
    )
    {
        PATH_DATA       *this =  OBJ_NIL;
        char            *pData;
        size_t          len;

        // Do initialization.
        if (NULL == pStr) {
            return this;
        }

        pData = getenv(pStr);
        if (NULL == pData)
            ;
        else {
            len = strlen(pData);
            if (len) {
                this = Path_NewA(pData);
            }
        }

        // Return to caller.
        return( this );
    }



    PATH_DATA *     Path_NewFromW32STR(
        W32STR_DATA     *pStr
    )
    {
        PATH_DATA       *this;
        ERESULT         eRc;

        // Do initialization.
        if (NULL == pStr) {
            return OBJ_NIL;
        }

        this = Path_Alloc( );
        this = Path_Init(this);
        if (this) {
            eRc = AStr_AppendW32Str((ASTR_DATA *)this, pStr);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }

        // Return to caller.
        return( this );
    }



    PATH_DATA *     Path_NewW32(
        uint32_t        len,
        const
        W32CHR_T        *pStr
    )
    {
        PATH_DATA       *this;
        ERESULT         eRc;

        // Do initialization.
        if (NULL == pStr) {
            return OBJ_NIL;
        }

        this = Path_New( );
        if (this) {
            eRc = AStr_AppendW32((ASTR_DATA *)this, len, pStr);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }

        // Return to caller.
        return( this );
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

        const
        char *          Path_getData (
            PATH_DATA       *this
        )
        {

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !Path_Validate(this) ) {
                DEBUG_BREAK();
            }
    #endif

            return AStr_getData((ASTR_DATA *)this);
        }



        ASTR_DATA *     Path_getAStr (
            PATH_DATA       *this
        )
        {

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !Path_Validate(this) ) {
                DEBUG_BREAK();
            }
    #endif

            return (ASTR_DATA *)this;
        }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Path_getSize (
        PATH_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Path_getSuperVtbl (
        PATH_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
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
    //                          A p p e n d
    //---------------------------------------------------------------

    ERESULT         Path_AppendA(
        PATH_DATA       *this,
        const
        char            *pStr
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = AStr_AppendA((ASTR_DATA *)this, pStr);

        // Return to caller.
        return eRc;
    }


    ERESULT         Path_AppendAStr(
        PATH_DATA       *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = AStr_Append((ASTR_DATA *)this, pStr);

        // Return to caller.
        return eRc;
    }


    ERESULT         Path_AppendDir(
        PATH_DATA       *this,
        ASTR_DATA       *pDir
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        W32CHR_T        chr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (pDir) {
            eRc = Path_AppendA(this, AStr_getData(pDir));
        }
        chr = AStr_CharGetLastW32((ASTR_DATA *)this);
        if ((chr < 0) || !(chr == '/')) {
            eRc = AStr_AppendA((ASTR_DATA *)this, "/");
        }

        // Return to caller.
        return eRc;
    }


    ERESULT         Path_AppendDirA(
        PATH_DATA        *this,
        const
        char            *pDirA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        W32CHR_T        chr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (pDirA) {
            eRc = Path_AppendFileNameA(this, pDirA);
        }
        chr = AStr_CharGetLastW32((ASTR_DATA *)this);
        if ((chr < 0) || !(chr == '/')) {
            eRc = AStr_AppendA((ASTR_DATA *)this, "/");
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                 A p p e n d  E x t A
    //---------------------------------------------------------------

    ERESULT         Path_AppendExtA(
        PATH_DATA        *this,
        const
        char            *pExt
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Path_Validate( this ) ) {
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
            eRc = AStr_AppendA((ASTR_DATA *)this, ".");
            if (ERESULT_HAS_FAILED(eRc)) {
                return eRc;
            }
        }
        eRc = AStr_AppendA((ASTR_DATA *)this, pExt);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }

        eRc = Path_Clean(this);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                 A p p e n d  F i l e  N a m e
    //---------------------------------------------------------------

    ERESULT         Path_AppendFileName(
        PATH_DATA        *this,
        ASTR_DATA       *pFileName
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Path_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pFileName) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = AStr_AppendA((ASTR_DATA *)this, "/");
        if (ERESULT_HAS_FAILED(eRc)) {
            (void)AStr_Truncate((ASTR_DATA *)this, 0);
            return eRc;
        }

        eRc = AStr_Append((ASTR_DATA *)this, pFileName);
        if (ERESULT_HAS_FAILED(eRc)) {
            (void)AStr_Truncate((ASTR_DATA *)this, 0);
            return eRc;
        }

        eRc = Path_Clean(this);
        if (ERESULT_HAS_FAILED(eRc)) {
            (void)AStr_Truncate((ASTR_DATA *)this, 0);
            return eRc;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    ERESULT         Path_AppendFileNameA(
        PATH_DATA        *this,
        const
        char            *pFileNameA
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Path_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pFileNameA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = AStr_AppendA((ASTR_DATA *)this, "/");
        if (ERESULT_HAS_FAILED(eRc)) {
            (void)AStr_Truncate((ASTR_DATA *)this, 0);
            return eRc;
        }

        eRc = AStr_AppendA((ASTR_DATA *)this, pFileNameA);
        if (ERESULT_HAS_FAILED(eRc)) {
            (void)AStr_Truncate((ASTR_DATA *)this, 0);
            return eRc;
        }

        eRc = Path_Clean(this);
        if (ERESULT_HAS_FAILED(eRc)) {
            (void)AStr_Truncate((ASTR_DATA *)this, 0);
            return eRc;
        }

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
        ERESULT eRc = Path_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another PATH object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Path_Assign (
        PATH_DATA		*this,
        PATH_DATA       *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Path_Validate(pOther)) {
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
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C l e a n
    //---------------------------------------------------------------

    ERESULT         Path_Clean(
        PATH_DATA        *this
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
        if( !Path_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (0 == AStr_getLength((ASTR_DATA *)this)) {
            return ERESULT_SUCCESS;
        }

        if ((AStr_getLength((ASTR_DATA *)this)) >= 1) {
            chr1 = AStr_CharGetW32((ASTR_DATA *)this, 1);
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
                chr1 = AStr_CharGetW32((ASTR_DATA *)this, i+1);
                chr2 = AStr_CharGetW32((ASTR_DATA *)this, i+2);
                if( (chr1 == '/') && (chr2 == '/') ) {
                    eRc = AStr_Remove((ASTR_DATA *)this, (i + 1), 1 );
                    if (ERESULT_HAS_FAILED(eRc)) {
                        ;
                    }
                    continue;
                }
            }
            if ((AStr_getLength((ASTR_DATA *)this) - i) >= 3) {
                chr1 = AStr_CharGetW32((ASTR_DATA *)this, i+1);
                chr2 = AStr_CharGetW32((ASTR_DATA *)this, i+2);
                chr3 = AStr_CharGetW32((ASTR_DATA *)this, i+3);
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
            chr1 = AStr_CharGetW32((ASTR_DATA *)this, i-2);
            chr2 = AStr_CharGetW32((ASTR_DATA *)this, i-1);
            chr3 = AStr_CharGetW32((ASTR_DATA *)this, i);
            if( (chr1 == '/') && (chr2 == '.') && (chr3 == '/') ) {
                eRc = AStr_Remove((ASTR_DATA *)this, (i - 2), 2 );
                if (ERESULT_HAS_FAILED(eRc)) {
                    ;
                }
            }
        }

        for (;;) {
            i = AStr_getLength((ASTR_DATA *)this);
            chr1 = AStr_CharGetW32((ASTR_DATA *)this, i);
            if ((chr1 == '/') && (i > 1)) {
                eRc = AStr_Remove((ASTR_DATA *)this, i, 1 );
                if (ERESULT_HAS_FAILED(eRc)) {
                    ;
                }
            }
            else
                break;
        }

        eRc = Path_ExpandVars(this, OBJ_NIL);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         Path_Compare (
        PATH_DATA     *this,
        PATH_DATA     *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Path_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = AStr_Compare( (ASTR_DATA *)this, (ASTR_DATA *)pOther );

        return eRc;
    }
    
   
     ERESULT         Path_CompareA(
         PATH_DATA       *this,
         const
         char            *pOther
     )
     {
         ERESULT         eRc;

         // Do initialization.
 #ifdef NDEBUG
 #else
         if( !Path_Validate(this) ) {
             DEBUG_BREAK();
             return ERESULT_INVALID_OBJECT;
         }
 #endif

         eRc = AStr_CompareA( (ASTR_DATA *)this, pOther );

         // Return to caller.
         return eRc;
     }


     ERESULT         Path_CompareRightA(
         PATH_DATA        *this,
         const
         char            *pOther
     )
     {
         ERESULT         eRc;

         // Do initialization.
 #ifdef NDEBUG
 #else
         if( !Path_Validate(this) ) {
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
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Path      *pCopy = Path_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a PATH object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    PATH_DATA *     Path_Copy (
        PATH_DATA       *this
    )
    {
        PATH_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef PATH_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Path_New( );
        if (pOther) {
            eRc = Path_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                 C r e a t e  E m p t y
    //---------------------------------------------------------------

    ERESULT         Path_CreateEmpty(
        PATH_DATA       *this
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = Path_IsExisting(this);
        if (eRc == ERESULT_SUCCESS) {
            return ERESULT_FILE_ALREADY_EXISTS;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       C S t r i n g A
    //---------------------------------------------------------------

    char *          Path_CStringA(
        PATH_DATA        *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Path_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        // Return to caller.
        return AStr_CStringA((ASTR_DATA *)this, NULL);
    }



    //---------------------------------------------------------------
    //                          D a t e s
    //---------------------------------------------------------------

    ERESULT         Path_DateLastUpdated (
       PATH_DATA        *this,
       DATETIME_DATA    **ppDate
    )
    {
        char            *pStr = NULL;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
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
        if (!Path_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pStr = (char *)AStr_getData((ASTR_DATA *)this);
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pStr, &statBuffer);
        if (0 == iRc) {
            pTime = DateTime_NewFromTimeT(statBuffer.st_mtimespec.tv_sec);
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

    void            Path_Dealloc (
        OBJ_ID          objId
    )
    {
        PATH_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((PATH_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
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
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Path      *pDeepCopy = Path_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a PATH object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    PATH_DATA *     Path_DeepyCopy (
        PATH_DATA       *this
    )
    {
        PATH_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Path_New( );
        if (pOther) {
            eRc = Path_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                       D e l e t e
    //---------------------------------------------------------------

    ERESULT         Path_Delete(
        PATH_DATA        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        const
        char            *pStrA = NULL;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        bool            bRc;
#endif

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pStrA = Path_getData(this);
        if (NULL == pStrA) {
            return ERESULT_INTERNAL_ERROR;
        }

#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pStrA, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFREG) {
                iRc = unlink(pStrA);
                if (0 == iRc) {
                    eRc = ERESULT_SUCCESS;
                }
                else {
                    eRc = ERESULT_FILE_OPERATION_FAILED;
                }
            }
            else if ((statBuffer.st_mode & S_IFMT) == S_IFDIR) {
                iRc = rmdir(pStrA);
                if (0 == iRc) {
                    eRc = ERESULT_SUCCESS;
                }
                else {
                    eRc = ERESULT_FILE_OPERATION_FAILED;
                }
            }
            else
                eRc = ERESULT_FILE_OPERATION_FAILED;
        }
        else
            eRc = ERESULT_PATH_NOT_FOUND;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        //TODO: DeleteFileW is more pwerful. Need to investgate using
        //      it instead
        bRc = DeleteFileA(pStrA);
        if (bRc)
            eRc = ERESULT_SUCCESS;
        else
            eRc = ERESULT_FILE_OPERATION_FAILED;
#endif

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
    ERESULT         Path_Disable (
        PATH_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
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
    ERESULT         Path_Enable (
        PATH_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
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
    //     E x p a n d  E n v i r o n m e n t  V a r i a b l e s
    //---------------------------------------------------------------

    ERESULT         Path_ExpandVars(
        PATH_DATA       *this,
        OBJ_ID          pHash
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Path_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        eRc = AStr_ExpandVars((ASTR_DATA *)this, pHash);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       F i l e  S i z e
    //---------------------------------------------------------------

    ERESULT         Path_FileSize(
        PATH_DATA       *this,
        int64_t         *pFileSize
    )
    {
        char            *pStr = NULL;
        ERESULT         eRc = ERESULT_SUCCESS;
        int64_t         size;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pStr = (char *)AStr_getData((ASTR_DATA *)this);
        if (pStr) {
            size = file_SizeA(pStr);
            if (-1 == size) {
                eRc = ERESULT_DATA_NOT_FOUND;
            }
            if (pFileSize)
                *pFileSize = size;
        }
        else
            eRc = ERESULT_DATA_ERROR;

        // Return to caller.
        return eRc;
    }




    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PATH_DATA *   Path_Init (
        PATH_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(PATH_DATA);
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

        this = (OBJ_ID)AStr_Init((ASTR_DATA *)this);            // Needed for Inheritance
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Path_Vtbl);
        
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
        fprintf(
                stderr, 
                "Path::sizeof(PATH_DATA) = %lu\n", 
                sizeof(PATH_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(PATH_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s D i r
    //---------------------------------------------------------------

    ERESULT         Path_IsDir (
        PATH_DATA       *this
    )
    {
        char            *pStr = NULL;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        #if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
                DWORD           dwFileAttr;
        #endif
        ERESULT         eRc = ERESULT_PATH_NOT_FOUND;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pStr = (char *)Path_getData(this);
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pStr, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFDIR) {
                eRc = ERESULT_SUCCESS;
                Path_AppendSep(this);
            }
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        dwFileAttr = GetFileAttributesA(pStrA);
        if (dwFileAttr != INVALID_FILE_ATTRIBUTES) {
            if (dwFileAttr & FILE_ATTRIBUTE_DIRECTORY) {
                eRc = ERESULT_SUCCESS;
                Path_AppendSep(this);
            }
        }
#endif

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Path_IsEnabled (
        PATH_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
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
    //                       I s E x i s t i n g
    //---------------------------------------------------------------

    ERESULT         Path_IsExisting (
        PATH_DATA        *this
    )
    {
        const
        char            *pStrA = NULL;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        DWORD           dwFileAttr;
#endif
        ERESULT         eRc = ERESULT_PATH_NOT_FOUND;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pStrA = (char *)Path_getData(this);
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pStrA, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFDIR) {
                Path_AppendSep(this);
            }
            eRc = ERESULT_SUCCESS;
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        dwFileAttr = GetFileAttributesA(pStrA);
        if (dwFileAttr != INVALID_FILE_ATTRIBUTES) {
            eRc = ERESULT_SUCCESS;
            if (dwFileAttr & FILE_ATTRIBUTE_DIRECTORY) {
                Path_AppendSep(this);
            }
        }
#endif

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       I s F i l e
    //---------------------------------------------------------------

    ERESULT         Path_IsFile (
        PATH_DATA        *this
    )
    {
        const
        char            *pStr = NULL;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
        //int             ourErrno;
#endif
        ERESULT         eRc = ERESULT_PATH_NOT_FOUND;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pStr = (char *)Path_getData(this);
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pStr, &statBuffer);
#ifdef XYZZY
        ourErrno = errno;
        if (ourErrno) {
            perror(NULL);
        }
#endif
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFDIR) {
                Path_AppendSep(this);
            }
            if ((statBuffer.st_mode & S_IFMT) == S_IFREG) {
                eRc = ERESULT_SUCCESS;
            }
        }
#endif

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       I s L i n k
    //---------------------------------------------------------------

    ERESULT         Path_IsLink (
        PATH_DATA        *this
    )
    {
        const
        char            *pStr = NULL;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_PATH_NOT_FOUND;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pStr = (char *)Path_getData(this);
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pStr, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFDIR) {
                Path_AppendSep(this);
            }
            if ((statBuffer.st_mode & S_IFMT) == S_IFLNK) {
                eRc = ERESULT_SUCCESS;
            }
        }
#endif

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                     M a k e  F i l e
    //---------------------------------------------------------------

    ERESULT         Path_MakeFile(
        PATH_DATA        *this,
        ASTR_DATA       *pFileName,
        ASTR_DATA       *pFileExt
    )
    {
        ERESULT         eRc;
        int32_t         chr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = AStr_Truncate((ASTR_DATA *)this, 0);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }

        if (pFileName) {
            eRc = AStr_Append((ASTR_DATA *)this, pFileName);
            if (ERESULT_HAS_FAILED(eRc)) {
                (void)AStr_Truncate((ASTR_DATA *)this, 0);
                return eRc;
            }
        }

        if (pFileExt) {
            chr = AStr_CharGetW32(pFileExt, 1);
            if (chr == '.')
                ;
            else {
                eRc = AStr_AppendA((ASTR_DATA *)this, ".");
                if (ERESULT_HAS_FAILED(eRc)) {
                    (void)AStr_Truncate((ASTR_DATA *)this, 0);
                    return eRc;
                }
            }
            eRc = AStr_Append((ASTR_DATA *)this, pFileExt);
            if (ERESULT_HAS_FAILED(eRc)) {
                (void)AStr_Truncate((ASTR_DATA *)this, 0);
                return eRc;
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                     M a k e  P a t h
    //---------------------------------------------------------------

    ERESULT         Path_MakePath(
        PATH_DATA        *this,
        ASTR_DATA       *pDrive,
        PATH_DATA       *pDir,
        PATH_DATA       *pFileName
        )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Path_Validate(this) ) {
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

        eRc = Path_Clean(this);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          M a t c h
    //---------------------------------------------------------------

    ERESULT         Path_MatchA(
        PATH_DATA       *this,
        const
        char            *pPattern
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

#ifdef NDEBUG
#else
        if( !Path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc =   AStr_MatchA((ASTR_DATA *)this, pPattern);

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
        void        *pMethod = Path_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Path", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Path_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        PATH_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Path_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(PATH_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Path_Class();
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
                            return Path_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Path_Enable;
                        }
                        break;

#ifdef  PATH_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Path_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Path_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Path_ToDebugString;
                        }
#ifdef  PATH_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Path_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Path_ToDebugString)
                    return "ToDebugString";
#ifdef  PATH_JSON_SUPPORT
                if (pData == Path_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
        //---------------------------------------------------------------
        //                     S p l i t  F i l e
        //---------------------------------------------------------------

        ERESULT         Path_SplitFile(
            PATH_DATA        *this,
            ASTR_DATA       **ppFileName,
            ASTR_DATA       **ppFileExt
        )
        {
            ERESULT         eRc;
            uint32_t        index2;
            uint32_t        begin = 1;
            uint32_t        end;
            uint32_t        begDir = 1;
            //ASTR_DATA       *pFileName = OBJ_NIL;
            //ASTR_DATA       *pFileExt = OBJ_NIL;

            // Do initialization.
    #ifdef NDEBUG
    #else
            if( !Path_Validate(this) ) {
                DEBUG_BREAK();
                return ERESULT_INVALID_OBJECT;
            }
    #endif

            index2 = 0;
            eRc = AStr_CharFindPrevW32((ASTR_DATA *)this, &index2, '.');
            if (ERESULT_IS_SUCCESSFUL(eRc)) {
                begin = begDir;
                end = index2 - 1;
                if (ppFileName) {
                    if (begin <= end) {
                        eRc =   AStr_Mid(
                                        (ASTR_DATA *)this,
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
                end = AStr_getLength((ASTR_DATA *)this);
                if (ppFileExt) {
                    if (begin <= end) {
                        eRc =   AStr_Mid(
                                          (ASTR_DATA *)this,
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
                    end = AStr_getLength((ASTR_DATA *)this);
                    if (begin <= end) {
                        eRc =   AStr_Mid(
                                        (ASTR_DATA *)this,
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

        ERESULT         Path_SplitPath(
            PATH_DATA        *this,
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
            if( !Path_Validate(this) ) {
                DEBUG_BREAK();
                return ERESULT_INVALID_OBJECT;
            }
    #endif

            index = 0;
            eRc = AStr_CharFindNextW32((ASTR_DATA *)this, &index, ':');
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
            eRc = AStr_CharFindPrevW32((ASTR_DATA *)this, &index, '/');
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
                            *ppDir = Path_NewFromAStr(pStr);
                            Path_Clean(*ppDir);
                            obj_Release(pStr);
                        }
                    }
                    else if (begin == index) {
                        if (ppDir) {
                            *ppDir = Path_NewA("/");
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
                            *ppFileName = Path_NewFromAStr(pStr);
                            Path_Clean(*ppFileName);
                            obj_Release(pStr);
                        }
                    }
                }
            }

            // Return to caller.
            return ERESULT_SUCCESS;
        }



        //---------------------------------------------------------------
        //                      T o  A S t r
        //---------------------------------------------------------------

        ASTR_DATA *     Path_ToAStr(
            PATH_DATA       *this
        )
        {

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !Path_Validate(this) ) {
                DEBUG_BREAK();
            }
    #endif

            return (ASTR_DATA *)this;
        }



        //---------------------------------------------------------------
        //                      T o  B a s h
        //---------------------------------------------------------------

        ERESULT         Path_ToBash(
            PATH_DATA        *this,
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
            if( !Path_Validate(this) ) {
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
                chr = AStr_CharGetW32((ASTR_DATA *)this, i+1);
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
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Path_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Path_ToDebugString (
        PATH_DATA      *this,
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
        if (!Path_Validate(this)) {
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
                    Path_getSize(this),
                    obj_getRetainCount(this)
            );

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    "\t\"%s\"\n",
                    Path_getData(this)
                );

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
    //                      T o  S t d e r r
    //---------------------------------------------------------------

    ERESULT         Path_ToStderr(
        PATH_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Path_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        fprintf(stderr, "%s", Path_getData(this));

        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      T o V e r s i o n e d
    //---------------------------------------------------------------

    PATH_DATA *     Path_ToVersioned(
        PATH_DATA       *this
    )
    {
        ERESULT         eRc;
        PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pWrkD = OBJ_NIL;
        ASTR_DATA       *pWrkE = OBJ_NIL;
        ASTR_DATA       *pWrkW = OBJ_NIL;
        uint32_t        i;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Path_Validate(this) ) {
            DEBUG_BREAK();
            return pPath;
        }
#endif

        eRc = Path_IsFile(this);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return pPath;
        }

        eRc = Path_SplitFile(this, &pWrkD, &pWrkE);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pWrkD)) {
            DEBUG_BREAK();
            obj_Release(pWrkD);
            pWrkD = OBJ_NIL;
            obj_Release(pWrkE);
            pWrkE = OBJ_NIL;
            return pPath;
        }

        for (i=0; i<10000; ++i) {
            pWrkW = AStr_New( );
            eRc = AStr_AppendPrint(pWrkW, "%04d.%s", i, AStr_getData(pWrkE));
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pWrkW);
                pWrkW = OBJ_NIL;
                break;
            }
            pPath = Path_NewFromDirExt(pWrkD, pWrkW);
            if (OBJ_NIL == pPath) {
                obj_Release(pWrkW);
                pWrkW = OBJ_NIL;
                break;
            }
            eRc = Path_IsFile(pPath);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pWrkW);
                pWrkW = OBJ_NIL;
                break;
            }
            obj_Release(pWrkW);
            pWrkW = OBJ_NIL;
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        obj_Release(pWrkD);
        pWrkD = OBJ_NIL;
        obj_Release(pWrkE);
        pWrkE = OBJ_NIL;
        return pPath;
    }



    //---------------------------------------------------------------
    //                      T o  W i n
    //---------------------------------------------------------------

    ERESULT         Path_ToWin(
        PATH_DATA        *this,
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
        if( !Path_Validate(this) ) {
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
            chr = AStr_CharGetW32((ASTR_DATA *)this, i+1);
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
    bool            Path_Validate (
        PATH_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_PATH))
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


        if (!(obj_getSize(this) >= sizeof(PATH_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //              V e r s i o n e d  R e n a m e
    //---------------------------------------------------------------

    ERESULT         Path_VersionedRename(
        PATH_DATA        *this
    )
    {
        PATH_DATA       *pPath = OBJ_NIL;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Path_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = Path_IsFile(this);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        pPath = Path_ToVersioned(this);
        if (pPath) {
            eRc = file_RenameA(Path_getData(this), Path_getData(pPath));
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        // Return to caller.
        return eRc;
    }




    
#ifdef	__cplusplus
}
#endif


