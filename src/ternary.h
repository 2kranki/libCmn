// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Ternary Search Tree (ternary) Header
//****************************************************************
/*
 * Program
 *			Ternary Search Tree (ternary)
 * Purpose
 *			This object provides a Ternary Search Tree as defined
 *          by Robert Sedgewick and Jon Bentley. A Ternary Search 
 *          Tree is similar to a Binary Tree except it has 3 links
 *          instead of 2. The third link is based on an equal path.
 *          Also, a TST stores one character at a time of the key.
 *          So, it generally is very fast to search especially if
 *          the keys were not added inorder but randomly.
 *
 * Remarks
 *	1.      A Ternary Search Tree does not facilitate actually ex-
 *          tracting the words that were added to it. So, one has
 *          to add the word to the data stored in the tree if needed.
 *
 * History
 *	09/19/2015 Generated
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


#ifndef         TERNARY_H
#define         TERNARY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ternary_data_s	TERNARY_DATA;

    typedef struct ternary_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in table_object.c.
    } TERNARY_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the ternary including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    TERNARY_DATA *  ternary_Alloc(
        void
    );
    
    
    TERNARY_DATA *  ternary_New(
        uint32_t        bufferSize
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         ternary_getLastError(
        TERNARY_DATA    *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    bool            ternary_Add(
        TERNARY_DATA	*this,
        int32_t			*pName,
        void            *pData
    );
    
    
    /*!
     Search for the key.
     @return    If key is found, return the data ptr, otherwise NULL.
     */
    void *          ternary_Find(
        TERNARY_DATA	*this,
        int32_t			*pszKey
    );
    
    
    TERNARY_DATA * ternary_Init(
        TERNARY_DATA    *this,
        uint32_t        bufferSize
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = ternary_ToDebugString(this,4);
     @endcode
     @param     this    TERNARY_DATA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ternary_ToDebugString(
        TERNARY_DATA    *this,
        int             indent
    );
    
    
    ERESULT         ternaryTree_VisitPreorder(
        TERNARY_DATA	*this,
        void            (pVisitor)(
                            OBJ_ID          ,       // Object supplied below
                            void            *       // Word associated Data Ptr
        ),
        OBJ_ID          pObject
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* TERNARY_H */

