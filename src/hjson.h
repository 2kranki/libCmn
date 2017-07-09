// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Human JSON Parser (hjson) Header
//****************************************************************
/*
 * Program
 *			Human JSON Parser (hjson)
 * Purpose
 *			This object parses an HJSON file into an appropriate
 *          nodes. HJSON is a relaxed version of JSON. To parse
 *          it, we use a specialized lexical scanner, lexj.
 *
 * Remarks
 *	1.      I changed the definition of the quoteless string to end
 *          with '\n' and any of '{','}','[',']',':',','. This al-
 *          lows it to be used for object names as well as quote-
 *          less strings. If any of those characters needs to be
 *          added to a string, then simply quote the string.
 *
 * History
 *	07/08/2017 Generated
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
#include        <node.h>
#include        <false.h>
#include        <null.h>
#include        <path.h>
#include        <true.h>


#ifndef         HJSON_H
#define         HJSON_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct hjson_data_s	HJSON_DATA;    // Inherits from OBJ.

    typedef struct hjson_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in hjson_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(HJSON_DATA *);
    } HJSON_VTBL;



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
     @return:   pointer to hjson object if successful, otherwise OBJ_NIL.
     */
    HJSON_DATA *     hjson_Alloc(
    );
    
    
    HJSON_DATA *    hjson_NewAStr(
        ASTR_DATA       *pSzStr,        // Buffer of file data
        uint16_t		tabSize         // Tab Spacing if any
    );
    
    
    HJSON_DATA *    hjson_NewFromFile(
        PATH_DATA       *pFilePath,     // Input File Path
        uint16_t		tabSize         // Tab Spacing if any
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NODEHASH_DATA * hjson_getFileObject(
        HJSON_DATA      *this
    );
    
    
    ERESULT         hjson_getLastError(
        HJSON_DATA		*this
    );
    
    
    PATH_DATA *     hjson_getPath(
        HJSON_DATA      *this
    );
    
    bool            hjson_setPath(
        HJSON_DATA      *this,
        PATH_DATA       *pValue
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    HJSON_DATA *    hjson_InitAStr(
        HJSON_DATA      *this,
        ASTR_DATA       *pAStr,         // Buffer of file data
        uint16_t		tabSize         // Tab Spacing if any
    );
    
    HJSON_DATA *    hjson_InitFile(
        HJSON_DATA      *this,
        PATH_DATA       *pFilePath,
        uint16_t        tabSize         // Tab Spacing if any
    );
    
    
    // If successful, returns a node, "hash", which has a nodeHash
    // as its data.
    NODE_DATA *     hjson_ParseFile(
        HJSON_DATA		*this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = hjson_ToDebugString(this,4);
     @endcode:
     @param:    this    HJSON object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    hjson_ToDebugString(
        HJSON_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* HJSON_H */

