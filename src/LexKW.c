// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   LexKW.c
 *  Generated 03/30/2021 20:19:39
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
#include        <LexKW_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    // A binary search is performed on this table. So, it must
    // be kept sorted by key word.
    static
    LEX_KWDTBL_ENTRY   kwdTbl[] = {
        // Upper case keywords would go here!
        {"%goal",               LEX_KWD_GOAL,               LEX_LANG_LL1},
        {"%term",               LEX_KWD_TERM,               LEX_LANG_LL1},
        {"@autoreleasepool",    LEX_KWD_AT_AUTO,            LEX_LANG_OBJC},
        {"@catch",              LEX_KWD_AT_CATCH,           LEX_LANG_OBJC},
        {"@class",              LEX_KWD_AT_CLASS,           LEX_LANG_OBJC},
        {"@dynamic",            LEX_KWD_AT_DYNAMIC,         LEX_LANG_OBJC},
        {"@encode",             LEX_KWD_AT_ENCODE,          LEX_LANG_OBJC},
        {"@end",                LEX_KWD_AT_END,             LEX_LANG_OBJC},
        {"@finally",            LEX_KWD_AT_FINALLY,         LEX_LANG_OBJC},
        {"@implementation",     LEX_KWD_AT_IMPLEMENTATION,  LEX_LANG_OBJC},
        {"@interface",          LEX_KWD_AT_INTERFACE,       LEX_LANG_OBJC},
        {"@optional",           LEX_KWD_AT_OPTIONAL,        LEX_LANG_OBJC},
        {"@package",            LEX_KWD_AT_PKG,             LEX_LANG_OBJC},
        {"@private",            LEX_KWD_AT_PRIVATE,         LEX_LANG_OBJC},
        {"@property",           LEX_KWD_AT_PROPERTY,        LEX_LANG_OBJC},
        {"@protected",          LEX_KWD_AT_PROTECTED,       LEX_LANG_OBJC},
        {"@protocol",           LEX_KWD_AT_PROTOCOL,        LEX_LANG_OBJC},
        {"@public",             LEX_KWD_AT_PUBLIC,          LEX_LANG_OBJC},
        {"@selector",           LEX_KWD_AT_SEL,             LEX_LANG_OBJC},
        {"@synchronized",       LEX_KWD_AT_SYNC,            LEX_LANG_OBJC},
        {"@synthesize",         LEX_KWD_AT_SYNTH,           LEX_LANG_OBJC},
        {"@throw",              LEX_KWD_AT_THROW,           LEX_LANG_OBJC},
        {"@try",                LEX_KWD_AT_TRY,             LEX_LANG_OBJC},
        {"NS_ENUM",             LEX_KWD_NSENUM,             LEX_LANG_OBJC},
        {"NS_OPTIONS",          LEX_KWD_NSOPTIONS,          LEX_LANG_OBJC},
        {"_asm",                LEX_KWD_ASM,                LEX_LANG_MSC},
        {"_cdecl",              LEX_KWD_CDECL,              LEX_LANG_MSC},
        {"_emit",               LEX_KWD_EMIT,               LEX_LANG_MSC},
        {"_entry",              LEX_KWD_ENTRY,              LEX_LANG_MSC},
        {"_far",                LEX_KWD_FAR,                LEX_LANG_MSC},
        {"_fortran",            LEX_KWD_FORTRAN,            LEX_LANG_MSC},
        {"_near",               LEX_KWD_NEAR,               LEX_LANG_MSC},
        {"_pascal",             LEX_KWD_PASCAL,             LEX_LANG_MSC},
        {"auto",                LEX_KWD_AUTO,               LEX_LANG_C},
        {"bool",                LEX_KWD_BOOL,               LEX_LANG_C},
        {"break",               LEX_KWD_BREAK,              LEX_LANG_C},
        {"case",                LEX_KWD_CASE,               LEX_LANG_C},
        {"char",                LEX_KWD_CHAR,               LEX_LANG_C},
        {"class",               LEX_KWD_CLASS,              LEX_LANG_CPP},
        {"const",               LEX_KWD_CONST,              LEX_LANG_C},
        {"continue",            LEX_KWD_CONTINUE,           LEX_LANG_C},
        {"default",             LEX_KWD_DEFAULT,            LEX_LANG_C},
        {"delete",              LEX_KWD_DELETE,             LEX_LANG_CPP},
        {"do",                  LEX_KWD_DO,                 LEX_LANG_C},
        {"double",              LEX_KWD_DOUBLE,             LEX_LANG_C},
        {"else",                LEX_KWD_ELSE,               LEX_LANG_C},
        {"end",                 LEX_KWD_END,                LEX_LANG_C},
        {"enum",                LEX_KWD_ENUM,               LEX_LANG_C},
        {"extern",              LEX_KWD_EXTERN,             LEX_LANG_C},
        {"float",               LEX_KWD_FLOAT,              LEX_LANG_C},
        {"for",                 LEX_KWD_FOR,                LEX_LANG_C},
        {"friend",              LEX_KWD_FRIEND,             LEX_LANG_CPP},
        {"goto",                LEX_KWD_GOTO,               LEX_LANG_C},
        {"id",                  LEX_KWD_ID,                 LEX_LANG_OBJC},
        {"if",                  LEX_KWD_IF,                 LEX_LANG_C},
        {"inline",              LEX_KWD_INLINE,             LEX_LANG_C},
        {"int",                 LEX_KWD_INT,                LEX_LANG_C},
        {"int128_t",            LEX_KWD_INT128,             LEX_LANG_C},
        {"int16_t",             LEX_KWD_INT16,              LEX_LANG_C},
        {"int256_t",            LEX_KWD_INT256,             LEX_LANG_C},
        {"int32_t",             LEX_KWD_INT32,              LEX_LANG_C},
        {"int64_t",             LEX_KWD_INT64,              LEX_LANG_C},
        {"int8_t",              LEX_KWD_INT8,               LEX_LANG_C},
        {"long",                LEX_KWD_LONG,               LEX_LANG_C},
        {"new",                 LEX_KWD_NEW,                LEX_LANG_CPP},
        {"operator",            LEX_KWD_OPERATOR,           LEX_LANG_CPP},
        {"overload",            LEX_KWD_OVERLOAD,           LEX_LANG_CPP},
        {"public",              LEX_KWD_PUBLIC,             LEX_LANG_CPP},
        {"register",            LEX_KWD_REGISTER,           LEX_LANG_C},
        {"return",              LEX_KWD_RETURN,             LEX_LANG_C},
        {"select",              LEX_KWD_SELECT,             LEX_LANG_C},
        {"short",               LEX_KWD_SHORT,              LEX_LANG_C},
        {"signed",              LEX_KWD_SIGNED,             LEX_LANG_C},
        {"sizeof",              LEX_KWD_SIZEOF,             LEX_LANG_C},
        {"static",              LEX_KWD_STATIC,             LEX_LANG_C},
        {"struct",              LEX_KWD_STRUCT,             LEX_LANG_C},
        {"switch",              LEX_KWD_SWITCH,             LEX_LANG_C},
        {"this",                LEX_KWD_THIS,               LEX_LANG_CPP},
        {"typedef",             LEX_KWD_TYPEDEF,            LEX_LANG_C},
        {"uint128_t",           LEX_KWD_UINT128,            LEX_LANG_C},
        {"uint16_t",            LEX_KWD_UINT16,             LEX_LANG_C},
        {"uint256_t",           LEX_KWD_UINT256,            LEX_LANG_C},
        {"uint32_t",            LEX_KWD_UINT32,             LEX_LANG_C},
        {"uint64_t",            LEX_KWD_UINT64,             LEX_LANG_C},
        {"uint8_t",             LEX_KWD_UINT8,              LEX_LANG_C},
        {"union",               LEX_KWD_UNION,              LEX_LANG_C},
        {"unsigned",            LEX_KWD_UNSIGNED,           LEX_LANG_C},
        {"virtual",             LEX_KWD_VIRTUAL,            LEX_LANG_CPP},
        {"void",                LEX_KWD_VOID,               LEX_LANG_C},
        {"volatile",            LEX_KWD_VOLATILE,           LEX_LANG_C},
        {"while",               LEX_KWD_WHILE,              LEX_LANG_C},
    };

    static
    int         cKwdTbl = sizeof(kwdTbl)/sizeof(LEX_KWDTBL_ENTRY);





 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LEXKW_DATA *     LexKW_Alloc (
        void
    )
    {
        LEXKW_DATA       *this;
        uint32_t        cbSize = sizeof(LEXKW_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    LEXKW_DATA *     LexKW_New (
        void
    )
    {
        LEXKW_DATA       *this;
        
        this = LexKW_Alloc( );
        if (this) {
            this = LexKW_Init(this);
        } 
        return this;
    }



    // Perform a binary search on the keyword table. (Keyword table
    // must be kept sorted!)
    LEX_KWDTBL_ENTRY * LexKW_Search(
        const
        char            *pNameA
    )
    {
        LEX_KWDTBL_ENTRY
                        *pEntry;
        int             iRc;
        uint32_t        high = cKwdTbl - 1;
        uint32_t        low = 0;
        uint32_t        mid;

        while( low < high ) {
            mid = (high + low) / 2;
            pEntry = &kwdTbl[mid];
            iRc = strcmp(pEntry->pKwd, pNameA);
            if( iRc < 0 ) {
                low = mid + 1;
            }
            else if( iRc == 0 ) {
                return pEntry;
            }
            else {
                high = mid;
            }
        }
        if( high == low ) {
            pEntry = &kwdTbl[low];
            iRc = strcmp(pEntry->pKwd, pNameA);
            if(iRc == 0) {
                return pEntry;
            }
        }

        return NULL;
    }



    bool            LexKW_ValidateKeywords (
    )
    {
        bool            fRc = true;
        int             i;
        int             iRc;

        for (i = 0; i < (cKwdTbl - 1); i++) {
            iRc = strcmp(kwdTbl[i].pKwd, kwdTbl[i+1].pKwd);
            if (iRc < 0)
                ;
            else {
                fRc = false;
                break;
            }
        }

        return fRc;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        LexKW_getPriority (
        LEXKW_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            LexKW_setPriority (
        LEXKW_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        LexKW_getSize (
        LEXKW_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * LexKW_getStr (
        LEXKW_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        LexKW_setStr (
        LEXKW_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  LexKW_getSuperVtbl (
        LEXKW_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
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
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = LexKW_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another LEXKW object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         LexKW_Assign (
        LEXKW_DATA       *this,
        LEXKW_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!LexKW_Validate(pOther)) {
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
        //pOther->x     = this->x; 

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
    int             LexKW_Compare (
        LEXKW_DATA     *this,
        LEXKW_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!LexKW_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        LexKW      *pCopy = LexKW_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LEXKW object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LEXKW_DATA *     LexKW_Copy (
        LEXKW_DATA       *this
    )
    {
        LEXKW_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef LEXKW_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = LexKW_New( );
        if (pOther) {
            eRc = LexKW_Assign(this, pOther);
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

    void            LexKW_Dealloc (
        OBJ_ID          objId
    )
    {
        LEXKW_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((LEXKW_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        LexKW_setStr(this, OBJ_NIL);

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
        LexKW      *pDeepCopy = LexKW_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LEXKW object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LEXKW_DATA *     LexKW_DeepyCopy (
        LEXKW_DATA       *this
    )
    {
        LEXKW_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = LexKW_New( );
        if (pOther) {
            eRc = LexKW_Assign(this, pOther);
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
    ERESULT         LexKW_Disable (
        LEXKW_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return eRc;
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
    ERESULT         LexKW_Enable (
        LEXKW_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    LEXKW_DATA *   LexKW_Init (
        LEXKW_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(LEXKW_DATA);
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_LEXKW);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&LexKW_Vtbl);
#ifdef  LEXKW_JSON_SUPPORT
        JsonIn_RegisterClass(LexKW_Class());
#endif
        
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
        if (!LexKW_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "LexKW::sizeof(LEXKW_DATA) = %lu\n", 
                sizeof(LEXKW_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(LEXKW_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         LexKW_IsEnabled (
        LEXKW_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
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
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = LexKW_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "LexKW", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          LexKW_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        LEXKW_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(LEXKW_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)LexKW_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return LexKW_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return LexKW_Enable;
                        }
                        break;

                    case 'P':
#ifdef  LEXKW_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return LexKW_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return LexKW_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return LexKW_ToDebugString;
                        }
#ifdef  LEXKW_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return LexKW_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return LexKW_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == LexKW_ToDebugString)
                    return "ToDebugString";
#ifdef  LEXKW_JSON_SUPPORT
                if (pData == LexKW_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = LexKW_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     LexKW_ToDebugString (
        LEXKW_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexKW_Validate(this)) {
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
                    LexKW_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
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
    bool            LexKW_Validate (
        LEXKW_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_LEXKW))
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


        if (!(obj_getSize(this) >= sizeof(LEXKW_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


