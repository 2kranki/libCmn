// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Program Dictionary (Dict) Header
//****************************************************************
/*
 * Program
 *			Program Dictionary (Dict)
 * Purpose
 *			This object provides a Dictionary of Data needed for the
 *          generation process.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/23/2019 Generated
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





#include        <genMake.h>
#include        <AStr.h>


#ifndef         DICT_H
#define         DICT_H


//#define   DICT_SINGLETON    1


/*
                            Global Dictionary Keys
 
 */
 
#define libBaseID       "libBase"       /* Library Directory Base Directory */
//#define libDepsID       "libDeps"       /* Library Dependencies */
#define mainID          "main"          /* if program, main routine file name */
#define makeTypeID      "makeType"      /* "d" for debug, "r" for release */
//#define namePrefixID    "namePrefix"    /* normally "" or "lib" */
//#define nameID          "name"          /* program or library base name */
#define objDirVarID     "objDirVar"     /*  Object Base Directory */
#define objsVarID       "objsVar"        /*  Object Output Accum Variable Name */
#define osArchID        "osArch"        /* "x86", "x86_64" */
#define osTypeID        "osType"        /* "macos32", "macos64", "win32" or "win64" */
#define pgmBaseID       "pgmBase"       /* Program output Base Directory */
#define resultTypeID    "resultType"    /* "pgm" or "lib" */
#define srcDirID        "srcDir"        /* Source File Base Drive and Directory */
#define srcDirVarID     "srcDirVar"        /* Makefile Source File Directory Variable */
//#define srcDepsID       "srcDeps"       /* Source Dependencies */
#define srcFileID       "srcFile"       /* Source JSON File Path*/
#define tmpDirID        "tmpDir"        /* Temporary File Base Directory */
#define tstBinVarID     "tstBinVar"     /* Test Binary Output Directory */
#define tstSrcID        "tstSrc"        /* Test Source Directory */
#define tstSrcVarID     "tstSrcVar"     /* Test Source Directory */
#define testsVarID      "testsVar"      /* Test Output Accum Variable Name */







#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Dict_data_s	DICT_DATA;            // Inherits from OBJ
    typedef struct Dict_class_data_s DICT_CLASS_DATA;   // Inherits from OBJ

    typedef struct Dict_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Dict_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DICT_DATA *);
    } DICT_VTBL;

    typedef struct Dict_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Dict_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DICT_DATA *);
    } DICT_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  DICT_SINGLETON
    DICT_DATA *     Dict_Shared (
        void
    );

    bool            Dict_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Dict object if successful, otherwise OBJ_NIL.
     */
    DICT_DATA *     Dict_Alloc (
        void
    );
    
    
    OBJ_ID          Dict_Class (
        void
    );
    
    
    DICT_DATA *     Dict_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NODEHASH_DATA * Dict_getNodeHash (
        DICT_DATA     *this
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         Dict_Add(
        DICT_DATA       *this,
        const
        char            *pName,
        OBJ_ID          pData
    );


    ERESULT         Dict_AddA(
        DICT_DATA       *this,
        const
        char            *pName,
        const
        char            *pData
    );


    ERESULT         Dict_AddUpdate(
        DICT_DATA       *this,
        const
        char            *pName,
        OBJ_ID          pData
    );


    ERESULT         Dict_AddUpdateA(
        DICT_DATA       *this,
        const
        char            *pName,
        const
        char            *pData
    );


    /*!
     Set the default values for the O/S which this is compiled on.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Dict_Defaults (
        DICT_DATA        *this
    );


    /*!
     Substitute environment variables into the current string using a BASH-like
     syntax.  Variable names should have the syntax of:
     '$' '{'[a-zA-Z_][a-zA-Z0-9_]* '}'.
     Substitutions are not rescanned after insertion.
     @param     this    object pointer
     @param     pStr    String to be expanded in-place
     @return    ERESULT_SUCCESS if successful.  Otherwise, an ERESULT_* error code
     is returned.
     */
    ERESULT         Dict_Expand(
        DICT_DATA       *this,
        ASTR_DATA       *pStr
    );

   
    /*!
     Get the dictionary value for a given name.
     @param     this    object pointer
     @param     pNameA  pointer to UTF-8 Name string
     @return    if successful, pointer to data string.  Otherwise, NULL.
     */
    const
    char *          Dict_GetA (
        DICT_DATA       *this,
        const
        char            *pNameA
    );


    DICT_DATA *     Dict_Init (
        DICT_DATA       *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Dict_ToDebugString(this,4);
     @endcode 
     @param     this    DICT object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Dict_ToDebugString (
        DICT_DATA       *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DICT_H */

