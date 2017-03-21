// vi:nu:et:sts=4 ts=4 sw=4
//****************************************************************
//  PIC32 Circular Buffer 8-Bit Elements (cb8) Support  Header
//****************************************************************
/*
 * Program
 *				PIC32 Circular Buffer 8-Bit Elements (cb8) Subroutines
 * Purpose
 *				These subroutines provide a general purpose set of
 *				routines to provide a Circular (FIFO) Buffer of
 *              uint8_t elements. The buffer is designed to work in
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


#ifndef         CB8_H
#define         CB8_H




//****************************************************************
//* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
//****************************************************************

typedef struct cb8_data_s	CB8_DATA;




/****************************************************************
* * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
****************************************************************/

#ifdef	__cplusplus
extern "C" {
#endif


//---------------------------------------------------------------
//                      *** Properties ***
//---------------------------------------------------------------

uint16_t        cb8_getSize(
	CB8_DATA        *this
);



//---------------------------------------------------------------
//                      *** Methods ***
//---------------------------------------------------------------

// cb8_Close() frees the control blocks
// built at open.
// Returns:
//      NULL on success
//      cbp if failure
CB8_DATA *     cb8_Close(
	CB8_DATA        *this
);


uint16_t        cb8_Count(
    CB8_DATA        *this
);
    
    
bool            cb8_Get(
	CB8_DATA        *this,
    uint8_t         *data
);


bool            cb8_IsEmpty(
	CB8_DATA        *this
);


bool            cb8_IsFull(
	CB8_DATA        *this
);


// cb8_Open() allocates the control blocks for
// the buffer given the size in uint32_t's.
// Returns:
//      cbp  if successful
//      NULL on failure
CB8_DATA *     cb8_Open(
    uint16_t        size            // Size of Buffer in uint32_t's
);


bool            cb8_Put(
	CB8_DATA        *this,
    uint8_t         value
);



#ifdef	__cplusplus
}
#endif

#endif	/* CB8_H */

