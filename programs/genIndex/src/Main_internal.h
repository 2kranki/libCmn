// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Main_internal.h
 *  Generated 10/31/2021 16:52:50
 *
 * Notes:
 *  --  N/A
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




#include        <Main.h>
#include        <Appl_internal.h>
#ifdef  MAIN_USE_DICT
#include        <dict.h>
#endif
#include        <Exec_internal.h>
#include        <JsonIn.h>


#ifndef MAIN_INTERNAL_H
#define MAIN_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Main_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    APPL_DATA       super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pName;
    ASTR_DATA       *pPrefix;
    ASTR_DATA       *pStart;
    ASTR_DATA       *pStr;
#ifdef  MAIN_USE_DICT
    DICT_DATA       *pDict;
#endif

};
#pragma pack(pop)

    extern
    struct Main_class_data_s  Main_ClassObj;

    extern
    const
    MAIN_VTBL         Main_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  MAIN_SINGLETON
    MAIN_DATA *     Main_getSingleton (
        void
    );

    bool            Main_setSingleton (
     MAIN_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    APPL_DATA *     Main_getAppl (
        MAIN_DATA       *this
    );


    OBJ_IUNKNOWN *  Main_getSuperVtbl (
        MAIN_DATA       *this
    );


    ERESULT         Main_Assign (
        MAIN_DATA       *this,
        MAIN_DATA       *pOther
    );


    PATH_DATA *     Main_CheckInputPath (
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    );

    
    MAIN_DATA *     Main_Copy (
        MAIN_DATA       *this
    );


    void            Main_Dealloc (
        OBJ_ID          objId
    );


    MAIN_DATA *     Main_DeepCopy (
        MAIN_DATA       *this
    );


    ERESULT         Main_ParseArgsDefault (
        MAIN_DATA        *this
    );


    int             Main_ParseArgsLong (
        MAIN_DATA       *this,
        int             *pArgC,
        const
        char            ***pppArgV
    );


    int             Main_ParseArgsShort (
        MAIN_DATA       *this,
        int             *pArgC,
        const
        char            ***pppArgV
    );


#ifdef  MAIN_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    MAIN_DATA *     Main_ParseJsonObject (
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
    ERESULT         Main_ParseJsonFields (
        JSONIN_DATA     *pParser,
        MAIN_DATA       *pObject
    );
#endif


    /*!
     Process each command line argument, parsing the HJSON file and
     generating the Makefile.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         Main_ProcessArg (
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    );


    void *          Main_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ERESULT         Main_SetupFromArgV (
        MAIN_DATA       *this,
        uint16_t        cArgs,
        char            *ppArgV[],
        char            **ppEnv
    );


#ifdef  MAIN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Main_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Main_ToJson (
        MAIN_DATA      *this
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
    ERESULT         Main_ToJsonFields (
        MAIN_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif


    ERESULT         Main_UsageDesc (
        MAIN_DATA       *this,
        FILE            *pOutput,
        PATH_DATA       *pProgramPath
    );


    ERESULT         Main_UsageProgLine (
        MAIN_DATA       *this,
        FILE            *pOutput,
        PATH_DATA       *pProgramPath,
        const
        char            *pNameA
    );


    ERESULT         Main_UsageOptions (
        MAIN_DATA       *this,
        FILE            *pOutput
    );


#ifdef NDEBUG
#else
    bool            Main_Validate (
        MAIN_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* MAIN_INTERNAL_H */

