// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Hash Table of Objects (ObjHash) Header
//****************************************************************
/*
 * Program
 *			Hash Table of Objects (ObjHash)
 * Purpose
 *          This object provides a standardized way of handling
 *          a Hash table for objects. The objects must support
 *          the compare() and hash() functions in their object
 *          vtbl. Since this is how the objects are looked at,
 *          this table has no knowledge of a key and objects
 *          must always be suppied for searches, deletions, etc.
 *
 *          The hash chains are manipulated like a push down
 *          stack with the latest addition being the closest
 *          to the head of the chain. So, if duplicate entries
 *          are allowed (see duplicates property), the
 *          lastest addition of that name will be the first
 *          to be found.
 *
 *          Entries are now added to the Hash chains and to
 *          Scope chains.  The default Scope level is 0. Scopes
 *          are a push-down stack. When a Scope is popped,
 *          all of its entries are removed from the table.
 *          ScopeOpen() pushes a new Scope level. ScopeClose()
 *          pops the scope level.
 *
 * Remarks
 *    1.    The objects added to this table must support the
 *          compare() and hash() methods. The compare() method
 *          must be able to compare its object against any
 *          other object in the table.  These methods are
 *          part of the common VTBL for each object, and must
 *          be implemented.
 *
 * History
 *  10/24/2015  Generated
 *  01/31/2018  Added the ability to have duplicate symbols
 *	02/02/2020  Regenerated and upgraded json
 *  12/16/2021  Added Scope levels.
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
#include        <Blocks.h>
#include        <ObjEnum.h>


#ifndef         OBJHASH_H
#define         OBJHASH_H


//#define   OBJHASH_IS_IMMUTABLE     1
#define   OBJHASH_JSON_SUPPORT     1
//#define   OBJHASH_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ObjHash_data_s	OBJHASH_DATA;            // Inherits from BLOCKS
    typedef struct ObjHash_class_data_s OBJHASH_CLASS_DATA;   // Inherits from OBJ

    typedef struct ObjHash_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjHash_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJHASH_DATA *);
    } OBJHASH_VTBL;

    typedef struct ObjHash_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjHash_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJHASH_DATA *);
    } OBJHASH_CLASS_VTBL;


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

#ifdef  OBJHASH_SINGLETON
    OBJHASH_DATA *  ObjHash_Shared (
        void
    );

    void            ObjHash_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ObjHash object if successful, otherwise OBJ_NIL.
     */
    OBJHASH_DATA *  ObjHash_Alloc (
        void
    );
    
    
    OBJ_ID          ObjHash_Class (
        void
    );
    
    
    OBJHASH_DATA *  ObjHash_New (
        void
    );
    
    
    OBJHASH_DATA *  ObjHash_NewWithSize (
        uint16_t        cHash       // [in] Hash Table Size
    );


#ifdef  OBJHASH_JSON_SUPPORT
    OBJHASH_DATA *  ObjHash_NewFromJsonString (
        ASTR_DATA       *pString
    );

    OBJHASH_DATA *  ObjHash_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     @property  Duplicates is set true (default) if duplicates are allowed
                or false if they are not.
     */
    bool            ObjHash_getDuplicates (
        OBJHASH_DATA    *this
    );

    bool            ObjHash_setDuplicates (
        OBJHASH_DATA    *this,
        bool            fValue
    );


    uint32_t        ObjHash_getScopeSize (
        OBJHASH_DATA    *this
    );


    uint32_t        ObjHash_getSize (
        OBJHASH_DATA    *this
    );


    BLOCKS_DATA *   ObjHash_getSuper (
        OBJHASH_DATA    *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add an object to the Hash Table if the supplied key does not exist
     in the table or if duplicates are allowed.  The object being added
     must support the compare() and hash() methods and will be added to
     the current scope.
     @param     this    object pointer
     @param     pObject object pointer to be added to the table
     @param     pIndex  An optional pointer to uint32_t which will contain
                a unique number for the object if it is added to the Hash
                successfully.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjHash_Add (
        OBJHASH_DATA    *this,
        OBJ_ID          pObject,
        uint32_t        *pIndex
    );

    /*!
     Add an object to the Hash Table if the supplied key does not exist
     in the table or if duplicates are allowed.  The object being added
     must support the compare() and hash() methods and will be added to
     the current scope.
     @param     this    object pointer
     @param     pObject object pointer to be added to the table
     @param     pIndex  An optional pointer to uint32_t which will contain
                a unique number for the object if it is added to the Hash
                successfully.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjHash_AddInScope (
        OBJHASH_DATA    *this,
        uint32_t        scope,
        OBJ_ID          pObject,
        uint32_t        *pIndex
    );

    /*!
     Add an object to the Hash Table as a singleton entry which will not
     be added to the hash or scope indices.  It can only be accessed with
     ObjHash_FindIndex() and deleted with DeleteUnlinked(). It will not
     added into the ObjHash's indices.
     @param     this    object pointer
     @param     pObject object pointer to be added to the table
     @param     pIndex  An optional pointer to uint32_t which will contain
                        a unique number for the object if it is added to the
                        Hash successfully.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjHash_AddUnlinked(
        OBJHASH_DATA    *this,
        OBJ_ID          pObject,
        uint32_t        *pIndex
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = ObjHash_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another OBJHASH object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         ObjHash_Assign (
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
    ERESULT         ObjHash_CalcHashStats (
        OBJHASH_DATA    *this,
        uint32_t        *pNumBuckets,   // Number of Hash Buckets
        uint32_t        *pNumEmpty,     // Number of Empty Hash Buckets
        uint32_t        *pNumMax,       // Maximum Number in any one Hash Bucket
        uint32_t        *pNumAvg        // Average Number in each Hash Bucket
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        ObjHash      *pCopy = ObjHash_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a OBJHASH object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJHASH_DATA *     ObjHash_Copy (
        OBJHASH_DATA       *this
    );


    /*! Delete the first entry found matching the given object
        from the hash and returns it.
     @return    return the object deleted from the hash if successful.
                Otherwise, return OBJ_NIL and set an ERESULT_* error.
     */
    OBJ_ID          ObjHash_Delete (
        OBJHASH_DATA    *this,
        OBJ_ID          pObject
    );


    /*! Delete all entries found in the hash.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjHash_DeleteAll (
        OBJHASH_DATA    *this
    );


    /*! Delete the object for the given index.
     @return    If successful, the object deleted. Otherwise, return OBJ_NIL
                and set an ERESULT_* error.
     */
    OBJ_ID          ObjHash_DeleteIndex (
        OBJHASH_DATA    *this,
        uint32_t        index
    );


    /*! Delete the object for the given index which must have been added
     to the Hash by AddUnlinked().  DeleteIndex() should be used if AddUnlinked()
     was not used.
     @return    If successful, the object deleted. Otherwise, return OBJ_NIL
                and set an ERESULT_* error.
     */
    ERESULT         ObjHash_DeleteUnlinked(
        OBJHASH_DATA    *this,
        uint32_t        index
    );


    /*! Create an enumerator for the Hash in ascending order
         if the object contains a compare() method.
     @param     this    object pointer
     @return    If successful, an Enumerator object which must be
                 released, otherwise OBJ_NIL.
     @warning   Remember to release the returned Enumerator.
     */
    OBJENUM_DATA *  ObjHash_Enum (
        OBJHASH_DATA    *this
    );


    /*! Find searches the appropriate object chain for the first entry
        which matches using the object's comparison routine.
     @param     this    object pointer
     @return    If successful, the object address. Otherwise, return OBJ_NIL.
     */
    OBJ_ID          ObjHash_Find (
        OBJHASH_DATA    *this,
        OBJ_ID          pObject
    );


    OBJ_ID          ObjHash_FindCmp(
        OBJHASH_DATA    *this,
        OBJ_ID          pObject,
        P_OBJ_COMPARE   pCmp
    );


    /*! Find the object for the given index.
     @param     this    object pointer
     @return    If successful, the object address. Otherwise, return OBJ_NIL.
     */
    OBJ_ID          ObjHash_FindIndex (
        OBJHASH_DATA    *this,
        uint32_t        index
    );


    /*! Find the n'th object for the given object.
     @param     this    object pointer
     @return    If successful, the object address. Otherwise, return OBJ_NIL.
     */
    OBJ_ID          ObjHash_Findth(
        OBJHASH_DATA    *this,
        OBJ_ID          pObject,
        uint16_t        index           // 0..n th entry with same name
    );


    OBJHASH_DATA *  ObjHash_Init (
        OBJHASH_DATA    *this
    );


    /*!
     Delete the current Scope if it is greater than 0 and optionally
     return an enumerator for those objects.  The objects will be deleted
     from the Hash Table. Optionally they will be returned in an Enumerator
     if you want the use of them.
     @param     this    object pointer
     @param     ppEnum  optional Enumerator object return pointer
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error.
     */
    ERESULT         ObjHash_ScopeClose (
        OBJHASH_DATA    *this,
        OBJENUM_DATA    **ppEnum
    );


    /*!
     Get the number of entries in the specified Scope.
     @param     this    object pointer
     @param     scope   scope level number (relative to 0)
     @return    If successful, the nuimber of entries in the requested scope.
                Otherwise, 0.
     */
    uint32_t        ObjHash_ScopeCount (
        OBJHASH_DATA    *this,
        uint32_t        scope
    );


    /*! Create an enumerator for the Scope in ascending order
         if the object contains a compare() method.
     @param     this    object pointer
     @param     scope   scope number (relative to 0)
     @return    If successful, an Enumerator object which must be
                 released, otherwise OBJ_NIL.
     @warning   Remember to release the returned Enumerator.
     */
    OBJENUM_DATA *  ObjHash_ScopeEnum (
        OBJHASH_DATA    *this,
        uint32_t        scope
    );


    /*! Open a new Scope making it the current Scope. Scopes work
     like a push down stack with the newest one on the top.
     @param     this    object pointer
     @return    If successful, the new scope number relative to 0;
                otherwise -1;
     */
    int32_t         ObjHash_ScopeOpen (
        OBJHASH_DATA    *this
    );


#ifdef  OBJHASH_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ObjHash_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjHash_ToJson (
        OBJHASH_DATA    *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjHash_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    ObjHash_ToDebugString (
        OBJHASH_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJHASH_H */

