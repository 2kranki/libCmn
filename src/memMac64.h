// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  MacOS 64-Bit Memory Debug (memMac64) Header
//****************************************************************
/*
 * Program
 *          MacOS 64-Bit Memory Debug (memMac64)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate memMac64 to run things without complications
 *          of interfering with the main memMac64. A memMac64 may be 
 *          called a memMac64 on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  02/08/2016 Generated
 *  02/15/2021 Regenerated
 *  02/21/2021 Added multi-tasking support
 *  02/28/2021 Fixed several locking problems and Added bypass support
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


#ifndef         MEMMAC64_H
#define         MEMMAC64_H


//#define   MEMMAC64_IS_IMMUTABLE     1
//#define   MEMMAC64_JSON_SUPPORT     1
#define   MEMMAC64_SINGLETON        1



#undef mem_Calloc
#if        defined(NDEBUG)
#    define    mem_Calloc( Num, Size )\
    calloc( Num, Size )
#else
#    define    mem_Calloc( Num, Size )\
    memMac64_DebugCalloc( memMac64_Shared(), Num, Size, __FILE__, __LINE__ )
#endif

#undef mem_CallocAbort
#if        defined(NDEBUG)
#    define    mem_CallocAbort( Num, Size )\
    memMac64_CallocAbort( memMac64_Shared(), Num, Size, __FILE__, __LINE__ )
#else
#    define    mem_CallocAbort( Num, Size )\
    memMac64_DebugCallocAbort( memMac64_Shared(), Num, Size, __FILE__, __LINE__ )
#endif

#undef mem_CheckArea
#if        defined(NDEBUG)
#    define    mem_CheckArea( pData )\
/* */
#else
#    define    mem_CheckArea( pData )\
memMac64_DebugCheckArea( memMac64_Shared(), pData, __FILE__, __LINE__ )
#endif

#undef mem_Dump
#if        defined(NDEBUG)
#    define    mem_Dump( )\
    /* */
#else
#    define    mem_Dump( )\
    memMac64_DebugDump( memMac64_Shared(), __FILE__, __LINE__ )
#endif

#undef mem_Free
#if        defined(NDEBUG)
#   define  mem_Free( ptr )  free( ptr )
#else
#   define  mem_Free( ptr ) \
    memMac64_DebugFree( memMac64_Shared(), ptr, __FILE__, __LINE__ )
#endif

#undef mem_FreeObject
#if        defined(NDEBUG)
#   define  mem_FreeObject( ptr )  free( ptr )
#else
#   define  mem_FreeObject( ptr ) \
    memMac64_DebugFreeObject( memMac64_Shared(), ptr, __FILE__, __LINE__ )
#endif

#undef mem_Init
#if        defined(NDEBUG)
#    define    mem_Init( )\
    /* */
#else
#    define    mem_Init( )\
    memMac64_Shared()
#endif

#undef mem_Malloc
#if        defined(NDEBUG)
#   define  mem_Malloc( size ) \
malloc( size )
#else
#   define  mem_Malloc( size ) \
    memMac64_DebugMalloc( memMac64_Shared(), size, __FILE__, __LINE__ )
#endif

#undef mem_MallocAbort
#if        defined(NDEBUG)
#   define  mem_MallocAbort( size ) \
    memMac64_CallocAbort( memMac64_Shared(), 1, (size), __FILE__, __LINE__ )
#else
#   define  mem_MallocAbort( size ) \
    memMac64_DebugCallocAbort( memMac64_Shared(), 1, (size), __FILE__, __LINE__ )
#endif

#undef mem_MallocObject
#if        defined(NDEBUG)
#   define  mem_MallocObject( size ) \
    malloc( size )
#else
#   define  mem_MallocObject( size ) \
    memMac64_DebugMallocObject( memMac64_Shared(), size, __FILE__, __LINE__ )
#endif

#undef mem_Realloc
#if        defined(NDEBUG)
#   define  mem_Realloc( ptr, size ) \
    realloc( ptr, size )
#else
#   define  mem_Realloc( ptr, size ) \
    memMac64_DebugRealloc( memMac64_Shared(), ptr, size, __FILE__, __LINE__ )
#endif

#undef mem_Release
#if        defined(NDEBUG)
#    define    mem_Release( )\
/* */
#else
#    define    mem_Release( )\
memMac64_SharedReset()
#endif

#undef mem_StrDup
#if        defined(NDEBUG)
#   define  mem_StrDup( ptr ) \
    strdup( ptr )
#else
#   define  mem_StrDup( ptr ) \
    memMac64_DebugStrDup( memMac64_Shared(), ptr, __FILE__, __LINE__ )
#endif




#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct memMac64_data_s  MEMMAC64_DATA;            // Inherits from OBJ
    typedef struct memMac64_class_data_s MEMMAC64_CLASS_DATA;   // Inherits from OBJ

    typedef struct memMac64_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in memMac64_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MEMMAC64_DATA *);
    } MEMMAC64_VTBL;

    typedef struct memMac64_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in memMac64_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MEMMAC64_DATA *);
    } MEMMAC64_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  MEMMAC64_SINGLETON
    MEMMAC64_DATA * memMac64_Shared (
        void
    );

    void            memMac64_SharedReset (
        void
    );
#endif


    OBJ_ID          memMac64_Class (
        void
    );
    
    
    MEMMAC64_DATA * memMac64_New (
        void
    );
    
    
#ifdef  MEMMAC64_JSON_SUPPORT
    MEMMAC64_DATA * memMac64_NewFromJsonString (
        ASTR_DATA       *pString
    );

    MEMMAC64_DATA * memMac64_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            memMac64_getBypass (
        MEMMAC64_DATA   *this
    );

    bool            memMac64_setBypass (
        MEMMAC64_DATA   *this,
        bool            fValue
    );


    bool            memMac64_getDebug(
        MEMMAC64_DATA   *this
    );

    bool            memMac64_setDebug(
        MEMMAC64_DATA   *this,
        bool            value
    );


    bool            memMac64_setLeakExit(
        MEMMAC64_DATA   *this,
        P_VOID_EXIT1    rtn,
        void            *pObject
    );


    const
    char *          memMac64_getTitle(
        MEMMAC64_DATA   *this
    );

    bool            memMac64_setTitle(
        MEMMAC64_DATA   *this,
        const
        char            *pValue
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    void *          memMac64_CallocAbort(
        MEMMAC64_DATA    *this,
        size_t            cNum,
        size_t            cSize,
        const
        char            *pFilePath,
        size_t            iLine
    );


    void *          memMac64_DebugCalloc(
        MEMMAC64_DATA    *this,
        size_t            cNum,
        size_t            cSize,
        const
        char            *pFilePath,
        size_t            iLine
    );


    void *          memMac64_DebugCallocAbort(
        MEMMAC64_DATA    *this,
        size_t            cNum,
        size_t            cSize,
        const
        char            *pFilePath,
        size_t            iLine
    );


    bool            memMac64_DebugCheck(
        MEMMAC64_DATA    *this,
        const
        char            *pFilePath,
        size_t            iLine
    );


    bool            memMac64_DebugCheckArea(
        MEMMAC64_DATA    *this,
        void            *pData,
        const
        char            *pFilePath,
        size_t            iLine
    );


    bool            memMac64_DebugDidAlloc(
        MEMMAC64_DATA    *this,
        void            *pData,
        const
        char            *pFilePath,
        size_t            iLine
    );


    bool            memMac64_DebugDump(
        MEMMAC64_DATA    *this,
        const
        char            *pFilePath,
        size_t            iLine
    );


    bool            memMac64_DebugFree(
        MEMMAC64_DATA    *this,
        void            *pData,
        const
        char            *pFilePath,
        size_t            iLine
    );


    bool            memMac64_DebugFreeObject(
        MEMMAC64_DATA    *this,
        void            *pData,
        const
        char            *pFilePath,
        size_t            iLine
    );


    size_t          memMac64_DebugGetSize(
        MEMMAC64_DATA    *this,
        void            *pData,
        const
        char            *pFilePath,
        size_t            iLine
    );


    void *            memMac64_DebugMalloc(
        MEMMAC64_DATA    *this,
        size_t            cbSize,
        const
        char            *pFilePath,
        size_t            iLine
    );


    void *            memMac64_DebugMallocAbort(
        MEMMAC64_DATA    *this,
        size_t            cbSize,
        const
        char            *pFilePath,
        size_t            iLine
    );


    void *            memMac64_DebugMallocObject(
        MEMMAC64_DATA    *this,
        size_t            cbSize,
        const
        char            *pFilePath,
        size_t            iLine
    );


    void *            memMac64_DebugRealloc(
        MEMMAC64_DATA    *this,
        void            *pData,
        size_t            cbSize,
        const
        char            *pFilePath,
        size_t            iLine
    );


    char *          memMac64_DebugStrDup(
        MEMMAC64_DATA    *this,
        const
        char            *pOldStr,
        const
        char            *pFilePath,
        size_t            iLine
    );


    /*!
     Allocate a memory area or abort if it does not work. No memory over-write
     areas are added. This is only used if NDEBUG is set. This bypasses all
     debugging mechanisms.
     @param     this        object pointer
     @param     cbSize      memory area size in bytes
     @param     pFilePath   program file path
     @param     iLine       line number within program file path
     @return    If successful, memory pointer, otherwise NULL.
     @warning   Remember to free the returned memory area.
     */
    void *          memMac64_MallocAbort(
        MEMMAC64_DATA   *this,
        size_t          cbSize,
        const
        char            *pFilePath,
        size_t          iLine
    );

 
#ifdef  MEMMAC64_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = memMac64_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     memMac64_ToJson (
        MEMMAC64_DATA   *this
    );
#endif


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
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     memMac64_ToDebugString (
        MEMMAC64_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* MEMMAC64_H */

