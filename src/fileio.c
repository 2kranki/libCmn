// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   fileio.c
 *	Generated 07/30/2016 20:56:36
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
#include "fileio_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            fileio_task_body(
        void            *pData
    )
    {
        //FILEIO_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    FILEIO_DATA *   fileio_Alloc(
    )
    {
        FILEIO_DATA     *this;
        uint32_t        cbSize = sizeof(FILEIO_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    FILEIO_DATA *   fileio_New(
        uint32_t        headerSize,
        PATH_DATA       *pPath
    )
    {
        FILEIO_DATA       *this;
        
        this = fileio_Alloc( );
        if (this) {
            this = fileio_Init(this,headerSize,pPath);
        } 
        return this;
    }



    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         fileio_getLastError(
        FILEIO_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !fileio_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    bool            fileio_setLastError(
        FILEIO_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !fileio_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    PATH_DATA *     fileio_getPath(
        FILEIO_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !fileio_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pPath;
    }
    
    
    bool          fileio_setPath(
        FILEIO_DATA     *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !fileio_Validate(this) ) {
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
    
    
    
    uint16_t      fileio_getPriority(
        FILEIO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !fileio_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            fileio_setPriority(
        FILEIO_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !fileio_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    uint32_t        fileio_getSize(
        FILEIO_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !fileio_Validate(this) ) {
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
    
    ERESULT         fileio_Assign(
        FILEIO_DATA		*this,
        FILEIO_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fileio_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !fileio_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        if (pOther->pPath) {
            obj_Release(pOther->pPath);
            pOther->pPath = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pPath) {
            if (obj_getVtbl(this->pPath)->pCopy) {
                pOther->pPath = obj_getVtbl(this->pPath)->pCopy(this->pPath);
            }
            else {
                obj_Retain(this->pPath);
                pOther->pPath = this->pPath;
            }
        }

        // Copy other data from this object to other.
        pOther->headerSize = this->headerSize;
        if (this->headerSize && this->pHeader) {
            pOther->pHeader = mem_Malloc(this->headerSize);
            if (pOther->pHeader) {
                memmove(pOther->pHeader, this->pHeader, this->headerSize);
            }
        }
        
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;

        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    FILEIO_DATA *     fileio_Copy(
        FILEIO_DATA       *this
    )
    {
        FILEIO_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fileio_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = fileio_New(this->headerSize,this->pPath);
        if (pOther) {
            eRc = fileio_Assign(this, pOther);
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

    void            fileio_Dealloc(
        OBJ_ID          objId
    )
    {
        FILEIO_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !fileio_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        fileio_setPath(this,OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          C l o s e
    //---------------------------------------------------------------

    bool            fileio_Close(
        FILEIO_DATA		*this
    )
    {
        bool            fRc = false;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !fileio_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

#ifdef XYZZY
        if (this->fOpen) {
            fileio_writeHeader(this);
            fileio_CloseInternal(this);
            fRc = true;
        }
#endif

        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    bool            fileio_Enable(
        FILEIO_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !fileio_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    FILEIO_DATA *   fileio_Init(
        FILEIO_DATA     *this,
        uint32_t        headerSize,
        PATH_DATA       *pPath
    )
    {
        uint32_t        cbSize = sizeof(FILEIO_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        if (pPath == OBJ_NIL) {
            //DEBUG_BREAK();
            obj_Release(this);
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

        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_FILEIO);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_FILEIO); // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&fileio_Vtbl);
        
        fileio_setPath(this, pPath);
        this->headerSize = headerSize;

    #ifdef NDEBUG
    #else
        if( !fileio_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            fileio_IsEnabled(
        FILEIO_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fileio_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(this))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     fileio_ToDebugString(
        FILEIO_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        
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
                     "{%p(fileio) ",
                     this
            );
        AStr_AppendA(pStr, str);

        if (this->pPath) {
            if (((OBJ_DATA *)(this->pPath))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pPath))->pVtbl->pToDebugString(
                                                    this->pPath,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        
        j = snprintf(str, sizeof(str), " %p(fileio)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            fileio_Validate(
        FILEIO_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_FILEIO) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(FILEIO_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


