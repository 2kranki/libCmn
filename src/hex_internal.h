// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   hex_internal.h
 *	Generated 10/08/2016 09:17:56
 *
 * Notes:
 *  --	N/A
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



#include    <hex.h>
#include    <jsonIn.h>


#ifndef HEX_INTERNAL_H
#define	HEX_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct hex_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    uint32_t        *pLen;              // Remaining length of buffer
    //                                  // (Decremented if char added)
    char            **ppBuffer;         // Ascii representation of digit stored
    //                                  // at ptr and ptr is advanced

};
#pragma pack(pop)

    extern
    const
    struct hex_class_data_s  hex_ClassObj;

    extern
    const
    HEX_VTBL         hex_Vtbl;


    // Internal Functions
    void            hex_Dealloc(
        OBJ_ID          objId
    );

    
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new null object if successful, otherwise, OBJ_NIL
     @warning   Returned null object must be released.
     */
    uint8_t *       hex_ParseObject(
        JSONIN_DATA     *pParser,
        uint32_t        *pLength
    );
    
    
    uint32_t        hex_putBytes16Obj(
        HEX_DATA        *this,
        bool            f64,
        uint64_t        offset,
        uint32_t        cData,
        const
        void            *pData,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    );

    
    bool            hex_putChar(
        HEX_DATA        *this,
        uint8_t         data
    );


    void *          hex_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
#ifdef NDEBUG
#else
    bool			hex_Validate(
        HEX_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* HEX_INTERNAL_H */

