// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ioRcd.c
 *	Generated 01/12/2017 00:06:08
 *
 */

 
/*
 * COPYRIGHT  - (C) Copyright 2016  BY Robert White Services, LLC
 *             This computer software is the proprietary information
 *             of Robert White Services, LLC and is subject to a
 *             License Agreement between the user hereof and Robert
 *             White Services, LLC. All concepts, programs, tech-
 *             niques,  object code  and  source code are the Trade
 *             Secrets of Robert White Services, LLC.
 */




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include "ioRcd_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            ioRcd_task_body(
        void            *pData
    )
    {
        //IORCD_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    IORCD_DATA *     ioRcd_Alloc(
    )
    {
        IORCD_DATA      *this;
        uint32_t        cbSize = sizeof(IORCD_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    IORCD_DATA *     ioRcd_New(
    )
    {
        IORCD_DATA       *this;
        
        this = ioRcd_Alloc( );
        if (this) {
            this = ioRcd_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         ioRcd_getLastError(
        IORCD_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ioRcd_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            ioRcd_setLastError(
        IORCD_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !ioRcd_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    PATH_DATA *     ioRcd_getPath(
        IORCD_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ioRcd_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        ioRcd_setLastError(this, ERESULT_SUCCESS);
        return this->pPath;
    }
    
    
    bool            ioRcd_setPath(
        IORCD_DATA      *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !ioRcd_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pPath) {
            obj_Release(this->pPath);
        }
        this->pPath = pValue;
        
        ioRcd_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    uint16_t        ioRcd_getPriority(
        IORCD_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ioRcd_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        ioRcd_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            ioRcd_setPriority(
        IORCD_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !ioRcd_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        ioRcd_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        ioRcd_getSize(
        IORCD_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !ioRcd_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        ioRcd_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = ioRcd__Assign(this,pOther);
     @endcode:
     @param:    this    IORCD object pointer
     @param:    pOther  a pointer to another IORCD object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         ioRcd_Assign(
        IORCD_DATA		*this,
        IORCD_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ioRcd_Validate(this) ) {
            DEBUG_BREAK();
            return ioRcd_getLastError(this);
        }
        if( !ioRcd_Validate(pOther) ) {
            DEBUG_BREAK();
            return ioRcd_getLastError(pOther);
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
        
        //goto eom;

        // Return to caller.
        ioRcd_setLastError(this, ERESULT_SUCCESS);
    //eom:
        //FIXME: Implement the assignment.        
        ioRcd_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return ioRcd_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        ioRcd      *pCopy = ioRcd_Copy(this);
     @endcode:
     @param:    this    IORCD object pointer
     @return:   If successful, a IORCD object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the IORCD object.
     */
    IORCD_DATA *     ioRcd_Copy(
        IORCD_DATA       *this
    )
    {
        IORCD_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ioRcd_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ioRcd_New( );
        if (pOther) {
            eRc = ioRcd_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        ioRcd_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            ioRcd_Dealloc(
        OBJ_ID          objId
    )
    {
        IORCD_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !ioRcd_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((IORCD_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

#ifdef XYZZY
        if (this->pArray) {
            obj_Release(this->pArray);
            this->pArray = OBJ_NIL;
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         ioRcd_Disable(
        IORCD_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            ioRcd_setLastError(this, ERESULT_INVALID_OBJECT);
            return ioRcd_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !ioRcd_Validate(this) ) {
            DEBUG_BREAK();
            return ioRcd_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        ioRcd_setLastError(this, ERESULT_SUCCESS);
        return ioRcd_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         ioRcd_Enable(
        IORCD_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !ioRcd_Validate(this) ) {
            DEBUG_BREAK();
            return ioRcd_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        ioRcd_setLastError(this, ERESULT_SUCCESS);
        return ioRcd_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    IORCD_DATA *   ioRcd_Init(
        IORCD_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(IORCD_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_IORCD);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_IORCD);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ioRcd_Vtbl);
        
        ioRcd_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !ioRcd_Validate(this) ) {
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
    
    ERESULT         ioRcd_IsEnabled(
        IORCD_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ioRcd_Validate(this) ) {
            DEBUG_BREAK();
            return ioRcd_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            ioRcd_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ioRcd_getLastError(this);
        }
        
        // Return to caller.
        ioRcd_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ioRcd_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = ioRcd_ToDebugString(this,4);
     @endcode:
     @param:    this    IORCD object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     ioRcd_ToDebugString(
        IORCD_DATA      *this,
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
                     "{%p(ioRcd) size=%d\n",
                     this,
                     ioRcd_getSize(this)
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
        j = snprintf(str, sizeof(str), " %p(ioRcd)}\n", this);
        AStr_AppendA(pStr, str);
        
        ioRcd_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            ioRcd_Validate(
        IORCD_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_IORCD) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(IORCD_DATA)) ) {
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


