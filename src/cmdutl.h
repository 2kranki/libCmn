// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Command Utilities (cmdutl) Header
//****************************************************************
/*
 * Program
 *			Command Utilities (cmdutl)
 * Purpose
 *			This object provides a standardized way of parsing or
 *          constructing CMDUTL data.
 *
 *          cmdline : string arg*       // First string is program path
 *                  ;
 *          arg     : ws* (name ('=' value)? | string ('=' value) | number)
 *                  ;
 *          object  : '{' ws* value (',' ws* value)* ws* '}'
 *                  ;
 *          value   : name | string | number
 *                  ;
 *          name    : [a-zA-Z][a-zA-Z0-9_]
 *                  ;
 *          ws      : ' ' | '\b' | '\f' | '\n' | '\r' | '\t'
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
#include        <node.h>
#include        <false.h>
#include        <null.h>
#include        <path.h>
#include        <true.h>
#include        <AStr.h>


#ifndef         CMDUTL_H
#define         CMDUTL_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


#ifndef         CMDUTL_FIELD_MAX
#define         CMDUTL_FIELD_MAX  512
#endif

    
    typedef struct cmdutl_data_s	CMDUTL_DATA;


    typedef struct cmdutl_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        
        // Properties:
        
        // Methods:
        
    } CMDUTL_VTBL;
    
    
    
        


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    CMDUTL_DATA *   cmdutl_Alloc(
        void
    );
    
    
    WSTR_DATA *     cmdutl_ConvertArgcToWStr(
        int             argc,
        const
        char            *argv[]
    );
    
    
    CMDUTL_DATA *   cmdutl_NewAStr(
        ASTR_DATA       *pSzStr,        // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    );
    
    CMDUTL_DATA *   cmdutl_NewWStr(
        WSTR_DATA       *pSzStr,        // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    );
    
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NODEHASH_DATA * cmdutl_getFileObject(
        CMDUTL_DATA     *this
    );
    
    
    PATH_DATA *     cmdutl_getPath(
        CMDUTL_DATA     *this
    );

    bool            cmdutl_setPath(
        CMDUTL_DATA     *this,
        PATH_DATA       *pValue
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    CMDUTL_DATA *     cmdutl_InitFile(
        CMDUTL_DATA     *this,
        PATH_DATA       *pFilePath,
        uint16_t        tabSize                 // Tab Spacing if any
    );
    
    CMDUTL_DATA *     cmdutl_InitAStr(
        CMDUTL_DATA     *this,
        ASTR_DATA       *pAStr,         // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    );
    
    CMDUTL_DATA *     cmdutl_InitWStr(
        CMDUTL_DATA     *this,
        WSTR_DATA       *pWStr,         // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    );
    
    
    NODE_DATA *     cmdutl_ParseFile(
        CMDUTL_DATA		*this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     cmdutl_ToDebugString(
        CMDUTL_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* CMDUTL_H */

