// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   ObjCb_internal.h
 *	Generated 02/21/2020 14:01:14
 *
 * Notes:
 *  --	N/A
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




#include        <ObjCb.h>
#include        <JsonIn.h>
#include        <psxCond.h>
#include        <psxLock.h>
#include        <psxSem.h>


#ifndef OBJCB_INTERNAL_H
#define	OBJCB_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct ObjCb_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    PSXCOND_DATA    *pEmpty;
    PSXCOND_DATA    *pFull;
    PSXMUTEX_DATA   *pMutex;
    uint32_t        cEntries;    // maximum number of elements
    volatile
    uint8_t         fStop;
    uint8_t         rsvd8;
    uint16_t        rsvd16;
    volatile
    uint32_t        start;        // index of oldest element
    volatile
    uint32_t        end;        // index at which to write new element
    volatile
    uint32_t        numWritten;
    volatile
    uint32_t        numRead;
    OBJ_ID          *pEntries;

};
#pragma pack(pop)

    extern
    struct ObjCb_class_data_s  ObjCb_ClassObj;

    extern
    const
    OBJCB_VTBL         ObjCb_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OBJCB_SINGLETON
    OBJCB_DATA *     ObjCb_getSingleton (
        void
    );

    bool            ObjCb_setSingleton (
     OBJCB_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  ObjCb_getSuperVtbl (
        OBJCB_DATA     *this
    );


    ERESULT         ObjCb_Assign (
        OBJCB_DATA    *this,
        OBJCB_DATA    *pOther
    );


    OBJCB_DATA *       ObjCb_Copy (
        OBJCB_DATA     *this
    );


    void            ObjCb_Dealloc (
        OBJ_ID          objId
    );


#ifdef  OBJCB_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    OBJCB_DATA *       ObjCb_ParseJsonObject (
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
    ERESULT         ObjCb_ParseJsonFields (
        JSONIN_DATA     *pParser,
        OBJCB_DATA     *pObject
    );
#endif


    void *          ObjCb_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  OBJCB_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ObjCb_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjCb_ToJson (
        OBJCB_DATA      *this
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
    ERESULT         ObjCb_ToJsonFields (
        OBJCB_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			ObjCb_Validate (
        OBJCB_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OBJCB_INTERNAL_H */

