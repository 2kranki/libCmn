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
 
 *          cmdstr  : string (ws | arg)*            // First string is program path
 *                  ;
 *          arg     : name ('=' value)?
 *                  | string ('=' value)?
 *                  | array
 *                  | number
 *                  ;
 *          value   : name | string | number | array
 *                  ;
 *          array   : '[' ws* value (',' ws* value)* ws* ']'
 *                  ;
 *          name    : [a-zA-Z][a-zA-Z0-9_]*
 *                  ;
 *          ws      : ' ' | '\b' | '\f' | '\n' | '\r' | '\t'
 *                  ;
 *          string  : '"' string_chars* '"'
 *                  ;
 *          string_chars
 *                  : [\b\f\n\r\t\\\/ !]
 *                  | [#-~]
 *                  | '\\' '"'
 *                  | '\\' ('u'|'U') hexdigit*
 *                  | '\\' '\\'
 *                  ;
 *          number  : ('-')? [1-9][0-9]* ('.' [0-9]+)? exp?
 *                  | [0]([xX][0-9a-fA-F]*
 *                  | [0][0-7]*
 *                  ;
 *          exp     : ('e' | 'E') ('-' | '+')? [0-9]+
 *                  ;
 *

 
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

    static
    int             cmdutl_is_dashdash(
        const
        char            *arg
    )
    {
        return arg != NULL && arg[0] == '-' && arg[1] == '-' && arg[2] == '\0';
    }

    
    
    static
    int             cmdutl_is_shortopt(
        const
        char            *arg
    )
    {
        return arg != NULL && arg[0] == '-' && arg[1] != '-' && arg[1] != '\0';
    }

    
    
    static
    int             cmdutl_is_longopt(
        const
        char            *arg
    )
    {
        return arg != NULL && arg[0] == '-' && arg[1] == '-' && arg[2] != '\0';
    }

    
    
    static
    void            cmdutl_permute(
        CMDUTL_DATA     *this,
        int             index
    )
    {
        char            *nonoption = this->argv[index];
        int             i;
        
        for (i = index; i < this->optIndex - 1; i++) {
            this->argv[i] = this->argv[i + 1];
        }
        this->argv[this->optIndex - 1] = nonoption;
    }
    

    static
    int             cmdutl_argtype(
        const
        char            *optstring,
        char            c
    )
    {
        int             count = CMDUTL_ARG_OPTION_NONE;
        if (c == ':')
            return -1;
        for (; *optstring && c != *optstring; optstring++);
        if (!*optstring)
            return -1;
        if (optstring[1] == ':')
            count += optstring[2] == ':' ? 2 : 1;
        return count;
    }

    
    
    static
    bool            cmdutl_longopts_end(
        const
        CMDUTL_OPTION   *pOptions,
        int             i
    )
    {
        return (NULL == pOptions[i].pLongName) && (0 == pOptions[i].shortName);
    }

    
    
    static
    void            cmdutl_from_long(
        const
        CMDUTL_OPTION   *pOptions,
        char            *optstring
    )
    {
        char            *p = optstring;
        int             i;
        
        for (i = 0; !cmdutl_longopts_end(pOptions, i); i++) {
            if (pOptions[i].shortName) {
                int             a;
                *p++ = pOptions[i].shortName;
                for (a = 0; a < (int)pOptions[i].argOption; a++)
                    *p++ = ':';
            }
        }
        *p = '\0';
    }

    
    
    /* Unlike strcmp(), handles options containing "=". */
    static
    int             cmdutl_longopts_match(
        const
        char            *pLongName,
        const
        char            *option
    )
    {
        const
        char            *a = option;
        const
        char            *n = pLongName;
        
        if (pLongName == 0)
            return 0;
        for (; *a && *n && *a != '='; a++, n++)
            if (*a != *n)
                return 0;
        return *n == '\0' && (*a == '\0' || *a == '=');
    }

    
    
    /* Return the part after "=", or NULL. */
    static
    char *          cmdutl_longopts_arg(
        char            *option
    )
    {
        // Find '=' within option if it exists.
        for (; *option && *option != '='; option++)
            ;
        
        if (*option == '=')
            return option + 1;
        
        return NULL;
    }
    
    static
    int             cmdutl_long_fallback(
        CMDUTL_DATA     *this,
        const
        CMDUTL_OPTION   *pOptions,
        int             *longindex
    )
    {
        int             result;
        char            optstring[96 * 3 + 1];  /* 96 ASCII printable characters */
        cmdutl_from_long(pOptions, optstring);
        result = cmdutl_Parse(this, optstring);
        if (longindex != 0) {
            *longindex = -1;
            if (result != -1) {
                int i;
                for (i = 0; !cmdutl_longopts_end(pOptions, i); i++)
                    if (pOptions[i].shortName == this->optopt)
                        *longindex = i;
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


    char *          cmdutl_Arg(
        CMDUTL_DATA    *this
    )
    {
        char            *option = this->argv[this->optIndex];
        
        this->subopt = 0;
        
        if (option != 0)
            this->optIndex++;
        
        return option;
    }

    
    
    //--------------------------------------------------------------
    //                  B u i l d  E r r o r  M s g
    //--------------------------------------------------------------
    
    ERESULT         cmdutl_BuildErrorMsg(
        CMDUTL_DATA    *this,
        const
        char            *pMsg,
        const
        char            *pData
    )
    {
        uint32_t        p = 0;
        const
        char            *sep = " -- '";

        // Do initialization.
#ifdef NDEBUG
#else
        if( !cmdutl_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        
        while (*pMsg)
            this->errmsg[p++] = *pMsg++;
        while (*sep)
            this->errmsg[p++] = *sep++;
        while (p < sizeof(this->errmsg) - 2 && *pData)
            this->errmsg[p++] = *pData++;
        this->errmsg[p++] = '\'';
        this->errmsg[p++] = '\0';

        // Return to caller.
        return ERESULT_SUCCESS;
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

        cmdutl_setPath(this, OBJ_NIL);
        
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

        this->permute = 1;
        this->optIndex = 1;
        this->subopt = 0;
        this->optarg = 0;
        this->errmsg[0] = '\0';
        
        this->cArgs  = cArgs;
        this->ppArgs = ppArgs;

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
    //                          L o n g
    //---------------------------------------------------------------
    
    int             cmdutl_Long(
        CMDUTL_DATA     *this,
        const
        CMDUTL_OPTION   *pOptions,
        int             *longindex
    )
    {
        int             i;
        char            *option = this->argv[this->optIndex];
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        if (option == 0) {
            return -1;
        } else if (cmdutl_is_dashdash(option)) {
            this->optIndex++; /* consume "--" */
            return -1;
        } else if (cmdutl_is_shortopt(option)) {
            return cmdutl_long_fallback(this, pOptions, longindex);
        } else if (!cmdutl_is_longopt(option)) {
            if (this->permute) {
                int index = this->optIndex++;
                int r = cmdutl_Long(this, pOptions, longindex);
                cmdutl_permute(this, index);
                this->optIndex--;
                return r;
            } else {
                return -1;
            }
        }
        
        /* Parse as long option. */
        this->errmsg[0] = '\0';
        this->optopt = 0;
        this->optarg = 0;
        option += 2; /* skip "--" */
        this->optIndex++;
        for (i = 0; !cmdutl_longopts_end(pOptions, i); i++) {
            const char *name = pOptions[i].pLongName;
            if (cmdutl_longopts_match(name, option)) {
                char *arg;
                if (longindex)
                    *longindex = i;
                this->optopt = pOptions[i].shortName;
                arg = cmdutl_longopts_arg(option);
                if (pOptions[i].argOption == CMDUTL_ARG_OPTION_NONE && arg != 0) {
                    return cmdutl_BuildErrorMsg(this, "option takes no arguments", name);
                } if (arg != 0) {
                    this->optarg = arg;
                } else if (pOptions[i].argOption == CMDUTL_ARG_OPTION_REQUIRED) {
                    this->optarg = this->argv[this->optIndex];
                    if (this->optarg == 0)
                        return cmdutl_BuildErrorMsg(this, "option requires an argument", name);
                    else
                        this->optIndex++;
                }
                return this->optopt;
            }
        }
        return cmdutl_BuildErrorMsg(this, "invalid option", option);
    }

    
    
    //---------------------------------------------------------------
    //                          P a r s e
    //---------------------------------------------------------------
    
    int             cmdutl_Parse(
        CMDUTL_DATA     *this,
        const
        char            *optstring
    )
    {
        int             type;
        char            *next;
        char            *option = this->argv[this->optIndex];
        
#ifdef NDEBUG
#else
        if( !cmdutl_Validate(this) ) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        this->errmsg[0] = '\0';
        this->optopt = 0;
        this->optarg = 0;
        if (option == NULL) {
            return -1;
        } else if (cmdutl_is_dashdash(option)) {
            this->optIndex++; /* consume "--" */
            return -1;
        } else if (!cmdutl_is_shortopt(option)) {
            if (this->permute) {
                int index = this->optIndex++;
                int r = cmdutl_Parse(this, optstring);
                cmdutl_permute(this, index);
                this->optIndex--;
                return r;
            } else {
                return -1;
            }
        }
        option += this->subopt + 1;
        this->optopt = option[0];
        type = cmdutl_argtype(optstring, option[0]);
        next = this->argv[this->optIndex + 1];
        switch (type) {
            case -1: {
                char str[2] = {0, 0};
                str[0] = option[0];
                this->optIndex++;
                return cmdutl_BuildErrorMsg(this, "invalid option", str);
            }
            case CMDUTL_ARG_OPTION_NONE:
                if (option[1]) {
                    this->subopt++;
                } else {
                    this->subopt = 0;
                    this->optIndex++;
                }
                return option[0];
            case CMDUTL_ARG_OPTION_REQUIRED:
                this->subopt = 0;
                this->optIndex++;
                if (option[1]) {
                    this->optarg = option + 1;
                } else if (next != 0) {
                    this->optarg = next;
                    this->optIndex++;
                } else {
                    char str[2] = {0, 0};
                    str[0] = option[0];
                    this->optarg = 0;
                    return cmdutl_BuildErrorMsg(this, "option requires an argument", str);
                }
                return option[0];
            case CMDUTL_ARG_OPTION_OPTIONAL:
                this->subopt = 0;
                this->optIndex++;
                if (option[1])
                    this->optarg = option + 1;
                else
                    this->optarg = 0;
                return option[0];
        }
        
        return 0;
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


