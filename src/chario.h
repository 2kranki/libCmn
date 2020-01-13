// vi:nu:et:sts=4 ts=4 sw=4
//****************************************************************
//              Character I/O (chario) Support  Header
//****************************************************************
/*
 * Program
 *				Character I/O (chario) Object Definition
 * Purpose
 *				These provide a general definition of a character
 *				I/O object used to objectify the interface.
 *
 *
 * Remarks
 *	1.			None
 *
 * History
 *	10/26/2014	Created from scratch.
 * References
 *		"Data Structures and Algorithms", Alfred V. Aho et al,
 *			Addison-Wesley, 1985
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




#ifndef     CHARIO_H
#define	    CHARIO_H

#include    <stdbool.h>
#include    <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif
    


//****************************************************************
//* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
//****************************************************************



typedef struct chario_data_s {

    // Object provided as the first parameter of each of the
    // routines below.
    void            *pObjectRx;
    void            *pObjectTx;

    // Returns true if a char was received within the time out,
    // otherwise false.  
    bool            (*GetRxChar)( 
        void            *pObjectRx,
        int32_t         *pData,         // Return Data ptr,
                                        // if NULL, return data is flushed.
        uint32_t        timeOut_ms      // Time Out in ms to wait
                                        // (0 == no wait, 0xFFFFFFFF == infinite)
    );

    // PutChar writes a character to the device, blocking until
    // the character can actually be sent.
    bool            (*PutTxChar)( 
        void            *pObjectTx,
        int32_t         data,
        uint32_t        timeOut_ms      // Time Out in ms to wait
                                        // (0 == no wait, 0xFFFFFFFF == infinite)
    );
}   CHARIO_DATA;


#ifdef	__cplusplus
}
#endif
        


#endif	    /* CHARIO_H */

