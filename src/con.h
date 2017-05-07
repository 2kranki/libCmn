// vi:nu:et:sts=4 ts=4 sw=4
//****************************************************************
//              Console I/O (con) Support  Header
//****************************************************************
/*
 * Program
 *				Console I/O (con) Subroutines
 * Purpose
 *				These subroutines provide a general purpose set of
 *				routines to provide support for console I/O. These
 *				are primitive compared to making them posix.
 *              receivers.
 *
 *
 * Remarks
 *	1.			XC32 allows 4 register variables per function call.
 *	            So, we will restrict most function calls to 4 or less.
 *
 * History
 *	10/26/2014	Created from scratch.
 * References
 *		"Data Structures and Algorithms", Alfred V. Aho et al,
 *			Addison-Wesley, 1985
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




#include    <cmn_defs.h>
#include    <ascii.h>
#include    <chario.h>


#ifndef CON_H
#define	CON_H   1



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

typedef struct con_data_s	CON_DATA;

    typedef struct con_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        
        // Properties:
        
        // Methods:
        
    } CON_VTBL;
    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates a string with max length of 'size'.
     */
    CON_DATA *     con_Alloc(
        uint16_t        size
    );
    
    
    CON_DATA *     con_New(
        uint16_t        size
    );
    
    
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /* Insert CR to a LF without a preceding CR on output.
     * (Default is TRUE.)
     */
    bool            con_getAddCR2SingletonLF(
        CON_DATA        *this
    );

    void            con_setAddCR2SingletonLF(
        CON_DATA        *this,
        bool            data
    );


    /*  Add LF to each CR on output.
     */
    bool            con_getAddLF2CR(
        CON_DATA        *this
    );

    void            con_setAddLF2CR(
        CON_DATA        *this,
        bool            data
    );


    bool            con_getEcho(
        CON_DATA        *this
    );

    void            con_setEcho(
        CON_DATA        *this,
        bool            data
    );


    CHARIO_DATA *   con_getCharIO(
        CON_DATA        *this
    );

    void            con_setCharIO(
        CON_DATA        *this,
        CHARIO_DATA     *pCharIO
    );


    bool            con_getUseXonXoff(
        CON_DATA        *this
    );

    void            con_setUseXonXoff(
        CON_DATA        *this,
        bool            data
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Get the next character.
     @return:   character, otherwise -1.
     */
    char            con_In(
        CON_DATA        *this,
        uint32_t        timeout
    );


    /* con_InCString collects a string interpreting
     * certain characters:
     *      Backspace or Delete -- Erase last character
     *      CR - prints CR/LF and returns string.
     *
     * Returns: an umm_malloc'd area which must be
     *          freed with umm_free.
     */
    bool            con_InCString(
        CON_DATA        *this,
        uint16_t        cLenMax,
        uint16_t        *cLen,
        char            *pBufferIn,
        uint32_t        timeout
    );


    // Init() initializes the control blocks for
    // this object. The size should be the same
    // as was passed to Alloc().
    CON_DATA *      con_Init(
        CON_DATA        *this
    );
    
    
    bool            con_Lock(
        CON_DATA        *this
    );


    // ========== Character Output ==========

    // Output 'value' spaces
    void            con_OutOffset(
        CON_DATA        *this,
        uint32_t        value
    );
    
    bool            con_Out(
        CON_DATA        *this,
        uint8_t         value
    );

    void            con_OutCrLf(
        CON_DATA        *this
    );

    // Output LF then value spaces
    void            con_OutLfOffset(
        CON_DATA        *this,
        uint32_t        value
    );

    void            con_OutCString(
        CON_DATA        *this,
        uint16_t        cLen,
        const
        char            *pString
    );

    void            con_Puts(
        CON_DATA        *this,
        const
        char            *pString
    );


    void            con_PutsDec32(
        CON_DATA        *this,
        uint16_t        offset,
        const
        char            *pString,
        uint32_t        num
    );
    
    
    void            con_PutsHex16(
        CON_DATA        *this,
        uint16_t        offset,
        const
        char            *pString,
        uint16_t        num
    );
    
    
    void            con_PutsHex32(
        CON_DATA        *this,
        uint16_t        offset,
        const
        char            *pString,
        uint32_t        num
    );
    
    
    void            con_PutsStr(
        CON_DATA        *this,
        uint16_t        offset,
        const
        char            *pString1,
        const
        char            *pString2
    );
    
    
    // ========== Decimal Output ==========

    void            con_OutDec16(
        CON_DATA        *this,
        uint16_t        value
    );
    void            con_OutDec32(
        CON_DATA        *this,
        uint32_t        value
    );


    // ========== Hexadecimal Output ==========

    void            con_OutHex4(
        CON_DATA        *this,
        uint32_t        data
    );

    void            con_OutHex8(
        CON_DATA        *this,
        uint32_t        data
    );

    void            con_OutHex16(
        CON_DATA        *this,
        uint32_t        data
    );

    void            con_OutHex32(
        CON_DATA        *this,
        uint32_t        data
    );

    void            con_OutHex64(
        CON_DATA        *this,
        uint64_t        data
    );


    /*! Display up to 16 bytes of a memory area in hex and ascii.
     */
    void            con_OutBytes16_32(
        CON_DATA        *this,
        const
        uint32_t        offset,
        uint16_t        cLen,
        const
        void            *pData
    );


    bool            con_Printf(
        CON_DATA        *this,
        const
        char			*pFormat,
        ...
    );


    bool            con_Unlock(
        CON_DATA        *this
    );



#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

