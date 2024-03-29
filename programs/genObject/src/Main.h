// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Main (Main) Header
//****************************************************************
/*
 * Program
 *			Main (Main)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate Main to run things without complications
 *          of interfering with the main Main. A Main may be 
 *          called a Main on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/28/2020 Generated
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





#include        <genObject_defs.h>
#include        <AStr.h>
#include        <Dict.h>
#include        <Gen.h>
#include        <NodeClass.h>


#ifndef         MAIN_H
#define         MAIN_H


//#define   MAIN_IS_IMMUTABLE     1
//#define   MAIN_JSON_SUPPORT     1
#define   MAIN_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Main_data_s	MAIN_DATA;            // Inherits from OBJ
    typedef struct Main_class_data_s MAIN_CLASS_DATA;   // Inherits from OBJ

    typedef struct Main_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Main_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MAIN_DATA *);
    } MAIN_VTBL;

    typedef struct Main_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Main_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MAIN_DATA *);
    } MAIN_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  MAIN_SINGLETON
    MAIN_DATA *     Main_Shared (
        void
    );

    void            Main_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Main object if successful, otherwise OBJ_NIL.
     */
    MAIN_DATA *     Main_Alloc (
        void
    );
    
    
    OBJ_ID          Main_Class (
        void
    );
    
    
    MAIN_DATA *     Main_New (
        void
    );
    
    
#ifdef  MAIN_JSON_SUPPORT
    MAIN_DATA *   Main_NewFromJsonString (
        ASTR_DATA       *pString
    );

    MAIN_DATA *   Main_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    GEN_DATA *      Main_getGen (
        MAIN_DATA       *this
    );


    APPL_DATA *     Main_getSuper (
        MAIN_DATA       *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    int             Main_Exec(
        MAIN_DATA       *this
    );


    MAIN_DATA *     Main_Init (
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
        MAIN_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Main_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Main_ToDebugString (
        MAIN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

