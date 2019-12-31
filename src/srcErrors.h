// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SRCERRORS Console Transmit Task (SrcErrors) Header
//****************************************************************
/*
 * Program
 *			Separate SrcErrors (SrcErrors)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate SrcErrors to run things without complications
 *          of interfering with the main SrcErrors. A SrcErrors may be 
 *          called a SrcErrors on other O/S's.
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
#include        <ObjEnum.h>
#include        <ObjMethod.h>
#include        <SrcError.h>


#ifndef         SRCERRORS_H
#define         SRCERRORS_H


#define   SRCERRORS_JSON_SUPPORT 1
#define   SRCERRORS_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SrcErrors_data_s	SRCERRORS_DATA;            // Inherits from OBJ
    typedef struct SrcErrors_class_data_s SRCERRORS_CLASS_DATA;   // Inherits from OBJ

    typedef struct SrcErrors_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcErrors_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCERRORS_DATA *);
    } SRCERRORS_VTBL;

    typedef struct SrcErrors_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcErrors_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCERRORS_DATA *);
    } SRCERRORS_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SRCERRORS_SINGLETON
    SRCERRORS_DATA * SrcErrors_Shared (
        void
    );

    void            SrcErrors_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SrcErrors object if successful, otherwise OBJ_NIL.
     */
    SRCERRORS_DATA * SrcErrors_Alloc (
        void
    );
    
    
    OBJ_ID          SrcErrors_Class (
        void
    );
    
    
    SRCERRORS_DATA * SrcErrors_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            SrcErrors_getExitOnFatal (
        SRCERRORS_DATA  *this
    );

    bool            SrcErrors_setExitOnFatal (
        SRCERRORS_DATA  *this,
        bool            value
    );


    /*!
     The Fatal Property is true if any of the errors added were "fatal".
     */
    bool            SrcErrors_getFatal (
        SRCERRORS_DATA  *this                   // OBJ_NIL for Shared instance
    );


    /*!
     The Fatal Error Exit is executed anytime that a fatal error
     is added to the collection. If the exit returns an eresult
     error code then the exit process is terminated and program
     termination is aborted (ie the program will continue to run).
     Otherwise, the program is immediately terminated on any of the
     ERESULT successful completion codes.
     */
    bool            SrcErrors_setFatalExit (
        SRCERRORS_DATA  *this,
        OBJMETHOD_DATA  *pFatalExit
    );


    /*!
     Total number of errors property
     */
    uint32_t        SrcErrors_getNumErrors (
        SRCERRORS_DATA  *this           // OBJ_NIL for Shared instance
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

     /*!
      Create a new fatal error and add it to the internal collection.
      Execute the Fatal Error Exit if available.
      @param     this    SRCERRORS object pointer (if OBJ_NIL,
                         srcErrors_Shared() is used.)
      @param     severity error severity as defined in enum srcError_Severity
      @param     pLocation Location of first character where error occurred (optional)
      @param     pErrorString  A character string describing the error without
                         the source location
      @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_* error code.
      */
     bool        SrcErrors_AddErrorA (
         SRCERRORS_DATA  *this,
         uint16_t        severity,
         const
         SRCLOC          *pLocation,
         const
         char            *pErrorString,
         ...
     );
     
     
     ERESULT         SrcErrors_AddFatal (
         SRCERRORS_DATA  *this,
         SRCERROR_DATA   *pError
     );
     
     
     /*!
      Create a new fatal error and add it to the internal collection.
      Execute the Fatal Error Exit if available.
      @param     this    SRCERRORS object pointer (if OBJ_NIL,
                         srcErrors_Shared() is used.)
      @param     pLocation Location of first character where error occurred (optional)
      @param     pErrorString  A character string describing the error without
                             the source location
      @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_* error code.
      */
     ERESULT         SrcErrors_AddFatalA (
         SRCERRORS_DATA  *this,
         const
         SRCLOC          *pLocation,
         const
         char            *pErrorString,
         ...
     );
     
     
     /*!
      Create a new fatal error and add it to the internal collection.
      Execute the Fatal Error Exit if available.
      @param     this    SRCERRORS object pointer (if OBJ_NIL,
                         srcErrors_Shared() is used.)
      @param     pLocation       Location of first character where error occurred
                                 (optional)
      @param     pErrorString    A character string describing the error without
                                 the source location
      @param     arg_ptr         a va_list pointer
      @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_* error code.
      */
     ERESULT         SrcErrors_AddFatalArgsA (
         SRCERRORS_DATA  *this,
         const
         SRCLOC          *pLocation,
         const
         char            *pErrorString,
         va_list         arg_ptr
     );
     
     
     /*!
      Create a new fatal error and add it to the internal collection.
      Execute the Fatal Error Exit if available.
      @param     this    SRCERRORS object pointer (if OBJ_NIL,
      srcErrors_Shared() is used.)
      @param     pToken  Pointer to a token object
      @param     pExpected  A character string describing the expected tokens
      @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_* error code.
      */
     ERESULT        SrcErrors_AddFatalExpectingA (
         SRCERRORS_DATA  *this,
         TOKEN_DATA      *pToken,
         const
         char            *pExpected
     );
     
     
     /*!
      Create a new fatal error and add it to the internal collection.
      Execute the Fatal Error Exit if available.
      @param     this    SRCERRORS object pointer (if OBJ_NIL,
                         srcErrors_Shared() is used.)
      @param     pToken  Pointer to a token object
      @param     pErrorString  A character string describing the error without
                         the source location
      @return    If successful, true; otherwise, false and an ERESULT_*
                 error will be set in Last Error.
      */
     ERESULT        SrcErrors_AddFatalFromTokenA (
         SRCERRORS_DATA  *this,
         TOKEN_DATA      *pToken,
         const
         char            *pErrorString,
         ...
     );
     
    
     /*!
      Create an enumeration of all the errors in the collection.
      Example:
      @code
      OBJENUM_DATA   *pEnum = OBJ_NIL;
      ASTR_DATA      *pDesc = srcErrors_EnumErrors(this, &pEnum);
      @endcode
      @param     this    SZTBL_DATA object pointer
      @return    If successful, an Enum Object of all the errors.
                 Otherwise, OBJ_NIL and an ERESULT_* error code
                 in Last Error.
      @warning   Remember to release the returned Enumeration object.
      */
     OBJENUM_DATA * SrcErrors_EnumErrors (
         SRCERRORS_DATA  *this
     );
     
     
     /*!
      If a fatal error has occurred, print all errors to stderr,
      execute the fatal error exit if present, then exit with
      the given error code.  If no fatal errors occurred, simply
      return without any impact.
      @param     this        object pointer or OBJ_NIL for Shared instance
      */
     void           SrcErrors_ExitOnFatal(
         SRCERRORS_DATA  *this
     );
     
     
    SRCERRORS_DATA * SrcErrors_Init (
        SRCERRORS_DATA  *this
    );


    SRCERROR_DATA * SrcErrors_LatestError (
        SRCERRORS_DATA  *this
    );
    
    
    /*!
     Print all errors on stderr.
     @param     this        object pointer or OBJ_NIL for Shared instance
     */
    void            SrcErrors_Print (
        SRCERRORS_DATA  *this,
        FILE            *pFile
    );
    
    
    /*!
     Clear all errors and error status.
     @param     this        object pointer or OBJ_NIL for Shared instance
     */
    void            SrcErrors_Reset (
        SRCERRORS_DATA  *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SrcErrors_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    SrcErrors_ToDebugString (
        SRCERRORS_DATA  *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SRCERRORS_H */

