// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  MD5 Check Sum Support (ChkSumMD5) Header
//****************************************************************
/*
 * Program
 *          MD5 Check Sum Support (ChkSumMD5)
 * Purpose
 *          This object provides support for calculating MD5 checksums.
 *          The normal usage is to create a new object, ChkSumMD5,
 *          pass blocks of data to Update() and then finalize the
 *          result with Finalize().  If you need to do more than 1
 *          calculation, you can issue Restart() to reset the MD5
 *          calculation engine.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  11/21/2021 Renerated from md5ChkSum and changed calculation
 *          engines from md5_plumb to md5. Both are public domain.
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
#include        <Value.h>


#ifndef         CHKSUMMD5_H
#define         CHKSUMMD5_H


//#define   CHKSUMMD5_IS_IMMUTABLE     1
#define   CHKSUMMD5_JSON_SUPPORT       1
//#define   CHKSUMMD5_SINGLETON        1
//#define       CHKSUMMD5_MSGS   1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ChkSumMD5_data_s  CHKSUMMD5_DATA;          // Inherits from CHKSUMMD5
    typedef struct ChkSumMD5_class_data_s CHKSUMMD5_CLASS_DATA;  // Inherits from OBJ

    typedef struct ChkSumMD5_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //ChkSumMD5_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ChkSumMD5_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CHKSUMMD5_DATA *);
    } CHKSUMMD5_VTBL;

    typedef struct ChkSumMD5_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ChkSumMD5_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CHKSUMMD5_DATA *);
    } CHKSUMMD5_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  CHKSUMMD5_SINGLETON
    CHKSUMMD5_DATA * ChkSumMD5_Shared (
        void
    );

    void            ChkSumMD5_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ChkSumMD5 object if successful, otherwise OBJ_NIL.
     */
    CHKSUMMD5_DATA * ChkSumMD5_Alloc (
        void
    );
    
    
    OBJ_ID          ChkSumMD5_Class (
        void
    );
    
    
    CHKSUMMD5_DATA * ChkSumMD5_New (
        void
    );
    
    
#ifdef  CHKSUMMD5_JSON_SUPPORT
    CHKSUMMD5_DATA * ChkSumMD5_NewFromJsonString (
        ASTR_DATA       *pString
    );

    CHKSUMMD5_DATA * ChkSumMD5_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


    CHKSUMMD5_DATA * ChkSumMD5_NewFromUtf8File(
        PATH_DATA       *pPath
    );


    /*!
     Parse a UTF-8 Input string generating the file path and digest from it.
     @param     pInput      Input string to be parsed
     @param     ppPath      Pointer to File Path to be returned optionally
                            (Use OBJ_NIL if not needed.)
     @param     ppDigest    Optional pointer to an Value object to be
                            returned. (Used OBJ_NIL if not needed.)
     @return    If successful, ERESULT_SUCCESS and optionally a path and/or
                digest objects.  Otherwise, an ERESULT_* error code.
     @warning   Remember to release the returned path and value objects if
                present.
     */
    ERESULT         ChkSumMD5_ParseDigest(
        ASTR_DATA       *pInput,
        PATH_DATA       **ppPath,
        VALUE_DATA      **ppDigest
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     digest is 16 bytes long md5 check sum.
     */
    uint8_t *       ChkSumMD5_getDigest(
        CHKSUMMD5_DATA  *this
    );


    ASTR_DATA *     ChkSumMD5_getStrMD5(
        CHKSUMMD5_DATA  *this
    );


#ifdef CHKSUMMD5_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            ChkSumMD5_setMsgs (
        CHKSUMMD5_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Finalize the md5 check sum calculation generating the digest.
     @param     this        object pointer
     @param     pPath       an optional file name that is used to
                            generate the MD5 output string.  This is
                            required if the MD5 output string is being
                            generated.  Otherwise, it is not needed.
     @param     ppOutput    Optional pointer to an ASTR pointer where
                            a new MD5 Digest ASTR is returned.
     @return    If successful, ERESULT_SUCCESS and an optional MD5 ASTR.
                Otherwise, an ERESULT_* error code.
     @warning   Remember to release the returned ppOutput AStr object.
     */
    ERESULT         ChkSumMD5_Finalize(
        CHKSUMMD5_DATA  *this,
        PATH_DATA       *pPath,         // (in) Optional File Path
        ASTR_DATA       **ppOutput      // (out) Optional MD5 String
    );


    /*!
     Process the given file path generating the md5 check sum and optionally
     generating the digest string for that file path.
     @param     this        object pointer
     @param     pPath       File Path of file to be calculated
     @param     ppOutput    Optional pointer to an ASTR pointer where
                            a new MD5 Digest ASTR is returned.
     @return    If successful, ERESULT_SUCCESS and an optional MD5 ASTR.
                Otherwise, an ERESULT_* error code.
     @warning   Remember to release the returned ppOutput AStr object.
     */
    ERESULT         ChkSumMD5_FromUtf8File(
        CHKSUMMD5_DATA  *this,
        PATH_DATA       *pPath,         // (in) File Path
        ASTR_DATA       **ppOutput      // (out) Optional MD5 String
    );


    CHKSUMMD5_DATA *   ChkSumMD5_Init (
        CHKSUMMD5_DATA     *this
    );


    /*!
     Restart the MD5 calculation engine to process another MD5 calculation.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ChkSumMD5_Restart (
        CHKSUMMD5_DATA  *this
    );


#ifdef  CHKSUMMD5_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ChkSumMD5_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ChkSumMD5_ToJson (
        CHKSUMMD5_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ChkSumMD5_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ChkSumMD5_ToDebugString (
        CHKSUMMD5_DATA  *this,
        int             indent
    );
    
    
    /*!
     Update the checksum with more data. This method should be called as many times
     as needed. The data order is important.
     @param     this    Mobject pointer
     @param     pData   Pointer to data to be check summed
     @param     len     length of area pointed to by pData
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error code.
     */
    ERESULT         ChkSumMD5_Update(
        CHKSUMMD5_DATA  *this,
        const
        uint8_t         *pData,
        uint32_t        len
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* CHKSUMMD5_H */

