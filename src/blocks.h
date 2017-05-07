// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          A List of Data Blocks (blocks) Header
//****************************************************************
/*
 * Program
 *			A List of Data Blocks (blocks)
 * Purpose
 *			This object provides a updatable list of data blocks.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	09/04/2016 Generated
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


#ifndef         BLOCKS_H
#define         BLOCKS_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct blocks_data_s	BLOCKS_DATA;    // Inherits from OBJ.

    typedef struct blocks_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in blocks_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BLOCKS_DATA *);
    } BLOCKS_VTBL;



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
     @return:   pointer to blocks object if successful, otherwise OBJ_NIL.
     */
    BLOCKS_DATA * blocks_Alloc(
    );
    
    
    BLOCKS_DATA * blocks_New(
        uint16_t    blockSize
    );
    
    
    /*!
     Return the amount of overhead space that will be required from the block
     for blocks to provide proper support.  This amount should be added to the
     blocksize needed when calling New() or Init(). Note that this is a class
     method and does not need a reference to a BLOCKS_DATA.
     Example:
     @code:
            uint16_t overhead = blocks_Overhead();
     @endcode:
     @return:   The amount needed from the blocksize for blocks_ to operate
                successfully.
     */
    uint16_t    blocks_Overhead(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        blocks_getBlockSize(
        BLOCKS_DATA     *this
    );
    
    
    ERESULT     blocks_getLastError(
        BLOCKS_DATA		*this
    );


    /*!
     Return the number of blocks in the list.
     Example:
     @code:
        uint32_t cBlocks = blocks_getSize(this);
     @endcode:
     @param:    this    BLOCKS object pointer
     @return:   The amount the number of blocks in the list.
     */
    uint32_t        blocks_getSize(
        BLOCKS_DATA     *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    void *      blocks_Add(
        BLOCKS_DATA *this
    );


    void *      blocks_Block(
        BLOCKS_DATA *this,
        uint32_t    index           // Relative to 1
    );
    
    
    ERESULT     blocks_Delete(
        BLOCKS_DATA	*this,
        void        *pBlock
    );

   
    BLOCKS_DATA * blocks_Init(
        BLOCKS_DATA *this,
        uint16_t    blockSize
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = blocks_ToDebugString(this,4);
     @endcode:
     @param:    this    BLOCKS object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    blocks_ToDebugString(
        BLOCKS_DATA     *this,
        int             indent
    );
    
    
    uint32_t        blocks_Useable(
        BLOCKS_DATA		*this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BLOCKS_H */

