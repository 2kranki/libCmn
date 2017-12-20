// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   crc.c
 *	Generated 07/25/2017 10:42:33
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
#include <crc_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    CRC_DEF         crcDefs[5] = {
        {   "CRC-16 (ARC)",
            16,                     // Width
            0x8005,                 // Poly
            0x0000,                 // Initial Value
            1,                      // fReflectInput
            1,                      // fReflectOutput
            0x0000,                 // Xor Output
            0xBB3D                  // Checksum for "123456789"
        },
        {   "CRC-16 (CCITT)",
            16,                     // Width
            0x1021,                 // Poly
            0x1D0F,                 // Initial Value
            0,                      // fReflectInput
            0,                      // fReflectOutput
            0x0000,                 // Xor Output
            0xE5CC                  // Checksum for "123456789"
        },
        {
            "CRC-32",
            32,                     // Width
            0x04C11DB7,             // Poly
            0xFFFFFFFF,             // Initial Value
            1,                      // fReflectInput
            1,                      // fReflectOutput
            0xFFFFFFFF,             // Xor Output
            0xCBF43926              // Checksum for "123456789"
        },
        {
            "CRC-32 (IEEE)",
            32,                     // Width
            0x04C11DB7,             // Poly
            0xFFFFFFFF,             // Initial Value
            1,                      // fReflectInput
            1,                      // fReflectOutput
            0xFFFFFFFF,             // Xor Output
            0xCBF43926              // Checksum for "123456789"
        },
        {
            "CRC-32 (MPEG2)",
            32,                     // Width
            0x04C11DB7,             // Poly
            0xFFFFFFFF,             // Initial Value
            0,                      // fReflectInput
            0,                      // fReflectOutput
            0x00000000,             // Xor Output
            0x0376E6E7              // Checksum for "123456789"
        }
    };


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //**********************************************************
    //				C r c 3 2 T a b l e   B u i l d
    //**********************************************************
    
    ERESULT         crc_BuildCrc32Table(
        CRC_DATA        *this
    )
    {
        ERESULT			eRc = ERESULT_SUCCESS;
        uint32_t		i;
        uint32_t		j;
        uint32_t		crc;
        uint32_t        highbit;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !crc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if( NULL == this->pCrc32Table )
            ;
        else {
            mem_Free( this->pCrc32Table );
            this->pCrc32Table = NULL;
        }
        
        // Allocate the table.
        this->pCrc32Table = mem_Malloc( (sizeof(uint32_t) * 256) );
        if( NULL == this->pCrc32Table ) {
            eRc = ERESULT_OUT_OF_MEMORY;
            goto Exit00;
        }
        
        // Build the table values.
        for( i=0; i<256; ++i ) {
            crc = i;
            crc <<= (this->pDef->width - 8);
            for (j=8; j>0; --j) {
                highbit = crc & this->topbit;
                crc <<= 1;
                if (highbit) {
                    crc ^= this->pDef->poly;
                }
            }
            this->pCrc32Table[i] = crc & this->crcMask;
        }
        
        // Return to caller.
        eRc = ERESULT_SUCCESS;
    Exit00:
        return eRc;
    }
    
    

    //  Returns the value v with the bottom b [0,32] bits
    // reflected around their center.
    uint32_t        crc_Reflect(
        uint32_t        v,
        int             cBits
    )
    {
        int             i;
        uint32_t        t = v;
        
        for (i=0; i<cBits; i++) {
            if (t & 1L)
                v |=  (1 << ((cBits - 1) - i));
            else
                v &= ~(1 << ((cBits - 1) - i));
            t >>= 1;
        }
        return v;
    }
    
    
    

    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    CRC_DATA *     crc_Alloc(
    )
    {
        CRC_DATA       *this;
        uint32_t        cbSize = sizeof(CRC_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    CRC_DATA *      crc_New(
        CRC_TYPE        type
    )
    {
        CRC_DATA        *this;
        
        this = crc_Alloc( );
        if (this) {
            this = crc_Init(this, type);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint32_t        crc_getCheck(
        CRC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !crc_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        crc_setLastError(this, ERESULT_SUCCESS);
        return this->pDef->check;
    }
    
    
    uint32_t        crc_getCrc(
        CRC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !crc_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        crc_setLastError(this, ERESULT_SUCCESS);
        return this->crc;
    }
    
    
    bool            crc_setCrc(
        CRC_DATA        *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !crc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->crc = value;
        
        crc_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         crc_getLastError(
        CRC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !crc_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        return this->eRc;
    }


    bool            crc_setLastError(
        CRC_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !crc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                      A c c u m
    //---------------------------------------------------------------
    
    uint32_t        crc_AccumBlock(
        CRC_DATA		*this,
        uint32_t        len,
        const
        uint8_t         *pData
    )
    {
        uint32_t        index;
        uint32_t        crc;
        uint8_t         byte;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !crc_Validate(this) ) {
            DEBUG_BREAK();
            return crc_getLastError(this);
        }
        if (pData == NULL) {
            DEBUG_BREAK();
            crc_setLastError(this, ERESULT_INVALID_PARAMETER);
            return 0;
        }
#endif

        if (len == 0) {
            crc_setLastError(this, ERESULT_SUCCESS);
            return 0;
        }
        crc = this->pDef->init;
        
        // Accumulate the CRC.
        while (len--) {
            byte = *pData++;
            if (this->pDef->fRefIn) {
                byte = crc_Reflect(byte, 8);
            }
            index = (uint16_t)(((crc >> (this->pDef->width - 8)) ^ byte) & 0xFF);
            crc = (crc << 8) ^ this->pCrc32Table[index];
        }
        
        // Now adjust it.
        if (this->pDef->fRefOut) {
            crc = crc_Reflect(crc, this->pDef->width);
        }
        crc ^= this->pDef->xorout;
        crc &= this->crcMask;
        this->crc = crc;
        
        // Return to caller.
        crc_setLastError(this, ERESULT_SUCCESS);
        return crc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = crc__Assign(this,pOther);
     @endcode
     @param     this    CRC object pointer
     @param     pOther  a pointer to another CRC object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         crc_Assign(
        CRC_DATA		*this,
        CRC_DATA        *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !crc_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !crc_Validate(pOther) ) {
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
        crc_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        crc_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return crc_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        crc      *pCopy = crc_Copy(this);
     @endcode
     @param     this    CRC object pointer
     @return    If successful, a CRC object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the CRC object.
     */
    CRC_DATA *     crc_Copy(
        CRC_DATA       *this
    )
    {
        CRC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !crc_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = crc_New(obj_getSize(this));
        if (pOther) {
            eRc = crc_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        crc_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            crc_Dealloc(
        OBJ_ID          objId
    )
    {
        CRC_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !crc_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if( this->pCrc32Table ) {
            mem_Free( this->pCrc32Table );
            this->pCrc32Table = NULL;
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

    ERESULT         crc_Disable(
        CRC_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            crc_setLastError(this, ERESULT_INVALID_OBJECT);
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !crc_Validate(this) ) {
            DEBUG_BREAK();
            return crc_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        crc_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         crc_Enable(
        CRC_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !crc_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        crc_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    CRC_DATA *      crc_Init(
        CRC_DATA        *this,
        CRC_TYPE        type
    )
    {
        uint32_t        cbSize = sizeof(CRC_DATA);
        ERESULT         eRc;
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_CRC);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_CRC);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&crc_Vtbl);
        
        crc_setLastError(this, ERESULT_GENERAL_FAILURE);

        this->type = type;
        this->pDef = &crcDefs[type-1];
        this->topbit = ((uint32_t)1 << (this->pDef->width - 1));
        this->crcMask = ((((uint32_t)1 << (this->pDef->width - 1)) - 1) << 1) | 1;
        switch( type ) {
            case	CRC_TYPE_16:						// CRC-16 (Old used in PKARC)
                eRc = crc_BuildCrc32Table( this );
                if( ERESULT_FAILED(eRc) ) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }
                break;
            case	CRC_TYPE_CCITT_16:                  // 16-Bit CCITT CRC
                eRc = crc_BuildCrc32Table( this );
                if( ERESULT_FAILED(eRc) ) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }
                break;
            case	CRC_TYPE_32:						// CRC-32 (New used in PKZIP)(Default)
                eRc = crc_BuildCrc32Table( this );
                if( ERESULT_FAILED(eRc) ) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }
                break;
            case	CRC_TYPE_IEEE_32:					// 32-Bit IEEEE-802 CRC
                eRc = crc_BuildCrc32Table( this );
                if( ERESULT_FAILED(eRc) ) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }
                break;
            case	CRC_TYPE_MPEG2_32:					// 32-Bit MPEG2 CRC
                eRc = crc_BuildCrc32Table( this );
                if( ERESULT_FAILED(eRc) ) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }
                break;
            default:                                    // Invalid CRC Type
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
                break;
        }
        

    #ifdef NDEBUG
    #else
        if( !crc_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(CRC_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         crc_IsEnabled(
        CRC_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !crc_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            crc_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        crc_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          crc_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        CRC_DATA   *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !crc_Validate(this) ) {
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
                            return crc_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return crc_Enable;
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
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = crc_ToDebugString(this,4);
     @endcode
     @param     this    CRC object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     crc_ToDebugString(
        CRC_DATA      *this,
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
        if( !crc_Validate(this) ) {
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
                     "{%p(crc)\n",
                     this
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
        j = snprintf(str, sizeof(str), " %p(crc)}\n", this);
        AStr_AppendA(pStr, str);
        
        crc_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            crc_Validate(
        CRC_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_CRC) )
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


        if( !(obj_getSize(this) >= sizeof(CRC_DATA)) ) {
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


