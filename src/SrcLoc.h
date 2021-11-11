// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Source File Location (srcLoc) Header
//****************************************************************
/*
 * Program
 *			Source File Location (srcLoc)
 * Purpose
 *			This object provides a means of handing a location
 *          within a source/text file.
 *
 * Remarks
 *	1.      The fileIndex is consistent with the index into the
 *          szTbl. So, the file path can be stored in the shared
 *          szTbl and then retrieved from it when needed.
 *
 * History
 *	01/01/2016  Generated
 *  11/25/2019  Changed fileIndex to uint32_t from uint16_t to make
 *              it compatible with szTbl.
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


    typedef struct SrcLoc_data_s	SRCLOC_DATA;

//  SRCLOC size must be a multiple of 8.
#pragma pack(push, 1)
    typedef struct SrcLoc_s    {
        uint32_t        fileIndex;          // File Name Index
        //                                  // Note: If zero, then the entire
        //                                  //      location is ignored.
        uint16_t        colNo;              // Source Input Column Number (relative to 1)
        //                                  // If empty line, colNo is 0.
        uint16_t        unused16;
        uint32_t        lineNo;             // Source Input Line Number (relative to 0)
        uint32_t        unused32;
        int64_t         offset;             // File Offset (zero based)
    } SRCLOC;
#pragma pack(pop)
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    SRCLOC_DATA *   SrcLoc_Alloc(
        void
    );
    
    
    OBJ_ID          SrcLoc_Class(
        void
    );
    
    
    SRCLOC_DATA *   SrcLoc_NewFLC(
        uint32_t        fileIndex,              // File Index
        int64_t         offset,
        uint32_t        lineNo,
        uint16_t        colNo
    );
    
    
    SRCLOC_DATA *   SrcLoc_NewSrcLoc(
        SRCLOC          *pSrc
    );
    
    
    SRCLOC_DATA *   SrcLoc_NewFromJsonString(
        ASTR_DATA       *pString
    );
    
    
    SRCLOC_DATA *   SrcLoc_NewFromJsonStringA(
        const
        char            *pString
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        SrcLoc_getColNo(
        SRCLOC_DATA     *this
    );

    bool            SrcLoc_setColNo(
        SRCLOC_DATA     *this,
        uint16_t        value
    );
    
    
    uint32_t        SrcLoc_getFileIndex(
        SRCLOC_DATA      *this
    );
    
    bool            SrcLoc_setFileIndex(
        SRCLOC_DATA      *this,
        uint32_t         value
    );
    
    
    uint32_t        SrcLoc_getLineNo(
        SRCLOC_DATA     *this
    );
    
    bool            SrcLoc_setLineNo(
        SRCLOC_DATA     *this,
        uint32_t        value
    );
    
    
    int64_t         SrcLoc_getOffset(
        SRCLOC_DATA     *this
    );
    
    bool            SrcLoc_setOffset(
        SRCLOC_DATA     *this,
        int64_t         value
    );
    

    SRCLOC *        SrcLoc_getSrc(
        SRCLOC_DATA     *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     @result    0 if this == other
                1 if this != other
     */
    ERESULT         SrcLoc_Compare(
        SRCLOC_DATA		*this,
        SRCLOC_DATA     *pOther
    );
    
    
    SRCLOC_DATA *   SrcLoc_Init(
        SRCLOC_DATA     *this
    );

    SRCLOC_DATA *   SrcLoc_InitFLC(
        SRCLOC_DATA     *this,
        uint32_t        fileIndex,              // File Index
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
    ASTR_DATA *    SrcLoc_ToDebugString(
        SRCLOC_DATA     *this,
        int             indent
    );
    
    
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SrcLoc_ToJson(this);
     @endcode
     @param     this    SRCLOC object pointer
     @return    If successful, an AStr object which must be released containing the
     JSON text, otherwise OBJ_NIL and LastError set to an appropriate
     ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcLoc_ToJson(
        SRCLOC_DATA     *this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SRCLOC_H */

