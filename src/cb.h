// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Circular Buffer (cb) Support  Header
//****************************************************************
/*
 * Program
 *				Circular Buffer (cb) Subroutines
 * Purpose
 *				These subroutines provide a general purpose set of
 *				routines to provide a Circular (FIFO) Buffer of
 *              size elements. The buffer is designed to work in
 *				multi-tasking environment with a single sender and
 *              receiver. It is not safe for multiple senders or
 *              receivers with proper locking.
 *
 *
 * Remarks
 *	1.			XC32 allows 4 register variables per function call.
 *	            So, we will restrict most function calls to 4 or less.
 *  2.          This objects uses flags, OBJ_FLAG_USER1, OBJ_FLAG_USER2
 *              OBJ_FLAG_USER3, and OBJ_FLAG_USER4.
 *
 * History
 *	12/30/2014	Created from cb8.
 *  05/31/2017  Moved to using the psxSem and psxLock classes instead of
 *              having environment specific code.
 *  08/12/2021  Changed to allow buffer to grow dynamically.
 *
 * References
 *      http://en.wikipedia.org/wiki/Circular_buffer
 *		"Data Structures and Algorithms", Alfred V. Aho et al,
 *			Addison-Wesley, 1985
 *		"Data Structures using C", Aaron M. Tenenbaum et al,
 *			Prentice-Hall, 1990
 *		"Programs and Data Structures in C", Leendert Ammeraal,
 *			John Wiley & Sons, 1987
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




#include        <cmn_defs.h>


#ifndef         CB_H
#define         CB_H



#ifdef	__cplusplus
extern "C" {
#endif
    
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

    typedef struct cb_data_s	CB_DATA;

    typedef struct cb_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fatFCB_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CB_DATA *);
    } CB_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    /*!
     Allocate an object.
     @return    If successful, a pointer to the new object,
                otherwise OBJ_NIL.
     */
    CB_DATA *      cb_Alloc (
        void
    );
    
    
    /*!
     Allocate and initialize an object with a circular buffer
     size of 0. To use this object, you will need to run
     Setup().
     @return    If successful, a pointer to the new object,
                otherwise OBJ_NIL.
     */
    CB_DATA *       cb_New (
        void
    );


    /*!
     Allocate one contiguous object large enough for all the entries
     of the Circular Buffer.  Round the element size up to a multiple
     of 4 before calculating object size. The total object size is
     limited to <64k.
     @param     elemSize the size of one element. This must be a
                mutiple of 4.
     @param     size    the number of elements in the Circular Buffer
     @return    If successful, a pointer to the new object,
                otherwise OBJ_NIL.
     */
    CB_DATA *       cb_NewWithSizes (
        uint16_t        elemSize,       // Element Size in bytes
        uint16_t        size,           // Number of Elements in Buffer
        bool            fFixed
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        cb_getElementSize (
        CB_DATA       *this
    );
    

    /*! @property   Buffer Entry Initialization
                    If supplied, each new buffer entry will be passed
                    to this method to be initialized.  This is primarily
                    used for objects in the entry.
     */
    bool            cb_setEntryInit (
        CB_DATA         *this,
        int             (*pEntryInit)(
                                   OBJ_ID,       // pInitEntryObj
                                   OBJ_ID,       // CB_DATA *
                                   void *,       // Entry *
                                   uint16_t      // Entry Size
                        ),
        OBJ_ID          pEntryInitObj
    );


    /*! @property   Buffer Entry Termination
                    If supplied, each new buffer entry will be passed
                    to this method when the buffer is being released.
     */
    bool            cb_setEntryTerm (
        CB_DATA         *this,
        int             (*pEntryTerm)(
                                   OBJ_ID,       // pInitEntryObj
                                   OBJ_ID,       // CB_DATA *
                                   void *,       // Entry *
                                   uint16_t      // Entry Size
                        ),
        OBJ_ID          pEntryTermObj
    );


    /*! @property   Fixed Size Buffer
                    If true, the buffer is fixed in size.  If false,
                    the buffer will be expanded whenever needed. The
                    buffer defaults to fixed.
     */
    bool            cb_getFixed (
        CB_DATA         *this
    );

    bool            cb_setFixed (
        CB_DATA         *this,
        bool            fValue
    );


    /*! @property   Protected Buffer
                    If true, all buffer changes are protected by locks
                    and mutexes. If false (default), no multi-thread
                    protection is provided.
        @warning    This should be set immediately after NewWithSizes()
                    or New() to protect for multi-threaded operation.
     */
    bool            cb_getProtect (
        CB_DATA         *this
    );

    bool            cb_setProtect (
        CB_DATA         *this,
        bool            fValue
    );


    uint16_t        cb_getSize (
        CB_DATA        *this
    );

    


    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Get the current number of element in the buffer.
     @param     this    object pointer
     @return    If successful, the current number of elements in the
                buffer, otherwise -1.
     */
    int32_t        cb_Count (
        CB_DATA         *this
    );
        

    /*!
     Get the next element from the buffer if available within the given time.
     Normally, this method is called from one thread and Put() from a different
     thread.
     @param     this    object pointer
     @param     pValue  ptr to returned element data area
     @return    If successful, true and the element is moved to pValue,
                otherwise false.
     */
    bool            cb_Get (
        CB_DATA         *this,
        void            *pValue         // Copies element into the provided buffer
    );


    bool            cb_isEmpty (
        CB_DATA         *this
    );


    bool            cb_isFull (
        CB_DATA         *this
    );


    // cb_Init() allocates the control blocks for
    // the buffer given the size in uint32_t's.
    // Returns:
    //      cbp  if successful
    //      NULL on failure
    CB_DATA *       cb_Init (
        CB_DATA         *this
    );


    /*!
     Pause the buffer flow releasing any tasks waiting to get/put data.
     This is necessary especially just prior to termination since all
     conditions and mutexes must be in an unlocked state.
     @param     this    CB object pointer
     @return    If successful, true, otherwise false.
     @warning   Pause()/Resume() only work if the buffer is protected.
                See the Protection Property.
     */
    bool            cb_Pause (
        CB_DATA         *this
    );
    
    
    /*!
     Add an element to the end of the buffer if space is available. If space
     is not available, wait until it is.
     Normally, this method is called from one thread and Get() from a different
     thread.
     @param     this    CB object pointer
     @param     pValue  ptr to returned element data area
     @return    If successful, true and the element is moved to pValue,
                otherwise false.
     */
    bool            cb_Put (
        CB_DATA         *this,
        void            *pValue
    );


    /*!
     Resume buffer flow if it was previously paused.
     @param     this    CB object pointer
     @return    If successful, true, otherwise false.
     */
    bool            cb_Resume (
        CB_DATA         *this
    );
    
    
    /*!
     Setup the circular buffer. This is called by NewWithSizes(). You should
     only call this after New() before any other methods are called. This will
     establish the buffer. The buffer will be initialized if the initiablization
     method is provided.
     @param     this    CB object pointer
     @param     elemSize Size of each element within the buffer
     @param     size    Number of elements in the buffer
     @param     fFixed  true == fixed buffer size never to be expanded,
                        false == expand buffer when buffer is full
     @return    If successful, true, otherwise false.
     */
    bool            cb_Setup(
        CB_DATA         *this,
        uint16_t        elemSize,       // Element Size in bytes
        uint16_t        size,           // Number of Elements in Buffer
        bool            fFixed
    );


    ASTR_DATA *     cb_ToDebugString (
        CB_DATA         *this,
        int             indent
    );
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* CB_H */

