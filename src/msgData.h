// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          MSGDATA Console Transmit Task (msgData) Header
//****************************************************************
/*
 * Program
 *			Separate msgData (msgData)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate msgData to run things without complications
 *          of interfering with the main msgData. A msgData may be 
 *          called a msgData on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/04/2017 Generated
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


#ifndef         MSGDATA_H
#define         MSGDATA_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct msgData_data_s	MSGDATA_DATA;    // Inherits from OBJ.

    typedef struct msgData_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in msgData_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MSGDATA_DATA *);
    } MSGDATA_VTBL;



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
     @return    pointer to msgData object if successful, otherwise OBJ_NIL.
     */
    MSGDATA_DATA *  msgData_Alloc(
        uint16_t        dataSize        // Size of Data
    );
    
    
    MSGDATA_DATA *  msgData_New(
        uint32_t        origin,
        uint32_t        dest,
        uint16_t        size,
        void            *pData
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    void *          msgData_getData(
        MSGDATA_DATA    *this
    );
    
    
    uint32_t        msgData_getDestination(
        MSGDATA_DATA    *this
    );
    
    
    ERESULT         msgData_getLastError(
        MSGDATA_DATA	*this
    );


    uint32_t        msgData_getNum32(
        MSGDATA_DATA    *this
    );
    
    bool            msgData_setNum32(
        MSGDATA_DATA    *this,
        uint32_t        value
    );
    

    uint32_t        msgData_getOrigin(
        MSGDATA_DATA     *this
    );
    
    
    uint16_t        msgData_getSize(
        MSGDATA_DATA    *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Copy the current object creating a new object.
     Example:
     @code
     msgData      *pCopy = msgData_Copy(this);
     @endcode
     @param     this    MSGDATA object pointer
     @return    If successful, a MSGDATA object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the MSGDATA object.
     */
    MSGDATA_DATA *  msgData_Copy(
        MSGDATA_DATA    *this
    );
    
    
    MSGDATA_DATA *  msgData_Init(
        MSGDATA_DATA    *this,
        uint32_t        origin,
        uint32_t        dest,
        uint16_t        size,
        void            *pData
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = msgData_ToDebugString(this,4);
     @endcode 
     @param     this    MSGDATA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    msgData_ToDebugString(
        MSGDATA_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MSGDATA_H */

