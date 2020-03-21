// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SYM Console Transmit Task (Sym) Header
//****************************************************************
/*
 * Program
 *			Separate Sym (Sym)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate Sym to run things without complications
 *          of interfering with the main Sym. A Sym may be 
 *          called a Sym on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	02/22/2020 Generated
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


#ifndef         SYM_H
#define         SYM_H


//#define   SYM_IS_IMMUTABLE     1
#define   SYM_JSON_SUPPORT     1
//#define   SYM_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Sym_data_s	SYM_DATA;            // Inherits from OBJ
    typedef struct Sym_class_data_s SYM_CLASS_DATA;   // Inherits from OBJ

    typedef struct Sym_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Sym_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SYM_DATA *);
    } SYM_VTBL;

    typedef struct Sym_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Sym_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SYM_DATA *);
    } SYM_CLASS_VTBL;


// WARNING: Objects that inherit from this one cannot expand entry.
//          Those fields must be added here.

#pragma pack(push, 1)
    typedef struct sym_entry_s {
        char            name[65];           // NUL-terminated name
        // Note: Abs or Rel may not be valid in initial passes.
        uint8_t         fAbs;               // Absolute value
        uint8_t         fRel;               // Relocatable value
        uint8_t         rsvd8;
        uint32_t        hash;               // Hash Code for name
        uint32_t        token;              // unique token for name
        int32_t         cls;                // User Defined Class
        int32_t         type;               // See SYM_TYPE
        uint32_t        section;            // Section/Struct Identifier (0 == none)
        uint16_t        prim;               // See SYM_PRIMITIVE;
        uint16_t        len;                // Data Length in Bytes
        uint16_t        dup;                // Duplication Factor
        uint16_t        align;              // Required Storage Alignment
        //                                  //  0 == None (same as 1)
        //                                  //  1 == Byte Boundary
        //                                  //  2 == 16 Bit Boundary
        //                                  //  4 == 32 Bit Boundary
        //                                  //  8 == 64 Bit Boundary
        //                                  // 16 == 128 Bit Boundary
        uint16_t        scale;              // Binary or Decimal Shift Amount
        uint16_t        rsvd16;
        int32_t         value;
        uint8_t         extra[64];          // Used as needed
    } SYM_ENTRY;
#pragma pack(pop)




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SYM_SINGLETON
    SYM_DATA *     Sym_Shared (
        void
    );

    void           Sym_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Sym object if successful, otherwise OBJ_NIL.
     */
    SYM_DATA *      Sym_Alloc (
        void
    );
    
    
    OBJ_ID          Sym_Class (
        void
    );
    
    
    SYM_DATA *      Sym_New (
        void
    );
    
    
    SYM_DATA *      Sym_NewA(
        int32_t         cls,
        const
        char            *pNameA
    );


#ifdef  SYM_JSON_SUPPORT
    SYM_DATA *      Sym_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SYM_DATA *      Sym_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: Value is Absolute
     */
    bool            Sym_getAbs (
        SYM_DATA        *this
    );

    bool            Sym_setAbs (
        SYM_DATA        *this,
        bool            value
    );


    /*! Property: Alignment (0,2,4,8,16,...)
     */
    uint16_t        Sym_getAlign (
        SYM_DATA     *this
    );

    bool            Sym_setAlign (
        SYM_DATA        *this,
        uint16_t        value
    );


    /*! Property: Class
     */
    int32_t         Sym_getClass (
        SYM_DATA        *this
    );

    bool            Sym_setClass (
        SYM_DATA        *this,
        int32_t         value
    );


    /*! Property: Duplication Factor
     */
    uint16_t        Sym_getDup (
        SYM_DATA     *this
    );

    bool            Sym_setDup (
        SYM_DATA        *this,
        uint16_t        value
    );


    /*! Property: Extra Data
     64 byte data that can be used as needed, it
     is initialized for use by U8VlArray optionally.
     */
    uint8_t *       Sym_getExtra (
        SYM_DATA        *this
    );


    /*! Property: Hash
     */
    uint32_t        Sym_getHash (
        SYM_DATA        *this
    );

    bool            Sym_setHash (
        SYM_DATA        *this,
        uint32_t        value
    );


    /*! Property: Length
     */
    uint16_t        Sym_getLen (
        SYM_DATA     *this
    );

    bool            Sym_setLen (
        SYM_DATA        *this,
        uint16_t        value
    );


    const
    char *          Sym_getNameA (
        SYM_DATA        *this
    );


    /*! Property: Primary
     */
    uint16_t        Sym_getPrim (
        SYM_DATA     *this
    );

    bool            Sym_setPrim (
        SYM_DATA        *this,
        uint16_t        value
    );


    /*! Property: Value is Relocatable
     */
    bool            Sym_getRel (
        SYM_DATA        *this
    );

    bool            Sym_setRel (
        SYM_DATA        *this,
        bool            value
    );


    /*! Property: Scale
     */
    uint16_t        Sym_getScale (
        SYM_DATA     *this
    );

    bool            Sym_setScale (
        SYM_DATA        *this,
        uint16_t        value
    );


    /*! Property: Section
     */
    uint32_t        Sym_getSection (
        SYM_DATA        *this
    );

    bool            Sym_setSection (
        SYM_DATA        *this,
        uint32_t        value
    );


    /*! Property: Token
     */
    uint32_t        Sym_getToken (
        SYM_DATA        *this
    );

    bool            Sym_setToken (
        SYM_DATA        *this,
        uint32_t        value
    );


    /*! Property: Type
     */
    int32_t         Sym_getType (
        SYM_DATA        *this
    );

    bool            Sym_setType (
        SYM_DATA        *this,
        int32_t         value
    );


    /*! Property: Value
     */
    int32_t         Sym_getValue (
        SYM_DATA        *this
    );

    bool            Sym_setValue (
        SYM_DATA        *this,
        int32_t         value
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
        ERESULT eRc = Sym_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another SYM object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Sym_Assign (
        SYM_DATA        *this,
        SYM_DATA        *pOther
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         Sym_Compare (
        SYM_DATA     *this,
        SYM_DATA     *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        Sym      *pCopy = Sym_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a SYM object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SYM_DATA *     Sym_Copy (
        SYM_DATA       *this
    );


    SYM_DATA *      Sym_Init (
        SYM_DATA        *this
    );


#ifdef  SYM_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Sym_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Sym_ToJson (
        SYM_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Sym_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Sym_ToDebugString (
        SYM_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SYM_H */

