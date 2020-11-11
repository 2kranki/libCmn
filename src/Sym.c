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
#include        <trace.h>
#include        <utf8.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            Sym_task_body (
        void            *pData
    )
    {
        //SYM_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SYM_DATA *     Sym_Alloc (
        void
    )
    {
        SYM_DATA       *this;
        uint32_t        cbSize = sizeof(SYM_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SYM_DATA *     Sym_New (
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



    SYM_DATA *     Sym_NewA(
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





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

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
    //                        A l i g n
    //---------------------------------------------------------------

    uint16_t        Sym_getAlign (
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



    //---------------------------------------------------------------
    //                        E x t r a
    //---------------------------------------------------------------

    uint8_t *       Sym_getExtra (
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

        return (uint8_t *)Sym_getEntry(this)->extra;
    }



    //---------------------------------------------------------------
    //                    U n u s e d  F l a g 1
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
        return (Sym_getEntry(this)->fFlgs1 & SYM_FLGS1_UNUSED1) ? true : false;
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
            Sym_getEntry(this)->fFlgs1 |= SYM_FLGS1_UNUSED1;
        } else {
            Sym_getEntry(this)->fFlgs1 &= ~SYM_FLGS1_UNUSED1;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    U n u s e d  F l a g 2
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
        return (Sym_getEntry(this)->fFlgs1 & SYM_FLGS1_UNUSED2) ? true : false;
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
            Sym_getEntry(this)->fFlgs1 |= SYM_FLGS1_UNUSED2;
        } else {
            Sym_getEntry(this)->fFlgs1 &= ~SYM_FLGS1_UNUSED2;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    U n u s e d  F l a g 3
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
        return (Sym_getEntry(this)->fFlgs1 & SYM_FLGS1_UNUSED3) ? true : false;
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
            Sym_getEntry(this)->fFlgs1 |= SYM_FLGS1_UNUSED3;
        } else {
            Sym_getEntry(this)->fFlgs1 &= ~SYM_FLGS1_UNUSED3;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    U n u s e d  F l a g 4
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
        return (Sym_getEntry(this)->fFlgs1 & SYM_FLGS1_UNUSED4) ? true : false;
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
            Sym_getEntry(this)->fFlgs1 |= SYM_FLGS1_UNUSED4;
        } else {
            Sym_getEntry(this)->fFlgs1 &= ~SYM_FLGS1_UNUSED4;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    U n u s e d  F l a g 5
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
        return (Sym_getEntry(this)->fFlgs1 & SYM_FLGS1_UNUSED5) ? true : false;
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
            Sym_getEntry(this)->fFlgs1 |= SYM_FLGS1_UNUSED5;
        } else {
            Sym_getEntry(this)->fFlgs1 &= ~SYM_FLGS1_UNUSED5;
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
        return (Sym_getEntry(this)->fFlgs2 & SYM_FLGS1_UNUSED6) ? true : false;
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
            Sym_getEntry(this)->fFlgs2 |= SYM_FLGS1_UNUSED6;
        } else {
            Sym_getEntry(this)->fFlgs2 &= ~SYM_FLGS1_UNUSED6;
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
        return (Sym_getEntry(this)->fFlgs2 & SYM_FLGS1_UNUSED7) ? true : false;
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
            Sym_getEntry(this)->fFlgs2 |= SYM_FLGS1_UNUSED7;
        } else {
            Sym_getEntry(this)->fFlgs2 &= ~SYM_FLGS1_UNUSED7;
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
        return (Sym_getEntry(this)->fFlgs2 & SYM_FLGS1_UNUSED8) ? true : false;
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
            Sym_getEntry(this)->fFlgs2 |= SYM_FLGS1_UNUSED8;
        } else {
            Sym_getEntry(this)->fFlgs2 &= ~SYM_FLGS1_UNUSED8;
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
        return (Sym_getEntry(this)->fFlgs2 & SYM_FLGS1_UNUSED9) ? true : false;
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
            Sym_getEntry(this)->fFlgs2 |= SYM_FLGS1_UNUSED9;
        } else {
            Sym_getEntry(this)->fFlgs2 &= ~SYM_FLGS1_UNUSED9;
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
        return (Sym_getEntry(this)->fFlgs2 & SYM_FLGS1_UNUSED10) ? true : false;
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
            Sym_getEntry(this)->fFlgs2 |= SYM_FLGS1_UNUSED10;
        } else {
            Sym_getEntry(this)->fFlgs2 &= ~SYM_FLGS1_UNUSED10;
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
        return (Sym_getEntry(this)->fFlgs2 & SYM_FLGS1_UNUSED11) ? true : false;
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
            Sym_getEntry(this)->fFlgs2 |= SYM_FLGS1_UNUSED11;
        } else {
            Sym_getEntry(this)->fFlgs2 &= ~SYM_FLGS1_UNUSED11;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    U n u s e d  F l a g 1 2
    //---------------------------------------------------------------

    bool            Sym_getFlg12 (
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
        return (Sym_getEntry(this)->fFlgs2 & SYM_FLGS1_UNUSED12) ? true : false;
    }


    bool            Sym_setFlg12 (
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
            Sym_getEntry(this)->fFlgs2 |= SYM_FLGS1_UNUSED12;
        } else {
            Sym_getEntry(this)->fFlgs2 &= ~SYM_FLGS1_UNUSED12;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                    U n u s e d  F l a g 1 3
    //---------------------------------------------------------------

    bool            Sym_getFlg13 (
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
        return (Sym_getEntry(this)->fFlgs2 & SYM_FLGS1_UNUSED13) ? true : false;
    }


    bool            Sym_setFlg13 (
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
            Sym_getEntry(this)->fFlgs2 |= SYM_FLGS1_UNUSED13;
        } else {
            Sym_getEntry(this)->fFlgs2 &= ~SYM_FLGS1_UNUSED13;
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

        return Sym_getEntry(this)->name;
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

        str_Copy((char *)Sym_getEntry(this)->name, sizeof(Sym_getEntry(this)->name), pValue);
        Sym_getEntry(this)->hash = str_HashAcmA(Sym_getEntry(this)->name, NULL);

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

        i = this->entry.cls - pOther->entry.cls;
        if (0 == i) {
            i = utf8_StrCmp(this->entry.name, pOther->entry.name);
        }
        if (i < 0)
            i =  -1;
        else if (i > 0)
            i = 1;
        
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

        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SYM);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Sym_Vtbl);

        // Set up Extra to be used by U8VlArray.
        this->entry.extra[0] = sizeof(this->entry.extra);
        this->entry.extra[1] = 2;

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
//#if defined(__APPLE__)
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
        char            *pStr = pData;
        
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

        len = utf8_Utf8ToChrConStr(0, this->entry.name, sizeof(NameA), NameA);
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


