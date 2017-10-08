// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Executable Function Pointer (execPtr) Header
//****************************************************************
/*
 * Program
 *			Executable Function Pointer (execPtr)
 * Purpose
 *			This object provides a way of wrapping a function pointer
 *          into an object which can then be passed around in other
 *          objects.  Since nothing is really known of the function
 *          pointer, it can not be saved in a JSON string for instance.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	10/07/2017 Generated
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


#ifndef         EXECPTR_H
#define         EXECPTR_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct execPtr_data_s	EXECPTR_DATA;    // Inherits from OBJ.

    typedef struct execPtr_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in execPtr_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(EXECPTR_DATA *);
    } EXECPTR_VTBL;



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
     @return    pointer to execPtr object if successful, otherwise OBJ_NIL.
     */
    EXECPTR_DATA *     execPtr_Alloc(
        void
    );
    
    
    EXECPTR_DATA *     execPtr_New(
        void            *pFunc
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     Description Property - can be used for any documentation purposes
     needed
     */
    ASTR_DATA * execPtr_getDesc(
        EXECPTR_DATA *this
    );
    
    bool        execPtr_setDesc(
        EXECPTR_DATA *this,
        ASTR_DATA   *pValue
    );
    

    void *      execPtr_getFunc(
        EXECPTR_DATA *this
    );
    
    
    ERESULT     execPtr_getLastError(
        EXECPTR_DATA *this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     execPtr_Disable(
        EXECPTR_DATA *this
    );


    ERESULT     execPtr_Enable(
        EXECPTR_DATA *this
    );

   
    EXECPTR_DATA *  execPtr_Init(
        EXECPTR_DATA    *this,
        void            *pFunc
    );


    ERESULT         execPtr_IsEnabled(
        EXECPTR_DATA    *this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = execPtr_ToDebugString(this,4);
     @endcode 
     @param     this    EXECPTR object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     execPtr_ToDebugString(
        EXECPTR_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* EXECPTR_H */

