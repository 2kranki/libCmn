// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Indexed Data Block (blkidx16) Header
//****************************************************************
/*
 * Program
 *			Indexed Data Block (blkidx16)
 * Purpose
 *			These subroutines provide a general purpose set of
 *			routines to build and manipulate dynamic tables of
 *			variable length data.
 *
 *          All offsets within the block are numeric. No addresses
 *          are maintained in the block. So, it can be safely
 *          written to disk if needed.
 *
 *          The block header can contain an area reserved for
 *          any use. Just specify the amount at open time.
 *          Also, each record contains a uint32_t amount which
 *          can be used for anything.
 *
 *
 * Remarks
 *	1.			Table Entries are numbered starting with one.  If
 *				zero is returned for an entry number, it should be
 *				considered an error.
 *	2.			Once entries are gotten they do not get moved dyna-
 *				mically.  So, if you convert an entry number into
 *				an address, it will be valid until you delete that
 *				entry.
 * References
 *		"Data Structures and Algorithms", Alfred V. Aho et al,
 *			Addison-Wesley, 1985
 *		"Data Structures using C", Aaron M. Tenenbaum et al,
 *			Prentice-Hall, 1990
 *		"Programs and Data Structures in C", Leendert Ammeraal,
 *			John Wiley & Sons, 1987
 *
 * History
 *	03/05/2017 Generated
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


#ifndef         BLKIDX16_H
#define         BLKIDX16_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct blkidx16_data_s	BLKIDX16_DATA;    // Inherits from OBJ.

    typedef struct blkidx16_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in blkidx16_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BLKIDX16_DATA *);
    } BLKIDX16_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    BLKIDX16_DATA *     blkidx16_Alloc(
    );
    
    
    BLKIDX16_DATA *     blkidx16_New(
        uint16_t        blockSize,          // Size of the Block
        uint16_t        rsvdSize            // Size of Reserved Area
                                            // within the block
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     blkidx16_getLastError(
        BLKIDX16_DATA		*this
    );


    /*!
     Return the amount of unused space in the index block.
     @param:    this    BLKIDX16 object pointer
     @return:   If successful, the amount of unused space in the
                block
     */
    uint16_t        blkidx16_getUnused(
        BLKIDX16_DATA   *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         blkidx16_AddData(
        BLKIDX16_DATA   *this,
        uint16_t        dataSize,
        void            *pData,
        uint16_t        *pIndex             // Optional Returned Index
    );


    uint16_t        blkidx16_DataSize(
        BLKIDX16_DATA	*this,
        uint16_t        index
    );
    
    
    BLKIDX16_DATA * blkidx16_Init(
        BLKIDX16_DATA   *this,
        uint16_t        blockSize,          // Size of the Block
        uint16_t        rsvdSize            // Size of Reserved Area
                                            // within the block
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = blkidx16_ToDebugString(this,4);
     @endcode:
     @param:    this    BLKIDX16 object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    blkidx16_ToDebugString(
        BLKIDX16_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BLKIDX16_H */

