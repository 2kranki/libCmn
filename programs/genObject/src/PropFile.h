// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Property File Generation (PropFile) Header
//****************************************************************
/*
 * Program
 *          Property File Generation (PropFile)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate PropFile to run things without complications
 *          of interfering with the main PropFile. A PropFile may be 
 *          called a PropFile on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  11/23/2021 Generated
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


#ifndef         PROPFILE_H
#define         PROPFILE_H


//#define   PROPFILE_IS_IMMUTABLE     1
//#define   PROPFILE_JSON_SUPPORT     1
//#define   PROPFILE_SINGLETON        1
//#define       PROPFILE_MSGS   1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct PropFile_data_s  PROPFILE_DATA;          // Inherits from PROPFILE
    typedef struct PropFile_class_data_s PROPFILE_CLASS_DATA;  // Inherits from OBJ

    typedef struct PropFile_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //PropFile_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in PropFile_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PROPFILE_DATA *);
    } PROPFILE_VTBL;

    typedef struct PropFile_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in PropFile_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PROPFILE_DATA *);
    } PROPFILE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  PROPFILE_SINGLETON
    PROPFILE_DATA *     PropFile_Shared (
        void
    );

    void            PropFile_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to PropFile object if successful, otherwise OBJ_NIL.
     */
    PROPFILE_DATA *     PropFile_Alloc (
        void
    );
    
    
    OBJ_ID          PropFile_Class (
        void
    );
    
    
    PROPFILE_DATA *     PropFile_New (
        void
    );
    
    
#ifdef  PROPFILE_JSON_SUPPORT
    PROPFILE_DATA *   PropFile_NewFromJsonString (
        ASTR_DATA       *pString
    );

    PROPFILE_DATA *   PropFile_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef PROPFILE_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            PropFile_setMsgs (
        PROPFILE_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     PropFile_Disable (
        PROPFILE_DATA       *this
    );


    ERESULT     PropFile_Enable (
        PROPFILE_DATA       *this
    );

   
    PROPFILE_DATA *   PropFile_Init (
        PROPFILE_DATA     *this
    );


    ERESULT     PropFile_IsEnabled (
        PROPFILE_DATA       *this
    );
    
 
#ifdef  PROPFILE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = PropFile_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     PropFile_ToJson (
        PROPFILE_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = PropFile_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     PropFile_ToDebugString (
        PROPFILE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* PROPFILE_H */

