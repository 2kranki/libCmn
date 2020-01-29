// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Disk Directory or File Path (Path) Header
//****************************************************************
/*
 * Program
 *			Disk Directory or File Path (Path)
 * Purpose
 *          This object provides a standardized way of handling a path
 *
 *          This path is based partially on url format and Unix path
 *          format. The general form of a path is:
 *              [driveSpecifier:] [/directory]* fileName [.ext]
 *
 * Remarks
 *    1.    The object User flags and Misc data are not used in this
 *          object.
 *
 * History
 *  06/09/2015 Generated
 *	01/29/2020 Regenerated and added json support
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
#include        <dateTime.h>


#ifndef         PATH_H
#define         PATH_H


//#define   PATH_IS_IMMUTABLE     1
#define   PATH_JSON_SUPPORT     1
//#define   PATH_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    //typedef struct Path_data_s	PATH_DATA;            // Inherits from OBJ
    //typedef struct Path_class_data_s PATH_CLASS_DATA;   // Inherits from OBJ

    typedef struct Path_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Path_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PATH_DATA *);
    } PATH_VTBL;

    typedef struct Path_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Path_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PATH_DATA *);
    } PATH_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  PATH_SINGLETON
    PATH_DATA *     Path_Shared (
        void
    );

    void            Path_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Path object if successful, otherwise OBJ_NIL.
     */
    PATH_DATA *     Path_Alloc (
        void
    );
    
    
    OBJ_ID          Path_Class (
        void
    );
    
    
    PATH_DATA *     Path_New (
        void
    );
    
    
#ifdef  PATH_JSON_SUPPORT
    PATH_DATA *   Path_NewFromJsonString(
        ASTR_DATA       *pString
    );

    PATH_DATA *   Path_NewFromJsonStringA(
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     Path_Disable (
        PATH_DATA		*this
    );


    ERESULT     Path_Enable (
        PATH_DATA		*this
    );

   
    PATH_DATA *   Path_Init (
        PATH_DATA     *this
    );


    ERESULT     Path_IsEnabled (
        PATH_DATA		*this
    );
    
 
#ifdef  PATH_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Path_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Path_ToJson(
        PATH_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Path_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Path_ToDebugString (
        PATH_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* PATH_H */

