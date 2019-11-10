// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeBase.c
 *	Generated 11/03/2019 08:11:17
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
#include        <NodeBase_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            NodeBase_task_body (
        void            *pData
    )
    {
        //NODEBASE_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    //---------------------------------------------------------------
    //              A c c u m u l a t e  S t r i n g s
    //---------------------------------------------------------------

    /*!
     Given an node array of strings accumulate them into the given
     ASTR array.
     @param     pNodes      Node array object pointer
     @param     pArray      String array object pointer (Where strings are to be accumulated)
     @return    If successful, a ERESULT_SUCCESS, otherwise an ERESULT_* error code.
     */
    ERESULT_DATA *  NodeBase_AccumStrings(
        NODEARRAY_DATA  *pNodes,
        ASTRARRAY_DATA  *pArray
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ERESULT_DATA    *pErr = OBJ_NIL;
        NODE_DATA       *pNode;
        uint32_t        i;
        uint32_t        iMax;
        ASTR_DATA       *pStr;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (OBJ_NIL == pNodes) {
            DEBUG_BREAK();
            pErr = eResult_NewStrA(ERESULT_INVALID_PARAMETER,
                                   "Error: Missing Nodes Pointer!");
            return pErr;
        }
        if (OBJ_NIL == pArray) {
            DEBUG_BREAK();
            pErr = eResult_NewStrA(ERESULT_INVALID_PARAMETER,
                                   "Error: Missing Array Pointer!");
            return pErr;
        }
    #endif

        iMax = nodeArray_getSize(pNodes);
        for (i=0; i<iMax; i++) {
            pNode = nodeArray_Get(pNodes, i+1);
            if (pNode) {
                pStr = jsonIn_CheckNodeForString(pNode);
                if (pStr) {
                    eRc = AStrArray_AppendStr(pArray, pStr, NULL);
                    if (ERESULT_FAILED(eRc)) {
                        pErr = eResult_NewStrA(eRc, NULL);
                        break;
                    }
                }
            }
        }

        // Return to caller.
        return pErr;
    }



    NODEBASE_DATA *     NodeBase_Alloc (
        void
    )
    {
        NODEBASE_DATA       *this;
        uint32_t        cbSize = sizeof(NODEBASE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODEBASE_DATA *     NodeBase_New (
        void
    )
    {
        NODEBASE_DATA       *this;
        
        this = NodeBase_Alloc( );
        if (this) {
            this = NodeBase_Init(this);
        } 
        return this;
    }



    ERESULT_DATA *  NodeBase_Parse (
        NODE_DATA       *pNode,
        NODEBASE_DATA   **ppBase
    )
    {
        ERESULT         eRc;
        ERESULT_DATA    *pErr = OBJ_NIL;
        NODEARRAY_DATA  *pArray;
        NODEHASH_DATA   *pHash;
        NODE_DATA       *pHashItem;
        ASTR_DATA       *pStr;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (OBJ_NIL == pNode) {
            DEBUG_BREAK();
            pErr = eResult_NewStrA(ERESULT_INVALID_PARAMETER, "Error: Missing Node!");
            return pErr;
        }
        if (OBJ_NIL == ppBase) {
            DEBUG_BREAK();
            pErr = eResult_NewStrA(ERESULT_INVALID_PARAMETER,
                                   "Error: Missing Base Node Pointer!");
            return pErr;
        }
        if (OBJ_NIL == *ppBase) {
            DEBUG_BREAK();
            pErr = eResult_NewStrA(ERESULT_INVALID_PARAMETER,
                                   "Error: Missing Base Node Pointer!");
            return pErr;
        }
    #endif

        if (jsonIn_CheckNodeForNull(pNode)) {
            return OBJ_NIL;
        }
        else if (jsonIn_CheckNodeForFalse(pNode)) {
            obj_Release(*ppBase);
            *ppBase = OBJ_NIL;
            return OBJ_NIL;
        }
        else if (jsonIn_CheckNodeForTrue(pNode)) {
            return OBJ_NIL;
        }
        pArray = jsonIn_CheckNodeForArray(pNode);
        if (pArray) {
            // We have an array of Dependencies. So, add them to the base node.
            pErr = NodeBase_AccumStrings(node_getData(pNode), NodeBase_getDeps(*ppBase));
            if (pErr) {
                DEBUG_BREAK();
                return pErr;
            }
            return OBJ_NIL;
        }
        pHash = jsonIn_CheckNodeForHash(pNode);
        if (pHash) {
            // Ok, we have a hash, so there might a lot to parse here.

            pHashItem = nodeHash_FindA(pHash, 0, "arch");
            if (pHashItem) {
                pStr = jsonIn_CheckNodeDataForString(pHashItem);
                if (pStr) {
                   eRc = AStrArray_AppendStr(NodeBase_getArches(*ppBase), pStr, NULL);
                   if (ERESULT_FAILED(eRc)) {
                       return eResult_NewStrA(eRc, NULL);
                   }
                } else {
                   pArray = jsonIn_CheckNodeDataForArray(pHashItem);
                   if (pArray) {
                       pErr = NodeBase_AccumStrings(pArray, NodeBase_getArches(*ppBase));
                       if (pErr) {
                           return pErr;
                       }
                   }
                }
            }

            pHashItem = nodeHash_FindA(pHash, 0, "deps");
            if (pHashItem) {
                pStr = jsonIn_CheckNodeDataForString(pHashItem);
                if (pStr) {
                    eRc = AStrArray_AppendStr(NodeBase_getDeps(*ppBase), pStr, NULL);
                    if (ERESULT_FAILED(eRc)) {
                        return eResult_NewStrA(eRc, NULL);
                    }
                } else {
                    pArray = jsonIn_CheckNodeDataForArray(pHashItem);
                    if (pArray) {
                        pErr = NodeBase_AccumStrings(pArray, NodeBase_getDeps(*ppBase));
                        if (pErr) {
                            return pErr;
                        }
                    }
                }
            }

            pHashItem = nodeHash_FindA(pHash, 0, "srcs");
            if (pHashItem) {
                pStr = jsonIn_CheckNodeDataForString(pHashItem);
                if (pStr) {
                    eRc = AStrArray_AppendStr(NodeBase_getSrcs(*ppBase), pStr, NULL);
                    if (ERESULT_FAILED(eRc)) {
                        return eResult_NewStrA(eRc, NULL);
                    }
                } else {
                    pArray = jsonIn_CheckNodeDataForArray(pHashItem);
                    if (pArray) {
                        pErr = NodeBase_AccumStrings(pArray, NodeBase_getSrcs(*ppBase));
                        if (pErr) {
                            return pErr;
                        }
                    }
                }
            }

            pHashItem = nodeHash_FindA(pHash, 0, "name");
            if (pHashItem) {
                ASTR_DATA       *pStr = jsonIn_CheckNodeForString(node_getData(pHashItem));
                if (pStr) {
                    eRc = NodeBase_setName(*ppBase, pStr);
                    if (ERESULT_FAILED(eRc)) {
                        return eResult_NewStrA(eRc, NULL);
                    }
                }
            }

            pHashItem = nodeHash_FindA(pHash, 0, "suffix");
            if (pHashItem) {
                ASTR_DATA       *pStr = jsonIn_CheckNodeForString(node_getData(pHashItem));
                if (pStr) {
                    eRc = NodeBase_setSuffix(*ppBase, pStr);
                    if (ERESULT_FAILED(eRc)) {
                        return eResult_NewStrA(eRc, NULL);
                    }
                }
            }

            pHashItem = nodeHash_FindA(pHash, 0, "os");
            if (pHashItem) {
                pStr = jsonIn_CheckNodeDataForString(pHashItem);
                if (pStr) {
                    eRc = AStrArray_AppendStr(NodeBase_getOSs(*ppBase), pStr, NULL);
                    if (ERESULT_FAILED(eRc)) {
                        return eResult_NewStrA(eRc, NULL);
                    }
                } else {
                    pArray = jsonIn_CheckNodeDataForArray(pHashItem);
                    if (pArray) {
                        pErr = NodeBase_AccumStrings(pArray, NodeBase_getOSs(*ppBase));
                        if (pErr) {
                            return pErr;
                        }
                    }
                }
            }

        }    // End of Hash Checking

        // Return to caller.
        if (OBJ_NIL == pErr) {
            NodeBase_SortArrays(*ppBase);
        }
        return pErr;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      A r c h e s
    //---------------------------------------------------------------

    ASTRARRAY_DATA *    NodeBase_getArches (
        NODEBASE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArches;
    }
    
    
    bool                NodeBase_setArches (
        NODEBASE_DATA       *this,
        ASTRARRAY_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_REQARCHES_OWNED
        obj_Retain(pValue);
        if (this->pArches) {
            obj_Release(this->pArches);
        }
#endif
        this->pArches = pValue;
        
        return true;
    }
                


    //---------------------------------------------------------------
    //           S o u r c e  D e p e n d e n c i e s
    //---------------------------------------------------------------
    
    ASTRARRAY_DATA *    NodeBase_getDeps (
        NODEBASE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pDeps;
    }
    
    
    bool                NodeBase_setDeps (
        NODEBASE_DATA       *this,
        ASTRARRAY_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_DEPS_OWNED
        obj_Retain(pValue);
        if (this->pDeps) {
            obj_Release(this->pDeps);
        }
#endif
        this->pDeps = pValue;
        
        return true;
    }
        
        
        
    //---------------------------------------------------------------
    //                        N a m e
    //---------------------------------------------------------------
    
    ASTR_DATA *     NodeBase_getName (
        NODEBASE_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pName;
    }
    
    
    bool            NodeBase_setName (
        NODEBASE_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_NAME_OWNED
        obj_Retain(pValue);
        if (this->pName) {
            obj_Release(this->pName);
        }
#endif
        this->pName = pValue;
        
        return true;
    }
        
        
        
    //---------------------------------------------------------------
    //                           N o d e
    //---------------------------------------------------------------
    
    NODE_DATA *     NodeBase_getNode (
        NODEBASE_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return (NODE_DATA *)this;
    }

                
    //---------------------------------------------------------------
    //                          O S
    //---------------------------------------------------------------

    ASTRARRAY_DATA *    NodeBase_getOSs (
        NODEBASE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pOSs;
    }
    
    
    bool                NodeBase_setOSs (
        NODEBASE_DATA       *this,
        ASTRARRAY_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_REQOSS_OWNED
        obj_Retain(pValue);
        if (this->pOSs) {
            obj_Release(this->pOSs);
        }
#endif
        this->pOSs = pValue;
        
        return true;
    }
            
            

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        NodeBase_getPriority (
        NODEBASE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            NodeBase_setPriority (
        NODEBASE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
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
    
    uint32_t        NodeBase_getSize (
        NODEBASE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S o u r c e s
    //---------------------------------------------------------------
    
    ASTRARRAY_DATA *    NodeBase_getSrcs (
        NODEBASE_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pSrcs;
    }
    
    
    bool                NodeBase_setSrcs (
        NODEBASE_DATA       *this,
        ASTRARRAY_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_SRCS_OWNED
        obj_Retain(pValue);
        if (this->pSrcs) {
            obj_Release(this->pSrcs);
        }
#endif
        this->pSrcs = pValue;
        
        return true;
    }
                
    

    //---------------------------------------------------------------
    //                        S u f f i x
    //---------------------------------------------------------------
    
    ASTR_DATA *     NodeBase_getSuffix (
        NODEBASE_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pSuffix;
    }
    
    
    bool            NodeBase_setSuffix (
        NODEBASE_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_NAME_OWNED
        obj_Retain(pValue);
        if (this->pSuffix) {
            obj_Release(this->pSuffix);
        }
#endif
        this->pSuffix = pValue;
        
        return true;
    }
            
            
            
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NodeBase_getSuperVtbl (
        NODEBASE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
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
    //                          A p p e n d
    //---------------------------------------------------------------

    ERESULT_DATA *  NodeBase_AppendArches (
        NODEBASE_DATA   *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
#endif
        
        eRc = AStrArray_AppendStr(this->pArches, pStr, NULL);

        // Return to caller.
        return ERESULT_FAILED(eRc) ? eResult_NewStrA(eRc, NULL) : OBJ_NIL;
    }


    ERESULT_DATA *  NodeBase_AppendDeps (
        NODEBASE_DATA   *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
#endif
        
        eRc = AStrArray_AppendStr(this->pDeps, pStr, NULL);

        // Return to caller.
        return ERESULT_FAILED(eRc) ? eResult_NewStrA(eRc, NULL) : OBJ_NIL;
    }


    ERESULT_DATA *  NodeBase_AppendOSs (
        NODEBASE_DATA   *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
#endif
        
        eRc = AStrArray_AppendStr(this->pOSs, pStr, NULL);

        // Return to caller.
        return ERESULT_FAILED(eRc) ? eResult_NewStrA(eRc, NULL) : OBJ_NIL;
    }


    ERESULT_DATA *  NodeBase_AppendSrcs (
        NODEBASE_DATA   *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
    #endif
        
        eRc = AStrArray_AppendStr(this->pSrcs, pStr, NULL);

        // Return to caller.
        return ERESULT_FAILED(eRc) ? eResult_NewStrA(eRc, NULL) : OBJ_NIL;
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
        ERESULT eRc = NodeBase_Assign(this,pOther);
     @endcode 
     @param     this    NODEBASE object pointer
     @param     pOther  a pointer to another NODEBASE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NodeBase_Assign (
        NODEBASE_DATA   *this,
        NODEBASE_DATA   *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeBase_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        if (pOther->pDeps) {
            obj_Release(pOther->pDeps);
            pOther->pDeps = OBJ_NIL;
        }
        if (pOther->pName) {
            obj_Release(pOther->pName);
            pOther->pName = OBJ_NIL;
        }
        if (pOther->pOSs) {
            obj_Release(pOther->pOSs);
            pOther->pOSs = OBJ_NIL;
        }
        if (pOther->pArches) {
            obj_Release(pOther->pArches);
            pOther->pArches = OBJ_NIL;
        }
        if (pOther->pSrcs) {
            obj_Release(pOther->pSrcs);
            pOther->pSrcs = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pDeps) {
            if (obj_getVtbl(this->pDeps)->pCopy) {
                pOther->pDeps = obj_getVtbl(this->pDeps)->pCopy(this->pDeps);
            }
            else {
                obj_Retain(this->pDeps);
                pOther->pDeps = this->pDeps;
            }
        }
        if (this->pName) {
            if (obj_getVtbl(this->pName)->pCopy) {
                pOther->pName = obj_getVtbl(this->pName)->pCopy(this->pName);
            }
            else {
                obj_Retain(this->pName);
                pOther->pName = this->pName;
            }
        }
        if (this->pOSs) {
            if (obj_getVtbl(this->pOSs)->pCopy) {
                pOther->pOSs = obj_getVtbl(this->pOSs)->pCopy(this->pOSs);
            }
            else {
                obj_Retain(this->pOSs);
                pOther->pOSs = this->pOSs;
            }
        }
        if (this->pArches) {
            if (obj_getVtbl(this->pArches)->pCopy) {
                pOther->pArches = obj_getVtbl(this->pArches)->pCopy(this->pArches);
            }
            else {
                obj_Retain(this->pArches);
                pOther->pArches = this->pArches;
            }
        }
        if (this->pSrcs) {
            if (obj_getVtbl(this->pSrcs)->pCopy) {
                pOther->pSrcs = obj_getVtbl(this->pSrcs)->pCopy(this->pSrcs);
            }
            else {
                obj_Retain(this->pSrcs);
                pOther->pSrcs = this->pSrcs;
            }
        }

        // Copy other data from this object to other.
        
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
    ERESULT         NodeBase_Compare (
        NODEBASE_DATA     *this,
        NODEBASE_DATA     *pOther
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
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeBase_Validate(pOther)) {
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
        NodeBase      *pCopy = NodeBase_Copy(this);
     @endcode 
     @param     this    NODEBASE object pointer
     @return    If successful, a NODEBASE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODEBASE_DATA *     NodeBase_Copy (
        NODEBASE_DATA       *this
    )
    {
        NODEBASE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NodeBase_New( );
        if (pOther) {
            eRc = NodeBase_Assign(this, pOther);
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

    void            NodeBase_Dealloc (
        OBJ_ID          objId
    )
    {
        NODEBASE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODEBASE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        NodeBase_setArches(this, OBJ_NIL);
        NodeBase_setDeps(this, OBJ_NIL);
        NodeBase_setName(this, OBJ_NIL);
        NodeBase_setOSs(this, OBJ_NIL);
        NodeBase_setSrcs(this, OBJ_NIL);
        NodeBase_setSuffix(this, OBJ_NIL);

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
    ERESULT         NodeBase_Disable (
        NODEBASE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeBase_Validate(this)) {
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
    ERESULT         NodeBase_Enable (
        NODEBASE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeBase_Validate(this)) {
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

    NODEBASE_DATA *   NodeBase_Init (
        NODEBASE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODEBASE_DATA);
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

        this = (OBJ_ID)node_Init((NODE_DATA *)this);    // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODEBASE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodeBase_Vtbl);
        
        this->pDeps = AStrArray_New( );
        if (OBJ_NIL == this->pDeps) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pArches = AStrArray_New( );
        if (OBJ_NIL == this->pArches) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pOSs = AStrArray_New( );
        if (OBJ_NIL == this->pOSs) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pSrcs = AStrArray_New( );
        if (OBJ_NIL == this->pSrcs) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "NodeBase::sizeof(NODEBASE_DATA) = %lu\n", sizeof(NODEBASE_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODEBASE_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NodeBase_IsEnabled (
        NODEBASE_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
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
        void        *pMethod = NodeBase_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NodeBase", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NodeBase_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODEBASE_DATA   *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEBASE_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NodeBase_Class();
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
                            return NodeBase_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NodeBase_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NodeBase_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return NodeBase_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NodeBase_ToDebugString)
                    return "ToDebugString";
                if (pData == NodeBase_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                     S o r t  A r r a y s
    //---------------------------------------------------------------
    
    ERESULT_DATA *  NodeBase_SortArrays (
        NODEBASE_DATA   *this
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
#endif
        
        if (this->pDeps) {
            eRc = AStrArray_SortAscending(this->pDeps);
            if (ERESULT_FAILED(eRc)) {
                return eResult_NewStrA(eRc, NULL);
            }
        }
        if (this->pSrcs) {
            eRc = AStrArray_SortAscending(this->pSrcs);
            if (ERESULT_FAILED(eRc)) {
                return eResult_NewStrA(eRc, NULL);
            }
        }

        // Return to caller.
        return OBJ_NIL;
    }
        
        
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     NodeBase_ToJSON (
        NODEBASE_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!NodeBase_Validate(this)) {
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
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
        ASTR_DATA *     NodeBase_ToString (
            NODEBASE_DATA   *this
        )
        {
            ERESULT         eRc;
            //int             j;
            ASTR_DATA       *pStr;
            const
            OBJ_INFO        *pInfo;
            uint32_t        i;
            uint32_t        iMax;
            
            // Do initialization.
    #ifdef NDEBUG
    #else
            if (!NodeBase_Validate(this)) {
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
            
            eRc = AStr_AppendPrint(
                        pStr,
                        "%s:\n",
                        pInfo->pClassName
                );

            if (this->pName) {
                AStr_AppendPrint(pStr, "\tname: %s\n", AStr_getData(this->pName));
            }
            if (this->pSuffix) {
                AStr_AppendPrint(pStr, "\tsuffix: %s\n", AStr_getData(this->pSuffix));
            }
            if (this->pArches) {
                AStr_AppendPrint(pStr, "\tarches[\n");
                iMax = AStrArray_getSize(this->pArches);
                for (i=0; i<iMax; i++) {
                    AStr_AppendPrint(pStr, "\t\t%s\n",
                                     AStr_getData(AStrArray_Get(this->pArches, i+1)));
                }
                AStr_AppendPrint(pStr, "\t]\n");
            }
            if (this->pOSs) {
                AStr_AppendPrint(pStr, "\tOSs[\n");
                iMax = AStrArray_getSize(this->pOSs);
                for (i=0; i<iMax; i++) {
                    AStr_AppendPrint(pStr, "\t\t%s\n",
                                     AStr_getData(AStrArray_Get(this->pOSs, i+1)));
                }
                AStr_AppendPrint(pStr, "\t]\n");
            }
            if (this->pDeps) {
                AStr_AppendPrint(pStr, "\tdeps[\n");
                iMax = AStrArray_getSize(this->pDeps);
                for (i=0; i<iMax; i++) {
                    AStr_AppendPrint(pStr, "\t\t%s\n",
                                     AStr_getData(AStrArray_Get(this->pDeps, i+1)));
                }
                AStr_AppendPrint(pStr, "\t]\n");
            }
            if (this->pSrcs) {
                AStr_AppendPrint(pStr, "\tsrcs[\n");
                iMax = AStrArray_getSize(this->pSrcs);
                for (i=0; i<iMax; i++) {
                    AStr_AppendPrint(pStr, "\t\t%s\n",
                                     AStr_getData(AStrArray_Get(this->pSrcs, i+1)));
                }
                AStr_AppendPrint(pStr, "\t]\n");
            }

            return pStr;
        }
        
        
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeBase_ToDebugString(this,4);
     @endcode 
     @param     this    NODEBASE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeBase_ToDebugString (
        NODEBASE_DATA   *this,
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
        if (!NodeBase_Validate(this)) {
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
                    "{%p(%s)\n",
                    this,
                    pInfo->pClassName
            );

        if (this->pName) {
            if (((OBJ_DATA *)(this->pName))->pVtbl->pToDebugString) {
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent, ' ');
                }
                AStr_AppendA(pStr, "Name:\n");
                pWrkStr =   ((OBJ_DATA *)(this->pName))->pVtbl->pToDebugString(
                                                    this->pName,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        if (this->pSuffix) {
            if (((OBJ_DATA *)(this->pSuffix))->pVtbl->pToDebugString) {
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent, ' ');
                }
                AStr_AppendA(pStr, "Suffix:\n");
                pWrkStr =   ((OBJ_DATA *)(this->pSuffix))->pVtbl->pToDebugString(
                                                    this->pSuffix,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        if (this->pArches) {
            if (((OBJ_DATA *)(this->pArches))->pVtbl->pToDebugString) {
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent, ' ');
                }
                AStr_AppendA(pStr, "Arches:\n");
                pWrkStr =   ((OBJ_DATA *)(this->pArches))->pVtbl->pToDebugString(
                                                    this->pArches,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        if (this->pOSs) {
            if (((OBJ_DATA *)(this->pOSs))->pVtbl->pToDebugString) {
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent, ' ');
                }
                AStr_AppendA(pStr, "OSs:\n");
                pWrkStr =   ((OBJ_DATA *)(this->pOSs))->pVtbl->pToDebugString(
                                                    this->pOSs,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        if (this->pDeps) {
            if (((OBJ_DATA *)(this->pDeps))->pVtbl->pToDebugString) {
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent, ' ');
                }
                AStr_AppendA(pStr, "Dependencies:\n");
                pWrkStr =   ((OBJ_DATA *)(this->pDeps))->pVtbl->pToDebugString(
                                                    this->pDeps,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        if (this->pSrcs) {
            if (((OBJ_DATA *)(this->pSrcs))->pVtbl->pToDebugString) {
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent, ' ');
                }
                AStr_AppendA(pStr, "Source Files:\n");
                pWrkStr =   ((OBJ_DATA *)(this->pSrcs))->pVtbl->pToDebugString(
                                                    this->pSrcs,
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
    bool            NodeBase_Validate (
        NODEBASE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODEBASE))
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


        if (!(obj_getSize(this) >= sizeof(NODEBASE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


