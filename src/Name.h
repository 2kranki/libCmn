// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                      Name (Name) Header
//****************************************************************
/*
 * Program
 *			Name (Name)
 * Purpose
 *            This object provides a read-only name to be used in
 *          other containers.
 *
 * Remarks
 *    1.    OBJ_FLAG_USER1 is used internally and should not be
 *          used by any objects which inherit from this one.
 *
 * History
 *  02/07/2016 Generated
 *	01/11/2020 Regenerated
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
#include        <str.h>


#ifndef         NAME_H
#define         NAME_H


#define   NAME_JSON_SUPPORT 1
//#define   NAME_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Name_data_s	NAME_DATA;            // Inherits from OBJ
    typedef struct Name_class_data_s NAME_CLASS_DATA;   // Inherits from OBJ

    typedef struct Name_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Name_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NAME_DATA *);
    } NAME_VTBL;

    typedef struct Name_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Name_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NAME_DATA *);
    } NAME_CLASS_VTBL;


    typedef enum Name_type_e {
        NAME_TYPE_UNKNOWN=0,
        NAME_TYPE_INTEGER,          // int64_t
        NAME_TYPE_UTF8,             // UTF-8 NUL-terminated String
        NAME_TYPE_UTF8_CON,         // UTF-8 NUL-terminated String Constant
        NAME_TYPE_ASTR,             // AStr Object
    } NAME_TYPE;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NAME_SINGLETON
    NAME_DATA *     Name_Shared (
        void
    );

    void            Name_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Name object if successful, otherwise OBJ_NIL.
     */
    NAME_DATA *     Name_Alloc (
        void
    );
    
    
    OBJ_ID          Name_Class (
        void
    );
    
    
    NAME_DATA *     Name_New (
        void
    );
    
    
    NAME_DATA *     Name_NewFromJsonString (
        ASTR_DATA       *pString
    );


    NAME_DATA *     Name_NewFromJsonStringA (
        const
        char            *pString
    );


    uint32_t        Name_NewUnique (
        OBJ_ID          objId
    );


    NAME_DATA *     Name_NewInt (
        int64_t         value
    );


    NAME_DATA *     Name_NewAStr (
        ASTR_DATA       *pValue
    );


    /*!
     Create a new name from a UTF-8 character string.  The character string
     is copied into the new object and then released upon object deletion.
     @param     pValue  pointer to a NUL-terminated UTF-8 Character String.
     @return    If successful, a new name object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned object when you are done
                with it.
     */
    NAME_DATA *     Name_NewUTF8 (
        const
        char            *pValue
    );


    /*!
     Create a new name from a UTF-8 character constant.  Since it is a character
     constant the name will not be copied nor released.
     @param     pValue  pointer to a NUL-terminated UTF-8 Character Constant.
     @return    If successful, a new name object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned object when you are done
                with it.
     */
    NAME_DATA *     Name_NewUTF8Con (
        const
        char            *pValue
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        Name_getHash (
        NAME_DATA       *this
    );


    /*!
     Get the name value as an integer if it was defined as an int.
     @return    If successful, the integer value an AStr object which must be released,
     otherwise OBJ_NIL.
     */
    int64_t         Name_getInt (
        NAME_DATA       *this
    );


    /*!
     Get the name value as an AStr object.
     @return    If successful, an AStr object which must be released,
                 otherwise OBJ_NIL.
     */
    ASTR_DATA *     Name_getStr (
        NAME_DATA       *this
    );

    bool            Name_setStr (
        NAME_DATA       *this,
        ASTR_DATA       *pValue
    );


    /*!
     Get the name value as a UTF-8 string.
     @return    If successful, a UTF-8 string which must be freed
                using mem_Free(), otherwise NULL.
     */
    char *          Name_getUTF8 (
        NAME_DATA       *this
    );

    bool            Name_setUTF8 (
        NAME_DATA       *this,
        const
        char            *pValue
    );

    bool            Name_setUTF8Con (
        NAME_DATA       *this,
        const
        char            *pValue
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
        ERESULT eRc = Name_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another NAME object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Name_Assign (
        NAME_DATA       *this,
        NAME_DATA       *pOther
    );


    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Name_Compare (
        NAME_DATA       *this,
        NAME_DATA       *pOther
    );

   
    /*!
     Compare the name to the provided string.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Name_CompareA (
        NAME_DATA       *this,
        const
        char            *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        Name      *pCopy = Name_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a NAME object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NAME_DATA *     Name_Copy (
        NAME_DATA       *this
    );

    NAME_DATA *     Name_DeepCopy (
        NAME_DATA       *this
    );


    /*!
     Create a hash for the name value. The name value is always
     converted to a UTF-8 string and then that is hashed.
     @param     this    object pointer
     @return    Hash Code
     */
    uint32_t        Name_Hash (
        NAME_DATA       *this
    );


    NAME_DATA *     Name_Init (
        NAME_DATA       *this
    );


    ERESULT         Name_IsEnabled (
        NAME_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Name_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Name_ToJson(
        NAME_DATA   *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Name_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Name_ToDebugString (
        NAME_DATA       *this,
        int             indent
    );
    
    
    /*!
     Get the name value as a string object.
     @return    If successful, an AStr object which must be released,
                 otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object when you are done
                 with it.
     */
    ASTR_DATA *     Name_ToString (
        NAME_DATA       *this
    );


    /*!
     Get the name value as a UTF-8 string.
     @return    If successful, a UTF-8 string which must be freed
                using mem_Free(), otherwise NULL.
     @warning   Remember to free the returned string when you are done
                 with it.
     */
    char *          Name_ToUTF8 (
        NAME_DATA       *this
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* NAME_H */

