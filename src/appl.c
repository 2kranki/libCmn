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
#include    <str.h>
#include    <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    APPL_CLO        defaultArgs[] = {
        {
            '?',                        // Short
            NULL,                       // Long
            APPL_ARG_PROGRAM,           // Class
            APPL_ARG_EXEC,              // Type
            0,                          // Offset
            (void *)appl_Help,          // Executed Routine
            "Display Help"              // Description
        },
        {
            'd',
            "debug",
            APPL_ARG_PROGRAM,
            APPL_ARG_BOOL,
            offsetof(APPL_DATA, fDebug),
            NULL,
            "Set Debug Mode"
        },
        {
            'f',
            "force",
            APPL_ARG_PROGRAM,
            APPL_ARG_BOOL,
            offsetof(APPL_DATA, fForce),
            NULL,
            "Set Force Mode"
        },
        {
            'h',
            "help",
            APPL_ARG_PROGRAM,
            APPL_ARG_EXEC,
            0,
            (void *)appl_Help,
            "Display Help"
        },
        {
            's',
            "quiet",
            APPL_ARG_PROGRAM,
            APPL_ARG_BOOL,
            offsetof(APPL_DATA, fQuiet),
            NULL,
            "Set Quiet Mode"
            
        },
        {
            's',
            "silent",
            APPL_ARG_PROGRAM,
            APPL_ARG_BOOL,
            offsetof(APPL_DATA, fQuiet),
            NULL,
            "Set Quiet Mode"
        },
        {
            'v',
            "verbose",
            APPL_ARG_PROGRAM,
            APPL_ARG_INCR,
            offsetof(APPL_DATA, iVerbose),
            NULL,
            "Set Verbose Mode"
        },
    };
    static
    int             cDefaultArgs = (sizeof(defaultArgs) / sizeof(APPL_CLO));


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //               F i n d  A r g u m e n t
    //---------------------------------------------------------------
    
    APPL_CLO *      appl_ArgFindLong(
        APPL_DATA       *this,
        const
        char            *pLong
    )
    {
        int             iRc = 0;
        APPL_CLO        *pClo = NULL;
        int             i = 0;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        // Search Group Args.
        if (this->cGroupArgs && this->pGroupArgs) {
            for (i=0; i<this->cGroupArgs; ++i) {
                if (this->pGroupArgs[i].pArgLong) {
                    iRc = str_Compare(pLong, this->pGroupArgs[i].pArgLong);
                    if (0 == iRc) {
                        pClo = &this->pGroupArgs[i];
                        return pClo;
                    }
                }
            }
        }
        
        // Search Program Args.
        if (this->cProgramArgs && this->pProgramArgs) {
            for (i=0; i<this->cProgramArgs; ++i) {
                if (this->pProgramArgs[i].pArgLong) {
                    iRc = str_Compare(pLong, this->pProgramArgs[i].pArgLong);
                    if (0 == iRc) {
                        pClo = &this->pProgramArgs[i];
                        return pClo;
                    }
                }
            }
        }
        
        // Search Default Args.
        if (cDefaultArgs) {
            for (i=0; i<cDefaultArgs; ++i) {
                if (defaultArgs[i].pArgLong) {
                    iRc = str_Compare(pLong, defaultArgs[i].pArgLong);
                    if (0 == iRc) {
                        pClo = &defaultArgs[i];
                        return pClo;
                    }
                }
            }
        }
        
        return pClo;
    }
    
    

    APPL_CLO *      appl_ArgFindShort(
        APPL_DATA       *this,
        char            chr
    )
    {
        int             iRc = 0;
        APPL_CLO        *pClo = NULL;
        int             i = 0;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        // Search Group Args.
        if (this->cGroupArgs && this->pGroupArgs) {
            for (i=0; i<this->cGroupArgs; ++i) {
                if (this->pGroupArgs[i].argChr) {
                    iRc = chr - this->pGroupArgs[i].argChr;
                    if (0 == iRc) {
                        pClo = &this->pGroupArgs[i];
                        return pClo;
                    }
                }
            }
        }
        
        // Search Program Args.
        if (this->cProgramArgs && this->pProgramArgs) {
            for (i=0; i<this->cProgramArgs; ++i) {
                if (this->pProgramArgs[i].argChr) {
                    iRc = chr - this->pProgramArgs[i].argChr;
                    if (0 == iRc) {
                        pClo = &this->pProgramArgs[i];
                        return pClo;
                    }
                }
            }
        }
        
        // Search Default Args.
        if (cDefaultArgs) {
            for (i=0; i<cDefaultArgs; ++i) {
                if (defaultArgs[i].argChr) {
                    iRc = chr - defaultArgs[i].argChr;
                    if (0 == iRc) {
                        pClo = &defaultArgs[i];
                        return pClo;
                    }
                }
            }
        }
        
        return pClo;
    }
    
    
    
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
    
    
    APPL_DATA *     appl_NewFromArgV(
        int             cArgs,
        const
        char            *ppArgs[],
        const
        char            **ppEnv
    )
    {
        APPL_DATA       *this;
        ERESULT         eRc;
        
        this = appl_Alloc( );
        if (this) {
            this = appl_Init(this);
            if (this) {
                eRc = appl_SetupFromArgV(this, cArgs, ppArgs, ppEnv);
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          A r g  D e f s
    //---------------------------------------------------------------
    
    bool            appl_setArgDefs(
        APPL_DATA       *this,
        uint16_t        cProgramArgs,
        APPL_CLO        *pProgramArgs,
        uint16_t        cGroupArgs,
        APPL_CLO        *pGroupArgs
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->cProgramArgs = cProgramArgs;
        this->pProgramArgs = pProgramArgs;
        this->cGroupArgs = cGroupArgs;
        this->pGroupArgs = pGroupArgs;
        
        appl_setLastError(this, ERESULT_SUCCESS);
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
        return fRc;
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         appl_getLastError(
        APPL_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            appl_setLastError(
        APPL_DATA       *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
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
        int             (*pProcessArg)(OBJ_ID, ASTR_DATA *)
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

        appl_setLastError(this, ERESULT_SUCCESS);
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

        appl_setLastError(this, ERESULT_SUCCESS);
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
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
        APPL_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return appl_getLastError(this);
        }
        if( !appl_Validate(pOther) ) {
            DEBUG_BREAK();
            return appl_getLastError(pOther);
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
        appl_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        appl_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return appl_getLastError(this);
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
        appl_setLastError(this, ERESULT_SUCCESS);
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
        appl_setDateTime(this, OBJ_NIL);
        appl_setEnv(this, OBJ_NIL);
        appl_setProgramPath(this, OBJ_NIL);
        appl_setProperties(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
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
            appl_setLastError(this, ERESULT_INVALID_OBJECT);
            return appl_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return appl_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        appl_setLastError(this, ERESULT_SUCCESS);
        return appl_getLastError(this);
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
            return appl_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        appl_setLastError(this, ERESULT_SUCCESS);
        return appl_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E x e c
    //---------------------------------------------------------------
    
    int             appl_Exec(
        APPL_DATA       *this
    )
    {
        int             iRc = 0;
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return appl_getLastError(this);
        }
#endif
        
        eRc = appl_ParseArgs(this);
        if (ERESULT_FAILED(eRc)) {
            return 8;
        }

        if (this->pProcessArg) {
            for (;;) {
                pStr = appl_NextArg(this);
                if (OBJ_NIL == pStr) {
                    break;
                }
                iRc = this->pProcessArg(this->pObjProcess, pStr);
                if (iRc) {
                    return iRc;
                }
            }
        }

        // Return to caller.
        appl_setLastError(this, ERESULT_SUCCESS);
        return iRc;
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
        exit(4);
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
        
        appl_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->pDateTime = dateTime_NewCurrent( );
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
        BREAK_NOT_BOUNDARY4(&this->eRc);
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
            return appl_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            appl_setLastError(this, ERESULT_SUCCESS_TRUE);
            return appl_getLastError(this);
        }
        
        // Return to caller.
        appl_setLastError(this, ERESULT_SUCCESS_FALSE);
        return appl_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                  N e x t  A r g u m e n t
    //---------------------------------------------------------------
    
    ASTR_DATA *     appl_NextArg(
        APPL_DATA       *this
    )
    {
        ASTR_DATA       *pData = OBJ_NIL;
        ERESULT         eRc = ERESULT_DATA_MISSING;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->nextArg <= AStrArray_getSize(this->pArgs)) {
            pData = AStrArray_Get(this->pArgs, this->nextArg);
            if (pData) {
                ++this->nextArg;
                eRc = ERESULT_SUCCESS;
            }
        }

        // Return to caller.
        appl_setLastError(this, eRc);
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
            num = nodeHash_getSize(this->pProperties);
        }
        
        // Return to caller.
        return num;
    }
    
    
    
    //---------------------------------------------------------------
    //                  P a r s e  A r g u m e n t s
    //---------------------------------------------------------------
    
    ERESULT         appl_ParseArgs(
        APPL_DATA       *this
    )
    {
        ERESULT         eRc;
        int             wrkArgC = 0;
        int             i;
#ifdef XYZZY
        int             offset;
        int             len;
        char            wrkstr[64];
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == this->pArgs) {
            DEBUG_BREAK();
            appl_setLastError(this, ERESULT_DATA_MISSING);
            return ERESULT_DATA_MISSING;
        }
#endif
        TRC_OBJ(this,"%s:\n", __func__);
        wrkArgC = AStrArray_getSize(this->pArgs);
#ifdef NDEBUG
#else
        if (wrkArgC < 1) {
            DEBUG_BREAK();
            appl_setLastError(this, ERESULT_DATA_MISSING);
            return ERESULT_DATA_MISSING;
        }
#endif

#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            fprintf(stdout, "\tcArgs = %d\n", wrkArgC);
            for (i=0; i<wrkArgC; ++i) {
                ASTR_DATA           *pStr = OBJ_NIL;
                pStr = AStrArray_Get(this->pArgs, (i+1));
                if (pStr) {
                    fprintf(stderr, "\targ[%d]=\"%s\"\n", i, AStr_getData(pStr));
               }
            }
            fprintf(stdout, "\n");
        }
#endif
        
        // Process the arguments skipping the program path.
        while (this->nextArg <= wrkArgC) {
            ASTR_DATA           *pStr = OBJ_NIL;
            ASTR_DATA           *pWrk = OBJ_NIL;
            uint32_t            len = 0;
            pStr = AStrArray_Get(this->pArgs, this->nextArg);
            if (pStr) {
                len = AStr_getLength(pStr);
                if (ERESULT_SUCCESS_EQUAL == AStr_CompareLeftA(pStr, "--not-")) {
                    if (6 == len) {
                        appl_Usage(this, "ERROR - Missing flag");
                        exit(8);
                    }
                    eRc = AStr_Right(pStr, (len - 6), &pWrk);
                    if (!ERESULT_FAILED(eRc)) {
                        eRc = appl_ParseArgsLong(this, false, pWrk);
                        obj_Release(pWrk);
                        pWrk = OBJ_NIL;
                    }
                }
                else if (ERESULT_SUCCESS_EQUAL == AStr_CompareLeftA(pStr, "--")) {
                    if (2 == len) {
                        // End of Option Scanning
                        break;
                    }
                    eRc = AStr_Right(pStr, (len - 2), &pWrk);
                    if (!ERESULT_FAILED(eRc)) {
                        eRc = appl_ParseArgsLong(this, true, pWrk);
                        obj_Release(pWrk);
                        pWrk = OBJ_NIL;
                    }
                }
                else if (ERESULT_SUCCESS_EQUAL == AStr_CompareLeftA(pStr, "-")) {
                    if (1 == len) {
                        appl_Usage(this, "ERROR - Missing flag");
                        exit(8);
                    }
                }
                else {
                    break;
                }
                ++this->nextArg;
            }
        }

        appl_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         appl_ParseArgsLong(
        APPL_DATA       *this,
        bool            fTrue,
        ASTR_DATA       *pArg
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pName = OBJ_NIL;
        ASTR_DATA       *pData = OBJ_NIL;
        uint32_t        idxEql = 0;
        uint32_t        len = 0;
        APPL_CLO        *pClo = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        len = AStr_getLength(pArg);
        eRc = AStr_CharFindNextW32(pArg, &idxEql, '=');
        if (ERESULT_FAILED(eRc)) {
            pName = AStr_Copy(pArg);
        }
        else {
            if (1 == idxEql) {
                appl_Usage(this, "ERROR - Missing flag - %s", AStr_getData(pArg));
                exit(8);
            }
            eRc = AStr_Left(pArg, (idxEql - 1), &pName);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
            if (idxEql < len) {
                eRc = AStr_Right(pArg, (len - idxEql), &pData);
                if (ERESULT_FAILED(eRc)) {
                    obj_Release(pName);
                    return eRc;
                }
            }
            else {
                appl_Usage(this, "ERROR - Missing data - %s", AStr_getData(pArg));
                exit(8);
            }
        }
        
        pClo = appl_ArgFindLong(this, AStr_getData(pName));
        if (NULL == pClo) {
            appl_Usage(this, "ERROR - Unknown flag - %s", AStr_getData(pName));
            exit(8);
        }
        
        if (pClo) {
            void            *pPtr = (uint8_t *)this + pClo->offset;
            switch (pClo->type) {
                case APPL_ARG_BOOL:             // uint8_t - 0 or 1
                    if (fTrue) {
                        *((uint8_t *)pPtr) = 1;
                    }
                    else {
                        *((uint8_t *)pPtr) = 0;
                    }
                    break;
                case APPL_ARG_EXEC:             // Execute given routine
                    eRc = pClo->pExec(this, pData);
                    if (ERESULT_FAILED(eRc)) {
                        appl_Usage(
                                   this,
                                   "ERROR - Execute Routine for --%s failed!",
                                   pClo->pArgLong
                        );
                        exit(8);
                    }
                    break;
                case APPL_ARG_INCR:             // uint16_t - Every occurence increases the
                    //                          // associated value (default is 0);
                    if (fTrue) {
                        *((uint16_t *)pPtr) += 1;
                    }
                    else {
                        *((uint16_t *)pPtr) -= 1;
                    }
                    break;
                case APPL_ARG_NUMBER:           // Number pointer
                    break;
                case APPL_ARG_PATH:             // Path pointer
                    if (OBJ_NIL == pData) {
                        if (this->nextArg < AStrArray_getSize(this->pArgs)) {
                            pData = AStrArray_Get(this->pArgs, this->nextArg);
                            if (pData) {
                                pData = AStr_Copy(pData);
                                ++this->nextArg;
                            }
                        }
                    }
                    if (pData) {
                        *((PATH_DATA **)pPtr) = path_NewFromAStr(pData);
                    }
                    else {
                        appl_Usage(
                                   this,
                                   "ERROR - Missing Path for --%s",
                                   pClo->pArgLong
                        );
                        exit(8);
                    }
                    break;
                case APPL_ARG_STRING:           // AStr pointer
                    if (OBJ_NIL == pData) {
                        if (this->nextArg < AStrArray_getSize(this->pArgs)) {
                            pData = AStrArray_Get(this->pArgs, this->nextArg);
                            if (pData) {
                                pData = AStr_Copy(pData);
                                ++this->nextArg;
                            }
                        }
                    }
                    if (pData) {
                        *((ASTR_DATA **)pPtr) = pData;
                        pData = OBJ_NIL;
                    }
                    else {
                        appl_Usage(
                                   this,
                                   "ERROR - Missing Path for --%s",
                                   pClo->pArgLong
                                   );
                        exit(8);
                    }
                    break;
                default:
                    break;
            }
        }

        // Return to caller.
        obj_Release(pName);
        obj_Release(pData);
        return eRc;
    }
    
    
    ERESULT         appl_ParseArgsShort(
        APPL_DATA       *this,
        int             *pArgC,
        const
        char            ***pppArgV
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        const
        char            *pWrk = **pppArgV + 1;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        while (*pWrk) {
            switch(tolower(*pWrk)) {
                case '?':
                case 'h':
                    appl_Usage(this, NULL);
                    exit(4);
                    break;
                case 'd':
                    ++this->fDebug;
                    break;
                default:
                    if (this->pParseArgsShort) {
                        eRc = this->pParseArgsShort(this->pObjPrs, pArgC, pppArgV);
                    }
            }
            ++pWrk;
        }
        
        // Return to caller.
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
            this->pProperties = nodeHash_New( 17 );
            if (OBJ_NIL == this->pProperties) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        eRc = nodeHash_Add(this->pProperties, pData);
        
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
            pProperty = nodeHash_FindA(this->pProperties, pName);
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
        const
        char            *ppArgV[],
        const
        char            **ppEnv
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
        appl_setProgramPath(this, OBJ_NIL);
        appl_setEnv(this, OBJ_NIL);

        pArgs = AStrArray_NewFromArgV(cArgs, ppArgV);
        if (pArgs) {
            appl_setArgs(this, pArgs);           // Reset any prior data.
            obj_Release(pArgs);
            pArgs = OBJ_NIL;
        }
        else {
            eRc = ERESULT_OUT_OF_MEMORY;
        }
        if ((cArgs > 0) && ppArgV && ppArgV[0]) {
            pPath = path_NewA(ppArgV[0]);
            appl_setProgramPath(this, pPath);
            obj_Release(pPath);
        }
        if (ppEnv) {
            pArgs = AStrArray_NewFromArrayA(ppEnv);
            if (pArgs) {
                appl_setEnv(this, pArgs);
                obj_Release(pArgs);
            }
        }
        this->nextArg = 2;

        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = appl_ToDebugString(this,4);
     @endcode:
     @param:    this    APPL object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
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
        
        appl_setLastError(this, ERESULT_SUCCESS);
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
            eRc = path_SplitPath(this->pProgramPath, OBJ_NIL, OBJ_NIL, &pName);
            if (pName) {
                pNameA = path_getData(pName);
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
        APPL_CLO        *pClo
    )
    {
        ERESULT         eRc;
        int32_t         len;
        
                eRc = AStr_Truncate(pStr, 0);
                eRc = AStr_AppendA(pStr, "  ");
                if (pClo->argChr) {
                    eRc = AStr_AppendCharW32(pStr, '-');
                    eRc = AStr_AppendCharW32(pStr, pClo->argChr);
                }
                if (pClo->pArgLong) {
                    if (pClo->argChr) {
                        eRc = AStr_AppendCharW32(pStr, ',');
                    }
                    eRc = AStr_AppendA(pStr, "--");
                    eRc = AStr_AppendA(pStr, pClo->pArgLong);
                }
                len = 25 - AStr_getLength(pStr);
                if (len > 0) {
                    eRc = AStr_AppendCharRepeatW32(pStr, len, ' ');
                }
                else {
                    eRc = AStr_AppendCharW32(pStr, ' ');
                }
                if (pClo->pDesc) {
                    eRc = AStr_AppendA(pStr, pClo->pDesc);
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
            eRc = path_SplitPath(this->pProgramPath, OBJ_NIL, OBJ_NIL, &pName);
            if (pName) {
                pNameA = path_getData(pName);
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
        if (cDefaultArgs) {
            for (i=0; i<cDefaultArgs; ++i) {
                appl_UsageArg(this, pStr, &defaultArgs[i]);
                fprintf( pOutput, "%s\n", AStr_getData(pStr));
            }
        }
        if (this->cProgramArgs) {
            for (i=0; i<this->cProgramArgs; ++i) {
                appl_UsageArg(this, pStr, &this->pProgramArgs[i]);
                fprintf( pOutput, "%s\n", AStr_getData(pStr));
            }
        }
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
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


