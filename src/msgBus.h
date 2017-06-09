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
 *          have previously register with this object. The object
 *          id of the registered objects is used as an indentifier
 *          within the system.
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
        uint16_t        messageSize,
        uint16_t        messageCount        // Max Message Queue size
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         msgBus_getLastError(
        MSGBUS_DATA		*this
    );


    uint32_t        msgBus_getWait(
        MSGBUS_DATA     *this
    );
    
    bool            msgBus_setWait(
        MSGBUS_DATA     *this,
        uint32_t        value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Broadcast a message to all objects registered on the message bus
     except the originator if the originator is identified.
     @param:    this    MSGBUS object pointer
     @param:    pRcvData Ptr to receive routine data area which is used
                        as the routine/data for identification or NULL.
                        If an object id is supplied, that object will
                        not receive the message otherwise all registered
                        objects will receive the message.
     @param:    pRcv    method within pObj that receives the messages
     @return:   If successful, ERESULT_SUCCESS, otherwise and ERESULT_* error.
     */
    ERESULT     msgBus_Broadcast(
        MSGBUS_DATA		*this,
        void            *pRcvData,
        uint8_t         *pMsg
    );
    
    
    ERESULT     msgBus_Disable(
        MSGBUS_DATA		*this
    );


    ERESULT     msgBus_Enable(
        MSGBUS_DATA		*this
    );

   
    MSGBUS_DATA *   msgBus_Init(
        MSGBUS_DATA     *this,
        uint16_t        messageSize,
        uint16_t        messageCount        // Max Message Queue size
    );


    ERESULT     msgBus_IsEnabled(
        MSGBUS_DATA		*this
    );
    
 
    /*!
     Add an object to the message bus giving its method for message reception.
     @param:    this    MSGBUS object pointer
     @param:    pRcvData Ptr to receive routine data area and the key used to
                        identify the routine/data for message transmission
     @param:    pRcv    a routine that will receive the msg as its second parameter
                        and its data ptr as its first parameter
     @return:   If successful, ERESULT_SUCCESS, otherwise and ERESULT_* error.
     */
    ERESULT     msgBus_Register(
        MSGBUS_DATA		*this,
        void            (*pRcv)(void *, void *),
        void            *pRcvData
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
    
    
    /*!
     Remove an object from the message bus.
     @param:    this    MSGBUS object pointer
     @param:    pRcvData Ptr to receive routine data area and the key used to
                        identify the routine/data for message transmission
     @return:   If successful, ERESULT_SUCCESS, otherwise and ERESULT_* error.
     */
    ERESULT     msgBus_UnregisterObject(
        MSGBUS_DATA		*this,
        void            *pRcvData
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MSGBUS_H */

