// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Sym.c
 *	Generated 02/22/2020 20:18:12
 *
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include        <Sym_internal.h>
#include        <Misc.h>
#include        <str.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    
    /* The following tables were generated from:
     * "sym_c_prim.txt"
     * If you want to change this enum, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // This table is in enum order and provides
    // the index + 1 into the Sym_C_Prim_entries
    // table. 0 means no enum entry.
    const
    uint16_t    Sym_C_Prim_index[41] = {
        37, 5, 1, 2, 13, 14, 27, 28,
        15, 16, 23, 24, 38, 39, 6, 7,
        17, 18, 29, 30, 8, 11, 19, 22,
        31, 34, 9, 10, 20, 21, 32, 33,
        40, 41, 3, 4, 25, 26, 35, 36,
        12,
    };

    const
    uint32_t    cSym_C_Prim_index = 41;




    typedef struct {
        const
        char            *pEnum;
        char            *pDesc;
        char            *pName;
        uint32_t        value;
    } Sym_C_Prim_entry;

    // This table is in alphanumeric order to be searched
    // with a sequential or binary search by description.

    const
    Sym_C_Prim_entry    Sym_C_Prim_entries[] = {
        {"SYM_C_PRIM_CHAR", "", "CHAR", 2},
        {"SYM_C_PRIM_CHAR_PTR", "", "CHAR_PTR", 3},
        {"SYM_C_PRIM_ENUM", "", "ENUM", 34},
        {"SYM_C_PRIM_ENUM_PTR", "", "ENUM_PTR", 35},
        {"SYM_C_PRIM_FUNC_PTR", "", "FUNC_PTR", 1},
        {"SYM_C_PRIM_INT", "", "INT", 14},
        {"SYM_C_PRIM_INT_PTR", "", "INT_PTR", 15},
        {"SYM_C_PRIM_LONG", "", "LONG", 20},
        {"SYM_C_PRIM_LONGLONG", "", "LONGLONG", 26},
        {"SYM_C_PRIM_LONGLONG_PTR", "", "LONGLONG_PTR", 27},
        {"SYM_C_PRIM_LONG_PTR", "", "LONG_PTR", 21},
        {"SYM_C_PRIM_MACRO", "", "MACRO", 40},
        {"SYM_C_PRIM_SCHAR", "", "SCHAR", 4},
        {"SYM_C_PRIM_SCHAR_PTR", "", "SCHAR_PTR", 5},
        {"SYM_C_PRIM_SHORT", "", "SHORT", 8},
        {"SYM_C_PRIM_SHORT_PTR", "", "SHORT_PTR", 9},
        {"SYM_C_PRIM_SINT", "", "SINT", 16},
        {"SYM_C_PRIM_SINT_PTR", "", "SINT_PTR", 17},
        {"SYM_C_PRIM_SLONG", "", "SLONG", 22},
        {"SYM_C_PRIM_SLONGLONG", "", "SLONGLONG", 28},
        {"SYM_C_PRIM_SLONGLONG_PTR", "", "SLONGLONG_PTR", 29},
        {"SYM_C_PRIM_SLONG_PTR", "", "SLONG_PTR", 23},
        {"SYM_C_PRIM_SSHORT", "", "SSHORT", 10},
        {"SYM_C_PRIM_SSHORT_PTR", "", "SSHORT_PTR", 11},
        {"SYM_C_PRIM_STRUCT", "", "STRUCT", 36},
        {"SYM_C_PRIM_STRUCT_PTR", "", "STRUCT_PTR", 37},
        {"SYM_C_PRIM_UCHAR", "", "UCHAR", 6},
        {"SYM_C_PRIM_UCHAR_PTR", "", "UCHAR_PTR", 7},
        {"SYM_C_PRIM_UINT", "", "UINT", 18},
        {"SYM_C_PRIM_UINT_PTR", "", "UINT_PTR", 19},
        {"SYM_C_PRIM_ULONG", "", "ULONG", 24},
        {"SYM_C_PRIM_ULONGLONG", "", "ULONGLONG", 30},
        {"SYM_C_PRIM_ULONGLONG_PTR", "", "ULONGLONG_PTR", 31},
        {"SYM_C_PRIM_ULONG_PTR", "", "ULONG_PTR", 25},
        {"SYM_C_PRIM_UNION", "", "UNION", 38},
        {"SYM_C_PRIM_UNION_PTR", "", "UNION_PTR", 39},
        {"SYM_C_PRIM_UNKNOWN", "", "UNKNOWN", 0},
        {"SYM_C_PRIM_USHORT", "", "USHORT", 12},
        {"SYM_C_PRIM_USHORT_PTR", "", "USHORT_PTR", 13},
        {"SYM_C_PRIM_VOID", "", "VOID", 32},
        {"SYM_C_PRIM_VOID_PTR", "", "VOID_PTR", 33},
    };

    uint32_t    cSym_C_Prim_entries = 41;




    /* The following tables were generated from:
     * "sym_phy_prim.txt"
     * If you want to change this enum, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // This table is in enum order and provides
    // the index + 1 into the Sym_Phy_Prim_entries
    // table. 0 means no enum entry.
    const
    uint16_t    Sym_Phy_Prim_index[20] = {
        16, 1, 6, 12, 3, 8, 14, 11,
        20, 18, 2, 7, 13, 5, 9, 17,
        19, 4, 10, 15,
    };

    const
    uint32_t    cSym_Phy_Prim_index = 20;




    typedef struct {
        const
        char            *pEnum;
        char            *pDesc;
        char            *pName;
        uint32_t        value;
    } Sym_Phy_Prim_entry;

    // This table is in alphanumeric order to be searched
    // with a sequential or binary search by description.

    const
    Sym_Phy_Prim_entry    Sym_Phy_Prim_entries[] = {
        {"SYM_PHY_PRIM_CHAR", "", "CHAR", 1},
        {"SYM_PHY_PRIM_DBLWORD", "", "DBLWORD", 10},
        {"SYM_PHY_PRIM_HALF", "", "HALF", 4},
        {"SYM_PHY_PRIM_POINTER", "", "POINTER", 17},
        {"SYM_PHY_PRIM_QUAD", "", "QUAD", 13},
        {"SYM_PHY_PRIM_SCHAR", "", "SCHAR", 2},
        {"SYM_PHY_PRIM_SDBLWORD", "", "SDBLWORD", 11},
        {"SYM_PHY_PRIM_SHALF", "", "SHALF", 5},
        {"SYM_PHY_PRIM_SQUAD", "", "SQUAD", 14},
        {"SYM_PHY_PRIM_STRUCT", "", "STRUCT", 18},
        {"SYM_PHY_PRIM_SWORD", "", "SWORD", 7},
        {"SYM_PHY_PRIM_UCHAR", "", "UCHAR", 3},
        {"SYM_PHY_PRIM_UDBLWORD", "", "UDBLWORD", 12},
        {"SYM_PHY_PRIM_UHALF", "", "UHALF", 6},
        {"SYM_PHY_PRIM_UNION", "", "UNION", 19},
        {"SYM_PHY_PRIM_UNKNOWN", "", "UNKNOWN", 0},
        {"SYM_PHY_PRIM_UQUAD", "", "UQUAD", 15},
        {"SYM_PHY_PRIM_UWORD", "", "UWORD", 9},
        {"SYM_PHY_PRIM_VOID", "", "VOID", 16},
        {"SYM_PHY_PRIM_WORD", "", "WORD", 8},
    };

    uint32_t    cSym_Phy_Prim_entries = 20;





 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /* The following routine was generated from:
     * "sym_c_prim.txt"
     * If you want to change it, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // Given an enum value, return its character format.
    const
    char *            Sym_C_PrimToEnum (
        uint32_t        value
    )
    {
        if (value >= cSym_C_Prim_index) {
            return "<<<Unknown Enum Value>>>";
        }
        if (Sym_C_Prim_index[value]) {
            return Sym_C_Prim_entries[Sym_C_Prim_index[value] - 1].pEnum;
        } else {
            return "<<<Unknown Enum Value>>>";
        }
    }

    // Given an enum value, return its name.
    const
    char *            Sym_C_PrimToName (
        uint32_t        value
    )
    {
        if (value >= cSym_C_Prim_index) {
            return NULL;
        }
        if (Sym_C_Prim_index[value]) {
            return Sym_C_Prim_entries[Sym_C_Prim_index[value] - 1].pName;
        } else {
            return NULL;
        }
    }



    /* The following routine was generated from:
     * "sym_c_prim.txt"
     * If you want to change it, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // Given an enum description, return its value + 1 or
    // 0 for not found.
    const
    uint32_t        Sym_EnumToC_Prim (
        char            *pDescA
    )
    {
        Sym_C_Prim_entry    *pEntry = NULL;
        uint32_t        value = 0;

        if (pDescA) {
            pEntry = Misc_SearchBinaryStrA(
                        pDescA,
                        (void *)Sym_C_Prim_entries,
                        cSym_C_Prim_entries,
                        sizeof(Sym_C_Prim_entry),
                        offsetof(Sym_C_Prim_entry, pEnum)
                );
            if (pEntry) {
                value = pEntry->value + 1;
            }
        }
        return value;
    }



    /* The following routine was generated from:
     * "sym_phy_prim.txt"
     * If you want to change it, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // Given an enum value, return its character format.
    const
    char *            Sym_Phy_PrimToEnum (
        uint32_t        value
    )
    {
        if (value >= cSym_Phy_Prim_index) {
            return "<<<Unknown Enum Value>>>";
        }
        if (Sym_Phy_Prim_index[value]) {
            return Sym_Phy_Prim_entries[Sym_Phy_Prim_index[value] - 1].pEnum;
        } else {
            return "<<<Unknown Enum Value>>>";
        }
    }

    // Given an enum value, return its name.
    const
    char *            Sym_Phy_PrimToName (
        uint32_t        value
    )
    {
        if (value >= cSym_Phy_Prim_index) {
            return NULL;
        }
        if (Sym_Phy_Prim_index[value]) {
            return Sym_Phy_Prim_entries[Sym_Phy_Prim_index[value] - 1].pName;
        } else {
            return NULL;
        }
    }



    /* The following routine was generated from:
     * "sym_phy_prim.txt"
     * If you want to change it, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // Given an enum description, return its value + 1 or
    // 0 for not found.
    const
    uint32_t        Sym_EnumToPhy_Prim (
        char            *pDescA
    )
    {
        Sym_Phy_Prim_entry    *pEntry = NULL;
        uint32_t        value = 0;

        if (pDescA) {
            pEntry = Misc_SearchBinaryStrA(
                        pDescA,
                        (void *)Sym_Phy_Prim_entries,
                        cSym_Phy_Prim_entries,
                        sizeof(Sym_Phy_Prim_entry),
                        offsetof(Sym_Phy_Prim_entry, pEnum)
                );
            if (pEntry) {
                value = pEntry->value + 1;
            }
        }
        return value;
    }






    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SYM_DATA *      Sym_Alloc (
        void
    )
    {
        SYM_DATA        *this;
        uint32_t        cbSize = sizeof(SYM_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SYM_DATA *      Sym_New (
        void
    )
    {
        SYM_DATA       *this;
        
        this = Sym_Alloc( );
        if (this) {
            this = Sym_Init(this);
        } 
        return this;
    }



    SYM_DATA *      Sym_NewA(
        int32_t         cls,
        const
        char            *pNameA
    )
    {
        SYM_DATA        *this;

        if (OBJ_NIL == pNameA) {
            return OBJ_NIL;
        }

        this = Sym_New( );
        if (this) {
            Sym_setNameA(this, pNameA);
            Sym_getEntry(this)->cls = cls;
        }

        return this;
    }



    SYM_DATA *      Sym_NewW32(
        int32_t         cls,
        const
        W32CHR_T        *pNameW32
    )
    {
        SYM_DATA        *this;

        if (OBJ_NIL == pNameW32) {
            return OBJ_NIL;
        }

        this = Sym_New( );
        if (this) {
            Sym_setNameW32(this, pNameW32);
            Sym_getEntry(this)->cls = cls;
        }

        return this;
    }



    SYM_DATA *      Sym_NewEntry(
        SYM_ENTRY       *pEntry
    )
    {
        SYM_DATA        *this;

        if (OBJ_NIL == pEntry) {
            return OBJ_NIL;
        }

        this = Sym_New( );
        if (this) {
            Sym_setEntry(this, pEntry);
        }

        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A c t i v e
    //---------------------------------------------------------------

    bool            Sym_getActive (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return (Sym_getEntry(this)->fFlgs1 & SYM_FLGS1_ACT) ? true : false;
    }


    bool            Sym_setActive (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->fFlgs1 |= SYM_FLGS1_ACT;
        } else {
            Sym_getEntry(this)->fFlgs1 &= ~SYM_FLGS1_ACT;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                          A b s o l u t e
    //---------------------------------------------------------------

    bool            Sym_getAbs (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return (Sym_getEntry(this)->fFlgs1 & SYM_FLGS1_ABS) ? true : false;
    }


    bool            Sym_setAbs (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->fFlgs1 |= SYM_FLGS1_ABS;
        } else {
            Sym_getEntry(this)->fFlgs1 &= ~SYM_FLGS1_ABS;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                        A d d r e s s
    //---------------------------------------------------------------

    uint32_t        Sym_getAddr (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->addr;
    }


    bool            Sym_setAddr (
        SYM_DATA        *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->addr = value;

        return true;
    }



    //---------------------------------------------------------------
    //                        A l i g n
    //---------------------------------------------------------------

    uint16_t        Sym_getAlign (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->align;
    }


    bool            Sym_setAlign (
        SYM_DATA        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->align = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          C l a s s
    //---------------------------------------------------------------

    int32_t         Sym_getClass (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->cls;
    }


    bool            Sym_setClass (
        SYM_DATA        *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->cls = value;

        return true;
    }



    //---------------------------------------------------------------
    //                 D i s p l a c e m e n t
    //---------------------------------------------------------------

    uint32_t        Sym_getDisp (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->disp;
    }


    bool            Sym_setDisp (
        SYM_DATA        *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->disp = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          D u p
    //---------------------------------------------------------------

    uint16_t        Sym_getDup (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->dup;
    }


    bool            Sym_setDup (
        SYM_DATA        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->dup = value;

        return true;
    }



    //---------------------------------------------------------------
    //                        E n t r y
    //---------------------------------------------------------------

    SYM_ENTRY *     Sym_getEntry (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return &this->entry;
    }


    bool            Sym_setEntry (
        SYM_DATA        *this,
        SYM_ENTRY       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        memmove(&this->entry, pValue, sizeof(SYM_ENTRY));

        return true;
    }



    //---------------------------------------------------------------
    //                          E x t r a 2
    //---------------------------------------------------------------

    uint8_t *       Sym_getExtra2 (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return (uint8_t *)Sym_getEntry(this)->extra2;
    }



    //---------------------------------------------------------------
    //                   R e s e r v e d  F l a g 1
    //---------------------------------------------------------------

    bool            Sym_getFlg1 (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return (Sym_getEntry(this)->fFlgs1 & SYM_FLGS1_RSVD1) ? true : false;
    }


    bool            Sym_setFlg1 (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->fFlgs1 |= SYM_FLGS1_RSVD1;
        } else {
            Sym_getEntry(this)->fFlgs1 &= ~SYM_FLGS1_RSVD1;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                  R e s e r v e d  F l a g 2
    //---------------------------------------------------------------

    bool            Sym_getFlg2 (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return (Sym_getEntry(this)->fFlgs1 & SYM_FLGS1_RSVD2) ? true : false;
    }


    bool            Sym_setFlg2 (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->fFlgs1 |= SYM_FLGS1_RSVD2;
        } else {
            Sym_getEntry(this)->fFlgs1 &= ~SYM_FLGS1_RSVD2;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    R e s e r v e d  F l a g 3
    //---------------------------------------------------------------

    bool            Sym_getFlg3 (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return (Sym_getEntry(this)->fFlgs1 & SYM_FLGS1_RSVD3) ? true : false;
    }


    bool            Sym_setFlg3 (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->fFlgs1 |= SYM_FLGS1_RSVD3;
        } else {
            Sym_getEntry(this)->fFlgs1 &= ~SYM_FLGS1_RSVD3;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    R e s e r v e d  F l a g 4
    //---------------------------------------------------------------

    bool            Sym_getFlg4 (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return (Sym_getEntry(this)->fFlgs1 & SYM_FLGS1_RSVD4) ? true : false;
    }


    bool            Sym_setFlg4 (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->fFlgs1 |= SYM_FLGS1_RSVD4;
        } else {
            Sym_getEntry(this)->fFlgs1 &= ~SYM_FLGS1_RSVD4;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    R e s e r v e d  F l a g 5
    //---------------------------------------------------------------

    bool            Sym_getFlg5 (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return (Sym_getEntry(this)->fFlgs1 & SYM_FLGS1_RSVD5) ? true : false;
    }


    bool            Sym_setFlg5 (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->fFlgs1 |= SYM_FLGS1_RSVD5;
        } else {
            Sym_getEntry(this)->fFlgs1 &= ~SYM_FLGS1_RSVD5;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    U n u s e d  F l a g 6
    //---------------------------------------------------------------

    bool            Sym_getFlg6 (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return (Sym_getEntry(this)->fFlgs2 & SYM_FLGS2_UNUSED3) ? true : false;
    }


    bool            Sym_setFlg6 (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->fFlgs2 |= SYM_FLGS2_UNUSED3;
        } else {
            Sym_getEntry(this)->fFlgs2 &= ~SYM_FLGS2_UNUSED3;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    U n u s e d  F l a g 7
    //---------------------------------------------------------------

    bool            Sym_getFlg7 (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return (Sym_getEntry(this)->fFlgs2 & SYM_FLGS2_UNUSED4) ? true : false;
    }


    bool            Sym_setFlg7 (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->fFlgs2 |= SYM_FLGS2_UNUSED4;
        } else {
            Sym_getEntry(this)->fFlgs2 &= ~SYM_FLGS2_UNUSED4;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    U n u s e d  F l a g 8
    //---------------------------------------------------------------

    bool            Sym_getFlg8 (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return (Sym_getEntry(this)->fFlgs2 & SYM_FLGS2_UNUSED5) ? true : false;
    }


    bool            Sym_setFlg8 (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->fFlgs2 |= SYM_FLGS2_UNUSED5;
        } else {
            Sym_getEntry(this)->fFlgs2 &= ~SYM_FLGS2_UNUSED5;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    U n u s e d  F l a g 9
    //---------------------------------------------------------------

    bool            Sym_getFlg9 (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return (Sym_getEntry(this)->fFlgs2 & SYM_FLGS2_UNUSED6) ? true : false;
    }


    bool            Sym_setFlg9 (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->fFlgs2 |= SYM_FLGS2_UNUSED6;
        } else {
            Sym_getEntry(this)->fFlgs2 &= ~SYM_FLGS2_UNUSED6;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    U n u s e d  F l a g 1 0
    //---------------------------------------------------------------

    bool            Sym_getFlg10 (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return (Sym_getEntry(this)->fFlgs2 & SYM_FLGS2_UNUSED7) ? true : false;
    }


    bool            Sym_setFlg10 (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->fFlgs2 |= SYM_FLGS2_UNUSED7;
        } else {
            Sym_getEntry(this)->fFlgs2 &= ~SYM_FLGS2_UNUSED7;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    U n u s e d  F l a g 1 1
    //---------------------------------------------------------------

    bool            Sym_getFlg11 (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return (Sym_getEntry(this)->fFlgs2 & SYM_FLGS2_UNUSED8) ? true : false;
    }


    bool            Sym_setFlg11 (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->fFlgs2 |= SYM_FLGS2_UNUSED8;
        } else {
            Sym_getEntry(this)->fFlgs2 &= ~SYM_FLGS2_UNUSED8;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                        H a s h
    //---------------------------------------------------------------

    uint32_t        Sym_getHash (
        SYM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->hash;
    }


    bool            Sym_setHash (
        SYM_DATA        *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->hash = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          L e n
    //---------------------------------------------------------------

    uint16_t        Sym_getLen (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->len;
    }


    bool            Sym_setLen (
        SYM_DATA        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->len = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          L e v e l
    //---------------------------------------------------------------

    uint8_t         Sym_getLevel (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->level;
    }


    bool            Sym_setLevel (
        SYM_DATA        *this,
        uint8_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->level = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          L i n k
    //---------------------------------------------------------------

    uint32_t        Sym_getLink (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->link;
    }


    bool            Sym_setLink (
        SYM_DATA        *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->link = value;

        return true;
    }



    //---------------------------------------------------------------
    //                         L i s t
    //---------------------------------------------------------------

    OBJ_ID          Sym_getList (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pList;
    }


    bool            Sym_setList (
        SYM_DATA        *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
        if (pValue && !obj_IsKindOf(pValue, OBJ_IDENT_SYMLIST)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pList) {
            obj_Release(this->pList);
        }
        this->pList = (SYMLIST_DATA *)pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                       L o c a t i o n
    //---------------------------------------------------------------

    SRCLOC *        Sym_getLoc(
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Sym_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return &this->entry.loc;
    }


    bool            Sym_setLoc (
        SYM_DATA        *this,
        const
        SRCLOC          *pValue
    )
    {
        //uint32_t        len;

#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
        if (NULL == pValue) {
            DEBUG_BREAK();
            return false;
        }
#endif

        memmove(&this->entry.loc, pValue, sizeof(SRCLOC));

        return true;
    }



    //---------------------------------------------------------------
    //                          N a m e
    //---------------------------------------------------------------

    const
    char *          Sym_getNameA (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->nameA;
    }


    bool            Sym_setNameA (
        SYM_DATA        *this,
        const
        char            *pValue
    )
    {
        //uint32_t        len;

#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
        if (NULL == pValue) {
            DEBUG_BREAK();
            return false;
        }
#endif

        str_Copy(
                 (char *)Sym_getEntry(this)->nameA,
                 sizeof(Sym_getEntry(this)->nameA),
                 pValue
        );
        Sym_getEntry(this)->hash = str_HashAcmA(Sym_getEntry(this)->nameA, NULL);

        return true;
    }


    bool            Sym_setNameW32 (
        SYM_DATA        *this,
        const
        W32CHR_T        *pValue
    )
    {
        //uint32_t        len;


#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
        if (NULL == pValue) {
            DEBUG_BREAK();
            return false;
        }
#endif

        utf8_W32StrToUtf8Str(
                             0,
                             pValue,
                             sizeof(Sym_getEntry(this)->nameA),
                             Sym_getEntry(this)->nameA
        );
        Sym_getEntry(this)->hash = str_HashAcmA(Sym_getEntry(this)->nameA, NULL);

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i m
    //---------------------------------------------------------------

    uint16_t        Sym_getPrim (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->prim;
    }


    bool            Sym_setPrim (
        SYM_DATA        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->prim = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          R e c o r d
    //---------------------------------------------------------------

    uint32_t         Sym_getRecord (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->record;
    }


    bool            Sym_setRecord (
        SYM_DATA        *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->record = value;

        return true;
    }



    //---------------------------------------------------------------
    //                 R e g i s t e r  N u m b e r
    //---------------------------------------------------------------

    uint16_t        Sym_getReg (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->reg;
    }


    bool            Sym_setReg (
        SYM_DATA        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->reg = value;

        return true;
    }



    //---------------------------------------------------------------
    //                     R e l o c a t a b l e
    //---------------------------------------------------------------

    bool            Sym_getRel (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return (Sym_getEntry(this)->fFlgs1 & SYM_FLGS1_REL) ? true : false;
    }


    bool            Sym_setRel (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->fFlgs1 |= SYM_FLGS1_REL;
        } else {
            Sym_getEntry(this)->fFlgs1 &= ~SYM_FLGS1_REL;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                        S c a l e
    //---------------------------------------------------------------

    uint16_t        Sym_getScale (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->scale;
    }


    bool            Sym_setScale (
        SYM_DATA        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->scale = value;

        return true;
    }



    //---------------------------------------------------------------
    //                      S e c t i o n
    //---------------------------------------------------------------

    uint32_t        Sym_getSection (
        SYM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->section;
    }


    bool            Sym_setSection (
        SYM_DATA        *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->section = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Sym_getSize (
        SYM_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                      S t o r a g e  C l a s s
    //---------------------------------------------------------------

    uint32_t        Sym_getStorageClass (
        SYM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->storcls;
    }


    bool            Sym_setStorageClass (
        SYM_DATA        *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->storcls = value;

        return true;
    }



    //---------------------------------------------------------------
    //                S t r u c t  I d e n t i f i e r
    //---------------------------------------------------------------

    uint32_t        Sym_getStructID (
        SYM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->strct;
    }


    bool            Sym_setStructID (
        SYM_DATA        *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->strct = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Sym_getSuperVtbl (
        SYM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                        T o k e n
    //---------------------------------------------------------------

    uint32_t        Sym_getToken (
        SYM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->token;
    }


    bool            Sym_setToken (
        SYM_DATA        *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->token = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          T y p e
    //---------------------------------------------------------------

    int32_t         Sym_getType (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->type;
    }


    bool            Sym_setType (
        SYM_DATA        *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->type = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          V a l u e
    //---------------------------------------------------------------

    int32_t         Sym_getValue (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->value;
    }


    bool            Sym_setValue (
        SYM_DATA        *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->value = value;

        return true;
    }





    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
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
        SYM_DATA		*this,
        SYM_DATA        *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Sym_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        memcpy(&pOther->entry, &this->entry, sizeof(SYM_ENTRY));

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Sym_Compare (
        SYM_DATA        *this,
        SYM_DATA        *pOther
    )
    {
        int             i = 0;

#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Sym_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        i = Sym_CompareA(this, pOther->entry.cls, pOther->entry.nameA);
        
        return i;
    }
    
   
    int             Sym_CompareA (
        SYM_DATA        *this,
        int32_t         cls,
        const
        char            *pNameA
    )
    {
        int             i = 0;

#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (NULL == pNameA) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        if (0 == cls) {
            i = utf8_StrCmp(this->entry.nameA, pNameA);
        } else {
            i = this->entry.cls - cls;
            if (0 == i) {
                i = utf8_StrCmp(this->entry.nameA, pNameA);
            }
            if (i < 0)
                i = -1;
            else if (i > 0)
                i = 1;
        }

        return i;
    }



    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
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
    )
    {
        SYM_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SYM_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Sym_New( );
        if (pOther) {
            eRc = Sym_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            Sym_Dealloc (
        OBJ_ID          objId
    )
    {
        SYM_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SYM_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Sym_setList(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Sym      *pDeepCopy = Sym_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SYM object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SYM_DATA *     Sym_DeepyCopy (
        SYM_DATA       *this
    )
    {
        SYM_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Sym_New( );
        if (pOther) {
            eRc = Sym_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Sym_Disable (
        SYM_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Sym_Enable (
        SYM_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------

    uint32_t        Sym_Hash(
        SYM_DATA        *this
    )
    {

#ifdef NDEBUG
#else
        if( !Sym_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->entry.hash;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SYM_DATA *   Sym_Init (
        SYM_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SYM_DATA);
        //ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)Node_Init((NODE_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SYM);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Sym_Vtbl);
#ifdef  SYM_JSON_SUPPORT
        JsonIn_RegisterClass(Sym_Class());
#endif

        // Set up Extra2 to be used by U8VlArray.
        this->entry.extra2[0] = SYM_EXTRA2_MAXLEN;
        this->entry.extra2[1] = 2;

        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
        fprintf(
                stderr, 
                "Sym::sizeof(SYM_DATA) = %lu\n", 
                sizeof(SYM_DATA)
        );
        fprintf(
                stderr,
                "Sym::sizeof(SYM_ENTRY) = %lu\n",
                sizeof(SYM_ENTRY)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SYM_DATA));
        BREAK_NOT_BOUNDARY4(sizeof(SYM_ENTRY));
        BREAK_NOT_BOUNDARY4(sizeof(SYM_ENTRY));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Sym_IsEnabled (
        SYM_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                          L i s t
    //---------------------------------------------------------------

    ERESULT         Sym_ListAdd (
        SYM_DATA        *this,
        SYM_DATA        *pSym
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Sym_Validate(pSym)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pList) {
            this->pList = SymList_New();
            if (OBJ_NIL == this->pList) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }

        eRc = SymList_Add2Tail(this->pList, pSym);

        // Return to caller.
        return eRc;
    }


    SYM_DATA *      Sym_ListFindA (
        SYM_DATA        *this,
        int32_t         cls,
        const
        char            *pNameA
    )
    {
        //ERESULT         eRc;
        SYM_DATA        *pSym = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        if (this->pList) {
            pSym = SymList_FindA(this->pList, cls, pNameA);
        }

        // Return to caller.
        return pSym;
    }



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = Sym_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Sym", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Sym_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SYM_DATA     *this = objId;
        const
        char         *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SYM_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Sym_Class();
                break;
                
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'S':
                    if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                        return &this->pSuperVtbl;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return Sym_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Sym_Enable;
                        }
                        break;

#ifdef  SYM_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Sym_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Sym_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Sym_ToDebugString;
                        }
#ifdef  SYM_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Sym_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Sym_ToDebugString)
                    return "ToDebugString";
#ifdef  SYM_JSON_SUPPORT
                if (pData == Sym_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
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
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Sym_ToDebugString (
        SYM_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        char            NameA[256];
        uint32_t        len;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    Sym_getSize(this),
                    obj_getRetainCount(this)
            );

        len = utf8_Utf8ToChrConStr(0, this->entry.nameA, sizeof(NameA), NameA);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Name:\"%s\",\n", NameA);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Class:%d,\n", this->entry.cls);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Type:%d,\n", this->entry.type);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Prim:%d,\n", this->entry.prim);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Len:%d,\n", this->entry.len);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Dup:%d,\n", this->entry.dup);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Align:%d,\n", this->entry.align);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Scale:%d,\n", this->entry.scale);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Value:%d,\n", this->entry.value);

#ifdef  XYZZY
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            Sym_Validate (
        SYM_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SYM))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(SYM_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


