// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   main_internal.h
 *	Generated 11/30/2018 16:54:35
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




#include        <main.h>
#include        <appl_internal.h>
#include        <jsonIn.h>
#include        <nodeBTP.h>
#include        <TextOut.h>


#ifndef MAIN_INTERNAL_H
#define	MAIN_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct main_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    APPL_DATA       super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        osType;         // See OSTYPE
    uint16_t        outType;        // See OUTTYPE
    uint16_t        fBackup;        // true == backup output file if it exists
    uint16_t        rsvd16;
    NODEBTP_DATA    *pDict;
    DBPRS_DATA      *pPrs;
    OBJ_ID          pGen;
    PATH_DATA       *pFilePath;
    PATH_DATA       *pOutputPath;
    TEXTOUT_DATA    *pOutput;
    NODE_DATA       *pNodes;
    ASTR_DATA       *pOut;

};
#pragma pack(pop)

    extern
    struct main_class_data_s  main_ClassObj;

    extern
    const
    MAIN_VTBL         main_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  MAIN_SINGLETON
    MAIN_DATA *     main_getSingleton (
        void
    );

    bool            main_setSingleton (
     MAIN_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            main_setParser (
        MAIN_DATA       *this,
        DBPRS_DATA      *pValue
    );
    
    
    OBJ_IUNKNOWN *  main_getSuperVtbl (
        MAIN_DATA     *this
    );


    void            main_Dealloc (
        OBJ_ID          objId
    );


    ERESULT         main_DictAdd(
                                 MAIN_DATA       *this,
                                 const
                                 char            *pName,
                                 OBJ_ID          pData
                                 );
    
    ERESULT         main_DictAddA(
                                  MAIN_DATA       *this,
                                  const
                                  char            *pName,
                                  const
                                  char            *pData
                                  );
    
    ERESULT         main_DictAddUpdate(
                                       MAIN_DATA       *this,
                                       const
                                       char            *pName,
                                       OBJ_ID          pData
                                       );
    
    ERESULT         main_DictAddUpdateA(
                                        MAIN_DATA        *this,
                                        const
                                        char            *pName,
                                        const
                                        char            *pData
                                        );
    
    ERESULT         main_ParseArgsDefault(
                                          MAIN_DATA        *this
                                          );
    
    int             main_ParseArgsLong(
                                       MAIN_DATA       *this,
                                       int             *pArgC,
                                       const
                                       char            ***pppArgV
                                       );
    
    int             main_ParseArgsShort(
                                        MAIN_DATA       *this,
                                        int             *pArgC,
                                        const
                                        char            ***pppArgV
                                        );
    
    ERESULT         main_ParseInputFile(
                                        MAIN_DATA       *this,
                                        PATH_DATA       *pPath
                                        );
    
    ERESULT         main_ParseInputStr(
                                       MAIN_DATA       *this,
                                       const
                                       char            *pStr
                                       );
    
    ERESULT         main_ProcessInit(
                                     MAIN_DATA       *this
                                     );
    
    ERESULT         main_ProcessArg(
                                    MAIN_DATA       *this,
                                    ASTR_DATA       *pStr
                                    );

    
    MAIN_DATA *       main_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          main_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     main_ToJSON (
        MAIN_DATA      *this
    );


    ERESULT         main_UsageDesc(
        MAIN_DATA       *this,
        FILE            *pOutput,
        PATH_DATA       *pProgramPath
    );
    
    
    ERESULT         main_UsageProgLine(
        MAIN_DATA       *this,
        FILE            *pOutput,
        PATH_DATA       *pProgramPath,
        const
        char            *pNameA
    );
    
    
    ERESULT         main_UsageOptions(
        MAIN_DATA       *this,
        FILE            *pOutput
    );
    
    


#ifdef NDEBUG
#else
    bool			main_Validate (
        MAIN_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_INTERNAL_H */

