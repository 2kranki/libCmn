// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Array of Methods and Objects (execArray) Header
//****************************************************************
/*
 * Program
 *			Array of Methods and Objects (execArray)
 * Purpose
 *			This object provides an array of methods and objects that
 *          can be all be executed at once. The method/object combination
 *          can be added multiple times. So, this could be used for
 *          instance to release objects in an Obj-C autorelease type
 *          system.
 *
 * Remarks
 *
 * History
 *	10/02/2015 Generated
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


#ifndef         EXECARRAY_H
#define         EXECARRAY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct execArray_data_s	EXECARRAY_DATA;

    typedef struct execArray_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in execArray_object.c.
    } EXECARRAY_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the execArray including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    EXECARRAY_DATA * execArray_Alloc(
    );
    
    
    EXECARRAY_DATA * execArray_New(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add a method/object pair to the array.
     @return:       ERESULT_SUCCESS
     */
    ERESULT         execArray_AddMethod(
        EXECARRAY_DATA	*this,
        P_VOIDEXIT1_PTR pMethod,
        OBJ_ID          pObject         // May be OBJ_NIL
    );


    /*!
     Execute all the methods/objects in the array.
     @return:       ERESULT_SUCCESS
     */
    ERESULT         execArray_Execute(
        EXECARRAY_DATA  *this
    );


    EXECARRAY_DATA * execArray_Init(
        EXECARRAY_DATA  *this
    );


    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     execArray_ToDebugString(
        EXECARRAY_DATA  *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* EXECARRAY_H */

