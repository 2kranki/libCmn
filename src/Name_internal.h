// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Name_internal.h
 *	Generated 01/11/2020 10:01:40
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




#include        <Name.h>
#include        <AStr.h>
#include        <JsonIn.h>
#include        <W32Str.h>


#ifndef NAME_INTERNAL_H
#define	NAME_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Name_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define NAME_FLAG_HASH  OBJ_FLAG_USER1  /* Hash is initialized. */

    // Common Data
    uint16_t        type;               /* Type in union below*/
    uint16_t        rsvd;
    union {
        char            chrs[8];            // UTF-8 Character w/NUL
        int64_t         integer;            // Integer
        const
        char            *pChrs;             // UTF-8 Character String
        OBJ_ID          pObj;               // any object
    };
    uint32_t            hash;

};
#pragma pack(pop)

    extern
    struct Name_class_data_s  Name_ClassObj;

    extern
    const
    NAME_VTBL         Name_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NAME_SINGLETON
    NAME_DATA *     Name_getSingleton (
        void
    );

    bool            Name_setSingleton (
     NAME_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Name_getSuperVtbl (
        NAME_DATA     *this
    );


    void            Name_Dealloc (
        OBJ_ID          objId
    );


#ifdef  NAME_JSON_SUPPORT
    NAME_DATA *     Name_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          Name_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  NAME_JSON_SUPPORT
    ASTR_DATA *     Name_ToJson (
        NAME_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			Name_Validate (
        NAME_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NAME_INTERNAL_H */

