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
 *          HJSON is a relaxed form of JSON.  JSON data is accepted,
 *          as well as a less formal syntax. (See the BNF below.)
 *          Our form of HJSON is based on the formal definition
 *          that can be found on the internet.  However, we have
 *          modified it slightly for our own purposes.
 *
 *          ParseFileHash() parses JSON text that has a hash at
 *          the highest level, '{'...'}'.  This is the normal
 *          language definition.  ParseFileValue() can be used
 *          to parse JSON starting at 'value' rule in the grammar
 *          below if the highest level is not necessarily a hash.
 *          A hash or array is always returned in the data of a
 *          node whose name is "array" or "hash".  Likewise, the
 *          keywords, null, true and false, are always returned
 *          as a data object of null, true or false of a node
 *          whose name is the same keyword of "null", "true" or
 *          "false"
 *
 *          If errors occur in the parse, the shared object for
 *          srcErrors will contain those error descriptions. So,
 *          "SrcErrors_Print(OBJ_NIL);" will print the errors on
 *          stderr.  "SrcErrors_ExitOnFatal(OBJ_NIL);" will print
 *          the errors and then exit if any fatal errors occurred.
 *          See srcErrors.h for more information.
 *
 *          The output of this parsing can be determined by looking
 *          at the grammar below. The output is nodes with specific
 *          names and the node data being the provide data object.
 *          The highest node should be a "hash" nodes.
 *
 * Remarks
 *	1.      I changed the definition of the quoteless string to end
 *          with '\n' and any of '{','}','[',']',':',','. This al-
 *          lows it to be used for object names as well as quote-
 *          less strings. If any of those characters needs to be
 *          added to a string, then simply quote the string.
 *  2.      We do not support multi-line strings at this point.
 *  3.      A data node's extra field will contain the SrcLoc Object
 *          defining the start of the data in the source file.
 *
 * History
 *	07/08/2017 Generated
 *  10/08/2018 Changed to allow empty arrays and hashes.
 *  11/26/2019 Added SrcLoc object to data node's extra field.
 *  08/26/2021 Fixed multiple strings in the value of a pair to
 *              not concatenate if the following token is ':'
 *              indicating that it was a name without a separating
 *              comma.
 */


/*                  OUR HJSON BNF
 
 BNF Suffixes:
    ? == 0 or 1 repetition
    + == 1 or more repetitions
    * == 0 or more repetitions
 
 
 
 object     :   '{' members '}'             <= OBJ_IDENT_NODE("hash") -> (data) OBJ_IDENT_NODEHASH
            ;
 members    :   pair ((',' | '\n') pair?)*
            |
            ;
 pair       :   (string | quoteless-string) (':' | '=') value
                                            <= OBJ_IDENT_NODE(name string) -> (data) value node (see below)
            ;
 array      :   '[' elements ']'            <= OBJ_IDENT_NODE("array") -> (data) OBJ_IDENT_NODEARRAY
            ;
 elements   :   value (',' value)*
            |
            ;
 value      :   string                      <= OBJ_IDENT_NODE("string") -> (data) OBJ_IDENT_ASTR
            |   number                      <= OBJ_IDENT_NODE("integer") -> (data) OBJ_IDENT_ASTR
            |   object                      <= OBJ_IDENT_NODE("hash") -> (data) OBJ_IDENT_NODEHASH
            |   array                       <= OBJ_IDENT_NODE("array") -> (data) OBJ_IDENT_NODEARRAY
            |   "true"                      <= OBJ_IDENT_NODE("true") -> (data) OBJ_IDENT_TRUE
            |   "false"                     <= OBJ_IDENT_NODE("false") -> (data) OBJ_IDENT_FALSE
            |   "null"                      <= OBJ_IDENT_NODE("null") -> (data) OBJ_IDENT_NULL
            ;
 string     :   '"' char* '"'
            ;
 quoteless-string
            :   any-Unicode-char-except-','-':'-'='-'['-']'-'{'-or-'}'+
            ;
 char       :   any-Unicode-char-except-'"'-or-'\'-or-control-char
            |   "\""
            |   "\\"
            |   "\/"
            |   "\b"
            |   "\f"
            |   "\n"
            |   "\r"
            |   "\t"
            |   "\u" four-hex-digits
            ;
 number     :   int
            |   int frac
            |   int exp
            |   int frac exp
            ;
 int        :   digit
            |   digit digit*
            |   '-' digit
            |   '-' digit digit*
            ;
 frac       :   '.' digit*
            ;
 exp        :   e digit*
            ;
 digit      :   '1'..'9'
            ;
 e          :   ('e' 'E') ('+' | '-')?
            ;
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
#include        <Node.h>
#include        <False.h>
#include        <Null.h>
#include        <Path.h>
#include        <True.h>


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
        void
    );
    
    
    HJSON_DATA *    hjson_NewA(
        const
        char            *pSzStr,        // Buffer of file data
        uint16_t        tabSize         // Tab Spacing if any
    );
    
    
    HJSON_DATA *    hjson_NewAStr(
        ASTR_DATA       *pSzStr,        // Buffer of file data
        uint16_t		tabSize         // Tab Spacing if any
    );
    
    
    HJSON_DATA *    hjson_NewFromFile(
        FILE            *pFile,         // Input File
        uint16_t		tabSize         // Tab Spacing if any
    );
    
    
    HJSON_DATA *    hjson_NewFromPath(
        PATH_DATA       *pPath,         // Input File Path
        uint16_t		tabSize         // Tab Spacing if any
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NODEHASH_DATA * hjson_getFileObject(
        HJSON_DATA      *this
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
        FILE            *pFile,         // Input File
        uint16_t        tabSize         // Tab Spacing if any
    );
    
    HJSON_DATA *    hjson_InitPath(
        HJSON_DATA       *this,
        PATH_DATA       *pFilePath,
        uint16_t        tabSize         // Tab Spacing if any
    );
    
    
    /*!
     Parse the input file assuming that it is a JSON Hash, ('{'...'}'), is
     at the highest level. Insure that srcErrors is reset before calling this.
     @param     this    HJSON object pointer
     @return    If successful, a Hash Node object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned Hash Node object.
     */
    NODE_DATA *     hjson_ParseFileHash(
        HJSON_DATA		*this
    );
    
    
    /*!
     Parse the input file assuming that it is a JSON value as given in
     the grammar above.  You must test the object returned to determine
     what type that it is (Node, Node Array, Node Hash, True, False, Null).
     @param     this    HJSON object pointer
     @return    If successful, a Node object or Node Collection which
                must be released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODE_DATA *     hjson_ParseFileValue(
        HJSON_DATA        *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = hjson_ToDebugString(this,4);
     @endcode
     @param     this    HJSON object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    hjson_ToDebugString(
        HJSON_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* HJSON_H */

