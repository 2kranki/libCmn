// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   cloprs_internal.h
 *	Generated 08/22/2018 12:43:41
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




#include        <cloprs.h>
#include        <jsonIn.h>


#ifndef CLOPRS_INTERNAL_H
#define	CLOPRS_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct cloprs_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        reserved;
    ASTR_DATA       *pStr;

    // Program Arguments and Options
    uint16_t        cOptions;
    uint16_t        rsvd16_2;
    ASTRARRAY_DATA  *pArgs;
    ASTRARRAY_DATA  *pEnv;
    uint16_t        cProgramArgs;
    uint16_t        cGroupArgs;
    uint32_t        nextArg;
    PATH_DATA       *pProgramPath;
    CLO_OPTION      *pProgramArgs;
    CLO_OPTION      *pGroupArgs;
    
    OBJ_ID          pObjPrs;
    /*!
     Set the defaults for the program options.
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
                an ERESULT_* error code
     */
    ERESULT         (*pParseProgramDefaults)(OBJ_ID);
    /*!
     Set the defaults for the group options.
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
                an ERESULT_* error code
     */
    ERESULT         (*pParseGroupDefaults)(OBJ_ID);
    ERESULT         (*pParseError)(OBJ_ID, ASTR_DATA *);
    
};
#pragma pack(pop)

    extern
    const
    struct cloprs_class_data_s  cloprs_ClassObj;

    extern
    const
    CLOPRS_VTBL         cloprs_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  cloprs_getSuperVtbl(
        CLOPRS_DATA     *this
    );


    void            cloprs_Dealloc(
        OBJ_ID          objId
    );


    ERESULT         cloprs_ParseArgsLong(
        CLOPRS_DATA     *this,
        bool            fTrue,
        ASTR_DATA       *pArg
    );
    
    
    ERESULT         cloprs_ParseArgsShort(
        CLOPRS_DATA     *this,
        int             *pArgC,
        const
        char            ***pppArgV
    );
    
    
    CLOPRS_DATA *       cloprs_ParseObject(
        JSONIN_DATA     *pParser
    );


    void *          cloprs_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     cloprs_ToJSON(
        CLOPRS_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			cloprs_Validate(
        CLOPRS_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* CLOPRS_INTERNAL_H */

