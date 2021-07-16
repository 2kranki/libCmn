// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   block16.c
 *	Generated 01/05/2016 07:38:50
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
#include <block16_internal.h>
#include <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            block16_task_body(
        void            *pData
    )
    {
        //BLOCK_DATA  *cbp = pData;
        
    }
#endif



    // An offset of zero should never occur. So, it denotes an error.
    static
    uint32_t        block16_DataOffset(
        BLOCK16_DATA    *this
    )
    {
        uint32_t        offset = 0;
        
        if (this->pBlock) {
            offset  = ROUNDUP4(sizeof(BLOCKED16_DATA));
            offset += this->pBlock->headerSize;
            offset += this->pBlock->dataUsed;
        }
        return offset;
    }
    
    
    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BLOCK16_DATA *   block16_Alloc(
    )
    {
        BLOCK16_DATA    *this;
        uint32_t        cbSize = sizeof(BLOCK16_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    // Given the data size, block16_blockSize returns the size of
    // the block that will be acquired.
    uint32_t		block16_CalcBlockSize(
        uint16_t        headerSize,
        uint16_t        dataSize
    )
    {
        uint32_t        cbSize;
        
        // Do initialization.
        cbSize = ROUNDUP4(sizeof(BLOCKED16_DATA));
        if (headerSize) {
            cbSize += ROUNDUP4(headerSize);
        }
        if (dataSize) {
            cbSize += ROUNDUP4(dataSize);
        }
        else {
            return 0;
        }
        
        // Return to caller.
        return( cbSize );
    }
    
    
    
    BLOCK16_DATA *   block16_New(
    )
    {
        BLOCK16_DATA    *this;
        
        this = block16_Alloc( );
        if (this) {
            this = block16_Init(this);
        } 
        return this;
    }



    BLOCK16_DATA *   block16_NewWithSizes(
        uint16_t        headerSize,
        uint16_t        dataSize
    )
    {
        BLOCK16_DATA    *this;
        
        this = block16_Alloc( );
        if (this) {
            this = block16_InitWithSizes(this, headerSize, dataSize);
        }
        return this;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    void *          block16_getBlock(
        BLOCK16_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !block16_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pBlock;
    }
    
    
    bool            block16_setBlock(
        BLOCK16_DATA    *this,
        void            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !block16_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (this->pBlock) {
            mem_Free(this->pBlock);
        }
        this->pBlock = pValue;
        
        return true;
    }
    
    
    
    void *          block16_getData(
        BLOCK16_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !block16_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NULL(this->pBlock);
#endif
        
        return &this->pBlock->header[this->pBlock->headerSize];
    }
    
    

    uint16_t        block16_getDataOffset(
        BLOCK16_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !block16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        BREAK_NULL(this->pBlock);
#endif
        
        return this->pBlock->headerSize;
    }
    

    
    uint16_t        block16_getDataSize(
        BLOCK16_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !block16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        BREAK_NULL(this->pBlock);
#endif
        
        return this->pBlock->dataSize;
    }
    

    
    uint16_t        block16_getDataUsed(
        BLOCK16_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !block16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        BREAK_NULL(this->pBlock);
#endif
        
        return this->pBlock->dataUsed;
    }
    
    
    bool            block16_setDataUsed(
        BLOCK16_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !block16_Validate(this) ) {
            DEBUG_BREAK();
        }
        BREAK_NULL(this->pBlock);
#endif
        
        this->pBlock->dataUsed = value;
        
        return true;
    }
    
    
    
    void *          block16_getHeader(
        BLOCK16_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !block16_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NULL(this->pBlock);
#endif
        
        return &this->pBlock->header[0];
    }
    
    
    
    uint16_t        block16_getHeaderSize(
        BLOCK16_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !block16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        BREAK_NULL(this->pBlock);
#endif

        return this->pBlock->headerSize;
    }

    
    bool            block16_setHeaderSize(
        BLOCK16_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !block16_Validate(this) ) {
            DEBUG_BREAK();
        }
        BREAK_NULL(this->pBlock);
#endif
        
        this->pBlock->headerSize = value;
        
        return true;
    }



    ERESULT         block16_getLastError(
        BLOCK16_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !block16_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        return this->eRc;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //----------------------------------------------------------
    //                    A d d D a t a
    //----------------------------------------------------------
    
    bool			block16_AddData(
        BLOCK16_DATA	*this,
        uint16_t        dataSize,
        void            *pData
    )
    {
        void            *pBlockData;
        
        /* Validate the input parameters.
         */
#ifdef NDEBUG
#else
        if( !block16_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if( dataSize > (this->pBlock->dataSize - this->pBlock->dataUsed) )
            return false;
#endif
        
        pBlockData = (uint8_t *)(this->pBlock) + block16_DataOffset(this);
        if (pBlockData == NULL) {
            return false;
        }
        memmove(pBlockData, pData, dataSize);
        this->pBlock->dataUsed += dataSize;
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            block16_Dealloc(
        OBJ_ID          objId
    )
    {
        BLOCK16_DATA    *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !block16_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pBlock) {
            mem_Free(this->pBlock);
            this->pBlock = NULL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D a t a  P t r
    //---------------------------------------------------------------

    void *          block16_DataPtr(
        BLOCK16_DATA    *this
    )
    {
        void            *pData = NULL;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !block16_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        BREAK_NULL(this->pBlock);
    #endif
        
        pData = (void *)&this->pBlock->header[this->pBlock->headerSize];
        
        // Return to caller.
        return pData;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BLOCK16_DATA *  block16_Init(
        BLOCK16_DATA    *this
    )
    {
        uint32_t        cbSize = sizeof(BLOCK16_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (BLOCK16_DATA *)obj_Init( this, cbSize, OBJ_IDENT_BLOCK32 );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            //obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_BLOCK32);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&block16_Vtbl);
        
    #ifdef NDEBUG
    #else
        if( !block16_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->pBlock);
    #endif

        return this;
    }

     

    BLOCK16_DATA *  block16_InitWithSizes(
        BLOCK16_DATA    *this,
        uint16_t        headerSize,
        uint16_t        dataSize
    )
    {
        uint32_t        cbBlock;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (0 == dataSize) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = block16_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            //obj_Release(this);
            return OBJ_NIL;
        }
        
        cbBlock = block16_CalcBlockSize(headerSize, dataSize);
        if (0 == cbBlock) {
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pBlock = mem_Calloc(1, cbBlock);
        if (NULL == this->pBlock) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pBlock->cbSize = cbBlock;
        this->pBlock->headerSize = ROUNDUP_WORD(headerSize);
        this->pBlock->dataSize = ROUNDUP_WORD(dataSize);
        
        return this;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     block16_ToDebugString(
        BLOCK16_DATA    *this,
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
                     "{%p(block16) ",
                     this
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
        
        j = snprintf( str, sizeof(str), " (block16)%p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            block16_Validate(
        BLOCK16_DATA    *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_BLOCK16) )
                ;
            else
                return false;
        }
        else
            return false;
        this->eRc = ERESULT_INVALID_OBJECT;
        if( !(obj_getSize(this) >= sizeof(BLOCK16_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


