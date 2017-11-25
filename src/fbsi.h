// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                Sequential File Input (fbsi) Header
//****************************************************************
/*
 * Program
 *			Sequential File Input (fbsi)
 * Purpose
 *			This object provides a standard way of reading
 *          files from disk. Its advantage over just
 *          using stream I/O is that you have the additional
 *          properties associated with the file such as its
 *          path within this object.
 *
 * Remarks
 *	1.      ???
 *
 * History
 *	05/21/2015 Generated
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
#include        <path.h>


#ifndef         FBSI_H
#define         FBSI_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct fbsi_data_s	FBSI_DATA;

    typedef struct fbsi_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fat16_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(FBSI_DATA *);
    } FBSI_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the fbsi including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    FBSI_DATA *     fbsi_Alloc(
        void
    );
    
    
    FBSI_DATA *     fbsi_NewPath(
        PATH_DATA       *pFilePath
    );
    
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    PATH_DATA *     fbsi_getPath(
        FBSI_DATA		*this
    );
    
    bool            fbsi_setPath(
        FBSI_DATA		*this,
        PATH_DATA       *pValue
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         fbsi_Getwc(
        FBSI_DATA		*this,
        int32_t         *pChar
    );
    
    
    FBSI_DATA *     fbsi_InitPath(
        FBSI_DATA       *this,
        PATH_DATA       *pFilePath
    );


    FBSI_DATA *     fbsi_InitAStr(
        FBSI_DATA       *this,
        ASTR_DATA       *pStr,          // Buffer of file data
        PATH_DATA       *pFilePath      // Optoinal File Path used for Documentation Purposes
    );
    
    
    bool            fbsi_IsAtEOF(
        FBSI_DATA		*this
    );
    
    
    /*!
     Push the given character onto the stack for retrieval on the next Getc or
     Getwc.
     Example:
     @code
     ERESULT      eRc = fbsi_Push(pObj,'/');
     @endcode
     @param     this    fbsi object pointer
     @param     chr     character to be pushed
     @return    If successful, ERESULT_SUCCESS is returned, otherwise an
                ERESULT error code is returned.
     */
    ERESULT         fbsi_Push(
        FBSI_DATA		*this,
        int32_t         chr
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = fbsi_ToDebugString(pObj,4);
     @endcode
     @param     this    fat16 object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                 description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     fbsi_ToDebugString(
        FBSI_DATA       *this,
        int             indent
    );
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* FBSI_H */

