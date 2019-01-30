// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//        Motorola S-Record Reader/Writer (SRecords) Header
//****************************************************************
/*
 * Program
 *			Motorola S-Record Reader/Writer (SRecords)
 * Purpose
 *			This object provides a standardized way of reading or
 *          writing an S-Record text file. S-Records are one way
 *          of sharing binary data between applications. They are
 *          full text representations of the binary data.
 *
 *          From the MC68000 Family Programmer's Reference Manual:
 *
 *          An S-record format module may contain S-records of the following types:
 *
 *          S0 — The header record for each block of S-records. The code/data field
 *               may contain any descriptive information identifying the following
 *               block of S-records. The address field is normally zeros.
 *                  2 chars - "S0"
 *                  2 char Hex/1 byte - number of data Hex pairs following this field
 *                                      (ie 2 for adr + 3 for data + 1 for checksum)
 *                  4 char Hex/2 byte Address Field (Big Endian)
 *                  6 char Hex/3 bytes - "HDR"
 *                  2 char Hex/1 byte checksum
 *              Example: S00600004844521B
 *
 *          S1 - A record containing code/data and the 2-byte address at which the
 *               code/data is to reside.
 *                  2 chars - "S1"
 *                  2 char Hex/1 byte - number of data Hex pairs in following this field
 *                  4 char Hex/2 byte Address Field  (Big Endian)
 *                  2n char Hex/ n bytes of Code/Data
 *                  2 char Hex/1 byte checksum
 *              Example: S107003000144ED492
 *
 *          S2 - A record containing code/data and the 3-byte address at which the
 *               code/data is to reside.
 *                  2 chars - "S2"
 *                  2 char Hex/1 byte - number of data Hex pairs in following this field
 *                  6 char Hex/3 byte Address Field  (Big Endian)
 *                  2n char Hex/ n bytes of Code/Data
 *                  2 char Hex/1 byte checksum
 *
 *          S3 - A record containing code/data and the 4-byte address at which the
 *               code/data is to reside.
 *                  2 chars - "S3"
 *                  2 char Hex/1 byte - number of data Hex pairs in following this field
 *                  8 char Hex/4 byte Address Field  (Big Endian)
 *                  2n char Hex/ n bytes of Code/Data
 *                  2 char Hex/1 byte checksum
 *
 *          S5 - A record containing the number of S1, S2, and S3 records transmitted
 *               in a particular block. This count appears in the address field.
 *               There is no code/data field.
 *
 *          S7 - A termination record for a block of S3 records. The address field
 *               may optionally contain the 4-byte address of the instruction to which
 *               control is to be passed. There is no code/data field.
 *
 *          S8 - A termination record for a block of S2 records. The address field may
 *               optionally contain the 3-byte address of the instruction to which
 *               control is to be passed. There is no code/data field.
 *
 *          S9 - A termination record for a block of S1 records. The address field may
 *               optionally contain the 2-byte address of the instruction to which
 *               control is to be passed.  If this address is not specified, the first
 *               entry point specification encountered in the object module input will
 *               be used. There is no code/ data field.
 *                  2 chars - "S9"
 *                  2 char Hex/1 byte - number of Hex pairs in following this field
 *                  4 char Hex/2 byte Address Field  (Big Endian)
 *                  2 char Hex/1 byte checksum
 *              Example: S9030000FC
 *
 *          Each block of S-Records uses only one termination record. S7 and S8 records
 *          are only active when control is to be passed to a 3- or 4- byte address;
 *          otherwise, an S9 is used for termination. Normally, there is only one S1
 *          header record, although it is possible for multiple header records to occur.
 *
 *          The checksum is the least significant byte of one's complement of the sum of
 *          the values represented by the pairs of characters making up the record length,
 *          address, and the code/data fields.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/22/2017 Generated
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


#ifndef         SRECORDS_H
#define         SRECORDS_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SRecords_data_s	SRECORDS_DATA;    // Inherits from OBJ.

    typedef struct SRecords_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SRecords_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRECORDS_DATA *);
    } SRECORDS_VTBL;



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
     @return    pointer to SRecords object if successful, otherwise OBJ_NIL.
     */
    SRECORDS_DATA *     SRecords_Alloc(
        void
    );
    
    
    OBJ_ID              SRecords_Class(
        void
    );


    SRECORDS_DATA *     SRecords_New(
        void
    );
    
    
    /*!
     Create a string that contains the appropriate records for the given data block.
     Example:
     @code
     ASTR_DATA      *pRecords = SRecords_ToStringS1(this, 4);
     @endcode
     @param     load    Load Address for Data Block
     @param     start   Block Start Address (Use 0 if not needed.)
     @param     len     number of bytes in the data block
     @param     pData   Pointer to first byte of data block
     @return    If successful, an AStr object which must be released containing the
                records, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SRecords_ToStringS1(
        uint16_t        load,               // Load Address of First Data Byte
        uint16_t        start,              // Optional Start Address
        uint16_t        len,                // Length of Data
        uint8_t         *pData              // Data Pointer
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     SRecords_getLastError(
        SRECORDS_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     SRecords_Disable(
        SRECORDS_DATA		*this
    );


    SRECORDS_DATA *   SRecords_Init(
        SRECORDS_DATA     *this
    );


    ERESULT     SRecords_IsEnabled(
        SRECORDS_DATA		*this
    );
    
 
    ERESULT         SRecords_ReadFromAStr(
        SRECORDS_DATA   *this,
        ASTR_DATA       *pStr,
        uint8_t         *pMemory,
        uint32_t        cMemory,
        uint32_t        *pMemoryUsed
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SRecords_ToDebugString(this,4);
     @endcode 
     @param     this    SRECORDS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    SRecords_ToDebugString(
        SRECORDS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SRECORDS_H */

