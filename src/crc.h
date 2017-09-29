// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Cyclic Reduncdancy Checksum (crc) Header
//****************************************************************
/*
 * Program
 *			Cyclic Reduncdancy Checksum (crc)
 * Purpose
 *          This object provides several different Cyclic Redundancy
 *          Checksum (CRC) calculators.  Each is table drive and the
 *          table is built at init() time.
 *
 *          It turns out that the standards are less than standard and
 *          multiple standards are for each type.  Argh! So, I put the
 *          parameters in a table and use that to generate the crc table
 *          and accompanying calculations.
 * Remarks
 *	1.      None
 * References
 *          "Implementing the CCITT Cyclical Redundancy Check", Bob Felice,
 *          The C User's Journal, Sep 1990, pg 61
 *          "A PAINLESS GUIDE TO CRC ERROR DETECTION ALGORITHMS", Ross N. Williams,
 *          http://www.ross.net/crc/download/crc_v3.txt, Many thanks for this
 *          article. My system is derived from his code which was public
 *          domain.
 *
 * History
 *	07/25/2017 Generated
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


#ifndef         CRC_H
#define         CRC_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct crc_data_s	CRC_DATA;    // Inherits from OBJ.

    typedef struct crc_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in crc_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CRC_DATA *);
    } CRC_VTBL;


    typedef enum crc_type_e {
        CRC_TYPE_UNKNOWN    = 0,
        CRC_TYPE_16			= 1,	// CRC-16 (Old used in PKARC)
        CRC_TYPE_CCITT_16	= 2,	// 16-Bit CCITT CRC
        CRC_TYPE_32			= 3,	// CRC-32 (New used in PKZIP)(Default)
        CRC_TYPE_IEEE_32	= 4,	// 32-Bit IEEEE-802 CRC
        CRC_TYPE_MPEG2_32	= 5		// 32-Bit MPEG2 CRC
    } CRC_TYPE;
    
    

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
     @return:   pointer to crc object if successful, otherwise OBJ_NIL.
     */
    CRC_DATA *      crc_Alloc(
        void
    );
    
    
    CRC_DATA *      crc_New(
        CRC_TYPE        type
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        crc_getCheck(
        CRC_DATA     *this
    );
    
    
    uint16_t        crc_getCrc16(
        CRC_DATA        *this
    );
    
    bool            crc_setCrc16(
        CRC_DATA        *this,
        uint16_t        value
    );
    
    
    uint32_t        crc_getCrc32(
        CRC_DATA        *this
    );
    
    bool            crc_setCrc32(
        CRC_DATA        *this,
        uint32_t        value
    );
    
    
    ERESULT         crc_getLastError(
        CRC_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    uint32_t        crc_AccumBlock(
        CRC_DATA		*this,
        uint32_t        len,
        const
        uint8_t         *pData
    );
    
    
    CRC_DATA *      crc_Init(
        CRC_DATA        *this,
        CRC_TYPE        type
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = crc_ToDebugString(this,4);
     @endcode:
     @param:    this    CRC object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    crc_ToDebugString(
        CRC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* CRC_H */

