// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Generate Make (genMake) Header
//****************************************************************
/*
 * Program
 *			Generate Make (genMake) Header
 * Purpose
 *			This header supplies the constants and macros needed
 *			by the Generate Make (genMake) objects.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/10/2018 Generated
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





#include        <cmn_defs.h>
#include        <Appl.h>
#include        <AStr.h>
#include        <DateTime.h>
#include        <Path.h>


#ifndef         GENMAKE_H
#define         GENMAKE_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef enum main_idents_e {
        MAIN_IDENT_BASE=OBJ_IDENT_USER_ENTRIES,
        OBJ_IDENT_DICT,
        OBJ_IDENT_DICT_CLASS,
        OBJ_IDENT_EXPANDNODES,
        OBJ_IDENT_EXPANDNODES_CLASS,
        OBJ_IDENT_GENBASE,
        OBJ_IDENT_GENBASE_CLASS,
        OBJ_IDENT_GENMAC,
        OBJ_IDENT_GENMAC_CLASS,
        OBJ_IDENT_GENWIN,
        OBJ_IDENT_GENWIN_CLASS,
        OBJ_IDENT_NODEBASE,
        OBJ_IDENT_NODEBASE_CLASS,
        OBJ_IDENT_NODEHDR,
        OBJ_IDENT_NODEHDR_CLASS,
        OBJ_IDENT_NODELIB,
        OBJ_IDENT_NODELIB_CLASS,
        OBJ_IDENT_NODEOBJ,
        OBJ_IDENT_NODEOBJ_CLASS,
        OBJ_IDENT_NODEPGM,
        OBJ_IDENT_NODEPGM_CLASS,
        OBJ_IDENT_NODERTN,
        OBJ_IDENT_NODERTN_CLASS,
        OBJ_IDENT_NODERTNA,
        OBJ_IDENT_NODERTNA_CLASS,
        OBJ_IDENT_NODETEST,
        OBJ_IDENT_NODETEST_CLASS,
        OBJ_IDENT_NODETSTA,
        OBJ_IDENT_NODETSTA_CLASS,
        OBJ_IDENT_SRCPARSE,
        OBJ_IDENT_SRCPARSE_CLASS,
        OBJ_IDENT_SRCREF,
        OBJ_IDENT_SRCREF_CLASS,
    } MAIN_IDENTS;
    

    typedef enum genMake_os_e {
        GENMAKE_OS_UNKNOW=0,
        GENMAKE_OS_MACOS32,
        GENMAKE_OS_MACOS64,
        GENMAKE_OS_WIN32,
        GENMAKE_OS_WIN64,
        GENMAKE_OS_PIC32
    } GENMAKE_OS;
    
    typedef enum genMake_type_e {
        GENMAKE_TYPE_UNKNOW=0,
        GENMAKE_TYPE_LIB,
        GENMAKE_TYPE_PGM
    } GENMAKE_TYPE;


    
#ifdef XYZZY
    typedef struct exec_data_s	EXEC_DATA;    // Inherits from OBJ.

    typedef struct exec_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in exec_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(EXEC_DATA *);
    } EXEC_VTBL;
#endif



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* GENMAKE_H */

