// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Dir_internal.h
 *	Generated 01/31/2020 10:23:30
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




#include        <Dir.h>
#include        <JsonIn.h>
#include        <ObjEnum_internal.h>


#ifndef DIR_INTERNAL_H
#define	DIR_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif



    // Only data that remains static through the directory structure
    // should remain here.  All dynamic data should be passed through
    // method parametera.
#pragma pack(push, 1)
    typedef struct Scanner_data_s {
        bool            (*pScanner)(void *, DIRENTRY_DATA *, void *);
        void            *pObject;
        void            *pData;
        const
        char            *pPatternA;
        bool            fRecurse;
    } SCANNER_DATA;
#pragma pack(pop)




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Dir_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data

};
#pragma pack(pop)

    extern
    struct Dir_class_data_s  Dir_ClassObj;

    extern
    const
    DIR_VTBL         Dir_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  DIR_SINGLETON
    DIR_DATA *     Dir_getSingleton (
        void
    );

    bool            Dir_setSingleton (
     DIR_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Dir_getSuperVtbl (
        DIR_DATA     *this
    );


    ERESULT         Dir_Assign (
        DIR_DATA    *this,
        DIR_DATA    *pOther
    );


    DIR_DATA *       Dir_Copy (
        DIR_DATA     *this
    );


    void            Dir_Dealloc (
        OBJ_ID          objId
    );


#ifdef  DIR_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    DIR_DATA *       Dir_ParseJsonObject (
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
    ERESULT         Dir_ParseJsonFields (
        JSONIN_DATA     *pParser,
        DIR_DATA     *pObject
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
    ERESULT         Dir_ToJsonFields (
        DIR_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif


    void *          Dir_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  DIR_JSON_SUPPORT
    ASTR_DATA *     Dir_ToJson (
        DIR_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			Dir_Validate (
        DIR_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* DIR_INTERNAL_H */

