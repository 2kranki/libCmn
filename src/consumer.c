// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   consumer.c
 *	Generated 06/29/2016 10:31:45
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
#include "consumer_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    void *          consumer_task_body(
        void            *pData
    )
    {
        CONSUMER_DATA   *this = pData;
        uint8_t         msg[512];
        uint8_t         *pEntry = (void *)msg;
        bool            fRc;
        
        // WARNING: We had to make this pausible.
        fRc = cb_Get(this->pBuffer, pEntry);
        if (fRc) {
            if (this->pMsgRcvRoutine) {
                this->pMsgRcvRoutine(this->pRoutineData, pEntry);
            }
         }
        
        return NULL;
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    CONSUMER_DATA * consumer_Alloc(
    )
    {
        CONSUMER_DATA   *this;
        uint32_t        cbSize = sizeof(CONSUMER_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return( this );
    }



    CONSUMER_DATA * consumer_New(
        uint16_t        messageSize,
        uint16_t        messageCount,       // Max Message Queue size
        void *          (*pMsgRoutine)(void *, void *),
        void            *pRoutineData
    )
    {
        CONSUMER_DATA   *this;
        
        this = consumer_Alloc( );
        if (this) {
            this =  consumer_Init(
                                 this,
                                 messageSize,
                                 messageCount,
                                 pMsgRoutine,
                                 pRoutineData
                    );
        } 
        return( this );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         consumer_getLastError(
        CONSUMER_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !consumer_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    bool            consumer_setLastError(
        CONSUMER_DATA   *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !consumer_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    uint16_t        consumer_getPriority(
        CONSUMER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !consumer_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            consumer_setPriority(
        CONSUMER_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !consumer_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        //this->priority = value;
        return true;
    }



    uint32_t        consumer_getSize(
        CONSUMER_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !consumer_Validate( this ) ) {
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

    void            consumer_Dealloc(
        OBJ_ID          objId
    )
    {
        CONSUMER_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !consumer_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((CONSUMER_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        // WARNING: Order is important here!
        
        cb_Pause(this->pBuffer);
        psxThread_Terminate(this->pThread);
        
        if (this->pThread) {
            obj_Release(this->pThread);
            this->pThread = OBJ_NIL;
        }
        
        if (this->pLock) {
            obj_Release(this->pLock);
            this->pLock = OBJ_NIL;
        }
        
        if (this->pBuffer) {
            obj_Release(this->pBuffer);
            this->pBuffer = OBJ_NIL;
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc( this );
        //this->pOBJ->iVtbl.pDealloc( this );  // Needed for Inheritance
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            consumer_Disable(
        CONSUMER_DATA   *this
    )
    {

        // Do initialization.
        if (NULL == this) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !consumer_Validate( this ) ) {
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
    //                          E n a b l e
    //---------------------------------------------------------------

    bool            consumer_Enable(
        CONSUMER_DATA	*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !consumer_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    CONSUMER_DATA * consumer_Init(
        CONSUMER_DATA   *this,
        uint16_t        messageSize,
        uint16_t        messageCount,       // Max Message Queue size
        void *          (*pMsgRoutine)(void *, void *),
        void            *pRoutineData
    )
    {
        uint32_t        cbSize = sizeof(CONSUMER_DATA);
        
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

        this = (OBJ_ID)obj_Init( this, cbSize, OBJ_IDENT_CONSUMER );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_CONSUMER); // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&consumer_Vtbl);
        
        this->pMsgRcvRoutine = pMsgRoutine;
        this->pRoutineData = pRoutineData;
        
        this->pBuffer = cb_New(messageSize, messageCount);
        if (OBJ_NIL == this->pBuffer) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pLock = psxLock_New();
        if (OBJ_NIL == this->pLock) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pThread = psxThread_New(consumer_task_body, this, 0);
        if (OBJ_NIL == this->pThread) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !consumer_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            consumer_IsEnabled(
        CONSUMER_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !consumer_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(this))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                    S e n d  M e s s a g e
    //---------------------------------------------------------------
    
    ERESULT         consumer_SendMessage(
        CONSUMER_DATA	*this,
        void            *pMsg
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !consumer_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        fRc = cb_Put(this->pBuffer, pMsg);
        if (!fRc) {
            consumer_setLastError(this, ERESULT_GENERAL_FAILURE);
            return ERESULT_GENERAL_FAILURE;
        }
        
        // Return to caller.
        consumer_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     consumer_ToDebugString(
        CONSUMER_DATA   *this,
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
                     "{%p(consumer) size=%d ",
                     this,
                     consumer_getSize(this)
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
        
        j = snprintf( str, sizeof(str), " %p(consumer)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            consumer_Validate(
        CONSUMER_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_CONSUMER) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(CONSUMER_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


