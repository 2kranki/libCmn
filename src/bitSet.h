// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Bit Set (bitset) Header
//****************************************************************
/*
 * Program
 *				Bit Set (bitset)
 * Purpose
 *				This object provides a standardized way of handling
 *              a Bit Set.
 *
 * Remarks
 *	1.      All indices are relative to one.
 *
 * History
 *	06/21/2015 Generated
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


#ifndef         bitSet_H
#define         bitSet_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct bitSet_data_s	BITSET_DATA;

    typedef struct bitSet_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        // Properties:
        // Methods:
    } BITSET_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    BITSET_DATA *   bitSet_Alloc(
        uint16_t        size        // Maximum Number of bits in set
    );
    
    
    BITSET_DATA *   bitSet_New(
        uint16_t        size        // Maximum Number of bits in set
    );
    
    
    OBJ_ID          bitSet_Class(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        bitSet_getSize(
        BITSET_DATA     *this
    );
    
    
    // Number of 32-bit elements used in bitset
    uint16_t        bitSet_getSizeUsed(
        BITSET_DATA     *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    // this = pOther;
    ERESULT         bitSet_Assign(
        BITSET_DATA		*this,
        BITSET_DATA		*pOther
    );
    
    
    // Returns ERESULT_SUCCESSFUL_COMPLETION if the Other set is fully
    // contained within our set.
    ERESULT         bitSet_Contains(
        BITSET_DATA		*this,
        BITSET_DATA		*pOther
    );
    
    
    BITSET_DATA *   bitSet_Copy(
        BITSET_DATA		*this
    );
    
    
    bool            bitSet_Get(
        BITSET_DATA		*this,
        uint16_t        index
    );


    BITSET_DATA *   bitSet_Init(
        BITSET_DATA     *this
    );


    // this = this & pOther;
    ERESULT         bitSet_Intersect(
        BITSET_DATA		*this,
        BITSET_DATA		*pOther
    );
    
    
    // this = -this;
    ERESULT         bitSet_Invert(
        BITSET_DATA		*this
    );
    
    
    ERESULT         bitSet_IsEmpty(
        BITSET_DATA		*this
    );
    
    
    // Returns ERESULT_SUCCESS_TRUE if the
    // two sets are equal. Otherwise, it
    // returns ERESULT_SUCCESS_FALSE. Note:
    // both are successful result codes.
    ERESULT         bitSet_IsEqual(
        BITSET_DATA		*this,
        BITSET_DATA		*pOther
    );
    
    
    ERESULT         bitSet_Set(
        BITSET_DATA		*this,
        uint16_t        index,
        bool            value
    );
    
    
    ERESULT         bitSet_SetEmpty(
        BITSET_DATA		*this
    );
    
    
    // this = this - pOther;
    // which is the same as:
    // this = this & ^pOther;
    ERESULT         bitSet_Subtract(
        BITSET_DATA		*this,
        BITSET_DATA		*pOther
    );
    
    
    // The string returned must be obj_Release()'d.
    ASTR_DATA *     bitSet_ToDataString(
        BITSET_DATA     *this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     bitSet_ToDebugString(
        BITSET_DATA     *this,
        int             indent
    );
    
    
    /*!
     Create a string that describes this object as a static const 
     uint32_t array with the given name.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     bitSet_ToUint32String(
        BITSET_DATA     *this,
        const
        char            *pName
    );
    
    
    // this = this | pOther;
    // Returns:
    //      ERESULT_SUCCESSFUL_COMPLETION (if nothing changed)
    //      ERESULT_DATA_CHANGED (if bitset changed)
    ERESULT         bitSet_Union(
        BITSET_DATA		*this,
        BITSET_DATA		*pOther
    );
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* bitSet_H */

