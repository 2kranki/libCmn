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


    
    

    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SRCLOC_DATA *     srcLoc_Alloc(
    )
    {
        SRCLOC_DATA     *this;
        uint32_t        cbSize = sizeof(SRCLOC_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SRCLOC_DATA *     srcLoc_NewFLC(
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo
    )
    {
        SRCLOC_DATA     *this;
        
        this = srcLoc_Alloc( );
        if (this) {
            this = srcLoc_InitFLC(this, pFileName, lineNo, colNo);
        } 
        return this;
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
        SRCLOC_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !srcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->colNo = value;
        return true;
    }
    
    
    
    const char *    srcLoc_getFileName(
        SRCLOC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcLoc_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        return this->pFileName;
    }
    
    
    bool            srcLoc_setFileName(
        SRCLOC_DATA     *this,
        const
        char            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !srcLoc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->pFileName = pValue;
        return true;
    }
    
    
    
    uint32_t        srcLoc_getLineNo(
        SRCLOC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !srcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->lineNo;
    }
    
    bool            srcLoc_setLineNo(
        SRCLOC_DATA     *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !srcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->lineNo = value;
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       C o m p a r e
    //---------------------------------------------------------------
    
    ERESULT         srcLoc_Compare(
        SRCLOC_DATA		*this,
        SRCLOC_DATA     *pOther
    )
    {
        int             iRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcLoc_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !srcLoc_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if ((NULL == this->pFileName) && (NULL == pOther->pFileName)) {
        }
        else if ((NULL == this->pFileName) && pOther->pFileName) {
            return ERESULT_SUCCESS_LESS_THAN;
        }
        else if (this->pFileName && (NULL == pOther->pFileName)) {
            return ERESULT_SUCCESS_GREATER_THAN;
        }
        else {
            iRc = strcmp(this->pFileName, pOther->pFileName);
            if (iRc < 0) {
                return ERESULT_SUCCESS_LESS_THAN;
            }
            if (iRc > 0) {
                return ERESULT_SUCCESS_GREATER_THAN;
            }
        }
        if( OBJ_NIL == pOther ) {
            DEBUG_BREAK();
            return ERESULT_SUCCESS_GREATER_THAN;
        }
                
        if (this->lineNo < pOther->lineNo) {
            return ERESULT_SUCCESS_LESS_THAN;
        }
        if (this->lineNo > pOther->lineNo) {
            return ERESULT_SUCCESS_GREATER_THAN;
        }

        if (this->colNo < pOther->colNo) {
            return ERESULT_SUCCESS_LESS_THAN;
        }
        if (this->colNo > pOther->colNo) {
            return ERESULT_SUCCESS_GREATER_THAN;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_EQUAL;
    }
    
    

    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            srcLoc_Dealloc(
        OBJ_ID          objId
    )
    {
        SRCLOC_DATA     *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !srcLoc_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            srcLoc_Disable(
        SRCLOC_DATA     *this
    )
    {

        // Do initialization.
        if (NULL == this) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !srcLoc_Validate(this) ) {
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

    bool            srcLoc_Enable(
        SRCLOC_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !srcLoc_Validate(this) ) {
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

    SRCLOC_DATA *   srcLoc_Init(
        SRCLOC_DATA       *this
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (SRCLOC_DATA *)obj_Init(this, cbSize, OBJ_IDENT_SRCLOC);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_SRCLOC);
        obj_setVtbl(this, &srcLoc_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !srcLoc_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     
    SRCLOC_DATA *   srcLoc_InitFLC(
        SRCLOC_DATA     *this,
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo
    )
    {
        
        this = srcLoc_Init(this);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        srcLoc_setFileName(this, pFileName);
        srcLoc_setLineNo(this, lineNo);
        srcLoc_setColNo(this, colNo);
        
#ifdef NDEBUG
#else
        if( !srcLoc_Validate(this) ) {
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
    
    bool            srcLoc_IsEnabled(
        SRCLOC_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcLoc_Validate(this) ) {
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
    
    void *          srcLoc_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    )
    {
        SRCLOC_DATA     *this = objId;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !srcLoc_Validate(this) ) {
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
                            return srcLoc_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return srcLoc_ToJSON;
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
    
    ASTR_DATA *     srcLoc_ToDebugString(
        SRCLOC_DATA     *this,
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
                     "{%p(srcLoc) file=%s line=%d col=%d ",
                     this,
                     srcLoc_getFileName(this),
                     srcLoc_getLineNo(this),
                     srcLoc_getColNo(this)
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
        
        j = snprintf(str, sizeof(str), " %p}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    ASTR_DATA *     srcLoc_ToJSON(
        SRCLOC_DATA     *this
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !srcLoc_Validate(this) ) {
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
                 "{\"objectType\":\"%s\",\"FileName\":\"%s\",\"LineNo\":%d,\"ColNo\":%d",
                 pInfo->pClassName,
                 (this->pFileName ? this->pFileName : ""),
                 this->lineNo,
                 this->colNo
            );
        AStr_AppendA(pStr, str);
        
        AStr_AppendA(pStr, "}\n");
        //BREAK_TRUE(AStr_getLength(pStr) > 2048);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            srcLoc_Validate(
        SRCLOC_DATA      *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_SRCLOC) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(SRCLOC_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


