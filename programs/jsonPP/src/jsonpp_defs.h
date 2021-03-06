// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  JSON Pretty Print (jsonpp) Header
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
                            Global Dictionary Keys
 
 */
 
#define libBaseID       "libBase"       /* Library Directory Base Directory */
#define libDepsID       "libDeps"       /* Library Dependencies */
#define mainID          "main"          /* if program, main routine file name */
#define makeTypeID      "makeType"      /* "d" for debug, "r" for release */
#define namePrefixID    "namePrefix"    /* normally "" or "lib" */
#define nameID          "name"          /* program or library base name */
#define objBaseID       "objBase"       /*  Object Base Directory */
#define osTypeID        "osType"        /* "macosx", "win32" or "win64" */
#define outBaseID       "outBase"       /* Base Directory for output */
#define resultTypeID    "resultType"    /* "pgm" or "lib" */
#define srcBaseID       "srcDir"        /* Source File Base Drive and Directory */
#define srcDepsID       "srcDeps"       /* Source Dependencies */
#define srcFileID       "srcFile"       /* Source JSON File */
#define tmpBaseID       "tmpBase"       /* Temporary File Base Directory */
//#define srcPathID       "srcPath"       /* Source File Full Path */ ???

//#define DICT_OBJ_PREFIX         "obj_prefix"    // ???








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


#ifndef         JSONPP_H
#define         JSONPP_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef enum main_idents_e {
        MAIN_IDENT_BASE=OBJ_IDENT_USER_ENTRIES,
        MAIN_IDENT_DBPRS,
        MAIN_IDENT_DBPRS_CLASS,
        MAIN_IDENT_HDRNODE,
        MAIN_IDENT_HDRNODE_CLASS,
        MAIN_IDENT_GENBASE,
        MAIN_IDENT_GENBASE_CLASS,
        MAIN_IDENT_GENOSX,
        MAIN_IDENT_GENOSX_CLASS,
        MAIN_IDENT_GENWIN,
        MAIN_IDENT_GENWIN_CLASS,
        MAIN_IDENT_LIBNODE,
        MAIN_IDENT_LIBNODE_CLASS,
        MAIN_IDENT_MAIN,
        MAIN_IDENT_MAIN_CLASS,
        MAIN_IDENT_OBJNODE,
        MAIN_IDENT_OBJNODE_CLASS,
        MAIN_IDENT_PGMNODE,
        MAIN_IDENT_PGMNODE_CLASS,
        MAIN_IDENT_RTNNODE,
        MAIN_IDENT_RTNNODE_CLASS,
        MAIN_IDENT_SRCPARSE,
        MAIN_IDENT_SRCPARSE_CLASS,
        MAIN_IDENT_TSTNODE,
        MAIN_IDENT_TSTNODE_CLASS,
    } MAIN_IDENTS;
    

    typedef enum genMake_os_e {
        GENMAKE_OS_UNKNOW=0,
        GENMAKE_OS_MACOSX,
        GENMAKE_OS_MSC32,
        GENMAKE_OS_MSC64,
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

#endif	/* JSONPP_H */

