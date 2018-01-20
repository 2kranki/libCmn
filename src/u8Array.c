// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   u8Array.c
 *	Generated 08/07/2015 09:47:23
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
#include    <u8Array_internal.h>
#include    <ascii.h>
#include    <file.h>
#include    <hex.h>
#include    <path_internal.h>
#include    <stdio.h>



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

    U8ARRAY_DATA *  u8Array_Alloc(
    )
    {
        U8ARRAY_DATA    *cbp;
        uint32_t        cbSize = sizeof(U8ARRAY_DATA);
        
        cbp = obj_Alloc( cbSize );
        
        return( cbp );
    }



    U8ARRAY_DATA *  u8Array_New(
    )
    {
        U8ARRAY_DATA    *this;
        
        this = u8Array_Alloc( );
        if (this) {
            this = u8Array_Init(this);
        }
        
        return this;
    }
    
    
    U8ARRAY_DATA *  u8Array_NewFromBuffer(
        uint32_t        size,
        uint8_t         *pData
    )
    {
        U8ARRAY_DATA    *this;
        
        this = u8Array_Alloc( );
        if (this) {
            this = u8Array_Init(this);
            if (this) {
                u8Array_AppendBuffer(this, size, pData);
            }
        }
        
        return this;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    bool            u8Array_setBigEndian(
        U8ARRAY_DATA    *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        obj_FlagSet(this, U8ARRAY_FLAG_BIGENDIAN, value);
        
        return true;
    }
    
    
    
    uint8_t *       u8Array_getData(
        U8ARRAY_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return array_Ptr(this->pData, 1);
    }
    
    
    
    uint16_t        u8Array_getMisc(
        U8ARRAY_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        this->eRc = ERESULT_SUCCESS;
        return this->misc;
    }
    
    bool            u8Array_setMisc(
        U8ARRAY_DATA    *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->misc = value;
        
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    
    
    
    uint32_t        u8Array_getSize(
        U8ARRAY_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return array_getSize(this->pData);
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                         A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         u8Array_Append(
        U8ARRAY_DATA	*this,
        U8ARRAY_DATA	*other
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !u8Array_Validate(other) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc =   array_Append(
                        this->pData,
                        other->pData
                );
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         u8Array_AppendBuffer(
        U8ARRAY_DATA	*this,
        uint32_t        size,
        uint8_t         *pData
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc =  array_AppendData(
                            this->pData,
                            size,
                            pData
                );
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         u8Array_AppendData(
        U8ARRAY_DATA	*this,
        uint8_t         data
    )
    {
        ERESULT         eRc;
        uint32_t        offset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        offset = array_getSize(this->pData);
        eRc =   array_AppendData(
                        this->pData,
                        1,
                        &data
                );
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         u8Array_AppendFile(
        U8ARRAY_DATA	*this,
        PATH_DATA       *pPath
    )
    {
        //ERESULT         eRc;
        int64_t         size = 0;
        int             chr;
        FILE            *pFile;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        size = file_SizeA(path_getData(pPath));
        if (-1 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }
        if (0 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        pFile = fopen(path_getData(pPath), "rb");
        if (NULL == pFile) {
            return ERESULT_FILE_NOT_FOUND;
        }
        while ( (chr = fgetc(pFile)) != EOF ) {
            u8Array_AppendData(this, (chr & 0xFF));
        }
        fclose(pFile);
        pFile = NULL;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    

    //---------------------------------------------------------------
    //                         A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         u8Array_Assign(
        U8ARRAY_DATA	*this,
        U8ARRAY_DATA	*pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (pOther->pData) {
            obj_Release(pOther->pData);
        }
        
        pOther->pData = array_Copy(this->pData);
        if (OBJ_NIL == pOther->pData) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                         C o p y
    //---------------------------------------------------------------
    
    U8ARRAY_DATA *  u8Array_Copy(
        U8ARRAY_DATA	*this
    )
    {
        U8ARRAY_DATA	*pOther;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = u8Array_New();
        if (pOther) {
            eRc = u8Array_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            u8Array_Dealloc(
        OBJ_ID          objId
    )
    {
        U8ARRAY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pData) {
            obj_Release(this->pData);
            this->pData = OBJ_NIL;
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    uint8_t         u8Array_Delete(
        U8ARRAY_DATA	*this,
        uint32_t        index
    )
    {
        uint8_t         data = 0;
        uint16_t        *pData;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if ((index > 0) && (index <= array_getSize(this->pData)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        pData = array_Ptr(this->pData, index);
        if (pData) {
            data = *pData;
            eRc = array_Delete(this->pData, index, 1);
            if (ERESULT_HAS_FAILED(eRc)) {
                return 0;
            }
        }
        
        // Return to caller.
        return data;
    }
    
    
    uint8_t         u8Array_DeleteFirst(
        U8ARRAY_DATA	*this
    )
    {
        uint8_t         data = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = u8Array_Delete(this,1);
        
        // Return to caller.
        return data;
    }
    
    
    uint8_t         u8Array_DeleteLast(
        U8ARRAY_DATA	*this
    )
    {
        uint8_t         data = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = u8Array_Delete(this, array_getSize(this->pData));
        
        // Return to caller.
        return data;
    }
    
    
    
    //---------------------------------------------------------------
    //                         G e t
    //---------------------------------------------------------------
    
    uint8_t         u8Array_Get(
        U8ARRAY_DATA	*this,
        uint32_t        index
    )
    {
        uint8_t         data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if ((index > 0) && (index <= array_getSize(this->pData)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = *((uint8_t *)array_Ptr(this->pData, index));
        
        return data;
    }
    
    
    uint8_t         u8Array_GetFirst(
        U8ARRAY_DATA	*this
    )
    {
        uint8_t         data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        data = u8Array_Get(this, 1);
        
        return data;
    }
    
    
    uint8_t         u8Array_GetLast(
        U8ARRAY_DATA	*this
    )
    {
        uint8_t         data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = u8Array_Get(this, array_getSize(this->pData));
        
        return data;
    }
    
    
    
    ERESULT         u8Array_GetU8(
        U8ARRAY_DATA	*this,
        uint32_t        index,
        uint8_t         *pValue
    )
    {
        uint8_t         value = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if ((index > 0) && (index <= array_getSize(this->pData)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        value = *((uint8_t *)array_Ptr(this->pData, index));
        
        
        // Return to caller.
        if (pValue) {
            *pValue = value;
        }
        return ERESULT_SUCCESS;
    }
    
    
    //---------------------------------------------------------------
    //                       G e t U 1 6
    //---------------------------------------------------------------
    
    ERESULT         u8Array_GetU16(
        U8ARRAY_DATA	*this,
        uint32_t        index,
        uint16_t        *pValue
    )
    {
        uint8_t         *pData;
        uint16_t        value = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((index > 0) && (index <= (array_getSize(this->pData)+1)))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if ((index + 1) <= array_getSize(this->pData))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pData = array_Ptr(this->pData, index);
        if (NULL == pData) {
            return ERESULT_INVALID_MEMORY_ADDRESS;
        }
        if (obj_Flag(this, U8ARRAY_FLAG_BIGENDIAN)) {
            value |= (*pData++ << 8);
            value = *pData++;
        }
        else {
            value = *pData++;
            value |= (*pData++ << 8);
        }
        if (pValue) {
            *pValue = value;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    //---------------------------------------------------------------
    //                       G e t U 2 4
    //---------------------------------------------------------------
    
    ERESULT         u8Array_GetU24(
        U8ARRAY_DATA	*this,
        uint32_t        index,
        uint32_t        *pValue
    )
    {
        uint8_t         *pData;
        uint32_t        value = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((index > 0) && (index <= (array_getSize(this->pData)+1)))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if ((index + 2) <= array_getSize(this->pData))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pData = array_Ptr(this->pData, index);
        if (NULL == pData) {
            return ERESULT_INVALID_MEMORY_ADDRESS;
        }
        if (obj_Flag(this, U8ARRAY_FLAG_BIGENDIAN)) {
            value |= (*pData++ << 16);
            value |= (*pData++ << 8);
            value = *pData++;
        }
        else {
            value = *pData++;
            value |= (*pData++ << 8);
            value |= (*pData++ << 16);
        }
        if (pValue) {
            *pValue = value;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         u8Array_GetU32(
        U8ARRAY_DATA	*this,
        uint32_t        index,
        uint32_t        *pValue
    )
    {
        uint8_t         *pData;
        uint32_t        value = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((index > 0) && (index <= (array_getSize(this->pData)+1)))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if ((index + 3) <= array_getSize(this->pData))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pData = array_Ptr(this->pData, index);
        if (NULL == pData) {
            return ERESULT_INVALID_MEMORY_ADDRESS;
        }
        if (obj_Flag(this, U8ARRAY_FLAG_BIGENDIAN)) {
            value |= (*pData++ << 24);
            value |= (*pData++ << 16);
            value |= (*pData++ << 8);
            value = *pData++;
        }
        else {
            value = *pData++;
            value |= (*pData++ << 8);
            value |= (*pData++ << 16);
            value |= (*pData++ << 24);
        }
        if (pValue) {
            *pValue = value;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    U8ARRAY_DATA *   u8Array_Init(
        U8ARRAY_DATA       *this
    )
    {
        uint16_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (U8ARRAY_DATA *)obj_Init( this, cbSize, OBJ_IDENT_U8ARRAY );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_U8ARRAY);
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&u8Array_Vtbl);
        
        this->pData = array_New(1);
        if (OBJ_NIL == this->pData) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(sizeof(U8ARRAY_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         u8Array_Insert(
        U8ARRAY_DATA    *this,
        uint32_t        index,
        uint8_t         data
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((index > 0) && (index <= (array_getSize(this->pData)+1)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        eRc = array_InsertData(this->pData, index, 1, &data);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         u8Array_InsertData(
        U8ARRAY_DATA    *this,
        uint32_t        index,
        uint32_t        len,
        const
        uint8_t         *pData
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (index > 0)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if ((len > 0) && (pData))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = array_InsertData(this->pData, index, len, (void *)pData);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                            P u t
    //---------------------------------------------------------------
    
    ERESULT         u8Array_PutU8(
        U8ARRAY_DATA    *this,
        const
        uint32_t        index,
        const
        uint8_t         data
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (index > 0)
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        while (index > array_getSize(this->pData)) {
            eRc = u8Array_AppendData(this, 0);
        }
        
        *((uint8_t *)array_Ptr(this->pData, index)) = data;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         u8Array_PutU16(
        U8ARRAY_DATA    *this,
        const
        uint32_t        index,
        const
        uint16_t        data
    )
    {
        ERESULT         eRc;
        uint8_t         *pChr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (index > 0)
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        while ((index + 1) > array_getSize(this->pData)) {
            eRc = u8Array_AppendData(this, 0);
        }
        
        pChr = (uint8_t *)array_Ptr(this->pData, index);
        if (obj_Flag(this, U8ARRAY_FLAG_BIGENDIAN)) {
            *pChr++ = (data >> 8) & 0xFF;
            *pChr++ = data & 0xFF;
        }
        else {
            *pChr++ = data & 0xFF;
            *pChr++ = (data >> 8) & 0xFF;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         u8Array_PutU24(
        U8ARRAY_DATA    *this,
        const
        uint32_t        index,
        const
        uint32_t        data
    )
    {
        ERESULT         eRc;
        uint8_t         *pChr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (index > 0)
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        while ((index + 2) > array_getSize(this->pData)) {
            eRc = u8Array_AppendData(this, 0);
        }
        
        pChr = (uint8_t *)array_Ptr(this->pData, index);
        if (obj_Flag(this, U8ARRAY_FLAG_BIGENDIAN)) {
            *pChr++ = (data >> 16) & 0xFF;
            *pChr++ = (data >> 8) & 0xFF;
            *pChr++ = data & 0xFF;
        }
        else {
            *pChr++ = data & 0xFF;
            *pChr++ = (data >> 8) & 0xFF;
            *pChr++ = (data >> 16) & 0xFF;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         u8Array_PutU32(
        U8ARRAY_DATA    *this,
        const
        uint32_t        index,
        const
        uint32_t        data
    )
    {
        ERESULT         eRc;
        uint8_t         *pChr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (index > 0)
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        while ((index + 3) > array_getSize(this->pData)) {
            eRc = u8Array_AppendData(this, 0);
        }
        
        pChr = (uint8_t *)array_Ptr(this->pData, index);
        if (obj_Flag(this, U8ARRAY_FLAG_BIGENDIAN)) {
            *pChr++ = (data >> 24) & 0xFF;
            *pChr++ = (data >> 16) & 0xFF;
            *pChr++ = (data >> 8) & 0xFF;
            *pChr++ = data & 0xFF;
        }
        else {
            *pChr++ = data & 0xFF;
            *pChr++ = (data >> 8) & 0xFF;
            *pChr++ = (data >> 16) & 0xFF;
            *pChr++ = (data >> 24) & 0xFF;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     u8Array_ToConstantString(
        U8ARRAY_DATA    *this
    )
    {
        uint32_t        i;
        uint32_t        iMax;
        uint8_t         *pData;
        uint8_t         wchr;
        ASTR_DATA       *pWrkStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pWrkStr = AStr_New();
        if (pWrkStr == OBJ_NIL) {
            return pWrkStr;
        }
        
        iMax = array_getSize(this->pData);
        pData = array_Ptr(this->pData, 1);
        if (iMax) {
            for (i=0; i<iMax; ++i) {
                wchr = *pData++;
                if (ascii_isAsciiW32(wchr) && ascii_isPrintableA(wchr)) {
                    AStr_AppendCharA(pWrkStr, wchr);
                }
                else {
                    switch (wchr) {
                            
                        case 9:
                            AStr_AppendA(pWrkStr, "\\t");
                            break;
                            
                        case 10:
                            AStr_AppendA(pWrkStr, "\\n");
                            break;
                            
                        case 12:
                            AStr_AppendA(pWrkStr, "\\f");
                            break;
                            
                        case 13:
                            AStr_AppendA(pWrkStr, "\\r");
                            break;
                            
                        default:
                            AStr_AppendA(pWrkStr, "\\x");
                            AStr_AppendCharA(pWrkStr, hex_DigitToChrA((wchr >> 4) & 0xF));
                            AStr_AppendCharA(pWrkStr, hex_DigitToChrA(wchr & 0xF));
                            break;
                    }
                }
            }
        }
        
        return pWrkStr;
    }
    
    
    ASTR_DATA *     u8Array_ToDebugString(
        U8ARRAY_DATA    *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
//        int             jMax;
//        uint8_t         *pData;
        ASTR_DATA       *pWrkStr;
        
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
                     "{%p(u8Array) size=%d max=%d data=[\n",
                     this,
                     array_getSize(this->pData),
                     array_getMax(this->pData)
                     );
        AStr_AppendA(pStr, str);

        pWrkStr = array_ToDebugString(this->pData,indent+3);
        if (pWrkStr) {
            AStr_Append(pStr, pWrkStr);
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
        }

#ifdef XYZZY
        jMax = array_getSize(this->pData);
        pData = array_Ptr(this->pData, 1);
        if (jMax) {
            for (j=0; j<(jMax-1); ++j) {
                snprintf( str, sizeof(str), "%d,", *pData++ );
                AStr_AppendA(pStr, str);
            }
            snprintf( str, sizeof(str), "%d", *pData );
            AStr_AppendA(pStr, str);
        }
#endif
        
        j = snprintf( str, sizeof(str), "\n] (u8Array)%p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                  W r i t e  T o  F i l e
    //---------------------------------------------------------------
    
    ERESULT         u8Array_WriteToFile(
        U8ARRAY_DATA    *this,
        PATH_DATA       *pPath
    )
    {
        FILE            *pFile;
        char            *pChr;
        uint32_t        index = 0;
        uint32_t        size;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !path_Validate(pPath) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef XYZZY
        pFile = fopen(path_getData(pPath), "r");
        if (NULL == pFile) {
            return ERESULT_FILE_NOT_FOUND;
        }
        while ( (chr = fgetc(pFile)) != EOF ) {
            u8Array_AppendData(pArray, (chr & 0xFF));
        }
        fclose(pFile);
        pFile = NULL;
#endif
        
        pChr = (char *)array_Ptr(this->pData, 1);
        size = array_getSizeInBytes(this->pData);
        pFile = fopen(path_getData(pPath), "w");
        if (NULL == pFile) {
            return ERESULT_OPEN_ERROR;
        }
        while ( index < size ) {
            fputc(*(pChr+index), pFile);
            ++index;
        }
        fclose(pFile);
        pFile = NULL;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            u8Array_Validate(
        U8ARRAY_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if(this) {
            if ( obj_IsKindOf(this,OBJ_IDENT_U8ARRAY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(U8ARRAY_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


