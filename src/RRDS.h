// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//     Relative Record Dataset (ie Fixed size records indexed
//              by record number) (RRDS) Header
//****************************************************************
/*
 * Program
 *          Relative Record Dataset (ie Fixed size records indexed
 *          by record number) (RRDS)
 * Purpose
 *          The RRDS routines provide Record I/O functions for a
 *          dataset/file.  An RRDS dataset/file consists of zero
 *          or more fixed length records as used on large IBM
 *          mainframes.
 *
 *          The default size is 80 bytes. It is assumed that data
 *          is only in columns 1 - 71. Column 72 is a continuation
 *          indicator with a default continuation column of 16.
 *          Columns 73 - 80 are assumed to be sequence numbers
 *          which are not checked.
 *
 *          All memory needed is gotten from the operating system
 *          to minimize impact on C's Heap.
 *
 *          An associated LRU buffering mechanism is utilized in
 *          these routines if the dataset is defined as disk based.
 *
 *          An optional area at the beginning of the file can be
 *          reserved for control information if needed.  This
 *          reserve size sets the size of the area and the offset
 *          into the file of the first record.  This size must
 *          be specified before an create() or open().
 *
 * Remarks
 *    1.    If the default record size is used, the lines may be
 *          80-82 characters. When a dataset is opened, it will
 *          be scanned at bytes 81 and 82 to determine if there
 *          are \r, \n, \r\n or \n\r characters after the 80
 *          bytes of data.
 *
 * History
 *  01/05/2019 Generated
 *  07/10/2021 Regenerated and modified to include memory based
 *              files with this object.
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
#include        <lru.h>


#ifndef         RRDS_H
#define         RRDS_H


//#define   RRDS_IS_IMMUTABLE     1
//#define   RRDS_JSON_SUPPORT     1
//#define   RRDS_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct RRDS_data_s  RRDS_DATA;            // Inherits from OBJ
    typedef struct RRDS_class_data_s RRDS_CLASS_DATA;   // Inherits from OBJ

    typedef struct RRDS_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RRDS_object.c.
        // Properties:
        // Methods:
    } RRDS_VTBL;

    typedef struct RRDS_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RRDS_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(RRDS_DATA *);
    } RRDS_CLASS_VTBL;


    // RRDS Record Terminators
    typedef enum  RRDS_rcd_trm_e {
        RRDS_RCD_TRM_UNKNOWN=0,
        RRDS_RCD_TRM_NONE,
        RRDS_RCD_TRM_CR,
        RRDS_RCD_TRM_NL,
        RRDS_RCD_TRM_CRNL,
        RRDS_RCD_TRM_NLCR
    } RRDS_RCD_TRMS;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  RRDS_SINGLETON
    RRDS_DATA *     RRDS_Shared (
        void
    );

    void            RRDS_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to RRDS object if successful, otherwise OBJ_NIL.
     */
    RRDS_DATA *     RRDS_Alloc (
        void
    );
    
    
    OBJ_ID          RRDS_Class (
        void
    );
    
    
    RRDS_DATA *     RRDS_New (
        void
    );
    
    
#ifdef  RRDS_JSON_SUPPORT
    RRDS_DATA *     RRDS_NewFromJsonString (
        ASTR_DATA       *pString
    );

    RRDS_DATA *     RRDS_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint8_t         RRDS_getFillChar (
        RRDS_DATA       *this
    );

    bool            RRDS_setFillChar (
        RRDS_DATA       *this,
        uint8_t         value
    );


    PATH_DATA *     RRDS_getPath (
        RRDS_DATA       *this
    );


    void *          RRDS_getReserve (
        RRDS_DATA       *this
    );


    /*!
     The record offset property should be set before a dataset/file
     is opened or created. This offset sets the beginning of the
     records to start at it in the file allowing the beginning of
     the file to be used for other purposes. The default for this
     is zero.
     */
    uint16_t        RRDS_getReserveSize (
        RRDS_DATA       *this
    );

    bool            RRDS_setReserveSize (
        RRDS_DATA     *this,
        uint16_t        value
    );


    /*!
     The record size property should be set before a dataset/file
     is opened or created. This size does not include any record
     terminators such as '\n' or '\r'.  Also, once the dataset can
     be read or written then this property can not be changed.
     The default record size is 80 which matches IBM's 80-col cards.
     */
    uint16_t        RRDS_getRecordSize (
        RRDS_DATA       *this
    );

    bool            RRDS_setRecordSize (
        RRDS_DATA     *this,
        uint16_t        value
    );


    /*! Number of Records in the Dataset Property
     */
    uint32_t        RRDS_getSize (
        RRDS_DATA       *this
    );




    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------


    /*! Close the file and free the areas associated with reading and
     writing to the file instance.
     @param     fDelete     If true, delete the file after closing it.
     @Return    If successful, ERESULT_SUCCESS; otherwise an ERESULT_*
                error.
     */
    ERESULT         RRDS_Close (
        RRDS_DATA       *this,
        bool            fDelete
    );


    /*! Create a new Relative Record Data Set (RRDS). This method
        or Open() must be called prior to using any other RRDS I/O
        calls.  Use Close() to flush buffers and close the file.
        Use Destroy() to close the file deleting it.
     @param     this    object pointer
     @param     pPath   path pointer
     @param     fMem    true == create a memory based file rather
                        than one on disk. This file will be deleted
                        upon Close()/Destroy().
                        false == create a disk file with all data
                        being read/written there.
     @Return    If file is open, ERESULT_SUCCESS; otherwise an
                ERESULT_* error.
     */
    ERESULT         RRDS_Create (
        RRDS_DATA       *this,
        PATH_DATA       *pPath,
        bool            fMem
    );


    RRDS_DATA *     RRDS_Init (
        RRDS_DATA       *this
    );


    /*!
     IsOpen() returns ERESULT_SUCCESS if the file is open and
     ready to be read.
     @param     this    object pointer
     @Return    If file is open, ERESULT_SUCCESS; otherwise an
                ERESULT_* error.
     */
    ERESULT         RRDS_IsOpen (
        RRDS_DATA        *this
    );


    /*!
     Open() creates an instance of the Page File System using
     a previously created file.    This routine or Create() must
     be called prior to using any other calls.    Use Close()
     to terminate and free the instance created by Create() or
     this routine.
     @param     this    object pointer
     @param     pPath   dataset path pointer
     @Return    If successful, ERESULT_SUCCESS; otherwise an ERESULT_*
                error.
     */
    ERESULT         RRDS_Open (
        RRDS_DATA       *this,
        PATH_DATA       *pPath,
        bool            fMem
    );


    /* RecordRead() reads a Block from the File if it exists to the
     * address specified.
     * Returns:
     *    RRDS_OK            =    Successful Completion
     *    RRDS_ERROR_BADCB    =    Invalid RRDS_CB Pointer
     *    RRDS_ERROR_NOMEM    =    Out of Memory in File Extend
     *    RRDS_ERROR_PAGE    =    Bad Block Number
     *    RRDS_ERROR_READ    =    Disk Read Error
     *    RRDS_ERROR_SEEK    =    Disk Seek Error
     *    RRDS_ERROR_WRITE    =    Disk Write Error in File Extend
     */
    ERESULT         RRDS_RecordRead (
        RRDS_DATA       *this,
        uint32_t        recordNum,
        uint8_t         *pData
    );


    /* RecordWrite() writes a Block to the File from the address specified.
     * Returns:
     *    RRDS_OK            =    Successful Completion
     *    RRDS_ERROR_BADCB    =    Invalid RRDS_CB Pointer
     *    RRDS_ERROR_NOMEM    =    Out of Memory in File Extend
     *    RRDS_ERROR_PAGE    =    Bad Block Number
     *    RRDS_ERROR_SEEK    =    Disk Seek Error
     *    RRDS_ERROR_WRITE    =    Disk Write Error in File Extend
     */
    ERESULT         RRDS_RecordWrite (
        RRDS_DATA       *this,
        uint32_t        recordNum,
        uint8_t         *pData    // Data Ptr (if NULL, a FillChar record is written)
    );


    /*!
     Initialize the RRDS and LRU mechanisms for this RRDS and the basic
     constants.  This overrides the defaults of record size of 80, record
     terminator dependent on O/S, LRU buffers of 1 and LRU Hash of 13. This
     should be called before a Create() or an Open().
     @param     this    object pointer
     @param     cLRU    number of LRU buffers to use (relative to one and default is 1)
                        (0 == illegal, 1 == bypass LRU, > 1 == use LRU buffering)
     @param     cHash   Number of Hash chains for LRU mechanism
                        (You should use a prime number for this and default is 13).
     @Return    If successful, ERESULT_SUCCESS; otherwise an ERESULT_*
                error.
     */
    ERESULT         RRDS_SetupSizes (
        RRDS_DATA       *this,
        uint16_t        recordSize,     // Record Size without optional terminator
        uint16_t        recordTerm,     // Record Terminator Type
        //                              // (See RRDS_rcd_trm_e above)
        uint16_t        cLRU,           // Number of LRU Buffers
        uint16_t        cHash           // Number of LRU Hash Chains
    );


#ifdef  RRDS_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = RRDS_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RRDS_ToJson (
        RRDS_DATA       *this
    );
#endif


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
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RRDS_ToDebugString (
        RRDS_DATA       *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* RRDS_H */

