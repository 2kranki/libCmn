// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Simple String Hash Table (szHash) Header
//****************************************************************
/*
 * Program
 *				NUL-Terminated String Hash Table (SZHASH)
 * Purpose
 *				These subroutines provide an open chained hash
 *              table for keys of szString. Regular and Wide
 *              character strings are supported. The table is
 *              stored in UTF8 format.
 *
 *              Internal nodes are blocked to limit memory 
 *              fragmentation. The maximum number of hash
 *              chains is 65535. The overall size can grow
 *              bigger since the nodes are chained from the
 *              hash table.
 *
 * Remarks
 *	1.			All keys must be unique within the table.
 *  2.          There are several conforming hash functions
 *              as well as a conforming comparison function
 *              in "str".
 *  3.          Since pointers are used for both the key and
 *              the data, you could substitute pointers to any
 *              other type of object as long as you provide
 *              the hash and comparison routines that are ap-
 *              propriate for that type.
 *  4.          Neither the key nor the data is copied.  The
 *              pointers to them are stored in the table.  So,
 *              care must be taken that the key and data are
 *              NOT changed while they are stored in table.
 *
 * History
 *	06/11/2015 Generated
 *
 * References
 *		"Data Structures and Algorithms", Alfred V. Aho et al,
 *			Addison-Wesley, 1985
 *		"Data Structures using C", Aaron M. Tenenbaum et al,
 *			Prentice-Hall, 1990
 *		"Programs and Data Structures in C", Leendert Ammeraal,
 *			John Wiley & Sons, 1987
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
#include        <szTbl.h>
#include        <AStr.h>
#include        <Enum.h>


#ifndef         SZHASH_H
#define         SZHASH_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct szHash_data_s	SZHASH_DATA;

    typedef struct szHash_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in timer_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TIMER_DATA *);
    } SZHASH_VTBL;
    
    
    
    // Prime numbers for hash table sizes within 16 bits
    // (Maximum size is 65535)
    typedef enum szHash_table_size_e {
        SZHASH_TABLE_SIZE_XXXXXSMALL = 5,
        SZHASH_TABLE_SIZE_XXXXSMALL = 11,
        SZHASH_TABLE_SIZE_XXXSMALL = 17,
        SZHASH_TABLE_SIZE_XXSMALL = 37,
        SZHASH_TABLE_SIZE_XSMALL = 67,
        SZHASH_TABLE_SIZE_SMALL = 131,
        SZHASH_TABLE_SIZE_MEDIUM = 257,
        SZHASH_TABLE_SIZE_LARGE  = 521,
        SZHASH_TABLE_SIZE_XLARGE = 1031
    } SZHASH_TABLE_SIZE;
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    SZHASH_DATA *       szHash_Alloc(
        void
    );
    
    
    SZHASH_DATA *       szHash_New(
        uint16_t            cHash
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool			szHash_setCompare(
        SZHASH_DATA     *this,
        int             (*pCompare)(const char *pKey1, const char *pKey2),
        int             (*pCompareAW32)(const char *pKey1, const W32CHR_T *pKey2)
    );
    
    
    bool			szHash_setComputeHash(
        SZHASH_DATA     *this,
        uint32_t        (*pComputeHash)(const char *pszKey1, size_t *pLen),
        uint32_t        (*pComputeHashW32)(const W32CHR_T *pszKey1, size_t *pLen)
    );
    
    
    bool            szHash_getDuplicates(
        SZHASH_DATA     *this
    );
    
    bool            szHash_setDuplicates(
        SZHASH_DATA     *this,
        bool            fValue
    );
    

    ERESULT         szHash_getLastError(
        SZHASH_DATA     *this
    );
    
    
    /* Size() returns the current number of used entries.
     * Returns:
     *		Current Number of Entries in Table
     */
    uint32_t        szHash_getSize(
        SZHASH_DATA		*this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Create a new entry in the hash table if the supplied key does not
     exist in the table unless duplicates are allowed.  If duplicates
     are allowed, then the entry is added in such a fashion that it will
     always be found first.
     @param     this        Object Pointer
     @param     pszKey      Pointer to UTF-8 Key which is NUL-terminated
     @param     pData       Pointer to any area to be connected to the
                            key
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         szHash_AddA(
        SZHASH_DATA     *this,
        const
        char            *pszKey,
        void			*pData
    );
    
    
    /* Delete() deletes the first entry found matching the Key given.
     * Returns:
     *		TRUE	= Entry successfully deleted.
     *		FALSE	= Entry could not be deleted.
     */
    ERESULT         szHash_DeleteA(
        SZHASH_DATA     *this,
        const
        char            *pszKey
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = szHash_EnumKeys(this, &pEnum);
     @endcode
     @param     this    object pointer
     @return    If successful, pointer to an Enumeration Object Pointer.
                Otherwise, OBJ_NIL and an ERESULT_* error code in the
                Last Error Code.
     @warning   Remember to release the returned Enumeration object.
     */
    ENUM_DATA *     szHash_EnumKeys(
        SZHASH_DATA     *this
    );
    
    
    /* Find() returns the data associated with the string if found,
     * otherwise NULL.
     */
    void *          szHash_FindA(
        SZHASH_DATA     *this,
        const
        char            *pszKey
    );
    
    void *          szHash_FindW32(
        SZHASH_DATA     *this,
        const
        W32CHR_T        *pszKey
    );
    
    
    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    SZHASH_DATA *   szHash_Init(
        SZHASH_DATA     *this,
        uint16_t        cHash       // [in] Hash Table Size
    );


    /*!
     Create a string that describes this object and the
     objects within it.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *    szHash_ToDebugString(
        SZHASH_DATA     *this,
        int             indent
    );
    
    
    /* Update() re-initializes a particular active entry pointer.
     * The old data ptr is discarded and the new one is put in its
     * place.
     * Returns:
     *		TRUE	= Entry successfully deleted.
     *		FALSE	= Entry could not be deleted.
     */
    ERESULT         szHash_UpdateA(
        SZHASH_DATA		*this,
        const
        char            *pszKey,
        void			*pData
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* SZHASH_H */

