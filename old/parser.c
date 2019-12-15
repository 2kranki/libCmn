// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   parser.c
 *	Generated 07/03/2015 21:39:30
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
#include "parser_internal.h"
#include <nodeHash.h>
#include <token_internal.h>
#include <trace.h>
#include <stdarg.h>



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

    PARSER_DATA *     parser_Alloc(
    )
    {
        PARSER_DATA       *cbp;
        uint32_t        cbSize = sizeof(PARSER_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    PARSER_DATA *     parser_New(
        uint16_t        k
    )
    {
        PARSER_DATA       *cbp;
        
        // Do initialization.
        
        cbp = parser_Alloc();
        cbp = parser_Init(cbp,k);
        
        // Return to caller.
        return( cbp );
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    OBJ_ID          parser_getAux1(
        PARSER_DATA     *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !parser_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pAux1;
    }
    
    
    bool            parser_setAux1(
        PARSER_DATA     *cbp,
        OBJ_ID           pValue
    )
    {
#ifdef NDEBUG
#else
        if( !parser_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pAux1) {
            obj_Release(cbp->pAux1);
        }
        cbp->pAux1 = pValue;
        
        return true;
    }
    
    
    
    OBJ_ID          parser_getAux2(
        PARSER_DATA     *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !parser_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pAux2;
    }
    
    
    bool            parser_setAux2(
        PARSER_DATA     *cbp,
        OBJ_ID           pValue
    )
    {
#ifdef NDEBUG
#else
        if( !parser_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pAux2) {
            obj_Release(cbp->pAux2);
        }
        cbp->pAux2 = pValue;
        
        return true;
    }
    
    
    
    SRCERRORS_DATA * parser_getErrors(
        PARSER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !parser_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pErrors;
    }
    
    
    bool            parser_setErrors(
        PARSER_DATA     *this,
        SRCERRORS_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !parser_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pErrors) {
            obj_Release(this->pErrors);
        }
        this->pErrors = pValue;
        
        return true;
    }
    
    
    
    COMPILER_DATA *  parser_getCompiler(
        PARSER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!parser_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pCompiler;
    }
    
    
    bool            parser_setCompiler(
        PARSER_DATA     *this,
        COMPILER_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!parser_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pCompiler) {
            obj_Release(this->pCompiler);
        }
        this->pCompiler = pValue;
        
        return true;
    }
    
    
    
    bool            parser_setParseFunction(
        PARSER_DATA     *this,
        bool            (*pParse)(OBJ_ID,NODETREE_DATA **),
        OBJ_ID          pParseObj
    )
    {
#ifdef NDEBUG
#else
        if (!parser_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pParse = pParse;
        this->pParseObj  = pParseObj;
        
        return true;
    }
    
    
    
    uint16_t        parser_getPriority(
        PARSER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!parser_Validate(this)) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            parser_setPriority (
        PARSER_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!parser_Validate(this)) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    OBJARRAY_DATA * parser_getSemanticStack (
        PARSER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!parser_Validate(this)) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pSemanticStack;
    }
    
    
    uint32_t        parser_getSize(
        PARSER_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!parser_Validate(this)) {
            DEBUG_BREAK();
        }
#endif
        return( 0 );
    }



    bool            parser_setSourceFunction(
        PARSER_DATA     *this,
        TOKEN_DATA *   (*pSrcChrAdvance)(OBJ_ID,uint16_t),
        TOKEN_DATA *   (*pSrcChrLookAhead)(OBJ_ID,uint16_t),
        OBJ_ID          pSrcObj
    )
    {
#ifdef NDEBUG
#else
        if (!parser_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pSrcChrAdvance = pSrcChrAdvance;
        this->pSrcChrLookAhead = pSrcChrLookAhead;
        this->pSrcObj = pSrcObj;
        
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            parser_Dealloc(
        OBJ_ID          objId
    )
    {
        PARSER_DATA     *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !parser_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        this->pErrors = OBJ_NIL;                // (Not Owned)
        parser_setAux1(this, OBJ_NIL);
        parser_setAux2(this, OBJ_NIL);
        parser_setCompiler(this, OBJ_NIL);

        if (this->pProperties) {
            obj_Release(this->pProperties);
            this->pProperties = OBJ_NIL;
        }
        
        if (this->pSemanticStack) {
            obj_Release(this->pSemanticStack);
            this->pSemanticStack = OBJ_NIL;
        }
        
        if (this->pInputs) {
            uint16_t        ui16;
            for (ui16=0; ui16<this->sizeInputs; ++ui16) {
                if (obj_getType(&this->pInputs[ui16]) == OBJ_IDENT_TOKEN) {
                    //token_ReleaseDataIfObj(&this->pInputs[ui16]);
                }
            }
            mem_Free(this->pInputs);
            this->pInputs = NULL;
            this->sizeInputs = 0;
            this->curInputs = 0;
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                    E r r o r  M e t h o d s
    //---------------------------------------------------------------
    
    // All error methods are simply a pass-thru back to compiler.
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------
    
    PARSER_DATA *   parser_Init(
        PARSER_DATA     *this,
        uint16_t        k
    )
    {
        uint32_t        i;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init(this, obj_getSize(this), OBJ_IDENT_PARSER);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&parser_Vtbl);
        
        this->sizeInputs = k;
        this->pInputs = mem_Calloc(k, sizeof(TOKEN_DATA));
        if (OBJ_NIL == this->pInputs) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        for (i=0; i<k; ++i) {
            TOKEN_DATA      *pToken;
            pToken = &this->pInputs[i];
            token_Init(pToken);
        }
        
        //FIXME: this->pErrors = eResult_Shared();
        
#ifdef NDEBUG
#else
        if( !parser_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->numErrors);
#endif
        
        return this;
    }
    
    
    
    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------
    
    TOKEN_DATA *    parser_InputAdvance(
        PARSER_DATA     *this,
        uint16_t        numChrs
    )
    {
        uint32_t        i;
        
        // Do initialization.
        TRC_OBJ( this, "parser_InputAdvance: %d\n", numChrs );
#ifdef NDEBUG
#else
        if( !parser_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        // Shift inputs.
        for (i=0; i<numChrs; ++i) {
            parser_InputNextChar(this);
        }
        
        // Return to caller.
        return &this->pInputs[this->curInputs];
    }
    
    
    
    //--------------------------------------------------------------
    //               I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------
    
    TOKEN_DATA *    parser_InputLookAhead(
        PARSER_DATA     *this,
        uint16_t        num
    )
    {
        uint16_t        idx;
        TOKEN_DATA      *pToken;
        
        // Do initialization.
        TRC_OBJ( this, "parser_InputLookAhead: %d\n", num );
#ifdef NDEBUG
#else
        if( !parser_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (!obj_IsFlag(this, PARSER_INIT_DONE)) {
            parser_InputAdvance(this, this->sizeInputs);
            obj_FlagOn(this, PARSER_INIT_DONE);
        }
        
        idx = (this->curInputs + num - 1) % this->sizeInputs;
        pToken = &this->pInputs[idx];
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA       *pStr = token_ToDebugString(pToken, 4);
            TRC_OBJ( this, "\treturning token = %s\n", AStr_getData(pStr) );
            obj_Release(pStr);
        }
#endif
        
        // Return to caller.
        return pToken;
    }
    
    
    
    
    //--------------------------------------------------------------
    //                  I n p u t  N e x t  C h a r
    //--------------------------------------------------------------
    
    ERESULT         parser_InputNextChar(
        PARSER_DATA     *this
    )
    {
        TOKEN_DATA      *scp;
        TOKEN_DATA      *pToken;
        
        // Do initialization.
        TRC_OBJ( this, "parser_InputNextChar: \n" );
#ifdef NDEBUG
#else
        if( !parser_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        BREAK_NULL(this->pSrcChrLookAhead);
        BREAK_NULL(this->pSrcChrAdvance);
        
        // Release top token;
        //token_ReleaseDataIfObj(&this->pInputs[this->curInputs]);
        
        // Add the next char to the queue.
        pToken = &this->pInputs[this->curInputs];
        scp = this->pSrcChrLookAhead(this->pSrcObj,1);
        BREAK_NULL(scp);
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA       *pStr = token_ToDebugString(scp, 4);
            TRC_OBJ( this, "\ttoken(%d) = %s\n", this->curInputs, AStr_getData(pStr) );
            obj_Release(pStr);
        }
#endif
        token_Assign(scp, pToken);
        this->curInputs = (this->curInputs + 1) % this->sizeInputs;
        this->pSrcChrAdvance(this->pSrcObj,1);
        
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  C h r
    //--------------------------------------------------------------
    
    TOKEN_DATA *    parser_MatchInputChr(
        PARSER_DATA     *this,
        int32_t         chr
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !parser_Validate( this ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        if(chr == token_getChrW32(&this->pInputs[0]) ) {
            obj_Retain(&this->pInputs[0]);
            scp = &this->pInputs[0];
            (void)parser_InputNextChar(this);
            return scp;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  C l a s s
    //--------------------------------------------------------------
    
    TOKEN_DATA *    parser_MatchInputCls(
        PARSER_DATA     *this,
        int32_t         cls
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !parser_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        scp = &this->pInputs[0];
        if(cls == token_getClass(scp) ) {
            obj_Retain(scp);
            (void)parser_InputNextChar(this);
            return scp;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //--------------------------------------------------------------
    //               M a t c h  I n p u t  R a n g e
    //--------------------------------------------------------------
    
    TOKEN_DATA *    parser_MatchInputRange(
        PARSER_DATA     *this,
        int32_t         chrBeg,
        int32_t         chrEnd
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        int32_t         chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !parser_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        scp = &this->pInputs[0];
        chr = token_getChrW32(scp);
        if((chr >= chrBeg) && (chr <= chrEnd) ) {
            obj_Retain(scp);
            (void)parser_InputNextChar(this);
            return scp;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  S e t
    //--------------------------------------------------------------
    
    TOKEN_DATA *    parser_MatchInputSet(
        PARSER_DATA     *this,
        int32_t         *pSet           // NULL-terminated Set
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        int32_t         chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !parser_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (NULL == pSet) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        scp = &this->pInputs[0];
        chr = token_getChrW32(scp);
        while (*pSet) {
            if(chr == *pSet) {
                obj_Retain(scp);
                (void)parser_InputNextChar(this);
                return scp;
            }
            ++pSet;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P a r s e
    //---------------------------------------------------------------
    
    ERESULT         parser_Parse(
        PARSER_DATA     *this,
        NODETREE_DATA   **ppTree
    )
    {
        //ERESULT         eRc;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !parser_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        BREAK_NULL(this->pParse);
        fRc = this->pParse(this->pParseObj,ppTree);
        if (!fRc) {
            return ERESULT_GENERAL_FAILURE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P r o p e r t y
    //---------------------------------------------------------------
    
    NODE_DATA *     parser_Property(
        PARSER_DATA     *this,
        const
        char            *pName
    )
    {
        //ERESULT         eRc;
        NODE_DATA       *pProperty = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !parser_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            pProperty = nodeHash_FindA(this->pProperties, 0, pName);
        }
        
        // Return to caller.
        return pProperty;
    }
    
    
    
    //---------------------------------------------------------------
    //                     P r o p e r t y  A d d
    //---------------------------------------------------------------
    
    ERESULT         parser_PropertyAdd(
        PARSER_DATA     *this,
        NODE_DATA       *pData
        )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !parser_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pData) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (OBJ_NIL == this->pProperties) {
            this->pProperties = nodeHash_NewWithSize( 17 );
            if (OBJ_NIL == this->pProperties) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        eRc = nodeHash_Add( this->pProperties, pData );
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //              P r o p e r t y  C o u n t
    //---------------------------------------------------------------
    
    uint16_t        parser_PropertyCount(
        PARSER_DATA		*this
    )
    {
        uint16_t        num = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !parser_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (this->pProperties) {
            num = nodeHash_getSize(this->pProperties);
        }
        
        // Return to caller.
        return num;
    }
    
    
    
    //---------------------------------------------------------------
    //                    P r o p e r t i e s
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * parser_Properties(
        PARSER_DATA     *this
    )
    {
        //ERESULT         eRc;
        NODEARRAY_DATA  *pProperties = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !parser_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            pProperties = nodeHash_Nodes(this->pProperties);
        }
        
        // Return to caller.
        return pProperties;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          parser_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        PARSER_DATA     *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !parser_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(PARSER_DATA);
                break;
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
#ifdef XYZZY
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return hex_Disable;
                        }
                        break;
                        
                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return hex_Enable;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return hex_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return hex_ToJSON;
                        }
                        break;
#endif
                        
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
    //                      S e m  G e t
    //---------------------------------------------------------------
    
    NODE_DATA *     parser_SemGet(
        PARSER_DATA     *this,
        uint16_t        index
    )
    {
        NODE_DATA       *pItem = OBJ_NIL;
        
        if( this->pSemanticStack ) {
            pItem = objArray_Get(this->pSemanticStack,index);
        }
        
        // Return to caller.
#ifdef NDEBUG
#else
        if (pItem) {
            TRC_OBJ( this,
                    "\tparser_SemGet(%d):  returning: %s\n",
                    index,
                    node_getName(pItem)
                    );
        }
        else {
            TRC_OBJ( this,
                    "\tparser_SemGet(%d):  returning: NULL\n",
                    index
                    );
        }
#endif
        return pItem;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e m  P o p
    //---------------------------------------------------------------
    
    NODE_DATA *         parser_SemPop(
        PARSER_DATA     *this
    )
    {
        NODE_DATA       *pItem = OBJ_NIL;
        
        /* Pop 1 element from the top of the semantic stack.
         */
        if( this->pSemanticStack ) {
            pItem = objArray_DeleteLast(this->pSemanticStack);
            TRC_OBJ( this,
                     "\tparser_SemPop:  %s\n",
                     node_getName(pItem)
            );
        }
        
        // Return to caller.
        return pItem;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e m  P u s h
    //---------------------------------------------------------------
    
    bool			parser_SemPush(
        PARSER_DATA     *this,
        NODE_DATA       *pItem
    )
    {
        ERESULT         eRc;
        
        if  (NULL == pItem) {
            DEBUG_BREAK();
            return false;
        }
        
        if (this->pSemanticStack == OBJ_NIL) {
            this->pSemanticStack = objArray_New();
            if (this->pSemanticStack == OBJ_NIL) {
                DEBUG_BREAK();
                return false;
            }
        }
        
        eRc = objArray_AppendObj(this->pSemanticStack, pItem, NULL);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            TRC_OBJ( this,
                     "\tparse_SemPush:  %s\n",
                     node_getName(pItem)
            );
        }
        else {
            DEBUG_BREAK();
            return false;
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e m  T o p
    //---------------------------------------------------------------
    
    NODE_DATA *     parser_SemTop(
        PARSER_DATA     *this
    )
    {
        NODE_DATA       *pItem = OBJ_NIL;
        
        if( this->pSemanticStack ) {
            pItem = objArray_GetLast(this->pSemanticStack);
            if (pItem) {
                TRC_OBJ( this,
                         "\tparser_SemTop:  %s\n",
                         node_getName(pItem)
                );
            }
        }
        
        // Return to caller.
        return pItem;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            parser_Validate(
        PARSER_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_PARSER) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(PARSER_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


