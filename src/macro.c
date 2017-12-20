// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   macro.c
 *	Generated 08/08/2015 08:06:48
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
#include "macro_internal.h"
#include <utf8.h>
#include <stdio.h>



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

    MACRO_DATA *     macro_Alloc(
    )
    {
        MACRO_DATA      *this;
        uint32_t        cbSize = sizeof(MACRO_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    MACRO_DATA *    macro_NewWithName(
        NAME_DATA       *pName
    )
    {
        MACRO_DATA      *this;
        
        if (OBJ_NIL == pName) {
            return OBJ_NIL;
        }
        
        this = macro_Alloc( );
        if (this) {
            this = macro_Init(this,pName);
        }
        
        return this;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    NAME_DATA *     macro_getName(
        MACRO_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !macro_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return node_getName((NODE_DATA *)this);
    }
    
    
    bool            macro_setName(
        MACRO_DATA      *this,
        NAME_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !macro_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->pName = pValue;
        
        return true;
    }
    
    
    
    uint16_t        macro_getPriority(
        MACRO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !macro_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            macro_setPriority(
        MACRO_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !macro_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        //this->priority = value;
        return true;
    }



    uint32_t        macro_getSize(
        MACRO_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !macro_Validate(this) ) {
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

    void            macro_Dealloc(
        OBJ_ID          objId
    )
    {
        MACRO_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !macro_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        macro_setName(this, OBJ_NIL);
        if (this->pBody) {
            obj_Release(this->pBody);
            this->pBody = OBJ_NIL;
        }
        if (this->pKeywordParameters) {
            obj_Release(this->pKeywordParameters);
            this->pKeywordParameters = OBJ_NIL;
        }
        if (this->pPositionalParameters) {
            obj_Release(this->pPositionalParameters);
            this->pPositionalParameters = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            macro_Disable(
        MACRO_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !macro_Validate(this) ) {
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

    bool            macro_Enable(
        MACRO_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !macro_Validate(this) ) {
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

    MACRO_DATA *   macro_Init(
        MACRO_DATA      *this,
        NAME_DATA       *pName
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (MACRO_DATA *)node_InitWithName((NODE_DATA *)this, pName, OBJ_NIL);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_MACRO);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&macro_Vtbl);
        
        macro_setName(this,pName);

    #ifdef NDEBUG
    #else
        if( !macro_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return this;
    }

     
    MACRO_DATA *    macro_InitWithUTF8Con(
        MACRO_DATA      *this,
        const
        char            *pStrA
        )
    {
        NAME_DATA       *pName = OBJ_NIL;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pName = name_NewUTF8Con(pStrA);
        if (pName) {
            this = macro_Init( this, pName );
            if (OBJ_NIL == this) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            obj_Release(pName);
            pName = OBJ_NIL;
        }
        
        return this;
    }
    
    

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            macro_IsEnabled(
        MACRO_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !macro_Validate(this) ) {
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
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          macro_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MACRO_DATA      *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !macro_Validate(this) ) {
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
                        
#ifdef XYZZY
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return macro_Disable;
                        }
                        break;
                        
                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return macro_Enable;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return macro_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return macro_ToJSON;
                        }
                        break;
#endif
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     macro_ToDebugString(
        MACRO_DATA      *this,
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
                     "{%p(macro) side=%d ",
                     this,
                     macro_getSize(this)
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
        
        j = snprintf( str, sizeof(str), " %p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            macro_Validate(
        MACRO_DATA      *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this,OBJ_IDENT_MACRO) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(MACRO_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


