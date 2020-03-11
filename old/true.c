// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   True.c
 *	Generated 11/12/2015 10:21:08
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
#include "true_internal.h"
#include <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    
    static
    TRUE_DATA       *pShared = OBJ_NIL;
    static
    TRUE_DATA       singleton = {{0}};


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TRUE_DATA *     true_Alloc(
    )
    {
        TRUE_DATA       *this = &singleton;
        //uint32_t        cbSize = sizeof(TRUE_DATA);
        
        // Fake Obj initialization.
        memset(this, 0, sizeof(TRUE_DATA));
        //OBJ_INIT_SHARED(cbp,cbSize);
        
        // Return to caller.
        return this;
    }



    TRUE_DATA *     true_New(
    )
    {
        TRUE_DATA       *this;
        
        if (pShared == OBJ_NIL) {
            pShared = true_Alloc( );
            if (pShared) {
                pShared = true_Init(pShared);
            }
        }
        this = pShared;
        return this;
    }



    TRUE_DATA *     true_Shared(
    )
    {
        return true_New();
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        true_getPriority(
        TRUE_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !true_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            true_setPriority(
        TRUE_DATA     *cbp,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !true_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    uint32_t        true_getSize(
        TRUE_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !true_Validate( cbp ) ) {
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

    void            true_Dealloc(
        OBJ_ID          objId
    )
    {
        TRUE_DATA       *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !true_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            true_Disable(
        TRUE_DATA		*cbp
    )
    {

        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !true_Validate( cbp ) ) {
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

    bool            true_Enable(
        TRUE_DATA		*cbp
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !true_Validate( cbp ) ) {
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

    TRUE_DATA *     true_Init(
        TRUE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(TRUE_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        //cbSize = obj_getSize(cbp);
        this = (TRUE_DATA *)obj_Init(this, cbSize, OBJ_IDENT_TRUE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_TRUE);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&true_Vtbl);
        
        //this->stackSize = obj_getMisc1(cbp);
        //this->pArray = ObjArray_New( );

    #ifdef NDEBUG
    #else
        if( !true_Validate(this) ) {
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
    
    bool            true_IsEnabled(
        TRUE_DATA		*cbp
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !true_Validate( cbp ) ) {
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
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          true_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        TRUE_DATA       *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !true_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return true_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return true_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     true_ToDebugString(
        TRUE_DATA       *this,
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
                     "{%p(True) side=%d ",
                     this,
                     true_getSize(this)
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (cbp->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->toDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->toDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf(str, sizeof(str), " %p(True)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    ASTR_DATA *     true_ToJSON(
        TRUE_DATA       *this
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !true_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{\"objectType\":\"%s\"",
                     pInfo->pClassName
                     );
        AStr_AppendA(pStr, str);
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            true_Validate(
        TRUE_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_TRUE) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(TRUE_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


