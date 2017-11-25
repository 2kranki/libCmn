// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ebcdic.c
 *	Generated 02/12/2017 23:40:15
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
#include "ebcdic_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    
    static
    const
    uint8_t     Ascii2EbcdicTable[128] = {
        0x00,0x01,0x02,0x03,0x04,0x2D,0x2E,0x2F,    /* 000-007 */
        0x16,0x05,0x25,0x0B,0x0C,0x0D,0x0E,0x0F,    /* 008-015 */
        0x10,0x11,0x12,0x13,0x14,0x3D,0x32,0x26,    /* 016-023 */
        0x18,0x19,0x3F,0x27,0x1C,0x1D,0x1E,0x1F,    /* 024-031 */
        0x40,0x5A,0x7F,0x7B,0x5B,0x6C,0x50,0x7D,    /* 032-039 */
        0x4D,0x5D,0x5C,0x4E,0x6B,0x60,0x4B,0x61,    /* 040-047 */
        0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,    /* 048-055 */
        0xF8,0xF9,0x7A,0x5E,0x4C,0x7E,0x6E,0x6F,    /* 056-063 */
        0x7C,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,    /* 064-071 */
        0xC8,0xC9,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,    /* 072-079 */
        0xD7,0xD8,0xD9,0xE2,0xE3,0xE4,0xE5,0xE6,    /* 080-087 */
        0xE7,0xE8,0xE9,0xAD,0xE0,0xBD,0x5F,0x6D,    /* 088-095 */
        0x79,0x81,0x82,0x83,0x84,0x85,0x86,0x87,    /* 096-103 */
        0x88,0x89,0x91,0x92,0x93,0x94,0x95,0x96,    /* 104-111 */
        0x97,0x98,0x99,0xA2,0xA3,0xA4,0xA5,0xA6,    /* 112-119 */
        0xA7,0xA8,0xA9,0xC0,0x6A,0xD0,0xA1,0x07     /* 120-127 */
    };
    
    
    static
    const
    uint8_t     Ebcdic2AsciiTable[256] = {
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 00-07 */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 08-0F */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 10-17 */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 18-1F */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 20-27 */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 28-2F */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 30-37 */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 38-3F */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 40-47 */
        0x20,0x20,0x20,0x2E,0x3C,0x28,0x2B,0x7C,    /* 48-4F */
        0x26,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 50-57 */
        0x20,0x20,0x21,0x24,0x2A,0x29,0x3B,0x7E,    /* 58-5F */
        0x2D,0x2F,0x20,0x20,0x20,0x20,0x20,0x20,    /* 60-67 */
        0x20,0x20,0x20,0x2C,0x25,0x5F,0x3E,0x3F,    /* 68-6F */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 70-77 */
        0x20,0x20,0x3A,0x23,0x40,0x27,0x3D,0x22,    /* 78-7F */
        0x24,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 80-87 */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 88-8F */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 90-97 */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* 98-9F */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* A0-A7 */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* A8-AF */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* B0-B7 */
        0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,    /* B8-BF */
        0x20,0x41,0x42,0x43,0x44,0x45,0x46,0x47,    /* C0-C7 */
        0x48,0x49,0x20,0x20,0x20,0x20,0x20,0x20,    /* C8-CF */
        0x20,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,    /* D0-D7 */
        0x51,0x52,0x20,0x20,0x20,0x20,0x20,0x20,    /* D8-DF */
        0x20,0x20,0x53,0x54,0x55,0x56,0x57,0x58,    /* E0-E7 */
        0x59,0x5A,0x20,0x20,0x20,0x20,0x20,0x20,    /* E8-EF */
        0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,    /* F0-F7 */
        0x38,0x39,0x20,0x20,0x20,0x20,0x20,0x20     /* F8-FF */
    };
    
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    EBCDIC_DATA *     ebcdic_Alloc(
    )
    {
        EBCDIC_DATA     *this;
        uint32_t        cbSize = sizeof(EBCDIC_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    EBCDIC_DATA *     ebcdic_New(
    )
    {
        EBCDIC_DATA       *this;
        
        this = ebcdic_Alloc( );
        if (this) {
            this = ebcdic_Init(this);
        } 
        return this;
    }



    uint8_t         asciiToEbcdic(
        char            asciiChar
    )
    {
        return Ascii2EbcdicTable[asciiChar & 0x7F];
    }
    

    
    char            ebcdicToAscii(
        uint8_t         ebcdicChar
    )
    {
        return Ebcdic2AsciiTable[ebcdicChar & 0xFF];
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         ebcdic_getLastError(
        EBCDIC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ebcdic_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            ebcdic_setLastError(
        EBCDIC_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !ebcdic_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        ebcdic_getPriority(
        EBCDIC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ebcdic_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        ebcdic_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }

    bool            ebcdic_setPriority(
        EBCDIC_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !ebcdic_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        ebcdic_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    uint32_t        ebcdic_getSize(
        EBCDIC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !ebcdic_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        ebcdic_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }




    ASTR_DATA * ebcdic_getStr(
        EBCDIC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ebcdic_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        ebcdic_setLastError(this, ERESULT_SUCCESS);
        return this->pStr;
    }
    
    
    bool        ebcdic_setStr(
        EBCDIC_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !ebcdic_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        ebcdic_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = ebcdic__Assign(this,pOther);
     @endcode
     @param     this    EBCDIC object pointer
     @param     pOther  a pointer to another EBCDIC object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         ebcdic_Assign(
        EBCDIC_DATA		*this,
        EBCDIC_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ebcdic_Validate(this) ) {
            DEBUG_BREAK();
            return ebcdic_getLastError(this);
        }
        if( !ebcdic_Validate(pOther) ) {
            DEBUG_BREAK();
            return ebcdic_getLastError(pOther);
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
        ebcdic_setLastError(this, ERESULT_SUCCESS);
    //eom:
        //FIXME: Implement the assignment.        
        ebcdic_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return ebcdic_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        ebcdic      *pCopy = ebcdic_Copy(this);
     @endcode
     @param     this    EBCDIC object pointer
     @return    If successful, a EBCDIC object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the EBCDIC object.
     */
    EBCDIC_DATA *     ebcdic_Copy(
        EBCDIC_DATA       *this
    )
    {
        EBCDIC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ebcdic_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ebcdic_New( );
        if (pOther) {
            eRc = ebcdic_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        ebcdic_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            ebcdic_Dealloc(
        OBJ_ID          objId
    )
    {
        EBCDIC_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !ebcdic_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((EBCDIC_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        ebcdic_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         ebcdic_Disable(
        EBCDIC_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            ebcdic_setLastError(this, ERESULT_INVALID_OBJECT);
            return ebcdic_getLastError(this);
        }
    #ifdef NDEBUG
    #else
        if( !ebcdic_Validate(this) ) {
            DEBUG_BREAK();
            return ebcdic_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        ebcdic_setLastError(this, ERESULT_SUCCESS);
        return ebcdic_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         ebcdic_Enable(
        EBCDIC_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !ebcdic_Validate(this) ) {
            DEBUG_BREAK();
            return ebcdic_getLastError(this);
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        ebcdic_setLastError(this, ERESULT_SUCCESS);
        return ebcdic_getLastError(this);
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    EBCDIC_DATA *   ebcdic_Init(
        EBCDIC_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(EBCDIC_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_EBCDIC);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_EBCDIC);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ebcdic_Vtbl);
        
        ebcdic_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !ebcdic_Validate(this) ) {
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
    
    ERESULT         ebcdic_IsEnabled(
        EBCDIC_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ebcdic_Validate(this) ) {
            DEBUG_BREAK();
            return ebcdic_getLastError(this);
        }
#endif
        
        if (obj_IsEnabled(this)) {
            ebcdic_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ebcdic_getLastError(this);
        }
        
        // Return to caller.
        ebcdic_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ebcdic_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = ebcdic_ToDebugString(this,4);
     @endcode
     @param     this    EBCDIC object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ebcdic_ToDebugString(
        EBCDIC_DATA      *this,
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
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(ebcdic) size=%d\n",
                     this,
                     ebcdic_getSize(this)
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
        j = snprintf(str, sizeof(str), " %p(ebcdic)}\n", this);
        AStr_AppendA(pStr, str);
        
        ebcdic_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            ebcdic_Validate(
        EBCDIC_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_EBCDIC) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(EBCDIC_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


