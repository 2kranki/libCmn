// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Source File Reference (SrcRef) Header
//****************************************************************
/*
 * Program
 *			Source File Reference (SrcRef)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate SrcRef to run things without complications
 *          of interfering with the main SrcRef. A SrcRef may be 
 *          called a SrcRef on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/05/2019 Generated
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


#ifndef         SRCREF_H
#define         SRCREF_H


//#define   SRCREF_JSON_SUPPORT 1
//#define   SRCREF_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SrcRef_data_s	SRCREF_DATA;            // Inherits from OBJ
    typedef struct SrcRef_class_data_s SRCREF_CLASS_DATA;   // Inherits from OBJ

    typedef struct SrcRef_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcRef_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCREF_DATA *);
    } SRCREF_VTBL;

    typedef struct SrcRef_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcRef_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCREF_DATA *);
    } SRCREF_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SRCREF_SINGLETON
    SRCREF_DATA *     SrcRef_Shared (
        void
    );

    bool            SrcRef_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SrcRef object if successful, otherwise OBJ_NIL.
     */
    SRCREF_DATA *   SrcRef_Alloc (
        void
    );
    
    
    OBJ_ID          SrcRef_Class (
        void
    );
    
    
    SRCREF_DATA *   SrcRef_New (
        void
    );
    
    
    SRCREF_DATA *   SrcRef_NewFile (
        ASTRC_DATA      *pDir,
        ASTRC_DATA      *pName,
        ASTRC_DATA      *pSuffix
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ASTRC_DATA *    SrcRef_getDir (
        SRCREF_DATA     *this
    );

    bool            SrcRef_setDir (
        SRCREF_DATA     *this,
        ASTRC_DATA      *pValue
    );


    ASTRC_DATA *    SrcRef_getName (
        SRCREF_DATA     *this
    );

    bool            SrcRef_setName (
        SRCREF_DATA     *this,
        ASTRC_DATA      *pValue
    );


    ASTRC_DATA *    SrcRef_getSuffix (
        SRCREF_DATA     *this
    );

    bool            SrcRef_setSuffix (
        SRCREF_DATA     *this,
        ASTRC_DATA      *pValue
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    SRCREF_DATA *   SrcRef_Init (
        SRCREF_DATA     *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SrcRef_ToDebugString(this,4);
     @endcode 
     @param     this    SRCREF object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcRef_ToDebugString (
        SRCREF_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SRCREF_H */

