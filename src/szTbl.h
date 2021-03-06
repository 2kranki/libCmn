// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Static String Table (szTbl) Header
//****************************************************************
/*
 * Program
 *			Static String Table (szTbl)
 * Purpose
 *          These routines maintain a table of strings using an open
 *          hash table to save space in the heap.  Normally, we save
 *          each string that we are going to use in the table. Then,
 *          we use the version saved in the table for our processing.
 *          Be aware that strings saved are static and should not be
 *          changed since they may be accessed by multiple pointers.
 *
 * Remarks
 *	1.      All indices are relative to 1, not 0.
 *  2.      Strings are uint8_t values 0 - 255. 0 is used to denote
 *          the end of the string. UTF-8 works since it is greater
 *          than 0 for each byte representing a character.  W32
 *          characters are stored as UTF-8.
 *  3.      The token associated with a string in the table
 *          will never change and can be relied on as long as the
 *          table is in existence.
 *
 * History
 *	06/12/2015 Generated
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


#ifndef         SZTBL_H
#define         SZTBL_H 1



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct szTbl_data_s	SZTBL_DATA;

    typedef struct szTbl_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in timer_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TIMER_DATA *);
    } SZTBL_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    SZTBL_DATA *    szTbl_Alloc (
        void
    );
    
    
    OBJ_ID          szTbl_Class (
        void
    );


    SZTBL_DATA *     szTbl_New (
        void
    );
    
    
    SZTBL_DATA *    szTbl_NewFromJSONString (
        ASTR_DATA       *pString
    );
    
    
    SZTBL_DATA *    szTbl_NewFromJSONStringA (
        const
        char            *pString
    );
    
    
    /*!
     Access a table that is shared by all objects.  For most applications, it is
     best to use this table rather than create a separate one.
     @return    If successful, a pointer to the shared szTbl.  Otherwise, OBJ_NIL.
     */
    SZTBL_DATA *    szTbl_Shared (
        void
    );
    
    
    // Release the Shared String Table.
    SZTBL_DATA *    szTbl_SharedReset (
        void
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        szTbl_getSize (
        SZTBL_DATA       *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    SZTBL_DATA *     szTbl_Init (
        SZTBL_DATA      *this
    );


    /* StringToString adds the input string to the table and returns
     * the address of the string in the table.
     */
    const
    char *          szTbl_StringToString (
        SZTBL_DATA      *this,
        const
        char            *pStr           // [in]
    );
    
    const
    char *          szTbl_StringW32ToString (
        SZTBL_DATA      *this,
        const
        W32CHR_T        *pStr           // [in]
    );
    
    
    /*!
     Add a string to the table if it is not already present and return a token used to
     identify the string in the table.
     Example:
     @code
     ERESULT    eRc = szTbl_StringToToken(this, &utf8_char_string, &token);
     @endcode
     @param     this    SZTBL_DATA object pointer
     @param     pStr    Pointer to a NUL-terminated UTF-8 Character String
     @return    If successful, the token for the string in the string table
                and Last Error is ERESULT_SUCCESS. If unsuccessful, an ap-
                propriate ERESULT_* error is put in Last Errorreturned and
                *pToken contains 0.
     */
    uint32_t         szTbl_StringToToken (
        SZTBL_DATA      *this,
        const
        char            *pStr           // [in]
    );
    
    
    uint32_t         szTbl_StringW32ToToken (
        SZTBL_DATA      *this,
        const
        W32CHR_T        *pStr          // [in]
    );
    
    
    uint32_t        szTbl_TokenToHash (
        SZTBL_DATA      *this,
        uint32_t        token           // [in]
    );
    
    
    const
    char *           szTbl_TokenToString (
        SZTBL_DATA      *this,
        uint32_t        token           // [in]
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = szTbl_ToDebugString(this,4);
     @endcode
     @param     this    SZTBL_DATA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     szTbl_ToDebugString (
        SZTBL_DATA      *this,
        int             indent
    );

    
    ASTR_DATA *     szTbl_ToJSON (
        SZTBL_DATA      *this
    );
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* SZTBL_H */

