// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   CmdUtl_internal.h
 *	Generated 01/31/2020 13:17:41
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




#include        <CmdUtl.h>
#include        <JsonIn.h>
#include        <Node_internal.h>
#include        <NodeArray.h>
#include        <NodeHash.h>
#include        <NodeTree.h>
#include        <Path.h>
#include        <SrcFile.h>
#include        <stdio.h>
#include        <wchar.h>


#ifndef CMDUTL_INTERNAL_H
#define	CMDUTL_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct CmdUtl_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
    CMDUTL_OPTION   *pOptions;

    // Common Data
    PATH_DATA       *pPath;             // Program Path
    char            **ppArgV;
    char            *pOptArg;
    W32CHR_T        optopt;
    char            errmsg[64];
    int             subopt;
    int             optIndex;

    // ArgC/ArgV Stuff
    ASTRARRAY_DATA  *pSavedArgs;
    OBJ_ID          pObj;
    void            (*pFatalError)(
        const
        char            *fmt,
        ...
    );

    // Program Arguments and Options
    uint16_t        cOptions;
    char            fPermute;
    uint8_t         rsvd8_1;
    uint32_t        nextArg;
    CMDUTL_OPTION   *pOptDefns;

};
#pragma pack(pop)

    extern
    struct CmdUtl_class_data_s  CmdUtl_ClassObj;

    extern
    const
    CMDUTL_VTBL         CmdUtl_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  CMDUTL_SINGLETON
    CMDUTL_DATA *   CmdUtl_getSingleton (
        void
    );

    bool            CmdUtl_setSingleton (
     CMDUTL_DATA        *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            CmdUtl_setArgV (
        CMDUTL_DATA     *this,
        ASTRARRAY_DATA  *pValue
    );


    OBJ_IUNKNOWN *  CmdUtl_getSuperVtbl (
        CMDUTL_DATA     *this
    );


    ERESULT         CmdUtl_AppendCharToField (
        CMDUTL_DATA     *cbp,
        W32CHR_T        chr
    );


    int             CmdUtl_Argtype (
        const
        char            *optstring,
        char            c
    );


    ERESULT         CmdUtl_Assign (
        CMDUTL_DATA    *this,
        CMDUTL_DATA    *pOther
    );


    CMDUTL_DATA *   CmdUtl_Copy (
        CMDUTL_DATA     *this
    );


    int             CmdUtl_CreateErrorMsg (
        CMDUTL_DATA     *this,
        const
        char            *pMsg,
        const
        char            *pData
    );


    void            CmdUtl_Dealloc (
        OBJ_ID          objId
    );


    int             CmdUtl_IsDashDash(
        const
        char            *arg
    );


    int             CmdUtl_IsLongOpt(
        const
        char            *arg
    );


    int             CmdUtl_IsShortOpt(
        const
        char            *arg
    );


    char *          CmdUtl_LongOptsArg(
        char            *option
    );


    bool            CmdUtl_LongOptsEnd(
        const
        CMDUTL_OPTION   *pOptions,
        int             i
    );


    int             CmdUtl_LongOptsFallback(
        CMDUTL_DATA     *this,
        const
        CMDUTL_OPTION   *pOptions,
        int             *pLongIndex
    );


    int             CmdUtl_LongOptsMatch(
        const
        char            *pLongName,
        const
        char            *option
    );


    bool            CmdUtl_OptstringFromLongOptions(
        const
        CMDUTL_OPTION   *pOptions,
        int             len,
        char            *pOptstring
    );


    int             CmdUtl_Parse(
        CMDUTL_DATA     *this,
        const
        char            *optstring
    );


#ifdef  CMDUTL_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    CMDUTL_DATA *   CmdUtl_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         CmdUtl_ParseJsonFields (
        JSONIN_DATA     *pParser,
        CMDUTL_DATA     *pObject
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         CmdUtl_ToJsonFields (
        CMDUTL_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif


    int             CmdUtl_ParseLong(
        CMDUTL_DATA     *this,
        CMDUTL_OPTION   *pOptions,
        int             *longindex
    );


    void            CmdUtl_Permute(
        CMDUTL_DATA     *this,
        int             index
    );


    void *          CmdUtl_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  CMDUTL_JSON_SUPPORT
    ASTR_DATA *     CmdUtl_ToJson (
        CMDUTL_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			CmdUtl_Validate (
        CMDUTL_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* CMDUTL_INTERNAL_H */

