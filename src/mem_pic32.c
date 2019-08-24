//****************************************************************
//						Oscillator Functions			
//****************************************************************
// vi: nu:noai:ts=4:sw=4

/*
 * Todo List
 *  ---         None yet
 * Remarks
 *  1.          None
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





/****************************************************************
* * * * * * * * * * * *  data definitions   * * * * * * * * * * *
****************************************************************/

/* Header File Inclusion */
//#include        <xc.h>
#include        <stdlib.h>
#include        <string.h>
#include        "cmn.h"
#include        "mem_pic32.h"




/****************************************************************
* * * * * * * * * * *  Internal Subroutines * * * * * * * * * * *
****************************************************************/





/****************************************************************
* * * * * * * * * * *  External Subroutines   * * * * * * * * * *
****************************************************************/



//===============================================================
//                      *** Class Methods ***
//===============================================================






//===============================================================
//                      *** Properties ***
//===============================================================






//===============================================================
//                      *** Methods ***
//===============================================================


// StrDup() duplicates a NUL terminated string.
char *          mem_StrDup(
    const
    char			*pOldStr
)
{
    char            *pNewStr = NULL;
    size_t          len = 0;
    
    if (NULL == pOldStr) {
        return NULL;
    }
    
    pNewStr = (char *)pOldStr;
    while (*pNewStr++) {
        ++len;
    }
    ++len;
    
    pNewStr = mem_Malloc(len);
    if (NULL == pNewStr) {
        return NULL;
    }
    
    while (len--) {
        *pNewStr++ = *pOldStr++;
    }
    *pNewStr = '\0';
    
    
    return pNewStr;
}









