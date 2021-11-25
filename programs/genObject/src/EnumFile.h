// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Enumeration File Generation (EnumFile) Header
//****************************************************************
/*
 * Program
 *          Enumeration File Generation (EnumFile)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate EnumFile to run things without complications
 *          of interfering with the main EnumFile. A EnumFile may be 
 *          called a EnumFile on other O/S's.
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


#ifndef         ENUMFILE_H
#define         ENUMFILE_H


//#define   ENUMFILE_IS_IMMUTABLE     1
//#define   ENUMFILE_JSON_SUPPORT     1
//#define   ENUMFILE_SINGLETON        1
//#define       ENUMFILE_MSGS   1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct EnumFile_data_s  ENUMFILE_DATA;          // Inherits from ENUMFILE
    typedef struct EnumFile_class_data_s ENUMFILE_CLASS_DATA;  // Inherits from OBJ

    typedef struct EnumFile_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //EnumFile_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in EnumFile_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ENUMFILE_DATA *);
    } ENUMFILE_VTBL;

    typedef struct EnumFile_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in EnumFile_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ENUMFILE_DATA *);
    } ENUMFILE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  ENUMFILE_SINGLETON
    ENUMFILE_DATA *     EnumFile_Shared (
        void
    );

    void            EnumFile_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to EnumFile object if successful, otherwise OBJ_NIL.
     */
    ENUMFILE_DATA *     EnumFile_Alloc (
        void
    );
    
    
    OBJ_ID          EnumFile_Class (
        void
    );
    
    
    ENUMFILE_DATA *     EnumFile_New (
        void
    );
    
    
#ifdef  ENUMFILE_JSON_SUPPORT
    ENUMFILE_DATA *   EnumFile_NewFromJsonString (
        ASTR_DATA       *pString
    );

    ENUMFILE_DATA *   EnumFile_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef ENUMFILE_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            EnumFile_setMsgs (
        ENUMFILE_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     EnumFile_Disable (
        ENUMFILE_DATA       *this
    );


    ERESULT     EnumFile_Enable (
        ENUMFILE_DATA       *this
    );

   
    ENUMFILE_DATA *   EnumFile_Init (
        ENUMFILE_DATA     *this
    );


    ERESULT     EnumFile_IsEnabled (
        ENUMFILE_DATA       *this
    );
    
 
#ifdef  ENUMFILE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = EnumFile_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     EnumFile_ToJson (
        ENUMFILE_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = EnumFile_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     EnumFile_ToDebugString (
        ENUMFILE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* ENUMFILE_H */

