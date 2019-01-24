// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Least Recently Used Buffering (lru) Header
//****************************************************************
/*
 * Program
 *			Least Recently Used Buffering (lru)
 * Purpose
 *			This object provides a standardized way of handling
 *          Least Recently Used Buffering.
 *
 *          These routines intercept the normal read/write process.
 *          First, the using object must give this object the physical
 *          read and/or write routines. Second, it must then call
 *          the routines provided by this object which will utilize
 *          the LRU buffering only calling the physical routines
 *          when physical reads or writes must be performed.
 *
 *          The logical sector number is simply used to distinguish
 *          the buffers by hashing it and otherwise is simply passed
 *          on as is to the physical read/write routines.
 *
 *          Optionally, you can load the buffers with reads or locks
 *          without buffer pointers and then get the buffer address
 *          using FindBuffer().  Be aware that if you did not lock
 *          the buffer, it might be re-used while you have access to
 *          it.  Lock()/Unlock() pairs are the safest way to go.
 *
 * Remarks
 *	1.      If the delayed-writes property is set, writing to the file
 *          is only done when a buffer is needed for re-use or the \
 *          system is being shutdown.  Writes are accumulated in memory
 *          until then minimizing I/O.
 *
 * History
 *	10/21/2016 Generated
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
#include        <AStr.h>


#ifndef         LRU_H
#define         LRU_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct lru_data_s	LRU_DATA;    // Inherits from OBJ.

    typedef struct lru_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in lru_object.c.
        // Properties:
        // Methods:
        ERESULT         (*pRead) (
            LRU_DATA        *this,
            uint32_t        lsn,        // Logical Sector Number
            uint8_t         *pBuffer    // Address of Buffer to read into
        );
        ERESULT         (*pWrite) (
            LRU_DATA        *this,
            uint32_t        lsn,        // Logical Sector Number
            uint8_t         *pBuffer    // Address of Buffer to write from
        );
    } LRU_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return:   pointer to lru object if successful, otherwise OBJ_NIL.
     */
    LRU_DATA *     lru_Alloc (
        void
    );
    
    
    LRU_DATA *      lru_New (
        void
    );
    
    
    /*!
     Create a new LRU object which will need to have sector read and
     write routines added before it can actually be used.
     @param     blockSize   Size of Block to be read/written
     @param     cacheSize   Number of Block Buffers to use. Prime
                            numbers work the best for this.
     @param     hashSize    Size of Hash Table. Prime numbers work best
                            for this.
     @return    If successful, a new LRU object; otherwise, OBJ_NIL.
     */
    LRU_DATA *     lru_NewWithSizes (
        uint32_t        blockSize,
        uint32_t        cacheSize,
        uint16_t        hashSize
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     The delay writes property indicates if all writes to the file
     should be delayed until the buffer is needed by the LRU mechanism,
     a FlushAll is requested or the LRU system is closed.
     */
    bool            lru_getDelayWrites(
        LRU_DATA        *this
    );
    
    bool            lru_setDelayWrites(
        LRU_DATA        *this,
        bool            value
    );

    
    /*!
     Set the logical sector read routine. It is assumed that this routine
     will always read sectorSize bytes.
     @return:   If successful, true, otherwise, false and getLastError()
                will provide the error code.
     */
    bool            lru_setLogicalSectorRead (
        LRU_DATA        *this,
        ERESULT         (*pLogicalRead) (
            OBJ_ID          pReadObject,
            uint32_t        lsn,                // Logical Sector Number
            uint8_t         *pBuffer            // Buffer of sectorSize bytes
        ),
        OBJ_ID          pReadObject
    );
    
    
    /*!
     Set the logical sector write routine. It is assumed that this routine
     will always write sectorSize bytes.
     @return:   If successful, true, otherwise, false and getLastError() 
                will provide the error code.
     */
    bool            lru_setLogicalSectorWrite (
        LRU_DATA        *this,
        ERESULT         (*pLogicalWrite) (
            OBJ_ID          pWriteObject,
            uint32_t        lsn,                // Logical Sector Number
            uint8_t         *pBuffer            // Buffer of sectorSize bytes
        ),
        OBJ_ID          pWriteObject
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Attach an Object to an active Buffer.  The object must support
     lruAttach() and lruDetach() methods.  The lruAttach() is called
     when object is attached to the buffer.  The lruDetach() is called
     when the buffer is being reused for a different record on the
     lru list.  Both routines are found via the QueryInfo() method of
     the object.
     @param     this    object pointer
     @param     lsn     logical sector number
     @param     pObject object pointer to be attached to the buffer
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         lru_AttachObjectToBuffer (
        LRU_DATA        *this,
        uint32_t        lsn,
        OBJ_ID          pObject
    );
    
    
    /*!
     Flush all dirty buffers on the LRU and Locked chains.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         lru_FlushAll (
        LRU_DATA        *this
    );
    
    
    /*!
     Search the LRU buffers for the buffer given.  If found, return
     the buffer address.
     @param     this    object pointer
     @param     lsn     logical sector number
     @return    If successful, the buffer address. Otherwise, NULL.
     */
    uint8_t *       lru_FindBuffer (
        LRU_DATA        *this,
        uint32_t        lsn
    );
    
    
    LRU_DATA *      lru_Init (
        LRU_DATA        *this
    );


    /*!
     Read data into the given buffer for size number of bytes if possible
     and then lock it from being re-used.  The sector will be taken from
     the LRU cache if present. Otherwise, it will be added to the lockded
     cache and removed from the LRU cache.
     Example:
     @code
     ERESULT    eRc = lru_Lock(this, 4, &buffer[0]);
                if (!ERESULT_FAILED(eRc)) {
                    // Process data here...
                }
     @endcode
     @param     this    object pointer
     @param     lsn     logical sector number
     @param     pBuffer optional pointer to the buffer of sector size bytes or larger
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         lru_Lock (
        LRU_DATA        *this,
        uint32_t        lsn,
        uint8_t         *pBuffer
    );
    
    
    /*!
     Search the LRU buffers for the buffer given.  If found, set the
     buffer as dirty so that it will be flushed out the next time
     that flusing is triggered.
     @param     this    object pointer
     @param     lsn     logical sector number
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         lru_MakeDirty (
        LRU_DATA        *this,
        uint32_t        lsn
    );
    
    
    /*!
     Read data into the given buffer for size number of bytes if possible.
     The sector will be taken from the LRU cache if present. Otherwise, it
     will be added to the LRU cache possibly bumping out the oldest sector
     if the LRU cache was full.
     Example:
     @code
        ERESULT     eRc = lru_Read(this, 4, &buffer[0]);
                    if (!ERESULT_FAILED(eRc)) {
                        // Process data here...
                    }
     @endcode
     @param     this    object pointer
     @param     lsn     logical sector number
     @param     pBuffer optional pointer to the buffer of sector size bytes or larger
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         lru_Read (
        LRU_DATA        *this,
        uint32_t        lsn,
        uint8_t         *pBuffer
    );
    
    
    ERESULT         lru_Setup (
        LRU_DATA        *this,
        uint32_t        blockSize,
        uint16_t        cacheSize,          // Number of Blocks in Cache
        uint16_t        hashSize
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = lru_ToDebugString(this,4);
     @endcode
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    lru_ToDebugString (
        LRU_DATA        *this,
        int             indent
    );
    
    
    /*!
     Unlock a previously locked buffer and optionally mark it as dirty
     (ie needing to be flushed).
     @param     this    object pointer
     @param     lsn     logical sector number
     @param     fDirty  true == make buffer as dirty
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         lru_Unlock (
        LRU_DATA        *this,
        uint32_t        lsn,
        bool            fDirty
    );
    
    
    /*!
     Write the data out from the given buffer for sector size bytes.
     The sector will be added to the LRU cache possibly bumping out 
     the oldest sector if the LRU cache was full.
     Example:
     @code
         ERESULT    eRc = lru_Write(this, 4, &buffer[0]);
                    if (ERESULT_FAILED(eRc)) {
                        // Process error here...
                    }
     @endcode
     @param     this    object pointer
     @param     lsn     logical sector number
     @param     pBuffer pointer to the buffer of sector size bytes or larger
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         lru_Write (
        LRU_DATA        *this,
        uint32_t        lsn,
        uint8_t         *pBuffer
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* LRU_H */

