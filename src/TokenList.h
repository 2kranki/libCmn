// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          A List of Tokens (TokenList) Header
//****************************************************************
/*
 * Program
 *			A List of Tokens (TokenList)
 * Purpose
 *            This object provides a list of tokens.
 * Remarks
 *    1.      Each token in the list must only be referenced for use
 *          and never copied or released. They can be assigned.
 *
 * History
 *  07/22/2015 Generated
 *	01/02/2020 Regenerated
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
#include        <ObjEnum.h>
#include        <ObjList.h>
#include        <Token.h>


#ifndef         TOKENLIST_H
#define         TOKENLIST_H


#define   TOKENLIST_JSON_SUPPORT 1
//#define   TOKENLIST_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct TokenList_data_s	TOKENLIST_DATA;            // Inherits from OBJ
    typedef struct TokenList_class_data_s TOKENLIST_CLASS_DATA;   // Inherits from OBJ

    typedef struct TokenList_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TokenList_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TOKENLIST_DATA *);
    } TOKENLIST_VTBL;

    typedef struct TokenList_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TokenList_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TOKENLIST_DATA *);
    } TOKENLIST_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  TOKENLIST_SINGLETON
    TOKENLIST_DATA * TokenList_Shared (
        void
    );

    void            TokenList_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to TokenList object if successful, otherwise OBJ_NIL.
     */
    TOKENLIST_DATA * TokenList_Alloc (
        void
    );
    
    
    OBJ_ID          TokenList_Class (
        void
    );
    
    
    TOKENLIST_DATA * TokenList_New (
        void
    );
    
    
    TOKENLIST_DATA * TokenList_NewFromJsonString(
        ASTR_DATA       *pString
    );


    TOKENLIST_DATA * TokenList_NewFromJsonStringA(
        const
        char            *pString
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJLIST_DATA *  TokenList_getList (
        TOKENLIST_DATA  *this
    );


    uint32_t        TokenList_getSize (
        TOKENLIST_DATA  *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         TokenList_Add2Head (
        TOKENLIST_DATA  *this,
        TOKEN_DATA      *pNode
    );


    ERESULT         TokenList_Add2Tail (
        TOKENLIST_DATA  *this,
        TOKEN_DATA      *pNode
    );


    /*!
     This routine appends (adds to the tail) the other list to this list.
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_???.
     */
    ERESULT         TokenList_Append (
        TOKENLIST_DATA  *this,
        TOKENLIST_DATA  *other
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = TokenList_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another TOKENLIST object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         TokenList_Assign (
        TOKENLIST_DATA  *this,
        TOKENLIST_DATA  *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        TokenList      *pCopy = TokenList_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a TOKENLIST object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TOKENLIST_DATA * TokenList_Copy (
        TOKENLIST_DATA  *this
    );


    ERESULT         TokenList_DeleteAll (
        TOKENLIST_DATA  *this
    );


    ERESULT         TokenList_DeleteHead (
        TOKENLIST_DATA  *this
    );


    ERESULT         TokenList_DeleteTail (
        TOKENLIST_DATA  *this
    );


    OBJENUM_DATA *  TokenList_Enum(
        TOKENLIST_DATA  *this
    );


    TOKEN_DATA *    TokenList_Head (
        TOKENLIST_DATA  *this
    );


    /*!
     Index() returns the Ith entry from the Head of the List.
     @param     index is relative to 1 from the Head of the List
     @return    Token Ptr if successful, otherwise NULL
     @warning:  This method must starts at the head and moves toward
                 the index'th token in the list every time that it is
                 called.
     */
    TOKEN_DATA *    TokenList_Index (
        TOKENLIST_DATA  *this,
        int32_t         index                    // (relative to 1)
    );


    TOKENLIST_DATA * TokenList_Init (
        TOKENLIST_DATA  *this
    );


    /*!
     This routine prepends (adds to the head) the other list to this list.
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_???.
     */
    ERESULT         TokenList_Prepend (
        TOKENLIST_DATA  *this,
        TOKENLIST_DATA  *other
    );


    TOKEN_DATA *    TokenList_Tail (
        TOKENLIST_DATA  *this
    );


    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = TokenList_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     TokenList_ToJson(
        TOKENLIST_DATA   *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = TokenList_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     TokenList_ToDebugString (
        TOKENLIST_DATA  *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* TOKENLIST_H */

