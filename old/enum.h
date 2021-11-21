// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Enumerator Base Class (enum) Header
//****************************************************************
/*
 * Program
 *			Enumerator Base Class (enum)
 * Purpose
 *			This object provides a standardized enumerator based
 *          how enumeration is handled in COM/OLE2.
 *
 * Remarks
 *	1.      Objects, Enum and objEnum, must be kept synchronized
 *          in their interfaces.
 *
 * History
 *	06/30/2017 Generated
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


#ifndef         ENUM_H
#define         ENUM_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct enum_data_s	ENUM_DATA;    // Inherits from OBJ.

    typedef struct enum_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in enum_object.c.
        // Properties:
        // Methods:
        ERESULT         (*pNext)(ENUM_DATA *, uint32_t, void **, uint32_t *);
        ERESULT         (*pSkip)(ENUM_DATA *, uint32_t);
        ERESULT         (*pReset)(ENUM_DATA *);
        ERESULT         (*pLookAhead)(ENUM_DATA *, uint32_t, OBJ_ID *);
        uint32_t        (*pRemaining)(ENUM_DATA *);
    } ENUM_VTBL;



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
     @return:   pointer to enum object if successful, otherwise OBJ_NIL.
     */
    ENUM_DATA *     enum_Alloc(
        void
    );
    
    
    ENUM_DATA *     enum_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     enum_getLastError(
        ENUM_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ENUM_DATA *   enum_Init(
        ENUM_DATA     *this
    );


    /*!
     Return the elements at the specified offset from the current item. An offset
     of 0 returns the current item. Do not alter which item is the current one.
     If the offset is beyond the range of items, then ERESULT_OUT_OF_RANGE is
     returned.
     @param     this    ENUM object pointer
     @param     offset  offset of object to return (relative to zero)
     @param     ppVoid  where the object address should be returned
     @return    If successful ERESULT_SUCCESS and data returned in ppVoid,
                 otherwise an ERESULT_* error.
     */
    ERESULT         enum_LookAhead(
        ENUM_DATA       *this,
        uint32_t        offset,
        void            **ppVoid
    );
    
    
    /*!
     Return the next arraySize of elements if available in ppVoidArray and set 
     NumReturned to the number of elements returned. If the enumerator has gone 
     past the end, zero will be returned in NumReturned.
     @param     this    ENUM object pointer
     @param     arraySize size of ppVoidArray
     @param     ppVoidArray an array of void pointers which are filled in by this
                        this method if any elements are left to enumerate.
     @return    If successful ERESULT_SUCCESS and data returned in ppVoidArray
                with the number of returned elements in pNumReturned, otherwise
                an ERESULT_* error and 0 in NumReturned.
     */
    ERESULT         enum_Next(
        ENUM_DATA       *this,
        uint32_t        arraySize,
        void            **ppVoidArray,
        uint32_t        *pNumReturned
    );
    
    
    /*!
     Return the remaining number of items left to be enumerated.
     @param     this    ENUM object pointer
     @return    The number of items left to be enumerated
     */
    uint32_t        enum_Remaining(
        ENUM_DATA       *this
    );
    
    
    /*!
     Reset the enumerator to the beginning of the enumeration.
     @param     this    ENUM object pointer
     @return    If successful ERESULT_SUCCESS, otherwise an ERESULT_* error.
     */
    ERESULT         enum_Reset(
        ENUM_DATA       *this
    );
    
    
    /*!
     Return the next numSkip of elements in the enumeration. Skipping might put
     the enumerator past the end of the enumeration.
     @param     this    ENUM object pointer
     @param     numSkip number of elements to skip
     @return    If successful ERESULT_SUCCESS, otherwise an ERESULT_* error.
     */
    ERESULT         enum_Skip(
        ENUM_DATA       *this,
        uint32_t        numSkip
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = enum_ToDebugString(this,4);
     @endcode
     @param     this    ENUM object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     enum_ToDebugString(
        ENUM_DATA       *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* ENUM_H */

