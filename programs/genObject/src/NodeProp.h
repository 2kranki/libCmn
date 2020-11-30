// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//            Class Property Definition (NodeProp) Header
//****************************************************************
/*
 * Program
 *			Class Property Definition (NodeProp)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate NodeProp to run things without complications
 *          of interfering with the main NodeProp. A NodeProp may be 
 *          called a NodeProp on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/26/2020 Generated
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


#ifndef         NODEPROP_H
#define         NODEPROP_H


//#define   NODEPROP_IS_IMMUTABLE     1
#define   NODEPROP_JSON_SUPPORT     1
//#define   NODEPROP_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodeProp_data_s	NODEPROP_DATA;            // Inherits from OBJ
    typedef struct NodeProp_class_data_s NODEPROP_CLASS_DATA;   // Inherits from OBJ

    typedef struct NodeProp_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeProp_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEPROP_DATA *);
    } NODEPROP_VTBL;

    typedef struct NodeProp_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeProp_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEPROP_DATA *);
    } NODEPROP_CLASS_VTBL;

    typedef enum NodeProp_Vis_e {
        NODEPROP_VIS_NONE=0,
        NODEPROP_VIS_PUBLIC,
        NODEPROP_VIS_READ_ONLY
    } NODEPROP_VIS;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEPROP_SINGLETON
    NODEPROP_DATA * NodeProp_Shared (
        void
    );

    void            NodeProp_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeProp object if successful, otherwise OBJ_NIL.
     */
    NODEPROP_DATA * NodeProp_Alloc (
        void
    );
    
    
    OBJ_ID          NodeProp_Class (
        void
    );
    
    
    NODEPROP_DATA * NodeProp_New (
        void
    );
    
    
#ifdef  NODEPROP_JSON_SUPPORT
    NODEPROP_DATA * NodeProp_NewFromJsonString (
        ASTR_DATA       *pString
    );

    NODEPROP_DATA * NodeProp_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! @property   External - External Name
     */
    ASTR_DATA *     NodeProp_getExternal (
        NODEPROP_DATA   *this
    );

    bool            NodeProp_setExternal (
        NODEPROP_DATA   *this,
        ASTR_DATA       *pValue
    );


    /*! @property   Init - Default Initialization
     */
    ASTR_DATA *     NodeProp_getInit (
        NODEPROP_DATA   *this
    );

    bool            NodeProp_setInit (
        NODEPROP_DATA   *this,
        ASTR_DATA       *pValue
    );


    ASTR_DATA *     NodeProp_getInternal (
        NODEPROP_DATA   *this
    );

    bool            NodeProp_setInternal (
        NODEPROP_DATA   *this,
        ASTR_DATA       *pValue
    );


    ASTR_DATA *     NodeProp_getLong (
        NODEPROP_DATA   *this
    );

    bool            NodeProp_setLong (
        NODEPROP_DATA   *this,
        ASTR_DATA       *pValue
    );


    ASTR_DATA *     NodeProp_getName (
        NODEPROP_DATA   *this
    );

    bool            NodeProp_setName (
        NODEPROP_DATA   *this,
        ASTR_DATA       *pValue
    );


    ASTR_DATA *     NodeProp_getShort (
        NODEPROP_DATA   *this
    );

    bool            NodeProp_setShort (
        NODEPROP_DATA   *this,
        ASTR_DATA       *pValue
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
        ERESULT eRc = NodeProp_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another NODEPROP object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         NodeProp_Assign (
        NODEPROP_DATA        *this,
        NODEPROP_DATA     *pOther
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         NodeProp_Compare (
        NODEPROP_DATA     *this,
        NODEPROP_DATA     *pOther
    );

   
    /*!
    Copy the current object creating a new object.
    Example:
    @code
     NodeProp      *pCopy = NodeProp_Copy(this);
    @endcode
    @param     this    object pointer
    @return    If successful, a NODEPROP object which must be
             released, otherwise OBJ_NIL.
    @warning   Remember to release the returned object.
    */
    NODEPROP_DATA * NodeProp_Copy (
        NODEPROP_DATA   *this
    );


    /*!
     Generate a string that contains the Property Definition for the
     code file.
     @param     this    object pointer
     @param     pClass  Class Name
     @param     pClassUC Uppercase Class Name
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeProp_GenCode (
        NODEPROP_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    );


    /*!
     Generate a string that contains the Property Definition for the
     header file.
     @param     this    object pointer
     @param     pClass  Class Name
     @param     pClassUC Uppercase Class Name
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeProp_GenHdrDefn (
        NODEPROP_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    );


    /*!
     Generate a string that contains the Property Definition for the
     internal header file.
     @param     this    object pointer
     @param     pClass  Class Name
     @param     pClassUC Uppercase Class Name
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeProp_GenIntDefn (
        NODEPROP_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    );


    /*!
     Generate a string that contains the Property Definition for the
     internal header file variable definition.
     @param     this    object pointer
     @param     pClass  Class Name
     @param     pClassUC Uppercase Class Name
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeProp_GenIntVar (
        NODEPROP_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    );


    NODEPROP_DATA * NodeProp_Init (
        NODEPROP_DATA   *this
    );


#ifdef  NODEPROP_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = NodeProp_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeProp_ToJson (
        NODEPROP_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeProp_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeProp_ToDebugString (
        NODEPROP_DATA   *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEPROP_H */

