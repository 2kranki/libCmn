// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   srcErrors_internal.h
 *	Generated 12/17/2017 07:12:35
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




#include    <srcErrors.h>
#include    <objArray.h>


#ifndef SRCERRORS_INTERNAL_H
#define	SRCERRORS_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

 #pragma pack(push, 1)
struct srcErrors_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    OBJARRAY_DATA   *pErrors;
    
    void            (*pFatalExit)(OBJ_ID, SRCERRORS_DATA *);
    OBJ_ID          pFatalExitObject;

};
#pragma pack(pop)

    extern
    const
    struct srcErrors_class_data_s  srcErrors_ClassObj;

    extern
    const
    SRCERRORS_VTBL         srcErrors_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool        srcErrors_setErrors(
        SRCERRORS_DATA  *this,
        OBJARRAY_DATA   *pValue
    );
    
    
   bool            srcErrors_setLastError(
        SRCERRORS_DATA     *this,
        ERESULT         value
    );


    OBJ_IUNKNOWN *  srcErrors_getSuperVtbl(
        SRCERRORS_DATA     *this
    );


    void            srcErrors_Dealloc(
        OBJ_ID          objId
    );


    void *          srcErrors_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     srcErrors_ToJSON(
        SRCERRORS_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			srcErrors_Validate(
        SRCERRORS_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SRCERRORS_INTERNAL_H */

