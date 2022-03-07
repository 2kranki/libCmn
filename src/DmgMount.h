// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Mount a DMG file (DmgMount) Header
//****************************************************************
/*
 * Program
 *          Mount a DMG file (DmgMount)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate DmgMount to run things without complications
 *          of interfering with the main DmgMount. A DmgMount may be 
 *          called a DmgMount on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  03/06/2022 Generated
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


#ifndef         DMGMOUNT_H
#define         DMGMOUNT_H


//#define   _IS_IMMUTABLE     1
//#define   _JSON_SUPPORT     1
//#define   _SINGLETON        1
//#define       DMGMOUNT_MSGS   1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct DmgMount_data_s  DMGMOUNT_DATA;          // Inherits from DMGMOUNT
    typedef struct DmgMount_class_data_s DMGMOUNT_CLASS_DATA;  // Inherits from OBJ

    typedef struct DmgMount_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //DmgMount_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in DmgMount_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DMGMOUNT_DATA *);
    } DMGMOUNT_VTBL;

    typedef struct DmgMount_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in DmgMount_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DMGMOUNT_DATA *);
    } DMGMOUNT_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  DMGMOUNT_SINGLETON
    DMGMOUNT_DATA *     DmgMount_Shared (
        void
    );

    void            DmgMount_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to DmgMount object if successful, otherwise OBJ_NIL.
     */
    DMGMOUNT_DATA *     DmgMount_Alloc (
        void
    );
    
    
    OBJ_ID          DmgMount_Class (
        void
    );
    
    
    DMGMOUNT_DATA *     DmgMount_New (
        void
    );
    
    
#ifdef  DMGMOUNT_JSON_SUPPORT
    DMGMOUNT_DATA *   DmgMount_NewFromJsonString (
        ASTR_DATA       *pString
    );

    DMGMOUNT_DATA *   DmgMount_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef DMGMOUNT_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            DmgMount_setMsgs (
        DMGMOUNT_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     DmgMount_Disable (
        DMGMOUNT_DATA       *this
    );


    ERESULT     DmgMount_Enable (
        DMGMOUNT_DATA       *this
    );

   
    DMGMOUNT_DATA *   DmgMount_Init (
        DMGMOUNT_DATA     *this
    );


    ERESULT     DmgMount_IsEnabled (
        DMGMOUNT_DATA       *this
    );
    
 
#ifdef  DMGMOUNT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = DmgMount_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     DmgMount_ToJson (
        DMGMOUNT_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = DmgMount_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     DmgMount_ToDebugString (
        DMGMOUNT_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* DMGMOUNT_H */

