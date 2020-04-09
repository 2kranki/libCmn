// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Graph16_internal.h
 *	Generated 03/11/2020 17:37:49
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




#include        <Graph16.h>
#include        <I16Array_internal.h>
#include        <JsonIn.h>
#include        <ObjArray.h>


#ifndef GRAPH16_INTERNAL_H
#define	GRAPH16_INTERNAL_H




#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Graph16_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        edgesMax;		// middle edge index
    uint16_t        edgesUsed;
    uint16_t        verticesMax;    // max Vertex Index
    uint16_t        verticesUsed;
    int16_t         *pEdges;        // Edge Array of Node Indices
    //                              // Indexed with +/- edge index
    int16_t         *pNext;         // Edge Array of Edge Indices
    //                              // (Used to index into Edges)
    //                              // Indexed with +/- edge index
    int16_t         *pFirst;        // Vertex Array of Edge Indices
    //                              // (Used to index into Edges)
    //                              // Indexed with + vertex index

};
#pragma pack(pop)

    extern
    struct Graph16_class_data_s  Graph16_ClassObj;

    extern
    const
    GRAPH16_VTBL         Graph16_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  GRAPH16_SINGLETON
    GRAPH16_DATA *     Graph16_getSingleton (
        void
    );

    bool            Graph16_setSingleton (
     GRAPH16_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Graph16_getSuperVtbl (
        GRAPH16_DATA     *this
    );


    ERESULT         Graph16_Assign (
        GRAPH16_DATA    *this,
        GRAPH16_DATA    *pOther
    );


    GRAPH16_DATA *  Graph16_Copy (
        GRAPH16_DATA     *this
    );


    void            Graph16_Dealloc (
        OBJ_ID          objId
    );


#ifdef  GRAPH16_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    GRAPH16_DATA *  Graph16_ParseJsonObject (
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
    ERESULT         Graph16_ParseJsonFields (
        JSONIN_DATA     *pParser,
        GRAPH16_DATA    *pObject
    );
#endif


    void *          Graph16_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    void            Graph16_RebuildIndex (
        GRAPH16_DATA    *this
    );


#ifdef  GRAPH16_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Graph16_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Graph16_ToJson (
        GRAPH16_DATA      *this
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
    ERESULT         Graph16_ToJsonFields (
        GRAPH16_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif


    void            Graph16_UpdateIndex (
        GRAPH16_DATA    *this,
        int16_t         e
    );


#ifdef NDEBUG
#else
    bool			Graph16_Validate (
        GRAPH16_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* GRAPH16_INTERNAL_H */

