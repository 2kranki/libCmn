// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Simple Index (sidx) Header
//****************************************************************
/*
 * Program
 *			Simple Index (sidx)
 * Purpose
 *			This object provides a simple index into some other
 *          set of objects. It stores an index amount and an
 *          offset in its table. When a value is needed, the
 *          closest value and offset will be returned. The index
 *          is of a fixed size with a starting interval between
 *          entries. When the index becomes full, the interval
 *          is doubled and every other entry is removed.
 *
 *          Normally, you would call addIndex() every time that
 *          you read a line or process something. The index will
 *          automatically adjust when it gets full. It just makes
 *          it easier to get to some point in a file or process
 *          if that needs
 * Remarks
 *	1.      ???
 *
 * History
 *	09/07/2015 Generated
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


#ifndef         SIDX_H
#define         SIDX_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct sidx_data_s	SIDX_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    SIDX_DATA *     sidx_Alloc(
        uint16_t    tableSize
    );
    
    
    SIDX_DATA *     sidx_New(
        uint16_t    tableSize
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        sidx_getInterval(
        SIDX_DATA       *this
    );
    
    
    uint16_t        sidx_getSize(
        SIDX_DATA       *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    // Every time that a new item is added to the object that needs
    // indexing, AddIndex() should be called. It will only save the
    // item based on the current interval.
    bool            sidx_AddIndex(
        SIDX_DATA       *this,
        uint32_t        index,
        uint32_t        offset
    );
    

    // FindIndex() finds the closest index in its table that minimizes
    // the forward search needed to find the actual object needed.
    bool            sidx_FindIndex(
        SIDX_DATA		*this,
        uint32_t        index,
        uint32_t        *pIndex,
        uint32_t        *pOffset
    );
    
    
    SIDX_DATA *     sidx_Init(
        SIDX_DATA       *this,
        uint32_t        interval
    );


    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     sidx_ToDebugString(
        SIDX_DATA       *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SIDX_H */

