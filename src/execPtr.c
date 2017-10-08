// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   execPtr.c
 *	Generated 10/07/2017 12:40:01
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
#include <execPtr_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            execPtr_task_body(
        void            *pData
    )
    {
        //EXECPTR_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    EXECPTR_DATA *  execPtr_Alloc(
    )
    {
        EXECPTR_DATA    *this;
        uint32_t        cbSize = sizeof(EXECPTR_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    EXECPTR_DATA *  execPtr_New(
        void            *pFunc
    )
    {
        EXECPTR_DATA       *this;
        
        this = execPtr_Alloc( );
        if (this) {
            this = execPtr_Init(this, pFunc);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ASTR_DATA * execPtr_getDesc(
        EXECPTR_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        execPtr_setLastError(this, ERESULT_SUCCESS);
        return this->pDesc;
    }
    
    
    bool        execPtr_setDesc(
        EXECPTR_DATA *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pDesc) {
            obj_Release(this->pDesc);
        }
        this->pDesc = pValue;
        
        execPtr_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    void *      execPtr_getFunc(
        EXECPTR_DATA *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        execPtr_setLastError(this, ERESULT_SUCCESS);
        return this->pFunc;
    }

    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         execPtr_getLastError(
        EXECPTR_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            execPtr_setLastError(
        EXECPTR_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        execPtr_getPriority(
        EXECPTR_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        execPtr_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            execPtr_setPriority(
        EXECPTR_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        execPtr_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = execPtr__Assign(this,pOther);
     @endcode:
     @param:    this    EXECPTR object pointer
     @param:    pOther  a pointer to another EXECPTR object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         execPtr_Assign(
        EXECPTR_DATA		*this,
        EXECPTR_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !execPtr_Validate(pOther) ) {
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
        execPtr_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        execPtr_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return execPtr_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        execPtr      *pCopy = execPtr_Copy(this);
     @endcode:
     @param:    this    EXECPTR object pointer
     @return:   If successful, a EXECPTR object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the EXECPTR object.
     */
    EXECPTR_DATA *     execPtr_Copy(
        EXECPTR_DATA       *this
    )
    {
        EXECPTR_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = execPtr_New(this->pFunc);
        if (pOther) {
            eRc = execPtr_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        execPtr_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            execPtr_Dealloc(
        OBJ_ID          objId
    )
    {
        EXECPTR_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((EXECPTR_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
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

    ERESULT         execPtr_Disable(
        EXECPTR_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            execPtr_setLastError(this, ERESULT_INVALID_OBJECT);
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            return execPtr_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        execPtr_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         execPtr_Enable(
        EXECPTR_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        execPtr_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    EXECPTR_DATA *  execPtr_Init(
        EXECPTR_DATA    *this,
        void            *pFunc
    )
    {
        uint32_t        cbSize = sizeof(EXECPTR_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_EXECPTR);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_EXECPTR);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&execPtr_Vtbl);
        
        execPtr_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->pFunc = pFunc;

    #ifdef NDEBUG
    #else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "offsetof(eRc) = %lu\n", offsetof(EXECPTR_DATA,eRc));
        fprintf(stderr, "sizeof(EXECPTR_DATA) = %lu\n", sizeof(EXECPTR_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(EXECPTR_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         execPtr_IsEnabled(
        EXECPTR_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            execPtr_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        execPtr_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          execPtr_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    )
    {
        EXECPTR_DATA   *this = objId;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !execPtr_Validate(this) ) {
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
                            return execPtr_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return execPtr_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return execPtr_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return execPtr_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pStr);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = execPtr_ToDebugString(this,4);
     @endcode:
     @param:    this    EXECPTR object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     execPtr_ToDebugString(
        EXECPTR_DATA      *this,
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
        if( !execPtr_Validate(this) ) {
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
                     "{%p(execPtr) pFunc=%p\n",
                     this,
                     this->pFunc
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
        
        if (this->pDesc) {
            if (indent) {
                AStr_AppendCharRepeatW(pStr, indent, ' ');
            }
            str[0] = '\0';
            j = snprintf(
                         str,
                         sizeof(str),
                         "desc = \"%s\"\n",
                         AStr_getData(this->pDesc)
                         );
            AStr_AppendA(pStr, str);
        }
        
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(execPtr)}\n", this);
        AStr_AppendA(pStr, str);
        
        execPtr_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     execPtr_ToJSON(
        EXECPTR_DATA      *this
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !execPtr_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{ \"objectType\":\"%s\"",
                     pInfo->pClassName
                     );
        AStr_AppendA(pStr, str);
        
        if (this->pDesc) {
            str[0] = '\0';
            j = snprintf(
                         str,
                         sizeof(str),
                         " \"desc\":\"%s\" ",
                         AStr_getData(this->pDesc)
                         );
            AStr_AppendA(pStr, str);
        }
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            execPtr_Validate(
        EXECPTR_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_EXECPTR) )
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


        if( !(obj_getSize(this) >= sizeof(EXECPTR_DATA)) ) {
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


