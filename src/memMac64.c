// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   memMac64.c
 *  Generated 02/15/2021 16:01:03
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
#include        <memMac64_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    

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
    //         HexDigit - Print a Hexadecimal Digit
    //---------------------------------------------------------------

    static
    void            hex_putDigit(
        uint8_t         input,
        char            **ppBuffer      // Ascii representation of digit stored
                                        // at ptr and ptr is advanced
    )
    {
        char            WrkChr;

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
    //                            hex_putUint8
    //---------------------------------------------------------------

    static
    uint32_t        hex_putUint8(
        uint8_t            input,
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
    //                            hex_putUint32
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
    //                        hex_putUint64
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
    //                        hex_putBytes16
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
        len += hex_putUint64( (uint64_t)pData, ppBuffer );
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
    //                   L o c k  M u t e x
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         memMac64_LockMutex (
        MEMMAC64_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             iRc;

        iRc = pthread_mutex_lock(&this->mutex);
        if (iRc == 0)
            ;
        else {
            eRc = ERESULT_FAILURE;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                   U n l o c k  M u t e x
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         memMac64_UnlockMutex (
        MEMMAC64_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             iRc;

        iRc = pthread_mutex_unlock(&this->mutex);
        if (iRc == 0)
            ;
        else {
            eRc = ERESULT_FAILURE;
        }

        // Return to caller.
        return eRc;
    }




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    MEMMAC64_DATA * memMac64_New (
        void
    )
    {
        MEMMAC64_DATA   *this;
        
        this = memMac64_Shared( );
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                        B y p a s s
    //---------------------------------------------------------------

    bool            memMac64_getBypass (
        MEMMAC64_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            memMac64_setBypass (
        MEMMAC64_DATA   *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        memMac64_LockMutex(this);
        this->fBypass = fValue ? 1 : 0;
        memMac64_UnlockMutex(this);

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        memMac64_getPriority (
        MEMMAC64_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            memMac64_setPriority (
        MEMMAC64_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        memMac64_getSize (
        MEMMAC64_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  memMac64_getSuperVtbl (
        MEMMAC64_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = memMac64_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another MEMMAC64 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         memMac64_Assign (
        MEMMAC64_DATA       *this,
        MEMMAC64_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!memMac64_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                    C a l l o c  A b o r t
    //---------------------------------------------------------------

    void *          memMac64_CallocAbort(
        MEMMAC64_DATA        *this,
        size_t            cNum,
        size_t            cSize,
        const
        char            *pFilePath,
        size_t            iLine
    )
    {
        void            *pRet = NULL;

        // Do initialization.
        if ((cSize == 0) || (cNum == 0)) {
            DEBUG_BREAK();
            fprintf(
                    stderr,
                    "FATAL: Calloc(0) called from %s, line: %zu\n\n",
                    pFilePath,
                    iLine
                    );
            exit(EXIT_FAILURE);
            //return NULL;
        }

        pRet = calloc(cNum, cSize);
        if (pRet == NULL) {
            DEBUG_BREAK();
            fprintf(
                    stderr,
                    "FATAL: Out of Memory - Calloc(%zu,%zu) called from %s, line: %zu\n\n",
                    cNum,
                    cSize,
                    pFilePath,
                    iLine
                    );
            exit(EXIT_FAILURE);
            //return NULL;
        }

        // Return to caller.
        return( pRet );
    }



    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             memMac64_Compare (
        MEMMAC64_DATA     *this,
        MEMMAC64_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!memMac64_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        memMac64      *pCopy = memMac64_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a MEMMAC64 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    MEMMAC64_DATA *     memMac64_Copy (
        MEMMAC64_DATA       *this
    )
    {
        MEMMAC64_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef MEMMAC64_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = memMac64_New( );
        if (pOther) {
            eRc = memMac64_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            memMac64_Dealloc (
        OBJ_ID          objId
    )
    {
        MEMMAC64_DATA   *this = objId;
        //ERESULT         eRc;
        int             iRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((MEMMAC64_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        // Validate the Memory Block Chain if requested.
        if( this->fDebugMemory ) {
            memMac64_DebugCheck( this, NULL, 0 );
        }
        if (listdl_Count(&this->blockList)) {
            if (this->pLeakExit) {
                this->pLeakExit(this->pLeakExitObject);
            }

            if (this->pTitle)
                ;
            else {
                this->pTitle = "==>memMac64_Dealloc<==";
            }
            memMac64_DebugDump(this, this->pTitle, 0);
        }

        iRc = pthread_mutex_destroy(&this->mutex);
        if (iRc) {
            DEBUG_BREAK();
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //            mem_DebugCalloc - Allocate a Memory Block
    //---------------------------------------------------------------

    void *          memMac64_DebugCalloc(
        MEMMAC64_DATA   *this,
        size_t          cNum,
        size_t          cbSize,
        const
        char            *pFilePath,
        size_t          iLine
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        void            *pRet = NULL;
        size_t          cbRequest;

        // Do initialization.
        if ((cbSize == 0) || (cNum == 0)) {
            DEBUG_BREAK();
            fprintf(
                    stderr,
                    "FATAL: Calloc(0) called from %s, line: %zu\n\n",
                    pFilePath,
                    iLine
            );
            //exit(EXIT_FAILURE);
            return NULL;
        }
        if (this->fBypass) {
            pRet = calloc(cNum, cbSize);
            return pRet;
        }
        //fprintf(stderr, "mem_DebugCalloc &this=%p\n", &this);
        cbRequest = cNum * cbSize;

        // Validate the Memory Block Chain if requested.
        if( this->fDebugMemory ) {
            memMac64_DebugCheck( this, pFilePath, iLine );
        }

        memMac64_LockMutex(this);
        pActual = memMac64_DebugInternalMalloc( this, cbRequest, pFilePath, iLine );
        memMac64_UnlockMutex(this);
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


    void *          memMac64_DebugCallocAbort(
        MEMMAC64_DATA   *this,
        size_t          cNum,
        size_t          cSize,
        const
        char            *pFilePath,
        size_t          iLine
    )
    {
        void            *pRet = NULL;

        // Do initialization.
        if ((cSize == 0) || (cNum == 0)) {
            DEBUG_BREAK();
            fprintf(
                    stderr,
                    "FATAL: Calloc(0) called from %s, line: %zu\n\n",
                    pFilePath,
                    iLine
                    );
            exit(EXIT_FAILURE);
            //return NULL;
        }

        pRet = memMac64_DebugCalloc(this, cNum, cSize, pFilePath, iLine);
        if (pRet == NULL) {
            DEBUG_BREAK();
            fprintf(
                    stderr,
                    "FATAL: Out of Memory - Calloc() called from %s, line: %zu\n\n",
                    pFilePath,
                    iLine
                    );
            exit(EXIT_FAILURE);
            //return NULL;
        }

        // Return to caller.
        return( pRet );
    }




    //---------------------------------------------------------------
    //            memMac64_DebugCheck - Check for Bad Memory Blocks
    //---------------------------------------------------------------

    bool            memMac64_DebugCheck(
        MEMMAC64_DATA   *this,
        const
        char            *pFilePath,
        size_t          iLine
    )
    {
        bool            fRc = false;
        MEM_BLOCKHEADER *pActual = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !memMac64_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        memMac64_LockMutex(this);

        // Validate the Block List.
        fRc = listdl_IsValidList( &this->blockList );
        if( !fRc ) {
            DEBUG_BREAK();
            return fRc;
        }

        // Find the Area in the Block Header List.
        for(    pActual = (MEM_BLOCKHEADER *)listdl_Head( &this->blockList );
                pActual;
                pActual = (MEM_BLOCKHEADER *)listdl_Next( &this->blockList, pActual )
            ) {
            fRc = memMac64_DebugCheckAreaInt( this, pActual->data, pFilePath, iLine );
            if( !fRc ) {
                DEBUG_BREAK();
                break;
            }
        }

        // Return to caller.
        memMac64_UnlockMutex(this);
        return fRc ;
    }



    //---------------------------------------------------------------
    //        memMac64_DebugCheckArea - Check for a Bad Memory Block
    //---------------------------------------------------------------

    bool            memMac64_DebugCheckArea(
        MEMMAC64_DATA   *this,
        void            *pData,
        const
        char            *pFilePath,
        size_t          iLine
    )
    {
        bool            fRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !memMac64_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        memMac64_LockMutex(this);
        fRc = memMac64_DebugCheckAreaInt(this, pData, pFilePath, iLine);
        memMac64_UnlockMutex(this);

        // Return to caller.
        return fRc;
    }


    bool            memMac64_DebugCheckAreaInt(
        MEMMAC64_DATA   *this,
        void            *pData,
        const
        char            *pFilePath,
        size_t          iLine
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        MEM_BLOCKTRAILER
                        *pTrailer = NULL;
        MEM_BLOCKHEADER *pActualCalc = NULL;

        // Do initialization.

        pActualCalc = Data2Block(pData);
        if (pActualCalc->pMem == this) {
        }
        else {
            if( !memMac64_Validate( pActual->pMem ) ) {
                fprintf(
                        stderr,
                        "\nWarning - Data Area did not validate!\n"
                        );
                memMac64_DebugDumpBlock(this,pData);
                DEBUG_BREAK();
                return false;
            }
            fprintf(
                    stderr,
                    "===> Warning - memMac64_DebugRealloc is switching this from %p to %p\n",
                    this,
                    pActual->pMem
            );
            this = pActual->pMem;       // Oops, it was malloc'd from
                                        // a different memMac64 object.
        }

        // Find the Area in the Block Header List.
        pActual = memMac64_DebugFind(this, pData);
        if( NULL == pActual ) {
            fprintf(
                    stderr,
                    "\nWarning - Data Area was not found in Block Header List!\n"
                    );
            memMac64_DebugDumpBlock(this, pData);
            DEBUG_BREAK();
            return false;
        }

        // Check for Underrun.
        if( 0 == memcmp( pActual->check, CheckValue, sizeof(CheckValue) ) )
            ;
        else {
            fprintf(
                    stderr,
                    "\nWarning - Data Area had an underrun problem!\n"
                    );
            memMac64_DebugDumpBlock(this,pData);
            DEBUG_BREAK();
            return false;
        }

        // Check for Overrun.
        pTrailer = BLOCK_PTRAILER(pActual);
        if( 0 == memcmp( pTrailer, CheckValue, sizeof(CheckValue) ) )
            ;
        else {
            fprintf(stderr, "\nWarning - Data Area had an overrun problem!\n");
            memMac64_DebugDumpBlock(this, pData);
            DEBUG_BREAK();
            return false;
        }

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //    mem_DebugDidAlloc - Did We previously allocate a Block
    //---------------------------------------------------------------

    bool            memMac64_DebugDidAlloc(
        MEMMAC64_DATA   *this,
        void            *pData,
        const
        char            *pFilePath,
        size_t          iLine
    )
    {
        bool            fRc = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !memMac64_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if( NULL == pData ) {
            return false;
        }

        // Validate the Memory Block Chain if requested.
        if( this->fDebugMemory ) {
            memMac64_DebugCheck( this, pFilePath, iLine );
        }

        fRc = memMac64_DebugCheckArea(this, pData, pFilePath, iLine);

        // Return to caller.
        return fRc;
    }




    //---------------------------------------------------------------
    //            mem_DebugDump - Check for Any Memory Blocks
    //---------------------------------------------------------------

    bool            memMac64_DebugDump(
        MEMMAC64_DATA   *this,
        const
        char            *pFilePath,
        size_t          iLine
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        bool            fFnd = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !memMac64_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        // Validate the chain.
        memMac64_DebugCheck( this, pFilePath, iLine );

        // Dump any areas found on the list.
        memMac64_LockMutex(this);
        for(pActual = (MEM_BLOCKHEADER *)listdl_Head( &this->blockList );
            pActual;
            pActual = (MEM_BLOCKHEADER *)listdl_Next( &this->blockList, pActual )
        ) {
            uint8_t         fBypassSave;
            if (trace_Shared() == (void *)&pActual->data) {
                continue;
            }
            fBypassSave = this->fBypass;
            this->fBypass = 1;
            memMac64_DebugDumpBlock(this, (const char *)&pActual->data);
            this->fBypass = fBypassSave;
            fFnd = true;
        }
        memMac64_UnlockMutex(this);

        // Return to caller.
        return fFnd;
    }



    //---------------------------------------------------------------
    //            mem_DebugDump - Check for Any Memory Blocks
    //---------------------------------------------------------------

    void            memMac64_DebugDumpBlock(
        MEMMAC64_DATA   *this,
        const
        char            *pData
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        bool            fFnd = false;
        OBJ_DATA        *pObj;
        ASTR_DATA       *pStr;
        char            buffer[2048];
        char            *pBuffer = buffer;
        //uint32_t        i;
        uint32_t        size;
        const
        char            *pBytes;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !memMac64_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        // Point back to the Block Header and verify what we can.
        pActual = Data2Block(pData);
        if (pActual->pMem == this) {
        }
        else {
            if( !memMac64_Validate( pActual->pMem ) ) {
                DEBUG_BREAK();
                return;
            }
            fprintf(
                    stderr,
                    "===> Warning - memMac64_DebugDumpBlock is switching this from %p to %p\n",
                    this,
                    pActual->pMem
                    );
            this = pActual->pMem;       // Oops, it was malloc'd from
            //                          // a different memMac64 object.
        }

        // Check for Underrun.
        if( 0 == memcmp( pActual->check, CheckValue, sizeof(CheckValue) ) )
            fFnd = true;
        else {
            fFnd = false;
        }

        fprintf(stderr, "\n\ndata ptr: %p\n", pData);
        if (fFnd) {
            fprintf(stderr, "\tIs an allocated area from memMac64 %p\n", pActual->pMem);
            fprintf(stderr, "\tRequested_Size=%ld  Actual_Size=%ld\n",
                            pActual->cbSize, pActual->cbActual);
            if (pActual->flags & MEM_FLAG_OBJECT) {
                const
                OBJ_INFO        *pInfo = obj_getInfo((OBJ_ID)pData);
                fprintf(
                        stderr,
                        "\tObject:\n\t\tType: (%d)%s\n",
                        obj_getType((OBJ_ID)pData),
                        (pInfo ? pInfo->pClassName : "???")
                );
                fprintf(stderr, "\t\tRetain Count: %d\n", obj_getRetainCount(&pActual->data));
                fprintf(stderr, "\t\tMisc: %d\n", obj_getMisc(&pActual->data));
                fprintf(stderr, "\t\tMisc1: %d\n", obj_getMisc1(&pActual->data));
                fprintf(stderr, "\t\tMisc2: %d\n", obj_getMisc2(&pActual->data));
                if (obj_IsFlag(&pActual->data, OBJ_FLAG_ALLOC)) {
                    fprintf(stderr, "\t\tFlag: Alloc\n");
                }
                if (obj_IsFlag(&pActual->data, OBJ_FLAG_INIT)) {
                    fprintf(stderr, "\t\tFlag: Init\n");
                }
                if (obj_IsFlag(&pActual->data, OBJ_FLAG_ENABLED)) {
                    fprintf(stderr, "\t\tFlag: Enabled\n");
                }
                if (obj_IsFlag(&pActual->data, OBJ_FLAG_TRACE)) {
                    fprintf(stderr, "\t\tFlag: Trace\n");
                }
                if (obj_IsFlag(&pActual->data, OBJ_FLAG_USER1)) {
                    fprintf(stderr, "\t\tFlag: User1\n");
                }
                if (obj_IsFlag(&pActual->data, OBJ_FLAG_USER2)) {
                    fprintf(stderr, "\t\tFlag: User2\n");
                }
                if (obj_IsFlag(&pActual->data, OBJ_FLAG_USER3)) {
                    fprintf(stderr, "\t\tFlag: User3\n");
                }
                if (obj_IsFlag(&pActual->data, OBJ_FLAG_USER4)) {
                    fprintf(stderr, "\t\tFlag: User4\n");
                }
                if (obj_IsFlag(&pActual->data, OBJ_FLAG_USER5)) {
                    fprintf(stderr, "\t\tFlag: User5\n");
                }
                if (obj_IsFlag(&pActual->data, OBJ_FLAG_USER6)) {
                    fprintf(stderr, "\t\tFlag: User6\n");
                }
                if (obj_IsFlag(&pActual->data, OBJ_FLAG_USER7)) {
                    fprintf(stderr, "\t\tFlag: User7\n");
                }
                if (obj_IsFlag(&pActual->data, OBJ_FLAG_USER8)) {
                    fprintf(stderr, "\t\tFlag: User8\n");
                }
                pObj = (OBJ_DATA *)pData;
                if (pObj->pVtbl && pObj->pVtbl->pToDebugString) {
                    uint8_t         fBypassSave;
                    fBypassSave = this->fBypass;
                    this->fBypass = 1;
                    pStr = pObj->pVtbl->pToDebugString(pObj, 0);
                    fprintf(stderr, "debug: \n%s\n\n\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    this->fBypass = fBypassSave;
                }
                else {
                    fprintf( stderr, "\nData @ %p:\n", pData );
                    pBuffer = buffer;
                    size = (uint32_t)pActual->cbSize;
                    //if (size > 128)
                        //size = 128;
                    if (0 == size)
                        size = 1;
                    pBytes = pData;
                    for (;;) {
                        hex_putBytes16_32(size, pBytes, 2048, &pBuffer);
                        fprintf(stderr, "%s\n", buffer);
                        pBytes += 16;
                        pBuffer = buffer;
                        if (size <= 16)
                            break;
                        size -= 16;
                    }
                    fprintf(stderr, "\n");
                }
            }
            else {
                fprintf( stderr, "\nData @ %p:\n", pData );
                pBuffer = buffer;
                size = (uint32_t)pActual->cbSize;
                if (size > 128)
                    size = 128;
                if (0 == size)
                    size = 1;
                pBytes = pData;
                for (;;) {
                    hex_putBytes16_32(size, pBytes, 2048, &pBuffer);
                    fprintf(stderr, "%s\n", buffer);
                    pBytes += 16;
                    pBuffer = buffer;
                    if (size <= 16)
                        break;
                    size -= 16;
                }
                fprintf(stderr, "\n");
            }
        }
        else {
            fprintf(stderr, "\tDoes not seem to be a memMac64 allocated area.\n");
        }
        //DEBUG_BREAK();

        // Return to caller.
    }



    //---------------------------------------------------------------
    //      memMac64_DebugFind - Find a memory block on the chain
    //---------------------------------------------------------------

    MEM_BLOCKHEADER * memMac64_DebugFind(
        MEMMAC64_DATA   *this,
        void            *pData
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;

        // Do initialization.
        //fprintf(stderr, "memMac64_DebugFind &this=%p\n", &this);
#ifdef NDEBUG
#else
        if( !memMac64_Validate( this ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        // Find the Area in the Block Header List.
        for(pActual = (MEM_BLOCKHEADER *)listdl_Head(&this->blockList);
            pActual;
            pActual = (MEM_BLOCKHEADER *)listdl_Next(&this->blockList, pActual)
        ) {
            if( pActual->data == pData ) {
                break;
            }
        }

        // Return to caller.
        return pActual;
    }



    //---------------------------------------------------------------
    //            mem_DebugInternalMalloc - Allocate a Memory Block
    //---------------------------------------------------------------

    MEM_BLOCKHEADER * memMac64_DebugInternalMalloc(
        MEMMAC64_DATA     *this,
        size_t            cbSize,
        const
        char              *pFile,
        size_t            iLine
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        MEM_BLOCKTRAILER
                        *pTrailer = NULL;
        void            *pRet = NULL;
        size_t          cbActual;

        // Do initialization.
        if (cbSize == 0) {
            return NULL;
        }
        if (this->fBypass) {
            pActual = calloc(1, cbSize);
            return pActual;
        }

        // Allocate the memory.
        cbActual = cbSize + sizeof(MEM_BLOCKHEADER);
        cbActual += sizeof(MEM_BLOCKTRAILER);
        pActual = malloc( cbActual );
        if( NULL == pActual ) {
            pRet = NULL;
            goto Exit00;
        }
        pRet =    (MEM_BLOCKHEADER *)listdl_Add2Tail( &this->blockList, pActual );
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



    //---------------------------------------------------------------
    //                memMac64_DebugFree - Free an Allocated Block
    //---------------------------------------------------------------

    bool            memMac64_DebugFree(
        MEMMAC64_DATA   *this,
        void            *pData,
        const
        char            *pFilePath,
        size_t          iLine
    )
    {
        bool            fRc = false;
        MEM_BLOCKHEADER *pActual = NULL;

        // Do initialization.
        //fprintf(stderr, "mem_DebugFree &this=%p\n", &this);
#ifdef NDEBUG
#else
        if( !memMac64_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if( NULL == pData ) {
            goto Exit00;
        }
        if (this->fBypass) {
            free(pData);
            fRc = true;
            goto Exit00;
        }
        if( !(((int)pData & 0x03) == 0) ) {
            DEBUG_BREAK();
            goto Exit00;
        }
        memMac64_LockMutex(this);

        // Point back to the Block Header and verify what we can.
        pActual = Data2Block(pData);
        if (pActual->pMem == this) {
        }
        else {
            if( !memMac64_Validate( pActual->pMem ) ) {
                DEBUG_BREAK();
                memMac64_UnlockMutex(this);
                return false;
            }
            fprintf(
                    stderr,
                    "===> Warning - memMac64_DebugFree is switching this from %p to %p\n",
                    this,
                    pActual->pMem
            );
            this = pActual->pMem;       // Oops, it was malloc'd from
                                        // a different memMac64 object.
        }

        // Validate the Memory Block.
        fRc = memMac64_DebugCheckAreaInt( this, pData, pFilePath, iLine );
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
        memMac64_UnlockMutex(this);

        // Return to caller.
    Exit00:
        return fRc;
    }




    //---------------------------------------------------------------
    //        mem_DebugFreeObject - Free an Allocated Block
    //---------------------------------------------------------------

    bool            memMac64_DebugFreeObject(
        MEMMAC64_DATA        *this,
        void            *pData,
        const
        char            *pFilePath,
        size_t            iLine
    )
    {
        bool            fRc = false;
        MEM_BLOCKHEADER *pActual = NULL;

        // Do initialization.
        //fprintf(stderr, "memMac64_DebugFreeObject &this=%p\n", &this);
#ifdef NDEBUG
#else
        if( !memMac64_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if( NULL == pData ) {
            goto Exit00;
        }
        if (this->fBypass) {
            free(pData);
            fRc = true;
            goto Exit00;
        }
        if( !(((int)pData & 0x03) == 0) ) {
            DEBUG_BREAK();
            goto Exit00;
        }
        memMac64_LockMutex(this);

        // Point back to the Block Header and verify what we can.
        pActual = Data2Block(pData);
        if (pActual->pMem == this) {
        }
        else {
            if( !memMac64_Validate( pActual->pMem ) ) {
                DEBUG_BREAK();
                memMac64_UnlockMutex(this);
                return false;
            }
            fprintf(
                    stderr,
                    "===> Warning - memMac64_DebugFreeObject is switching this from %p to %p\n",
                    this,
                    pActual->pMem
            );
            this = pActual->pMem;       // Oops, it was malloc'd from
            // a different memMac64 object.
        }

        // Validate the Memory Block.
        fRc = memMac64_DebugCheckAreaInt(this, pData, pFilePath, iLine);
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
        memMac64_UnlockMutex(this);

        // Return to caller.
    Exit00:
        return( fRc );
    }




    //---------------------------------------------------------------
    //        memMac64_DebugGetSize - Get an Allocated Block Size
    //---------------------------------------------------------------

    size_t          memMac64_DebugGetSize(
        MEMMAC64_DATA        *this,
        void            *pData,
        const
        char            *pFilePath,
        size_t            iLine
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        size_t            iRc = 0;
        bool            fRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !memMac64_Validate( this ) ) {
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
            if( !memMac64_Validate( pActual->pMem ) ) {
                DEBUG_BREAK();
                return false;
            }
            fprintf(
                    stderr,
                    "===> Warning - memMac64_DebugGetSize is switching this from %p to %p\n",
                    this,
                    pActual->pMem
            );
            this = pActual->pMem;       // Oops, it was malloc'd from
            // a different memMac64 object.
        }

        // Validate the Memory Block.
        fRc = memMac64_DebugCheckArea( this, pData, pFilePath, iLine );
        if( !fRc ) {
            DEBUG_BREAK();
        }

        // Validate the Memory Block Chain if requested.
        if( this->fDebugMemory ) {
            memMac64_DebugCheck( this, pFilePath, iLine );
        }

        iRc = pActual->cbSize;

        // Return to caller.
        return iRc;
    }




    //---------------------------------------------------------------
    //            mem_DebugMalloc - Allocate a Memory Block
    //---------------------------------------------------------------

    void *            memMac64_DebugMalloc(
        MEMMAC64_DATA   *this,
        size_t          cbSize,
        const
        char            *pFilePath,
        size_t          iLine
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        void            *pRet = NULL;

        // Do initialization.
        //fprintf(stderr, "mem_DebugMalloc\t&this=%p\n", &this);
#ifdef NDEBUG
#else
        if( !memMac64_Validate( this ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        if( cbSize > 0 )
            ;
        else {
            DEBUG_BREAK();
            fprintf(
                    stderr,
                    "FATAL: Calloc(0) called from %s, line: %zu\n\n",
                    pFilePath,
                    iLine
                    );
            //exit(EXIT_FAILURE);
            return NULL;
        }
        if (this->fBypass) {
            pRet = calloc(1, cbSize);
            return pRet;
        }

        memMac64_LockMutex(this);
        pActual = memMac64_DebugInternalMalloc( this, cbSize, pFilePath, iLine );
        pRet = pActual->data;
        memMac64_UnlockMutex(this);

        // Return to caller.
    //Exit00:
        if (pRet && !(((int)pRet & 0x03) == 0) ) {
            DEBUG_BREAK();
        }
        return( pRet );
    }


    void *          memMac64_DebugMallocAbort(
        MEMMAC64_DATA        *this,
        size_t            cSize,
        const
        char            *pFilePath,
        size_t            iLine
    )
    {
        void            *pRet = NULL;

        // Do initialization.
        if (cSize == 0) {
            DEBUG_BREAK();
            fprintf(
                    stderr,
                    "FATAL: Malloc(0) called from %s, line: %zu\n\n",
                    pFilePath,
                    iLine
                    );
            exit(EXIT_FAILURE);
            //return NULL;
        }

        pRet = memMac64_DebugMalloc(this, cSize, pFilePath, iLine);
        if (pRet == NULL) {
            DEBUG_BREAK();
            fprintf(
                    stderr,
                    "FATAL: Out of Memory - Malloc() called from %s, line: %zu\n\n",
                    pFilePath,
                    iLine
                    );
            exit(EXIT_FAILURE);
            //return NULL;
        }

        // Return to caller.
        return( pRet );
    }




    //---------------------------------------------------------------
    //            mem_DebugMallocObject - Allocate a Memory Block
    //---------------------------------------------------------------

    void *            memMac64_DebugMallocObject(
        MEMMAC64_DATA   *this,
        size_t          cbSize,
        const
        char            *pFilePath,
        size_t          iLine
    )
    {
        MEM_BLOCKHEADER *pActual = NULL;
        void            *pRet = NULL;

        // Do initialization.
        //fprintf(stderr, "mem_DebugMallocObject\t&this=%p\n", &this);
#ifdef NDEBUG
#else
        if( !memMac64_Validate( this ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        if (cbSize == 0) {
            DEBUG_BREAK();
            fprintf(
                    stderr,
                    "FATAL: MallocObject(0) called from %s, line: %zu\n\n",
                    pFilePath,
                    iLine
                    );
            exit(EXIT_FAILURE);
            //return NULL;
        }
        if (this->fBypass) {
            pRet = calloc(1, cbSize);
            return pRet;
        }

        memMac64_LockMutex(this);
        pActual = memMac64_DebugInternalMalloc( this, cbSize, pFilePath, iLine );
        memMac64_UnlockMutex(this);
        if (pActual == NULL) {
            DEBUG_BREAK();
            fprintf(
                    stderr,
                    "FATAL: MallocObject(%zu) called from %s, line: %zu\n\n",
                    cbSize,
                    pFilePath,
                    iLine
                    );
            exit(EXIT_FAILURE);
            //return NULL;
        }
        pActual->flags |= MEM_FLAG_OBJECT;

        // Return to caller.
        pRet = pActual->data;
        if (pRet && !(((int)pRet & 0x03) == 0) ) {
            DEBUG_BREAK();
        }
        return pRet;
    }




    //---------------------------------------------------------------
    //                rmwMemDebugRealloc - Resize a Memory Block
    //---------------------------------------------------------------

    void *          memMac64_DebugRealloc(
        MEMMAC64_DATA   *this,
        void            *pData,
        size_t          cbSize,
        const
        char            *pFilePath,
        size_t          iLine
    )
    {
        uint8_t         *pNewData;
        MEM_BLOCKHEADER *pActual = NULL;
        void            *pRet = NULL;
        size_t          cbOld;
        bool            fRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !memMac64_Validate( this ) ) {
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
        if (this->fBypass) {
            pRet = realloc(pData, cbSize);
            return pRet;
        }

        // Point back to the Block Header and verify what we can.
        pActual = Data2Block(pData);
        if (pActual->pMem == this) {
        }
        else {
            if( !memMac64_Validate( pActual->pMem ) ) {
                DEBUG_BREAK();
                return false;
            }
            fprintf(
                    stderr,
                    "===> Warning - memMac64_DebugRealloc is switching this from %p to %p\n",
                    this,
                    pActual->pMem
            );
            this = pActual->pMem;       // Oops, it was malloc'd from
            // a different memMac64 object.
        }

        // Validate the Memory Block Chain if requested.
        fRc = memMac64_DebugCheckArea( this, pData, pFilePath, iLine );
        if( !fRc ) {
            DEBUG_BREAK();
        }

        // Validate the Memory Block Chain if requested.
        if( this->fDebugMemory ) {
            memMac64_DebugCheck( this, pFilePath, iLine );
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
        pNewData = (uint8_t *)memMac64_DebugMalloc( this, cbSize, pFilePath, iLine );
        if( pNewData )
            ;
        else
            return( NULL );

        // Copy the Data over to the new area.
        memmove( pNewData, pData, cbOld );

        // Now free the old area.
        memMac64_DebugFree( this, pData, pFilePath, iLine );

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

    char *          memMac64_DebugStrDup(
        MEMMAC64_DATA        *this,
        const
        char            *pOldStr,
        const
        char            *pFilePath,
        size_t            iLine
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

        pNewStr = memMac64_DebugMalloc(this, (len+1), pFilePath, iLine);
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
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        memMac64      *pDeepCopy = memMac64_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a MEMMAC64 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    MEMMAC64_DATA *     memMac64_DeepyCopy (
        MEMMAC64_DATA       *this
    )
    {
        MEMMAC64_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = memMac64_New( );
        if (pOther) {
            eRc = memMac64_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         memMac64_Disable (
        MEMMAC64_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         memMac64_Enable (
        MEMMAC64_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    MEMMAC64_DATA * memMac64_Init (
        MEMMAC64_DATA   *this
    )
    {
        uint32_t        cbSize = sizeof(MEMMAC64_DATA);
        //ERESULT         eRc;
        int             iRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_MEMMAC64);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&memMac64_Vtbl);
#ifdef  MEMMAC64_JSON_SUPPORT
        JsonIn_RegisterClass(memMac64_Class());
#endif
        
        //this->mutex = PTHREAD_MUTEX_INITIALIZER;
        iRc = pthread_mutex_init(&this->mutex, NULL);
        if (iRc) {
            DEBUG_BREAK();
        }

        // Initialize the Memory Block Chain.
        listdl_Init( &this->blockList, 0 );

#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "memMac64::sizeof(MEMMAC64_DATA) = %lu\n", 
                sizeof(MEMMAC64_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(MEMMAC64_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         memMac64_IsEnabled (
        MEMMAC64_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                 M a l l o c  A b o r t
    //---------------------------------------------------------------

    void *          memMac64_MallocAbort(
        MEMMAC64_DATA   *this,
        size_t          cSize,
        const
        char            *pFilePath,
        size_t          iLine
    )
    {
        //ERESULT         eRc;
        void            *pRet = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif

        if (0 == cSize) {
            DEBUG_BREAK();
            fprintf(
                    stderr,
                    "FATAL: Malloc(0) called from %s, line: %zu\n\n",
                    pFilePath,
                    iLine
                    );
            exit(EXIT_FAILURE);
            //return NULL;
        }

        pRet = malloc(cSize);
        if (pRet == NULL) {
            DEBUG_BREAK();
            fprintf(
                    stderr,
                    "FATAL: Out of Memory - Malloc() called from %s, line: %zu\n\n",
                    pFilePath,
                    iLine
                    );
            exit(EXIT_FAILURE);
            //return NULL;
        }

        // Return to caller.
        return pRet;
    }



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = memMac64_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "memMac64", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          memMac64_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MEMMAC64_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(MEMMAC64_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)memMac64_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return memMac64_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return memMac64_Enable;
                        }
                        break;

                    case 'P':
#ifdef  MEMMAC64_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return memMac64_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return memMac64_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return memMac64_ToDebugString;
                        }
#ifdef  MEMMAC64_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return memMac64_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return memMac64_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == memMac64_ToDebugString)
                    return "ToDebugString";
#ifdef  MEMMAC64_JSON_SUPPORT
                if (pData == memMac64_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = memMac64_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     memMac64_ToDebugString (
        MEMMAC64_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!memMac64_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    memMac64_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            memMac64_Validate (
        MEMMAC64_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_MEMMAC64))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(MEMMAC64_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


