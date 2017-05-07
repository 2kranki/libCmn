// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Fixed Sized Header and Data Areas (block) Header
//****************************************************************
/*
 * Program
 *			A block with fixed size header and data areas (block)
 * Purpose
 *			This object provides the means of manipulating a data
 *          block that consists of a fixed size header and a fixed
 *          size data area whose combined sizes must fit in a
 *          uint32_t.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	01/05/2016 Generated
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


#ifndef         BLOCK_H
#define         BLOCK_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct block_data_s	BLOCK_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    BLOCK_DATA *     block_Alloc(
    );
    
    
    uint32_t		block_CalcBlockSize(
        uint32_t        headerSize,
        uint32_t        dataSize
    );
    
    
    BLOCK_DATA *     block_New(
    );
    
    BLOCK_DATA *    block_NewWithSizes(
        uint32_t        headerSize,
        uint32_t        dataSize
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    void *          block_getData(
        BLOCK_DATA     *this
    );
    
    
    uint32_t        block_getDataOffset(
        BLOCK_DATA     *this
    );
    
    
    uint32_t        block_getDataSize(
        BLOCK_DATA     *this
    );
    
    
    void *          block_getHeader(
        BLOCK_DATA     *this
    );
    
    
    uint32_t        block_getHeaderSize(
        BLOCK_DATA     *this
    );
    
    
    ERESULT         block_getLastError(
        BLOCK_DATA     *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    // block_DataPtr returns a pointer to the beginning of the data
    // in the block. Care must be taken how this pointer is used to
    // maintain the integrity of the block.
    void *          block_DataPtr(
        BLOCK_DATA      *this
    );
    
    
    /* Disable() terminates the block block.
     */
    bool        block_Disable(
        BLOCK_DATA		*cbp
    );


    /* Enable() starts the block.
     */
    bool        block_Enable(
        BLOCK_DATA		*cbp
    );


    bool            block_IsEnabled(
        BLOCK_DATA      *this
    );
    
    
    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    BLOCK_DATA *    block_Init(
        BLOCK_DATA      *this
    );

    BLOCK_DATA *    block_InitWithSizes(
        BLOCK_DATA      *this,
        uint32_t        headerSize,
        uint32_t        dataSize
    );
    

    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = block_ToDebugString(this,4);
     @endcode:
     @param:    this    BLOCK object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    block_ToDebugString(
        BLOCK_DATA     *cbp,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BLOCK_H */

