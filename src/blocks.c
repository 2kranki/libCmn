// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   blocks32.c
 *	Generated 09/04/2016 13:13:56
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
#include <blocks_internal.h>
#include <enum_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    // Groups are always added to the end of the group list.
    BLOCKS_BLOCK *  blocks_AddBlock(
        BLOCKS_DATA     *this
    )
    {
        BLOCKS_BLOCK    *pBlock = NULL;
        
        pBlock = mem_Malloc(this->blockSize);
        if (pBlock) {
            pBlock->list.pNext = 0;
            pBlock->list.pPrev = 0;
            listdl_Add2Tail(&this->blocks, pBlock);
        }
        
        return pBlock;
    }



    
    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BLOCKS_DATA *   blocks_Alloc(
    )
    {
        BLOCKS_DATA     *this;
        uint32_t        cbSize = sizeof(BLOCKS_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BLOCKS_DATA *   blocks_New(
        uint32_t        blockSize
    )
    {
        BLOCKS_DATA   *this;
        
        this = blocks_Alloc( );
        if (this) {
            this = blocks_Init(this, blockSize);
        } 
        return this;
    }



    uint32_t        blocks_Available(
        uint32_t        blockSize       // If 0, use default size.
    )
    {
        uint32_t        avail = 0;
        
        if (blockSize == 0)
            blockSize = BLOCKS_BLOCK_SIZE;
        avail = blockSize - sizeof(BLOCKS_BLOCK);
        
        return avail;
    }
    
    
    


    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint32_t        blocks_getBlockAvail(
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        this->eRc = ERESULT_SUCCESS;
        return this->blockAvail;
    }
    
    
    
    uint32_t        blocks_getBlockSize(
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        this->eRc = ERESULT_SUCCESS;
        return this->blockSize;
    }
    
    
    
    ERESULT         blocks_getLastError(
        BLOCKS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        return this->eRc;
    }



    uint32_t        blocks_getSize(
        BLOCKS_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        this->eRc = ERESULT_SUCCESS;
        return this->cBlocks;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A d d
    //---------------------------------------------------------------
    
    void *          blocks_Add(
        BLOCKS_DATA     *this
    )
    {
        BLOCKS_BLOCK    *pBlock = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        pBlock = blocks_AddBlock(this);
        if (pBlock == NULL) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return NULL;
        }
        memset(pBlock->data, 0, this->blockAvail);
        ++this->cBlocks;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return pBlock->data;
    }
    
    
    
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = blocks__Assign(this,pOther);
     @endcode
     @param     this    BLOCKS object pointer
     @param     pOther  a pointer to another BLOCKS object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         blocks_Assign(
        BLOCKS_DATA		*this,
        BLOCKS_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( !blocks_Validate(pOther) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        //goto eom;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        this->eRc = ERESULT_NOT_IMPLEMENTED; // <-- Remove this!
    //eom:
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        blocks      *pCopy = blocks_Copy(this);
     @endcode
     @param     this    BLOCKS object pointer
     @return    If successful, a BLOCKS object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the BLOCKS object.
     */
    BLOCKS_DATA *   blocks_Copy(
        BLOCKS_DATA     *this
    )
    {
        BLOCKS_DATA     *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = blocks_New(this->blockSize);
        if (pOther) {
            eRc = blocks_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        this->eRc = ERESULT_SUCCESS;
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            blocks_Dealloc(
        OBJ_ID          objId
    )
    {
        BLOCKS_DATA     *this = objId;
        BLOCKS_BLOCK    *pBlock;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        while (listdl_Count(&this->blocks)) {
            pBlock = listdl_DeleteTail(&this->blocks);
            mem_Free(pBlock);
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //----------------------------------------------------------
    //                        E n u m
    //----------------------------------------------------------
    
    ERESULT         blocks_Enum(
        BLOCKS_DATA     *this,
        ENUM_DATA       **ppEnum
    )
    {
        ENUM_DATA       *pEnum = OBJ_NIL;
        //uint32_t        i;
        BLOCKS_BLOCK    *pBlock;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            if (ppEnum) {
                *ppEnum = pEnum;
            }
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEnum = enum_New( );
        if (pEnum) {
        }
        else {
            if (ppEnum) {
                *ppEnum = pEnum;
            }
            return ERESULT_OUT_OF_MEMORY;
        }
        
        pBlock = listdl_Head(&this->blocks);
        for (; pBlock; ) {
            enum_Append(pEnum, (void *)pBlock->data, NULL);
            pBlock = listdl_Next(&this->blocks, pBlock);
        }
        
        // Return to caller.
        if (ppEnum) {
            *ppEnum = pEnum;
        }
        return ERESULT_SUCCESS;
    }
    
    
    
    //----------------------------------------------------------
    //                        G e t
    //----------------------------------------------------------
    
    void *          blocks_Get(
        BLOCKS_DATA     *this,
        uint32_t        index
    )
    {
        //uint32_t        i;
        BLOCKS_BLOCK    *pBlock;
        uint32_t        count = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif
        
        pBlock = listdl_Head(&this->blocks);
        for (; pBlock; ) {
            ++count;
            if (count == index) {
                this->eRc = ERESULT_SUCCESS;
                return pBlock->data;
            }
            pBlock = listdl_Next(&this->blocks, pBlock);
        }
        
        // Return to caller.
        this->eRc = ERESULT_DATA_NOT_FOUND;
        return NULL;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BLOCKS_DATA *   blocks_Init(
        BLOCKS_DATA     *this,
        uint32_t        blockSize
    )
    {
        uint32_t        cbSize = sizeof(BLOCKS_DATA);
        
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BLOCKS);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_BLOCKS);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&blocks_Vtbl);
        
        if (blockSize == 0)
            blockSize = BLOCKS_BLOCK_SIZE;
        this->blockSize = blockSize;
        this->blockAvail = blocks_Available(blockSize);
        listdl_Init( &this->blocks,  offsetof(BLOCKS_BLOCK, list) );

    #ifdef NDEBUG
    #else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = blocks_ToDebugString(this,4);
     @endcode
     @param     this    BLOCKS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     blocks_ToDebugString(
        BLOCKS_DATA     *this,
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
                     "{%p(blocks)  cBlocks=%d\n",
                     this,
                     this->cBlocks
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
        
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(blocks)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            blocks_Validate(
        BLOCKS_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_BLOCKS) )
                ;
            else
                return false;
        }
        else
            return false;
        this->eRc = ERESULT_INVALID_OBJECT;
        if( !(obj_getSize(this) >= sizeof(BLOCKS_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


