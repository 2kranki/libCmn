// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Symbol Table Entry (Sym) Header
//****************************************************************
/*
 * Program
 *			Symbol Table Entry (Sym)
 * Purpose
 *			This object provides a standardized Symbol Table Entry.
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
#include        <Node.h>
#include        <SrcLoc.h>


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


    // Primitive Types
    // Note: Signed Types are even, unsigned types are odd.
    /* The following enum was generated from:
     * "sym_prim.txt"
     * If you want to change this enum, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    typedef enum Sym_Prim_e {
        SYM_PRIM_UNKNOWN=0,
        SYM_PRIM_CHAR=1,
        SYM_PRIM_UCHAR=2,
        SYM_PRIM_HALF=3,
        SYM_PRIM_UHALF=4,
        SYM_PRIM_WORD=5,
        SYM_PRIM_UWORD=6,
        SYM_PRIM_DBLWORD=7,
        SYM_PRIM_UDBLWORD=8,
        SYM_PRIM_QUAD=9,
        SYM_PRIM_UQUAD=10,
        SYM_PRIM_VOID=11,
        SYM_PRIM_POINTER=12,
    } SYM_PRIMS;




    // Storage Type
    /*
     Note: Signed Types are even, unsigned types are odd.
     */
    typedef enum Sym_storage_types_e {
        SYM_STOR_TYPE_UNKNOWN=0,
        SYM_STOR_TYPE_PUBLIC=0x8000,
        SYM_STOR_TYPE_EXTERN=0x4000,
        // If not public and not extern,
        // then local/private.
        SYM_STOR_TYPE_STATIC=0x2000,

        // Storage Type Modifiers
        SYM_STOR_TYPE_CONSTANT=0x0800,
        SYM_STOR_TYPE_VOLATILE=0x0400,
        SYM_STOR_TYPE_RESTRICT=0x0200,

        //
        SYM_STOR_TYPE_AUTO=0x0080,
        SYM_STOR_TYPE_BSS=0x0040,
        SYM_STOR_TYPE_CODE=0x0020,
        SYM_STOR_TYPE_DATA=0x0010,
        SYM_STOR_TYPE_REGISTER=0x0008,
    } SYM_STORAGE_TYPES;



// WARNING: Objects that inherit from this one cannot expand entry.
//          Those fields must be added here.

#define SYM_NAME_MAXLEN 64
#define SYM_EXTRA2_MAXLEN 132
#pragma pack(push, 1)
    typedef struct sym_entry_s {
        char            nameA[SYM_NAME_MAXLEN+1]; // NUL-terminated name
        // Note: Abs or Rel may not be valid in initial passes.
        uint8_t         fFlgs1;             // Flags
        #define SYM_FLGS1_ACT       0x80        // Active Entry
        #define SYM_FLGS1_ABS       0x40        // Absolute Address
        #define SYM_FLGS1_REL       0x20        // Relocatable Address
        #define SYM_FLGS1_RSVD1     0x10        // Reserved Flag 1
        #define SYM_FLGS1_RSVD2     0x08        // Reserved Flag 2
        #define SYM_FLGS1_RSVD3     0x04        // Reserved Flag 3
        #define SYM_FLGS1_RSVD4     0x02        // Reserved Flag 4
        #define SYM_FLGS1_RSVD5     0x01        // Reserved Flag 5
        uint8_t         fFlgs2;             // Flags - Used as needed
        #define SYM_FLGS2_UNUSED1   0x10        // Unused Flag
        #define SYM_FLGS2_UNUSED2   0x10        // Unused Flag
        #define SYM_FLGS2_UNUSED3   0x10        // Unused Flag
        #define SYM_FLGS2_UNUSED4   0x10        // Unused Flag
        #define SYM_FLGS2_UNUSED5   0x08        // Unused Flag
        #define SYM_FLGS2_UNUSED6   0x04        // Unused Flag
        #define SYM_FLGS2_UNUSED7   0x02        // Unused Flag
        #define SYM_FLGS2_UNUSED8   0x01        // Unused Flag
        uint8_t         extra1;             // Used as needed
        SRCLOC          loc;                // Source Definition Location
        uint32_t        hash;               // Hash Code for name
        uint32_t        token;              // unique token for name
        int32_t         cls;                // User Defined Class
        int32_t         type;               // See SYM_TYPE
        uint32_t        strct;              // Struct Identifier (0 == none)
        uint32_t        storcls;            // Storage Class (See SYM_STORAGE_TYPES)
        uint32_t        section;            // Section/Segment Identifier (0 == none)
        uint32_t        addr;               // Address within Section/Segment
        int32_t         value;
        uint32_t        record;             // Input Record Number
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
        uint16_t        reg;                // Register Number (SYM_FLGS1_REGISTER)
        //                                  //  true  == Register Number Assignment
        //                                  //  false == Base Register
        uint32_t        disp;               // Displacement in Base Register
        uint8_t         extra2[SYM_EXTRA2_MAXLEN];  // Used as needed (Initialized
        //                                  // for U8VlArray)
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

    /*! Property: Entry is Active.
     This flag can be used to indicate that an entry has been defined
     which allows usage of a variable/label prior to it being defined.
     */
    bool            Sym_getActive (
        SYM_DATA        *this
    );

    bool            Sym_setActive (
        SYM_DATA        *this,
        bool            value
    );


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
    uint32_t        Sym_getDisp (
        SYM_DATA     *this
    );

    bool            Sym_setDisp (
        SYM_DATA        *this,
        uint32_t        value
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


    /*! Property: Extra Data 1
     1 byte of data that can be used as needed.
     */
    uint8_t         Sym_getExtra1 (
        SYM_DATA        *this
    );

    bool            Sym_setExtra1 (
        SYM_DATA        *this,
        uint8_t         value
    );


    /*! Property: Extra Data 2
     64 byte data that can be used as needed, it
     is initialized for use by U8VlArray optionally.
     */
    uint8_t *       Sym_getExtra2 (
        SYM_DATA        *this
    );


    /*! Property: Unused Flag1
     */
    bool            Sym_getFlg1 (
        SYM_DATA        *this
    );

    bool            Sym_setFlg1 (
        SYM_DATA        *this,
        bool            value
    );


    /*! Property: Unused Flag2
     */
    bool            Sym_getFlg2 (
        SYM_DATA        *this
    );

    bool            Sym_setFlg2 (
        SYM_DATA        *this,
        bool            value
    );


    /*! Property: Unused Flag3
     */
    bool            Sym_getFlg3 (
        SYM_DATA        *this
    );

    bool            Sym_setFlg3 (
        SYM_DATA        *this,
        bool            value
    );


    /*! Property: Unused Flag4
     */
    bool            Sym_getFlg4 (
        SYM_DATA        *this
    );

    bool            Sym_setFlg4 (
        SYM_DATA        *this,
        bool            value
    );


    /*! Property: Unused Flag5
     */
    bool            Sym_getFlg5 (
        SYM_DATA        *this
    );

    bool            Sym_setFlg5 (
        SYM_DATA        *this,
        bool            value
    );


    /*! Property: Unused Flag6
     */
    bool            Sym_getFlg6 (
        SYM_DATA        *this
    );

    bool            Sym_setFlg6 (
        SYM_DATA        *this,
        bool            value
    );


    /*! Property: Unused Flag7
     */
    bool            Sym_getFlg7 (
        SYM_DATA        *this
    );

    bool            Sym_setFlg7 (
        SYM_DATA        *this,
        bool            value
    );


    /*! Property: Unused Flag8
     */
    bool            Sym_getFlg8 (
        SYM_DATA        *this
    );

    bool            Sym_setFlg8 (
        SYM_DATA        *this,
        bool            value
    );


    /*! Property: Unused Flag9
     */
    bool            Sym_getFlg9 (
        SYM_DATA        *this
    );

    bool            Sym_setFlg9 (
        SYM_DATA        *this,
        bool            value
    );


    /*! Property: Unused Flag10
     */
    bool            Sym_getFlg10 (
        SYM_DATA        *this
    );

    bool            Sym_setFlg10 (
        SYM_DATA        *this,
        bool            value
    );


    /*! Property: Unused Flag11
     */
    bool            Sym_getFlg11 (
        SYM_DATA        *this
    );

    bool            Sym_setFlg11 (
        SYM_DATA        *this,
        bool            value
    );


    /*! Property: Unused Flag12
     */
    bool            Sym_getFlg12 (
        SYM_DATA        *this
    );

    bool            Sym_setFlg12 (
        SYM_DATA        *this,
        bool            value
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


    SRCLOC *        Sym_getLoc(
        SYM_DATA        *this
    );

    bool            Sym_setLoc (
        SYM_DATA        *this,
        const
        SRCLOC          *pValue
    );


    const
    char *          Sym_getNameA (
        SYM_DATA        *this
    );


    /*! Property: Node
     */
    NODE_DATA *     Sym_getNode (
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


    /*! Property: Inpu Record Numer where symbol
     is defined.
     */
    uint32_t        Sym_getRecord (
        SYM_DATA        *this
    );

    bool            Sym_setRecord (
        SYM_DATA        *this,
        uint32_t        value
    );


    /*! Property: Base Register/Register
     */
    uint16_t        Sym_getReg (
        SYM_DATA     *this
    );

    bool            Sym_setReg (
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


    /*! Property: Storage Class
     */
    uint32_t        Sym_getStorageClass (
        SYM_DATA        *this
    );

    bool            Sym_setStorageClass (
        SYM_DATA        *this,
        uint32_t        value
    );


    /*! Property: Structure Identifier
     */
    uint32_t        Sym_getStructID (
        SYM_DATA        *this
    );

    bool            Sym_setStructID (
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
        SYM_DATA        *this,
        SYM_DATA        *pOther
    );

    int             Sym_CompareA (
        SYM_DATA        *this,
        int32_t         cls,
        const
        char            *pNameA
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
    SYM_DATA *      Sym_Copy (
        SYM_DATA        *this
    );


    uint32_t        Sym_Hash(
        SYM_DATA        *this
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
        SYM_DATA        *this
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
    ASTR_DATA *     Sym_ToDebugString (
        SYM_DATA        *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SYM_H */

