// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Object Hash Table (objHash) Header
//****************************************************************
/*
 * Program
 *			Object Hash Table (objHash)
 * Purpose
 *			This object provides a standardized way of handling
 *          a Hash table for objects. The objects must support
 *          the compare() and hash() functions in their object
 *          vtbl. Since this is how the objects are looked at,
 *          this table has no knowledge of a key and objects
 *          must always be suppied for searches, deletions, etc.
 *
 *          The hash chains are manipulated like a push down
 *          stack with the latest addition being the closest
 *          to the head of the chain. So, if duplicate entries
 *          are allowed (see objHash_setDuplicates()), the
 *          lastest addition of that name will be the first
 *          to be found.
 *
 * Remarks
 *	1.      The objects added to this table must support the
 *          compare() and hash() methods. The compare() method
 *          must be able to compare its object against any
 *          other object in the table.  These methods are
 *          part of the common VTBL for each object.
 *
 * History
 *  01/31/2018  Added the ability to have duplicate symbols
 *	10/24/2015  Generated
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
#include        <objEnum.h>


#ifndef         OBJHASH_H
#define         OBJHASH_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct objHash_data_s	OBJHASH_DATA;

    typedef struct objHash_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fatFCB_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CB_DATA *);
    } OBJHASH_VTBL;
    
    

    // Prime numbers for hash table sizes within 16 bits
    // (Maximum size is 65535)
    typedef enum objHash_table_size_e {
        OBJHASH_TABLE_SIZE_XXXXXSMALL = 5,
        OBJHASH_TABLE_SIZE_XXXXSMALL = 17,
        OBJHASH_TABLE_SIZE_XXXSMALL = 31,
        OBJHASH_TABLE_SIZE_XXSMALL = 61,
        OBJHASH_TABLE_SIZE_XSMALL = 127,
        OBJHASH_TABLE_SIZE_SMALL = 257,
        OBJHASH_TABLE_SIZE_MEDIUM = 2053,
        OBJHASH_TABLE_SIZE_LARGE  = 4099,
        OBJHASH_TABLE_SIZE_XLARGE = 16411
    } OBJHASH_TABLE_SIZE;
    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    OBJHASH_DATA *  objHash_Alloc(
        void
    );
    
    
    OBJHASH_DATA *  objHash_New(
        uint16_t        cHash       // [in] Hash Table Size
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            objHash_getDuplicates(
        OBJHASH_DATA    *this
    );
    
    bool            objHash_setDuplicates(
        OBJHASH_DATA    *this,
        bool            fValue
    );
    

    ERESULT         objHash_getLastError(
        OBJHASH_DATA    *this
    );
    
    
    uint32_t        objHash_getSize(
        OBJHASH_DATA    *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*! Add an object to the Hash Table if the supplied key does not exist
     in the table or if duplicates are allowed.  The object being added
     must support the compare() and hash() methods.
     @param     this    object pointer
     @param     pObject object pointer to be added to the table
     @param     pIndex  An optional pointer to uint32_t which will contain
                a unique number for the object if it is added to the Hash
                successfully.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         objHash_Add(
        OBJHASH_DATA    *this,
        OBJ_ID          pObject,
        uint32_t        *pIndex
    );
    
    
    ERESULT         objHash_Assign(
        OBJHASH_DATA    *this,
        OBJHASH_DATA    *pOther
    );
    
    
    /*! Add an object to the Hash Table if the supplied key does not exist
     in the table or if duplicates are allowed.  The object being added
     must support the compare() and hash() methods.
     @param     this        object pointer
     @param     pNumBuckets Number of Hash Buckets in Index
     @param     pNumEmpty   Number of Empty Hash Buckets
     @param     pNumMax     Maximum Number of nodes in any one Hash Bucket
     @param     pNumAvg     Average Number of nodes in Hash Buckets that
                            have nodes
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT            objHash_CalcHashStats(
        OBJHASH_DATA    *this,
        uint32_t        *pNumBuckets,   // Number of Hash Buckets
        uint32_t        *pNumEmpty,     // Number of Empty Hash Buckets
        uint32_t        *pNumMax,       // Maximum Number in any one Hash Bucket
        uint32_t        *pNumAvg        // Average Number in each Hash Bucket
    );
    
    
    OBJHASH_DATA *  objHash_Copy(
        OBJHASH_DATA    *this
    );
    
    
    /*! Delete the first entry found matching the given object
        from the hash and returns it.
     @return    return the object deleted from the hash if successful.
                Otherwise, return OBJ_NIL and set an ERESULT_* error.
     */
    OBJ_ID          objHash_Delete(
        OBJHASH_DATA    *this,
        OBJ_ID          pObject
    );
    
    
    /*! Delete all entries found in the hash.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         objHash_DeleteAll(
        OBJHASH_DATA    *this
    );
    
    
    /*! Delete the object for the given index.
     @return    If successful, the object deleted. Otherwise, return OBJ_NIL
                and set an ERESULT_* error.
     */
    OBJ_ID          objHash_DeleteIndex(
        OBJHASH_DATA    *this,
        uint32_t        index
    );
    
    
    /*! Create an enumerator for the Hash in ascending order
         if the object contains a compare() method.
     @param     this    object pointer
     @return    If successful, an Enumerator object which must be
                 released, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    OBJENUM_DATA *  objHash_Enum(
        OBJHASH_DATA    *this
    );
    
    
    /* Find() returns the data associated with the given object if
     * found, otherwise OBJ_NIL is returned.
     */
    OBJ_ID          objHash_Find (
        OBJHASH_DATA    *this,
        OBJ_ID          pObject
    );
    
    
    /*! Find the object for the given index.
     @return    If successful, the object address. Otherwise, return OBJ_NIL.
     */
    OBJ_ID          objHash_FindIndex (
        OBJHASH_DATA    *this,
        uint32_t        index
    );
    
    
    OBJHASH_DATA *  objHash_Init(
        OBJHASH_DATA    *this,
        uint16_t        cHash       // [in] Hash Table Size
    );


    /*!
     Rebuild the hash index with a different number of Hash Buckets.
     This method allows you to grow the index dynamically as needed.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT            objHash_RebuildIndex(
        OBJHASH_DATA    *this,
        uint32_t        cHash           // Number of Hash Buckets
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     objHash_ToDebugString(
        OBJHASH_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJHASH_H */

