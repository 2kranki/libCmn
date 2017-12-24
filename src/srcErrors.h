// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SRCERRORS Console Transmit Task (srcErrors) Header
//****************************************************************
/*
 * Program
 *			Separate srcErrors (srcErrors)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate srcErrors to run things without complications
 *          of interfering with the main srcErrors. A srcErrors may be 
 *          called a srcErrors on other O/S's.
 *
 * Remarks
 *	1.      This object can be accessed as a singleton which is
 *          probably preferred.
 *  2.      If OBJ_NIL is passed in the "this" parameter, then
 *          internally srcErrors_Shared() is substituted for
 *          the object pointer.
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
#include        <objEnum.h>
#include        <srcError.h>


#ifndef         SRCERRORS_H
#define         SRCERRORS_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct srcErrors_data_s	SRCERRORS_DATA;    // Inherits from OBJ.

    typedef struct srcErrors_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in srcErrors_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCERRORS_DATA *);
    } SRCERRORS_VTBL;



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
     @return    pointer to srcErrors object if successful, otherwise OBJ_NIL.
     */
    SRCERRORS_DATA *     srcErrors_Alloc(
        void
    );
    
    
    SRCERRORS_DATA *     srcErrors_New(
        void
    );
    
    
    SRCERRORS_DATA *    srcErrors_Shared(
        void
    );
    
    
    bool                srcErrors_SharedReset(
        void
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     The Fatal Error Exit is executed anytime that a fatal error
     is added to the collection. The last error in the collection
     will be the one that triggered the exit being called.
     */
    bool            srcErrors_setFatalExit(
        SRCERRORS_DATA  *this,
        void            (*pFatalExit)(OBJ_ID, SRCERRORS_DATA *),
        OBJ_ID          pFatalExitObject
    );
    
    
    ERESULT     srcErrors_getLastError(
        SRCERRORS_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Create a new fatal error and add it to the internal collection.
     Execute the Fatal Error Exit if available.
     @param     this    SRCERRORS object pointer (if OBJ_NIL,
                        srcErrors_Shared() is used.)
     @param     pLocation Location of first character where error occurred (optional)
     @param     pErrorString  A character string describing the error without
                            the source location
     @return    If successful, true; otherwise, false and an ERESULT_*
     error will be set in Last Error.
     */
    bool        srcErrors_AddFatal(
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
     @param     pToken  Pointer to a token object
     @param     pErrorString  A character string describing the error without
                        the source location
     @return    If successful, true; otherwise, false and an ERESULT_*
                error will be set in Last Error.
     */
    bool        srcErrors_AddFatalFromToken(
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
    OBJENUM_DATA *  srcErrors_EnumErrors(
        SRCERRORS_DATA  *this
    );
    
    
    SRCERRORS_DATA * srcErrors_Init(
        SRCERRORS_DATA  *this
    );


    SRCERROR_DATA * srcErrors_LatestError(
        SRCERRORS_DATA  *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = srcErrors_ToDebugString(this,4);
     @endcode 
     @param     this    SRCERRORS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    srcErrors_ToDebugString(
        SRCERRORS_DATA  *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SRCERRORS_H */
