// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   nodeScan_internal.h
 *	Generated 10/16/2015 09:19:12
 *
 * Notes:
 *  --	N/A
 *
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



#include    <nodeScan.h>
#include    <nodeArray.h>


#ifndef NODESCAN_INTERNAL_H
#define	NODESCAN_INTERNAL_H


#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum tok_typ_e {
        TOK_TYP_EOF=-1,
        TOK_TYP_INVALID=0,
        TOK_TYP_LPAREN=1,
        TOK_TYP_RPAREN=2,
        TOK_TYP_PERCENT=3,
        TOK_TYP_INT=4,
        TOK_TYP_COLON=5,
        TOK_TYP_POUND=6,
        TOK_TYP_PERIOD=7
    } TOK_TYP;
#define TOK_TYP_VALID(x) ((x >= TOK_TYP_LPAREN) && (x <= TOK_TYP_PERIOD))
    
    typedef struct scanner_entry_s {
        int         nodeClass;               // Node Class for comparison
        int         scanLabel;              // Optional index to Returned Node Pointer
    } SCANNER_ENTRY;
    
    // MAX values should be evenly divisible by 8
#define MAX_SCANNER_ENTRIES     32
#define MAX_SCANNER_LABELS      16

#pragma pack(push, 1)
struct nodeScan_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Common Data
    uint32_t        index;
    uint32_t        rsvd32_1;
    NODEARRAY_DATA  *pArray;    // linearalized Tree converted to an array with
    //                          // up/down members.

    // ScanF Input
    ASTR_DATA       *pScanInput;
    uint32_t        curChar;
    int32_t         tokInt;
    
    // ScanF Scan Data
    uint32_t        offset;         // Offset within pArray of current scan comparison.
    uint32_t        scanLength;
    int32_t         nodeTypes[MAX_SCANNER_ENTRIES];
    uint32_t        rsvd32_2;
    uint32_t        cLabels;        // Node Labels which are returned Node Pointers if
    //                              // matched
    NODE_DATA       **ppLabels[MAX_SCANNER_LABELS];

};
#pragma pack(pop)

    extern
    const
    NODESCAN_VTBL   nodeScan_Vtbl;
    extern
    const
    struct nodeScan_class_data_s   nodeScan_ClassObj;



    // Internal Functions
    void            nodeScan_Dealloc(
        OBJ_ID          objId
    );


    int             nodeScan_Lex(
        NODESCAN_DATA  *this
    );
    
    
    void *          nodeScan_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    );
    
    
#ifdef NDEBUG
#else
    bool			nodeScan_Validate(
        NODESCAN_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODESCAN_INTERNAL_H */

