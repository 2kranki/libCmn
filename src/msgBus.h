// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Message BUS/Rebroadcaster (msgBus) Header
//****************************************************************
/*
 * Program
 *			Message BUS/Rebroadcaster (msgBus)
 * Purpose
 *			This object simulates a message bus. Other objects
 *          register with it and then send broadcast messages
 *          which are rebroadcast to all the other objects that
 *          have previously register with this object.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	05/31/2017 Generated
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


#ifndef         MSGBUS_H
#define         MSGBUS_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct msgObj_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in msgBus_object.c.
        // Properties:
        // Methods:
        ERESULT         (*pReceive)(OBJ_ID, void *);
        ERESULT         (*pTransmit)(OBJ_ID, void *);
    } MSGOBJ_VTBL;
    
    
    typedef struct msgBus_data_s	MSGBUS_DATA;    // Inherits from OBJ.

    typedef struct msgBus_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in msgBus_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MSGBUS_DATA *);
    } MSGBUS_VTBL;



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
     @return:   pointer to msgBus object if successful, otherwise OBJ_NIL.
     */
    MSGBUS_DATA *     msgBus_Alloc(
    );
    
    
    MSGBUS_DATA *     msgBus_New(
        uint16_t    size                // Message Size
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     msgBus_getLastError(
        MSGBUS_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     msgBus_Broadcast(
        MSGBUS_DATA		*this,
        uint8_t         *pMsg
    );
    
    
    ERESULT     msgBus_Disable(
        MSGBUS_DATA		*this
    );


    ERESULT     msgBus_Enable(
        MSGBUS_DATA		*this
    );

   
    MSGBUS_DATA *   msgBus_Init(
        MSGBUS_DATA     *this
    );


    ERESULT     msgBus_IsEnabled(
        MSGBUS_DATA		*this
    );
    
 
    ERESULT     msgBus_RegisterObject(
        MSGBUS_DATA		*this,
        OBJ_ID          pObj,
        ERESULT         (*pReceive)(OBJ_ID, void *)
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = msgBus_ToDebugString(this,4);
     @endcode:
     @param:    this    MSGBUS object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    msgBus_ToDebugString(
        MSGBUS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MSGBUS_H */
