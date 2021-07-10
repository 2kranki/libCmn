// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NetHTTPR.c
 *  Generated 07/07/2021 09:54:54
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
#include        <NetHTTPR_internal.h>
#include        <ascii.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    
    typedef struct cmd_s {
        const
        char        *pNameA;
        int         cmd;
    } CMD;

    // Table must be sorted by Name.
    static
    const
    CMD             pCmds[] = {
        {"CONNECT", NETHTTPR_CMD_CONNECT},
        {"DELETE",  NETHTTPR_CMD_DELETE},
        {"GET",     NETHTTPR_CMD_GET},
        {"HEAD",    NETHTTPR_CMD_HEAD},
        {"OPTIONS", NETHTTPR_CMD_OPTIONS},
        {"POST",    NETHTTPR_CMD_POST},
        {"PUT",     NETHTTPR_CMD_PUT},
        {"TRACE",   NETHTTPR_CMD_TRACE},
        {"UNKNOWN", NETHTTPR_CMD_UNKNOWN},
    };

    static
    const
    int             cCmds = sizeof(pCmds) / sizeof(CMD);



 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    int             NetHTTPR_CmdToInternal (
        const
        char            *pData
    )
    {
        int             i;
        int             iRc = NETHTTPR_CMD_UNKNOWN;

        for (i=0; i<cCmds; i++) {
            if (0 == strcmp(pData, pCmds[i].pNameA))
                iRc = pCmds[i].cmd;
        }

        return iRc;
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NETHTTPR_DATA *     NetHTTPR_Alloc (
        void
    )
    {
        NETHTTPR_DATA       *this;
        uint32_t        cbSize = sizeof(NETHTTPR_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NETHTTPR_DATA *     NetHTTPR_New (
        void
    )
    {
        NETHTTPR_DATA       *this;
        
        this = NetHTTPR_Alloc( );
        if (this) {
            this = NetHTTPR_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          B o d y
    //---------------------------------------------------------------

    ASTR_DATA *     NetHTTPR_getBody (
        NETHTTPR_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pBody;
    }


    bool            NetHTTPR_setBody (
        NETHTTPR_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pBody) {
            obj_Release(this->pBody);
        }
        this->pBody = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                 M a j o r  R e l e a s e
    //---------------------------------------------------------------

    uint16_t        NetHTTPR_getMajorRelease (
        NETHTTPR_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->majRel;
    }


    bool            NetHTTPR_setMajorRelease (
        NETHTTPR_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->majRel = value;

        return true;
    }



    //---------------------------------------------------------------
    //                 M i n o r  R e l e a s e
    //---------------------------------------------------------------

    uint16_t        NetHTTPR_getMinorRelease (
        NETHTTPR_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->minRel;
    }


    bool            NetHTTPR_setMinorRelease (
        NETHTTPR_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->minRel = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        NetHTTPR_getPriority (
        NETHTTPR_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            NetHTTPR_setPriority (
        NETHTTPR_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
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
    
    uint32_t        NetHTTPR_getSize (
        NETHTTPR_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NetHTTPR_getSuperVtbl (
        NETHTTPR_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          U R I
    //---------------------------------------------------------------

    ASTR_DATA *     NetHTTPR_getURI (
        NETHTTPR_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pURI;
    }


    bool            NetHTTPR_setURI (
        NETHTTPR_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pURI) {
            obj_Release(this->pURI);
        }
        this->pURI = pValue;

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
        ERESULT eRc = NetHTTPR_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NETHTTPR object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NetHTTPR_Assign (
        NETHTTPR_DATA       *this,
        NETHTTPR_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NetHTTPR_Validate(pOther)) {
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
        //pOther->x     = this->x; 

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
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             NetHTTPR_Compare (
        NETHTTPR_DATA     *this,
        NETHTTPR_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!NetHTTPR_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        NetHTTPR      *pCopy = NetHTTPR_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NETHTTPR object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NETHTTPR_DATA *     NetHTTPR_Copy (
        NETHTTPR_DATA       *this
    )
    {
        NETHTTPR_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef NETHTTPR_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = NetHTTPR_New( );
        if (pOther) {
            eRc = NetHTTPR_Assign(this, pOther);
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

    void            NetHTTPR_Dealloc (
        OBJ_ID          objId
    )
    {
        NETHTTPR_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NETHTTPR_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        NetHTTPR_setBody(this, OBJ_NIL);
        NetHTTPR_setURI(this, OBJ_NIL);

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
        NetHTTPR      *pDeepCopy = NetHTTPR_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NETHTTPR object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NETHTTPR_DATA *     NetHTTPR_DeepyCopy (
        NETHTTPR_DATA       *this
    )
    {
        NETHTTPR_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NetHTTPR_New( );
        if (pOther) {
            eRc = NetHTTPR_Assign(this, pOther);
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
    ERESULT         NetHTTPR_Disable (
        NETHTTPR_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return eRc;
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
    ERESULT         NetHTTPR_Enable (
        NETHTTPR_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NETHTTPR_DATA * NetHTTPR_Init (
        NETHTTPR_DATA   *this
    )
    {
        uint32_t        cbSize = sizeof(NETHTTPR_DATA);
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of NetHTTPR_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NETHTTPR);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NetHTTPR_Vtbl);
#ifdef  NETHTTPR_JSON_SUPPORT
        JsonIn_RegisterClass(NetHTTPR_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "NetHTTPR::sizeof(NETHTTPR_DATA) = %lu\n", 
                sizeof(NETHTTPR_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NETHTTPR_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NetHTTPR_IsEnabled (
        NETHTTPR_DATA   *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
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
    //                      P a r s e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NetHTTPR_Parse (
        NETHTTPR_DATA   *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pLine = OBJ_NIL;
        ASTRARRAY_DATA  *pLines = OBJ_NIL;
        ASTR_DATA       *pField = OBJ_NIL;
        ASTRARRAY_DATA  *pFields = OBJ_NIL;
        static
        const
        W32CHR_T        eols[3] = {
            '\n',
            '\r',
            0
        };
        static
        const
        W32CHR_T        spaces[2] = {
            ' ',
            0
        };
        int             i;
        int             iMax;
        int             numMaj;
        int             numMin;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        // Break the buffer up into trimmed lines.
        pLines = AStr_SplitOnCharW32(pStr, '\n');
        if (OBJ_NIL == pLines) {
            return ERESULT_GENERAL_FAILURE;
        }
        iMax = AStrArray_getSize(pLines);
        for (i=0; i<iMax; i++) {
            pLine = AStrArray_Get(pLines, i+1);
            if (pLine) {
                AStr_Trim(pLine);
            }
        }
        pLine = OBJ_NIL;

        // Scan the first line.
        pLine = AStrArray_Get(pLines, 1);
        TRC_OBJ(this,"\tFirst Line: \"%s\"\n", AStr_getData(pLine));
        if (pLine) {
            pFields = AStr_SplitOnCharW32(pLine, ' ');
            iMax = AStrArray_getSize(pFields);
            if (3 == iMax)
                ;
            else {
#ifdef NDEBUG
#else
                TRC_OBJ(this,"\tDid not find 3 fields on First Line, only %d!\n", iMax);
                for (i=0; i<iMax; i++) {
                    TRC_OBJ(this,"\t%d: \"%s\"\n", i, AStr_getData(AStrArray_Get(pFields, i+1)));
                }
#endif
                obj_Release(pFields);
                pFields = OBJ_NIL;
                obj_Release(pLines);
                pLines = OBJ_NIL;
                return ERESULT_INVALID_SYNTAX;
            }

            // Field 1 == Command
            pField = AStrArray_Get(pFields, 1);
            TRC_OBJ(this,"\tField 1: \"%s\"\n", AStr_getData(pField));
            i = NetHTTPR_CmdToInternal(AStr_getData(pField));
            if (NETHTTPR_CMD_UNKNOWN == i) {
                TRC_OBJ(this,"\tUnknown Command!\n");
                obj_Release(pFields);
                pFields = OBJ_NIL;
                obj_Release(pLines);
                pLines = OBJ_NIL;
                return ERESULT_INVALID_SYNTAX;
            }
            this->cmd = i;

            // Field 2 == URI
            pField = AStrArray_Get(pFields, 2);
            if (pField) {
                TRC_OBJ(this,"\tField 2 (URI): \"%s\"\n", AStr_getData(pField));
                obj_Retain(pField);
                this->pURI = pField;
            }

            // Field 3 == HTTPn.n
            pField = AStrArray_Get(pFields, 3);
            if (pField) {
                TRC_OBJ(this,"\tField 3: \"%s\"\n", AStr_getData(pField));
                i = AStr_CompareLeftA(pField, "HTTP/");
                if (0 == i) {
                    i = 6;
                    iMax = AStr_getSize(pField);
                    numMaj = 0;
                    while ((i <= iMax) && ascii_isNumericW32(AStr_CharGetW32(pField, i))) {
                        numMaj *= 10;
                        numMaj += AStr_CharGetW32(pField, i) - '0';
                        i++;
                    }
                    if ('.' == AStr_CharGetW32(pField, i))
                        i++;
                    else {
                        TRC_OBJ(this, "\tInvalid char, need '.', found %c!\n",
                                        AStr_CharGetW32(pField, i));
                        obj_Release(pFields);
                        pFields = OBJ_NIL;
                        obj_Release(pLines);
                        pLines = OBJ_NIL;
                        return ERESULT_INVALID_SYNTAX;
                    }
                    numMin = 0;
                    while ((i <= iMax) && ascii_isNumericW32(AStr_CharGetW32(pField, i))) {
                        numMin *= 10;
                        numMin += AStr_CharGetW32(pField, i) - '0';
                        i++;
                    }
                    TRC_OBJ(this, "\tFound Maj.Min: %d.%d\n", numMaj, numMin);
                    this->majRel = numMaj;
                    this->minRel = numMin;
                } else {
                    TRC_OBJ(this, "\tMissing \"HTTP/\"!\n");
                    obj_Release(pFields);
                    pFields = OBJ_NIL;
                    obj_Release(pLines);
                    pLines = OBJ_NIL;
                    return ERESULT_INVALID_SYNTAX;
                }
            }

            obj_Release(pFields);
            pFields = OBJ_NIL;
        }

        obj_Release(pLines);
        pLines = OBJ_NIL;

        // Return to caller.
        return eRc;
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
        void        *pMethod = NetHTTPR_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NetHTTPR", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NetHTTPR_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NETHTTPR_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NetHTTPR_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(NETHTTPR_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NetHTTPR_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return NetHTTPR_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NetHTTPR_Enable;
                        }
                        break;

                    case 'P':
#ifdef  NETHTTPR_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return NetHTTPR_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return NetHTTPR_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NetHTTPR_ToDebugString;
                        }
#ifdef  NETHTTPR_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return NetHTTPR_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return NetHTTPR_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NetHTTPR_ToDebugString)
                    return "ToDebugString";
#ifdef  NETHTTPR_JSON_SUPPORT
                if (pData == NetHTTPR_ToJson)
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
        ASTR_DATA      *pDesc = NetHTTPR_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NetHTTPR_ToDebugString (
        NETHTTPR_DATA   *this,
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
        if (!NetHTTPR_Validate(this)) {
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
                    NetHTTPR_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
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
    bool            NetHTTPR_Validate (
        NETHTTPR_DATA   *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NETHTTPR))
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


        if (!(obj_getSize(this) >= sizeof(NETHTTPR_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


