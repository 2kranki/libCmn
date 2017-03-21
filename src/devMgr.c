// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   devMgr.c
 *	Generated 02/24/2016 11:41:23
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
#include "devMgr_internal.h"
#include <AStr.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            devMgr_task_body(
        void            *pData
    )
    {
        //DEVMGR_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    DEVMGR_DATA *     devMgr_Alloc(
        uint16_t        stackSize
    )
    {
        DEVMGR_DATA       *this;
        uint32_t        cbSize = sizeof(DEVMGR_DATA);
        
        // Do initialization.
        
        if (0 == stackSize) {
            stackSize = 256;
        }
        cbSize += stackSize << 2;
        this = obj_Alloc( cbSize );
        obj_setMisc1(this, stackSize);
        
        // Return to caller.
        return( this );
    }



    DEVMGR_DATA *     devMgr_New(
        uint16_t        stackSize
    )
    {
        DEVMGR_DATA       *this;
        
        this = devMgr_Alloc( stackSize );
        if (this) {
            this = devMgr_Init( this );
        } 
        return( this );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    OBJARRAY_DATA * devMgr_getArray(
        DEVMGR_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !devMgr_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    
    bool            devMgr_setArray(
        DEVMGR_DATA     *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !devMgr_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pArray) {
            obj_Release(this->pArray);
        }
        this->pArray = pValue;
        
        return true;
    }
    
    
    
    uint16_t        devMgr_getPriority(
        DEVMGR_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !devMgr_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            devMgr_setPriority(
        DEVMGR_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !devMgr_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        //this->priority = value;
        return true;
    }



    uint32_t        devMgr_getSize(
        DEVMGR_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !devMgr_Validate( this ) ) {
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

    void            devMgr_Dealloc(
        OBJ_ID          objId
    )
    {
        DEVMGR_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !devMgr_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pArray) {
            obj_Release(this->pArray);
            this->pArray = OBJ_NIL;
        }

        obj_Dealloc( this );
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            devMgr_Disable(
        DEVMGR_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !devMgr_Validate( this ) ) {
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

    bool            devMgr_Enable(
        DEVMGR_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !devMgr_Validate( this ) ) {
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

    DEVMGR_DATA *   devMgr_Init(
        DEVMGR_DATA     *this
    )
    {
        uint32_t        cbSize = sizeof(DEVMGR_DATA);
        uint32_t        i;
        
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

        this = (DEVMGR_DATA *)obj_Init( this, cbSize, OBJ_IDENT_DEVMGR );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_DEVMGR);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&devMgr_Vtbl);
        
        listdl_Init(&this->freeList, offsetof(DEVMGR_DEVICE, list));
        listdl_Init(&this->list, offsetof(DEVMGR_DEVICE, list));
        for (i=0; i<MAX_DEVICES; ++i) {
            listdl_Add2Tail(&this->freeList, &this->devices[i]);
        }

    #ifdef NDEBUG
    #else
        if( !devMgr_Validate( this ) ) {
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
    
    bool            devMgr_IsEnabled(
        DEVMGR_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !devMgr_Validate( this ) ) {
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
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     devMgr_ToDebugString(
        DEVMGR_DATA      *this,
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
                     "{%p(devMgr) size=%d ",
                     this,
                     devMgr_getSize(this)
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
        
        j = snprintf( str, sizeof(str), " %p(devMgr)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            devMgr_Validate(
        DEVMGR_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_DEVMGR) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(DEVMGR_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


