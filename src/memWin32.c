// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   memWin32.c
 *	Generated 02/08/2016 19:45:14
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include    "memWin32_internal.h"
#include    "trace.h"
//#include    <pthread.h>
#include    <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    static
    MEMMSC_DATA     shared = {{0}};
    static
    MEMMSC_DATA     *pShared = OBJ_NIL;
    
    static
    const                          // 1234567890123456
    char            CheckValue[16] = "XYZZY234156xyzzy";
    
    static
    const
    char            *pHexChr = "0123456789ABCDEF";
    
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    // 		HexDigit - Print a Hexadecimal Digit
    //---------------------------------------------------------------
    
    static
    void            hex_putDigit(
        uint8_t         input,
        char            **ppBuffer      // Ascii representation of digit stored
                                        // at ptr and ptr is advanced
    )
    {
        char        	WrkChr;
        
        // Do initialization.
        
        // Print the Number.
        WrkChr = (char)(input & 0x0F);
        WrkChr = pHexChr[(int)WrkChr];
        //    WrkChr = (char)( WrkChr < 10 ? WrkChr + '0' : WrkChr + 'A' - 10 );
        **ppBuffer = WrkChr;
        ++*ppBuffer;
        
        // Return to caller.
    }
    
    
    
    
    //---------------------------------------------------------------
    //							hex_putUint8
    //---------------------------------------------------------------
    
    static
    uint32_t        hex_putUint8(
        uint8_t	        input,
        char            **ppBuffer      // Ascii representation of digit stored
                                        // at ptr and ptr is advanced
    )
    {
        
        // Do initialization.
        
        // Print the byte.
        if (ppBuffer) {
            hex_putDigit( (uint8_t)(input >> 4), ppBuffer );
            hex_putDigit( input, ppBuffer );
        }
        
        // Return to caller.
        return 2;
    }
    
    
    
    
    //---------------------------------------------------------------
    //							hex_putUint32
    //---------------------------------------------------------------
    
    static
    uint32_t        hex_putUint32(
        uint32_t        input,
        char            **ppBuffer      // Ascii representation of digit stored
                                        // at ptr and ptr is advanced
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        
        // Print the byte.
        len += hex_putUint8( (uint8_t)(input >> 24), ppBuffer );
        len += hex_putUint8( (uint8_t)(input >> 16), ppBuffer );
        len += hex_putUint8( (uint8_t)(input >> 8), ppBuffer );
        len += hex_putUint8( (uint8_t)input, ppBuffer );
        
        // Return to caller.
        return len;
    }
    
    
    
    
    //---------------------------------------------------------------
    //						hex_putUint64
    //---------------------------------------------------------------
    
    static
    uint32_t        hex_putUint64(
        uint64_t        input,
        char            **ppBuffer      // Ascii representation of digit stored
                                        // at ptr and ptr is advanced
    )
    {
        uint32_t        len = 0;
        
        // Do initialization.
        
        // Print the byte.
        len += hex_putUint32( (uint32_t)(input >> 32), ppBuffer );
        len += hex_putUint32( (uint32_t)input, ppBuffer );
        
        // Return to caller.
        return len;
    }
    
    
    
    
    //---------------------------------------------------------------
    //						hex_putBytes16
    //---------------------------------------------------------------
    
    static
    uint32_t            hex_putBytes16_32(
        uint16_t            cLen,
        const
        void                *pData,
        uint16_t            cBuffer,
        char                **ppBuffer      // Hex and Ascii representation of data
    )
    {
        uint32_t            i;
        uint32_t            j;
        char                wrkChr;
        uint32_t            len = 0;
        
        // Do initialization.
        if( 0 == cLen )
            return 0;
        if( NULL == pData )
            return 0;
        if( 16 < cLen )
            cLen = 16;
        
        //  Display the line.
#ifdef __APPLE__
        len += hex_putUint64( (uint64_t)pData, ppBuffer );
#else
        len += hex_putUint32( (uint32_t)pData, ppBuffer );
#endif
        if (ppBuffer) {
            **ppBuffer = ' ';
            ++*ppBuffer;
        }
        ++len;
        for( i=0; i<4; i++ ) {
            if (ppBuffer) {
                **ppBuffer = ' ';
                ++*ppBuffer;
            }
            ++len;
            for( j=0; j<4; j++ ) {
                if( (4*i+j) < cLen ) {
                    len += hex_putUint8( ((uint8_t *)pData)[(4*i)+j], ppBuffer );
                }
                else {
                    if (ppBuffer) {
                        **ppBuffer = ' ';
                        ++*ppBuffer;
                    }
                    ++len;
                    if (ppBuffer) {
                        **ppBuffer = ' ';
                        ++*ppBuffer;
                    }
                    ++len;
                }
            }
        }
        if (ppBuffer) {
            **ppBuffer = ' ';
            ++*ppBuffer;
        }
        ++len;
        if (ppBuffer) {
            **ppBuffer = ' ';
            ++*ppBuffer;
        }
        ++len;
        if (ppBuffer) {
            **ppBuffer = '*';
            ++*ppBuffer;
        }
        ++len;
        for( i=0; i<16; i++ ) {
            wrkChr = (char)((uint8_t)((uint8_t *)pData)[i] & 0x7F);
            if (wrkChr == 0x7F)
                wrkChr = '.';
            if (wrkChr < ' ')
                wrkChr = '.';
            if( i < cLen ) {
                if (ppBuffer) {
                    **ppBuffer = wrkChr;
                    ++*ppBuffer;
                }
                ++len;
            }
            else {
                if (ppBuffer) {
                    **ppBuffer = ' ';
                    ++*ppBuffer;
                }
                ++len;
            }
        }
        if (ppBuffer) {
            **ppBuffer = '*';
            ++*ppBuffer;
        }
        ++len;
        if (ppBuffer) {
            **ppBuffer = '\0';
            ++*ppBuffer;
        }
        ++len;
        
        // Return to caller.
        return len;
    }
    
    
    
    //---------------------------------------------------------------
    //			mem_DebugDump - Check for Any Memory Blocks
    //---------------------------------------------------------------

    void			memMSC_DebugDumpBlock(
        MEMMSC_DATA		*this,
        const
        char			*pData
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        bool			fFnd = false;
        OBJ_DATA        *pObj;
        ASTR_DATA       *pStr;
        char            buffer[2048];
        char            *pBuffer = buffer;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        // Point back to the Block Header and verify what we can.
        pActual = Data2Block(pData);
        if (pActual->pMem == this) {
        }
        else {
            if( !memMSC_Validate( pActual->pMem ) ) {
                DEBUG_BREAK();
                return;
            }
            fprintf(
                    stderr,
                    "===> Warning - memMSC_DebugDumpBlock is switching this from %p to %p\n",
                    this,
                    pActual->pMem
                    );
            this = pActual->pMem;       // Oops, it was malloc'd from
            // a different memOSX object.
        }
        
        // Check for Underrun.
        if( 0 == memcmp( pActual->check, CheckValue, sizeof(CheckValue) ) )
            fFnd = true;
        else {
            fFnd = false;
        }
        
        fprintf(stderr, "\n\ndata ptr: %p\n", pData);
        if (fFnd) {
            fprintf(stderr, "\tIs an allocated area from memOSX %p\n", pActual->pMem);
            fprintf(stderr, "\tRequested Size=%ld  Actual Size=%ld\n",
                            pActual->cbSize,pActual->cbActual);
            if (pActual->flags & MEM_FLAG_OBJECT) {
                const
                OBJ_INFO        *pInfo = obj_getInfo((OBJ_ID)pData);
                fprintf(
                        stderr,
                        "Object:  Type: (%d)%s\n",
                        obj_getType((OBJ_ID)pData),
                        (pInfo ? pInfo->pClassName : "???")
                );
                fprintf(stderr, "\tRetain Count: %d\n", obj_getRetainCount(&pActual->data));
                pObj = (OBJ_DATA *)pData;
                if (pObj->pVtbl->pToDebugString) {
                    pStr = pObj->pVtbl->pToDebugString(pObj,0);
                    fprintf(stderr, "debug: \n%s\n\n\n", AStr_getData(pStr));
                    obj_Release(pStr);
                }
            }
        }
        else {
            fprintf(stderr, "\tDoes not seem to be a memOSX allocated area.\n");
        }
        fprintf( stderr, "\nData @ %p:\n", pData );
        pBuffer = buffer;
        hex_putBytes16_32(64, pData, 2048, &pBuffer);
        fprintf(stderr, "%s\n\n", buffer);
    
        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //      memMSC_DebugFind - Find a memory block on the chain
    //---------------------------------------------------------------
    
    MEM_BLOCKHEADER * memMSC_DebugFind(
        MEMMSC_DATA		*this,
        void            *pData
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        
        // Do initialization.
        //fprintf(stderr, "memMSC_DebugFind &this=%p\n", &this);
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        // Find the Area in the Block Header List.
        for(	pActual = (MEM_BLOCKHEADER *)listdl_Head( &this->blockList );
            pActual;
            pActual = (MEM_BLOCKHEADER *)listdl_Next( &this->blockList, pActual )
            ) {
            if( pActual->data == pData ) {
                break;
            }
        }
        
        // Return to caller.
        return pActual;
    }
    
    
    
    //---------------------------------------------------------------
    //			mem_DebugInternalMalloc - Allocate a Memory Block
    //---------------------------------------------------------------
    static
    MEM_BLOCKHEADER *
                        memMSC_DebugInternalMalloc(
        MEMMSC_DATA     *this,
        size_t			cbSize,
        const
        char			*pFile,
        size_t			iLine
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        MEM_BLOCKTRAILER
                        *pTrailer = NULL;
        void			*pRet = NULL;
        size_t          cbActual;
        
        // Do initialization.
        if (cbSize == 0) {
            return NULL;
        }
        
        // Allocate the memory.
        cbActual = cbSize + sizeof(MEM_BLOCKHEADER);
        cbActual += sizeof(MEM_BLOCKTRAILER);
        pActual = malloc( cbActual );
        if( NULL == pActual ) {
            pRet = NULL;
            goto Exit00;
        }
        pRet =	(MEM_BLOCKHEADER *)listdl_Add2Tail( &this->blockList, pActual );
        if( NULL == pRet ) {
            (void)free( pActual );
            pActual = NULL;
            goto Exit00;
        }
        pActual->cbActual = cbActual;
        pActual->cbSize = cbSize;
        memmove( pActual->check, CheckValue, sizeof(CheckValue) );
        memset( pActual->data, 0, cbSize );
        pTrailer = (void *)((char *)&pActual->data[0] + pActual->cbSize);
        memmove( pTrailer, CheckValue, sizeof(CheckValue) );
        pActual->pFile = pFile;
        pActual->iLine = iLine;
        pActual->flags = 0;
        pActual->filler1 = 0;
        pActual->pMem = this;
        
        // Return to caller.
    Exit00:
        // Insure 4-byte alignment.
        if (pActual && !(((int)pActual & 0x03) == 0) ) {
            DEBUG_BREAK();
        }      
        return pActual;
    }
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    MEMMSC_DATA *     memMSC_Alloc(
    )
    {
        MEMMSC_DATA       *this;
        uint32_t        cbSize = sizeof(MEMMSC_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return( this );
    }



    MEMMSC_DATA *     memMSC_New(
    )
    {
        MEMMSC_DATA       *this;
        
        this = memMSC_Alloc( );
        if (this) {
            this = memMSC_Init( this );
        } 
        return( this );
    }



    MEMMSC_DATA *   memMSC_Shared(
    )
    {
        //int             iRc;
        //MEMMSC_DATA     *pShared;
        
        if (pShared) {
        }
        else {
            pShared = memMSC_Init(&shared);
        }
        
        return pShared;
    }
    
    
    MEMMSC_DATA *   memMSC_SharedReset(
    )
    {
        
        if (pShared) {
            obj_Release(pShared);
            pShared = OBJ_NIL;
            memset(&shared, 0, sizeof(MEMMSC_DATA));
        }
        
        return pShared;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    bool            memMSC_getDebug(
        MEMMSC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        return this->fDebugMemory;
    }

    bool            memMSC_setDebug(
        MEMMSC_DATA     *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        this->fDebugMemory = value;
        return true;
    }



    uint32_t        memMSC_getSize(
        MEMMSC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        return( 0 );
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            memMSC_Dealloc(
        OBJ_ID          objId
    )
    {
        MEMMSC_DATA     *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        // Validate the Memory Block Chain if requested.
        if( this->fDebugMemory ) {
            memMSC_DebugCheck( this, NULL, 0 );
        }
        if (listdl_Count(&this->blockList)) {
            memMSC_DebugDump(this, "memMSC_Dealloc", 0);
        }
        
        obj_Dealloc( this );
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //			mem_DebugCalloc - Allocate a Memory Block
    //---------------------------------------------------------------

    void *          memMSC_DebugCalloc(
        MEMMSC_DATA		*this,
        size_t			cNum,
        size_t			cSize,
        const
        char			*pFilePath,
        size_t			iLine
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        void			*pRet = NULL;
        size_t          cbRequest;
        
        // Do initialization.
        //fprintf(stderr, "mem_DebugCalloc &this=%p\n", &this);
        cbRequest = cNum * cSize;
        
        // Validate the Memory Block Chain if requested.
        if( this->fDebugMemory ) {
            memMSC_DebugCheck( this, pFilePath, iLine );
        }
        
        pActual = memMSC_DebugInternalMalloc( this, cbRequest, pFilePath, iLine );
        pRet = (void *)pActual->data;
        memset(pRet, 0, cbRequest);
        
        // Return to caller.
    //Exit00:
        // Insure 4-byte alignment.
        if (pRet && !(((int)pRet & 0x03) == 0) ) {
            DEBUG_BREAK();
        }      
        return( pRet );
    }
    
    
    
    
    //---------------------------------------------------------------
    //			memMSC_DebugCheck - Check for Bad Memory Blocks
    //---------------------------------------------------------------
    
    bool			memMSC_DebugCheck(
        MEMMSC_DATA		*this,
        const
        char			*pFilePath,
        size_t			iLine
    )
    {
        bool			fRc = false;
        MEM_BLOCKHEADER *pActual = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        // Validate the Block List.
        fRc = listdl_IsValidList( &this->blockList );
        if( !fRc ) {
            DEBUG_BREAK();
            return fRc;
        }
        
        // Find the Area in the Block Header List.
        for(	pActual = (MEM_BLOCKHEADER *)listdl_Head( &this->blockList );
            pActual;
            pActual = (MEM_BLOCKHEADER *)listdl_Next( &this->blockList, pActual )
            ) {
            fRc = memMSC_DebugCheckArea( this, pActual->data, pFilePath, iLine );
            if( !fRc ) {
                DEBUG_BREAK();
                break;
            }
        }
        
        // Return to caller.
        return( fRc );
    }
    
    
    
    //---------------------------------------------------------------
    //		memMSC_DebugCheckArea - Check for a Bad Memory Block
    //---------------------------------------------------------------
    
    bool			memMSC_DebugCheckArea(
        MEMMSC_DATA		*this,
        void            *pData,
        const
        char			*pFilePath,
        size_t			iLine
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        MEM_BLOCKTRAILER
                        *pTrailer = NULL;
        MEM_BLOCKHEADER *pActualCalc = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pActualCalc = Data2Block(pData);
        if (pActualCalc->pMem == this) {
        }
        else {
            if( !memMSC_Validate( pActual->pMem ) ) {
                memMSC_DebugDumpBlock(this,pData);
                DEBUG_BREAK();
                return false;
            }
            fprintf(
                    stderr,
                    "===> Warning - memMSC_DebugRealloc is switching this from %p to %p\n",
                    this,
                    pActual->pMem
            );
            this = pActual->pMem;       // Oops, it was malloc'd from
                                        // a different memOSX object.
        }
        
        // Find the Area in the Block Header List.
        pActual = memMSC_DebugFind( this, pData );
        if( NULL == pActual ) {
            memMSC_DebugDumpBlock(this,pData);
            DEBUG_BREAK();
            return( false );
        }
        
        // Check for Underrun.
        if( 0 == memcmp( pActual->check, CheckValue, sizeof(CheckValue) ) )
            ;
        else {
            memMSC_DebugDumpBlock(this,pData);
            DEBUG_BREAK();
            return( false );
        }
        
        // Check for Overrun.
        pTrailer = BLOCK_PTRAILER(pActual);
        if( 0 == memcmp( pTrailer, CheckValue, sizeof(CheckValue) ) )
            ;
        else {
            memMSC_DebugDumpBlock(this,pData);
            DEBUG_BREAK();
            return( false );
        }
        
        // Return to caller.
        return( true );
    }
    
    
    
    //---------------------------------------------------------------
    //	mem_DebugDidAlloc - Did We previously allocate a Block
    //---------------------------------------------------------------
    
    bool			memMSC_DebugDidAlloc(
        MEMMSC_DATA		*this,
        void			*pData,
        const
        char			*pFilePath,
        size_t			iLine
    )
    {
        bool            fRc = false;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if( NULL == pData ) {
            return false;
        }
        
        // Validate the Memory Block Chain if requested.
        if( this->fDebugMemory ) {
            memMSC_DebugCheck( this, pFilePath, iLine );
        }
        
        fRc = memMSC_DebugCheckArea(this, pData, pFilePath, iLine);
        
        // Return to caller.
        return fRc;
    }
    
    
    
    
    //---------------------------------------------------------------
    //			mem_DebugDump - Check for Any Memory Blocks
    //---------------------------------------------------------------
    
    bool			memMSC_DebugDump(
        MEMMSC_DATA		*this,
        const
        char			*pFilePath,
        size_t			iLine
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        bool			fFnd = false;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        // Validate the chain.
        memMSC_DebugCheck( this, pFilePath, iLine );
        
        // Dump any areas found on the list.
        for(pActual = (MEM_BLOCKHEADER *)listdl_Head( &this->blockList );
            pActual;
            pActual = (MEM_BLOCKHEADER *)listdl_Next( &this->blockList, pActual )
            ) {
            if (trace_Shared() == (void *)&pActual->data) {
                continue;
            }
            memMSC_DebugDumpBlock(this, (const char *)&pActual->data);
            fFnd = true;
        }
        
        // Return to caller.
        return fFnd;
    }
    
    
    
    
    //---------------------------------------------------------------
    //				memMSC_DebugFree - Free an Allocated Block
    //---------------------------------------------------------------
    
    bool			memMSC_DebugFree(
        MEMMSC_DATA		*this,
        void			*pData,
        const
        char			*pFilePath,
        size_t			iLine
    )
    {
        bool			fRc = false;
        MEM_BLOCKHEADER *pActual = NULL;
        
        // Do initialization.
        //fprintf(stderr, "mem_DebugFree &this=%p\n", &this);
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if( NULL == pData ) {
            goto Exit00;
        }
        if( !(((int)pData & 0x03) == 0) ) {
            DEBUG_BREAK();
            goto Exit00;
        }
        
        // Point back to the Block Header and verify what we can.
        pActual = Data2Block(pData);
        if (pActual->pMem == this) {
        }
        else {
            if( !memMSC_Validate( pActual->pMem ) ) {
                DEBUG_BREAK();
                return false;
            }
            fprintf(
                    stderr,
                    "===> Warning - memMSC_DebugFree is switching this from %p to %p\n",
                    this,
                    pActual->pMem
            );
            this = pActual->pMem;       // Oops, it was malloc'd from
                                        // a different memOSX object.
        }
        
        // Validate the Memory Block.
        fRc = memMSC_DebugCheckArea( this, pData, pFilePath, iLine );
        if( !fRc ) {
            DEBUG_BREAK();
        }
        
        // Remove the block from the List.
        listdl_Delete( &this->blockList, pActual );
        
        // Free the memory.
        memset(pActual, 0, pActual->cbActual);
        free( pActual );
        pActual = NULL;
        pData = NULL;
        fRc = true;
        
        // Return to caller.
    Exit00:
        return( fRc );
    }
    
    
    
    
    //---------------------------------------------------------------
    //		mem_DebugFreeObject - Free an Allocated Block
    //---------------------------------------------------------------
    
    bool			memMSC_DebugFreeObject(
        MEMMSC_DATA		*this,
        void			*pData,
        const
        char			*pFilePath,
        size_t			iLine
    )
    {
        bool			fRc = false;
        MEM_BLOCKHEADER *pActual = NULL;
        
        // Do initialization.
        //fprintf(stderr, "memMSC_DebugFreeObject &this=%p\n", &this);
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if( NULL == pData ) {
            goto Exit00;
        }
        if( !(((int)pData & 0x03) == 0) ) {
            DEBUG_BREAK();
            goto Exit00;
        }
        
        // Point back to the Block Header and verify what we can.
        pActual = Data2Block(pData);
        if (pActual->pMem == this) {
        }
        else {
            if( !memMSC_Validate( pActual->pMem ) ) {
                DEBUG_BREAK();
                return false;
            }
            fprintf(
                    stderr,
                    "===> Warning - memMSC_DebugFreeObject is switching this from %p to %p\n",
                    this,
                    pActual->pMem
            );
            this = pActual->pMem;       // Oops, it was malloc'd from
            // a different memOSX object.
        }
        
        // Validate the Memory Block.
        fRc = memMSC_DebugCheckArea( this, pData, pFilePath, iLine );
        if( !fRc ) {
            DEBUG_BREAK();
        }
        
        // Remove the block from the List.
        listdl_Delete( &this->blockList, pActual );
        
        // Free the memory.
        pActual->flags &= ~MEM_FLAG_OBJECT;
        memset(pActual, 0, pActual->cbActual);
        free( pActual );
        pActual = NULL;
        pData = NULL;
        fRc = true;
        
        // Return to caller.
    Exit00:
        return( fRc );
    }
    
    
    
    
    //---------------------------------------------------------------
    //		memMSC_DebugGetSize - Get an Allocated Block Size
    //---------------------------------------------------------------
    
    size_t          memMSC_DebugGetSize(
        MEMMSC_DATA		*this,
        void			*pData,
        const
        char			*pFilePath,
        size_t			iLine
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        size_t			iRc = 0;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        if( NULL == pData ) {
            return 0;
        }
        
        // Point back to the Block Header and verify what we can.
        pActual = Data2Block(pData);
        if (pActual->pMem == this) {
        }
        else {
            if( !memMSC_Validate( pActual->pMem ) ) {
                DEBUG_BREAK();
                return false;
            }
            fprintf(
                    stderr,
                    "===> Warning - memMSC_DebugGetSize is switching this from %p to %p\n",
                    this,
                    pActual->pMem
            );
            this = pActual->pMem;       // Oops, it was malloc'd from
            // a different memOSX object.
        }
        
        // Validate the Memory Block.
        fRc = memMSC_DebugCheckArea( this, pData, pFilePath, iLine );
        if( !fRc ) {
            DEBUG_BREAK();
        }
        
        // Validate the Memory Block Chain if requested.
        if( this->fDebugMemory ) {
            memMSC_DebugCheck( this, pFilePath, iLine );
        }
        
        iRc = pActual->cbSize;
        
        // Return to caller.
        return iRc;
    }
    
    
    
    
    //---------------------------------------------------------------
    //			mem_DebugMalloc - Allocate a Memory Block
    //---------------------------------------------------------------
    
    void *			memMSC_DebugMalloc(
        MEMMSC_DATA		*this,
        size_t			cbSize,
        const
        char			*pFilePath,
        size_t			iLine
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        void			*pRet = NULL;
        
        // Do initialization.
        //fprintf(stderr, "mem_DebugMalloc\t&this=%p\n", &this);
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        if( cbSize > 0 )
            ;
        else {
            DEBUG_BREAK();
            return( NULL );
        }
        
        pActual = memMSC_DebugInternalMalloc( this, cbSize, pFilePath, iLine );
        pRet = pActual->data;
        
        // Return to caller.
    //Exit00:
        if (pRet && !(((int)pRet & 0x03) == 0) ) {
            DEBUG_BREAK();
        }
        return( pRet );
    }
    
    
    
    
    //---------------------------------------------------------------
    //			mem_DebugMallocObject - Allocate a Memory Block
    //---------------------------------------------------------------
    
    void *			memMSC_DebugMallocObject(
        MEMMSC_DATA		*this,
        size_t			cbSize,
        const
        char			*pFilePath,
        size_t			iLine
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        void			*pRet = NULL;
        
        // Do initialization.
        //fprintf(stderr, "mem_DebugMallocObject\t&this=%p\n", &this);
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        if( cbSize > 0 )
            ;
        else {
            DEBUG_BREAK();
            return( NULL );
        }
        
        pActual = memMSC_DebugInternalMalloc( this, cbSize, pFilePath, iLine );
        pActual->flags |= MEM_FLAG_OBJECT;
        
        // Return to caller.
        pRet = pActual->data;
        if (pRet && !(((int)pRet & 0x03) == 0) ) {
            DEBUG_BREAK();
        }
        return( pRet );
    }
    
    
    
    
    //---------------------------------------------------------------
    //				rmwMemDebugRealloc - Resize a Memory Block
    //---------------------------------------------------------------
    
    void *			memMSC_DebugRealloc(
        MEMMSC_DATA		*this,
        void			*pData,
        size_t			cbSize,
        const
        char			*pFilePath,
        size_t			iLine
    )
    {
        uint8_t			*pNewData;
        MEM_BLOCKHEADER *pActual = NULL;
        void			*pRet = NULL;
        size_t			cbOld;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        if( pData )
            ;
        else
            return( NULL );
        if( 0 == cbSize )
            ;
        else
            return( NULL );
        
        // Point back to the Block Header and verify what we can.
        pActual = Data2Block(pData);
        if (pActual->pMem == this) {
        }
        else {
            if( !memMSC_Validate( pActual->pMem ) ) {
                DEBUG_BREAK();
                return false;
            }
            fprintf(
                    stderr,
                    "===> Warning - memMSC_DebugRealloc is switching this from %p to %p\n",
                    this,
                    pActual->pMem
            );
            this = pActual->pMem;       // Oops, it was malloc'd from
            // a different memOSX object.
        }
        
        // Validate the Memory Block Chain if requested.
        fRc = memMSC_DebugCheckArea( this, pData, pFilePath, iLine );
        if( !fRc ) {
            DEBUG_BREAK();
        }
        
        // Validate the Memory Block Chain if requested.
        if( this->fDebugMemory ) {
            memMSC_DebugCheck( this, pFilePath, iLine );
        }
        
        cbOld = pActual->cbSize;
        
        // If down-sizing, just store new used size and
        // adjust trailing header.
        if( cbSize <= pActual->cbSize ) {
            pActual->cbSize = cbSize;
            //TODO: Adjust/Create trailing header.
            pRet = pActual->data;
            return( pRet );
        }
        
        // Allocate the new area.
        pNewData = (uint8_t *)memMSC_DebugMalloc( this, cbSize, pFilePath, iLine );
        if( pNewData )
            ;
        else
            return( NULL );
        
        // Copy the Data over to the new area.
        memmove( pNewData, pData, cbOld );
        
        // Now free the old area.
        memMSC_DebugFree( this, pData, pFilePath, iLine );
        
        // Return to caller.
    //Exit00:
        if (pRet && !(((int)pRet & 0x03) == 0) ) {
            DEBUG_BREAK();
        }
        return( pRet );
    }
    
    
    
    //---------------------------------------------------------------
    //          StrDup() duplicates a NUL terminated string.
    //---------------------------------------------------------------

    char *          memMSC_DebugStrDup(
        MEMMSC_DATA		*this,
        const
        char			*pOldStr,
        const
        char			*pFilePath,
        size_t			iLine
    )
    {
        char            *pNewStr = NULL;
        char            *pNewStrSav;
        size_t          len = 0;
        
        if (NULL == pOldStr) {
            return NULL;
        }
        
        pNewStr = (char *)pOldStr;
        while (*pNewStr++) {
            ++len;
        }
        
        pNewStr = memMSC_DebugMalloc(this, (len+1), pFilePath, iLine);
        if (NULL == pNewStr) {
            return NULL;
        }
        pNewStrSav = pNewStr;
        
        while (len--) {
            *pNewStr++ = *((const char *)pOldStr++);
        }
        *pNewStr = '\0';
        
        return pNewStrSav;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------
    
    MEMMSC_DATA *   memMSC_Init(
        MEMMSC_DATA     *this
    )
    {
        uint32_t        cbSize = sizeof(MEMMSC_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        //cbSize = obj_getSize(this);
        this = (MEMMSC_DATA *)obj_Init( this, cbSize, OBJ_IDENT_MEMMSC );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_MEMMSC);
        obj_setVtbl(this, &memMSC_Vtbl);
        
        // Initialize the Memory Block Chain.
        listdl_Init( &this->blockList, 0 );
        
        
#ifdef NDEBUG
#else
        if( !memMSC_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
#endif
        
        return this;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     memMSC_ToDebugString(
        MEMMSC_DATA     *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(memMSC) ",
                     this
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf( str, sizeof(str), " %p(memMSC)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            memMSC_Validate(
        MEMMSC_DATA     *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_MEMMSC) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(MEMMSC_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


