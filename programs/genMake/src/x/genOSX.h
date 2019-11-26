// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          GENOSX Console Transmit Task (genOSX) Header
//****************************************************************
/*
 * Program
 *			Separate genOSX (genOSX)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate genOSX to run things without complications
 *          of interfering with the main genOSX. A genOSX may be 
 *          called a genOSX on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/18/2018 Generated
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





#include        <Dict.h>
#include        <genMake.h>
#include        <genBase.h>
#include        <AStr.h>
#include        <node.h>
#include        <nodeArray.h>
#include        <nodeHash.h>
#include        <szHash.h>


#ifndef         GENOSX_H
#define         GENOSX_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct genOSX_data_s	GENOSX_DATA;    // Inherits from genBase.

    typedef struct genOSX_vtbl_s	{
        GENBASE_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in genOSX_object.c.
        // Properties:
        // Methods:
    } GENOSX_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to genOSX object if successful, otherwise OBJ_NIL.
     */
    GENOSX_DATA *   genOSX_Alloc(
        void
    );
    
    
    OBJ_ID          genOSX_Class(
        void
    );
    
    
    GENOSX_DATA *   genOSX_New(
        NODEHASH_DATA   *pDict
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NODEHASH_DATA * genOSX_getDict(
        GENOSX_DATA     *this
    );
    
    bool            genOSX_setDict(
        GENOSX_DATA     *this,
        NODEHASH_DATA   *pValue
    );

    
    ERESULT         genOSX_setLibIncludePath(
        GENOSX_DATA     *this,
        PATH_DATA *     (*pLibIncludePath)(
                                    GENOSX_DATA *,
                                    const char *,
                                    const char *,
                                    const char *
                        )
    );
    
    
    ERESULT         genOSX_setLibInstalledPath(
        GENOSX_DATA     *this,
        PATH_DATA *     (*pLibInstalledPath)(
                                            GENOSX_DATA *,
                                            const char *,
                                            const char *,
                                            const char *
                        )
    );
    
    
    ERESULT         genOSX_setLibName(
        GENOSX_DATA     *this,
        ASTR_DATA *     (*pLibName)(
                                  GENOSX_DATA *,
                                  const char *,
                                  const char *
        )
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Generate the Make File writing it to the output file.
     @param     this    GENOSX object pointer
     @param     pNodes  The scanned JSON nodes
     @param     pDict   Dictionary for various substitutions
     @param     pOutput An open FILE in writeable mode
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         genOSX_GenMakefile(
        GENOSX_DATA     *this,
        NODE_DATA       *pNodes,
        SZHASH_DATA     *pDict,
        DATETIME_DATA   *pDateTime,
        TEXTOUT_DATA    *pOutput
    );
    
    
    ASTR_DATA *     genOSX_GenCompileJson(
        GENOSX_DATA     *this,
        const
        char            *pName,             // Object Name
        const
        char            *pSrcDir,           // Default - "SRCDIR"
        const
        char            *pObjDir,           // Default - "OBJDIR"
        const
        char            *pObjVar,           // Default - "OBJS"
        const
        char            *pFlgVar,           // If present, adds another Make Flag
        //                                  // variable in addition to CFLAGS
        //                                  // (Default - none)
        NODEARRAY_DATA  *pSrcDeps,          // Source Dependencies (normally .h files)
        NODEARRAY_DATA  *pObjDeps           // Object Dependencies (ie files to be
                                            // included in the compile statement, file
                                            // extension must match that of pName above)
    );
    
    
    ASTR_DATA *     genOSX_GenCompileObject(
        GENOSX_DATA     *this,
        const
        char            *pName,             // Object Name
        const
        char            *pSrcDir,           // Default - "SRCDIR"
        const
        char            *pObjDir,           // Default - "OBJDIR"
        const
        char            *pObjVar,           // Default - "OBJS"
        const
        char            *pFlgVar,           // If present, adds another Make Flag
        //                                  // variable in addition to CFLAGS
        //                                  // (Default - none)
        NODEARRAY_DATA  *pSrcDeps,          // Source Dependencies (normally .h files)
        NODEARRAY_DATA  *pObjDeps           // Object Dependencies (ie files to be
                                            // included in the compile statement, file
                                            // extension must match that of pName above)
);
    
    
    ASTR_DATA *     genOSX_GenCompileRoutine(
        GENOSX_DATA    *this,
        const
        char            *pName,             // Routine File Name including extension
        const
        char            *pSrcDir,           // Default - "SRCDIR"
        const
        char            *pObjDir,           // Default - "OBJDIR"
        const
        char            *pObjVar,           // Default - "OBJS"
        const
        char            *pFlgVar,           // If present, adds another Make Flag
        //                                  // variable in addition to CFLAGS
        //                                  // (Default - none)
        NODEARRAY_DATA  *pSrcDeps,          // Source Dependencies (normally .h files)
        NODEARRAY_DATA  *pObjDeps,          // Object Dependencies (ie files to be
                                            // included in the compile statement, file
                                            // extension must match that of pName above)
        bool            fCO,                // true == compile only
        bool            fExec
    );
    
    
    ASTR_DATA *     genOSX_GenCompileTest(
        GENOSX_DATA    *this,
        const
        char            *pName,             // Object Name
        const
        char            *pSrcDir,           // Default - "TEST_SRC"
        const
        char            *pObjDir,           // Default - "TEST_OBJ"
        const
        char            *pObjVar,           // Default - "TESTS"
        const
        char            *pFlgVar,           // If present, adds another Make Flag
        //                                  // variable in addition to CFLAGS
        //                                  // (Default - none)
        NODEARRAY_DATA  *pSrcDeps,          // Source Dependencies (normally .h files)
        NODEARRAY_DATA  *pObjDeps           // Object Dependencies (ie files to be
                                            // included in the compile statement, file
                                            // extension must match that of pName above)
    );
    
    
    GENOSX_DATA *   genOSX_Init(
        GENOSX_DATA     *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = genOSX_ToDebugString(this,4);
     @endcode 
     @param     this    GENOSX object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    genOSX_ToDebugString(
        GENOSX_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* GENOSX_H */

