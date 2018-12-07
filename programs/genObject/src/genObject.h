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
#include        <appl.h>
#include        <AStr.h>
#include        <dateTime.h>
#include        <path.h>


#ifndef         GENOBJECT_H
#define         GENOBJECT_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef enum obj_genObject_idents_e {
        OBJ_GENOBJECT_IDENT_BASE=OBJ_IDENT_USER_ENTRIES,
        OBJ_IDENT_DBPRS,
        OBJ_IDENT_DBPRS_CLASS,
        OBJ_IDENT_GENBASE,
        OBJ_IDENT_GENBASE_CLASS,
        //OBJ_IDENT_MAIN,               // Defined in cmn_defs
        //OBJ_IDENT_MAIN_CLASS
        OBJ_IDENT_PROPERTY,
        OBJ_IDENT_PROPERTY_CLASS,
    } OBJ_GENOBJECT_IDENTS;
    

    typedef enum genObject_os_e {
        GENOBJECT_OS_UNKNOW=0,
        GENOBJECT_OS_MACOSX,
        GENOBJECT_OS_MSC32,
        GENOBJECT_OS_MSC64,
        GENOBJECT_OS_PIC32
    } GENOBJECT_OS;
    
    typedef enum genObject_type_e {
        GENOBJECT_TYPE_UNKNOW=0,
        GENOBJECT_TYPE_LIB,
        GENOBJECT_TYPE_PGM
    } GENOBJECT_TYPE;


    
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

#endif	/* GENOBJECT_H */

