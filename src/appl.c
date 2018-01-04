// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   appl.c
 *	Generated 06/05/2017 10:38:38
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
#include    <appl_internal.h>
#include    <dir.h>
#include    <misc.h>
#include    <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            appl_scan_body(
        void            *pData
    )
    {
        //APPL_DATA  *this = pData;
        
    }
#endif



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
        uint16_t    cArgs,
        const
        char        *pArgs[]
    )
    {
        APPL_DATA       *this;
        
        this = appl_Alloc( );
        if (this) {
            this = appl_Init(this, cArgs, pArgs);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

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
        APPL_DATA     *this
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
        APPL_DATA     *this,
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
    
    

    bool            appl_setParseArgs(
        APPL_DATA       *this,
        void            (*pValueDefaults)(OBJ_ID),
        int             (*pValueLong)(OBJ_ID, const char *),
        int             (*pValueShort)(OBJ_ID, const char *)
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pParseArgsDefaults = pValueDefaults;
        this->pParseArgsLong = pValueLong;
        this->pParseArgsShort = pValueShort;
        
        return true;
    }
    
    
    
    bool            appl_setProcessArgs(
        APPL_DATA       *this,
        int             (*pProcessArg)(OBJ_ID, const char *)
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pProcessArg = pProcessArg;
        
        return true;
    }
    
    
    
    bool            appl_setParseArgsDefaults(
        APPL_DATA       *this,
        void            (*pValue)(OBJ_ID)
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pParseArgsDefaults = pValue;
        
        return true;
    }
    
    
    
    bool            appl_setParseArgsLong(
        APPL_DATA       *this,
        int             (*pValue)(OBJ_ID, const char *)
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pParseArgsLong = pValue;
        
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
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                     A d d  P r o p e r t y
    //---------------------------------------------------------------
    
    ERESULT         appl_AddProperty(
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
        
        pOther = appl_New(this->cArgs, this->ppArgs);
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

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((APPL_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

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
    //                          I n i t
    //---------------------------------------------------------------

    APPL_DATA *     appl_Init(
        APPL_DATA       *this,
        uint16_t        cArgs,
        const
        char            **ppArgs
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
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_APPL);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&appl_Vtbl);
        
        appl_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->cArgs = cArgs;
        this->ppArgs = ppArgs;

    #ifdef NDEBUG
    #else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(APPL_DATA));
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
    
    int             appl_ParseArgs(
        APPL_DATA       *this
    )
    {
        int             wrkArgC = this->cArgs;
        const
        char            **ppWrkArgV = this->ppArgs;
        int             i;
#ifdef XYZZY
        int             offset;
        int             len;
        char            wrkstr[64];
#endif
        int             iRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        TRC_OBJ(this,"%s:\n", __func__);
        
        // Set option defaults here;
        this->fDebug = 0;
        this->fForce = 0;
        this->iVerbose = 0;
        if (this->pParseArgsDefaults) {
            this->pParseArgsDefaults(this);
        }

#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            fprintf(stdout, "\tcArgs = %d\n", wrkArgC);
            for (i=0; i<wrkArgC; ++i) {
                fprintf(stdout, "\targ[%d]=\"%s\"\n", i, ppWrkArgV[i]);
            }
            fprintf(stdout, "\n");
        }
#endif
        
        // Validate some of the input.
#ifdef XYZZY
        pResults->pProgramPath = argv[0];
        if( wrkArgC <= 1 ) {
            usage( "No arguments" );
        }
#endif
#ifdef XYZZY
        if( wrkArgC == 2 && ppWrkArgV[1][0] == '?' && ppWrkArgV[1][1] == 0) {
            appl_Usage( );
            exit(99);
        }
#endif
        
        // Process the switches.
        for (wrkArgC--,ppWrkArgV++; wrkArgC>0; wrkArgC--,ppWrkArgV++) {
            if (0 == strcmp(*ppWrkArgV, "--debug")) {
                ++this->fDebug;
            }
            else if (0 == strcmp(*ppWrkArgV, "--no-debug")) {
                --this->fDebug;
            }
            else if (0 == strcmp(*ppWrkArgV, "--force")) {
                ++this->fForce;
            }
            else if (0 == strcmp(*ppWrkArgV, "--no-force")) {
                --this->fForce;
            }
            else if (this->pParseArgsLong) {
                iRc = APPL_PARSE_RC_ERROR;
                iRc = this->pParseArgsLong(this, *ppWrkArgV);
                switch (iRc) {
                    case APPL_PARSE_RC_BUMP:
                        break;
                        
                    case APPL_PARSE_RC_NEXT:
                        break;
                        
                    default:
                        //appl_Usage(this, "Unknown flag");
                        break;
                }
            }
#ifdef  XYZZY
            else if (0 == strncmp(*ppWrkArgV, "--file", 6)) {
                if (*(*ppWrkArgV+6) == '\0') {
                    ++ppWrkArgV;
                    --wrkArgC;
                    if (wrkArgC <= 0) {
                        usage("ERROR: --file is missing the path!\n");
                        return 99;
                    }
                    pResults->pFile = strdup(*ppWrkArgV);
                }
                else {
                    pResults->pFile = strdup(*ppWrkArgV+6);
                }
            }
#endif
#ifdef  XYZZY
            else if (0 == strncmp(*argv, "--name", 6)) {
                wrkstr[0] = '\0';
                len = (int)strlen(*argv) - 6;
                offset = 6;
                if ('=' == *(*argv + offset)) {
                    ++offset;
                    --len;
                }
                if ('"' == *(*argv + offset)) {
                    ++offset;
                    len -= 2;
                }
                if (len > 63) {
                    len =  63;
                    fprintf(stderr, "WARNING - name is too long! Limiting length to 63!\n");
                }
                strncat(wrkstr, (*argv + offset), len);
                if (len) {
                    pResults->pName = strdup(wrkstr);
                }
            }
#endif
            else if (0 == strcmp(*ppWrkArgV, "--")) {
                --wrkArgC;
                ++ppWrkArgV;
                break;
            }
            else if (**ppWrkArgV == '-') {
                const
                char        *pWrk = *ppWrkArgV + 1;
                while (*pWrk) {
                    switch(tolower(*pWrk)) {
                        case 'd':
                            ++this->fDebug;
                            break;
#ifdef  XYZZY
                        case 'f':
                            ++pWrk;
                            if (*pWrk == '\0') {
                                ++ppWrkArgV;
                                --wrkArgC;
                                if (wrkArgC <= 0) {
                                    usage("ERROR: --file is missing the path!\n");
                                    return 99;
                                }
                                pResults->pFile = strdup(*ppWrkArgV);
                            }
                            else {
                                pResults->pFile = strdup(*ppWrkArgV);
                            }
                            pWrk = "";
                            continue;
                            break;
#endif
#ifdef  XYZZY
                        case 'm':
                            ++pResults->mFlag;
                            break;
                        case 'n':
                            ++pResults->nFlag;
                            break;
                        case 'r':       // -r<string> or -r=<string> or -r <string>
                            ++pWrk;
                            if (*pWrk == '=') {
                                ++pWrk;
                                if (*pWrk == '\0') {
                                    usage("ERROR: -r is missing its string!\n");
                                    return 99;
                                }
                                else {
                                    pResults->pR = strdup(pWrk);
                                }
                                pWrk = "";
                                continue;
                            }
                            else if (*pWrk == '\0') {
                                ++ppWrkArgV;
                                --wrkArgC;
                                if (wrkArgC <= 0) {
                                    usage("ERROR: -r is missing its string!\n");
                                    return 99;
                                }
                                pResults->pR = strdup(*ppWrkArgV);
                            }
                            else {
                                if (*pWrk == '\0') {
                                    usage("ERROR: -r is missing its string!\n");
                                    return 99;
                                }
                                else {
                                    pResults->pR = strdup(pWrk);
                                }
                                pWrk = "";
                                continue;
                            }
                            break;
#endif
                        default:
                            iRc = APPL_PARSE_RC_ERROR;
                            if (this->pParseArgsShort) {
                                iRc = this->pParseArgsShort(this, pWrk);
                            }
                            switch (iRc) {
                                case APPL_PARSE_RC_BUMP:
                                    ++pWrk;
                                    if (*pWrk == '\0') {
                                        ++ppWrkArgV;
                                        --wrkArgC;
                                    }
                                    break;
                                    
                                case APPL_PARSE_RC_NEXT:
                                    ++ppWrkArgV;
                                    --wrkArgC;
                                    break;
                                    
                                default:
                                    appl_Usage(this, "Unknown flag");
                                    break;
                            }
                    }
                    ++pWrk;
                }
            }
            else
                break;
        }
        
        this->cOptions = wrkArgC;
        this->ppOptions = ppWrkArgV;
        
        return 0;
    }
    
    
    
    //---------------------------------------------------------------
    //              P r o c e s s  A r g s
    //---------------------------------------------------------------
    
    int             appl_ProcessArgs(
        APPL_DATA       *this
    )
    {
        int             iRc = 0;
        int             i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pProcessArg) {
            for (i=0; i<this->cOptions; ++i) {
                iRc = this->pProcessArg(this, this->ppOptions[i]);
                if (iRc) {
                    break;
                }
            }
        }
        
        // Return to caller.
        return iRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P r o p e r t y
    //---------------------------------------------------------------
    
    NODE_DATA *     appl_Property(
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
        const
        char            *pProgramName = NULL;
        
        fprintf(pOutput, "\n\n");
        pProgramName = this->ppArgs[0];
        if (pMsg) {
            va_list     values;
            va_start(values, pMsg);
            vsnprintf(szMsg, sizeof(szMsg), pMsg, values);
            va_end(values);
            fprintf(pOutput, "?%s - %s\n\n", pProgramName, szMsg);
        }
        
        if (this->pUsageProgLine) {
            this->pUsageProgLine(this, pOutput);
        }
        else {
            fprintf(
                pOutput,
                "Usage: %s -[dfh]\n",
                pProgramName
            );
        }
        if (this->pUsageDesc) {
            this->pUsageDesc(this, pOutput);
        }
        fprintf( pOutput, "\t--[no-]debug   Set debug mode\n");
        fprintf( pOutput, "\t--[no-]force   Set force mode\n");
        fprintf( pOutput, "\t-h,--help      Display this help and exit\n");
        if (this->pUsageSwitches) {
            this->pUsageSwitches(this, pOutput);
        }
        fprintf(pOutput, "\n\n\n");
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


