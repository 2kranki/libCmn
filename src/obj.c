// vi: nu:noai:ts=4:sw=4

//****************************************************************
//					C Object (obj) Implementation
//****************************************************************

/*
 * Todo List
 *  ---         Add OBJ_Sort() with a comparison exit routine which
 *              points at the Data associated with an Entry.
 *  ---         Add routines to provide a doubly-linked list capability.
 *              See LLD.h for details.
 * Remarks
 *  1.          None
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



/****************************************************************
* * * * * * * * * * * *  data definitions   * * * * * * * * * * *
****************************************************************/

/* Header File Inclusion */
#include        <stdlib.h>
#include        <string.h>
#include        "obj.h"



#ifdef	__cplusplus
extern	"C" {
#endif

    
    static
    const
    OBJ_INFO        obj_Info;
    

    static
    bool            obj_ClassIsKindOf(
        uint16_t        classID
    )
    {
        if (OBJ_IDENT_OBJ_CLASS == classID) {
            return true;
        }
        return false;
    }

    
    OBJ_ID          obj_ClassSuper(
        OBJ_ID          id
    );
    
    
    static
    uint16_t        obj_ClassWhoAmI(
    )
    {
        return OBJ_IDENT_OBJ_CLASS;
    }
    
    
    bool            obj_ClassEnable(
        OBJ_ID          id
    )
    {
        return true;
    }
    

    bool            obj_ClassDisable(
        OBJ_ID          id
    )
    {
        return true;
    }

    
    static
    const
	OBJ_IUNKNOWN    obj_ClassVtbl = {
        &obj_Info,
        obj_ClassIsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        obj_Class,
        obj_ClassWhoAmI,
        obj_ClassEnable,
        obj_ClassDisable
    };
 
    
    const
    OBJ_DATA        obj_ClassObj = {
        &obj_ClassVtbl,
        sizeof(OBJ_DATA),
        OBJ_IDENT_OBJ_CLASS,
        0,
        1
    };
    

    OBJ_ID          obj_ClassSuper(
        OBJ_ID          id
    )
    {
        return (OBJ_ID)&obj_ClassObj;
    }
    
 
    static
    bool            obj_ObjIsKindOf(
        uint16_t        classID
    )
    {
        if (OBJ_IDENT_OBJ == classID) {
            return true;
        }
        return false;
    }
    
    
    
    static
    uint16_t        obj_ObjWhoAmI(
    )
    {
        return OBJ_IDENT_OBJ;
    }
    
    
    static
    const
	OBJ_IUNKNOWN    obj_Vtbl = {
        &obj_Info,
        obj_ObjIsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        obj_Dealloc,
        obj_Class,
        obj_ObjWhoAmI,
        obj_Enable,
        obj_Disable
    };
    
    
    static
    const
    OBJ_IUNKNOWN    obj_VtblShared = {
        &obj_Info,
        obj_ObjIsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        obj_Dealloc,
        obj_Class,
        obj_ObjWhoAmI,
        obj_Enable,
        obj_Disable
    };
    
    
    
    static
    const
    OBJ_INFO        obj_Info = {
        "object",
        "Base Object",
        (OBJ_DATA *)&obj_ClassObj,
        (OBJ_DATA *)&obj_ClassObj
    };
    
    
    
    //---------------------------------------------------------------
    //					Internal Subroutine Definitions     
    //---------------------------------------------------------------
    




    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines * * * * * * * * * * *
    ****************************************************************/





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    //---------------------------------------------------------------
    //                          A l l o c
    //---------------------------------------------------------------
    
    OBJ_ID          obj_Alloc(
        uint16_t        size
    )
    {
        OBJ_DATA        *this;
        uint16_t        newSize;
        
#ifdef NDEBUG
#else
        if ( size >= sizeof(struct obj_data_s) )
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        newSize = ROUNDUP4(size);
        this = mem_MallocObject(newSize);
        if (this) {
            memset(this, 0, newSize);
            this->pVtbl = &obj_Vtbl;
            this->cbSize = size;
            this->cbIdent = OBJ_IDENT_OBJ;
            this->cbRetainCount = 1;
            obj_FlagOn(this, OBJ_FLAG_ALLOC);
        }
        
        return (OBJ_ID)this;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C l a s s
    //---------------------------------------------------------------
    
    OBJ_ID          obj_Class(
    )
    {
        return (OBJ_ID)&obj_ClassObj;
    }
    
    

    const
    OBJ_IUNKNOWN *  obj_StaticVtbl(
    )
    {
        return &obj_Vtbl;
    }

    
    
    const
    OBJ_IUNKNOWN *  obj_StaticVtblShared(
    )
    {
        return &obj_VtblShared;
    }

    
    

    //===============================================================
    //                      *** Properties ***
    //===============================================================

    bool            obj_IsEnabled(
        void            *pVoid
    )
    {
        OBJ_DATA		*this = pVoid;
        
        // Do initialization.
        
        if (this->cbFlags & (1 << OBJ_FLAG_ENABLED))
            return true;
        
        // Return to caller.
        return false;
    }
    
 
    
    uint16_t        obj_getFlags(
        void            *pVoid
    )
    {
        OBJ_DATA		*this = pVoid;
        
        return this->cbFlags;
    }
    
    
    bool			obj_setFlags(
        OBJ_ID          objId,
        uint16_t        value
    )
    {
        OBJ_DATA		*this = objId;
        
        this->cbFlags = value;
        
        return true;
    }
    
    
    

    uint16_t        obj_getIdent(
        OBJ_ID          objId
    )
    {
        OBJ_DATA		*this = objId;
        
        return this->cbIdent;
    }
    
    
    bool			obj_setIdent(
        OBJ_ID          objId,
        uint16_t        value
    )
    {
        OBJ_DATA		*this = objId;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( 0 == value) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->cbIdent = value;
        
        return true;
    }
    
    
    
    const
    OBJ_INFO *      obj_getInfo(
        OBJ_ID          objId
    )
    {
        OBJ_DATA		*this = objId;
        
        if (this == OBJ_NIL) {
            return NULL;
        }
        if (this->pVtbl == NULL) {
            return NULL;
        }
        return this->pVtbl->pInfo;
    }
    
    
    
    uint16_t        obj_getSize(
        OBJ_ID          objId
    )
    {
        OBJ_DATA		*this = objId;
        
        return this->cbSize;
    }
    
    
    bool			obj_setSize(
        OBJ_ID          objId,
        uint16_t        value
    )
    {
        OBJ_DATA		*this = objId;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( 0 == value) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->cbSize = value;
        
        return true;
    }
    
    
    
    uint16_t        obj_getRetainCount(
        OBJ_ID          objId
    )
    {
        OBJ_DATA		*this = objId;
        
        return this->cbRetainCount;
    }
    

    
    bool			obj_setRetainCount(
        OBJ_ID          objId,
        uint16_t        value
    )
    {
        OBJ_DATA		*this = objId;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( 0 == value) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->cbRetainCount = value;
        
        return true;
    }
    
    
    
    uint32_t        obj_getMisc(
        OBJ_ID          objId
    )
    {
        OBJ_DATA		*this = objId;
        
        return this->cbMisc;
    }


    bool			obj_setMisc(
        OBJ_ID          objId,
        uint32_t        value
    )
    {
        OBJ_DATA		*this = objId;
        
        this->cbMisc = value;
        
        return true;
    }



    uint16_t        obj_getMisc1(
        OBJ_ID          objId
    )
    {
        OBJ_DATA		*this = objId;
        
        return this->cbMisc1;
    }
    
    
    bool			obj_setMisc1(
        OBJ_ID          objId,
        uint16_t        value
    )
    {
        OBJ_DATA		*this = objId;
        
        this->cbMisc1 = value;
        
        return true;
    }
    
    
    
    uint16_t        obj_getMisc2(
        OBJ_ID          objId
    )
    {
        OBJ_DATA		*this = objId;
        
        return this->cbMisc2;
    }
    
    
    bool			obj_setMisc2(
        OBJ_ID          objId,
        uint16_t        value
    )
    {
        OBJ_DATA		*this = objId;
        
        this->cbMisc2 = value;
        
        return true;
    }
    
    
    
    OBJ_ID          obj_getSuper(
        OBJ_ID          objId
    )
    {
        return objId;
    }
    
    
    uint16_t        obj_getType(
        OBJ_ID          objId
    )
    {
        OBJ_DATA		*this = objId;
        
        if (this == OBJ_NIL) {
            return 0;
        }
        if (this->pVtbl == NULL) {
            return 0;
        }
        
        return this->pVtbl->pWhoAmI();
    }
    
    

    OBJ_IUNKNOWN *	obj_getVtbl(
        OBJ_ID          objId
    )
    {
        OBJ_DATA		*this = objId;
        
        if (this == OBJ_NIL) {
            return 0;
        }
        return (void *)this->pVtbl;
    }
    

    
    bool			obj_setVtbl(
        OBJ_ID           objId,
        const
        OBJ_IUNKNOWN     *pValue
    )
    {
        OBJ_DATA		*this = objId;
        
        this->pVtbl = pValue;
        return true;
    }
    
    


    //===============================================================
    //                      *** Methods ***
    //===============================================================


    //---------------------------------------------------------------
    //                      D e a l l o c
    //---------------------------------------------------------------
    
    void            obj_Dealloc(
        void            *pVoid
    )
    {
        OBJ_DATA		*this = pVoid;
        uint32_t        cbSize;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            return;
        }
        cbSize = obj_getSize(this);
        
        // Free the main control block.
        if (obj_IsFlag(this, OBJ_FLAG_ALLOC)) {
            mem_FreeObject(this);
            this = OBJ_NIL;
        }
        else {
            memset(this, 0, cbSize);
        }
        
        // Return to caller.
    }
    
    
    
    
    //---------------------------------------------------------------
    //					  D i s a b l e
    //---------------------------------------------------------------

    bool            obj_Disable(
        void            *pVoid
    )
    {
        OBJ_DATA		*this = pVoid;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            return false;
        }
        
        this->cbFlags &= ~(1 << OBJ_FLAG_ENABLED);
        
        // Return to caller.
        return true;
    }




    //---------------------------------------------------------------
    //					  E n a b l e
    //---------------------------------------------------------------

    bool            obj_Enable(
        OBJ_ID          objId
    )
    {
        OBJ_DATA		*this = objId;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            return false;
        }
        
        this->cbFlags |= (1 << OBJ_FLAG_ENABLED);

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          I s A
    //---------------------------------------------------------------
    
    bool            obj_IsA(
        OBJ_ID          objId,
        uint16_t        type
    )
    {
        OBJ_DATA		*this = objId;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            return false;
        }
        
        if (type == this->pVtbl->pWhoAmI())
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                          I s F l a g
    //---------------------------------------------------------------
    
    bool            obj_IsFlag(
        OBJ_ID          objId,
        uint16_t        flag
    )
    {
        OBJ_DATA		*this = objId;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (OBJ_NIL == this) {
            return false;
        }
        if ((flag > 15)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->cbFlags & (1 << flag))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                      I s K i n d O f
    //---------------------------------------------------------------
    
    bool            obj_IsKindOf(
        OBJ_ID          objId,
        uint16_t        type
    )
    {
        OBJ_DATA		*this = objId;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            return false;
        }
        
        if (this->pVtbl == NULL) {
            return false;
        }
        
        if (this->pVtbl->pIsKindOf == NULL) {
            return false;
        }
        
        if (this->pVtbl->pIsKindOf(type))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                          F l a g
    //---------------------------------------------------------------
    
    bool            obj_Flag(
        OBJ_ID          objId,
        uint16_t        flag
    )
    {
        OBJ_DATA		*this = objId;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (OBJ_NIL == this) {
            return false;
        }
        if ((flag > 15)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->cbFlags & (1 << flag))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                      F l a g O f f
    //---------------------------------------------------------------
    
    bool            obj_FlagOff(
        OBJ_ID          objId,
        uint16_t        flag
    )
    {
        OBJ_DATA        *this = objId;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if ((flag > 15)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->cbFlags &= ~(1 << flag);
        
        // Return to caller.
        return true;
    }
    
    
    
    
    //---------------------------------------------------------------
    //					  F l a g O n
    //---------------------------------------------------------------
    
    bool            obj_FlagOn(
        OBJ_ID          objId,
        uint16_t        flag
    )
    {
        OBJ_DATA        *this = objId;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if ((flag > 15)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->cbFlags |= (1 << flag);
        
        // Return to caller.
        return true;
    }
    
    
    
    bool            obj_FlagSet(
        OBJ_ID          objId,
        uint16_t        flag,
        bool            fValue
    )
    {
        OBJ_DATA        *this = objId;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if ((flag > 15)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (fValue) {
            this->cbFlags |= (1 << flag);
        }
        else {
            this->cbFlags &= ~(1 << flag);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //						  I n i t
    //---------------------------------------------------------------

    OBJ_ID          obj_Init(
        void            *pVoid,
        uint16_t        size,
        uint16_t        objectIdentifier
    )
    {
        OBJ_DATA        *this = pVoid;

        // Do initialization.
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (this) {
            if (obj_IsFlag(this, OBJ_FLAG_INIT)) {
                DEBUG_BREAK();
                return this;
            }
            // We assume that if the Object Identifier is
            // already set to us, then we allocated the
            // object. This will do until we do a class
            // object.
            if ((OBJ_IDENT_OBJ == this->cbIdent) && (obj_IsFlag(this, OBJ_FLAG_ALLOC))) {
            }
            else {
                memset(this, 0, size);
            }
            this->pVtbl = &obj_Vtbl;
            this->cbSize = size;
            this->cbIdent = objectIdentifier;
            obj_FlagOn(this, OBJ_FLAG_INIT);
            this->cbRetainCount = 1;
        }

        
        // Return to caller.
        return (OBJ_ID)this;
    }




    //---------------------------------------------------------------
    //                      R e l e a s e
    //---------------------------------------------------------------
    
    OBJ_ID          obj_Release(
        OBJ_ID          objId
    )
    {
        OBJ_DATA        *this = objId;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        if (NULL == this->pVtbl) {
            return OBJ_NIL;
        }
        if (obj_IsFlag(this, OBJ_FLAG_ALLOC)) {
            if (this->pVtbl->pRelease) {
                this->pVtbl->pRelease(this);
            }
        }
        return objId;
    }
    
    
    OBJ_ID          obj_ReleaseNull(
        OBJ_ID          objId
    )
    {
        return objId;
    }
    
    
    OBJ_ID          obj_ReleaseStandard(
        OBJ_ID          objId
    )
    {
        OBJ_DATA        *this = objId;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (obj_IsFlag(this, OBJ_FLAG_ALLOC)) {
            --this->cbRetainCount;
            if (0 == this->cbRetainCount) {
                // Release/destroy this object.
                (*this->pVtbl->pDealloc)(objId);
                objId = OBJ_NIL;
            }
        }
        
        return objId;
    }
    
    
    
    //---------------------------------------------------------------
    //                      R e t a i n
    //---------------------------------------------------------------
    
    OBJ_ID          obj_Retain(
        OBJ_ID          objId
    )
    {
        OBJ_DATA        *this = objId;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        if (obj_IsFlag(this, OBJ_FLAG_ALLOC)) {
            if (this->pVtbl->pRetain) {
                this->pVtbl->pRetain(this);
            }
        }
        return objId;
    }
    
    
    OBJ_ID          obj_RetainNull(
        OBJ_ID          objId
    )
    {
        return objId;
    }
    
    
    OBJ_ID          obj_RetainStandard(
        OBJ_ID          objId
    )
    {
        OBJ_DATA        *this = objId;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        if (obj_IsFlag(this, OBJ_FLAG_ALLOC)) {
            ++this->cbRetainCount;
        }
        return objId;
    }
    
    

    //---------------------------------------------------------------
    //              T o  D e b u g  S t r i n g
    //---------------------------------------------------------------
    
    OBJ_ID          obj_ToDebugString(
        OBJ_ID          objId,
        int             indent
    )
    {
        OBJ_DATA        *this = objId;
        OBJ_ID          *pStr = OBJ_NIL;
        OBJ_IUNKNOWN    *pVtbl;
        
        if (OBJ_NIL == this) {
            return pStr;
        }
        pVtbl = obj_getVtbl(this);
        if (NULL == pVtbl) {
            return pStr;
        }
        pStr = pVtbl->pToDebugString(this, indent);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                          T r a c e
    //---------------------------------------------------------------
    
    bool            obj_Trace(
        OBJ_ID          objId
    )
    {
        OBJ_DATA		*this = objId;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (OBJ_NIL == this) {
            return false;
        }
#endif
        
        if (this->cbFlags & (1 << OBJ_FLAG_TRACE))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    bool            obj_TraceSet(
        OBJ_ID          objId,
        bool            fValue
    )
    {
        OBJ_DATA		*this = objId;
        bool            old;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (OBJ_NIL == this) {
            return false;
        }
#endif
        old = obj_Trace(objId);

        if (fValue) {
            this->cbFlags |= (1 << OBJ_FLAG_TRACE);
        }
        else {
            this->cbFlags &= ~(1 << OBJ_FLAG_TRACE);
        }
        
        // Return to caller.
        return old;
    }
    
    
    
    

    
    
#ifdef	__cplusplus
};
#endif






