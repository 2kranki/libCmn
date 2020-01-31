// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   appl.c
 * Generated 06/05/2017 10:38:38
 *
 */

/*
 There are several approaches to scanning/parsing command line arguments:
 
 One technique is to put the usage and argument scanning hard coded in
 the program.  For most programs, this is quite easy to do and not worth
 a lot of fuss over.
 
 One technique is to have a predefined tabular mechanism that defines
 what switches are and have the parsed output put into specific locations
 previously defined.
 
 Another technique is to parse the switches and options into a "parse"
 tree of nodes which would then be scanned similar to how we scan JSON
 text. Using this technique gives us the power of the JSON format which
 the long switches fit nicely such as --xyzzy="{1:23,2:\"/abc/a.txt\"}"
 */

/*
 Another thing to think about is what should be the format of our output?
 
 One technique is generate dynamic structures internally and supply
 routines to query the structures.  The more that I have thought about;
 the more that I think that this is the proper support.  A lot of programs
 are very simple in their need for command line parsing, but some such
 as the linker can be quite complex.  JSON or Apple's plist make very
 powerful ways of building the node structure.
 
 Another technique is to put the output in specific locations defined
 by the caller using a base and offset.  The problem with this is that
 it gets more difficult if a switch is entered more than once.  An
 example of this is designating multiple libraries using the linker.
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
#include    <appl_internal.h>
#include    <ascii.h>
#include    <dir.h>
#include    <misc.h>
#include    <scanner.h>
#include    <str.h>
#include    <trace.h>
#include    <utf8.h>



#ifdef	__cplusplus
extern "C" {
#endif
    
    // NOTE:    These options will be searched after the program option
    //          defaults.  So, they can be over-ridden by the same.
    CMDUTL_OPTION       defaultOptDefns[] = {
        {
            NULL,                       // Long
            '?',                        // Short
            CMDUTL_ARG_OPTION_NONE,     // Class
            CMDUTL_TYPE_EXEC,           // Type
            0,                          // Offset
            (void *)appl_Help,          // Executed Routine
            "Display Help"              // Description
        },
        {
            "debug",
            'd',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_BOOL,
            offsetof(APPL_DATA, fDebug),
            NULL,
            "Set Debug Mode"
        },
        {
            "force",
            'f',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_BOOL,
            offsetof(APPL_DATA, fForce),
            NULL,
            "Set Force Mode"
        },
        {
            "help",
            'h',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_EXEC,
            0,
            (void *)appl_Help,
            "Display Help"
        },
        {
            "quiet",
            's',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_BOOL,
            offsetof(APPL_DATA, fQuiet),
            NULL,
            "Set Quiet Mode"
            
        },
        {
            "silent",
            's',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_BOOL,
            offsetof(APPL_DATA, fQuiet),
            NULL,
            "Set Quiet Mode"
        },
        {
            "verbose",
            'v',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_INCR,
            offsetof(APPL_DATA, iVerbose),
            NULL,
            "Set Verbose Mode"
        },
        {NULL,0,0,0,0,NULL,NULL}                    // End of Table
    };


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //          C o n s t r u c t  P r o g r a m  L i n e
    //---------------------------------------------------------------
    
    ASTR_DATA *     appl_ConstructProgramLine(
        int             cArgs,
        const
        char            **ppArgs
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        uint32_t        i;
        
        if (cArgs) {
            pStr = AStr_NewA(*ppArgs);
            if (pStr) {
                for(i=1; i<cArgs; ++i) {
                    eRc = AStr_AppendA(pStr, " ");
                    if (ERESULT_FAILED(eRc)) {
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                        break;
                    }
                    eRc = AStr_AppendA(pStr, ppArgs[i]);
                    if (ERESULT_FAILED(eRc)) {
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                        break;
                    }
                }
            }
        }
        return pStr;
    }
    

    
    bool            appl_OptionsEnd(
        const
        CMDUTL_OPTION   *pOptions,
        int             i
    )
    {
        return (NULL == pOptions[i].pLongName) && (0 == pOptions[i].shortName);
    }
    
    
    
        //---------------------------------------------------------------
        //              P a r s e  P r o g r a m  L i n e
        //---------------------------------------------------------------
        
        ERESULT         appl_ParseProgramLine(
            const
            char            *pCmdStr,           // UTF-8 Command String
            ASTRCARRAY_DATA **ppArgV
        )
        {
            ERESULT         eRc = ERESULT_SUCCESS;
            char            quote;
            uint32_t        iMax;
            W32CHR_T        *pW32Str = NULL;
            W32CHR_T        *pW32Start = NULL;
            W32CHR_T        *pW32Cur = NULL;
            ASTRCARRAY_DATA *pArgV;

            // Do initialization.
    #ifdef NDEBUG
    #else
            if(NULL == pCmdStr) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
    #endif
            if (ppArgV) {
                *ppArgV = OBJ_NIL;
            }

            //TODO: Convert this process from ascii to UTF-8. Easiest would
            // be to create W32Str.
            iMax = (uint32_t)utf8_StrLenA(pCmdStr);
            pW32Str = utf8_ChrConToW32Str(pCmdStr);
            if (NULL == pW32Str) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
            pW32Cur = pW32Str;

            // Set up to scan the parameters.
            pArgV = AStrCArray_New( );
            if(NULL == pArgV) {
                DEBUG_BREAK();
                mem_Free(pW32Str);
                return ERESULT_OUT_OF_MEMORY;
            }

            // Scan off the each parameter.
            while( *pW32Cur ) {
                pW32Start = NULL;
                
                // Pass over white space.
                while( *pW32Cur && ascii_isWhiteSpaceW32(*pW32Cur) )
                    pW32Cur++;
                if (*pW32Cur == '\0') {
                    break;
                }
                
                pW32Start = pW32Cur;
                while( *pW32Cur ) {
                    // Scan off quoted Arguments.
                    if( (*pW32Cur == '"') || (*pW32Cur == '\'') ) {
                        quote = *pW32Cur++;
                        while( *pW32Cur && (*pW32Cur != quote) ) {
                            pW32Cur++;
                        }
                        pW32Cur++;      // Keep the quote.
                    }
                    // Scan until white space.
                    if ((*pW32Cur == '\0') || ascii_isWhiteSpaceW32(*pW32Cur)) {
                        break;
                    }
                    // Accumulate non-quoted char.
                    pW32Cur++;
                }
                if (!(*pW32Cur == '\0')) {
                    *pW32Cur = '\0';    // Mark the end of the argument.
                    pW32Cur++;
                }

                // Add the argument to the array.
                if( pW32Start && *pW32Start) {
                    ASTRC_DATA          *pStr = AStrC_NewW32(pW32Start);
                    eRc = AStrCArray_AppendAStrC(pArgV, pStr, NULL);
                    if (ERESULT_FAILED(eRc)) {
                        break;
                    }
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            // Return to caller.
            mem_Free(pW32Str);
            pW32Str = NULL;
            if (ppArgV) {
                *ppArgV = pArgV;
            }
            return eRc;
        }
        
        
        


    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    APPL_DATA *     appl_Alloc(
    )
    {
        APPL_DATA       *this;
        uint32_t        cbSize = sizeof(APPL_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    //                       F a t a l  E r r o r
    //---------------------------------------------------------------
    
    void            appl_ErrorFatal(
        const
        char            *fmt,
        ...
    )
    {
        va_list         argsp;
        
        va_start( argsp, fmt );
        fprintf( stderr, "Fatal Error:  " );
        vfprintf( stderr, fmt, argsp );
        va_end( argsp );
        fprintf( stderr, "\n\n\n" );
        
        exit( 99 );
    }
    
    
    
    void            appl_ErrorFatalArg(
        const
        char            *fmt,
        va_list         argsp
    )
    {
        
        fprintf( stderr, "Fatal Error:  " );
        vfprintf( stderr, fmt, argsp );
        fprintf( stderr, "\n\n\n" );
        
        exit( 99 );
    }
    
    
    
    void            appl_ErrorFatalArgOnEresult(
        ERESULT         eRc,
        const
        char            *fmt,
        va_list         argsp
    )
    {
        
        if (ERESULT_FAILED(eRc)) {
            fprintf( stderr, "Fatal Error:  " );
            vfprintf( stderr, fmt, argsp );
            fprintf( stderr, "\n\n\n" );
            exit( 100 );
        }
    }
    
    
    
    void            appl_ErrorFatalOnBool(
        bool            fRc,
        const
        char            *fmt,
        ...
    )
    {
        va_list         argsp;
        
        if (fRc) {
            va_start( argsp, fmt );
            fprintf( stderr, "Fatal Error:  " );
            vfprintf( stderr, fmt, argsp );
            va_end( argsp );
            fprintf( stderr, "\n\n\n" );
            exit( 100 );
        }
    }
    
    
    
    void            appl_ErrorFatalOnEresult(
        ERESULT         eRc,
        const
        char            *fmt,
        ...
    )
    {
        va_list         argsp;
        
        if (ERESULT_FAILED(eRc)) {
            va_start( argsp, fmt );
            fprintf( stderr, "Fatal Error:  " );
            vfprintf( stderr, fmt, argsp );
            va_end( argsp );
            fprintf( stderr, "\n\n\n" );
            exit( 100 );
        }
    }
    
    
    
    void            appl_ErrorFatalFLC(
        const
        char            *pFileName,
        uint32_t        linnum,
        uint16_t        colnum,
        const
        char            *fmt,
        ...
    )
    {
        va_list         argsp;
        
        va_start( argsp, fmt );
        fprintf(
                stderr,
                "Fatal Error: %s line: %d col: %d  ",
                (pFileName ? pFileName : ""),
                linnum,
                colnum
        );
        vfprintf( stderr, fmt, argsp );
        va_end( argsp );
        fprintf( stderr, "\n\n\n" );
        
        exit( 99 );
    }
    
    
    
    void            appl_ErrorFatalFLCArg(
        const
        char            *pFileName,
        uint32_t        linnum,
        uint16_t        colnum,
        const
        char            *fmt,
        va_list         argsp
    )
    {
        
        fprintf(
                stderr,
                "Fatal Error: %s line: %d col: %d  ",
                (pFileName ? pFileName : ""),
                linnum,
                colnum
                );
        vfprintf( stderr, fmt, argsp );
        fprintf( stderr, "\n\n\n" );
        
        exit( 99 );
    }
    
    
    
    APPL_DATA *     appl_New(
    )
    {
        APPL_DATA       *this;
        
        this = appl_Alloc( );
        if (this) {
            this = appl_Init(this);
        }
        return this;
    }
    
    
    APPL_DATA *     appl_NewWithArgV(
        int             cArgs,
        char            *ppArgs[],
        char            **ppEnv,
        CMDUTL_OPTION   *pPgmOptDefns
    )
    {
        APPL_DATA       *this;
        ERESULT         eRc;
        
        this = appl_Alloc( );
        if (this) {
            this = appl_Init(this);
            if (this) {
                eRc = appl_SetupFromArgV(this, cArgs, ppArgs, ppEnv, pPgmOptDefns);
            }
        }
        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      A r g s
    //---------------------------------------------------------------
    
    ASTRARRAY_DATA * appl_getArgs(
        APPL_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArgs;
    }
    
    
    bool            appl_setArgs(
        APPL_DATA       *this,
        ASTRARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pArgs) {
            obj_Release(this->pArgs);
        }
        this->pArgs = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          A r g  D e f s
    //---------------------------------------------------------------
    
    bool            appl_setArgDefs(
        APPL_DATA       *this,
        CMDUTL_OPTION   *pProgramArgs
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pPgmOptDefns = pProgramArgs;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C m d
    //---------------------------------------------------------------
    
    CMDUTL_DATA *   appl_getCmd(
        APPL_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pCmd;
    }
    
    
    bool            appl_setCmd(
        APPL_DATA       *this,
        CMDUTL_DATA     *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pCmd) {
            obj_Release(this->pCmd);
        }
        this->pCmd = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D a t e  T i m e
    //---------------------------------------------------------------
    
    DATETIME_DATA * appl_getDateTime(
        APPL_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pDateTime;
    }
    
    
    bool            appl_setDateTime(
        APPL_DATA       *this,
        DATETIME_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pDateTime) {
            obj_Release(this->pDateTime);
        }
        this->pDateTime = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          D e b u g
    //---------------------------------------------------------------
    
    bool            appl_getDebug(
        APPL_DATA       *this
    )
    {
        bool            fRc = false;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return fRc;
        }
#endif
        
        if (this->fDebug) {
            fRc = true;
        }
        
        return fRc;
    }
    
    bool            appl_setDebug(
        APPL_DATA       *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (fValue)
            this->fDebug = true;
        else
            this->fDebug = false;
        
        return true;
    }
    

    
    //---------------------------------------------------------------
    //                      E n v
    //---------------------------------------------------------------
    
    ASTRARRAY_DATA * appl_getEnv(
        APPL_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pEnv;
    }
    
    
    bool            appl_setEnv(
        APPL_DATA       *this,
        ASTRARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pEnv) {
            obj_Release(this->pEnv);
        }
        this->pEnv = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          F o r c e
    //---------------------------------------------------------------
    
    bool            appl_getForce(
        APPL_DATA       *this
    )
    {
        bool            fRc = false;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return fRc;
        }
#endif
        
        if (this->fForce) {
            fRc = true;
        }
        
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P a r s e  A r g s
    //---------------------------------------------------------------
    
    bool            appl_setParseArgs(
        APPL_DATA       *this,
        OBJ_ID          pObj,
        ERESULT         (*pValueDefaults)(OBJ_ID),
        int             (*pValueLong)(
                                      OBJ_ID          this,
                                      bool            fTrue,
                                      ASTR_DATA       *pName,
                                      ASTR_DATA       *pWrk,
                                      uint32_t        index,
                                      ASTRARRAY_DATA  *pArgs
                        ),
        int             (*pValueShort)(OBJ_ID, int *, const char ***)
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pObjPrs = pObj;
        this->pParseArgsDefaults = pValueDefaults;
        this->pParseArgsLong = pValueLong;
        this->pParseArgsShort = pValueShort;
        
        return true;
    }
    
    
    
    bool            appl_setProcessArgs(
        APPL_DATA       *this,
        OBJ_ID          pObj,
        ERESULT         (*pProcessInit)(OBJ_ID),
        ERESULT         (*pProcessArg)(OBJ_ID, ASTR_DATA *)
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pObjProcess = pObj;
        this->pProcessInit = pProcessInit;
        this->pProcessArg = pProcessArg;
        
        return true;
    }
    
    
    
    uint16_t        appl_getPriority(
        APPL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            appl_setPriority(
        APPL_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                P r o g r a m  P a t h
    //---------------------------------------------------------------
    
    PATH_DATA *     appl_getProgramPath(
        APPL_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pProgramPath;
    }
    
    
    bool            appl_setProgramPath(
        APPL_DATA       *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pProgramPath) {
            obj_Release(this->pProgramPath);
        }
        this->pProgramPath = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P r o p e r t i e s
    //---------------------------------------------------------------
    
    NODEHASH_DATA * appl_getProperties(
        APPL_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pProperties;
    }
    
    
    bool            appl_setProperties(
        APPL_DATA       *this,
        NODEHASH_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pProperties) {
            obj_Release(this->pProperties);
        }
        this->pProperties = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          Q u i e t
    //---------------------------------------------------------------
    
    bool            appl_getQuiet(
        APPL_DATA       *this
    )
    {
        bool            fRc = false;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return fRc;
        }
#endif
        
        if (this->fQuiet) {
            fRc = true;
        }
        
        return fRc;
    }
    
    
    
    uint32_t        appl_getSize(
        APPL_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return 0;
    }
    
    
    
    //---------------------------------------------------------------
    //                          U s a g e
    //---------------------------------------------------------------
    
    bool            appl_setUsage(
        APPL_DATA       *this,
        OBJ_ID          pObj,
        ERESULT         (*pUsageDesc)(OBJ_ID, FILE *, PATH_DATA *),
        ERESULT         (*pUsageProgLine)(OBJ_ID, FILE *, PATH_DATA *, const char *),
        ERESULT         (*pUsageOptions)(OBJ_ID, FILE *)
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pObjUsage = pObj;
        this->pUsageDesc = pUsageDesc;
        this->pUsageProgLine = pUsageProgLine;
        this->pUsageOptions = pUsageOptions;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          V e r b o s e
    //---------------------------------------------------------------
    
    int             appl_getVerbose(
        APPL_DATA       *this
    )
    {
        int             iRc = -1;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return iRc;
        }
#endif
        
        iRc = this->iVerbose;
        
        return iRc;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = appl__Assign(this,pOther);
     @endcode
     @param     this    APPL object pointer
     @param     pOther  a pointer to another APPL object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         appl_Assign(
        APPL_DATA		*this,
        APPL_DATA       *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !appl_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        appl      *pCopy = appl_Copy(this);
     @endcode
     @param     this    APPL object pointer
     @return    If successful, a APPL object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the APPL object.
     */
    APPL_DATA *     appl_Copy(
        APPL_DATA       *this
    )
    {
        APPL_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = appl_New( );
        if (pOther) {
            eRc = appl_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            appl_Dealloc(
        OBJ_ID          objId
    )
    {
        APPL_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        appl_setArgs(this, OBJ_NIL);
        appl_setCmd(this, OBJ_NIL);
        appl_setDateTime(this, OBJ_NIL);
        appl_setEnv(this, OBJ_NIL);
        appl_setProgramPath(this, OBJ_NIL);
        appl_setProperties(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         appl_Disable(
        APPL_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         appl_Enable(
        APPL_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E x e c
    //---------------------------------------------------------------
    
    int             appl_Exec(
        APPL_DATA       *this
    )
    {
        //ERESULT         eRc;
        //ASTR_DATA       *pStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef XYZZY
        eRc = appl_ParseArgs(this);
        if (ERESULT_FAILED(eRc)) {
            return 16;
        }

        if (this->pProcessArg) {
            if (this->pProcessInit) {
                eRc = this->pProcessInit(this->pObjProcess);
                if (ERESULT_FAILED(eRc)) {
                    return 16;
                }
            }
            for (;;) {
                pStr = appl_NextArg(this);
                if (OBJ_NIL == pStr) {
                    break;
                }
                eRc = this->pProcessArg(this->pObjProcess, pStr);
                if (ERESULT_FAILED(eRc)) {
                    return 16;
                }
            }
        }
#endif

        // Return to caller.
        return 0;
    }
    
    
    
    //---------------------------------------------------------------
    //                          E x i t
    //---------------------------------------------------------------
    
    void            appl_Exit(
        APPL_DATA       *this,
        int             exitCode
    )
    {
        //ERESULT         eRc;
        //ASTR_DATA       *pStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            goto exit;
        }
#endif
        
        // Do application clean up.
        
        // Return to caller.
    exit:
        exit(exitCode);
    }
    
    
    
    //---------------------------------------------------------------
    //                          H e l p
    //---------------------------------------------------------------
    
    ERESULT         appl_Help(
        APPL_DATA       *this,
        ASTR_DATA       *pStr
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        appl_UsageNoMsg(this);
        this->exitRC = 4;
        
        return ERESULT_GENERAL_FAILURE;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    APPL_DATA *     appl_Init(
        APPL_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(APPL_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }

        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_APPL);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            //obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_APPL);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&appl_Vtbl);
        
        this->pDateTime = DateTime_NewCurrent( );
        if (OBJ_NIL == this->pDateTime) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //fprintf(stderr, "sizeof(APPL_DATA) = %lu\n", sizeof(APPL_DATA));
        BREAK_NOT_BOUNDARY4((void *)sizeof(APPL_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         appl_IsEnabled(
        APPL_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s M o r e
    //---------------------------------------------------------------
    
    bool            appl_IsMore(
        APPL_DATA       *this
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = cmdutl_IsMore(this->pCmd);
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                  N e x t  A r g u m e n t
    //---------------------------------------------------------------
    
    char *          appl_NextArg(
        APPL_DATA       *this
    )
    {
        char            *pData = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pData = cmdutl_NextArg(this->pCmd);

        // Return to caller.
        return pData;
    }
    
    
    
    //---------------------------------------------------------------
    //              N u m b e r  O f  P r o p e r t i e s
    //---------------------------------------------------------------
    
    uint16_t        appl_NumberOfProperties(
        APPL_DATA       *this
    )
    {
        uint16_t        num = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (this->pProperties) {
            num = NodeHash_getSize(this->pProperties);
        }
        
        // Return to caller.
        return num;
    }
    
    
    
    //---------------------------------------------------------------
    //                 P r o c e s s  O p t i o n s
    //---------------------------------------------------------------
    
    ERESULT         appl_ProcessOptions(
        APPL_DATA       *this
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Process the arguments skipping the program path.
        eRc = cmdutl_ProcessOptions(this->pCmd);

        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                     P r o p e r t y  A d d
    //---------------------------------------------------------------
    
    ERESULT         appl_PropertyAdd(
        APPL_DATA       *this,
        NODE_DATA       *pData
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pData) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (OBJ_NIL == this->pProperties) {
            this->pProperties = NodeHash_New( );
            if (OBJ_NIL == this->pProperties) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        eRc = NodeHash_Add(this->pProperties, pData);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                    P r o p e r t y  F i n d
    //---------------------------------------------------------------
    
    NODE_DATA *     appl_PropertyFind(
        APPL_DATA       *this,
        const
        char            *pName
    )
    {
        //ERESULT         eRc;
        NODE_DATA       *pProperty = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            pProperty = NodeHash_FindA(this->pProperties, 0, pName);
        }
        
        // Return to caller.
        return pProperty;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          appl_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        APPL_DATA       *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
                // Query for an address to specific data within the object.
                // This should be used very sparingly since it breaks the
                // object's encapsulation.
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
                        
                    case 'C':
                        if (str_Compare("ClassObject", (char *)pStr) == 0) {
                            return (void *)&appl_ClassObj;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return appl_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Ensable", (char *)pStr) == 0) {
                            return appl_Enable;
                        }
                        break;

                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                 S e t u p  F r o m  A r g V
    //---------------------------------------------------------------
    
    /*!
     Set up to parse the given input resetting any prior parse data.
     @param     this    object pointer
     @param     cArgs   number of charater strings in ppArgs
     @param     ppArgV  point to a charater string array
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
                an ERESULT_* error code
     */
    ERESULT         appl_SetupFromArgV(
        APPL_DATA       *this,
        uint16_t        cArgs,
        char            *ppArgV[],
        char            **ppEnv,
        CMDUTL_OPTION   *pPgmOptDefns
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTRARRAY_DATA  *pArgs;
        PATH_DATA       *pPath;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Set program defaults here;
        this->fDebug = 0;
        this->fForce = 0;
        this->iVerbose = 0;
        if (this->pParseArgsDefaults) {
            eRc = this->pParseArgsDefaults(this->pObjPrs);
        }
        
        // Reset any prior parse data.
        appl_setArgs(this, OBJ_NIL);
        appl_setCmd(this, OBJ_NIL);
        appl_setProgramPath(this, OBJ_NIL);
        appl_setEnv(this, OBJ_NIL);
        
        pArgs = AStrArray_NewFromArgV(cArgs, (const char **)ppArgV);
        if (pArgs) {
            appl_setArgs(this, pArgs);           // Reset any prior data.
            obj_Release(pArgs);
            pArgs = OBJ_NIL;
        }
        else {
            eRc = ERESULT_OUT_OF_MEMORY;
        }
        if ((cArgs > 0) && ppArgV && ppArgV[0]) {
            pPath = Path_NewA(ppArgV[0]);
            appl_setProgramPath(this, pPath);
            obj_Release(pPath);
        }
        if (ppEnv) {
            pArgs = AStrArray_NewFromArrayA((const char **)ppEnv);
            if (pArgs) {
                appl_setEnv(this, pArgs);
                obj_Release(pArgs);
            }
        }
        this->pPgmOptDefns = pPgmOptDefns;

        this->pCmd = cmdutl_New(cArgs, ppArgV);
        if (OBJ_NIL == this->pCmd) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        cmdutl_setObject(this->pCmd, this);
        eRc = cmdutl_SetupOptions(this->pCmd, defaultOptDefns, pPgmOptDefns);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        
        return eRc;
    }
    
    
    bool            appl_SetupFromStr(
        APPL_DATA       *this,
        const
        char            *pCmdStr            // UTF-8 Command String
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
#ifdef XYZZY
        uint16_t        cbSize;
        int             Num = 0;
#endif
        //char            *pCurChr;
#ifdef XYZZY
        char            *pCurCmd;
        char            quote;
        int             cArg = 1;
        char            **pArgV = NULL;
#endif
        uint32_t        iMax;
        W32CHR_T        *pW32Str = NULL;
        W32CHR_T        *pW32Wrk = NULL;
        ASTRARRAY_DATA  *pArgs;

        // Do initialization.
#ifdef NDEBUG
#else
        if(!appl_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(NULL == pCmdStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        //TODO: Convert this process from ascii to UTF-8. Easiest would
        // be to create W32Str.
        iMax = (uint32_t)utf8_StrLenA(pCmdStr);
        pW32Str = utf8_ChrConToW32Str(pCmdStr);
        if (NULL == pW32Str) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        pW32Wrk = pW32Str;

        // Set up to scan the parameters.
        pArgs = AStrArray_New( );
        if(NULL == pArgs) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        //FIXME: pCurChr = pCmdStr;

        // Set program defaults here;
        this->fDebug = 0;
        this->fForce = 0;
        this->iVerbose = 0;
        if (this->pParseArgsDefaults) {
            eRc = this->pParseArgsDefaults(this->pObjPrs);
        }
        
        // Reset any prior parse data.
        appl_setArgs(this, OBJ_NIL);
        appl_setProgramPath(this, OBJ_NIL);
        appl_setEnv(this, OBJ_NIL);
        
        
        // Analyze input string to calculate array needed.
#ifdef XYZZY
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
        
        // Scan off the each parameter.
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
#endif

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = appl_ToDebugString(this,4);
     @endcode
     @param     this    APPL object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     appl_ToDebugString(
        APPL_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(appl) fDebug=%c fForce=%c iVerbose=%d\n",
                     this,
                     (this->fDebug ? 'T' : 'F'),
                     (this->fDebug ? 'T' : 'F'),
                     this->iVerbose
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(appl)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       U s a g e
    //---------------------------------------------------------------
    
    void            appl_Usage(
        APPL_DATA       *this,
        char            *pMsg,
                        ...
    )
    {
        FILE            *pOutput = stderr;
        char            szMsg[1024];
        ERESULT         eRc;
        PATH_DATA       *pName = OBJ_NIL;
        const
        char            *pNameA = "???";

        fprintf(pOutput, "\n\n");
        if (this->pProgramPath) {
            eRc = Path_SplitPath(this->pProgramPath, OBJ_NIL, OBJ_NIL, &pName);
            if (pName) {
                pNameA = Path_getData(pName);
            }
        }
        if (pMsg) {
            va_list     values;
            va_start(values, pMsg);
            vsnprintf(szMsg, sizeof(szMsg), pMsg, values);
            va_end(values);
            //fprintf(pOutput, "%s - %s\n\n", pNameA, szMsg);
            fprintf(pOutput, "%s\n", szMsg);
        }
        
        appl_UsageNoMsg(this);
        obj_Release(pName);
        pName = OBJ_NIL;
    }
    
    
    void            appl_UsageArg(
        APPL_DATA       *this,
        ASTR_DATA       *pStr,              // in-out
        CMDUTL_OPTION   *pOption
    )
    {
        ERESULT         eRc;
        int32_t         len;
        
        eRc = AStr_Truncate(pStr, 0);
        eRc = AStr_AppendA(pStr, "  ");
        if (pOption->shortName) {
            eRc = AStr_AppendCharW32(pStr, '-');
            eRc = AStr_AppendCharW32(pStr, pOption->shortName);
        }
        if (pOption->pLongName) {
            if (pOption->shortName) {
                eRc = AStr_AppendCharW32(pStr, ',');
            }
            eRc = AStr_AppendA(pStr, "--");
            eRc = AStr_AppendA(pStr, pOption->pLongName);
        }
        len = 25 - AStr_getLength(pStr);
        if (len > 0) {
            eRc = AStr_AppendCharRepeatW32(pStr, len, ' ');
        }
        else {
            eRc = AStr_AppendCharW32(pStr, ' ');
        }
        if (pOption->pDesc) {
            eRc = AStr_AppendA(pStr, pOption->pDesc);
        }
    }
    
    
    void            appl_UsageNoMsg(
        APPL_DATA       *this
    )
    {
        FILE            *pOutput = stderr;
        ERESULT         eRc;
        PATH_DATA       *pName = OBJ_NIL;
        const
        char            *pNameA = "???";
        int             i;
        ASTR_DATA       *pStr = OBJ_NIL;

        pStr = AStr_New( );
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK( );
            return;
        }
        if (this->pProgramPath) {
            eRc = Path_SplitPath(this->pProgramPath, OBJ_NIL, OBJ_NIL, &pName);
            if (pName) {
                pNameA = Path_getData(pName);
            }
        }
        fprintf(pOutput, "\n");
        fprintf(pOutput, "Usage:\n");
        if (this->pUsageProgLine) {
            this->pUsageProgLine(
                                 this->pObjUsage,
                                 pOutput,
                                 this->pProgramPath,
                                 pNameA
            );
        }
        else {
            fprintf(
                    pOutput,
                    "  %s [options]\n",
                    pNameA
            );
        }
        if (this->pUsageDesc) {
            fprintf(pOutput, "Description:\n");
            this->pUsageDesc(this->pObjUsage, pOutput, this->pProgramPath);
        }
        fprintf( pOutput, "Options:\n");
        for (i=0; !appl_OptionsEnd(defaultOptDefns, i); ++i) {
            appl_UsageArg(this, pStr, &defaultOptDefns[i]);
            fprintf( pOutput, "%s\n", AStr_getData(pStr));
        }
        //FIXME: Remove ifdef below
#ifdef XYZZY
        if (this->pProgramArgs) {
            for (i=0; !appl_OptionsEnd(this->pProgramArgs, i); ++i) {
                appl_UsageArg(this, pStr, &this->pProgramArgs[i]);
                fprintf( pOutput, "%s\n", AStr_getData(pStr));
            }
        }
#endif
        if (this->pUsageOptions) {
            this->pUsageOptions(this->pObjUsage, pOutput);
        }
        fprintf(pOutput, "\n\n\n");

        obj_Release(pName);
        pName = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    
    

    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            appl_Validate(
        APPL_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_APPL) )
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if( !(obj_getSize(this) >= sizeof(APPL_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //              V e r b o s e  I n c r e a s e
    //---------------------------------------------------------------
    
    ERESULT         appl_VerboseIncrease(
        APPL_DATA       *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        appl_UsageNoMsg(this);
        this->exitRC = 4;
        
        return ERESULT_GENERAL_FAILURE;
    }
    
    
    

    
#ifdef	__cplusplus
}
#endif


