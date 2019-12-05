// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          MAIN Console Transmit Task (main) Header
//****************************************************************
/*
 * Program
 *			Separate main (main)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate main to run things without complications
 *          of interfering with the main main. A main may be 
 *          called a main on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	07/17/2017 Generated
 */

/***
                        Directory Structures
 
 Output:
    library: ${outBase}/${osType}/${libPrefix}${libName}.${'a' or 'lib'}
    include: ${outBase}/${osType}/include/xxx.h
 
    This structure is also assumed for include purposes from the "lib_deps"
    section.
 
 

 
 
 
 
 
 
 ***/




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
#include        <Dict.h>
#include        <ExpandNodes.h>
#include        <fbso.h>
#include        <node.h>
#include        <nodeArray.h>
#include        <path.h>
#include        <SrcParse.h>
#include        <szHash.h>
#include        <TextOut.h>


#ifndef         MAIN_H
#define         MAIN_H

#define MAIN_SINGLETON  1


#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Main_data_s	MAIN_DATA;    // Inherits from APPL_DATA.

    typedef struct Main_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Main_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MAIN_DATA *);
    } MAIN_VTBL;


    typedef enum os_type_e {
        OSTYPE_UNKNOWN=0,
        OSTYPE_MACOS32,
        OSTYPE_MACOS64,
        OSTYPE_MSC32,
        OSTYPE_MSC64
    } OSTYPE;
    
    
    typedef enum out_type_e {
        OUTTYPE_UNKNOW=0,
        OUTTYPE_CLP,                // Command Line Program
        OUTTYPE_LIB                 // Library
    } OUTTYPE;
    
    
    

    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef MAIN_SINGLETON
    MAIN_DATA *     Main_Shared(
        void
    );

    void            Main_SharedReset(
        void
    );
#endif
    
    
    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to main object if successful, otherwise OBJ_NIL.
     */
    MAIN_DATA *     Main_Alloc(
        void
    );
    
    
    MAIN_DATA *     Main_New(
        void
    );
    
    MAIN_DATA *     Main_NewFromArgV(
        uint16_t        cArgs,
        char            **ppArgs,
        char            **ppEnv
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    APPL_DATA *     Main_getAppl(
        MAIN_DATA       *this
    );
    
    
    DICT_DATA *     Main_getDict(
        MAIN_DATA       *this
    );
    
    
    PATH_DATA *     Main_getFilePath(
        MAIN_DATA       *this
    );
    
    bool            Main_setFilePath(
        MAIN_DATA       *this,
        PATH_DATA       *pValue
    );
    

    uint16_t        Main_getOsType(
        MAIN_DATA       *this
    );
    
    bool            Main_setOsType(
        MAIN_DATA       *this,
        uint16_t        value
    );

    
    TEXTOUT_DATA *  Main_getOutput(
        MAIN_DATA       *this
    );
    
    bool            Main_setOutput(
        MAIN_DATA       *this,
        TEXTOUT_DATA    *pValue
    );
    

    PATH_DATA *     Main_getOutputPath(
        MAIN_DATA       *this
    );
    
    bool            Main_setOutputPath(
        MAIN_DATA       *this,
        PATH_DATA       *pValue
    );
    

    uint16_t        Main_getOutType(
        MAIN_DATA       *this
    );
    
    bool            Main_setOutType(
        MAIN_DATA       *this,
        uint16_t        value
    );

    
    SRCPARSE_DATA * Main_getParser(
        MAIN_DATA       *this
    );

    bool            Main_setParser(
        MAIN_DATA       *this,
        SRCPARSE_DATA   *pValue
    );


    NODEARRAY_DATA * Main_getRoutines(
        MAIN_DATA       *this
    );

    bool            Main_setRoutines(
        MAIN_DATA       *this,
        NODEARRAY_DATA  *pValue
    );


    ASTR_DATA *     Main_getStr(
        MAIN_DATA       *this
    );
    
    
    NODEARRAY_DATA * Main_getTests(
        MAIN_DATA       *this
    );

    bool            Main_setTests(
        MAIN_DATA       *this,
        NODEARRAY_DATA  *pValue
    );


    int             Main_getVerbose(
        MAIN_DATA       *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    int             Main_Exec(
        MAIN_DATA		*this
    );

   
    /*!
     Generate a makefile given the internal nodes and the dictionary passed
     from the ParseInput phase.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Main_GenMakefile(
        MAIN_DATA       *this
    );
    
    
    MAIN_DATA *     Main_Init(
        MAIN_DATA       *this
    );


    /*!
     Parse the given input file resetting any prior parse data and
     building the appropriate node tables from the JSON. The parser
     and its tables will be saved internally for later phases of
     the generation process.
     @param     this        object pointer
     @param     pPath       JSON Input File Path
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
                an ERESULT_* error code
     */
    ERESULT         Main_ParseInputFile(
        MAIN_DATA       *this,
        PATH_DATA       *pPath
    );


    /*!
     Set up to parse the given input resetting any prior parse data.
     @param     this        object pointer
     @param     cArgs       number of charater strings in ppArgs
     @param     ppArgV      pointer to a charater string array
     @param     ppEnv       pointer to a charater string array
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
     an ERESULT_* error code
     */
    ERESULT         Main_SetupFromArgV(
        MAIN_DATA       *this,
        uint16_t        cArgs,
        char            *ppArgV[],
        char            **ppEnv
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = Main_ToDebugString(this,4);
     @endcode
     @param     this    MAIN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Main_ToDebugString(
        MAIN_DATA       *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

