// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   node.c
 *	Generated 06/30/2015 22:51:43
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
#include        "node_internal.h"
#include        <stdarg.h>
#include        <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    
    

    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODE_DATA *     node_Alloc(
    )
    {
        NODE_DATA       *this;
        uint32_t        cbSize = sizeof(NODE_DATA);
        
        // Do initialization.

        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODE_DATA *     node_NewWithInt(
        int64_t         ident,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *this;
        
        this = node_Alloc( );
        if (this) {
            this = node_InitWithInt(this, ident, pData);
        }
        
        return this;
    }
    
    
    
    NODE_DATA *     node_NewWithName(
        NAME_DATA       *pName,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *this;
        
        if (OBJ_NIL == pName) {
            return OBJ_NIL;
        }
        
        this = node_Alloc( );
        if (this) {
            this = node_InitWithName(this, pName, pData);
        }
        
        return this;
    }
    
    
    
    NODE_DATA *     node_NewWithPtr(
        const
        void            *pValue,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *this;
        
        this = node_Alloc( );
        if (this) {
            this = node_InitWithPtr(this, pValue, pData);
        }
        
        return this;
    }
    
    
    
    NODE_DATA *     node_NewWithUTF8(
        const
        char            *pName,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *this;
        
        if (OBJ_NIL == pName) {
            return OBJ_NIL;
        }
        
        this = node_Alloc( );
        if (this) {
            this = node_InitWithUTF8(this, pName, pData);
        }
        
        return this;
    }
    
    
    
    NODE_DATA *     node_NewWithUTF8AndClass(
        const
        char            *pName,
        int32_t         cls,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *this;
        
        if (OBJ_NIL == pName) {
            return OBJ_NIL;
        }
        
        this = node_Alloc( );
        if (this) {
            this = node_InitWithUTF8(this,pName,pData);
            if (this) {
                node_setClass(this, cls);
            }
        }
        
        return this;
    }
    
    
    NODE_DATA *     node_NewWithUTF8Con(
        const
        char            *pName,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *this;
        
        if (OBJ_NIL == pName) {
            return OBJ_NIL;
        }
        
        this = node_Alloc( );
        if (this) {
            this = node_InitWithUTF8Con(this,pName,pData);
        }
        
        return this;
    }
    
    
    NODE_DATA *     node_NewWithUTF8ConAndClass(
        const
        char            *pName,
        int32_t         cls,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *this;
        
        if (OBJ_NIL == pName) {
            return OBJ_NIL;
        }
        
        this = node_Alloc( );
        if (this) {
            this = node_InitWithUTF8Con(this,pName,pData);
            if (this) {
                node_setClass(this, cls);
            }
        }
        
        return this;
    }
    
    
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    int32_t         node_getClass(
        NODE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->cls;
    }
    
    
    bool            node_setClass(
        NODE_DATA       *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->cls = value;
        return true;
    }
    
    
    
    OBJ_ID          node_getData(
        NODE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pData;
    }
    
    
    bool            node_setData(
        NODE_DATA       *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pData) {
            obj_Release(this->pData);
        }
        this->pData = pValue;
        
        return true;
    }
    
    
    
    void *          node_getExtra(
        NODE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pExtra;
    }
    
    
    bool            node_setExtra(
        NODE_DATA       *this,
        void            *pValue
                                 )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pExtra = pValue;
        
        return true;
    }
    
    
    
    uint32_t        node_getIndex(
        NODE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->index;
    }
    
    
    bool            node_setIndex(
        NODE_DATA       *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        this->index = value;
        
        return true;
    }
    
    
    
    uint16_t        node_getMisc(
        NODE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return obj_getMisc2(this);
    }
    
    
    bool            node_setMisc(
        NODE_DATA       *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_setMisc2(this, value);
        return true;
    }
    
    
    
    NAME_DATA *     node_getName(
        NODE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pName;
    }

    
    const
    void *          node_getNamePtr(
        NODE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return name_getPtr(this->pName);
    }
    
    
    const
    char *          node_getNameUTF8(
        NODE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return name_getUTF8(this->pName);
    }
    
    

    bool            node_setName(
        NODE_DATA       *this,
        NAME_DATA       *pValue
    )
    {
#ifdef XYZZY
        ERESULT         eRc;
#endif
        
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pName) {
            obj_Release(this->pName);
        }
        this->pName = pValue;

#ifdef XYZZY
        eRc = szTbl_StringToString(szTbl_Shared(), pValue, &cbp->pName);
        if (ERESULT_FAILURE(eRc)) {
            return false;
        }
#endif
        
        return true;
    }
    
    
    
    OBJ_ID          node_getOther(
        NODE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pOther;
    }
    
    
    bool            node_setOther(
        NODE_DATA       *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pOther) {
            obj_Release(this->pOther);
        }
        this->pOther = pValue;
        
        return true;
    }
    
    
    
    NODEARRAY_DATA * node_getProperties(
        NODE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pProperties;
    }
    
    
    bool            node_setProperties(
        NODE_DATA       *this,
        NODEARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pProperties) {
            obj_Release(this->pProperties);
        }
        this->pProperties = pValue;
        
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         node_Assign(
        NODE_DATA       *this,
        NODE_DATA       *pOther
    )
    {
        
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !node_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        // Release objects and areas in other object.
        node_setName(pOther, OBJ_NIL);
        node_setData(pOther, OBJ_NIL);
        node_setOther(pOther, OBJ_NIL);
        node_setProperties(pOther, OBJ_NIL);
        
        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pName) {
            if (obj_getVtbl(this->pName)->pCopy) {
                pOther->pName = obj_getVtbl(this->pName)->pCopy(this->pName);
            }
            else {
                obj_Retain(this->pName);
                pOther->pName = this->pName;
            }
        }
        if (this->pData) {
            if (obj_getVtbl(this->pData)->pCopy) {
                pOther->pData = obj_getVtbl(this->pData)->pCopy(this->pData);
            }
            else {
                obj_Retain(this->pData);
                pOther->pData = this->pData;
            }
        }
        if (this->pOther) {
            if (obj_getVtbl(this->pOther)->pCopy) {
                pOther->pOther = obj_getVtbl(this->pOther)->pCopy(this->pOther);
            }
            else {
                obj_Retain(this->pOther);
                pOther->pOther = this->pOther;
            }
        }
        if (this->pProperties) {
            if (obj_getVtbl(this->pProperties)->pCopy) {
                pOther->pProperties = obj_getVtbl(this->pProperties)->pCopy(this->pProperties);
            }
            else {
                obj_Retain(this->pProperties);
                pOther->pProperties = this->pProperties;
            }
        }
        
        // Copy other data from this object to other.
        pOther->cls = this->cls;
        pOther->index = this->index;
        pOther->pExtra = this->pExtra;

        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                        C o m p a r e
    //---------------------------------------------------------------
    
    ERESULT         node_Compare(
        NODE_DATA		*this,
        NODE_DATA       *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate( this ) ) {
            DEBUG_BREAK();
            return -1;
        }
        if( !node_Validate( pOther ) ) {
            DEBUG_BREAK();
            return -1;
        }
#endif

        eRc = name_Compare(this->pName, pOther->pName);
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    NODE_DATA *     node_Copy(
        NODE_DATA       *this
    )
    {
        NODE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        OBJ_ID          *pData = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        // Make a copy of the data.
        if (this->pData) {
            if (obj_getVtbl(this->pData)->pCopy) {
                pData = obj_getVtbl(this->pData)->pCopy(this->pData);
            }
        }
        pOther = node_NewWithName(this->pName,pData);
        obj_Release(pData);
        pData = OBJ_NIL;
        if (this->pOther) {
            if (obj_getVtbl(this->pOther)->pCopy) {
                pData = obj_getVtbl(this->pOther)->pCopy(this->pOther);
            }
        }
        node_setOther(pOther, pData);
        obj_Release(pData);
        pData = OBJ_NIL;
        
        DEBUG_BREAK();                      //ERESULT_NOT_IMPLEMENTED;
        
        //FIXME: Assign does not work!
        eRc = node_Assign(this, pOther);
        if (ERESULT_HAS_FAILED(eRc)) {
            obj_Release(pOther);
            pOther = OBJ_NIL;
            return OBJ_NIL;
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            node_Dealloc(
        OBJ_ID          objId
    )
    {
        NODE_DATA       *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        node_setProperties(this, OBJ_NIL);
        node_setData(this, OBJ_NIL);
        node_setName(this, OBJ_NIL);
        node_setOther(this, OBJ_NIL);

        obj_setVtbl(this, (OBJ_IUNKNOWN *)this->pSuperVtbl);
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODE_DATA *     node_Init(
        NODE_DATA       *this
    )
    {
        uint16_t        cbSize = sizeof(NODE_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, cbSize, OBJ_IDENT_NODE );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&node_Vtbl);
        
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->pProperties);
#endif

        return this;
    }

     

    NODE_DATA *     node_InitWithInt(
        NODE_DATA       *this,
        int64_t         ident,
        OBJ_ID          pData
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = node_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pName = name_NewInt(ident);
        if (OBJ_NIL == this->pName) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        node_setData(this, pData);
        
        return this;
    }
    
    
    
    NODE_DATA *     node_InitWithName(
        NODE_DATA       *this,
        NAME_DATA       *pName,
        OBJ_ID          pData
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = node_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        if (pName) {
            obj_Retain(pName);
            this->pName = pName;
            if (OBJ_NIL == this->pName) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
        }
        
        node_setData(this, pData);
        
        return this;
    }
    
    
    
    NODE_DATA *     node_InitWithPtr(
        NODE_DATA       *this,
        const
        void            *pValue,
        OBJ_ID          pData
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = node_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        if (pValue) {
            this->pName = name_NewPtr(pValue);
            if (OBJ_NIL == this->pName) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
        }
        
        node_setData(this, pData);
        
        return this;
    }
    
    
    
    NODE_DATA *     node_InitWithUTF8(
        NODE_DATA       *this,
        const
        char            *pName,
        OBJ_ID          pData
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = node_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        if (pName) {
            this->pName = name_NewUTF8(pName);
            if (OBJ_NIL == this->pName) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
        }
        
        node_setData(this, pData);
        
        return this;
    }
    
    
    
    NODE_DATA *     node_InitWithUTF8Con(
        NODE_DATA       *this,
        const
        char            *pName,
        OBJ_ID          pData
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = node_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        if (pName) {
            this->pName = name_NewUTF8Con(pName);
            if (OBJ_NIL == this->pName) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
        }
        
        node_setData(this, pData);
        
        return this;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            node_IsEnabled(
        NODE_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(this))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                    P r o p e r t y  G e t
    //---------------------------------------------------------------
    
    NODE_DATA *     node_Property(
        NODE_DATA       *this,
        const
        char            *pName
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pProperty = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            eRc = nodeArray_FindA(this->pProperties, pName, &pProperty);
        }
        
        // Return to caller.
        return pProperty;
    }
    
    
    
    //---------------------------------------------------------------
    //                     P r o p e r t y  A d d
    //---------------------------------------------------------------
    
    ERESULT         node_PropertyAdd(
        NODE_DATA       *this,
        NODE_DATA       *pData
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pData) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (OBJ_NIL == this->pProperties) {
            this->pProperties = nodeArray_New( );
            if (OBJ_NIL == this->pProperties) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        eRc = nodeArray_AppendNode(this->pProperties, pData, NULL );
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //              P r o p e r t y  C o u n t
    //---------------------------------------------------------------
    
    uint16_t        node_PropertyCount(
        NODE_DATA		*this
    )
    {
        uint16_t        num = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (this->pProperties) {
            num = nodeArray_getSize(this->pProperties);
        }
        
        // Return to caller.
        return num;
    }
    
    
    
    //---------------------------------------------------------------
    //                    P r o p e r t i e s
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * node_Properties(
        NODE_DATA       *this
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            eRc = nodeArray_SortAscending(this->pProperties);
        }
        
        // Return to caller.
        return this->pProperties;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     node_ToDebugString(
        NODE_DATA       *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        char            *pName;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        str[0] = '\0';
        pName = node_getNameUTF8(this);
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(node) Name=%s class=%d index=%d misc=%d\n",
                     this,
                     pName,
                     node_getClass(this),
                     node_getIndex(this),
                     node_getMisc(this)
            );
        mem_Free((void *)pName);
        AStr_AppendA(pStr, str);
        
        if (this->pData) {
            AStr_AppendCharRepeatA(pStr, indent+3, ' ');
            AStr_AppendA(pStr, "Data:\n");
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+6
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        
        if (this->pProperties) {
            AStr_AppendCharRepeatA(pStr, indent+3, ' ');
            AStr_AppendA(pStr, "Properties:\n");
            if (this->pProperties) {
                if (((OBJ_DATA *)(this->pProperties))->pVtbl->pToDebugString) {
                    pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pProperties,
                                                    indent+6
                                );
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
        
        if (this->pOther) {
            AStr_AppendCharRepeatA(pStr, indent+3, ' ');
            AStr_AppendA(pStr, "Other:\n");
            if (this->pOther) {
                if (((OBJ_DATA *)(this->pOther))->pVtbl->pToDebugString) {
                    pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pOther,
                                                    indent+6
                                );
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
        
        AStr_AppendA(pStr, "\n");
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        j = snprintf( str, sizeof(str), " %p(node)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            node_Validate(
        NODE_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_NODE) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(NODE_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


