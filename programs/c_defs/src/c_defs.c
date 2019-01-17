//
//  c_defs
//
//  Created by bob on 1/14/19.
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


#include    <cmn_defs.h>
#include    <AStr.h>
#include    <dbCsv.h>
#include    <path.h>
#include    <trace.h>




//===============================================================
//                          M a i n
//===============================================================

int             main(
    int             argc,
    const
    char *          argv[]
)
{
    bool            fRc;
    
        fprintf(stdout, "size of ptr: %d\n", (int)sizeof(long *));
        fprintf(stdout, "size of long: %d\n", (int)sizeof(long));
        fprintf(stdout, "size of int: %d\n", (int)sizeof(int));
        fprintf(stdout, "size of short: %d\n", (int)sizeof(short));
        fprintf(stdout, "size of uint64_t: %d\n", (int)sizeof(uint64_t));
        fprintf(stdout, "size of uint32_t: %d\n", (int)sizeof(uint32_t));
        fprintf(stdout, "size of uint16_t: %d\n", (int)sizeof(uint16_t));

    return 0;
}
