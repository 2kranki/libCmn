// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Main_internal.h
 *	Generated 07/17/2017 14:59:49
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




#include        <Main.h>
#include        <Appl_internal.h>
#include        <ExpandNodes.h>
#include        <NodeHash.h>
#include        <SrcParse.h>


#ifndef MAIN_INTERNAL_H
#define	MAIN_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct Main_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    APPL_DATA       super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        osType;         // See OSTYPE
    uint16_t        outType;        // See OUTTYPE
    uint16_t        fBackup;        // true == backup output file if it exists
    uint16_t        rsvd16;
    DICT_DATA       *pDict;
    OBJ_ID          pGen;
    PATH_DATA       *pFilePath;
    PATH_DATA       *pOutputPath;
    TEXTOUT_DATA    *pOutput;
    NODEARRAY_DATA  *pRtns;         // All RtnA's including disabled ones
    NODEARRAY_DATA  *pTests;        // All TstA's including disabled ones.
    NODE_DATA       *pNodes;
    ASTR_DATA       *pOut;
    SRCPARSE_DATA   *pParser;
    EXPANDNODES_DATA *pExpand;
    const
    char            *pOsName;
    const
    char            *pOsArch;

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
    MAIN_DATA *     Main_getSingleton(
        void
    );
    
    bool            Main_setSingleton(
        MAIN_DATA       *pValue
    );
#endif
    
    
    void *          MainClass_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
    

    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------
    
  
    PATH_DATA *     Main_CheckInputPath (
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    );

    PATH_DATA *     Main_CreateOutputPath (
        MAIN_DATA       *this,
        ASTR_DATA       *pStr,
        const
        char            *pOsNameA
    );

    void            Main_Dealloc (
        OBJ_ID          objId
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
    
    /*!
     Parse the given file into a JSON Node structure and
     perform some cursory checks on the structure.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         Main_ParseInputFile (
        MAIN_DATA       *this,
        PATH_DATA       *pPath
    );
    
    /*!
     Parse the given string into a JSON Node structure and
     perform some cursory checks on the structure.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         Main_ParseInputStr (
        MAIN_DATA       *this,
        const
        char            *pStr
    );
    
    ERESULT         Main_ProcessInit (
        MAIN_DATA       *this
    );
    
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


    ERESULT         Main_SetupOsArch (
        MAIN_DATA        *this
    );


    ERESULT         Main_SetupTextOutAStr (
        MAIN_DATA        *this
    );


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
    bool			Main_Validate (
        MAIN_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_INTERNAL_H */

