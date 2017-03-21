// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                Data block (block) Support  Header
//****************************************************************

/*
 * Program
 *				Data block (block) Support Subroutines
 * Purpose
 *				These subroutines provide a general purpose set of
 *				routines to build and manipulate a block of data.
 *				A block consists of 3 portions. The first is the
 *              control portion that defines the rest of the block.
 *              The second is an optional fixed-size header that can
 *              be used for any purpose and is a fixed number of
 *              bytes. The last is the variable-sized data itself.
 *              The total size of the block is the size of the control
 *              portion, the header and the the data with each section's
 *              size rounded up to the nearest word.
 *
 *
 * Remarks
 *	1.			The Block's internal structures should not contain any pointers. 
 *              So, it can be used in a file if needed. Use offsets instead.
 *  2.          The combined size of the control, header and data
 *              portions of the block is limited to 64k.
 * History
 *	12/01/14	Adapted for cmnLib.
 *	11/15/93	Added Borland C++ for OS/2 support.
 *	04/18/93	Added block16_MaxCount() to get an array size when using
 *				block16_Update() to create a sparse array.
 *	04/15/93	Changed block16_Update() for adding or updating entries
 *				based on an entry number.
 *	03/19/93	Added cbSize checking on all external functions.
 *	02/08/93	Added MEM_ support.
 *	01/21/93	Added IBM C Set/2 support.
 *	06/26/92	Created from CLF routines.
 * References
 *		"Data Structures and Algorithms", Alfred V. Aho et al,
 *			Addison-Wesley, 1985
 *		"Data Structures using C", Aaron M. Tenenbaum et al,
 *			Prentice-Hall, 1990
 *		"Programs and Data Structures in C", Leendert Ammeraal,
 *			John Wiley & Sons, 1987
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


#ifndef BLOCK16_H
#define BLOCK16_H	1


//****************************************************************
//* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
//****************************************************************


typedef struct block16_data_s		BLOCK16_DATA;





/****************************************************************
* * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
****************************************************************/

#ifdef	__cplusplus
extern	"C" {
#endif

    
    // block16_Open calculates the needed buffer size, allocates an
    // area and sets up the control portion of the block.
    BLOCK16_DATA *	block16_Open(
                                 uint16_t        headerSize,
                                 uint16_t        dataSize
                                 );
    
    
    // block16_CalcBlocksize calculates the size of the block in bytes
    // given the header and data sizes. If the total size exceeds
    // 64k, then 0 is returned.
    uint16_t		block16_CalcBlockSize(
        uint16_t        headerSize,
        uint16_t        dataSize
    );


    // block16_AddData adds Data to the end of the buffer.
    bool			block16_AddData(
                                    BLOCK16_DATA	*this,
                                    uint16_t        size,
                                    void            *data
                                    );
    
    
    // block16_Close frees the block and its associated data.
    BLOCK16_DATA *	block16_Close(
        BLOCK16_DATA	*this
    );
        
        
    // block16_Copy allocates a new block copying all the data from
    // this block to the new block.
    BLOCK16_DATA *	block16_Copy(
        BLOCK16_DATA	*this
    );
        

    // block16_DataPtr returns a pointer to the beginning of the data
    // in the block. Care must be taken how this pointer is used to
    // maintain the integrity of the block.
    void *          block16_DataPtr(
        BLOCK16_DATA    *this
    );


    // block16_DataSize provides the size of the data portion
    // of the block.
    uint16_t        block16_DataSize(
        BLOCK16_DATA    *this
    );
    
    
    // block16_DataSize provides the size of the data portion
    // of the block that is in use.
    uint16_t        block16_DataUsed(
        BLOCK16_DATA    *this
    );
    
    
    // block16_DataUseAll sets the data used size to be the max
    // maximum allowed for this buffer.
    bool			block16_DataUseAll(
        BLOCK16_DATA	*this
    );
    
    
    // block16_HeaderGet copies the Header Data to the specified
    // buffer using block16_HeaderSize() to determine the amount
    // of data to be transferred.
    bool			block16_HeaderGet(
        BLOCK16_DATA	*this,
        void            *pHeader
    );


    // block16_HeaderOffset returns the offset into the block for
    // the header. This may be needed for other objects such as
    // listdl.
    uint16_t        block16_HeaderOffset(
        void
    );
    
    
    // block16_DataPtr returns a pointer to the beginning of the header
    // in the block. Care must be taken how this pointer is used to
    // maintain the integrity of the block.
    void *          block16_HeaderPtr(
        BLOCK16_DATA      *this
    );


    // block16_HeaderPut copies the Header Data from the specified
    // buffer using block16_HeaderSize() to determine the amount
    // of data to be transferred.
    bool			block16_HeaderPut(
        BLOCK16_DATA	*this,
        void            *pHeader
    );


    // block16_HeaderSize provides the size of the header portion
    // of the block.
    uint16_t        block16_HeaderSize(
        BLOCK16_DATA    *this
    );


    // block16_Init assumes that it has been passed an area of the
    // size that block16_CalcBlockSize would provide and sets up
    // the control portion of the block. This can be used when
    // you want a block within another structure. For instance,
    // you could use block16_Open() to create a very large block
    // and then break it up into smaller blocks internally by
    // using this function.
    bool			block16_Init(
        BLOCK16_DATA	*this,
        uint16_t        headerSize,
        uint16_t        dataSize
    );
    
    
    // block16_UnusedDataSize calculates the amount of remaining
    // space in the block that is unused for data.
    uint16_t		block16_UnusedDataSize(
        BLOCK16_DATA	*this
    );


    
#ifdef	__cplusplus
};
#endif




#endif
