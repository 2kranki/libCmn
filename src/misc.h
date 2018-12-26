// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Miscellaneous Routines (misc) Header
//****************************************************************
/*
 * Program
 *			Miscellaneous Routines (misc)
 * Purpose
 *			This object provides Miscellaneous Routines which
 *          do not fit into other objects.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/25/2015 Generated
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
#define         MISC_H 1



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct misc_data_s	MISC_DATA;

    typedef struct misc_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fatFCB_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(FATFCB_DATA *);
    } MISC_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the misc including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    MISC_DATA *     misc_Alloc(
        void
    );
    
    
    MISC_DATA *     misc_New(
        void
    );
    
    
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
    
    bool        misc_AbbrevA(
        const
        char            *pPattern,	// Pattern to match it against;
                                    // lowercase letters are optional
        const
        char            *pText		// Text to test
    );
    
    
    /*! Reverse the bits in the supplied 32-bit value.
     */
    uint32_t        misc_BitReversal32(
        uint32_t        a
    );
    

    /*! Reverse the bits in the supplied 64-bit value.
     */
    uint64_t        misc_BitReversal64(
        uint64_t        x
    );
    
    
    /*! Compute even parity given a value.
     @param     value   integer value of which we need the parity for
     @return    true if even parity, otherwise false.
     */
    
    bool            misc_ComputeEvenParity32(
        uint32_t        value
    );
    
    bool            misc_ComputeEvenParity16(
        uint16_t        value
    );
    
    bool            misc_ComputeEvenParity8(
        uint8_t         value
    );
    
    
    /*!
     Exchange the two given data areas (ie data1 -> data2 and data2 -> data1).
     @param     pData1  non-NULL data pointer
     @param     pData2  non-NULL data pointer
     @param     size    number of bytes in each area
     @return    If successful, ERESULT_SUCCESS.  Othewise, an ERESULT_* error
                code.
     */
    ERESULT         misc_Exchange(
        void            *pData1,
        void            *pData2,
        uint32_t        size
    );
    
    
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
    bool            misc_PatternMatchA(
        const
        char            *pPattern,          // UTF-8 Pattern String
        const
        char            *pName,             // UTF-8 Name String
        const
        char            *pEquiv,            // UTF-8 Equivalent String
        char            *pNewname           // Optional UTF-8 Output String
    );
    
    
    
    uint32_t        misc_Pwr2_Shift(
        uint32_t        amt
    );
    
    
    


    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*! 
     * Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    MISC_DATA *   misc_Init(
        MISC_DATA     *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = misc_ToDebugString(this,4);
     @endcode:
     @param     this    MISC object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object when you are done
                with it.
     */
    ASTR_DATA *    misc_ToDebugString(
        MISC_DATA       *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MISC_H */

