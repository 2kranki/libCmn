// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//  Object with a Variable Number of Integer Links (ObjVLink)
//****************************************************************
/*
 * Program
 *			Object with a Variable Number of Integer Links (ObjVLink)
 * Purpose
 *			This object provides for adding a variable number of
 *          external integer links to an object. There are also a
 *          fixed number of links such as parent, left and right.
 *
 * Remarks
 *	1.      This object uses signed indices so that the sign can be
 *	        used for something such as back pointers.  It is assumed
 *          that an index must be non-zero.
 *  2.      The fixed indices can be accessed directly through their
 *          property methods or via get/set using OBJVLINK_INDEX
 *          indices.
 *
 * History
 *	01/14/2020 Generated
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


#ifndef         OBJVLINK_H
#define         OBJVLINK_H


#define   OBJVLINK_JSON_SUPPORT 1
//#define   OBJVLINK_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ObjVLink_data_s	OBJVLINK_DATA;            // Inherits from OBJ
    typedef struct ObjVLink_class_data_s OBJVLINK_CLASS_DATA;   // Inherits from OBJ

    typedef struct ObjVLink_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjVLink_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJVLINK_DATA *);
    } OBJVLINK_VTBL;

    typedef struct ObjVLink_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjVLink_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJVLINK_DATA *);
    } OBJVLINK_CLASS_VTBL;


    // Index values used the Get/Set which will access the fixed indices
    // as well as those in the optional array.
    typedef enum  ObjVLink_Index_e {
        OBJVLINK_INDEX_UNKNOWN=0,   // Not Allowed
        OBJVLINK_INDEX_INDEX,
        OBJVLINK_INDEX_LEFT,
        OBJVLINK_INDEX_MIDDLE,
        OBJVLINK_INDEX_MISC,
        OBJVLINK_INDEX_PARENT,
        OBJVLINK_INDEX_RIGHT,
        OBJVLINK_INDEX_HIGH         // Beginning value to access the array.
    } OBJVLINK_INDEX;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  OBJVLINK_SINGLETON
    OBJVLINK_DATA * ObjVLink_Shared (
        void
    );

    void            ObjVLink_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ObjVLink object if successful, otherwise OBJ_NIL.
     */
    OBJVLINK_DATA * ObjVLink_Alloc (
        void
    );
    
    
    OBJ_ID          ObjVLink_Class (
        void
    );
    
    
    OBJVLINK_DATA * ObjVLink_New (
        void
    );
    
    
#ifdef  OBJVLINK_JSON_SUPPORT
    OBJVLINK_DATA * ObjVLink_NewFromJsonString(
        ASTR_DATA       *pString
    );

    OBJVLINK_DATA * ObjVLink_NewFromJsonStringA(
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    int32_t         ObjVLink_getIndex (
        OBJVLINK_DATA   *this
    );
    
    bool            ObjVLink_setIndex (
        OBJVLINK_DATA   *this,
        int32_t         value
    );


    int32_t         ObjVLink_getLeft (
        OBJVLINK_DATA   *this
    );
    
    bool            ObjVLink_setLeft (
        OBJVLINK_DATA   *this,
        int32_t         value
    );


    int32_t         ObjVLink_getMiddle (
        OBJVLINK_DATA   *this
    );
    
    bool            ObjVLink_setMiddle (
        OBJVLINK_DATA   *this,
        int32_t         value
    );


    int32_t         ObjVLink_getMisc (
        OBJVLINK_DATA   *this
    );
    
    bool            ObjVLink_setMisc (
        OBJVLINK_DATA   *this,
        int32_t         value
    );


    int32_t         ObjVLink_getParent (
        OBJVLINK_DATA   *this
    );
    
    bool            ObjVLink_setParent (
        OBJVLINK_DATA   *this,
        int32_t         value
    );


    int32_t         ObjVLink_getRight (
        OBJVLINK_DATA   *this
    );
    
    bool            ObjVLink_setRight (
        OBJVLINK_DATA   *this,
        int32_t         value
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = ObjVLink_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another OBJVLINK object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         ObjVLink_Assign (
        OBJVLINK_DATA   *this,
        OBJVLINK_DATA   *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        ObjVLink      *pCopy = ObjVLink_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a OBJVLINK object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJVLINK_DATA *     ObjVLink_Copy (
        OBJVLINK_DATA       *this
    );


    /*!
     Get the index'th entry in the array. If it doesn't exist or there
     is an error, return zero which is not a legal index.
     Indices must be non-zero.
     @param     this    objArray object pointer
     @return    If successful, an index number, otherwise 0.
     */
    int32_t         ObjVLink_Get (
        OBJVLINK_DATA   *this,
        uint32_t        index       // Relative to 1
    );


    OBJVLINK_DATA * ObjVLink_Init (
        OBJVLINK_DATA   *this
    );


    uint32_t        ObjVLink_NumVLinks (
        OBJVLINK_DATA	*this
    );
    
 
    /*!
     Set the index'th entry in the array to the given index.
     @param     this    objArray object pointer
     @param     index   unsigned integer > 0
     @param     amt     signed integer
     @return    If successful, an old index number, otherwise 0.
     */
    int32_t         ObjVLink_Set (
        OBJVLINK_DATA   *this,
        uint32_t        index,      // Relative to 1
        int32_t         amt
    );


#ifdef  OBJVLINK_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ObjVLink_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjVLink_ToJson(
        OBJVLINK_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjVLink_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    ObjVLink_ToDebugString (
        OBJVLINK_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJVLINK_H */

