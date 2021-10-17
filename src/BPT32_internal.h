// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   BPT32_internal.h
 *	Generated 01/12/2019 14:04:44
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




#include        <BPT32.h>
#include        <BPT32Index_internal.h>
#include        <BPT32Leaf_internal.h>
#include        <JsonIn.h>
#include        <lru_internal.h>
#include        <ObjArray.h>
#include        <RRDS_internal.h>


#ifndef BPT_INTERNAL_H
#define	BPT_INTERNAL_H



#define     PROPERTY_IO_OWNED       1
#define     PROPERTY_PATH_OWNED     1
#define     PROPERTY_ROOT_OWNED     1
#define     PROPERTY_STR_OWNED      1



#ifdef	__cplusplus
extern "C" {
#endif


    //          Block Descriptor
#pragma pack(push, 1)
    typedef struct  BPT32_blkidx_s {
        OBJ_ID          pBlock;
        uint32_t        blockLsn;       // Current Node Number in Work Block
    } BPT_BLKIDX;
#pragma pack(pop)
    
    
    //                      File Header
    // This header is saved in the 1st record of the file.
#pragma pack(push, 1)
    typedef struct  BPT32_header_s {
        uint16_t        dataSize;       // Size of Data in node
        uint16_t        actualSize;
        uint32_t        blockSize;
        uint32_t        cRecords;       // Number of Records in the File including header
        uint32_t        root;           // Root Block Index
        uint32_t        dataHead;       // Head of Leaf Chain
        uint32_t        dataTail;       // End of Leaf Chain
        uint32_t        deleteHead;     // Head of Free Block Chain
    } BPT32_HEADER;
#pragma pack(pop)
    
    
    

    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct BPT32_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
    // OBJ_FLAG_USER1 is used in LRU

    // Common Data
    RRDS_DATA       *pIO;
    LRU_DATA        *pLRU;          // LRU Mechanism from RRDS (not owned)
    uint32_t        size;		    // maximum number of elements
    uint8_t         fMem;
    uint8_t         rsvd8;
    uint16_t        cLRU;
    uint16_t        cHash;
    uint16_t        dataSize;       // Size of Data in node
    uint32_t        blockSize;
    ASTR_DATA       *pStr;
    PATH_DATA       *pPath;
    OBJ_ID          pRoot;          // Root Record
    BPT32_HEADER    *pHdr;
    OBJARRAY_DATA   *pSrchStk;      // Search Block List

    uint32_t        lastLSN;
    uint32_t        lastKey;

};
#pragma pack(pop)

    extern
    struct BPT32_class_data_s  BPT32_ClassObj;

    extern
    const
    BPT32_VTBL       BPT32_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPT_SINGLETON
    BPT_DATA *     BPT32_getSingleton (
        void
    );

    bool            BPT32_setSingleton (
        BPT_DATA       *pValue
    );
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            BPT32_getMem (
        BPT32_DATA     *this
    );

    bool            BPT32_setMem (
        BPT32_DATA      *this,
        bool            fValue
    );


    bool            BPT32_setReadWrite (
        BPT32_DATA      *this,
        ERESULT         (*pBlockRead) (
                           OBJ_ID          pObject,
                           LBN32_T         lbn,                // Logical Sector Number
                           uint8_t         *pBuffer            // Buffer of sectorSize bytes
                           ),
        ERESULT         (*pBlockWrite) (
                            OBJ_ID         pObject,
                            LBN32_T        lsn,                // Logical Sector Number
                            uint8_t        *pBuffer            // Buffer of sectorSize bytes
                            ),
        OBJ_ID          pBlockObject
    );

    
    OBJ_IUNKNOWN *  BPT32_getSuperVtbl (
        BPT32_DATA      *this
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = BPT32_Assign(this,pOther);
     @endcode
     @param     this    BPT32 object pointer
     @param     pOther  a pointer to another BPT32 object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         BPT32_Assign (
        BPT32_DATA     *this,
        BPT32_DATA     *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        BPT32      *pCopy = BPT32_Copy(this);
     @endcode
     @param     this    BPT32 object pointer
     @return    If successful, a BPT32 object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPT32_DATA *    BPT32_Copy (
        BPT32_DATA      *this
    );


    void            BPT32_Dealloc (
        OBJ_ID          objId
    );


    ERESULT         BPT32_BlockRead(
        BPT32_DATA      *this,
        LBN32_T         lbn,                // Logical Block Number
        OBJ_ID          *ppObj
    );
    
    
    ERESULT         BPT32_BlockSearchKey (
        BPT32_DATA      *this,
        LBN32_T         lbn,                // Logical Block Number
        uint32_t        key,
        void            *pData
    );
    
    
    ERESULT         BPT32_BlockSplit(
        BPT32_DATA      *this,
        OBJ_ID          *pLeft,
        OBJ_ID          *pRight
    );
    
    
    BPT32_DATA *    BPT32_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          BPT32_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ERESULT         BPT32_SetupRRDS(
        BPT32_DATA      *this
    );
    
    
    ASTR_DATA *     BPT32_ToJSON (
        BPT32_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			BPT32_Validate (
        BPT32_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BPT_INTERNAL_H */

