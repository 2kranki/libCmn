// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Opc360.c
 *	Generated 02/29/2020 23:01:22
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
#include        <Opc360_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    
    typedef struct Opcode_feature_s {
        char        *pDesc;
        uint16_t    value;
    } OPCODE_FEATURE;

    static
    OPCODE_FEATURE  OpcFeatures[] = {
        {"OPCODE_FEATURE_CC",      0x0080},    // Condition Code is set
        {"OPCODE_FEATURE_PR",      0x0040},    // Privileged Instruction
        {"OPCODE_FEATURE_DEC",     0x0020},    // Requires Decimal Arithmetic Unit
        {"OPCODE_FEATURE_MEMP",    0x0010},    // Requires Storage Protection
        {"OPCODE_FEATURE_DIRC",    0x0008},    // Requires Direct Control Feature
    };
    static
    uint16_t        cOpcFeatures = sizeof(OpcFeatures)/sizeof(OPCODE_FEATURE);


    typedef struct Opcode_interrupt_s {
        char        *pDesc;
        uint16_t    value;
    } OPCODE_INTERRUPT;

    static
    OPCODE_INTERRUPT OpcInterrupts[] = {
        {"OPCODE_INTERRUPT_OPER",    1},    // Operation
        {"OPCODE_INTERRUPT_PRIV",    2},    // Priviliged Operation
        {"OPCODE_INTERRUPT_EXEC",    3},    // Execute
        {"OPCODE_INTERRUPT_PROT",    4},    // Protection
        {"OPCODE_INTERRUPT_ADDR",    5},    // Addressing
        {"OPCODE_INTERRUPT_SPEC",    6},    // Specification
        {"OPCODE_INTERRUPT_DATA",    7},    // Data
        {"OPCODE_INTERRUPT_FIXO",    8},    // Fixed-point Overflow
        {"OPCODE_INTERRUPT_FIXD",    9},    // Fixed-point Divide
        {"OPCODE_INTERRUPT_DECO",   10},    // Decimal Overflow
        {"OPCODE_INTERRUPT_DECD",   11},    // Decimal Divide
        {"OPCODE_INTERRUPT_EXO",    12},    // Exponent Overflow
        {"OPCODE_INTERRUPT_EXU",    13},    // Exponent Underflow
        {"OPCODE_INTERRUPT_SIG",    14},    // Significance
        {"OPCODE_INTERRUPT_FPD",    15},    // Floating-point Divide
        {"OPCODE_INTERRUPT_SEGT",   16},    // Segment Translation
        {"OPCODE_INTERRUPT_PAGT",   17}     // Page Translation
    };
    static
    uint16_t        cOpcInterrupts = sizeof(OpcInterrupts)/sizeof(OPCODE_INTERRUPT);


    typedef struct Opcode_type_s {
        uint16_t    value;
        char        *pDesc;
    } OPCODE_TYPE;

    static
    OPCODE_TYPE     OpcTypes[] = {
        {0,     "OPCODE_TYPE_UNKNOWN"},
        {1,     "OPCODE_TYPE_NONE"},           // No operands
        {2,     "OPCODE_TYPE_I"},              // integer
        {3,     "OPCODE_TYPE_R"},              // r1
        {4,     "OPCODE_TYPE_RR"},             // r1,r2
        {5,     "OPCODE_TYPE_RS"},             // r1,r3,d2(b2)
        {6,     "OPCODE_TYPE_RX"},             // r1,d2(x2,b2)
        {7,     "OPCODE_TYPE_SI"},             // d1(b1),i2
        {8,     "OPCODE_TYPE_SS1"},            // d1(l1,b1),d2(l2,b2)
        {9,     "OPCODE_TYPE_SS2"},            // d1(l,b1),d2(b2)
        {10,    "OPCODE_TYPE_PSEUDO"},         // Pseudo Opcode
        {11,    "OPCODE_TYPE_MACRO"},          // Macro Instruction
    };
    static
    uint16_t        cOpcTypes = sizeof(OpcTypes)/sizeof(OPCODE_TYPE);




 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            Opc360_task_body (
        void            *pData
    )
    {
        //OPC360_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OPC360_DATA *     Opc360_Alloc (
        void
    )
    {
        OPC360_DATA       *this;
        uint32_t        cbSize = sizeof(OPC360_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    const
    char *          Opc360_FeatureDesc (
        uint16_t        num
    )
    {
        uint32_t        i;

        if (num) {
            for (i=0; i<cOpcFeatures; i++) {
                if (num == OpcFeatures[i].value) {
                    return OpcFeatures[i].pDesc;
                }
            }
        }
        return 0;
    }


    uint16_t        Opc360_FeatureValue (
        const
        char             *pStrA
    )
    {
        uint32_t            i;

        if (pStrA) {
            for (i=0; i<cOpcFeatures; i++) {
                if (0 == strcmp(pStrA, OpcFeatures[i].pDesc)) {
                    return OpcFeatures[i].value;
                }
            }
        }
        return 0;
    }



    const char *    Opc360_InterruptDesc (
        uint16_t        num
    )
    {
        uint32_t        i;

        if (num) {
            for (i=0; i<cOpcInterrupts; i++) {
                if (num == OpcInterrupts[i].value) {
                    return OpcInterrupts[i].pDesc;
                }
            }
        }
        return 0;
    }


    uint16_t          Opc360_InterruptValue (
        const
        char              *pStrA
    )
    {
        uint32_t            i;

        if (pStrA) {
            for (i=0; i<cOpcInterrupts; i++) {
                if (0 == strcmp(pStrA, OpcInterrupts[i].pDesc)) {
                    return OpcInterrupts[i].value;
                }
            }
        }
        return 0;
    }



    OPC360_DATA *     Opc360_New (
        void
    )
    {
        OPC360_DATA       *this;
        
        this = Opc360_Alloc( );
        if (this) {
            this = Opc360_Init(this);
        } 
        return this;
    }



    OPC360_DATA *   Opc360_NewA (
        const
        char            *pNameA
    )
    {
        OPC360_DATA       *this;

        this = Opc360_New( );
        if (this) {
            Opcode_setNameA((OPCODE_DATA *)this, pNameA);
        }
        return this;
    }



    const
    char *          Opc360_TypeDesc (
        uint16_t        num
    )
    {
        uint32_t        i;

        if (num) {
            for (i=0; i<cOpcTypes; i++) {
                if (num == OpcTypes[i].value) {
                    return OpcTypes[i].pDesc;
                }
            }
        }
        return 0;
    }


    uint16_t          Opc360_TypeValue (
        const
        char              *pStrA
    )
    {
        uint32_t            i;

        if (pStrA) {
            for (i=0; i<cOpcTypes; i++) {
                if (0 == strcmp(pStrA, OpcTypes[i].pDesc)) {
                    return OpcTypes[i].value;
                }
            }
        }
        return 0;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                         E n t r y
    //---------------------------------------------------------------

    OPCODE_ENTRY *  Opc360_getEntry (
        OPC360_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return &((OPCODE_DATA *)this)->entry;
    }


    //---------------------------------------------------------------
    //                          N a m e
    //---------------------------------------------------------------

    const
    char *          Opc360_getNameA (
        OPC360_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Opc360_getEntry(this)->Name;
    }



    //---------------------------------------------------------------
    //                         O p c o d e
    //---------------------------------------------------------------

    OPCODE_DATA *   Opc360_getOpcode (
        OPC360_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (OPCODE_DATA *)this;
    }


    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Opc360_getPriority (
        OPC360_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Opc360_setPriority (
        OPC360_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                         S i z e
    //---------------------------------------------------------------
    
    uint32_t        Opc360_getSize (
        OPC360_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Opc360_getSuperVtbl (
        OPC360_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
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
        ERESULT eRc = Opc360_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another OPC360 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Opc360_Assign (
        OPC360_DATA		*this,
        OPC360_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Opc360_Validate(pOther)) {
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
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
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
    ERESULT         Opc360_Compare (
        OPC360_DATA     *this,
        OPC360_DATA     *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;

#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Opc360_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = Opcode_Compare((OPCODE_DATA *)this, (OPCODE_DATA *)pOther);

        return eRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Opc360      *pCopy = Opc360_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OPC360 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OPC360_DATA *     Opc360_Copy (
        OPC360_DATA       *this
    )
    {
        OPC360_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef OPC360_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Opc360_New( );
        if (pOther) {
            eRc = Opc360_Assign(this, pOther);
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

    void            Opc360_Dealloc (
        OBJ_ID          objId
    )
    {
        OPC360_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OPC360_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

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
        Opc360      *pDeepCopy = Opc360_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OPC360 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OPC360_DATA *     Opc360_DeepyCopy (
        OPC360_DATA       *this
    )
    {
        OPC360_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Opc360_New( );
        if (pOther) {
            eRc = Opc360_Assign(this, pOther);
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
    ERESULT         Opc360_Disable (
        OPC360_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
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
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Opc360_Enable (
        OPC360_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
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
    //                          I n i t
    //---------------------------------------------------------------

    OPC360_DATA *   Opc360_Init (
        OPC360_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(OPC360_DATA);
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

        this = (OBJ_ID)Opcode_Init((OPCODE_DATA *)this);        // Needed for Inheritance
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Opc360_Vtbl);

        Opc360_getOpcode(this)->pFeatureDesc = Opc360_FeatureDesc;
        Opc360_getOpcode(this)->pFeatureValue = Opc360_FeatureValue;
        Opc360_getOpcode(this)->pInterruptDesc = Opc360_InterruptDesc;
        Opc360_getOpcode(this)->pInterruptValue = Opc360_InterruptValue;
        Opc360_getOpcode(this)->pTypeDesc = Opc360_TypeDesc;
        Opc360_getOpcode(this)->pTypeValue = Opc360_TypeValue;

#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Opc360::sizeof(OPC360_DATA) = %lu\n", 
                sizeof(OPC360_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OPC360_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Opc360_IsEnabled (
        OPC360_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
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
        void        *pMethod = Opc360_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Opc360", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Opc360_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OPC360_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Opc360_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(OPC360_DATA);
                break;

            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Opc360_Class();
                break;

            // Query for an address to specific data within the object.
            // This should be used very sparingly since it breaks the
            // object's encapsulation.
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {

                    case 'O':
                        if (str_Compare("Opcode", (char *)pStr) == 0) {
                            return this;
                        }
                        break;

                    case 'S':
                        if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                            return &this->pSuperVtbl;
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
                            return Opc360_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Opc360_Enable;
                        }
                        break;

#ifdef  OPC360_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Opc360_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Opc360_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Opc360_ToDebugString;
                        }
#ifdef  OPC360_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Opc360_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Opc360_ToDebugString)
                    return "ToDebugString";
#ifdef  OPC360_JSON_SUPPORT
                if (pData == Opc360_ToJson)
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
        ASTR_DATA      *pDesc = Opc360_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Opc360_ToDebugString (
        OPC360_DATA      *this,
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
        if (!Opc360_Validate(this)) {
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
                    Opc360_getSize(this),
                    obj_getRetainCount(this)
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
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            Opc360_Validate (
        OPC360_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_OPC360))
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


        if (!(obj_getSize(this) >= sizeof(OPC360_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


