// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          List of Objects (ObjList) Header
//****************************************************************
/*
 * Program
 *			List of Objects (ObjList)
 * Purpose
 *          This object provides a list of objects which provides
 *          for fast addition and deletion of objects.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/15/2019 Generated
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
#include        <ObjArray.h>
#include        <ObjEnum.h>


#ifndef         OBJLIST_H
#define         OBJLIST_H


#define   OBJLIST_JSON_SUPPORT 1
//#define   OBJLIST_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ObjList_data_s	OBJLIST_DATA;            // Inherits from OBJ
    typedef struct ObjList_class_data_s OBJLIST_CLASS_DATA;   // Inherits from OBJ

    typedef struct ObjList_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjList_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJLIST_DATA *);
    } OBJLIST_VTBL;

    typedef struct ObjList_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjList_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJLIST_DATA *);
    } OBJLIST_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  OBJLIST_SINGLETON
    OBJLIST_DATA *     ObjList_Shared (
        void
    );

    bool            ObjList_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ObjList object if successful, otherwise OBJ_NIL.
     */
    OBJLIST_DATA *  ObjList_Alloc (
        void
    );
    
    
    OBJ_ID          ObjList_Class (
        void
    );
    
    
    OBJLIST_DATA *  ObjList_New (
        void
    );
    
    
    OBJLIST_DATA *   ObjList_NewFromJsonString(
        ASTR_DATA       *pString
    );


    OBJLIST_DATA * ObjList_NewFromJsonStringA(
        const
        char            *pString
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     Ordered property causes the list to be sorted according to the
     vtbl compare routine.  For Ordered to work properly all objects
     in the list should be of the same type.
     */
    bool            ObjList_getOrdered (
        OBJLIST_DATA    *this
    );

    bool            ObjList_setOrdered (
        OBJLIST_DATA    *this,
        bool            fValue
    );


    /*!
     Size property is the numbers of objects on the list.
     */
    uint32_t        ObjList_getSize (
        OBJLIST_DATA   *this
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         ObjList_Add2Head (
        OBJLIST_DATA    *this,
        OBJ_ID          pObject
    );
    
    
    ERESULT         ObjList_Add2Tail (
        OBJLIST_DATA    *this,
        OBJ_ID          pObject
    );
    
    
    ERESULT         ObjList_Append (
        OBJLIST_DATA    *this,
        OBJLIST_DATA    *pOther
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = ObjList_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another OBJLIST object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         ObjList_Assign (
        OBJLIST_DATA    *this,
        OBJLIST_DATA    *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        ObjList      *pCopy = ObjList_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a OBJLIST object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJLIST_DATA *  ObjList_Copy (
        OBJLIST_DATA    *this
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
    OBJLIST_DATA *  ObjList_DeepCopy (
        OBJLIST_DATA    *this
    );
    
    
    ERESULT         ObjList_DeleteAll (
        OBJLIST_DATA    *this
    );


    ERESULT         ObjList_DeleteHead (
        OBJLIST_DATA    *this
    );
    
    ERESULT         ObjList_DeleteIndex (
        OBJLIST_DATA    *this,
        uint32_t        index
    );
    
    ERESULT         ObjList_DeleteTail (
        OBJLIST_DATA    *this
    );
    
    
     /*! Create an enumerator for the list.
      @return    If successful, an ENUM object is returned.  Otherwise,
      OBJ_NIL.
      @warning   Remember to release the returned ENUM object.
      */
     OBJENUM_DATA * ObjList_Enum (
         OBJLIST_DATA   *this
     );
     
     
     ERESULT        ObjList_ForEach (
         OBJLIST_DATA   *this,
         P_ERESULT_EXIT3 pScan,
         OBJ_ID         pObject,        // Used as first parameter of scan method
         //                             // Second Argument is current list element
         void           *pArg3          // Third Argument of Scan
     );
     
     
     OBJ_ID         ObjList_Head (
         OBJLIST_DATA   *this
     );

    
     OBJ_ID         ObjList_Index (
         OBJLIST_DATA   *this,
         int32_t        index                    // (relative to 1)
     );
     
     
    OBJLIST_DATA *  ObjList_Init (
        OBJLIST_DATA    *this
    );


    OBJ_ID          ObjList_Next (
        OBJLIST_DATA    *this
    );
    
    
    OBJARRAY_DATA * ObjList_Objects (
        OBJLIST_DATA    *this
    );
    
    
    ERESULT         ObjList_Prepend(
        OBJLIST_DATA    *this,
        OBJLIST_DATA    *other
    );


    OBJ_ID          ObjList_Prev (
        OBJLIST_DATA    *this
    );
    
    
    /*! Shift the tail to the head and returns the new head.
     @return    If successful, the current head bject is returned.
                Otherwise, OBJ_NIL.
     */
    OBJ_ID          ObjList_ShiftHead (
        OBJLIST_DATA    *this
    );
    
    
    /*! Shift the head to the tail and returns the new head.
     @return    If successful, the current head bject is returned.
                Otherwise, OBJ_NIL.
     */
    OBJ_ID          ObjList_ShiftTail (
        OBJLIST_DATA    *this
    );
    
    
    ERESULT         ObjList_SortAscending (
        OBJLIST_DATA    *this
    );
    
    
    OBJ_ID          ObjList_Tail (
        OBJLIST_DATA    *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ObjList_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjList_ToJson (
        OBJLIST_DATA      *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjList_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    ObjList_ToDebugString (
        OBJLIST_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJLIST_H */

