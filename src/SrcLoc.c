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
#include "SrcLoc_internal.h"
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

    /*! Allocate an area large enough for the object data and the
     srcloc data. Initialize the data pointer to within the area gotten.
     @return        A pointer to the combined data and  object if
                    successful or OBJ_NIL if not.
     */
    SRCLOC_DATA *     SrcLoc_Alloc(
    )
    {
        SRCLOC_DATA     *this;
        uint32_t        cbSize = sizeof(SRCLOC_DATA);
        
        // Do initialization.
        
        cbSize += ROUNDUP4(sizeof(SRCLOC));
        this = obj_Alloc( cbSize );
        this->pData = (SRCLOC *)((uint8_t *)this + sizeof(SRCLOC_DATA));
        
        // Return to caller.
        return this;
    }



    SRCLOC_DATA *     SrcLoc_NewFLC(
        uint32_t        fileIndex,              // File Index
        int64_t         offset,
        uint32_t        lineNo,
        uint16_t        colNo
    )
    {
        SRCLOC_DATA     *this;
        
        this = SrcLoc_Alloc( );
        if (this) {
            this = SrcLoc_InitFLC(this, fileIndex, offset, lineNo, colNo);
        } 
        return this;
    }


    SRCLOC_DATA *     SrcLoc_NewSrcLoc(
        SRCLOC          *pSrc
    )
    {
        SRCLOC_DATA     *this;
        
        this = SrcLoc_Alloc( );
        if (this) {
            this = SrcLoc_Init(this);
            if (this && pSrc) {
                memmove(this->pData, pSrc, sizeof(SRCLOC));
            }
        }
        return this;
    }
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          C o l  N o
    //---------------------------------------------------------------
    
    uint16_t        SrcLoc_getColNo(
        SRCLOC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pData->colNo;
    }
    
    
    bool            SrcLoc_setColNo(
        SRCLOC_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->pData->colNo = value;
        return true;
    }
    
    
    
    uint32_t        SrcLoc_getFileIndex(
        SRCLOC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->pData->fileIndex;
    }
    
    
    bool            SrcLoc_setFileIndex(
        SRCLOC_DATA     *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->pData->fileIndex = value;
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                         L i n e  N o
    //---------------------------------------------------------------
    
    uint32_t        SrcLoc_getLineNo(
        SRCLOC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pData->lineNo;
    }
    
    bool            SrcLoc_setLineNo(
        SRCLOC_DATA     *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->pData->lineNo = value;
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                         O f f s e t
    //---------------------------------------------------------------
    
    int64_t         SrcLoc_getOffset(
        SRCLOC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pData->offset;
    }
    
    bool            SrcLoc_setOffset(
        SRCLOC_DATA     *this,
        int64_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->pData->offset = value;
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S r c
    //---------------------------------------------------------------
    
    SRCLOC *        SrcLoc_getSrc(
        SRCLOC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pData;
    }
    
    
    bool            SrcLoc_setSrc(
        SRCLOC_DATA     *this,
        SRCLOC          *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->pData = pValue;
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       C o m p a r e
    //---------------------------------------------------------------
    
    int             SrcLoc_Compare(
        SRCLOC_DATA		*this,
        SRCLOC_DATA     *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if( !SrcLoc_Validate(pOther) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
#endif
        
        if( OBJ_NIL == pOther ) {
            DEBUG_BREAK();
            return 1;
        }
                
        if (this->pData->fileIndex == pOther->pData->fileIndex) {
            ;
        }
        else {
            return 1;
        }
        
        if (this->pData->lineNo == pOther->pData->lineNo) {
            ;
        }
        else {
            return 1;
        }
        
        if (this->pData->colNo == pOther->pData->colNo) {
            ;
        }
        else {
            return 1;
        }
        
        // Return to caller.
        return 0;
    }
    
    

    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            SrcLoc_Dealloc(
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
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        if (obj_Flag(this, SRCLOC_FLAG_ALLOC)) {
            mem_Free(this->pData);
            this->pData = NULL;
        }

        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SRCLOC_DATA *   SrcLoc_Init(
        SRCLOC_DATA     *this
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
        obj_setVtbl(this, &SrcLoc_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = ObjArray_New( );

    #ifdef NDEBUG
    #else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     
    SRCLOC_DATA *   SrcLoc_InitFLC(
        SRCLOC_DATA     *this,
        uint32_t        fileIndex,              // File Index
        int64_t         offset,
        uint32_t        lineNo,
        uint16_t        colNo
    )
    {
        
        this = SrcLoc_Init(this);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        SrcLoc_setFileIndex(this, fileIndex);
        SrcLoc_setOffset(this, offset);
        SrcLoc_setLineNo(this, lineNo);
        SrcLoc_setColNo(this, colNo);
        
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
#endif
        
        return this;
    }
    
    

    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          SrcLoc_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SRCLOC_DATA     *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
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
                            return SrcLoc_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return SrcLoc_ToJson;
                        }
                        break;
                        
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
    
    ASTR_DATA *     SrcLoc_ToDebugString(
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
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(srcLoc) fileIndex=%10d offset=%lld line=%d col=%d ",
                     this,
                     SrcLoc_getFileIndex(this),
                     SrcLoc_getOffset(this),
                     SrcLoc_getLineNo(this),
                     SrcLoc_getColNo(this)
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
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            SrcLoc_Validate(
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


