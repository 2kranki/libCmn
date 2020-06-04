// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//    Preprocessor Lexical Analyzer - Phase 1 (pplex1) Header
//****************************************************************
/*
 * Program
 *			Preprocessor Lexical Analyzer - Phase 1 (pplex1)
 * Purpose
 *			This object serves as a filter to convert all C
 *          trigraphs back into normal C letters. Most source
 *          tokens are just passed through this. When a trigraph
 *          is recognized, it is converted into one token from
 *          three input tokens.
 *
 * Remarks
 *	1.      The input to this phase is srcFile Tokens. The output
 *          is also srcFile Tokens unlike the following phases
 *          which output PPLEX Tokens.
 *
 * History
 *	09/15/2015 Generated
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
#include        <Token.h>

#ifndef         PPLEX1_H
#define         PPLEX1_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct pplex1_data_s	PPLEX1_DATA; // Inherits from LEX

    typedef struct pplex1_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in consumer_object.c.
        // Properties:
        // Methods:
    } PPLEX1_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    PPLEX1_DATA *     pplex1_Alloc(
        void
    );
    
    
    PPLEX1_DATA *     pplex1_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    LEX_DATA *      pplex1_getLex(
        PPLEX1_DATA    *this
    );


    /*! If true, then NL tokens are passed to the user of this system.
     Otherwise, the default is that NL tokens are skipped over.
     @warning   This must be done before you create the lexers.
     */
    bool            pplex1_getReturnNL(
        PPLEX1_DATA     *this
    );

    bool            pplex1_setReturnNL(
        PPLEX1_DATA     *this,
        bool            fValue
    );


    /*! If true, then White-Space tokens (which include comments) are passed
     to the user of this system.  Otherwise, the default is that White-Space
     tokens are skipped over.
     @warning   This must be done before you create the lexers.
     */
    bool            pplex1_getReturnWS(
        PPLEX1_DATA     *this
    );

    bool            pplex1_setReturnWS(
        PPLEX1_DATA     *this,
        bool            fValue
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    PPLEX1_DATA *   pplex1_Init(
        PPLEX1_DATA     *this
    );


    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     pplex1_ToDebugString(
        PPLEX1_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* PPLEX1_H */

