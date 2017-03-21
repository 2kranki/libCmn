//****************************************************************
//				C Fixed Array (CFA) Internal Header				
//****************************************************************
// vi: nu:noai:ts=4:sw=4

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




/****************************************************************
* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
****************************************************************/

/* Header File Inclusion */
#include        <cfa.h>


#ifndef         CFA_INTERNAL_H
#define         CFA_INTERNAL_H	1



#ifdef	__cplusplus
extern	"C" {
#endif
    
    
    /*                Main Control Block
     */
    /* This control block resides only in memory and is used to provide
     * the information necessary to access the CFA data.
     */
#pragma pack(push, 1)
    struct cfa_data_s {
        /* Warning - OBJ_DATA must be first in this object!
         */
        OBJ_DATA        super;
        OBJ_IUNKNOWN    *pSuperVtbl;

        uint16_t		cEntries;		// Number of entries in Array
        uint16_t		entrySize;		// Entry Size
        uint16_t		actualEntrySize;// Entry Size Used (rounded to 4 bytes)
        uint16_t        reserved;

        void			**ppIndex;		// Array Index Starting point
        // --- Index 
        //		(cEntries * sizeof(void *)) where each entry contains a
        //		pointer to the actual data in the table.
        //
        // --- Data Entries
        //
    };
#pragma pack(pop)


    extern
    const
    OBJ_IUNKNOWN    cfa_Vtbl;

    
    
    
    // Internal Functions
#ifdef RMW_DEBUG
    bool		cfa_Validate(
        CFA_DATA       *cbp
    );
#endif

    void        cfa_Dealloc(
        OBJ_ID      objId
    );



#ifdef	__cplusplus
}
#endif

#endif	/* CFA_INTERNAL_H */

