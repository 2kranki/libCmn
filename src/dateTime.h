// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          DATETIME Console Transmit Task (DateTime) Header
//****************************************************************
/*
 * Program
 *			Separate dateTime (dateTime)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate DateTime to run things without complications
 *          of interfering with the main DateTime. A DateTime may be 
 *          called a DateTime on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	08/25/2016 Generated
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


#ifndef         DATETIME_H
#define         DATETIME_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct dateTime_data_s	DATETIME_DATA;    // Inherits from OBJ.

    typedef struct dateTime_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in DateTime_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DATETIME_DATA *);
    } DATETIME_VTBL;



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
     @return:   pointer to DateTime object if successful, otherwise OBJ_NIL.
     */
    DATETIME_DATA *     dateTime_Alloc(
    );
    
    
    DATETIME_DATA *     dateTime_New(
    );
    
    
    DATETIME_DATA *     dateTime_NewCurrent(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    int16_t         dateTime_getDay(
        DATETIME_DATA	*this
    );
    
    bool            dateTime_setDay(
        DATETIME_DATA	*this,
        int16_t         pValue
    );
    
    
    int16_t         dateTime_getMonth(
        DATETIME_DATA	*this
    );
    
    bool            dateTime_setMonth(
        DATETIME_DATA	*this,
        int16_t         pValue
    );
    
    
    int16_t         dateTime_getYear(
        DATETIME_DATA	*this
    );
    
    bool            dateTime_setYear(
        DATETIME_DATA	*this,
        int16_t         pValue
    );
    
    
    int16_t         dateTime_getHours(
        DATETIME_DATA	*this
    );
    
    bool            dateTime_setHours(
        DATETIME_DATA	*this,
        int16_t         pValue
    );
    
    
    int16_t         dateTime_getMins(
        DATETIME_DATA	*this
    );
    
    bool            dateTime_setMins(
        DATETIME_DATA	*this,
        int16_t         pValue
    );
    
    
    int16_t         dateTime_getSecs(
        DATETIME_DATA	*this
    );
    
    bool            dateTime_setSecs(
        DATETIME_DATA	*this,
        int16_t         pValue
    );
    
    
    int16_t         dateTime_getMilli(
        DATETIME_DATA	*this
    );
    
    bool            dateTime_setMilli(
        DATETIME_DATA	*this,
        int16_t         pValue
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         dateTime_Assign(
        DATETIME_DATA	*this,
        DATETIME_DATA   *pOther
    );
    
    
    DATETIME_DATA * dateTime_Copy(
        DATETIME_DATA   *this
    );
    
    
    DATETIME_DATA * dateTime_Init(
        DATETIME_DATA   *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = &P__ToDebugString(pObj,4);
     @endcode:
     @param:    this    DateTime object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    dateTime_ToDebugString(
        DATETIME_DATA   *this,
        int             indent
    );
    
    /*!
     Create a string that has the date formatted as MM/DD/YYYY HH:MM:SS.III.
     Example:
     @code:
     ASTR_DATA      *pDesc = dateTime_ToDebugString(pObj,4);
     @endcode:
     @param:    this    DateTime object pointer
     @return:   If successful, an AStr object which must be released containing the
                string, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    dateTime_ToString(
        DATETIME_DATA   *this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DATETIME_H */

