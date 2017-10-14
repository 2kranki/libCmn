// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   dirEntry.c
 *	Generated 06/23/2015 20:03:11
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

#ifdef __APPLE__
#   define _DARWIN_FEATURE_64_BIT_INODE /**/
#endif


/* Header File Inclusion */
#include    <dirEntry_internal.h>
#include    <misc.h>



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

    DIRENTRY_DATA *     dirEntry_Alloc(
    )
    {
        DIRENTRY_DATA   *cbp;
        uint32_t        cbSize = sizeof(DIRENTRY_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    DIRENTRY_DATA * dirEntry_NewA(
        PATH_DATA       *pDir,
        const
        char            *pNameStr,
        uint8_t         type
    )
    {
        DIRENTRY_DATA   *cbp;
        ASTR_DATA       *pName;
        
        pName = AStr_NewA(pNameStr);
        if (OBJ_NIL == pName) {
            return OBJ_NIL;
        }
        
        cbp = dirEntry_Alloc();
        cbp = dirEntry_Init(cbp);
        if (OBJ_NIL == cbp) {
            return cbp;
        }
        
        (void)dirEntry_setDir(cbp, pDir);
        (void)dirEntry_setName(cbp, pName);
        (void)dirEntry_setType(cbp, type);

        obj_Release(pName);
        pName = OBJ_NIL;
        
        // Return to caller.
        return( cbp );
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    PATH_DATA *     dirEntry_getDir(
        DIRENTRY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pDir;
    }
    
    bool            dirEntry_setDir(
        DIRENTRY_DATA   *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pDir) {
            obj_Release(this->pDir);
        }
        this->pDir = pValue;
        
        return true;
    }
    
    
    
    ASTR_DATA *     dirEntry_getName(
        DIRENTRY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pName;
    }
    
    bool            dirEntry_setName(
        DIRENTRY_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pName) {
            obj_Release(this->pName);
        }
        this->pName = pValue;
        
        return true;
    }
    
    
    
    uint8_t         dirEntry_getType(
        DIRENTRY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->type;
    }

    bool            dirEntry_setType(
        DIRENTRY_DATA   *this,
        uint8_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->type = value;
        return true;
    }



    uint32_t        dirEntry_getSize(
        DIRENTRY_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return( 0 );
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            dirEntry_Dealloc(
        OBJ_ID          objId
    )
    {
        DIRENTRY_DATA   *this = objId;

        // Do initialization.
        if (OBJ_NIL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        (void)dirEntry_setDir(this, OBJ_NIL);
        (void)dirEntry_setName(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    DIRENTRY_DATA *   dirEntry_Init(
        DIRENTRY_DATA       *this
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_DIRENTRY );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&dirEntry_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);

    #ifdef NDEBUG
    #else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          M a t c h
    //---------------------------------------------------------------
    
    ERESULT         dirEntry_MatchA(
        DIRENTRY_DATA   *this,
        const
        char            *pPattern
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc =   AStr_MatchA(this->pName, pPattern);
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          dirEntry_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    )
    {
        DIRENTRY_DATA   *this = objId;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
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
                            return dirEntry_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pStr);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = dirEntry_ToDebugString(this, 4);
     @endcode:
     @param:    this    DIRENTRY object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     dirEntry_ToDebugString(
        DIRENTRY_DATA   *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY
        ASTR_DATA       *pWrkStr;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dirEntry_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(dirEntry)\n",
                     this
                     );
        AStr_AppendA(pStr, str);
        
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
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(dirEntry)}\n", this);
        AStr_AppendA(pStr, str);
        
        //dirEntry_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            dirEntry_Validate(
        DIRENTRY_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_DIRENTRY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(DIRENTRY_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


