// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeArray.c
 *	Generated  08/08/2015 09:07:21
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
#include <nodeArray_internal.h>
#include <utf8.h>



#ifdef	__cplusplus
extern "C" {
#endif
    


#ifdef XYZZY
    typedef struct RE {
        int     type;   /* CHAR, STAR, etc. */
        char    ch;     /* the character itself */
        char    *ccl;   /* for [...] instead */
        int     nccl;   /* true if class is negated [^...] */
    } RE;

    /* match: search for regexp anywhere in text */
    int         match(
        char        *regexp,
        char        *text
                      )
    {
        if (regexp[0] == '^')
            return matchhere(regexp+1, text);
        do {    /* must look even if string is empty */
            if (matchhere(regexp, text))
                return 1;
        } while (*text++ != '\0');
        return 0;
    }
    
    
    /* matchhere: search for regexp at beginning of text */
    int         matchhere(
        char        *regexp,
        char        *text
                          )
    {
        if (regexp[0] == '\0')
            return 1;
        if (regexp[1] == '*')
            return matchstar(regexp[0], regexp+2, text);
        if ((regexp[0] == '$') && (regexp[1] == '\0'))
            return (*text == '\0');
        if ((*text != '\0') && ((regexp[0] == '.') || (regexp[0] == *text)))
            return matchhere(regexp+1, text+1);
        return 0;
    }
    
    
    /* matchstar: search for c*regexp at beginning of text */
    int         matchstar(
        int         c,
        char        *regexp,
        char        *text
    )
    {
        do {    /* a * matches zero or more instances */
            if (matchhere(regexp, text))
                return 1;
        } while (*text != '\0' && (*text++ == c || c == '.'));
        return 0;
    }
#endif
    
    
    
    
    
 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    int         matchhere(
        char        *regexp,
        char        *text
    );
    int         matchstar(
        int         c,
        char        *regexp,
        char        *text
    );

    
    /* match: search for regexp anywhere in text */
    int         match(
        char        *regexp,
        char        *text
    )
    {
        if (regexp[0] == '^')
            return matchhere(regexp+1, text);
        do {    /* must look even if string is empty */
            if (matchhere(regexp, text))
                return 1;
        } while (*text++ != '\0');
        return 0;
    }

    
    /* matchhere: search for regexp at beginning of text */
    int         matchhere(
        char        *regexp,
        char        *text
    )
    {
        if (regexp[0] == '\0')
            return 1;
        if (regexp[1] == '*')
            return matchstar(regexp[0], regexp+2, text);
        if (regexp[0] == '$' && regexp[1] == '\0')
            return *text == '\0';
        if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text))
            return matchhere(regexp+1, text+1);
        return 0;
    }

    
    /* matchstar: search for c*regexp at beginning of text */
    int         matchstar(
        int         c,
        char        *regexp,
        char        *text
    )
    {
        do {    /* a * matches zero or more instances */
            if (matchhere(regexp, text))
                return 1;
        } while (*text != '\0' && (*text++ == c || c == '.'));
        return 0;
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODEARRAY_DATA *     nodeArray_Alloc(
    )
    {
        NODEARRAY_DATA       *cbp;
        uint32_t        cbSize = sizeof(NODEARRAY_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    NODEARRAY_DATA *     nodeArray_New(
    )
    {
        NODEARRAY_DATA       *cbp;
        
        // Do initialization.
        
        cbp = nodeArray_Alloc( );
        if (cbp) {
            cbp = nodeArray_Init(cbp);
        }
        
        // Return to caller.
        return( cbp );
    }
    
    
    
    //---------------------------------------------------------------
    //                        M a t c h  S e t
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeArray_MatchSet(
        int             (*pCompare)(NODE_DATA *,NODE_DATA *),
        NODE_DATA       *pNode,
        NODE_DATA       **ppNodeSet     // NULL-terminated Set of Nodes
    )
    {
        int             cmp;
        NODE_DATA       *pFound = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (NULL == ppNodeSet) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        while (*ppNodeSet) {
            cmp = pCompare(pNode, *ppNodeSet);
            if(0 == cmp) {
                pFound = *ppNodeSet;
                break;
            }
            ++ppNodeSet;
        }
        
        // Return to caller.
        return pFound;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    OBJARRAY_DATA *  nodeArray_getArray(
        NODEARRAY_DATA  *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pArray;
    }
    
    
    bool            nodeArray_setArray(
        NODEARRAY_DATA  *cbp,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pArray) {
            obj_Release(cbp->pArray);
        }
        cbp->pArray = pValue;
        
        return true;
    }
    
    
    
    bool            nodeArray_setCompare(
        NODEARRAY_DATA  *cbp,
        int             (*pCompare)(NODE_DATA *,NODE_DATA *)
    )
    {
#ifdef NDEBUG
#else
        if( !nodeArray_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        cbp->pCompare = pCompare;
        
        return true;
    }
    
    
    
    uint32_t        nodeArray_getSize(
        NODEARRAY_DATA  *cbp
    )
    {
        uint32_t        i = 0;
        
#ifdef NDEBUG
#else
        if( !nodeArray_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (cbp->pArray) {
            i = objArray_getSize(cbp->pArray);
        }
        return i;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         nodeArray_Append(
        NODEARRAY_DATA	*this,
        NODEARRAY_DATA	*pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        uint32_t        max;
        NODE_DATA       *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeArray_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        max = nodeArray_getSize(pOther);
        
        for (i=0; i<max; ++i) {
            pNode = nodeArray_Get(pOther, i+1);
            if (pNode) {
                eRc = nodeArray_AppendNode(this, pNode, NULL);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         nodeArray_AppendNode(
        NODEARRAY_DATA	*this,
        NODE_DATA       *pObject,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (OBJ_NIL == this->pArray) {
            this->pArray = objArray_New();
            if (OBJ_NIL == this->pArray) {
                return ERESULT_MEMORY_EXCEEDED;
            }
        }
        
        eRc = objArray_AppendObj(this->pArray, pObject, pIndex);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         nodeArray_Assign(
        NODEARRAY_DATA	*cbp,
        NODEARRAY_DATA	*pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeArray_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = objArray_Assign(cbp->pArray, pOther->pArray);
        pOther->pCompare = cbp->pCompare;
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * nodeArray_Copy(
        NODEARRAY_DATA	*cbp
    )
    {
        NODEARRAY_DATA  *pOther;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeArray_Alloc();
        pOther = nodeArray_Init(pOther);
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        pOther->pArray = objArray_Copy(cbp->pArray);
        if (pOther->pArray) {
            pOther->pCompare = cbp->pCompare;
            return pOther;
        }
        
        // Return to caller.
        obj_Release(pOther);
        return( OBJ_NIL );
    }
    
    
    
    uint32_t        nodeArray_Count(
        NODEARRAY_DATA  *this
    )
    {
        uint32_t        i = 0;
        
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (this->pArray) {
            i = objArray_getSize(this->pArray);
        }
        return i;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            nodeArray_Dealloc(
        OBJ_ID          objId
    )
    {
        NODEARRAY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pArray) {
            obj_Release(this->pArray);
            this->pArray = OBJ_NIL;
        }

        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                        D e l e t e
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeArray_DeleteFirst(
        NODEARRAY_DATA	*this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_DeleteFirst(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    NODE_DATA *     nodeArray_DeleteLast(
        NODEARRAY_DATA	*this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_DeleteLast(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------
    
    ERESULT         nodeArray_FindA(
        NODEARRAY_DATA	*this,
        const
        char            *pName,
        NODE_DATA       **ppNode
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        uint32_t        size;
        uint32_t        i;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        size = nodeArray_getSize(this);
        for (i=0; i<size; ++i) {
            pNode = (NODE_DATA *)objArray_Get(this->pArray, i+1);
            if (pNode) {
                eRc = name_CompareA(node_getName(pNode), pName);
                if( eRc == ERESULT_SUCCESS_EQUAL ) {
                    if (ppNode) {
                        *ppNode = pNode;
                    }
                    return ERESULT_SUCCESSFUL_COMPLETION;
                }
            }
        }
        
        // Return to caller.
        if (ppNode) {
            *ppNode = OBJ_NIL;
        }
        return ERESULT_DATA_NOT_FOUND;
    }
    
    
    
    //---------------------------------------------------------------
    //                        G e t
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeArray_Get(
        NODEARRAY_DATA	*this,
        uint32_t        index       // Relative to 1
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_Get(this->pArray, index);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    NODE_DATA *     nodeArray_GetFirst(
        NODEARRAY_DATA	*this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_GetFirst(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    NODE_DATA *     nodeArray_GetLast(
        NODEARRAY_DATA	*this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_GetLast(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODEARRAY_DATA *   nodeArray_Init(
        NODEARRAY_DATA       *this
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_NODEARRAY );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeArray_Vtbl);
        
        this->pCompare = &node_Compare;
        
    #ifdef NDEBUG
    #else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         nodeArray_InsertAfter(
                                          NODEARRAY_DATA	*this,
                                          uint32_t        index,
                                          NODE_DATA       *pObject
                                          )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (OBJ_NIL == this->pArray) {
            this->pArray = objArray_New();
            if (OBJ_NIL == this->pArray) {
                return ERESULT_MEMORY_EXCEEDED;
            }
        }
        
        eRc = objArray_InsertObj(this->pArray, index, pObject);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                         S o r t
    //---------------------------------------------------------------
    
    ERESULT         nodeArray_SortAscending(
        NODEARRAY_DATA	*cbp
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        
        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !nodeArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (cbp->pArray) {
            eRc = objArray_SortAscending(cbp->pArray, (OBJ_COMPARE)cbp->pCompare);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     nodeArray_ToDebugString(
        NODEARRAY_DATA  *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        NODE_DATA       *pNode;
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(nodeArray) Size=%d\n",
                     cbp,
                     objArray_getSize(cbp->pArray)
                );
        AStr_AppendA(pStr, str);
        
        if (cbp->pArray) {
            for (j=0; j<objArray_getSize(cbp->pArray); ++j) {
                pNode = objArray_Get(cbp->pArray, j+1);
                if ( pNode && ((OBJ_DATA *)(pNode))->pVtbl->pToDebugString) {
                    pWrkStr =   ((OBJ_DATA *)(pNode))->pVtbl->pToDebugString(
                                        pNode,
                                        indent+3
                                );
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
        
        AStr_AppendCharA(pStr, '\n');
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        j = snprintf( str, sizeof(str), "%p(nodeArray)}\n", cbp );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeArray_Validate(
        NODEARRAY_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_NODEARRAY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(NODEARRAY_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                   V i s i t  A s c e n d i n g
    //---------------------------------------------------------------
    
    ERESULT         nodeArray_VisitAscending(
        NODEARRAY_DATA	*cbp,
        void            (pVisitor)(
                                   OBJ_ID,             // Object supplied below
                                   NODE_DATA *         // Current Node
                        ),
        OBJ_ID          pObject
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        NODE_DATA       *pNode = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
        BREAK_NULL(cbp->pArray);
#endif
        
        iMax = objArray_getSize(cbp->pArray);
        for (i=1; i<=iMax; ++i) {
            pNode = objArray_Get(cbp->pArray, i);
            pVisitor(pObject,pNode);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


