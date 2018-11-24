// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODEENUM Console Transmit Task (nodeEnum) Header
//****************************************************************
/*
 * Program
 *			Separate nodeEnum (nodeEnum)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate nodeEnum to run things without complications
 *          of interfering with the main nodeEnum. A nodeEnum may be 
 *          called a nodeEnum on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/23/2018 Generated
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


#ifndef         NODEENUM_H
#define         NODEENUM_H


//#define   NODEENUM_SINGLETON    1

#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct nodeEnum_data_s	NODEENUM_DATA;            // Inherits from OBJ
    typedef struct nodeEnum_class_data_s NODEENUM_CLASS_DATA;   // Inherits from OBJ

    typedef struct nodeEnum_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeEnum_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEENUM_DATA *);
    } NODEENUM_VTBL;

    typedef struct nodeEnum_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeEnum_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEENUM_DATA *);
    } NODEENUM_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEENUM_SINGLETON
    NODEENUM_DATA *     nodeEnum_Shared(
        void
    );

    bool            nodeEnum_SharedReset(
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to nodeEnum object if successful, otherwise OBJ_NIL.
     */
    NODEENUM_DATA * nodeEnum_Alloc(
        void
    );
    
    
    OBJ_ID          nodeEnum_Class(
        void
    );
    
    
    NODEENUM_DATA * nodeEnum_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        nodeEnum_getSize(
        NODEENUM_DATA   *this
    );
    
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    NODEENUM_DATA *   nodeEnum_Init(
        NODEENUM_DATA     *this
    );


    /*!
     Return the elements at the specified offset from the current item. An offset
     of 0 returns the current item. Do not alter which item is the current one.
     If the offset is beyond the range of items, then ERESULT_OUT_OF_RANGE is
     returned.
     @param     this    object pointer
     @param     offset  offset of object to return (relative to zero)
     @param     ppObj   where the object address should be returned
     @return    If successful ERESULT_SUCCESS and data returned in ppVoid,
     otherwise an ERESULT_* error.
     */
    ERESULT         nodeEnum_LookAhead(
        NODEENUM_DATA   *this,
        uint32_t        offset,
        OBJ_ID          *ppObj
    );
    
    
    /*!
     Return the next arraySize of elements if available in ppVoidArray and set
     NumReturned to the number of elements returned. If the enumerator has gone
     past the end, zero will be returned in NumReturned.
     @param     this    OBJENUM object pointer
     @param     arraySize size of ppVoidArray
     @param     ppObjArray      an array of void pointers which are filled in by this
     this method if any elements are left to enumerate.
     @param     pNumReturned    where the number of returned objected pointers is
     to be put (optional);
     @return    If successful ERESULT_SUCCESS and data returned in ppObjArray
     with the number of returned elements in pNumReturned, otherwise
     an ERESULT_* error and 0 in pNumReturned.
     */
    ERESULT         nodeEnum_Next(
        NODEENUM_DATA   *this,
        uint32_t        arraySize,
        OBJ_ID          *ppObjArray,
        uint32_t        *pNumReturned
    );
    
    
    /*!
     Return the remaining number of items left to be enumerated.
     @param     this    OBJENUM object pointer
     @return    The number of items left to be enumerated
     */
    uint32_t        nodeEnum_Remaining(
        NODEENUM_DATA   *this
    );
    
    
    /*!
     Reset the enumerator to the beginning of the enumeration.
     @param     this    OBJENUM object pointer
     @return    If successful ERESULT_SUCCESS, otherwise an ERESULT_* error.
     */
    ERESULT         nodeEnum_Reset(
        NODEENUM_DATA   *this
    );
    
    
    /*!
     Return the next numSkip of elements in the enumeration. Skipping might put
     the enumerator past the end of the enumeration.
     @param     this    OBJENUM object pointer
     @param     numSkip number of elements to skip
     @return    If successful ERESULT_SUCCESS, otherwise an ERESULT_* error.
     */
    ERESULT         nodeEnum_Skip(
        NODEENUM_DATA   *this,
        uint32_t        numSkip
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = nodeEnum_ToDebugString(this,4);
     @endcode 
     @param     this    NODEENUM object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     nodeEnum_ToDebugString(
        NODEENUM_DATA   *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEENUM_H */

