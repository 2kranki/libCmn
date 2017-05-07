// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          CON_FIO Console Transmit Task (con_fio) Header
//****************************************************************
/*
 * Program
 *			Separate con_fio (con_fio)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate con_fio to run things without complications
 *          of interfering with the main con_fio. A con_fio may be 
 *          called a con_fio on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal con_fio. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	10/04/2016 Generated
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
#include        <ascii.h>
#include        <chario.h>


#ifndef         CON_FIO_H
#define         CON_FIO_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct con_fio_data_s	CON_FIO_DATA;    // Inherits from OBJ.

    typedef struct con_fio_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in con_fio_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CON_FIO_DATA *);
    } CON_FIO_VTBL;



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
     @return:   pointer to con_fio object if successful, otherwise OBJ_NIL.
     */
    CON_FIO_DATA *  con_fio_Alloc(
    );
    
    
    CON_FIO_DATA *  con_fio_New(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    CHARIO_DATA *   con_fio_getChario(
        CON_FIO_DATA    *this
    );
    
    
    FILE *          con_fio_getFileIn(
        CON_FIO_DATA    *this
    );
    
    bool            con_fio_setFileIn(
        CON_FIO_DATA    *this,
        FILE            *pValue
    );
    
    
    FILE *          con_fio_getFileOut(
        CON_FIO_DATA    *this
    );
    
    bool            con_fio_setFileOut(
        CON_FIO_DATA    *this,
        FILE            *pValue
    );
    
    
    ERESULT     con_fio_getLastError(
        CON_FIO_DATA	*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    int32_t         con_fio_Getc(
        CON_FIO_DATA	*this
    );
    
    
    CON_FIO_DATA *   con_fio_Init(
        CON_FIO_DATA     *this
    );


    ERESULT          con_fio_Putc(
        CON_FIO_DATA    *this,
        int32_t         value
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = con_fio_ToDebugString(this,4);
     @endcode:
     @param:    this    CON_FIO object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    con_fio_ToDebugString(
        CON_FIO_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* CON_FIO_H */

