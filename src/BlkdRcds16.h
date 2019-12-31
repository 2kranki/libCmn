// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Block of Variable-sized Records (BlkdRcds16) Header
//****************************************************************
/*
 *          These subroutines provide a general purpose set of
 *          routines to build and manipulate a block of variable
 *          length data records. The block size is restricted to
 *          32,768.
 *
 *          All offsets within the block are numeric. No addresses
 *          are maintained in the block. So, it can be safely
 *          written to disk if needed.
 *
 *          The block header can contain an area reserved for
 *          any use. Just specify the amount at open time.
 *
 * Remarks
 *    1.          Records are numbered starting with 1.  If
 *                zero is returned for a record index, it should be
 *                considered an error.
 *
 * References:
 *  *      "Data Structures and Algorithms", Alfred V. Aho et al,
 *          Addison-Wesley, 1985
 *  *       "Data Structures using C", Aaron M. Tenenbaum et al,
 *          Prentice-Hall, 1990
 *  *      "Programs and Data Structures in C", Leendert Ammeraal,
 *          John Wiley & Sons, 1987
 *  *      "VSAM: Architecture, Theory and Applications", Larry Brumbaugh,
 *          McGraw-Hill, 1993
 * History
 *	12/22/2019 Regenerated
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


#ifndef         BLKDRCDS16_H
#define         BLKDRCDS16_H


//#define   BLKDRCDS16_JSON_SUPPORT 1
//#define   BLKDRCDS16_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BlkdRcds16_data_s	BLKDRCDS16_DATA;            // Inherits from OBJ
    typedef struct BlkdRcds16_class_data_s BLKDRCDS16_CLASS_DATA;   // Inherits from OBJ

    typedef struct BlkdRcds16_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BlkdRcds16_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BLKDRCDS16_DATA *);
    } BLKDRCDS16_VTBL;

    typedef struct BlkdRcds16_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BlkdRcds16_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BLKDRCDS16_DATA *);
    } BLKDRCDS16_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BLKDRCDS16_SINGLETON
    BLKDRCDS16_DATA * BlkdRcds16_Shared (
        void
    );

    bool            BlkdRcds16_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to BlkdRcds16 object if successful, otherwise OBJ_NIL.
     */
    BLKDRCDS16_DATA * BlkdRcds16_Alloc (
        void
    );
    
    
    uint16_t        BlkdRcds16_CalcBlockSize(
        uint16_t        rsvdSize,
        uint16_t        numRecords,
        uint16_t        recordSize              // Average Record Size
    );
    
    
    OBJ_ID          BlkdRcds16_Class (
        void
    );
    
    
    BLKDRCDS16_DATA * BlkdRcds16_New (
        void
    );
    
    BLKDRCDS16_DATA * BlkdRcds16_NewWithSizes (
        uint16_t        blockSize,
        uint16_t        rsvdSize
    );
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint8_t *       BlkdRcds16_getData (
        BLKDRCDS16_DATA *this
    );


    uint16_t        BlkdRcds16_getNumRecords (
        BLKDRCDS16_DATA *this
    );


    uint16_t        BlkdRcds16_getUnused (
        BLKDRCDS16_DATA *this
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    BLKDRCDS16_DATA * BlkdRcds16_Init (
        BLKDRCDS16_DATA *this
    );


    ERESULT         BlkdRcds16_RecordAdd (
       BLKDRCDS16_DATA *this,
       uint16_t        size,
       void            *pData,
       uint16_t        *pIndex             // (Optional) Returned Output Index
    );


    ERESULT         BlkdRcds16_RecordDelete (
       BLKDRCDS16_DATA *this,
       uint16_t        index
    );


    /*!
    Copy a record from the block into a supplied area.
    @param     this        BLKDRCDS16 object pointer
    @param     index       record number (relative to 1)
    @param     dataSize    size of the supplied data area
    @param     pData       Optional pointer to the data area. If NULL, no data
                           is copied.
    @param     pSizeUsed   Optional pointer to a size to be returned. The size
                           used will be the record size if it fits in the area
                           provided or the truncated size of the area provided.
                           If NULL, no size is returned.
    @return    If successful, ERESULT_SUCCESS. An ERESULT_* error code.
    */
    ERESULT         BlkdRcds16_RecordGet (
       BLKDRCDS16_DATA *this,
       uint16_t        index,
       uint16_t        dataSize,
       void            *pData,             // Optional
       uint16_t        *pSizeUsed          // Optional
    );


    ERESULT         BlkdRcds16_RecordGetSize (
       BLKDRCDS16_DATA *this,
       uint16_t        index,
       uint16_t        *pSize
    );


    ERESULT         BlkdRcds16_RecordUpdate (
       BLKDRCDS16_DATA *this,
       uint16_t        index,
       uint16_t        dataSize,
       void            *pData
    );


    ERESULT         BlkdRcds16_SetupDataBlock (
        BLKDRCDS16_DATA *this,
        uint16_t        blockSize,
        uint16_t        rsvdSize
    );


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
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    BlkdRcds16_ToDebugString (
        BLKDRCDS16_DATA *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BLKDRCDS16_H */

