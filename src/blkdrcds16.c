// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   BlkdRcds16.c
 *	Generated 12/22/2019 10:06:17
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
#include        <BlkdRcds16_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            BlkdRcds16_task_body (
        void            *pData
    )
    {
        //BLKDRCDS16_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BLKDRCDS16_DATA *     BlkdRcds16_Alloc (
        void
    )
    {
        BLKDRCDS16_DATA       *this;
        uint32_t        cbSize = sizeof(BLKDRCDS16_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    uint16_t        BlkdRcds16_CalcBlockSize(
        uint16_t        rsvdSize,
        uint16_t        numRecords,
        uint16_t        recordSize              // Average Record Size
    )
    {
        uint32_t        cbSize;
        uint32_t        dataSize;
        
        // Do initialization.
        dataSize  = recordSize + sizeof(INDEX_RECORD);
        dataSize *= numRecords;
        if (dataSize && (dataSize < 32768)) {
        }
        else {
            return 0;
        }
        
        cbSize  = sizeof(DATA_BLOCK);
        cbSize += rsvdSize;
        cbSize += dataSize;
        
        if( cbSize > 32768 ) {
            cbSize = 0;                 // TOO Big!
        }
        
        // Return to caller.
        return cbSize;
    }
    
    
    
    uint16_t        BlkdRcds16_CalcDataSize(
        uint16_t        blockSize,
        uint16_t        rsvdSize
    )
    {
        uint32_t        cbSize;
        
        // Do initialization.
        cbSize = sizeof(DATA_BLOCK) + rsvdSize;
        if (cbSize > 32768) {
            return 0;
        }
        if (blockSize < cbSize) {
            return 0;
        }
        
        cbSize  = blockSize;
        cbSize -= sizeof(DATA_BLOCK);
        cbSize -= rsvdSize;
        
        // Return to caller.
        return cbSize;
    }

    
    
    BLKDRCDS16_DATA *     BlkdRcds16_New (
        void
    )
    {
        BLKDRCDS16_DATA       *this;
        
        this = BlkdRcds16_Alloc( );
        if (this) {
            this = BlkdRcds16_Init(this);
        } 
        return this;
    }


    BLKDRCDS16_DATA * BlkdRcds16_NewWithSizes (
        uint16_t        blockSize,
        uint16_t        rsvdSize
    )
    {
        BLKDRCDS16_DATA *this;
        ERESULT         eRc;
        
        this = BlkdRcds16_New( );
        if (this) {
            eRc = BlkdRcds16_SetupDataBlock(this, blockSize, rsvdSize);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                return OBJ_NIL;
            }
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                       D a t a
    //---------------------------------------------------------------
    
    uint8_t *       BlkdRcds16_getData(
        BLKDRCDS16_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        return (uint8_t *)this->pBlock;
    }
    
    
    bool            BlkdRcds16_setData(
        BLKDRCDS16_DATA *this,
        uint8_t         *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pBlock = (DATA_BLOCK *)pValue;
        
        return true;
    }
    
        

    //---------------------------------------------------------------
    //                N u m b e r  o f  R e c o r d s
    //---------------------------------------------------------------
    
    uint16_t        BlkdRcds16_getNumRecords(
        BLKDRCDS16_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if (this->pBlock) {
        }
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->pBlock->numRecords;
    }
        
        
        
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        BlkdRcds16_getPriority (
        BLKDRCDS16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            BlkdRcds16_setPriority (
        BLKDRCDS16_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        BlkdRcds16_getSize (
        BLKDRCDS16_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * BlkdRcds16_getStr (
        BLKDRCDS16_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        BlkdRcds16_setStr (
        BLKDRCDS16_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_STR_OWNED
        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
#endif
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  BlkdRcds16_getSuperVtbl (
        BLKDRCDS16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                         U n u s e d
    //---------------------------------------------------------------
    
    uint16_t        BlkdRcds16_getUnused(
        BLKDRCDS16_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if (this->pBlock) {
        }
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->pBlock->unusedSize;
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
        ERESULT eRc = BlkdRcds16_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another BLKDRCDS16 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         BlkdRcds16_Assign (
        BLKDRCDS16_DATA		*this,
        BLKDRCDS16_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!BlkdRcds16_Validate(pOther)) {
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
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         BlkdRcds16_Compare (
        BLKDRCDS16_DATA     *this,
        BLKDRCDS16_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!BlkdRcds16_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        BlkdRcds16      *pCopy = BlkdRcds16_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BLKDRCDS16 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BLKDRCDS16_DATA *     BlkdRcds16_Copy (
        BLKDRCDS16_DATA       *this
    )
    {
        BLKDRCDS16_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = BlkdRcds16_New( );
        if (pOther) {
            eRc = BlkdRcds16_Assign(this, pOther);
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

    void            BlkdRcds16_Dealloc (
        OBJ_ID          objId
    )
    {
        BLKDRCDS16_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BLKDRCDS16_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        BlkdRcds16_setStr(this, OBJ_NIL);

        if (this->pBlock) {
            mem_Free(this->pBlock);
            this->pBlock = NULL;
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
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
    ERESULT         BlkdRcds16_Disable (
        BLKDRCDS16_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!BlkdRcds16_Validate(this)) {
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
    ERESULT         BlkdRcds16_Enable (
        BLKDRCDS16_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BLKDRCDS16_DATA *   BlkdRcds16_Init (
        BLKDRCDS16_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(BLKDRCDS16_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BLKDRCDS16);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&BlkdRcds16_Vtbl);
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

    #ifdef NDEBUG
    #else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "BlkdRcds16::sizeof(BLKDRCDS16_DATA) = %lu\n", sizeof(BLKDRCDS16_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BLKDRCDS16_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         BlkdRcds16_IsEnabled (
        BLKDRCDS16_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
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
    //                P a r s e  J s o n  O b j e c t
    //---------------------------------------------------------------
    
#ifdef  BLKDRCDS16_JSON_SUPPORT
     BLKDRCDS16_DATA * BlkdRcds16_ParseJsonObject (
         JSONIN_DATA     *pParser
    )
    {
        return OBJ_NIL;
    }
#endif
        
        
        
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
        void        *pMethod = BlkdRcds16_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "BlkdRcds16", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          BlkdRcds16_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        BLKDRCDS16_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BLKDRCDS16_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)BlkdRcds16_Class();
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
                            return BlkdRcds16_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return BlkdRcds16_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return BlkdRcds16_ToDebugString;
                        }
#ifdef  SRCREF_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return BlkdRcds16_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == BlkdRcds16_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == BlkdRcds16_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       R e c o r d  A d d
    //---------------------------------------------------------------
    
    ERESULT         BlkdRcds16_RecordAdd (
        BLKDRCDS16_DATA *this,
        uint16_t        rcdSize,
        void            *pData,
        uint16_t        *pIndex             // Optional Output Index
    )
    {
        uint16_t        offset = 0;
        uint8_t         *pBlockData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->pBlock) {
        }
        else {
            return ERESULT_GENERAL_FAILURE;
        }
        if ((rcdSize == 0) || (rcdSize >= 32768)) {
            return ERESULT_DATA_SIZE;
        }
        if ((rcdSize + sizeof(INDEX_RECORD)) > this->pBlock->unusedSize) {
            return ERESULT_DATA_TOO_BIG;
        }
#endif
        
        offset = sizeof(DATA_BLOCK);
        offset += (this->pBlock->numRecords * sizeof(INDEX_RECORD));
        offset += this->pBlock->unusedSize;
        offset -= rcdSize;
        pBlockData = (((uint8_t *)this->pBlock) + offset);
        memmove(pBlockData, pData, rcdSize);
        this->pBlock->unusedSize -= rcdSize + sizeof(INDEX_RECORD);
        this->pBlock->index[this->pBlock->numRecords].idxOffset = offset;
        this->pBlock->index[this->pBlock->numRecords].idxSize = rcdSize;
        ++this->pBlock->numRecords;
        
        // Return to caller.
        if (pIndex) {
            *pIndex = this->pBlock->numRecords;
        }
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                  R e c o r d  D e l e t e
    //---------------------------------------------------------------
    
    ERESULT         BlkdRcds16_RecordDelete (
        BLKDRCDS16_DATA    *this,
        uint16_t        index
    )
    {
        uint16_t        dataOffset;
        uint16_t        dataSize;
        uint16_t        numShiftRcds;
        uint16_t        shiftSize;
        uint8_t         *start;
        uint8_t         *shiftTo;
        int             i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->pBlock) {
        }
        else {
            return ERESULT_GENERAL_FAILURE;
        }
        if ((index == 0) || (index > this->pBlock->numRecords)) {
            return ERESULT_OUT_OF_RANGE;
        }
#endif
        
        dataOffset = this->pBlock->index[index-1].idxOffset;
        dataSize = this->pBlock->index[index-1].idxSize;
        numShiftRcds = this->pBlock->numRecords - index;
        
        if( numShiftRcds ) {
            // Shift the data.
            shiftSize = 0;
            for( i=0; i<numShiftRcds; ++i ) {
                shiftSize += this->pBlock->index[index+i].idxSize;
            }
            if( shiftSize ) {
                start = (uint8_t *)this->pBlock
                        + this->pBlock->index[this->pBlock->numRecords - 1].idxOffset;
                shiftTo = start + dataSize;
                memmove( shiftTo, start, shiftSize );
            }
            // Shift the index.
            shiftSize = sizeof(INDEX_RECORD) * numShiftRcds;
            if( shiftSize ) {
                start = (uint8_t *)&this->pBlock->index[index];
                shiftTo = (uint8_t *)&this->pBlock->index[index-1];
                memmove( shiftTo, start, shiftSize );
                // Adjust the index for new offsets.
                for( i=0; i<numShiftRcds; ++i ) {
                    this->pBlock->index[index-1+i].idxOffset += dataSize;
                }
            }
        }
        
        // Give the record space back.
        this->pBlock->unusedSize += (dataSize + sizeof(INDEX_RECORD));
        --this->pBlock->numRecords;
        this->pBlock->index[this->pBlock->numRecords].idxOffset = 0;
        this->pBlock->index[this->pBlock->numRecords].idxSize = 0;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                  R e c o r d  G e t
    //---------------------------------------------------------------
    
    ERESULT         BlkdRcds16_RecordGet (
        BLKDRCDS16_DATA    *this,
        uint16_t        index,
        uint16_t        dataSize,
        void            *pData,
        uint16_t        *pReturnedSize
    )
    {
        INDEX_RECORD    *pIndex;
        uint16_t        size;
        uint8_t         *pBlockData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->pBlock) {
        }
        else {
            return ERESULT_GENERAL_FAILURE;
        }
        if ((index == 0) || (index > this->pBlock->numRecords)) {
            return ERESULT_OUT_OF_RANGE;
        }
#endif
        
        pIndex = (INDEX_RECORD *)(&this->pBlock->index[index-1]);
        size = pIndex->idxSize;
        pBlockData = (((uint8_t *)this->pBlock) + pIndex->idxOffset);
        
        size = size < dataSize ? size : dataSize;
        if (pData && size) {
            memmove(pData, pBlockData, size);
        }
        
        // Return to caller.
        if (pReturnedSize) {
            *pReturnedSize = size;
        }
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                  R e c o r d  G e t  S i z e
    //---------------------------------------------------------------
    
    ERESULT         BlkdRcds16_RecordGetSize (
        BLKDRCDS16_DATA *this,
        uint16_t        index,
        uint16_t        *pSize
    )
    {
        INDEX_RECORD    *pIndex;
        uint16_t        size;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->pBlock) {
        }
        else {
            return ERESULT_GENERAL_FAILURE;
        }
        if ((index == 0) || (index > this->pBlock->numRecords)) {
            return ERESULT_OUT_OF_RANGE;
        }
#endif
        
        pIndex = (INDEX_RECORD *)(&this->pBlock->index[index-1]);
        size = pIndex->idxSize;
        
        // Return to caller.
        if (pSize) {
            *pSize = size;
        }
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                  R e c o r d  U p d a t e
    //---------------------------------------------------------------
    
    ERESULT         BlkdRcds16_RecordUpdate (
        BLKDRCDS16_DATA *this,
        uint16_t        index,
        uint16_t        dataSize,
        void            *pData
    )
    {
        INDEX_RECORD    *pIndex;
        uint16_t        dataShiftAmt = 0;
        uint16_t        dataShiftOff = 0;
        uint16_t        shiftFirstRcd;          // Relative to 1
        uint16_t        shiftLastRcd;           // Relative to 1
        uint8_t         *start;
        uint8_t         *shiftTo;
        int             i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BlkdRcds16_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->pBlock) {
        }
        else {
            return ERESULT_GENERAL_FAILURE;
        }
        if ((index == 0) || (index > this->pBlock->numRecords)) {
            return ERESULT_OUT_OF_RANGE;
        }
        if (dataSize > (this->pBlock->unusedSize + this->pBlock->index[index-1].idxSize)) {
            return ERESULT_DATA_TOO_BIG;
        }
#endif
        
        pIndex = (INDEX_RECORD *)(&this->pBlock->index[index-1]);
        shiftFirstRcd = index + 1;
        shiftLastRcd = this->pBlock->numRecords;
        
        if( dataSize == pIndex->idxSize )
            ;
        else {
            if (dataSize < pIndex->idxSize) {
                dataShiftOff = pIndex->idxSize - dataSize;
                if( (index < this->pBlock->numRecords) && dataShiftOff ) {
                    // Shift the data towards the end of the block closing the hole.
                    dataShiftAmt = 0;
                    for( i=shiftFirstRcd; i<=shiftLastRcd; ++i ) {
                        dataShiftAmt += this->pBlock->index[i-1].idxSize;
                    }
                    if( dataShiftAmt ) {
                        start = (uint8_t *)this->pBlock
                                + this->pBlock->index[shiftLastRcd-1].idxOffset;
                        shiftTo = start + dataShiftOff;
                        memmove( shiftTo, start, dataShiftAmt );
                    }
                    // Adjust the index for new offsets.
                    for( i=shiftFirstRcd; i<=shiftLastRcd; ++i ) {
                        this->pBlock->index[i-1].idxOffset += dataShiftOff;
                    }
                }
                pIndex->idxOffset += dataShiftOff;
            }
            else {
                dataShiftOff = dataSize - pIndex->idxSize;
                if( (index < this->pBlock->numRecords) && dataShiftOff ) {
                    // Shift the data towards the beginning of the block to make more room.
                    dataShiftAmt = 0;
                    for( i=shiftFirstRcd; i<=shiftLastRcd; ++i ) {
                        dataShiftAmt += this->pBlock->index[i-1].idxSize;
                    }
                    if( dataShiftAmt ) {
                        start = (uint8_t *)this->pBlock
                                + this->pBlock->index[shiftLastRcd-1].idxOffset;
                        shiftTo = start - dataShiftOff;
                        memmove( shiftTo, start, dataShiftAmt );
                    }
                    // Adjust the index for new offsets.
                    for( i=shiftFirstRcd; i<=shiftLastRcd; ++i ) {
                        this->pBlock->index[i-1].idxOffset -= dataShiftOff;
                    }
                }
                pIndex->idxOffset -= dataShiftOff;
            }
            this->pBlock->unusedSize += pIndex->idxSize;
            this->pBlock->unusedSize -= dataSize;
        }
        
        pIndex->idxSize = dataSize;
        start = (uint8_t *)this->pBlock + pIndex->idxOffset;
        memmove( start, pData, dataSize);
       
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
        
        
    //---------------------------------------------------------------
    //                  S e t u p  D a t a  B l o c k
    //---------------------------------------------------------------
    
    ERESULT         BlkdRcds16_SetupDataBlock (
        BLKDRCDS16_DATA *this,
        uint16_t        blockSize,
        uint16_t        rsvdSize
    )
    {
        uint16_t        minSize;
        
        #ifdef NDEBUG
        #else
                if (!BlkdRcds16_Validate(this)) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_OBJECT;
                }
        #endif
        
        if (this->pBlock) {
            mem_Free(this->pBlock);
            this->pBlock = NULL;
        }
        this->blockSize = blockSize;
        this->rsvdSize = rsvdSize;
        if (0 == blockSize) {
            return ERESULT_SUCCESS;
        }
        
        minSize = sizeof(DATA_BLOCK) + sizeof(INDEX_RECORD)
                + sizeof(DATA_BLOCK) + rsvdSize + 1;
        if ((blockSize < minSize) || (blockSize > 32768)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        
        this->pBlock = mem_Malloc(blockSize);
        if (this->pBlock) {
        }
        else {
            DEBUG_BREAK();
            obj_Release(this);
            return ERESULT_OUT_OF_MEMORY;
        }
        this->pBlock->cbSize = blockSize - sizeof(DATA_BLOCK);
        // Warning: The above limits the cbSize to less than 32768 which leaves
        //          the high order bit of cbSize available.
        this->pBlock->unusedSize = blockSize - sizeof(DATA_BLOCK) - rsvdSize;
        this->pBlock->rsvdSize = rsvdSize;
        this->pBlock->numRecords = 0;

        return ERESULT_SUCCESS;
    }

     

    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
#ifdef  BLKDRCDS16_JSON_SUPPORT
     ASTR_DATA *     BlkdRcds16_ToJson (
        BLKDRCDS16_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!BlkdRcds16_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{\"objectType\":\"%s\"",
                        pInfo->pClassName
                    );
            
            AStr_AppendA(pStr, "}\n");
        }
        
        return pStr;
    }
#endif
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BlkdRcds16_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     BlkdRcds16_ToDebugString (
        BLKDRCDS16_DATA      *this,
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
        if (!BlkdRcds16_Validate(this)) {
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
                    BlkdRcds16_getSize(this),
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
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            BlkdRcds16_Validate (
        BLKDRCDS16_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_BLKDRCDS16))
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


        if (!(obj_getSize(this) >= sizeof(BLKDRCDS16_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


