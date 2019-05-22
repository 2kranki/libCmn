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
 *          have previously registered with this object.
 *
 *          A receiver object should have a message of the form:
 *              void receiver(OBJ_ID, uint16 len, uint8_t *pMsg);
 *          in its vtbl. A receiver is registered using the OBJ_ID
 *          and the offset of receiver method in the objects vtbl.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	05/31/2017 Generated
 *  10/25/2017 Changed registration to use a unique number instead
 *          an object pointer.
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
#include        <msgData.h>
#include        <objMethod.h>


#ifndef         MSGBUS_H
#define         MSGBUS_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

    typedef
    ERESULT         (*MSGBUS_RECEIVE)(OBJ_ID, MSGDATA_DATA *);

    
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
        void
    );
    
    
    MSGBUS_DATA *     msgBus_New(
        uint16_t        messageCount        // Max Message Queue size
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        msgBus_getRegistrySize(
        MSGBUS_DATA     *this
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
     Broadcast a message to one or all of the objects registered on
     the message bus except the originator if the originator is identified.
     @param     this    MSGBUS object pointer
     @param     origin  Token for originater or 0
     @param     msgDest If 0, all receivers will get the message.
                         Otherwise, it is a token previously returned
                         by the registration process and only that
                         receiver will get the message.
     @param     msglen  length of the message
     @param     pMsg    Pointer to the message
     @return    If successful, ERESULT_SUCCESS, otherwise and ERESULT_* error.
     */
    ERESULT     msgBus_Broadcast(
        MSGBUS_DATA		*this,
        int32_t         origin,
        int32_t         msgDest,
        uint16_t        msglen,
        uint8_t         *pMsg
    );
    
    
    MSGBUS_DATA *   msgBus_Init(
        MSGBUS_DATA     *this,
        uint16_t        messageCount        // Max Message Queue size
    );


    ERESULT         msgBus_RegisterObjectMethod(
        MSGBUS_DATA     *this,
        OBJMETHOD_DATA  *pRcvObj,
        int32_t         *pToken
    );
    
    /*!
     Add an object to the message bus giving its method for message reception.
     @param     this    MSGBUS object pointer
     @param     pRcvObj Pointer to the receive object which must have a method,
                               void receiver(OBJ_ID, uint16 len, uint8_t *pMsg);
                           in its vtbl. A receiver is registered using the OBJ_ID
                           and the offset of receiver method in the objects vtbl.
     @param     pMethodA UTF-8 method name which must be included in the objects's
                         QueryInfo method.
     @param     pToken  an optional token number used to unregister this receiver
                         if needed
     @return    If successful, ERESULT_SUCCESS, otherwise and ERESULT_* error.
     */
    ERESULT     msgBus_RegisterObjectA(
        MSGBUS_DATA		*this,
        OBJ_ID          *pRcvObj,
        char            *pMethodA,
        int32_t         *pToken
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = msgBus_ToDebugString(this,4);
     @endcode
     @param     this    MSGBUS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    msgBus_ToDebugString(
        MSGBUS_DATA     *this,
        int             indent
    );
    
    
    /*!
     Remove an object from the message bus.
     @param     this    MSGBUS object pointer
     @param     token   When the object was registered, this token was returned.
                         it is used to identify which object is to be unregistered.
     @return    If successful, ERESULT_SUCCESS, otherwise and ERESULT_* error.
     */
    ERESULT     msgBus_UnregisterObject(
        MSGBUS_DATA		*this,
        int32_t         token
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MSGBUS_H */

