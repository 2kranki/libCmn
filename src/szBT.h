// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Static String Binary Tree (szBT) Header
//****************************************************************
/*
 * Program
 *			Static String Binary Tree (szBT)
 * Purpose
 *			This object provides a search tree for data indexed
 *          by a NUL-Terminated UTF-8 string. No data or keys are
 *          stored within the tree, only pointers are stored.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	02/25/2020 Generated
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


#ifndef         SZBT_H
#define         SZBT_H


//#define   SZBT_IS_IMMUTABLE     1
//#define   SZBT_JSON_SUPPORT     1
//#define   SZBT_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct szBT_data_s	SZBT_DATA;            // Inherits from OBJ
    typedef struct szBT_class_data_s SZBT_CLASS_DATA;   // Inherits from OBJ

    typedef struct szBT_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in szBT_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SZBT_DATA *);
    } SZBT_VTBL;

    typedef struct szBT_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in szBT_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SZBT_DATA *);
    } SZBT_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SZBT_SINGLETON
    SZBT_DATA *     szBT_Shared (
        void
    );

    void            szBT_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to szBT object if successful, otherwise OBJ_NIL.
     */
    SZBT_DATA *     szBT_Alloc (
        void
    );
    
    
    OBJ_ID          szBT_Class (
        void
    );
    
    
    SZBT_DATA *     szBT_New (
        void
    );
    
    
#ifdef  SZBT_JSON_SUPPORT
    SZBT_DATA *   szBT_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SZBT_DATA *   szBT_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        szBT_getSize (
        SZBT_DATA       *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the given node to the Hash. Duplicates are not allowed.
     @param     this        Object Pointer
     @param     pNameA      Name Character String Pointer
     @param     pData       Data Pointer
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
                error code is returned.
     */
    ERESULT         szBT_AddUpdateA (
        SZBT_DATA       *this,
        const
        char            *pNameA,            // UTF-8
        void            *pData
    );


    ERESULT         szBT_DeleteA (
        SZBT_DATA       *this,
        const
        char            *pNameA
    );


    /*!
     Search the Tree for a particular node using the characteristics of
     the given node and its compare function.
     @return    If successful, an NODE object is returned.  Otherwise,
                OBJ_NIL.
     */
    void *          szBT_FindA (
        SZBT_DATA       *this,
        const
        char            *pNameA
    );


    /*!
     Scan all the nodes of the Tree in no particular order.
     @return    ERESULT_SUCCESS if successful completion.  Otherwise,
                an ERESULT_* error code is returned.
     */
    ERESULT         szBT_ForEach (
        SZBT_DATA       *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,               // Used as first parameter of scan method
        void            *pArg3              // Used as third parameter of scan method
    );


    SZBT_DATA *     szBT_Init (
        SZBT_DATA       *this
    );


#ifdef  SZBT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = szBT_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     szBT_ToJson (
        SZBT_DATA       *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = szBT_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    szBT_ToDebugString (
        SZBT_DATA       *this,
        int             indent
    );
    
    
    ERESULT         szBT_VerifyTree (
        SZBT_DATA       *this
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* SZBT_H */

