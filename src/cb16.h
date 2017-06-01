// vi:nu:et:sts=4 ts=4 sw=4
//****************************************************************
//  PIC32 Circular Buffer 16-Bit Elements (cb16) Support  Header
//****************************************************************
/*
 * Program
 *				PIC32 Circular Buffer 16-Bit Elements (cb16) Subroutines
 * Purpose
 *				These subroutines provide a general purpose set of
 *				routines to provide a Circular (FIFO) Buffer of
 *              uint32_t elements. The buffer is designed to work in
 *				multi-tasking environment with a single sender and
 *              receiver. It is not safe for multiple senders or
 *              receivers.
 *
 *
 * Remarks
 *	1.			XC32 allows 4 register variables per function call.
 *	            So, we will restrict most function calls to 4 or less.
 *
 * History
 *	10/05/2014	Created from scratch.
 * References
 *      http://en.wikipedia.org/wiki/Circular_buffer
 *		"Data Structures and Algorithms", Alfred V. Aho et al,
 *			Addison-Wesley, 1985
 *		"Data Structures using C", Aaron M. Tenenbaum et al,
 *			Prentice-Hall, 1990
 *		"Programs and Data Structures in C", Leendert Ammeraal,
 *			John Wiley & Sons, 1987
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


#ifndef         CB16_H
#define         CB16_H



#ifdef	__cplusplus
extern "C" {
#endif
    


    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

    typedef struct cb16_data_s	CB16_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    /* Alloc() allocates an area large enough for 'size' entries.
     * The same size should be passed to Init() without change.
     */
    CB16_DATA *      cb16_Alloc(
        uint16_t        size            // Number of Elements in Buffer
    );
    
    
    CB16_DATA *      cb16_New(
        uint16_t        size            // Number of Elements in Buffer
    );
    
    
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        cb16_getSize(
        CB16_DATA       *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    bool            cb16_Get(
        CB16_DATA       *this,
        uint16_t        *pData,
        uint32_t        timeout
    );


    bool            cb16_IsEmpty(
        CB16_DATA       *this
    );


    bool            cb16_IsFull(
        CB16_DATA       *this
    );


    CB16_DATA *     cb16_Init(
        CB16_DATA       *this
    );


    bool            cb16_Put(
        CB16_DATA       *this,
        uint16_t        value,
        uint32_t        timeout
    );



#ifdef	__cplusplus
}
#endif

#endif	/* CB16_H */

