// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          CLOOPT Console Transmit Task (cloOpt) Header
//****************************************************************
/*
 * Program
 *			Separate cloOpt (cloOpt)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate cloOpt to run things without complications
 *          of interfering with the main cloOpt. A cloOpt may be 
 *          called a cloOpt on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal cloOpt. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	06/05/2017 Generated
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


#ifndef         CLOOPT_H
#define         CLOOPT_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef enum cloOpt_type_e {
        CLOOPT_TYPE_UNKNOWN=0,
        CLOOPT_TYPE_CSV,            // ???
        CLOOPT_TYPE_NUMBER,
        CLOOPT_TYPE_STRING,
        CLOOPT_TYPE_SWITCH,
    } CLOOPT_TYPE;
    

    typedef struct cloOpt_data_s	CLOOPT_DATA;    // Inherits from OBJ.

    typedef struct cloOpt_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in cloOpt_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CLOOPT_DATA *);
    } CLOOPT_VTBL;



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
     @return:   pointer to cloOpt object if successful, otherwise OBJ_NIL.
     */
    CLOOPT_DATA *     cloOpt_Alloc(
        void
    );
    
    
    CLOOPT_DATA *     cloOpt_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     cloOpt_getLastError(
        CLOOPT_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     cloOpt_Disable(
        CLOOPT_DATA		*this
    );


    ERESULT     cloOpt_Enable(
        CLOOPT_DATA		*this
    );

   
    CLOOPT_DATA *   cloOpt_Init(
        CLOOPT_DATA     *this
    );


    ERESULT     cloOpt_IsEnabled(
        CLOOPT_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = cloOpt_ToDebugString(this,4);
     @endcode
     @param     this    CLOOPT object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    cloOpt_ToDebugString(
        CLOOPT_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* CLOOPT_H */

