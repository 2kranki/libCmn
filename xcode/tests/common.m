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



#include    "common.h"
#include    <stdio.h>
#include    <string.h>
#import     <Foundation/Foundation.h>




// NULL Terminated list of random words
char            *ppWords01[] = {
    "bob",
    "bobby",
    "iryana",
    "dashsa",
    "dasha",
    "name",
    "way",
    "bigger",
    "Now",
    "is",
    "the",
    "time",
    "for",
    "all",
    "good",
    "men",
    "to",
    "come",
    "aid",
    "of",
    "their",
    "country",
    "We",
    "need",
    "another",
    "item",
    "in",
    "here",
    "are",
    "you",
    "alright",
    "with",
    "this",
    "he",
    "first",
    "way",
    "oil",
    "down",
    "made",
    "as",
    "at",
    "was",
    "with",
    "be",
    "or",
    "and",
    "his",
    "a",
    "that",
    "on",
    "they",
    "have",
    "it",
    "from",
    "or",
    "but",
    "there",
    "she",
    "one",
    "not",
    "when",
    "use",
    "do",
    "had",
    "what",
    "your",
    "an",
    "how",
    "sent",
    "married",
    "longer",
    "immediately",
    "god",
    "women",
    "hours",
    "ten",
    "understand",
    "son",
    "horse",
    "wonder",
    "cold",
    "beyond",
    "please",
    "fair",
    "became",
    "sight",
    "met",
    "afterwards",
    "eye",
    "year",
    "show",
    "general",
    "itself",
    "silence",
    "lord",
    "wrong",
    "turning",
    "daughter",
    "stay",
    "forward",
    "interest",
    "thoughts",
    "followed",
    "different",
    "opened",
    "several",
    "idea",
    "received",
    "change",
    "laid",
    "strange",
    "nobody",
    "fact",
    "during",
    "feet",
    "tears",
    (char *)NULL
};





//===============================================================
//                    *** Char I/O Mock ***
//===============================================================

// Input will end up being a set of strings. Each terminated by NUL.
static
char            charInputBuffer[1024];
static
int             cInput = 0;
static
int             cInputCur = 0;


bool        chrInputAdd(
    char        *pMsg
)
{
    size_t      len;
    int         i;
    
    if (pMsg) {
        len = strlen(pMsg);
        if (len+cInput > 1024) {
            [NSException	raise: NSGenericException
                        format: @"ERROR: %@  REASON: %@",
                                @"Input Character Buffer Overflow",
                                @"Attempting to add more data than the Input Character"
                                @"buffer can hold!"
             ];
        }
        for (i=0; i<len; ++i) {
            charInputBuffer[cInput++] = *pMsg++;
        }
        charInputBuffer[cInput++] = '\0';
    }
    else {
        [NSException	raise: NSGenericException
                    format: @"ERROR: %@  REASON: %@",
                            @"Missing Input Data",
                            @"Missing data to add to the Input Character"
                            @"buffer!"
         ];
    }
    return true;
}



// This must conform to charIO!
bool        chrInputGet(
    void            *pObjectRx,
    int32_t         *pData,         // Return Data ptr,
                                    // if NULL, return data is flushed.
    uint32_t        timeOut_ms      // Time Out in ms to wait
                                    // (0 == no wait, 0xFFFFFFFF == infinite)
)
{

    if (cInputCur < cInput) {
        if (pData) {
            *pData = charInputBuffer[cInputCur++];
        }
        else
            ++cInputCur;
        return true;
    }

    return false;
}



void        chrInputReset(
)
{
    cInput = 0;
    cInputCur = 0;
}


static
const
int             cOutputMax = 16384;
static
char            szOutput[cOutputMax];
static
int             cOutputCur = 0;

bool        chrOutputPut(
    void            *pObjectTx,
    int32_t         data,
    uint32_t        timeOut_ms      // Time Out in ms to wait
    // (0 == no wait, 0xFFFFFFFF == infinite)
)
{
    fputc( (data & 0xFF), stderr );
    if (cOutputCur >= (cOutputMax-1)) {
        return false;
    }
    szOutput[cOutputCur++] = (char)(data & 0xFF);
    szOutput[cOutputCur] = '\0';
    return true;
}


char *      chrOutputData(
    int         *pLen
)
{
    if (pLen) {
        *pLen = cOutputCur;
    }
    return szOutput;
}


void        chrOutputReset(
)
{
    cOutputCur = 0;
}


CHARIO_DATA chrIO = {
    NULL,
    NULL,
    &chrInputGet,
    &chrOutputPut
};













