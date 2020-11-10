// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          OBJENUM Console Transmit Task (ObjEnum) Header
//****************************************************************
/*
 * Program
 *			Separate ObjEnum (ObjEnum)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate ObjEnum to run things without complications
 *          of interfering with the main ObjEnum. A ObjEnum may be 
 *          called a ObjEnum on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/16/2019 Generated
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


#ifndef         OBJENUM_H
#define         OBJENUM_H


//#define   OBJENUM_JSON_SUPPORT 1
//#define   OBJENUM_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ObjEnum_data_s	OBJENUM_DATA;            // Inherits from OBJ
    typedef struct ObjEnum_class_data_s OBJENUM_CLASS_DATA;   // Inherits from OBJ

    typedef struct ObjEnum_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjEnum_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJENUM_DATA *);
    } OBJENUM_VTBL;

    typedef struct ObjEnum_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjEnum_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJENUM_DATA *);
    } OBJENUM_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  OBJENUM_SINGLETON
    OBJENUM_DATA *  ObjEnum_Shared (
        void
    );

    bool            ObjEnum_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ObjEnum object if successful, otherwise OBJ_NIL.
     */
    OBJENUM_DATA *  ObjEnum_Alloc (
        void
    );
    
    
    OBJ_ID          ObjEnum_Class (
        void
    );
    
    
    OBJENUM_DATA *  ObjEnum_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        ObjEnum_getSize (
        OBJENUM_DATA       *this
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
        ERESULT eRc = ObjEnum_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another OBJENUM object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         ObjEnum_Assign (
        OBJENUM_DATA    *this,
        OBJENUM_DATA    *pOther
    );

   
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        ObjEnum      *pCopy = ObjEnum_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a OBJENUM object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJENUM_DATA *   ObjEnum_Copy (
        OBJENUM_DATA    *this
    );


    OBJENUM_DATA *   ObjEnum_Init (
        OBJENUM_DATA    *this
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
    ERESULT         ObjEnum_LookAhead (
        OBJENUM_DATA    *this,
        uint32_t        offset,
        OBJ_ID          *ppObj
    );
    
    
    /*!
     Return the next arraySize of elements if available in ppVoidArray and set
     NumReturned to the number of elements returned. If the enumerator has gone
     past the end, zero will be returned in NumReturned.
     @param     this        object pointer
     @param     arraySize   size of ppVoidArray
     @param     ppObjArray  an array of void pointers which are filled in by this
                            this method if any elements are left to enumerate.
     @param     pNumReturned    where the number of returned objected pointers is
                                to be put (optional);
     @return    If successful ERESULT_SUCCESS and data returned in ppObjArray
                 with the number of returned elements in pNumReturned, otherwise
                 an ERESULT_* error and 0 in pNumReturned.
     */
    ERESULT         ObjEnum_Next (
        OBJENUM_DATA    *this,
        uint32_t        arraySize,
        OBJ_ID          *ppObjArray,
        uint32_t        *pNumReturned
    );
    
    
    /*!
     Return the remaining number of items left to be enumerated.
     @param     this    object pointer
     @return    The number of items left to be enumerated
     */
    uint32_t        ObjEnum_Remaining (
        OBJENUM_DATA    *this
    );
    
    
    /*!
     Reset the enumerator to the beginning of the enumeration.
     @param     this    OBJENUM object pointer
     @return    If successful ERESULT_SUCCESS, otherwise an ERESULT_* error.
     */
    ERESULT         ObjEnum_Reset (
        OBJENUM_DATA    *this
    );
    
    
    /*!
     Return the next numSkip of elements in the enumeration. Skipping might put
     the enumerator past the end of the enumeration.
     @param     this    OBJENUM object pointer
     @param     numSkip number of elements to skip
     @return    If successful ERESULT_SUCCESS, otherwise an ERESULT_* error.
     */
    ERESULT         ObjEnum_Skip (
        OBJENUM_DATA    *this,
        uint32_t        numSkip
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjEnum_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    ObjEnum_ToDebugString (
        OBJENUM_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJENUM_H */

