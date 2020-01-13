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
 *
 * History
 *	12/30/2014	Created from cb8.
 *  05/31/2017  Moved to using the psxSem and psxLock classes instead of
 *              having environment specific code.
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
 * TODO
 *  --          Implement iGet/iPut where they are executed in a non-
 *              interruptable state and at a higher priority than normal
 *              processing.
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
    CB_DATA *      cb_Alloc(
        uint16_t        elemSize,       // Element Size in bytes (multiple of 4)
        uint16_t        size            // Number of Elements in Buffer
    );
    
    
    CB_DATA *       cb_New(
        uint16_t        elemSize,       // Element Size in bytes
        uint16_t        size            // Number of Elements in Buffer
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        cb_getElementSize(
        CB_DATA       *this
    );
    
    
    uint16_t        cb_getSize(
        CB_DATA        *this
    );

    


    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    uint16_t        cb_Count(
        CB_DATA         *this
    );
        

    /*!
     Get the next element from the buffer if available within the given time.
     Normally, this method is called from one thread and Put() from a different
     thread.
     @param     this    CB object pointer
     @param     pValue  ptr to returned element data area
     @return    If successful, true and the element is moved to pValue,
                otherwise false.
     */
    bool            cb_Get(
        CB_DATA         *this,
        void            *pValue         // Copies element into the provided buffer
    );


    bool            cb_isEmpty(
        CB_DATA         *this
    );


    bool            cb_isFull(
        CB_DATA         *this
    );


    // cb_Init() allocates the control blocks for
    // the buffer given the size in uint32_t's.
    // Returns:
    //      cbp  if successful
    //      NULL on failure
    CB_DATA *       cb_Init(
        CB_DATA         *this
    );


    /*!
     Pause the buffer flow releasing any tasks waiting to get/put data.
     This is necessary especially just prior to termination since all
     conditions and mutexes must be in an unlocked state.
     */
    bool            cb_Pause(
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
    bool            cb_Put(
        CB_DATA         *this,
        void            *pValue
    );


    bool            cb_Resume(
        CB_DATA         *this
    );
    
    
    ASTR_DATA *     cb_ToDebugString(
        CB_DATA         *this,
        int             indent
    );
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* CB_H */

