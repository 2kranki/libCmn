// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   histBase.c
 *	Generated 02/26/2016 00:57:45
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
#include "histBase_internal.h"
#include <AStr.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            histBase_task_body(
        void            *pData
    )
    {
        //HISTBASE_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    HISTBASE_DATA *     histBase_Alloc(
        uint16_t        tableSize
    )
    {
        HISTBASE_DATA       *this;
        uint32_t        cbSize = sizeof(HISTBASE_DATA);
        
        // Do initialization.
        
        if (0 == tableSize) {
            tableSize = 256;
        }
        if (tableSize && !(tableSize & (tableSize - 1))) {
            // Power of 2!
        }
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        cbSize += tableSize * sizeof(HIST_ENTRY);
        if (cbSize > ((64 * 1024) - 1)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        this = obj_Alloc( cbSize );
        obj_setMisc1(this, tableSize);
        
        // Return to caller.
        return( this );
    }



    HISTBASE_DATA *     histBase_New(
        DEVMGR_DATA     *pMgr,
        uint16_t        tableSize           // Number of elements
    )
    {
        HISTBASE_DATA       *this;
        
        this = histBase_Alloc( tableSize );
        if (this) {
            this = histBase_Init( this, pMgr );
        } 
        return( this );
    }



    const
    char *          histBase_SubsysDesc(
        HIST_SUBSYS     code
    )
    {
        switch (code) {
            case HIST_SUBSYS_UNKNOWN:
                return "UNKNOWN";
                break;
            case HIST_SUBSYS_CANBASE:
                return "CANBASE";
                break;
            case HIST_SUBSYS_CP0BASE:
                return "CP0BASE";
                break;
            case HIST_SUBSYS_CP0DEV:
                return "CP0DEV";
                break;
            case HIST_SUBSYS_OSCBASE:
                return "OSCBASE";
                break;
            case HIST_SUBSYS_RTCCBASE:
                return "RTCCBASE";
                break;
            case HIST_SUBSYS_SYSBASE:
                return "SYSBASE";
                break;
            case HIST_SUBSYS_TMR1BASE:
                return "TMR1BASE";
                break;
            case HIST_SUBSYS_TMRNBASE:
                return "TMRNBASE";
                break;
            case HIST_SUBSYS_UARTBASE:
                return "UARTBASE";
                break;
            case HIST_SUBSYS_UARTDEV:
                return "UARTDEV";
                break;
        }
        return "";
    }
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    bool            histBase_setCount(
        HISTBASE_DATA   *this,
        uint32_t        (*pCountFunc)(void *),
        void            *pCountData
    )
    {
#ifdef NDEBUG
#else
        if( !histBase_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        this->pCountFunc = pCountFunc;
        this->pCountData = pCountData;
        
        return true;
    }
    
    
    
    uint32_t        histBase_getSize(
        HISTBASE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !histBase_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        return this->size;
    }



    bool            histBase_setWrap(
        HISTBASE_DATA   *this,
        void            (*pWrapFunc)(void *,HISTBASE_DATA *),
        void            *pWrapData
    )
    {
#ifdef NDEBUG
#else
        if( !histBase_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        this->pWrapFunc = pWrapFunc;
        this->pWrapData = pWrapData;
        
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            histBase_Dealloc(
        OBJ_ID          objId
    )
    {
        HISTBASE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !histBase_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            ((HISTBASE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((DEVBASE_DATA *)this,NULL);
        }

        this->mask = 0;
        this->size = 0;
        this->numWrite = 0;
        
        this->pDevVtbl->iVtbl.pDealloc( this );
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            histBase_Disable(
        HISTBASE_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !histBase_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    HISTBASE_DATA * histBase_Init(
        HISTBASE_DATA   *this,
        DEVMGR_DATA     *pMgr
    )
    {
        uint32_t        cbSize = sizeof(HISTBASE_DATA);
        uint32_t        tableSize = 0;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        tableSize = obj_getMisc(this);
        cbSize += tableSize * sizeof(HIST_ENTRY);
        if (cbSize > ((64 * 1024) - 1)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        this = (HISTBASE_DATA *)devBase_Init( (DEVBASE_DATA *)this, pMgr );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);         // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_HISTBASE);
        this->pDevVtbl = (DEVBASE_VTBL *)obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&histBase_Vtbl);
        
        this->size = tableSize;
        this->mask = tableSize - 1;
        this->numWrite = 0;
        obj_FlagOff(this, HISTBASE_FLAG_LOCKED);
        
    #ifdef NDEBUG
    #else
        if( !histBase_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->array);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I o c t r l
    //---------------------------------------------------------------
    
    ERESULT         histBase_Ioctl(
        HISTBASE_DATA	*this,
        uint32_t        request,
        void            *pParm1,
        void            *pParm2
    )
    {
        HIST_ENTRY      entry;
        ERESULT         eRc;
        uint32_t        value;
        uint32_t        i;
        HIST_ENTRY      *pEntry;
        void            (*pFunc)(void *, HIST_ENTRY *);
        bool            fWeLockedTable = false;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !histBase_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = this->pDevVtbl->pIoctl((OBJ_ID)this, request, pParm1, pParm2);
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        
        switch (request & 0xFF) {

            case HIST_IOCTL_OP_ADD:
                if (obj_IsFlag(this, HISTBASE_FLAG_LOCKED)) {
                    return ERESULT_FILE_LOCK_VIOLATION;
                }
                if (this->pWrapFunc) {
                    if ((this->numWrite > 0) && (0 == (this->numWrite & this->mask))) {
                        this->pWrapFunc(this->pWrapData,this);
                    }
                }
                entry.ident = (request >> 8) & 0xFFFF;
                entry.subsys = (request >> 24) & 0xFF;
                entry.data0 = (uint32_t)pParm1;
                entry.data1 = (uint32_t)pParm2;
                if (this->pCountFunc) {
                    entry.timeStamp = this->pCountFunc(this->pCountData);
                }
                memmove(
                        &this->array[this->numWrite & this->mask],
                        &entry,
                        sizeof(HIST_ENTRY)
                );
                ++this->numWrite;
                break;
                
            case HIST_IOCTL_OP_LOCK:
                if (obj_IsFlag(this, HISTBASE_FLAG_LOCKED)) {
                    return ERESULT_FILE_LOCK_VIOLATION;
                }
                obj_FlagOn(this, HISTBASE_FLAG_LOCKED);
                break;
                
            case HIST_IOCTL_OP_UNLOCK:
                if (!obj_IsFlag(this, HISTBASE_FLAG_LOCKED)) {
                    return ERESULT_FILE_LOCK_VIOLATION;
                }
                obj_FlagOff(this, HISTBASE_FLAG_LOCKED);
                break;
                
            case HIST_IOCTL_OP_SIZE:
                if (pParm1) {
                    value = this->size * sizeof(HIST_ENTRY);
                    *(uint32_t *)pParm1 = value;
                }
                break;
                
            case HIST_IOCTL_OP_ENUMERATE:
                if (!obj_IsFlag(this, HISTBASE_FLAG_LOCKED)) {
                    obj_FlagOn(this, HISTBASE_FLAG_LOCKED);
                    fWeLockedTable = true;
                }
                if (NULL == pParm1) {
                    return ERESULT_INVALID_PARAMETER;
                }
                pFunc = pParm1;
                for (i=0; i<this->size; ++i) {
                    pEntry = &this->array[(this->numWrite + i) & this->mask];
                    pFunc(pParm2,pEntry);
                }
                if (fWeLockedTable) {
                    obj_FlagOff(this, HISTBASE_FLAG_LOCKED);
                }
                break;
                
            default:
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
                break;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                       R e a d
    //---------------------------------------------------------------
    
    ERESULT         histBase_Read(
        HISTBASE_DATA	*this,
        uint32_t        amt,
        void            *pData,
        uint32_t        *pAmtRead
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        HIST_ENTRY      *pEntry;
        
        // Do initialization.
        if (pAmtRead) {
            *pAmtRead = 0;
        }
#ifdef NDEBUG
#else
        if( !histBase_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = this->pDevVtbl->pRead((OBJ_ID)this, amt, pData, pAmtRead);
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        
        if (!obj_IsFlag(this, HISTBASE_FLAG_LOCKED)) {
            return ERESULT_FILE_LOCK_VIOLATION;
        }
        
        // We want to send the table with the oldest entry first
        for (i=0; i<this->size; ++i) {
            pEntry = &this->array[(this->numWrite + i) & this->mask];
            if (amt >= sizeof(HIST_ENTRY)) {
                memmove(pData, pEntry, sizeof(HIST_ENTRY));
                amt -= sizeof(HIST_ENTRY);
                pData = ((uint8_t *)pData) + sizeof(HIST_ENTRY);
                *pAmtRead += sizeof(HIST_ENTRY);
            }
            else {
                break;
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                        S t a r t
    //---------------------------------------------------------------
    
    ERESULT         histBase_Start(
        HISTBASE_DATA	*this,
        void            *pParm
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !histBase_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        eRc = this->pDevVtbl->pStart((OBJ_ID)this, NULL);
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                        S t o p
    //---------------------------------------------------------------
    
    ERESULT         histBase_Stop(
        HISTBASE_DATA	*this,
        void            *pParm
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !histBase_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_FlagOn(this, HISTBASE_FLAG_LOCKED);
        eRc = this->pDevVtbl->pStop((OBJ_ID)this, NULL);
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     histBase_ToDebugString(
        HISTBASE_DATA      *this,
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
                     "{%p(histBase) size=%d ",
                     this,
                     histBase_getSize(this)
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
        
        j = snprintf( str, sizeof(str), " %p(histBase)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            histBase_Validate(
        HISTBASE_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_HISTBASE) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(HISTBASE_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


