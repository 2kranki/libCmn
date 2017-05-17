// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   cb.c
 * Author: bob
 *
 * Created on October 25, 2014
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




#include "cb_internal.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    

 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef NDEBUG
#else
    static
    bool			cb_Validate(
        CB_DATA         *cbp
    );
#endif


    static
    void *          cb_GetPtr(
        CB_DATA         *cbp,
        uint16_t        index
    )
    {
        uint8_t         *ptr;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cb_Validate( cbp ) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if( index >= cbp->cEntries ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        ptr = &cbp->entries[(index * cbp->elemSize)];

        // Return to caller.
        return( ptr );
    }




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    //---------------------------------------------------------------
    //                        A l l o c
    //---------------------------------------------------------------

    CB_DATA *       cb_Alloc(
        uint16_t        size,           // Number of Elements in Buffer
        uint16_t        elemSize        // Element Size in bytes
    )
    {
        CB_DATA         *cbp;
        uint32_t        cbSize;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (0 == size) {
            DEBUG_BREAK();
            return NULL;
        }
        if (0 == elemSize) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        cbSize = size * elemSize;
        cbSize += sizeof(CB_DATA);
        if ((64 * 1024) <= cbSize) {
            return NULL;
        }
        
        cbp = obj_Alloc( cbSize );
        obj_setMisc1(cbp, size);
        obj_setMisc2(cbp, elemSize);
        
        // Return to caller.
        return( cbp );
    }



    

    //===============================================================
    //                    P r o p e r t i e s
    //===============================================================

    uint16_t        cb_getSize(
        CB_DATA       *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cb_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        // Return to caller.
        return( cbp->cEntries );
    }




    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        C o u n t
    //---------------------------------------------------------------

    uint16_t        cb_Count(
        CB_DATA       *cbp
    )
    {
        uint16_t        count;
#ifdef __PIC32MX_ENV__
        INTERRUPT_STATUS;
#endif
        
        // Validate the input parameters.
    #ifdef NDEBUG
    #else
        if( !cb_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
    #endif
        
        // We need to disable interrupts so that we have
        // uninterrupted access to both variables.
#ifdef __PIC32MX_ENV__
        DISABLE_INTERRUPTS();
#endif
        
        count = (uint16_t)(cbp->numWritten - cbp->numRead);
        
#ifdef __PIC32MX_ENV__
        RESTORE_INTERRUPTS;
#endif
        
        // Return to caller.
        return( count );
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------
    
    void        cb_Dealloc(
        OBJ_ID      objId
    )
    {
        CB_DATA		*cbp = objId;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ( !cb_Validate(cbp) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
#ifdef __PIC32MX_TNEO_ENV__
        tn_mutex_delete(&cbp->putMutex);
        tn_mutex_delete(&cbp->getMutex);
#endif
        
        obj_Dealloc(cbp);
        cbp = NULL;
        
        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //                            G e t
    //---------------------------------------------------------------

    bool            cb_Get(
        CB_DATA         *cbp,
        void            *pData
    )
    {
        bool            fRc = false;
        uint8_t         *pElem;
#ifdef __PIC32MX_TNEO_ENV__
        TN_RC           tRc;
#endif

        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !cb_Validate(cbp) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
#ifdef __PIC32MX_TNEO_ENV__
        tRc = tn_mutex_lock( &cbp->getMutex, TN_WAIT_INFINITE );
        if (TN_RC_OK == tRc)
            ;
        else {
            return false;
        }
#endif
        
        if ( (pData == NULL) || cb_isEmpty(cbp) ) {
        }
        else {
            pElem = cb_GetPtr( cbp, cbp->start );
            if( pElem ) {
                if( pData ) {
                    memmove( pData, pElem, cbp->elemSize );
                }
                // below needed if multi-processor
                //__sync_fetch_and_add( &cbp->numRead, 1 ); 
                ++cbp->numRead;
                ++cbp->start;
                if (cbp->start == cbp->cEntries) {
                    cbp->start = 0;
                }
                fRc = true;
            }
        }
        
#ifdef __PIC32MX_TNEO_ENV__
        tn_mutex_unlock(&cbp->getMutex);
#endif
        
        return fRc;
    }

     

    //---------------------------------------------------------------
    //                       i s E m p t y
    //---------------------------------------------------------------

    bool            cb_isEmpty(
        CB_DATA         *cbp
    )
    {
        bool            fRc = false;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !cb_Validate(cbp) ) {
            DEBUG_BREAK();
            return cbp;
        }
    #endif

        if (((uint16_t)(cbp->numWritten - cbp->numRead)) == 0)
            fRc = true;
        
        return fRc;
    }


     
    //---------------------------------------------------------------
    //                       i s F u l l
    //---------------------------------------------------------------

    bool            cb_isFull(
        CB_DATA       *cbp
    )
    {
        bool            fRc = false;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !cb_Validate(cbp) ) {
            DEBUG_BREAK();
            return cbp;
        }
    #endif

        if ( ((uint16_t)(cbp->numWritten - cbp->numRead)) == cbp->cEntries )
            fRc = true;
        
        return fRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    CB_DATA *       cb_Init(
        CB_DATA         *this
    )
    {
        uint32_t        cbSize = sizeof(CB_DATA);
        uint32_t        dataSize;
        uint16_t        size =  obj_getMisc1(this);
        uint16_t        elemSize =  obj_getMisc2(this);


        // Do initialization.
        if (NULL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( 0 == size ) {
            DEBUG_BREAK();
            return NULL;
        }
        if( 0 == elemSize ) {
            DEBUG_BREAK();
            return NULL;
        }
        // Must be less than 2^31 because of numWritten and numRead.
        // This should not happen since size is 16 bits.
        if ( !(size < 0x7FFF) ) {
            return NULL;
        }
#endif
        cbSize += size * elemSize;

        
        this = obj_Init( this, cbSize, OBJ_IDENT_CB );
        if (NULL == this) {
            return NULL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this,(OBJ_IUNKNOWN *)&cb_Vtbl);
        
        dataSize = size * elemSize;
        if (dataSize >= (64 * 1024)) {
            return NULL;
        }        
        this->cEntries = size;
        this->elemSize = elemSize;
        
#ifdef __PIC32MX_TNEO_ENV__
        tn_mutex_create(&this->getMutex, TN_MUTEX_PROT_INHERIT, 0);
        tn_mutex_create(&this->putMutex, TN_MUTEX_PROT_INHERIT, 0);
#endif
        
        return this;
    }

     

    //---------------------------------------------------------------
    //                            P u t
    //---------------------------------------------------------------

    bool            cb_Put(
        CB_DATA         *cbp,
        void            *pValue
    )
    {
        bool            fRc = false;
        uint8_t         *pElem;
#ifdef __PIC32MX_TNEO_ENV__
        TN_RC           tRc;
#endif

        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !cb_Validate(cbp) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

#ifdef __PIC32MX_TNEO_ENV__
        tRc = tn_mutex_lock( &cbp->putMutex, TN_WAIT_INFINITE );
        if (TN_RC_OK == tRc)
            ;
        else {
            return false;
        }
#endif

        if ( cb_isFull(cbp) ) {
        }
        else {
            pElem = cb_GetPtr( cbp, cbp->end );
            if (pElem) {
                memmove(pElem, pValue, cbp->elemSize);
                ++cbp->numWritten;
                ++cbp->end;
                if (cbp->end == cbp->cEntries) {
                    cbp->end = 0;
                }
                fRc = true;
            }
        }

#ifdef __PIC32MX_TNEO_ENV__
        tn_mutex_unlock(&cbp->putMutex);
#endif
        
        return fRc;
    }



    //---------------------------------------------------------------
    //                        V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    static
    bool			cb_Validate(
        CB_DATA       *cbp
    )
    {

        // Do initialization.

        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_CB) )
                ;
            else
                return false;
        }
        else {
            DEBUG_BREAK();
            return false;
        }
        if( obj_getSize(cbp) >= sizeof(CB_DATA) )
            ;
        else {
            DEBUG_BREAK();
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif



#ifdef	__cplusplus
}
#endif




