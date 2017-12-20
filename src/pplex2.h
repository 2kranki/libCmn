// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//    Preprocessor Lexical Analyzer - Phase 2 (pplex2) Header
//****************************************************************
/*
 * Program
 *			Preprocessor Lexical Analyzer - Phase 2 (pplex2)
 * Purpose
 *			This object scans a source stream breaking it up into
 *          small pieces of strings called tokens. Nothing is con-
 *          verted to another format. Only strings are returned in
 *          the tokens and in a string table.
 *
 *          There are two primary methods for the scanner, NextToken()
 *          and PushToken(). NextToken() returns the address of the
 *          next token scanned from the source. The token should not
 *          be released. If long term retention of it is needed, 
 *          simply make a copy of it and use that. The next call to
 *          NextToken() will overwrite the prior token.  PushToken()
 *          pushes the token given by making a copy of it and adding
 *          it to an internal queue. The queue is maintained in FIFO
 *          order. When NextToken() is called, it always returns the
 *          bottom of the queue if it has items in it.
 *
 * Remarks
 *	1.      The input to this phase is srcFile Tokens. The output
 *          is PPLEX Tokens.
 *  2.      Keywords are not handled here. They should be handled
 *          in the next phase of the lexer.
 *
 * History
 *	05/25/2015 Generated
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
#include        <srcFiles.h>
#include        <szTbl.h>
#include        <token.h>


#ifndef         PPLEX2_H
#define         PPLEX2_H 1



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct pplex2_data_s	PPLEX2_DATA; // Inherits from LEX

    typedef struct pplex2_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in consumer_object.c.
        // Properties:
        // Methods:
    } PPLEX2_VTBL;
    
    

    
    
    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    PPLEX2_DATA *   pplex2_Alloc(
        void
    );
    
    
    PPLEX2_DATA *   pplex2_New(
        uint16_t        k
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    
    // Comments is a flag to indicate if comments should be
    // included in the token stream. The default is false
    // which excludes comments from the token stream.
    bool            pplex2_getComments(
        PPLEX2_DATA     *this
    );
    
    bool            pplex2_setComments(
        PPLEX2_DATA     *this,
        bool            value
    );
    
    
    bool            pplex2_setKwdSelection(
        PPLEX2_DATA     *this,
        uint16_t        value
    );
    
    
    bool            pplex2_getReturnNL(
        PPLEX2_DATA     *this
    );
    
    bool            pplex2_setReturnNL(
        PPLEX2_DATA     *this,
        bool            value
    );
    
    
    bool            pplex2_getReturnWS(
        PPLEX2_DATA     *this
    );
    
    bool            pplex2_setReturnWS(
        PPLEX2_DATA     *this,
        bool            value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    PPLEX2_DATA *   pplex2_Init(
        PPLEX2_DATA     *this,
        uint16_t        k
    );

    
    
#ifdef	__cplusplus
}
#endif

#endif	/* PPLEX2_H */

