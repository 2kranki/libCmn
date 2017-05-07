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
#include "cmdutl_internal.h"
#include "ascii.h"
#include "AStr.h"
#include "nodeArray.h"
#include "nodeHash.h"
#include "trace.h"
#include "WStr.h"
#include <stdio.h>



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
    int32_t         cmdutl_UnicodeGetc(
        CMDUTL_DATA     *this
    )
    {
        int32_t         wrkChr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        switch (this->inputType) {
                
            case OBJ_IDENT_ASTR:
                wrkChr = AStr_CharGetW(this->pAStr, ++this->fileOffset );
                break;
                
            case OBJ_IDENT_FILE:
                wrkChr = fgetwc( this->pFile);
                if( wrkChr == EOF ) {
                    if( feof(this->pFile) ) {
                        return -1; //ERESULT_EOF_ERROR;
                    }
                    else
                        return -1; //ERESULT_READ_ERROR;
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
                
            case OBJ_IDENT_WSTR:
                wrkChr = WStr_CharGetW(this->pWStr, ++this->fileOffset );
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
    
    int32_t         cmdutl_ParseAlpha(
        CMDUTL_DATA       *cbp
    )
    {
        int32_t         chr;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        chr = cmdutl_InputLookAhead(cbp, 1);
        
        if( (chr >= 'a') && (chr <= 'z') ) {
            cmdutl_AppendCharToField(cbp, chr);
            cmdutl_InputAdvance(cbp, 1);
            chr -= '0';
        }
        else if( (chr >= 'A') && (chr <= 'Z') ) {
            cmdutl_AppendCharToField(cbp, chr);
            cmdutl_InputAdvance(cbp, 1);
            chr -= '0';
        }
        else {
            chr = -1;
        }
        
        // Return to caller.
        return chr;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  A r r a y
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseArray(
        CMDUTL_DATA       *cbp
    )
    {
        int32_t         chr;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        OBJ_ID          pChild = OBJ_NIL;
        //bool            fRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(cbp,"%s:\n", __func__);
        
        cmdutl_ParseWS(cbp);
        chr = cmdutl_InputLookAhead(cbp, 1);
        if( chr == '[' ) {
            cmdutl_InputAdvance(cbp, 1);
        }
        else {
            return OBJ_NIL;
        }
        
        pArray = nodeArray_New( );
        if (pArray == OBJ_NIL) {
            eResult_ErrorFatalFLC(
                eResult_Shared(),
                path_getData(cbp->pPath),
                cbp->lineNo,
                cbp->colNo,
                "Out of Memory"
            );
            return pNode;
        }
        
        pChild = cmdutl_ParseValue(cbp);
        if (pChild) {
            nodeArray_AppendNode(pArray, pChild, NULL);
            obj_Release(pChild);
        }
        else {
            obj_Release(pArray);
            return OBJ_NIL;
        }
        
        for (;;) {
            cmdutl_ParseWS(cbp);
            chr = cmdutl_InputLookAhead(cbp, 1);
            if( chr == ',' ) {
                cmdutl_InputAdvance(cbp, 1);
            }
            else
                break;
            pChild = cmdutl_ParseValue(cbp);
            if (pChild) {
                nodeArray_AppendNode(pArray, pChild, NULL);
                obj_Release(pChild);
            }
            else {
                eResult_ErrorFatalFLC(
                    eResult_Shared(),
                    path_getData(cbp->pPath),
                    cbp->lineNo,
                    cbp->colNo,
                    "Expecting a value, but found %c(0x%02X)",
                    chr,
                    chr
                );
            }
        }
        
        cmdutl_ParseWS(cbp);
        chr = cmdutl_InputLookAhead(cbp, 1);
        if( chr == ']' ) {
            cmdutl_InputAdvance(cbp, 1);
        }
        else {
            eResult_ErrorFatalFLC(
                eResult_Shared(),
                path_getData(cbp->pPath),
                cbp->lineNo,
                cbp->colNo,
                "Expecting ']', but found %c(0x%02X)",
                chr,
                chr
            );
        }
        
        pNode = node_NewWithUTF8("array", pArray);
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
        CMDUTL_DATA       *cbp,
        int32_t         ending
    )
    {
        int32_t         chr;
        uint32_t        i;
        int32_t         wrk;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        chr = cmdutl_InputLookAhead(cbp, 1);
        if (chr == ending) {
            return false;
        }
        if ( chr == '\\') {
            chr = cmdutl_InputAdvance(cbp, 1);
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
                    cmdutl_AppendCharToField(cbp, chr);
                    cmdutl_InputAdvance(cbp, 1);
                    for (i=0; i<2; ++i) {
                        wrk = 0;
                        chr = cmdutl_ParseDigitOctal(cbp);
                        if (chr >= 0) {
                            wrk = (wrk << 3) | chr;
                        }
                        else {
                            chr = cmdutl_InputLookAhead(cbp, 1);
                            eResult_ErrorFatalFLC(
                                eResult_Shared(),
                                path_getData(cbp->pPath),
                                cbp->lineNo,
                                cbp->colNo,
                                "Invalid octal char, %c(0x%02X)",
                                chr,
                                chr
                            );
                        }
                    }
                    return true;
#endif
                    
                case 'b':
                    cmdutl_AppendCharToField(cbp, '\b');
                    cmdutl_InputAdvance(cbp, 1);
                    return true;
                    
                case 'f':
                    cmdutl_AppendCharToField(cbp, '\f');
                    cmdutl_InputAdvance(cbp, 1);
                    return true;
                    
                case 'n':
                    cmdutl_AppendCharToField(cbp, '\n');
                    cmdutl_InputAdvance(cbp, 1);
                    return true;
                    
                case 'r':
                    cmdutl_AppendCharToField(cbp, '\r');
                    cmdutl_InputAdvance(cbp, 1);
                    return true;
                    
                case 't':
                    cmdutl_AppendCharToField(cbp, '\t');
                    cmdutl_InputAdvance(cbp, 1);
                    return true;

#ifdef XYZZY
                case 'v':
                    cmdutl_AppendCharToField(cbp, '\v');
                    cmdutl_InputAdvance(cbp, 1);
                    return true;
#endif
                    
                case '\\':
                    cmdutl_AppendCharToField(cbp, '\\');
                    cmdutl_InputAdvance(cbp, 1);
                    return true;
                    
                case '/':
                    cmdutl_AppendCharToField(cbp, '/');
                    cmdutl_InputAdvance(cbp, 1);
                    return true;
                    
                case '\'':
                    cmdutl_AppendCharToField(cbp, '\'');
                    cmdutl_InputAdvance(cbp, 1);
                    return true;
                    
                case '"':
                    cmdutl_AppendCharToField(cbp, chr);
                    cmdutl_InputAdvance(cbp, 1);
                    return true;
                    
                case 'u':
                    cmdutl_AppendCharToField(cbp, chr);
                    cmdutl_InputAdvance(cbp, 1);
                    for (i=0; i<4; ++i) {
                        wrk = 0;
                        chr = cmdutl_ParseDigitHex(cbp);
                        if (chr >= 0) {
                            wrk = (wrk << 4) | chr;
                        }
                        else {
                            chr = cmdutl_InputLookAhead(cbp, 1);
                            eResult_ErrorFatalFLC(
                                eResult_Shared(),
                                path_getData(cbp->pPath),
                                cbp->lineNo,
                                cbp->colNo,
                                "Invalid hexadecimal char, %c(0x%02X)",
                                chr,
                                chr
                            );
                        }
                    }
                    break;
                    
                default:
                    chr = cmdutl_InputLookAhead(cbp, 1);
                    eResult_ErrorFatalFLC(
                                          eResult_Shared(),
                                          path_getData(cbp->pPath),
                                          cbp->lineNo,
                                          cbp->colNo,
                                          "Invalid char after \\, %c(0x%02X)",
                                          chr,
                                          chr
                    );
                    break;
            }
        }
        else {
            cmdutl_AppendCharToField(cbp, chr);
            cmdutl_InputAdvance(cbp, 1);
        }
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  D i g i t  0-9
    //---------------------------------------------------------------
    
    int32_t         cmdutl_ParseDigit0To9(
        CMDUTL_DATA       *cbp
    )
    {
        int32_t         chr;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        chr = cmdutl_InputLookAhead(cbp, 1);
        
        if( (chr >= '0') && (chr <= '9') ) {
            cmdutl_AppendCharToField(cbp, chr);
            cmdutl_InputAdvance(cbp, 1);
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
    
    int32_t         cmdutl_ParseDigit1To9(
        CMDUTL_DATA       *cbp
    )
    {
        int32_t         chr;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        chr = cmdutl_InputLookAhead(cbp, 1);
        
        if( (chr >= '1') && (chr <= '9') ) {
            cmdutl_AppendCharToField(cbp, chr);
            cmdutl_InputAdvance(cbp, 1);
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
    
    int32_t         cmdutl_ParseDigitHex(
        CMDUTL_DATA       *cbp
    )
    {
        int32_t         chr;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        chr = cmdutl_InputLookAhead(cbp, 1);
        
        if( (chr >= '0') && (chr <= '9') ) {
            cmdutl_InputAdvance(cbp, 1);
            chr -= '0';
        }
        else if( (chr >= 'A') && (chr <= 'F') ) {
            cmdutl_InputAdvance(cbp, 1);
            chr = chr - 'A' + 10;
        }
        else if( (chr >= 'a') && (chr <= 'f') ) {
            cmdutl_InputAdvance(cbp, 1);
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
    
    int32_t         cmdutl_ParseDigitOctal(
        CMDUTL_DATA       *cbp
    )
    {
        int32_t         chr;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        chr = cmdutl_InputLookAhead(cbp, 1);
        
        if( (chr >= '0') && (chr <= '7') ) {
            cmdutl_InputAdvance(cbp, 1);
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
        CMDUTL_DATA       *cbp
    )
    {
        int32_t         chr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(cbp,"%s:\n", __func__);
        
        cmdutl_ParseWS(cbp);
        chr = cmdutl_InputLookAhead(cbp, 1);
        if (chr < 0) {
            cmdutl_InputAdvance(cbp, 1);
            return true;
        }
        
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //               P a r s e  F i l e  O b j e c t
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseFileObject(
        CMDUTL_DATA       *cbp
    )
    {
        int32_t         chr;
        NODE_DATA       *pNode;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(cbp,"%s:\n", __func__);
        
        pNode = cmdutl_ParseHash(cbp);
        if( OBJ_NIL == pNode ) {
            return pNode;
        }
        
        cmdutl_ParseWS(cbp);
        if(!cmdutl_ParseEOF(cbp)) {
            chr = cmdutl_InputLookAhead(cbp, 1);
            eResult_ErrorFatalFLC(
                eResult_Shared(),
                path_getData(cbp->pPath),
                cbp->lineNo,
                cbp->colNo,
                "Expecting EOF, but found %c(0x%02X)",
                chr,
                chr
            );
        }
        
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  H a s h
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseHash(
        CMDUTL_DATA       *cbp
    )
    {
        int32_t         chr;
        NODE_DATA       *pNode = OBJ_NIL;
        NODEHASH_DATA   *pHash = OBJ_NIL;
        NODE_DATA       *pChild;
        ERESULT         eRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(cbp,"%s:\n", __func__);
        
        cmdutl_ParseWS(cbp);
        chr = cmdutl_InputLookAhead(cbp, 1);
        if( chr == '{' ) {
            cmdutl_InputAdvance(cbp, 1);
        }
        else {
            return pNode;
        }
        
        pHash = nodeHash_New(NODEHASH_TABLE_SIZE_XXXSMALL);
        if (pHash == OBJ_NIL) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        pChild = cmdutl_ParsePair(cbp);
        if (pChild) {
            eRc = nodeHash_Add(pHash, pChild);
            obj_Release(pChild);
            pChild = OBJ_NIL;
            for (;;) {
                cmdutl_ParseWS(cbp);
                chr = cmdutl_InputLookAhead(cbp, 1);
                if( chr == ',' ) {
                    cmdutl_InputAdvance(cbp, 1);
                }
                else
                    break;
                pChild = cmdutl_ParsePair(cbp);
                if (pChild) {
                    eRc = nodeHash_Add(pHash, pChild);
                    obj_Release(pChild);
                    pChild = OBJ_NIL;
                }
                else {
                    eResult_ErrorFatalFLC(
                        eResult_Shared(),
                        path_getData(cbp->pPath),
                        cbp->lineNo,
                        cbp->colNo,
                        "Expecting a value, but found %c(0x%02X)",
                        chr,
                        chr
                    );
                }
            }
        }
        
        cmdutl_ParseWS(cbp);
        chr = cmdutl_InputLookAhead(cbp, 1);
        if( chr == '}' ) {
            cmdutl_InputAdvance(cbp, 1);
        }
        else {
            eResult_ErrorFatalFLC(
                eResult_Shared(),
                path_getData(cbp->pPath),
                cbp->lineNo,
                cbp->colNo,
                "Expecting '}', but found %c(0x%02X)",
                chr,
                chr
            );
            obj_Release(pNode);
            pNode = OBJ_NIL;
            return pNode;
        }
        
        pNode = node_NewWithUTF8("hash", pHash);
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
        CMDUTL_DATA       *cbp
    )
    {
        int32_t         chr;
        NODE_DATA       *pNode = OBJ_NIL;
        FALSE_DATA      *pFalse = false_New();
        NULL_DATA       *pNull = null_New();
        TRUE_DATA       *pTrue = true_New();
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(cbp,"%s:\n", __func__);
        cbp->lenFld = 0;
        cbp->pFld[0] = 0;
        
        cmdutl_ParseWS(cbp);
        while ((chr=cmdutl_ParseAlpha(cbp)) > 0) {
        }
        str_ToLowerW(cbp->pFld);
        if (cbp->lenFld) {
            if (0 == str_CompareW(L"false", cbp->pFld)) {
                pNode = node_NewWithUTF8("false", pFalse);
            }
            else if (0 == str_CompareW(L"null", cbp->pFld)) {
                pNode = node_NewWithUTF8("null", pNull);
            }
            else if (0 == str_CompareW(L"true", cbp->pFld)) {
                pNode = node_NewWithUTF8("true", pTrue);
            }
            else {
                eResult_ErrorFatalFLC(
                    eResult_Shared(),
                    path_getData(cbp->pPath),
                    cbp->lineNo,
                    cbp->colNo,
                    "Expecting false, null or true, but found %c(0x%02X)",
                    chr,
                    chr
                );
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
        CMDUTL_DATA       *cbp
    )
    {
        int32_t         chr;
        NODE_DATA       *pNode = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        bool            fRc = false;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        cbp->lenFld = 0;
        cbp->pFld[0] = 0;
        
        cmdutl_ParseWS(cbp);
        chr = cmdutl_InputLookAhead(cbp, 1);
        if( chr == '-' ) {
            cmdutl_AppendCharToField(cbp, chr);
            cmdutl_InputAdvance(cbp, 4);
        }
        if( chr == '0' ) {
            cmdutl_AppendCharToField(cbp, chr);
            chr = cmdutl_InputAdvance(cbp, 4);
            fRc = true;
        }
        else if ( cmdutl_ParseDigit1To9(cbp) >= 0) {
            while (cmdutl_ParseDigit0To9(cbp) >= 0) {
            }
            fRc = true;
        }
        
        if (!fRc) {
            return OBJ_NIL;
        }
        
        chr = cmdutl_InputLookAhead(cbp, 1);
        if( chr == '.' ) {
            cmdutl_AppendCharToField(cbp, chr);
            cmdutl_InputAdvance(cbp, 4);
            if (cmdutl_ParseDigit0To9(cbp) > 0)
                ;
            else {
                eResult_ErrorFatalFLC(
                    eResult_Shared(),
                    path_getData(cbp->pPath),
                    cbp->lineNo,
                    cbp->colNo,
                    "Expecting 0-9, but found %c(0x%02X)",
                    chr,
                    chr
                );
            }
            while (cmdutl_ParseDigit0To9(cbp) > 0) {
            }
        }
        
        chr = cmdutl_InputLookAhead(cbp, 1);
        if( (chr == 'e') || (chr == 'E') ) {
            cmdutl_AppendCharToField(cbp, chr);
            cmdutl_InputAdvance(cbp, 4);
            if( (chr == '-') || (chr == '+') ) {
                cmdutl_AppendCharToField(cbp, chr);
                cmdutl_InputAdvance(cbp, 4);
            }
            if (cmdutl_ParseDigit0To9(cbp) > 0)
                ;
            else {
                eResult_ErrorFatalFLC(
                    eResult_Shared(),
                    path_getData(cbp->pPath),
                    cbp->lineNo,
                    cbp->colNo,
                    "Expecting 0-9, but found %c(0x%02X)",
                    chr,
                    chr
                );
            }
            while (cmdutl_ParseDigit0To9(cbp) > 0) {
            }
        }

        if (fRc) {
            pStr = AStr_NewW(cbp->pFld);
            if (pStr) {
                pNode = node_NewWithUTF8("number", pStr);
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
        CMDUTL_DATA       *cbp
    )
    {
        int32_t         chr;
        NODE_DATA       *pData = OBJ_NIL;
        NODE_DATA       *pName = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        const
        char            *pszName;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(cbp,"%s:\n", __func__);
        
        pName = cmdutl_ParseString(cbp);
        if (pName == OBJ_NIL) {
            return OBJ_NIL;
        }
        
        cmdutl_ParseWS(cbp);
        chr = cmdutl_InputLookAhead(cbp, 1);
        if( chr == ':' ) {
            cmdutl_InputAdvance(cbp, 1);
        }
        else {
            eResult_ErrorFatalFLC(
                eResult_Shared(),
                path_getData(cbp->pPath),
                cbp->lineNo,
                cbp->colNo,
                "Expecting ':', but found %c(0x%02X)",
                chr,
                chr
            );
            obj_Release(pNode);
            pNode = OBJ_NIL;
            return OBJ_NIL;
        }

        pData = cmdutl_ParseValue(cbp);
        if (pData == OBJ_NIL) {
            eResult_ErrorFatalFLC(
                eResult_Shared(),
                path_getData(cbp->pPath),
                cbp->lineNo,
                cbp->colNo,
                "Expecting a \"value\""
            );
            obj_Release(pName);
            return OBJ_NIL;
        }

        pszName = AStr_CStringA(node_getData(pName), NULL);
        pNode = node_NewWithUTF8(pszName, pData);
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
        CMDUTL_DATA       *cbp
    )
    {
        bool            fRc = false;
        int32_t         chr;
        NODE_DATA       *pNode = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(cbp,"%s:\n", __func__);
        cbp->lenFld = 0;
        cbp->pFld[0] = 0;
        
        cmdutl_ParseWS(cbp);
        chr = cmdutl_InputLookAhead(cbp, 1);
        if (chr == '"') {
            cmdutl_InputAdvance(cbp, 1);
        }
        else
            return false;
        
        for (;;) {
            if (cmdutl_ParseChrCon(cbp,'"')) {
                // Do something, maybe!
            }
            else {
                break;
            }
        }
        
        chr = cmdutl_InputLookAhead(cbp, 1);
        if (chr == '"') {
            cmdutl_InputAdvance(cbp, 1);
            fRc = true;
        }
        
        if (fRc) {
            pStr = AStr_NewW(cbp->pFld);
            if (pStr) {
                pNode = node_NewWithUTF8("string", pStr);
#ifdef NDEBUG
#else
                ASTR_DATA   *pStrDbg = AStr_ToDebugString(pStr, 0);
                TRC_OBJ(cbp,"\tstring: %s\n", AStr_getData(pStrDbg));
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
        CMDUTL_DATA       *cbp
    )
    {
        bool            fRc = false;
        int32_t         chr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        for (;;) {
            chr = cmdutl_InputLookAhead(cbp, 1);
            fRc = WStr_IsWhiteSpaceW(chr);
            if( fRc ) {
                cmdutl_InputAdvance(cbp, 1);
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



    //---------------------------------------------------------------
    //                C o n v e r t  A r g c  t o  W S t r
    //---------------------------------------------------------------
    
    WSTR_DATA *     cmdutl_ConvertArgcToWStr(
        int             argc,
        const
        char            *argv[]
    )
    {
        int             i;
        WSTR_DATA       *pStr = OBJ_NIL;
        ERESULT         eRc;
        
        pStr = WStr_New();
        for (i=0; i<argc; ++i) {
            eRc = WStr_AppendA(pStr, argv[i]);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pStr);
                return OBJ_NIL;
            }
            eRc = WStr_AppendCharW(pStr, 1, ' ');
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pStr);
                return OBJ_NIL;
            }
        }
        eRc = WStr_AppendCharW(pStr, 1, '\n');
        
        // Return to caller.
        return pStr;
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
            this = cmdutl_InitAStr( this, pAStr, pPath, tabSize );
        }
        return( this );
    }
    
    
    
    CMDUTL_DATA *   cmdutl_NewWStr(
        WSTR_DATA       *pWStr,         // Buffer of file data
        PATH_DATA       *pPath,         // Program Path (Arg[0])
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        CMDUTL_DATA     *this;
        
        this = cmdutl_Alloc( );
        if (this) {
            this = cmdutl_InitWStr( this, pWStr, pPath, tabSize );
        }
        return( this );
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
        int32_t        chr
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
        CMDUTL_DATA   *cbp = objId;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        switch (cbp->inputType) {
                
            case OBJ_IDENT_FILE:
                if (cbp->pFile) {
                    fclose(cbp->pFile);
                    cbp->pFile = NULL;
                }
                break;
                
            case OBJ_IDENT_ASTR:
                if (cbp->pAStr) {
                    obj_Release(cbp->pAStr);
                    cbp->pAStr = OBJ_NIL;
                }
                break;
                
            case OBJ_IDENT_WSTR:
                if (cbp->pWStr) {
                    obj_Release(cbp->pWStr);
                    cbp->pWStr = OBJ_NIL;
                }
                break;
                
            default:
                break;
        }
        
        cmdutl_setPath(cbp, OBJ_NIL);
        
        if (cbp->pFld) {
            mem_Free(cbp->pFld);
            cbp->pFld    = NULL;
            cbp->sizeFld = 0;
            cbp->lenFld  = 0;
        }
        
        if (cbp->pInputs) {
            mem_Free(cbp->pInputs);
            cbp->pInputs    = NULL;
            cbp->sizeInputs = 0;
            cbp->curInputs  = 0;
        }
        
        obj_Dealloc( cbp );
        cbp = NULL;

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

     

    CMDUTL_DATA *     cmdutl_InitFile(
        CMDUTL_DATA       *cbp,
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        char            *pszFileName;
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pPath) {
            fprintf( stderr, "Fatal Error - Missing input source file path.\n" );
            obj_Release(cbp);
            return OBJ_NIL;
        }
        
        cbp = cmdutl_Init( cbp );
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        cmdutl_setPath(cbp, pPath);
        cbp->tabSize = tabSize;
        
        // Open the file.
        cbp->inputType = OBJ_IDENT_FILE;
        pszFileName = path_CStringA(pPath);
        if (pszFileName) {
            cbp->pFile = fopen( pszFileName, "r" );
            if (NULL == cbp->pFile) {
                obj_Release(cbp);
                return OBJ_NIL;
            }
            mem_Free(pszFileName);
            pszFileName = NULL;
        }
        else {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        
        return cbp;
    }
    
    
    
    CMDUTL_DATA *     cmdutl_InitAStr(
        CMDUTL_DATA       *cbp,
        ASTR_DATA       *pAStr,         // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pAStr) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        obj_Retain(pAStr);
        
        cbp = cmdutl_Init( cbp );
        if (OBJ_NIL == cbp) {
            obj_Release(cbp);
            obj_Release(pAStr);
            return OBJ_NIL;
        }
        
        cmdutl_setPath(cbp, pPath);
        cbp->tabSize = tabSize;
        
        // Open the file.
        cbp->inputType = OBJ_IDENT_ASTR;
        //obj_Retain(pSzStr);   // retained above
        cbp->pAStr = pAStr;
        cbp->fileOffset = 0;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
            obj_Release(cbp);
            obj_Release(pAStr);
            return OBJ_NIL;
        }
#endif
        
        return cbp;
    }
    
    
    CMDUTL_DATA *     cmdutl_InitWStr(
        CMDUTL_DATA       *cbp,
        WSTR_DATA       *pWStr,         // Buffer of file data
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
        cbp->inputType = OBJ_IDENT_WSTR;
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
    
    int32_t         cmdutl_InputAdvance(
        CMDUTL_DATA      *cbp,
        uint16_t        numChrs
    )
    {
        uint32_t        i;
        int32_t         chr;
        
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
    
    int32_t         cmdutl_InputLookAhead(
        CMDUTL_DATA       *cbp,
        uint16_t        num
    )
    {
        uint16_t        idx;
        int32_t         chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        idx = (cbp->curInputs + num - 1) % cbp->sizeInputs;
        chr = cbp->pInputs[idx];
        
        // Return to caller.
        return chr;
    }
    
    
    
    
    //--------------------------------------------------------------
    //                  I n p u t  N e x t  C h a r
    //--------------------------------------------------------------
    
    ERESULT         cmdutl_InputNextChar(
        CMDUTL_DATA      *cbp
    )
    {
        int32_t         chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Add the next char to the queue.
        chr = cmdutl_UnicodeGetc(cbp);
        cbp->pInputs[cbp->curInputs] = chr;
        cbp->curInputs = (cbp->curInputs + 1) % cbp->sizeInputs;
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P a r s e  F i l e
    //---------------------------------------------------------------
    
    NODE_DATA *     cmdutl_ParseFile(
        CMDUTL_DATA		*cbp
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        TRC_OBJ(cbp,"%s:\n", __func__);
        
        cbp->fileOffset = 0;
        cmdutl_InputAdvance(cbp, cbp->sizeInputs);
        pNode = cmdutl_ParseFileObject(cbp);
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     cmdutl_ToDebugString(
        CMDUTL_DATA       *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(cmdutl) ",
                     cbp
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (cbp->pData) {
            if (((OBJ_DATA *)(cbp->pData))->pVtbl->toDebugString) {
                pWrkStr =   ((OBJ_DATA *)(cbp->pData))->pVtbl->toDebugString(
                                                    cbp->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf( str, sizeof(str), " %p}\n", cbp );
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


