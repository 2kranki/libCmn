// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Generate a File (Gen) Header
//****************************************************************
/*
 * Program
 *			Generate a File (Gen)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate Gen to run things without complications
 *          of interfering with the main Gen. A Gen may be 
 *          called a Gen on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	05/05/2020 Generated
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


#ifndef         GEN_H
#define         GEN_H


//#define   GEN_IS_IMMUTABLE     1
//#define   GEN_JSON_SUPPORT     1
//#define   GEN_SINGLETON        1

#define OBJECT_NAME         "LNAME"
#define OBJECT_NAME_UPPER   "UNAME"



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Gen_data_s	GEN_DATA;            // Inherits from OBJ
    typedef struct Gen_class_data_s GEN_CLASS_DATA;   // Inherits from OBJ

    typedef struct Gen_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Gen_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GEN_DATA *);
    } GEN_VTBL;

    typedef struct Gen_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Gen_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GEN_DATA *);
    } GEN_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  GEN_SINGLETON
    GEN_DATA *      Gen_Shared (
        void
    );

    void            Gen_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Gen object if successful, otherwise OBJ_NIL.
     */
    GEN_DATA *      Gen_Alloc (
        void
    );
    
    
    OBJ_ID          Gen_Class (
        void
    );
    
    
    GEN_DATA *      Gen_New (
        void
    );
    
    
#ifdef  GEN_JSON_SUPPORT
    GEN_DATA *      Gen_NewFromJsonString (
        ASTR_DATA       *pString
    );

    GEN_DATA *      Gen_NewFromJsonStringA (
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

    ERESULT         Gen_AddUpdateA(
        GEN_DATA        *this,
        const
        char            *pNameA,
        ASTR_DATA       *pData
    );


    ASTR_DATA *     Gen_FindA (
        GEN_DATA		*this,
        const
        char            *pNameA
    );


    /*!
     Expand the variables (of the form ${...}) in the model file creating
     the output file.
     @param     this    object pointer
     @param     pModel  Model File Path to be expanded
     @param     pOutput Output File Path
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Gen_ExpandFile (
        GEN_DATA		*this,
        PATH_DATA       *pModel,
        PATH_DATA       *pOutput
    );

   
    GEN_DATA *      Gen_Init (
        GEN_DATA        *this
    );


#ifdef  GEN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Gen_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Gen_ToJson (
        GEN_DATA        *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Gen_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Gen_ToDebugString (
        GEN_DATA        *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* GEN_H */

