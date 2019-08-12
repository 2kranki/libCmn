// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SCANREADER Console Transmit Task (scanReader) Header
//****************************************************************
/*
 * Program
 *			Separate scanReader (scanReader)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate scanReader to run things without complications
 *          of interfering with the main scanReader. A scanReader may be 
 *          called a scanReader on other O/S's.
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
#include        <w32Reader.h>


#ifndef         SCANREADER_H
#define         SCANREADER_H


//#define   SCANREADER_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct scanReader_data_s	SCANREADER_DATA;            // Inherits from OBJ
    typedef struct scanReader_class_data_s SCANREADER_CLASS_DATA;   // Inherits from OBJ

    // Conforms to w32Reader Interface
    typedef struct scanReader_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in scanReader_object.c.
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
    } SCANREADER_VTBL;

    typedef struct scanReader_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in scanReader_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SCANREADER_DATA *);
    } SCANREADER_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SCANREADER_SINGLETON
    SCANREADER_DATA *     scanReader_Shared (
        void
    );

    bool            scanReader_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to scanReader object if successful, otherwise OBJ_NIL.
     */
    SCANREADER_DATA * scanReader_Alloc (
        void
    );
    
    
    OBJ_ID          scanReader_Class (
        void
    );
    
    
    SCANREADER_DATA * scanReader_New (
        void
    );
    
    
    SCANREADER_DATA * scanReader_NewA (
        const
        char            *pStr
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    W32_READER *    scanReader_getReader (
        SCANREADER_DATA *this
    );
    
    
    const
    char *          scanReader_getStr (
        SCANREADER_DATA     *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    SCANREADER_DATA *   scanReader_Init (
        SCANREADER_DATA     *this
    );


    /*!
     Next() scans the next charater from the data.
     @param     this    object pointer
     @return    the next UTF-32 character or -1 for EOF
     */
    int32_t         scanReader_Next (
        SCANREADER_DATA *this
    );
    
    
    /*!
     Peek() returns the n'th character after the last one read.
     @param     this    object pointer
     @param     n       Number of chars to look ahead (relative to 1)
     @return    the requested UTF-32 character or -1 for EOF
     */
    int32_t         scanReader_Peek (
        SCANREADER_DATA *this,
        uint32_t         n               // Number of chars to look ahead
    );
    
    
    /*!
     Rescan() restarts the scan to the beginning of the data.
     @param     this    object pointer
     @return    An ERESULT result code
     */
    ERESULT         scanReader_Rescan (
        SCANREADER_DATA *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = scanReader_ToDebugString(this,4);
     @endcode 
     @param     this    SCANREADER object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    scanReader_ToDebugString (
        SCANREADER_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SCANREADER_H */

