// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   srcFiles.c
 *	Generated by 08/06/2015 14:36:39
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
#include "srcFiles_internal.h"



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

    SRCFILES_DATA * srcFiles_Alloc(
    )
    {
        SRCFILES_DATA   *cbp;
        uint32_t        cbSize = sizeof(SRCFILES_DATA);
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    SRCFILES_DATA * srcFiles_New(
    )
    {
        SRCFILES_DATA   *cbp;
        
        cbp = srcFiles_Alloc( );
        if (cbp) {
            cbp = srcFiles_Init(cbp);
        }
        
        // Return to caller.
        return( cbp );
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    bool            srcFiles_getReuse(
        SRCFILES_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcFiles_Validate( cbp ) )
            return false;
#endif
        
        // Return to caller.
        return cbp->fReuse;
    }
    
    
    bool            srcFiles_setReuse(
        SRCFILES_DATA   *cbp,
        bool            fValue
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcFiles_Validate( cbp ) )
            return false;
#endif
        
        if (fValue) {
            cbp->fReuse = true;
        }
        else {
            cbp->fReuse = false;
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    uint32_t        srcFiles_getSize(
        SRCFILES_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !srcFiles_Validate( cbp ) ) {
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

    void            srcFiles_Dealloc(
        OBJ_ID          objId
    )
    {
        SRCFILES_DATA   *cbp = objId;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !srcFiles_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (cbp->pStack) {
            obj_Release(cbp->pStack);
            cbp->pStack = OBJ_NIL;
            cbp->pTop = OBJ_NIL;
        }

        obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SRCFILES_DATA * srcFiles_Init(
        SRCFILES_DATA   *this
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_SRCFILES );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        obj_setVtbl(this, &srcFiles_Vtbl);
        
        //cbp->stackSize = obj_getMisc1(cbp);

    #ifdef NDEBUG
    #else
        if( !srcFiles_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->fReuse);
    #endif

        return this;
    }

     
    SRCFILES_DATA * srcFiles_InitAStr(
        SRCFILES_DATA   *this,
        ASTR_DATA       *pAStr,         // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs,
        bool            fRemoveNLs
    )
    {
        SRCFILE_DATA    *pSrc;
        
        this = srcFiles_Init( this );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pSrc = srcFile_Alloc();
        pSrc = srcFile_InitAStr(pSrc, pAStr, pFilePath, tabSize, false, false);
        if (OBJ_NIL == pSrc) {
            obj_Release(this);
            return OBJ_NIL;
        }
        srcFiles_StackPush(this,pSrc);

        return this;
    }
    
    
    SRCFILES_DATA * srcFiles_InitWStr(
        SRCFILES_DATA   *this,
        WSTR_DATA       *pWStr,         // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs,
        bool            fRemoveNLs
    )
    {
        SRCFILE_DATA    *pSrc;
        
        this = srcFiles_Init( this );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pSrc = srcFile_Alloc();
        pSrc = srcFile_InitWStr(pSrc, pWStr, pFilePath, tabSize, false, false);
        if (OBJ_NIL == pSrc) {
            obj_Release(this);
            return OBJ_NIL;
        }
        srcFiles_StackPush(this,pSrc);
        
        return this;
    }
    
    

    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------
    
    TOKEN_DATA *    srcFiles_InputAdvance(
        SRCFILES_DATA   *this,
        uint16_t        numChrs
    )
    {
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcFiles_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pToken = srcFile_InputAdvance(this->pTop, numChrs);
        
        // Return to caller.
        return pToken;
    }
    
    
    
    //--------------------------------------------------------------
    //               I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------
    
    TOKEN_DATA *    srcFiles_InputLookAhead(
        SRCFILES_DATA   *this,
        uint16_t        num
    )
    {
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcFiles_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pToken = srcFile_InputLookAhead(this->pTop, num);
        
        // Return to caller.
        return pToken;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                      S t a c k  G e t
    //---------------------------------------------------------------
    
    SRCFILE_DATA *  srcFiles_StackGet(
        SRCFILES_DATA   *cbp,
        uint16_t        index
    )
    {
        SRCFILE_DATA	*pItem = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcFiles_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pItem = objArray_Get(cbp->pStack, index);
        
        // Return to caller.
        return pItem;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S t a c k  P o p
    //---------------------------------------------------------------
    
    SRCFILE_DATA *  srcFiles_StackPop(
        SRCFILES_DATA   *cbp
    )
    {
        SRCFILE_DATA	*pItem = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcFiles_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        /* Pop 1 element from the top of the parse stack.
         */
        if( objArray_getSize(cbp->pStack) ) {
            pItem = objArray_DeleteLast(cbp->pStack);
            cbp->pTop = pItem;
        }
        else {
            cbp->pTop = OBJ_NIL;
        }
        
        // Return to caller.
        return pItem;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S t a c k  P u s h
    //---------------------------------------------------------------
    
    ERESULT			srcFiles_StackPush(
        SRCFILES_DATA   *cbp,
        SRCFILE_DATA    *pItem
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcFiles_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if  (NULL == pItem) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = objArray_AppendObj(cbp->pStack,pItem,NULL);
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        cbp->pTop = pItem;
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S t a c k  T o p
    //---------------------------------------------------------------
    
    SRCFILE_DATA *  srcFiles_StackTop(
        SRCFILES_DATA   *cbp
    )
    {
        SRCFILE_DATA	*pItem = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcFiles_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
       
        pItem = cbp->pTop;
        
        // Return to caller.
        return pItem;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     srcFiles_ToDebugString(
        SRCFILES_DATA   *this,
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
                     "{%p(srcFiles) ",
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
        
        j = snprintf( str, sizeof(str), " %p(srcFiles)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            srcFiles_Validate(
        SRCFILES_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_SRCFILES) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(SRCFILES_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


