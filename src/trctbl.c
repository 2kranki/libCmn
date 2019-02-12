// vi:nu:et:sts=4 ts=4 sw=4 tw=90

/*
 * File:   trctbl.c
 * Author: bob
 *
 * Created on December 26, 2014
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



#include "trctbl_internal.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    
    TRCTBL_DATA     *sharedObject = NULL;
    
    
    
 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef NDEBUG
#else
    bool			trctbl_Validate(
        TRCTBL_DATA       *cbp
    );
#endif


    

    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                   C l a s s  M e t h o d s
    //===============================================================


    TRCTBL_DATA *   trctbl_Alloc(
        uint16_t        size
    )
    {
        TRCTBL_DATA     *cbp;
        uint32_t        tableSize;
        
        // Do initialization.
        if (0 == size) {
            return NULL;
        }
        
        tableSize = size * sizeof(TRCTBL_ENTRY);
        tableSize += sizeof(TRCTBL_DATA);
        if ((64 * 1024) <= tableSize) {
            return NULL;
        }
        cbp = obj_Alloc( tableSize );
        
        // Return to caller.
        return( cbp );
    }


    void            trctbl_resetShared(
        void
    )
    {
        TRCTBL_DATA     *cbp = sharedObject;
        
        if (cbp) {
            obj_Release(cbp);
            sharedObject = NULL;
        }
        
    }
    
    
    const
    char *          trctbl_SubsysDesc(
        SUBSYS_CODES    code
    )
    {
        switch (code) {
            case SUBSYS_UNKNOWN:
                return "SUBSYS_UNKNOWN";
                break;
            case SUBSYS_CAN:
                return "SUBSYS_CAN";
                break;
            case SUBSYS_CON:
                return "SUBSYS_CON";
                break;
            case SUBSYS_I2C:
                return "SUBSYS_I2C";
                break;
            case SUBSYS_MON:
                return "SUBSYS_MON";
                break;
            case SUBSYS_RTCC:
                return "SUBSYS_RTCC";
                break;
            case SUBSYS_SPI:
                return "SUBSYS_SPI";
                break;
            case SUBSYS_UART:
                return "SUBSYS_UART";
                break;
        }
    }
    
    
    TRCTBL_DATA *   trctbl_SharedObject(
    )
    {
        TRCTBL_DATA     *cbp = sharedObject;
        
        if (NULL == cbp) {
            cbp = trctbl_Alloc( 256 );
            cbp = trctbl_Init(cbp, 256);
            sharedObject = cbp;
        }
        
        return( cbp );
    }
    
    


    //===============================================================
    //                    P r o p e r t i e s
    //===============================================================

    uint16_t        trctbl_getSize(
        TRCTBL_DATA       *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !trctbl_Validate( cbp ) )
            return -1;
#endif

        // Return to caller.
        return( cbp->size );
    }




    //===============================================================
    //                    M e t h o d s
    //===============================================================


    //**********************************************************
    //                     A d d  E n t r y
    //**********************************************************
    
    void            trctbl_Add(
        TRCTBL_DATA     *cbp,
        uint16_t        ident,
        uint8_t         subsys,
        uint8_t         misc8,
        uint16_t        misc16
    )
    {
#ifdef __APPLE__
#else
        INTERRUPT_STATUS;
#endif
        TRCTBL_ENTRY     *pEntry;
        
        // Do initialization.
        if (NULL == cbp) {
            return;
        }
#ifdef NDEBUG
#else
        if ( !trctbl_Validate(cbp) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        if (obj_IsFlag(cbp, TRCTBL_FLAG_IGNORE)) {
            return;
        }

        trctbl_Lock(cbp);
#ifdef __APPLE__
#else
        DISABLE_INTERRUPTS();
#endif
        pEntry = &cbp->entries[cbp->end];
        pEntry->ident = ident;
        pEntry->subsys = subsys;
        pEntry->misc8 = misc8;
        pEntry->misc16 = misc16;
        ++cbp->numWritten;
        ++cbp->end;
        if (cbp->end == cbp->size) {
            cbp->end = 0;
        }
#ifdef __APPLE__
#else
        RESTORE_INTERRUPTS;
#endif
        trctbl_Unlock(cbp);

    }
    
    
    
    //**********************************************************
    //                     C o p y  T a b l e
    //**********************************************************
    
    // FIXME: figure this out
#ifdef  XYZZY
    TRCTBL *        trctbl_CopyTable(
        TRCTBL_DATA     *cbp
    )
    {
        TRCTBL          *pTable = NULL;
        
        if( NULL == cbp )
            return NULL;

        pTable = (TRCTBL *)mem_Malloc( cbp->pTable->cbSize );
        if (pTable) {
            memmove(pTable, cbp->pTable, cbp->pTable->cbSize);
        }
        
        return pTable;
    }
#endif
    
    
    
    //**********************************************************
    //                        D e a l l o c
    //**********************************************************

    void            trctbl_Dealloc(
        OBJ_ID          objId
    )
    {
        TRCTBL_DATA     *cbp = objId;

        // Do initialization.
#ifdef NDEBUG
#else
        if ( !trctbl_Validate(cbp) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        if (NULL == cbp) {
            return;
        }
        
#ifdef USE_PIC32
        tn_mutex_delete(&cbp->lock);
#endif

        if (cbp == sharedObject) {
            sharedObject = NULL;
        }
        obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //**********************************************************
    //                            G e t
    //**********************************************************

    bool            trctbl_Get(
        TRCTBL_DATA     *cbp,
        uint16_t        index,
        TRCTBL_ENTRY    *pEntry
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ( !trctbl_Validate(cbp) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if ( (index >= cbp->size) ) {
            return false;
        }
        else {
            pEntry->data0 = cbp->entries[index].data0;
            pEntry->data1 = cbp->entries[index].data1;
        }
        
        return true;
    }

     

    //**********************************************************
    //                       I n i t
    //**********************************************************

    TRCTBL_DATA *   trctbl_Init(
        TRCTBL_DATA     *cbp,
        uint16_t        size            // Size of Table in TRCTBL_ENTRY
    )
    {
        uint32_t        cbSize = sizeof(TRCTBL_DATA);

        if( NULL == cbp ) {
            return cbp;
        }
        
        //cbSize = obj_getSize(cbp);
        //cbSize -= sizeof(TRCTBL_DATA);
        //cbSize /= sizeof(TRCTBL_ENTRY);

        cbSize = sizeof(TRCTBL_DATA);
        cbp = obj_Init( cbp, cbSize, OBJ_IDENT_TRCTBL );
        cbp->super.pVtbl = &trctbl_Vtbl;
#ifdef USE_PIC32
        tn_mutex_create(&cbp->lock, TN_MUTEX_PROT_INHERIT, 0);
#endif

        cbp->size = size;
        
        return cbp;
    }

     

    //**********************************************************
    //                        L o c k
    //**********************************************************
    
    void            trctbl_Lock(
        TRCTBL_DATA     *cbp
    )
    {
        
        // Do initialization.
        if (NULL == cbp) {
            return;
        }
#ifdef NDEBUG
#else
        if ( !trctbl_Validate(cbp) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
#ifdef USE_PIC32
        tn_mutex_lock(&cbp->lock, TN_WAIT_INFINITE);
#endif
        
        // Return to caller.
    }
    
    
    
    /**********************************************************
                                P u t
     **********************************************************/

    void            trctbl_Put(
        TRCTBL_DATA       *cbp,
        TRCTBL_ENTRY      *pEntry
    )
    {
#ifdef __APPLE__
#else
        INTERRUPT_STATUS;
#endif

        // Do initialization.
        if (NULL == cbp) {
            return;
        }
#ifdef NDEBUG
#else
        if ( !trctbl_Validate(cbp) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        if (obj_IsFlag(cbp, TRCTBL_FLAG_IGNORE)) {
            return;
        }

        trctbl_Lock(cbp);
#ifdef __APPLE__
#else
        DISABLE_INTERRUPTS();
#endif
        cbp->entries[cbp->end].data0 = pEntry->data0;
        cbp->entries[cbp->end].data1 = pEntry->data1;
        ++cbp->numWritten;
        ++cbp->end;
        if (cbp->end == cbp->size) {
            cbp->end = 0;
        }
#ifdef __APPLE__
#else
        RESTORE_INTERRUPTS;
#endif
        trctbl_Unlock(cbp);

    }

     
    //**********************************************************
    //                      U n l o c k
    //**********************************************************
    
    void            trctbl_Unlock(
        TRCTBL_DATA     *cbp
    )
    {
        
        // Do initialization.
        if (NULL == cbp) {
            return;
        }
#ifdef NDEBUG
#else
        if ( !trctbl_Validate(cbp) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
#ifdef USE_PIC32
        tn_mutex_unlock(&cbp->lock);
#endif
        
        // Return to caller.
    }
    
    
    
    //**********************************************************
    //                      V a l i d a t e
    //**********************************************************

    #ifdef NDEBUG
    #else
    bool			trctbl_Validate(
        TRCTBL_DATA       *cbp
    )
    {

        // Do initialization.

        if( cbp && (OBJ_IDENT_TRCTBL == obj_getType(cbp)) )
            ;
        else
            return false;
        if( !(sizeof(TRCTBL_DATA) == obj_getSize(cbp)) )
            return false;

        // Return to caller.
        return true;
    }
#endif




#ifdef	__cplusplus
}
#endif



