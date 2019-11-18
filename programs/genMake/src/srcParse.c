// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   srcParse.c
 *	Generated 08/19/2019 01:17:17
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
#include        <srcParse_internal.h>
#include        <hjson.h>
#include        <NodeHdr.h>
#include        <NodeLib.h>
#include        <NodeObj.h>
#include        <NodePgm.h>
#include        <NodeRtn.h>
#include        <NodeTest.h>
#include        <srcErrors.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            srcParse_task_body (
        void            *pData
    )
    {
        //SRCPARSE_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SRCPARSE_DATA *     srcParse_Alloc (
        void
    )
    {
        SRCPARSE_DATA       *this;
        uint32_t        cbSize = sizeof(SRCPARSE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SRCPARSE_DATA *     srcParse_New (
        void
    )
    {
        SRCPARSE_DATA       *this;
        
        this = srcParse_Alloc( );
        if (this) {
            this = srcParse_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                       L i b r a r y
    //---------------------------------------------------------------
    
    NODELIB_DATA *  srcParse_getLib (
        SRCPARSE_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pLib;
    }
    
    
    bool            srcParse_setLib (
        SRCPARSE_DATA   *this,
        NODELIB_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_LIB_OWNED
        obj_Retain(pValue);
        if (this->pLib) {
            obj_Release(this->pLib);
        }
#endif
        this->pLib = pValue;
        
        return true;
    }
            
            
            
    //---------------------------------------------------------------
    //                       N o d e s
    //---------------------------------------------------------------
    
    NODE_DATA *  srcParse_getNodes (
        SRCPARSE_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pNodes;
    }
    
    
    bool            srcParse_setNodes (
        SRCPARSE_DATA   *this,
        NODE_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_NODES_OWNED
        obj_Retain(pValue);
        if (this->pNodes) {
            obj_Release(this->pNodes);
        }
#endif
        this->pNodes = pValue;
        
        return true;
    }
                
                
                
    //---------------------------------------------------------------
    //                        O b j e c t s
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * srcParse_getObjs (
        SRCPARSE_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pObjs;
    }
    
    
    bool            srcParse_setObjs (
        SRCPARSE_DATA   *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_OBJS_OWNED
        obj_Retain(pValue);
        if (this->pObjs) {
            obj_Release(this->pObjs);
        }
#endif
        this->pObjs = pValue;
        
        return true;
    }
        
        
        
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        srcParse_getPriority (
        SRCPARSE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            srcParse_setPriority (
        SRCPARSE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                       L i b r a r y
    //---------------------------------------------------------------
    
    NODEPGM_DATA *  srcParse_getPgm (
        SRCPARSE_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pPgm;
    }
    
    
    bool            srcParse_setPgm (
        SRCPARSE_DATA   *this,
        NODEPGM_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_PGM_OWNED
        obj_Retain(pValue);
        if (this->pPgm) {
            obj_Release(this->pPgm);
        }
#endif
        this->pPgm = pValue;
        
        return true;
    }
                
                
                
    //---------------------------------------------------------------
    //                        R o u t i n e s
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * srcParse_getRtns (
        SRCPARSE_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pRtns;
    }
    
    
    bool            srcParse_setRtns (
        SRCPARSE_DATA   *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_RTNS_OWNED
        obj_Retain(pValue);
        if (this->pRtns) {
            obj_Release(this->pRtns);
        }
#endif
        this->pRtns = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        srcParse_getSize (
        SRCPARSE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  srcParse_getSuperVtbl (
        SRCPARSE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
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
        ERESULT eRc = srcParse_Assign(this,pOther);
     @endcode 
     @param     this    SRCPARSE object pointer
     @param     pOther  a pointer to another SRCPARSE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         srcParse_Assign (
        SRCPARSE_DATA		*this,
        SRCPARSE_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!srcParse_Validate(pOther)) {
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
    ERESULT         srcParse_Compare (
        SRCPARSE_DATA     *this,
        SRCPARSE_DATA     *pOther
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
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!srcParse_Validate(pOther)) {
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
        srcParse      *pCopy = srcParse_Copy(this);
     @endcode 
     @param     this    SRCPARSE object pointer
     @return    If successful, a SRCPARSE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SRCPARSE_DATA *     srcParse_Copy (
        SRCPARSE_DATA       *this
    )
    {
        SRCPARSE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = srcParse_New( );
        if (pOther) {
            eRc = srcParse_Assign(this, pOther);
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

    void            srcParse_Dealloc (
        OBJ_ID          objId
    )
    {
        SRCPARSE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SRCPARSE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        srcParse_setLib(this, OBJ_NIL);
        srcParse_setObjs(this, OBJ_NIL);
        srcParse_setPgm(this, OBJ_NIL);
        srcParse_setRtns(this, OBJ_NIL);

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
    ERESULT         srcParse_Disable (
        SRCPARSE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!srcParse_Validate(this)) {
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
    ERESULT         srcParse_Enable (
        SRCPARSE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!srcParse_Validate(this)) {
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

    SRCPARSE_DATA *   srcParse_Init (
        SRCPARSE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SRCPARSE_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, MAIN_IDENT_SRCPARSE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&srcParse_Vtbl);
        
        this->pObjs = objArray_New( );
        if (OBJ_NIL == this->pObjs) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pRtns = objArray_New( );
        if (OBJ_NIL == this->pRtns) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "srcParse::sizeof(SRCPARSE_DATA) = %lu\n", sizeof(SRCPARSE_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SRCPARSE_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         srcParse_IsEnabled (
        SRCPARSE_DATA	*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
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
    //              P a r s e  J s o n  I n p u t
    //---------------------------------------------------------------
    
    ERESULT_DATA *  srcParse_ParseJsonFile(
        SRCPARSE_DATA   *this,
        PATH_DATA       *pPath,
        NODE_DATA       **ppNodes
    )
    {
        ERESULT_DATA    *pErr = OBJ_NIL;
        HJSON_DATA      *pObj = OBJ_NIL;
        NODEHASH_DATA   *pHash;
        NODE_DATA       *pFileNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcParse_Validate(this) ) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
        if (OBJ_NIL == ppNodes) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
#endif
        *ppNodes = OBJ_NIL;

        pObj = hjson_NewFromPath(pPath, 4);
        if (pObj) {
            pFileNode = hjson_ParseFileHash(pObj);
            srcErrors_ExitOnFatal(OBJ_NIL);
            obj_Release(pObj);
            pObj = OBJ_NIL;
        }
        
        if (pFileNode) {
            pHash = node_getData(pFileNode);
            if (OBJ_NIL == pHash) {
                fprintf(stderr, "ERROR - No JSON Hash to process\n\n\n");
                exit(12);
            }
            if (!obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
                fprintf(stderr, "ERROR - Missing JSON Hash to process\n\n\n");
                exit(12);
            }
        }
        else {
            fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
            exit(12);
        }
        
        // Return to caller.
        if (OBJ_NIL == pErr)
            *ppNodes = pFileNode;
        return pErr;
    }
    
    
    ERESULT_DATA *  srcParse_ParseJsonStr(
        SRCPARSE_DATA   *this,
        const
        char            *pStrA,
        NODE_DATA       **ppNodes
    )
    {
        ERESULT_DATA    *pErr = OBJ_NIL;
        HJSON_DATA      *pObj = OBJ_NIL;
        NODE_DATA       *pFileNode = OBJ_NIL;
        NODEHASH_DATA   *pHash = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcParse_Validate(this) ) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
        if (NULL == pStrA) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
        if (OBJ_NIL == ppNodes) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
#endif
        *ppNodes = OBJ_NIL;
        
        pObj = hjson_NewA(pStrA, 4);
        if (pObj) {
            pFileNode = hjson_ParseFileHash(pObj);
            srcErrors_ExitOnFatal(OBJ_NIL);
            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        if (pFileNode) {
            pHash = node_getData(pFileNode);
            if (OBJ_NIL == pHash) {
                fprintf(stderr, "ERROR - No JSON Hash to process\n\n\n");
                exit(12);
            }
            if (!obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
                fprintf(stderr, "ERROR - Missing JSON Hash to process\n\n\n");
                exit(12);
            }
        }
        else {
            fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
            exit(12);
        }

        // Return to caller.
        if (OBJ_NIL == pErr)
            *ppNodes = pFileNode;
        return pErr;
    }
    
    

    //---------------------------------------------------------------
    //                  P a r s e  L i b r a r y
    //---------------------------------------------------------------
    
    ERESULT_DATA *  srcParse_ParseLibrary(
        SRCPARSE_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        ERESULT_DATA    *pErr = OBJ_NIL;
        NODELIB_DATA    *pLib = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcParse_Validate(this) ) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
        if(OBJ_NIL == pNode) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
        if(!obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
        //BREAK_NULL(this->pDict);
#endif
        
        // We cheat and let NodeLib parse the Object.
        pErr = NodeLib_Parse(pNode, &pLib);
        if (pErr) {
            DEBUG_BREAK();
            return pErr;
        }
        this->pLib = pLib;

        // Return to caller.
        return pErr;
    }
    
            
            
        //---------------------------------------------------------------
        //                  P a r s e  O b j e c t
        //---------------------------------------------------------------

        ERESULT_DATA *  srcParse_ParseObject(
            SRCPARSE_DATA   *this,
            NODE_DATA       *pNode
        )
        {
            ERESULT         eRc;
            NODEOBJ_DATA    *pObj = OBJ_NIL;        // Primary Object
            ERESULT_DATA    *pErr = OBJ_NIL;

            // Do initialization.
    #ifdef NDEBUG
    #else
            if (!srcParse_Validate(this)) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
            }
            if (OBJ_NIL == pNode) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
            }
            if (!obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
            }
    #endif
            
            // We cheat and let NodeObj parse the Object.
            pErr = NodeObj_Parse(pNode, &pObj);
            if (pErr) {
                DEBUG_BREAK();
                return pErr;
            }
            
            eRc = objArray_AppendObj(this->pObjs, pObj, NULL);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(pObj);
                return eResult_NewStrA(eRc, NULL);
            }
            obj_Release(pObj);
            pObj = OBJ_NIL;

            // Return to caller.
            return pErr;
        }
        
        
        
        //---------------------------------------------------------------
        //                  P a r s e  O b j e c t s
        //---------------------------------------------------------------
        
        ERESULT_DATA *  srcParse_ParseObjects(
            SRCPARSE_DATA   *this,
            NODE_DATA       *pNodes
        )
        {
            ERESULT_DATA    *pErr = OBJ_NIL;
            NODEARRAY_DATA  *pArray = OBJ_NIL;
            NODE_DATA       *pNode = OBJ_NIL;
            uint32_t        i;
            uint32_t        iMax;

            // Do initialization.
    #ifdef NDEBUG
    #else
            if( !srcParse_Validate(this) ) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
            }
            if (OBJ_NIL == pNodes) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
            }
            if (!obj_IsKindOf(pNodes, OBJ_IDENT_NODE)) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
            }
    #endif
            
            pArray = jsonIn_CheckNodeForArray(pNodes);
            if (pArray) {
                iMax = nodeArray_getSize(pArray);
                for(i=0; i<iMax; ++i) {
                    pNode = nodeArray_Get(pArray, (i+1));
                    if (pNode) {
                        pErr = srcParse_ParseObject(this, pNode);
                        if (pErr) {
                            DEBUG_BREAK();
                            break;
                        }
                    }
                }
            }
            else {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_SYNTAX,
                                       "Objects must be found in an array!");
            }

            // Return to caller.
            return pErr;
        }
        
        
        
        //---------------------------------------------------------------
        //                  P a r s e  L i b r a r y
        //---------------------------------------------------------------
        
        ERESULT_DATA *  srcParse_ParseProgram(
            SRCPARSE_DATA   *this,
            NODE_DATA       *pNode
        )
        {
            ERESULT_DATA    *pErr = OBJ_NIL;
            NODEPGM_DATA    *pPgm = OBJ_NIL;

            // Do initialization.
    #ifdef NDEBUG
    #else
            if( !srcParse_Validate(this) ) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
            }
            if(OBJ_NIL == pNode) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
            }
            if(!obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
                DEBUG_BREAK();
                return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
            }
            //BREAK_NULL(this->pDict);
    #endif
            
            // We cheat and let NodeLib parse the Object.
            pErr = NodePgm_Parse(pNode, &pPgm);
            if (pErr) {
                DEBUG_BREAK();
                return pErr;
            }
            this->pPgm = pPgm;

            // Return to caller.
            return pErr;
        }
        
                
                
    //---------------------------------------------------------------
    //                  P a r s e  R o u t i n e
    //---------------------------------------------------------------

    ERESULT_DATA *  srcParse_ParseRoutine(
        SRCPARSE_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        ERESULT         eRc;
        NODERTN_DATA    *pRtn = OBJ_NIL;
        ERESULT_DATA    *pErr = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
        if (OBJ_NIL == pNode) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
        if (!obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
#endif
        
        // We cheat and let NodeRtn parse the Object.
        pErr = NodeRtn_Parse(pNode, &pRtn);
        if (pErr) {
            DEBUG_BREAK();
            return pErr;
        }
        
        eRc = objArray_AppendObj(this->pRtns, pRtn, NULL);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pRtn);
            return eResult_NewStrA(eRc, NULL);
        }
        obj_Release(pRtn);
        pRtn = OBJ_NIL;

        // Return to caller.
        return pErr;
    }
    
    
    
    //---------------------------------------------------------------
    //                  P a r s e  R o u t i n e s
    //---------------------------------------------------------------
    
    ERESULT_DATA *  srcParse_ParseRoutines(
        SRCPARSE_DATA   *this,
        NODE_DATA       *pNodes
    )
    {
        ERESULT_DATA    *pErr = OBJ_NIL;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !srcParse_Validate(this) ) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
        if (OBJ_NIL == pNodes) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
        if (!obj_IsKindOf(pNodes, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_PARAMETER, NULL);
        }
#endif
        
        pArray = jsonIn_CheckNodeForArray(pNodes);
        if (pArray) {
            iMax = nodeArray_getSize(pArray);
            for(i=0; i<iMax; ++i) {
                pNode = nodeArray_Get(pArray, (i+1));
                if (pNode) {
                    pErr = srcParse_ParseRoutine(this, pNode);
                    if (pErr) {
                        DEBUG_BREAK();
                        break;
                    }
                }
            }
        }
        else {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_SYNTAX,
                                   "Objects must be found in an array!");
        }

        // Return to caller.
        return pErr;
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
        void        *pMethod = srcParse_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "srcParse", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          srcParse_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SRCPARSE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SRCPARSE_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)srcParse_Class();
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
                            return srcParse_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return srcParse_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return srcParse_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == srcParse_ToDebugString)
                    return "ToDebugString";
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
        ASTR_DATA      *pDesc = srcParse_ToDebugString(this,4);
     @endcode 
     @param     this    SRCPARSE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     srcParse_ToDebugString (
        SRCPARSE_DATA   *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!srcParse_Validate(this)) {
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
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    srcParse_getSize(this)
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
    bool            srcParse_Validate (
        SRCPARSE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, MAIN_IDENT_SRCPARSE))
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


        if (!(obj_getSize(this) >= sizeof(SRCPARSE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


