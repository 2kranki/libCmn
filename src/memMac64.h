// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          MEMOSX Console Transmit Task (memOSX) Header
//****************************************************************
/*
 * Program
 *			Separate memOSX (memOSX)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate memOSX to run things without complications
 *          of interfering with the main memOSX. A memOSX may be 
 *          called a memOSX on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal memOSX. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	02/08/2016 Generated
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


#ifndef         MEMOSX_H
#define         MEMOSX_H


#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct memOSX_data_s	MEMOSX_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

#undef mem_Calloc
#if		defined(NDEBUG)
#	define	mem_Calloc( Num, Size )\
    calloc( Num, Size )
#else
#	define	mem_Calloc( Num, Size )\
    memOSX_DebugCalloc( memOSX_Shared(), Num, Size, __FILE__, __LINE__ )
#endif

#undef mem_CallocAbort
#if		defined(NDEBUG)
#	define	mem_CallocAbort( Num, Size )\
    memOSX_CallocAbort( memOSX_Shared(), Num, Size, __FILE__, __LINE__ )
#else
#	define	mem_CallocAbort( Num, Size )\
    memOSX_DebugCallocAbort( memOSX_Shared(), Num, Size, __FILE__, __LINE__ )
#endif
    
#undef mem_CheckArea
#if        defined(NDEBUG)
#    define    mem_CheckArea( pData )\
/* */
#else
#    define    mem_CheckArea( pData )\
memOSX_DebugCheckArea( memOSX_Shared(), pData, __FILE__, __LINE__ )
#endif
    
#undef mem_Dump
#if		defined(NDEBUG)
#	define	mem_Dump( )\
    /* */
#else
#	define	mem_Dump( )\
    memOSX_DebugDump( memOSX_Shared(), __FILE__, __LINE__ )
#endif
    
#undef mem_Free
#if		defined(NDEBUG)
#   define  mem_Free( ptr )  free( ptr )
#else
#   define  mem_Free( ptr ) \
    memOSX_DebugFree( memOSX_Shared(), ptr, __FILE__, __LINE__ )
#endif
    
#undef mem_FreeObject
#if		defined(NDEBUG)
#   define  mem_FreeObject( ptr )  free( ptr )
#else
#   define  mem_FreeObject( ptr ) \
    memOSX_DebugFreeObject( memOSX_Shared(), ptr, __FILE__, __LINE__ )
#endif
    
#undef mem_Init
#if		defined(NDEBUG)
#	define	mem_Init( )\
    /* */
#else
#	define	mem_Init( )\
    memOSX_Shared()
#endif
    
#undef mem_Malloc
#if		defined(NDEBUG)
#   define  mem_Malloc( size ) \
malloc( size )
#else
#   define  mem_Malloc( size ) \
    memOSX_DebugMalloc( memOSX_Shared(), size, __FILE__, __LINE__ )
#endif
    
#undef mem_MallocAbort
#if		defined(NDEBUG)
#   define  mem_MallocAbort( size ) \
    memOSX_CallocAbort( memOSX_Shared(), 1, (size), __FILE__, __LINE__ )
#else
#   define  mem_MallocAbort( size ) \
    memOSX_DebugCallocAbort( memOSX_Shared(), 1, (size), __FILE__, __LINE__ )
#endif
    
#undef mem_MallocObject
#if		defined(NDEBUG)
#   define  mem_MallocObject( size ) \
    malloc( size )
#else
#   define  mem_MallocObject( size ) \
    memOSX_DebugMallocObject( memOSX_Shared(), size, __FILE__, __LINE__ )
#endif
    
#undef mem_Realloc
#if		defined(NDEBUG)
#   define  mem_Realloc( ptr, size ) \
    realloc( ptr, size )
#else
#   define  mem_Realloc( ptr, size ) \
    memOSX_DebugRealloc( memOSX_Shared(), ptr, size, __FILE__, __LINE__ )
#endif
    
#undef mem_Release
#if		defined(NDEBUG)
#	define	mem_Release( )\
/* */
#else
#	define	mem_Release( )\
memOSX_SharedReset()
#endif
    
#undef mem_StrDup
#if		defined(NDEBUG)
#   define  mem_StrDup( ptr ) \
    strdup( ptr )
#else
#   define  mem_StrDup( ptr ) \
    memOSX_DebugStrDup( memOSX_Shared(), ptr, __FILE__, __LINE__ )
#endif
    
    
    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    MEMOSX_DATA *     memOSX_Alloc(
        void
    );
    
    
    MEMOSX_DATA *     memOSX_New(
        void
    );
    
    
    MEMOSX_DATA *     memOSX_Shared(
        void
    );
    
    MEMOSX_DATA *     memOSX_SharedReset(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            memOSX_getDebug(
        MEMOSX_DATA     *this
    );
    
    bool            memOSX_setDebug(
        MEMOSX_DATA     *this,
        bool            value
    );
    
    
    bool            memOSX_setLeakExit(
        MEMOSX_DATA     *this,
        P_VOID_EXIT1    rtn,
        void            *pObject
    );
    
    
    const
    char *          memOSX_getTitle(
        MEMOSX_DATA     *this
    );
    
    bool            memOSX_setTitle(
        MEMOSX_DATA     *this,
        const
        char            *pValue
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    void *          memOSX_CallocAbort(
        MEMOSX_DATA		*this,
        size_t			cNum,
        size_t			cSize,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    void *          memOSX_DebugCalloc(
        MEMOSX_DATA		*this,
        size_t			cNum,
        size_t			cSize,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    void *          memOSX_DebugCallocAbort(
        MEMOSX_DATA		*this,
        size_t			cNum,
        size_t			cSize,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    bool			memOSX_DebugCheck(
        MEMOSX_DATA		*this,
        const
        char			*pFilePath,
        size_t			iLine
    );


    bool			memOSX_DebugCheckArea(
        MEMOSX_DATA		*this,
        void            *pData,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    bool			memOSX_DebugDidAlloc(
        MEMOSX_DATA		*this,
        void			*pData,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    bool			memOSX_DebugDump(
        MEMOSX_DATA		*this,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    bool			memOSX_DebugFree(
        MEMOSX_DATA		*this,
        void			*pData,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    bool			memOSX_DebugFreeObject(
        MEMOSX_DATA		*this,
        void			*pData,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    size_t          memOSX_DebugGetSize(
        MEMOSX_DATA		*this,
        void			*pData,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    void *			memOSX_DebugMalloc(
        MEMOSX_DATA		*this,
        size_t			cbSize,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    void *			memOSX_DebugMallocAbort(
        MEMOSX_DATA		*this,
        size_t			cbSize,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    void *			memOSX_DebugMallocObject(
        MEMOSX_DATA		*this,
        size_t			cbSize,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    void *			memOSX_DebugRealloc(
        MEMOSX_DATA		*this,
        void			*pData,
        size_t			cbSize,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    char *          memOSX_DebugStrDup(
        MEMOSX_DATA		*this,
        const
        char			*pOldStr,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    MEMOSX_DATA *   memOSX_Init(
        MEMOSX_DATA     *this
    );


    void *			memOSX_MallocAbort(
        MEMOSX_DATA		*this,
        size_t			cbSize,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = memOSX_ToDebugString(pObj,4);
     @endcode
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released,
                 otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    memOSX_ToDebugString(
        MEMOSX_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MEMOSX_H */

