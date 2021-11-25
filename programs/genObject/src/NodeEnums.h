// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Enumeration File Generation (NodeEnums) Header
//****************************************************************
/*
 * Program
 *          Enumeration File Generation (NodeEnums)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate NodeEnums to run things without complications
 *          of interfering with the main NodeEnums. A NodeEnums may be 
 *          called a NodeEnums on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  11/22/2021 Generated
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


#ifndef         NODEENUMS_H
#define         NODEENUMS_H


//#define   NODEENUMS_IS_IMMUTABLE     1
#define   NODEENUMS_JSON_SUPPORT       1
//#define   NODEENUMS_SINGLETON        1
//#define       NODEENUMS_MSGS   1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodeEnums_data_s  NODEENUMS_DATA;          // Inherits from NODEENUMS
    typedef struct NodeEnums_class_data_s NODEENUMS_CLASS_DATA;  // Inherits from OBJ

    typedef struct NodeEnums_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //NodeEnums_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeEnums_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEENUMS_DATA *);
    } NODEENUMS_VTBL;

    typedef struct NodeEnums_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeEnums_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEENUMS_DATA *);
    } NODEENUMS_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEENUMS_SINGLETON
    NODEENUMS_DATA *     NodeEnums_Shared (
        void
    );

    void            NodeEnums_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeEnums object if successful, otherwise OBJ_NIL.
     */
    NODEENUMS_DATA *     NodeEnums_Alloc (
        void
    );
    
    
    OBJ_ID          NodeEnums_Class (
        void
    );
    
    
    NODEENUMS_DATA *     NodeEnums_New (
        void
    );
    
    
#ifdef  NODEENUMS_JSON_SUPPORT
    NODEENUMS_DATA *   NodeEnums_NewFromJsonString (
        ASTR_DATA       *pString
    );

    NODEENUMS_DATA *   NodeEnums_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef NODEENUMS_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            NodeEnums_setMsgs (
        NODEENUMS_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     NodeEnums_Disable (
        NODEENUMS_DATA       *this
    );


    ERESULT     NodeEnums_Enable (
        NODEENUMS_DATA       *this
    );

   
    NODEENUMS_DATA *   NodeEnums_Init (
        NODEENUMS_DATA     *this
    );


    ERESULT     NodeEnums_IsEnabled (
        NODEENUMS_DATA       *this
    );
    
 
#ifdef  NODEENUMS_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = NodeEnums_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeEnums_ToJson (
        NODEENUMS_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeEnums_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeEnums_ToDebugString (
        NODEENUMS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* NODEENUMS_H */

