// vi:nu:et:sts=4 ts=4 sw=4

/*****************************************************************/
/*				File Record I/O System (RRDS) Header File		 */
/*****************************************************************/
/*
 * Purpose
 *			The RRDS routines provide Record I/O functions for a
 *			dataset/file.  An RRDS dataset/file consists of an
 *			optional fixed-length Header followed by zero or more
 *			fixed length records. The header size is internally
 *          calculated based on compile time constants.
 *
 *			The Header and Record I/O are separate from each other.
 *			All memory needed is gotten from the operating system
 *			to minimize impact on C's Heap.
 *
 *			Prior to closing the header information should be
 *          updated if needed, because it will automatically be
 *			written out as part of the close.
 *
 *			An associated LRU buffering mechanism is utilized in
 *			these routines.
 * Remarks
 *	1.		These routines do not actually store any data into
 *			the file other than what is requested.	This was
 *			done to accomodate various file layouts.
 * History
 *	11/16/93	Added Borland C++ for OS/2 support.
 *	10/27/93	Fixed RRDS_Close() to force a flush of the Header
 *				if present.
 *	10/26/93	Removed from RRDS_Create() and RRDS_Open() the Number
 *				of Buffers parameter since it wasn't being used and
 *				was misleading.
 *	10/25/93	Changed RRDS_Create() and RRDS_Open() to have the
 *				returned CB Ptr to be the last parameter so as
 *				to be more consistent with other systems.
 *	10/01/93	Fixed incorrect variable usage in OS2V2 code.
 *	09/23/93	Changed RRDS_ERROR to use uint16_t.
 *	08/29/93	Created from PFS routines.
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




#include        <cmn_defs.h>
#include        <path.h>


#ifndef         RRDS32_H
#define         RRDS32_H	1



#ifdef	__cplusplus
extern	"C" {
#endif
    


    /****************************************************************
    * * * * * * * * * * * *  data definitions   * * * * * * * * * * *
    ****************************************************************/

    typedef struct rrds32_data_s	RRDS32_DATA;
    //typedef uint32_t			RRDS_NUM;        /* Block Number */

    typedef struct rrds32_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in table_object.c.
        ERESULT         (*pBlockRead)(
            RRDS32_DATA 	*this,
            uint32_t        recordNum,
            uint8_t         *pData
        );
        ERESULT         (*pBlockWrite)(
            RRDS32_DATA 	*this,
            uint32_t		recordNum,
            uint8_t			*pData	/* Data Ptr (if NULL, a FillChar
                                     * record is written)
                                     */
        );
    } RRDS32_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    RRDS32_DATA *   rrds32_Alloc(
        void
    );
    
    
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------
    
    /* getBlkNum() returns the current number of records in the
     * the dataset.
     * Returns:
     *	RRDS_OK			=	Successful Completion
     *	RRDS_ERROR_BADCB	=	Invalid RRDS_CB Pointer
     */
    uint32_t         rrds32_getBlkNum(
        RRDS32_DATA 	*this
    );
    
    
    /* GetRecordSize() returns the record size.
     */
    uint16_t        rrds32_getRecordSize(
        RRDS32_DATA 	*this
    );
    
    
    /* GetFillChar() returns the current Fill Character.
     */
    char            rrds32_getFillChar(
        RRDS32_DATA 	*this
    );
    
    bool            rrds32_setFillChar(
        RRDS32_DATA     *this,
        char            value
    );
    
    
    ERESULT         rrds32_getLastError(
        RRDS32_DATA     *this
    );
    
    
    /* GetUserSize() returns the User Area size.
     */
    uint16_t        rrds32_getUserSize(
        RRDS32_DATA 	*this
    );
    
    
    /* GetUserPtr() returns a pointer to the User Area.
     */
    uint8_t *       rrds32_getUserPtr(
        RRDS32_DATA 	*this
    );
    
    

    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
    /* BlockRead() reads a Block from the File if it exists to the 
     * address specified.
     * Returns:
     *	RRDS_OK			=	Successful Completion
     *	RRDS_ERROR_BADCB	=	Invalid RRDS_CB Pointer
     *	RRDS_ERROR_NOMEM	=	Out of Memory in File Extend
     *	RRDS_ERROR_PAGE	=	Bad Block Number
     *	RRDS_ERROR_READ	=	Disk Read Error
     *	RRDS_ERROR_SEEK	=	Disk Seek Error
     *	RRDS_ERROR_WRITE	=	Disk Write Error in File Extend
     */
    ERESULT         rrds32_BlockRead(
        RRDS32_DATA 	*this,
        uint32_t        recordNum,
        uint8_t         *pData
    );


    /* BlockWrite() writes a Block to the File from the address specified.
     * Returns:
     *	RRDS_OK			=	Successful Completion
     *	RRDS_ERROR_BADCB	=	Invalid RRDS_CB Pointer
     *	RRDS_ERROR_NOMEM	=	Out of Memory in File Extend
     *	RRDS_ERROR_PAGE	=	Bad Block Number
     *	RRDS_ERROR_SEEK	=	Disk Seek Error
     *	RRDS_ERROR_WRITE	=	Disk Write Error in File Extend
     */
    ERESULT         rrds32_BlockWrite(
        RRDS32_DATA 	*this,
        uint32_t		recordNum,
        uint8_t			*pData	/* Data Ptr (if NULL, a FillChar
                                 *	record is written)
                                 */
    );


    /* Close() closes a file keeping it and frees the areas
     * associated with the file instance.
     * Returns NULL on succesful completion.
      */
    ERESULT         rrds32_Close(
        RRDS32_DATA     *this
    );


    /* Create() creates an instance of a new RRDS.	This
     * routine or Open() must be called prior to using any other
     * RRDS I/O calls.  Use Close() to flush buffers and close the
     * file. Use Destroy() to close the file deleting it.
     */
    ERESULT         rrds32_Create(
        RRDS32_DATA     *this,
        const
        char            *pFilePath,
        uint16_t        recordSize,     // Must be on 4-byte boundary
        uint16_t        headerSize      // Must be on 4-byte boundary
    );


    /* Destroy() closes a file deleting it and frees the areas
     * associated with the file instance.
     * Returns:
     *	RRDS_OK			=	Successful Completion
     *	RRDS_ERROR_BADCB	=	Invalid RRDS_CB Pointer
     *	RRDS_ERROR_CLOSE	=	Disk File Close Error
     *	RRDS_ERROR_NOMEM	=	No Memory Available
     *	RRDS_ERROR_SEEK	=	Disk Seek Error
     *	RRDS_ERROR_WRITE	=	Disk Write Error in File Extend
     */
    ERESULT         rrds32_Destroy(
        RRDS32_DATA     *this
    );


    RRDS32_DATA *	rrds32_Init(
        RRDS32_DATA     *this,
        uint16_t        cLRU            // Number of LRU Buffers
    );
    
    
    /* Open() creates an instance of the Page File System using
     * a previously created file.	This routine or Create() must
     * be called prior to using any other calls.	Use Close()
     * to terminate and free the instance created by Create() or
     * this routine.
     * Returns NULL on unsuccessful completion.
     */
    ERESULT         rrds32_Open(
        RRDS32_DATA     *this,
        const
        char            *pFilePath
    );



    /*!
     Create a string that describes this object and the
     objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = rrds32_ToDebugString(pObj,4);
     @endcode:
     @param:    this    object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     rrds32_ToDebugString(
        RRDS32_DATA     *this,
        int             indent
    );
    
    
    
    
#ifdef	__cplusplus
};
#endif


#endif
