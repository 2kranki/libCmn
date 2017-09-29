// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          B-Plus Tree (bptree) Header
//****************************************************************
/*
 * Program
 *			B-Plus Tree (bptree)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate bptree to run things without complications
 *          of interfering with the main bptree. A bptree may be 
 *          called a bptree on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal bptree. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	03/05/2017 Generated
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


#ifndef         BPTREE_H
#define         BPTREE_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct bptree_data_s	BPTREE_DATA;    // Inherits from OBJ.

    typedef struct bptree_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in bptree_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPTREE_DATA *);
    } BPTREE_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    BPTREE_DATA *   bptree_Alloc(
        void
    );
    
    
    BPTREE_DATA *   bptree_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         bptree_getLastError(
        BPTREE_DATA     *this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     bptree_Disable(
        BPTREE_DATA		*this
    );


    ERESULT     bptree_Enable(
        BPTREE_DATA		*this
    );

   
    BPTREE_DATA *   bptree_Init(
        BPTREE_DATA     *this
    );


    ERESULT     bptree_IsEnabled(
        BPTREE_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = bptree_ToDebugString(this,4);
     @endcode:
     @param:    this    BPTREE object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    bptree_ToDebugString(
        BPTREE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BPTREE_H */

