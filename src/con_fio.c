// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   con_fio.c
 *	Generated 10/04/2016 18:36:11
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
#include "con_fio_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    bool            con_fio_getRxChar(
        void            *pObjectRx,
        int32_t         *pData,         // Return Data ptr,
                                        // if NULL, return data is flushed.
        uint32_t        timeOut_ms      // Time Out in ms to wait
                                        // (0 == no wait, 0xFFFFFFFF == infinite)
    )
    {
        CON_FIO_DATA    *this = pObjectRx;
        int             data;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        if (NULL == pData) {
            *pData = 0;
            return true;
        }
        
        data = fgetc(this->pFileIn);
        if (pData) {
            *pData = data;
            return true;
        }
        
        if (pData) {
            *pData = -1;
        }
        return false;
    }
    
    
    
    bool            con_fio_putTxChar(
        void            *pObjectTx,
        int32_t         data,
        uint32_t        timeOut_ms      // Time Out in ms to wait
                                        // (0 == no wait, 0xFFFFFFFF == infinite)
    )
    {
        CON_FIO_DATA    *this = pObjectTx;
        int             i;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        i = fputc(data, this->pFileOut);
        if (i < 0) {
            return false;
        }

        return true;
    }
    
    
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    CON_FIO_DATA *  con_fio_Alloc(
    )
    {
        CON_FIO_DATA    *this;
        uint32_t        cbSize = sizeof(CON_FIO_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    CON_FIO_DATA *     con_fio_New(
    )
    {
        CON_FIO_DATA       *this;
        
        this = con_fio_Alloc( );
        if (this) {
            this = con_fio_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    CHARIO_DATA *   con_fio_getChario(
        CON_FIO_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        return &this->chario;
    }
    
    

    FILE *          con_fio_getFileIn(
        CON_FIO_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pFileIn;
    }
    
    
    bool            con_fio_setFileIn(
        CON_FIO_DATA    *this,
        FILE            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->pFileIn = pValue;
        obj_FlagOff(this, CON_FIO_FLAG_ATTR);
        
        return true;
    }
    
    
    
    FILE *          con_fio_getFileOut(
        CON_FIO_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pFileOut;
    }
    
    
    bool            con_fio_setFileOut(
        CON_FIO_DATA    *this,
        FILE            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->pFileOut = pValue;
        
        return true;
    }
    
    
    
    ERESULT         con_fio_getLastError(
        CON_FIO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        return this->eRc;
    }



    uint16_t        con_fio_getPriority(
        CON_FIO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            con_fio_setPriority(
        CON_FIO_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    uint32_t        con_fio_getSize(
        CON_FIO_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
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
     @code:
        ERESULT eRc = con_fio__Assign(this,pOther);
     @endcode:
     @param:    this    CON_FIO object pointer
     @param:    pOther  a pointer to another CON_FIO object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         con_fio_Assign(
        CON_FIO_DATA		*this,
        CON_FIO_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( !con_fio_Validate(pOther) ) {
            DEBUG_BREAK();
            return this->eRc;
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
        
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        //goto eom;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        this->eRc = ERESULT_NOT_IMPLEMENTED; // <-- Remove this!
    //eom:
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        con_fio      *pCopy = con_fio_Copy(this);
     @endcode:
     @param:    this    CON_FIO object pointer
     @return:   If successful, a CON_FIO object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the CON_FIO object.
     */
    CON_FIO_DATA *     con_fio_Copy(
        CON_FIO_DATA       *this
    )
    {
        CON_FIO_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = con_fio_New( );
        if (pOther) {
            eRc = con_fio_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        this->eRc = ERESULT_SUCCESS;
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            con_fio_Dealloc(
        OBJ_ID          objId
    )
    {
        CON_FIO_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((CON_FIO_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif
        
        if ( obj_Flag(this, CON_FIO_FLAG_ATTR) ) {
            tcsetattr( STDIN_FILENO, TCSANOW, &this->oldattr );
        }

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         con_fio_Disable(
        CON_FIO_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return this->eRc;
        }
    #ifdef NDEBUG
    #else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         con_fio_Enable(
        CON_FIO_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }



    //---------------------------------------------------------------
    //                          G e t c
    //---------------------------------------------------------------
    
    int32_t         con_fio_Getc(
        CON_FIO_DATA	*this
    )
    {
        bool            fRc;
        int32_t         value = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        fRc = this->chario.GetRxChar(this->chario.pObjectRx, &value, 0);
        if (!fRc) {
            this->eRc = ERESULT_IO_ERROR;
            return -1;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return value;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    CON_FIO_DATA *   con_fio_Init(
        CON_FIO_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(CON_FIO_DATA);
        struct termios  newattr;
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_CON_FIO);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_CON_FIO);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&con_fio_Vtbl);
        
        this->pFileIn  = stdin;
        this->pFileOut = stdout;
        this->chario.pObjectRx = this;
        this->chario.pObjectTx = this;
        this->chario.GetRxChar = con_fio_getRxChar;
        this->chario.PutTxChar = con_fio_putTxChar;

        tcgetattr(STDIN_FILENO, &this->oldattr);
        obj_FlagOn(this, CON_FIO_FLAG_ATTR);
        newattr = this->oldattr;
        newattr.c_lflag &= ~( ICANON | ECHO);
        tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        
    #ifdef NDEBUG
    #else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->pFileOut);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          P u t c
    //---------------------------------------------------------------
    
    ERESULT         con_fio_Putc(
        CON_FIO_DATA	*this,
        int32_t         value
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !con_fio_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        fRc = this->chario.PutTxChar(this->chario.pObjectTx, value, 0);
        if (!fRc) {
            this->eRc = ERESULT_IO_ERROR;
            return this->eRc;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = con_fio_ToDebugString(this,4);
     @endcode:
     @param:    this    CON_FIO object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     con_fio_ToDebugString(
        CON_FIO_DATA      *this,
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
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(con_fio)\n",
                     this
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
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(con_fio)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            con_fio_Validate(
        CON_FIO_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_CON_FIO) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(CON_FIO_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


