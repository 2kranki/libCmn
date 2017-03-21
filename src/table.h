// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//        Table Manager (table) Support Subroutines Header
//****************************************************************

/*
 * Program
 *				Table Manager (table) Subroutines
 * Purpose
 *				These subroutines provide a general purpose set of
 *				routines to build and manipulate dynamic tables of
 *				fixed size data. The active data is blocked and
 *              maintained on a linked list.
 *
 *
 * Remarks
 *	1.			Table Entries are numbered starting with one.  If
 *				zero is returned for an entry number, it should be
 *				considered an error.
 *	2.			Once entries are gotten they do not get moved dyna-
 *				mically.  So, if you convert an entry number into
 *				an address, it will be valid until you delete that
 *				entry.
 *  History
 *	11/15/93	Added Borland C++ for OS/2 support.
 *	04/18/93	Added table_MaxCount() to get an array size when using
 *				table_Update() to create a sparse array.
 *	04/15/93	Changed table_Update() for adding or updating entries
 *				based on an entry number.
 *	03/19/93	Added cbSize checking on all external functions.
 *	02/08/93	Added MEM_ support.
 *	01/21/93	Added IBM C Set/2 support.
 *	06/26/92	Created from CLF routines.
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




#include		<cmn_defs.h>


#ifndef TABLE_H
#define TABLE_H	1



#ifdef	__cplusplus
extern	"C" {
#endif
    

    
/****************************************************************
* * * * * * * * * * * *  data definitions   * * * * * * * * * * *
****************************************************************/

    
    typedef struct table_data_s	TABLE_DATA;
    typedef uint16_t            TABLE_INDEX;

    typedef struct table_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in table_object.c.
    } TABLE_VTBL;
    
    





    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    TABLE_DATA *	table_Alloc(
    );
    
    
    uint32_t        table_FindBlockSize(
        uint32_t        approxBlockSizeInK,     // Approx Num of K in block size
        uint32_t        entryDataSize
    );
    
    
    uint32_t        table_FindNumEntries(
        uint32_t        approxBlockSizeInK,     // Approx Num of K in block size
        uint32_t        entryDataSize
    );
    
    
    TABLE_DATA *    table_New(
        uint16_t        entriesPerBlock,
        uint16_t        entryDataSize,
        bool            fFixed
    );

    
    
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------
    
    ERESULT         table_getLastError(
        TABLE_DATA      *this
    );

    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
    /* Add() returns a new entry pointer if available. The
     * new entry is added to the tail of the active list.
     * Returns:
     *		NULL	= Entry not found or invalid table.
     *		DataPtr = Entry Data Address when found.
     */
    void *			table_Add(
        TABLE_DATA		*this
    );
    
    
    // Count() returns the number of active entries in the Table.
    // Returns:
    //			Current Number of List Entries
    TABLE_INDEX 	table_Count(
        TABLE_DATA		*this
    );

    
    // Delete() deletes the entry provided.
    // Returns:
    //			true  =	Successful Completion
    //			false =	Invalid List or Invalid Entry
    bool			table_Delete(
        TABLE_DATA      *this,
        void            *pData
    );

    
    /* Head() returns the entry pointer to the head
     * of the active list.
     * Returns:
     *		NULL	= Entry not found or invalid table.
     *		DataPtr = Entry Data Address when found.
     */
    void *			table_Head(
        TABLE_DATA		*this
    );
    
    
    /* Init() opens an existing table and setups the control blocks
     * for access to it.
     * Returns:
     *		NULL	= Table could not be founded.
     *		Handle	= Successful Open - Table Handle used on other calls.
     */
    TABLE_DATA *	table_Init(
        TABLE_DATA		*this,
        uint16_t        entriesPerBlock,
        uint16_t        entryDataSize,
        bool            fFixed			// true if Fixed Size Table
    );

    
    void			table_Lock(
        TABLE_DATA		*this
    );
    
    
    /* MoveBefore() moves data2 before data1 in the
     * chain.
     */
    bool			table_MoveBefore(
        TABLE_DATA      *this,
        void            *pData1,
        void            *pData2
    );
    
    
    /* Next() returns the next entry pointer given the current
     * entry of the active list.
     * Returns:
     *		NULL	= Entry not found or invalid table.
     *		DataPtr = Entry Data Address when found.
     */
    void *			table_Next(
        TABLE_DATA      *this,
        void            *pData      // Current 
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = table_ToDebugString(this,4);
     @endcode:
     @param:    this    TABLE_DATA object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     table_ToDebugString(
        TABLE_DATA      *this,
        int             indent
    );
    
    
    void			table_Unlock(
        TABLE_DATA		*
    );
    
    
    // Visit each entry in the table from head to tail.
    ERESULT         table_VisitAscending(
        TABLE_DATA      *this,
        void            (pVisitor)(
                                   OBJ_ID,              // Object supplied below
                                   void *               // Current Entry
        ),
        OBJ_ID          pObject
    );

    
    
    
#ifdef	__cplusplus
};
#endif




#endif			// TABLE_H
