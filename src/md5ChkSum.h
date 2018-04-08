// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          MD5CHKSUM Console Transmit Task (md5ChkSum) Header
//****************************************************************
/*
 * Program
 *			Separate md5ChkSum (md5ChkSum)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate md5ChkSum to run things without complications
 *          of interfering with the main md5ChkSum. A md5ChkSum may be 
 *          called a md5ChkSum on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/01/2018 Generated
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
#include        <value.h>


#ifndef         MD5CHKSUM_H
#define         MD5CHKSUM_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct md5ChkSum_data_s	MD5CHKSUM_DATA;    // Inherits from OBJ.

    typedef struct md5ChkSum_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in md5ChkSum_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MD5CHKSUM_DATA *);
    } MD5CHKSUM_VTBL;



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
     @return    pointer to md5ChkSum object if successful, otherwise OBJ_NIL.
     */
    MD5CHKSUM_DATA * md5ChkSum_Alloc(
        void
    );
    
    
    OBJ_ID          md5ChkSum_Class(
        void
    );
    
    
    MD5CHKSUM_DATA * md5ChkSum_New(
        void
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
    ERESULT         md5ChkSum_ParseDigest(
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
    uint8_t *       md5ChkSum_getDigest(
        MD5CHKSUM_DATA  *this
    );
    
    
    ERESULT         md5ChkSum_getLastError(
        MD5CHKSUM_DATA  *this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Finalize the md5 check sum calculation generating the digest.
     @param     this        MD5CHKSUM object pointer
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
    ERESULT         md5ChkSum_Finalize(
        MD5CHKSUM_DATA	*this,
        PATH_DATA       *pPath,         // (in) Optional File Path
        ASTR_DATA       **ppOutput      // (out) Optional MD5 String
    );

   
    /*!
     Process the given file path generating the md5 check sum and optionally
     generating the digest string for that file path.
     @param     this        MD5CHKSUM object pointer
     @param     pPath       File Path of file to be calculated
     @param     ppOutput    Optional pointer to an ASTR pointer where
                            a new MD5 Digest ASTR is returned.
     @return    If successful, ERESULT_SUCCESS and an optional MD5 ASTR.
                Otherwise, an ERESULT_* error code.
     @warning   Remember to release the returned ppOutput AStr object.
     */
    ERESULT         md5ChkSum_FromUtf8File(
        MD5CHKSUM_DATA  *this,
        PATH_DATA       *pPath,         // (in) File Path
        ASTR_DATA       **ppOutput      // (out) Optional MD5 String
    );
    
    
    MD5CHKSUM_DATA * md5ChkSum_Init(
        MD5CHKSUM_DATA  *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = md5ChkSum_ToDebugString(this,4);
     @endcode 
     @param     this    MD5CHKSUM object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA * md5ChkSum_ToDebugString(
        MD5CHKSUM_DATA  *this,
        int             indent
    );
    
    
    /*!
     Update the checksum with more data. This method should be called as many times
     as needed. The data order is important.
     @param     this    MD5CHKSUM object pointer
     @param     pData   Pointer to data to be check summed
     @param     len     length of area pointed to by pData
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error code.
     */
    ERESULT         md5ChkSum_Update(
        MD5CHKSUM_DATA  *this,
        const
        uint8_t         *pData,
        uint32_t        len
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MD5CHKSUM_H */

