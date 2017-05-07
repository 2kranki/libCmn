// vi:nu:et:sts=4 ts=4 sw=4
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




#include        "objCb_internal.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    

 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef NDEBUG
#else
    static
    bool			objCb_Validate(
        OBJCB_DATA         *cbp
    );
#endif


#ifdef XYZZY
    static
    OBJ_ID          objCb_GetPtr(
        OBJCB_DATA      *cbp,
        uint16_t        index
    )
    {
        OBJ_ID         ptr;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objCb_Validate( cbp ) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if( (index > 0) && (index <= cbp->cEntries) )
            ;
        else {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        ptr = &cbp->entries[index];

        // Return to caller.
        return( ptr );
    }
#endif

    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    //---------------------------------------------------------------
    //                        A l l o c
    //---------------------------------------------------------------

    OBJCB_DATA *       objCb_Alloc(
        uint16_t        size            // Number of Elements in Buffer
    )
    {
        OBJCB_DATA      *cbp;
        uint32_t        cbSize;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (0 == size) {
            DEBUG_BREAK();
            return NULL;
        }
        // Must be less than 2^31 because of numWritten and numRead.
        // This should not happen since size is 16 bits.
        if (size < 0x7FFF)
            ;
        else {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        cbSize = size * sizeof(OBJ_ID);
        cbSize += sizeof(OBJCB_DATA);
        if ((64 * 1024) <= cbSize) {
            return NULL;
        }
        
        cbp = obj_Alloc( cbSize );
        obj_setMisc1( cbp, size );
        
        // Return to caller.
        return( cbp );
    }



    OBJCB_DATA *       objCb_New(
        uint16_t        size            // Number of Elements in Buffer
    )
    {
        OBJCB_DATA      *cbp;
        
        cbp = objCb_Alloc( size );
        cbp = objCb_Init( cbp );
        
        return( cbp );
    }
    
    
    
    

    //===============================================================
    //                    P r o p e r t i e s
    //===============================================================

    uint16_t        objCb_getSize(
        OBJCB_DATA       *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objCb_Validate( cbp ) ) {
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

    uint16_t        objCb_Count(
        OBJCB_DATA       *cbp
    )
    {
        uint16_t        count;
#ifdef __APPLE__
#else
        INTERRUPT_STATUS;
#endif
        
        // Validate the input parameters.
    #ifdef NDEBUG
    #else
        if( !objCb_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
    #endif
        
        // We need to disable interrupts so that we have
        // uninterrupted access to both variables.
#ifdef __APPLE__
#else
        DISABLE_INTERRUPTS();
#endif
        
        count = (uint16_t)(cbp->numWritten - cbp->numRead);
        
#ifdef __APPLE__
#else
        RESTORE_INTERRUPTS;
#endif
        
        // Return to caller.
        return( count );
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------
    
    void        objCb_Dealloc(
        OBJ_ID      objId
    )
    {
        OBJCB_DATA		*cbp = objId;
        uint32_t        i;
        OBJ_ID          pObj;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ( !objCb_Validate(cbp) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
#ifdef USE_PIC32
        tn_mutex_delete(&cbp->putMutex);
        tn_mutex_delete(&cbp->getMutex);
#endif
        
        for (i=0; i<cbp->cEntries; ++i) {
            pObj = cbp->entries[i];
            if (pObj) {
                obj_Release(pObj);
                cbp->entries[i] = OBJ_NIL;
            }
        }
        
        obj_Dealloc(cbp);
        cbp = NULL;
        
        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //                            G e t
    //---------------------------------------------------------------

    bool            objCb_Get(
        OBJCB_DATA      *cbp,
        OBJ_ID          *ppData
    )
    {
        bool            fRc = false;
#ifdef USE_PIC32
        TN_RC           tRc;
#endif

        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !objCb_Validate(cbp) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
#ifdef USE_PIC32
        tRc = tn_mutex_lock( &cbp->getMutex, TN_WAIT_INFINITE );
        if (TN_RC_OK == tRc)
            ;
        else {
            return false;
        }
#endif
        
        if ( (ppData == NULL) || objCb_isEmpty(cbp) ) {
        }
        else {
            *ppData = cbp->entries[cbp->start];
            cbp->entries[cbp->start] = OBJ_NIL;
            // below needed if multi-processor
            //__sync_fetch_and_add( &cbp->numRead, 1 );
            ++cbp->numRead;
            ++cbp->start;
            if (cbp->start == cbp->cEntries) {
                cbp->start = 0;
            }
            fRc = true;
        }
        
#ifdef USE_PIC32
        tn_mutex_unlock(&cbp->getMutex);
#endif
        
        return fRc;
    }

     

    //---------------------------------------------------------------
    //                       i s E m p t y
    //---------------------------------------------------------------

    bool            objCb_isEmpty(
        OBJCB_DATA         *cbp
    )
    {
        bool            fRc = false;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !objCb_Validate(cbp) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        if (((uint16_t)(cbp->numWritten - cbp->numRead)) == 0)
            fRc = true;
        
        return fRc;
    }


     
    //---------------------------------------------------------------
    //                       i s F u l l
    //---------------------------------------------------------------

    bool            objCb_isFull(
        OBJCB_DATA       *cbp
    )
    {
        bool            fRc = false;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !objCb_Validate(cbp) ) {
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

    OBJCB_DATA *       objCb_Init(
        OBJCB_DATA         *cbp
    )
    {
        uint16_t        size =  obj_getMisc1(cbp);


        // Do initialization.
        if (NULL == cbp) {
            return NULL;
        }
        
        cbp = obj_Init( cbp, obj_getSize(cbp), OBJ_IDENT_OBJCB );
        if (NULL == cbp) {
            return NULL;
        }
        obj_setVtbl(cbp,&objCb_Vtbl);
        
        cbp->cEntries = size;
        
#ifdef USE_PIC32
        tn_mutex_create(&cbp->getMutex, TN_MUTEX_PROT_INHERIT, 0);
        tn_mutex_create(&cbp->putMutex, TN_MUTEX_PROT_INHERIT, 0);
#endif
        
        return cbp;
    }

     

    //---------------------------------------------------------------
    //                            P u t
    //---------------------------------------------------------------

    bool            objCb_Put(
        OBJCB_DATA      *cbp,
        OBJ_ID          pValue
    )
    {
        bool            fRc = false;
#ifdef USE_PIC32
        TN_RC           tRc;
#endif

        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !objCb_Validate(cbp) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

#ifdef USE_PIC32
        tRc = tn_mutex_lock( &cbp->putMutex, TN_WAIT_INFINITE );
        if (TN_RC_OK == tRc)
            ;
        else {
            return false;
        }
#endif

        if ( objCb_isFull(cbp) ) {
        }
        else {
            obj_Retain(pValue);
            cbp->entries[cbp->end] = pValue;
            ++cbp->numWritten;
            ++cbp->end;
            if (cbp->end == cbp->cEntries) {
                cbp->end = 0;
            }
            fRc = true;
        }

#ifdef USE_PIC32
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
    bool			objCb_Validate(
        OBJCB_DATA       *cbp
    )
    {

        // Do initialization.

        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_OBJCB) )
                ;
            else
                return false;
        }
        else {
            DEBUG_BREAK();
            return false;
        }
        if( obj_getSize(cbp) >= sizeof(OBJCB_DATA) )
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




