// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   screen.c
 *	Generated 07/26/2018 19:52:43
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
#include        <screen_internal.h>
#include        <trace.h>
#include        <sys/ioctl.h>
#include        <stdio.h>
#include        <unistd.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                    S c r e e n  S i z e
    //---------------------------------------------------------------
    
    bool            screen_ScreenSizeGet(
        SCREEN_DATA       *this
    )
    {
        struct winsize w;
        
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        this->nrows = w.ws_row;
        this->ncols = w.ws_col;
        
        return 0;
    }
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SCREEN_DATA *   screen_Alloc(
        void
    )
    {
        SCREEN_DATA     *this;
        uint32_t        cbSize = sizeof(SCREEN_DATA);
        
        // Do initialization.
        
        this = obj_Alloc(cbSize);
        
        // Return to caller.
        return this;
    }



    SCREEN_DATA *   screen_New(
        void
    )
    {
        SCREEN_DATA       *this;
        
        this = screen_Alloc( );
        if (this) {
            this = screen_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                     N u m  C o l s
    //---------------------------------------------------------------
    
    int             screen_getNumCols(
        SCREEN_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->ncols;
    }
    
    
    
    //---------------------------------------------------------------
    //                     N u m  R o w s
    //---------------------------------------------------------------
    
    int             screen_getNumRows(
        SCREEN_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->nrows;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        screen_getPriority(
        SCREEN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            screen_setPriority(
        SCREEN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
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
    
    uint32_t        screen_getSize(
        SCREEN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * screen_getStr(
        SCREEN_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        screen_setStr(
        SCREEN_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
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
    
    OBJ_IUNKNOWN *  screen_getSuperVtbl(
        SCREEN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
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
        ERESULT eRc = screen__Assign(this,pOther);
     @endcode 
     @param     this    SCREEN object pointer
     @param     pOther  a pointer to another SCREEN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         screen_Assign(
        SCREEN_DATA		*this,
        SCREEN_DATA     *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !screen_Validate(pOther) ) {
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
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         screen_Compare(
        SCREEN_DATA     *this,
        SCREEN_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !screen_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        screen      *pCopy = screen_Copy(this);
     @endcode 
     @param     this    SCREEN object pointer
     @return    If successful, a SCREEN object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the SCREEN object.
     */
    SCREEN_DATA *     screen_Copy(
        SCREEN_DATA       *this
    )
    {
        SCREEN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = screen_New( );
        if (pOther) {
            eRc = screen_Assign(this, pOther);
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
    //                          C u r s o r
    //---------------------------------------------------------------
    
    ERESULT         screen_CursorHome(
        SCREEN_DATA     *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef SCREEN_USE_ANSI
        fprintf(this->pScrnOut, "\033[H)");
#endif
        
        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            screen_Dealloc(
        OBJ_ID          objId
    )
    {
        SCREEN_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SCREEN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        screen_setStr(this, OBJ_NIL);

#ifdef  SCREEN_USE_CURSES
        clear( );               // clear screen, send cursor to position (0,0)
        refresh( );             // implement all changes since last refresh
        endwin( );              // restore original window and leave.
#endif

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

    ERESULT         screen_Disable(
        SCREEN_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !screen_Validate(this) ) {
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
    //                          E c h o
    //---------------------------------------------------------------
    
    ERESULT         screen_Echo(
        SCREEN_DATA     *this,
        bool            fOn
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef  SCREEN_USE_CURSES
        if (fOn)
            echo( );
        else
            noecho( );
#else
#endif

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         screen_Enable(
        SCREEN_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !screen_Validate(this) ) {
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
    //                          E r a s e
    //---------------------------------------------------------------
    
    ERESULT         screen_EraseDown(
        SCREEN_DATA     *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef  SCREEN_USE_CURSES
        // clear( );
#endif
#ifdef SCREEN_USE_ANSI
        fprintf(this->pScrnOut, "\033[J");     // Erase entire line.
#endif
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         screen_EraseLine(
        SCREEN_DATA     *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef  SCREEN_USE_CURSES
        // clear( );
#endif
#ifdef SCREEN_USE_ANSI
        fprintf(this->pScrnOut, "\033[2K");     // Erase entire line.
#endif
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         screen_EraseScreen(
        SCREEN_DATA     *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef  SCREEN_USE_CURSES
        clear( );
#endif
#ifdef SCREEN_USE_ANSI
        fprintf(this->pScrnOut, "\033[2J");     // Erase screen and home cursor.
#endif
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         screen_EraseToLineEnd(
        SCREEN_DATA     *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef  SCREEN_USE_CURSES
        // clear( );
#endif
#ifdef SCREEN_USE_ANSI
        fprintf(this->pScrnOut, "\033[K");     // Erase from current cursor to EOL.
#endif
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         screen_EraseUp(
        SCREEN_DATA     *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef  SCREEN_USE_CURSES
        // clear( );
#endif
#ifdef SCREEN_USE_ANSI
        fprintf(this->pScrnOut, "\033[1J");     // Erase entire line.
#endif
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    

    //---------------------------------------------------------------
    //                        G e t c h
    //---------------------------------------------------------------
    
    int             screen_Getch(
        SCREEN_DATA     *this
    )
    {
#ifdef  SCREEN_USE_CURSES
        int             chr = ERR;
#else
        int             chr = -1;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return chr;
        }
#endif
        
#ifdef  SCREEN_USE_CURSES
        chr = getch( );
#endif

        // Return to caller.
        return chr;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SCREEN_DATA *   screen_Init(
        SCREEN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SCREEN_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SCREEN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_SCREEN);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&screen_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

#ifdef  SCREEN_USE_CURSES
        this->pWndMain = initscr( );
        cbreak( );              // no waiting for Enter key
        noecho( );
        this->nrows = getmaxy(this->pWndMain);
        this->ncols = getmaxx(this->pWndMain);
        clear( );               // clear screen, send cursor to position (0,0)
        refresh( );             // implement all changes since last refresh
#endif
#ifdef SCREEN_USE_ANSI
        this->termType = SCREEN_TYPE_ANSI;
#endif
        
    #ifdef NDEBUG
    #else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "screen::sizeof(SCREEN_DATA) = %lu\n", sizeof(SCREEN_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SCREEN_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         screen_IsEnabled(
        SCREEN_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
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
    //                     P r i n t
    //---------------------------------------------------------------
    
    ERESULT         screen_Print(
        SCREEN_DATA     *this,
        int             row,
        int             col,
        const
        char            *pFormat,
        ...
    )
    {
        //ERESULT         eRc;
        char            str[256];
        int             size;
        va_list         arg_ptr;
        char            *pStr = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        va_start( arg_ptr, pFormat );
        str[0] = '\0';
        size = vsnprintf( str, sizeof(str), pFormat, arg_ptr );
        va_end( arg_ptr );
        if (size >= sizeof(str)) {
            ++size;
            pStr = (char *)mem_Malloc(size);
            if( pStr == NULL ) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
            va_start( arg_ptr, pFormat );
            size = vsnprintf( pStr, size, pFormat, arg_ptr );
            va_end( arg_ptr );
#ifdef  SCREEN_USE_CURSES
            mvaddstr(row, col, str);
#endif
            mem_Free( pStr );
            pStr = NULL;
        }
        else {
#ifdef  SCREEN_USE_CURSES
            mvaddstr(row, col, str);
#endif
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
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
        void        *pMethod = screen_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "screen", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          screen_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SCREEN_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)screen_Class();
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
                            return screen_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return screen_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return screen_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return screen_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == screen_ToDebugString)
                    return "ToDebugString";
                if (pData == screen_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          E c h o
    //---------------------------------------------------------------
    
    ERESULT         screen_RawKeyboard(
        SCREEN_DATA     *this,
        bool            fOn
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef  SCREEN_USE_CURSES
        if (fOn)
            cbreak( );
        else
            nocbreak( );
#else
#endif
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S c r o l l
    //---------------------------------------------------------------
    
    ERESULT         screen_ScrollDown(
        SCREEN_DATA     *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef  SCREEN_USE_CURSES
        // clear( );
#endif
#ifdef SCREEN_USE_ANSI
        fprintf(this->pScrnOut, "\033D");     // Erase entire line.
#endif
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         screen_ScrollScreen(
        SCREEN_DATA     *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef  SCREEN_USE_CURSES
        clear( );
#endif
#ifdef SCREEN_USE_ANSI
        fprintf(this->pScrnOut, "\033[r");     // Erase screen and home cursor.
#endif
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         screen_ScrollScreenLines(
        SCREEN_DATA     *this,
        uint16_t        beg,
        uint16_t        end
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef  SCREEN_USE_CURSES
        clear( );
#endif
#ifdef SCREEN_USE_ANSI
        fprintf(this->pScrnOut, "\033[%d;%dr", beg, end);
#endif
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         screen_ScrollToLineEnd(
        SCREEN_DATA     *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef  SCREEN_USE_CURSES
        // clear( );
#endif
#ifdef SCREEN_USE_ANSI
        fprintf(this->pScrnOut, "\033[K");     // Erase from current cursor to EOL.
#endif
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         screen_ScrollUp(
        SCREEN_DATA     *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#ifdef  SCREEN_USE_CURSES
        // clear( );
#endif
#ifdef SCREEN_USE_ANSI
        fprintf(this->pScrnOut, "\033M");     // Erase entire line.
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
        ASTR_DATA      *pDesc = screen_ToDebugString(this,4);
     @endcode 
     @param     this    SCREEN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     screen_ToDebugString(
        SCREEN_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    screen_getSize(this)
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
    
    
    
    ASTR_DATA *     screen_ToJSON(
        SCREEN_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !screen_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        eRc =   AStr_AppendPrint(
                    pStr,
                    "{\"objectType\":\"%s\"",
                    pInfo->pClassName
                );
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            screen_Validate(
        SCREEN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_SCREEN) )
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


        if( !(obj_getSize(this) >= sizeof(SCREEN_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


