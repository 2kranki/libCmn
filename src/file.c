// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   file.c
 *	Generated by 06/09/2015 16:36:07
 *
 * Created on December 30, 2014
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
#include    "file_internal.h"



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

    FILE_DATA *     file_Alloc(
    )
    {
        FILE_DATA       *this;
        uint32_t        cbSize = sizeof(FILE_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    FILE_DATA *     file_New(
    )
    {
        FILE_DATA       *this;
        
        // Do initialization.
        
        this = file_Alloc( );
        if (this) {
            this = file_Init(this);
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    //---------------------------------------------------------------
    //                       F i l e  S i z e A
    //---------------------------------------------------------------
    
    ERESULT         file_SizeA(
        const
        char            *pPath,
        int64_t         *pFileSize
    )
    {
#if defined(__MACOSX_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc;
        
        if (pPath) {
#if defined(__MACOSX_ENV__)
            iRc = stat(pPath, &statBuffer);
            if (0 == iRc) {
                if ((statBuffer.st_mode & S_IFMT) == S_IFREG) {
                    if (pFileSize) {
                        *pFileSize = statBuffer.st_size;
                    }
                    eRc = ERESULT_SUCCESSFUL_COMPLETION;
                }
                else
                    eRc = ERESULT_FAILURE_FALSE;
            }
            else
#endif
                eRc = ERESULT_PATH_NOT_FOUND;
        }
        else {
            eRc = ERESULT_DATA_ERROR;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                   F i l e  T o  A r r a y A
    //---------------------------------------------------------------
    
    ERESULT         file_ToArrayA(
        const
        char            *pPath,
        U8ARRAY_DATA    **ppArray
    )
    {
        ERESULT         eRc;
        U8ARRAY_DATA    *pArray;
        int64_t         size = 0;
        int             chr;
        FILE            *pFile;
        
        eRc = file_SizeA( pPath, &size );
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }
        if (0 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }
        pArray = u8Array_New();
        if (OBJ_NIL == pArray) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }

        pFile = fopen(pPath, "rb");
        if (NULL == pFile) {
            return ERESULT_FILE_NOT_FOUND;
        }
        while ( (chr = fgetc(pFile)) != EOF ) {
            u8Array_AppendData(pArray, (chr & 0xFF), NULL);
        }
        fclose(pFile);
        pFile = NULL;
        
        // Return to caller.
        if (ppArray) {
            *ppArray = pArray;
        }
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                   F i l e  T o  B u f f e r A
    //---------------------------------------------------------------
    
    ERESULT         file_ToBufferA(
        const
        char            *pPath,
        uint8_t         **ppBuffer
    )
    {
        ERESULT         eRc;
        uint8_t         *pBuffer = NULL;
        int64_t         size;
        int             chr;
        FILE            *pFile;
        uint8_t         *pData;
        
        if (ppBuffer) {
            *ppBuffer = pBuffer;
        }
        eRc = file_SizeA( pPath, &size );
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }
        if (0 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }
        pBuffer = mem_Malloc(size);
        if (OBJ_NIL == pBuffer) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        pFile = fopen(pPath, "rb");
        if (NULL == pFile) {
            return ERESULT_FILE_NOT_FOUND;
        }
        pData = pBuffer;
        while ( (chr = fgetc(pFile)) != EOF ) {
            *pData++ = (chr & 0xFF);
        }
        fclose(pFile);
        pFile = NULL;
        
        // Return to caller.
        if (ppBuffer) {
            *ppBuffer = pBuffer;
        }
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o u c h A
    //---------------------------------------------------------------
    
    ERESULT         file_TouchA(
        const
        char            *pPath
    )
    {
#if defined(__MACOSX_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        
        if (pPath) {
#if defined(__MACOSX_ENV__)
            iRc = stat(pPath, &statBuffer);
            if (0 == iRc) {
                if ((statBuffer.st_mode & S_IFMT) == S_IFREG) {
                    iRc = utimes(pPath, NULL);
                    if (0 == iRc) {
                        eRc = ERESULT_SUCCESSFUL_COMPLETION;
                    }
                }
                else
                    eRc = ERESULT_FAILURE_FALSE;
            }
            else {
                if (iRc == ENOENT) {
                    ;
                }
                eRc = ERESULT_PATH_NOT_FOUND;
            }
#endif
        }
        else
            eRc = ERESULT_DATA_ERROR;
        
        // Return to caller.
        return eRc;
    }
    
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        file_getPriority(
        FILE_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !file_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            file_setPriority(
        FILE_DATA       *cbp,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !file_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    uint32_t        file_getSize(
        FILE_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !file_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        return 0;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            file_Dealloc(
        OBJ_ID          objId
    )
    {
        FILE_DATA       *this = objId;
        bool            fRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !file_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        fRc = file_Disable( this );

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc( this );
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            file_Disable(
        FILE_DATA		*cbp
    )
    {

        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !file_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        // Put code here...

        obj_Disable(cbp);
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    bool            file_Enable(
        FILE_DATA		*cbp
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !file_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
        obj_Enable(cbp);

        // Put code here...
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    FILE_DATA *   file_Init(
        FILE_DATA       *this
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_FILE );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&file_Vtbl);
        
        //cbp->stackSize = obj_getMisc1(cbp);

    #ifdef NDEBUG
    #else
        if( !file_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            file_IsEnabled(
        FILE_DATA		*cbp
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !file_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(cbp))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     file_ToDebugString(
        FILE_DATA       *this,
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
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(fbsi) ",
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
        
        j = snprintf(str, sizeof(str), " %p(fbsi)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            file_Validate(
        FILE_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_FILE) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(FILE_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


