// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Compiler_internal.h
 *	Generated 01/04/2020 23:19:02
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




#include        <Compiler.h>
#include        <JsonIn.h>
#include        <ObjArray.h>
#include        <node.h>


#ifndef COMPILER_INTERNAL_H
#define	COMPILER_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Compiler_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    SRCERRORS_DATA  *pErrors;
    OBJ_ID          pListing;
    PATH_DATA       *pInputPath;
    PATH_DATA       *pOutputDir;
    PATH_DATA       *pTempDir;
    ASTR_DATA       *pProgramName;
    SRCFILES_DATA   *pSourceFiles;
    SZTBL_DATA      *pStringTable;
    OBJ_ID          pFileTable;
    OBJ_ID          pLexer;
    OBJ_ID          pSymbolTable;
    OBJ_ID          pParseTree;
    NODEARRAY_DATA  *pQueue0;
    NODEARRAY_DATA  *pQueue1;
    OBJARRAY_DATA   *pQueue2;
    OBJARRAY_DATA   *pQueue3;
    NODEHASH_DATA   *pProperties;
    uint32_t        numErrors;

};
#pragma pack(pop)

    extern
    struct Compiler_class_data_s  Compiler_ClassObj;

    extern
    const
    COMPILER_VTBL         Compiler_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  COMPILER_SINGLETON
    COMPILER_DATA *     Compiler_getSingleton (
        void
    );

    bool            Compiler_setSingleton (
     COMPILER_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Compiler_getSuperVtbl (
        COMPILER_DATA     *this
    );


    void            Compiler_Dealloc (
        OBJ_ID          objId
    );


#ifdef  COMPILER_JSON_SUPPORT
    COMPILER_DATA *       Compiler_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          Compiler_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     Compiler_ToJson (
        COMPILER_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			Compiler_Validate (
        COMPILER_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* COMPILER_INTERNAL_H */

