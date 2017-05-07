// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  JSON (json) Header
//****************************************************************
/*
 * Program
 *			json file input (json)
 * Purpose
 *			This object provides a standardized way of parsing or
 *          constructing JSON data. An 'object' is a hash with
 *          keys and data entries.
 *
 *          json    : value+
 *                  ;
 *          value   : array | object | string | number
 *                  ;
 *          object  : '{' ws* object_value (',' ws* object_value)* ws* '}'
 *                  ;
 *          object_value
 *                  : string ws* ':' ws* value
 *                  ;
 *          array   : '[' ws* value ws* (',' ws* value)* ws* ']'
 *                  ;
 *          ws      : ' ' | '\n' | '\r' | '\t'
 *                  ;
 *          string  : '"' string_chars* '"'
 *                  ;
 *          string_chars  
 *                  : [\b\f\n\r\t\\\/ !] 
 *                  | [#-~]
 *                  | '\\' '"' 
 *                  | '\\' ('u'|'U') hexdigit*
 *                  | '\\' '\\'
 *                  ;
 *          number  : ('-')? [1-9][0-9]* ('.' [0-9]+)? exp?
 *                  ;
 *          exp     : ('e' | 'E') ('-' | '+')? [0-9]+
 *                  ;
 *
 *      Arrays returned are node children and objects are hashes.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	10/18/2015 Generated
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


#ifndef         JSON_H
#define         JSON_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


#ifndef         JSON_FIELD_MAX
#define         JSON_FIELD_MAX  512
#endif

    
    typedef struct json_data_s	JSON_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the json including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    JSON_DATA *     json_Alloc(
    );
    
    
    JSON_DATA *     json_NewAStr(
        ASTR_DATA       *pSzStr,        // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    );
    
    
    JSON_DATA *     json_NewFromFile(
        PATH_DATA       *pPath,         // Input File Path
        uint16_t		tabSize         // Tab Spacing if any
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NODEHASH_DATA * json_getFileObject(
        JSON_DATA       *this
    );
    
    
    PATH_DATA *     json_getPath(
        JSON_DATA       *this
    );

    bool            json_setPath(
        JSON_DATA       *this,
        PATH_DATA       *pValue
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    JSON_DATA *     json_InitFile(
        JSON_DATA       *this,
        PATH_DATA       *pFilePath,
        uint16_t        tabSize         // Tab Spacing if any
    );
    
    JSON_DATA *     json_InitAStr(
        JSON_DATA       *this,
        ASTR_DATA       *pAStr,         // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    );
    
    JSON_DATA *     json_InitWStr(
        JSON_DATA       *this,
        WSTR_DATA       *pWStr,         // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    );
    

    // If successful, returns a node, "hash", which has a nodeHash
    // as its data.
    NODE_DATA *     json_ParseFile(
        JSON_DATA		*this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     json_ToDebugString(
        JSON_DATA       *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* JSON_H */

