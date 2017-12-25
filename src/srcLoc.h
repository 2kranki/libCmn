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

#pragma pack(push, 1)
    typedef struct srcLoc_s    {
        uint16_t        fileIndex;          // File Name Index
        //                                  // Note: If zero, then the entire
        //                                  //      location is ignored.
        uint16_t        colNo;              // Source Input Column Number
        uint32_t        lineNo;             // Source Input Line Number
        int64_t         offset;             // File Offset
    } SRCLOC;
#pragma pack(pop)
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    SRCLOC_DATA *     srcLoc_Alloc(
        void
    );
    
    
    OBJ_ID          srcLoc_Class(
        void
    );
    
    
    SRCLOC_DATA *     srcLoc_NewFLC(
        uint16_t        fileIndex,              // File Index
        int64_t         offset,
        uint32_t        lineNo,
        uint16_t        colNo
    );
    
    
    SRCLOC_DATA *     srcLoc_NewSrcLoc(
        SRCLOC          *pSrc
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
    
    
    uint16_t        srcLoc_getFileIndex(
        SRCLOC_DATA      *this
    );
    
    bool            srcLoc_setFileIndex(
        SRCLOC_DATA      *this,
        uint16_t         value
    );
    
    
    uint32_t        srcLoc_getLineNo(
        SRCLOC_DATA     *this
    );
    
    bool            srcLoc_setLineNo(
        SRCLOC_DATA     *this,
        uint32_t        value
    );
    
    
    int64_t         srcLoc_getOffset(
        SRCLOC_DATA     *this
    );
    
    bool            srcLoc_setOffset(
        SRCLOC_DATA     *this,
        int64_t         value
    );
    

    SRCLOC *        srcLoc_getSrc(
        SRCLOC_DATA     *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     @result    ERESULT_SUCCESS_EQUAL if this == other or
                ERESULT_SUCCESS_UNEQUAL
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
        uint16_t        fileIndex,              // File Index
        int64_t         offset,
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
    
    
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = srcLoc_ToJSON(this);
     @endcode
     @param     this    SRCLOC object pointer
     @return    If successful, an AStr object which must be released containing the
     JSON text, otherwise OBJ_NIL and LastError set to an appropriate
     ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     srcLoc_ToJSON(
        SRCLOC_DATA     *this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SRCLOC_H */

