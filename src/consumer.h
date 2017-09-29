// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//       Consumer Input Message Queue Task (consumer) Header
//****************************************************************
/*
 * Program
 *			Consumer Input Message Queue Task (consumer)
 * Purpose
 *			This object provides a standardized way of handling
 *          messages in a separate task where the messages are
 *          queued from other tasks or interrupts.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	06/29/2016 Generated
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


#ifndef         CONSUMER_H
#define         CONSUMER_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct consumer_data_s	CONSUMER_DATA;    // Inherits from OBJ.

    typedef struct consumer_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in consumer_object.c.
        // Properties:
        // Methods:
    } CONSUMER_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    CONSUMER_DATA *     consumer_Alloc(
        void
    );
    
    
    CONSUMER_DATA *     consumer_New(
        uint16_t        messageSize,
        uint16_t        messageCount,        // Max Message Queue size
        void *          (*pMsgRcvRoutine)(void *, void *),
        void            *pRoutineData
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         consumer_getLastError(
        CONSUMER_DATA   *this
    );
    

    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    bool            consumer_Disable(
        CONSUMER_DATA	*this
    );


    bool            consumer_Enable(
        CONSUMER_DATA	*this
    );

   
    CONSUMER_DATA * consumer_Init(
        CONSUMER_DATA   *this,
        uint16_t        messageSize,
        uint16_t        messageCount,       // Max Message Queue size
        void *          (*pMsgRoutine)(void *, void *),
        void            *pRoutineData
    );


    bool            consumer_IsEnabled(
        CONSUMER_DATA	*this
    );
    
 
    ERESULT         consumer_SendMessage(
        CONSUMER_DATA	*this,
        void            *pMsg
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = consumer_ToDebugString(pObj,4);
     @endcode:
     @param:    this    consumer object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     consumer_ToDebugString(
        CONSUMER_DATA   *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* CONSUMER_H */

