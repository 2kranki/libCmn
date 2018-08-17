// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   cmdutl.c
 *	Generated 10/18/2015 19:44:45
 *
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include        <cmdutl_internal.h>
#include        <ascii.h>
#include        <AStr.h>
#include        <AStrArray.h>
#include        <nodeArray.h>
#include        <nodeHash.h>
#include        <scanner.h>
#include        <srcErrors.h>
#include        <trace.h>
#include        <utf8.h>
#include        <W32Str.h>
#include        <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /* ParseCmdStr() sets up an ArgC/ArgV type array given
     * a command line string.
     */
#ifdef XYZZY
    static
    bool			cmdutl_ParseCmdStr(
        CMDUTL_DATA		*this,
        char            *pCmdStr
    )
    {
        uint16_t        cbSize;
        int             Num = 0;
        char            *pCurCmd;
        char            quote;
        
        // Do initialization.
        if( pCmdStr == NULL )
            return( false );
        
        // Analyze input string to calculate array needed.
        this->cArg = 1;
        //TODO: cbSize = 2 * sizeof(char *);
        this->ppArg = (char **)mem_Malloc( cbSize );
#ifdef XYZZY
        if( this->ppArg ) {
            this->flags |= GOT_ARGV;
        }
        else
            return false;
#endif
        *(this->ppArg) = "";     // Set program name.
        
        /* Scan off the each parameter.
         */
        while( *pCmdStr ) {
            pCurCmd = NULL;
            
            // Pass over white space.
            while( *pCmdStr && ((*pCmdStr == ' ') || (*pCmdStr == '\n')
                                || (*pCmdStr == '\r') || (*pCmdStr == '\t')) )
                ++pCmdStr;
            
            // Handle Quoted Arguments.
            if( (*pCmdStr == '\"') || (*pCmdStr == '\'') ) {
                quote = *pCmdStr++;
                pCurCmd = pCmdStr;
                while( *pCmdStr && (*pCmdStr != quote) ) {
                    ++pCmdStr;
                }
                if( *pCmdStr ) {
                    *pCmdStr = '\0';
                    ++pCmdStr;
                }
            }
            
            // Handle Non-Quoted Arguments.
            else if( *pCmdStr ) {
                pCurCmd = pCmdStr;
                // Scan until white space.
                while( *pCmdStr && !((*pCmdStr == ' ') || (*pCmdStr == '\n')
                                     || (*pCmdStr == '\r') || (*pCmdStr == '\t')) ) {
                    ++pCmdStr;
                }
                if( *pCmdStr ) {
                    *pCmdStr = '\0';
                    ++pCmdStr;
                }
            }
            else
                continue;
            
            // Add the command to the array.
            if( pCurCmd ) {
                ++Num;
                this->ppArg = (char **)mem_Realloc( this->ppArg, ((Num + 2) * sizeof(char *)) );
                if( this->ppArg ) {
                    this->ppArg[Num]   = pCurCmd;
                    this->ppArg[Num+1] = NULL;
                    ++this->cArg;
                }
                else
                    return( false );
            }
        }
        
        // Return to caller.
        return true;
    }
#endif
    
    
    
    // Returns the next character from the file as a positive number.
    // If the character returned is negative then it is an ERESULT code.
    W32CHR_T        cmdutl_UnicodeGetc(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        wrkChr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        switch (this->inputType) {
                
            case OBJ_IDENT_ASTR:
                wrkChr = AStr_CharGetW32(this->pAStr, ++this->fileOffset);
                if(EOF == wrkChr) {
                    obj_FlagSet(this, OBJ_FLAG_EOF, true);
                    return EOF; //ERESULT_EOF_ERROR;
                }
                break;
                
            case OBJ_IDENT_FILE:
                wrkChr = fgetwc( this->pFile);
                if( wrkChr == EOF ) {
                    if( feof(this->pFile) ) {
                        obj_FlagSet(this, OBJ_FLAG_EOF, true);
                        return EOF; //ERESULT_EOF_ERROR;
                    }
                    else
                        obj_FlagSet(this, OBJ_FLAG_EOF, true);
                        return EOF; //ERESULT_READ_ERROR;
                }
                break;
                
#ifdef XYZZY
            case OBJ_IDENT_FBSI:
                eRc = fbsi_Getwc(this->pFbsi, &wrkChr );
                if (ERESULT_FAILURE(eRc)) {
                    chr = EOF;
                }
                break;
#endif
                
#ifdef XYZZY
            case OBJ_IDENT_U8ARRAY:
                eRc = srcFile_u8ArrayGetc(this, &wrkChr);
                if (ERESULT_FAILURE(eRc)) {
                    chr = EOF;
                }
                break;
#endif
                
            case OBJ_IDENT_W32STR:
                wrkChr = W32Str_CharGetW32(this->pWStr, ++this->fileOffset );
                break;
                
            default:
                wrkChr = EOF;
                break;
        }
        
        if( (wrkChr >= ' ') && (wrkChr < ASCII_DEL) )
            ;
        else if( (wrkChr == ASCII_LF) || (wrkChr == ASCII_CR) )
            ;
        else if( wrkChr == ASCII_CPM_EOF ) {
            while ((wrkChr = fgetwc(this->pFile)) != EOF) {
            }
            obj_FlagSet(this, OBJ_FLAG_EOF, true);
            return ERESULT_EOF_ERROR;
        }
        else if( wrkChr == ASCII_TAB )
            ;
        else if (wrkChr > 128)
            ;
        else {
            return ERESULT_INVALID_DATA;
        }
        
        // Return to caller.
        return wrkChr;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  A l p h a  a-z A-Z
    //---------------------------------------------------------------
    
    W32CHR_T        cmdutl_ParseAlpha(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        chr = cmdutl_InputLookAhead(this, 1);
        
        if( (chr >= 'a') && (chr <= 'z') ) {
            cmdutl_AppendCharToField(this, chr);
            cmdutl_InputAdvance(this, 1);
            chr -= '0';
        }
        else if( (chr >= 'A') && (chr <= 'Z') ) {
            cmdutl_AppendCharToField(this, chr);
            cmdutl_InputAdvance(this, 1);
            chr -= '0';
        }
        else {
            chr = -1;
        }
        
        // Return to caller.
        return chr;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  A r g
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseArg(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        OBJ_ID          pChild = OBJ_NIL;
        //bool            fRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        cmdutl_ParseWS(this);
        
        pArray = nodeArray_New( );
        if (pArray == OBJ_NIL) {
            //FIXME: Add proper error
#ifdef XYZZY
            srcErrors_AddFatalFromToken(
                                        OBJ_NIL,
                                        pToken,
                                        "Expecting ':'"
                                        );
            eResult_ErrorFatalFLC(
                                  eResult_Shared(),
                                  path_getData(this->pPath),
                                  this->lineNo,
                                  this->colNo,
                                  "Out of Memory"
                                  );
#endif
            return pNode;
        }
        
        pChild = cmdutl_ParseValue(this);
        if (pChild) {
            nodeArray_AppendNode(pArray, pChild, NULL);
            obj_Release(pChild);
        }
        else {
            obj_Release(pArray);
            return OBJ_NIL;
        }
        
        for (;;) {
            cmdutl_ParseWS(this);
            chr = cmdutl_InputLookAhead(this, 1);
            if( chr == ',' ) {
                cmdutl_InputAdvance(this, 1);
            }
            else
                break;
            pChild = cmdutl_ParseValue(this);
            if (pChild) {
                nodeArray_AppendNode(pArray, pChild, NULL);
                obj_Release(pChild);
            }
            else {
                //FIXME: Add proper error
#ifdef XYZZY
                srcErrors_AddFatalFromToken(
                                            OBJ_NIL,
                                            pToken,
                                            "Expecting ':'"
                                            );
                eResult_ErrorFatalFLC(
                                      eResult_Shared(),
                                      path_getData(this->pPath),
                                      this->lineNo,
                                      this->colNo,
                                      "Expecting a value, but found %c(0x%02X)",
                                      chr,
                                      chr
                                      );
#endif
            }
        }
        
        cmdutl_ParseWS(this);
        chr = cmdutl_InputLookAhead(this, 1);
        if( chr == ']' ) {
            cmdutl_InputAdvance(this, 1);
        }
        else {
            //FIXME: Add proper error
#ifdef XYZZY
            srcErrors_AddFatalFromToken(
                                        OBJ_NIL,
                                        pToken,
                                        "Expecting ':'"
                                        );
            eResult_ErrorFatalFLC(
                                  eResult_Shared(),
                                  path_getData(this->pPath),
                                  this->lineNo,
                                  this->colNo,
                                  "Expecting ']', but found %c(0x%02X)",
                                  chr,
                                  chr
                                  );
#endif
        }
        
        pNode = node_NewWithUTF8AndClass("array", 0, pArray);
        obj_Release(pArray);
        if (pNode == OBJ_NIL) {
            //FIXME: Error Fatal
            return pNode;
        }
        
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  A r g s
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseArgs(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        OBJ_ID          pChild = OBJ_NIL;
        //bool            fRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        cmdutl_ParseWS(this);
        
        pArray = nodeArray_New( );
        if (pArray == OBJ_NIL) {
            //FIXME: Add proper error
#ifdef XYZZY
            srcErrors_AddFatalFromToken(
                                        OBJ_NIL,
                                        pToken,
                                        "Expecting ':'"
                                        );
            eResult_ErrorFatalFLC(
                                  eResult_Shared(),
                                  path_getData(this->pPath),
                                  this->lineNo,
                                  this->colNo,
                                  "Out of Memory"
                                  );
#endif
            return pNode;
        }
        
        pChild = cmdutl_ParseValue(this);
        if (pChild) {
            nodeArray_AppendNode(pArray, pChild, NULL);
            obj_Release(pChild);
        }
        else {
            obj_Release(pArray);
            return OBJ_NIL;
        }
        
        for (;;) {
            cmdutl_ParseWS(this);
            chr = cmdutl_InputLookAhead(this, 1);
            if( chr == ',' ) {
                cmdutl_InputAdvance(this, 1);
            }
            else
                break;
            pChild = cmdutl_ParseValue(this);
            if (pChild) {
                nodeArray_AppendNode(pArray, pChild, NULL);
                obj_Release(pChild);
            }
            else {
                //FIXME: Add proper error
#ifdef XYZZY
                srcErrors_AddFatalFromToken(
                                            OBJ_NIL,
                                            pToken,
                                            "Expecting ':'"
                                            );
                eResult_ErrorFatalFLC(
                                      eResult_Shared(),
                                      path_getData(this->pPath),
                                      this->lineNo,
                                      this->colNo,
                                      "Expecting a value, but found %c(0x%02X)",
                                      chr,
                                      chr
                                      );
#endif
            }
        }
        
        cmdutl_ParseWS(this);
        chr = cmdutl_InputLookAhead(this, 1);
        if( chr == ']' ) {
            cmdutl_InputAdvance(this, 1);
        }
        else {
            //FIXME: Add proper error
#ifdef XYZZY
            srcErrors_AddFatalFromToken(
                                        OBJ_NIL,
                                        pToken,
                                        "Expecting ':'"
                                        );
            eResult_ErrorFatalFLC(
                                  eResult_Shared(),
                                  path_getData(this->pPath),
                                  this->lineNo,
                                  this->colNo,
                                  "Expecting ']', but found %c(0x%02X)",
                                  chr,
                                  chr
                                  );
#endif
        }
        
        pNode = node_NewWithUTF8AndClass("array", 0, pArray);
        obj_Release(pArray);
        if (pNode == OBJ_NIL) {
            //FIXME: Error Fatal
            return pNode;
        }
        
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  A r r a y
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseArray(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        OBJ_ID          pChild = OBJ_NIL;
        //bool            fRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        cmdutl_ParseWS(this);
        chr = cmdutl_InputLookAhead(this, 1);
        if( chr == '[' ) {
            cmdutl_InputAdvance(this, 1);
        }
        else {
            return OBJ_NIL;
        }
        
        pArray = nodeArray_New( );
        if (pArray == OBJ_NIL) {
            //FIXME: Add proper error
#ifdef XYZZY
            srcErrors_AddFatalFromToken(
                                        OBJ_NIL,
                                        pToken,
                                        "Expecting ':'"
                                        );
            eResult_ErrorFatalFLC(
                eResult_Shared(),
                path_getData(this->pPath),
                this->lineNo,
                this->colNo,
                "Out of Memory"
            );
#endif
            return pNode;
        }
        
        pChild = cmdutl_ParseValue(this);
        if (pChild) {
            nodeArray_AppendNode(pArray, pChild, NULL);
            obj_Release(pChild);
        }
        else {
            obj_Release(pArray);
            return OBJ_NIL;
        }
        
        for (;;) {
            cmdutl_ParseWS(this);
            chr = cmdutl_InputLookAhead(this, 1);
            if( chr == ',' ) {
                cmdutl_InputAdvance(this, 1);
            }
            else
                break;
            pChild = cmdutl_ParseValue(this);
            if (pChild) {
                nodeArray_AppendNode(pArray, pChild, NULL);
                obj_Release(pChild);
            }
            else {
                //FIXME: Add proper error
#ifdef XYZZY
                srcErrors_AddFatalFromToken(
                                            OBJ_NIL,
                                            pToken,
                                            "Expecting ':'"
                                            );
                eResult_ErrorFatalFLC(
                    eResult_Shared(),
                    path_getData(this->pPath),
                    this->lineNo,
                    this->colNo,
                    "Expecting a value, but found %c(0x%02X)",
                    chr,
                    chr
                );
#endif
            }
        }
        
        cmdutl_ParseWS(this);
        chr = cmdutl_InputLookAhead(this, 1);
        if( chr == ']' ) {
            cmdutl_InputAdvance(this, 1);
        }
        else {
            //FIXME: Add proper error
#ifdef XYZZY
            srcErrors_AddFatalFromToken(
                                        OBJ_NIL,
                                        pToken,
                                        "Expecting ':'"
                                        );
            eResult_ErrorFatalFLC(
                eResult_Shared(),
                path_getData(this->pPath),
                this->lineNo,
                this->colNo,
                "Expecting ']', but found %c(0x%02X)",
                chr,
                chr
            );
#endif
        }
        
        pNode = node_NewWithUTF8AndClass("array", 0, pArray);
        obj_Release(pArray);
        if (pNode == OBJ_NIL) {
            //FIXME: Error Fatal
            return pNode;
        }
        
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                    P a r s e  C h a r s
    //---------------------------------------------------------------
    
    // The first character of the name has already been parsed, but
    // not advanced. So, we just keep accumulating the proper letters
    // until there are no more that are acceptable.
    
    bool            cmdutl_ParseChrCon(
        CMDUTL_DATA     *this,
        W32CHR_T        ending
    )
    {
        W32CHR_T        chr;
        uint32_t        i;
        W32CHR_T        wrk;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        chr = cmdutl_InputLookAhead(this, 1);
        if (chr == ending) {
            return false;
        }
        if ( chr == '\\') {
            chr = cmdutl_InputAdvance(this, 1);
            switch (chr) {
                    
#ifdef XYZZY
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                    cmdutl_AppendCharToField(this, chr);
                    cmdutl_InputAdvance(this, 1);
                    for (i=0; i<2; ++i) {
                        wrk = 0;
                        chr = cmdutl_ParseDigitOctal(this);
                        if (chr >= 0) {
                            wrk = (wrk << 3) | chr;
                        }
                        else {
                            chr = cmdutl_InputLookAhead(this, 1);
                            eResult_ErrorFatalFLC(
                                eResult_Shared(),
                                path_getData(this->pPath),
                                this->lineNo,
                                this->colNo,
                                "Invalid octal char, %c(0x%02X)",
                                chr,
                                chr
                            );
                        }
                    }
                    return true;
#endif
                    
                case 'b':
                    cmdutl_AppendCharToField(this, '\b');
                    cmdutl_InputAdvance(this, 1);
                    return true;
                    
                case 'f':
                    cmdutl_AppendCharToField(this, '\f');
                    cmdutl_InputAdvance(this, 1);
                    return true;
                    
                case 'n':
                    cmdutl_AppendCharToField(this, '\n');
                    cmdutl_InputAdvance(this, 1);
                    return true;
                    
                case 'r':
                    cmdutl_AppendCharToField(this, '\r');
                    cmdutl_InputAdvance(this, 1);
                    return true;
                    
                case 't':
                    cmdutl_AppendCharToField(this, '\t');
                    cmdutl_InputAdvance(this, 1);
                    return true;

#ifdef XYZZY
                case 'v':
                    cmdutl_AppendCharToField(this, '\v');
                    cmdutl_InputAdvance(this, 1);
                    return true;
#endif
                    
                case '\\':
                    cmdutl_AppendCharToField(this, '\\');
                    cmdutl_InputAdvance(this, 1);
                    return true;
                    
                case '/':
                    cmdutl_AppendCharToField(this, '/');
                    cmdutl_InputAdvance(this, 1);
                    return true;
                    
                case '\'':
                    cmdutl_AppendCharToField(this, '\'');
                    cmdutl_InputAdvance(this, 1);
                    return true;
                    
                case '"':
                    cmdutl_AppendCharToField(this, chr);
                    cmdutl_InputAdvance(this, 1);
                    return true;
                    
                case 'u':
                    cmdutl_AppendCharToField(this, chr);
                    cmdutl_InputAdvance(this, 1);
                    for (i=0; i<4; ++i) {
                        wrk = 0;
                        chr = cmdutl_ParseDigitHex(this);
                        if (chr >= 0) {
                            wrk = (wrk << 4) | chr;
                        }
                        else {
                            chr = cmdutl_InputLookAhead(this, 1);
                            //FIXME: Add proper error
#ifdef XYZZY
                            srcErrors_AddFatalFromToken(
                                                        OBJ_NIL,
                                                        pToken,
                                                        "Expecting ':'"
                                                        );
                            eResult_ErrorFatalFLC(
                                eResult_Shared(),
                                path_getData(this->pPath),
                                this->lineNo,
                                this->colNo,
                                "Invalid hexadecimal char, %c(0x%02X)",
                                chr,
                                chr
                            );
#endif
                        }
                    }
                    break;
                    
                default:
                    chr = cmdutl_InputLookAhead(this, 1);
                    //FIXME: Add proper error
#ifdef XYZZY
                    srcErrors_AddFatalFromToken(
                                                OBJ_NIL,
                                                pToken,
                                                "Expecting ':'"
                                                );
                    eResult_ErrorFatalFLC(
                                          eResult_Shared(),
                                          path_getData(this->pPath),
                                          this->lineNo,
                                          this->colNo,
                                          "Invalid char after \\, %c(0x%02X)",
                                          chr,
                                          chr
                    );
#endif
                    break;
            }
        }
        else {
            cmdutl_AppendCharToField(this, chr);
            cmdutl_InputAdvance(this, 1);
        }
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  C m d S t r
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseCmdStr(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        NODE_DATA       *pNode = OBJ_NIL;
        //OBJ_ID          pChild = OBJ_NIL;
        //bool            fRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        cmdutl_ParseWS(this);
        
        pNode = cmdutl_ParseArgs(this);
        if( OBJ_NIL == pNode ) {
            return pNode;
        }
        
        cmdutl_ParseWS(this);
        if(!cmdutl_ParseEOF(this)) {
            chr = cmdutl_InputLookAhead(this, 1);
            //FIXME: Add proper error
#ifdef XYZZY
            srcErrors_AddFatalFromToken(
                                        OBJ_NIL,
                                        pToken,
                                        "Expecting ':'"
                                        );
            eResult_ErrorFatalFLC(
                                  eResult_Shared(),
                                  path_getData(this->pPath),
                                  this->lineNo,
                                  this->colNo,
                                  "Expecting EOF, but found %c(0x%02X)",
                                  chr,
                                  chr
                                  );
#endif
        }
        
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  D i g i t  0-9
    //---------------------------------------------------------------
    
    W32CHR_T        cmdutl_ParseDigit0To9(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        chr = cmdutl_InputLookAhead(this, 1);
        
        if( (chr >= '0') && (chr <= '9') ) {
            cmdutl_AppendCharToField(this, chr);
            cmdutl_InputAdvance(this, 1);
            chr -= '0';
        }
        else {
            chr = -1;
        }
        
        // Return to caller.
        return chr;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  D i g i t  1-9
    //---------------------------------------------------------------
    
    W32CHR_T        cmdutl_ParseDigit1To9(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        chr = cmdutl_InputLookAhead(this, 1);
        
        if( (chr >= '1') && (chr <= '9') ) {
            cmdutl_AppendCharToField(this, chr);
            cmdutl_InputAdvance(this, 1);
            chr -= '0';
        }
        else {
            chr = -1;
        }
        
        // Return to caller.
        return chr;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  D i g i t  H e x
    //---------------------------------------------------------------
    
    W32CHR_T        cmdutl_ParseDigitHex(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        chr = cmdutl_InputLookAhead(this, 1);
        
        if( (chr >= '0') && (chr <= '9') ) {
            cmdutl_InputAdvance(this, 1);
            chr -= '0';
        }
        else if( (chr >= 'A') && (chr <= 'F') ) {
            cmdutl_InputAdvance(this, 1);
            chr = chr - 'A' + 10;
        }
        else if( (chr >= 'a') && (chr <= 'f') ) {
            cmdutl_InputAdvance(this, 1);
            chr = chr - 'a' + 10;
        }
        else {
            chr = -1;
        }
        
        // Return to caller.
        return chr;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  D i g i t  O c t a l
    //---------------------------------------------------------------
    
    W32CHR_T        cmdutl_ParseDigitOctal(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        chr = cmdutl_InputLookAhead(this, 1);
        
        if( (chr >= '0') && (chr <= '7') ) {
            cmdutl_InputAdvance(this, 1);
            chr -= '0';
        }
        else {
            chr = -1;
        }
        
        // Return to caller.
        return chr;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  E O F
    //---------------------------------------------------------------
    
    bool            cmdutl_ParseEOF(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        cmdutl_ParseWS(this);
        chr = cmdutl_InputLookAhead(this, 1);
        if (chr < 0) {
            cmdutl_InputAdvance(this, 1);
            return true;
        }
        
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //               P a r s e  F i l e  O b j e c t
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseFileObject(
        CMDUTL_DATA       *this
    )
    {
        W32CHR_T        chr;
        NODE_DATA       *pNode;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        pNode = cmdutl_ParseArgs(this);
        if( OBJ_NIL == pNode ) {
            return pNode;
        }
        
        cmdutl_ParseWS(this);
        if(!cmdutl_ParseEOF(this)) {
            chr = cmdutl_InputLookAhead(this, 1);
            //FIXME: Add proper error
#ifdef XYZZY
            srcErrors_AddFatalFromToken(
                                        OBJ_NIL,
                                        pToken,
                                        "Expecting ':'"
                                        );
            eResult_ErrorFatalFLC(
                eResult_Shared(),
                path_getData(this->pPath),
                this->lineNo,
                this->colNo,
                "Expecting EOF, but found %c(0x%02X)",
                chr,
                chr
            );
#endif
        }
        
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  H a s h
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseHash(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        NODE_DATA       *pNode = OBJ_NIL;
        NODEHASH_DATA   *pHash = OBJ_NIL;
        NODE_DATA       *pChild;
        ERESULT         eRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        cmdutl_ParseWS(this);
        chr = cmdutl_InputLookAhead(this, 1);
        if( chr == '{' ) {
            cmdutl_InputAdvance(this, 1);
        }
        else {
            return pNode;
        }
        
        pHash = nodeHash_New(NODEHASH_TABLE_SIZE_XXXSMALL);
        if (pHash == OBJ_NIL) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        pChild = cmdutl_ParsePair(this);
        if (pChild) {
            eRc = nodeHash_Add(pHash, pChild);
            obj_Release(pChild);
            pChild = OBJ_NIL;
            for (;;) {
                cmdutl_ParseWS(this);
                chr = cmdutl_InputLookAhead(this, 1);
                if( chr == ',' ) {
                    cmdutl_InputAdvance(this, 1);
                }
                else
                    break;
                pChild = cmdutl_ParsePair(this);
                if (pChild) {
                    eRc = nodeHash_Add(pHash, pChild);
                    obj_Release(pChild);
                    pChild = OBJ_NIL;
                }
                else {
                    //FIXME: Add proper error
#ifdef XYZZY
                    srcErrors_AddFatalFromToken(
                                                OBJ_NIL,
                                                pToken,
                                                "Expecting ':'"
                                                );
                    eResult_ErrorFatalFLC(
                        eResult_Shared(),
                        path_getData(this->pPath),
                        this->lineNo,
                        this->colNo,
                        "Expecting a value, but found %c(0x%02X)",
                        chr,
                        chr
                    );
#endif
                }
            }
        }
        
        cmdutl_ParseWS(this);
        chr = cmdutl_InputLookAhead(this, 1);
        if( chr == '}' ) {
            cmdutl_InputAdvance(this, 1);
        }
        else {
            //FIXME: Add proper error
#ifdef XYZZY
            srcErrors_AddFatalFromToken(
                                        OBJ_NIL,
                                        pToken,
                                        "Expecting ':'"
                                        );
            eResult_ErrorFatalFLC(
                eResult_Shared(),
                path_getData(this->pPath),
                this->lineNo,
                this->colNo,
                "Expecting '}', but found %c(0x%02X)",
                chr,
                chr
            );
#endif
            obj_Release(pNode);
            pNode = OBJ_NIL;
            return pNode;
        }
        
        pNode = node_NewWithUTF8AndClass("hash", 0, pHash);
        obj_Release(pHash);
        pHash = OBJ_NIL;
        if (pNode == OBJ_NIL) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  K e y  W o r d
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseKeyWord(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        NODE_DATA       *pNode = OBJ_NIL;
        FALSE_DATA      *pFalse = false_New();
        NULL_DATA       *pNull = null_New();
        TRUE_DATA       *pTrue = true_New();
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this,"%s:\n", __func__);
        this->lenFld = 0;
        this->pFld[0] = 0;
        
        cmdutl_ParseWS(this);
        while ((chr=cmdutl_ParseAlpha(this)) > 0) {
        }
        str_ToLowerW32(this->pFld);
        if (this->lenFld) {
            if (0 == utf8_StrCmpAW32("false", this->pFld)) {
                pNode = node_NewWithUTF8AndClass("false", 0, pFalse);
            }
            else if (0 == utf8_StrCmpAW32("null", this->pFld)) {
                pNode = node_NewWithUTF8AndClass("null", 0, pNull);
            }
            else if (0 == utf8_StrCmpAW32("true", this->pFld)) {
                pNode = node_NewWithUTF8AndClass("true", 0, pTrue);
            }
            else {
                //FIXME: Add proper error
#ifdef XYZZY
                srcErrors_AddFatalFromToken(
                                            OBJ_NIL,
                                            pToken,
                                            "Expecting ':'"
                                            );
                eResult_ErrorFatalFLC(
                    eResult_Shared(),
                    path_getData(this->pPath),
                    this->lineNo,
                    this->colNo,
                    "Expecting false, null or true, but found %c(0x%02X)",
                    chr,
                    chr
                );
#endif
            }
        }
        
        obj_Release(pFalse);
        obj_Release(pNull);
        obj_Release(pTrue);
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  N u m b e r
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseNumber(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        NODE_DATA       *pNode = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        bool            fRc = false;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->lenFld = 0;
        this->pFld[0] = 0;
        
        cmdutl_ParseWS(this);
        chr = cmdutl_InputLookAhead(this, 1);
        if( chr == '-' ) {
            cmdutl_AppendCharToField(this, chr);
            cmdutl_InputAdvance(this, 4);
        }
        if( chr == '0' ) {
            cmdutl_AppendCharToField(this, chr);
            chr = cmdutl_InputAdvance(this, 4);
            fRc = true;
        }
        else if ( cmdutl_ParseDigit1To9(this) >= 0) {
            while (cmdutl_ParseDigit0To9(this) >= 0) {
            }
            fRc = true;
        }
        
        if (!fRc) {
            return OBJ_NIL;
        }
        
        chr = cmdutl_InputLookAhead(this, 1);
        if( chr == '.' ) {
            cmdutl_AppendCharToField(this, chr);
            cmdutl_InputAdvance(this, 4);
            if (cmdutl_ParseDigit0To9(this) > 0)
                ;
            else {
                //FIXME: Add proper error
#ifdef XYZZY
                srcErrors_AddFatalFromToken(
                                            OBJ_NIL,
                                            pToken,
                                            "Expecting ':'"
                                            );
                eResult_ErrorFatalFLC(
                    eResult_Shared(),
                    path_getData(this->pPath),
                    this->lineNo,
                    this->colNo,
                    "Expecting 0-9, but found %c(0x%02X)",
                    chr,
                    chr
                );
#endif
            }
            while (cmdutl_ParseDigit0To9(this) > 0) {
            }
        }
        
        chr = cmdutl_InputLookAhead(this, 1);
        if( (chr == 'e') || (chr == 'E') ) {
            cmdutl_AppendCharToField(this, chr);
            cmdutl_InputAdvance(this, 4);
            if( (chr == '-') || (chr == '+') ) {
                cmdutl_AppendCharToField(this, chr);
                cmdutl_InputAdvance(this, 4);
            }
            if (cmdutl_ParseDigit0To9(this) > 0)
                ;
            else {
                //FIXME: Add proper error
#ifdef XYZZY
                srcErrors_AddFatalFromToken(
                                            OBJ_NIL,
                                            pToken,
                                            "Expecting ':'"
                                            );
                eResult_ErrorFatalFLC(
                    eResult_Shared(),
                    path_getData(this->pPath),
                    this->lineNo,
                    this->colNo,
                    "Expecting 0-9, but found %c(0x%02X)",
                    chr,
                    chr
                );
#endif
            }
            while (cmdutl_ParseDigit0To9(this) > 0) {
            }
        }

        if (fRc) {
            pStr = AStr_NewW32(this->pFld);
            if (pStr) {
                pNode = node_NewWithUTF8AndClass("number", 0, pStr);
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //          P a r s e  N a m e - V a l u e  P a i r
    //---------------------------------------------------------------
    
    // We scan the Name as a string and return a node with the name
    // being that string and the value being the data portion of the
    // node.
    
    NODE_DATA *     cmdutl_ParsePair(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        NODE_DATA       *pData = OBJ_NIL;
        NODE_DATA       *pName = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        const
        char            *pszName;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        pName = cmdutl_ParseString(this);
        if (pName == OBJ_NIL) {
            return OBJ_NIL;
        }
        
        cmdutl_ParseWS(this);
        chr = cmdutl_InputLookAhead(this, 1);
        if( chr == ':' ) {
            cmdutl_InputAdvance(this, 1);
        }
        else {
            //FIXME: Add proper error
#ifdef XYZZY
            srcErrors_AddFatalFromToken(
                                        OBJ_NIL,
                                        pToken,
                                        "Expecting ':'"
                                        );
            eResult_ErrorFatalFLC(
                eResult_Shared(),
                path_getData(this->pPath),
                this->lineNo,
                this->colNo,
                "Expecting ':', but found %c(0x%02X)",
                chr,
                chr
            );
#endif
            obj_Release(pNode);
            pNode = OBJ_NIL;
            return OBJ_NIL;
        }

        pData = cmdutl_ParseValue(this);
        if (pData == OBJ_NIL) {
            //FIXME: Add proper error
#ifdef XYZZY
            srcErrors_AddFatalFromToken(
                                        OBJ_NIL,
                                        pToken,
                                        "Expecting ':'"
                                        );
            eResult_ErrorFatalFLC(
                eResult_Shared(),
                path_getData(this->pPath),
                this->lineNo,
                this->colNo,
                "Expecting a \"value\""
            );
#endif
            obj_Release(pName);
            return OBJ_NIL;
        }

        pszName = AStr_CStringA(node_getData(pName), NULL);
        pNode = node_NewWithUTF8AndClass(pszName, 0, pData);
        mem_Free((void *)pszName);
        pszName = NULL;
        obj_Release(pName);
        pName = OBJ_NIL;
        obj_Release(pData);
        pData = OBJ_NIL;

        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  S t r i n g
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseString(
        CMDUTL_DATA     *this
    )
    {
        bool            fRc = false;
        W32CHR_T        chr;
        NODE_DATA       *pNode = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        this->lenFld = 0;
        this->pFld[0] = 0;
        
        cmdutl_ParseWS(this);
        chr = cmdutl_InputLookAhead(this, 1);
        if (chr == '"') {
            cmdutl_InputAdvance(this, 1);
        }
        else
            return false;
        
        for (;;) {
            if (cmdutl_ParseChrCon(this,'"')) {
                // Do something, maybe!
            }
            else {
                break;
            }
        }
        
        chr = cmdutl_InputLookAhead(this, 1);
        if (chr == '"') {
            cmdutl_InputAdvance(this, 1);
            fRc = true;
        }
        
        if (fRc) {
            pStr = AStr_NewW32(this->pFld);
            if (pStr) {
                pNode = node_NewWithUTF8AndClass("string", 0, pStr);
#ifdef NDEBUG
#else
                ASTR_DATA   *pStrDbg = AStr_ToDebugString(pStr, 0);
                TRC_OBJ(this, "\tstring: %s\n", AStr_getData(pStrDbg));
                obj_Release(pStrDbg);
#endif
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  V a l u e
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseValue(
        CMDUTL_DATA       *cbp
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        //bool            fRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        pNode = cmdutl_ParseHash(cbp);
        if (pNode) {
            return pNode;
        }
        pNode = cmdutl_ParseArray(cbp);
        if (pNode) {
            return pNode;
        }
        pNode = cmdutl_ParseString(cbp);
        if (pNode) {
            return pNode;
        }
        pNode = cmdutl_ParseNumber(cbp);
        if (pNode) {
            return pNode;
        }
        pNode = cmdutl_ParseKeyWord(cbp);
        if (pNode) {
            return pNode;
        }
        
        return OBJ_NIL;
    }
    
    
    
    //---------------------------------------------------------------
    //               P a r s e  W h i t e  S p a c e
    //---------------------------------------------------------------
    
    bool            cmdutl_ParseWS(
        CMDUTL_DATA       *this
    )
    {
        bool            fRc = false;
        W32CHR_T        chr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        for (;;) {
            chr = cmdutl_InputLookAhead(this, 1);
            fRc = ascii_isWhiteSpaceW32(chr);
            if( fRc ) {
                cmdutl_InputAdvance(this, 1);
            }
            else
                break;
        }
        
        return fRc;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    CMDUTL_DATA *   cmdutl_Alloc(
    )
    {
        CMDUTL_DATA     *cbp;
        uint32_t        cbSize = sizeof(CMDUTL_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    ASTR_DATA *     cmdutl_ArgvToAStr(
        int             argc,
        const
        char            *argv[]
    )
    {
        int             i;
        ASTR_DATA       *pStr = OBJ_NIL;
        ERESULT         eRc;
        
        pStr = AStr_New();
        for (i=0; i<argc; ++i) {
            eRc = AStr_AppendA(pStr, argv[i]);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pStr);
                return OBJ_NIL;
            }
            eRc = AStr_AppendCharA(pStr, ' ');
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pStr);
                return OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pStr;
    }
    
    
    
    /*! Set up an ArgC/ArgV type array given a command line string
     excluding the program name.
     @param     pCmdStrA    Pointer to a UTF-8 Argument character string
     @return    If successful, an AStrArray object which must be
     released containing the Argument Array, otherwise
     OBJ_NIL if an error occurred.
     @warning   Remember to release the returned AStrArray object.
     */
    //FIXME: We need to make this aware of the Array and Hash allowed in
    //FIXME: in parameters since they may have whitespace between elements.
    ASTRARRAY_DATA * cmdutl_CommandStringToArray(
        const
        char            *pCmdStrA
    )
    {
        ERESULT         eRc;
        bool            fRc;
        char            *pCurCmd;
        uint32_t        cmdLen = 0;
        char            *pCurChr;
        ASTRARRAY_DATA  *pArgs = OBJ_NIL;
        ASTR_DATA       *pArg = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if(pCmdStrA && (utf8_StrLenA(pCmdStrA) > 0))
            ;
        else {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        pArgs = AStrArray_New( );
        if (OBJ_NIL == pArgs) {
            DEBUG_BREAK();
            //return ERESULT_OUT_OF_MEMORY;
            return OBJ_NIL;
        }
        pCurChr = (char *)pCmdStrA;
        
        // Set up program name argument.
        pArg = AStr_NewA("");
        if (pArg) {
            eRc = AStrArray_AppendStr(pArgs, pArg, NULL);
            obj_Release(pArg);
            pArg = OBJ_NIL;
        }
        
        // Scan off the each parameter.
        while( pCurChr && *pCurChr ) {
            pCurCmd = NULL;
            cmdLen = 0;
            
            // Pass over white space.
            fRc = scanner_ScanWhite(&pCurChr, NULL);
            
            // Handle Quoted Arguments.
            pArg = scanner_ScanStringToAStr(&pCurChr, NULL);
            if (pArg) {
                eRc = AStrArray_AppendStr(pArgs, pArg, NULL);
                obj_Release(pArg);
                pArg = OBJ_NIL;
            }
            
        }
        
        // Return to caller.
        return pArgs;
    }
    
    
    
    CMDUTL_DATA *   cmdutl_NewAStr(
        ASTR_DATA       *pAStr,         // Buffer of file data
        PATH_DATA       *pPath,         // Program Path (Arg[0])
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        CMDUTL_DATA       *this;
        
        this = cmdutl_Alloc( );
        if (this) {
            this = cmdutl_InitAStr(this, pAStr, pPath, tabSize);
        }
        return this;
    }
    
    
    
    CMDUTL_DATA *   cmdutl_NewW32Str(
        W32STR_DATA     *pWStr,         // Buffer of file data
        PATH_DATA       *pPath,         // Program Path (Arg[0])
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        CMDUTL_DATA     *this;
        
        this = cmdutl_Alloc( );
        if (this) {
            this = cmdutl_InitW32Str( this, pWStr, pPath, tabSize );
        }
        return this;
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    PATH_DATA *     cmdutl_getPath(
        CMDUTL_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pPath;
    }

    
    bool        cmdutl_setPath(
        CMDUTL_DATA *this,
        PATH_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pPath) {
            obj_Release(this->pPath);
        }
        this->pPath = pValue;
        
        return true;
    }
    
    
    
    uint16_t        cmdutl_getPriority(
        CMDUTL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        //return this->priority;
        return 0;
    }

    
    bool            cmdutl_setPriority(
        CMDUTL_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        //this->priority = value;
        return true;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //--------------------------------------------------------------
    //           A p p e n d  T o k e n  T o  S t r i n g
    //--------------------------------------------------------------
    
    ERESULT         cmdutl_AppendCharToField(
        CMDUTL_DATA    *this,
        W32CHR_T       chr
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        
        if ((this->lenFld + 1) < this->sizeFld) {
            this->pFld[this->lenFld++] = chr;
            this->pFld[this->lenFld] = '\0';
        }
        else
            return ERESULT_DATA_TOO_BIG;
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            cmdutl_Dealloc(
        OBJ_ID          objId
    )
    {
        CMDUTL_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        switch (this->inputType) {
                
            case OBJ_IDENT_FILE:
                if (this->pFile) {
                    fclose(this->pFile);
                    this->pFile = NULL;
                }
                break;
                
            case OBJ_IDENT_ASTR:
                if (this->pAStr) {
                    obj_Release(this->pAStr);
                    this->pAStr = OBJ_NIL;
                }
                break;
                
            case OBJ_IDENT_W32STR:
                if (this->pWStr) {
                    obj_Release(this->pWStr);
                    this->pWStr = OBJ_NIL;
                }
                break;
                
            default:
                break;
        }
        
        cmdutl_setPath(this, OBJ_NIL);
        
        if (this->pFld) {
            mem_Free(this->pFld);
            this->pFld    = NULL;
            this->sizeFld = 0;
            this->lenFld  = 0;
        }
        
        if (this->pInputs) {
            mem_Free(this->pInputs);
            this->pInputs    = NULL;
            this->sizeInputs = 0;
            this->curInputs  = 0;
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;
        
        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    CMDUTL_DATA *     cmdutl_Init(
        CMDUTL_DATA       *this
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (CMDUTL_DATA *)obj_Init( this, cbSize, OBJ_IDENT_CMDUTL );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(cbp, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)cbp, OBJ_IDENT_CMDUTL);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&cmdutl_Vtbl);
        obj_FlagSet(this, OBJ_FLAG_EOF, false);

        this->sizeFld = CMDUTL_FIELD_MAX;
        this->pFld = mem_Calloc(this->sizeFld, sizeof(int32_t));
        if (this->pFld == NULL) {
            this->sizeFld = 0;
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->sizeInputs = 5;
        this->pInputs = mem_Calloc(this->sizeInputs, sizeof(int32_t));
        if (this->pInputs == NULL) {
            this->sizeInputs = 0;
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    CMDUTL_DATA *   cmdutl_InitFile(
        CMDUTL_DATA     *this,
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        char            *pszFileName;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pPath) {
            fprintf( stderr, "Fatal Error - Missing input source file path.\n" );
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = cmdutl_Init(this);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cmdutl_setPath(this, pPath);
        this->tabSize = tabSize;
        
        // Open the file.
        this->inputType = OBJ_IDENT_FILE;
        pszFileName = path_CStringA(pPath);
        if (pszFileName) {
            this->pFile = fopen( pszFileName, "r" );
            if (NULL == this->pFile) {
                obj_Release(this);
                return OBJ_NIL;
            }
            mem_Free(pszFileName);
            pszFileName = NULL;
        }
        else {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        return this;
    }
    
    
    
    CMDUTL_DATA *   cmdutl_InitAStr(
        CMDUTL_DATA     *this,
        ASTR_DATA       *pAStr,         // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pAStr) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_Retain(pAStr);
        
        this = cmdutl_Init(this);
        if (OBJ_NIL == this) {
            obj_Release(this);
            obj_Release(pAStr);
            return OBJ_NIL;
        }
        
        cmdutl_setPath(this, pPath);
        this->tabSize = tabSize;
        
        // Open the file.
        this->inputType = OBJ_IDENT_ASTR;
        //obj_Retain(pSzStr);   // retained above
        this->pAStr = pAStr;
        this->fileOffset = 0;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            obj_Release(pAStr);
            return OBJ_NIL;
        }
#endif
        
        return this;
    }
    
    
    CMDUTL_DATA *   cmdutl_InitW32Str(
        CMDUTL_DATA     *cbp,
        W32STR_DATA     *pWStr,         // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pWStr) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        obj_Retain(pWStr);
        
        cbp = cmdutl_Init( cbp );
        if (OBJ_NIL == cbp) {
            obj_Release(cbp);
            obj_Release(pWStr);
            return OBJ_NIL;
        }
        
        cmdutl_setPath(cbp, pPath);
        cbp->tabSize = tabSize;
        
        // Open the file.
        cbp->inputType = OBJ_IDENT_W32STR;
        //obj_Retain(pWStr);    // retained above
        cbp->pWStr = pWStr;
        cbp->fileOffset = 0;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
            obj_Release(cbp);
            obj_Release(pWStr);
            return OBJ_NIL;
        }
#endif
        
        return cbp;
    }
    
    
    
    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------
    
    W32CHR_T        cmdutl_InputAdvance(
        CMDUTL_DATA     *cbp,
        uint16_t        numChrs
    )
    {
        uint32_t        i;
        W32CHR_T        chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        // Shift inputs.
        for (i=0; i<numChrs; ++i) {
            cmdutl_InputNextChar(cbp);
        }
        
        chr = cbp->pInputs[cbp->curInputs];
        if (chr) {
            switch (chr) {
                    
                case '\b':
                    if (cbp->colNo) {
                        --cbp->colNo;
                    }
                    break;
                    
                case '\f':
                case '\n':
                    ++cbp->lineNo;
                    break;
                    
                case '\r':
                    cbp->colNo = 0;
                    break;
                    
                case '\t':
                    if( cbp->tabSize ) {
                        chr = ' ';
                        if( ((cbp->colNo-1) % cbp->tabSize) )
                            cbp->colNo += ((cbp->colNo-1) % cbp->tabSize);
                        else
                            cbp->colNo += cbp->tabSize;
                    }
                    else {
                        ++cbp->colNo;
                    }
                    break;
                    
                default:
                    if (chr) {
                        ++cbp->colNo;
                    }
                    break;
            }
        }
        
        // Return to caller.
        return chr;
    }
    
    
    
    //--------------------------------------------------------------
    //               I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------
    
    W32CHR_T        cmdutl_InputLookAhead(
        CMDUTL_DATA     *this,
        uint16_t        num
    )
    {
        uint16_t        idx;
        W32CHR_T        chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        idx = (this->curInputs + num - 1) % this->sizeInputs;
        chr = this->pInputs[idx];
        
        // Return to caller.
        return chr;
    }
    
    
    
    
    //--------------------------------------------------------------
    //                  I n p u t  N e x t  C h a r
    //--------------------------------------------------------------
    
    ERESULT         cmdutl_InputNextChar(
        CMDUTL_DATA     *this
    )
    {
        W32CHR_T        chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Add the next char to the queue.
        chr = cmdutl_UnicodeGetc(this);
        this->pInputs[this->curInputs] = chr;
        this->curInputs = (this->curInputs + 1) % this->sizeInputs;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P a r s e  F i l e
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseFile(
        CMDUTL_DATA		*this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        this->fileOffset = 0;
        cmdutl_InputAdvance(this, this->sizeInputs);
        pNode = cmdutl_ParseCmdStr(this);
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     cmdutl_ToDebugString(
        CMDUTL_DATA     *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(cmdutl) ",
                     this
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->toDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->toDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf( str, sizeof(str), " %p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            cmdutl_Validate(
        CMDUTL_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_CMDUTL) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(CMDUTL_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


