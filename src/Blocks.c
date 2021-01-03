// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Blocks.c
 *	Generated 01/10/2020 11:54:27
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
#include        <Blocks_internal.h>
#include        <enum_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    bool            Blocks_AddBlock (
        BLOCKS_DATA     *this
    )
    {
        BLOCKS_BLOCK    *pBlock;
        BLOCKS_NODE     *pNode;
        uint32_t        i;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
        }
        if (0 == this->blockSize) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (0 == listdl_Count(&this->freeList))
            ;
        else {
            return true;
        }

        // Get a new block.
        pBlock = (BLOCKS_BLOCK *)mem_Malloc( this->blockSize );
        if( NULL == pBlock ) {
            return false;
        }
        listdl_Add2Tail(&this->blocks, pBlock);
        ++this->cBlocks;

        // Now chain the entries to the Free chain.
        for (i=0; i<this->cRecordsPerBlock; ++i) {
            pNode = (BLOCKS_NODE *)((uint8_t *)&pBlock->data + (this->recordSize * i));
            listdl_Add2Tail(&this->freeList, pNode);
        }

        // Return to caller.
        return true;
    }



    ERESULT         Blocks_RecordFreeExit (
        BLOCKS_DATA     *this,
        void            *pRecord,
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //BLOCKS_NODE     *pNode = (BLOCKS_NODE *)((uint8_t *)pRecord - sizeof(BLOCKS_NODE));

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = Blocks_RecordFree(this, pRecord);

        // Return to caller.
        return eRc;
    }





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BLOCKS_DATA *     Blocks_Alloc (
        void
    )
    {
        BLOCKS_DATA       *this;
        uint32_t        cbSize = sizeof(BLOCKS_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BLOCKS_DATA *     Blocks_New (
        void
    )
    {
        BLOCKS_DATA       *this;
        
        this = Blocks_Alloc( );
        if (this) {
            this = Blocks_Init(this);
        } 
        return this;
    }



    BLOCKS_DATA *   Blocks_NewWithSizes (
        uint32_t        blockSize,
        uint32_t        recordSize
    )
    {
        BLOCKS_DATA     *this;
        ERESULT         eRc;

        this = Blocks_Alloc( );
        if (this) {
            this = Blocks_Init(this);
            if (this) {
                eRc = Blocks_SetupSizes(this, blockSize, recordSize);
                if (ERESULT_FAILED(eRc)) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    this = OBJ_NIL;
                }
            }
        }
        return this;
    }



    int32_t         Blocks_Available (
        uint32_t        blockSize       // If 0, use default size.
    )
    {
        int32_t         avail = 0;

        if (blockSize == 0) {
            blockSize = BLKS_BLOCK_SIZE;
        }
        avail = blockSize - sizeof(BLOCKS_BLOCK);

        return avail;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  B l o c k  A v a i l
    //---------------------------------------------------------------

    uint32_t        Blocks_getBlockAvail (
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->blockAvail;
    }



    uint32_t        Blocks_getBlockSize (
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->blockSize;
    }



    /*!
     * The delete exit is called whenever an active record is to be
     * freed allowing any clean up to be performed.
     */
    bool            Blocks_setDeleteExit (
        BLOCKS_DATA     *this,
        P_ERESULT_EXIT3 pDelete,
        OBJ_ID          pObj,           // Used as first parameter of scan method
        void            *pArg3          // Used as third parameter of scan method
    )
    {
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pDelete   = pDelete;
        this->pObj      = pObj;
        this->pArg3     = pArg3;

        return true;
    }


    LISTDL_DATA *   Blocks_getList (
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return &this->activeList;
    }



    uint32_t        Blocks_getNumActive (
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return listdl_Count(&this->activeList);
    }



    //---------------------------------------------------------------
    //                R e c o r d s  P e r  B l o c k
    //---------------------------------------------------------------

    uint32_t        Blocks_getRecordsPerBlock(
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->cRecordsPerBlock;
    }



    //---------------------------------------------------------------
    //                      R e c o r d  S i z e
    //---------------------------------------------------------------

    uint32_t        Blocks_getRecordSize(
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->recordSize;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Blocks_getSize (
        BLOCKS_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->cBlocks;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Blocks_getSuperVtbl (
        BLOCKS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                        U n i q u e
    //---------------------------------------------------------------

    uint32_t        Blocks_getUnique (
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->recordSize;
    }





    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = Blocks_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another BLOCKS object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Blocks_Assign (
        BLOCKS_DATA		*this,
        BLOCKS_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Blocks_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
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
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Blocks_Compare (
        BLOCKS_DATA     *this,
        BLOCKS_DATA     *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Blocks_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
#endif

        return iRc;
    }

   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Blocks      *pCopy = Blocks_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BLOCKS object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BLOCKS_DATA *     Blocks_Copy (
        BLOCKS_DATA       *this
    )
    {
        BLOCKS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Blocks_New( );
        if (pOther) {
            eRc = Blocks_Assign(this, pOther);
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

    void            Blocks_Dealloc (
        OBJ_ID          objId
    )
    {
        BLOCKS_DATA     *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BLOCKS_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        (void)Blocks_Reset(this);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //----------------------------------------------------------
    //           D e l e t e  A l l  R e c o r d s
    //----------------------------------------------------------

    ERESULT         Blocks_DeleteAllRecords(
        BLOCKS_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        BLOCKS_BLOCK    *pBlock;
        BLOCKS_NODE     *pNode;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Delete all the active records.
        for (;;) {
            pNode = listdl_Tail(&this->activeList);
            if (pNode) {
                eRc = Blocks_RecordFree(this, pNode->data);
            }
            else
                break;
        }

        // Delete all the blocks.
        while (listdl_Count(&this->blocks)) {
            pBlock = listdl_DeleteTail(&this->blocks);
            mem_Free(pBlock);
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Blocks_Disable (
        BLOCKS_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Blocks_Enable (
        BLOCKS_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //----------------------------------------------------------
    //                        E n u m
    //----------------------------------------------------------

    ERESULT         Blocks_Enum (
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
        if( !Blocks_Validate(this) ) {
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



    //---------------------------------------------------------------
    //                          F o r  E a c h
    //---------------------------------------------------------------

    ERESULT         Blocks_ForEach(
        BLOCKS_DATA     *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        BLOCKS_NODE     *pEntry = OBJ_NIL;
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pScan ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pEntry = listdl_Head(&this->activeList);
        while ( pEntry ) {
            eRc = pScan(pObj, pEntry->data, pArg3);
            if (ERESULT_HAS_FAILED(eRc)) {
                break;
            }
            pEntry = listdl_Next(&this->activeList, pEntry);
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BLOCKS_DATA *   Blocks_Init (
        BLOCKS_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(BLOCKS_DATA);
        //ERESULT         eRc;
        
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
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Blocks_Vtbl);
        
        listdl_Init(&this->blocks,  offsetof(BLOCKS_BLOCK, list));
        listdl_Init(&this->activeList, 0);
        listdl_Init(&this->freeList, 0);

    #ifdef NDEBUG
    #else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "Blocks::sizeof(BLOCKS_DATA) = %lu\n", sizeof(BLOCKS_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BLOCKS_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Blocks_IsEnabled (
        BLOCKS_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = Blocks_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Blocks", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Blocks_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        BLOCKS_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BLOCKS_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Blocks_Class();
                break;
                
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'S':
                    if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                        return &this->pSuperVtbl;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return Blocks_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Blocks_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Blocks_ToDebugString;
                        }
#ifdef  SRCREF_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Blocks_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Blocks_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == Blocks_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //----------------------------------------------------------
    //                  R e c o r d
    //----------------------------------------------------------

    ERESULT         Blocks_RecordFree(
        BLOCKS_DATA     *this,
        void            *pRecord
    )
    {
        BLOCKS_NODE     *pNode = (BLOCKS_NODE *)((uint8_t *)pRecord - sizeof(BLOCKS_NODE));
        bool            fRc;
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        fRc = listdl_Delete(&this->activeList, pNode);
        if (fRc) {
            if (this->pDelete) {
                eRc = this->pDelete(this->pObj, pRecord, this->pArg3);
            }
            listdl_Add2Head(&this->freeList, pNode);
        }
        else
            eRc = ERESULT_DATA_NOT_FOUND;

        // Return to caller.
        return eRc;
    }


    void *          Blocks_RecordGet(
        BLOCKS_DATA    *this,
        int32_t        index                    // (relative to 1)
    )
    {
        BLOCKS_NODE     *pNode;
        void            *pData = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        pNode = listdl_Index(&this->activeList, index);
        if (pNode) {
            pData = pNode->data;
        }

        // Return to caller.
        return pData;
    }



    void *          Blocks_RecordGetUnique(
        BLOCKS_DATA    *this,
        uint32_t       unique
    )
    {
        BLOCKS_NODE     *pNode = NULL;


        // Do initialization.
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        // Since we do not have an index for unique item numbers,
        // we do a sequential search of the active list for the
        // item.
        while ((pNode = listdl_Next(&this->activeList, pNode))) {
            if (pNode->unique == unique) {
                return pNode->data;
            }
        }

        // Return to caller.
        return NULL;
    }



    void *          Blocks_RecordNew(
        BLOCKS_DATA     *this,
        uint32_t        *pUnique
    )
    {
        bool            fRc;
        //uint32_t        i;
        BLOCKS_NODE     *pNode;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            //this->eRc = ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif

        if (0 == listdl_Count(&this->freeList)) {
            fRc = Blocks_AddBlock(this);
            if (!fRc)
                return NULL;
        }

        pNode = listdl_DeleteHead(&this->freeList);
        if (pNode) {
            memset(pNode->data, 0, (this->recordSize - sizeof(BLOCKS_NODE)));
            listdl_Add2Head(&this->activeList, pNode);
        }
        pNode->unique = ++this->unique;

        // Return to caller.
        if (pUnique) {
            *pUnique = pNode->unique;
        }
        return pNode->data;
    }



    //---------------------------------------------------------------
    //                      R e s e t
    //---------------------------------------------------------------

    /*!
     Reset this object to its beginning state.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Blocks_Reset (
        BLOCKS_DATA     *this
    )
    {
        ERESULT         eRc;
        BLOCKS_BLOCK    *pBlock;
        BLOCKS_NODE     *pNode;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Delete all the active records.
        for (;;) {
            pNode = listdl_Tail(&this->activeList);
            if (pNode) {
                eRc = Blocks_RecordFree(this, pNode->data);
            }
            else
                break;
        }

        // Delete all the blocks.
        while (listdl_Count(&this->blocks)) {
            pBlock = listdl_DeleteTail(&this->blocks);
            mem_Free(pBlock);
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //----------------------------------------------------------
    //                      S e t u p
    //----------------------------------------------------------

    ERESULT         Blocks_SetupSizes(
        BLOCKS_DATA     *this,
        uint32_t        blockSize,
        uint32_t        recordSize
    )
    {
        ERESULT         eRc;

        // Do initialization.
        if (blockSize == 0)
            blockSize = BLKS_BLOCK_SIZE;
#ifdef NDEBUG
#else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#ifdef XYZZY
        if (this->cBlocks) {
            DEBUG_BREAK();
            return ERESULT_DATA_ALREADY_EXISTS;
        }
#endif
        if (recordSize > 0)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (recordSize > (blockSize - sizeof(BLOCKS_BLOCK))) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = Blocks_Reset(this);

        this->blockSize = blockSize;
        this->blockAvail = blockSize - sizeof(BLOCKS_BLOCK);
        this->dataSize = recordSize;
        recordSize = recordSize + sizeof(BLOCKS_NODE);
        this->recordSize = ((recordSize + 4 - 1) >> 2) << 2;
        if (recordSize) {
            this->cRecordsPerBlock = this->blockAvail / recordSize;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Blocks_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Blocks_ToDebugString (
        BLOCKS_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Blocks_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    Blocks_getSize(this),
                    obj_getRetainCount(this)
            );

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
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                  U n i q u e  F r o m  D a t a
    //---------------------------------------------------------------

    uint32_t        Blocks_UniqueFromData(
        BLOCKS_DATA     *this,
        void            *pData
    )
    {
        //uint32_t        i;
        BLOCKS_NODE     *pNode;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Blocks_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        pNode = Ptr2Node(pData);

        // Return to caller.
        return pNode->unique;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            Blocks_Validate (
        BLOCKS_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_BLOCKS))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(BLOCKS_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


