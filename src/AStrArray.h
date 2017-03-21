// vi:nu:et:sts=4 ts=4 sw=4 tw=90

//****************************************************************
//          ARRAY Console Transmit Task (AStrArray) Header
//****************************************************************
/*
 * Program
 *				Separate AStrArray (AStrArray)
 * Purpose
 *				This object provides a standardized way of handling
 *              a separate AStrArray to run things without complications
 *              of interfering with the main AStrArray. A AStrArray may be 
 *              called a AStrArray on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal AStrArray. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	Copied from NodeArray 09/25/2015
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


#ifndef         ASTRARRAY_H
#define         ASTRARRAY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // ASTRARRAY_DATA is defined in "str.h"

    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    ASTRARRAY_DATA * AStrArray_Alloc(
    );
    
    
    ASTRARRAY_DATA * AStrArray_New(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        AStrArray_getSize(
        ASTRARRAY_DATA	*cbp
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         AStrArray_AppendStr(
        ASTRARRAY_DATA	*cbp,
        ASTR_DATA       *pObject,
        uint32_t        *pIndex
    );
    
    
    // DeleteFromBottom() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    ASTR_DATA *     AStrArray_DeleteFirst(
        ASTRARRAY_DATA	*cbp
    );
    
    
    // DeleteFromTop() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    ASTR_DATA *     AStrArray_DeleteLast(
        ASTRARRAY_DATA	*cbp
    );
    
    
    ASTR_DATA *     AStrArray_Get(
        ASTRARRAY_DATA	*cbp,
        uint32_t        index       // Relative to 1
    );
    
    ASTR_DATA *     AStrArray_GetFirst(
        ASTRARRAY_DATA  *cbp
    );
    
    ASTR_DATA *     AStrArray_GetLast(
        ASTRARRAY_DATA	*cbp
    );
    
    
    ASTRARRAY_DATA * AStrArray_Init(
        ASTRARRAY_DATA  *cbp
    );


    ERESULT         AStrArray_InsertStr(
        ASTRARRAY_DATA	*cbp,
        uint32_t        index,
        ASTR_DATA       *pObject
    );
    
    
    ERESULT         AStrArray_SortAscending(
        ASTRARRAY_DATA	*cbp
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* ASTRARRAY_H */

