// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   objList.c
 *	Generated 09/14/2016 11:48:53
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
#include "objList_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    bool            objList_AddBlock(
        OBJLIST_DATA   *this
    )
    {
        OBJLIST_BLOCK   *pBlock;
        uint32_t        i;
        
        // Do initialization.
        if ( 0 == listdl_Count(&this->freeList) )
            ;
        else {
            return true;
        }
        
        // Get a new block.
        i = sizeof(OBJLIST_BLOCK) + (this->cBlock * sizeof(OBJLIST_NODE));
        pBlock = (OBJLIST_BLOCK *)mem_Malloc( i );
        if( NULL == pBlock ) {
            return false;
        }
        listdl_Add2Tail(&this->blocks, pBlock);
        
        // Now chain the entries to the Free chain.
        for (i=0; i<this->cBlock; ++i) {
            listdl_Add2Tail(&this->freeList, &pBlock->node[i]);
        }
        
        // Return to caller.
        return true;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJLIST_DATA *     objList_Alloc(
    )
    {
        OBJLIST_DATA       *this;
        uint32_t        cbSize = sizeof(OBJLIST_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJLIST_DATA *     objList_New(
    )
    {
        OBJLIST_DATA       *this;
        
        this = objList_Alloc( );
        if (this) {
            this = objList_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         objList_getLastError(
        OBJLIST_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objList_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        return this->eRc;
    }



    uint32_t        objList_getSize(
        OBJLIST_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if( !objList_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return listdl_Count(&this->list);
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A d d
    //---------------------------------------------------------------
    
    ERESULT         objList_Add2Head(
        OBJLIST_DATA    *this,
        OBJ_ID          pObject
    )
    {
        OBJLIST_NODE    *pEntry;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objList_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( (OBJ_NIL == pObject) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
#endif
        
        if (0 == listdl_Count(&this->freeList)) {
            if ( objList_AddBlock(this) )
                ;
            else {
                this->eRc = ERESULT_INSUFFICIENT_MEMORY;
                return this->eRc;
            }
        }
        
        pEntry = listdl_DeleteHead(&this->freeList);
        if (NULL == pEntry) {
            this->eRc = ERESULT_INSUFFICIENT_MEMORY;
            return this->eRc;
        }
        obj_Retain(pObject);
        pEntry->pObject = pObject;
        listdl_Add2Head(&this->list, pEntry);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    ERESULT         objList_Add2Tail(
        OBJLIST_DATA    *this,
        OBJ_ID          pObject
    )
    {
        OBJLIST_NODE    *pEntry;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objList_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( (OBJ_NIL == pObject) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
#endif
        
        if (0 == listdl_Count(&this->freeList)) {
            if ( objList_AddBlock(this) )
                ;
            else {
                this->eRc = ERESULT_INSUFFICIENT_MEMORY;
                return this->eRc;
            }
        }
        
        pEntry = listdl_DeleteHead(&this->freeList);
        if (NULL == pEntry) {
            this->eRc = ERESULT_INSUFFICIENT_MEMORY;
            return this->eRc;
        }
        obj_Retain(pObject);
        pEntry->pObject = pObject;
        listdl_Add2Tail(&this->list, pEntry);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code:
        ERESULT eRc = objList__Assign(this,pOther);
     @endcode:
     @param:    this    OBJLIST object pointer
     @param:    pOther  a pointer to another OBJLIST object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         objList_Assign(
        OBJLIST_DATA		*this,
        OBJLIST_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objList_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( !objList_Validate(pOther) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

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
        
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        //goto eom;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        this->eRc = ERESULT_NOT_IMPLEMENTED; // <-- Remove this!
    //eom:
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        objList      *pCopy = objList_Copy(this);
     @endcode:
     @param:    this    OBJLIST object pointer
     @return:   If successful, a OBJLIST object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the OBJLIST object.
     */
    OBJLIST_DATA *     objList_Copy(
        OBJLIST_DATA       *this
    )
    {
        OBJLIST_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = objList_New();
        if (pOther) {
            eRc = objList_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        this->eRc = ERESULT_SUCCESS;
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            objList_Dealloc(
        OBJ_ID          objId
    )
    {
        OBJLIST_DATA    *this = objId;
        OBJLIST_BLOCK   *pBlock;
        OBJLIST_NODE    *pEntry;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !objList_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OBJLIST_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
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
        
        while ( listdl_Count(&this->blocks) ) {
            pBlock = listdl_DeleteHead(&this->blocks);
            mem_Free( pBlock );
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    ERESULT         objList_DeleteHead(
        OBJLIST_DATA	*this
    )
    {
        OBJLIST_NODE    *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objList_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        pEntry = listdl_Head(&this->list);
        if (NULL == pEntry) {
            this->eRc = ERESULT_DATA_NOT_FOUND;
            return this->eRc;
        }
        
        obj_Release(pEntry->pObject);
        pEntry->pObject = OBJ_NIL;
        listdl_Delete(&this->list, pEntry);
        listdl_Add2Tail(&this->freeList, pEntry);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    ERESULT         objList_DeleteTail(
        OBJLIST_DATA	*this
    )
    {
        OBJLIST_NODE    *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objList_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        pEntry = listdl_Tail(&this->list);
        if (NULL == pEntry) {
            this->eRc = ERESULT_DATA_NOT_FOUND;
            return this->eRc;
        }
        
        obj_Release(pEntry->pObject);
        pEntry->pObject = OBJ_NIL;
        listdl_Delete(&this->list, pEntry);
        listdl_Add2Tail(&this->freeList, pEntry);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          F o r  E a c h
    //---------------------------------------------------------------
    
    ERESULT         objList_ForEach(
        OBJLIST_DATA    *this,
        P_VOIDEXIT2_BE  pScan,
        OBJ_ID          pObject            // Used as first parameter of scan method
    )
    {
        OBJLIST_NODE    *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objList_Validate(this) ) {
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
            this->eRc = pScan(pObject, pEntry->pObject);
            if (ERESULT_HAS_FAILED(this->eRc)) {
                break;
            }
            pEntry = listdl_Next(&this->list, pEntry);
        }
        
        // Return to caller.
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          H e a d
    //---------------------------------------------------------------

    OBJ_ID          objList_Head(
        OBJLIST_DATA    *this
    )
    {
        OBJ_ID          pObject = OBJ_NIL;
        OBJLIST_NODE    *pNode;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !objList_Validate(this) ) {
            DEBUG_BREAK();
            return pObject;
        }
    #endif
        
        pNode = listdl_Head(&this->list);
        if (pNode) {
            pObject = pNode->pObject;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return pObject;
    }



    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------
    
    OBJ_ID          objList_Index(
        OBJLIST_DATA    *this,
        int32_t			index					// (relative to 1)
    )
    {
        OBJ_ID          pObject = OBJ_NIL;
        OBJLIST_NODE    *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objList_Validate(this) ) {
            DEBUG_BREAK();
            return pObject;
        }
#endif
        
        pNode = listdl_Index(&this->list, index);
        if (pNode) {
            pObject = pNode->pObject;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return pObject;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJLIST_DATA *   objList_Init(
        OBJLIST_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(OBJLIST_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_OBJLIST);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_OBJLIST);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&objList_Vtbl);
        
        cbSize = LIST_BLOCK_SIZE - sizeof(OBJLIST_BLOCK);
        cbSize /= sizeof(OBJLIST_NODE);
        this->cBlock = cbSize;
        
        // Initialize the lists.
        listdl_Init(&this->freeList, offsetof(OBJLIST_NODE, list));
        listdl_Init(&this->blocks, offsetof(OBJLIST_NODE, list));
        listdl_Init(&this->list, offsetof(OBJLIST_NODE, list));
        
    #ifdef NDEBUG
    #else
        if( !objList_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->cBlock);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          T a i l
    //---------------------------------------------------------------
    
    OBJ_ID          objList_Tail(
        OBJLIST_DATA    *this
    )
    {
        OBJ_ID          pObject = OBJ_NIL;
        OBJLIST_NODE    *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objList_Validate(this) ) {
            DEBUG_BREAK();
            return pObject;
        }
#endif
        
        pNode = listdl_Tail(&this->list);
        if (pNode) {
            pObject = pNode->pObject;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return pObject;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = objList_ToDebugString(this,4);
     @endcode:
     @param:    this    OBJLIST object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     objList_ToDebugString(
        OBJLIST_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        OBJLIST_NODE    *pEntry = OBJ_NIL;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(objList) size=%d\n",
                     this,
                     objList_getSize(this)
            );
        AStr_AppendA(pStr, str);

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
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(objList)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            objList_Validate(
        OBJLIST_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_OBJLIST) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(OBJLIST_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


