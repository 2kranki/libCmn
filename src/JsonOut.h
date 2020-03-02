// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          JSON Object Output Support (JsonOut) Header
//****************************************************************
/*
 * Program
 *			JSON Object Output Support (JsonOut)
 * Purpose
 *			This object provides a standardized way of generating
 *			certain field types for JSON.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	08/27/2017 Generated
 *	01/25/2020 Regenerated
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


#ifndef         JSONOUT_H
#define         JSONOUT_H


//#define   JSONOUT_IS_CONSTANT      1
//#define   JSONOUT_JSON_SUPPORT     1
//#define   JSONOUT_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct JsonOut_data_s	JSONOUT_DATA;            // Inherits from OBJ
    typedef struct JsonOut_class_data_s JSONOUT_CLASS_DATA;   // Inherits from OBJ

    typedef struct JsonOut_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in JsonOut_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(JSONOUT_DATA *);
    } JSONOUT_VTBL;

    typedef struct JsonOut_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in JsonOut_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(JSONOUT_DATA *);
    } JSONOUT_CLASS_VTBL;


    typedef struct JsonOut_Flag1_s {
        uint8_t         flag;
        const
        char            *pName;
    } JSONOUT_FLAG1;

    typedef struct JsonOut_Flag2_s {
        uint16_t        flag;
        const
        char            *pName;
    } JSONOUT_FLAG2;

    typedef struct JsonOut_Flag4_s {
        uint32_t        flag;
        const
        char            *pName;
    } JSONOUT_FLAG4;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  JSONOUT_SINGLETON
    JSONOUT_DATA *     JsonOut_Shared (
        void
    );

    void            JsonOut_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to JsonOut object if successful, otherwise OBJ_NIL.
     */
    JSONOUT_DATA *  JsonOut_Alloc (
        void
    );
    
    
    OBJ_ID          JsonOut_Class (
        void
    );
    
    
    void            JsonOut_Append_i32 (
        const
        char            *pNameA,
        int32_t         num,
        ASTR_DATA       *pStr
    );

    void            JsonOut_Append_i32_array (
        const
        char            *pNameA,
        uint32_t        num,            // Number of entries
        const
        int32_t         *pNum,          // First Entry Pointer
        ASTR_DATA       *pStr
    );


    void            JsonOut_Append_i64 (
        const
        char            *pNameA,
        int64_t         num,
        ASTR_DATA       *pStr
    );


    /*!
     Attempt to append a object's json string to an already existing string
     with a given name if possible.
     @param     pNameA  Optional Name for the object (If not present, then
                        just the object hash appended.)
     @param     pObj    non-null object pointer
     @param     pStr    string to be added on to
     */
    void            JsonOut_Append_Object (
        const
        char            *pNameA,
        OBJ_ID          pObj,
        ASTR_DATA       *pStr
    );


    /*!
     Attempt to append a string's json string to an already existing string
     with a given name if possible. This is normally parsed with
     JsonIn_FindStringNodeInHashA()
     @param     pNameA  Name for the object
     @param     pObj    non-null string pointer
     @param     pStr    string to be added on to
     */
    void            JsonOut_Append_String (
        const
        char            *pNameA,
        ASTR_DATA       *pObj,
        ASTR_DATA       *pStr
    );

    void            JsonOut_Append_StringA (
        const
        char            *pNameA,
        const
        char            *pObjA,
        ASTR_DATA       *pStr
    );


    void            JsonOut_Append_u8 (
        const
        char            *pNameA,
        uint8_t         num,
        ASTR_DATA       *pStr
    );

    void            JsonOut_Append_u8_array (
        const
        char            *pNameA,
        uint32_t        num,            // Number of entries
        const
        uint8_t         *pNum,          // First Entry Pointer
        ASTR_DATA       *pStr
    );


    void            JsonOut_Append_u16 (
        const
        char            *pNameA,
        uint16_t        num,
        ASTR_DATA       *pStr
    );


    void            JsonOut_Append_u32 (
        const
        char            *pNameA,
        uint32_t        num,
        ASTR_DATA       *pStr
    );


    void            JsonOut_Append_utf8 (
        const
        char            *pNameA,
        const
        char            *pStrA,                 // UTF-8 String to be saved
        ASTR_DATA       *pStr
    );

    JSONOUT_DATA *  JsonOut_New (
        void
    );
    
    
#ifdef  JSONOUT_JSON_SUPPORT
    JSONOUT_DATA *   JsonOut_NewFromJsonString(
        ASTR_DATA       *pString
    );

    JSONOUT_DATA *   JsonOut_NewFromJsonStringA(
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         JsonOut_Disable (
        JSONOUT_DATA    *this
    );


    ERESULT         JsonOut_Enable (
        JSONOUT_DATA	*this
    );

   
    JSONOUT_DATA *  JsonOut_Init (
        JSONOUT_DATA    *this
    );


    ERESULT         JsonOut_IsEnabled (
        JSONOUT_DATA	*this
    );
    
 
#ifdef  JSONOUT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = JsonOut_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     JsonOut_ToJson(
        JSONOUT_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = JsonOut_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    JsonOut_ToDebugString (
        JSONOUT_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* JSONOUT_H */

