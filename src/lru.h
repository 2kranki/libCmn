// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          LRU Console Transmit Task (lru) Header
//****************************************************************
/*
 * Program
 *			Separate lru (lru)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate lru to run things without complications
 *          of interfering with the main lru. A lru may be 
 *          called a lru on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal lru. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
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
        ERESULT         (*pRead)(
            LRU_DATA        *this,
            uint32_t        lsn,
            uint8_t         *pBuffer
        );
        ERESULT         (*pWrite)(
            LRU_DATA        *this,
            uint32_t        lsn,
            uint8_t         *pBuffer
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
    LRU_DATA *     lru_Alloc(
    );
    
    
    LRU_DATA *     lru_New(
        uint32_t        sectorSize,
        uint32_t        cacheSize
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         lru_getLastError(
        LRU_DATA		*this
    );


    /*!
     Set the logical sector read routine. It is assumed that this routine
     will always read sectorSize bytes.
     @return:   If successful, true, otherwise, false and getLastError()
                will provide the error code.
     */
    bool            lru_setLogicalSectorRead(
        LRU_DATA        *this,
        ERESULT         (*pLogicalRead)(
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
    bool            lru_setLogicalSectorWrite(
        LRU_DATA        *this,
        ERESULT         (*pLogicalWrite)(
            OBJ_ID          pWriteObject,
            uint32_t        lsn,                // Logical Sector Number
            uint8_t         *pBuffer            // Buffer of sectorSize bytes
        ),
        OBJ_ID          pWriteObject
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    LRU_DATA *      lru_Init(
        LRU_DATA        *this,
        uint32_t        sectorSize,
        uint32_t        cacheSize
    );


    /*!
     Read data into the given buffer for size number of bytes if possible.
     The sector will be taken from the LRU cache if present. Otherwise, it
     will be added to the LRU cache possibly bumping out the oldest sector
     if the LRU cache was full.
     Example:
     @code:
        ERESULT  eRc = lru_Read(this, 4, &buffer[0]);
        if (!ERESULT_FAILED(eRc)) {
            // Process data here...
        }
     @endcode:
     @param:    this    LRU object pointer
     @param:    lsn     logical sector number
     @param:    pBuffer pointer to the buffer of sector size bytes or larger
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         lru_Read(
        LRU_DATA        *this,
        uint32_t        lsn,
        uint8_t         *pBuffer
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = lru_ToDebugString(this,4);
     @endcode:
     @param:    this    LRU object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    lru_ToDebugString(
        LRU_DATA        *this,
        int             indent
    );
    
    
    /*!
     Write the data out from the given buffer for sector size bytes.
     The sector will be added to the LRU cache possibly bumping out 
     the oldest sector if the LRU cache was full.
     Example:
     @code:
         ERESULT  eRc = lru_Write(this, 4, &buffer[0]);
         if (ERESULT_FAILED(eRc)) {
            // Process error here...
         }
     @endcode:
     @param:    this    LRU object pointer
     @param:    lsn     logical sector number
     @param:    pBuffer pointer to the buffer of sector size bytes or larger
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         lru_Write(
        LRU_DATA        *this,
        uint32_t        lsn,
        uint8_t         *pBuffer
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* LRU_H */

