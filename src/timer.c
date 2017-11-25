// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   timer.c
 *	Generated 06/06/2017 23:20:26
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
#include <timer_internal.h>



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

    TIMER_DATA *     timer_Alloc(
    )
    {
        TIMER_DATA      *this;
        uint32_t        cbSize = sizeof(TIMER_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TIMER_DATA *     timer_New(
        uint32_t        msWait,
        void            *(*timerRoutine)(void *),
        void            *routineData
    )
    {
        TIMER_DATA       *this;
        
        this = timer_Alloc( );
        if (this) {
            this = timer_Init(this, msWait, timerRoutine, routineData);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         timer_getLastError(
        TIMER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !timer_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            timer_setLastError(
        TIMER_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !timer_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    bool            timer_setRoutine(
        TIMER_DATA      *this,
        void            *(*timerRoutine)(void *),
        void            *routineData
    )
    {
        
#ifdef NDEBUG
#else
        if( !timer_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->timerBody = timerRoutine;
        this->timerData = routineData;
        
        return true;
    }
    
    
    
    uint32_t        timer_getWait(
        TIMER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !timer_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        timer_setLastError(this, ERESULT_SUCCESS);
        return this->msWait;
    }

    bool            timer_setWait(
        TIMER_DATA     *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !timer_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->msWait = value;
        if (this->pThread) {
            psxThread_setWait(this->pThread, value);
        }

        timer_setLastError(this, ERESULT_SUCCESS);
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
     @code
        ERESULT eRc = timer__Assign(this,pOther);
     @endcode
     @param     this    TIMER object pointer
     @param     pOther  a pointer to another TIMER object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         timer_Assign(
        TIMER_DATA		*this,
        TIMER_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !timer_Validate(this) ) {
            DEBUG_BREAK();
            return timer_getLastError(this);
        }
        if( !timer_Validate(pOther) ) {
            DEBUG_BREAK();
            return timer_getLastError(pOther);
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
        timer_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        timer_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return timer_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        timer      *pCopy = timer_Copy(this);
     @endcode
     @param     this    TIMER object pointer
     @return    If successful, a TIMER object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the TIMER object.
     */
    TIMER_DATA *     timer_Copy(
        TIMER_DATA       *this
    )
    {
        TIMER_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !timer_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        //FIXME: pOther = timer_New(obj_getSize(this));
        if (pOther) {
            eRc = timer_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        timer_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            timer_Dealloc(
        OBJ_ID          objId
    )
    {
        TIMER_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !timer_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((TIMER_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pThread) {
            psxThread_Terminate(this->pThread);
            obj_Release(this->pThread);
            this->pThread = OBJ_NIL;
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

    ERESULT         timer_Disable(
        TIMER_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            timer_setLastError(this, ERESULT_INVALID_OBJECT);
            return timer_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !timer_Validate(this) ) {
            DEBUG_BREAK();
            return timer_getLastError(this);
        }
    #endif

        obj_Disable(this);
        
        // Return to caller.
        timer_setLastError(this, ERESULT_SUCCESS);
        return timer_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         timer_Enable(
        TIMER_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !timer_Validate(this) ) {
            DEBUG_BREAK();
            return timer_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        timer_setLastError(this, ERESULT_SUCCESS);
        return timer_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    TIMER_DATA *    timer_Init(
        TIMER_DATA      *this,
        uint32_t        msWait,
        void            *(*timerRoutine)(void *),
        void            *routineData
    )
    {
        uint32_t        cbSize = sizeof(TIMER_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_TIMER);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_TIMER);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&timer_Vtbl);
        
        timer_setLastError(this, ERESULT_GENERAL_FAILURE);

        this->msWait = msWait;
        this->timerBody = timerRoutine;
        this->timerData = routineData;
        this->pThread = psxThread_New(timerRoutine, routineData, 0);
        if (this->pThread == OBJ_NIL) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        psxThread_setWait(this->pThread, this->msWait);

    #ifdef NDEBUG
    #else
        if( !timer_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(TIMER_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         timer_IsEnabled(
        TIMER_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !timer_Validate(this) ) {
            DEBUG_BREAK();
            return timer_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            timer_setLastError(this, ERESULT_SUCCESS_TRUE);
            return timer_getLastError(this);
        }
        
        // Return to caller.
        timer_setLastError(this, ERESULT_SUCCESS_FALSE);
        return timer_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          P a u s e
    //---------------------------------------------------------------
    
    bool            timer_Pause(
        TIMER_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !timer_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pThread) {
            psxThread_Pause(this->pThread);
        }
        
        timer_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          timer_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        TIMER_DATA   *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !timer_Validate(this) ) {
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
                            return timer_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Ensable", (char *)pStr) == 0) {
                            return timer_Enable;
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
    //                          R e s u m e
    //---------------------------------------------------------------
    
    bool            timer_Resume(
        TIMER_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !timer_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pThread) {
            psxThread_Resume(this->pThread);
        }
        
        timer_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = timer_ToDebugString(this,4);
     @endcode
     @param     this    TIMER object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     timer_ToDebugString(
        TIMER_DATA      *this,
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
        if( !timer_Validate(this) ) {
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
                     "{%p(timer) msWait=%d\n",
                     this,
                     this->msWait
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
        j = snprintf(str, sizeof(str), " %p(timer)}\n", this);
        AStr_AppendA(pStr, str);
        
        timer_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            timer_Validate(
        TIMER_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_TIMER) )
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


        if( !(obj_getSize(this) >= sizeof(TIMER_DATA)) ) {
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


