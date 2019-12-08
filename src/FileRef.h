// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          FILEREF Console Transmit Task (FileRef) Header
//****************************************************************
/*
 * Program
 *			Separate FileRef (FileRef)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate FileRef to run things without complications
 *          of interfering with the main FileRef. A FileRef may be 
 *          called a FileRef on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/06/2019 Generated
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
#include        <AStr.h>
#include        <AStrC.h>


#ifndef         FILEREF_H
#define         FILEREF_H


//#define   FILEREF_JSON_SUPPORT 1
//#define   FILEREF_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct FileRef_data_s	FILEREF_DATA;            // Inherits from OBJ
    typedef struct FileRef_class_data_s FILEREF_CLASS_DATA;   // Inherits from OBJ

    typedef struct FileRef_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in FileRef_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(FILEREF_DATA *);
    } FILEREF_VTBL;

    typedef struct FileRef_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in FileRef_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(FILEREF_DATA *);
    } FILEREF_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  FILEREF_SINGLETON
    FILEREF_DATA *  FileRef_Shared (
        void
    );

    bool            FileRef_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to FileRef object if successful, otherwise OBJ_NIL.
     */
    FILEREF_DATA *  FileRef_Alloc (
        void
    );
    
    
    OBJ_ID          FileRef_Class (
        void
    );
    
    
    FILEREF_DATA *  FileRef_New (
        void
    );
    
    
    FILEREF_DATA *  FileRef_NewWithData (
        ASTRC_DATA      *pDrv,
        ASTRC_DATA      *pDir,
        ASTRC_DATA      *pName,
        ASTRC_DATA      *pExt
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ASTRC_DATA *    FileRef_getDrv (
        FILEREF_DATA    *this
    );

    bool            FileRef_setDrv (
        FILEREF_DATA    *this,
        ASTRC_DATA      *pValue
    );


    ASTRC_DATA *    FileRef_getDir (
        FILEREF_DATA    *this
    );

    bool            FileRef_setDir (
        FILEREF_DATA    *this,
        ASTRC_DATA      *pValue
    );


    ASTRC_DATA *    FileRef_getExt (
        FILEREF_DATA    *this
    );

    bool            FileRef_setExt (
        FILEREF_DATA    *this,
        ASTRC_DATA      *pValue
    );


    ASTRC_DATA *    FileRef_getName (
        FILEREF_DATA    *this
    );

    bool            FileRef_setName (
        FILEREF_DATA    *this,
        ASTRC_DATA      *pValue
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    FILEREF_DATA *  FileRef_Init (
        FILEREF_DATA    *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = FileRef_ToDebugString(this,4);
     @endcode 
     @param     this    FILEREF object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     FileRef_ToDebugString (
        FILEREF_DATA    *this,
        int             indent
    );
    
    
    ASTR_DATA *     FileRef_ToString (
        FILEREF_DATA    *this
    );

    
#ifdef	__cplusplus
}
#endif

#endif	/* FILEREF_H */

