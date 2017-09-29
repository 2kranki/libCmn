// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Power of 2 Element Size Array (pwr2Array) Header
//****************************************************************
/*
 * Program
 *			Power of 2 Element Size Array (pwr2Array)
 * Purpose
 *			This object provides an array in which the size of the
 *          elements is a power of 2. Up to 2 ** 19 (512k) is sup-
 *          ported. The maximum array size is currently 2 GB.
 *
 * Remarks
 *	1.      All indices or offsets are relative to one and are in
 *          number of elements not bytes.
 *
 * History
 *	08/25/2015 Generated
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


#ifndef         PWR2ARRAY_H
#define         PWR2ARRAY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct pwr2Array_data_s	PWR2ARRAY_DATA;

    typedef struct pwr2Array_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in table_object.c.
    } PWR2ARRAY_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    PWR2ARRAY_DATA * pwr2Array_Alloc(
        void
    );
    
    
    PWR2ARRAY_DATA * pwr2Array_New(
        uint16_t        powerOf2    // Element Size as a Power of 2
    //                              // 0 == 1 byte, 1 == 2, 2 == 4, ...
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    void *          pwr2Array_getData(
        PWR2ARRAY_DATA  *this
    );
    
    
    bool            pwr2Array_getDontZero(
        PWR2ARRAY_DATA   *this
    );
    
    bool            pwr2Array_setDontZero(
        PWR2ARRAY_DATA  *this,
        bool            value
    );
    
    
    ERESULT         pwr2Array_getLastError(
        PWR2ARRAY_DATA  *this
    );
    
    
    uint32_t        pwr2Array_getMax(
        PWR2ARRAY_DATA  *this
    );

    
    uint32_t        pwr2Array_getSize(
        PWR2ARRAY_DATA  *this
    );
    
    bool            pwr2Array_setSize(
        PWR2ARRAY_DATA  *this,
        uint32_t        value
    );
    
    
    uint32_t        pwr2Array_getSizeInBytes(
        PWR2ARRAY_DATA  *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    // Adjust array size up or down as long as it stays less than
    // the max array size (ie this will not expand the array).
    bool            pwr2Array_AdjustSize(
        PWR2ARRAY_DATA  *this,
        int32_t         value
    );
    
    
    ERESULT         pwr2Array_Append(
        PWR2ARRAY_DATA  *this,
        PWR2ARRAY_DATA  *other
    );
    
    ERESULT         pwr2Array_AppendData(
        PWR2ARRAY_DATA  *this,
        uint32_t        numElems,
        void            *pData
    );
    
    ERESULT         pwr2Array_AppendSpacing(
        PWR2ARRAY_DATA  *this,
        uint32_t        numElems
    );
    
    
    // Assign cbp to pOther.
    ERESULT         pwr2Array_Assign(
        PWR2ARRAY_DATA  *this,
        PWR2ARRAY_DATA  *pOther
    );
    
    
    PWR2ARRAY_DATA * pwr2Array_Copy(
        PWR2ARRAY_DATA  *this
    );
    
    
    ERESULT         pwr2Array_Delete(
        PWR2ARRAY_DATA  *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems
    );
    
    
    uint32_t        pwr2Array_ElemSize(
        PWR2ARRAY_DATA  *this
    );
    
    
    /*!
     Copy a portion of an array to a given buffer.
     @return:   If successful, an AStr object which must be released,
     otherwise OBJ_NIL.
     */
    ERESULT         pwr2Array_Get(
        PWR2ARRAY_DATA  *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems,
        void            *pBuffer            // (out)
    );
    
    
    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    PWR2ARRAY_DATA * pwr2Array_Init(
        PWR2ARRAY_DATA  *this,
        uint16_t        powerOf2    // Element Size as a Power of 2
    //                              // 0 == 1 byte, 1 == 2, 2 == 4, ...
    );


    // Inserts the data before the index given.
    ERESULT         pwr2Array_InsertData(
        PWR2ARRAY_DATA  *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems,
        void            *pData              // (in)
    );
    
    
    // Make room for data, but don't add data.
    ERESULT         pwr2Array_InsertSpacing(
        PWR2ARRAY_DATA  *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = pwr2Array_ToDebugString(pObj,4);
     @endcode:
     @param:    this    object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     pwr2Array_ToDebugString(
        PWR2ARRAY_DATA  *this,
        int             indent
    );
    
    
    ERESULT         pwr2Array_Truncate(
        PWR2ARRAY_DATA	*this,
        uint32_t        len
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* PWR2ARRAY_H */

