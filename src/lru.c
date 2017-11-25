// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   lru.c
 *	Generated 10/21/2016 23:23:20
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
#include "lru_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /*!
     *  Search the lsn hash table for the sector. 
     *  @return     If found, move it to the head of the LRU list 
     *              and return it.  Otherwise, return NULL.
     */
    static
    LRU_SECTOR *    lru_FindLSN(
        LRU_DATA        *this,
        uint32_t        lsn
    )
    {
        uint32_t        hash = lsn % NUM_HASH_LIST;
        LRU_SECTOR      *pSector = NULL;
        
        while ((pSector = listdl_Next(&this->hashLists[hash], pSector))) {
            if (pSector->lsn == lsn) {
                break;
            }
        }
        if (pSector) {
            listdl_Move2Head(&this->lruList, pSector);
        }
        
        return pSector;
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LRU_DATA *      lru_Alloc(
    )
    {
        LRU_DATA       *this;
        uint32_t        cbSize = sizeof(LRU_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    LRU_DATA *      lru_New(
        uint32_t        sectorSize,
        uint32_t        cacheSize
    )
    {
        LRU_DATA       *this;
        
        this = lru_Alloc( );
        if (this) {
            this = lru_Init(this, sectorSize, cacheSize);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         lru_getLastError(
        LRU_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !lru_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }



    uint16_t        lru_getPriority(
        LRU_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !lru_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        this->eRc = ERESULT_SUCCESS;
        //return this->priority;
        return 0;
    }

    bool            lru_setPriority(
        LRU_DATA        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !lru_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        this->eRc = ERESULT_SUCCESS;
        return true;
    }



    bool            lru_setLogicalSectorRead(
        LRU_DATA        *this,
        ERESULT         (*pLogicalRead)(
            OBJ_ID          pReadObject,
            uint32_t        lsn,                // Logical Sector Number
            uint8_t         *pBuffer            // Buffer of sectorSize bytes
        ),
        OBJ_ID          pReadObject
    )
    {
#ifdef NDEBUG
#else
        if( !lru_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pLogicalRead = pLogicalRead;
        this->pReadObject = pReadObject;
        
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    
    
    
    uint32_t        lru_getSize(
        LRU_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !lru_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        this->eRc = ERESULT_SUCCESS;
        return 0;
    }



    bool            lru_setLogicalSectorWrite(
        LRU_DATA        *this,
        ERESULT         (*pLogicalWrite)(
            OBJ_ID          pWriteObject,
            uint32_t        lsn,                // Logical Sector Number
            uint8_t         *pBuffer            // Buffer of sectorSize bytes
        ),
        OBJ_ID          pWriteObject
    )
    {
#ifdef NDEBUG
#else
        if( !lru_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pLogicalWrite = pLogicalWrite;
        this->pWriteObject = pWriteObject;
        
        this->eRc = ERESULT_SUCCESS;
        return true;
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
        ERESULT eRc = lru__Assign(this,pOther);
     @endcode
     @param     this    LRU object pointer
     @param     pOther  a pointer to another LRU object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         lru_Assign(
        LRU_DATA		*this,
        LRU_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lru_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( !lru_Validate(pOther) ) {
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
        lru      *pCopy = lru_Copy(this);
     @endcode
     @param     this    LRU object pointer
     @return    If successful, a LRU object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the LRU object.
     */
    LRU_DATA *     lru_Copy(
        LRU_DATA       *this
    )
    {
        LRU_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lru_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = lru_New( this->sectorSize, this->cacheSize );
        if (pOther) {
            eRc = lru_Assign(this, pOther);
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

    void            lru_Dealloc(
        OBJ_ID          objId
    )
    {
        LRU_DATA        *this = objId;
        LRU_SECTOR      *pSector = NULL;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !lru_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((LRU_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif
        
        // Free the sectors.
        while ((pSector = (LRU_SECTOR *)listdl_DeleteHead(&this->freeList))) {
            mem_Free(pSector);
        }
        while ((pSector = (LRU_SECTOR *)listdl_DeleteHead(&this->lruList))) {
            mem_Free(pSector);
        }

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         lru_Disable(
        LRU_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return this->eRc;
        }
    #ifdef NDEBUG
    #else
        if( !lru_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         lru_Enable(
        LRU_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !lru_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    LRU_DATA *      lru_Init(
        LRU_DATA        *this,
        uint32_t        sectorSize,
        uint32_t        cacheSize
    )
    {
        uint32_t        cbSize = sizeof(LRU_DATA);
        uint32_t        i;
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_LRU);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_LRU);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&lru_Vtbl);
        
        listdl_Init(&this->freeList, offsetof(LRU_SECTOR, lruList));
        listdl_Init(&this->lruList, offsetof(LRU_SECTOR, lruList));
        for (i=0; i<NUM_HASH_LIST; ++i) {
            listdl_Init(&this->hashLists[i], offsetof(LRU_SECTOR, hashList));
        }
        this->sectorSize = sectorSize;
        this->cacheSize = cacheSize;
        for (i=0; i<cacheSize; ++i) {
            LRU_SECTOR          *pSector;
            pSector = mem_Calloc(1, (sizeof(LRU_SECTOR) + sectorSize));
            if (pSector) {
                listdl_Add2Head(&this->freeList, pSector);
            }
            else {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
        }

    #ifdef NDEBUG
    #else
        if( !lru_Validate(this) ) {
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
    
    void *          lru_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        LRU_DATA        *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !lru_Validate(this) ) {
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
                            return lru_ToDebugString;
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
    //                          R e a d
    //---------------------------------------------------------------
    
    ERESULT         lru_Read(
        LRU_DATA        *this,
        uint32_t        lsn,
        uint8_t         *pBuffer
    )
    {
        LRU_SECTOR      *pSector = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lru_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if (pBuffer == NULL) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
#endif
        
        // Use sector if already in LRU Cache.
        pSector = lru_FindLSN(this, lsn);
        if (pSector) {
            memmove(pBuffer, pSector->data, this->sectorSize);
            this->eRc = ERESULT_SUCCESS;
            return this->eRc;
        }
        
        // Get a sector to use.
        if (listdl_Count(&this->freeList)) {
            pSector = listdl_DeleteHead(&this->freeList);
        }
        else {
            pSector = listdl_DeleteTail(&this->lruList);
            listdl_Delete(&this->hashLists[pSector->lsn % NUM_HASH_LIST], pSector);
        }
        
        // Set up the sector.
        this->eRc = this->pLogicalRead(this->pReadObject, lsn, pSector->data);
        if (ERESULT_FAILED(this->eRc)) {
            DEBUG_BREAK();
            listdl_Add2Head(&this->freeList, pSector);
            return this->eRc;
        }
        pSector->lsn = lsn;
        memmove(pBuffer, pSector->data, this->sectorSize);
        
        listdl_Add2Head(&this->lruList, pSector);
        listdl_Add2Head(&this->hashLists[lsn % NUM_HASH_LIST], pSector);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = lru_ToDebugString(this,4);
     @endcode
     @param     this    LRU object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     lru_ToDebugString(
        LRU_DATA        *this,
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
                     "{%p(lru) size=%d\n",
                     this,
                     this->cacheSize
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
        j = snprintf(str, sizeof(str), " %p(lru)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            lru_Validate(
        LRU_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_LRU) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(LRU_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                          W r i t e
    //---------------------------------------------------------------
    
    ERESULT         lru_Write(
        LRU_DATA        *this,
        uint32_t        lsn,
        uint8_t         *pBuffer
    )
    {
        LRU_SECTOR      *pSector = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lru_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if (pBuffer == NULL) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
#endif
        
        // Use sector if already in LRU Cache.
        pSector = lru_FindLSN(this, lsn);
        if (pSector) {
            memmove(pSector->data, pBuffer, this->sectorSize);
            this->eRc = ERESULT_SUCCESS;
            return this->eRc;
        }
        else {
            // Get a sector to use.
            if (listdl_Count(&this->freeList)) {
                pSector = listdl_DeleteHead(&this->freeList);
            }
            else {
                pSector = listdl_DeleteTail(&this->lruList);
                listdl_Delete(&this->hashLists[pSector->lsn % NUM_HASH_LIST], pSector);
            }
            // Chain it to the lru and hash lists.
            listdl_Add2Head(&this->lruList, pSector);
            listdl_Add2Head(&this->hashLists[lsn % NUM_HASH_LIST], pSector);
        }
        
        // Set up the sector and write it out.
        pSector->lsn = lsn;
        memmove(pSector->data, pBuffer, this->sectorSize);
        this->eRc = this->pLogicalWrite(this->pReadObject, lsn, pBuffer);
        if (ERESULT_FAILED(this->eRc)) {
            DEBUG_BREAK();
            listdl_Add2Head(&this->freeList, pSector);
            return this->eRc;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


