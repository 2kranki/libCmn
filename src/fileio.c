// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   fileio.c
 *	Generated 07/30/2016 20:56:36
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
#include    <fileio_internal.h>
#include    <fcntl.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /* Local function declarations
     */
#ifdef NOT_NEEDED_YET
    static
    bool            fileio_FileDelete (
        const
        char            *pFileName
    );
#endif
    
    
#ifdef NOT_NEEDED_YET
    static
    bool            fileio_FileExtend (
        FILEIO_DATA      *this,
        uint32_t         Block           /* Block to extend to */
    );
#endif

    
    
    
    
    
    //----------------------------------------------------------------
    //           fileio_FileCreate - Create and Open a File
    //----------------------------------------------------------------
    /* Purpose
     *      This function creates a new file over-writing an existing
     *      one if present.
     * Returns
     *          RRDS_OK          =   Successful Completion
     *          RRDS_ERROR_OPEN  =   Disk File Open Error
     */
#ifdef NOT_NEEDED_YET
    static
    int             fileio_FileCreate (
        const
        char            *pFilePath
    )
    {
        int             fileHandle;
        
        //  Open the File.
        fileHandle = open(pFilePath, (O_CREAT | O_TRUNC | O_RDWR), 0644);
        if(-1 == fileHandle) {
            return -1;
        }
        
        // Return to Caller.
        return fileHandle;
    }
#endif
    
    
    
    //----------------------------------------------------------------
    //               fileio_FileDelete - Delete a File
    //----------------------------------------------------------------
    /* Purpose
     *          This function deletes a File.
     * Returns
     *          RRDS_OK              =   Successful Completion
     *          RRDS_ERROR_DELETE    =   Disk File Deletion Error
     */
#ifdef NOT_NEEDED_YET
    static
    bool            fileio_FileDelete (
        const
        char            *pFileName
    )
    {
        int             iRc;
        
        //  Delete the File.
        iRc = unlink(pFileName);
        if(iRc == 0)
            ;
        else
            return false;
        
        // Return to Caller.
        return true;
    }
#endif
    
    
    
    //----------------------------------------------------------------
    //      fileio_FileExtend - Extend the File with Zeroed Records
    //----------------------------------------------------------------
    /* Purpose
     *          This function writes zero-filled records into the File.
     * Returns
     *          RRDS_OK          =   Successful Completion
     *          RRDS_ERROR_NOMEM =   Memory Allocation Error
     *          RRDS_ERROR_SEEK  =   Disk Seek Error
     *          RRDS_ERROR_WRITE =   Disk Write Error
     */
#ifdef NOT_NEEDED_YET
    static
    bool            fileio_FileExtend (
        FILEIO_DATA     *this,
        uint32_t        recordNum           /* Record to extend to */
    )
    {
#ifdef  XYZZY
        uint32_t        curRec;
        size_t          fileOffset;
        char            *pFillData;
        bool            fRc;
        
        // Fill the File until Block number of records exist.
        if( recordNum > this->recordNum ) {
            
            pFillData = (char *)mem_Malloc(this->recordSize);
            if( NULL == pFillData ) {
                return false;
            }
            memset(pFillData, this->header.data.fillChar, this->recordSize);
            
            for( curRec=this->recordNum+1; curRec<=recordNum; ++curRec ) {
                fileOffset = rrds32_RecordOffset(this, curRec);
                fRc = rrds32_FileWrite( this->fileHandle,
                                       fileOffset,
                                       this->recordSize,
                                       pFillData
                                       );
                if( !fRc ) {
                    mem_Free(pFillData);
                    return false;
                }
            }
            mem_Free(pFillData);
            pFillData = NULL;
            this->recordNum = recordNum;
        }
#endif
        
        // Return to Caller.
        return true;
    }
#endif
    
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    FILEIO_DATA *   fileio_Alloc (
    )
    {
        FILEIO_DATA     *this;
        uint32_t        cbSize = sizeof(FILEIO_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    FILEIO_DATA *   fileio_New (
    )
    {
        FILEIO_DATA     *this;
        
        this = fileio_Alloc( );
        if (this) {
            this = fileio_Init(this);
        } 
        return this;
    }



    FILEIO_DATA *   fileio_NewCreate (
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        FILEIO_DATA     *pObj = OBJ_NIL;
        
        pObj = fileio_New( );
        if (pObj) {
            eRc = fileio_Create(pObj, pPath);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pObj);
                pObj = OBJ_NIL;
                return pObj;
            }
            eRc = fileio_Close(pObj, false);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pObj);
                pObj = OBJ_NIL;
                return pObj;
            }
            eRc = fileio_Open(pObj, pPath);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pObj);
                pObj = OBJ_NIL;
                return pObj;
            }
        }
        
        return pObj;
    }
    
    
    
    FILEIO_DATA *   fileio_NewOpen (
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        FILEIO_DATA     *pObj = OBJ_NIL;
        
        pObj = fileio_New( );
        if (pObj) {
            eRc = fileio_Open(pObj, pPath);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pObj);
                pObj = OBJ_NIL;
                return pObj;
            }
        }
        
        return pObj;
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    bool            fileio_getAppend (
        FILEIO_DATA     *this
    )
    {
        int             fileFlags;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        if (!fileio_IsOpen(this)) {
            return false;
        }
        
        fileFlags = fcntl(this->fileHandle, F_GETFL, 0);
        if (fileFlags & O_APPEND) {
            return true;
        }
        
        //return this->priority;
        return false;
    }
    
    bool            fileio_setAppend (
        FILEIO_DATA     *this,
        bool            fValue
    )
    {
        int             fileFlags;
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (!fileio_IsOpen(this)) {
            return false;
        }
        
        fileFlags = fcntl(this->fileHandle, F_GETFL, 0);
        if (fValue)
            fileFlags |= O_APPEND;
        else
            fileFlags &= ~O_APPEND;
        if (fcntl(this->fileHandle, F_SETFL, fileFlags) < 0) {
            return false;
        }
        
        return true;
    }
    
    
    
    PATH_DATA *     fileio_getPath (
        FILEIO_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pPath;
    }
    
    
    bool          fileio_setPath (
        FILEIO_DATA     *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        //obj_Retain(pValue);
        if (this->pPath) {
            obj_Release(this->pPath);
        }
        if (pValue) {
            this->pPath = path_Copy(pValue);
        }
        else {
            this->pPath = OBJ_NIL;
        }
        
        return true;
    }
    
    
    
    uint16_t      fileio_getPriority (
        FILEIO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            fileio_setPriority (
        FILEIO_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    uint32_t        fileio_getSize (
        FILEIO_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return 0;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         fileio_Assign (
        FILEIO_DATA		*this,
        FILEIO_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!fileio_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        if (pOther->pPath) {
            obj_Release(pOther->pPath);
            pOther->pPath = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pPath) {
            if (obj_getVtbl(this->pPath)->pCopy) {
                pOther->pPath = obj_getVtbl(this->pPath)->pCopy(this->pPath);
            }
            else {
                obj_Retain(this->pPath);
                pOther->pPath = this->pPath;
            }
        }

        // Copy other data from this object to other.
#ifdef XYZZY
        pOther->headerSize = this->headerSize;
        if (this->headerSize && this->pHeader) {
            pOther->pHeader = mem_Malloc(this->headerSize);
            if (pOther->pHeader) {
                memmove(pOther->pHeader, this->pHeader, this->headerSize);
            }
        }
#endif
        
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;

        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C l o s e
    //---------------------------------------------------------------
    
    ERESULT     fileio_Close (
        FILEIO_DATA *this,
        bool        fDelete
    )
    {
        int         iRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!obj_Flag(this, FILEIO_FILE_OPEN)) {
            DEBUG_BREAK();
            return ERESULT_FILE_CLOSED;
        }
#endif
        
        //  Close the File.
        this->fileHandle = close(this->fileHandle);
        if (this->fileHandle == -1) {
            return ERESULT_CLOSE_ERROR;
        }
        obj_FlagSet(this, FILEIO_FILE_OPEN, false);
        
        if (fDelete) {
            iRc = unlink(path_getData(this->pPath));
        }
        
        fileio_setPath(this, OBJ_NIL);

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    FILEIO_DATA *     fileio_Copy (
        FILEIO_DATA       *this
    )
    {
        FILEIO_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = fileio_New( );
        if (pOther) {
            eRc = fileio_Assign(this, pOther);
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
    
    ERESULT         fileio_Create (
        FILEIO_DATA     *this,
        PATH_DATA       *pPath
    )
    {
        int             fileHandle;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (pPath == OBJ_NIL) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (this->pPath) {
            obj_Release(this->pPath);
        }
        this->pPath = path_Copy(pPath);
        if (this->pPath) {
            path_Clean(this->pPath);
        }
        else {
            return ERESULT_OUT_OF_MEMORY;
        }

        //  Open the File.
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        fileHandle =    open(
                             path_getData(this->pPath),
                             (O_CREAT | O_TRUNC | O_RDWR),
                             (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
                        );
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        DEBUG_BREAK();
        //FIXME: This needs to be updated and tested.
        fileHandle =    open(
                             path_getData(this->pPath),
                             (O_APPEND | O_RDWR),
                             (S_IREAD | S_IWRITE)
                             );
#endif
        if (fileHandle == -1) {
            return ERESULT_OPEN_ERROR;
        }
        this->fileHandle = fileHandle;
        obj_FlagSet(this, FILEIO_FILE_OPEN, true);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            fileio_Dealloc (
        OBJ_ID          objId
    )
    {
        FILEIO_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        if (obj_Flag(this, FILEIO_FILE_OPEN)) {
            fileio_Close(this, false);
        }

        fileio_setPath(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    bool            fileio_Enable (
        FILEIO_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!fileio_Validate(this)) {
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
    //                          G e t s
    //---------------------------------------------------------------
    
    ERESULT         fileio_Gets (
        FILEIO_DATA     *this,
        uint32_t        cBuffer,
        uint8_t         *pBuffer
    )
    {
        ERESULT         eRc;
        uint8_t         *pChr;
        uint8_t         chr = 0;
        uint32_t        amtRead;
        off_t           fileOffset;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (cBuffer > 1)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == pBuffer) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        --cBuffer;                      // Allow for trailing NUL.
        
        pChr = pBuffer;
        for (;;) {
            if (--cBuffer == 0)
                break;
            eRc = fileio_Read(this, 1, &chr, &amtRead);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            if (!(1 == amtRead))
                break;
            if (chr == '\n')
                break;
            if (chr == '\r')
                break;
            *pChr++ = chr;
        }
        *pChr++ = '\0';                 // Add trailing NUL.

        // Remove '\r' '\n' or '\n' '\r' combination.
        if ((chr == '\n') || (chr == '\r')) {
            eRc = fileio_Read(this, 1, &chr, &amtRead);
            if (!ERESULT_FAILED(eRc) && (1 == amtRead)) {
                if ((chr == '\n') || (chr == '\r'))
                    ;
                else {
                    fileOffset = fileio_SeekCur(this, -1);
                }
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    FILEIO_DATA *   fileio_Init (
        FILEIO_DATA     *this
    )
    {
        uint32_t        cbSize = sizeof(FILEIO_DATA);
        
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

        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_FILEIO);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_FILEIO); // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&fileio_Vtbl);
        
    #ifdef NDEBUG
    #else
        if( !fileio_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s O p e n
    //---------------------------------------------------------------
    
    bool            fileio_IsOpen (
        FILEIO_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_Flag(this, FILEIO_FILE_OPEN))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //----------------------------------------------------------------
    //                          O p e n
    //----------------------------------------------------------------
    
    ERESULT         fileio_Open (
        FILEIO_DATA     *this,
        PATH_DATA       *pPath
    )
    {
        int             fileHandle;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fileio_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (pPath == OBJ_NIL) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (this->pPath) {
            obj_Release(this->pPath);
        }
        this->pPath = path_Copy(pPath);
        if (this->pPath) {
            path_Clean(this->pPath);
        }
        else {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        //  Open the File.
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        fileHandle =    open(
                             path_getData(this->pPath),
                             (O_RDWR),
                             (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
                             );
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        fileHandle =    open(
                             path_getData(this->pPath),
                             (O_APPEND | O_RDWR),
                             (S_IREAD | S_IWRITE)
                             );
#endif
        if(-1 == fileHandle) {
            if (errno == ENOENT) {
                return ERESULT_FILE_NOT_FOUND;
            }
            //perror(NULL);
            return ERESULT_OPEN_ERROR;
        }
        this->fileHandle = fileHandle;
        obj_FlagSet(this, FILEIO_FILE_OPEN, true);
        
        // Return to Caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          fileio_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        FILEIO_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
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
                        
#ifdef XYZZY
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return fileio_Disable;
                        }
                        break;
                        
                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return fileio_Enable;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return fileio_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return fileio_ToJSON;
                        }
                        break;
#endif
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //----------------------------------------------------------------
    //                          R e a d
    //----------------------------------------------------------------

    ERESULT         fileio_Read (
        FILEIO_DATA     *this,
        uint32_t        cBuffer,            // (in)
        void            *pBuffer,           // (in)
        uint32_t        *pReadCount         // (out)
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        size_t          bytes_read;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        // Read in the area.
        bytes_read = read(this->fileHandle, pBuffer, cBuffer);
        if (-1 == bytes_read) {
            return ERESULT_READ_ERROR;
        }
        if (pReadCount) {
            *pReadCount = (uint32_t)bytes_read;
        }
        if(bytes_read == cBuffer)
            ;
        else {
            eRc = ERESULT_SUCCESS_PARTIAL_DATA;
        }
        
        // Return to Caller.
        return eRc;
    }
    
    
    
    //----------------------------------------------------------------
    //                          S e e k
    //----------------------------------------------------------------
    
    off_t           fileio_SeekBegin (
        FILEIO_DATA     *this,
        off_t           offset
    )
    {
        off_t           fileOffset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        //  Position within the File.
        fileOffset = lseek(this->fileHandle, offset, SEEK_SET);
        
        // Return to Caller.
        return fileOffset;
    }
    
    
    off_t           fileio_SeekCur (
        FILEIO_DATA     *this,
        off_t           offset
    )
    {
        off_t           fileOffset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        //  Position within the File.
        fileOffset = lseek(this->fileHandle, offset, SEEK_CUR);
        
        // Return to Caller.
        return fileOffset;
    }
    
    
    off_t           fileio_SeekEnd (
        FILEIO_DATA     *this,
        off_t           offset
    )
    {
        off_t           fileOffset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        //  Position within the File.
        fileOffset = lseek(this->fileHandle, offset, SEEK_END);
        
        // Return to Caller.
        return fileOffset;
    }
    
    

    //---------------------------------------------------------------
    //                          S i z e
    //---------------------------------------------------------------
    
    size_t          fileio_Size (
        FILEIO_DATA     *this
    )
    {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        size_t          fileSize = -1;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
        if (!obj_Flag(this, FILEIO_FILE_OPEN)) {
            return -1;
        }
#endif
        
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = fstat(this->fileHandle, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFREG) {
                fileSize = statBuffer.st_size;
            }
        }
#endif
        
        // Return to caller.
        return fileSize;
    }
    
    
    
    
    //----------------------------------------------------------------
    //                          T e l l
    //----------------------------------------------------------------
    
    off_t           fileio_Tell (
        FILEIO_DATA     *this
    )
    {
        off_t           fileOffset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        //  Position within the File.
        fileOffset = lseek(this->fileHandle, 0, SEEK_CUR);
        
        // Return to Caller.
        return fileOffset;
    }
    
    

    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     fileio_ToDebugString (
        FILEIO_DATA      *this,
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
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(fileio) ",
                     this
            );
        AStr_AppendA(pStr, str);

        if (this->pPath) {
            if (((OBJ_DATA *)(this->pPath))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pPath))->pVtbl->pToDebugString(
                                                    this->pPath,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        
        j = snprintf(str, sizeof(str), " %p(fileio)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            fileio_Validate(
        FILEIO_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_FILEIO) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(FILEIO_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    //----------------------------------------------------------------
    //              Write a Memory Area to the File
    //----------------------------------------------------------------
    /* Purpose
     *          This function writes a Memory Area to the File.
     * Returns
     *          ERESULT_SUCCESS     =   Successful Completion
     *          ERESULT_SEEK_ERROR  =   Disk Seek Error
     *          ERESULT_WRITE_ERROR =   Disk Write Error
     */
    ERESULT         fileio_Write (
        FILEIO_DATA     *this,
        uint32_t        cBuffer,
        const
        void            *pBuffer
    )
    {
        size_t          bytes_written;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!fileio_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Write the data.
        bytes_written = write(this->fileHandle, pBuffer, cBuffer);
        if (bytes_written == -1) {
            return ERESULT_WRITE_ERROR;
        }
        if(bytes_written == cBuffer)
            ;
        else {
            return ERESULT_WRITE_ERROR;
        }
        
        // Return to Caller.
        return ERESULT_SUCCESS;
    }
    
    
    

    
#ifdef	__cplusplus
}
#endif


