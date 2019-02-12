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
#include        <path.h>
#include        <szData.h>
#include        <stdarg.h>
#include        <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct node_class_desc_s {
        int             integer;
        const
        char            *pDescription;
    } NODE_CLASS_DESC;

    
    static
    NODE_CLASS_DESC     classTable[] = {
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
        NODE_CLASS_DATA *pClass;
        
        this = node_Alloc( );
        if (this) {
            pClass = node_Class( );
            this = node_Init(this);
            if (this)
                this->unique = ++pClass->unique;
        }
        
        return this;
    }
    
    
    
    NODE_DATA *     node_NewWithInt(
        int64_t         ident,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *this;
        
        this = node_New( );
        if (this) {
            this->pName = name_NewInt(ident);
            if (OBJ_NIL == this->pName) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            node_setData(this, pData);
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
        
        this = node_New( );
        if (this) {
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
        }
        
        return this;
    }
    
    
    
    NODE_DATA *     node_NewWithUTF8AndClass(
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *this;
        NAME_DATA       *pName = OBJ_NIL;
        
        if (OBJ_NIL == pNameA) {
            return OBJ_NIL;
        }
        
        this = node_New( );
        if (this) {
            if (pNameA) {
                pName = name_NewUTF8(pNameA);
                node_setName(this, pName);
                obj_Release(pName);
                pName = OBJ_NIL;
            }
            node_setClass(this, cls);
            node_setData(this, pData);
        }
        
        return this;
    }
    
    
    
    NODE_DATA *     node_NewWithUTF8ConAndClass(
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *this;
        NAME_DATA       *pName = OBJ_NIL;

        if (OBJ_NIL == pNameA) {
            return OBJ_NIL;
        }
        
        this = node_New( );
        if (this) {
            if (pNameA) {
                pName = name_NewUTF8Con(pNameA);
                node_setName(this, pName);
                obj_Release(pName);
                pName = OBJ_NIL;
            }
            node_setClass(this, cls);
            node_setData(this, pData);
        }
        
        return this;
    }
    
    
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

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
            return 0;
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
            return OBJ_NIL;
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
            return OBJ_NIL;
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
        
        return hash;
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
            return 0;
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
            return 0;
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
            return OBJ_NIL;
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
            return 0;
        }
#endif
        
        return name_getInt(this->pName);
    }
    
    
    
    char *          node_getNameUTF8(
        NODE_DATA       *this
    )
    {
        char            *pStrA = NULL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        if (this->pName) {
            pStrA = name_getUTF8(this->pName);
        }
        
        return pStrA;
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
            return OBJ_NIL;
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
    //                      P r o p e r t i e s
    //---------------------------------------------------------------
    
    NODEBTP_DATA *  node_getProperties(
        NODE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pProperties;
    }
    
    
    bool            node_setProperties(
        NODE_DATA       *this,
        NODEBTP_DATA    *pValue
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
            return 0;
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
            return false;
        }
#endif
        this->type = value;
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       U n i q u e
    //---------------------------------------------------------------
    
    uint32_t        node_getUnique(
        NODE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->unique;
    }
    
    
    bool            node_setUnique(
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
        this->unique = value;
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
        node_setExtra(pOther, OBJ_NIL);
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
        if (this->pExtra) {
            if (obj_getVtbl(this->pExtra)->pCopy) {
                pOther->pExtra = obj_getVtbl(this->pExtra)->pCopy(this->pExtra);
            }
            else {
                obj_Retain(this->pExtra);
                pOther->pExtra = this->pExtra;
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
        pOther->type = this->type;
        obj_FlagSet(pOther, NODE_DUP_NAME, obj_Flag(this, NODE_DUP_NAME));
        obj_setMisc2(pOther, obj_getMisc2(this));

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
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        int             i = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !node_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        i = node_getClass((NODE_DATA *)this) - node_getClass((NODE_DATA *)pOther);
        if (0 == i) {
            eRc =   name_Compare(
                            node_getName((NODE_DATA *)this),
                            node_getName((NODE_DATA *)pOther)
                    );
            return eRc;
        }
        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        

        return eRc;
    }
    
    
    ERESULT         node_CompareA(
        NODE_DATA       *this,
        int32_t         cls,
        const
        char            *pName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pName) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (0 == cls) {
            eRc = name_CompareA(this->pName, pName);
        }
        else {
            int         iRc;
            iRc = node_getClass(this) - cls;
            if (0 == iRc) {
                eRc = name_CompareA(this->pName, pName);
                return eRc;
            }
            if (iRc < 0) {
                eRc = ERESULT_SUCCESS_GREATER_THAN;
            }
            else {
                eRc = ERESULT_SUCCESS_LESS_THAN;
            }
            
        }
        
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
            return OBJ_NIL;
        }
        
        // Make a copy of the optional data.
        if (this->pData) {
            if (obj_getVtbl(this->pData)->pDeepCopy) {
                pData = obj_getVtbl(this->pData)->pDeepCopy(this->pData);
            }
            else {
                return OBJ_NIL;
            }
        }
        
        // Make a copy of the required name.
        if (this->pName) {
            if (obj_getVtbl(this->pName)->pDeepCopy) {
                pData = obj_getVtbl(this->pName)->pDeepCopy(this->pName);
            }
            else {
                return OBJ_NIL;
            }
        }
        else {
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
            return pArray;
        }
        
        if (obj_IsKindOf(pData, OBJ_IDENT_NODEHASH)) {
            pArray = nodeHash_Nodes((NODEHASH_DATA *)pData);
        }
        else if (obj_IsKindOf(pData,OBJ_IDENT_NODEARRAY)) {
            pArray = nodeArray_Copy((NODEARRAY_DATA *)pData);
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
        
        this = obj_Init(this, cbSize, OBJ_IDENT_NODE);
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
    
    OBJ_ID          node_PropertyA (
        NODE_DATA       *this,
        const
        char            *pNameA
    )
    {
        OBJ_ID          pProperty = OBJ_NIL;
        NODE_DATA       *pFound = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!node_Validate( this )) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (NULL == pNameA) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            pFound = nodeBTP_FindA(this->pProperties, 0, pNameA);
            if (pFound) {
                pProperty = node_getData(pFound);
            }
        }
        
        // Return to caller.
        return pProperty;
    }
    
    
    
    //---------------------------------------------------------------
    //                     P r o p e r t y  A d d
    //---------------------------------------------------------------
    
    ERESULT         node_PropertyAddA(
        NODE_DATA       *this,
        const
        char            *pNameA,
        OBJ_ID          pData
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (OBJ_NIL == this->pProperties) {
            this->pProperties = nodeBTP_New( );
            if (OBJ_NIL == this->pProperties) {
                eRc = ERESULT_OUT_OF_MEMORY;
                goto eom;
            }
        }
        
        pNode = node_NewWithUTF8AndClass(0, pNameA, pData);
        if (pNode == OBJ_NIL) {
            eRc = ERESULT_OUT_OF_MEMORY;
            goto eom;
        }
        eRc = nodeBTP_Add(this->pProperties, pNode, true);
        obj_Release(pNode);
        pNode = OBJ_NIL;
        if (ERESULT_FAILED(eRc)) {
            goto eom;
        }
        
        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        return eRc;
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
            num = nodeBTP_getSize(this->pProperties);
        }
        
        // Return to caller.
        return num;
    }
    
    
    
    //---------------------------------------------------------------
    //                    P r o p e r t y  K e y s
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * node_Properties(
        NODE_DATA       *this
    )
    {
        NODEARRAY_DATA  *pArray = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            pArray = nodeBTP_Nodes(this->pProperties);
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
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return node_ToJSON;
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
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        char            *pName;
        OBJ_IUNKNOWN    *pVtbl;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        pName = node_getNameUTF8(this);
        AStr_AppendPrint(
                    pStr,
                     "{%p(node) Name=%s class=%d misc1=%d misc2=%d\n",
                     this,
                     pName,
                     node_getClass(this),
                     node_getMisc1(this),
                     node_getMisc2(this)
            );
        mem_Free((void *)pName);
        
        AStr_AppendCharRepeatA(pStr, indent, ' ');

        if (this->pData) {
            AStr_AppendCharRepeatA(pStr, indent+3, ' ');
            AStr_AppendA(pStr, "Data:\n");
            pVtbl = obj_getVtbl(this->pData);
            if (pVtbl && pVtbl->pToDebugString) {
                pWrkStr = pVtbl->pToDebugString(this->pData, indent+6);
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        
        if (this->pProperties) {
            AStr_AppendCharRepeatA(pStr, indent+3, ' ');
            AStr_AppendA(pStr, "Properties:\n");
            if (this->pProperties) {
                pVtbl = obj_getVtbl(this->pProperties);
                if (pVtbl && pVtbl->pToDebugString) {
                    pWrkStr = pVtbl->pToDebugString(this->pData, indent+6);
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
        
        if (this->pOther) {
            AStr_AppendCharRepeatA(pStr, indent+3, ' ');
            AStr_AppendA(pStr, "Other:\n");
            if (this->pOther) {
                pVtbl = obj_getVtbl(this->pOther);
                if (pVtbl && pVtbl->pToDebugString) {
                    pWrkStr = pVtbl->pToDebugString(this->pData, indent+6);
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
        
        AStr_AppendA(pStr, "\n");
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        AStr_AppendPrint(pStr, " %p(node)}\n", this);
        
        return pStr;
    }
    
    
    ASTR_DATA *     node_ToString_Data(
        NODE_DATA       *this
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        void *          (*pQueryInfo)(
            OBJ_ID          objId,
            uint32_t        type,
            void            *pData
        );
        ASTR_DATA *     (*pToString)(
            OBJ_ID          objId
        );

        // Do initialization.
#ifdef NDEBUG
#else
        if( !node_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pData) {
            if (obj_IsKindOf(this, OBJ_IDENT_ASTR)) {
                pStr = AStr_Copy((ASTR_DATA *)this->pData);
            }
            else if (obj_IsKindOf(this, OBJ_IDENT_PATH)) {
                pStr = AStr_Copy(path_getAStr((PATH_DATA *)this->pData));
            }
            else {
                pQueryInfo = obj_getVtbl(this->pData)->pQueryInfo;
                if (pQueryInfo) {
                    pToString = (*pQueryInfo)(
                                        this->pData,
                                        OBJ_QUERYINFO_TYPE_METHOD,
                                        "ToString"
                                );
                    if (pToString) {
                        pStr = (*pToString)(this->pData);
                    }
                }
            }
        }

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
            if ( obj_IsKindOf(this, OBJ_IDENT_NODE) )
                ;
            else if ( obj_IsKindOf(this, OBJ_IDENT_NODELINK) )
                ;
            else if ( obj_IsKindOf(this, OBJ_IDENT_NODELNKP) )
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


