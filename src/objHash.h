// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          OBJHASH Console Transmit Task (objHash) Header
//****************************************************************
/*
 * Program
 *			Separate objHash (objHash)
 * Purpose
 *			This object provides a standardized way of handling
 *          a Hash table for objects. The objects must support
 *          the compare() and hash() functions in their object
 *          vtbl. Since this is how the objects are looked at,
 *          this table has no knowledge of a key and objects
 *          must always be suppied for seaches, deletions, etc.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	10/24/2015 Generated
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


#ifndef         OBJHASH_H
#define         OBJHASH_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct objHash_data_s	OBJHASH_DATA;


    // Prime numbers for hash table sizes within 16 bits
    // (Maximum size is 65535)
    typedef enum objHash_table_size_e {
        OBJHASH_TABLE_SIZE_XXXXXSMALL = 5,
        OBJHASH_TABLE_SIZE_XXXXSMALL = 17,
        OBJHASH_TABLE_SIZE_XXXSMALL = 31,
        OBJHASH_TABLE_SIZE_XXSMALL = 61,
        OBJHASH_TABLE_SIZE_XSMALL = 127,
        OBJHASH_TABLE_SIZE_SMALL = 257,
        OBJHASH_TABLE_SIZE_MEDIUM = 2053,
        OBJHASH_TABLE_SIZE_LARGE  = 4099,
        OBJHASH_TABLE_SIZE_XLARGE = 16411
    } OBJHASH_TABLE_SIZE;
    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    OBJHASH_DATA *  objHash_Alloc(
        void
    );
    
    
    OBJHASH_DATA *  objHash_New(
        uint16_t        cHash       // [in] Hash Table Size
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    // Add() creates a new node and adds it to the hash table if the
    // supplied key does not exist in the table.
    ERESULT         objHash_Add(
        OBJHASH_DATA    *this,
        OBJ_ID			pObject
    );
    
    
    // Delete() deletes the first entry found matching the given object.
    ERESULT         objHash_Delete(
        OBJHASH_DATA    *this,
        OBJ_ID          *pObject
    );
    
    
    /* Find() returns the data associated with the given object if 
     * found, otherwise OBJ_NIL is returned.
     */
    OBJ_ID          objHash_Find(
        OBJHASH_DATA    *this,
        OBJ_ID          *pObject
    );
    
    
    OBJHASH_DATA *  objHash_Init(
        OBJHASH_DATA    *this,
        uint16_t        cHash       // [in] Hash Table Size
    );


    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     objHash_ToDebugString(
        OBJHASH_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJHASH_H */

