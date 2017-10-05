// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Null.c
 *	Generated 11/12/2015 10:20:43
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
#include "null_internal.h"
#include <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    
    static
    NULL_DATA       *pShared = OBJ_NIL;
    static
    NULL_DATA       singleton = {{0}};


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NULL_DATA *     null_Alloc(
    )
    {
        NULL_DATA       *this = &singleton;
        //uint32_t        cbSize = sizeof(NULL_DATA);
        
        // Fake Obj initialization.
        memset(this, 0, sizeof(NULL_DATA));
        
        // Return to caller.
        return this;
    }



    NULL_DATA *     null_New(
    )
    {
        NULL_DATA       *this;
        
        if (pShared == OBJ_NIL) {
            pShared = null_Alloc( );
            if (pShared) {
                pShared = null_Init(pShared);
            }
        }
        this = pShared;
        return this;
    }



    NULL_DATA *     null_Shared(
    )
    {
        return null_New();
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        null_getPriority(
        NULL_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !null_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            null_setPriority(
        NULL_DATA     *cbp,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !null_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    uint32_t        null_getSize(
        NULL_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !null_Validate( cbp ) ) {
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

    void            null_Dealloc(
        OBJ_ID          objId
    )
    {
        NULL_DATA   *cbp = objId;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !null_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        //obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NULL_DATA *   null_Init(
        NULL_DATA       *cbp
    )
    {
        uint32_t        cbSize = sizeof(NULL_DATA);
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        //cbSize = obj_getSize(cbp);
        cbp = (NULL_DATA *)obj_Init( cbp, cbSize, OBJ_IDENT_NULL );
        if (OBJ_NIL == cbp) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        //obj_setSize(cbp, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)cbp, OBJ_IDENT_NULL);
        obj_setVtbl(cbp, (OBJ_IUNKNOWN *)&null_Vtbl);
        
        //cbp->stackSize = obj_getMisc1(cbp);
        //cbp->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !null_Validate( cbp ) ) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return cbp;
    }

     

    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          null_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    )
    {
        NULL_DATA       *this = objId;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !null_Validate(this) ) {
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
                            return null_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return null_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pStr);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     null_ToDebugString(
        NULL_DATA       *this,
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
                     "{%p(Null) ",
                     this
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (this->pData) {
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
        
        j = snprintf(str, sizeof(str), " %p(Null)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    ASTR_DATA *     null_ToJSON(
        NULL_DATA       *this
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !null_Validate(this) ) {
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
    bool            null_Validate(
        NULL_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_NULL) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(NULL_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


