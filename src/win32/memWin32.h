// vi:nu:et:sts=4 ts=4 sw=4 tw=90

//****************************************************************
//          MEMMSC Console Transmit Task (memMSC) Header
//****************************************************************
/*
 * Program
 *			Separate memMSC (memMSC)
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
 *	04/12/2017 Generated
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


#ifndef         MEMMSC_H
#define         MEMMSC_H


#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct memMSC_data_s	MEMMSC_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

#undef mem_Calloc
#if		defined(NDEBUG)
#	define	mem_Calloc( Num, Size )\
    calloc( Num, Size )
#else
#	define	mem_Calloc( Num, Size )\
    memMSC_DebugCalloc( memMSC_Shared(), Num, Size, __FILE__, __LINE__ )
#endif

#undef mem_Dump
#if		defined(NDEBUG)
#	define	mem_Dump( )\
    /* */
#else
#	define	mem_Dump( )\
    memMSC_DebugDump( memMSC_Shared(), __FILE__, __LINE__ )
#endif
    
#undef mem_Free
#if		defined(NDEBUG)
#   define  mem_Free( ptr )  free( ptr )
#else
#   define  mem_Free( ptr ) \
    memMSC_DebugFree( memMSC_Shared(), ptr, __FILE__, __LINE__ )
#endif
    
#undef mem_FreeObject
#if		defined(NDEBUG)
#   define  mem_FreeObject( ptr )  free( ptr )
#else
#   define  mem_FreeObject( ptr ) \
    memMSC_DebugFreeObject( memMSC_Shared(), ptr, __FILE__, __LINE__ )
#endif
    
#undef mem_Init
#if		defined(NDEBUG)
#	define	mem_Init( )\
    /* */
#else
#	define	mem_Init( )\
    memMSC_Shared()
#endif
    
#undef mem_Malloc
#if		defined(NDEBUG)
#   define  mem_Malloc( size ) \
malloc( size )
#else
#   define  mem_Malloc( size ) \
    memMSC_DebugMalloc( memMSC_Shared(), size, __FILE__, __LINE__ )
#endif
    
#undef mem_MallocObject
#if		defined(NDEBUG)
#   define  mem_MallocObject( size ) \
    malloc( size )
#else
#   define  mem_MallocObject( size ) \
    memMSC_DebugMallocObject( memMSC_Shared(), size, __FILE__, __LINE__ )
#endif
    
#undef mem_Realloc
#if		defined(NDEBUG)
#   define  mem_Realloc( ptr, size ) \
    realloc( ptr, size )
#else
#   define  mem_Realloc( ptr, size ) \
    memMSC_DebugRealloc( memMSC_Shared(), ptr, size, __FILE__, __LINE__ )
#endif
    
#undef mem_Release
#if		defined(NDEBUG)
#	define	mem_Release( )\
                /* */
#else
#	define	mem_Release( )\
                memMSC_SharedReset()
#endif
    
#undef mem_StrDup
#if		defined(NDEBUG)
#   define  mem_StrDup( ptr ) \
    strdup( ptr )
#else
#   define  mem_StrDup( ptr ) \
    memMSC_DebugStrDup( memMSC_Shared(), ptr, __FILE__, __LINE__ )
#endif
    
    
    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    MEMMSC_DATA *     memMSC_Alloc(
    );
    
    
    MEMMSC_DATA *     memMSC_New(
    );
    
    
    MEMMSC_DATA *     memMSC_Shared(
    );
    
    MEMMSC_DATA *     memMSC_SharedReset(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            memMSC_getDebug(
        MEMMSC_DATA     *this
    );
    
    bool            memMSC_setDebug(
        MEMMSC_DATA     *this,
        bool            value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    void *          memMSC_DebugCalloc(
        MEMMSC_DATA		*this,
        size_t			cNum,
        size_t			cSize,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    bool			memMSC_DebugCheck(
        MEMMSC_DATA		*this,
        const
        char			*pFilePath,
        size_t			iLine
    );


    bool			memMSC_DebugCheckArea(
        MEMMSC_DATA		*this,
        void            *pData,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    bool			memMSC_DebugDidAlloc(
        MEMMSC_DATA		*this,
        void			*pData,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    bool			memMSC_DebugDump(
        MEMMSC_DATA		*this,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    bool			memMSC_DebugFree(
        MEMMSC_DATA		*this,
        void			*pData,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    bool			memMSC_DebugFreeObject(
        MEMMSC_DATA		*this,
        void			*pData,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    size_t          memMSC_DebugGetSize(
        MEMMSC_DATA		*this,
        void			*pData,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    void *			memMSC_DebugMalloc(
        MEMMSC_DATA		*this,
        size_t			cbSize,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    void *			memMSC_DebugMallocObject(
        MEMMSC_DATA		*this,
        size_t			cbSize,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    void *			memMSC_DebugRealloc(
        MEMMSC_DATA		*this,
        void			*pData,
        size_t			cbSize,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    char *          memMSC_DebugStrDup(
        MEMMSC_DATA		*this,
        const
        char			*pOldStr,
        const
        char			*pFilePath,
        size_t			iLine
    );
    
    
    MEMMSC_DATA *   memMSC_Init(
        MEMMSC_DATA     *this
    );


    /*!
     Create a string that describes this object and the
     objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = memMSC_ToDebugString(pObj,4);
     @endcode:
     @param:    this    object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released,
     otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    memMSC_ToDebugString(
        MEMMSC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MEMMSC_H */

