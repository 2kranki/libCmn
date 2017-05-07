// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODEMATRIX Console Transmit Task (nodeMatrix) Header
//****************************************************************
/*
 * Program
 *			Separate nodeMatrix (nodeMatrix)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate nodeMatrix to run things without complications
 *          of interfering with the main nodeMatrix. A nodeMatrix may be 
 *          called a nodeMatrix on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal nodeMatrix. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	08/31/2016 Generated
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
#include        <node.h>


#ifndef         NODEMATRIX_H
#define         NODEMATRIX_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // NODEMATRIX_DATA is defined in node.h

    typedef struct nodeMatrix_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeMatrix_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEMATRIX_DATA *);
    } NODEMATRIX_VTBL;



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
     @return:   pointer to nodeMatrix object if successful, otherwise OBJ_NIL.
     */
    NODEMATRIX_DATA * nodeMatrix_Alloc(
    );
    
    
    NODEMATRIX_DATA * nodeMatrix_New(
        uint32_t        n,
        uint32_t        m
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        nodeMatrix_getX(
        NODEMATRIX_DATA *this
    );
    
    
    uint32_t        nodeMatrix_getY(
        NODEMATRIX_DATA *this
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
     ERESULT    eRc = nodeMatrix__Assign(this,pOther);
     @endcode:
     @param:    this    NODEMATRIX_DATA object pointer
     @param:    pOther  a pointer to another NODEMATRIX_DATA object
     @return:   If successful, ERESULT_SUCCESS otherwise an
     ERESULT_* error
     */
    ERESULT         nodeMatrix_Assign(
        NODEMATRIX_DATA	*this,
        NODEMATRIX_DATA	*pOther
    );
    
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
     NODEMATRIX_DATA    *pCopy = nodeMatrix_Copy(this);
     @endcode:
     @param:    this    NODEMATRIX_DATA object pointer
     @return:   If successful, an NODEMATRIX_DATA object which must be released,
     otherwise OBJ_NIL.
     @warning: Remember to release the returned the OBJMATRIX_DATA object.
     */
    NODEMATRIX_DATA * nodeMatrix_Copy(
        NODEMATRIX_DATA	*this
    );
    
    
    NODE_DATA * nodeMatrix_Get(
        NODEMATRIX_DATA	*this,
        uint32_t        x,
        uint32_t        y
    );
    
    
    NODEMATRIX_DATA * nodeMatrix_Init(
        NODEMATRIX_DATA *this,
        uint32_t        n,
        uint32_t        m
    );


    ERESULT     nodeMatrix_Set(
        NODEMATRIX_DATA	*this,
        uint32_t        x,
        uint32_t        y,
        NODE_DATA       *pValue
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = nodeMatrix_ToDebugString(pObject,4);
     @endcode:
     @param:    this    NODEMATRIX_DATA object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    nodeMatrix_ToDebugString(
        NODEMATRIX_DATA *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEMATRIX_H */

