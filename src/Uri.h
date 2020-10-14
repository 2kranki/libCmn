// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//      Uniform Resource Identifier - RFC 3986 (Uri) Header
//****************************************************************
/*
 * Program
 *          Uniform Resource Identifier - RFC 3986 (Uri)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate Uri to run things without complications
 *          of interfering with the main Uri. A Uri may be 
 *          called a Uri on other O/S's.
 *
 *          A Uniform Resource Identifier (URI) provides a simple and extensible
 *          means for identifying a resource. This specification of URI syntax and
 *          semantics is derived from concepts introduced by the World Wide Web global
 *          information initiative, whose use of these identifiers dates from 1990 and
 *          is described in "Universal Resource Identifiers in WWW" [RFC1630]. The
 *          syntax is designed to meet the recommendations laid out in "Functional
 *          Recommendations for Internet Resource Locators" [RFC1736] and "Functional
 *          Requirements for Uniform Resource Names" [RFC1737]. (Taken from RFC3986)
 *
 * Remarks
 *  1.      None
 *
 * History
 *  10/13/2020 Generated
 */

/*
            Collected ABNF for URI (from RFC 3986)

 URI = scheme ":" hier-part [ "?" query ] [ "#" fragment ]

 hier-part = "//" authority path-abempty
            / path-absolute
            / path-rootless
            / path-empty

 URI-reference= URI / relative-ref

 absolute-URI = scheme ":" hier-part [ "?" query ]

 relative-ref = relative-part [ "?" query ] [ "#" fragment ]

 relative-part = "//" authority path-abempty
                / path-absolute
                / path-noscheme
                / path-empty

 scheme = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )

 authority = [ userinfo "@" ] host [ ":" port ]

 userinfo = *( unreserved / pct-encoded / sub-delims / ":" )

 host = IP-literal / IPv4address / reg-name

 port = *DIGIT

 IPv6address =
 h16
 ls32

 IP-literal = "[" ( IPv6address / IPvFuture ) "]"

 IPvFuture = "v" 1*HEXDIG "." 1 *( unreserved / sub-delims / ":" )
 IPv4address =                       6( h16 ":" ) ls32
              /                 "::" 5( h16 ":" ) ls32
              / [         h16 ] "::" 4( h16 ":" ) ls32
              / [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
              / [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
              / [ *3( h16 ":" ) h16 ] "::"
              / [ *4( h16 ":" ) h16 ] "::"
              / [ *5( h16 ":" ) h16 ] "::"
              / [ *6( h16 ":" ) h16 ] "::"

 h16 = 1*4HEXDIG

 ls32 = ( h16 ":" h16 ) / IPv4address

 IPv4address = dec-octet "." dec-octet "." dec-octet "." dec-octet

 dec-octet = DIGIT              ; 0-9
        / %x31-39 DIGIT         ; 10-99
        / "1" 2DIGIT            ; 100-199
        / "2" %x30-34 DIGIT     ; 200-249
        / "25" %x30-35          ; 250-255

 reg-name = *( unreserved / pct-encoded / sub-delims )

 path = path-abempty            ; begins with "/" or is empty
        / path-absolute         ; begins with "/" but not "//"
        / path-noscheme         ; begins with a non-colon segment
        / path-rootless         ; begins with a segment
        / path-empty            ; zero characters

 path-abempty = *( "/" segment )

 path-absolute = "/" [ segment-nz *( "/" segment ) ]

 path-noscheme = segment-nz-nc *( "/" segment )

 path-rootless = segment-nz *( "/" segment )

 path-empty = 0<pchar>

 segment = *pchar

 segment-nz = 1*pchar

 segment-nz-nc = 1*( unreserved / pct-encoded / sub-delims / "@" )
                ; non-zero-length segment without any colon ":"

 pchar = unreserved / pct-encoded / sub-delims / ":" / "@"

 query = *( pchar / "/" / "?" )

 fragment = *( pchar / "/" / "?" )

 pct-encoded = "%" HEXDIG HEXDIG

 unreserved = ALPHA / DIGIT / "-" / "." / "_" / "~"

 reserved = gen-delims / sub-delims

 gen-delims = ":" / "/" / "?" / "#" / "[" / "]"/ "@"

 sub-delims = "!" / "$" / "&" / "’" / "(" / ")"
                / "*" / "+" / "," / ";" / "="

 */

/*
 Parsing a URI Reference with a Regular Expression (from RFC 3986)

 ^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?
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


#ifndef         URI_H
#define         URI_H


//#define   URI_IS_IMMUTABLE     1
#define   URI_JSON_SUPPORT       1
//#define   URI_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Uri_data_s  URI_DATA;            // Inherits from OBJ
    typedef struct Uri_class_data_s URI_CLASS_DATA;   // Inherits from OBJ

    typedef struct Uri_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Uri_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(URI_DATA *);
    } URI_VTBL;

    typedef struct Uri_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Uri_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(URI_DATA *);
    } URI_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  URI_SINGLETON
    URI_DATA *     Uri_Shared (
        void
    );

    void            Uri_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Uri object if successful, otherwise OBJ_NIL.
     */
    URI_DATA *     Uri_Alloc (
        void
    );
    
    
    OBJ_ID          Uri_Class (
        void
    );
    
    
    URI_DATA *     Uri_New (
        void
    );
    
    
#ifdef  URI_JSON_SUPPORT
    URI_DATA *   Uri_NewFromJsonString (
        ASTR_DATA       *pString
    );

    URI_DATA *   Uri_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ASTR_DATA * Uri_getAuthority (
        URI_DATA     *this
    );

    bool        Uri_setAuthority (
        URI_DATA     *this,
        ASTR_DATA   *pValue
    );


    ASTR_DATA * Uri_getFragment (
        URI_DATA     *this
    );

    bool        Uri_setFragment (
        URI_DATA     *this,
        ASTR_DATA   *pValue
    );


    ASTR_DATA * Uri_getPath (
        URI_DATA     *this
    );

    bool        Uri_setPath (
        URI_DATA     *this,
        ASTR_DATA   *pValue
    );


    ASTR_DATA * Uri_getScheme (
        URI_DATA     *this
    );

    bool        Uri_setScheme (
        URI_DATA     *this,
        ASTR_DATA   *pValue
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     Uri_Disable (
        URI_DATA       *this
    );


    ERESULT     Uri_Enable (
        URI_DATA       *this
    );

   
    URI_DATA *   Uri_Init (
        URI_DATA     *this
    );


    ERESULT     Uri_IsEnabled (
        URI_DATA       *this
    );
    
 
#ifdef  URI_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Uri_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Uri_ToJson (
        URI_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Uri_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Uri_ToDebugString (
        URI_DATA     *this,
        int             indent
    );
    
    
    ASTR_DATA *     Uri_ToString (
        URI_DATA        *this
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* URI_H */

