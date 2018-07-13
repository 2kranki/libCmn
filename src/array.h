// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          ARRAY Console Transmit Task (array) Header
//****************************************************************
/*
 * Program
 *			Separate array (array)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate array to run things without complications
 *          of interfering with the main array. A array may be 
 *          called a array on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/08/2017 Generated
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
        uint16_t        elemSize        // Element Size in bytes
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint8_t *        array_getData(
        ARRAY_DATA     *this
    );
    
    
    uint16_t        array_getElemSize(
        ARRAY_DATA      *this
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
    ARRAY_DATA *     array_Copy(
        ARRAY_DATA       *this
    );
    
    
    ERESULT         array_Delete(
        ARRAY_DATA      *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems
    );
    
    
    /*!
     Expand the array to minimum size provided.  Array expansion is done
     by a power of 2 (ie 2, 4, 8, 16, 32, 64, 128, 256, 512, ...).
     @param     this    Array Object Pointer
     @param     min     minimum number of array elements needed
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
     error.
     */
    ERESULT         array_Expand(
        ARRAY_DATA      *this,
        uint32_t        min
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
     Make room for data, but don't add data.
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
    
    
    ERESULT         array_Truncate(
        ARRAY_DATA      *this,
        uint32_t        len
    );
    
    
    /*!
     Zeroes the data in the array and adjust array size if needed.
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
     error.
     */
    ERESULT         array_Zero(
        ARRAY_DATA      *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* ARRAY_H */

