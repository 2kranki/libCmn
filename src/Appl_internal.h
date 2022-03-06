// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Appl_internal.h
 *	Generated 01/31/2020 13:16:48
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




#include        <Appl.h>
#include        <AStrCArray.h>
#include        <JsonIn.h>
#include        <Log.h>
#include        <NodeHash.h>


#ifndef APPL_INTERNAL_H
#define	APPL_INTERNAL_H




#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Appl_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    DATETIME_DATA   *pDateTime;
    NODEHASH_DATA   *pProperties;

    // Program Arguments and Options
    int32_t         exitRC;         // Exit Return Code
    uint16_t        fDebug;
    uint16_t        fForce;
    uint16_t        fQuiet;
    uint16_t        iVerbose;
    CMDUTL_DATA     *pCmd;
    ASTRARRAY_DATA  *pArgs;
    ASTRARRAY_DATA  *pEnv;
    PATH_DATA       *pProgramPath;
    CMDUTL_OPTION   *pPgmOptDefns;
    LOG_DATA        *pLog;

    OBJ_ID          pObjPrs;
    ERESULT         (*pParseArgsDefaults)(OBJ_ID);
    /*!
     @return    If successful, ERESULT_SUCCESS_0, ERESULT_SUCCESS_1,
                ERESULT_SUCCESS_2 or ERESULT_SUCCESS_3 to denote how
                many parameters were used beyond the normal 1.  Otherwise,
                an ERESULT_* error code
     */
    ERESULT         (*pParseArgsLong)(
                            OBJ_ID          this,
                            bool            fTrue,
                            ASTR_DATA       *pName,
                            ASTR_DATA       *pWrk,
                            uint32_t        index,
                            ASTRARRAY_DATA  *pArgs
                    );
    ERESULT         (*pParseArgsShort)(OBJ_ID, int *, const char ***);
    ERESULT         (*pParseArgsError)(OBJ_ID, int *, const char ***);

    // 
    OBJ_ID          pObjProcess;
    int             (*pProcess)(OBJ_ID);
    ERESULT         (*pProcessInit)(OBJ_ID);
    ERESULT         (*pProcessArg)(OBJ_ID, ASTR_DATA *);
    ERESULT         (*pProcessTerm)(OBJ_ID); 

    OBJ_ID          pObjUsage;
    ERESULT         (*pUsageProgLine)(OBJ_ID, FILE *, PATH_DATA *, const char *);
    ERESULT         (*pUsageDesc)(OBJ_ID, FILE *, PATH_DATA *);
    ERESULT         (*pUsageOptions)(OBJ_ID, FILE *);


};
#pragma pack(pop)

    extern
    struct Appl_class_data_s  Appl_ClassObj;

    extern
    const
    APPL_VTBL         Appl_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  APPL_SINGLETON
    APPL_DATA * Appl_getSingleton (
        void
    );

    bool        Appl_setSingleton (
     APPL_DATA          *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            Appl_setCmd(
        APPL_DATA       *this,
        CMDUTL_DATA     *pValue
    );


    bool            Appl_setDebug(
        APPL_DATA       *this,
        bool            fValue
    );


    bool            Appl_setParseArgsDefaults(
        APPL_DATA       *this,
        ERESULT         (*pValue)(OBJ_ID)
    );


    bool            Appl_setParseArgsKeywords(
        APPL_DATA       *this,
        void            (*pValue)(OBJ_ID, const char *)
    );


    OBJ_IUNKNOWN * Appl_getSuperVtbl (
        APPL_DATA       *this
    );


    ERESULT         Appl_Assign (
        APPL_DATA       *this,
        APPL_DATA       *pOther
    );


    ASTR_DATA *     Appl_ConstructProgramLine(
        int             cArgs,
        const
        char            **ppArgs
    );


    APPL_DATA *     Appl_Copy (
        APPL_DATA       *this
    );


    void            Appl_Dealloc (
        OBJ_ID          objId
    );


    ERESULT         Appl_Help(
        APPL_DATA       *this,
        ASTR_DATA       *pStr
    );


    ERESULT         Appl_ParseArgsLong(
        APPL_DATA       *this,
        bool            fTrue,
        ASTR_DATA       *pArg
    );


    ERESULT         Appl_ParseArgsShort(
        APPL_DATA       *this,
        int             *pArgC,
        const
        char            ***pppArgV
    );


#ifdef  APPL_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    APPL_DATA *     Appl_ParseJsonObject (
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
    ERESULT         Appl_ParseJsonFields (
        JSONIN_DATA     *pParser,
        APPL_DATA       *pObject
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
    ERESULT         Appl_ToJsonFields (
        APPL_DATA       *this,
        ASTR_DATA       *pStr
    );
#endif


    int             Appl_Process(
        APPL_DATA       *this
    );


    void *          Appl_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  APPL_JSON_SUPPORT
    ASTR_DATA *     Appl_ToJson (
        APPL_DATA       *this
    );
#endif


    void            Appl_UsageArg(
        APPL_DATA       *this,
        ASTR_DATA       *pStr,              // in-out
        CMDUTL_OPTION   *pOption
    );


    void            Appl_UsageNoMsg(
        APPL_DATA       *this
    );


#ifdef NDEBUG
#else
    bool			Appl_Validate (
        APPL_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* APPL_INTERNAL_H */

