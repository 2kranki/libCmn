// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   memFile.c
 *	Generated 01/13/2019 15:55:15
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
#include        <memFile_internal.h>
#include        <trace.h>






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

    MEMFILE_DATA *     memFile_Alloc (
        void
    )
    {
        MEMFILE_DATA       *this;
        uint32_t        cbSize = sizeof(MEMFILE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    MEMFILE_DATA *     memFile_New (
        void
    )
    {
        MEMFILE_DATA       *this;
        
        this = memFile_Alloc( );
        if (this) {
            this = memFile_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        memFile_getPriority (
        MEMFILE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            memFile_setPriority (
        MEMFILE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
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
    
    uint32_t        memFile_getSize (
        MEMFILE_DATA    *this
    )
    {
        uint32_t        size = -1;
        
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (obj_Flag(this, MEMFILE_FILE_OPEN)) {
            size = array_getSizeInBytes(this->pData);
        }
        
        return 0;
    }



    //---------------------------------------------------------------
    //                           P a t h
    //---------------------------------------------------------------
    
    PATH_DATA *     memFile_getPath (
        MEMFILE_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pPath;
    }
    
    
    bool        memFile_setPath (
        MEMFILE_DATA    *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_STR_OWNED
        obj_Retain(pValue);
        if (this->pPath) {
            obj_Release(this->pPath);
        }
#endif
        this->pPath = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  memFile_getSuperVtbl (
        MEMFILE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
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
        ERESULT eRc = memFile_Assign(this,pOther);
     @endcode 
     @param     this    MEMFILE object pointer
     @param     pOther  a pointer to another MEMFILE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         memFile_Assign (
        MEMFILE_DATA		*this,
        MEMFILE_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!memFile_Validate(pOther)) {
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
    //                          C l o s e
    //---------------------------------------------------------------
    
    ERESULT         memFile_Close (
        MEMFILE_DATA    *this,
        bool            fDelete
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        this->offset = 0;
        if (fDelete) {
            eRc = array_Truncate(this->pData, 0);
        }
        obj_FlagOff(this, MEMFILE_FILE_OPEN);
        
        // Return to caller.
        return ERESULT_SUCCESS;
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
    ERESULT         memFile_Compare (
        MEMFILE_DATA     *this,
        MEMFILE_DATA     *pOther
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
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!memFile_Validate(pOther)) {
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
        memFile      *pCopy = memFile_Copy(this);
     @endcode 
     @param     this    MEMFILE object pointer
     @return    If successful, a MEMFILE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    MEMFILE_DATA *     memFile_Copy (
        MEMFILE_DATA       *this
    )
    {
        MEMFILE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = memFile_New( );
        if (pOther) {
            eRc = memFile_Assign(this, pOther);
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
    //                          C r e a t e
    //---------------------------------------------------------------
    
    ERESULT         memFile_Create (
        MEMFILE_DATA    *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        memFile_setPath(this, OBJ_NIL);
        this->pPath = path_Copy(pPath);
        if (this->pPath) {
            path_Clean(this->pPath);
        }
        else {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        eRc = array_Truncate(this->pData, 0);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        this->offset = 0;
        obj_FlagOn(this, MEMFILE_FILE_OPEN);

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            memFile_Dealloc (
        OBJ_ID          objId
    )
    {
        MEMFILE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((MEMFILE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        memFile_setPath(this, OBJ_NIL);
        if (this->pData) {
            obj_Release(this->pData);
            this->pData = OBJ_NIL;
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
    ERESULT         memFile_Disable (
        MEMFILE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!memFile_Validate(this)) {
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
    ERESULT         memFile_Enable (
        MEMFILE_DATA	*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!memFile_Validate(this)) {
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
    //                         G e t s
    //---------------------------------------------------------------
    
    ERESULT         memFile_Gets (
        MEMFILE_DATA    *this,
        uint32_t        cBuffer,
        uint8_t         *pBuffer
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        //obj_Enable(this);
        
        // Put code here...
        
        // Return to caller.
        return ERESULT_NOT_IMPLEMENTED;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    MEMFILE_DATA *   memFile_Init (
        MEMFILE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(MEMFILE_DATA);
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

        //this = (OBJ_ID)blks_Init((BLKS_DATA *)this);        // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_MEMFILE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                          // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_MEMFILE);      // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&memFile_Vtbl);
        
        this->pData = array_NewWithSize(1);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "memFile::sizeof(MEMFILE_DATA) = %lu\n", sizeof(MEMFILE_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(MEMFILE_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                         O p e n
    //---------------------------------------------------------------
    
    ERESULT         memFile_Open (
        MEMFILE_DATA    *this,
        PATH_DATA       *pPath
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        memFile_setPath(this, OBJ_NIL);
        this->pPath = path_Copy(pPath);
        if (this->pPath) {
            path_Clean(this->pPath);
        }
        else {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        this->offset = 0;
        obj_FlagOn(this, MEMFILE_FILE_OPEN);

        // Return to caller.
        return ERESULT_SUCCESS;
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
        void        *pMethod = memFile_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "memFile", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          memFile_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MEMFILE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(MEMFILE_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)memFile_Class();
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
                            return memFile_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return memFile_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return memFile_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return memFile_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == memFile_ToDebugString)
                    return "ToDebugString";
                if (pData == memFile_ToJSON)
                    return "ToJson";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e a d
    //---------------------------------------------------------------
    
    ERESULT         memFile_Read(
        MEMFILE_DATA    *this,
        uint32_t        cBuffer,            // (in)
        void            *pBuffer,           // (in)
        uint32_t        *pReadCount         // (out)
    )
    {
        //ERESULT         eRc = ERESULT_INVALID_PARAMETER;
        uint8_t         *pData;
        uint32_t        sizeRead;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (0 == cBuffer) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == pBuffer) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        // Insure that we have the space for it.
        sizeRead = array_getSizeInBytes(this->pData);
        sizeRead -= this->offset;
        if (sizeRead > cBuffer) {
            sizeRead = cBuffer;
        }
        
        if (sizeRead > 0) {
            pData = array_GetAddrOf(this->pData, (uint32_t)this->offset+1);
            memmove(pBuffer, pData, sizeRead);
        }
        if (pReadCount) {
            *pReadCount = sizeRead;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //----------------------------------------------------------------
    //                          S e e k
    //----------------------------------------------------------------
    
    off_t           memFile_SeekBegin (
        MEMFILE_DATA    *this,
        off_t           offset
    )
    {
        off_t           fileOffset = -1;
        uint32_t        sizeFile;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        //  Position within the File.
        sizeFile = array_getSizeInBytes(this->pData);
        if (offset <= sizeFile) {
            this->offset = offset;
            fileOffset = offset;
        }
        
        // Return to Caller.
        return fileOffset;
    }
    
    
    off_t           memFile_SeekCur (
        MEMFILE_DATA    *this,
        off_t           offset
    )
    {
        off_t           fileOffset = -1;
        uint32_t        sizeFile;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        //  Position within the File.
        sizeFile = array_getSizeInBytes(this->pData);
        fileOffset = this->offset + offset;
        if (fileOffset > sizeFile)
            fileOffset = -1;
        else {
            this->offset = fileOffset;
        }
        
        // Return to Caller.
        return fileOffset;
    }
    
    
    off_t           memFile_SeekEnd (
        MEMFILE_DATA    *this,
        off_t           offset
    )
    {
        off_t           fileOffset = -1;
        uint32_t        sizeFile;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        //  Position within the File.
        sizeFile = array_getSizeInBytes(this->pData);
        fileOffset = sizeFile + offset;
        if (fileOffset > sizeFile)
            fileOffset = -1;
        else {
            this->offset = fileOffset;
        }

        // Return to Caller.
        return fileOffset;
    }
    
    
    
    //----------------------------------------------------------
    //                      S e t u p
    //----------------------------------------------------------
    
    ERESULT         memFile_SetupSizes(
        MEMFILE_DATA    *this,
        uint32_t        blockSize
    )
    {
        ERESULT         eRc = ERESULT_INVALID_PARAMETER;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (blockSize > 0)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        //eRc = blks_SetupSizes((BLKS_DATA *)this, blockSize);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S i z e
    //---------------------------------------------------------------
    
    size_t          memFile_Size (
        MEMFILE_DATA    *this
    )
    {
        size_t          fileSize = -1;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
        if (!obj_Flag(this, MEMFILE_FILE_OPEN)) {
            return -1;
        }
#endif
        
        fileSize = array_getSizeInBytes(this->pData);
        
        // Return to caller.
        return fileSize;
    }
    
    
    
    
    //----------------------------------------------------------------
    //                          T e l l
    //----------------------------------------------------------------
    
    off_t           memFile_Tell (
        MEMFILE_DATA    *this
    )
    {
        off_t           fileOffset = -1;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        //  Position within the File.
        //fileOffset = lseek(this->fileHandle, 0, SEEK_CUR);
        
        // Return to Caller.
        return fileOffset;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     memFile_ToJSON (
        MEMFILE_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
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
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = memFile_ToDebugString(this,4);
     @endcode 
     @param     this    MEMFILE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     memFile_ToDebugString (
        MEMFILE_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
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
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    memFile_getSize(this)
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
    bool            memFile_Validate (
        MEMFILE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_MEMFILE))
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


        if (!(obj_getSize(this) >= sizeof(MEMFILE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                      W r i t e
    //---------------------------------------------------------------
    
    ERESULT         memFile_Write(
        MEMFILE_DATA    *this,
        uint32_t        cBuffer,
        const
        void            *pBuffer
    )
    {
        ERESULT         eRc = ERESULT_INVALID_PARAMETER;
        uint8_t         *pData;
        int32_t         sizeNeeded;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (0 == cBuffer) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == pBuffer) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        // Insure that we have the space for it.
        sizeNeeded = array_getSizeInBytes(this->pData);
        sizeNeeded -= this->offset;
        sizeNeeded -= cBuffer;
        if ( sizeNeeded < 0) {
            sizeNeeded = -sizeNeeded;
            eRc = array_AppendSpacing(this->pData, sizeNeeded);
        }
        
        pData = array_GetAddrOf(this->pData, (uint32_t)this->offset+1);
        memmove(pData, pBuffer, cBuffer);

        // Return to caller.
        return eRc;
    }

    
    

    
#ifdef	__cplusplus
}
#endif


