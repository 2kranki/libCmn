// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SRCLOC Console Transmit Task (srcLoc) Header
//****************************************************************
/*
 * Program
 *			Separate srcLoc (srcLoc)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate srcLoc to run things without complications
 *          of interfering with the main srcLoc. A srcLoc may be 
 *          called a srcLoc on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal srcLoc. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	01/01/2016 Generated
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
#include        <AStr.h>


#ifndef         SRCLOC_H
#define         SRCLOC_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct srcLoc_data_s	SRCLOC_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    SRCLOC_DATA *     srcLoc_Alloc(
    );
    
    
    SRCLOC_DATA *     srcLoc_NewFLC(
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo
    );
    
    
    SRCLOC_DATA *   srcLoc_NewFromJSONString(
        ASTR_DATA       *pString
    );
    
    
    SRCLOC_DATA *   srcLoc_NewFromJSONStringA(
        const
        char            *pString
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        srcLoc_getColNo(
        SRCLOC_DATA     *this
    );

    bool            srcLoc_setColNo(
        SRCLOC_DATA     *this,
        uint16_t        value
    );
    
    
    const char *    srcLoc_getFileName(
        SRCLOC_DATA      *this
    );
    
    bool            srcLoc_setFileName(
        SRCLOC_DATA      *this,
        const
        char            *pValue
    );
    
    
    uint32_t        srcLoc_getLineNo(
        SRCLOC_DATA     *this
    );
    
    bool            srcLoc_setLineNo(
        SRCLOC_DATA     *this,
        uint32_t        value
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     @result    ERESULT_SUCCESS_EQUAL if this == other,
                ERESULT_SUCCESS_LESS_THAN if this < other or
                ERESULT_SUCCESS_GREATER_THAN if this > other.
     */
    ERESULT         srcLoc_Compare(
        SRCLOC_DATA		*this,
        SRCLOC_DATA     *pOther
    );
    
    
    SRCLOC_DATA *   srcLoc_Init(
        SRCLOC_DATA     *this
    );

    SRCLOC_DATA *   srcLoc_InitFLC(
        SRCLOC_DATA     *this,
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo
    );
    

    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *    srcLoc_ToDebugString(
        SRCLOC_DATA     *this,
        int             indent
    );
    
    
    ASTR_DATA *     srcLoc_ToJSON(
        SRCLOC_DATA     *this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SRCLOC_H */

