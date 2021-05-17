// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Consumer_internal.h
 *  Generated 05/04/2021 09:30:56
 *
 * Notes:
 *  --  N/A
 *
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




#include        <Consumer.h>
#include        <JsonIn.h>
#include        <ObjCb.h>
#include        <psxMutex.h>
#include        <psxSem.h>
#include        <psxThread.h>


#ifndef CONSUMER_INTERNAL_H
#define CONSUMER_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Consumer_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;
    ASTR_DATA       *pStr;
    OBJCB_DATA      *pQueue;
    PSXTHREAD_DATA  *pThread;
    OBJ_ID          pOther;

    // Flags
    volatile
    uint8_t         fQuit;
    volatile
    uint8_t         fRunning;
    volatile
    uint8_t         fSkip;              // Stop processing messages
    uint8_t         reserved;
    volatile
    uint32_t        msWaitTime;

    // Support Routines
    void            (*pTaskBody)(OBJ_ID);
    OBJ_ID          pTaskObj;
    void            (*pTimedOut)(OBJ_ID);
    OBJ_ID          pTimedOutObj;
    int             (*pService)(OBJ_ID, OBJ_ID);
    void            *pServiceObj;       // 1st parameter for service routine

    uint32_t        numHandled;         // Number of messages handled
    uint32_t        numDiscard;         // Number of messages that could not be written
    //                                  // into the queue or handled
    uint32_t        numWritten;         // Number of messages written into the queue
};
#pragma pack(pop)

    extern
    struct Consumer_class_data_s  Consumer_ClassObj;

    extern
    const
    CONSUMER_VTBL         Consumer_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  CONSUMER_SINGLETON
    CONSUMER_DATA * Consumer_getSingleton (
        void
    );

    bool            Consumer_setSingleton (
     CONSUMER_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Consumer_getSuperVtbl (
        CONSUMER_DATA     *this
    );


    ERESULT         Consumer_Assign (
        CONSUMER_DATA    *this,
        CONSUMER_DATA    *pOther
    );


    CONSUMER_DATA * Consumer_Copy (
        CONSUMER_DATA     *this
    );


    void            Consumer_Dealloc (
        OBJ_ID          objId
    );


#ifdef  CONSUMER_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    CONSUMER_DATA * Consumer_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Consumer_ParseJsonFields (
        JSONIN_DATA     *pParser,
        CONSUMER_DATA   *pObject
    );
#endif


    void *          Consumer_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    /*!
     Send an object to the consumer FIFO's queue. Normally, this
     would only be used by the Producer object. If fWait is true,
     this will block until there is an empty slot in the queue
     for the data object. If fWait is false, ERESULT_BUFFER_FULL
     is returned and the object is not added to the queue.
     @param     this    object pointer
     @param     pObj    data object pointer to be added to queue
     @param     fWait   Wait for queue to have an empty slot
     @return    If successful, ERESULT_SUCCESS. Otherwise,
                an ERESULT_* error code.
     */
    ERESULT         Consumer_Send (
        CONSUMER_DATA   *this,
        OBJ_ID          pObj,
        bool            fWait           // true == Wait for queue to have an empty slot
    );


#ifdef  CONSUMER_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Consumer_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Consumer_ToJson (
        CONSUMER_DATA      *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Consumer_ToJsonFields (
        CONSUMER_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            Consumer_Validate (
        CONSUMER_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* CONSUMER_INTERNAL_H */

