// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   hashtbl_internal.h
 *	Generated 01/12/2019 11:49:43
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




#include        <hashtbl.h>
#include        <blocks_internal.h>
#include        <jsonIn.h>


#ifndef HASHTBL_INTERNAL_H
#define	HASHTBL_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct hashtbl_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    BLOCKS_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        rsvd16;
    ASTR_DATA       *pStr;

};
#pragma pack(pop)

    extern
    struct hashtbl_class_data_s  hashtbl_ClassObj;

    extern
    const
    HASHTBL_VTBL         hashtbl_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  HASHTBL_SINGLETON
    HASHTBL_DATA *     hashtbl_getSingleton (
        void
    );

    bool            hashtbl_setSingleton (
     HASHTBL_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  hashtbl_getSuperVtbl (
        HASHTBL_DATA     *this
    );


    void            hashtbl_Dealloc (
        OBJ_ID          objId
    );


    HASHTBL_DATA *       hashtbl_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          hashtbl_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     hashtbl_ToJSON (
        HASHTBL_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			hashtbl_Validate (
        HASHTBL_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* HASHTBL_INTERNAL_H */

