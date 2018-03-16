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
#include        <node_internal.h>
#include        <AStrArray.h>
#include        <objArray.h>
#include        <szData.h>
#include        <stdarg.h>
#include        <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct node_class_data_s {
        int             integer;
        const
        char            *pDescription;
    } NODE_CLASS_DATA;
    
    static
    NODE_CLASS_DATA     classTable[] = {
        {NODE_CLASS_UNKNOWN,    "NODE_CLASS_UNKNOWN"},
        {NODE_CLASS_ROOT,       "NODE_CLASS_ROOT"},
        {NODE_CLASS_ANY,        "NODE_CLASS_ANY"},
        {NODE_CLASS_KLEENE,     "NODE_CLASS_KLEENE"},
        {NODE_CLASS_INTEGER,    "NODE_CLASS_INTEGER"},
        {NODE_CLASS_STRING,     "NODE_CLASS_STRING"},
        {NODE_CLASS_OPEN,       "NODE_CLASS_OPEN"},
        {NODE_CLASS_CLOSE,      "NODE_CLASS_CLOSE"},
        {NODE_CLASS_USER,       "NODE_CLASS_USER"},
    };
    static
    int                 cClassTable = (sizeof(classTable) / sizeof(NODE_CLASS_DATA));

    
    
 
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



    const
    char *          node_FindClassDescription(
        int             class
    )
    {
        int             i;
        
        for(i=0; i<cClassTable; ++i) {
            if (class == classTable[i].integer) {
                return classTable[i].pDescription;
            }
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    
    int             node_FindClassInteger(
        const
        char            *pDesc
    )
    {
        int             i;
        
        for(i=0; i<cClassTable; ++i) {
            if (0 == strcmp(pDesc, classTable[i].pDescription)) {
                return classTable[i].integer;
            }
        }
        
        // Return to caller.
        return -1;
    }
    
    
    
    NODE_DATA *     node_New(
    )
    {
        NODE_DATA       *this;
        
        this = node_Alloc( );
        if (this) {
            this = node_Init(this);
        }
        
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

    //---------------------------------------------------------------
    //                      C h i l d  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        node_getChild(
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
        
        return this->leftIndex;
    }
    
    
    bool            node_setChild(
        NODE_DATA       *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->leftIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C l a s s
    //---------------------------------------------------------------
    
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
    
    
    
    //---------------------------------------------------------------
    //                          D a t a
    //---------------------------------------------------------------
    
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
    
    
    
    //---------------------------------------------------------------
    //                          E x t r a
    //---------------------------------------------------------------
    
    OBJ_ID          node_getExtra(
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
        if (this->pExtra) {
            obj_Release(this->pExtra);
        }
        this->pExtra = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      F r o m  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        node_getFrom(
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
        
        return this->leftIndex;
    }
    
    
    bool            node_setFrom(
        NODE_DATA       *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->leftIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------
    
    uint32_t        node_getHash(
        NODE_DATA       *this
    )
    {
        uint32_t        hash = 0;
        ERESULT         eRc = ERESULT_KEY_NOT_FOUND;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return hash;
        }
#endif
        
        if (this->pName) {
            hash = name_getHash(this->pName);
            eRc = ERESULT_SUCCESS;
        }
        
        this->eRc = eRc;
        return hash;
    }
    
    
    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------
    
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
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         node_getLastError(
        NODE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    bool            node_setLastError(
        NODE_DATA       *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L e f t  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        node_getLeft(
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
        
        return this->leftIndex;
    }
    
    
    bool            node_setLeft(
        NODE_DATA       *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->leftIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                   M i d d l e  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        node_getMiddle(
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
        
        return this->middleIndex;
    }
    
    
    bool            node_setMiddle(
        NODE_DATA       *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->middleIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          M i s c
    //---------------------------------------------------------------
    
    uint16_t        node_getMisc1(
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
        
        return obj_getMisc1(this);
    }
    
    
    bool            node_setMisc1(
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
        obj_setMisc1(this, value);
        return true;
    }
    
    
    
    uint16_t        node_getMisc2(
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
    
    
    bool            node_setMisc2(
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
    
    
    
    //---------------------------------------------------------------
    //                          N a m e
    //---------------------------------------------------------------
    
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

    
    uint64_t        node_getNameInt(
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
        
        return name_getInt(this->pName);
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
    
    
    
    //---------------------------------------------------------------
    //                          O t h e r
    //---------------------------------------------------------------
    
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
    
    
    
    //---------------------------------------------------------------
    //                   P a r e n t  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        node_getParent(
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
        
        return this->parentIndex;
    }
    
    
    bool            node_setParent(
        NODE_DATA       *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->parentIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P r o p e r t i e s
    //---------------------------------------------------------------
    
    OBJHASH_DATA * node_getProperties(
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
        OBJHASH_DATA    *pValue
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
    
    
    
    //---------------------------------------------------------------
    //                      R i g h t  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        node_getRight(
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
        
        return this->rightIndex;
    }
    
    
    bool            node_setRight(
        NODE_DATA       *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->rightIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                    S i b l i n g  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        node_getSibling(
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
        
        return this->rightIndex;
    }
    
    
    bool            node_setSibling(
        NODE_DATA       *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->rightIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                    T o  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        node_getTo(
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
        
        return this->rightIndex;
    }
    
    
    bool            node_setTo(
        NODE_DATA       *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->rightIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          T y p e
    //---------------------------------------------------------------
    
    int32_t         node_getType(
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
        
        return this->type;
    }
    
    
    bool            node_setType(
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
        this->type = value;
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        A c c e p t
    //---------------------------------------------------------------
    
    ERESULT         node_Accept(
        NODE_DATA        *this,
        VISITOR_DATA     *pVisitor
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        ERESULT         (*pMethod)(VISITOR_DATA *this, NODE_DATA *pObj) = NULL;
        const
        OBJ_IUNKNOWN    *pVtbl;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pVisitor ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pStr = AStr_NewA("Visit_node_");
        if (OBJ_NIL == pStr) {
            return ERESULT_OUT_OF_MEMORY;
        }
        AStr_AppendHex32(pStr, this->type);
        
        pVtbl = obj_getVtbl(pVisitor);
        if (pVtbl && pVtbl->pQueryInfo) {
            pMethod =   pVtbl->pQueryInfo(
                                pVisitor,
                                OBJ_QUERYINFO_TYPE_METHOD,
                                (void *)AStr_getData(pStr)
                        );
        }
        
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        if (NULL == pMethod) {
            DEBUG_BREAK();
            return ERESULT_INVALID_FUNCTION;
        }
        
        eRc = pMethod(pVisitor, this);
        
        return eRc;
    }
    
    
    
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
    //                      D e e p  C o p y
    //---------------------------------------------------------------
    
    NODE_DATA *     node_DeepCopy(
        NODE_DATA       *this
    )
    {
        NODE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        OBJ_ID          *pData = OBJ_NIL;
        NAME_DATA       *pName = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = node_New( );
        if (OBJ_NIL == pOther) {
            node_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        
        // Make a copy of the optional data.
        if (this->pData) {
            if (obj_getVtbl(this->pData)->pDeepCopy) {
                pData = obj_getVtbl(this->pData)->pDeepCopy(this->pData);
            }
            else {
                node_setLastError(this, ERESULT_GENERAL_FAILURE);
                return OBJ_NIL;
            }
        }
        
        // Make a copy of the required name.
        if (this->pName) {
            if (obj_getVtbl(this->pName)->pDeepCopy) {
                pData = obj_getVtbl(this->pName)->pDeepCopy(this->pName);
            }
            else {
                node_setLastError(this, ERESULT_GENERAL_FAILURE);
                return OBJ_NIL;
            }
        }
        else {
            node_setLastError(this, ERESULT_GENERAL_FAILURE);
            return OBJ_NIL;
        }

        pOther = node_NewWithName(pName, pData);
        obj_Release(pData);
        pData = OBJ_NIL;
        obj_Release(pName);
        pName = OBJ_NIL;
        if (this->pOther) {
            if (obj_getVtbl(this->pOther)->pDeepCopy) {
                pData = obj_getVtbl(this->pOther)->pDeepCopy(this->pOther);
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
    //                 D a t a  T o  A r r a y
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * node_DataToArray(
        NODE_DATA       *this
    )
    {
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        OBJ_ID          *pData = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pData = node_getData(this);
        if (OBJ_NIL == pData) {
            node_setLastError(this, ERESULT_DATA_MISSING);
            return pArray;
        }
        
        if (obj_IsKindOf(pData,OBJ_IDENT_NODEHASH)) {
            this->eRc = nodeHash_Nodes((NODEHASH_DATA *)pData, &pArray);
        }
        else if (obj_IsKindOf(pData,OBJ_IDENT_NODEARRAY)) {
            pArray = nodeArray_Copy((NODEARRAY_DATA *)pData);
            if (pArray) {
                node_setLastError(this, ERESULT_SUCCESS);
            }
            else {
                node_setLastError(this, ERESULT_DATA_ERROR);
            }
        }
        else {
            node_setLastError(this, ERESULT_DATA_MISSING);
        }

        // Return to caller.
        return pArray;
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
        node_setExtra(this, OBJ_NIL);
        node_setName(this, OBJ_NIL);
        node_setOther(this, OBJ_NIL);

        obj_setVtbl(this, (OBJ_IUNKNOWN *)this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

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
    
    OBJ_ID          node_Property(
        NODE_DATA       *this,
        const
        char            *pName
    )
    {
        OBJ_ID          pProperty = OBJ_NIL;
        SZDATA_DATA     *pData = OBJ_NIL;
        SZDATA_DATA     *pFound = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            pData = szData_NewA(pName);
            if (pData) {
                pFound = objHash_Find(this->pProperties, pData);
                obj_Release(pData);
                pData = OBJ_NIL;
                if (pFound) {
                    pProperty = szData_getData(pFound);
                }
            }
        }
        
        // Return to caller.
        return pProperty;
    }
    
    
    
    //---------------------------------------------------------------
    //                     P r o p e r t y  A d d
    //---------------------------------------------------------------
    
    ERESULT         node_PropertyAdd(
        NODE_DATA       *this,
        const
        char            *pName,
        NODE_DATA       *pData
    )
    {
        ERESULT         eRc;
        SZDATA_DATA     *pSzData = OBJ_NIL;
        
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
            this->pProperties = objHash_New(OBJHASH_TABLE_SIZE_XXXSMALL);
            if (OBJ_NIL == this->pProperties) {
                this->eRc = ERESULT_OUT_OF_MEMORY;
                goto eom;
            }
        }
        
        pSzData = szData_NewA(pName);
        if (pSzData == OBJ_NIL) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            goto eom;
        }
        szData_setData(pSzData, pData);
        eRc = objHash_Add(this->pProperties, pSzData, NULL);
        if (ERESULT_FAILED(eRc)) {
            this->eRc = eRc;
            goto eom;
        }
        obj_Release(pSzData);
        pSzData = OBJ_NIL;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
    eom:
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //              P r o p e r t y  C o u n t
    //---------------------------------------------------------------
    
    uint32_t        node_PropertyCount(
        NODE_DATA		*this
    )
    {
        uint32_t        num = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (this->pProperties) {
            num = objHash_getSize(this->pProperties);
        }
        
        // Return to caller.
        return num;
    }
    
    
    
    //---------------------------------------------------------------
    //                    P r o p e r t y  K e y s
    //---------------------------------------------------------------
    
    ASTRARRAY_DATA * node_PropertyKeys(
        NODE_DATA       *this
    )
    {
        ERESULT         eRc;
        ASTRARRAY_DATA  *pArray = OBJ_NIL;
        OBJENUM_DATA    *pEnum = OBJ_NIL;
        uint32_t        i;
        SZDATA_DATA     *pData;
        ASTR_DATA       *pStr = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            pEnum = objHash_Enum(this->pProperties);
            if (pEnum ==  OBJ_NIL) {
                return pArray;
            }
            pArray = AStrArray_New();
            if (pArray ==  OBJ_NIL) {
                return pArray;
            }
            for (;;) {
                eRc = objEnum_Next(pEnum, 1, (OBJ_ID *)&pData, &i);
                if (i)
                    ;
                else
                    break;
                pStr = AStr_NewA(szData_getName(pData));
                if (pStr) {
                    eRc = AStrArray_AppendStr(pArray, pStr, NULL);
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
            obj_Release(pEnum);
            pEnum = OBJ_NIL;
        }
        
        // Return to caller.
        return pArray;
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
     void        *pMethod = node_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode
     @param     objId   OBJTEST object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                         for OBJ_QUERYINFO_TYPE_METHOD, this field points to a
                         character string which represents the method name without
                         the object name, "node", prefix,
                         for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                         address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                 OBJ_QUERYINFO_TYPE_INFO: info pointer,
                 OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                 OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          node_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODE_DATA       *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'A':
                        if (str_Compare("Accept", (char *)pStr) == 0) {
                            return node_Accept;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return node_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
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
                     "{%p(node) Name=%s class=%d index=%d misc1=%d misc2=%d\n",
                     this,
                     pName,
                     node_getClass(this),
                     node_getIndex(this),
                     node_getMisc1(this),
                     node_getMisc2(this)
            );
        mem_Free((void *)pName);
        AStr_AppendA(pStr, str);
        
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        AStr_AppendPrint(pStr, "\tleft=%d middle=%d right=%d parent=%d\n",
                         node_getLeft(this),
                         node_getMiddle(this),
                         node_getRight(this),
                         node_getParent(this)
        );

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


