// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ObjBT.c
 *	Generated 03/01/2020 21:30:29
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
#include        <ObjBT_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                  D e l e t e  E x i t
    //---------------------------------------------------------------

    ERESULT         ObjBT_DeleteExit(
        OBJBT_DATA      *this,
        OBJBT_RECORD    *pRecord,
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        if (pRecord->node.pKey) {
            obj_Release(pRecord->node.pKey);
            pRecord->node.pKey = OBJ_NIL;
        }
        if (pRecord->node.pValue) {
            obj_Release(pRecord->node.pValue);
            pRecord->node.pValue = OBJ_NIL;
        }

        return eRc;
    }



    //---------------------------------------------------------------
    //                  E n u m  E x i t
    //---------------------------------------------------------------

    ERESULT         ObjBT_EnumExit(
        OBJBT_DATA      *this,
        OBJBT_RECORD    *pRecord,
        OBJENUM_DATA    *pEnum
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        //NODE_DATA       *pNode = pRecord->node.pKey;

#ifdef IF_NEEDED
        if (pRecord->node.pKey && pEnum) {
            eRc = ObjEnum_AppendObj(pEnum, (OBJ_ID)pNode);
        }
#endif

        return eRc;
    }



    //---------------------------------------------------------------
    //                  F i n d  E x i t
    //---------------------------------------------------------------

    ERESULT         ObjBT_FindExit(
        NODEBT_DATA     *this,
        OBJBT_RECORD    *pRecord,
        OBJBT_FIND      *pFind
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODE_DATA       *pNode = pRecord->node.pKey;

        if (pNode) {
            if (pFind->unique == pRecord->unique) {
                pFind->pRecord = pRecord;
                return ERESULT_DATA_NOT_FOUND;
            }
        }

        return eRc;
    }



    //---------------------------------------------------------------
    //                  F i n d  U n i q u e
    //---------------------------------------------------------------

    OBJBT_RECORD *  ObjBT_FindUnique(
        NODEBT_DATA     *this,
        uint32_t        unique
    )
    {
        LISTDL_DATA     *pList;
        BLOCKS_NODE     *pEntry = NULL;
        OBJBT_RECORD    *pRecord = NULL;

        pList = Blocks_getList((BLOCKS_DATA *)this);
        if (pList) {
            pEntry = listdl_Head(pList);
            while (pEntry) {
                pRecord = (OBJBT_RECORD *)pEntry->data;
                if (unique == pRecord->unique) {
                    break;
                }
                pEntry = listdl_Next(pList, pEntry);
            }
        }

        return pRecord;
    }



    //---------------------------------------------------------------
    //                  N o d e  C o m p a r e
    //---------------------------------------------------------------

    int             ObjBT_NodeCmp(
        void            *pKeyA,
        void            *pKeyB
    )
    {
        int             iRc;

        iRc = strcmp((char *)pKeyA, (char *)pKeyB);
        return iRc;
    }





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJBT_DATA *     ObjBT_Alloc (
        void
    )
    {
        OBJBT_DATA       *this;
        uint32_t        cbSize = sizeof(OBJBT_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJBT_DATA *     ObjBT_New (
        void
    )
    {
        OBJBT_DATA       *this;
        
        this = ObjBT_Alloc( );
        if (this) {
            this = ObjBT_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        ObjBT_getPriority (
        OBJBT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjBT_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            ObjBT_setPriority (
        OBJBT_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!ObjBT_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        ObjBT_getSize (
        OBJBT_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!ObjBT_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return (uint32_t)this->tree.size;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  ObjBT_getSuperVtbl (
        OBJBT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjBT_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
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
        ERESULT eRc = ObjBT_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another OBJBT object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         ObjBT_Assign (
        OBJBT_DATA		*this,
        OBJBT_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjBT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjBT_Validate(pOther)) {
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
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
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
    ERESULT         ObjBT_Compare (
        OBJBT_DATA     *this,
        OBJBT_DATA     *pOther
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
        if (!ObjBT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjBT_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
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
        ObjBT      *pCopy = ObjBT_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJBT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJBT_DATA *     ObjBT_Copy (
        OBJBT_DATA       *this
    )
    {
        OBJBT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjBT_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef OBJBT_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = ObjBT_New( );
        if (pOther) {
            eRc = ObjBT_Assign(this, pOther);
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

    void            ObjBT_Dealloc (
        OBJ_ID          objId
    )
    {
        OBJBT_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!ObjBT_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OBJBT_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
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
        ObjBT      *pDeepCopy = ObjBT_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJBT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJBT_DATA *     ObjBT_DeepyCopy (
        OBJBT_DATA       *this
    )
    {
        OBJBT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjBT_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ObjBT_New( );
        if (pOther) {
            eRc = ObjBT_Assign(this, pOther);
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
    ERESULT         ObjBT_Disable (
        OBJBT_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjBT_Validate(this)) {
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
    ERESULT         ObjBT_Enable (
        OBJBT_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjBT_Validate(this)) {
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
    //                          F o r  E a c h
    //---------------------------------------------------------------

    ERESULT         ObjBT_ForEach(
        OBJBT_DATA      *this,
        P_ERESULT_EXIT4 pScan,
        OBJ_ID          pObj,               // Used as first parameter of scan method
        //                                  // second parameter is key
        //                                  // third parameter is data
        void            *pArg4              // Used as fourth parameter of scan method
    )
    {
        LISTDL_DATA     *pList = NULL;
        BLOCKS_NODE     *pEntry = NULL;
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjBT_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pScan ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pList = Blocks_getList((BLOCKS_DATA *)this);
        pEntry = listdl_Head(pList);
        while (pEntry) {
            OBJBT_RECORD        *pRecord = (OBJBT_RECORD *)pEntry->data;

            eRc =   pScan(pObj, pRecord->node.pKey, pRecord->node.pValue, pArg4);
            if (ERESULT_FAILED(eRc))
                break;

            pEntry = listdl_Next(pList, pEntry);
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJBT_DATA *   ObjBT_Init (
        OBJBT_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(OBJBT_DATA);
        ERESULT         eRc;
        
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

        this = (OBJ_ID)Blocks_Init((BLOCKS_DATA *)this);        // Needed for Inheritance
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ObjBT_Vtbl);
        
        this->unique = 1;
        // Set up Blocks to hold tree data.
        eRc = Blocks_SetupSizes((BLOCKS_DATA *)this, 0, sizeof(OBJBT_RECORD));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        Blocks_setDeleteExit(
                        (BLOCKS_DATA *)this,
                        (void *)ObjBT_DeleteExit,
                        this,               // 1st parameter
                        NULL                // 3rd parameter
        );

        // Set up Red-Black tree to use Blocks to hold its data.
        rbt_Init(
                 &this->tree,
                 (void *)ObjBT_NodeCmp,
                 (sizeof(OBJBT_RECORD) - sizeof(RBT_NODE)),
                 (void *)Blocks_RecordNew,
                 (void *)Blocks_RecordFree,
                 this
        );
        this->tree.pNodeAlloc = (void *)Blocks_RecordNew;
        this->tree.pNodeFree = (void *)Blocks_RecordFree;
        this->tree.pObjAllocFree = this;
        this->tree.dataSize = sizeof(OBJBT_RECORD) - sizeof(RBT_NODE);

#ifdef NDEBUG
#else
        if (!ObjBT_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "ObjBT::sizeof(OBJBT_DATA) = %lu\n", 
                sizeof(OBJBT_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OBJBT_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         ObjBT_IsEnabled (
        OBJBT_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjBT_Validate(this)) {
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
        void        *pMethod = ObjBT_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "ObjBT", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          ObjBT_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJBT_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!ObjBT_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(OBJBT_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)ObjBT_Class();
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
                            return ObjBT_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return ObjBT_Enable;
                        }
                        break;

#ifdef  OBJBT_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return ObjBT_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return ObjBT_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return ObjBT_ToDebugString;
                        }
#ifdef  OBJBT_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return ObjBT_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == ObjBT_ToDebugString)
                    return "ToDebugString";
#ifdef  OBJBT_JSON_SUPPORT
                if (pData == ObjBT_ToJson)
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
        ASTR_DATA      *pDesc = ObjBT_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjBT_ToDebugString (
        OBJBT_DATA      *this,
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
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjBT_Validate(this)) {
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
                    ObjBT_getSize(this),
                    obj_getRetainCount(this)
            );

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
    bool            ObjBT_Validate (
        OBJBT_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_OBJBT))
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


        if (!(obj_getSize(this) >= sizeof(OBJBT_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


