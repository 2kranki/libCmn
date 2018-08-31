// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   cmdutl.c
 *	Generated 10/18/2015 19:44:45
 *
 */

/***
 Pass 1:

 We parsed the arguments without knowing anything about them.  This causes the need
 for delimiters such as '=' to attach values to options which is non-standard.  In
 parsing this, we end up with a nodeHash hierarchy which must then be parsed by the
 program.  So, we are parsing the arguments two times.
 
 cmdstr : string (ws | arg)*            // First string is program path
        ;
 arg    : name ('=' value)?
        | string ('=' value)?
        | array
        | number
        ;
 
 value  : name
        | string
        | number
        | array
        ;
 
 array  : '[' ws* value (',' ws* value)* ws* ']'
        ;
 
 name   : [a-zA-Z][a-zA-Z0-9_]*
        ;
 
 ws     : ' '
        | '\b'
        | '\f'
        | '\n'
        | '\r'
        | '\t'
        ;
 
 string : '"' string_chars* '"'
        ;
 
 strchr : [\b\f\n\r\t\\\/ !]
        | [#-~]
        | '\\' '"'
        | '\\' ('u'|'U') hexdigit*
        | '\\' '\\'
        ;
 
 number : ('-')? [1-9][0-9]* ('.' [0-9]+)? numexp?      // Decimal or Float
        | [0]([xX][0-9a-fA-F]*                          // Hexadecimal
        | [0][0-7]*                                     // Octal
        ;
 numexp : ('e' | 'E') ('-' | '+')? [0-9]+
        ;


 
 Pass 2:
 
 We tried parsing the arguments by having exits at different parse points.  This worked
 fair, but requires the exits to be able to communicate back about whether an option
 has an argument or not.  Also, we had to parse the short and long options separately.
 This became very clumsy to implement.
 
 
 Pass 3:
 
 optparse is a public domain package which we have altered substantially to be only driven
 
 ***/



 
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

    int             cmdutl_CreateErrorMsg(
        CMDUTL_DATA     *this,
        const
        char            *pMsg,
        const
        char            *pData
    )
    {
        unsigned        p = 0;
        unsigned        e = sizeof(this->errmsg) - 2;
        const
        char            *sep = " -- '";
        
        while (*pMsg && (p < e))
            this->errmsg[p++] = *pMsg++;
        while (*sep && (p < e))
            this->errmsg[p++] = *sep++;
        while (p < sizeof(this->errmsg) - 2 && *pData && (p < e))
            this->errmsg[p++] = *pData++;
        this->errmsg[p++] = '\'';
        this->errmsg[p++] = '\0';
        return '?';
    }
    

    
    int             cmdutl_IsDashDash(
        const
        char            *arg
    )
    {
        return arg != NULL && arg[0] == '-' && arg[1] == '-' && arg[2] == '\0';
    }

    
    
    int             cmdutl_IsShortOpt(
        const
        char            *arg
    )
    {
        return arg != NULL && arg[0] == '-' && arg[1] != '-' && arg[1] != '\0';
    }

    
    
    int             cmdutl_IsLongOpt(
        const
        char            *pArg
    )
    {
        return pArg != NULL && pArg[0] == '-' && pArg[1] == '-' && pArg[2] != '\0';
    }

    
    
    void            cmdutl_Permute(
        CMDUTL_DATA     *this,
        int             index
    )
    {
        char            *nonoption = this->ppArgV[index];
        int             i;
        
        for (i = index; i < this->optIndex - 1; i++) {
            this->ppArgV[i] = this->ppArgV[i + 1];
        }
        this->ppArgV[this->optIndex - 1] = nonoption;
    }
    

    
    int             cmdutl_Argtype(
        const
        char            *optstring,
        char            c
    )
    {
        int             count = CMDUTL_ARG_OPTION_NONE;
        if (c == ':')
            return -1;
        for (; *optstring && c != *optstring; optstring++)
            ;
        if (!*optstring)
            return -1;
        if (optstring[1] == ':')
            count += optstring[2] == ':' ? 2 : 1;
        return count;
    }

    
    
    bool            cmdutl_LongOptsEnd(
        const
        CMDUTL_OPTION   *pOptions,
        int             i
    )
    {
        return (NULL == pOptions[i].pLongName) && (0 == pOptions[i].shortName);
    }


    
   /*! Construct the getopt() option string from the given Long Option Table.
    @param     pOptions     Option Table with last entry having NULL and 0
                            for Long and Short names respectively
    @param      pOptstring  an output area for the getopt-like string
    @return:    true if successful, otherwise false
    */
    bool            cmdutl_OptstringFromLongOptions(
        const
        CMDUTL_OPTION   *pOptions,
        int             len,
        char            *pOptstring
    )
    {
        char            *p = pOptstring;
        int             i;
        
        for (i = 0; !cmdutl_LongOptsEnd(pOptions, i); i++) {
            if (pOptions[i].shortName && ascii_isAlphanumericA(pOptions[i].shortName)) {
                int             a;
                *p++ = pOptions[i].shortName;
                --len;
                if (len == 0) {
                    return false;
                }
                for (a = 0; a < (int)pOptions[i].argOption; a++) {
                    *p++ = ':';
                    --len;
                    if (len == 0) {
                        return false;
                    }
                }
            }
        }
        *p = '\0';
        --len;
        if (len == 0) {
            return false;
        }
        return true;
    }

    
    
    /* Unlike strcmp(), handles options containing "=". */
    int             cmdutl_LongOptsMatch(
        const
        char            *pLongName,
        const
        char            *pOption
    )
    {
        const
        char            *a = pOption;
        const
        char            *n = pLongName;
        
        if (pLongName == NULL)
            return 0;
        for (; *a && *n && *a != '='; a++, n++)
            if (*a != *n)
                return 0;
        return *n == '\0' && (*a == '\0' || *a == '=');
    }

    
    
    /* Return the part after "=", or NULL. */
    char *          cmdutl_LongOptsArg(
        char            *pOption
    )
    {
        // Find '=' within option if it exists.
        for (; *pOption && *pOption != '='; pOption++)
            ;
        
        if (*pOption == '=')
            return pOption + 1;
        
        return NULL;
    }

    
    
    int             cmdutl_LongOptsFallback(
        CMDUTL_DATA     *this,
        const
        CMDUTL_OPTION   *pOptions,
        int             *pLongIndex
    )
    {
        int             result;
        char            optstring[(96 * 3) + 1];  /* 96 ASCII printable characters */
        bool            fRc;
        
        // Convert the long option table into a getopt option string.
        fRc = cmdutl_OptstringFromLongOptions(pOptions, ((96 * 3) + 1), optstring);
        if (!fRc) {
            return '?';
        }
        
        // Now try to find the option using the option string.
        result = cmdutl_Parse(this, optstring);
        if (pLongIndex != NULL) {
            *pLongIndex = -1;
            if (result != -1) {
                // Found short name. Now translate optstring index into
                // Options Table index.
                int i;
                for (i = 0; !cmdutl_LongOptsEnd(pOptions, i); i++)
                    if (pOptions[i].shortName == this->optopt)
                        *pLongIndex = i;
            }
        }
        return result;
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
    
    
    
    CMDUTL_DATA *   cmdutl_New(
        int             cArgs,
        char            **ppArgs
    )
    {
        CMDUTL_DATA       *this;
        
        this = cmdutl_Alloc( );
        if (this) {
            this = cmdutl_Init(this, cArgs, ppArgs);
        }
        return this;
    }
    
    
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //--------------------------------------------------------------
    //                          A r g V
    //--------------------------------------------------------------
    
    ASTRARRAY_DATA *    cmdutl_getArgV(
        CMDUTL_DATA         *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pSavedArgs;
    }
    
    
    bool            cmdutl_setArgV(
        CMDUTL_DATA     *this,
        ASTRARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pSavedArgs) {
            obj_Release(this->pSavedArgs);
        }
        this->pSavedArgs = pValue;
        
        return true;
    }
    
    
    
    //--------------------------------------------------------------
    //                       O b j e c t
    //--------------------------------------------------------------
    
    OBJ_ID      cmdutl_getObject(
        CMDUTL_DATA *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pObj;
    }
    
    
    bool        cmdutl_setObject(
        CMDUTL_DATA *this,
        OBJ_ID      pValue
    )
    {
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pObj) {
            obj_Release(this->pObj);
        }
        this->pObj = pValue;
        
        return true;
    }
    
    
    
    //--------------------------------------------------------------
    //              O p t i o n  D e f i n i t i o n s
    //--------------------------------------------------------------
    
    CMDUTL_OPTION * cmdutl_getOptionDefinitions(
        CMDUTL_DATA *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pOptDefns;
    }
    

    
    //--------------------------------------------------------------
    //                          P a t h
    //--------------------------------------------------------------
    
    PATH_DATA *     cmdutl_getPath(
        CMDUTL_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
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
        if( !cmdutl_Validate(this) ) {
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
    
    
    
    //--------------------------------------------------------------
    //                      P e r m u t e
    //--------------------------------------------------------------
    
    bool            cmdutl_getPermute(
        CMDUTL_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->fPermute;
    }
    
    
    bool            cmdutl_setPermute(
        CMDUTL_DATA     *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->fPermute = fValue;
        
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    char *          cmdutl_Arg(
        CMDUTL_DATA    *this
    )
    {
        char            *option = this->ppArgV[this->optIndex];
        
        this->subopt = 0;
        
        if (option != 0)
            this->optIndex++;
        
        return option;
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

        cmdutl_setObject(this, OBJ_NIL);
        cmdutl_setPath(this, OBJ_NIL);
        if (this->pSavedArgs) {
            obj_Release(this->pSavedArgs);
            this->pSavedArgs = OBJ_NIL;
        }
        if (this->pOptDefns) {
            mem_Free(this->pOptDefns);
            this->pOptDefns = NULL;
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

    CMDUTL_DATA *   cmdutl_Init(
        CMDUTL_DATA     *this,
        int             cArgs,
        char            **ppArgs
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

        if ( cArgs && ppArgs) {
            if(cmdutl_Reset(this, cArgs, ppArgs))
                ;
            else {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
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

     

    
    //---------------------------------------------------------------
    //                      I s  M o r e
    //---------------------------------------------------------------
    
    bool            cmdutl_IsMore(
        CMDUTL_DATA     *this
    )
    {
        char            *pArg = NULL;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if (this->ppArgV == NULL)
            return false;
#endif
        
        pArg = this->ppArgV[this->optIndex];
        if (pArg) {
            return true;
        }
        
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                      N e x t  A r g
    //---------------------------------------------------------------
    
    char *          cmdutl_NextArg(
        CMDUTL_DATA     *this
    )
    {
        char            *pArg = NULL;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if (this->ppArgV == NULL) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pArg = this->ppArgV[this->optIndex];
        this->optopt = 0;
        this->subopt = 0;
        if (pArg) {
            if ('-' == *pArg) {
                return NULL;
            }
            ++this->optIndex;
        }
        
        return pArg;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P a r s e
    //---------------------------------------------------------------
    
    int             cmdutl_Parse(
        CMDUTL_DATA     *this,
        const
        char            *pOptString
    )
    {
        int             type;
        char            *pNext;
        char            *pOption;
        int             iRc;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return -1;
        }
        if(this->ppArgV == NULL) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        pOption = this->ppArgV[this->optIndex];
        this->errmsg[0] = '\0';
        this->optopt = 0;
        this->pOptArg = NULL;
        if (pOption == NULL) {
            return -1;
        }
        else if (cmdutl_IsDashDash(pOption)) {
            this->optIndex++; /* consume "--" */
            return -1;
        }
        else if (!cmdutl_IsShortOpt(pOption)) {
            if (this->fPermute) {
                int         index = this->optIndex++;
                int         r = cmdutl_Parse(this, pOptString);
                cmdutl_Permute(this, index);
                this->optIndex--;
                return r;
            }
            else {
                return -1;
            }
        }
        pOption += this->subopt + 1;
        this->optopt = pOption[0];
        type = cmdutl_Argtype(pOptString, pOption[0]);
        pNext = this->ppArgV[this->optIndex + 1];
        switch (type) {
            case -1: {
                char str[2] = {0, 0};
                str[0] = pOption[0];
                this->optIndex++;
                iRc = cmdutl_CreateErrorMsg(this, "invalid option", str);
                return iRc;
            }
            case CMDUTL_ARG_OPTION_NONE:
                if (pOption[1]) {
                    this->subopt++;
                }
                else {
                    this->subopt = 0;
                    this->optIndex++;
                }
                return pOption[0];
            case CMDUTL_ARG_OPTION_REQUIRED:
                this->subopt = 0;
                this->optIndex++;
                if (pOption[1]) {
                    this->pOptArg = pOption + 1;
                }
                else if (pNext != NULL) {
                    this->pOptArg = pNext;
                    this->optIndex++;
                }
                else {
                    char str[2] = {0, 0};
                    str[0] = pOption[0];
                    this->pOptArg = NULL;
                    iRc = cmdutl_CreateErrorMsg(this, "option requires an argument", str);
                    return iRc;
                }
                return pOption[0];
            case CMDUTL_ARG_OPTION_OPTIONAL:
                this->subopt = 0;
                this->optIndex++;
                if (pOption[1])
                    this->pOptArg = pOption + 1;
                else
                    this->pOptArg = NULL;
                return pOption[0];
        }
        
        return 0;
    }

    
    
    //---------------------------------------------------------------
    //                     P a r s e  L o n g
    //---------------------------------------------------------------
    
    int             cmdutl_ParseLong(
        CMDUTL_DATA     *this,
        CMDUTL_OPTION   *pOptions,
        int             *longindex
    )
    {
        int             i;
        char            *pOption;
        int             iRc;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return -1;
        }
        if(this->ppArgV == NULL) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        this->errmsg[0] = '\0';
        this->optopt = 0;
        this->pOptArg = NULL;
        pOption = this->ppArgV[this->optIndex];
        if (pOption == 0) {
            return -1;
        }
        else if (cmdutl_IsDashDash(pOption)) {
            this->optIndex++;       /* consume "--" */
            return -1;
        }
        else if (cmdutl_IsShortOpt(pOption)) {
            return cmdutl_LongOptsFallback(this, pOptions, longindex);
        }
        else if (!cmdutl_IsLongOpt(pOption)) {
            if (this->fPermute) {
                int             index = this->optIndex++;
                int             r = cmdutl_ParseLong(this, pOptions, longindex);
                cmdutl_Permute(this, index);
                this->optIndex--;
                return r;
            }
            else {
                return -1;
            }
        }
        
        /* Parse as long option. */
        this->errmsg[0] = '\0';
        this->optopt = 0;
        this->pOptArg = NULL;
        pOption += 2; /* skip "--" */
        this->optIndex++;
        for (i = 0; !cmdutl_LongOptsEnd(pOptions, i); i++) {
            const
            char            *name = pOptions[i].pLongName;
            if (cmdutl_LongOptsMatch(name, pOption)) {
                char        *pArg;
                if (longindex)
                    *longindex = i;
                this->optopt = pOptions[i].shortName;
                pArg = cmdutl_LongOptsArg(pOption);
                if (pOptions[i].argOption == CMDUTL_ARG_OPTION_NONE && (pArg != NULL)) {
                    iRc = cmdutl_CreateErrorMsg(this, "option takes no arguments", name);
                    return iRc;
                }
                if (pArg != 0) {
                    this->pOptArg = pArg;
                }
                else if (pOptions[i].argOption == CMDUTL_ARG_OPTION_REQUIRED) {
                    this->pOptArg = this->ppArgV[this->optIndex];
                    if (this->pOptArg == NULL) {
                        iRc = cmdutl_CreateErrorMsg(this, "option requires an argument", name);
                        return iRc;
                    }
                    else
                        this->optIndex++;
                }
                return this->optopt;
            }
        }
        iRc = cmdutl_CreateErrorMsg(this, "invalid option", pOption);
        return iRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P r o c e s s  O p t i o n
    //---------------------------------------------------------------
    
    bool            cmdutl_ProcessOption(
        CMDUTL_DATA     *this,
        CMDUTL_OPTION   *pOption
    )
    {
        ERESULT         eRc;
        bool            fRc = false;
        int             iRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        char            option[16];
        void            *pPtr;

#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return fRc;
        }
        if (this->ppArgV == NULL) {
            DEBUG_BREAK();
            return fRc;
        }
#endif
        
        if (pOption) {
            pPtr = (uint8_t *)this->pObj + pOption->offset;
            if ((0 == pOption->offset) || (NULL == pPtr)) {
                return false;
            }
            switch (pOption->argType) {
                case CMDUTL_TYPE_EXEC:         // Execute given routine
                    if (pOption->pExec) {
                        eRc = pOption->pExec(this->pObj, this->pOptArg);
                        if (ERESULT_FAILED(eRc)) {
                            //FIXME: appl_Usage(this, "ERROR - Execute Routine for --%s failed!", pClo->pArgLong);
                            exit(8);
                        }
                    }
                    break;
                case CMDUTL_TYPE_BOOL:          // uint16_t - 0 or 1
                case CMDUTL_TYPE_INCR:          // uint16_t - Every occurence increases the
                    //                          // associated value (default is 0);
                    if (pPtr) {
                        *((uint16_t *)pPtr) += 1;
                    }
                    break;
                case CMDUTL_TYPE_NUMBER:        // Number pointer
                    break;
                case CMDUTL_TYPE_PATH:          // Path pointer
                    if (NULL == this->pOptArg) {
                        option[0] = this->optopt;
                        option[1] = '\0';
                        iRc =   cmdutl_CreateErrorMsg(
                                    this,
                                    "option requires an argument",
                                    option
                                );
                        return false;
                    }
                    else {
                        pPath = path_NewA(this->pOptArg);
                        *((PATH_DATA **)pPtr) = pPath;
                        pPath = OBJ_NIL;
                    }
                    break;
                case CMDUTL_TYPE_STRING:        // AStr pointer
                    if (NULL == this->pOptArg) {
                        option[0] = this->optopt;
                        option[1] = '\0';
                        iRc =   cmdutl_CreateErrorMsg(
                                    this,
                                    "option requires an argument",
                                    option
                                );
                        return false;
                    }
                    else {
                        pStr = AStr_NewA(this->pOptArg);
                        *((ASTR_DATA **)pPtr) = pStr;
                        pStr = OBJ_NIL;
                    }
                    break;
                default:
                    break;
            }
        }
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e s e t
    //---------------------------------------------------------------
    
    bool            cmdutl_Reset(
        CMDUTL_DATA     *this,
        int             cArgs,
        char            **ppArgs
    )
    {
        ASTRARRAY_DATA  *pArgs;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->fPermute = false;
        this->optIndex = 1;
        this->subopt = 0;
        this->pOptArg = NULL;
        this->errmsg[0] = '\0';
        this->ppArgV = ppArgs;
        
        if (cArgs && ppArgs) {
            pArgs = AStrArray_NewFromArgV(cArgs, (void *)ppArgs);
            cmdutl_setArgV(this, pArgs);
            obj_Release(pArgs);
        }
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e t u p  O p t i o n s
    //---------------------------------------------------------------
    
    ERESULT         cmdutl_SetupOptions(
        CMDUTL_DATA     *this,
        CMDUTL_OPTION   *pDefaultOptions,
        CMDUTL_OPTION   *pProgramOptions
    )
    {
        int             i;
        int             j;
        int             cDefault = 0;
        int             cProgram = 0;
        int             cTotal = 0;
        CMDUTL_OPTION   *pOptions = NULL;
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->ppArgV == NULL) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        
        if (pDefaultOptions) {
            pOptions = pDefaultOptions;
            for (i=0; !cmdutl_LongOptsEnd(pOptions, i); i++) {
                ++cDefault;
            }
        }
        
        if (pProgramOptions) {
            pOptions = pProgramOptions;
            for (i=0; !cmdutl_LongOptsEnd(pOptions, i); i++) {
                ++cDefault;
            }
        }
        
        cTotal = cDefault + cProgram + 1;
        this->pOptDefns = mem_Calloc(cTotal, sizeof(CMDUTL_OPTION));
        if (NULL == this->pOptDefns) {
            return ERESULT_OUT_OF_MEMORY;
        }
        j = 0;
        
        if (pDefaultOptions) {
            pOptions = pDefaultOptions;
            for (i=0; !cmdutl_LongOptsEnd(pOptions, i); i++) {
                this->pOptDefns[j++] = pOptions[i];
            }
        }
        
        if (pProgramOptions) {
            pOptions = pProgramOptions;
            for (i=0; !cmdutl_LongOptsEnd(pOptions, i); i++) {
                this->pOptDefns[j++] = pOptions[i];
            }
        }
        
        return ERESULT_SUCCESS;
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
        CMDUTL_DATA      *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_CMDUTL) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(CMDUTL_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


