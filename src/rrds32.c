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
bool            rrds32_FileExtend(
	RRDS32_DATA      *this,
	uint32_t         lsn                /* Block to extend to */
);
static
ERESULT         rrds32_Header_Read(
    RRDS32_DATA     *this,
    RRDS32_HEADER   *pBuffer
);
static
ERESULT         rrds32_Header_Write(
    RRDS32_DATA     *this
);
static
ERESULT         rrds32_LSN_Read(
    RRDS32_DATA    *this,
    uint32_t       recordNum,
    uint8_t        *pBuffer
);
static
ERESULT         rrds32_LSN_Write(
    RRDS32_DATA    *this,
    uint32_t       recordNum,
    uint8_t        *pBuffer
);
static
size_t          rrds32_RecordOffset(
    RRDS32_DATA    *this,
    uint32_t       recordNum
);




//----------------------------------------------------------------
//                      F i l e  C l o s e
//----------------------------------------------------------------
static
ERESULT         rrds32_FileClose(
    RRDS32_DATA     *this,
    bool            fDelete
)
{
    ERESULT         eRc;
    
    if (this->pIO && fileio_IsOpen(this->pIO)) {
        // Flush the file header.
        eRc = rrds32_Header_Write(this);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        
        // Close the file.
        eRc = fileio_Close(this->pIO, fDelete);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        
    }
    
    if (this->pLRU) {
        obj_Release(this->pLRU);
        this->pLRU = OBJ_NIL;
    }
    
    if (this->pIO) {
        obj_Release(this->pIO);
        this->pIO = OBJ_NIL;
    }
    
    if (this->pHeader) {
        mem_Free(this->pHeader);
        this->pHeader = NULL;
    }
    
    // Return to Caller.
    return ERESULT_SUCCESS;
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
	RRDS32_DATA     *this,
	uint32_t        recordNum           /* Record to extend to */
)
{
    ERESULT         eRc;
	uint32_t        curRec;
	size_t          fileOffset;
	uint8_t         *pFillData;

	// Fill the File until Block number of records exist.
	if( recordNum > this->pHeader->recordNum ) {

        pFillData = (uint8_t *)mem_Malloc(this->pHeader->recordSize);
		if( NULL == pFillData ) {
			return false;
        }
        memset(pFillData, this->pHeader->fillChar, this->pHeader->recordSize);

		for(curRec=(this->pHeader->recordNum + 1); curRec<=recordNum; ++curRec) {
			fileOffset = rrds32_RecordOffset(this, curRec);
			eRc = rrds32_LSN_Write(
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
        this->pHeader->recordNum = recordNum;
	}

	// Return to Caller.
	return true;
}



//----------------------------------------------------------------
//                      R e a d  H e a d e r
//----------------------------------------------------------------
static
ERESULT         rrds32_Header_Read(
    RRDS32_DATA     *this,
    RRDS32_HEADER   *pBuffer
)
{
    ERESULT         eRc;
    off_t           fileOffset = 0;
    off_t           seekOffset;
    
    // Seek to the appropriate location within the file.
    seekOffset = fileio_Seek(this->pIO, fileOffset);
    if (seekOffset == fileOffset)
        ;
    else {
        DEBUG_BREAK();
        rrds32_setLastError(this, ERESULT_SEEK_ERROR);
        return -1;
    }
    
    // Read the data.
    eRc = fileio_Read(this->pIO, this->headerSize, pBuffer);
    
    // Return to Caller.
    rrds32_setLastError(this, eRc);
    return eRc;
}



//----------------------------------------------------------------
//                  W r i t e  H e a d e r
//----------------------------------------------------------------
static
ERESULT         rrds32_Header_Write(
    RRDS32_DATA     *this
)
{
    ERESULT         eRc;
    off_t           fileOffset = 0;
    off_t           seekOffset;
    
    // Seek to the appropriate location within the file.
    seekOffset = fileio_Seek(this->pIO, fileOffset);
    if (seekOffset == fileOffset)
        ;
    else {
        DEBUG_BREAK();
        rrds32_setLastError(this, ERESULT_SEEK_ERROR);
        return -1;
    }
    
    // Read the data.
    eRc = fileio_Write(this->pIO, this->headerSize, this->pHeader);
    
    // Return to Caller.
    rrds32_setLastError(this, eRc);
    return eRc;
}



//----------------------------------------------------------------
//              R e a d  D a t a  U s i n g  L S N
//----------------------------------------------------------------
static
ERESULT         rrds32_LSN_Read(
    RRDS32_DATA     *this,
    uint32_t        lsn,
    uint8_t         *pBuffer
)
{
    ERESULT         eRc;
    off_t           fileOffset;
    off_t           seekOffset;

    // Seek to the appropriate location within the file.
    fileOffset = rrds32_RecordOffset(this,lsn);
    seekOffset = fileio_Seek(this->pIO, fileOffset);
    if (seekOffset == fileOffset)
        ;
    else {
        DEBUG_BREAK();
        rrds32_setLastError(this, ERESULT_SEEK_ERROR);
        return -1;
    }
    
    // Read the data.
    eRc = fileio_Read(this->pIO, this->pHeader->recordSize, pBuffer);

    // Return to Caller.
    rrds32_setLastError(this, eRc);
    return eRc;
}



//----------------------------------------------------------------
//              W r i t e  D a t a  U s i n g  L S N
//----------------------------------------------------------------
static
ERESULT         rrds32_LSN_Write(
    RRDS32_DATA     *this,
    uint32_t        lsn,
    uint8_t         *pBuffer
)
{
    ERESULT         eRc;
    off_t           fileOffset = lsn;
    off_t           seekOffset;
    
    // Seek to the appropriate location within the file.
    fileOffset = rrds32_RecordOffset(this, lsn);
    seekOffset = fileio_Seek(this->pIO, fileOffset);
    if (seekOffset == fileOffset)
        ;
    else {
        DEBUG_BREAK();
        rrds32_setLastError(this, ERESULT_SEEK_ERROR);
        return -1;
    }
    
    // Write the data.
    eRc = fileio_Write(this->pIO, this->pHeader->recordSize, pBuffer);
    if (!ERESULT_FAILED(eRc)) {
        if (lsn > this->pHeader->recordNum)
            this->pHeader->recordNum = lsn;
    }
    
    // Return to Caller.
    rrds32_setLastError(this, eRc);
    return eRc;
}



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
    
    fileOffset = (this->pHeader->recordSize * (recordNum-1)) + this->pHeader->cbSize;
    
    // Return to Caller.
    return fileOffset;
}



//----------------------------------------------------------------
//              Set up the FileIO and LRU objects
//----------------------------------------------------------------
ERESULT         rrds32_Setup(
    RRDS32_DATA     *this,
    PATH_DATA       *pPath,
    uint16_t        cLRU,           // Number of LRU Buffers
    uint16_t        recordSize,
    uint16_t        headerSize
)
{
    this->pIO = fileio_New(pPath);
    if (OBJ_NIL == this->pIO) {
        DEBUG_BREAK();
        rrds32_setLastError(this, ERESULT_OBJECT_CREATION);
        return ERESULT_OBJECT_CREATION;
    }
    
    this->pLRU = lru_New(recordSize, cLRU);
    if (OBJ_NIL == this->pLRU) {
        DEBUG_BREAK();
        rrds32_setLastError(this, ERESULT_OBJECT_CREATION);
        return ERESULT_OBJECT_CREATION;
    }
    
    // Now tie the LRU object to the fileio object.
    lru_setLogicalSectorRead(this->pLRU, (void *)rrds32_LSN_Read, this);
    lru_setLogicalSectorWrite(this->pLRU, (void *)rrds32_LSN_Write, this);
    
    this->headerSize = headerSize;
    if (this->pHeader) {
        this->pHeader->recordSize = recordSize;
    }
    
    // Return to caller.
    rrds32_setLastError(this, ERESULT_SUCCESS);
    return ERESULT_SUCCESS;
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

RRDS32_DATA *   rrds32_Alloc(
)
{
    RRDS32_DATA     *this;
    uint32_t        cbSize = sizeof(RRDS32_DATA);
    
    // Do initialization.
    
    this = obj_Alloc( cbSize );
    
    // Return to caller.
    return this;
}



//---------------------------------------------------------------
//                          N e w
//---------------------------------------------------------------

RRDS32_DATA *   rrds32_New(
)
{
    RRDS32_DATA     *this;
    
    // Do initialization.
    
    this = rrds32_Alloc( );
    if (this) {
        this = rrds32_Init(this);
    }
    
    // Return to caller.
    return this;
}





//===============================================================
//                    P r o p e r t i e s
//===============================================================

//----------------------------------------------------------------
//      getRecordNum - Get the Number of Blocks in the File
//----------------------------------------------------------------

uint32_t         rrds32_getRecordNum(
    RRDS32_DATA 		*this
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
    
	/* Return to caller.
	 */
	return( this->pHeader->recordNum );
}




//----------------------------------------------------------------
//              getRecordSize - Get the Record Size
//----------------------------------------------------------------

uint16_t        rrds32_getRecordSize(
    RRDS32_DATA        *this
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
	return( this->pHeader->recordSize );
}



//----------------------------------------------------------------
//              getFillChar - Get the Fill Character
//----------------------------------------------------------------

char            rrds32_getFillChar(
    RRDS32_DATA     *this
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
	return( this->pHeader->fillChar );
}


bool            rrds32_setFillChar(
    RRDS32_DATA     *this,
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
    
    this->pHeader->fillChar = value;

    
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
    RRDS32_DATA        *this
)
{
    uint16_t        size = RRDS32_HEADER_SIZE;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
    size -= offsetof(RRDS32_HEADER, userData);
    
	// Return to caller.
	return( size );
}




//----------------------------------------------------------------
//          getUserPtr - Get a pointer to the User Area
//----------------------------------------------------------------

uint8_t *       rrds32_getUserPtr(
    RRDS32_DATA        *this
)
{
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
	// Return to caller.
	return this->pHeader->userData;
}






//===============================================================
//                    M e t h o d s
//===============================================================


//----------------------------------------------------------------
//                  Close - Close down an Instance
//----------------------------------------------------------------
/* Purpose
 *          This function terminates a System.
 * Returns
 *          Nothing
 */
ERESULT         rrds32_Close(
	RRDS32_DATA     *this,
    bool            fDelete
)
{
    ERESULT         eRc;

	// Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return this->eRc;
    }
#endif

	// Flush the file header.
    eRc = rrds32_FileClose(this, fDelete);
    if (ERESULT_FAILED(eRc)) {
        return eRc;
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
    PATH_DATA       *pPath,
    uint16_t        cLRU,           // Number of LRU Buffers
    uint16_t        recordSize,
    uint16_t        headerSize
)
{
    ERESULT         eRc;

#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();              // Should not happen!
        return this->eRc;
    }
    if (OBJ_NIL == pPath) {
        this->eRc = ERESULT_INVALID_PARAMETER;
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
    if (((cLRU == 0) || (cLRU > 1)) && !(cLRU == 34))
        ;
    else {
        this->eRc = ERESULT_INVALID_PARAMETER;
        return this->eRc;
    }
#endif
    
    // Setup the file Header.
    if (headerSize < RRDS32_HEADER_SIZE) {
        headerSize = RRDS32_HEADER_SIZE;
    }
    this->pHeader = (RRDS32_HEADER *)mem_Calloc(1, headerSize);
    if (NULL == this->pHeader) {
        this->eRc = ERESULT_OUT_OF_MEMORY;
        return this->eRc;
    }
    this->pHeader->cbSize = headerSize;
    //this->pHeader->cbFlags = 0;
    this->pHeader->cbIdent = RRDS32_HEADER_IDENTIFIER;
    this->pHeader->recordSize  = recordSize;
    //this->pHeader->recordNum  = 0;
    //this->pHeader->fillChar = 0;

    eRc = rrds32_Setup(this, pPath, cLRU, recordSize, headerSize);
    if (ERESULT_FAILED(eRc)) {
        this->eRc = eRc;
        return eRc;
    }
    
	// Create the file.
    eRc = fileio_Create(this->pIO, pPath);
    if (ERESULT_FAILED(eRc)) {
        this->eRc = eRc;
        return eRc;
    }
    
    eRc = rrds32_Header_Write(this);
    if (ERESULT_FAILED(eRc)) {
        this->eRc = eRc;
        return eRc;
    }

    eRc = fileio_Close(this->pIO, false);
    if (ERESULT_FAILED(eRc)) {
        this->eRc = eRc;
        return eRc;
    }

    eRc = fileio_Open(this->pIO, pPath);
    if (ERESULT_FAILED(eRc)) {
        this->eRc = eRc;
        return eRc;
    }
    
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
    ERESULT         eRc;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return;
    }
#endif
    
    eRc = rrds32_FileClose(this, false);
    
    obj_setVtbl(this, this->pSuperVtbl);
    // pSuperVtbl is saved immediately after the super object which we
    // inherit from is initialized.
    this->pSuperVtbl->pDealloc(this);
    this = OBJ_NIL;

	// Return to caller.
}



//----------------------------------------------------------------
//                      Init - Initialize the object
//----------------------------------------------------------------

RRDS32_DATA *   rrds32_Init(
    RRDS32_DATA     *this
)
{
    uint32_t        cbSize = sizeof(RRDS32_DATA);
    
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
    
#ifdef NDEBUG
#else
    BREAK_NOT_BOUNDARY4(sizeof(RRDS32_DATA));
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
    PATH_DATA       *pPath,
    uint16_t        cLRU            // Number of LRU Buffers
)
{
    ERESULT         eRc;
    RRDS32_HEADER   header;

	// Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return this->eRc;
    }
#endif    

    // Set up the FileIO and LRU objects.
    eRc = rrds32_Setup(this, pPath, cLRU, 0, 0);
    if (ERESULT_FAILED(eRc)) {
        this->eRc = eRc;
        return eRc;
    }
    
    eRc = fileio_Open(this->pIO, pPath);
    if (ERESULT_FAILED(eRc)) {
        this->eRc = eRc;
        return eRc;
    }
    
    eRc = fileio_Read(this->pIO, sizeof(RRDS32_HEADER), (uint8_t *)&header);
    if (ERESULT_FAILED(eRc)) {
        this->eRc = eRc;
        return eRc;
    }
    this->headerSize = header.cbSize;
    this->pHeader = (RRDS32_HEADER *)mem_Malloc(this->headerSize);
    if (NULL == this->pHeader) {
        this->eRc = ERESULT_OUT_OF_MEMORY;
        return this->eRc;
    }

    eRc = rrds32_Header_Read(this, this->pHeader);
    if (ERESULT_FAILED(eRc)) {
        this->eRc = eRc;
        return eRc;
    }

	// Return to caller.
    this->eRc = ERESULT_SUCCESS;
	return ERESULT_SUCCESS;
}



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

void *          rrds32_QueryInfo(
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    RRDS32_DATA     *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
#ifdef NDEBUG
#else
    if( !rrds32_Validate(this) ) {
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
                        return rrds32_ToDebugString;
                    }
#ifdef XYZZY
                    if (str_Compare("ToJSON", (char *)pStr) == 0) {
                        return rrds32_ToJSON;
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
//              RecordRead - Read a Block into Memory
//----------------------------------------------------------------

ERESULT         rrds32_RecordRead(
    RRDS32_DATA     *this,
    uint32_t        recordNum,
    uint8_t         *pData
)
{
    ERESULT         eRc;
    //size_t          fileOffset;
    
    // Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return ERESULT_INVALID_OBJECT;
    }
    if (!fileio_IsOpen(this->pIO)) {
        DEBUG_BREAK();
        return ERESULT_DATA_NOT_FOUND;
    }
#endif
    if( recordNum == 0 ) {
        this->eRc = ERESULT_INVALID_PARAMETER;
        return this->eRc;
    }
    if( recordNum > this->pHeader->recordNum ) {
        this->eRc = ERESULT_INVALID_PARAMETER;
        return this->eRc;
    }
    
    // Read the Block into Memory.
#ifdef USE_LRU
    eRc = lru_Read(this->pLRU, recordNum, pData);
#else
    eRc = rrds32_LSN_Read(this, recordNum, pData);
#endif
    if (ERESULT_FAILED(eRc)) {
        this->eRc = ERESULT_IO_ERROR;
        return this->eRc;
    }

    // Return to caller.
    this->eRc = ERESULT_SUCCESS;
    return this->eRc;
}




//----------------------------------------------------------------
//              RecordWrite - Write a Block to the File
//----------------------------------------------------------------

ERESULT         rrds32_RecordWrite(
    RRDS32_DATA     *this,
    uint32_t        recordNum,
    uint8_t         *pData
)
{
    ERESULT         eRc;
    
    // Do initialization.
#ifdef NDEBUG
#else
    if ( !rrds32_Validate(this) ) {
        DEBUG_BREAK();
        return ERESULT_INVALID_OBJECT;
    }
    if (!fileio_IsOpen(this->pIO)) {
        DEBUG_BREAK();
        return ERESULT_DATA_NOT_FOUND;
    }
#endif
    if( recordNum == 0 ) {
        this->eRc = ERESULT_INVALID_PARAMETER;
        return this->eRc;
    }
    
    /* Fill the File if a block is accessed beyond the end of the
     * File.
     */
    if( recordNum > this->pHeader->recordNum+1 ) {
        if( rrds32_FileExtend( this, recordNum-1 ) )
            ;
        else {
            this->eRc = ERESULT_IO_ERROR;
            return this->eRc;
        }
    }
    
    // Write the Block to the File.
#ifdef USE_LRU
    eRc = lru_Write(this->pLRU, recordNum, pData);
#else
    eRc = rrds32_LSN_Write(this, recordNum, pData);
#endif
    if (ERESULT_FAILED(eRc)) {
        this->eRc = ERESULT_IO_ERROR;
        return this->eRc;
    }
    
    // Return to caller.
    this->eRc = ERESULT_SUCCESS;
    return this->eRc;
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
        AStr_AppendCharRepeatW32(pStr, indent, ' ');
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









