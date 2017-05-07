// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   devBase.c
 *	Generated 02/23/2016 11:32:06
 *
 * Notes:
 *  --      We use the object enable/disable mechanism for start/
 *          stop purposes.
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
#include "devBase_internal.h"
#include <AStr.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            devBase_task_body(
        void            *pData
    )
    {
        //DEVBASE_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    DEVBASE_DATA *  devBase_Alloc(
    )
    {
        DEVBASE_DATA    *this;
        uint32_t        cbSize = sizeof(DEVBASE_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return( this );
    }



    DEVBASE_DATA *  devBase_New(
        DEVMGR_DATA     *pMgr
    )
    {
        DEVBASE_DATA       *this;
        
        this = devBase_Alloc( );
        if (this) {
            this = devBase_Init( this, pMgr );
        } 
        return( this );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    DEVMGR_DATA *   devBase_getMgr(
        DEVBASE_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !devBase_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pMgr;
    }
    
    
    bool            devBase_setMgr(
        DEVBASE_DATA    *this,
        DEVMGR_DATA     *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !devBase_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pMgr) {
            obj_Release(this->pMgr);
        }
        this->pMgr = pValue;
        
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            devBase_Dealloc(
        OBJ_ID          objId
    )
    {
        DEVBASE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !devBase_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (obj_IsEnabled(this)) {
            ((DEVBASE_VTBL *)obj_getVtbl(this))->pStop(this,NULL);
        }
        
        devBase_setMgr(this, OBJ_NIL);

        obj_Dealloc( this );
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                       G e t c
    //---------------------------------------------------------------
    
    ERESULT         devBase_Getc(
        DEVBASE_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !devBase_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (!obj_IsEnabled(this)) {
            DEBUG_BREAK();
            return ERESULT_FILE_CLOSED;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    DEVBASE_DATA *   devBase_Init(
        DEVBASE_DATA    *this,
        DEVMGR_DATA     *pMgr
    )
    {
        uint32_t        cbSize = sizeof(DEVBASE_DATA);
        
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

        this = (DEVBASE_DATA *)obj_Init( this, cbSize, OBJ_IDENT_DEVBASE );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_DEVBASE);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&devBase_Vtbl);
        
        devBase_setMgr(this, pMgr);

    #ifdef NDEBUG
    #else
        if( !devBase_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I o c t r l
    //---------------------------------------------------------------
    
    ERESULT         devBase_Ioctl(
        DEVBASE_DATA	*this,
        uint32_t        request,
        void            *pParm1,
        void            *pParm2
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !devBase_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (!obj_IsEnabled(this)) {
            DEBUG_BREAK();
            return ERESULT_FILE_CLOSED;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                       P u t c
    //---------------------------------------------------------------
    
    ERESULT         devBase_Putc(
        DEVBASE_DATA	*this,
        int32_t         data
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !devBase_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (!obj_IsEnabled(this)) {
            DEBUG_BREAK();
            return ERESULT_FILE_CLOSED;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                       R e a d
    //---------------------------------------------------------------
    
    ERESULT         devBase_Read(
        DEVBASE_DATA	*this,
        uint32_t        amt,
        void            *pData,
        uint32_t        *pAmtRead
    )
    {
        
        // Do initialization.
        if (pAmtRead) {
            *pAmtRead = 0;
        }
#ifdef NDEBUG
#else
        if( !devBase_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (!obj_IsEnabled(this)) {
            DEBUG_BREAK();
            return ERESULT_FILE_CLOSED;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                       S t a r t
    //---------------------------------------------------------------
    
    ERESULT         devBase_Start(
        DEVBASE_DATA	*this,
        void            *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !devBase_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_OPEN_ERROR;
        }
        
        obj_Enable(this);
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                       S t o p
    //---------------------------------------------------------------
    
    ERESULT         devBase_Stop(
        DEVBASE_DATA	*this,
        void            *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !devBase_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (!obj_IsEnabled(this)) {
            DEBUG_BREAK();
            return ERESULT_FILE_CLOSED;
        }
        
        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     devBase_ToDebugString(
        DEVBASE_DATA      *this,
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
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(devBase) ",
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
        
        j = snprintf( str, sizeof(str), " %p(devBase)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       W r i t e
    //---------------------------------------------------------------
    
    ERESULT         devBase_Write(
        DEVBASE_DATA	*this,
        uint32_t        amt,
        void            *pData,
        uint32_t        *pAmtWritten
    )
    {
        
        // Do initialization.
        if (pAmtWritten) {
            *pAmtWritten = 0;
        }
#ifdef NDEBUG
#else
        if( !devBase_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (!obj_IsEnabled(this)) {
            DEBUG_BREAK();
            return ERESULT_FILE_CLOSED;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            devBase_Validate(
        DEVBASE_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_DEVBASE) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(DEVBASE_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


