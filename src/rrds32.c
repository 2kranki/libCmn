// vi:nu:et:sts=4 ts=4 sw=4

/****************************************************************/
/*          File Block I/O System (FBS) Support Routines        */
/****************************************************************/
/*
 * Program
 *              File Block I/O System (FBS) Subroutines
 * Purpose
 *              See FBS.H for a description of these routines.
 * Todo List
 *  --          Add data buffering???
 *  --          Finish Documentation (inc Error Codes ).
 * Remarks
 *              None
 * History
 *              See RRDS.H for the history.
 * References
 *              See RRDS.H for the references.
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




/****************************************************************
* * * * * * * * * * * *  data definitions   * * * * * * * * * * *
****************************************************************/

/* Header File Inclusion */
#include	<rrds32_internal.h>



/****************************************************************
* * * * * * * * * * * *  data definitions   * * * * * * * * * * *
****************************************************************/





/****************************************************************
* * * * * * * * * * *  Internal Subroutines * * * * * * * * * * *
****************************************************************/


/* Local function declarations
 */
static
bool            rrds32_FileClose(
    int             fileHandle
);

static
bool            rrds32_FileCreate(
    const
    char            *pFileName,
    int             *pFileHandle
);

static
bool            rrds32_FileDelete(
    const
	char            *pFileName
);

static
bool            rrds32_FileExtend(
	RRDS32_DATA        *cbp,
	uint32_t         Block           /* Block to extend to */
);

static
bool            rrds32_FileOpen(
    const
    char            *pFilePath,
	int             *pFileHandle
);

static
bool            rrds32_FileRead(
    int             fileHandle,
    size_t          offset,
	uint16_t        cBuffer,
	void            *pBuffer
);

static
bool            rrds32_FileWrite(
    int             fileHandle,
	size_t          offset,
	uint16_t        cBuffer,
	void            *pBuffer
);

#ifdef NDEBUG
#else
static
bool            rrds32_Validate(
    RRDS32_DATA        *cbp
);
#endif





//----------------------------------------------------------------
//      uint32_hash - calculate a hash for a 32 bit number
//----------------------------------------------------------------

#ifdef XYZZY
static
uint32_t        uint32_hash(
    uint32_t        x
)
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x);
    return x;
}
#endif



//----------------------------------------------------------------
//      BlockOffset - calculate file offset from Record Number
//----------------------------------------------------------------
static
size_t          rrds32_RecordOffset(
    RRDS32_DATA    *this,
    uint32_t       recordNum
)
{
    size_t          fileOffset;
    
    fileOffset = (this->recordSize * (recordNum-1)) + RRDS32_HEADER_SIZE;
    
	// Return to Caller.
	return fileOffset;
}



//----------------------------------------------------------------
//                  Construct the LRU Buffers
//----------------------------------------------------------------

#ifdef XYZZY
static
bool            rrds32_ConstructLruBuffers(
    RRDS32_DATA      *this
)
{
    uint32_t        i;
    uint8_t         *pBuffer;
    
    if (0 == this->cBuffers) {
        return false;
    }
    if (0 == this->recordSize) {
        return false;
    }
    
    if (NULL == this->pBuffers) {
        this->pBuffers = mem_Malloc(this->recordSize * this->cBuffers);
        if (NULL == this->pBuffers) {
            return false;
        }
    }
    
    pBuffer = this->pBuffers;
    for (i=0; i<this->cBuffers; ++i) {
        this->pLruTable[i].pBuffer = pBuffer;
        pBuffer += this->recordSize;
    }
    
	return true;
}
#endif



//----------------------------------------------------------------
//                  Destruct the LRU Buffers
//----------------------------------------------------------------

#ifdef XYZZY
static
bool            rrds32_DestructLruBuffers(
    RRDS32_DATA      *this
)
{
    uint32_t        i;
    
    if (this->pBuffers) {
        mem_Free(this->pBuffers);
        this->pBuffers = NULL;
    }
    
    for (i=0; i<this->cBuffers; ++i) {
        this->pLruTable[i].pBuffer = NULL;
    }
    
	return true;
}
#endif



//----------------------------------------------------------------
//                  rrds_FileClose - Close a File
//----------------------------------------------------------------
/* Purpose
 *          This function closes a File.
 * Returns
 *          RRDS_OK          =   Successful Completion
 *          RRDS_ERROR_OPEN  =   Disk File Close Error
 */
static
bool            rrds32_FileClose(
	int             fileHandle
)
{

	//  Close the File.
    fileHandle = close(fileHandle);
    if (fileHandle == -1) {
		return false;
    }

	// Return to Caller.
	return true;
}



//----------------------------------------------------------------
//              rrds_FileCreate - Create and Open a File
//----------------------------------------------------------------
/* Purpose
 *      This function creates a new file over-writing an existing
 *      one if present.
 * Returns
 *          RRDS_OK          =   Successful Completion
 *          RRDS_ERROR_OPEN  =   Disk File Open Error
 */
static
bool            rrds32_FileCreate(
    const
    char            *pFilePath,
    int             *pFileHandle
)
{
    int             fileHandle;
    
	//  Open the File.
    fileHandle = open(pFilePath, (O_CREAT | O_TRUNC | O_RDWR), 0644);
	if( -1 == fileHandle ) {
		return false;
    }
    else {
        *pFileHandle = fileHandle;
    }
    
	// Return to Caller.
	return true;
}



//----------------------------------------------------------------
//               rrds32_FileDelete - Delete a File
//----------------------------------------------------------------
/* Purpose
 *          This function deletes a File.
 * Returns
 *          RRDS_OK              =   Successful Completion
 *          RRDS_ERROR_DELETE    =   Disk File Deletion Error
 */
static
bool            rrds32_FileDelete(
    const
	char            *pFileName
)
{
    int             iRc;

	//  Delete the File.
	iRc = unlink( pFileName );
	if( iRc == 0 )
		;
	else
		return false;

	// Return to Caller.
	return true;
}



//----------------------------------------------------------------
//      rrds_FileExtend - Extend the File with Zeroed Records 
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
bool            rrds32_FileExtend(
	RRDS32_DATA     *cbp,
	uint32_t        recordNum           /* Record to extend to */
)
{
	uint32_t        curRec;
	size_t          fileOffset;
	char            *pFillData;
    bool            fRc;

	// Fill the File until Block number of records exist.
	if( recordNum > cbp->recordNum ) {

        pFillData = (char *)mem_Malloc(cbp->recordSize);
		if( NULL == pFillData ) {
			return false;
        }
        memset(pFillData,cbp->header.data.fillChar,cbp->recordSize);

		for( curRec=cbp->recordNum+1; curRec<=recordNum; ++curRec ) {
			fileOffset = rrds32_RecordOffset(cbp, curRec);
			fRc = rrds32_FileWrite( cbp->fileHandle,
								fileOffset,
								cbp->recordSize,
								pFillData
				 );
			if( !fRc ) {
                mem_Free(pFillData);
				return false;
			}
		}
        mem_Free(pFillData);
        pFillData = NULL;
        cbp->recordNum = recordNum;
	}

	// Return to Caller.
	return true;
}



//----------------------------------------------------------------
//                  rrds_FileOpen - Open a File
//----------------------------------------------------------------
/* Purpose
 *          This function opens an existing file for reading,
 *          writing and appending.
 * Returns
 *          RRDS_OK          =   Successful Completion
 *          RRDS_ERROR_OPEN  =   Disk File Open Error
 */
static
bool            rrds32_FileOpen(
    const
    char            *pFilePath,
	int             *pFileHandle
)
{
    int             fileHandle;

	//  Open the File.
    fileHandle = open(
                      pFilePath,
                      (O_APPEND | O_RDWR),
                      (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
                );
	if( -1 == fileHandle ) {
		return false;
    }
    else {
        *pFileHandle = fileHandle;
    }

	// Return to Caller.
	return true;
}



//----------------------------------------------------------------
// rrds_FileRead - Read a portion of the File into a Memory Area
//----------------------------------------------------------------
/* Purpose
 *          This function reads a portion of the File into a
 *          Memory Area specified by the Caller.
 * Returns
 *          RRDS_OK          =   Successful Completion
 *          RRDS_ERROR_READ  =   Disk Write Error
 *          RRDS_ERROR_SEEK  =   Disk Seek Error
 */
static
bool            rrds32_FileRead(
	int             fileHandle,
	size_t          offset,
	uint16_t        cBuffer,
	void            *pBuffer
)
{
	size_t          fileOffset;
    size_t          bytes_read;

	//  Position within the File.
	fileOffset = lseek(fileHandle, offset, SEEK_SET);
	if( fileOffset == -1 ) {
		return( false );
    }

	// Read in the area.
    bytes_read = read(fileHandle, pBuffer, cBuffer);
    if (-1 == bytes_read) {
        return false;
    }
	if( bytes_read == cBuffer )
		;
	else
		return false;

	// Return to Caller.
	return true;
}




//----------------------------------------------------------------
//      rrds_FileWrite - Write a Memory Area into the File
//----------------------------------------------------------------
/* Purpose
 *          This function writes a Memory Area into the File.
 * Returns
 *          RRDS_OK          =   Successful Completion
 *          RRDS_ERROR_SEEK  =   Disk Seek Error
 *          RRDS_ERROR_WRITE =   Disk Write Error
 */
static
bool            rrds32_FileWrite(
	int             fileHandle,     
	size_t          offset,
	uint16_t        cBuffer,
	void            *pBuffer
)
{
	size_t          fileOffset;
    size_t          bytes_written;

	//  Position within the File.
	fileOffset = lseek(fileHandle, offset, SEEK_SET);
	if( fileOffset == -1 ) {
		return( false );
    }
    
	// Write the data.
    bytes_written = write(fileHandle, pBuffer, cBuffer);
    if (bytes_written == -1) {
        perror("write error: ");
        return false;
    }
	if( bytes_written == cBuffer )
		;
	else
		return( false );
    
	// Return to Caller.
	return( true );
}








/****************************************************************
* * * * * * * * * * *  External Subroutines * * * * * * * * * * *
****************************************************************/


//===============================================================
//                      *** Class Methods ***
//===============================================================

//---------------------------------------------------------------
//                        A l l o c
//---------------------------------------------------------------

RRDS32_DATA *      rrds32_Alloc(
)
{
    RRDS32_DATA        *cbp;
    uint32_t        cbSize;
    
    // Do initialization.
    
    cbSize = sizeof(RRDS32_DATA);
    
    cbp = obj_Alloc( cbSize );
    
    // Return to caller.
    return( cbp );
}





//===============================================================
//                    P r o p e r t i e s
//===============================================================

//----------------------------------------------------------------
//          getBlkNum - Get the Number of Blocks in the File
//----------------------------------------------------------------

uint32_t         rrds32_getBlkNum(
    RRDS32_DATA 		*cbp
)
{
    
	/* Do initialization.
	 */
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(cbp) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
	/* Return to caller.
	 */
	return( cbp->recordNum );
}




//----------------------------------------------------------------
//              getRecordSize - Get the Record Size
//----------------------------------------------------------------

uint16_t        rrds32_getRecordSize(
    RRDS32_DATA        *cbp
)
{
    
	/* Do initialization.
	 */
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(cbp) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
	// Return to caller.
	return( cbp->recordSize );
}



//----------------------------------------------------------------
//              getFillChar - Get the Fill Character
//----------------------------------------------------------------

char            rrds32_getFillChar(
    RRDS32_DATA       *this
)
{
    
	/* Do initialization.
	 */
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
	// Return to caller.
	return( this->header.data.fillChar );
}


bool            rrds32_setFillChar(
    RRDS32_DATA       *this,
    char            value
)
{
    
    /* Do initialization.
     */
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return false;
    }
#endif
    
    this->header.data.fillChar = value;

    
    // Return to caller.
    return true;
}



ERESULT         rrds32_getLastError(
    RRDS32_DATA     *this
)
{
    
    // Validate the input parameters.
#ifdef NDEBUG
#else
    if( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return this->eRc;
    }
#endif
    
    //this->eRc = ERESULT_SUCCESS;
    return this->eRc;
}


bool            rrds32_setLastError(
    RRDS32_DATA     *this,
    ERESULT         value
)
{
#ifdef NDEBUG
#else
    if( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return false;
    }
#endif
    
    this->eRc = value;
    
    return true;
}



//----------------------------------------------------------------
//              getUserSize - Get the User Area Size
//----------------------------------------------------------------

uint16_t        rrds32_getUserSize(
    RRDS32_DATA        *cbp
)
{
    uint16_t        size = RRDS32_HEADER_SIZE;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(cbp) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
    size -= sizeof(cbp->header.data);
    
	// Return to caller.
	return( size );
}




//----------------------------------------------------------------
//          getUserPtr - Get a pointer to the User Area
//----------------------------------------------------------------

uint8_t *       rrds32_getUserPtr(
    RRDS32_DATA        *cbp
)
{
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(cbp) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
	// Return to caller.
	return( (uint8_t *)&cbp->header.data.userData );
}






//===============================================================
//                    M e t h o d s
//===============================================================


//----------------------------------------------------------------
//              BlockRead - Read a Block into Memory
//----------------------------------------------------------------

ERESULT         rrds32_BlockRead(
	RRDS32_DATA     *this,
	uint32_t        recordNum,
	uint8_t         *pData
)
{
	size_t          fileOffset;

	// Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return this->eRc;
    }
#endif
    if( recordNum == 0 ) {
        this->eRc = ERESULT_INVALID_PARAMETER;
        return this->eRc;
    }
    if( recordNum > this->recordNum ) {
        this->eRc = ERESULT_INVALID_PARAMETER;
        return this->eRc;
    }

	// Read the Block into Memory.
    fileOffset = rrds32_RecordOffset(this, recordNum);
    if ( !rrds32_FileRead(this->fileHandle, fileOffset, this->recordSize, pData) ) {
        this->eRc = ERESULT_IO_ERROR;
        return this->eRc;
    }

	// Return to caller.
    this->eRc = ERESULT_SUCCESS;
    return this->eRc;
}




//----------------------------------------------------------------
//              BlockWrite - Write a Block to the File
//----------------------------------------------------------------

ERESULT         rrds32_BlockWrite(
	RRDS32_DATA     *this,
	uint32_t        recordNum,
	uint8_t         *pData
)
{
	size_t          fileOffset;

	// Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return this->eRc;
    }
#endif
    if( recordNum == 0 ) {
        this->eRc = ERESULT_INVALID_PARAMETER;
		return this->eRc;
    }

	/* Fill the File if a block is accessed beyond the end of the
	 * File.
	 */
	if( recordNum > this->recordNum+1 ) {
		if( rrds32_FileExtend( this, recordNum-1 ) )
			;
        else {
            this->eRc = ERESULT_IO_ERROR;
            return this->eRc;
        }
	}

	// Write the Block to the File.
    fileOffset = rrds32_RecordOffset(this, recordNum);
	if( pData ) {
		if ( rrds32_FileWrite(this->fileHandle, fileOffset, this->recordSize, pData) ) {
			if( recordNum > this->recordNum ) {
				this->recordNum = recordNum;
            }
		}
        else {
            this->eRc = ERESULT_IO_ERROR;
            return this->eRc;
        }
	}
	else {
        if ( !rrds32_FileExtend(this, recordNum) ) {
            this->eRc = ERESULT_IO_ERROR;
            return this->eRc;
        }
	}

	// Return to caller.
    this->eRc = ERESULT_SUCCESS;
	return this->eRc;
}




//----------------------------------------------------------------
//                  Close - Close down an Instance
//----------------------------------------------------------------
/* Purpose
 *          This function terminates a System.
 * Returns
 *          Nothing
 */
ERESULT         rrds32_Close(
	RRDS32_DATA     *this
)
{
    bool            fRc;
    uint32_t        i;
    size_t          offset;

	// Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return this->eRc;
    }
#endif

	/* Flush and Close the File.
	 */
	if( this->fileHandle ) {

        // Flush the LRU Buffers.
        for (i=0; i<this->cBuffers; ++i) {
            if (this->pLruTable[i].key && this->pLruTable[i].pBuffer) {
                offset = rrds32_RecordOffset(this, this->pLruTable[i].key);
                fRc = rrds32_FileWrite(
                                    this->fileHandle,
                                    offset,
                                    this->recordSize,
                                    this->pLruTable[i].pBuffer
                        );
            }
        }
        
		// Flush the header buffer.
        this->header.data.recordNum = this->recordNum;
        fRc = rrds32_FileWrite( this->fileHandle, 0, RRDS32_HEADER_SIZE, &this->header );
        if( !fRc ) {
            this->eRc = ERESULT_IO_ERROR;
            return this->eRc;
        }

		// Close the file.
		fRc = rrds32_FileClose( this->fileHandle );
		if( !fRc ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_IO_ERROR;
            return this->eRc;
        }
		this->fileHandle = 0;
	}

	// Free the control blocks.
	if( this->pFilePath ) {
		mem_Free((void *)this->pFilePath);
		this->pFilePath = NULL;
	}

	// Return to caller.
    this->eRc = ERESULT_SUCCESS;
	return ERESULT_SUCCESS;
}




//----------------------------------------------------------------
//                  Create - Create a File
//----------------------------------------------------------------

ERESULT         rrds32_Create(
    RRDS32_DATA     *this,
    const
	char            *pFilePath,
    uint16_t        recordSize,
    uint16_t        headerSize
)
{
    bool            fRc;

#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();              // Should not happen!
        return this->eRc;
    }
    if (0 == (recordSize & 0x3))
        ;
    else {
        this->eRc = ERESULT_INVALID_PARAMETER;
        return this->eRc;
    }
    if (0 == (headerSize & 0x3))
        ;
    else {
        this->eRc = ERESULT_INVALID_PARAMETER;
        return this->eRc;
    }
#endif
    
    this->recordSize  = recordSize;

	// Open the file.
	this->pFilePath = (char *)mem_StrDup( pFilePath );
	if( NULL == this->pFilePath ) {
        this->eRc = ERESULT_OUT_OF_MEMORY;
		return ERESULT_OUT_OF_MEMORY;
	}
	fRc = rrds32_FileCreate( this->pFilePath, &this->fileHandle );
	if( !fRc ) {
		mem_Free( (void *)this->pFilePath );
		this->pFilePath = NULL;
        this->eRc = ERESULT_OPEN_ERROR;
		return this->eRc;
	}
    
    this->header.data.cbSize  = RRDS32_HEADER_SIZE;
    this->header.data.cbIdent = RRDS32_HEADER_IDENTIFIER;
    this->header.data.recordSize = this->recordSize;

	// Return to caller.
    this->eRc = ERESULT_SUCCESS;
	return this->eRc;
}




//----------------------------------------------------------------
//                    D e a l l o c
//----------------------------------------------------------------

void            rrds32_Dealloc(
    OBJ_ID          objId
)
{
	RRDS32_DATA		*this = objId;
    bool            fRc;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return;
    }
#endif
    
    if (this->fileHandle) {
        fRc = rrds32_Close(this);
    }
    
    if (this->pBuffers) {
        mem_Free(this->pBuffers);
        this->pBuffers = NULL;
    }
    
    if (this->pHash) {
        obj_Release(this->pHash);
        this->pHash = OBJ_NIL;
    }
    
    if (this->pLruTable) {
        mem_Free(this->pLruTable);
        this->pLruTable = NULL;
    }
    
    obj_Dealloc(this);
    this = NULL;
    
	// Return to caller.
}



//----------------------------------------------------------------
//      Destroy - Close down an Instance deleting the file
//----------------------------------------------------------------

ERESULT         rrds32_Destroy(
	RRDS32_DATA     *this
)
{
    bool            fRc;

	// Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return this->eRc;
    }
#endif


	// Flush and Close the File.
	if( this->fileHandle ) {
		// Close the file.
		fRc = rrds32_FileClose( this->fileHandle );
		if( !fRc ) {
            this->eRc = ERESULT_CLOSE_ERROR;
            return this->eRc;
        }
		this->fileHandle = 0;
	}

	// Delete the file if necessary.
	if( this->pFilePath ) {
		fRc = rrds32_FileDelete( this->pFilePath );
		if( !fRc ) {
			return false;
        }
		mem_Free( (void *)this->pFilePath );
		this->pFilePath = NULL;
	}

	return ERESULT_SUCCESS;
}



//----------------------------------------------------------------
//                      Init - Initialize the object
//----------------------------------------------------------------

RRDS32_DATA *		rrds32_Init(
    RRDS32_DATA     *this,
    uint16_t        cLRU            // Number of LRU Buffers
)
{
    uint32_t        cbSize = sizeof(RRDS32_DATA);
    uint16_t        i;
    
#ifdef NDEBUG
#else
    if ( (0 == cLRU) || (cLRU > 2) )
        ;
    else {
        DEBUG_BREAK();
        return NULL;
    }
#endif
    
    if (OBJ_NIL == this) {
        return OBJ_NIL;
    }
    
    cbSize = obj_getSize(this);
    this = obj_Init( this, cbSize, OBJ_IDENT_RRDS32 );
    if (OBJ_NIL == this) {
        return OBJ_NIL;
    }
    //obj_setSize(this, cbSize);         // Needed for Inheritance
    //obj_setIdent((OBJ_ID)this, OBJ_IDENT_RRDS32);
    this->pSuperVtbl = obj_getVtbl(this);
    obj_setVtbl(this, (OBJ_IUNKNOWN *)&rrds32_Vtbl);
    
    this->cBuffers = cLRU;
    if (cLRU) {
        this->pLruTable = (LRU_ENTRY *)mem_Malloc(cLRU * sizeof(LRU_ENTRY));
        if (NULL == this->pLruTable) {
            obj_Release(this);
            return OBJ_NIL;
        }
    }
    
    // Set up the LRU Buffers.
    listdl_Init(&this->lru, offsetof(LRU_ENTRY, lru));
    listdl_Init(&this->lruFree, offsetof(LRU_ENTRY, lru));
    for (i=0; i<this->cBuffers; ++i) {
        listdl_Add2Head( &this->lruFree, &this->pLruTable[this->cBuffers-i] );
    }
    this->pHash = hash32_Alloc();
    this->pHash = hash32_Init(this->pHash,HASH32_TABLE_SIZE_XXXSMALL);
    if (OBJ_NIL == this->pHash) {
        DEBUG_BREAK();
        obj_Release(this);
        return OBJ_NIL;
        
    }
    
#ifdef NDEBUG
#else
    BREAK_NOT_BOUNDARY4(&this->header);
    BREAK_NOT_BOUNDARY4(&this->header.data.userData);
    BREAK_NOT_BOUNDARY4(&this->pLruTable);
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return this;
    }
#endif
    
	// Return to caller.
	return this;
}




//----------------------------------------------------------------
//                      Open - Open a File
//----------------------------------------------------------------

ERESULT         rrds32_Open(
    RRDS32_DATA     *this,
    const
	char			*pFilePath
)
{
    bool            fRc;

	// Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return this->eRc;
    }
#endif    
    if( pFilePath == NULL ) {
        this->eRc = ERESULT_INVALID_PARAMETER;
		return this->eRc;
    }

	// Open the file.
	this->pFilePath = (char *)mem_StrDup( pFilePath );
	if( this->pFilePath == NULL ) {
        this->eRc = ERESULT_OUT_OF_MEMORY;
        return this->eRc;
	}
	fRc = rrds32_FileOpen( pFilePath, &this->fileHandle );
	if( !fRc ) {
		(void)rrds32_Close(this);
        this->eRc = ERESULT_OPEN_ERROR;
        return this->eRc;
	}

	// Read in the Header.
	fRc = rrds32_FileRead( this->fileHandle, 0, RRDS32_HEADER_SIZE, &this->header );
	if( !fRc ) {
		(void)rrds32_Close(this);
        this->eRc = ERESULT_IO_ERROR;
        return this->eRc;
	}
    this->recordNum  = this->header.data.recordNum;
    this->recordSize = this->header.data.recordSize;
    
	// Return to caller.
    this->eRc = ERESULT_SUCCESS;
	return ERESULT_SUCCESS;
}



//---------------------------------------------------------------
//                       T o  S t r i n g
//---------------------------------------------------------------

ASTR_DATA *     rrds32_ToDebugString(
    RRDS32_DATA     *this,
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
        AStr_AppendCharRepeatW(pStr, indent, ' ');
    }
    str[0] = '\0';
    j = snprintf(
                 str,
                 sizeof(str),
                 "{%p(rrds) ",
                 this
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
    
    j = snprintf( str, sizeof(str), " %p}\n", this );
    AStr_AppendA(pStr, str);
    
    return pStr;
}



//----------------------------------------------------------------
//                          V a l i d a t e
//----------------------------------------------------------------

#ifdef NDEBUG
#else
bool			rrds32_Validate(
    RRDS32_DATA        *this
)
{
    
    // WARNING: We have established that we have a valid pointer
    // in this yet.
    if( this ) {
        if ( obj_IsKindOf(this,OBJ_IDENT_RRDS32) )
            ;
        else
            return false;
    }
    else
        return false;
    // Now, we have validated that we have a valid pointer in
    // this.
    
    
    if( !(obj_getSize(this) >= sizeof(RRDS32_DATA)) ) {
        this->eRc = ERESULT_INVALID_OBJECT;
        return false;
    }
    
    // Return to caller.
    this->eRc = ERESULT_SUCCESS;
    return true;
}
#endif









