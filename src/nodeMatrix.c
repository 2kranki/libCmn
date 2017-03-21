// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeMatrix.c
 *	Generated 08/31/2016 10:53:06
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
#include "nodeMatrix_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            nodeMatrix_task_body(
        void            *pData
    )
    {
        //NODEMATRIX_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODEMATRIX_DATA *     nodeMatrix_Alloc(
    )
    {
        NODEMATRIX_DATA *this;
        uint32_t        cbSize = sizeof(NODEMATRIX_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODEMATRIX_DATA * nodeMatrix_New(
        uint32_t        x,
        uint32_t        y
    )
    {
        NODEMATRIX_DATA *this;
        
        this = nodeMatrix_Alloc( );
        if (this) {
            this = nodeMatrix_Init(this,x,y);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    OBJMATRIX_DATA * nodeMatrix_getMatrix(
        NODEMATRIX_DATA *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pMatrix;
    }
    
    
    bool            nodeMatrix_setMatrix(
        NODEMATRIX_DATA  *this,
        OBJMATRIX_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pMatrix) {
            obj_Release(this->pMatrix);
        }
        this->pMatrix = pValue;
        
        return true;
    }
    
    
    
    uint16_t        nodeMatrix_getPriority(
        NODEMATRIX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            nodeMatrix_setPriority(
        NODEMATRIX_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    uint32_t        nodeMatrix_getX(
        NODEMATRIX_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !nodeMatrix_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return objMatrix_getX(this->pMatrix);
    }
    
    
    
    uint32_t        nodeMatrix_getY(
        NODEMATRIX_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !nodeMatrix_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return objMatrix_getY(this->pMatrix);
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         nodeMatrix_Assign(
        NODEMATRIX_DATA		*this,
        NODEMATRIX_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeMatrix_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        if (pOther->pMatrix) {
            obj_Release(pOther->pMatrix);
            pOther->pMatrix = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pMatrix) {
            if (obj_getVtbl(this->pMatrix)->pCopy) {
                pOther->pMatrix = obj_getVtbl(this->pMatrix)->pCopy(this->pMatrix);
            }
            else {
                obj_Retain(this->pMatrix);
                pOther->pMatrix = this->pMatrix;
            }
        }

        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    NODEMATRIX_DATA *     nodeMatrix_Copy(
        NODEMATRIX_DATA       *this
    )
    {
        NODEMATRIX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther =    nodeMatrix_New(
                        objMatrix_getX(this->pMatrix),
                        objMatrix_getY(this->pMatrix)
                    );
        if (pOther) {
            eRc = nodeMatrix_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            nodeMatrix_Dealloc(
        OBJ_ID          objId
    )
    {
        NODEMATRIX_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !nodeMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pMatrix) {
            obj_Release(this->pMatrix);
            this->pMatrix = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            nodeMatrix_Disable(
        NODEMATRIX_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !nodeMatrix_Validate(this) ) {
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

    bool            nodeMatrix_Enable(
        NODEMATRIX_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeMatrix_Validate(this) ) {
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
    //                          G e t
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeMatrix_Get(
        NODEMATRIX_DATA *this,
        uint32_t        x,
        uint32_t        y
    )
    {
        NODE_DATA       *pValue;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
      
        pValue = objMatrix_Get(this->pMatrix, x, y);
        
        // Return to caller.
        return pValue;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODEMATRIX_DATA * nodeMatrix_Init(
        NODEMATRIX_DATA *this,
        uint32_t        x,
        uint32_t        y
    )
    {
        uint32_t        cbSize = sizeof(NODEMATRIX_DATA);
        
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

        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODEMATRIX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_NODEMATRIX); // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeMatrix_Vtbl);
        
        this->pMatrix = objMatrix_New(x,y);
        if (OBJ_NIL == this->pMatrix) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if( !nodeMatrix_Validate(this) ) {
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
    
    bool            nodeMatrix_IsEnabled(
        NODEMATRIX_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeMatrix_Validate(this) ) {
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
    //                          S e t
    //---------------------------------------------------------------
    
    ERESULT         nodeMatrix_Set(
        NODEMATRIX_DATA *this,
        uint32_t        x,
        uint32_t        y,
        NODE_DATA       *pValue
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        eRc = objMatrix_Set(this->pMatrix, x, y, pValue);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     nodeMatrix_ToDebugString(
        NODEMATRIX_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        
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
                     "{%p(nodeMatrix) ",
                     this
            );
        AStr_AppendA(pStr, str);

        if (this->pMatrix) {
            if (((OBJ_DATA *)(this->pMatrix))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pMatrix))->pVtbl->pToDebugString(
                                                    this->pMatrix,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        
        j = snprintf(str, sizeof(str), " %p(nodeMatrix)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeMatrix_Validate(
        NODEMATRIX_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_NODEMATRIX) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(NODEMATRIX_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


