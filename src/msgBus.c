// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   msgBus.c
 *	Generated 05/31/2017 20:00:00
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
#include <msgBus_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            msgBus_task_body(
        void            *pData
    )
    {
        //MSGBUS_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    MSGBUS_DATA *   msgBus_Alloc(
    )
    {
        MSGBUS_DATA     *this;
        uint32_t        cbSize = sizeof(MSGBUS_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    MSGBUS_DATA *     msgBus_New(
        uint16_t        size
    )
    {
        MSGBUS_DATA       *this;
        
        this = msgBus_Alloc( );
        if (this) {
            this = msgBus_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         msgBus_getLastError(
        MSGBUS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            msgBus_setLastError(
        MSGBUS_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        msgBus_getPriority(
        MSGBUS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        msgBus_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            msgBus_setPriority(
        MSGBUS_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        msgBus_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        msgBus_getSize(
        MSGBUS_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        msgBus_setLastError(this, ERESULT_SUCCESS);
        return this->size;
    }




    ASTR_DATA * msgBus_getStr(
        MSGBUS_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        msgBus_setLastError(this, ERESULT_SUCCESS);
        return this->pStr;
    }
    
    
    bool        msgBus_setStr(
        MSGBUS_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        msgBus_setLastError(this, ERESULT_SUCCESS);
        return true;
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
        ERESULT eRc = msgBus__Assign(this,pOther);
     @endcode:
     @param:    this    MSGBUS object pointer
     @param:    pOther  a pointer to another MSGBUS object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         msgBus_Assign(
        MSGBUS_DATA		*this,
        MSGBUS_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return msgBus_getLastError(this);
        }
        if( !msgBus_Validate(pOther) ) {
            DEBUG_BREAK();
            return msgBus_getLastError(pOther);
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
        msgBus_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        msgBus_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return msgBus_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        msgBus      *pCopy = msgBus_Copy(this);
     @endcode:
     @param:    this    MSGBUS object pointer
     @return:   If successful, a MSGBUS object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the MSGBUS object.
     */
    MSGBUS_DATA *     msgBus_Copy(
        MSGBUS_DATA       *this
    )
    {
        MSGBUS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = msgBus_New(obj_getSize(this));
        if (pOther) {
            eRc = msgBus_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        msgBus_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            msgBus_Dealloc(
        OBJ_ID          objId
    )
    {
        MSGBUS_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((MSGBUS_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        msgBus_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         msgBus_Disable(
        MSGBUS_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            msgBus_setLastError(this, ERESULT_INVALID_OBJECT);
            return msgBus_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return msgBus_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        msgBus_setLastError(this, ERESULT_SUCCESS);
        return msgBus_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         msgBus_Enable(
        MSGBUS_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return msgBus_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        msgBus_setLastError(this, ERESULT_SUCCESS);
        return msgBus_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    MSGBUS_DATA *   msgBus_Init(
        MSGBUS_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(MSGBUS_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_MSGBUS);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_MSGBUS);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&msgBus_Vtbl);
        
        msgBus_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "offsetof(eRc) = %lu\n", offsetof(MSGBUS_DATA,eRc));
        fprintf(stderr, "sizeof(MSGBUS_DATA) = %lu\n", sizeof(MSGBUS_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(MSGBUS_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         msgBus_IsEnabled(
        MSGBUS_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return msgBus_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            msgBus_setLastError(this, ERESULT_SUCCESS_TRUE);
            return msgBus_getLastError(this);
        }
        
        // Return to caller.
        msgBus_setLastError(this, ERESULT_SUCCESS_FALSE);
        return msgBus_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = msgBus_ToDebugString(this,4);
     @endcode:
     @param:    this    MSGBUS object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     msgBus_ToDebugString(
        MSGBUS_DATA      *this,
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
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(msgBus) size=%d\n",
                     this,
                     msgBus_getSize(this)
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
        j = snprintf(str, sizeof(str), " %p(msgBus)}\n", this);
        AStr_AppendA(pStr, str);
        
        msgBus_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            msgBus_Validate(
        MSGBUS_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_MSGBUS) )
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


        if( !(obj_getSize(this) >= sizeof(MSGBUS_DATA)) ) {
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

