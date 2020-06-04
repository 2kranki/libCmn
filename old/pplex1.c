// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   pplex1.c
 *	Generated 09/15/2015 23:29:11
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
#include "pplex1_internal.h"
#include <ascii.h>
#include <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PPLEX1_DATA *     pplex1_Alloc(
    )
    {
        PPLEX1_DATA     *cbp;
        uint32_t        cbSize = sizeof(PPLEX1_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    PPLEX1_DATA *   pplex1_New(
    )
    {
        PPLEX1_DATA       *cbp;
        
        cbp = pplex1_Alloc( );
        if (cbp) {
            cbp = pplex1_Init(cbp);
        } 
        return( cbp );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      F l a g s
    //---------------------------------------------------------------

    uint32_t        pplex1_getFlags(
        PPLEX1_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !pplex1_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return Lex_getFlags((LEX_DATA *)this);
    }


    bool            pplex1_setFlags(
        PPLEX1_DATA     *this,
        uint32_t        value
    )
    {
        bool            fRc;

#ifdef NDEBUG
#else
        if( !pplex1_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        fRc = Lex_setFlags((LEX_DATA *)this, value);

        return fRc;
    }



    //---------------------------------------------------------------
    //               L e x i c a l  S c a n n e r
    //---------------------------------------------------------------

    LEX_DATA *      pplex1_getLex(
        PPLEX1_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !pplex1_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (LEX_DATA *)this;
    }





    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            pplex1_Dealloc(
        OBJ_ID          objId
    )
    {
        PPLEX1_DATA     *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !pplex1_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PPLEX1_DATA *   pplex1_Init(
        PPLEX1_DATA     *this
    )
    {
        bool            fRc;
        uint32_t        cbSize = sizeof(PPLEX1_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);         // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = (PPLEX1_DATA *)Lex_Init( (LEX_DATA *)this);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                          // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&pplex1_Vtbl);
        
        fRc =   Lex_setParserFunction(
                                (LEX_DATA *)this,
                                (void *)pplex1_ParseToken,
                                this
                );
        if (!fRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !pplex1_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return this;
    }

     

    //--------------------------------------------------------------
    //                      P a r s e  T o k e n
    //--------------------------------------------------------------
    
    /* ParseToken() gets the next token from the source file. It
     * saves that token for the file/line/col numbers and then
     * proceeds to build upon it. It accumulates tokens until
     * based on the class/type. When it finds a token which does
     * not belong to that class, it saves the current token
     * string to the string table, and tells the source file
     * to re-use the token which did not match on the next parse.
     * The token returned from this routine has the index of the
     * token string in the string table if it is larger than 1
     * character.
     */
    
    bool            pplex1_ParseToken(
        PPLEX1_DATA		*this
    )
    {
        ERESULT         eRc;
        TOKEN_DATA      *pInput;
        int32_t         cls;
        bool            fMore = true;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pplex1_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        while (fMore) {
            pInput = Lex_InputLookAhead((LEX_DATA *)this, 1);
            if (pInput) {
                cls = Token_getClass(pInput);
            }
            else {
                pInput = Lex_ParseEOF((LEX_DATA *)this);
                cls = Token_getClass(pInput);
                DEBUG_BREAK();
            }
            eRc = Lex_ParseTokenSetup((LEX_DATA *)this, pInput);
            if (cls == LEX_CLASS_EOF) {
                break;
            }
            
            switch (cls) {
                    
                case '?':           /*** '?' ***/
                    pInput = Lex_InputLookAhead((LEX_DATA *)this, 2);
                    cls = Token_getClass(pInput);
                    if( '?' == cls) {
                        pInput = Lex_InputLookAhead((LEX_DATA *)this, 3);
                        cls = Token_getClass(pInput);
                        if( '(' == cls) {
                            Token_setClass(&this->super.token, '[');
                            Token_setChrW32(&this->super.token, '[');
                            Lex_InputAdvance((LEX_DATA *)this, 3);
                            cls = '[';
                            fMore = false;
                            break;
                        }
                        if( '/' == cls) {
                            Token_setClass(&this->super.token, '\\');
                            Token_setChrW32(&this->super.token, '\\');
                            Lex_InputAdvance((LEX_DATA *)this, 3);
                            cls = '\\';
                            fMore = false;
                            break;
                        }
                        if( ')' == cls) {
                            Token_setClass(&this->super.token, ']');
                            Token_setChrW32(&this->super.token, ']');
                            Lex_InputAdvance((LEX_DATA *)this, 3);
                            fMore = false;
                            cls = ']';
                            break;
                        }
                        if( '\'' == cls) {
                            Token_setClass(&this->super.token, '^');
                            Token_setChrW32(&this->super.token, '^');
                            Lex_InputAdvance((LEX_DATA *)this, 3);
                            fMore = false;
                            cls = '^';
                            break;
                        }
                        if( '<' == cls) {
                            Token_setClass(&this->super.token, '{');
                            Token_setChrW32(&this->super.token, '{');
                            Lex_InputAdvance((LEX_DATA *)this, 3);
                            fMore = false;
                            cls = '{';
                            break;
                        }
                        if( '!' == cls) {
                            Token_setClass(&this->super.token, '|');
                            Token_setChrW32(&this->super.token, '|');
                            Lex_InputAdvance((LEX_DATA *)this, 3);
                            fMore = false;
                            cls = '|';
                            break;
                        }
                        if( '>' == cls) {
                            Token_setClass(&this->super.token, '}');
                            Token_setChrW32(&this->super.token, '}');
                            Lex_InputAdvance((LEX_DATA *)this, 3);
                            fMore = false;
                            cls = '}';
                            break;
                        }
                        if( '-' == cls) {
                            Token_setClass(&this->super.token, '~');
                            Token_setChrW32(&this->super.token, '~');
                            Lex_InputAdvance((LEX_DATA *)this, 3);
                            cls = '~';
                            fMore = false;
                            break;
                        }
                        if( '=' == cls) {
                            Token_setClass(&this->super.token, '#');
                            Token_setChrW32(&this->super.token, '#');
                            Lex_InputAdvance((LEX_DATA *)this, 3);
                            cls = '#';
                            fMore = false;
                            break;
                        }
                    }
                    Lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
                default:
                    Token_Assign(pInput, &this->super.token); //???
                    Lex_InputAdvance((LEX_DATA *)this, 1);
                    break;
            }
            fMore = false;
            break;
        }
        
        // Return to caller.
        //eRc = lex_ParseTokenFinalize((LEX_DATA *)this, newCls, fSaveStr);
        //BREAK_FALSE(ERESULT_IS_SUCCESSFUL(eRc));
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          pplex1_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        PPLEX1_DATA     *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !pplex1_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(PPLEX1_DATA);
                break;
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
#ifdef XYZZY
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return hex_Disable;
                        }
                        break;
                        
                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return hex_Enable;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return hex_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return hex_ToJSON;
                        }
                        break;
#endif
                        
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
    
    ASTR_DATA *     pplex1_ToDebugString(
        PPLEX1_DATA     *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA      *pWrkStr;
        
        if (OBJ_NIL == cbp) {
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
                     "{%p(pplex1) ",
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
    bool            pplex1_Validate(
        PPLEX1_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_PPLEX1) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(PPLEX1_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


