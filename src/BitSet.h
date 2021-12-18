// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Set of Bits (BitSet) Header
//****************************************************************
/*
 * Program
 *			Set of Bits (BitSet)
 * Purpose
 *			This object provides Set of Bits (on/off).
 *
 * Remarks
 *  1.      All indices are relative to one.
 *
 * History
 *  06/21/2015 Generated
 *	12/18/2019 Regenerated
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
#include        <u32Array.h>


#ifndef         BITSET_H
#define         BITSET_H


//#define   BITSET_JSON_SUPPORT 1
//#define   BITSET_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BitSet_data_s	BITSET_DATA;            // Inherits from OBJ
    typedef struct BitSet_class_data_s BITSET_CLASS_DATA;   // Inherits from OBJ

    typedef struct BitSet_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BitSet_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BITSET_DATA *);
    } BITSET_VTBL;

    typedef struct BitSet_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BitSet_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BITSET_DATA *);
    } BITSET_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BITSET_SINGLETON
    BITSET_DATA *   BitSet_Shared (
        void
    );

    bool            BitSet_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to BitSet object if successful, otherwise OBJ_NIL.
     */
    BITSET_DATA *   BitSet_Alloc (
        void
    );
    
    
    OBJ_ID          BitSet_Class (
        void
    );
    
    
    BITSET_DATA *   BitSet_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = BitSet_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another BITSET object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         BitSet_Assign (
        BITSET_DATA     *this,
        BITSET_DATA     *pOther
    );


    // Returns ERESULT_SUCCESS if the Other set is fully
    // contained within our set.
    ERESULT         BitSet_Contains (
        BITSET_DATA     *this,
        BITSET_DATA     *pOther
    );
    
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        BitSet      *pCopy = BitSet_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a BITSET object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BITSET_DATA *   BitSet_Copy (
        BITSET_DATA     *this
    );


    /*!
     Expand the set to be at least "size" bits. Zero any bits added.
     @param     this    object pointer
     @param     size    new number of bits
     @return    If successful, ERESULT_SUCCESS; otherwise an ERESULT_*
                error.
     */
    ERESULT         BitSet_Expand (
        BITSET_DATA     *this,
        uint32_t        size
    );


    bool            BitSet_Get (
        BITSET_DATA     *this,
        uint32_t        index
    );


    BITSET_DATA *   BitSet_Init (
        BITSET_DATA     *this
    );


    // this = this & pOther;
    ERESULT         BitSet_Intersect (
        BITSET_DATA     *this,
        BITSET_DATA     *pOther
    );
    
    
    // this = -this;
    ERESULT         BitSet_Invert (
        BITSET_DATA     *this
    );
    
    
    ERESULT         BitSet_IsEmpty (
        BITSET_DATA     *this
    );
    
    
    // Returns ERESULT_SUCCESS_TRUE if the
    // two sets are equal. Otherwise, it
    // returns ERESULT_SUCCESS_FALSE. Note:
    // both are successful result codes.
    ERESULT         BitSet_IsEqual (
        BITSET_DATA     *this,
        BITSET_DATA     *pOther
    );
    

    /*! Invert the given bit. This method requires that
     the bit must exist in the set.
     @param this    object pointer
     @param index   the index to the bit (relative to 1)
     @return        ERESULT_SUCCESS or an ERESULT_* error code
     */
    ERESULT         BitSet_Not (
        BITSET_DATA     *this,
        uint32_t        index
    );


    /*! Set the given bit expanding the bit set if necessary.
     @param this    object pointer
     @param index   the index to the bit (relative to 1)
     @param value   true or false
     @return        ERESULT_SUCCESS or an ERESULT_* error code
     */
    ERESULT         BitSet_Set (
        BITSET_DATA     *this,
        uint32_t        index,
        bool            value
    );
    
    
    /*! Set all the bits currently in the set to true.
     @param this    object pointer
     @return        ERESULT_SUCCESS or an ERESULT_* error code
     */
    ERESULT         BitSet_SetAll (
        BITSET_DATA     *this
    );
    
    
    // this = this - pOther;
    // which is the same as:
    // this = this & ^pOther;
    ERESULT         BitSet_Subtract (
        BITSET_DATA     *this,
        BITSET_DATA     *pOther
    );
    
    
    /*!
     Create a u32Array that contains the index to every element in this
     set.
     @param     this    object pointer
     @return    If successful, an u32Array object which must be released
                containing the set element numbers, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    U32ARRAY_DATA * BitSet_ToArrayU32 (
        BITSET_DATA     *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BitSet_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BitSet_ToDebugString (
        BITSET_DATA     *this,
        int             indent
    );
    
    
    /*!
     Create a string that contains this set as a collection of 4-byte integers
     using normal C/C++ syntax (ie. 0X01234). If multiple numbers are required,
     they are separated by ", ".
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                data, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BitSet_ToString (
        BITSET_DATA     *this
    );
    
    
    // this = this | pOther;
    // Returns:
    //      ERESULT_SUCCESS (if nothing changed)
    //      ERESULT_DATA_CHANGED (if bitset changed)
    ERESULT         BitSet_Union (
        BITSET_DATA     *this,
        BITSET_DATA     *pOther
    );


    ERESULT         BitSet_Zero (
        BITSET_DATA     *this
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* BITSET_H */

