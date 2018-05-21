// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   clo.c
 *	Generated 06/05/2017 21:57:10
 *
 */

/*
 There are several approaches to scanning/parsing command line switches:
 
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
 routines to query the structures.
 
 Another technique is to put the output in specific locations defined
 by the caller using a base and offset.
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
#include    <clo_internal.h>
#include    <ascii.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    
#ifdef XYZZY
    CLO_ARG         defaultArgs[] = {
        {'d', "debug",  CLO_TYPE_BOOL,  0, offsetof(CLO_DATA, fDebug), NULL, "Set Debug Mode"},
        {'f', "force",  CLO_TYPE_BOOL,  0, offsetof(CLO_DATA, fForce), NULL, "Set Force Mode"},
        {'v', "verbose", CLO_TYPE_INCR, 0, offsetof(CLO_DATA, iVerbose), NULL,  "Set Verbose Mode"},
    };
    static
    int             cDefaultArgs = 5;
#endif
    
    
    

 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //               F i n d  A r g u m e n t
    //---------------------------------------------------------------
    
#ifdef XYZZY
    CLO_ARG *       clo_ArgFindLong(
        CLO_DATA        *this,
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
        if (this->cGroupArguments && this->pGroupArguments) {
            for (i=0; i<this->cGroupArguments; ++i) {
                if (this->pGroupArguments[i].pArgLong) {
                    iRc = str_Compare(pLong, this->pGroupArguments[i].pArgLong);
                    if (0 == iRc) {
                        pClo = &this->pGroupArguments[i];
                        return pClo;
                    }
                }
            }
        }
        
        // Search Program Args.
        if (this->cProgramArguments && this->pProgramArguments) {
            for (i=0; i<this->cProgramArguments; ++i) {
                if (this->pProgramArguments[i].pArgLong) {
                    iRc = str_Compare(pLong, this->pProgramArguments[i].pArgLong);
                    if (0 == iRc) {
                        pClo = &this->pProgramArguments[i];
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
    
    
    
    CLO_ARG *       clo_ArgFindShort(
        CLO_DATA        *this,
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
        if (this->cGroupArguments && this->pGroupArguments) {
            for (i=0; i<this->cGroupArguments; ++i) {
                if (this->pGroupArguments[i].argChr) {
                    iRc = chr - this->pGroupArguments[i].argChr;
                    if (0 == iRc) {
                        pClo = &this->pGroupArguments[i];
                        return pClo;
                    }
                }
            }
        }
        
        // Search Program Args.
        if (this->cProgramArguments && this->pProgramArguments) {
            for (i=0; i<this->cProgramArguments; ++i) {
                if (this->pProgramArguments[i].argChr) {
                    iRc = chr - this->pProgramArguments[i].argChr;
                    if (0 == iRc) {
                        pClo = &this->pProgramArguments[i];
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
#endif
    
    
    
    //---------------------------------------------------------------
    //               P a r s e  A r g u m e n t
    //---------------------------------------------------------------
    
#ifdef XYZZY
    ERESULT         appl_ArgParseLong(
                                      APPL_DATA       *this,
                                      int             *pArgC,
                                      const
                                      char            ***pppArgV
                                      )
    {
        int             iRc = 0;
        APPL_CLO        *pClo = NULL;
        int             i = 0;
        int             len = 0;
        int             cData = 0;
        int             cName = 0;
        const
        char            *pData;
        const
        char            *pName;
        const
        char            *pWrk;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef NDEBUG
#else
        pWrk = **pppArgV;
        if ((*pWrk == '-') && (*(pWrk+1) == '-'))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_DATA_ERROR;
        }
#endif
        pWrk = **pppArgV + 2;
        len = (int)strlen(pWrk);
        
        return ERESULT_SUCCESS;
    }
    
    
    
    ERESULT         appl_ArgParseShort(
                                       APPL_DATA       *this,
                                       int             *pArgC,
                                       const
                                       char            ***pppArgV
                                       )
    {
        int             iRc = 0;
        APPL_CLO        *pClo = NULL;
        int             i = 0;
        const
        char            *pWrk;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef NDEBUG
#else
        pWrk = **pppArgV;
        if (*pWrk == '-')
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_DATA_ERROR;
        }
#endif
        pWrk = **pppArgV + 1;
        
        
        
        return ERESULT_SUCCESS;
    }
    
    
    
    ASTRARRAY_DATA * clo_ScanArgs(
        ASTR_DATA        *pStr
    )
    {
        ASTRARRAY_DATA  *pArray = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        ERESULT         eRc;
        int             i;
        int             iMax;
        int32_t         chr;
        #define STATE_LOOKING 1
        #define STATE_PARM 2
        #define STATE_IN_DBL 3
        #define STATE_IN_SNGL 4
        int             state = STATE_LOOKING;
        
        if (pStr == OBJ_NIL) {
            return OBJ_NIL;
        }
        if (AStr_getLength(pStr) == 0) {
            return OBJ_NIL;
        }
        pArray = AStrArray_New();
        if (pArray == OBJ_NIL) {
            return OBJ_NIL;
        }
        
        i = 0;
        iMax = AStr_getLength(pStr);
        for (i=0; i < iMax; ++i) {
            chr = AStr_CharGetW32(pStr, i+1);
            switch (state) {
                case STATE_LOOKING:
                    if ((chr == ' ') || (chr == '\t')) {
                        continue;
                    }
                    if (pWrk == OBJ_NIL) {
                        pWrk = AStr_New( );
                    }
                    else {
                        obj_Release(pArray);
                        obj_Release(pWrk);
                        return OBJ_NIL;
                    }
                    if (chr == '"') {
                        //AStr_AppendCharW(pWrk, chr);
                        state = STATE_IN_DBL;
                        continue;
                    }
                    if (chr == '\'') {
                        //AStr_AppendCharW(pWrk, chr);
                        state = STATE_IN_SNGL;
                        continue;
                    }
                    AStr_AppendCharW32(pWrk, chr);
                    state = STATE_PARM;
                    break;
                    
                case STATE_PARM:
                    if (pWrk == OBJ_NIL) {
                        pWrk = AStr_New( );
                    }
                    if ((chr == ' ') || (chr == '\t')) {
                        eRc = AStrArray_AppendStr(pArray, pWrk, NULL);
                        if (ERESULT_FAILED(eRc)) {
                            obj_Release(pArray);
                            obj_Release(pWrk);
                            return OBJ_NIL;
                        }
                        state = STATE_LOOKING;
                        continue;
                    }
                    break;
                    
                default:
                    break;
            }
        }
        if (pArray && pWrk) {
            eRc = AStrArray_AppendStr(pArray, pWrk, NULL);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pArray);
                obj_Release(pWrk);
                return OBJ_NIL;
            }
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }
        
        return pArray;
    }
#endif
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    CLO_DATA *     clo_Alloc(
    )
    {
        CLO_DATA       *this;
        uint32_t        cbSize = sizeof(CLO_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ASTR_DATA *     clo_ConstructProgramLine(
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
    
    
    
    CLO_DATA *     clo_New(
        void
    )
    {
        CLO_DATA        *this;
        
        this = clo_Alloc( );
        if (this) {
            this = clo_Init(this);
        }
        return this;
    }
    
    
    CLO_DATA *     clo_NewFromArgV(
        uint16_t        cArgs,
        const
        char            **ppArgs
    )
    {
        CLO_DATA        *this;
        ERESULT         eRc;
        
        this = clo_Alloc( );
        if (this) {
            this = clo_Init(this);
            if (this) {
                eRc = clo_SetupFromArgV(this, cArgs, ppArgs);
            }
        } 
        return this;
    }




    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A r g s
    //---------------------------------------------------------------
    
    ASTRARRAY_DATA * clo_getArgs(
        CLO_DATA        *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        clo_setLastError(this, ERESULT_SUCCESS);
        return this->pArgs;
    }
    
    
    bool            clo_setArgs(
        CLO_DATA        *this,
        ASTRARRAY_DATA  *pValue
                                   )
    {
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pArgs) {
            obj_Release(this->pArgs);
        }
        this->pArgs = pValue;
        
        clo_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          A r g  D e f s
    //---------------------------------------------------------------
    
    bool            clo_setArgDefs(
        CLO_DATA        *this,
        uint16_t        cProgramArgs1,
        CLO_ARG         *pProgramArgs1,
        uint16_t        cProgramArgs2,
        CLO_ARG         *pProgramArgs2,
        uint16_t        cGroupArgs,
        CLO_ARG         *pGroupArgs
    )
    {
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->cProgramArgs1 = cProgramArgs1;
        this->pProgramArgs1 = pProgramArgs1;
        this->cProgramArgs2 = cProgramArgs2;
        this->pProgramArgs2 = pProgramArgs2;
        this->cGroupArgs = cGroupArgs;
        this->pGroupArgs = pGroupArgs;

        clo_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         clo_getLastError(
        CLO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            clo_setLastError(
        CLO_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                      P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        clo_getPriority(
        CLO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        clo_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            clo_setPriority(
        CLO_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        clo_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    //---------------------------------------------------------------
    //                  P r o g r a m  P a t h
    //---------------------------------------------------------------
    
    PATH_DATA *  clo_getProgramPath(
        CLO_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        clo_setLastError(this, ERESULT_SUCCESS);
        return this->pProgramPath;
    }
    
    
    bool        clo_setProgramPath(
        CLO_DATA    *this,
        PATH_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pProgramPath) {
            obj_Release(this->pProgramPath);
        }
        this->pProgramPath = pValue;
        
        clo_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                           S i z e
    //---------------------------------------------------------------
    
    uint32_t        clo_getSize(
        CLO_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        clo_setLastError(this, ERESULT_SUCCESS);
        return 0;
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
        ERESULT eRc = clo__Assign(this,pOther);
     @endcode
     @param     this    CLO object pointer
     @param     pOther  a pointer to another CLO object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         clo_Assign(
        CLO_DATA		*this,
        CLO_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return clo_getLastError(this);
        }
        if( !clo_Validate(pOther) ) {
            DEBUG_BREAK();
            return clo_getLastError(pOther);
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
        clo_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        clo_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return clo_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        clo      *pCopy = clo_Copy(this);
     @endcode
     @param     this    CLO object pointer
     @return    If successful, a CLO object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the CLO object.
     */
    CLO_DATA *     clo_Copy(
        CLO_DATA       *this
    )
    {
        CLO_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        //FIXME: pOther = clo_New(obj_getSize(this));
        if (pOther) {
            eRc = clo_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        clo_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            clo_Dealloc(
        OBJ_ID          objId
    )
    {
        CLO_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((CLO_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        clo_setArgs(this, OBJ_NIL);
        clo_setProgramPath(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         clo_Disable(
        CLO_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            clo_setLastError(this, ERESULT_INVALID_OBJECT);
            return clo_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return clo_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        clo_setLastError(this, ERESULT_SUCCESS);
        return clo_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         clo_Enable(
        CLO_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return clo_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        clo_setLastError(this, ERESULT_SUCCESS);
        return clo_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    CLO_DATA *      clo_Init(
        CLO_DATA        *this
    )
    {
        uint32_t        cbSize = sizeof(CLO_DATA);
        //ERESULT         eRc;
        //int             i;
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_CLO);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_CLO);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&clo_Vtbl);
        
        clo_setLastError(this, ERESULT_GENERAL_FAILURE);

    #ifdef NDEBUG
    #else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(CLO_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         clo_IsEnabled(
        CLO_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            clo_setLastError(this, ERESULT_SUCCESS_TRUE);
            return clo_getLastError(this);
        }
        
        // Return to caller.
        clo_setLastError(this, ERESULT_SUCCESS_FALSE);
        return clo_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          clo_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        CLO_DATA        *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
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
                            return clo_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Ensable", (char *)pStr) == 0) {
                            return clo_Enable;
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
    
    
    
    /* ParseCmdStr() sets up an ArgC/ArgV type array given
     * a command line string.
     */
    bool			clo_ParseCmdLine(
        CLO_DATA		*this,
        const
        char            *pCmdLineA
    )
    {
        ASTR_DATA       *pCmdLine = OBJ_NIL;
#ifdef XYZZY
        uint16_t        cbSize;
        int             Num = 0;
        char            *pCurCmd;
        char            quote;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if( pCmdLineA == NULL ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pCmdLine = AStr_NewA(pCmdLineA);
        if(OBJ_NIL == pCmdLine) {
            DEBUG_BREAK();
            return false;
        }


#ifdef XYZZY
        // Analyze input string to calculate array needed.
        this->cArg = 1;
        //TODO: cbSize = 2 * sizeof(char *);
        this->ppArg = (char **)mem_Malloc( cbSize );
        if( this->ppArg ) {
            this->flags |= GOT_ARGV;
        }
        else
            return false;
        *(this->ppArg) = "";     // Set program name.
        
        /* Scan off the each parameter.
         */
        while( *pCmdLineA ) {
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
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                 S e t u p  F r o m  A r g V
    //---------------------------------------------------------------
    
    ERESULT         clo_SetupFromArgV(
        CLO_DATA        *this,
        uint16_t        cArgs,
        const
        char            **ppArgs
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTRARRAY_DATA  *pArgs;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !clo_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Reset any prior parse data.
        
        pArgs = AStrArray_NewFromArgV(cArgs, ppArgs);
        clo_setArgs(this, pArgs);           // Reset any prior data.
        if (pArgs) {
            obj_Release(pArgs);
            pArgs = OBJ_NIL;
        }
        else {
            eRc = ERESULT_OUT_OF_MEMORY;
        }
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = clo_ToDebugString(this,4);
     @endcode
     @param     this    CLO object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     clo_ToDebugString(
        CLO_DATA      *this,
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
        if( !clo_Validate(this) ) {
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
                     "{%p(clo) size=%d\n",
                     this,
                     clo_getSize(this)
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
        j = snprintf(str, sizeof(str), " %p(clo)}\n", this);
        AStr_AppendA(pStr, str);
        
        clo_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            clo_Validate(
        CLO_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_CLO) )
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


        if( !(obj_getSize(this) >= sizeof(CLO_DATA)) ) {
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


