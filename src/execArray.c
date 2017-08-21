// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   execArray.c
 *	Generated 10/02/2015 13:17:50
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
#include "execArray_internal.h"
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

    EXECARRAY_DATA * execArray_Alloc(
    )
    {
        EXECARRAY_DATA  *cbp;
        uint32_t        cbSize = sizeof(EXECARRAY_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    EXECARRAY_DATA *     execArray_New(
    )
    {
        EXECARRAY_DATA       *cbp;
        
        cbp = execArray_Alloc( );
        if (cbp) {
            cbp = execArray_Init( cbp );
        } 
        return( cbp );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    OBJARRAY_DATA * execArray_getObjects(
        EXECARRAY_DATA     *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !execArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return cbp->pObjects;
    }
    
    
    bool            execArray_setObjects(
        EXECARRAY_DATA     *cbp,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !execArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pObjects) {
            obj_Release(cbp->pObjects);
        }
        cbp->pObjects = pValue;
        
        return true;
    }
    
    
    
    uint16_t        execArray_getPriority(
        EXECARRAY_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !execArray_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            execArray_setPriority(
        EXECARRAY_DATA     *cbp,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !execArray_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    uint32_t        execArray_getSize(
        EXECARRAY_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !execArray_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        return( 0 );
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                      A d d  M e t h o d
    //---------------------------------------------------------------

    ERESULT         execArray_AddMethod(
        EXECARRAY_DATA	*cbp,
        P_VOIDEXIT1_PTR pMethod,
        OBJ_ID          pObject         // May be OBJ_NIL
    )
    {
        ERESULT         eRc;
        uint32_t        mthIndex = 0;
        uint32_t        objIndex = 0;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !execArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        eRc = objArray_AppendObj(cbp->pObjects, pObject, &objIndex);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            eRc = ptrArray_AppendData(cbp->pMethods, pMethod, &mthIndex);
        }
#ifdef NDEBUG
#else
        if( !(objIndex == mthIndex) ) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
#endif

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------
    
    void            execArray_Dealloc(
        OBJ_ID          objId
    )
    {
        EXECARRAY_DATA   *cbp = objId;
        
        // Do initialization.
        if (NULL == cbp) {
            return;
        }
#ifdef NDEBUG
#else
        if( !execArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        if (cbp->pObjects) {
            obj_Release(cbp->pObjects);
            cbp->pObjects = OBJ_NIL;
        }
        
        if (cbp->pMethods) {
            obj_Release(cbp->pMethods);
            cbp->pMethods = OBJ_NIL;
        }
        
        obj_Dealloc( cbp );
        cbp = NULL;
        
        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //                       E x e c u t e
    //---------------------------------------------------------------

    ERESULT         execArray_Execute(
        EXECARRAY_DATA	*cbp
    )
    {
        uint16_t        i;
        uint16_t        iMax;
        void            *pPtr;
        P_VOIDEXIT1_PTR pMethod;
        OBJ_ID          pObject;
        

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !execArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
        iMax = objArray_getSize(cbp->pObjects);
        for (i=1; i<=iMax; ++i) {
            pMethod = ptrArray_GetData(cbp->pMethods, i);
            pObject = objArray_Get(cbp->pObjects, i);
            pPtr = pMethod(pObject);
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    EXECARRAY_DATA *   execArray_Init(
        EXECARRAY_DATA       *this
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (EXECARRAY_DATA *)obj_Init( this, cbSize, OBJ_IDENT_EXECARRAY );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(cbp, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)cbp, OBJ_IDENT_EXECARRAY);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&execArray_Vtbl);
        
        //this->stackSize = obj_getMisc1(cbp);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !execArray_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->pMethods);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     execArray_ToDebugString(
        EXECARRAY_DATA  *this,
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
                     "{%p(execArray) ",
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
        
        j = snprintf( str, sizeof(str), " %p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            execArray_Validate(
        EXECARRAY_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_EXECARRAY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(EXECARRAY_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


