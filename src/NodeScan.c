// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeScan.c
 *	Generated 12/17/2019 10:10:16
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
#include        <NodeScan_internal.h>
#include        <ascii.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    int             NodeScan_ScanfLex(
        NODESCAN_DATA  *this
    );

    int             NodeScan_ScanfLexLA(
        NODESCAN_DATA  *this
    );

    int             NodeScan_ScanfLabel(
        NODESCAN_DATA  *this
    );


    int             NodeScan_ScanfType(
       NODESCAN_DATA  *this
    );


    int             NodeScan_ScanfLabel(
        NODESCAN_DATA  *this
    )
    {
        int             tok = TOK_TYP_INVALID;
        //W32CHR_T         chr;
        //int             i = 0;
        
        tok = NodeScan_ScanfLex(this);
        if (tok == TOK_TYP_PERCENT) {
            tok = NodeScan_ScanfLexLA(this);
            if (tok == TOK_TYP_INT) {
                
            }
            else {
                return TOK_TYP_INVALID;
            }
        }
        
        return TOK_TYP_INVALID;
    }


    int             NodeScan_ScanfLex(
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



    int             NodeScan_ScanfLexLA(
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

    NODESCAN_DATA *     NodeScan_Alloc (
        void
    )
    {
        NODESCAN_DATA       *this;
        uint32_t        cbSize = sizeof(NODESCAN_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODESCAN_DATA *     NodeScan_New (
        void
    )
    {
        NODESCAN_DATA       *this;
        
        this = NodeScan_Alloc( );
        if (this) {
            this = NodeScan_Init(this);
        } 
        return this;
    }


    NODESCAN_DATA *     NodeScan_NewFromArray (
        NODETREE_DATA   *pTree,
        NODEARRAY_DATA  *pArray     // Tree converted to array with up/down members.
    )
    {
        NODESCAN_DATA       *this;
        
        if (OBJ_NIL == pTree) {
            return OBJ_NIL;
        }
        if (OBJ_NIL == pArray) {
            return OBJ_NIL;
        }

        this = NodeScan_New( );
        if (this) {
            NodeScan_setTree(this, pTree);
            NodeScan_setCloseNode(this, NodeTree_getCloseNode(pTree));
            NodeScan_setOpenNode(this, NodeTree_getOpenNode(pTree));
            NodeScan_setArray(this, pArray);
        }
        return this;
    }


    NODESCAN_DATA *     NodeScan_NewFromTreePost (
        NODETREE_DATA   *pTree
    )
    {
        NODESCAN_DATA   *this;
        NODEARRAY_DATA  *pArray;
        
        if (OBJ_NIL == pTree) {
            return OBJ_NIL;
        }

        this = NodeScan_New( );
        if (this) {
            NodeScan_setTree(this, pTree);
            NodeScan_setCloseNode(this, NodeTree_getCloseNode(pTree));
            NodeScan_setOpenNode(this, NodeTree_getOpenNode(pTree));
            pArray = NodeTree_ToLinearizationPost(pTree);
            NodeScan_setArray(this, pArray);
            if (OBJ_NIL == pArray) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            obj_Release(pArray);
        }
        return this;
    }


    NODESCAN_DATA *     NodeScan_NewFromTreePre (
        NODETREE_DATA   *pTree
    )
    {
        NODESCAN_DATA   *this;
        NODEARRAY_DATA  *pArray;
        
        if (OBJ_NIL == pTree) {
            return OBJ_NIL;
        }

        this = NodeScan_New( );
        if (this) {
            NodeScan_setTree(this, pTree);
            NodeScan_setCloseNode(this, NodeTree_getCloseNode(pTree));
            NodeScan_setOpenNode(this, NodeTree_getOpenNode(pTree));
            pArray = NodeTree_ToLinearizationPre(pTree);
            if (OBJ_NIL == pArray) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            NodeScan_setArray(this, pArray);
            obj_Release(pArray);
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A r r a y
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * NodeScan_getArray(
        NODESCAN_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    
    bool            NodeScan_setArray(
        NODESCAN_DATA   *this,
        NODEARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !NodeScan_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pArray) {
            obj_Release(this->pArray);
        }
        this->pArray = pValue;
        NodeScan_setIndex(this, 0);
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                    C l o s e  N o d e
    //---------------------------------------------------------------
    
    NODELINK_DATA * NodeScan_getCloseNode(
        NODESCAN_DATA   *this
    )
    {
        
#ifdef NDEBUG
#else
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        return this->pClose;
    }
    
    
    bool            NodeScan_setCloseNode(
        NODESCAN_DATA   *this,
        NODELINK_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !NodeScan_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef PROPERTY_CLOSE_OWNED
        obj_Retain(pValue);
        if (this->pClose) {
            obj_Release(this->pClose);
        }
#endif
        this->pClose = pValue;

        return true;
    }
    
    

    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------
    
    uint32_t        NodeScan_getIndex(
        NODESCAN_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->index;
    }

    bool            NodeScan_setIndex(
        NODESCAN_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->index = value;
        
        return true;
    }



    //---------------------------------------------------------------
    //                    O p e n  N o d e
    //---------------------------------------------------------------
    
    NODELINK_DATA * NodeScan_getOpenNode(
        NODESCAN_DATA   *this
    )
    {
        
#ifdef NDEBUG
#else
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        return this->pOpen;
    }
    
    
    bool            NodeScan_setOpenNode(
        NODESCAN_DATA   *this,
        NODELINK_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !NodeScan_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef PROPERTY_OPEN_OWNED
        obj_Retain(pValue);
        if (this->pOpen) {
            obj_Release(this->pOpen);
        }
#endif
        this->pOpen = pValue;

        return true;
    }
        
        

    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        NodeScan_getSize (
        NODESCAN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NodeScan_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S t a r t
    //---------------------------------------------------------------
    
    uint32_t        NodeScan_getStart(
        NODESCAN_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->start;
    }
        

        
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NodeScan_getSuperVtbl (
        NODESCAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeScan_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                      N o d e  T r e e
    //---------------------------------------------------------------
    
    NODETREE_DATA * NodeScan_getTree(
        NODESCAN_DATA   *this
    )
    {
        
#ifdef NDEBUG
#else
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        return this->pTree;
    }
    
    
    bool            NodeScan_setTree(
        NODESCAN_DATA   *this,
        NODETREE_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !NodeScan_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef PROPERTY_TREE_OWNED
        obj_Retain(pValue);
        if (this->pTree) {
            obj_Release(this->pTree);
        }
#endif
        this->pTree = pValue;

        return true;
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
        ERESULT eRc = NodeScan_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NODESCAN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NodeScan_Assign (
        NODESCAN_DATA		*this,
        NODESCAN_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeScan_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeScan_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
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
    ERESULT         NodeScan_Compare (
        NODESCAN_DATA     *this,
        NODESCAN_DATA     *pOther
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
        if (!NodeScan_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeScan_Validate(pOther)) {
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
        NodeScan      *pCopy = NodeScan_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NODESCAN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODESCAN_DATA *     NodeScan_Copy (
        NODESCAN_DATA       *this
    )
    {
        NODESCAN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeScan_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NodeScan_New( );
        if (pOther) {
            eRc = NodeScan_Assign(this, pOther);
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

    void            NodeScan_Dealloc (
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
        if (!NodeScan_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODESCAN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        NodeScan_setArray(this, OBJ_NIL);
        NodeScan_setCloseNode(this, OBJ_NIL);
        NodeScan_setOpenNode(this, OBJ_NIL);
        NodeScan_setTree(this, OBJ_NIL);
        this->index = 0;
        this->start = 0;
        if (this->pScanInput) {
            obj_Release(this->pScanInput);
            this->pScanInput = OBJ_NIL;
        }


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
    ERESULT         NodeScan_Disable (
        NODESCAN_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeScan_Validate(this)) {
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
    ERESULT         NodeScan_Enable (
        NODESCAN_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeScan_Validate(this)) {
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

    NODESCAN_DATA *   NodeScan_Init (
        NODESCAN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODESCAN_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODESCAN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodeScan_Vtbl);
        
    #ifdef NDEBUG
    #else
        if (!NodeScan_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "NodeScan::sizeof(NODESCAN_DATA) = %lu\n", sizeof(NODESCAN_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODESCAN_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NodeScan_IsEnabled (
        NODESCAN_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeScan_Validate(this)) {
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
    
    
    
    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------
    
    NODE_DATA *     NodeScan_InputAdvance(
        NODESCAN_DATA    *this,
        uint32_t        numChrs
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (numChrs > 0)
            ;
        else {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return OBJ_NIL;
        }
#endif
        
        // Shift inputs.
        this->index += numChrs;
        if (this->index < NodeArray_getSize(this->pArray))
            ;
        else {
            return OBJ_NIL;
        }
        pNode = NodeArray_Get(this->pArray, (this->index + 1));

        // Return to caller.
        return pNode;
    }
    
    
    
    //--------------------------------------------------------------
    //               I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------
    
    NODE_DATA *     NodeScan_InputLookAhead(
        NODESCAN_DATA   *this,
        uint32_t        num
    )
    {
        uint32_t        idx;
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_DATA_MISSING);
            return OBJ_NIL;
        }
        if (num > 0)
            ;
        else {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return OBJ_NIL;
        }
#endif
        
        idx = this->index + (num - 1);
        if (idx < NodeArray_getSize(this->pArray))
            ;
        else {
            return OBJ_NIL;
        }
        pNode = NodeArray_Get(this->pArray, (idx + 1));
        
        // Return to caller.
        return pNode;
    }
    
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  N a m e
    //--------------------------------------------------------------
    
    NODE_DATA *     NodeScan_MatchName(
        NODESCAN_DATA    *this,
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
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        this->start = this->index;
        
        pNode = NodeScan_InputLookAhead(this, 1);
        if (pNode) {
            pName = node_getNameUTF8(pNode);
            cmp = strcmp(pName, pStr);
            mem_Free((void *)pName);
            if( 0 == cmp ) {
                (void)NodeScan_InputAdvance(this, 1);
                return pNode;
            }
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  C l a s s
    //--------------------------------------------------------------
    
    NODE_DATA *     NodeScan_MatchClass(
        NODESCAN_DATA    *this,
        int32_t         cls
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        this->start = this->index;

        if (this->index < NodeArray_getSize(this->pArray))
            ;
        else {
            return OBJ_NIL;
        }

        pNode = NodeScan_InputLookAhead(this, 1);
        if( pNode && ((cls == node_getClass(pNode)) || (cls == NODE_CLASS_ANY)) ) {
            (void)NodeScan_InputAdvance(this, 1);
            return pNode;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    

    //--------------------------------------------------------------
    //              M a t c h  I n p u t  C l a s s e s
    //--------------------------------------------------------------
    
    NODE_DATA *     NodeScan_MatchClasses(
        NODESCAN_DATA   *this,
        int32_t         *pSet
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        uint32_t        start;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (NULL == pSet) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        start = this->index;
        
        while (*pSet) {
            pNode = NodeScan_MatchClass(this, *pSet);
            if(pNode) {
                this->start = start;
                return pNode;
            }
            ++pSet;
        }
        
        // Return to caller.
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
    NODE_DATA *     NodeScan_MatchClassesRegex(
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
        //uint32_t        j;
        int32_t         *pIdxRegex;
        int32_t         curRegex;
        int32_t         stopRegex;
        //int32_t         curClass;
        bool            fKleene = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (NULL == pRegex) {
            DEBUG_BREAK();
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
            if ((startIndex + 1) <= NodeArray_getSize(this->pArray))
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
                pNodeStart = NodeScan_InputLookAhead(this, 1);
                if (OBJ_NIL == pNodeStart) {
                    return OBJ_NIL;
                }
            }
            else {
                stopRegex = curRegex;
            }
            if (0 == stopRegex) {
                return OBJ_NIL;
            }
            pNode = NodeScan_ScanClassUntil(this, stopRegex);
            if (OBJ_NIL == pNode) {
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
                    pNode = NodeScan_ScanClassUntil(this, stopRegex);
                    if (OBJ_NIL == pNode) {
                        return OBJ_NIL;
                    }
                }
                else
                    stopRegex = curRegex;
                pNode = NodeArray_Get(this->pArray, 1);
                if(pNode) {
                    return pNode;
                }
                ++pIdxRegex;
            }
        }
        
        // Return to caller.
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
        void        *pMethod = NodeScan_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NodeScan", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NodeScan_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODESCAN_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NodeScan_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODESCAN_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NodeScan_Class();
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
                            return NodeScan_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NodeScan_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NodeScan_ToDebugString;
                        }
#ifdef  SRCREF_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return NodeScan_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NodeScan_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == NodeScan_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       S c a n
    //---------------------------------------------------------------
    
    NODE_DATA *     NodeScan_ScanClassUntil(
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
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (0 == cls) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (cls == NODE_CLASS_KLEENE) {
            return OBJ_NIL;
        }
#endif
        
        if (this->index < NodeArray_getSize(this->pArray))
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        while (this->index < NodeArray_getSize(this->pArray)) {
            pNode = NodeArray_Get(this->pArray, (this->index + 1));
            if (OBJ_NIL == pNode) {
                return 0;
            }
            if (cls == NODE_CLASS_ANY) {
                return pNode;
            }
            curClass = node_getClass(pNode);
            if (cls == curClass) {
                return pNode;
            }
            (void)NodeScan_InputAdvance(this, 1);
        }
        
        return 0;
    }
    
    
    NODE_DATA *     NodeScan_ScanReset(
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
        if( !NodeScan_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        this->index = 0;
        pNode = NodeArray_Get(this->pArray, (this->index + 1));
        if (OBJ_NIL == pNode) {
            return OBJ_NIL;
        }
        
        return pNode;
    }
        
        

    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
#ifdef  NODESCAN_JSON_SUPPORT
     ASTR_DATA *     NodeScan_ToJson (
        NODESCAN_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!NodeScan_Validate(this)) {
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
        ASTR_DATA      *pDesc = NodeScan_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeScan_ToDebugString (
        NODESCAN_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeScan_Validate(this)) {
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
                    NodeScan_getSize(this),
                    obj_getRetainCount(this)
            );

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
    bool            NodeScan_Validate (
        NODESCAN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODESCAN))
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


        if (!(obj_getSize(this) >= sizeof(NODESCAN_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


