// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          EXEC Console Transmit Task (exec) Header
//****************************************************************
/*
 * Program
 *			Separate exec (exec)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate exec to run things without complications
 *          of interfering with the main exec. A exec may be 
 *          called a exec on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/10/2018 Generated
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





#include        <md5Util.h>
#include        <AStr.h>
#include        <md5ChkSum.h>


#ifndef         EXEC_H
#define         EXEC_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct exec_data_s	EXEC_DATA;    // Inherits from OBJ.

    typedef struct exec_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in exec_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(EXEC_DATA *);
    } EXEC_VTBL;



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
     @return    pointer to exec object if successful, otherwise OBJ_NIL.
     */
    EXEC_DATA *     exec_Alloc(
        void
    );
    
    
    OBJ_ID          exec_Class(
        void
    );
    
    
    EXEC_DATA *     exec_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint8_t *        exec_getDigest(
        EXEC_DATA       *this
    );
    
    
    ERESULT         exec_getLastError(
        EXEC_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Create an MD5 summary file for a file.
     @param     this    EXEC object pointer
     @param     pPath   pointer to a valid path object for an existing path
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         exec_CreateFileCheckSum(
        EXEC_DATA       *this,
        PATH_DATA       *pPath              // valid file path
    );


    ERESULT     exec_Enable(
        EXEC_DATA		*this
    );

   
    EXEC_DATA *   exec_Init(
        EXEC_DATA     *this
    );


    ERESULT     exec_IsEnabled(
        EXEC_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = exec_ToDebugString(this,4);
     @endcode 
     @param     this    EXEC object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    exec_ToDebugString(
        EXEC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* EXEC_H */

