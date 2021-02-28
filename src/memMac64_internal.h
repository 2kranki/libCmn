// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   memMac64_internal.h
 *  Generated 02/15/2021 16:01:03
 *
 * Notes:
 *  --  N/A
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




#include        <memMac64.h>
#include        <JsonIn.h>
#include        <listdl.h>


#ifndef MEMMAC64_INTERNAL_H
#define MEMMAC64_INTERNAL_H






#ifdef  __cplusplus
extern "C" {
#endif


//                        Memory Block Header
// This structure is the header of a memory block.    It lies before
// the actual memory block.
typedef struct mem_blockHeader_s     MEM_BLOCKHEADER;

struct mem_blockHeader_s {
    LISTDL_NODE         LDL;
    size_t              cbActual;            // Actual Block Size in uint8_t's
    size_t              cbSize;             // Requested Size in uint8_t's
    size_t              iLine;                // Creation Line Number with File
    size_t              size;                // True Size of Block excluding Header
    const
    char                *pFile;                // Creation File Name
    uint16_t            flags;
#define MEM_FLAG_OBJECT 0x0001
    uint16_t            filler1;
    MEMMAC64_DATA       *pMem;
    uint8_t             check[16];            // Check Value for Underrun
    // >>>>>>>>>>>>>>>>>  *** WARNING *** <<<<<<<<<<<<<<<<<<<<<<<<<
    // The offset of the Data must be on a DWORD boundary to be compatible
    // with OS/2 and MS/DOS.
    uint8_t             data[0];
};

typedef struct mem_blockTrailer_s     MEM_BLOCKTRAILER;

struct mem_blockTrailer_s {
    uint8_t             check[16];            // Check Value for Overrun
};
#define BLOCK_PDATA(pBlk) (pBlk->data)
#define BLOCK_PTRAILER(pBlk) ((MEM_BLOCKTRAILER *)(&pBlk->data[pBlk->cbSize]))
#define    Data2Block( pData )    ((void *)((uint8_t *)pData - offsetof(MEM_BLOCKHEADER,data)))




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct memMac64_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    LISTDL_DATA     blockList;
    uint8_t         fDebugMemory;
    uint8_t         fBypass;            // Bypass Debug Alloc/Free
    uint8_t         rsvd8[2];
    void            *pLeakExitObject;
    P_VOID_EXIT1    pLeakExit;          // Only called in memOSX_Dealloc if leaks are
    //                                  // present.
    const
    char            *pTitle;
    pthread_mutex_t mutex;

};
#pragma pack(pop)

    extern
    struct memMac64_class_data_s  memMac64_ClassObj;

    extern
    const
    MEMMAC64_VTBL         memMac64_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  MEMMAC64_SINGLETON
    MEMMAC64_DATA * memMac64_getSingleton (
        void
    );

    bool            memMac64_setSingleton (
     MEMMAC64_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  memMac64_getSuperVtbl (
        MEMMAC64_DATA     *this
    );


    ERESULT         memMac64_Assign (
        MEMMAC64_DATA    *this,
        MEMMAC64_DATA    *pOther
    );


    MEMMAC64_DATA * memMac64_Copy (
        MEMMAC64_DATA   *this
    );


    void            memMac64_Dealloc (
        OBJ_ID          objId
    );


    bool            memMac64_DebugCheckAreaInt(
        MEMMAC64_DATA   *this,
        void            *pData,
        const
        char            *pFilePath,
        size_t          iLine
    );


    void             memMac64_DebugDumpBlock(
        MEMMAC64_DATA        *this,
        const
        char            *pData
    );


    MEM_BLOCKHEADER * memMac64_DebugFind(
        MEMMAC64_DATA        *this,
        void            *pData
    );


    MEM_BLOCKHEADER * memMac64_DebugInternalMalloc(
        MEMMAC64_DATA     *this,
        size_t            cbSize,
        const
        char            *pFile,
        size_t            iLine
    );


    MEMMAC64_DATA * memMac64_Init (
        MEMMAC64_DATA   *this
    );


#ifdef  MEMMAC64_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    MEMMAC64_DATA * memMac64_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         memMac64_ParseJsonFields (
        JSONIN_DATA     *pParser,
        MEMMAC64_DATA   *pObject
    );
#endif


    void *          memMac64_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
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


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         memMac64_ToJsonFields (
        MEMMAC64_DATA   *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            memMac64_Validate (
        MEMMAC64_DATA   *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* MEMMAC64_INTERNAL_H */

