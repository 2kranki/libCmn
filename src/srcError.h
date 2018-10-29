// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SRCERROR Console Transmit Task (srcError) Header
//****************************************************************
/*
 * Program
 *			Separate srcError (srcError)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate srcError to run things without complications
 *          of interfering with the main srcError. A srcError may be 
 *          called a srcError on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/17/2017 Generated
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





#include        <cmn_defs.h>
#include        <AStr.h>
#include        <srcLoc.h>
#include        <token.h>


#ifndef         SRCERROR_H
#define         SRCERROR_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct srcError_data_s	SRCERROR_DATA;    // Inherits from OBJ.

    typedef struct srcError_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in srcError_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCERROR_DATA *);
    } SRCERROR_VTBL;
    
    typedef enum srcError_Severity {
        SRCERROR_SEVERITY_UNKNOWN = 0,
        SRCERROR_SEVERITY_INFO,
        SRCERROR_SEVERITY_WARNING,
        SRCERROR_SEVERITY_FATAL
    } SRCERROR_SEVERITY;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to srcError object if successful, otherwise OBJ_NIL.
     */
    SRCERROR_DATA * srcError_Alloc(
        void
    );
    
    
    SRCERROR_DATA * srcError_New(
        uint16_t        severity,
        const
        SRCLOC          *pLoc,
        const
        char            *pErrorString
    );
    
    
    SRCERROR_DATA * srcError_NewFatalFromToken(
        TOKEN_DATA      *pToken,
        ASTR_DATA       *pErrorString
    );
    
    
    SRCERROR_DATA * srcError_NewFatalFromTokenA(
        TOKEN_DATA      *pToken,
        const
        char            *pErrorString
    );
    
    
    SRCERROR_DATA * srcError_NewFromJSONString(
        ASTR_DATA       *pString
    );
    
    
    SRCERROR_DATA * srcError_NewFromJSONStringA(
        const
        char            *pString
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ASTR_DATA *     srcError_getErrorStr(
        SRCERROR_DATA   *this
    );
    
    
    SRCLOC *        srcError_getLocation(
        SRCERROR_DATA   *this
    );
    
    
    uint16_t        srcError_getSeverity(
        SRCERROR_DATA   *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
     ERESULT eRc = srcError__Assign(this,pOther);
     @endcode
     @param     this    SRCERROR object pointer
     @param     pOther  a pointer to another SRCERROR object
     @return    If successful, ERESULT_SUCCESS otherwise an
     ERESULT_* error
     */
    ERESULT         srcError_Assign(
        SRCERROR_DATA   *this,
        SRCERROR_DATA   *pOther
    );
    
    
    ERESULT         srcError_Compare(
        SRCERROR_DATA   *this,
        SRCERROR_DATA   *pOther
    );
    
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
     srcError      *pCopy = srcError_Copy(this);
     @endcode
     @param     this    SRCERROR object pointer
     @return    If successful, a SRCERROR object which must be released,
     otherwise OBJ_NIL.
     @warning  Remember to release the returned the SRCERROR object.
     */
    SRCERROR_DATA * srcError_Copy(
        SRCERROR_DATA   *this
    );
    
    
    SRCERROR_DATA * srcError_Init(
        SRCERROR_DATA   *this
    );


    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = srcError_ToJSON(this);
     @endcode
     @param     this    SRCERROR object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     srcError_ToJSON(
        SRCERROR_DATA   *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = srcError_ToDebugString(this,4);
     @endcode 
     @param     this    SRCERROR object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     srcError_ToDebugString(
        SRCERROR_DATA   *this,
        int             indent
    );
    
    
    ASTR_DATA *     srcError_ToString(
        SRCERROR_DATA   *this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SRCERROR_H */

