// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   appl.c
 *	Generated 06/05/2017 10:38:38
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
#include <appl_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            appl_task_body(
        void            *pData
    )
    {
        //APPL_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    APPL_DATA *     appl_Alloc(
    )
    {
        APPL_DATA       *this;
        uint32_t        cbSize = sizeof(APPL_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    APPL_DATA *     appl_New(
        uint16_t    cArgs,
        const
        char        *pArgs[]
    )
    {
        APPL_DATA       *this;
        
        this = appl_Alloc( );
        if (this) {
            this = appl_Init(this, cArgs, pArgs);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         appl_getLastError(
        APPL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            appl_setLastError(
        APPL_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        appl_getPriority(
        APPL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        appl_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            appl_setPriority(
        APPL_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        appl_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    NODEHASH_DATA * appl_getProperties(
        APPL_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        appl_setLastError(this, ERESULT_SUCCESS);
        return this->pProperties;
    }
    
    
    bool            appl_setProperties(
        APPL_DATA       *this,
        NODEHASH_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pProperties) {
            obj_Release(this->pProperties);
        }
        this->pProperties = pValue;
        
        appl_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    uint32_t        appl_getSize(
        APPL_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        appl_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                     A d d  P r o p e r t y
    //---------------------------------------------------------------
    
    ERESULT         appl_AddProperty(
        APPL_DATA       *this,
        NODE_DATA       *pData
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pData) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (OBJ_NIL == this->pProperties) {
            this->pProperties = nodeHash_New( 17 );
            if (OBJ_NIL == this->pProperties) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        eRc = nodeHash_Add(this->pProperties, pData);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code:
        ERESULT eRc = appl__Assign(this,pOther);
     @endcode:
     @param:    this    APPL object pointer
     @param:    pOther  a pointer to another APPL object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         appl_Assign(
        APPL_DATA		*this,
        APPL_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return appl_getLastError(this);
        }
        if( !appl_Validate(pOther) ) {
            DEBUG_BREAK();
            return appl_getLastError(pOther);
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
        appl_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        appl_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return appl_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        appl      *pCopy = appl_Copy(this);
     @endcode:
     @param:    this    APPL object pointer
     @return:   If successful, a APPL object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the APPL object.
     */
    APPL_DATA *     appl_Copy(
        APPL_DATA       *this
    )
    {
        APPL_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        //FIXME: pOther = appl_New(obj_getSize(this));
        if (pOther) {
            eRc = appl_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        appl_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            appl_Dealloc(
        OBJ_ID          objId
    )
    {
        APPL_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((APPL_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        appl_setProperties(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         appl_Disable(
        APPL_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            appl_setLastError(this, ERESULT_INVALID_OBJECT);
            return appl_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return appl_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        appl_setLastError(this, ERESULT_SUCCESS);
        return appl_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         appl_Enable(
        APPL_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return appl_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        appl_setLastError(this, ERESULT_SUCCESS);
        return appl_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    APPL_DATA *     appl_Init(
        APPL_DATA       *this,
        uint16_t        cArgs,
        const
        char            **pArgs
    )
    {
        uint32_t        cbSize = sizeof(APPL_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_APPL);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_APPL);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&appl_Vtbl);
        
        appl_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->cArgs = cArgs;
        this->pArgs = pArgs;

    #ifdef NDEBUG
    #else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(APPL_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         appl_IsEnabled(
        APPL_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return appl_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            appl_setLastError(this, ERESULT_SUCCESS_TRUE);
            return appl_getLastError(this);
        }
        
        // Return to caller.
        appl_setLastError(this, ERESULT_SUCCESS_FALSE);
        return appl_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //              N u m b e r  O f  P r o p e r t i e s
    //---------------------------------------------------------------
    
    uint16_t        appl_NumberOfProperties(
        APPL_DATA       *this
    )
    {
        uint16_t        num = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (this->pProperties) {
            num = nodeHash_getSize(this->pProperties);
        }
        
        // Return to caller.
        return num;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P r o p e r t y
    //---------------------------------------------------------------
    
    NODE_DATA *     appl_Property(
        APPL_DATA       *this,
        const
        char            *pName
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pProperty = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            eRc = nodeHash_FindA(this->pProperties, pName, &pProperty);
        }
        
        // Return to caller.
        return pProperty;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          appl_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    )
    {
        APPL_DATA   *this = objId;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !appl_Validate(this) ) {
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
                            return appl_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Ensable", (char *)pStr) == 0) {
                            return appl_Enable;
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
        ASTR_DATA      *pDesc = appl_ToDebugString(this,4);
     @endcode:
     @param:    this    APPL object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     appl_ToDebugString(
        APPL_DATA      *this,
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
        if( !appl_Validate(this) ) {
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
                     "{%p(appl) fDebug=%c fForce=%c iVerbose=%d\n",
                     this,
                     (this->fDebug ? 'T' : 'F'),
                     (this->fDebug ? 'T' : 'F'),
                     this->iVerbose
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
        j = snprintf(str, sizeof(str), " %p(appl)}\n", this);
        AStr_AppendA(pStr, str);
        
        appl_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            appl_Validate(
        APPL_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_APPL) )
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


        if( !(obj_getSize(this) >= sizeof(APPL_DATA)) ) {
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


