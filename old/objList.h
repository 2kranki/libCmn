// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              List of Objects (objList) Header
//****************************************************************
/*
 * Program
 *			A List of Objects (objList)
 * Purpose
 *			This object provides a list of objects which provides
 *          for fast addition and deletion of objects.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	09/14/2016 Generated
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
#include        <objArray.h>
#include        <objEnum.h>


#ifndef         OBJLIST_H
#define         OBJLIST_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct objList_data_s	OBJLIST_DATA;    // Inherits from OBJ.

    typedef struct objList_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in objList_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJLIST_DATA *);
    } OBJLIST_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    OBJLIST_DATA *  objList_Alloc (
        void
    );
    
    
    OBJLIST_DATA *  objList_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     Ordered property causes the list to be sorted according to the
     vtbl compare routine.  For Ordered to work properly all objects
     in the list should be of the same type.
     */
    bool            objList_getOrdered (
        OBJLIST_DATA    *this
    );
    
    bool            objList_setOrdered (
        OBJLIST_DATA    *this,
        bool            fValue
    );
    

    /*!
     Size property is the numbers of objects on the list.
     */
    uint32_t        objList_getSize (
        OBJLIST_DATA   *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         objList_Add2Head (
        OBJLIST_DATA    *this,
        OBJ_ID          pObject
    );
    
    
    ERESULT         objList_Add2Tail (
        OBJLIST_DATA    *this,
        OBJ_ID          pObject
    );
    
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
     ERESULT eRc = objList__Assign(this,pOther);
     @endcode
     @param     this    OBJLIST object pointer
     @param     pOther  a pointer to another OBJLIST object
     @return    If successful, ERESULT_SUCCESS otherwise an
     ERESULT_* error
     */
    ERESULT         objList_Assign (
        OBJLIST_DATA    *this,
        OBJLIST_DATA    *pOther
    );
    
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
     objList      *pCopy = objList_Copy(this);
     @endcode
     @param     this    OBJLIST object pointer
     @return    If successful, a OBJLIST object which must be released,
     otherwise OBJ_NIL.
     @warning   Remember to release the returned the OBJLIST object.
     */
    OBJLIST_DATA *     objList_Copy (
        OBJLIST_DATA       *this
    );
    
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
     objList      *pCopy = objList_DeepCopy(this);
     @endcode
     @param     this    OBJLIST object pointer
     @return    If successful, a OBJLIST object which must be released,
     otherwise OBJ_NIL.
     @warning   Remember to release the returned the OBJLIST object.
     */
    OBJLIST_DATA *  objList_DeepCopy (
        OBJLIST_DATA    *this
    );
    
    
    ERESULT         objList_DeleteHead (
        OBJLIST_DATA	*this
    );
    
    ERESULT         objList_DeleteIndex (
        OBJLIST_DATA    *this,
        uint32_t        index
    );
    
    ERESULT         objList_DeleteTail (
        OBJLIST_DATA	*this
    );
    
    
    /*! Create an enumerator for the list.
     @return    If successful, an ENUM object is returned.  Otherwise,
     OBJ_NIL.
     @warning   Remember to release the returned ENUM object.
     */
    OBJENUM_DATA *  objList_Enum (
        OBJLIST_DATA    *this
    );
    
    
    ERESULT         objList_ForEach (
        OBJLIST_DATA    *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObject,        // Used as first parameter of scan method
        //                              // Second Argument is current list element
        void            *pArg3          // Third Argument of Scan
    );
    
    
    OBJ_ID          objList_Head (
        OBJLIST_DATA    *this
    );

   
    OBJ_ID          objList_Index (
        OBJLIST_DATA    *this,
        int32_t			index					// (relative to 1)
    );
    
    
    OBJLIST_DATA *   objList_Init (
        OBJLIST_DATA    *this
    );


    OBJ_ID          objList_Next (
        OBJLIST_DATA    *this
    );
    
    
    OBJARRAY_DATA *  objList_Objects (
        OBJLIST_DATA    *this
    );
    
    
    OBJ_ID          objList_Prev (
        OBJLIST_DATA    *this
    );
    
    
    /*! Shift the tail to the head and returns the new head.
     @return    If successful, the current head bject is returned.
                Otherwise, OBJ_NIL.
     */
    OBJ_ID          objList_ShiftHead (
        OBJLIST_DATA    *this
    );
    
    
    /*! Shift the head to the tail and returns the new head.
     @return    If successful, the current head bject is returned.
                Otherwise, OBJ_NIL.
     */
    OBJ_ID          objList_ShiftTail (
        OBJLIST_DATA    *this
    );
    
    
    ERESULT         objList_SortAscending (
        OBJLIST_DATA    *this
    );
    
    
    OBJ_ID          objList_Tail (
        OBJLIST_DATA    *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = objList_ToDebugString(this,4);
     @endcode
     @param     this    OBJLIST object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    objList_ToDebugString (
        OBJLIST_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJLIST_H */

