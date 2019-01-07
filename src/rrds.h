// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Fixed Length File Record I/O System (rrds) Header
//****************************************************************
/*
 * Program
 *			Fixed Length File Record I/O System (rrds)
 * Purpose
 *          The RRDS routines provide Record I/O functions for a
 *          dataset/file.  An RRDS dataset/file consists of zero
 *          more fixed length records as used on large IBM main-
 *          frames.
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
 *          these routines.
 *
 * Remarks
 *	1.      Internally, lines may be 80-82 characters. When a
 *          dataset is opened, it will be scanned at bytes 80
 *          and 81 to determine if there are \r or \n characters
 *          after the 80 bytes of data.
 *
 * History
 *	01/05/2019 Generated
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


#ifndef         RRDS_H
#define         RRDS_H


//#define   RRDS_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct rrds_data_s	RRDS_DATA;            // Inherits from OBJ
    typedef struct rrds_class_data_s RRDS_CLASS_DATA;   // Inherits from OBJ

    typedef struct rrds_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in rrds_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(RRDS_DATA *);
    } RRDS_VTBL;

    typedef struct rrds_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in rrds_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(RRDS_DATA *);
    } RRDS_CLASS_VTBL;


    enum  rrds_rcd_trm_e {
        RRDS_RCD_TRM_UNKNOWN=0,
        RRDS_RCD_TRM_NONE,
        RRDS_RCD_TRM_CR,
        RRDS_RCD_TRM_NL,
        RRDS_RCD_TRM_CRNL,
        RRDS_RCD_TRM_NLCR
    };
    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  RRDS_SINGLETON
    RRDS_DATA *     rrds_Shared (
        void
    );

    bool            rrds_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to rrds object if successful, otherwise OBJ_NIL.
     */
    RRDS_DATA *     rrds_Alloc (
        void
    );
    
    
    OBJ_ID          rrds_Class (
        void
    );
    
    
    RRDS_DATA *     rrds_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     The record size property should be set before a dataset/file
     is opened or created. This size does not include any record
     terminators such as '\n' or '\r'.  Also, once the dataset can
     be read or written then this property can not be changed.
     The default record size is 80 which matches IBM's 80-col cards.
     */
    uint16_t        rrds_getRecordSize (
        RRDS_DATA       *this
    );
    
    bool            rrds_setRecordSize (
        RRDS_DATA     *this,
        uint16_t        value
    );
    

    /*! Number of Records in the Dataset Property
     */
    uint32_t        rrds_getSize (
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
    ERESULT         rrds_Close (
        RRDS_DATA       *this,
        bool            fDelete
    );
    
    
    /* Create() creates an instance of a new RRDS.    This
     * routine or Open() must be called prior to using any other
     * RRDS I/O calls.  Use Close() to flush buffers and close the
     * file. Use Destroy() to close the file deleting it.
     */
    ERESULT         rrds_Create (
        RRDS_DATA       *this,
        PATH_DATA       *pPath,
        uint16_t        cLRU            // Number of LRU Buffers
    );
    
    
    RRDS_DATA *     rrds_Init (
        RRDS_DATA       *this
    );


    /*!
     Open() creates an instance of the Page File System using
     a previously created file.    This routine or Create() must
     be called prior to using any other calls.    Use Close()
     to terminate and free the instance created by Create() or
     this routine.
     @param     this    object pointer
     @param     pPath   dataset path pointer
     @param     cLRU    number of LRU buffers to use (relative to zero)
     @Return    If successful, ERESULT_SUCCESS; otherwise an ERESULT_*
                error.
     */
    ERESULT         rrds_Open (
        RRDS_DATA       *this,
        PATH_DATA       *pPath,
        uint16_t        cLRU            // Number of LRU Buffers
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
    ERESULT         rrds_RecordRead (
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
    ERESULT         rrds_RecordWrite (
        RRDS_DATA       *this,
        uint32_t        recordNum,
        uint8_t         *pData    // Data Ptr (if NULL, a FillChar record is written)
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = rrds_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     rrds_ToDebugString (
        RRDS_DATA       *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* RRDS_H */

