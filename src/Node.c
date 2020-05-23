// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Node.c
 *	Generated 01/12/2020 16:09:18
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
#include        <Node_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    

    typedef struct Node_class_desc_s {
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
    int                 cClassTable = (sizeof(classTable) / sizeof(NODE_CLASS_DESC));



 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            Node_task_body (
        void            *pData
    )
    {
        //NODE_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODE_DATA *     Node_Alloc (
        void
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
    char *          Node_FindClassDescription(
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



    int             Node_FindClassInteger(
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



    NODE_DATA *     Node_New (
        void
    )
    {
        NODE_DATA       *this;
        
        this = Node_Alloc( );
        if (this) {
            this = Node_Init(this);
        } 
        return this;
    }



    NODE_DATA *     Node_NewWithAStr(
        ASTR_DATA       *pName,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *this;

        this = Node_New( );
        if (this) {
            this->pName = Name_NewAStr(pName);
            if (OBJ_NIL == this->pName) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            Node_setData(this, pData);
        }

        return this;
    }



    NODE_DATA *     Node_NewWithInt(
        int64_t         ident,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *this;

        this = Node_New( );
        if (this) {
            this->pName = Name_NewInt(ident);
            if (OBJ_NIL == this->pName) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            Node_setData(this, pData);
        }

        return this;
    }



    NODE_DATA *     Node_NewWithName(
        NAME_DATA       *pName,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *this;

        if (OBJ_NIL == pName) {
            return OBJ_NIL;
        }

        this = Node_New( );
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
            Node_setData(this, pData);
        }

        return this;
    }



    NODE_DATA *     Node_NewWithUTF8AndClass(
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

        this = Node_New( );
        if (this) {
            if (pNameA) {
                pName = Name_NewUTF8(pNameA);
                Node_setName(this, pName);
                obj_Release(pName);
                pName = OBJ_NIL;
            }
            Node_setClass(this, cls);
            Node_setData(this, pData);
        }

        return this;
    }



    NODE_DATA *     Node_NewWithUTF8ConAndClass(
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

        this = Node_New( );
        if (this) {
            if (pNameA) {
                pName = Name_NewUTF8Con(pNameA);
                Node_setName(this, pName);
                obj_Release(pName);
                pName = OBJ_NIL;
            }
            Node_setClass(this, cls);
            Node_setData(this, pData);
        }

        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                    A c c e p t  M e t h o d
    //---------------------------------------------------------------

    bool            Node_setAcceptMethod(
        NODE_DATA       *this,
        ERESULT         (*pAccept)(NODE_DATA *, OBJ_ID)
    )
    {
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pAccept = pAccept;

        return true;
    }



    //---------------------------------------------------------------
    //                          C l a s s
    //---------------------------------------------------------------

    int32_t         Node_getClass(
        NODE_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->cls;
    }


    bool            Node_setClass(
        NODE_DATA       *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->cls = value;
        return true;
    }



    //---------------------------------------------------------------
    //                          D a t a
    //---------------------------------------------------------------

    OBJ_ID          Node_getData(
        NODE_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pData;
    }


    bool            Node_setData(
        NODE_DATA       *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
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

    OBJ_ID          Node_getExtra(
        NODE_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pExtra;
    }


    bool            Node_setExtra(
        NODE_DATA       *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
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

    uint32_t        Node_getHash(
        NODE_DATA       *this
    )
    {
        uint32_t        hash = 0;
        ERESULT         eRc = ERESULT_KEY_NOT_FOUND;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return hash;
        }
#endif

        if (this->pName) {
            hash = Name_getHash(this->pName);
            eRc = ERESULT_SUCCESS;
        }

        return hash;
    }



    //---------------------------------------------------------------
    //                          M i s c
    //---------------------------------------------------------------

    uint32_t        Node_getMisc (
        NODE_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->misc;
    }


    bool            Node_setMisc (
        NODE_DATA       *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->misc = value;

        return true;
    }


    uint16_t        Node_getMisc1(
        NODE_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return obj_getMisc1(this);
    }


    bool            Node_setMisc1(
        NODE_DATA       *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_setMisc1(this, value);
        return true;
    }



    uint16_t        Node_getMisc2(
        NODE_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return obj_getMisc2(this);
    }


    bool            Node_setMisc2(
        NODE_DATA       *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
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

    NAME_DATA *     Node_getName (
        NODE_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Node_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pName;
    }


    bool            Node_setName (
        NODE_DATA       *this,
        NAME_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Node_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pName) {
            obj_Release(this->pName);
        }
        this->pName = pValue;

        return true;
    }


    uint64_t        Node_getNameInt(
        NODE_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Name_getInt(this->pName);
    }


        ASTR_DATA *     Node_getNameStr(
            NODE_DATA       *this
        )
        {

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !Node_Validate(this) ) {
                DEBUG_BREAK();
                return OBJ_NIL;
            }
    #endif

            return Name_getStr(this->pName);
        }


    char *          Node_getNameUTF8(
        NODE_DATA       *this
    )
    {
        char            *pStrA = NULL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        if (this->pName) {
            pStrA = Name_getUTF8(this->pName);
        }

        return pStrA;
    }



    //---------------------------------------------------------------
    //                          O t h e r
    //---------------------------------------------------------------

    OBJ_ID          Node_getOther(
        NODE_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pOther;
    }


    bool            Node_setOther(
        NODE_DATA       *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
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
    //                    P r o p e r t i e s
    //---------------------------------------------------------------

    NODEBT_DATA *   Node_getProperties (
        NODE_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Node_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pProperties;
    }


    bool            Node_setProperties (
        NODE_DATA       *this,
        NODEBT_DATA     *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Node_Validate(this)) {
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
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Node_getSize (
        NODE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Node_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Node_getSuperVtbl (
        NODE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Node_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          T y p e
    //---------------------------------------------------------------

    int32_t         Node_getType(
        NODE_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->type;
    }


    bool            Node_setType(
        NODE_DATA       *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
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

    uint32_t        Node_getUnique(
        NODE_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->unique;
    }


    bool            Node_setUnique(
        NODE_DATA       *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
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

    ERESULT         Node_Accept(
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
        if( !Node_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pVisitor ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pStr = AStr_NewA("Visit_Node_");
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
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = Node_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NODE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Node_Assign (
        NODE_DATA		*this,
        NODE_DATA       *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Node_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Node_Validate(pOther)) {
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
        Node_setName(pOther, OBJ_NIL);
        Node_setData(pOther, OBJ_NIL);
        Node_setExtra(pOther, OBJ_NIL);
        Node_setOther(pOther, OBJ_NIL);
        Node_setProperties(pOther, OBJ_NIL);

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
        obj_setMisc(pOther, obj_getMisc(this));
        obj_setMisc1(pOther, obj_getMisc1(this));
        obj_setMisc2(pOther, obj_getMisc2(this));
        // We skip unique on purpose.

        //goto eom;

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
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         Node_Compare (
        NODE_DATA     *this,
        NODE_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!Node_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Node_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        i = Node_getClass((NODE_DATA *)this) - Node_getClass((NODE_DATA *)pOther);
        if (0 == i) {
            eRc =   Name_Compare(
                            Node_getName((NODE_DATA *)this),
                            Node_getName((NODE_DATA *)pOther)
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
    
   
     ERESULT         Node_CompareA(
         NODE_DATA       *this,
         int32_t         cls,
         const
         char            *pName
     )
     {
         ERESULT         eRc = ERESULT_SUCCESS_EQUAL;

         // Do initialization.
 #ifdef NDEBUG
 #else
         if( !Node_Validate( this ) ) {
             DEBUG_BREAK();
             return ERESULT_INVALID_OBJECT;
         }
         if (NULL == pName) {
             DEBUG_BREAK();
             return ERESULT_INVALID_PARAMETER;
         }
 #endif

         if (0 == cls) {
             eRc = Name_CompareA(this->pName, pName);
         }
         else {
             int         iRc;
             iRc = Node_getClass(this) - cls;
             if (0 == iRc) {
                 eRc = Name_CompareA(this->pName, pName);
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
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Node      *pCopy = Node_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NODE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODE_DATA *     Node_Copy (
        NODE_DATA       *this
    )
    {
        NODE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Node_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Node_New( );
        if (pOther) {
            eRc = Node_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D e e p  C o p y
    //---------------------------------------------------------------

    NODE_DATA *     Node_DeepCopy(
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
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pOther = Node_New( );
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

        pOther = Node_NewWithName(pName, pData);
        obj_Release(pData);
        pData = OBJ_NIL;
        obj_Release(pName);
        pName = OBJ_NIL;
        if (this->pOther) {
            if (obj_getVtbl(this->pOther)->pDeepCopy) {
                pData = obj_getVtbl(this->pOther)->pDeepCopy(this->pOther);
            }
        }
        Node_setOther(pOther, pData);
        obj_Release(pData);
        pData = OBJ_NIL;

        DEBUG_BREAK();                      //ERESULT_NOT_IMPLEMENTED;

        //FIXME: Assign does not work!
        eRc = Node_Assign(this, pOther);
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

    NODEARRAY_DATA * Node_DataToArray(
        NODE_DATA       *this
    )
    {
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        OBJ_ID          *pData = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pData = Node_getData(this);
        if (OBJ_NIL == pData) {
            return pArray;
        }

        if (obj_IsKindOf(pData, OBJ_IDENT_NODEHASH)) {
            pArray = NodeHash_Nodes((NODEHASH_DATA *)pData);
        }
        else if (obj_IsKindOf(pData,OBJ_IDENT_NODEARRAY)) {
            pArray = NodeArray_Copy((NODEARRAY_DATA *)pData);
        }

        // Return to caller.
        return pArray;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            Node_Dealloc (
        OBJ_ID          objId
    )
    {
        NODE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Node_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Node_setName(this, OBJ_NIL);
        Node_setData(this, OBJ_NIL);
        Node_setExtra(this, OBJ_NIL);
        Node_setOther(this, OBJ_NIL);
        Node_setProperties(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
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
    ERESULT         Node_Disable (
        NODE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Node_Validate(this)) {
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
    ERESULT         Node_Enable (
        NODE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Node_Validate(this)) {
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
    //                          I n i t
    //---------------------------------------------------------------

    NODE_DATA *   Node_Init (
        NODE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODE_DATA);
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Node_Vtbl);
        
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
        if (!Node_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "Node::sizeof(NODE_DATA) = %lu\n", sizeof(NODE_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODE_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Node_IsEnabled (
        NODE_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Node_Validate(this)) {
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
    //                    P r o p e r t y  G e t
    //---------------------------------------------------------------

    OBJ_ID          Node_PropertyA (
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
        if (!Node_Validate( this )) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (NULL == pNameA) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pProperties) {
            pFound = NodeBT_FindA(this->pProperties, 0, pNameA);
            if (pFound) {
                pProperty = Node_getData(pFound);
            }
        }

        // Return to caller.
        return pProperty;
    }



    //---------------------------------------------------------------
    //                     P r o p e r t y  A d d
    //---------------------------------------------------------------

    ERESULT         Node_PropertyAddA(
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
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (OBJ_NIL == this->pProperties) {
            this->pProperties = NodeBT_New( );
            if (OBJ_NIL == this->pProperties) {
                eRc = ERESULT_OUT_OF_MEMORY;
                goto eom;
            }
        }

        pNode = Node_NewWithUTF8AndClass(0, pNameA, pData);
        if (pNode == OBJ_NIL) {
            eRc = ERESULT_OUT_OF_MEMORY;
            goto eom;
        }
        eRc = NodeBT_Add(this->pProperties, pNode, true);
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

    uint32_t        Node_PropertyCount(
        NODE_DATA        *this
    )
    {
        uint32_t        num = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (this->pProperties) {
            num = NodeBT_getSize(this->pProperties);
        }

        // Return to caller.
        return num;
    }



    //---------------------------------------------------------------
    //                    P r o p e r t y  K e y s
    //---------------------------------------------------------------

    NODEARRAY_DATA * Node_Properties(
        NODE_DATA       *this
    )
    {
        NODEARRAY_DATA  *pArray = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Node_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pProperties) {
            pArray = NodeBT_Nodes(this->pProperties);
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
        void        *pMethod = Node_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Node", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Node_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Node_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODE_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Node_Class();
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
                        
                    case 'A':
                        if (str_Compare("Accept", (char *)pStr) == 0) {
                            return Node_Accept;
                        }
                        break;

                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return Node_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Node_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Node_ToDebugString;
                        }
#ifdef  NODE_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Node_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Node_ToDebugString)
                    return "ToDebugString";
#ifdef  NODE_JSON_SUPPORT
                if (pData == Node_ToJson)
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
        ASTR_DATA      *pDesc = Node_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Node_ToDebugString (
        NODE_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        const
        char            *pName;
        OBJ_IUNKNOWN    *pVtbl;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Node_Validate(this)) {
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
                    Node_getSize(this),
                    obj_getRetainCount(this)
            );

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        pName = Node_getNameUTF8(this);
        if (pName) {
            eRc = AStr_AppendPrint(
                        pStr,
                        "Name=%s class=%d misc1=%d misc2=%d\n",
                        pName,
                        Node_getClass(this),
                        Node_getMisc1(this),
                        Node_getMisc2(this)
                );
            mem_Free((void *)pName);
            pName = NULL;
        }

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

        AStr_AppendCharRepeatA(pStr, indent, ' ');
        if (this->pProperties) {
            AStr_AppendCharRepeatA(pStr, indent+3, ' ');
            AStr_AppendA(pStr, "Properties:\n");
            if (this->pProperties) {
                pVtbl = obj_getVtbl(this->pProperties);
                if (pVtbl && pVtbl->pToDebugString) {
                    pWrkStr = pVtbl->pToDebugString(this->pProperties, indent+6);
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }

        AStr_AppendCharRepeatA(pStr, indent, ' ');
        if (this->pExtra) {
            AStr_AppendCharRepeatA(pStr, indent+3, ' ');
            AStr_AppendA(pStr, "Extra:\n");
            if (this->pExtra) {
                pVtbl = obj_getVtbl(this->pExtra);
                if (pVtbl && pVtbl->pToDebugString) {
                    pWrkStr = pVtbl->pToDebugString(this->pExtra, indent+6);
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }

        AStr_AppendCharRepeatA(pStr, indent, ' ');
        if (this->pOther) {
            AStr_AppendCharRepeatA(pStr, indent+3, ' ');
            AStr_AppendA(pStr, "Other:\n");
            if (this->pOther) {
                pVtbl = obj_getVtbl(this->pOther);
                if (pVtbl && pVtbl->pToDebugString) {
                    pWrkStr = pVtbl->pToDebugString(this->pOther, indent+6);
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }

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
    
    
    ASTR_DATA *     Node_ToString(
        NODE_DATA       *this
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
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
        if( !Node_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = Name_ToString(Node_getName(this));

        if (pStr && this->pData) {
            if (obj_IsKindOf(this, OBJ_IDENT_ASTR)) {
                pWrk = AStr_Copy((ASTR_DATA *)this->pData);
            }
            else if (obj_IsKindOf(this, OBJ_IDENT_PATH)) {
                pWrk = AStr_Copy(Path_getAStr((PATH_DATA *)this->pData));
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
                        pWrk = pToString(this->pData);
                    }
                }
            }
            if (pWrk) {
                AStr_AppendA(pStr, ":");
                AStr_Append(pStr, pWrk);
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
        }
        if (pStr) {
            AStr_AppendA(pStr, "\n");
        }

        return pStr;
    }



    ASTR_DATA *     Node_ToString_Data(
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
        if( !Node_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pData) {
            if (obj_IsKindOf(this, OBJ_IDENT_ASTR)) {
                pStr = AStr_Copy((ASTR_DATA *)this->pData);
            }
            else if (obj_IsKindOf(this, OBJ_IDENT_PATH)) {
                pStr = AStr_Copy(Path_getAStr((PATH_DATA *)this->pData));
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
                        pStr = pToString(this->pData);
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
    bool            Node_Validate (
        NODE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODE))
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


        if (!(obj_getSize(this) >= sizeof(NODE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


