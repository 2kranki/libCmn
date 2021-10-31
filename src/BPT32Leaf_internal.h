// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   BPT32Leaf_internal.h
 *	Generated 01/12/2019 14:04:41
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




#include        <BPT32Leaf.h>
#include        <JsonIn.h>


#ifndef BPT32LEAF_INTERNAL_H
#define	BPT32LEAF_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif



    /*      Node Descriptor
     */
#pragma pack(push, 1)
    typedef struct  BPT32Leaf_Node_s {
        //uint32_t        prev;         // Previous Leaf Node Index
        //uint32_t        next;         // Next Leaf Node Index
        uint32_t        key;           // Key Length
        uint8_t         data[0];
    } BPT32LEAF_NODE;
#pragma pack(pop)
    
    
#pragma pack(push, 1)
    typedef struct  BPT32Leaf_block_s {
        uint8_t         blockType;      // 'L'
        uint8_t         rsvd8;
        uint16_t        dataSize;
        uint16_t        actualSize;     // Actual Data Size rounded up
        uint16_t        max;            // Maximum Number of nodes
        uint16_t        used;           // Number of nodes in use
        uint32_t        prev;           // Previous Leaf Node Index
        uint32_t        next;           // Next Leaf Node Index
        BPT32LEAF_NODE  nodes[0];
    } BPT32LEAF_BLOCK;
#pragma pack(pop)
    
    

    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct BPT32Leaf_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define BPT32LEAF_BLOCK_ALLOC     OBJ_FLAG_USER1

    // Common Data
    //uint16_t        rsvd16;
    uint16_t        dataSize;       // Size of Data in node
    uint16_t        actualSize;     // Actual Data Size rounded up
    uint32_t        blockSize;
    uint32_t        lbn;            // Block Index Number in Dataset/File
    uint32_t        maxRcds;        // Maximum Number of Records in a Block
    BPT32LEAF_BLOCK *pBlock;
    uint32_t        lastKey;
    uint32_t        lastIndex;

    OBJ_ID          *pMgr;          // Block Manager
    P_ERESULT_EXIT5 pReq;           // Block Manager Request Method

};
#pragma pack(pop)

    extern
    struct BPT32Leaf_class_data_s  BPT32Leaf_ClassObj;

    extern
    const
    BPT32LEAF_VTBL         BPT32Leaf_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPT32LEAF_SINGLETON
    BPT32LEAF_DATA * BPT32Leaf_getSingleton (
        void
    );

    bool            BPT32Leaf_setSingleton (
     BPT32LEAF_DATA     *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  BPT32Leaf_getSuperVtbl (
        BPT32LEAF_DATA   *this
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = BPT32Leaf_Assign(this,pOther);
     @endcode
     @param     this    BPT32LEAF object pointer
     @param     pOther  a pointer to another BPT32LEAF object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         BPT32Leaf_Assign (
        BPT32LEAF_DATA     *this,
        BPT32LEAF_DATA     *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        BPT32Leaf      *pCopy = BPT32Leaf_Copy(this);
     @endcode
     @param     this    BPT32LEAF object pointer
     @return    If successful, a BPT32LEAF object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPT32LEAF_DATA *     BPT32Leaf_Copy (
        BPT32LEAF_DATA       *this
    );


    void            BPT32Leaf_Dealloc (
        OBJ_ID          objId
    );


    BPT32LEAF_NODE *  BPT32Leaf_FindNode (
        BPT32LEAF_DATA  *this,
        uint32_t        key,
        uint32_t        *pIndex
    );
    
    
    BPT32LEAF_NODE * BPT32Leaf_Index2Node (
        BPT32LEAF_DATA  *this,
        uint32_t        index
    );
    
    
    BPT32LEAF_DATA *       BPT32Leaf_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          BPT32Leaf_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     BPT32Leaf_ToJSON (
        BPT32LEAF_DATA    *this
    );


#ifdef NDEBUG
#else
    bool			BPT32Leaf_Validate (
        BPT32LEAF_DATA    *this
    );
#endif


    ERESULT         BPT32Leaf_Verify (
        BPT32LEAF_DATA    *this
    );
    
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* BPT32LEAF_INTERNAL_H */

