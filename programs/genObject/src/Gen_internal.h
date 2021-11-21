// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Gen_internal.h
 *	Generated 05/05/2020 09:59:00
 *
 * Notes:
 *  --	N/A
 *
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




#include        <Gen.h>
#include        <JsonIn.h>
#include        <TextIn.h>
#include        <TextOut.h>


#ifndef GEN_INTERNAL_H
#define	GEN_INTERNAL_H





#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Gen_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        rsvd16;
    DICT_DATA       *pDict;
    const
    char            *pModelDrvDirA;
    const
    char            *pOutputDrvDirA;

    void            (*pMsgInfo)(
        APPL_DATA       *this,
        const
        char            *fmt,
        ...
    );
    void            (*pMsgWarn)(
        APPL_DATA       *this,
        uint16_t        iVerbose,
        const
        char            *fmt,
        ...
    );
    OBJ_ID          pMsgObj;
};
#pragma pack(pop)

    extern
    struct Gen_class_data_s  Gen_ClassObj;

    extern
    const
    GEN_VTBL         Gen_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  GEN_SINGLETON
    GEN_DATA *      Gen_getSingleton (
        void
    );

    bool            Gen_setSingleton (
        GEN_DATA        *pValue
    );
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Gen_getSuperVtbl (
        GEN_DATA        *this
    );


    ERESULT         Gen_Assign (
        GEN_DATA        *this,
        GEN_DATA        *pOther
    );


    GEN_DATA *       Gen_Copy (
        GEN_DATA        *this
    );


    PATH_DATA *     Gen_CreateModelPath (
        GEN_DATA        *this,
        ASTR_DATA       *pModelFileName
    );


    PATH_DATA *     Gen_CreateOutputPath (
        GEN_DATA        *this,
        const
        char            *pSubDirA,
        const
        char            *pSuffixA
    );


    void            Gen_Dealloc (
        OBJ_ID          objId
    );


    /*!
     Delete the output files if they exist.
     @param this        Object Pointer
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Gen_DeleteObjectFiles (
        GEN_DATA        *this
    );


    ERESULT         Gen_ExpandData (
        GEN_DATA        *this,
        TEXTIN_DATA     *pInput,
        TEXTOUT_DATA    *pOutput,
        uint32_t        *pCnt
    );


    ERESULT         Gen_ExpandVars(
        GEN_DATA        *this,
        ASTR_DATA       *pInOut
    );


    /*!
     Return a header comment line as used in headings where the
     line is a single line comment followed by a fixed number of
     chr's.
     @param     this        object pointer
     @param     fAddOffset  true == prefix line with "\t"
     @param     chrW32      the character to appeend after the
                            single-line comment. Normally, this
                            is '*', '-' or '='.
     @return    if successful, an AStr object containing the header line.
                Otherwise, OBJ_NIL.
     */
    ASTR_DATA *     Gen_HeaderLine(
        GEN_DATA        *this,
        bool            fAddOffset,
        W32CHR_T        chrW32
    );


#ifdef  GEN_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    GEN_DATA *      Gen_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Gen_ParseJsonFields (
        JSONIN_DATA     *pParser,
        GEN_DATA        *pObject
    );
#endif


    int             Gen_PreProcBoolEval (
        GEN_DATA        *this,
        char            *z,
        int             lineno
    );


    /*!
     Run the preprocessor over the input file text.  The global variables
     azDefine[0] through azDefine[nDefine-1] contains the names of all defined
     macros.  This routine looks for "%ifdef" and "%ifndef" and "%endif" and
     comments them out.  Text in between is also commented out as appropriate.
     The initial version of this preprocessor was taken from "lemon" by
     by Richard Hipp which is part of SQLite, a great SQL tool. SQLite and
     this code was placed in the Public Domain by its author.
     @param     this    object pointer
     @param     z       a NUL-terminated character string containing all lines
                        of text that need to be scanned. On output, the lines
                        that need to be removed will be replaced with blank
                        lines including the %ifdef, %if, %ifndef, %else and
                        %endif lines.
     @return    If succesful, an AStr object which has the lines not needed
                removed.
    */
    ASTR_DATA *     Gen_PreprocInput (
        GEN_DATA        *this,
        char            *z
    );


    void *          Gen_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    /*!
     Return a spaced comment line as used in headings where each
     comment character is followed by a space and the comment is
     centered.
     @param     this    object pointer
     @param     pStrA   UTF-8 Comment to be spaced
     @return    if successful, an AStr object containing the header line.
                Otherwise, OBJ_NIL.
     */
    ASTR_DATA *     Gen_SpacedComment(
        GEN_DATA        *this,
        const
        char            *pStrA
    );


#ifdef  GEN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Gen_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Gen_ToJson (
        GEN_DATA        *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Gen_ToJsonFields (
        GEN_DATA        *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			Gen_Validate (
        GEN_DATA        *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* GEN_INTERNAL_H */

