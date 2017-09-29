// Common Routines and Data that can be used by all
// Tests
//

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


#import     <Foundation/Foundation.h>
#include    <stdbool.h>
#include    <stdint.h>
#include    <stdio.h>

#include    "chario.h"




//===============================================================
//                    *** Char I/O Mock ***
//===============================================================

bool            chrInputAdd(
    char            *pMsg
);

bool            chrInputGet(
    void            *pObjectRx,
    int32_t         *pData,         // Return Data ptr,
                                    // if NULL, return data is flushed.
    uint32_t        timeOut_ms      // Time Out in ms to wait
                                    // (0 == no wait, 0xFFFFFFFF == infinite)
);

void            chrInputReset(
    void
);


bool            chrOutputPut(
    void            *pObjectTx,
    int32_t         data,
    uint32_t        timeOut_ms      // Time Out in ms to wait
                                    // (0 == no wait, 0xFFFFFFFF == infinite)
);

char *          chrOutputData(
    int             *pLen
);

void            chrOutputReset(
    void
);


extern
CHARIO_DATA     chrIO;




//----------------------------------------------------------------
//                  Messages found in common04.c
//----------------------------------------------------------------
// NULL Terminated list of random words
extern
char            *ppWords01[];


