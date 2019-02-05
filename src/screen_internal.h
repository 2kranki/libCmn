// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   screen_internal.h
 *	Generated 07/26/2018 19:52:43
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




#include    <screen.h>
#include    <jsonIn.h>
#ifdef  SCREEN_USE_CURSES
#   include    <curses.h>
#endif


#ifndef SCREEN_INTERNAL_H
#define	SCREEN_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum screen_type_e {
        SCREEN_TYPE_UNKNOWN=0,
        SCREEN_TYPE_VISUAL_200=1,
        SCREEN_TYPE_ADDS_VIEWPOINT=2,
        SCREEN_TYPE_HAZELTINE_1500=3,
        SCREEN_TYPE_ADM_3=4,                // ADM-3 / Wyse 50+
        SCREEN_TYPE_ANSI=5
    } SCREEN_TYPE;


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct screen_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        reserved;
    ASTR_DATA       *pStr;
    int             nrows;
    int             ncols;
#ifdef  SCREEN_USE_CURSES
    WINDOW          *pWndMain;
#else
    int             termType;
#endif

};
#pragma pack(pop)

    extern
    const
    struct screen_class_data_s  screen_ClassObj;

    extern
    const
    SCREEN_VTBL         screen_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  screen_getSuperVtbl(
        SCREEN_DATA     *this
    );


    void            screen_Dealloc(
        OBJ_ID          objId
    );


    SCREEN_DATA *       screen_ParseObject(
        JSONIN_DATA     *pParser
    );


    void *          screen_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     screen_ToJSON(
        SCREEN_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			screen_Validate(
        SCREEN_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SCREEN_INTERNAL_H */

