// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   memOSX_internal.h
 *	Generated 02/08/2016 19:45:14
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




#include        <memOSX.h>
#include        <AStr.h>
#include        <listdl.h>
#include        <objArray.h>


#ifndef MEMOSX_INTERNAL_H
#define	MEMOSX_INTERNAL_H


#ifdef	__cplusplus
extern "C" {
#endif


    
    
    
    
    //*****************************************************************
    //* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
    //*****************************************************************
    
    //						Memory Block Header
    // This structure is the header of a memory block.	It lies before
    // the actual memory block.
    typedef struct mem_blockHeader_s     MEM_BLOCKHEADER;
    
    struct mem_blockHeader_s {
        LISTDL_NODE		LDL;
        size_t          cbActual;			// Actual Block Size in uint8_t's
        size_t          cbSize;             // Requested Size in uint8_t's
        size_t          iLine;				// Creation Line Number with File
        size_t          size;				// True Size of Block excluding Header
        const
        char			*pFile;				// Creation File Name
        uint16_t		flags;
#define MEM_FLAG_OBJECT 0x0001
        uint16_t		filler1;
        MEMOSX_DATA     *pMem;
        uint8_t			check[16];			// Check Value for Underrun
        // >>>>>>>>>>>>>>>>>  *** WARNING *** <<<<<<<<<<<<<<<<<<<<<<<<<
        // The offset of the Data must be on a DWORD boundary to be compatible
        // with OS/2 and MS/DOS.
        uint8_t			data[0];
    };
    
    typedef struct mem_blockTrailer_s     MEM_BLOCKTRAILER;
    
    struct mem_blockTrailer_s {
        uint8_t			check[16];			// Check Value for Overrun
    };
#define BLOCK_PDATA(pBlk) (pBlk->data)
#define BLOCK_PTRAILER(pBlk) ((MEM_BLOCKTRAILER *)(&pBlk->data[pBlk->cbSize]))
#define	Data2Block( pData )	((void *)((uint8_t *)pData - offsetof(MEM_BLOCKHEADER,data)))



#pragma pack(push, 1)
struct memOSX_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;

    // Common Data
    LISTDL_DATA		blockList;
    bool			fDebugMemory;
    void            *pLeakExitObject;
    P_VOIDEXIT1     pLeakExit;          // Only called in memOSX_Dealloc if leaks are
    //                                  // present.
    const
    char            *pTitle;

};
#pragma pack(pop)

    extern
    const
    OBJ_IUNKNOWN    memOSX_Vtbl;



    // Internal Functions
    void            memOSX_Dealloc(
        OBJ_ID          objId
    );

    void			memOSX_DebugDumpBlock(
        MEMOSX_DATA		*this,
        const
        char			*pData
    );
    
    MEM_BLOCKHEADER * memOSX_DebugFind(
        MEMOSX_DATA		*this,
        void            *pData
    );
    
#ifdef NDEBUG
#else
    bool			memOSX_Validate(
        MEMOSX_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* MEMOSX_INTERNAL_H */

