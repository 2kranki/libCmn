// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeScan.c
 *	Generated 10/16/2015 09:19:12
 *
 */

/*                  * * * Scan EBNF  * * *

 This is our EBNF for the scanf-like alternative scan system.
 
 
 scanner :   nodeList
         ;
 
 nodeList:   '#' '(' (typeList+ | nodeList) ')'     // Rooted Node with Children or
         ;                                          // child Rooted Node
 
 typeList:   typePair*
         ;
 
 typePair:   label ':' type
         |   type
         ;
 
 nodeType:   number
         ;
 
 label   :   '%' number
         ;
 
 number  :   [0..9]*
         ;

 
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
#include    <nodeScan_internal.h>
#include    <nodeTree_internal.h>
#include    <ascii.h>
#include    <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    int             nodeScan_ScanfLex(
        NODESCAN_DATA  *this
    );
    
    int             nodeScan_ScanfLexLA(
        NODESCAN_DATA  *this
    );
    
    int             nodeScan_ScanfLabel(
        NODESCAN_DATA  *this
    );

    
    int             nodeScan_ScanfType(
       NODESCAN_DATA  *this
    );
    
    
    int             nodeScan_ScanfLabel(
        NODESCAN_DATA  *this
    )
    {
        int             tok = TOK_TYP_INVALID;
        //W32CHR_T         chr;
        //int             i = 0;
        
        tok = nodeScan_ScanfLex(this);
        if (tok == TOK_TYP_PERCENT) {
            tok = nodeScan_ScanfLexLA(this);
            if (tok == TOK_TYP_INT) {
                
            }
            else {
                return TOK_TYP_INVALID;
            }
        }
        
        return TOK_TYP_INVALID;
    }
    
    
    int             nodeScan_ScanfLex(
         NODESCAN_DATA  *this
    )
    {
        int             tok = TOK_TYP_INVALID;
        W32CHR_T        chr;
        int             i = 0;
    
        chr = AStr_CharGetW32(this->pScanInput, this->curChar);
        while (ascii_isWhiteSpaceW32(chr)) {
            ++(this->curChar);
            chr = AStr_CharGetW32(this->pScanInput, this->curChar);
        }
        if (ascii_isNumericA(chr)) {
            while (ascii_isNumericA(chr)) {
                i = (i * 10) + (chr - '0');
                ++(this->curChar);
                chr = AStr_CharGetW32(this->pScanInput, this->curChar);
            }
            this->tokInt = i;
            return TOK_TYP_INT;
        }
        tok = TOK_TYP_INVALID;
        switch (chr) {
            case '#':
                ++(this->curChar);
                tok = TOK_TYP_POUND;
                break;
            case '(':
                ++(this->curChar);
                tok = TOK_TYP_LPAREN;
                break;
            case ')':
                ++(this->curChar);
                tok = TOK_TYP_RPAREN;
                break;
            case '%':
                ++(this->curChar);
                tok = TOK_TYP_PERCENT;
                break;
            case '.':
                ++(this->curChar);
                tok = TOK_TYP_PERIOD;
                break;
            case ':':
                ++(this->curChar);
                tok = TOK_TYP_COLON;
                break;
            case '\0':
                ++(this->curChar);
                tok = TOK_TYP_EOF;
                break;
        }
        
        return tok;
    }



    int             nodeScan_ScanfLexLA(
        NODESCAN_DATA  *this
    )
    {
        int             tok = TOK_TYP_INVALID;
        W32CHR_T        chr;
        
        chr = AStr_CharGetW32(this->pScanInput, this->curChar);
        while (ascii_isWhiteSpaceW32(chr)) {
            ++(this->curChar);
            chr = AStr_CharGetW32(this->pScanInput, this->curChar);
        }
        if (ascii_isNumericA(chr)) {
            return TOK_TYP_INT;
        }
        tok = TOK_TYP_INVALID;
        switch (chr) {
            case '#':
                tok = TOK_TYP_POUND;
                break;
            case '(':
                tok = TOK_TYP_LPAREN;
                break;
            case ')':
                tok = TOK_TYP_RPAREN;
                break;
            case '%':
                tok = TOK_TYP_PERCENT;
                break;
            case '.':
                tok = TOK_TYP_PERIOD;
                break;
            case ':':
                tok = TOK_TYP_COLON;
                break;
            case '\0':
                tok = TOK_TYP_EOF;
                break;
        }
        
        return tok;
    }
    
    
    

    
    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODESCAN_DATA * nodeScan_Alloc(
    )
    {
        NODESCAN_DATA   *this;
        uint32_t        cbSize = sizeof(NODESCAN_DATA);
        
        // Do initialization.
        
        this = obj_Alloc(cbSize);
        
        // Return to caller.
        return this;
    }



    NODESCAN_DATA * nodeScan_NewFromArray(
        NODEARRAY_DATA  *pArray     // Tree converted to array with up/down members.
    )
    {
        NODESCAN_DATA   *this;
        
        this = nodeScan_Alloc( );
        if (this) {
            this = nodeScan_InitArray(this, pArray);
            if (this) {
                this->pTree = nodeArray_getOther(pArray);
                BREAK_NULL(this->pTree);
                this->pClose = nodeTree_getCloseNode(this->pTree);
                this->pOpen = nodeTree_getOpenNode(this->pTree);
            }
        }
        return this;
    }



    NODESCAN_DATA * nodeScan_NewFromTree(
        NODETREE_DATA   *pTree
    )
    {
        NODESCAN_DATA   *this;
        NODEARRAY_DATA  *pArray;
        
        pArray = nodeTree_ToLinearizationPre(pTree);
        if (pArray) {
        }
        else {
            return OBJ_NIL;
        }
        
        this = nodeScan_Alloc( );
        if (this) {
            this = nodeScan_InitArray(this, pArray);
            this->pTree = pTree;
            this->pClose = nodeTree_getCloseNode(this->pTree);
            this->pOpen = nodeTree_getOpenNode(this->pTree);
        }
        
        return this;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A r r a y
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * nodeScan_getArray(
        NODESCAN_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    
    bool            nodeScan_setArray(
        NODESCAN_DATA   *this,
        NODEARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeScan_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pArray) {
            obj_Release(this->pArray);
        }
        this->pArray = pValue;
        nodeScan_setIndex(this, 0);
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                    C l o s e  N o d e
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeScan_getCloseNode(
        NODESCAN_DATA   *this
    )
    {
        
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        return this->pClose;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------
    
    uint32_t        nodeScan_getIndex(
        NODESCAN_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->index + 1;
    }

    bool            nodeScan_setIndex(
        NODESCAN_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->index = value - 1;
        
        return true;
    }



    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         nodeScan_getLastError(
        NODESCAN_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    bool            nodeScan_setLastError(
        NODESCAN_DATA   *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                    O p e n  N o d e
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeScan_getOpenNode(
        NODESCAN_DATA   *this
    )
    {
        
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        return this->pOpen;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S t a r t
    //---------------------------------------------------------------
    
    uint32_t        nodeScan_getStart(
        NODESCAN_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->start + 1;
    }
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            nodeScan_Dealloc(
        OBJ_ID          objId
    )
    {
        NODESCAN_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        nodeScan_setArray(this, OBJ_NIL);
        if (this->pScanInput) {
            obj_Release(this->pScanInput);
            this->pScanInput = OBJ_NIL;
        }

        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODESCAN_DATA * nodeScan_Init(
        NODESCAN_DATA   *this
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (NODESCAN_DATA *)obj_Init(this, cbSize, OBJ_IDENT_NODESCAN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_NODESCAN);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeScan_Vtbl);
        
        this->index = 1;

    #ifdef NDEBUG
    #else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(sizeof(NODESCAN_DATA));
    #endif

        return this;
    }

     
    NODESCAN_DATA * nodeScan_InitArray(
        NODESCAN_DATA   *this,
        NODEARRAY_DATA  *pValue
    )
    {
        
        this = nodeScan_Init(this);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }

        if (pValue) {
            nodeScan_setArray(this, pValue);
            nodeScan_setIndex(this, 1);
        }
        
        return this;
    }
    
    

    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------
    
    NODE_DATA *     nodeScan_InputAdvance(
        NODESCAN_DATA	*this,
        uint32_t        numChrs
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            this->eRc = ERESULT_DATA_MISSING;
            return OBJ_NIL;
        }
#endif
        
        // Shift inputs.
        ++this->index;
        if (this->index <= nodeArray_getSize(this->pArray))
            ;
        else {
            this->index = 1;
            this->eRc = ERESULT_EOF_ERROR;
            return OBJ_NIL;
        }
        pNode = nodeArray_Get(this->pArray, this->index);
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //--------------------------------------------------------------
    //               I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------
    
    NODE_DATA *     nodeScan_InputLookAhead(
        NODESCAN_DATA   *this,
        uint32_t        num
    )
    {
        uint32_t        idx;
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            this->eRc = ERESULT_DATA_MISSING;
            return OBJ_NIL;
        }
        if (num > 0)
            ;
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        
        idx = this->index + (num - 1);
        if (idx <= nodeArray_getSize(this->pArray))
            ;
        else {
            this->eRc = ERESULT_EOF_ERROR;
            return OBJ_NIL;
        }
        pNode = nodeArray_Get(this->pArray, idx);
        
        // Return to caller.
        return pNode;
    }
    
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  N a m e
    //--------------------------------------------------------------
    
    NODE_DATA *     nodeScan_MatchName(
        NODESCAN_DATA	*this,
        char            *pStr
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        const
        char            *pName;
        int             cmp;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            this->eRc = ERESULT_DATA_MISSING;
            return OBJ_NIL;
        }
#endif
        this->start = this->index;
        
        pNode = nodeArray_Get(this->pArray, this->index+1);
        if (pNode) {
            pName = node_getNameUTF8(pNode);
            cmp = strcmp(pName, pStr);
            mem_Free((void *)pName);
            if( 0 == cmp ) {
                (void)nodeScan_InputAdvance(this, 1);
                return pNode;
            }
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  C l a s s
    //--------------------------------------------------------------
    
    NODE_DATA *     nodeScan_MatchClass(
        NODESCAN_DATA	*this,
        int32_t         cls
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            this->eRc = ERESULT_DATA_MISSING;
            return OBJ_NIL;
        }
#endif
        this->start = this->index;

        if (this->index < nodeArray_getSize(this->pArray))
            ;
        else {
            this->eRc = ERESULT_EOF_ERROR;
            return OBJ_NIL;
        }

        pNode = nodeArray_Get(this->pArray, this->index);
        if( pNode && ((cls == node_getClass(pNode)) || (cls == NODE_CLASS_ANY)) ) {
            (void)nodeScan_InputAdvance(this, 1);
            this->eRc = ERESULT_SUCCESS;
            return pNode;
        }
        
        // Return to caller.
        this->eRc = ERESULT_DATA_NOT_FOUND;
        return OBJ_NIL;
    }
    
    

    //--------------------------------------------------------------
    //              M a t c h  I n p u t  C l a s s e s
    //--------------------------------------------------------------
    
    NODE_DATA *     nodeScan_MatchClasses(
        NODESCAN_DATA   *this,
        int32_t         *pSet
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        uint32_t        start;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            this->eRc = ERESULT_DATA_MISSING;
            return OBJ_NIL;
        }
        if (NULL == pSet) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        start = this->index;
        
        while (*pSet) {
            pNode = nodeScan_MatchClass(this, *pSet);
            if(pNode) {
                this->eRc = ERESULT_SUCCESS;
                this->start = start;
                return pNode;
            }
            ++pSet;
        }
        
        // Return to caller.
        this->eRc = ERESULT_DATA_NOT_FOUND;
        return OBJ_NIL;
    }
    
    
    /*!
     Scan the linerarized tree matching a regex-like array of types.
     @param     this    Object Pointer
     @param     pRegex  Pointer to a variable length array of node types which must
                        not be zero followed by a zero to terminate the list.
     @return    If successful, a starting index of the match relative to 1,
                otherwise 0.
     */
    NODE_DATA *     nodeScan_MatchClassesRegex(
        NODESCAN_DATA   *this,
        int32_t         *pRegex             // [in] Zero-terminated array of
                                            //      node types
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        NODE_DATA       *pNodeStart = OBJ_NIL;
        uint32_t        regexSize = 0;
        uint32_t        regexSrchLen = 0;   // Minimum search length
        uint32_t        startIndex;
        uint32_t        i;
        uint32_t        j;
        int32_t         *pIdxRegex;
        int32_t         curRegex;
        int32_t         stopRegex;
        int32_t         curClass;
        bool            fKleene = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            this->eRc = ERESULT_DATA_MISSING;
            return OBJ_NIL;
        }
        if (NULL == pRegex) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif

        // Find the number of elements in the regex.
        for (i=0,pIdxRegex=pRegex; *pIdxRegex; ++i,++pIdxRegex) {
            if (*pIdxRegex == NODE_CLASS_KLEENE)
                ;
            else
                ++regexSrchLen;
        }
        regexSize = i;
        
        // Do the search.  Note that this is a brute force scan for now. It simply
        // advances by 1 if the search is unsuccessful until EOF.
        startIndex = this->index - 1;
        for (;;) {
            if ((startIndex + 1) <= nodeArray_getSize(this->pArray))
                ;
            else {
                break;
            }
            
            // Reset the regex scan.
            pIdxRegex = pRegex;
            this->index = startIndex + 1;

            // Scan for first type in regex.
            curRegex = *pIdxRegex;
            if (curRegex == NODE_CLASS_KLEENE) {
                fKleene = true;
                stopRegex = *(pIdxRegex + 1);
                startIndex = this->index;
                pNodeStart = nodeArray_Get(this->pArray, this->index);
                if (OBJ_NIL == pNodeStart) {
                    this->eRc = ERESULT_GENERAL_FAILURE;
                    return OBJ_NIL;
                }
            }
            else {
                stopRegex = curRegex;
            }
            if (0 == stopRegex) {
                this->eRc = ERESULT_INVALID_DATA;
                return OBJ_NIL;
            }
            pNode = nodeScan_ScanClassUntil(this, stopRegex);
            if (OBJ_NIL == pNode) {
                this->eRc = ERESULT_DATA_NOT_FOUND;
                return OBJ_NIL;
            }
            if (fKleene) {
                fKleene = false;
            }
            else {
                startIndex = this->index;
            }
            ++pIdxRegex;
            
            // Match remainder of regex
            while (*pIdxRegex) {
                curRegex = *pIdxRegex;
                if (curRegex == NODE_CLASS_KLEENE) {
                    // Now we must scan until we find the regex value after the kleene.
                    stopRegex = *(pIdxRegex + 1);
                    pNode = nodeScan_ScanClassUntil(this, stopRegex);
                    if (OBJ_NIL == pNode) {
                        this->eRc = ERESULT_DATA_NOT_FOUND;
                        return OBJ_NIL;
                    }
                }
                else
                    stopRegex = curRegex;
                pNode = nodeArray_Get(this->pArray, 1);
                if(pNode) {
                    return pNode;
                }
                ++pIdxRegex;
            }
        }
        
        // Return to caller.
        this->eRc = ERESULT_DATA_NOT_FOUND;
        return OBJ_NIL;
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
    void *          nodeScan_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODESCAN_DATA   *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
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
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return nodeScan_ToDebugString;
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
    //                       S c a n
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeScan_ScanClassUntil(
        NODESCAN_DATA   *this,
        int32_t         cls
    )
    {
        int32_t         curClass;
        NODE_DATA       *pNode = OBJ_NIL;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            this->eRc = ERESULT_DATA_MISSING;
            return OBJ_NIL;
        }
        if (0 == cls) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
        if (cls == NODE_CLASS_KLEENE) {
            this->eRc = ERESULT_INVALID_DATA;
            return OBJ_NIL;
        }
#endif
        
        if (this->index <= nodeArray_getSize(this->pArray))
            ;
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_EOF_ERROR;
            return OBJ_NIL;
        }
        
        while (this->index <= nodeArray_getSize(this->pArray)) {
            pNode = nodeArray_Get(this->pArray, this->index);
            if (OBJ_NIL == pNode) {
                this->eRc = ERESULT_GENERAL_FAILURE;
                return 0;
            }
            if (cls == NODE_CLASS_ANY) {
                this->eRc = ERESULT_SUCCESS;
                return pNode;
            }
            curClass = node_getClass(pNode);
            if (cls == curClass) {
                this->eRc = ERESULT_SUCCESS;
                return pNode;
            }
            (void)nodeScan_InputAdvance(this, 1);
        }
        
        this->eRc = ERESULT_DATA_NOT_FOUND;
        return 0;
    }
    
    
    NODE_DATA *     nodeScan_ScanReset(
        NODESCAN_DATA   *this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            this->eRc = ERESULT_DATA_MISSING;
            return OBJ_NIL;
        }
#endif
        
        this->index = 1;
        pNode = nodeArray_Get(this->pArray, this->index);
        if (OBJ_NIL == pNode) {
            this->eRc = ERESULT_GENERAL_FAILURE;
            return OBJ_NIL;
        }
        
        this->eRc = ERESULT_SUCCESS;
        return pNode;
    }
    
    

    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     nodeScan_ToDebugString(
        NODESCAN_DATA   *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(nodeScan) index=%d ",
                     this,
                     nodeScan_getIndex(this)
            );
        AStr_AppendA(pStr, str);

        if (this->pArray) {
            if (((OBJ_DATA *)(this->pArray))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pArray))->pVtbl->pToDebugString(
                                                    this->pArray,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        
        j = snprintf( str, sizeof(str), " %p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeScan_Validate(
        NODESCAN_DATA   *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_NODESCAN) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(NODESCAN_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


