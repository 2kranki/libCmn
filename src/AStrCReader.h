// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              AStrC Reader (AStrCReader) Header
//****************************************************************
/*
 * Program
 *			AStrC Reader (AStrCReader)
 * Purpose
 *			This object provides an AStrC Reader which allows an
 *          AStrC to read one UTF-8 character at a time.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	08/11/2019 Generated
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
#include        <AStrC.h>
#include        <w32Reader.h>


#ifndef         ASTRCREADER_H
#define         ASTRCREADER_H


//#define   ASTRCREADER_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct AStrCReader_data_s	ASTRCREADER_DATA;            // Inherits from OBJ
    typedef struct AStrCReader_class_data_s ASTRCREADER_CLASS_DATA;   // Inherits from OBJ

    // Conforms to w32Reader Interface
    typedef struct AStrCReader_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in AStrCReader_object.c.
        // Properties:
        // Methods:
        // Next() reads the next UTF-32 character from the scan string.
        // It will return -1 if an error or end-of-string (EOS) is encountered.
        W32CHR_T    (*pNext)(OBJ_ID);
        // Peek() returns the n'th character after the current one or -1 if
        // beyond the end-of-string (EOS).
        W32CHR_T    (*pPeek)(
                             OBJ_ID,
                             uint32_t                    // Number of chars to look ahead
                             );
        // Rescan() restarts the scan to the beginning of the data.
        ERESULT     (*pRescan)(OBJ_ID);
    } ASTRCREADER_VTBL;

    typedef struct AStrCReader_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in AStrCReader_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ASTRCREADER_DATA *);
    } ASTRCREADER_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  ASTRCREADER_SINGLETON
    ASTRCREADER_DATA * AStrCReader_Shared (
        void
    );

    bool            AStrCReader_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to AStrCReader object if successful, otherwise OBJ_NIL.
     */
    ASTRCREADER_DATA * AStrCReader_Alloc (
        void
    );
    
    
    OBJ_ID          AStrCReader_Class (
        void
    );
    
    
    ASTRCREADER_DATA * AStrCReader_New (
        void
    );
    
    
    ASTRCREADER_DATA * AStrCReader_NewAStrC (
        ASTRC_DATA      *pStr
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    W32_READER *    AStrCReader_getReader (
        ASTRCREADER_DATA *this
    );
    
    
    ASTRC_DATA *    AStrCReader_getStr (
        ASTRCREADER_DATA *this
    );

    bool            AStrCReader_setStr (
        ASTRCREADER_DATA *this,
        ASTRC_DATA      *pValue
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ASTRCREADER_DATA * AStrCReader_Init (
        ASTRCREADER_DATA *this
    );


    /*!
     Next() reads the next charater from the data advancing
     the read pointer.
     @param     this    object pointer
     @return    the next UTF-32 character or -1 for EOF
     */
    int32_t         AStrCReader_Next (
        ASTRCREADER_DATA *this
    );
    
    
    /*!
     Peek() returns the n'th character after the last one read.
     @param     this    object pointer
     @param     n       Number of chars to look ahead (relative to 1)
     @return    the requested UTF-32 character or -1 for EOF
     */
    int32_t         AStrCReader_Peek (
        ASTRCREADER_DATA *this,
        uint32_t         n               // Number of chars to look ahead
    );
    
    
    /*!
     Rescan() resets the read pointer to the beginning of the string
     which restarts the scan to the beginning of the data.
     @param     this    object pointer
     @return    An ERESULT result code
     */
    ERESULT         AStrCReader_Rescan (
        ASTRCREADER_DATA *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = AStrCReader_ToDebugString(this,4);
     @endcode 
     @param     this    ASTRCREADER object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    AStrCReader_ToDebugString (
        ASTRCREADER_DATA *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* ASTRCREADER_H */

