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





#include        <jsonpp_defs.h>
#include        <AStr.h>
#include        <node.h>
#include        <nodeArray.h>
#include        <nodeHash.h>
#include        <path.h>
#include        <szHash.h>
#include        <textOut.h>


#ifndef         MAIN_H
#define         MAIN_H

#define MAIN_SINGLETON  1


#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct main_data_s	MAIN_DATA;    // Inherits from APPL_DATA.

    typedef struct main_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in main_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MAIN_DATA *);
    } MAIN_VTBL;


    typedef enum os_type_e {
        OSTYPE_UNKNOWN=0,
        OSTYPE_MACOS,
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
    MAIN_DATA *     main_Shared(
        void
    );

    void            main_SharedReset(
        void
    );
#endif
    
    
    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to main object if successful, otherwise OBJ_NIL.
     */
    MAIN_DATA *     main_Alloc(
        void
    );
    
    
    MAIN_DATA *     main_New(
        void
    );
    
    MAIN_DATA *     main_NewFromArgV(
        uint16_t        cArgs,
        char            **ppArgs,
        char            **ppEnv
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    APPL_DATA *     main_getAppl(
        MAIN_DATA       *this
    );
    
    
    NODEHASH_DATA * main_getDict(
        MAIN_DATA       *this
    );
    
    
    PATH_DATA *     main_getFilePath(
        MAIN_DATA       *this
    );
    
    bool            main_setFilePath(
        MAIN_DATA       *this,
        PATH_DATA       *pValue
    );
    

    TEXTOUT_DATA *  main_getOutput(
        MAIN_DATA       *this
    );
    
    bool            main_setOutput(
        MAIN_DATA       *this,
        TEXTOUT_DATA    *pValue
    );
    

    PATH_DATA *     main_getOutputPath(
        MAIN_DATA       *this
    );
    
    bool            main_setOutputPath(
        MAIN_DATA       *this,
        PATH_DATA       *pValue
    );
    

    ASTR_DATA *     main_getStr(
        MAIN_DATA       *this
    );
    
    
    int             main_getVerbose(
        MAIN_DATA       *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    int             main_Exec(
        MAIN_DATA		*this
    );

   
    /*!
     Generate the pretty print output given the internal nodes and the dictionary.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         main_GenPP(
        MAIN_DATA       *this
    );
    
    
    MAIN_DATA *     main_Init(
        MAIN_DATA       *this
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
    ERESULT         main_SetupFromArgV(
        MAIN_DATA       *this,
        uint16_t        cArgs,
        char            *ppArgV[],
        char            **ppEnv
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = main_ToDebugString(this,4);
     @endcode
     @param     this    MAIN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    main_ToDebugString(
        MAIN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

