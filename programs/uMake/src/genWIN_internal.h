// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   genWIN_internal.h
 *	Generated 04/18/2018 09:07:15
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




#include    <genWIN.h>


#ifndef GENWIN_INTERNAL_H
#define	GENWIN_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct genWIN_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    uint16_t        size;		    // maximum number of elements
    uint16_t        reserved;
    SZHASH_DATA     *pDict;
    ASTR_DATA       *pStr;
    FILE            *pOutput;       // (Not owned)

    PATH_DATA *     (*pLibIncludePath)(GENWIN_DATA *, const char *, const char *, const char *);
    PATH_DATA *     (*pLibInstalledPath)(GENWIN_DATA *, const char *, const char *, const char *);
    ASTR_DATA *     (*pLibName)(GENWIN_DATA *, const char *, const char *);
    PATH_DATA *     (*pLibObjectPath)(GENWIN_DATA *, const char *, const char *, const char *);
    
};
#pragma pack(pop)

    extern
    const
    struct genWIN_class_data_s  genWIN_ClassObj;

    extern
    const
    GENWIN_VTBL             genWIN_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

   bool            genWIN_setLastError(
        GENWIN_DATA     *this,
        ERESULT         value
    );


    OBJ_IUNKNOWN *  genWIN_getSuperVtbl(
        GENWIN_DATA     *this
    );


    void            genWIN_Dealloc(
        OBJ_ID          objId
    );


    void *          genWIN_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     genWIN_ToJSON(
        GENWIN_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			genWIN_Validate(
        GENWIN_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* GENWIN_INTERNAL_H */

