// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//        Line Index into File or Buffer (LineIndex) Header
//****************************************************************
/*
 * Program
 *          Line Index into File or Buffer (LineIndex)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate LineIndex to run things without complications
 *          of interfering with the main LineIndex. A LineIndex may be 
 *          called a LineIndex on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  12/18/2018 Generated as sidxe
 *  06/04/2020 Regenerated as LineIndex to make it more clear as
 *              to its functionality and use the new naming convention.
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
#include        <SrcLoc.h>


#ifndef         LINEINDEX_H
#define         LINEINDEX_H


//#define   LINEINDEX_IS_IMMUTABLE     1
#define   LINEINDEX_JSON_SUPPORT       1
//#define   LINEINDEX_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct LineIndex_data_s  LINEINDEX_DATA;            // Inherits from OBJ
    typedef struct LineIndex_class_data_s LINEINDEX_CLASS_DATA;   // Inherits from OBJ

    typedef struct LineIndex_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in LineIndex_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LINEINDEX_DATA *);
    } LINEINDEX_VTBL;

    typedef struct LineIndex_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in LineIndex_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LINEINDEX_DATA *);
    } LINEINDEX_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  LINEINDEX_SINGLETON
    LINEINDEX_DATA * LineIndex_Shared (
        void
    );

    void            LineIndex_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to LineIndex object if successful, otherwise OBJ_NIL.
     */
    LINEINDEX_DATA * LineIndex_Alloc (
        void
    );
    
    
    OBJ_ID          LineIndex_Class (
        void
    );
    
    
    LINEINDEX_DATA * LineIndex_New (
        void
    );
    
    LINEINDEX_DATA * LineIndex_NewWithMax (
        uint16_t        max
    );


#ifdef  LINEINDEX_JSON_SUPPORT
    LINEINDEX_DATA * LineIndex_NewFromJsonString (
        ASTR_DATA       *pString
    );

    LINEINDEX_DATA * LineIndex_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        LineIndex_getInterval (
        LINEINDEX_DATA  *this
    );


    uint32_t        LineIndex_getMax (
        LINEINDEX_DATA  *this
    );

    bool            LineIndex_setMax (
        LINEINDEX_DATA  *this,
        uint32_t        value
    );


    uint32_t        LineIndex_getMaxLine (
        LINEINDEX_DATA  *this
    );


    uint32_t        LineIndex_getSize (
        LINEINDEX_DATA  *this
    );


    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add a location to the index if it is needed.
     @param     this    object pointer
     @param     pLoc    pointer to a SRCLOC data area in which the lineNo
                        and offset fields will be used.
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         LineIndex_Add (
        LINEINDEX_DATA  *this,
        SRCLOC          *pLoc
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = LineIndex_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another LINEINDEX object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         LineIndex_Assign (
        LINEINDEX_DATA  *this,
        LINEINDEX_DATA  *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        LineIndex      *pCopy = LineIndex_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a LINEINDEX object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LINEINDEX_DATA * LineIndex_Copy (
        LINEINDEX_DATA  *this
    );

   
    /*!
     Find the location to the given lineNo that is at or before it. This
     allows for line positioning within a stream file or buffer.  It is
     assumed that some entries have been added to the table before a
     location can be returned.
     @param     this    object pointer
     @param     lineNo  Line number to be searched for
     @param     pLoc   pointer to a SRCLOC data area which will be returned.
     @return:   If successful, ERESULT_SUCCESS and the SRCLOC data is returned
                in ppLoc. Otherwise, an ERESULT_* error.
     */
    ERESULT         LineIndex_Find (
        LINEINDEX_DATA  *this,
        uint32_t        lineNo,
        SRCLOC          *pLoc
    );


     /*!
      Find the location to the given offset that is at or before it. This
      allows for line positioning within a stream file or buffer.  It is
      assumed that some entries have been added to the table before a
      location can be returned.
      @param     this    object pointer
      @param     offset  offset within buffer or file to be searched for
      @param     pLoc   pointer to a SRCLOC data area which will be returned.
      @return:   If successful, ERESULT_SUCCESS and the SRCLOC data is returned
                 in ppLoc. Otherwise, an ERESULT_* error.
      */
    ERESULT         LineIndex_FindOffset (
        LINEINDEX_DATA  *this,
        int64_t         offset,
        SRCLOC          *pLoc
    );


    LINEINDEX_DATA * LineIndex_Init (
        LINEINDEX_DATA  *this
    );


    /*!
     Reset the index as if it was just created with no data.
     @param     this    object pointer
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         LineIndex_Reset (
        LINEINDEX_DATA  *this
    );
    
 
#ifdef  LINEINDEX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = LineIndex_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LineIndex_ToJson (
        LINEINDEX_DATA  *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = LineIndex_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LineIndex_ToDebugString (
        LINEINDEX_DATA  *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* LINEINDEX_H */

