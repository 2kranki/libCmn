// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   BPT32Index_internal.h
 *	Generated 01/12/2019 14:04:35
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




#include        <BPT32Index.h>
#include        <JsonIn.h>


#ifndef BPT32INDEX_INTERNAL_H
#define	BPT32INDEX_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif



    /*      Node Descriptor
     */
#pragma pack(push, 1)
    typedef struct  BPT32Index_Node_s {
        //uint32_t        prev;           // Previous Leaf Node Index
        //uint32_t        next;           // Next Leaf Node Index
        uint32_t        key;
        uint32_t        index;
    } BPT32INDEX_NODE;
#pragma pack(pop)
    
    
#pragma pack(push, 1)
    typedef struct  BPT32Index_block_s {
        uint8_t         blockType;      // 'I'
        uint8_t         rsvd8;
        uint16_t        actualSize;     // Actual Data Size rounded up
        uint16_t        max;            // Maximum Number of nodes
        uint16_t        used;           // Number of nodes in use
        uint32_t        p0;             // Pointer 0
        BPT32INDEX_NODE nodes[0];
    } BPT32INDEX_BLOCK;
#pragma pack(pop)
    
    
    

    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct BPT32Index_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define BPT32INDEX_BLOCK_ALLOC    OBJ_FLAG_USER1

    // Common Data
    uint16_t        rsvd16;
    uint16_t        dataSize;       // Size of Data in node (NOT USED)
    uint32_t        blockSize;
    uint32_t        lbn;            // Logical Block Number in Dataset/File
    uint32_t        maxRcds;        // Maximum Number of Records in a Block
    BPT32INDEX_BLOCK *pBlock;
    
    OBJ_ID          *pMgr;          // Block Manager
    P_ERESULT_EXIT5 pReq;          // Block Manager Request Method
    
};
#pragma pack(pop)

    extern
    struct BPT32Index_class_data_s  BPT32Index_ClassObj;

    extern
    const
    BPT32INDEX_VTBL         BPT32Index_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPT32INDEX_SINGLETON
    BPT32INDEX_DATA * BPT32Index_getSingleton (
        void
    );

    bool            BPT32Index_setSingleton (
     BPT32INDEX_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  BPT32Index_getSuperVtbl (
        BPT32INDEX_DATA     *this
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = BPT32Index_Assign(this,pOther);
     @endcode
     @param     this    BPT32INDEX object pointer
     @param     pOther  a pointer to another BPT32INDEX object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         BPT32Index_Assign (
        BPT32INDEX_DATA        *this,
        BPT32INDEX_DATA     *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        BPT32Index      *pCopy = BPT32Index_Copy(this);
     @endcode
     @param     this    BPT32INDEX object pointer
     @return    If successful, a BPT32INDEX object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPT32INDEX_DATA *     BPT32Index_Copy (
        BPT32INDEX_DATA       *this
    );


    void            BPT32Index_Dealloc (
        OBJ_ID          objId
    );


    BPT32INDEX_NODE * BPT32Index_FindNode (
        BPT32INDEX_DATA   *this,
        uint32_t        key,
        uint32_t        *pIndex
    );
    
    
    BPT32INDEX_DATA * BPT32Index_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          BPT32Index_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ERESULT         BPT32Index_Split (
        BPT32INDEX_DATA   *this,
        uint32_t        key,
        uint32_t        data,
        uint32_t        nodeIndex,
        BPT32INDEX_DATA   **ppNew
    );
    
    
    ASTR_DATA *     BPT32Index_ToJSON (
        BPT32INDEX_DATA      *this
    );


#ifdef NDEBUG
#else
    bool			BPT32Index_Validate (
        BPT32INDEX_DATA       *this
    );
#endif



    ERESULT         BPT32Index_Verify (
        BPT32INDEX_DATA    *this
    );
    
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* BPT32INDEX_INTERNAL_H */

