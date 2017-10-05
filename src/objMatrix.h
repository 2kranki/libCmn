// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          OBJMATRIX Console Transmit Task (objMatrix) Header
//****************************************************************
/*
 * Program
 *			Separate objMatrix (objMatrix)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate objMatrix to run things without complications
 *          of interfering with the main objMatrix. A objMatrix may be 
 *          called a objMatrix on other O/S's.
 *
 * Remarks
 *	1.      The matrix size can not exceed (UINT32_MAX - 1)
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal objMatrix. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	10/07/2015 Generated
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


#ifndef         OBJMATRIX_H
#define         OBJMATRIX_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct objMatrix_data_s	OBJMATRIX_DATA;

    typedef struct objMatrix_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fatFCB_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CB_DATA *);
    } OBJMATRIX_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    OBJMATRIX_DATA * objMatrix_Alloc(
        void
    );
    
    
    OBJMATRIX_DATA * objMatrix_New(
        uint32_t        x,
        uint32_t        y
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        objMatrix_getX(
        OBJMATRIX_DATA  *this
    );
    
    
    uint32_t        objMatrix_getY(
        OBJMATRIX_DATA  *this
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
     ERESULT    eRc = objMatrix__Assign(this,pOther);
     @endcode:
     @param:    this    OBJMATRIX_DATA object pointer
     @param:    pOther  a pointer to another OBJMATRIX_DATA object
     @return:   If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         objMatrix_Assign(
        OBJMATRIX_DATA	*this,
        OBJMATRIX_DATA	*pOther
    );
    
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
     OBJMATRIX_DATA      *pCopy = objMatrix_Copy(this);
     @endcode:
     @param:    this    OBJMATRIX_DATA object pointer
     @return:   If successful, an OBJMATRIX_DATA object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the OBJMATRIX_DATA object.
     */
    OBJMATRIX_DATA * objMatrix_Copy(
        OBJMATRIX_DATA	*this
    );
    
    
    OBJ_ID          objMatrix_Get(
        OBJMATRIX_DATA	*this,
        uint32_t        x,
        uint32_t        y
    );
    
    
    OBJMATRIX_DATA * objMatrix_Init(
        OBJMATRIX_DATA  *this,
        uint32_t        x,
        uint32_t        y
    );


    ERESULT         objMatrix_Set(
        OBJMATRIX_DATA	*this,
        uint32_t        x,
        uint32_t        y,
        OBJ_ID          value
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = objMatrix_ToDebugString(this,4);
     @endcode:
     @param:    this    OBJMATRIX_DATA object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     objMatrix_ToDebugString(
        OBJMATRIX_DATA  *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJMATRIX_H */

