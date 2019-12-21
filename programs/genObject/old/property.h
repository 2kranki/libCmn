// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Object Property Definition (property) Header
//****************************************************************
/*
 * Program
 *			Object Property Definition (property)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate property to run things without complications
 *          of interfering with the main property. A property may be 
 *          called a property on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/02/2018 Generated
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





#include        <genObject.h>
#include        <AStr.h>


#ifndef         PROPERTY_H
#define         PROPERTY_H


//#define   PROPERTY_SINGLETON    1
#define     PROPERTY_DATANAME_OWNED 1
#define     PROPERTY_DESC_OWNED 1
#define     PROPERTY_DESCSHORT_OWNED 1
#define     PROPERTY_NAME_OWNED 1
#define     PROPERTY_TYPE_OWNED 1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct property_data_s	PROPERTY_DATA;            // Inherits from OBJ
    typedef struct property_class_data_s PROPERTY_CLASS_DATA;   // Inherits from OBJ

    typedef struct property_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in property_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PROPERTY_DATA *);
    } PROPERTY_VTBL;

    typedef struct property_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in property_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PROPERTY_DATA *);
    } PROPERTY_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  PROPERTY_SINGLETON
    PROPERTY_DATA * property_Shared (
        void
    );

    bool            property_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to property object if successful, otherwise OBJ_NIL.
     */
    PROPERTY_DATA * property_Alloc (
        void
    );
    
    
    OBJ_ID          property_Class (
        void
    );
    
    
    PROPERTY_DATA * property_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        property_getClass (
        PROPERTY_DATA   *this
    );
    
    bool            property_setClass (
        PROPERTY_DATA   *this,
        uint32_t        value
    );
    
    
    ASTR_DATA *     property_getDataName (
        PROPERTY_DATA   *this
    );
    
    bool            property_setDataName (
        PROPERTY_DATA   *this,
        ASTR_DATA       *pValue
    );

    
    ASTR_DATA *     property_getDesc (
        PROPERTY_DATA   *this
    );
    
    bool            property_setDesc (
        PROPERTY_DATA   *this,
        ASTR_DATA       *pValue
    );
    
    
    ASTR_DATA *     property_getDescShort (
        PROPERTY_DATA   *this
    );
    
    bool            property_setDescShort (
        PROPERTY_DATA   *this,
        ASTR_DATA       *pValue
    );
    
    
    /*!
     GenInternal property indicate the type for the field.
     */
    bool            property_getGenInternal (
        PROPERTY_DATA   *this
    );
    
    bool            property_setGenInternal (
        PROPERTY_DATA   *this,
        bool            fValue
    );
    
    
    ASTR_DATA *     property_getName (
        PROPERTY_DATA   *this
    );
    
    bool            property_setName (
        PROPERTY_DATA   *this,
        ASTR_DATA       *pValue
    );
    
    
    uint32_t        property_getShift (
        PROPERTY_DATA   *this
    );
    
    bool            property_setShift (
        PROPERTY_DATA   *this,
        uint32_t        value
    );

    
    /*!
     Type property is the type for the field.
     */
    ASTR_DATA *     property_getType (
        PROPERTY_DATA   *this
    );
    
    bool            property_setType (
        PROPERTY_DATA   *this,
        ASTR_DATA       *pValue
    );
    
    
    /*!
     TypeInternal property is the internal
     type for the field.  This is only needed
     if it differs from the Type property.
     */
    ASTR_DATA *     property_getTypeInternal (
        PROPERTY_DATA   *this
    );
    
    bool            property_setTypeInternal (
        PROPERTY_DATA   *this,
        ASTR_DATA       *pValue
    );
    
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Generate a string that describes the field for this object.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
     field definition, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     property_GenHeader (
        PROPERTY_DATA   *this
    );
    
    
    /*!
     Generate a string that describes the field for this object.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
     field definition, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     property_GenInternal (
        PROPERTY_DATA   *this
    );
    
    
    PROPERTY_DATA *   property_Init (
        PROPERTY_DATA     *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = property_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     property_ToDebugString (
        PROPERTY_DATA   *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* PROPERTY_H */

