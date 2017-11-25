// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Generic Disk File Input/Output (fileio) Header
//****************************************************************
/*
 * Program
 *			Generic Disk File Input/Output (fileio)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate fileio to run things without complications
 *          of interfering with the main fileio. A fileio may be 
 *          called a fileio on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal fileio. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	07/30/2016 Generated
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


#ifndef         FILEIO_H
#define         FILEIO_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct fileio_data_s	FILEIO_DATA;    // Inherits from OBJ.

    typedef struct fileio_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fileio_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(FILEIO_DATA *);
    } FILEIO_VTBL;



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
     @return:   pointer to fileio object if successful, otherwise OBJ_NIL.
     */
    FILEIO_DATA *   fileio_Alloc(
        void
    );
    
    
    FILEIO_DATA *   fileio_New(
        uint32_t        headerSize,
        PATH_DATA       *pPath
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         fileio_getLastError(
        FILEIO_DATA     *this
    );
    
    
    PATH_DATA *     fileio_getPath(
        FILEIO_DATA     *this
    );
    
    bool            fileio_setPath(
        FILEIO_DATA     *this,
        PATH_DATA       *pValue
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    bool            fileio_Close(
        FILEIO_DATA		*this
    );


    FILEIO_DATA *   fileio_Init(
        FILEIO_DATA     *this,
        uint32_t        headerSize,
        PATH_DATA       *pPath
    );


    bool            fileio_Open(
        FILEIO_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = fileio_ToDebugString(pObj,4);
     @endcode
     @param     this    fileio object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    fileio_ToDebugString(
        FILEIO_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* FILEIO_H */

