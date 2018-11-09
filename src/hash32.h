// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  HASH32 Table (hash32)
//****************************************************************
/*
 * Program
 *				hash32 table (hash32)
 * Purpose
 *				These subroutines provide an open chained hash
 *              table for keys of uint32_t. Internal nodes are
 *              blocked to limit memory fragmentation and the
 *              maximum hash table size is 65535. The overall
 *              size can grow bigger since it would be 65535
 *              chains of nodes.
 *
 * Remarks
 *	1.      N/A
 *
 * History
 *	06/07/2015 Generated
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


#ifndef         HASH32_H
#define         HASH32_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct hash32_data_s	HASH32_DATA;

    typedef struct hash32_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in hex_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(HEX_DATA *);
    } HASH32_VTBL;
    
    

    // Prime numbers for hash table sizes within 16 bits
    // (Maximum size is 65535)
    typedef enum hash32_table_size_e {
        HASH32_TABLE_SIZE_XXXSMALL = 31,
        HASH32_TABLE_SIZE_XXSMALL = 61,
        HASH32_TABLE_SIZE_XSMALL = 127,
        HASH32_TABLE_SIZE_SMALL = 257,
        HASH32_TABLE_SIZE_MEDIUM = 2053,
        HASH32_TABLE_SIZE_LARGE  = 4099,
        HASH32_TABLE_SIZE_XLARGE = 16411
    } HASH32_TABLE_SIZE;
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the hash32.
     */
    HASH32_DATA *   hash32_Alloc(
        void
    );
    
    
    OBJ_ID          hash32_Class(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        hash32_getCount(
        HASH32_DATA     *this
    );


    bool            hash32_getDuplicates(
        HASH32_DATA     *this
    );
    
    bool            hash32_setDuplicates(
        HASH32_DATA     *this,
        bool            fValue
    );
    

    

    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    bool            hash32_Add(
        HASH32_DATA     *this,
        uint32_t        key,
        void			*pData
    );
    
    
    bool            hash32_Delete(
        HASH32_DATA     *this,
        uint32_t        key
    );
    
    
    void *          hash32_Find(
        HASH32_DATA     *this,
        uint32_t        key
    );
    
    
    HASH32_DATA *   hash32_Init(
        HASH32_DATA     *this,
        uint16_t        cHash           // Hash Table Size (Prime Number)                                  
    );


    bool            hash32_Update(
        HASH32_DATA     *this,
        uint32_t        key,
        void            *pData
    );

    
    
#ifdef	__cplusplus
}
#endif

#endif	/* HASH32_H */

