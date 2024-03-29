// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Dynamic Array (array) Header
//****************************************************************
/*
 * Program
 *			Dynamic Array (array)
 * Purpose
 *			This object provides a dynamic array. That is an array
 *			which is mutable. However, the original array definitions
 *			such as element size may not be changed once the array
 *			is created.
 *
 * Remarks
 *	1.      Since this object supports Assign(), the array elements
 *          should not contain pointers unless Assign() and Copy()
 *          are not used.
 *
 * History
 *	11/08/2017 Generated
 *  12/01/2021 Added support for Stack and Queue operations.
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


#ifndef         ARRAY_H
#define         ARRAY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct array_data_s	ARRAY_DATA;    // Inherits from OBJ.

    typedef struct array_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in array_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ARRAY_DATA *);
    } ARRAY_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to array object if successful, otherwise OBJ_NIL.
     */
    ARRAY_DATA *    array_Alloc(
        void
    );
    
    
    ARRAY_DATA *    array_New(
        void
    );
    
    
    ARRAY_DATA *    array_NewWithSize(
        uint16_t        elemSize        // Element Size in bytes
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint8_t *       array_getData(
        ARRAY_DATA      *this
    );
    
    
    uint16_t        array_getElemSize(
        ARRAY_DATA      *this
    );
    
    
    /*!
     Misc property can be used for any purpose needed.  It is not
     used by this object.
     */
    uint32_t        array_getMisc(
        ARRAY_DATA      *this
    );
    
    bool            array_setMisc(
        ARRAY_DATA      *this,
        uint32_t        value
    );

    
    /*!
     @property other to be used to associate some other object to
     this array as needed.
     */
    OBJ_ID          array_getOther(
        ARRAY_DATA      *this
    );

    bool            array_setOther(
        ARRAY_DATA      *this,
        OBJ_ID          pValue
    );


    uint32_t        array_getSize(
        ARRAY_DATA      *this
    );
    
    
    uint32_t        array_getSizeInBytes(
        ARRAY_DATA      *this
    );
    
    
    uint16_t        array_getZeroNew(
        ARRAY_DATA      *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    // Adjust array size up or down as long as it stays less than
    // the max array size (ie this will not expand the array).
    bool            array_AdjustSize(
        ARRAY_DATA      *this,
        int32_t         value
    );
    
    
    ERESULT         array_Append(
        ARRAY_DATA      *this,
        ARRAY_DATA      *other
    );
    
    ERESULT         array_AppendData(
        ARRAY_DATA      *this,
        uint32_t        numElems,
        void            *pData
    );
    
    ERESULT         array_AppendSpacing(
        ARRAY_DATA      *this,
        uint32_t        numElems
    );
    
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
     ERESULT eRc = array__Assign(this,pOther);
     @endcode
     @param     this    ARRAY object pointer
     @param     pOther  a pointer to another ARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         array_Assign(
        ARRAY_DATA      *this,
        ARRAY_DATA      *pOther
    );
    
    
    /*!
     Bottom() returns the first (lowest) entry in the array.
     @param     this    object pointer
     */
    void *          array_Bottom (
        ARRAY_DATA      *this
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
     array      *pCopy = array_Copy(this);
     @endcode
     @param     this    ARRAY object pointer
     @return    If successful, a ARRAY object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the ARRAY object.
     */
    ARRAY_DATA *    array_Copy(
        ARRAY_DATA      *this
    );
    
    
    ERESULT         array_Delete(
        ARRAY_DATA      *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems
    );
    
    
    /*!
     Delete the odd entries in array shifting the elements down that are to
     be kept. After completion, the size is adjusted down and the misc field
     is doubled.  This is meant to be used where the array is  being used to
     index some table or file and the array needs to be compressed on occasion.
     For an example of this, see the sidxe object.
     @param     this    Object Pointer
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         array_DeleteOdd(
        ARRAY_DATA      *this
    );
    
    
    /*!
     Dequeue() removes the last entry from the end of the array.
     @param     this    object pointer
     @param     pData   optional non-null pointer where the entry will
                        be copied to if given
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         array_Dequeue (
        ARRAY_DATA      *this,
        void            *pData
    );


    /*!
     Enqueue() adds the supplied entry to the beginning of the array
     making it the first entry.
     @param     this    object pointer
     @param     pData   non-null pointer to be added
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         array_Enqueue (
        ARRAY_DATA      *this,
        void            *pData
    );


    /*!
     Expand the array to minimum size provided.  Array expansion is done
     by a power of 2 (ie 2, 4, 8, 16, 32, 64, 128, 256, 512, ...). The
     added space is zeroed. The array is expanded, but the usage count
     (ie size) is not affected.
     @param     this    Object Pointer
     @param     min     minimum number of array elements needed
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         array_Expand (
        ARRAY_DATA      *this,
        uint32_t        min
    );
    
    
    /*!
     First() returns the first (lowest) entry in the array.
     @param     this    object pointer
     */
    void *          array_First (
        ARRAY_DATA      *this
    );


    /*!
     Scan the array applying the given routine to each member of the
     array.  Second parameter to the Scan routine is the actual array
     entry address. Halt the scan if an error return code is returned
     by the scan routine.
     @param     this    Object Pointer
     @param     pScan   Scan Routine Address
     @param     pObj    First Parameter for the Scan Routine (optional)
     @param     pArg3   Third Parameter for the Scan Routine (optional)
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         array_ForEach(
        ARRAY_DATA      *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );
    
    
    /*!
     Copy a portion of an array to a given buffer.
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         array_Get(
        ARRAY_DATA      *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems,
        void            *pBuffer            // (out)
    );
    
    
    /*!
     Get the address of an array element.
     @return:   If successful, the address of the array element. Otherwise,
                NULL.
     */
    void *          array_GetAddrOf(
        ARRAY_DATA      *this,
        uint32_t        offset              // in elements (relative to 1)
    );
    
    
    ARRAY_DATA *    array_Init(
        ARRAY_DATA      *this
    );


    /*!
     Inserts the data before the index given.
     @param     this    ARRAY object pointer
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
    */
    ERESULT         array_InsertData(
        ARRAY_DATA      *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems,           // (in)
        void            *pData              // (in)
    );
    
    
    /*!
     Make room for data at the given offset, but don't add data.
     @param     this    ARRAY object pointer
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         array_InsertSpacing(
        ARRAY_DATA      *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems
    );
    
    
    /*!
     Last() returns the last (highest) entry in the array.
     @param     this    object pointer
     */
    void *          array_Last (
        ARRAY_DATA      *this
    );


    /*!
     Pop() removes the last entry from the end of the array.
     @param     this    object pointer
     @param     pData   optional non-null pointer where the entry will
                        be copied to if given
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         array_Pop (
        ARRAY_DATA      *this,
        void            *pData
    );


    /*!
     Push() adds the supplied entry to the end of the array
     making it the last entry.
     @param     this    object pointer
     @param     pData   non-null pointer to be added
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         array_Push (
        ARRAY_DATA      *this,
        void            *pData
    );


    /*!
     Copy the given data to the array and adjust array size if needed.
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         array_Put(
        ARRAY_DATA      *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems,
        void            *pData              // (in)
    );
    
    
    /*!
     Top() returns the last (highest) entry in the array.
     @param     this    object pointer
     */
    void *          array_Top (
        ARRAY_DATA      *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = array_ToDebugString(this,4);
     @endcode 
     @param     this    ARRAY object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     array_ToDebugString(
        ARRAY_DATA      *this,
        int             indent
    );
    
    
    /*!
     Truncate the number of elements in the array to the length given
     if the length < the current size of the array.
     @param     this    ARRAY object pointer
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         array_Truncate(
        ARRAY_DATA      *this,
        uint32_t        len
    );
    
    
    ERESULT         array_Xchg(
        ARRAY_DATA      *this,
        uint32_t        offset1,            // in elements (relative to 1)
        uint32_t        offset2             // in elements (relative to 1)
    );
    
    
    /*!
     Zero the specified data in the array and adjust array size if needed.
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         array_Zero(
        ARRAY_DATA      *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems
    );
    
    
    ERESULT         array_ZeroAll(
        ARRAY_DATA      *this
    );

    
#ifdef	__cplusplus
}
#endif

#endif	/* ARRAY_H */

