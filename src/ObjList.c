// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ObjList.c
 *	Generated 12/15/2019 12:58:04
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
#include        <ObjList_internal.h>
#include        <ObjEnum_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

OBJLIST_RECORD * ObjList_FindObj (
    OBJLIST_DATA    *this,
    OBJ_ID          pObj
)
{
    OBJLIST_RECORD  *pObjInt;
    ERESULT         eRc;
    P_OBJ_COMPARE   pCompare = obj_getVtbl(pObj)->pCompare;

    pObjInt = listdl_Head(&this->list);
    while ( pObjInt ) {
        eRc = pCompare(pObj, pObjInt->pObject);
        if (ERESULT_SUCCESS_GREATER_THAN == eRc)
            ;
        else {
            // pObj <= the current entry
            return pObjInt;
        }
        pObjInt = listdl_Next(&this->list, pObjInt);
    }
    
    // Return to caller.
    return NULL;
}


static
int             ObjList_SortCompare (
    OBJ_ID          pNode1,
    OBJ_ID          pNode2
)
{
    int             iRc;
    ERESULT         eRc;
    P_OBJ_COMPARE   pCompare = obj_getVtbl(pNode1)->pCompare;
    
    if (NULL == pCompare)
        return -1;
    eRc = pCompare(pNode1, pNode2);
    if (ERESULT_SUCCESS_EQUAL == eRc)
        iRc = 0;
    else if (ERESULT_SUCCESS_LESS_THAN == eRc)
        iRc = -1;
    else
        iRc = 1;
    
    // Return to caller.
    return iRc;
}





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJLIST_DATA *     ObjList_Alloc (
        void
    )
    {
        OBJLIST_DATA       *this;
        uint32_t        cbSize = sizeof(OBJLIST_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJLIST_DATA *     ObjList_New (
        void
    )
    {
        OBJLIST_DATA       *this;
        
        this = ObjList_Alloc( );
        if (this) {
            this = ObjList_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    LISTDL_DATA *   ObjList_getList (
        OBJLIST_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if(!ObjList_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        return &this->list;
    }
        
        
        
    //---------------------------------------------------------------
    //                       O r d e r e d
    //---------------------------------------------------------------
    
    bool            ObjList_getOrdered (
        OBJLIST_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (obj_Flag(this, LIST_FLAG_ORDERED))
            return true;
        else
            return false;
    }
    
    bool            ObjList_setOrdered (
        OBJLIST_DATA    *this,
        bool            fValue
    )
    {
        bool            fOrdered = false;
        ERESULT         eRc;
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (obj_Flag(this, LIST_FLAG_ORDERED))
            fOrdered = true;
        obj_FlagSet(this, LIST_FLAG_ORDERED, fValue);
        if (!fOrdered && fValue) {
            eRc = ObjList_SortAscending(this);
            if (ERESULT_FAILED(eRc))
                return false;
        }
        
        return true;
    }
        

        
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        ObjList_getSize (
        OBJLIST_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!ObjList_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return listdl_Count(&this->list);
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  ObjList_getSuperVtbl (
        OBJLIST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjList_Validate(this)) {
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
    //                          A d d
    //---------------------------------------------------------------
    
    ERESULT         ObjList_Add2Head (
        OBJLIST_DATA    *this,
        OBJ_ID          pObject
    )
    {
        OBJLIST_RECORD  *pEntry;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pObject) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pEntry = blocks_RecordNew((BLOCKS_DATA *)this, NULL);
        if (NULL == pEntry) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        obj_Retain(pObject);
        pEntry->pObject = pObject;
        pEntry->unique = ++this->unique;
        if (obj_Flag(this, LIST_FLAG_ORDERED)) {
            OBJLIST_RECORD      *pObjInt;
            // Find insertion point.
            pObjInt = ObjList_FindObj(this, pObject);
            // Do the insertion.
            if (pObjInt) {
                listdl_AddBefore(&this->list, pObjInt, pEntry);
            }
            else
                listdl_Add2Tail(&this->list, pEntry);
        }
        else
            listdl_Add2Head(&this->list, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         ObjList_Add2Tail (
        OBJLIST_DATA    *this,
        OBJ_ID          pObject
    )
    {
        OBJLIST_RECORD  *pEntry;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pObject) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pEntry = blocks_RecordNew((BLOCKS_DATA *)this, NULL);
        if (NULL == pEntry) {
            return ERESULT_OUT_OF_MEMORY;
        }

        obj_Retain(pObject);
        pEntry->pObject = pObject;
        pEntry->unique = ++this->unique;
        if (obj_Flag(this, LIST_FLAG_ORDERED)) {
            OBJLIST_RECORD      *pObjInt;
            // Find insertion point.
            pObjInt = ObjList_FindObj(this, pObject);
            // Do the insertion.
            if (pObjInt) {
                listdl_AddBefore(&this->list, pObjInt, pEntry);
            }
            else
                listdl_Add2Tail(&this->list, pEntry);
        }
        else
            listdl_Add2Tail(&this->list, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESS;
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
        ERESULT eRc = ObjList_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another OBJLIST object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         ObjList_Assign (
        OBJLIST_DATA	*this,
        OBJLIST_DATA    *pOther
    )
    {
        ERESULT         eRc;
        OBJLIST_RECORD  *pEntry = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjList_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjList_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        while (ObjList_getSize(pOther)) {
            eRc = ObjList_DeleteHead(pOther);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        pEntry = listdl_Head(&this->list);
        while ( pEntry ) {
            if (pEntry->pObject) {
                eRc = ObjList_Add2Tail(pOther, pEntry->pObject);
                if (ERESULT_FAILED(eRc)) {
                    break;
                }
            }
            pEntry = listdl_Next(&this->list, pEntry);
        }

        // Return to caller.
        return ERESULT_SUCCESS;
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
    ERESULT         ObjList_Compare (
        OBJLIST_DATA     *this,
        OBJLIST_DATA     *pOther
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
        if (!ObjList_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjList_Validate(pOther)) {
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
        ObjList      *pCopy = ObjList_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJLIST object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJLIST_DATA *     ObjList_Copy (
        OBJLIST_DATA       *this
    )
    {
        OBJLIST_DATA    *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjList_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ObjList_New( );
        if (pOther) {
            eRc = ObjList_Assign(this, pOther);
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
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            ObjList_Dealloc (
        OBJ_ID          objId
    )
    {
        OBJLIST_DATA    *this = objId;
        OBJLIST_RECORD  *pEntry;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!ObjList_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

        // Release all the nodes.
        while ( (pEntry = listdl_Head(&this->list)) ) {
            if (pEntry->pObject) {
                obj_Release(pEntry->pObject);
                pEntry->pObject = OBJ_NIL;
            }
            listdl_DeleteHead(&this->list);
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                        D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
     objList      *pCopy = ObjList_DeepCopy(this);
     @endcode
     @param     this    OBJLIST object pointer
     @return    If successful, a OBJLIST object which must be released,
     otherwise OBJ_NIL.
     @warning   Remember to release the returned the OBJLIST object.
     */
    OBJLIST_DATA *  ObjList_DeepCopy (
        OBJLIST_DATA    *this
    )
    {
        OBJLIST_DATA    *pOther = OBJ_NIL;
        ERESULT         eRc;
        OBJLIST_RECORD  *pEntry = OBJ_NIL;
        OBJ_ID          pObject;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ObjList_New();
        if (pOther) {
            pEntry = listdl_Head(&this->list);
            while ( pEntry ) {
                if (pEntry->pObject) {
                    if (pEntry->pObject) {
                        if (obj_getVtbl(pEntry->pObject)->pDeepCopy) {
                            pObject = obj_getVtbl(pEntry->pObject)->pCopy(pEntry->pObject);
                        }
                        else {
                            obj_Retain(pEntry->pObject);
                            pObject = pEntry->pObject;
                        }
                        eRc = ObjList_Add2Tail(pOther, pObject);
                        if (ERESULT_FAILED(eRc)) {
                            break;
                        }
                        obj_Release(pObject);
                    }
                }
                pEntry = listdl_Next(&this->list, pEntry);
            }
        }
        
        // Return to caller.
        return pOther;
    }
        
        
        
    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    ERESULT         ObjList_DeleteHead (
        OBJLIST_DATA    *this
    )
    {
        OBJLIST_RECORD  *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEntry = listdl_Head(&this->list);
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        obj_Release(pEntry->pObject);
        pEntry->pObject = OBJ_NIL;
        listdl_Delete(&this->list, pEntry);
        blocks_RecordFree((BLOCKS_DATA *)this, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         ObjList_DeleteIndex (
        OBJLIST_DATA    *this,
        uint32_t        index
    )
    {
        OBJLIST_RECORD  *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEntry = listdl_Index(&this->list, index);
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        obj_Release(pEntry->pObject);
        pEntry->pObject = OBJ_NIL;
        listdl_Delete(&this->list, pEntry);
        blocks_RecordFree((BLOCKS_DATA *)this, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         ObjList_DeleteTail (
        OBJLIST_DATA    *this
    )
    {
        OBJLIST_RECORD  *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEntry = listdl_Tail(&this->list);
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        obj_Release(pEntry->pObject);
        pEntry->pObject = OBJ_NIL;
        listdl_Delete(&this->list, pEntry);
        blocks_RecordFree((BLOCKS_DATA *)this, pEntry);

        // Return to caller.
        return ERESULT_SUCCESS;
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
    ERESULT         ObjList_Disable (
        OBJLIST_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!ObjList_Validate(this)) {
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
    ERESULT         ObjList_Enable (
        OBJLIST_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!ObjList_Validate(this)) {
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
    //                        E n u m
    //---------------------------------------------------------------
    
    OBJENUM_DATA *  ObjList_Enum (
        OBJLIST_DATA    *this
    )
    {
        ERESULT         eRc;
        OBJENUM_DATA    *pEnum = OBJ_NIL;
        OBJLIST_RECORD  *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pEnum = ObjEnum_New();
        if (pEnum) {
            pEntry = listdl_Head(&this->list);
            while ( pEntry ) {
                eRc = ObjEnum_AppendObj(pEnum, pEntry->pObject);
                if (ERESULT_FAILED(eRc)) {
                    obj_Release(pEnum);
                    pEnum = OBJ_NIL;
                    break;
                }
                pEntry = listdl_Next(&this->list, pEntry);
            }
        }
        
        // Return to caller.
        return pEnum;
    }
    
    
    
    //---------------------------------------------------------------
    //                          F o r  E a c h
    //---------------------------------------------------------------
    
    ERESULT         ObjList_ForEach (
        OBJLIST_DATA    *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObject,        // Used as first parameter of scan method
        void            *pArg3
    )
    {
        OBJLIST_RECORD  *pEntry = OBJ_NIL;
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pScan ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pEntry = listdl_Head(&this->list);
        while ( pEntry ) {
            eRc = pScan(pObject, pEntry->pObject, pArg3);
            if (ERESULT_HAS_FAILED(eRc)) {
                break;
            }
            pEntry = listdl_Next(&this->list, pEntry);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          H e a d
    //---------------------------------------------------------------

    OBJ_ID          ObjList_Head (
        OBJLIST_DATA    *this
    )
    {
        OBJ_ID          pObject = OBJ_NIL;
        OBJLIST_RECORD  *pNode;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return pObject;
        }
    #endif
        
        pNode = listdl_Head(&this->list);
        if (pNode) {
            pObject = pNode->pObject;
        }
        this->pCur = pNode;
        
        // Return to caller.
        return pObject;
    }



    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------
    
    OBJ_ID          ObjList_Index (
        OBJLIST_DATA    *this,
        int32_t            index                    // (relative to 1)
    )
    {
        OBJ_ID          pObject = OBJ_NIL;
        OBJLIST_RECORD  *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return pObject;
        }
#endif
        
        pNode = listdl_Index(&this->list, index);
        if (pNode) {
            pObject = pNode->pObject;
        }
        
        // Return to caller.
        return pObject;
    }
        
        
        
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJLIST_DATA *   ObjList_Init (
        OBJLIST_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(OBJLIST_DATA);
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

        this = (OBJ_ID)blocks_Init((BLOCKS_DATA *)this);        // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_OBJLIST);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ObjList_Vtbl);
        
        eRc = blocks_SetupSizes((BLOCKS_DATA *)this, 0, sizeof(OBJLIST_RECORD));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        listdl_Init(&this->list, offsetof(OBJLIST_RECORD, list));
        
#ifdef NDEBUG
    #else
        if (!ObjList_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "ObjList::sizeof(OBJLIST_DATA) = %lu\n", sizeof(OBJLIST_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OBJLIST_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         ObjList_IsEnabled (
        OBJLIST_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjList_Validate(this)) {
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
    //                          N e x t
    //---------------------------------------------------------------
    
    OBJ_ID          ObjList_Next (
        OBJLIST_DATA    *this
    )
    {
        OBJ_ID          pObject = OBJ_NIL;
        OBJLIST_RECORD  *pNode = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return pObject;
        }
#endif
        
        if (this->pCur) {
            pNode = listdl_Next(&this->list, this->pCur);
        }
        else {
            pNode = listdl_Head(&this->list);
        }
        this->pCur = pNode;
        if (pNode)
            pObject = pNode->pObject;
        
        // Return to caller.
        return pObject;
    }
    
    
    
    //---------------------------------------------------------------
    //                        O b j e c t s
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * ObjList_Objects (
        OBJLIST_DATA    *this
    )
    {
        ERESULT         eRc;
        OBJARRAY_DATA   *pArray = OBJ_NIL;
        OBJLIST_RECORD  *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pArray = ObjArray_New();
        if (pArray) {
            pEntry = listdl_Head(&this->list);
            while ( pEntry ) {
                eRc = ObjArray_Append(pArray, pEntry->pObject);
                if (ERESULT_FAILED(eRc)) {
                    obj_Release(pArray);
                    pArray = OBJ_NIL;
                    break;
                }
                pEntry = listdl_Next(&this->list, pEntry);
            }
        }
        
        // Return to caller.
        return pArray;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r e v
    //---------------------------------------------------------------
    
    OBJ_ID          ObjList_Prev (
        OBJLIST_DATA    *this
    )
    {
        OBJ_ID          pObject = OBJ_NIL;
        OBJLIST_RECORD  *pNode = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return pObject;
        }
#endif
        
        if (this->pCur) {
            pNode = listdl_Prev(&this->list, this->pCur);
        }
        else {
            pNode = listdl_Tail(&this->list);
        }
        this->pCur = pNode;
        if (pNode)
            pObject = pNode->pObject;
        
        // Return to caller.
        return pObject;
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
        void        *pMethod = ObjList_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "ObjList", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          ObjList_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJLIST_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!ObjList_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJLIST_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)ObjList_Class();
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
                            return ObjList_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return ObjList_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return ObjList_ToDebugString;
                        }
#ifdef  SRCREF_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return ObjList_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == ObjList_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == ObjList_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                         S o r t
    //---------------------------------------------------------------
    
    ERESULT         ObjList_SortAscending (
        OBJLIST_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        bool            fRc;
        
        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (listdl_Count(&this->list) < 2) {
            return ERESULT_SUCCESS;
        }
        
        fRc = listdl_Sort(&this->list, (void *)ObjList_SortCompare);
        if (fRc)
            eRc = ERESULT_SUCCESS;
        
        // Return to caller.
        return eRc;
    }

    
    
    //---------------------------------------------------------------
    //                      S h i f t  H e a d
    //---------------------------------------------------------------
    
    OBJ_ID          ObjList_ShiftHead (
        OBJLIST_DATA    *this
    )
    {
        OBJ_ID          pObject = OBJ_NIL;
        OBJLIST_RECORD  *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return pObject;
        }
#endif
        
        pNode = listdl_ShiftHead(&this->list);
        if (pNode) {
            pObject = pNode->pObject;
        }
        this->pCur = pNode;

        // Return to caller.
        return pObject;
    }
            
            
            
    //---------------------------------------------------------------
    //                      S h i f t  T a i l
    //---------------------------------------------------------------
    
    OBJ_ID          ObjList_ShiftTail (
        OBJLIST_DATA    *this
    )
    {
        OBJ_ID          pObject = OBJ_NIL;
        OBJLIST_RECORD  *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return pObject;
        }
#endif
        
        pNode = listdl_ShiftTail(&this->list);
        if (pNode) {
            pObject = pNode->pObject;
        }
        this->pCur = pNode;

        // Return to caller.
        return pObject;
    }
        
        
        
    //---------------------------------------------------------------
    //                          T a i l
    //---------------------------------------------------------------
    
    OBJ_ID          ObjList_Tail (
        OBJLIST_DATA    *this
    )
    {
        OBJ_ID          pObject = OBJ_NIL;
        OBJLIST_RECORD  *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjList_Validate(this) ) {
            DEBUG_BREAK();
            return pObject;
        }
#endif
        
        pNode = listdl_Tail(&this->list);
        if (pNode) {
            pObject = pNode->pObject;
        }
        this->pCur = pNode;

        // Return to caller.
        return pObject;
    }
        
        
        
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
#ifdef  OBJLIST_JSON_SUPPORT
     ASTR_DATA *     ObjList_ToJson (
        OBJLIST_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!ObjList_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{\"objectType\":\"%s\"",
                        pInfo->pClassName
                    );
            
            AStr_AppendA(pStr, "}\n");
        }
        
        return pStr;
    }
#endif
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjList_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjList_ToDebugString (
        OBJLIST_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        OBJLIST_RECORD  *pEntry = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjList_Validate(this)) {
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
                    ObjList_getSize(this),
                    obj_getRetainCount(this)
            );

        pEntry = listdl_Head(&this->list);
        while ( pEntry ) {
            if (((OBJ_DATA *)(pEntry->pObject))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(pEntry->pObject))->pVtbl->pToDebugString(
                                                pEntry->pObject,
                                                indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
            pEntry = listdl_Next(&this->list, pEntry);
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
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            ObjList_Validate (
        OBJLIST_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_OBJLIST))
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


        if (!(obj_getSize(this) >= sizeof(OBJLIST_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif

