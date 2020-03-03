// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Balanced Binary Tree for Objects (ObjBT) Header
//****************************************************************
/*
 * Program
 *			Balanced Binary Tree for Objects (ObjBT)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate ObjBT to run things without complications
 *          of interfering with the main ObjBT. A ObjBT may be 
 *          called a ObjBT on other O/S's.
 *
 * Remarks
 *    1.    The objects added to this table must support the
 *          compare() method. The compare() method must be able
 *          to compare its object against any other object in
 *          the table.  This method is part of the common VTBL
 *          for each object.
 *
 * History
 *	03/01/2020 Generated
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


#ifndef         OBJBT_H
#define         OBJBT_H


//#define   OBJBT_IS_IMMUTABLE     1
#define   OBJBT_JSON_SUPPORT     1
//#define   OBJBT_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ObjBT_data_s	OBJBT_DATA;            // Inherits from OBJ
    typedef struct ObjBT_class_data_s OBJBT_CLASS_DATA;   // Inherits from OBJ

    typedef struct ObjBT_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjBT_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJBT_DATA *);
    } OBJBT_VTBL;

    typedef struct ObjBT_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjBT_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJBT_DATA *);
    } OBJBT_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  OBJBT_SINGLETON
    OBJBT_DATA *    ObjBT_Shared (
        void
    );

    void            ObjBT_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ObjBT object if successful, otherwise OBJ_NIL.
     */
    OBJBT_DATA *    ObjBT_Alloc (
        void
    );
    
    
    OBJ_ID          ObjBT_Class (
        void
    );
    
    
    OBJBT_DATA *     ObjBT_New (
        void
    );
    
    
#ifdef  OBJBT_JSON_SUPPORT
    OBJBT_DATA *    ObjBT_NewFromJsonString (
        ASTR_DATA       *pString
    );

    OBJBT_DATA *    ObjBT_NewFromJsonStringA (
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

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = ObjBT_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another OBJBT object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         ObjBT_Assign (
        OBJBT_DATA      *this,
        OBJBT_DATA      *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        ObjBT      *pCopy = ObjBT_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a OBJBT object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJBT_DATA *    ObjBT_Copy (
        OBJBT_DATA      *this
    );

   
    OBJBT_DATA *    ObjBT_Init (
        OBJBT_DATA      *this
    );


#ifdef  OBJBT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ObjBT_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjBT_ToJson (
        OBJBT_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjBT_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    ObjBT_ToDebugString (
        OBJBT_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJBT_H */

