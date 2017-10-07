// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          U12ARRAY Console Transmit Task (u12Array) Header
//****************************************************************
/*
 * Program
 *			Separate u12Array (u12Array)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate u12Array to run things without complications
 *          of interfering with the main u12Array. A u12Array may be 
 *          called a u12Array on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal u12Array. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	10/08/2016 Generated
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


#ifndef         U12ARRAY_H
#define         U12ARRAY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct u12Array_data_s	U12ARRAY_DATA;    // Inherits from OBJ.

    typedef struct u12Array_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in u12Array_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(U12ARRAY_DATA *);
    } U12ARRAY_VTBL;



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
     @return:   pointer to u12Array object if successful, otherwise OBJ_NIL.
     */
    U12ARRAY_DATA *     u12Array_Alloc(
        void
    );
    
    
    U12ARRAY_DATA *     u12Array_New(
        void
    );
    
    
    U12ARRAY_DATA *     u12Array_NewFromData(
        uint32_t            cBuffer,
        uint8_t             *pBuffer
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     u12Array_getLastError(
        U12ARRAY_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
     ERESULT eRc = u12Array__Assign(this,pOther);
     @endcode
     @param     this    U12ARRAY object pointer
     @param     pOther  a pointer to another U12ARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an
                 ERESULT_* error
     */
    ERESULT         u12Array_Assign(
        U12ARRAY_DATA   *this,
        U12ARRAY_DATA   *pOther
    );
    
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
     u12Array      *pCopy = u12Array_Copy(this);
     @endcode
     @param     this    U12ARRAY object pointer
     @return    If successful, a U12ARRAY object which must be released,
                 otherwise OBJ_NIL.
     @warning   Remember to release the returned the U12ARRAY object.
     */
    U12ARRAY_DATA * u12Array_Copy(
        U12ARRAY_DATA   *this
    );
    
    
    /*!
     Find the first value in the array.
     @param     this    object pointer
     @param     value   value to search for
     @return    If successful, the position, otherwise 0xFFFF
     */
    uint16_t        u12Array_Find(
        U12ARRAY_DATA   *this,
        uint16_t        value
    );
    
    
    /*!
     Get the data from the array at the specified location.
     @param     this    object pointer
     @param     index   index into the array (relative to 1)
     @param     data    data to be put into the array
     @return    If successful, the data, otherwise 0xFFFF
     */
    uint16_t        u12Array_Get(
        U12ARRAY_DATA	*this,
        uint32_t        index
    );
    
    
    U12ARRAY_DATA * u12Array_Init(
        U12ARRAY_DATA   *this
    );


    /*!
     Put the given data into the array at the specified location.
     if the array needs to be expanded, '\0' are added as fill.
     @param     this    object pointer
     @param     index   index into the array (relative to 1)
     @param     data    data to be put into the array
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         u12Array_Put(
        U12ARRAY_DATA   *this,
        const
        uint32_t        index,
        const
        uint16_t        data
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = u12Array_ToDebugString(this,4);
     @endcode
     @param     this    U12ARRAY object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     u12Array_ToDebugString(
        U12ARRAY_DATA   *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* U12ARRAY_H */

