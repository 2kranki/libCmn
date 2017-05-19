// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   fbsi.c
 *	Generated 05/21/2015 11:25:33
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
#include    "fbsi_internal.h"



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

    FBSI_DATA *     fbsi_Alloc(
    )
    {
        FBSI_DATA       *cbp;
        uint32_t        cbSize = sizeof(FBSI_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    PATH_DATA *     fbsi_getPath(
        FBSI_DATA		*cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !fbsi_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pPath;
    }
    
    
    bool            fbsi_setPath(
        FBSI_DATA		*cbp,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !fbsi_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pPath) {
            obj_Release(cbp->pPath);
        }
        cbp->pPath = pValue;
        
        return true;
    }
    
    
    
    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            fbsi_Dealloc(
        OBJ_ID          objId
    )
    {
        FBSI_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !fbsi_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pFile) {
            fflush(this->pFile);
            fclose(this->pFile);
            this->pFile = NULL;
        }
        
        if (this->pBuffer) {
            mem_Free(this->pBuffer);
            this->pBuffer = NULL;
            this->bufferSize = 0;
            this->bufferUsed = 0;
        }
        
        fbsi_setPath(this, OBJ_NIL);
        
        if (this->pStack) {
            obj_Release(this->pStack);
            this->pBuffer = OBJ_NIL;
        }
        
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          G e t c
    //---------------------------------------------------------------

    ERESULT         fbsi_Getc(
        FBSI_DATA		*this,
        char            *pChar
    )
    {
        int             iRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !fbsi_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pChar) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
    #endif
        
        if (this->pStack && u32Array_getSize(this->pStack)) {
            *pChar = (char)u32Array_DeleteFirst(this->pStack);
            return ERESULT_SUCCESS;
        }
        
        iRc = fgetc(this->pFile);
        *pChar = iRc;
        if (EOF == iRc) {
            return ERESULT_EOF_ERROR;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          G e t w c
    //---------------------------------------------------------------
    
    ERESULT         fbsi_Getwc(
        FBSI_DATA		*this,
        int32_t         *pChar
    )
    {
        int32_t         iRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbsi_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pChar) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (this->pStack && u32Array_getSize(this->pStack)) {
            *pChar = (int32_t)u32Array_DeleteFirst(this->pStack);
            return ERESULT_SUCCESS;
        }
        
        iRc = fgetwc(this->pFile);
        *pChar = iRc;
        if (EOF == iRc) {
            return ERESULT_EOF_ERROR;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          G e t s
    //---------------------------------------------------------------
    
    ERESULT         fbsi_Gets(
        FBSI_DATA		*this,
        uint16_t        max,
        char            *pStr
    )
    {
        char            *pStr2;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbsi_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((NULL == pStr) || (0 == max)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pStr2 = fgets( pStr, max, this->pFile );
        if (NULL == pStr2) {
            if (fbsi_IsAtEOF(this)) {
                return ERESULT_EOF_ERROR;
            }
            return ERESULT_READ_ERROR;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    FBSI_DATA *   fbsi_Init(
        FBSI_DATA       *this,
        PATH_DATA       *pPath
    )
    {
        bool            fRc;
        char            *pFilePath = NULL;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        if (OBJ_NIL == pPath) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_FBSI );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&fbsi_Vtbl);
        
        fRc = fbsi_setPath(this, pPath);
        if (!fRc) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        pFilePath = path_CStringA(this->pPath);
        if (pFilePath == NULL) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pFile = fopen(pFilePath, "r");
        mem_Free(pFilePath);
        pFilePath = NULL;
        if (NULL == this->pFile) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !fbsi_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  A t  E O F
    //---------------------------------------------------------------
    
    ERESULT         fbsi_IsAtEOF(
        FBSI_DATA		*this
    )
    {
        
#ifdef NDEBUG
#else
        if( !fbsi_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (!feof(this->pFile)) {
            return ERESULT_FAILURE_FALSE;
        }
        
        return ERESULT_SUCCESS;
    }
    
    

    //---------------------------------------------------------------
    //                          G e t w c
    //---------------------------------------------------------------
    
    ERESULT         fbsi_Push(
        FBSI_DATA		*this,
        int32_t         chr
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbsi_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (OBJ_NIL == this->pStack) {
            this->pStack = u32Array_New();
            if (OBJ_NIL == this->pStack) {
                DEBUG_BREAK();
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        eRc = u32Array_AppendData(this->pStack, (uint32_t)chr);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     fbsi_ToDebugString(
        FBSI_DATA       *this,
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
    bool            fbsi_Validate(
        FBSI_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_FBSI) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(FBSI_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


