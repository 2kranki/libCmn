// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   FileIO.c
 *  Generated 07/10/2021 11:26:44
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
#include        <FileIO_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>
#include        <fcntl.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            FileIO_task_body (
        void            *pData
    )
    {
        //FILEIO_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    FILEIO_DATA *     FileIO_Alloc (
        void
    )
    {
        FILEIO_DATA       *this;
        uint32_t        cbSize = sizeof(FILEIO_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    FILEIO_DATA *     FileIO_New (
        void
    )
    {
        FILEIO_DATA       *this;
        
        this = FileIO_Alloc( );
        if (this) {
            this = FileIO_Init(this);
        } 
        return this;
    }



    FILEIO_DATA *   FileIO_NewCreate (
        PATH_DATA       *pPath,
        bool            fMem
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        FILEIO_DATA     *pObj = OBJ_NIL;

        pObj = FileIO_New( );
        if (pObj) {
            eRc = FileIO_Create(pObj, pPath, fMem);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pObj);
                pObj = OBJ_NIL;
                return pObj;
            }
            eRc = FileIO_Close(pObj, false);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pObj);
                pObj = OBJ_NIL;
                return pObj;
            }
            eRc = FileIO_Open(pObj, pPath, false);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pObj);
                pObj = OBJ_NIL;
                return pObj;
            }
        }

        return pObj;
    }



    FILEIO_DATA *   FileIO_NewOpen (
        PATH_DATA       *pPath,
        bool            fMem
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        FILEIO_DATA     *pObj = OBJ_NIL;

        pObj = FileIO_New( );
        if (pObj) {
            eRc = FileIO_Open(pObj, pPath, fMem);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pObj);
                pObj = OBJ_NIL;
                return pObj;
            }
        }

        return pObj;
    }



    FILEIO_DATA *   FileIO_NewStdin (
        void
    )
    {
        FILEIO_DATA     *this = OBJ_NIL;

        this = FileIO_New( );
        if (this) {

            this->openFlags = FILEIO_OPEN_NO;
            this->closeFlags = FILEIO_CLOSE_REQ;
            this->readAccess = 1;
            this->writeAccess = 0;
            this->status = FILEIO_STATUS_READ;
            this->fileHandle = fcntl(fileno(stdin), F_DUPFD, 0);
            if (this->fileHandle < 0) {
                obj_Release(this);
                this = OBJ_NIL;
                return this;
            }
        }

        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                        A p p e n d
    //---------------------------------------------------------------

    bool            FileIO_getAppend (
        FILEIO_DATA     *this
    )
    {
        int             fileFlags;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        if (!FileIO_IsOpen(this)) {
            return false;
        }

        fileFlags = fcntl(this->fileHandle, F_GETFL, 0);
        if (fileFlags & O_APPEND) {
            return true;
        }

        //return this->priority;
        return false;
    }

    bool            FileIO_setAppend (
        FILEIO_DATA     *this,
        bool            fValue
    )
    {
        int             fileFlags;
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (!FileIO_IsOpen(this)) {
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



    //---------------------------------------------------------------
    //                          D a t a
    //---------------------------------------------------------------

    U8ARRAY_DATA *  FileIO_getData (
        FILEIO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pData;
    }


    bool          FileIO_setData (
        FILEIO_DATA     *this,
        U8ARRAY_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pData) {
            obj_Release(this->pData);
        }
        this->pData = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          I O
    //---------------------------------------------------------------

    IO_INTERFACE *  FileIO_getIO (
        FILEIO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        obj_Retain(this);
        return (IO_INTERFACE *)this;
    }



    //---------------------------------------------------------------
    //                          P a t h
    //---------------------------------------------------------------

    PATH_DATA *     FileIO_getPath (
        FILEIO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pPath;
    }


    bool          FileIO_setPath (
        FILEIO_DATA     *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        //obj_Retain(pValue);
        if (this->pPath) {
            obj_Release(this->pPath);
        }
        if (pValue) {
            this->pPath = Path_Copy(pValue);
        }
        else {
            this->pPath = OBJ_NIL;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        FileIO_getPriority (
        FILEIO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            FileIO_setPriority (
        FILEIO_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
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
    
    int32_t         FileIO_getSize (
        FILEIO_DATA     *this
    )
    {
        uint32_t        size = -1;
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (obj_Flag(this, FILEIO_MEM_BASED)) {

        } else  {
        }
        return size;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  FileIO_getSuperVtbl (
        FILEIO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
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
        ERESULT eRc = FileIO_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another FILEIO object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         FileIO_Assign (
        FILEIO_DATA       *this,
        FILEIO_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!FileIO_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

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
        //pOther->x     = this->x; 

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

    ERESULT     FileIO_Close (
        FILEIO_DATA *this,
        bool        fDelete
    )
    {
        bool        fRc;
        int         iRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!obj_Flag(this, FILEIO_FILE_OPEN)) {
            DEBUG_BREAK();
            return ERESULT_FILE_CLOSED;
        }
#endif

        //  Close the File.
        if (obj_Flag(this, FILEIO_MEM_BASED)) {
            FILEIO_CLASS_VTBL   *pVtbl = (void *)obj_getVtbl(FileIO_Class());
            //FILEIO_DATA         *pFile;

            if (fDelete)
                ;
            else {
                if (this->pData && this->pPath) {
                    u8Array_setOther(this->pData, this->pPath);
                    u8Array_setMisc(this->pData, (uint32_t)this->offset);
                    pVtbl->pMemFileDelete(FileIO_getPath(this));
                    fRc = pVtbl->pMemFileAdd(this->pData);
                    obj_Release(this->pData);
                    this->pData = OBJ_NIL;
                }
            }
        } else  {
            this->fileHandle = close(this->fileHandle);
            if (this->fileHandle == -1) {
                return ERESULT_CLOSE_ERROR;
            }
            if (fDelete) {
                iRc = unlink(Path_getData(this->pPath));
            }
        }
        obj_FlagSet(this, FILEIO_FILE_OPEN, false);

        FileIO_setPath(this, OBJ_NIL);

        // Return to caller.
        return ERESULT_SUCCESS;
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
    int             FileIO_Compare (
        FILEIO_DATA     *this,
        FILEIO_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!FileIO_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        FileIO      *pCopy = FileIO_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a FILEIO object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    FILEIO_DATA *     FileIO_Copy (
        FILEIO_DATA       *this
    )
    {
        FILEIO_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef FILEIO_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = FileIO_New( );
        if (pOther) {
            eRc = FileIO_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C r e a t e
    //---------------------------------------------------------------

    ERESULT         FileIO_Create (
        FILEIO_DATA     *this,
        PATH_DATA       *pPath,
        bool            fMem
    )
    {
        ERESULT         eRc;
        int             fileHandle;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((pPath == OBJ_NIL) && !fMem) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (this->pPath) {
            obj_Release(this->pPath);
            this->pPath = OBJ_NIL;
        }
        if (pPath) {
            this->pPath = Path_Copy(pPath);
            if (this->pPath) {
                Path_Clean(this->pPath);
            } else {
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        if (fMem) {
            obj_FlagSet(this, FILEIO_MEM_BASED, true);
        } else {
            obj_FlagSet(this, FILEIO_MEM_BASED, false);
        }

        //  Open the File.
        if (obj_Flag(this, FILEIO_MEM_BASED)) {
            if (OBJ_NIL == this->pData) {
                this->pData = u8Array_New();
                if (OBJ_NIL == this->pData) {
                    DEBUG_BREAK();
                    return ERESULT_OUT_OF_MEMORY;
                }
            }
            eRc = u8Array_Truncate(this->pData, 0);
            this->offset = 0;
        } else  {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
            fileHandle =    open(
                                 Path_getData(this->pPath),
                                 (O_CREAT | O_TRUNC | O_RDWR),
                                 (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
                            );
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
            DEBUG_BREAK();
            //FIXME: This needs to be updated and tested.
            fileHandle =    open(
                                 Path_getData(this->pPath),
                                 (O_APPEND | O_RDWR),
                                 (S_IREAD | S_IWRITE)
                                 );
#endif
            if (fileHandle == -1) {
                return ERESULT_OPEN_ERROR;
            }
            this->fileHandle = fileHandle;
        }
        obj_FlagSet(this, FILEIO_FILE_OPEN, true);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            FileIO_Dealloc (
        OBJ_ID          objId
    )
    {
        FILEIO_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((FILEIO_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (obj_Flag(this, FILEIO_FILE_OPEN)) {
            FileIO_Close(this, false);
        }

        FileIO_setData(this, OBJ_NIL);
        FileIO_setPath(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        FileIO      *pDeepCopy = FileIO_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a FILEIO object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    FILEIO_DATA *   FileIO_DeepyCopy (
        FILEIO_DATA     *this
    )
    {
        FILEIO_DATA     *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = FileIO_New( );
        if (pOther) {
            eRc = FileIO_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
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
    ERESULT         FileIO_Disable (
        FILEIO_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return eRc;
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
    ERESULT         FileIO_Enable (
        FILEIO_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          F l u s h
    //---------------------------------------------------------------

    ERESULT         FileIO_Flush (
        FILEIO_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        if (obj_Flag(this, FILEIO_MEM_BASED)) {

        } else  {
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          G e t s
    //---------------------------------------------------------------

    ERESULT         FileIO_Gets (
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
        if (!FileIO_Validate(this)) {
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

        if (obj_Flag(this, FILEIO_MEM_BASED)) {
            return ERESULT_NOT_IMPLEMENTED;
        } else  {
            pChr = pBuffer;
            for (;;) {
                if (--cBuffer == 0)
                    break;
                eRc = FileIO_Read(this, 1, &chr, &amtRead);
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
                eRc = FileIO_Read(this, 1, &chr, &amtRead);
                if (!ERESULT_FAILED(eRc) && (1 == amtRead)) {
                    if ((chr == '\n') || (chr == '\r'))
                        ;
                    else {
                        fileOffset = FileIO_SeekCur(this, -1);
                    }
                }
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    ERESULT         FileIO_GetsW32 (
        FILEIO_DATA     *this,
        uint32_t        cBuffer,
        W32CHR_T        *pBuffer
    )
    {
        ERESULT         eRc;
        W32CHR_T        *pChr;
        W32CHR_T        chr = 0;
        uint32_t        amtRead;
        off_t           fileOffset;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
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

        if (obj_Flag(this, FILEIO_MEM_BASED)) {
            return ERESULT_NOT_IMPLEMENTED;
        } else  {
            pChr = pBuffer;
            for (;;) {
                if (--cBuffer == 0)
                    break;
                //TODO: chr = fgetwc();
                eRc = FileIO_Read(this, 1, &chr, &amtRead);
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
                eRc = FileIO_Read(this, 1, &chr, &amtRead);
                if (!ERESULT_FAILED(eRc) && (1 == amtRead)) {
                    if ((chr == '\n') || (chr == '\r'))
                        ;
                    else {
                        fileOffset = FileIO_SeekCur(this, -1);
                    }
                }
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    FILEIO_DATA *   FileIO_Init (
        FILEIO_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(FILEIO_DATA);
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of FileIO_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_FILEIO);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&FileIO_Vtbl);
#ifdef  FILEIO_JSON_SUPPORT
        JsonIn_RegisterClass(FileIO_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "FileIO::sizeof(FILEIO_DATA) = %lu\n", 
                sizeof(FILEIO_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(FILEIO_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         FileIO_IsEnabled (
        FILEIO_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
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
    //                       I s O p e n
    //---------------------------------------------------------------

    bool            FileIO_IsOpen (
        FILEIO_DATA        *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
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

    ERESULT         FileIO_Open (
        FILEIO_DATA     *this,
        PATH_DATA       *pPath,
        bool            fMem
    )
    {
        int             fileHandle;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !FileIO_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((pPath == OBJ_NIL) && !fMem) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (this->pPath) {
            obj_Release(this->pPath);
        }
        if (pPath) {
            this->pPath = Path_Copy(pPath);
            if (this->pPath) {
                Path_Clean(this->pPath);
            } else {
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        if (fMem) {
            obj_FlagSet(this, FILEIO_MEM_BASED, true);
        } else {
            obj_FlagSet(this, FILEIO_MEM_BASED, false);
        }

        //  Open the File.
        if (obj_Flag(this, FILEIO_MEM_BASED)) {
            FILEIO_CLASS_VTBL   *pVtbl = (void *)obj_getVtbl(FileIO_Class());
            U8ARRAY_DATA        *pData;
            pData = pVtbl->pMemFileFind(this->pPath);
            if (pData) {
                obj_Retain(pData);
                this->pData = pData;
                //this->offset = u8Array_getMisc(pData);
                pVtbl->pMemFileDelete(this->pPath);
                u8Array_setOther(pData, OBJ_NIL);
                this->offset = 0;
            }
            if (OBJ_NIL == this->pData) {
                this->pData = u8Array_New();
                if (OBJ_NIL == this->pData) {
                    DEBUG_BREAK();
                    return ERESULT_OUT_OF_MEMORY;
                }
                this->offset = 0;
            }
        } else  {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
            fileHandle =    open(
                                 Path_getData(this->pPath),
                                 (O_RDWR),
                                 (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
                                 );
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
            fileHandle =    open(
                                 Path_getData(this->pPath),
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
        }
        obj_FlagSet(this, FILEIO_FILE_OPEN, true);

        // Return to Caller.
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
        void        *pMethod = FileIO_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "FileIO", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          FileIO_QueryInfo (
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
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(FILEIO_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)FileIO_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'g':
                        if (str_Compare("getPath", (char *)pStr) == 0) {
                            return FileIO_getPath;
                        }
                        break;

                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return FileIO_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return FileIO_Enable;
                        }
                        break;

                    case 'P':
#ifdef  FILEIO_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return FileIO_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return FileIO_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return FileIO_ToDebugString;
                        }
#ifdef  FILEIO_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return FileIO_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return FileIO_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == FileIO_ToDebugString)
                    return "ToDebugString";
#ifdef  FILEIO_JSON_SUPPORT
                if (pData == FileIO_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //----------------------------------------------------------------
    //                          R e a d
    //----------------------------------------------------------------

    ERESULT         FileIO_Read (
        FILEIO_DATA     *this,
        uint32_t        cBuffer,            // (in)
        void            *pBuffer,           // (in)
        uint32_t        *pReadCount         // (out)
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        size_t          bytes_read;
        uint8_t         *pData;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        // Read in the area.
        if (obj_Flag(this, FILEIO_MEM_BASED)) {
            // Insure that we have the space for it.
            bytes_read = u8Array_getSize(this->pData);
            bytes_read -= this->offset;
            if (bytes_read > cBuffer) {
                bytes_read = cBuffer;
            }

            if (bytes_read > 0) {
                pData = u8Array_GetAddrOf(this->pData, ((uint32_t)this->offset + 1));
                memmove(pBuffer, pData, bytes_read);
            }
            if (pReadCount) {
                *pReadCount = (uint32_t)bytes_read;
            }
        } else  {
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
        }

        // Return to Caller.
        return eRc;
    }


    int32_t         FileIO_ReadIO (
        FILEIO_DATA     *this,
        uint8_t         *pBuffer,
        int32_t         size
    )
    {
        size_t          bytes_read = -1;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        // Read in the area.
        if (obj_Flag(this, FILEIO_MEM_BASED)) {

        } else  {
            bytes_read = read(this->fileHandle, pBuffer, size);
        }

        // Return to Caller.
        return (int32_t)bytes_read;
    }



    //----------------------------------------------------------------
    //                          S e e k
    //----------------------------------------------------------------

    off_t           FileIO_Seek (
        FILEIO_DATA     *this,
        off_t           offset,
        uint8_t         type
    )
    {
        off_t           offsetNew = -1;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        switch (type) {
            case IO_SEEK_SET:
                offsetNew = FileIO_SeekBegin(this, offset);
                break;

            case IO_SEEK_CUR:
                offsetNew = FileIO_SeekCur(this, offset);
                break;

            case IO_SEEK_END:
                offsetNew = FileIO_SeekEnd(this, offset);
                break;
        }

        // Return to caller.
        return offsetNew;
    }


    off_t           FileIO_SeekBegin (
        FILEIO_DATA     *this,
        off_t           offset
    )
    {
        off_t           fileOffset = -1;
        uint32_t        sizeFile;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
#endif

        //  Position within the File.
        if (obj_Flag(this, FILEIO_MEM_BASED)) {
            sizeFile = u8Array_getSize(this->pData);
            if (offset <= sizeFile) {
                this->offset = offset;
                fileOffset = offset;
            }
        } else  {
            fileOffset = lseek(this->fileHandle, offset, SEEK_SET);
        }

        // Return to Caller.
        return fileOffset;
    }


    off_t           FileIO_SeekCur (
        FILEIO_DATA     *this,
        off_t           offset
    )
    {
        off_t           fileOffset;
        uint32_t        sizeFile;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
#endif

        //  Position within the File.
        if (obj_Flag(this, FILEIO_MEM_BASED)) {
            sizeFile = u8Array_getSize(this->pData);
            fileOffset = this->offset + offset;
            if (fileOffset > sizeFile)
                fileOffset = -1;
            else {
                this->offset = fileOffset;
            }
        } else  {
            fileOffset = lseek(this->fileHandle, offset, SEEK_CUR);
        }

        // Return to Caller.
        return fileOffset;
    }


    off_t           FileIO_SeekEnd (
        FILEIO_DATA     *this,
        off_t           offset
    )
    {
        off_t           fileOffset;
        uint32_t        sizeFile;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
#endif

        //  Position within the File.
        if (obj_Flag(this, FILEIO_MEM_BASED)) {
            sizeFile = u8Array_getSize(this->pData);
            fileOffset = sizeFile + offset;
            if (fileOffset > sizeFile)
                fileOffset = -1;
            else {
                this->offset = fileOffset;
            }
        } else  {
            fileOffset = lseek(this->fileHandle, offset, SEEK_END);
        }

        // Return to Caller.
        return fileOffset;
    }



    //---------------------------------------------------------------
    //                          S i z e
    //---------------------------------------------------------------

    size_t          FileIO_Size (
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
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
        if (!obj_Flag(this, FILEIO_FILE_OPEN)) {
            return -1;
        }
#endif

        if (obj_Flag(this, FILEIO_MEM_BASED)) {
            if (this->pData) {
                fileSize = u8Array_getSize(this->pData);
            }
        } else  {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
            iRc = fstat(this->fileHandle, &statBuffer);
            if (0 == iRc) {
                if ((statBuffer.st_mode & S_IFMT) == S_IFREG) {
                    fileSize = statBuffer.st_size;
                }
            }
#endif
        }

        // Return to caller.
        return fileSize;
    }




    //----------------------------------------------------------------
    //                          T e l l
    //----------------------------------------------------------------

    off_t           FileIO_Tell (
        FILEIO_DATA     *this
    )
    {
        off_t           fileOffset = -1;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return -1;
        }
#endif

        //  Position within the File.
        if (obj_Flag(this, FILEIO_MEM_BASED)) {

        } else  {
            fileOffset = lseek(this->fileHandle, 0, SEEK_CUR);
        }

        // Return to Caller.
        return fileOffset;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = FileIO_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     FileIO_ToDebugString (
        FILEIO_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
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
                    FileIO_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
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
    bool            FileIO_Validate (
        FILEIO_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_FILEIO))
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


        if (!(obj_getSize(this) >= sizeof(FILEIO_DATA))) {
            return false;
        }

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
    ERESULT         FileIO_Write (
        FILEIO_DATA     *this,
        uint32_t        cBuffer,
        const
        void            *pBuffer
    )
    {
        ERESULT         eRc = ERESULT_INVALID_PARAMETER;
        size_t          bytes_written;
        uint8_t         *pData;
        int32_t         sizeNeeded;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Write the data.
        if (obj_Flag(this, FILEIO_MEM_BASED)) {
            sizeNeeded = u8Array_getSize(this->pData);
            sizeNeeded -= this->offset;
            sizeNeeded -= cBuffer;
            if (sizeNeeded < 0) {
                sizeNeeded = -sizeNeeded;
                eRc =   u8Array_Extend(
                                       this->pData,
                                       (sizeNeeded + u8Array_getSize(this->pData))
                        );
            }
            pData = u8Array_GetAddrOf(this->pData, (uint32_t)this->offset+1);
            memmove(pData, pBuffer, cBuffer);
            this->offset += cBuffer;
        } else  {
            bytes_written = write(this->fileHandle, pBuffer, cBuffer);
            if (bytes_written == -1) {
                return ERESULT_WRITE_ERROR;
            }
            if(bytes_written == cBuffer)
                ;
            else {
                return ERESULT_WRITE_ERROR;
            }
        }

        // Return to Caller.
        return ERESULT_SUCCESS;
    }


    int32_t         FileIO_WriteIO (
        FILEIO_DATA     *this,
        const
        uint8_t         *pBuffer,
        int32_t         size
    )
    {
        ERESULT         eRc = ERESULT_INVALID_PARAMETER;
        size_t          bytes_written = -1;
        uint8_t         *pData;
        int32_t         sizeNeeded;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!FileIO_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Write the data.
        if (obj_Flag(this, FILEIO_MEM_BASED)) {
            sizeNeeded = u8Array_getSize(this->pData);
            sizeNeeded -= this->offset;
            sizeNeeded -= size;
            if ( sizeNeeded < 0) {
                sizeNeeded = -sizeNeeded;
                eRc =   u8Array_Extend(
                                       this->pData,
                                       (sizeNeeded + u8Array_getSize(this->pData))
                        );
            }

            pData = u8Array_GetAddrOf(this->pData, (uint32_t)this->offset+1);
            memmove(pData, pBuffer, size);
        } else  {
            bytes_written = write(this->fileHandle, pBuffer, size);
        }

        // Return to Caller.
        return (int32_t)bytes_written;
    }




    
#ifdef  __cplusplus
}
#endif


