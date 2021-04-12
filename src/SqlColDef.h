// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Separate SqlColDef (SqlColDef) Header
//****************************************************************
/*
 * Program
 *			Separate SqlColDef (SqlColDef)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate SqlColDef to run things without complications
 *          of interfering with the main SqlColDef. A SqlColDef may be 
 *          called a SqlColDef on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/26/2020 Generated
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


#ifndef         SQLCOLDEF_H
#define         SQLCOLDEF_H


//#define   SQLCOLDEF_IS_IMMUTABLE     1
#define   SQLCOLDEF_JSON_SUPPORT     1
//#define   SQLCOLDEF_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SqlColDef_data_s	SQLCOLDEF_DATA;            // Inherits from OBJ
    typedef struct SqlColDef_class_data_s SQLCOLDEF_CLASS_DATA;   // Inherits from OBJ

    typedef struct SqlColDef_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlColDef_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLCOLDEF_DATA *);
    } SQLCOLDEF_VTBL;

    typedef struct SqlColDef_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlColDef_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLCOLDEF_DATA *);
    } SQLCOLDEF_CLASS_VTBL;


    typedef enum SqlColDef_types_e  {
        SQLCOLDEF_TYPE_UNDEFINED=0,
        SQLCOLDEF_TYPE_BLOB,
        SQLCOLDEF_TYPE_BOOL,
        SQLCOLDEF_TYPE_CHAR,
        SQLCOLDEF_TYPE_DATE,
        SQLCOLDEF_TYPE_FILLER,
        SQLCOLDEF_TYPE_INTEGER,
        SQLCOLDEF_TYPE_NUMBER,
        SQLCOLDEF_TYPE_REAL,
        SQLCOLDEF_TYPE_TEXT,
        SQLCOLDEF_TYPE_VARCHAR
    } SQLCOLDEF_TYPES;


    typedef enum SqlCol_flags_e  {
        SQLCOLDEF_FLAG_UNIQUE=0x0001,
        SQLCOLDEF_FLAG_NOT_NULL=0x0002,
        SQLCOLDEF_FLAG_AUTO_INC=0x0004,
        SQLCOLDEF_FLAG_PRIM_KEY=0x0008,
        SQLCOLDEF_FLAG_NO_TRAIL=0x0010,     // Remove Trailing White Space
    } SQLCOL_FLAGS;


    // This structure is designed so that this object can be initialized
    // from it using the FromStruct() method.
    typedef struct SqlColDef_Struct_s {
        const
        char                *pName;             // (Required)
        const
        char                *pDescription;      // (Required)
        const
        char                type;               // see SQLCOLDEF_TYPES
        uint16_t            keySequence;
        //                          0 == not a key column
        //                          1+ == column is part of the key in order
        //                                specified by this number
        int8_t              decimalPlaces;      // for SQLCOLDEF_TYPE_REAL
        uint8_t             seq;                // Column Sequence number for CSV
        //                                      // or other formats.
        int32_t             length;
        //                          For SQLCOLDEF_TYPE_TEXT and SQLCOLDEF_TYPE_VARCHAR,
        //                          a length of 0 just means that it is variable.
        int32_t             minimumLength;      // For use with TEXT, CHAR or VARCHAR
        uint32_t            flags;              // see SQLCOL_FLAGS
        char                *pDefaultValue;     // Value to be placed inside DEFAULT( )
        //                                      // (Optional)
        char                *pCheckExpression;  // Value to be placed inside CHECK( )
        //                                      // (Optional)
    } SQLCOLDEF_STRUCT;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SQLCOLDEF_SINGLETON
    SQLCOLDEF_DATA * SqlColDef_Shared (
        void
    );

    void            SqlColDef_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SqlColDef object if successful, otherwise OBJ_NIL.
     */
    SQLCOLDEF_DATA * SqlColDef_Alloc (
        void
    );
    
    
    OBJ_ID          SqlColDef_Class (
        void
    );
    
    
    SQLCOLDEF_DATA * SqlColDef_New (
        void
    );
    
    
#ifdef  SQLCOLDEF_JSON_SUPPORT
    SQLCOLDEF_DATA * SqlColDef_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SQLCOLDEF_DATA * SqlColDef_NewFromJsonStringA (
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

    ERESULT         SqlColDef_Disable (
        SQLCOLDEF_DATA  *this
    );


    ERESULT         SqlColDef_Enable (
        SQLCOLDEF_DATA	*this
    );

   
    SQLCOLDEF_DATA * SqlColDef_Init (
        SQLCOLDEF_DATA  *this
    );


    ERESULT         SqlColDef_IsEnabled (
        SQLCOLDEF_DATA	*this
    );
    
 
#ifdef  SQLCOLDEF_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SqlColDef_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlColDef_ToJson (
        SQLCOLDEF_DATA  *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SqlColDef_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlColDef_ToDebugString (
        SQLCOLDEF_DATA  *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SQLCOLDEF_H */

