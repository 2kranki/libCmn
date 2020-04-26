// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   NodeProp_internal.h
 *	Generated 04/26/2020 17:31:56
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




#include        <NodeProp.h>
#include        <JsonIn.h>


#ifndef NODEPROP_INTERNAL_H
#define	NODEPROP_INTERNAL_H





#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct NodeProp_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint8_t         fObj;           // True == Object
    uint8_t         rsvd8;
    ASTR_DATA       *pExternal;     // Optional External Property Name
    ASTR_DATA       *pInit;         // Optional Initialization
    ASTR_DATA       *pInternal;     // Optional Internal Property Name
    ASTR_DATA       *pLong;         // Long Description
    ASTR_DATA       *pName;         // Property Name
    ASTR_DATA       *pShort;        // Short Description

};
#pragma pack(pop)

    extern
    struct NodeProp_class_data_s  NodeProp_ClassObj;

    extern
    const
    NODEPROP_VTBL         NodeProp_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODEPROP_SINGLETON
    NODEPROP_DATA *     NodeProp_getSingleton (
        void
    );

    bool            NodeProp_setSingleton (
     NODEPROP_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  NodeProp_getSuperVtbl (
        NODEPROP_DATA     *this
    );


    ERESULT         NodeProp_Assign (
        NODEPROP_DATA    *this,
        NODEPROP_DATA    *pOther
    );


    NODEPROP_DATA *       NodeProp_Copy (
        NODEPROP_DATA     *this
    );


    void            NodeProp_Dealloc (
        OBJ_ID          objId
    );


#ifdef  NODEPROP_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    NODEPROP_DATA *       NodeProp_ParseJsonObject (
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
    ERESULT         NodeProp_ParseJsonFields (
        JSONIN_DATA     *pParser,
        NODEPROP_DATA     *pObject
    );
#endif


    void *          NodeProp_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  NODEPROP_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = NodeProp_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeProp_ToJson (
        NODEPROP_DATA      *this
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
    ERESULT         NodeProp_ToJsonFields (
        NODEPROP_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			NodeProp_Validate (
        NODEPROP_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODEPROP_INTERNAL_H */

