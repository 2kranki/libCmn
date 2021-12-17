// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   CmdUtl.c
 *	Generated 01/31/2020 13:17:41
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
#include        <CmdUtl_internal.h>
#include        <ascii.h>
#include        <AStr.h>
#include        <AStrArray.h>
#include        <NodeArray.h>
#include        <NodeHash.h>
#include        <Scanner.h>
#include        <SrcErrors.h>
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

     int             CmdUtl_CreateErrorMsg(
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



     int             CmdUtl_IsDashDash(
         const
         char            *arg
     )
     {
         return arg != NULL && arg[0] == '-' && arg[1] == '-' && arg[2] == '\0';
     }



     int             CmdUtl_IsShortOpt(
         const
         char            *arg
     )
     {
         return arg != NULL && arg[0] == '-' && arg[1] != '-' && arg[1] != '\0';
     }



     int             CmdUtl_IsLongOpt(
         const
         char            *pArg
     )
     {
         return pArg != NULL && pArg[0] == '-' && pArg[1] == '-' && pArg[2] != '\0';
     }



     void            CmdUtl_Permute(
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



     int             CmdUtl_Argtype(
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



    /*! Check for the end of the Options Table.
     @return    true if end of option table
     */
     bool            CmdUtl_IsEndOfOptions(
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
     @param     pOptstring  an output area for the getopt-like string
     @return:   true if successful, otherwise false
     */
     bool            CmdUtl_OptstringFromLongOptions(
         const
         CMDUTL_OPTION   *pOptions,
         int             len,
         char            *pOptstring
     )
     {
         char            *p = pOptstring;
         int             i;

         for (i = 0; !CmdUtl_IsEndOfOptions(pOptions, i); i++) {
             if (pOptions[i].shortName && ascii_isAlphanumericA(pOptions[i].shortName)) {
                 int             a;
                 *p++ = pOptions[i].shortName;
                 --len;
                 if (len == 0) {
                     return false;
                 }
                 for (a = CMDUTL_ARG_OPTION_NONE; a < (int)pOptions[i].argOption; a++) {
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
     int             CmdUtl_LongOptsMatch(
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
     char *          CmdUtl_LongOptsArg(
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



     int             CmdUtl_LongOptsFallback(
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
         fRc = CmdUtl_OptstringFromLongOptions(pOptions, ((96 * 3) + 1), optstring);
         if (!fRc) {
             return '?';
         }

         // Now try to find the option using the option string.
         result = CmdUtl_Parse(this, optstring);
         if (pLongIndex != NULL) {
             *pLongIndex = -1;
             if (result != -1) {
                 // Found short name. Now translate optstring index into
                 // Options Table index.
                 int i;
                 for (i = 0; !CmdUtl_IsEndOfOptions(pOptions, i); i++)
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

    CMDUTL_DATA *     CmdUtl_Alloc (
        void
    )
    {
        CMDUTL_DATA       *this;
        uint32_t        cbSize = sizeof(CMDUTL_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ASTR_DATA *     CmdUtl_ArgvToAStr(
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
    //FIXME: We need to make this aware of the Array and Hash allowed
    //FIXME: in parameters since they may have whitespace between elements.
    ASTRARRAY_DATA * CmdUtl_CommandStringToArray(
        const
        char            *pCmdStrA
    )
    {
        //ERESULT         eRc;
        ASTRARRAY_DATA  *pArgs = OBJ_NIL;
        SCANNER_DATA    *pScan = OBJ_NIL;

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
        pScan = Scanner_NewA(pCmdStrA);
        if (OBJ_NIL == pScan) {
            //return ERESULT_OUT_OF_MEMORY;
            return OBJ_NIL;
        }
        Scanner_setSeperator(pScan, '=');
        pArgs = Scanner_ScanStringToAstrArray(pScan);
        obj_Release(pScan);
        pScan = OBJ_NIL;

        // Return to caller.
        return pArgs;
    }



    CMDUTL_DATA *     CmdUtl_New (
        void
    )
    {
        CMDUTL_DATA       *this;
        
        this = CmdUtl_Alloc( );
        if (this) {
            this = CmdUtl_Init(this);
        } 
        return this;
    }



    CMDUTL_DATA *   CmdUtl_NewArgs(
        int             cArgs,
        char            **ppArgs
    )
    {
        CMDUTL_DATA     *this;
        ERESULT         eRc;

        this = CmdUtl_New( );
        if (this) {
            eRc = CmdUtl_Reset(this, cArgs, ppArgs);
        }
        return this;
    }


    CMDUTL_DATA *   CmdUtl_NewRescan(
        int             cArgs,
        char            **ppArgs
    )
    {
        CMDUTL_DATA     *this = OBJ_NIL;
        ASTR_DATA       *pStr;
        ASTRARRAY_DATA  *pArgs;
        ERESULT         eRc;

        pStr = CmdUtl_ArgvToAStr(cArgs, (const char **)ppArgs);
        if (pStr) {
            this = CmdUtl_New( );
            if (this) {
                eRc = CmdUtl_Reset(this, 0, NULL);
                if (!ERESULT_FAILED(eRc)) {
                    pArgs = CmdUtl_CommandStringToArray(AStr_getData(pStr));
                    if (pArgs) {
                        CmdUtl_setArgV(this, pArgs);
                        obj_Release(pArgs);
                        pArgs = OBJ_NIL;
                    } else {
                        obj_Release(this);
                        this = OBJ_NIL;
                    }
                }
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //--------------------------------------------------------------
    //                          A r g V
    //--------------------------------------------------------------

    ASTRARRAY_DATA *    CmdUtl_getArgV (
        CMDUTL_DATA         *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pSavedArgs;
    }


    bool            CmdUtl_setArgV (
        CMDUTL_DATA     *this,
        ASTRARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
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
    //                      F a t a l  E r r o r
    //--------------------------------------------------------------

    bool            CmdUtl_setFatalError (
        CMDUTL_DATA     *this,
        void            (*pFatalError)(
            const
            char            *fmt,
                            ...
        )
    )
    {
#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->pFatalError = pFatalError;

        return true;
    }



    //--------------------------------------------------------------
    //                       O b j e c t
    //--------------------------------------------------------------

    OBJ_ID      CmdUtl_getObject (
        CMDUTL_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pObj;
    }


    bool        CmdUtl_setObject (
        CMDUTL_DATA *this,
        OBJ_ID      pValue
    )
    {
#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        /*** NOT OWNED
        obj_Retain(pValue);
        if (this->pObj) {
            obj_Release(this->pObj);
        }
         */
        this->pObj = pValue;

        return true;
    }



    //--------------------------------------------------------------
    //              O p t i o n  D e f i n i t i o n s
    //--------------------------------------------------------------

    CMDUTL_OPTION * CmdUtl_getOptionDefinitions (
        CMDUTL_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pOptDefns;
    }



    //--------------------------------------------------------------
    //                          P a t h
    //--------------------------------------------------------------

    PATH_DATA *     CmdUtl_getPath (
        CMDUTL_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pPath;
    }


    bool        CmdUtl_setPath (
        CMDUTL_DATA *this,
        PATH_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
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

    bool            CmdUtl_getPermute (
        CMDUTL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->fPermute;
    }


    bool            CmdUtl_setPermute (
        CMDUTL_DATA     *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->fPermute = fValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        CmdUtl_getSize (
        CMDUTL_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!CmdUtl_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  CmdUtl_getSuperVtbl (
        CMDUTL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!CmdUtl_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A r g
    //---------------------------------------------------------------

    char *          CmdUtl_Arg(
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
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = CmdUtl_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another CMDUTL object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         CmdUtl_Assign (
        CMDUTL_DATA		*this,
        CMDUTL_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!CmdUtl_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!CmdUtl_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

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
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             CmdUtl_Compare (
        CMDUTL_DATA     *this,
        CMDUTL_DATA     *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!CmdUtl_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!CmdUtl_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
#endif

        return iRc;
    }

   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        CmdUtl      *pCopy = CmdUtl_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a CMDUTL object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    CMDUTL_DATA *     CmdUtl_Copy (
        CMDUTL_DATA       *this
    )
    {
        CMDUTL_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!CmdUtl_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef CMDUTL_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = CmdUtl_New( );
        if (pOther) {
            eRc = CmdUtl_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            CmdUtl_Dealloc (
        OBJ_ID          objId
    )
    {
        CMDUTL_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!CmdUtl_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((CMDUTL_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        CmdUtl_setObject(this, OBJ_NIL);
        CmdUtl_setPath(this, OBJ_NIL);
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
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        CmdUtl      *pDeepCopy = CmdUtl_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a CMDUTL object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    CMDUTL_DATA *     CmdUtl_DeepyCopy (
        CMDUTL_DATA       *this
    )
    {
        CMDUTL_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!CmdUtl_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = CmdUtl_New( );
        if (pOther) {
            eRc = CmdUtl_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         CmdUtl_Disable (
        CMDUTL_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!CmdUtl_Validate(this)) {
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

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         CmdUtl_Enable (
        CMDUTL_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!CmdUtl_Validate(this)) {
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
    //                          I n i t
    //---------------------------------------------------------------

    CMDUTL_DATA *   CmdUtl_Init (
        CMDUTL_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(CMDUTL_DATA);
        //ERESULT         eRc;
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_CMDUTL);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&CmdUtl_Vtbl);
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!CmdUtl_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
        fprintf(
                stderr, 
                "CmdUtl::sizeof(CMDUTL_DATA) = %lu\n", 
                sizeof(CMDUTL_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(CMDUTL_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         CmdUtl_IsEnabled (
        CMDUTL_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!CmdUtl_Validate(this)) {
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
    //                      I s  M o r e
    //---------------------------------------------------------------

    bool            CmdUtl_IsMore (
        CMDUTL_DATA     *this
    )
    {
        char            *pArg = NULL;

#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if (NULL == this->ppArgV) {
            return false;
        }
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

    char *          CmdUtl_NextArg (
        CMDUTL_DATA     *this
    )
    {
        char            *pArg = NULL;

#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if (NULL == this->ppArgV) {
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

    int             CmdUtl_Parse (
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
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
            return -1;
        }
        if (NULL == this->ppArgV) {
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
        else if (CmdUtl_IsDashDash(pOption)) {
            this->optIndex++; /* consume "--" */
            return -1;
        }
        else if (!CmdUtl_IsShortOpt(pOption)) {
            if (this->fPermute) {
                int         index = this->optIndex++;
                int         r = CmdUtl_Parse(this, pOptString);
                CmdUtl_Permute(this, index);
                this->optIndex--;
                return r;
            }
            else {
                return -1;
            }
        }
        pOption += this->subopt + 1;
        this->optopt = pOption[0];
        type = CmdUtl_Argtype(pOptString, pOption[0]);
        pNext = this->ppArgV[this->optIndex + 1];
        switch (type) {
            case -1: {
                char str[2] = {0, 0};
                str[0] = pOption[0];
                this->optIndex++;
                iRc = CmdUtl_CreateErrorMsg(this, "invalid option", str);
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
                    iRc = CmdUtl_CreateErrorMsg(this, "option requires an argument", str);
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

    int             CmdUtl_ParseLong (
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
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
            return -1;
        }
        if (NULL == this->ppArgV) {
            DEBUG_BREAK();
            return -1;
        }
#endif

        this->errmsg[0] = '\0';
        this->optopt = 0;
        this->pOptArg = NULL;
        pOption = this->ppArgV[this->optIndex];
        if (pOption == NULL) {
            return -1;
        }
        else if (CmdUtl_IsDashDash(pOption)) {
            this->optIndex++;       /* consume "--" */
            return -1;
        }
        else if (CmdUtl_IsShortOpt(pOption)) {
            return CmdUtl_LongOptsFallback(this, pOptions, longindex);
        }
        else if (!CmdUtl_IsLongOpt(pOption)) {
            if (this->fPermute) {
                int             index = this->optIndex++;
                int             r = CmdUtl_ParseLong(this, pOptions, longindex);
                CmdUtl_Permute(this, index);
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
        for (i = 0; !CmdUtl_IsEndOfOptions(pOptions, i); i++) {
            const
            char            *name = pOptions[i].pLongName;
            if (CmdUtl_LongOptsMatch(name, pOption)) {
                char        *pArg;
                if (longindex)
                    *longindex = i;
                this->optopt = pOptions[i].shortName;
                pArg = CmdUtl_LongOptsArg(pOption);
                if (pOptions[i].argOption == CMDUTL_ARG_OPTION_NONE && (pArg != NULL)) {
                    iRc = CmdUtl_CreateErrorMsg(this, "option takes no arguments", name);
                    return iRc;
                }
                if (pArg != 0) {
                    this->pOptArg = pArg;
                }
                else if (pOptions[i].argOption == CMDUTL_ARG_OPTION_REQUIRED) {
                    this->pOptArg = this->ppArgV[this->optIndex];
                    if (this->pOptArg == NULL) {
                        iRc = CmdUtl_CreateErrorMsg(this, "option requires an argument", name);
                        return iRc;
                    }
                    else
                        this->optIndex++;
                }
                return this->optopt;
            }
        }
        iRc = CmdUtl_CreateErrorMsg(this, "invalid option", pOption);
        return iRc;
    }



    //---------------------------------------------------------------
    //                 P r o c e s s  O p t i o n
    //---------------------------------------------------------------

    ERESULT         CmdUtl_ProcessOption (
        CMDUTL_DATA     *this,
        CMDUTL_OPTION   *pOption
    )
    {
        ERESULT         eRc;
        int             iRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        char            option[16];
        void            *pPtr;

#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->ppArgV) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif

        if (pOption) {
            pPtr = (uint8_t *)this->pObj + pOption->offset;
            if (NULL == pPtr) {
                return false;
            }
            switch (pOption->argType) {

                case CMDUTL_TYPE_EXEC:         // Execute given routine
                    if (pOption->pExec) {
                        eRc = pOption->pExec(this->pObj, this->pOptArg);
                        if (ERESULT_FAILED(eRc)) {
                            if (this->pFatalError) {
                                this->pFatalError(
                                            "ERROR - Execute Routine for --%s failed!",
                                            pOption->pLongName
                                );
                            }
                            return eRc;
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
                        iRc =   CmdUtl_CreateErrorMsg(
                                    this,
                                    "option requires a path argument",
                                    option
                                );
                        return ERESULT_DATA_MISSING;
                    }
                    else {
                        pPath = Path_NewA(this->pOptArg);
                        *((PATH_DATA **)pPtr) = pPath;
                        pPath = OBJ_NIL;
                    }
                    break;

                case CMDUTL_TYPE_STRING:        // AStr pointer
                    if (NULL == this->pOptArg) {
                        option[0] = this->optopt;
                        option[1] = '\0';
                        iRc =   CmdUtl_CreateErrorMsg(
                                    this,
                                    "option requires a string argument",
                                    option
                                );
                        return ERESULT_DATA_MISSING;
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

        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                 P r o c e s s  O p t i o n s
    //---------------------------------------------------------------

    ERESULT         CmdUtl_ProcessOptions (
        CMDUTL_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             iRc;
        int             longIndex;

#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->ppArgV) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        if (NULL == this->pOptDefns) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif

        // Parse and process the next group of options.
        for (;;) {
            longIndex = -1;
            iRc = CmdUtl_ParseLong(this, this->pOptDefns, &longIndex);
            if (-1 == iRc)
                break;
            if ('?' == iRc) {
                eRc = ERESULT_KEY_NOT_FOUND;
                break;
            }
            eRc = CmdUtl_ProcessOption(this, &this->pOptDefns[longIndex]);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
       }

        return eRc;
    }



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = CmdUtl_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "CmdUtl", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          CmdUtl_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        CMDUTL_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!CmdUtl_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(CMDUTL_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)CmdUtl_Class();
                break;
                
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'S':
                    if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                        return &this->pSuperVtbl;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return CmdUtl_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return CmdUtl_Enable;
                        }
                        break;

#ifdef  CMDUTL_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return CmdUtl_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return CmdUtl_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return CmdUtl_ToDebugString;
                        }
#ifdef  CMDUTL_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return CmdUtl_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == CmdUtl_ToDebugString)
                    return "ToDebugString";
#ifdef  CMDUTL_JSON_SUPPORT
                if (pData == CmdUtl_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e s e t
    //---------------------------------------------------------------

    bool            CmdUtl_Reset(
        CMDUTL_DATA     *this,
        int             cArgs,
        char            **ppArgs
    )
    {
        ASTRARRAY_DATA  *pArgs;

#ifdef NDEBUG
#else
        if( !CmdUtl_Validate(this) ) {
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
            CmdUtl_setArgV(this, pArgs);
            obj_Release(pArgs);
        }

        return true;
    }



    //---------------------------------------------------------------
    //                      S e t u p  O p t i o n s
    //---------------------------------------------------------------

    ERESULT         CmdUtl_SetupOptions(
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
        if( !CmdUtl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->ppArgV) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif

        if (pDefaultOptions) {
            pOptions = pDefaultOptions;
            for (i=0; !CmdUtl_IsEndOfOptions(pOptions, i); i++) {
                ++cDefault;
            }
        }

        if (pProgramOptions) {
            pOptions = pProgramOptions;
            for (i=0; !CmdUtl_IsEndOfOptions(pOptions, i); i++) {
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
            for (i=0; !CmdUtl_IsEndOfOptions(pOptions, i); i++) {
                this->pOptDefns[j++] = pOptions[i];
            }
        }

        if (pProgramOptions) {
            pOptions = pProgramOptions;
            for (i=0; !CmdUtl_IsEndOfOptions(pOptions, i); i++) {
                this->pOptDefns[j++] = pOptions[i];
            }
        }

        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = CmdUtl_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     CmdUtl_ToDebugString (
        CMDUTL_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!CmdUtl_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    CmdUtl_getSize(this),
                    obj_getRetainCount(this)
            );

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
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            CmdUtl_Validate (
        CMDUTL_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_CMDUTL))
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


        if (!(obj_getSize(this) >= sizeof(CMDUTL_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


