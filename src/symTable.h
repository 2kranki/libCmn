// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SYMTABLE Console Transmit Task (symTable) Header
//****************************************************************
/*
 * Program
 *			Separate symTable (symTable)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate symTable to run things without complications
 *          of interfering with the main symTable. A symTable may be 
 *          called a symTable on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal symTable. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	03/27/2017 Generated
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
#include        <objEnum.h>


#ifndef         SYMTABLE_H
#define         SYMTABLE_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct symTable_data_s	SYMTABLE_DATA;    // Inherits from OBJ.

    typedef struct symTable_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in symTable_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SYMTABLE_DATA *);
    } SYMTABLE_VTBL;



    // Prime numbers for hash table sizes within 16 bits
    // (Maximum size is 65535)
    typedef enum symTable_table_size_e {
        SYMTABLE_HASH_SIZE_XXXXXSMALL = 5,
        SYMTABLE_HASH_SIZE_XXXXSMALL = 17,
        SYMTABLE_HASH_SIZE_XXXSMALL = 31,
        SYMTABLE_HASH_SIZE_XXSMALL = 61,
        SYMTABLE_HASH_SIZE_XSMALL = 127,
        SYMTABLE_HASH_SIZE_SMALL = 257,
        SYMTABLE_HASH_SIZE_MEDIUM = 2053,
        SYMTABLE_HASH_SIZE_LARGE  = 4099,
        SYMTABLE_HASH_SIZE_XLARGE = 16411
    } SYMTABLE_HASH_SIZE;
    
    
    
    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    SYMTABLE_DATA *     symTable_Alloc(
        void
    );
    
    
    SYMTABLE_DATA *     symTable_New(
        uint16_t        cHash       // [in] Hash Table Size
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     symTable_getLastError(
        SYMTABLE_DATA   *this
    );


    uint32_t        symTable_getSize(
        SYMTABLE_DATA   *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*! Create a new node and adds it to the hash table if the
        supplied key does not exist in the table.
    @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
    */
    ERESULT         symTable_Add(
        SYMTABLE_DATA    *this,
        OBJ_ID           pObject
    );
    
    
    /*! Delete the first entry found matching the given object
        from the hash and returns it.
     @return    return the object deleted from the hash if successful.
                Otherwise, return OBJ_NIL and set an ERESULT_* error.
     */
    OBJ_ID          symTable_Delete(
        SYMTABLE_DATA   *this,
        OBJ_ID          pObject
    );
    
    
    /*! Delete all entries found in the hash.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         symTable_DeleteAll(
        SYMTABLE_DATA   *this
    );
    
    
    /*! Create an enumerator for the Hash in ascending order
        if the object contains a compare() method.
     @param     this    DIR_DATA object pointer
     @return    If successful, an Enumerator object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned objEnum object.
     */
    OBJENUM_DATA *  symTable_Enum(
        SYMTABLE_DATA   *this
    );
    
    
    /* Find() returns the data associated with the given object if
     * found, otherwise OBJ_NIL is returned.
     */
    OBJ_ID          symTable_Find(
        SYMTABLE_DATA   *this,
        OBJ_ID          pObject
    );
    
    
    SYMTABLE_DATA * symTable_Init(
        SYMTABLE_DATA   *this,
        uint16_t        cHash       // [in] Hash Table Size
    );


    ERESULT         symTable_IsEnabled(
        SYMTABLE_DATA	*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = symTable_ToDebugString(this,4);
     @endcode 
     @param     this    SYMTABLE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *    symTable_ToDebugString(
        SYMTABLE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SYMTABLE_H */

