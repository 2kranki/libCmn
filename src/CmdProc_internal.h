// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   CmdProc_internal.h
 *  Generated 12/29/2020 17:10:42
 *
 * Notes:
 *  --  N/A
 *
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




#include        <CmdProc.h>
#include        <JsonIn.h>


#ifndef CMDPROC_INTERNAL_H
#define CMDPROC_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct CmdProc_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint8_t         fUndo;          // true == has undo capability
    uint8_t         rsvd8;
    uint16_t        state;
    ASTR_DATA       *pStr;
    NODELIST_DATA   *pUndo;         // Saved change states.
    NODELIST_DATA   *pRedo;         // Saved undo states.
    CMDPROC_EXEC_INTERFACE
                    *pExec;
    CMDUTL_DATA     *pCmdUtl;

};
#pragma pack(pop)

    extern
    struct CmdProc_class_data_s  CmdProc_ClassObj;

    extern
    const
    CMDPROC_VTBL         CmdProc_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  CMDPROC_SINGLETON
    CMDPROC_DATA *     CmdProc_getSingleton (
        void
    );

    bool            CmdProc_setSingleton (
     CMDPROC_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  CmdProc_getSuperVtbl (
        CMDPROC_DATA     *this
    );


    ERESULT         CmdProc_Assign (
        CMDPROC_DATA    *this,
        CMDPROC_DATA    *pOther
    );


    CMDPROC_DATA *       CmdProc_Copy (
        CMDPROC_DATA     *this
    );


    void            CmdProc_Dealloc (
        OBJ_ID          objId
    );


#ifdef  CMDPROC_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    CMDPROC_DATA *       CmdProc_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         CmdProc_ParseJsonFields (
        JSONIN_DATA     *pParser,
        CMDPROC_DATA     *pObject
    );
#endif


    void *          CmdProc_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  CMDPROC_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = CmdProc_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     CmdProc_ToJson (
        CMDPROC_DATA      *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         CmdProc_ToJsonFields (
        CMDPROC_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            CmdProc_Validate (
        CMDPROC_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* CMDPROC_INTERNAL_H */

