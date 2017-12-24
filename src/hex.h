// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          HEX Console Transmit Task (hex) Header
//****************************************************************
/*
 * Program
 *			Separate hex (hex)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate hex to run things without complications
 *          of interfering with the main hex. A hex may be 
 *          called a hex on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal hex. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	10/08/2016 Generated
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


#ifndef         HEX_H
#define         HEX_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct hex_data_s	HEX_DATA;    // Inherits from OBJ.

    typedef struct hex_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in hex_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(HEX_DATA *);
    } HEX_VTBL;



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
     @return:   pointer to hex object if successful, otherwise OBJ_NIL.
     */
    HEX_DATA *     hex_Alloc(
        void
    );
    
    
    OBJ_ID          hex_Class(
        void
    );
    
    
    HEX_DATA *     hex_New(
        void
    );
    
    
    uint8_t *        hex_DataFromJSONString(
        ASTR_DATA       *pString,
        uint32_t        *pLength
    );
    
    uint8_t *       hex_DataFromJSONStringA(
        const
        char            *pString,
        uint32_t        *pLength
    );
    
    
    ASTR_DATA *     hex_DataToJSON(
        uint32_t        length,
        uint8_t         *pData
    );
    
    
    /*!
     Convert 0-15 to an ascii character. For instance, 10 becomes 'a'.
     @return:   if successful, the converted character. Otherwise, '?' is returned.
     */
    char            hex_DigitToChrA(
        int             value
    );
    
    
    /*!
     Try to convert the ascii character (ie one hex digit) with format of
     "[0..9a..fA..F]" to an integer. For instance, 'a' or 'A' becomes 10.
     @return:   if successful, the converted number. Otherwise, -1 is returned.
     */
    int             hex_DigitToIntA(
        const
        char            chr
    );
    
    
    /*!
     Try to convert the string to a unsigned 32-bit number with format of 
     "[+ | -][0..9a..fA..F]*". Overflow is not detected in the scan.
     @return:
     if successful, the scanned number. Otherwise, 0 is returned if the number
     is malformed.
     */
    bool            hex_ScanUint32A(
        uint32_t        cLen,
        const
        char            *pInputBuffer,
        uint32_t        *pAmount
    );
    
    
    HEX_DATA *      hex_Shared(
        void
    );
    
    
    bool            hex_SharedReset(
        void
    );
    
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     hex_getLastError(
        HEX_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    HEX_DATA *   hex_Init(
        HEX_DATA     *this
    );


    /*!
        Convert 16 uint8_t to printable form at a time.
     Example:
     @code
        uint32_t   strlen = hex_putU8(this, 4);
     @endcode
     @param     this    HEX object pointer
     @param     offset  number to be displayed as the address/offset
     @return    If successful, ppBuffer is advanced past the outputted chars and
                *pLen is decremented. The value returned is the length of the
                data put in the buffer.
     */
    uint32_t        hex_put16Bytes_32(
        HEX_DATA		*this,
        uint32_t        offset,
        uint32_t        cData,
        const
        uint8_t         *pData,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // Ascii representation of digit stored
        //                                  // at ptr and ptr is advanced
    );
    
    uint32_t        hex_put16BytesObj_32(
        HEX_DATA		*this,
        uint32_t        offset,
        uint32_t        cData,
        const
        uint8_t         *pData,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    );
    
    uint32_t        hex_put16Bytes_64(
        HEX_DATA		*this,
        uint64_t        offset,
        uint32_t        cData,
        const
        uint8_t         *pData,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // Ascii representation of digit stored
        //                                  // at ptr and ptr is advanced
    );
    
    uint32_t        hex_put16BytesObj_64(
        HEX_DATA		*this,
        uint64_t        offset,
        uint32_t        cData,
        const
        uint8_t         *pData,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    );
    
    
    /*!
     Convert uint8_t to printable form.
     Example:
     @code
        uint32_t   strlen = hex_putU8A(this, 4);
     @endcode
     @param     this    HEX object pointer
     @param     input   number to be converted
     @return    If successful, ppBuffer is advanced past the outputted chars and
                *pLen is decremented. The value returned is the length of the
                data put in the buffer.
     */
    uint32_t        hex_putU8A(
        HEX_DATA		*this,
        uint8_t	        input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // Ascii representation of digit stored
        //                                  // at ptr and ptr is advanced
    );

    uint32_t        hex_putU8Obj(
        HEX_DATA		*this,
        uint8_t	        input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    );
    
    
    /*!
     Convert uint16_t to printable form.
     Example:
     @code
     uint32_t   strlen = hex_putU16A(this, 4);
     @endcode
     @param     this    HEX object pointer
     @param     input   number to be converted
     @return    If successful, ppBuffer is advanced past the outputted chars and
                *pLen is decremented. The value returned is the length of the
                data put in the buffer.
     */
    uint32_t        hex_putU16A(
        HEX_DATA		*this,
        uint16_t	    input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // Ascii representation of digit stored
        //                                  // at ptr and ptr is advanced
    );
    
    uint32_t        hex_putU16Obj(
        HEX_DATA		*this,
        uint16_t	    input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    );
    
    
    /*!
     Convert uint32_t (low 24-bits only) to printable form.
     Example:
     @code
     uint32_t   strlen = hex_putU24A(this, 4);
     @endcode
     @param     this    HEX object pointer
     @param     input   number to be converted
     @return    If successful, ppBuffer is advanced past the outputted chars and
                *pLen is decremented. The value returned is the length of the
                data put in the buffer.
     */
    uint32_t        hex_putU24A(
        HEX_DATA		*this,
        uint32_t	    input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // Ascii representation of digit stored
        //                                  // at ptr and ptr is advanced
    );
    
    uint32_t        hex_putU24Obj(
        HEX_DATA		*this,
        uint32_t	    input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    );
    
    
    /*!
     Convert  to printable form.
     Example:
     @code
     uint32_t   strlen = hex_putU32A(this, 4);
     @endcode
     @param     this    HEX object pointer
     @param     input   number to be converted
     @return    If successful, ppBuffer is advanced past the outputted chars and
                *pLen is decremented. The value returned is the length of the
                data put in the buffer.
     */
    uint32_t        hex_putU32A(
        HEX_DATA		*this,
        uint32_t	    input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // Ascii representation of digit stored
        //                                  // at ptr and ptr is advanced
    );
    
    uint32_t        hex_putU32Obj(
        HEX_DATA		*this,
        uint32_t	    input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    );
    
    
    /*!
     Convert  to printable form.
     Example:
     @code
     uint32_t   strlen = hex_putU64A(this, 4);
     @endcode
     @param     this    HEX object pointer
     @param     input   number to be converted
     @return    If successful, ppBuffer is advanced past the outputted chars and
                *pLen is decremented. The value returned is the length of the
                data put in the buffer.
     */
    uint32_t        hex_putU64A(
        HEX_DATA		*this,
        uint64_t	    input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // Ascii representation of digit stored
        //                                  // at ptr and ptr is advanced
    );
    
    uint32_t        hex_putU64Obj(
        HEX_DATA		*this,
        uint64_t	    input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = hex_ToDebugString(this,4);
     @endcode
     @param     this    HEX object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     hex_ToDebugString(
        HEX_DATA        *this,
        int             indent
    );
    
    
    ASTR_DATA *     hex_ToJSON(
        HEX_DATA        *this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* HEX_H */

