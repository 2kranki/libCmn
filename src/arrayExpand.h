// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Expandable Array (arrayExpand) Header
//****************************************************************
/*
 * Program
 *			Expandable Array (arrayExpand)
 * Purpose
 *			This object provides an Expandable Array with a defined
 *          element size. Internally, the array is expanded as needed
 *          in multiples of two unless overriden.
 *
 * Remarks
 *	1.      The actual array will change as new elements are requested.
 *          So, you must be careful in not retaining ptrs within the
 *          array itself.
 *
 * History
 *	10/07/2016 Generated
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


#ifndef         ARRAYEXPAND_H
#define         ARRAYEXPAND_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct arrayExpand_data_s	ARRAYEXPAND_DATA;    // Inherits from OBJ.

    typedef struct arrayExpand_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in arrayExpand_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ARRAYEXPAND_DATA *);
    } ARRAYEXPAND_VTBL;



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
     @return:   pointer to arrayExpand object if successful, otherwise OBJ_NIL.
     */
    ARRAYEXPAND_DATA * arrayExpand_Alloc(
    );
    
    
    ARRAYEXPAND_DATA * arrayExpand_New(
        uint16_t        elemSize        // Element Size in bytes
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    void *          arrayExpand_getData(
        ARRAYEXPAND_DATA *this
    );
    
    
    uint32_t        arrayExpand_getElemSize(
        ARRAYEXPAND_DATA *this
    );
    
    
    ERESULT         arrayExpand_getLastError(
        ARRAYEXPAND_DATA *this
    );


    uint32_t        arrayExpand_getSize(
        ARRAYEXPAND_DATA *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code:
     ERESULT eRc = arrayExpand__Assign(this,pOther);
     @endcode:
     @param:    this    ARRAYEXPAND object pointer
     @param:    pOther  a pointer to another ARRAYEXPAND object
     @return:   If successful, ERESULT_SUCCESS otherwise an
     ERESULT_* error
     */
    ERESULT         arrayExpand_Assign(
        ARRAYEXPAND_DATA *this,
        ARRAYEXPAND_DATA *pOther
    );
    
    ERESULT         arrayExpand_AssignData(
        ARRAYEXPAND_DATA *this,
        uint16_t        elemSize,
        uint32_t        size,
        const
        void            *pBuffer
    );
    
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
     arrayExpand      *pCopy = arrayExpand_Copy(this);
     @endcode:
     @param:    this    ARRAYEXPAND object pointer
     @return:   If successful, a ARRAYEXPAND object which must be released,
     otherwise OBJ_NIL.
     @warning: Remember to release the returned the ARRAYEXPAND object.
     */
    ARRAYEXPAND_DATA * arrayExpand_Copy(
        ARRAYEXPAND_DATA *this
    );
    
    
    /*!
     Return a pointer to the array entry for the indexed item increasing the
     size of the array if needed.
     Example:
     @code:
            void *pData = arrayExpand_Elem(this,1); // First Entry
     @endcode:
     @param:    this    ARRAYEXPAND object pointer
     @param:    index   index of array element relative to 1
     @return:   If successful, a pointer to the array element, otherwise NULL.
     */
    void *          arrayExpand_Elem(
        ARRAYEXPAND_DATA *this,
        uint32_t        index               // (relative to 1)
    );

   
    ERESULT         arrayExpand_ExpandTo(
        ARRAYEXPAND_DATA *this,
        uint32_t        size                // (relative to 1)
    );
    
    
    ERESULT         arrayExpand_Get(
        ARRAYEXPAND_DATA *this,
        uint32_t        index,              // (relative to 1)
        uint32_t        cBuffer,
        void            *pBuffer
    );
    
    
    ARRAYEXPAND_DATA * arrayExpand_Init(
        ARRAYEXPAND_DATA *this,
        uint16_t        elemSize        // Element Size in bytes
    );


    ERESULT         arrayExpand_Set(
        ARRAYEXPAND_DATA *this,
        uint32_t        size,               // (relative to 1)
        uint32_t        cBuffer,
        const
        void            *pBuffer
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = arrayExpand_ToDebugString(this,4);
     @endcode:
     @param:    this    ARRAYEXPAND object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    arrayExpand_ToDebugString(
        ARRAYEXPAND_DATA *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* ARRAYEXPAND_H */

