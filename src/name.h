// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Name (name) Header
//****************************************************************
/*
 * Program
 *			Separate name (name)
 * Purpose
 *			This object provides a read-only name to be used in 
 *          other containers.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	02/07/2016 Generated
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
#include        <str.h>


#ifndef         NAME_H
#define         NAME_H 1



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef enum name_type_e {
        NAME_TYPE_UNKNOWN=0,
        NAME_TYPE_INTEGER,          // int64_t
        NAME_TYPE_PTR,              // void *
        NAME_TYPE_UTF8,             // UTF-8 NUL-terminated String
        NAME_TYPE_UTF8_CON,         // UTF-8 NUL-terminated String Constant
        NAME_TYPE_WSTR,             // WStr Object
    } NAME_TYPE;
    
    
    typedef struct name_data_s	NAME_DATA;

    typedef struct name_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        // Properties:
        // Methods:
    } NAME_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    NAME_DATA *     name_Alloc(
        void
    );
    
    
    NAME_DATA *     name_NewFromJSONString(
        ASTR_DATA       *pString
    );
    
    NAME_DATA *     name_NewFromJSONStringA(
        const
        char            *pString
    );
    
    
    uint32_t        name_NewUnique(
        OBJ_ID          objId
    );
    
    
    NAME_DATA *     name_NewInt(
        int64_t         value
    );
    
    NAME_DATA *     name_NewPtr(
        const
        void            *pValue
    );
    
    NAME_DATA *     name_NewStrA(
        ASTR_DATA       *pValue
    );
    
    NAME_DATA *     name_NewStrW(
        WSTR_DATA       *pValue
    );
    
    NAME_DATA *     name_NewUTF8(
        const
        char            *pValue
    );
    
    NAME_DATA *     name_NewUTF8Con(
        const
        char            *pValue
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     Get the name value if it is a ptr.
     @return    If successful, void ptr, otherwise NULL.
     */
    const
    void *          name_getPtr(
        NAME_DATA       *this
    );
    
    
    /*!
     Get the name value as an AStr object.
     @return    If successful, an AStr object which must be released,
                 otherwise OBJ_NIL.
     */
    ASTR_DATA *     name_getStrA(
        NAME_DATA       *this
    );
    
    
    /*!
     Get the name value as a WStr object.
     @return    If successful, an WStr object which must be released,
                 otherwise OBJ_NIL.
     */
    WSTR_DATA *     name_getStrW(
        NAME_DATA       *this
    );
    
    
    /*!
     Get the name value as a UTF-8 string.
     @return    If successful, a UTF-8 string which must be freed
                using mem_Free(), otherwise NULL.
     */
    char *          name_getUTF8(
        NAME_DATA       *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         name_Assign(
        NAME_DATA       *this,
        NAME_DATA       *pOther
    );
    
    
    ERESULT         name_Compare(
        NAME_DATA       *this,
        NAME_DATA       *pOther
    );
    
    /*!
     Compare the name to the provided string.
     @return    ERESULT_SUCCESS_EQUAL if name == other
                ERESULT_SUCCESS_LESS_THAN if name < other
                ERESULT_SUCCESS_GREATER_THAN if name > other
     */
    ERESULT         name_CompareA(
        NAME_DATA       *this,
        const
        char            *pOther
    );
    
    ERESULT         name_CompareW(
        NAME_DATA       *this,
        const
        int32_t         *pOther
    );
    
    
    NAME_DATA *     name_Copy(
        NAME_DATA       *this
    );
    
    
    /*!
     Create a hash for the name value. The name value is always
     converted to a UTF-8 string and then that is hashed.
     @return    Hash Code
     */
    uint32_t        name_Hash(
        NAME_DATA       *this
    );
    
    
    NAME_DATA *     name_InitInt(
        NAME_DATA       *this,
        int64_t         value
    );


    NAME_DATA *   name_InitPtr(
        NAME_DATA       *this,
        const
        void            *pValue
    );
    
    
    NAME_DATA *   name_InitStrA(
        NAME_DATA       *this,
        ASTR_DATA       *pValue
    );
    
    
    NAME_DATA *   name_InitStrW(
        NAME_DATA       *this,
        WSTR_DATA       *pValue
    );
    
    
    NAME_DATA *   name_InitUTF8(
        NAME_DATA       *this,
        const
        char            *pValue
    );
    
    
    NAME_DATA *   name_InitUTF8Con(
        NAME_DATA       *this,
        const
        char            *pValue
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = name_ToDebugString(this,4);
     @endcode
     @param     this    NAME object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object when you are done
                with it.
     */
    ASTR_DATA *     name_ToDebugString(
        NAME_DATA       *this,
        int             indent
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it in JSON format.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     name_ToJSON(
        NAME_DATA       *this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return    If successful, an AStr object which must be released,
                 otherwise OBJ_NIL.
     */
    ASTR_DATA *     name_ToString(
        NAME_DATA       *this
    );
    
    
    /*!
     Get the name value as a UTF-8 string.
     @return    If successful, a UTF-8 string which must be freed
                using mem_Free(), otherwise NULL.
     */
    char *          name_ToUTF8(
        NAME_DATA       *this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NAME_H */

