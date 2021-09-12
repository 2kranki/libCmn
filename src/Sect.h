// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Section Table Entry (Sect) Header
//****************************************************************
/*
 * Program
 *          Section Table Entry (Sect)
 * Purpose
 *          This object provides support for a program section
 *          or segment. It contains all the fields necessary
 *          for use in assemblers, compilers, dis-assemblers or
 *          linkers.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  12/27/2020 Generated
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
#include        <Syms.h>
#include        <u8Array.h>


#ifndef         SECT_H
#define         SECT_H


//#define   SECT_IS_IMMUTABLE     1
#define   SECT_JSON_SUPPORT       1
//#define   SECT_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Sect_data_s  SECT_DATA;            // Inherits from OBJ
    typedef struct Sect_class_data_s SECT_CLASS_DATA;   // Inherits from OBJ

    typedef struct Sect_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Sect_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SECT_DATA *);
    } SECT_VTBL;

    typedef struct Sect_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Sect_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SECT_DATA *);
    } SECT_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SECT_SINGLETON
    SECT_DATA *     Sect_Shared (
        void
    );

    void            Sect_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Sect object if successful, otherwise OBJ_NIL.
     */
    SECT_DATA *     Sect_Alloc (
        void
    );
    
    
    OBJ_ID          Sect_Class (
        void
    );
    
    
    SECT_DATA *     Sect_New (
        void
    );
    
    
    SECT_DATA *     Sect_NewFromDataA (
        char            ident,
        char            type,
        uint32_t        addr,
        uint32_t        offset,
        uint32_t        len,
        const
        char            *pNameA
    );


#ifdef  SECT_JSON_SUPPORT
    SECT_DATA *   Sect_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SECT_DATA *   Sect_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


    ASTR_DATA *     Sect_ToStringTitle (
        int             indent
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        Sect_getAddr (
        SECT_DATA       *this
    );

    bool            Sect_setAddr (
        SECT_DATA       *this,
        uint32_t        value
    );


    /*! @property   Big Endian Flag
     If true, then U16, U32, etc are stored in large/big endian order.
     Otherwise, they are stored in little endian order.
     */
    bool            Sect_getBigEndian(
        SECT_DATA       *this
    );

    bool            Sect_setBigEndian(
        SECT_DATA       *this,
        bool            value
    );


    char            Sect_getIdent (
        SECT_DATA       *this
    );

    bool            Sect_setIdent (
        SECT_DATA       *this,
        char            value
    );


    uint32_t        Sect_getLen (
        SECT_DATA       *this
    );

    bool            Sect_setLen (
        SECT_DATA       *this,
        uint32_t        value
    );


    ASTR_DATA *     Sect_getName (
        SECT_DATA       *this
    );

    bool            Sect_setName (
        SECT_DATA       *this,
        ASTR_DATA       *pValue
    );


    uint32_t        Sect_getOffset (
        SECT_DATA       *this
    );

    bool            Sect_setOffset (
        SECT_DATA       *this,
        uint32_t        value
    );


    uint32_t        Sect_getSection (
        SECT_DATA       *this
    );

    bool            Sect_setSection (
        SECT_DATA       *this,
        uint32_t        value
    );


    char            Sect_getType (
        SECT_DATA       *this
    );

    bool            Sect_setType (
        SECT_DATA       *this,
        char            value
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Append the given data to the end of the array breaking it up
     into multiple bytes using the Endian Property Setting.
     @return    If successful, ERESULT_SUCCESS, otherwise an
                ERESULT_* error.
     */
    ERESULT         Sect_AppendU8 (
        SECT_DATA       *this,
        uint8_t         data
    );

    ERESULT         Sect_AppendU16 (
        SECT_DATA       *this,
        uint16_t        data
    );

    ERESULT         Sect_AppendU24 (
        SECT_DATA       *this,
        uint32_t        data
    );

    ERESULT         Sect_AppendU32 (
        SECT_DATA       *this,
        uint32_t        data
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = Sect_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another SECT object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Sect_Assign (
        SECT_DATA       *this,
        SECT_DATA       *pOther
    );


    /*!
     Compare the two provided objects using their ident's.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Sect_Compare (
        SECT_DATA       *this,
        SECT_DATA       *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        Sect      *pCopy = Sect_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a SECT object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SECT_DATA *     Sect_Copy (
        SECT_DATA       *this
    );


    SECT_DATA *     Sect_Init (
        SECT_DATA       *this
    );


    /*!
     Create the key for this object.
     @param     this    object pointer
     @return    If successful, an AStr object which can be
                use in an index; otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Sect_Key (
        SECT_DATA       *this
    );


#ifdef  SECT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Sect_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Sect_ToJson (
        SECT_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Sect_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Sect_ToDebugString (
        SECT_DATA     *this,
        int             indent
    );
    
    
    ASTR_DATA *     Sect_ToString (
        SECT_DATA       *this,
        int             indent
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* SECT_H */

