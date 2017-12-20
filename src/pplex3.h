// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//    Preprocessor Lexical Analyzer - Phase 3 (pplex3) Header
//****************************************************************
/*
 * Program
 *			Preprocessor Lexical Analyzer - Phase 3 (pplex3)
 * Purpose
 *			This object uses the output of the phase 2 preprocessor
 *          to further analyze and combine tokens produced by it
 *          forming in some cases combined tokens representing
 *          keywords, combined operators and some literals.
 *
 *          The output of this phase should be good to reqpresent
 *          Objective C/C lexical tokens.
 *
 * Remarks
 *	1.      The input to this phase is PPLEX Tokens. The output
 *          is PPLEX Tokens.
 *
 * History
 *	09/17/2015 Generated
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
#include        <pplex.h>


#ifndef         PPLEX3_H
#define         PPLEX3_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct pplex3_data_s	PPLEX3_DATA; // Inherits from LEX

    typedef struct pplex3_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in consumer_object.c.
        // Properties:
        // Methods:
    } PPLEX3_VTBL;
    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    PPLEX3_DATA *     pplex3_Alloc(
        void
    );
    
    
    PPLEX3_DATA *     pplex3_New(
        uint16_t        k
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            pplex3_setKwdSelection(
        PPLEX3_DATA     *this,
        uint16_t        value
    );

    
    bool            pplex3_setParseFunction(
        PPLEX3_DATA     *this,
        bool            (*pUserExit)(OBJ_ID, TOKEN_DATA *),
        OBJ_ID          pUserObj
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the C keywords to the szTbl Shared object.
     @param     this    pplex3 object pointer
     @return    If successful, ERESULT_SUCCESS other an ERESULT_* error
     */
    ERESULT         pplex3_AddCToSzTbl(
        PPLEX3_DATA     *this
    );
    
    
    PPLEX3_DATA *   pplex3_Init(
        PPLEX3_DATA     *this,
        uint16_t        k
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = pplex3_ToDebugString(this,4);
     @endcode
     @param     this    pplex3 object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     pplex3_ToDebugString(
        PPLEX3_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* PPLEX3_H */

