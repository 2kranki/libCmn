// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SRCFILES Console Transmit Task (srcFiles) Header
//****************************************************************
/*
 * Program
 *				Separate srcFiles (srcFiles)
 * Purpose
 *				This object serves two purposes. First, it provides
 *              for file inclusion by using a stack of sources which
 *              when exhausted are popped off the stack. Second, it
 *              provides for translation from a file number used in
 *              the tokens back to a file name.
*
 * Remarks
 *	1.      None
 *
 * History
 *	08/06/2015 Generated
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
#include        <srcFile.h>
#include        <path.h>
#include        <Token.h>


#ifndef         SRCFILES_H
#define         SRCFILES_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct srcFiles_data_s	SRCFILES_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    SRCFILES_DATA *  srcFiles_Alloc(
        void
    );
    
    
    SRCFILES_DATA *  srcFiles_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ASTRARRAY_DATA * srcFiles_getPaths(
        SRCFILES_DATA   *this
    );
    

    bool            srcFiles_getReuse(
        SRCFILES_DATA   *this
    );
    
    bool            srcFiles_setReuse(
        SRCFILES_DATA   *this,
        bool            fValue
    );
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    uint16_t        srcFiles_AddPath(
        SRCFILES_DATA   *this
    );
    
    
    SRCFILES_DATA * srcFiles_Init(
        SRCFILES_DATA   *this
    );


    TOKEN_DATA *    srcFiles_InputAdvance(
        SRCFILES_DATA   *this,
        uint16_t        numChrs
    );
    
    
    TOKEN_DATA *    srcFiles_InputLookAhead(
        SRCFILES_DATA   *this,
        uint16_t        num
    );
    
    
    /*!
     Create a new srcFile object from the given parameters and push it to the
     top of the stack.
     */
    ERESULT         srcFiles_NewSrcFromAStr(
        SRCFILES_DATA   *this,
        PATH_DATA       *pFilePath,
        ASTR_DATA       *pAStr,         // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );
    
    ERESULT         srcFiles_NewSrcFromFile(
        SRCFILES_DATA   *this,
        FILE            *pFile,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );
    
    
    ERESULT         srcFiles_NewSrcFromPath(
        SRCFILES_DATA   *this,
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );
    
    
    ERESULT         srcFiles_StackPop(
        SRCFILES_DATA   *this
    );
    
    
    ERESULT			srcFiles_StackPush(
        SRCFILES_DATA   *this,
        SRCFILE_DATA    *pItem
    );
   
    
    SRCFILE_DATA *  srcFiles_StackTop(
        SRCFILES_DATA   *this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     srcFiles_ToDebugString(
        SRCFILES_DATA   *this,
        int             indent
    );
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* SRCFILES_H */

