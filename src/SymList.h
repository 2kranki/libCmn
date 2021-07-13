// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  List of Symbol Table Entries (SymList) Header
//****************************************************************
/*
 * Program
 *          List of Symbol Table Entries (SymList)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate SymList to run things without complications
 *          of interfering with the main SymList. A SymList may be 
 *          called a SymList on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  07/13/2021 Generated
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
#include        <Sym.h>


#ifndef         SYMLIST_H
#define         SYMLIST_H


//#define   SYMLIST_IS_IMMUTABLE     1
#define   SYMLIST_JSON_SUPPORT       1
//#define   SYMLIST_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SymList_data_s  SYMLIST_DATA;            // Inherits from OBJ
    typedef struct SymList_class_data_s SYMLIST_CLASS_DATA;   // Inherits from OBJ

    typedef struct SymList_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SymList_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SYMLIST_DATA *);
    } SYMLIST_VTBL;

    typedef struct SymList_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SymList_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SYMLIST_DATA *);
    } SYMLIST_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SYMLIST_SINGLETON
    SYMLIST_DATA *  SymList_Shared (
        void
    );

    void            SymList_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SymList object if successful, otherwise OBJ_NIL.
     */
    SYMLIST_DATA *  SymList_Alloc (
        void
    );
    
    
    OBJ_ID          SymList_Class (
        void
    );
    
    
    SYMLIST_DATA *  SymList_New (
        void
    );
    
    
#ifdef  SYMLIST_JSON_SUPPORT
    SYMLIST_DATA *  SymList_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SYMLIST_DATA *  SymList_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        SymList_getSize (
        SYMLIST_DATA       *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         SymList_Add2Head (
        SYMLIST_DATA    *this,
        SYM_DATA        *pSym
    );


    ERESULT         SymList_Add2Tail (
        SYMLIST_DATA    *this,
        SYM_DATA        *pSym
    );


    // Deletes first entry in list that matches the name.
    ERESULT         SymList_DeleteA (
        SYMLIST_DATA    *this,
        int32_t         cls,
        const
        char            *pNameA
    );


    ERESULT         SymList_DeleteHead (
        SYMLIST_DATA    *this
    );


    ERESULT         SymList_DeleteTail (
        SYMLIST_DATA    *this
    );


    SYM_DATA *      SymList_FindA(
        SYMLIST_DATA    *this,
        int32_t         cls,
        const
        char            *pNameA
    );


    ERESULT         SymList_ForEach(
        SYMLIST_DATA    *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );


    SYM_DATA *      SymList_Index (
        SYMLIST_DATA    *this,
        uint32_t        index
    );


    SYMLIST_DATA *   SymList_Init (
        SYMLIST_DATA     *this
    );


    /*!
     Sort the list by Name in ascending sequence.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
     error.
     */
    ERESULT         SymList_SortAscending(
        SYMLIST_DATA    *this
    );


#ifdef  SYMLIST_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SymList_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SymList_ToJson (
        SYMLIST_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SymList_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SymList_ToDebugString (
        SYMLIST_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* SYMLIST_H */

