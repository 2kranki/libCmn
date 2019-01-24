// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  A List of Tokens (tokenList) Header
//****************************************************************
/*
 * Program
 *			A List of Tokens (tokenList)
 * Purpose
 *			This object provides a list of tokens.
 * Remarks
 *	1.      Each token in the list must only be referenced for use
 *          and never copied or released. They can be assigned.

 *
 * History
 *	07/22/2015 Generated
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
#include        <enum.h>
#include        <token.h>


#ifndef         TOKENLIST_H
#define         TOKENLIST_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

    // typedef struct tokenList_data_s	TOKENLIST_DATA;     // Found in token.h

    typedef struct tokenList_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in table_object.c.
    } TOKENLIST_VTBL;
    

    // Prime numbers for hash table sizes within 16 bits
    // (Maximum size is 65535)
    typedef enum tokenList_table_size_e {
        TOKENLIST_TABLE_SIZE_XXXXXSMALL = 5,
        TOKENLIST_TABLE_SIZE_XXXXSMALL = 17,
        TOKENLIST_TABLE_SIZE_XXXSMALL = 31,
        TOKENLIST_TABLE_SIZE_XXSMALL = 61,
        TOKENLIST_TABLE_SIZE_XSMALL = 127,
        TOKENLIST_TABLE_SIZE_SMALL = 257,
        TOKENLIST_TABLE_SIZE_MEDIUM = 2053,
        TOKENLIST_TABLE_SIZE_LARGE  = 4099,
        TOKENLIST_TABLE_SIZE_XLARGE = 16411
    } TOKENLIST_TABLE_SIZE;
    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    TOKENLIST_DATA * tokenList_Alloc(
        void
    );
    
    
    TOKENLIST_DATA * tokenList_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /* Size() returns the current number of used entries.
     * Returns:
     *		Current Number of Entries in Table
     */
    uint32_t        tokenList_getSize(
        TOKENLIST_DATA   *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         tokenList_Add2Head(
        TOKENLIST_DATA   *this,
        TOKEN_DATA       *pNode
    );


    ERESULT         tokenList_Add2Tail(
        TOKENLIST_DATA   *this,
        TOKEN_DATA       *pNode
    );
    
    
    /*!
     This routine appends (adds to the tail) the other list to this list.
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_???.
     */
    ERESULT         tokenList_Append(
        TOKENLIST_DATA	*this,
        TOKENLIST_DATA	*other
    );
    
    
    ERESULT         tokenList_DeleteAll(
        TOKENLIST_DATA	*this
    );
    
    
    ERESULT         tokenList_DeleteHead(
        TOKENLIST_DATA	*this
    );
    
    
    ERESULT         tokenList_DeleteTail(
        TOKENLIST_DATA	*this
    );
    
    
    ERESULT         tokenList_Enum(
        TOKENLIST_DATA	*this,
        ENUM_DATA       **ppEnum
    );
    
    
    ERESULT         tokenList_ForEach(
        TOKENLIST_DATA	*this,
        P_ERESULT_EXIT2 pScan,
        OBJ_ID          pObj            // Used as first parameter of scan method
    );
    
    
    TOKEN_DATA *    tokenList_Head(
        TOKENLIST_DATA	*this
    );
    
    
    /*!
     Index() returns the Ith entry from the Head of the List.
     @param     index is relative to 1 from the Head of the List
     @return    Token Ptr if successful, otherwise NULL
     @warning:  This method must starts at the head and moves toward
                 the index'th token in the list every time that it is
                 called.
     */
    TOKEN_DATA *    tokenList_Index(
        TOKENLIST_DATA	*this,
        int32_t			index					// (relative to 1)
    );
    
    
    TOKENLIST_DATA * tokenList_Init(
        TOKENLIST_DATA   *this
    );


    /*!
     This routine prepends (adds to the head) the other list to this list.
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_???.
     */
    ERESULT         tokenList_Prepend(
        TOKENLIST_DATA	*this,
        TOKENLIST_DATA	*other
    );
    
    
    TOKEN_DATA *    tokenList_Tail(
        TOKENLIST_DATA	*this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     tokenList_ToDebugString(
        TOKENLIST_DATA   *this,
        int             indent
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* TOKENLIST_H */

