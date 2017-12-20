// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          TEXTIN Console Transmit Task (textIn) Header
//****************************************************************
/*
 * Program
 *			Separate textIn (textIn)
 * Purpose
 *			This object provides the means of processing an input
 *          text file from several different types of sources and
 *          tracking the source location as each character is
 *          returned.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/23/2017 Generated
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


#ifndef         TEXTIN_H
#define         TEXTIN_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct textIn_data_s	TEXTIN_DATA;    // Inherits from OBJ.

    typedef struct textIn_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in textIn_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TEXTIN_DATA *);
    } TEXTIN_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to textIn object if successful, otherwise OBJ_NIL.
     */
    TEXTIN_DATA *     textIn_Alloc(
        void
    );
    
    
    TEXTIN_DATA *     textIn_New(
        void
    );
    
    TEXTIN_DATA *   textIn_NewFromAStr(
        ASTR_DATA       *pStr,          // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     textIn_getLastError(
        TEXTIN_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    TEXTIN_DATA *  textIn_InitAStr(
        TEXTIN_DATA     *this,
        ASTR_DATA       *pStr,        // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t        tabSize       // Tab Spacing if any (0 will default to 4)
    );

    TEXTIN_DATA *  textIn_InitFile(
        TEXTIN_DATA     *this,
        FILE            *pFile,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );
    
    TEXTIN_DATA *  textIn_InitPath(
        TEXTIN_DATA     *this,
        PATH_DATA       *pFilePath,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );
    
    TEXTIN_DATA *  textIn_InitU8Array(
        TEXTIN_DATA     *this,
        U8ARRAY_DATA    *pBuffer,       // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );
    
    TEXTIN_DATA *  textIn_InitWStr(
        TEXTIN_DATA     *this,
        W32STR_DATA     *pWStr,         // Buffer of file data
        PATH_DATA       *pFilePath,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );
    

    /*! Get the location for the last character received.
     */
    ERESULT         textIn_Location(
        TEXTIN_DATA     *this,
        uint16_t        *pFilenameIndex,
        size_t          *pOffset,
        uint32_t        *pLineNo,
        uint16_t        *pColNo
    );
    
 
    /*!
     Return the next character in the file.
     @return    If successful, ERESULT_SUCCESS and *pChar contains the next
                character from the file, otherwise, an ERESULT_* error and
                *pChar contains EOF(-1).
     */
    W32CHR_T            textIn_NextChar(
        TEXTIN_DATA         *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = textIn_ToDebugString(this,4);
     @endcode 
     @param     this    TEXTIN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    textIn_ToDebugString(
        TEXTIN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* TEXTIN_H */

