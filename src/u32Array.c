// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   u32Array.c
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
#include    "u32Array_internal.h"
#include    "file.h"
#include    "path.h"
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

    U32ARRAY_DATA * u32Array_Alloc(
    )
    {
        U32ARRAY_DATA   *cbp;
        uint32_t        cbSize = sizeof(U32ARRAY_DATA);
        
        cbp = obj_Alloc( cbSize );
        
        return( cbp );
    }



    U32ARRAY_DATA * u32Array_New(
    )
    {
        U32ARRAY_DATA    *cbp;
        
        cbp = u32Array_Alloc( );
        cbp = u32Array_Init(cbp);
        
        return( cbp );
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    bool            u32Array_setBigEndian(
        U32ARRAY_DATA   *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        obj_FlagSet(this, U32ARRAY_FLAG_BIGENDIAN, value);
        
        return true;
    }
    
    
    
    uint32_t *      u32Array_getData(
        U32ARRAY_DATA   *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !u32Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return pwr2Array_Ptr((PWR2ARRAY_DATA *)cbp, 1);
    }
    
    
    
    uint32_t        u32Array_getSize(
        U32ARRAY_DATA   *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !u32Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return pwr2Array_getSize((PWR2ARRAY_DATA *)cbp);
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         u32Array_AppendData(
        U32ARRAY_DATA	*cbp,
        uint32_t        data
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc =   pwr2Array_InsertData(
                                 (PWR2ARRAY_DATA *)cbp,
                                 pwr2Array_getSize((PWR2ARRAY_DATA *)cbp)+1,
                                 1,
                                 &data
                );
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    ERESULT         u32Array_AppendFile(
        U32ARRAY_DATA	*this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;
        int64_t         size = 0;
        int             chr;
        FILE            *pFile;
        uint32_t        data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = file_SizeA( path_getData(pPath), &size );
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }
        if (0 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        pFile = fopen(path_getData(pPath), "rb");
        if (NULL == pFile) {
            return ERESULT_FILE_NOT_FOUND;
        }
        while ( !feof(pFile) ) {
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, U32ARRAY_FLAG_BIGENDIAN)) {
                data = (chr & 0xFF) << 24;
            }
            else {
                data = chr & 0xFF;
            }
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, U32ARRAY_FLAG_BIGENDIAN)) {
                data |= (chr & 0xFF) << 16;
            }
            else {
                data |= (chr & 0xFF) << 8;
            }
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, U32ARRAY_FLAG_BIGENDIAN)) {
                data = (chr & 0xFF) << 8;
            }
            else {
                data |= (chr & 0xFF) << 16;
            }
            chr = fgetc(pFile);
            if (feof(pFile)) {
                break;
            }
            if (obj_Flag(this, U32ARRAY_FLAG_BIGENDIAN)) {
                data = (chr & 0xFF);
            }
            else {
                data |= (chr & 0xFF) << 24;
            }
            u32Array_AppendData(this, data);
        }
        fclose(pFile);
        pFile = NULL;
        
        // Return to caller.
        return eRc;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                         A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         u32Array_Assign(
        U32ARRAY_DATA	*cbp,
        U32ARRAY_DATA	*pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = pwr2Array_Assign((PWR2ARRAY_DATA *)cbp, (PWR2ARRAY_DATA *)pOther);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                         C o p y
    //---------------------------------------------------------------
    
    U32ARRAY_DATA * u32Array_Copy(
        U32ARRAY_DATA	*cbp
    )
    {
        U32ARRAY_DATA	*pOther;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = u32Array_New();
        if (pOther) {
            eRc = u32Array_Assign(cbp, pOther);
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

    void            u32Array_Dealloc(
        OBJ_ID          objId
    )
    {
        U32ARRAY_DATA   *cbp = objId;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !u32Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        pwr2Array_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    uint32_t         u32Array_Delete(
        U32ARRAY_DATA	*cbp,
        uint32_t        index
    )
    {
        uint32_t        data = 0;
        uint32_t        *pData;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
        if ((index > 0) && (index <= pwr2Array_getSize((PWR2ARRAY_DATA *)cbp)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        pData = pwr2Array_Ptr((PWR2ARRAY_DATA *)cbp, index);
        if (pData) {
            data = *pData;
            eRc = pwr2Array_Delete((PWR2ARRAY_DATA *)cbp, index, 1);
            if (ERESULT_HAS_FAILED(eRc)) {
                return 0;
            }
        }
        
        // Return to caller.
        return data;
    }
    
    
    uint32_t         u32Array_DeleteFirst(
        U32ARRAY_DATA	*cbp
    )
    {
        uint32_t        data = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = u32Array_Delete(cbp,1);
        
        // Return to caller.
        return data;
    }
    
    
    uint32_t         u32Array_DeleteLast(
        U32ARRAY_DATA	*cbp
    )
    {
        uint32_t        data = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = u32Array_Delete(cbp, pwr2Array_getSize((PWR2ARRAY_DATA *)cbp));
        
        // Return to caller.
        return data;
    }
    
    
    
    //---------------------------------------------------------------
    //                         G e t
    //---------------------------------------------------------------
    
    uint32_t         u32Array_Get(
        U32ARRAY_DATA	*cbp,
        uint32_t        index
    )
    {
        uint32_t        data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
        if ((index > 0) && (index <= pwr2Array_getSize((PWR2ARRAY_DATA *)cbp)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = *((uint32_t *)pwr2Array_Ptr((PWR2ARRAY_DATA *)cbp, index));
        
        return data;
    }
    
    
    uint32_t        u32Array_GetFirst(
        U32ARRAY_DATA	*cbp
    )
    {
        uint32_t        data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = u32Array_Get(cbp, 1);
        
        return data;
    }
    
    
    uint32_t         u32Array_GetLast(
        U32ARRAY_DATA	*cbp
    )
    {
        uint32_t        data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        data = u32Array_Get(cbp, pwr2Array_getSize((PWR2ARRAY_DATA *)cbp));
        
        return data;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    U32ARRAY_DATA *   u32Array_Init(
        U32ARRAY_DATA     *this
    )
    {
        uint16_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (U32ARRAY_DATA *)pwr2Array_Init( (PWR2ARRAY_DATA *)this, 2 );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_U32ARRAY);
        this->pSuperVtbl = obj_getVtbl(this);   // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&u32Array_Vtbl);

    #ifdef NDEBUG
    #else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         u32Array_InsertData(
        U32ARRAY_DATA   *cbp,
        uint32_t        index,
        uint32_t        data
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((index > 0) && (index <= pwr2Array_getSize((PWR2ARRAY_DATA *)cbp)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        eRc = pwr2Array_InsertData((PWR2ARRAY_DATA *)cbp, index, 1, &data);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                            S e t
    //---------------------------------------------------------------
    
    ERESULT         u32Array_SetData(
        U32ARRAY_DATA   *cbp,
        uint32_t        index,
        uint32_t        data
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((index > 0) && (index <= pwr2Array_getSize((PWR2ARRAY_DATA *)cbp)))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        *((uint32_t *)pwr2Array_Ptr((PWR2ARRAY_DATA *)cbp, index)) = data;
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     u32Array_ToDebugString(
        U32ARRAY_DATA   *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        int             jMax;
        ASTR_DATA       *pStr;
        uint32_t        *pData;
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(token) size=%d max=%d data=[",
                     cbp,
                     pwr2Array_getSize((PWR2ARRAY_DATA *)cbp),
                     pwr2Array_getMax((PWR2ARRAY_DATA *)cbp)
                     );
        AStr_AppendA(pStr, str);

        jMax = pwr2Array_getSize((PWR2ARRAY_DATA *)cbp);
        pData = pwr2Array_Ptr((PWR2ARRAY_DATA *)cbp, 1);
        if (jMax) {
            for (j=0; j<(jMax-1); ++j) {
                snprintf( str, sizeof(str), "%d,", *pData++ );
                AStr_AppendA(pStr, str);
            }
            snprintf( str, sizeof(str), "%d", *pData );
            AStr_AppendA(pStr, str);
        }
        
        j = snprintf( str, sizeof(str), "] %p}\n", cbp );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            u32Array_Validate(
        U32ARRAY_DATA   *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_U32ARRAY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(U32ARRAY_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                  W r i t e  T o  F i l e
    //---------------------------------------------------------------
    
    ERESULT         u32Array_WriteToFile(
        U32ARRAY_DATA   *this,
        PATH_DATA       *pPath
    )
    {
        FILE            *pFile;
        uint32_t        index = 0;
        uint32_t        size;
        uint32_t        *pData;
        uint32_t        data;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !path_Validate(pPath) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pData = pwr2Array_getData((PWR2ARRAY_DATA *)this);
        size = pwr2Array_getSize((PWR2ARRAY_DATA *)this);
        pFile = fopen(path_getData(pPath), "w");
        if (NULL == pFile) {
            return ERESULT_OPEN_ERROR;
        }
        while ( index < size ) {
            data = pData[index++];
            if (obj_Flag(this, U32ARRAY_FLAG_BIGENDIAN)) {
                fputc(((data >> 24) & 0xFF), pFile);
                fputc(((data >> 16) & 0xFF), pFile);
                fputc(((data >> 8) & 0xFF), pFile);
                fputc((data & 0xFF), pFile);
            }
            else {
                fputc((data & 0xFF), pFile);
                fputc(((data >> 8) & 0xFF), pFile);
                fputc(((data >> 16) & 0xFF), pFile);
                fputc(((data >> 24) & 0xFF), pFile);
            }
        }
        fclose(pFile);
        pFile = NULL;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


