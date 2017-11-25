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


#ifndef         BLOCK16_H
#define         BLOCK16_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct block16_data_s	BLOCK16_DATA;

    
    typedef struct block16_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in bptree_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPTREE_DATA *);
    } BLOCK16_VTBL;
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    BLOCK16_DATA *  block16_Alloc(
        void
    );
    
    
    uint32_t		block16_CalcBlockSize(
        uint16_t        headerSize,
        uint16_t        dataSize
    );
    
    
    BLOCK16_DATA *  block16_New(
        void
    );
    
    BLOCK16_DATA *  block16_NewWithSizes(
        uint16_t        headerSize,
        uint16_t        dataSize
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    void *          block16_getData(
        BLOCK16_DATA   *this
    );
    
    
    uint16_t        block16_getDataOffset(
        BLOCK16_DATA   *this
    );
    
    
    uint16_t        block16_getDataSize(
        BLOCK16_DATA   *this
    );
    
    
    /*!
     DataUsed is a convenience property to be used if it is necessary
     to know or control how much of the data area has been used.
     @warning: The addData() method relies on .
     */
    uint16_t        block16_getDataUsed(
        BLOCK16_DATA    *this
    );
    
    bool            block_setDataUsed(
        BLOCK16_DATA    *this,
        uint16_t        value
    );
    
    
    void *          block16_getHeader(
        BLOCK16_DATA   *this
    );
    
    
    uint16_t        block16_getHeaderSize(
        BLOCK16_DATA   *this
    );
    
    
    ERESULT         block16_getLastError(
        BLOCK16_DATA   *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add data to the end of the data area within the block.
     @param     this    BLOCK32 object pointer
     @return    true if successful, otherwise false.
     */
    bool			block16_AddData(
        BLOCK16_DATA	*this,
        uint16_t        size,
        void            *pData
    );
    
    
    // block_DataPtr returns a pointer to the beginning of the data
    // in the block. Care must be taken how this pointer is used to
    // maintain the integrity of the block.
    void *          block16_DataPtr(
        BLOCK16_DATA   *this
    );
    
    
    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    BLOCK16_DATA *  block16_Init(
        BLOCK16_DATA   *this
    );

    BLOCK16_DATA *  block16_InitWithSizes(
        BLOCK16_DATA    *this,
        uint16_t        headerSize,
        uint16_t        dataSize
    );
    

    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = block_ToDebugString(this,4);
     @endcode
     @param     this    BLOCK32 object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    block16_ToDebugString(
        BLOCK16_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BLOCK16_H */

