// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   srcLoc.c
 *	Generated 01/01/2016 08:01:11
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
#include "srcLoc_internal.h"
#include <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            srcLoc_task_body(
        void            *pData
    )
    {
        //SRCLOC_DATA  *cbp = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SRCLOC_DATA *     srcLoc_Alloc(
    )
    {
        SRCLOC_DATA     *cbp;
        uint32_t        cbSize = sizeof(SRCLOC_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    SRCLOC_DATA *     srcLoc_NewFLC(
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo
    )
    {
        SRCLOC_DATA       *cbp;
        
        cbp = srcLoc_Alloc( );
        if (cbp) {
            cbp = srcLoc_InitFLC( cbp, pFileName, lineNo, colNo );
        } 
        return( cbp );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        srcLoc_getColNo(
        SRCLOC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcLoc_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->colNo;
    }
    
    
    bool            srcLoc_setColNo(
        SRCLOC_DATA     *cbp,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !srcLoc_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        cbp->colNo = value;
        return true;
    }
    
    
    
    const char *    srcLoc_getFileName(
        SRCLOC_DATA      *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcLoc_Validate( cbp ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        return cbp->pFileName;
    }
    
    
    bool            srcLoc_setFileName(
        SRCLOC_DATA      *cbp,
        const
        char            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !srcLoc_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        cbp->pFileName = pValue;
        return true;
    }
    
    
    
    uint32_t        srcLoc_getLineNo(
        SRCLOC_DATA     *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcLoc_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->lineNo;
    }
    
    bool            srcLoc_setLineNo(
        SRCLOC_DATA     *cbp,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !srcLoc_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        cbp->lineNo = value;
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            srcLoc_Dealloc(
        OBJ_ID          objId
    )
    {
        SRCLOC_DATA     *cbp = objId;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !srcLoc_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            srcLoc_Disable(
        SRCLOC_DATA     *cbp
    )
    {

        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !srcLoc_Validate( cbp ) ) {
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

    bool            srcLoc_Enable(
        SRCLOC_DATA		*cbp
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !srcLoc_Validate( cbp ) ) {
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

    SRCLOC_DATA *   srcLoc_Init(
        SRCLOC_DATA       *cbp
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(cbp);
        cbp = (SRCLOC_DATA *)obj_Init( cbp, cbSize, OBJ_IDENT_SRCLOC );
        if (OBJ_NIL == cbp) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        //obj_setSize(cbp, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)cbp, OBJ_IDENT_SRCLOC);
        obj_setVtbl(cbp, &srcLoc_Vtbl);
        
        //cbp->stackSize = obj_getMisc1(cbp);
        //cbp->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !srcLoc_Validate( cbp ) ) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return cbp;
    }

     
    SRCLOC_DATA *   srcLoc_InitFLC(
        SRCLOC_DATA     *cbp,
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo
    )
    {
        
        cbp = srcLoc_Init(cbp);
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        srcLoc_setFileName(cbp, pFileName);
        srcLoc_setLineNo(cbp, lineNo);
        srcLoc_setColNo(cbp, colNo);
        
#ifdef NDEBUG
#else
        if( !srcLoc_Validate( cbp ) ) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
#endif
        
        return cbp;
    }
    
    

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            srcLoc_IsEnabled(
        SRCLOC_DATA		*cbp
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcLoc_Validate( cbp ) ) {
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
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     srcLoc_ToDebugString(
        SRCLOC_DATA      *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == cbp) {
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
                     "{%p(srcLoc) file=%s line=%d col=%d ",
                     cbp,
                     srcLoc_getFileName(cbp),
                     srcLoc_getLineNo(cbp),
                     srcLoc_getColNo(cbp)
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (cbp->pData) {
            if (((OBJ_DATA *)(cbp->pData))->pVtbl->toDebugString) {
                pWrkStr =   ((OBJ_DATA *)(cbp->pData))->pVtbl->toDebugString(
                                                    cbp->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf( str, sizeof(str), " %p}\n", cbp );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            srcLoc_Validate(
        SRCLOC_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_SRCLOC) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(SRCLOC_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


