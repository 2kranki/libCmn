// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Primitive Value (Value) Header
//****************************************************************
/*
 * Program
 *			Primitive Value (Value)
 * Purpose
 *          This object provides a way to create an object from
 *          most primitive data including just raw memory.
 *          Since this is primitive data, it can be converted
 *          to/from Json and ported across systems with certain
 *          caveats.
 *
 * Remarks
 *    1.    If you are storing raw memory and that object is to be
 *          saved to JSON. It should not contain any pointers since
 *          those will probably be meaningless when the data is
 *          restored.  Also, you may be faced with little-endian
 *          vs big-endian translation which this object does not
 *          do.
 *
 * History
 *  08/26/2017 Generated
 *	12/31/2019 Regenerated
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


#ifndef         VALUE_H
#define         VALUE_H


#define   VALUE_JSON_SUPPORT 1
//#define   VALUE_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Value_data_s	VALUE_DATA;            // Inherits from OBJ
    typedef struct Value_class_data_s VALUE_CLASS_DATA;   // Inherits from OBJ

    typedef struct Value_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Value_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(VALUE_DATA *);
    } VALUE_VTBL;

    typedef struct Value_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Value_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(VALUE_DATA *);
    } VALUE_CLASS_VTBL;


    typedef enum Value_type_e {
        VALUE_TYPE_UNKNOWN=0,
        VALUE_TYPE_DOUBLE,          // 64-bit Float
        VALUE_TYPE_INT8,            // int8_t
        VALUE_TYPE_INT16,           // int16_t
        VALUE_TYPE_INT32,           // int32_t
        VALUE_TYPE_INT64,           // int64_t
        VALUE_TYPE_UINT8,           // int8_t
        VALUE_TYPE_UINT16,          // int16_t
        VALUE_TYPE_UINT32,          // int32_t
        VALUE_TYPE_UINT64,          // int64_t
        VALUE_TYPE_OBJECT,          // Any object that supports "ToJson" method
        VALUE_TYPE_DATA,            // Any data (pointer and length) (pointer and length
        //                          // must be valid for life of object)
        VALUE_TYPE_DATA_FREE,       // Any data (pointer and length) which will be freed
        //                          // using mem_Free() when no longer needed (pointer
        //                          // and length must be valid for life of object)
        VALUE_TYPE_HIGHEST
    } VALUE_TYPE;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  VALUE_SINGLETON
    VALUE_DATA *    Value_Shared (
        void
    );

    void            Value_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Value object if successful, otherwise OBJ_NIL.
     */
    VALUE_DATA *    Value_Alloc (
        void
    );
    
    
    OBJ_ID          Value_Class (
        void
    );
    
    
    VALUE_DATA *    Value_New (
        void
    );
    
    
    /*!
     Create a value object where the data will not be
     controlled by this object.
     */
    VALUE_DATA *    Value_NewData (
        int32_t         length,
        uint8_t         *pData
    );

    /*!
     Create a value object where the data will be freed upon
     release of the object.
     */
    VALUE_DATA *    Value_NewDataFree (
        int32_t         length,
        uint8_t         *pData
    );

    VALUE_DATA *    Value_NewDouble (
        double          value
    );

    VALUE_DATA *    Value_NewI8 (
        int8_t          value
    );

    VALUE_DATA *    Value_NewI16 (
        int16_t         value
    );

    VALUE_DATA *    Value_NewI32 (
        int32_t         value
    );

    VALUE_DATA *    Value_NewI64 (
        int64_t         value
    );

    VALUE_DATA *    Value_NewObject (
        OBJ_DATA        *pValue
    );

    VALUE_DATA *    Value_NewU8 (
        uint8_t         value
    );

    VALUE_DATA *    Value_NewU16 (
        uint16_t        value
    );

    VALUE_DATA *    Value_NewU32 (
        uint32_t        value
    );

    VALUE_DATA *    Value_NewU64 (
        uint64_t        value
    );


    VALUE_DATA *    Value_NewFromJsonString (
        ASTR_DATA       *pString
    );

    VALUE_DATA *    Value_NewFromJsonStringA (
        const
        char            *pString
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint8_t *       Value_getData (
        VALUE_DATA      *this
    );

    uint32_t        Value_getDataLen (
        VALUE_DATA      *this
    );

    bool            Value_setData (
        VALUE_DATA      *this,
        uint32_t        length,
        void            *pValue
    );

    bool            Value_setDataFree (
        VALUE_DATA      *this,
        uint32_t        length,
        void            *pValue
    );


    double          Value_getDouble (
        VALUE_DATA      *this
    );

    bool            Value_setDouble (
        VALUE_DATA      *this,
        double          value
    );


    int8_t          Value_getI8 (
        VALUE_DATA      *this
    );

    bool            Value_setI8 (
        VALUE_DATA      *this,
        int8_t          value
    );


    int16_t         Value_getI16 (
        VALUE_DATA      *this
    );

    bool            Value_setI16 (
        VALUE_DATA      *this,
        int16_t         value
    );


    int32_t         Value_getI32 (
        VALUE_DATA      *this
    );

    bool            Value_setI32 (
        VALUE_DATA      *this,
        int32_t         value
    );


    int64_t         Value_getI64 (
        VALUE_DATA      *this
    );

    bool            Value_setI64 (
        VALUE_DATA      *this,
        int64_t         value
    );


    /*! Property: 16-Bit Miscellaneous property which can be used for
                    whatever is necessary.
     */
    uint16_t        Value_getMisc16 (
        VALUE_DATA      *this
    );

    bool            Value_setMisc16 (
        VALUE_DATA      *this,
        uint16_t        value
    );


    OBJ_DATA *      Value_getObject (
        VALUE_DATA      *this
    );

    bool            Value_setObject (
        VALUE_DATA      *this,
        OBJ_DATA        *pValue
    );


    uint16_t        Value_getType (
        VALUE_DATA      *this
    );


    uint8_t         Value_getU8 (
        VALUE_DATA      *this
    );

    bool            Value_setU8 (
        VALUE_DATA      *this,
        uint8_t         value
    );


    uint16_t        Value_getU16 (
        VALUE_DATA      *this
    );

    bool            Value_setU16 (
        VALUE_DATA      *this,
        uint16_t        value
    );


    uint32_t        Value_getU32 (
        VALUE_DATA      *this
    );

    bool            Value_setU32 (
        VALUE_DATA      *this,
        uint32_t        value
    );


    uint64_t        Value_getU64 (
        VALUE_DATA      *this
    );

    bool            Value_setU64 (
        VALUE_DATA      *this,
        uint64_t        value
    );


    uint32_t        Value_getUser (
        VALUE_DATA      *this
    );

    bool            Value_setUser (
        VALUE_DATA      *this,
        uint32_t        value
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = Value_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another VALUE object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Value_Assign (
        VALUE_DATA      *this,
        VALUE_DATA      *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        Value      *pCopy = Value_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a VALUE object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    VALUE_DATA *   Value_Copy (
        VALUE_DATA      *this
    );

   
    VALUE_DATA *   Value_Init (
        VALUE_DATA      *this
    );


    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Value_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Value_ToJson(
        VALUE_DATA   *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Value_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Value_ToDebugString (
        VALUE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* VALUE_H */

