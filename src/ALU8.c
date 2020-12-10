// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ALU8.c
 *  Generated 12/06/2020 10:50:20
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
#include        <ALU8_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    static
    uint8_t         evenParityTable[256] = {
        1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
        0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
        0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
        1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
        0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
        1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
        1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
        0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
        0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
        1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
        1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
        0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
        1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,
        0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
        0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,
        1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1
    };




 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    int             ALU8_even_parity (
        uint32_t         x
    )
    {
        x ^= x >> 4;
        x ^= x >> 2;
        x ^= x >> 1;
        return (~x) & 1;
    }





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    ALU8_DATA *     ALU8_Alloc (
        void
    )
    {
        ALU8_DATA       *this;
        uint32_t        cbSize = sizeof(ALU8_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ASTR_DATA *     ALU8_GenEvenParityTable (
        void
    )
    {
        uint16_t        x = 0;
        ASTR_DATA       *pStr = AStr_New();

        if (OBJ_NIL == pStr )
            ;
        else {
            for (x=0; x<256; ++x) {
                if (ALU8_even_parity((uint8_t)x))
                    AStr_AppendA(pStr, "1,");
                else
                    AStr_AppendA(pStr, "0,");
            }
        }

        return pStr;
    }



    //---------------------------------------------------------------
    //                          E x e c
    //---------------------------------------------------------------

    /*!
     Execute an ALU operation.
     @param     oper        operation to perform, see E8085ALU_OPS.
     @param     flags       The flags to be used for input especially
                            the carry flag and the aux carray flag.
     @param     op1         operand 1
     @param     op2         operand 2
     @param     pResult     If non-null, store result at this location.
     @param     pFlags      if non-null, store the new flags at this
                            location.
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ALU8_Exec (
        int             oper,
        uint8_t         op1,
        uint8_t         op2,
        uint8_t         flags,
        uint8_t         *pFlags,
        uint8_t         *pResult
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint16_t        result = (op1 & 0xFF);
        uint8_t         newFlags = 0;
        uint8_t         tmp = 0;

        // Do initialization.

        switch (oper) {

            case ALU8_OP_UNKNOWN:
                result = 0;
                break;

            case ALU8_OP_ADD:
                tmp = (flags & ALU8_FLAG_CARRY) ? 1 : 0;
                result += op2 + tmp;
                if (result & 0xFF00) {
                    newFlags |= ALU8_FLAG_CARRY;
                }
                newFlags |= (((op1 & 0x0F) + (op2 & 0x0F) + tmp) > 15)
                            ? ALU8_FLAG_AUX_CARRY : 0;
                break;

            case ALU8_OP_AND:
                result &= op2;
                break;

            case ALU8_OP_COMPLEMENT:
                result = -op1;
                goto set;
                break;

            case ALU8_OP_DEC_ADJUST:
                // If the low 4 bits have a value > 9 or Aux_Carry == true,
                //      add 6 to lower 4 bits.
                if (((result & 0x0F) > 9) || (flags & ALU8_FLAG_AUX_CARRY)
                ) {
                    if ((result & 0x0F) > 3)
                        newFlags |= ALU8_FLAG_AUX_CARRY;
                    result += 0x06;
                }
                if (((result & 0xF0) > 0x90) || (flags & ALU8_FLAG_CARRY)
                ) {
                    if ((result & 0x00F0) > 0x0030)
                        newFlags |= ALU8_FLAG_CARRY;
                    result += 0x60;
                }
                break;

            case ALU8_OP_NOT:
                result = ~op1;
                goto set;
                break;

            case ALU8_OP_OR:
                result |= op2;
                break;

            case ALU8_OP_SHIFT_LEFT:
                result <<= 1;
                result |= (flags & ALU8_FLAG_CARRY) ? 1 : 0;
                if (result & 0xFF00) {
                    newFlags |= ALU8_FLAG_CARRY;
                }
                goto set;
                break;

            case ALU8_OP_SHIFT_RIGHT:
                if (result & 0x01) {
                    newFlags |= ALU8_FLAG_CARRY;
                }
                result = result >> 1;
                result |= (flags & ALU8_FLAG_CARRY) ? 0x80 : 0;
                goto set;
                break;

            case ALU8_OP_SUB:
                result -= (flags & ALU8_FLAG_CARRY) ? 1 : 0;
                result -= op2;
                if (result & 0xFF00) {
                    newFlags |= ALU8_FLAG_CARRY;
                }
                newFlags &= ~ALU8_FLAG_AUX_CARRY;
                newFlags |= (((op1 & 0x0F) + (op2 & 0x0F)) > 15)
                            ? ALU8_FLAG_AUX_CARRY : 0;
                break;

            case ALU8_OP_XOR:
                result ^= op2;
                break;
        }

        // Set the flags.
        if (0 == (result & 0x00FF)) {
            newFlags |= ALU8_FLAG_ZERO;
        }
        if (evenParityTable[result & 0x00FF]) {
            newFlags |= ALU8_FLAG_PARITY;
        }
        if (result & 0x80) {
            newFlags |= ALU8_FLAG_SIGN;
        }

        // Update the external registers if needed.
    set:
        if (pFlags) {
            *pFlags = newFlags;
        }
        if (pResult) {
            *pResult = result & 0xFF;
        }

        // Return to caller.
        return eRc;
    }



    ALU8_DATA *     ALU8_New (
        void
    )
    {
        ALU8_DATA       *this;
        
        this = ALU8_Alloc( );
        if (this) {
            this = ALU8_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        ALU8_getPriority (
        ALU8_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            ALU8_setPriority (
        ALU8_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
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
    
    uint32_t        ALU8_getSize (
        ALU8_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * ALU8_getStr (
        ALU8_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        ALU8_setStr (
        ALU8_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  ALU8_getSuperVtbl (
        ALU8_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
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
        ERESULT eRc = ALU8_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another ALU8 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         ALU8_Assign (
        ALU8_DATA       *this,
        ALU8_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ALU8_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

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
        //pOther->x     = this->x; 

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
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             ALU8_Compare (
        ALU8_DATA     *this,
        ALU8_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!ALU8_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        ALU8      *pCopy = ALU8_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a ALU8 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ALU8_DATA *     ALU8_Copy (
        ALU8_DATA       *this
    )
    {
        ALU8_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef ALU8_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = ALU8_New( );
        if (pOther) {
            eRc = ALU8_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            ALU8_Dealloc (
        OBJ_ID          objId
    )
    {
        ALU8_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((ALU8_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        ALU8_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        ALU8      *pDeepCopy = ALU8_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a ALU8 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ALU8_DATA *     ALU8_DeepyCopy (
        ALU8_DATA       *this
    )
    {
        ALU8_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ALU8_New( );
        if (pOther) {
            eRc = ALU8_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ALU8_Disable (
        ALU8_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ALU8_Enable (
        ALU8_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ALU8_DATA *   ALU8_Init (
        ALU8_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(ALU8_DATA);
        //ERESULT         eRc;
        
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_ALU8);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ALU8_Vtbl);
#ifdef  ALU8_JSON_SUPPORT
        JsonIn_RegisterClass(ALU8_Class());
#endif
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "ALU8::sizeof(ALU8_DATA) = %lu\n", 
                sizeof(ALU8_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(ALU8_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         ALU8_IsEnabled (
        ALU8_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
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
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = ALU8_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "ALU8", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          ALU8_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        ALU8_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(ALU8_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)ALU8_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return ALU8_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return ALU8_Enable;
                        }
                        break;

                    case 'P':
#ifdef  ALU8_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return ALU8_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return ALU8_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return ALU8_ToDebugString;
                        }
#ifdef  ALU8_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return ALU8_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return ALU8_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == ALU8_ToDebugString)
                    return "ToDebugString";
#ifdef  ALU8_JSON_SUPPORT
                if (pData == ALU8_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ALU8_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     ALU8_ToDebugString (
        ALU8_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ALU8_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    ALU8_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
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
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            ALU8_Validate (
        ALU8_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_ALU8))
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


        if (!(obj_getSize(this) >= sizeof(ALU8_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


