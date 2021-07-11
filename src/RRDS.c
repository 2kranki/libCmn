// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   RRDS.c
 *  Generated 07/10/2021 09:44:02
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
#include        <RRDS_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /* Local function declarations
     */
    static
    bool            RRDS_FileExtend (
        RRDS_DATA       *this,
        uint32_t        lsn                /* Block to extend to */
    );

    static
    ERESULT         RRDS_LSN_Read (
        RRDS_DATA       *this,
        uint32_t        recordNum,
        uint8_t         *pBuffer
    );

    static
    ERESULT         RRDS_LSN_Write (
        RRDS_DATA       *this,
        uint32_t        recordNum,
        uint8_t         *pBuffer
    );

    static
    size_t          RRDS_RecordOffset (
        RRDS_DATA       *this,
        uint32_t        recordNum
    );



    //----------------------------------------------------------------
    //                      F i l e  C l o s e
    //----------------------------------------------------------------
    static
    ERESULT         RRDS_FileClose (
        RRDS_DATA       *this,
        bool            fDelete
    )
    {
        ERESULT         eRc;

        if (this->pIO && FileIO_IsOpen(this->pIO)) {
            // Close the file.
            eRc = FileIO_Close(this->pIO, fDelete);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
        }

        RRDS_setFileIO(this, OBJ_NIL);

        // Return to Caller.
        return ERESULT_SUCCESS;
    }



    //----------------------------------------------------------------
    //      RRDS_FileExtend - Extend the File with Zeroed Records
    //----------------------------------------------------------------
    /* Purpose
     *          This function writes zero-filled records into the File.
     * Returns
     *          RRDS_OK          =   Successful Completion
     *          RRDS_ERROR_NOMEM =   Memory Allocation Error
     *          RRDS_ERROR_SEEK  =   Disk Seek Error
     *          RRDS_ERROR_WRITE =   Disk Write Error
     */
    static
    bool            RRDS_FileExtend (
        RRDS_DATA       *this,
        uint32_t        recordNum           /* Record to extend to */
    )
    {
        ERESULT         eRc;
        uint32_t        curRec;
        size_t          fileOffset;
        uint8_t         *pFillData;

        // Fill the File until Block number of records exist
        // bypassing the LRU mechanism.
        if( recordNum > this->cRecords ) {

            pFillData = (uint8_t *)mem_Malloc(this->recordSize);
            if( NULL == pFillData ) {
                return false;
            }
            memset(pFillData, this->fillChar, this->recordSize);

            for (curRec=(this->cRecords + 1); curRec <= recordNum; ++curRec) {
                fileOffset = RRDS_RecordOffset(this, curRec);
                eRc = RRDS_LSN_Write(
                                       this,
                                       curRec,
                                       pFillData
                                       );
                if(ERESULT_FAILED(eRc)) {
                    DEBUG_BREAK();
                    mem_Free(pFillData);
                    //pFillData = NULL;
                    return false;
                }
            }

            mem_Free(pFillData);
            //pFillData = NULL;
        }

        // Return to Caller.
        return true;
    }



    //----------------------------------------------------------------
    //              R e a d  D a t a  U s i n g  L S N
    //----------------------------------------------------------------
    static
    ERESULT         RRDS_LSN_Read (
        RRDS_DATA       *this,
        uint32_t        lsn,
        uint8_t         *pBuffer
    )
    {
        ERESULT         eRc;
        off_t           fileOffset;
        off_t           seekOffset;
        uint32_t        amtRead = 0;

        // Seek to the appropriate location within the file.
        fileOffset = RRDS_RecordOffset(this, lsn);
        seekOffset = FileIO_SeekBegin(this->pIO, fileOffset);
        if (seekOffset == fileOffset)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_SEEK_ERROR;
        }

        // Read the data.
        eRc = FileIO_Read(this->pIO, this->reqSize, pBuffer, &amtRead);

        // Return to Caller.
        return eRc;
    }



    //----------------------------------------------------------------
    //              W r i t e  D a t a  U s i n g  L S N
    //----------------------------------------------------------------
    static
    ERESULT         RRDS_LSN_Write (
        RRDS_DATA       *this,
        uint32_t        lsn,
        uint8_t         *pBuffer
    )
    {
        ERESULT         eRc;
        off_t           fileOffset = lsn;
        off_t           seekOffset;
        uint8_t         rcdtrm[2];
        int             cRcdtrm = 1;

        // Seek to the appropriate location within the file.
        fileOffset = RRDS_RecordOffset(this, lsn);
        seekOffset = FileIO_SeekBegin(this->pIO, fileOffset);
        if (seekOffset == fileOffset)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_SEEK_ERROR;
        }

        // Write the data.
        eRc = FileIO_Write(this->pIO, this->reqSize, pBuffer);
        if (!ERESULT_FAILED(eRc)) {
            if (lsn > this->cRecords) {
                this->cRecords = lsn;
            }
        }

        // Write the record terminator.
        switch (this->recordTerm) {
            case RRDS_RCD_TRM_NONE:
                cRcdtrm = 0;
                break;

            case RRDS_RCD_TRM_CR:
                cRcdtrm = 1;
                rcdtrm[0] = '\r';
                break;

            case RRDS_RCD_TRM_NL:
                cRcdtrm = 1;
                rcdtrm[0] = '\n';
                break;

            case RRDS_RCD_TRM_CRNL:
                cRcdtrm = 2;
                rcdtrm[0] = '\r';
                rcdtrm[1] = '\n';
                break;

            case RRDS_RCD_TRM_NLCR:
                cRcdtrm = 2;
                rcdtrm[0] = '\n';
                rcdtrm[1] = '\r';
                break;

            default:
                cRcdtrm = 0;
                break;
        }
        if (cRcdtrm) {
            eRc = FileIO_Write(this->pIO, cRcdtrm, rcdtrm);
            if (!ERESULT_FAILED(eRc)) {
                if (lsn > this->cRecords) {
                    this->cRecords = lsn;
                }
            }
        }

        // Return to Caller.
        return eRc;
    }



    //----------------------------------------------------------------
    //      BlockOffset - calculate file offset from Record Number
    //----------------------------------------------------------------
    static
    size_t          RRDS_RecordOffset (
        RRDS_DATA       *this,
        uint32_t        recordNum
    )
    {
        size_t          fileOffset;

        fileOffset = this->recordSize * (recordNum - 1);

        // Return to Caller.
        return fileOffset;
    }



    //----------------------------------------------------------------
    //              Set up the FileIO and LRU objects
    //----------------------------------------------------------------
    ERESULT         RRDS_Setup (
        RRDS_DATA       *this
    )
    {
        ERESULT         eRc;

        RRDS_setFileIO(this, OBJ_NIL);
        this->pIO = FileIO_New( );
        if (OBJ_NIL == this->pIO) {
            DEBUG_BREAK();
            return ERESULT_OBJECT_CREATION;
        }

        eRc = lru_Setup(this->pLRU, this->recordSize, this->cLRU, this->cHash);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this->pIO);
            this->pIO = OBJ_NIL;
            return ERESULT_OBJECT_CREATION;
        }

        // Now tie the LRU object to the fileio object.
        lru_setLogicalSectorRead(this->pLRU, (void *)RRDS_LSN_Read, this);
        lru_setLogicalSectorWrite(this->pLRU, (void *)RRDS_LSN_Write, this);

        // Return to caller.
        return ERESULT_SUCCESS;
    }




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    RRDS_DATA *     RRDS_Alloc (
        void
    )
    {
        RRDS_DATA       *this;
        uint32_t        cbSize = sizeof(RRDS_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    RRDS_DATA *     RRDS_New (
        void
    )
    {
        RRDS_DATA       *this;
        
        this = RRDS_Alloc( );
        if (this) {
            this = RRDS_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                        F i l e  I / O
    //---------------------------------------------------------------

    OBJ_ID          RRDS_getFileIO (
        RRDS_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pIO;
    }


    bool            RRDS_setFileIO (
        RRDS_DATA       *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pIO) {
            obj_Release(this->pIO);
        }
        this->pIO = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //               F i l l  C h a r a c t e r
    //---------------------------------------------------------------

    uint8_t         RRDS_getFillChar (
        RRDS_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->fillChar;
    }


    bool            RRDS_setFillChar (
        RRDS_DATA       *this,
        uint8_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->fillChar = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              L R U
    //---------------------------------------------------------------

    LRU_DATA *      RRDS_getLRU (
        RRDS_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pLRU;
    }


    bool            RRDS_setLRU (
        RRDS_DATA       *this,
        LRU_DATA        *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pLRU) {
            obj_Release(this->pLRU);
        }
        this->pLRU = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P a t h
    //---------------------------------------------------------------

    PATH_DATA *     RRDS_getPath (
        RRDS_DATA       *this
    )
    {
        PATH_DATA       *pPath = OBJ_NIL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->pIO) {
            pPath = FileIO_getPath(this->pIO);
        }

        return pPath;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        RRDS_getPriority (
        RRDS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            RRDS_setPriority (
        RRDS_DATA       *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                      R e c o r d  S i z e
    //---------------------------------------------------------------

    uint16_t        RRDS_getRecordSize (
        RRDS_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->reqSize;
    }


    bool            RRDS_setRecordSize (
        RRDS_DATA       *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (OBJ_NIL == this->pIO) {
            this->reqSize = value;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        RRDS_getSize (
        RRDS_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->cRecords;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  RRDS_getSuperVtbl (
        RRDS_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
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
        ERESULT eRc = RRDS_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another RRDS object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         RRDS_Assign (
        RRDS_DATA       *this,
        RRDS_DATA       *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!RRDS_Validate(pOther)) {
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
    
    
    
    //----------------------------------------------------------------
    //                  Close - Close down an Instance
    //----------------------------------------------------------------
    /* Purpose
     *          This function terminates a System.
     * Returns
     *          Nothing
     */
    ERESULT         RRDS_Close (
        RRDS_DATA       *this,
        bool            fDelete
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if ( !RRDS_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Flush the file header.
        eRc = RRDS_FileClose(this, fDelete);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

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
    int             RRDS_Compare (
        RRDS_DATA     *this,
        RRDS_DATA     *pOther
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
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!RRDS_Validate(pOther)) {
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
        RRDS      *pCopy = RRDS_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a RRDS object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    RRDS_DATA *     RRDS_Copy (
        RRDS_DATA       *this
    )
    {
        RRDS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef RRDS_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = RRDS_New( );
        if (pOther) {
            eRc = RRDS_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //----------------------------------------------------------------
    //                  Create - Create a File
    //----------------------------------------------------------------

    ERESULT         RRDS_Create (
        RRDS_DATA       *this,
        PATH_DATA       *pPath,
        bool            fMem
    )
    {
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if ( !RRDS_Validate(this) ) {
            DEBUG_BREAK();              // Should not happen!
            return ERESULT_INVALID_OBJECT;
        }
        if ((OBJ_NIL == pPath) && !fMem) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = RRDS_Setup(this);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        // Create the file.
        eRc = FileIO_Create(this->pIO, pPath, fMem);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        eRc = FileIO_Close(this->pIO, false);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        eRc = FileIO_Open(this->pIO, pPath, fMem);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            RRDS_Dealloc (
        OBJ_ID          objId
    )
    {
        RRDS_DATA   *this = objId;
        ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((RRDS_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        // Order is important here!
        eRc = RRDS_FileClose(this, false);
        RRDS_setLRU(this, OBJ_NIL);
        RRDS_setFileIO(this, OBJ_NIL);

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
        RRDS      *pDeepCopy = RRDS_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a RRDS object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    RRDS_DATA *     RRDS_DeepyCopy (
        RRDS_DATA       *this
    )
    {
        RRDS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = RRDS_New( );
        if (pOther) {
            eRc = RRDS_Assign(this, pOther);
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
    ERESULT         RRDS_Disable (
        RRDS_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
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
    ERESULT         RRDS_Enable (
        RRDS_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
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
    //                          I n i t
    //---------------------------------------------------------------

    RRDS_DATA *   RRDS_Init (
        RRDS_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(RRDS_DATA);
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
        // in the OBJ_INFO at the end of RRDS_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_RRDS);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&RRDS_Vtbl);
#ifdef  RRDS_JSON_SUPPORT
        JsonIn_RegisterClass(RRDS_Class());
#endif

        this->pLRU = lru_New();
        if (OBJ_NIL == this->pLRU) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        lru_setLogicalSectorRead(
                                 this->pLRU,
                                 (void *)RRDS_LSN_Read,
                                 this
        );
        lru_setLogicalSectorWrite(
                                  this->pLRU,
                                 (void *)RRDS_LSN_Write,
                                 this
        );

#if defined(__MACOSX_ENV__) || defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        this->recordTerm = RRDS_RCD_TRM_NL;
        this->recordSize = 81;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        this->rcdtrm = RRDS_RCD_TRM_CRNL;
        this->recordSize = 82;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        this->rcdtrm = RRDS_RCD_TRM_NL;
        this->recordSize = 81;
#endif
        this->reqSize = 80;
        this->fillChar = ' ';
        this->cLRU = 1;
        this->cHash = 13;


#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "RRDS::sizeof(RRDS_DATA) = %lu\n", 
                sizeof(RRDS_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(RRDS_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         RRDS_IsEnabled (
        RRDS_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
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

    ERESULT         RRDS_IsOpen (
        RRDS_DATA        *this
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (FileIO_IsOpen(this->pIO)) {
            return ERESULT_SUCCESS;
        }

        // Return to caller.
        return ERESULT_GENERAL_FAILURE;
    }



    //----------------------------------------------------------------
    //                      Open - Open a File
    //----------------------------------------------------------------

    ERESULT         RRDS_Open (
        RRDS_DATA       *this,
        PATH_DATA       *pPath,
        bool            fMem
    )
    {
        ERESULT         eRc;
        uint32_t        amtRead = 0;
        off_t           offset;
        size_t          fileSize;
        uint8_t         terms[2];

        // Do initialization.
#ifdef NDEBUG
#else
        if ( !RRDS_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Set up the FileIO and LRU objects.
        eRc = RRDS_Setup(this);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        eRc = FileIO_Open(this->pIO, pPath, fMem);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        // Records may or may not have \r\n or \n at the end of them. So,
        // record size can be 80-82 bytes.
        offset = FileIO_SeekBegin(this->pIO, this->reqSize);
        if (!(offset == this->reqSize)) {
            DEBUG_BREAK();
            return ERESULT_OPEN_ERROR;
        }
        eRc = FileIO_Read(this->pIO, sizeof(terms), terms, &amtRead);
        if ((ERESULT_FAILED(eRc)) || !(amtRead == 2)) {
            DEBUG_BREAK();
            return eRc;
        }
        if (terms[0] == '\r') {
            this->recordSize = 81;
            this->recordTerm = RRDS_RCD_TRM_CR;
            if (terms[1] == '\n') {
                this->recordSize = 82;
                this->recordTerm = RRDS_RCD_TRM_CRNL;
            }
        }
        else if (terms[0] == '\n') {
            this->recordSize = 81;
            this->recordTerm = RRDS_RCD_TRM_NL;
            if (terms[1] == '\r') {
                this->recordSize = 82;
                this->recordTerm = RRDS_RCD_TRM_NLCR;
            }
        }
        else {
            this->recordSize = 80;
            this->recordTerm = RRDS_RCD_TRM_NONE;
        }

        fileSize = FileIO_Size(this->pIO);
        this->cRecords = (uint32_t)(fileSize / this->recordSize);

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
        void        *pMethod = RRDS_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "RRDS", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          RRDS_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        RRDS_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!RRDS_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(RRDS_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)RRDS_Class();
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
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return RRDS_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return RRDS_Enable;
                        }
                        break;

                    case 'P':
#ifdef  RRDS_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return RRDS_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return RRDS_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return RRDS_ToDebugString;
                        }
#ifdef  RRDS_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return RRDS_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return RRDS_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == RRDS_ToDebugString)
                    return "ToDebugString";
#ifdef  RRDS_JSON_SUPPORT
                if (pData == RRDS_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //----------------------------------------------------------------
    //              RecordBuffer - Read a Block into Memory
    //----------------------------------------------------------------

    uint8_t *       RRDS_RecordBuffer (
        RRDS_DATA       *this,
        uint32_t        recordNum,
        uint8_t         **ppData
    )
    {
        ERESULT         eRc;
        //size_t          fileOffset;
        uint8_t         *pBuffer;

        // Do initialization.
#ifdef NDEBUG
#else
        if ( !RRDS_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
        if (!FileIO_IsOpen(this->pIO)) {
            DEBUG_BREAK();
            //return ERESULT_DATA_NOT_FOUND;
            return NULL;
        }
#endif

        eRc = RRDS_RecordRead(this, recordNum, NULL);
        if (ERESULT_FAILED(eRc)) {
            return NULL;
        }

        pBuffer = (uint8_t *)lru_FindBuffer(this->pLRU, recordNum);

        // Return to caller.
        return pBuffer;
    }




    //----------------------------------------------------------------
    //              RecordRead - Read a Block into Memory
    //----------------------------------------------------------------

    ERESULT         RRDS_RecordRead (
        RRDS_DATA       *this,
        uint32_t        recordNum,
        uint8_t         *pData
    )
    {
        ERESULT         eRc;
        //size_t          fileOffset;

        // Do initialization.
#ifdef NDEBUG
#else
        if ( !RRDS_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!FileIO_IsOpen(this->pIO)) {
            DEBUG_BREAK();
            return ERESULT_DATA_NOT_FOUND;
        }
#endif
        if( recordNum == 0 ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if( recordNum > this->cRecords ) {
            return ERESULT_INVALID_PARAMETER;
        }

        // Read the Block into Memory.
        if (this->cLRU > 1) {
            eRc = lru_Read(this->pLRU, recordNum, pData);
            if (ERESULT_FAILED(eRc)) {
                return ERESULT_IO_ERROR;
            }
        }
        else {
            eRc = RRDS_LSN_Read(this, recordNum, pData);
            if (ERESULT_FAILED(eRc)) {
                return ERESULT_IO_ERROR;
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }




    //----------------------------------------------------------------
    //              RecordWrite - Write a Block to the File
    //----------------------------------------------------------------

    ERESULT         RRDS_RecordWrite (
        RRDS_DATA       *this,
        uint32_t        recordNum,
        uint8_t         *pData
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if ( !RRDS_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!FileIO_IsOpen(this->pIO)) {
            DEBUG_BREAK();
            return ERESULT_DATA_NOT_FOUND;
        }
#endif
        if( recordNum == 0 ) {
            return ERESULT_INVALID_PARAMETER;
        }
        TRC_OBJ(this, "RRDS_RecordWrite recordNum=%d\n", recordNum);

        /* Fill the File if a block is accessed beyond the end of the
         * File.
         */
        if( recordNum > (this->cRecords + 1) ) {
            TRC_OBJ(
                    this,
                    "\tfile too short, extending from %d to %d\n",
                    this->cRecords,
                    recordNum
            );
            if( RRDS_FileExtend( this, (recordNum - 1) ) )
                ;
            else {
                return ERESULT_IO_ERROR;
            }
        }

        // Write the Block to the File.
        if (this->cLRU > 1) {
            TRC_OBJ(this, "\tLRU write...\n");
            eRc = lru_Write(this->pLRU, recordNum, pData);
            if (ERESULT_FAILED(eRc)) {
                TRC_OBJ(this, "\tLRU write error!\n");
                return ERESULT_IO_ERROR;
            }
            TRC_OBJ(this, "\tLRU write completed\n");
        }
        else {
            TRC_OBJ(this, "\tRRDS write...\n");
            eRc = RRDS_LSN_Write(this, recordNum, pData);
            if (ERESULT_FAILED(eRc)) {
                TRC_OBJ(this, "\tRRDS write error!\n");
                return ERESULT_IO_ERROR;
            }
            TRC_OBJ(this, "\tRRDS write completed\n");
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }




    //----------------------------------------------------------------
    //              Set up the FileIO and LRU objects
    //----------------------------------------------------------------
    ERESULT         RRDS_SetupSizes (
        RRDS_DATA       *this,
        uint16_t        recordSize,     // Requested Record Size
        uint16_t        recordTerm,     // Record Terminator Type
        //                              // (See RRDS_rcd_trm_e above)
        uint16_t        cLRU,           // Number of LRU Buffers
        uint16_t        cHash           // Number of LRU Hash Chains
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if ( !RRDS_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (0 == cLRU) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        this->reqSize = recordSize;
        this->recordTerm = recordTerm;
        this->cLRU = cLRU;
        this->cHash = cHash;
        switch (recordTerm) {
            case RRDS_RCD_TRM_NONE:
                this->recordSize = recordSize;
                break;

            case RRDS_RCD_TRM_CR:
                this->recordSize = recordSize + 1;
                break;

            case RRDS_RCD_TRM_NL:
                this->recordSize = recordSize + 1;
                break;

            case RRDS_RCD_TRM_CRNL:
                this->recordSize = recordSize + 2;
                break;

            case RRDS_RCD_TRM_NLCR:
                this->recordSize = recordSize + 2;
                break;

            default:
                this->recordSize = recordSize;
                break;
        }

        eRc = lru_Setup(this->pLRU, this->recordSize, cLRU, cHash);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_OBJECT_CREATION;
        }

        // Now tie the LRU object to the fileio object.
        lru_setLogicalSectorRead(this->pLRU, (void *)RRDS_LSN_Read, this);
        lru_setLogicalSectorWrite(this->pLRU, (void *)RRDS_LSN_Write, this);

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
        ASTR_DATA      *pDesc = RRDS_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     RRDS_ToDebugString (
        RRDS_DATA      *this,
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
        if (!RRDS_Validate(this)) {
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
                    RRDS_getSize(this),
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
    bool            RRDS_Validate (
        RRDS_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_RRDS))
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


        if (!(obj_getSize(this) >= sizeof(RRDS_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


