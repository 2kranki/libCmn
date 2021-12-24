// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  An array of Paths (PathArray) Header
//****************************************************************
/*
 * Program
 *          An array of Paths (PathArray)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate PathArray to run things without complications
 *          of interfering with the main PathArray. A PathArray may be 
 *          called a PathArray on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  12/23/2021 Generated
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
#include        <Path.h>


#ifndef         PATHARRAY_H
#define         PATHARRAY_H


//#define   PATHARRAY_IS_IMMUTABLE     1
#define   PATHARRAY_JSON_SUPPORT       1
//#define   PATHARRAY_SINGLETON        1
//#define       PATHARRAY_LOG   1


#ifdef   PATHARRAY_LOG
#include        <logInterface.h>
#endif



#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct PathArray_data_s  PATHARRAY_DATA;            // Inherits from OBJ
    typedef struct PathArray_class_data_s PATHARRAY_CLASS_DATA; // Inherits from OBJ

    typedef struct PathArray_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //PathArray_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in PathArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PATHARRAY_DATA *);
    } PATHARRAY_VTBL;

    typedef struct PathArray_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in PathArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PATHARRAY_DATA *);
    } PATHARRAY_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  PATHARRAY_SINGLETON
    PATHARRAY_DATA * PathArray_Shared (
        void
    );

    void            PathArray_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to PathArray object if successful, otherwise OBJ_NIL.
     */
    PATHARRAY_DATA * PathArray_Alloc (
        void
    );
    
    
    OBJ_ID          PathArray_Class (
        void
    );
    
    
    PATHARRAY_DATA * PathArray_New (
        void
    );
    
    
    PATHARRAY_DATA * PathArray_NewFromListA (
        const
        char            *pPathA,
        ...
    );

    PATHARRAY_DATA * PathArray_NewFromList (
        va_list         pList
    );


    /*!
     Split a directory into its components which are appended to
     this array.
     The provided directory must have the following structure:
            ['/'] [directory_name ('/' directory_name)*)]
     @param     pDir    PATH Object containing only directtory components
                        such as provided by Path_Split().
     @return    If successful, a PathArray object,  otherwise OBJ_NIL;
     */
    PATHARRAY_DATA * PathArray_NewFromPath (
        PATH_DATA       *pDir
    );


#ifdef  PATHARRAY_JSON_SUPPORT
    PATHARRAY_DATA * PathArray_NewFromJsonString (
        ASTR_DATA       *pString
    );

    PATHARRAY_DATA * PathArray_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJARRAY_DATA * PathArray_getArray (
        PATHARRAY_DATA  *this
    );


#ifdef PATHARRAY_LOG
    /*! @property   Logging
        Allows information and warning messages to be issued for this
        object. Messages will be skipped if Log is not set.
     */
    bool            PathArray_setLog (
        PATHARRAY_DATA  *this,
        OBJ_ID          pObj
    );
#endif


    uint32_t        PathArray_getSize (
        PATHARRAY_DATA  *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Append the given string to the array and return its index.
     @param     this    Object Pointer
     @param     pObject String Object to be added
     @param     pIndex  (Optional) Index Pointer
     @return    If successful, ERESULT_SUCCESS and the index in pIndex
                if it is not NULL.  Otherwise, an ERESULT_* error.
     */
    ERESULT         PathArray_AppendPath (
        PATHARRAY_DATA  *this,
        PATH_DATA       *pObject,
        uint32_t        *pIndex
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
     ERESULT eRc = AStrArray_Assign(this, pOther);
     @endcode
     @param     this    ASTRARRAY_DATA object pointer
     @param     pOther  a pointer to another ASTRARRAY_DATA object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         PathArray_Assign (
        PATHARRAY_DATA  *this,
        PATHARRAY_DATA  *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
     appl      *pCopy = AStrArray_Copy(this);
     @endcode
     @param     this    ASTRARRAY_DATA object pointer
     @return    If successful, a ASTRARRAY_DATA object which must
     be released, otherwise OBJ_NIL.
     @warning   Remember to release the returned the returned object.
     */
    PATHARRAY_DATA * PathArray_Copy (
        PATHARRAY_DATA  *this
    );


    // DeleteFromBottom() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    PATH_DATA *     PathArray_DeleteFirst (
        PATHARRAY_DATA  *this
    );


    // DeleteFromTop() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    PATH_DATA *     PathArray_DeleteLast (
        PATHARRAY_DATA  *this
    );


    /*!
     Create an enumerator for the array in ascending order.
     @param     this    object pointer
     @return    If successful, an Enumerator object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned Enum object.
     */
    OBJENUM_DATA *  PathArray_Enum (
        PATHARRAY_DATA  *this
    );

   
    /*!
     Get the i'th entry from the array if it exists.
     @param     this    object pointer
     @param     index   entry index relattive to 1
     @return    If successful, an AStr object,  otherwise OBJ_NIL;
     */
    PATH_DATA *     PathArray_Get (
        PATHARRAY_DATA  *this,
        uint32_t        index       // Relative to 1
    );

    PATH_DATA *     PathArray_GetFirst (
        PATHARRAY_DATA  *this
    );

    PATH_DATA *     PathArray_GetLast (
        PATHARRAY_DATA  *this
    );


    PATHARRAY_DATA * PathArray_Init (
        PATHARRAY_DATA  *this
    );


    ERESULT         PathArray_InsertStr (
        PATHARRAY_DATA  *this,
        uint32_t        index,
        PATH_DATA       *pObject
    );


    ERESULT         PathArray_SortAscending (
        PATHARRAY_DATA    *this
    );


    /*!
     Split a directory into its components which are appended to
     this array.
     The provided directory must have the following structure:
            ['/'] [directory_name ('/' directory_name)*)]
     @param     this    object pointer
     @param     pDir    PATH Object containing only directtory components
                        such as provided by Path_Split().
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         PathArray_SplitDir(
        PATHARRAY_DATA  *this,
        PATH_DATA       *pDir
    );


#ifdef  PATHARRAY_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = PathArray_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     PathArray_ToJson (
        PATHARRAY_DATA  *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = PathArray_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     PathArray_ToDebugString (
        PATHARRAY_DATA  *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* PATHARRAY_H */

