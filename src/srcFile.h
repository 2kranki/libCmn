// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Read a Source File  (srcFile) Header
//****************************************************************
/*
 * Program
 *				Read a Source File (srcFile)
 * Purpose
 *				This takes a file from several different sources
 *              and tokenizes it into a stream of token to be used
 *              for parsing. These routines are UTF-8 aware and
 *              will tokenize a multi-byte character into one token.
 *
 * Remarks
 *	1.      EOF(-1) denotes the end of file. So, the token class
 *          and token character will be set to EOF for every
 *          access at EOF.
 *
 * History
 *	06/17/2015 Generated
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
#include        <ascii.h>
#include        <fbsi.h>
#include        <path.h>
#include        <AStr.h>
#include        <token.h>
#include        <u8Array.h>
#include        <WStr.h>


#ifndef         SRCFILE_H
#define         SRCFILE_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct srcFile_data_s	SRCFILE_DATA;

    typedef struct srcFile_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in consumer_object.c.
        // Properties:
        // Methods:
    } SRCFILE_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    SRCFILE_DATA *     srcFile_Alloc(
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            srcFile_getReuse(
        SRCFILE_DATA    *this
    );
    
    bool            srcFile_setReuse(
        SRCFILE_DATA    *this,
        bool            fValue
    );
    
    bool            srcFile_getStripCR(
        SRCFILE_DATA    *this
    );
    
    bool            srcFile_setStripCR(
        SRCFILE_DATA    *this,
        bool            fValue
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    SRCFILE_DATA *  srcFile_InitFile(
        SRCFILE_DATA    *this,
        PATH_DATA       *pFilePath,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs,
        bool            fRemoveNLs
    );
    
    
    SRCFILE_DATA *  srcFile_InitAStr(
        SRCFILE_DATA    *this,
        ASTR_DATA       *pStr,          // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs,
        bool            fRemoveNLs
    );
    
    
    SRCFILE_DATA *  srcFile_InitU8Array(
        SRCFILE_DATA    *this,
        U8ARRAY_DATA    *pBuffer,       // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t		tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs,
        bool            fRemoveNLs
    );
    
    
    SRCFILE_DATA *  srcFile_InitWStr(
        SRCFILE_DATA    *this,
        WSTR_DATA       *pWStr,         // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs,
        bool            fRemoveNLs
    );
    
    
    TOKEN_DATA *    srcFile_InputAdvance(
        SRCFILE_DATA    *this,
        uint16_t        numChrs
    );
    
    
    TOKEN_DATA *    srcFile_InputLookAhead(
        SRCFILE_DATA    *this,
        uint16_t        num
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     srcFile_ToDebugString(
        SRCFILE_DATA    *this,
        int             indent
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* SRCFILE_H */

