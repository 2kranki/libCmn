// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   device.c
 *	Generated 02/23/2017 16:37:38
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
#include "device_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            device_task_body(
        void            *pData
    )
    {
        //DEVICE_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    DEVICE_DATA *     device_Alloc(
        uint16_t        stackSize
    )
    {
        DEVICE_DATA       *this;
        uint32_t        cbSize = sizeof(DEVICE_DATA);
        
        // Do initialization.
        
        if (0 == stackSize) {
            stackSize = 256;
        }
        cbSize += stackSize << 2;
        this = obj_Alloc( cbSize );
        obj_setMisc1(this, stackSize);
        
        // Return to caller.
        return this;
    }



    DEVICE_DATA *     device_New(
        uint16_t        stackSize
    )
    {
        DEVICE_DATA       *this;
        
        this = device_Alloc(stackSize);
        if (this) {
            this = device_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint32_t        device_getFlags(
        DEVICE_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        device_setLastError(this, ERESULT_SUCCESS);
        return this->flags;
    }

    
    bool            device_setFlags(
        DEVICE_DATA     *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->flags = value;
        
        device_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    ERESULT         device_getLastError(
        DEVICE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            device_setLastError(
        DEVICE_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        device_getPriority(
        DEVICE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        device_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            device_setPriority(
        DEVICE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        device_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        device_getSize(
        DEVICE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        device_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }




    ASTR_DATA * device_getStr(
        DEVICE_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        device_setLastError(this, ERESULT_SUCCESS);
        return this->pStr;
    }
    
    
    bool        device_setStr(
        DEVICE_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        device_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = device__Assign(this,pOther);
     @endcode:
     @param:    this    DEVICE object pointer
     @param:    pOther  a pointer to another DEVICE object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         device_Assign(
        DEVICE_DATA		*this,
        DEVICE_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return device_getLastError(this);
        }
        if( !device_Validate(pOther) ) {
            DEBUG_BREAK();
            return device_getLastError(pOther);
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
        device_setLastError(this, ERESULT_SUCCESS);
    //eom:
        //FIXME: Implement the assignment.        
        device_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return device_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        device      *pCopy = device_Copy(this);
     @endcode:
     @param:    this    DEVICE object pointer
     @return:   If successful, a DEVICE object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the DEVICE object.
     */
    DEVICE_DATA *     device_Copy(
        DEVICE_DATA       *this
    )
    {
        DEVICE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = device_New(obj_getSize(this));
        if (pOther) {
            eRc = device_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        device_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            device_Dealloc(
        OBJ_ID          objId
    )
    {
        DEVICE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((DEVICE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        device_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         device_Disable(
        DEVICE_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            device_setLastError(this, ERESULT_INVALID_OBJECT);
            return device_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return device_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        device_setLastError(this, ERESULT_SUCCESS);
        return device_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         device_Enable(
        DEVICE_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return device_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        device_setLastError(this, ERESULT_SUCCESS);
        return device_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    DEVICE_DATA *   device_Init(
        DEVICE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(DEVICE_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_DEVICE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_DEVICE);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&device_Vtbl);
        
        device_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !device_Validate(this) ) {
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
    
    ERESULT         device_IsEnabled(
        DEVICE_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !device_Validate(this) ) {
            DEBUG_BREAK();
            return device_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            device_setLastError(this, ERESULT_SUCCESS_TRUE);
            return device_getLastError(this);
        }
        
        // Return to caller.
        device_setLastError(this, ERESULT_SUCCESS_FALSE);
        return device_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = device_ToDebugString(this,4);
     @endcode:
     @param:    this    DEVICE object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     device_ToDebugString(
        DEVICE_DATA      *this,
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
        if( !device_Validate(this) ) {
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
                     "{%p(device) size=%d\n",
                     this,
                     device_getSize(this)
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
        j = snprintf(str, sizeof(str), " %p(device)}\n", this);
        AStr_AppendA(pStr, str);
        
        device_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            device_Validate(
        DEVICE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        // in this yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_DEVICE) )
                ;
            else
                return false;
        }
        else
            return false;
        // Now, we have validated that we have a valid pointer in
        // this.


        if( !(obj_getSize(this) >= sizeof(DEVICE_DATA)) ) {
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


