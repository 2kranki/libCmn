// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SRCERROR Console Transmit Task (SrcError) Header
//****************************************************************
/*
 * Program
 *			Separate SrcError (SrcError)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate SrcError to run things without complications
 *          of interfering with the main SrcError. A SrcError may be 
 *          called a SrcError on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/28/2019 Generated
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
#include        <SrcLoc.h>
#include        <Token.h>


#ifndef         SRCERROR_H
#define         SRCERROR_H


#define   SRCERROR_JSON_SUPPORT 1
//#define   SRCERROR_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SrcError_data_s	SRCERROR_DATA;            // Inherits from OBJ
    typedef struct SrcError_class_data_s SRCERROR_CLASS_DATA;   // Inherits from OBJ

    typedef struct SrcError_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcError_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCERROR_DATA *);
    } SRCERROR_VTBL;

    typedef struct SrcError_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcError_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCERROR_DATA *);
    } SRCERROR_CLASS_VTBL;


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

#ifdef  SRCERROR_SINGLETON
    SRCERROR_DATA * SrcError_Shared (
        void
    );

    bool            SrcError_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SrcError object if successful, otherwise OBJ_NIL.
     */
    SRCERROR_DATA * SrcError_Alloc (
        void
    );
    
    
    OBJ_ID          SrcError_Class (
        void
    );
    
    
    SRCERROR_DATA * SrcError_New (
        void
    );
    
    
   SRCERROR_DATA * SrcError_NewFromData(
       uint16_t        severity,
       const
       SRCLOC          *pLoc,
       const
       char            *pErrorStringA
   );
   
   
   SRCERROR_DATA * SrcError_NewFatalFromToken (
       TOKEN_DATA      *pToken,
       ASTR_DATA       *pErrorString
   );
   
   
   SRCERROR_DATA * SrcError_NewFatalFromTokenA (
       TOKEN_DATA      *pToken,
       const
       char            *pErrorStringA
   );
   
   
   SRCERROR_DATA * SrcError_NewFromJsonString (
       ASTR_DATA       *pString
   );
   
   
   SRCERROR_DATA * SrcError_NewFromJsonStringA (
       const
       char            *pStringA
   );
   

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ASTR_DATA *     SrcError_getErrorStr (
        SRCERROR_DATA   *this
    );


    SRCLOC *        SrcError_getLocation (
        SRCERROR_DATA   *this
    );


    uint16_t        SrcError_getSeverity (
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
     ERESULT eRc = SrcError__Assign(this,pOther);
     @endcode
     @param     this    SRCERROR object pointer
     @param     pOther  a pointer to another SRCERROR object
     @return    If successful, ERESULT_SUCCESS otherwise an
     ERESULT_* error
     */
    ERESULT         SrcError_Assign (
        SRCERROR_DATA   *this,
        SRCERROR_DATA   *pOther
    );
    
    
    ERESULT         SrcError_Compare (
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
    SRCERROR_DATA * SrcError_Copy (
        SRCERROR_DATA   *this
    );
    
    
    SRCERROR_DATA * SrcError_Init (
        SRCERROR_DATA   *this
    );


    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SrcError_ToJSON(this);
     @endcode
     @param     this    SRCERROR object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcError_ToJson (
        SRCERROR_DATA   *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SrcError_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    SrcError_ToDebugString (
        SRCERROR_DATA   *this,
        int             indent
    );
    
    
   ASTR_DATA *     SrcError_ToString (
       SRCERROR_DATA    *this
   );
   

    
#ifdef	__cplusplus
}
#endif

#endif	/* SRCERROR_H */

