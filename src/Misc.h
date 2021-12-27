// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Miscellaneous Routines (Misc) Header
//****************************************************************
/*
 * Program
 *          Miscellaneous Routines (Misc)
 * Purpose
 *          This object provides a group of routines that do not
 *          fit in any other category.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  12/27/2021 Generated
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


#ifndef         MISC_H
#define         MISC_H


//#define   MISC_IS_IMMUTABLE     1
//#define   MISC_JSON_SUPPORT     1
//#define   MISC_SINGLETON        1
//#define       MISC_LOG   1


#ifdef   MISC_LOG
#include        <logInterface.h>
#endif



#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Misc_data_s  MISC_DATA;          // Inherits from MISC
    typedef struct Misc_class_data_s MISC_CLASS_DATA;  // Inherits from OBJ

    typedef struct Misc_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //Misc_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Misc_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MISC_DATA *);
    } MISC_VTBL;

    typedef struct Misc_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Misc_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MISC_DATA *);
    } MISC_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  MISC_SINGLETON
    MISC_DATA *     Misc_Shared (
        void
    );

    void            Misc_SharedReset (
        void
    );
#endif


    /* AbbrevA() tests whether or not the input string, "text", is a valid
     * abbreviation of the pattern string, "pattern".  The pattern is a
     * string giving the input expected, with mandatory characters in
     * uppercase and optional ones in lowercase.  The function returns
     * true if the text string contains all of the required characters,
     * and no other characters except for any optional ones.
     * Examples:
     *     misc_AbbrevA("EXACT", "EXACT") == true;
     *     misc_AbbrevA("exact", "EXACT") == true;
     *     misc_AbbrevA("e", "EXACT") == false;
     *     misc_AbbrevA("e", "Exact") == true;
     *     misc_AbbrevA("x", "eXact") == true;
     *     misc_AbbrevA("ext", "eXact") == true;
     *     misc_AbbrevA("xray", "eXact") == false;
     */

    bool        Misc_AbbrevA(
        const
        char            *pPattern,    // Pattern to match it against;
                                    // lowercase letters are optional
        const
        char            *pText        // Text to test
    );


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Misc object if successful, otherwise OBJ_NIL.
     */
    MISC_DATA *     Misc_Alloc (
        void
    );
    
    
    /*! Reverse the bits in the supplied 32-bit value.
     */
    uint32_t        Misc_BitReversal32(
        uint32_t        a
    );


    /*! Reverse the bits in the supplied 64-bit value.
     */
    uint64_t        Misc_BitReversal64(
        uint64_t        x
    );


    OBJ_ID          Misc_Class (
        void
    );
    
    
    /*!
     Exchange the two given data areas (ie data1 -> data2 and data2 -> data1).
     @param     pData1  non-NULL data pointer
     @param     pData2  non-NULL data pointer
     @param     size    number of bytes in each area
     @return    If successful, ERESULT_SUCCESS.  Othewise, an ERESULT_* error
                code.
     */
    ERESULT         Misc_Exchange(
        void            *pData1,
        void            *pData2,
        uint32_t        size
    );


    /*! Compute even parity given a value.
     @param     value   integer value of which we need the parity for
     @return    true if even parity, otherwise false.
     */

    bool            Misc_IsEvenParity32(
        uint32_t        value
    );

    bool            Misc_IsEvenParity16(
        uint16_t        value
    );

    bool            Misc_IsEvenParity8(
        uint8_t         value
    );


    // Simple but slow routine to check if a number is prime.
    bool            Misc_IsPrime(
        uint64_t        amt
    );


    MISC_DATA *     Misc_New (
        void
    );
    
    
#ifdef  MISC_JSON_SUPPORT
    MISC_DATA *   Misc_NewFromJsonString (
        ASTR_DATA       *pString
    );

    MISC_DATA *   Misc_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


    /*!
     * PatternMatch() is a generalized procedure for working with "wild card"
     * names using the '*' and '?' conventions.  It is superior to the wild
     * card matcher provided in the CP/M BDOS in that it will allow operating
     * on named objects other than files.  It also will allow (and process
     * correctly) asterisks anywhere in the pattern; the pattern "*1.ASM" will
     * find any ".ASM" files whose names end in 1, no matter how long the names
     * are.
     *
     * There are two calling sequences for PatternMatch().  In the first, one
     * is interested merely in whether or not a name matches a pattern.  In
     * this calling sequence, the name is passed as the second argument, and
     * the pattern (possibly containing question marks and asterisks) is given
     * as the first.  The third argument ("equiv") is NULL, and the fourth
     * ("newname") need not be supplied.
     *
     * In the second calling sequence, the user also wishes to make an output
     * file name from the input name, in order to process requests like
     *     PIP *.BAK=*.C
     * In this case, the first two arguments are as above.  The third argument
     * "equiv" is the pattern to be used for the output name ("*.BAK" in the
     * example) and the fourth is a pointer to a character vector which will
     * receive the name.
     *
     * Question marks are not permitted in the "equiv" argument, but asterisks
     * are.  Each asterisk in the "equiv" string matches either (1) a single
     * asterisk in the input string, or (2) any number of consecutive question
     * marks in the input string.
     */
    bool            Misc_PatternMatchA(
        const
        char            *pPattern,          // UTF-8 Pattern String
        const
        char            *pName,             // UTF-8 Name String
        const
        char            *pEquiv,            // UTF-8 Equivalent String
        char            *pNewname           // Optional UTF-8 Output String
    );



    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = misc_ToDebugString(this,4);
     @endcode:
     @param     amt     a power (0 =< amt < 32)
     @return    0 If unsuccessful, othwise a prime number slightly greater than
                2 ** amt (ie 2 to the amt'th power)
     */
    uint32_t        Misc_Pwr2_Prime(
        uint32_t        amt
    );


    uint32_t        Misc_Pwr2_Shift(
        uint32_t        amt
    );



    /*!    Generic Search for an Element in a Sorted Array
     This routine performs a Binary Search on a provided sorted
     array trying to located a specific entry.  It is assumed
     that the array is in ascending order by key and that the
     key is embedded in the table (not a pointer to the key).
     Also, if the array is small, a simple search is performed
     rather than a binary one.
     @param     pKey    Key pointer with same type as key within element
     @param     pArray  Address of Sorted Array
     @param     Num     Number of elements in the Sorted Array
     @param     Width   Size of an element in bytes
     @param     Offset  Offset of the key within an element in bytes
     @param     pCmp    Comparison routine which returns -1 if first
                        key < second key, 0 if keys match and 1 if
                        first key > second key
     @return    If successful, array element pointer; Othwise, NULL.
     */
    void  *         Misc_SearchBinary(
        void            *pKey,
        void            *pArray,
        size_t          Num,
        size_t          Width,
        size_t          Offset,
        int             (*pCmp) (
            void            *,
            void            *
        )                               // Returns -1, 0, 1
    );


    /*!    Generic Search for an Element in a Sorted Array
     This routine performs a Binary Search on a provided sorted
     array trying to located a specific entry.  It is assumed
     that the array is in ascending order by key and that the
     key is a string pointer in each table entry.
     Also, if the array is small, a simple search is performed
     rather than a binary one.
     @param     pKey    Key pointer with same type as key within element
     @param     pArray  Address of Sorted Array
     @param     Num     Number of elements in the Sorted Array
     @param     Width   Size of an element in bytes
     @param     Offset  Offset of the key within an element in bytes
     @return    If successful, array element pointer; Othwise, NULL.
     */
    void  *         Misc_SearchBinaryStrA(
        void            *pKey,
        void            *pArray,
        size_t          Num,
        size_t          Width,
        size_t          Offset
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef MISC_LOG
    /*! @property   Logging
        Allows information and warning messages to be issued for this
        object. Messages will be skipped if Log is not set.
     */
    bool            Misc_setLog (
        MISC_DATA    *this,
        OBJ_ID          pObj
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     Misc_Disable (
        MISC_DATA       *this
    );


    ERESULT     Misc_Enable (
        MISC_DATA       *this
    );

   
    MISC_DATA *   Misc_Init (
        MISC_DATA     *this
    );


    ERESULT     Misc_IsEnabled (
        MISC_DATA       *this
    );
    
 
#ifdef  MISC_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Misc_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Misc_ToJson (
        MISC_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Misc_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Misc_ToDebugString (
        MISC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* MISC_H */

