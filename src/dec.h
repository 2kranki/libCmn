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
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal dec. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
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

    DEC_DATA *     dec_Alloc(
    );
    
    
    DEC_DATA *     dec_New(
    );
    
    
    // getInt32() tries to convert the string to a signed 32-bit
    // number with format [+ | -][0..9]*
    // 0 is returned if the number is mal-formed and overflow is
    // not checked.
    int32_t          dec_getInt32A(
        const
        char            *pStr
    );
    
    int32_t          dec_getInt32W(
        const
        uint32_t        *pStr
    );
    
    int64_t          dec_getInt64A(
        const
        char             *pStr
    );
    
    
    /*!
     @param:    pLen    buffer len ptr (len must be greater than 0)
     @param:    ppBuffer buffer ptr (12 bytes required minimum)
     @return:
     if successful, buffer will contain ascii representation of number
     with leading zeros and trailing NUL char. First byte will be '-'
     for negative value or ' '.
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
     @param:    pLen    buffer len ptr (len must be greater than 0)
     @param:    ppBuffer buffer ptr (22 bytes required minimum)
     @return:
     if successful, buffer will contain ascii representation of number
     with leading zeros and trailing NUL char. First byte will be '-'
     for negative value or ' '.
     */
    void            dec_putInt64A(
        int64_t			input,
        uint32_t        *pLen,              // Remaining length of buffer
        //                                  // (Decremented if char added)
        char            **ppBuffer          // buffer ptr which will be advanced
    );
    
    void            dec_putInt64AObj(
        int64_t			input,
        void            *pObject,
        bool            (*pPutChar)(void *, uint8_t)
    );
    
    
    /*!
     @param:    pLen    buffer len ptr (len must be greater than 0)
     @param:    ppBuffer buffer ptr (11 bytes required minimum)
     @return:
     if successful, buffer will contain ascii representation of number
     with leading zeros and trailing NUL char.
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
     @param:    pLen    buffer len ptr (len must be greater than 0)
     @param:    ppBuffer buffer ptr (21 bytes required minimum)
     @return:
                if successful, buffer will contain ascii representation of number
                with leading zeros and trailing NUL char.
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
     @code:
        ASTR_DATA      *pDesc = dec_ToDebugString(this,4);
     @endcode:
     @param:    this    DEC object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    dec_ToDebugString(
        DEC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DEC_H */

