// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          DEC Console Transmit Task (dec) Header
//****************************************************************
/*
 * Program
 *			Separate dec (dec)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate dec to run things without complications
 *          of interfering with the main dec. A dec may be 
 *          called a dec on other O/S's.
 *
 * Remarks
 *	1.      uint64_t values are 0 to 18,446,744,073,709,551,615.
 *          int64_t values are -9,223,372,036,854,775,808 to
 *                              9,223,372,036,854,775,807.
 *
 * History
 *	02/12/2017 Generated
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


#ifndef         DEC_H
#define         DEC_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct dec_data_s	DEC_DATA;    // Inherits from OBJ.

    typedef struct dec_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in dec_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DEC_DATA *);
    } DEC_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    DEC_DATA *      dec_Alloc(
        void
    );
    
    
    DEC_DATA *      dec_New(
        void
    );
    
    
    ERESULT         dec_UInt64FromJSONString(
        ASTR_DATA       *pString,
        uint64_t        *pData
    );
    
    ERESULT         dec_UInt64FromJSONStringA(
        const
        char            *pString,
        uint64_t        *pData
    );
    

    /*!
     Try to convert the string to a signed 32-bit number with format [+ | -]?[0..9]+
     @return:
             if successful, the scanned number. Otherwise, 0 is returned if the number
             is malformed.
     @Warning:
            Overflow is not checked.
     */
    int32_t         dec_getInt32A(
        const
        char            *pStr
    );
    
    uint32_t        dec_getUint32A(
        const
        char            *pStr
    );
    
    int32_t         dec_getInt32W32(
        const
        W32CHR_T        *pStr
    );
    
    int64_t         dec_getInt64A(
        const
        char             *pStr
    );
    
    uint64_t        dec_getUint64A(
        const
        char             *pStr
    );
    

    void            dec_Int32ToChr(
        int32_t			input,
        char            *pBuffer			// On return, will have
        //                                  // Ascii representation of
        //                                  // number with leading zeros
        //                                  // and trailing NUL char.
        //                                  // (12-bytes required)
    );
    
    
    void            dec_Int64ToChr(
        int64_t			input,
        char            *pBuffer			// On return, will have
        //                                  // Ascii representation of
        //                                  // number with leading zeros
        //                                  // and trailing NUL char.
        //                                  // (22-bytes required)
    );
    
    
    /*!
     If successful, buffer will contain ascii representation of number
     with leading zeros and trailing NUL char. First byte will be '-'
     for negative value or ' '.
     @param     pLen    buffer len ptr (len must be greater than 0)
     @param     ppBuffer buffer ptr (12 bytes required minimum)
     */
    void            dec_putInt32A(
        int32_t			input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // buffer ptr which will be advanced
    );
    
    void            dec_putInt32AObj(
        int32_t			input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    );
    
    
    /*!
     If successful, buffer will contain ascii representation of number
     with leading zeros and trailing NUL char. First byte will be '-'
     for negative value or ' '.
     @param     pLen    buffer len ptr (len must be greater than 0)
     @param     ppBuffer buffer ptr (22 bytes required minimum)
     */
    void            dec_putInt64A(
        int64_t			input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // buffer ptr which will be advanced
    );
    
    /*!
     Format an int16_t with or without leading zeroes and with an implied
     decimal point if needed.
     @param     pLen    buffer len ptr (len must be greater than 0)
     @param     ppBuffer buffer ptr (11 bytes required minimum)
     @return    If successful, buffer will contain ascii representation of number
                with leading zeros and trailing NUL char.
     */
    bool            dec_putInt64DecA(
        int64_t         input,
        int8_t          sign,               // -1 == leading, 0 == none, 1 == trailing
        bool            fAlignRight,        // false == left, true == right
        bool            fZeroFill,          // false == space fill, true == zero fill
        uint8_t         width,              // total field width
        uint8_t         dec,                // decimal point position
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char           **ppBuffer           // buffer ptr which will be advanced
    );
    
    void            dec_putInt64AObj(
        int64_t			input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    );
    
    bool            dec_putUint64DecA(
        uint64_t        input,
        bool            fAlignRight,        // false == left, true == right
        bool            fZeroFill,          // false == space fill, true == zero fill
        uint8_t         width,              // total field width
        uint8_t         dec,                // decimal point position
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // buffer ptr which will be advanced
    );
    

    /*!
     If successful, buffer will contain ascii representation of number
     with leading zeros and trailing NUL char.
     @param     pLen    buffer len ptr (len must be greater than 0)
     @param     ppBuffer buffer ptr (11 bytes required minimum)
     */
    void            dec_putUint32A(
        uint32_t		input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // buffer ptr which will be advanced
    );
    
    void            dec_putUint32AObj(
        uint32_t		input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    );
    
    
    /*!
     If successful, buffer will contain ascii representation of number
     with leading zeros and trailing NUL char.
     @param     pLen    buffer len ptr (len must be greater than 0)
     @param     ppBuffer buffer ptr (21 bytes required minimum)
     */
    void            dec_putUint64A(
        uint64_t        input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // buffer ptr which will be advanced
    );
    
    void            dec_putUint64AObj(
        uint64_t        input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    );
    
    
    void            dec_Uint32ToChr(
        uint32_t        input,
        char            *pBuffer			// On return, will have
        //                                  // Ascii representation of
        //                                  // number with leading zeros
        //                                  // and trailing NUL char.
        //                                  // (11-bytes required)
    );
    
    
    void            dec_Uint64ToChr(
        uint64_t        input,
        char            *pBuffer			// On return, will have
        //                                  // Ascii representation of
        //                                  // number with leading zeros
        //                                  // and trailing NUL char.
        //                                  // (21-bytes required)
    );
    
    
    ASTR_DATA *     dec_UInt64ToJSON(
        uint64_t        data
    );
    
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     dec_getLastError(
        DEC_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     dec_Disable(
        DEC_DATA		*this
    );


    ERESULT     dec_Enable(
        DEC_DATA		*this
    );

   
    DEC_DATA *   dec_Init(
        DEC_DATA     *this
    );


    ERESULT     dec_IsEnabled(
        DEC_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = dec_ToDebugString(this,4);
     @endcode
     @param     this    DEC object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    dec_ToDebugString(
        DEC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DEC_H */

