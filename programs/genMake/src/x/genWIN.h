// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          GENWIN Console Transmit Task (genWIN) Header
//****************************************************************
/*
 * Program
 *			Separate genWIN (genWIN)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate genWIN to run things without complications
 *          of interfering with the main genWIN. A genWIN may be 
 *          called a genWIN on other O/S's.
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





#include        <genMake.h>
#include        <genBase.h>
#include        <AStr.h>
#include        <node.h>
#include        <nodeArray.h>
#include        <nodeHash.h>
#include        <szHash.h>


#ifndef         GENWIN_H
#define         GENWIN_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct genWIN_data_s	GENWIN_DATA;    // Inherits from GENBASE.

    typedef struct genWIN_vtbl_s	{
        GENBASE_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in genWIN_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GENWIN_DATA *);
    } GENWIN_VTBL;



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
     @return    pointer to genWIN object if successful, otherwise OBJ_NIL.
     */
    GENWIN_DATA *     genWIN_Alloc(
        void
    );
    
    
    OBJ_ID            genWIN_Class(
        void
    );
    
    
    GENWIN_DATA *     genWIN_New(
        NODEHASH_DATA   *pDict
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ASTR_DATA *     genWIN_GenCompileJson(
        GENWIN_DATA     *this,
        const
        char            *pNameA,            // Routine File Name including extension
        const
        char            *pSrcDir,           // Default - "SRCDIR"
        const
        char            *pObjDir,           // Default - "OBJDIR"
        const
        char            *pObjVar,           // Default - "OBJS"
        const
        char            *pFlgVar,
        NODEARRAY_DATA  *pSrcDeps,          // Source Dependencies (normally .h files)
        NODEARRAY_DATA  *pObjDeps           // Object Dependencies (ie files to be
                                            // included in the compile statement, file
                                            // extension must match that of pName above)
    );
    
    
    ASTR_DATA *     genWIN_GenCompileObject(
        GENWIN_DATA     *this,
        const
        char            *pName,             // Object Name
        const
        char            *pSrcDir,           // Default - "SRCDIR"
        const
        char            *pObjDir,           // Default - "OBJDIR"
        const
        char            *pObjVar,           // Default - "OBJS"
        const
        char            *pFlgVar,
        NODEARRAY_DATA  *pSrcDeps,          // Source Dependencies (normally .h files)
        NODEARRAY_DATA  *pObjDeps           // Object Dependencies (ie files to be
                                            // included in the compile statement, file
                                            // extension must match that of pName above)
    );
    
    
    ASTR_DATA *     genWIN_GenCompileRoutine(
        GENWIN_DATA    *this,
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
        // variable in addition to CFLAGS
        // (Default - none)
        NODEARRAY_DATA  *pSrcDeps,          // Source Dependencies (normally .h files)
        NODEARRAY_DATA  *pObjDeps,          // Object Dependencies (ie files to be
        // included in the compile statement, file
        // extension must match that of pName above)
        bool            fCO,                // true == compile only
        bool            fExec               // true == execute the newly compiled
                                            //          program
    );
    
    
    ASTR_DATA *     genWIN_GenCompileTest(
        GENWIN_DATA     *this,
        const
        char            *pNameA,            // Routine File Name including extension
        const
        char            *pSrcDir,           // Default - "SRCDIR"
        const
        char            *pObjDir,           // Default - "OBJDIR"
        const
        char            *pObjVar,           // Default - "OBJS"
        const
        char            *pFlgVar,
        NODEARRAY_DATA  *pSrcDeps,          // Source Dependencies (normally .h files)
        NODEARRAY_DATA  *pObjDeps           // Object Dependencies (ie files to be
                                            // included in the compile statement, file
                                            // extension must match that of pName above)
    );
    
    
    /*!
     Generate the Make File writing it to the output file.
     @param     this    GENWIN object pointer
     @param     pNodes  The scanned JSON nodes
     @param     pDict   Dictionary for various substitutions
     @param     pOutput An open FILE in writeable mode
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         genWIN_GenMakefile(
        GENWIN_DATA     *this,
        NODE_DATA       *pNodes,
        SZHASH_DATA     *pDict,
        DATETIME_DATA   *pDateTime,
        FILE            *pOutput
    );
    
    
    GENWIN_DATA *   genWIN_Init(
        GENWIN_DATA     *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = genWIN_ToDebugString(this,4);
     @endcode 
     @param     this    GENWIN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    genWIN_ToDebugString(
        GENWIN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* GENWIN_H */

