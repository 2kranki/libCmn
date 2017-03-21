// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          ENDIAN Console Transmit Task (endian) Header
//****************************************************************
/*
 * Program
 *			Separate endian (endian)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate endian to run things without complications
 *          of interfering with the main endian. A endian may be 
 *          called a endian on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal endian. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	10/25/2016 Generated
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


#ifndef         ENDIAN_H
#define         ENDIAN_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct endian_data_s	ENDIAN_DATA;    // Inherits from OBJ.

    typedef struct endian_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in endian_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ENDIAN_DATA *);
    } ENDIAN_VTBL;



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
     @return:   pointer to endian object if successful, otherwise OBJ_NIL.
     */
    ENDIAN_DATA *     endian_Alloc(
    );
    
    
    ENDIAN_DATA *     endian_New(
    );
    
    
    ENDIAN_DATA *    endian_Shared(
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     endian_getLastError(
        ENDIAN_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    uint16_t        endian_GetU16Big(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    );

    uint16_t        endian_GetU16Little(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    );
    

    uint32_t        endian_GetU24Big(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    );
    
    uint32_t        endian_GetU24Little(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    );
    
    
    uint32_t        endian_GetU32Big(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    );
    
    uint32_t        endian_GetU32Little(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    );
    
    
    uint64_t        endian_GetU64Big(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    );
    
    uint64_t        endian_GetU64Little(
        ENDIAN_DATA     *this,
        uint8_t         *pValue
    );
    
    
    ENDIAN_DATA *   endian_Init(
        ENDIAN_DATA     *this
    );


    ERESULT         endian_PutU16Big(
        ENDIAN_DATA     *this,
        uint16_t        value,          // In
        uint8_t         *pValue         // Out 2-Byte output area
    );
    
    ERESULT         endian_PutU16Little(
        ENDIAN_DATA     *this,
        uint16_t        value,          // In
        uint8_t         *pValue         // Out 2-Byte output area
    );
    
 
    ERESULT         endian_PutU24Big(
        ENDIAN_DATA     *this,
        uint32_t        value,          // In
        uint8_t         *pValue         // Out 4-Byte output area
    );
    
    ERESULT         endian_PutU24Little(
        ENDIAN_DATA     *this,
        uint32_t        value,          // In
        uint8_t         *pValue         // Out 4-Byte output area
    );
    
    
    ERESULT         endian_PutU32Big(
        ENDIAN_DATA     *this,
        uint32_t        value,          // In
        uint8_t         *pValue         // Out 4-Byte output area
    );
    
    ERESULT         endian_PutU32Little(
        ENDIAN_DATA     *this,
        uint32_t        value,          // In
        uint8_t         *pValue         // Out 4-Byte output area
    );
    
    
    ERESULT         endian_PutU64Big(
        ENDIAN_DATA     *this,
        uint64_t        value,          // In
        uint8_t         *pValue         // Out 8-Byte output area
    );
    
    ERESULT         endian_PutU64Little(
        ENDIAN_DATA     *this,
        uint64_t        value,          // In
        uint8_t         *pValue         // Out 8-Byte output area
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = endian_ToDebugString(this,4);
     @endcode:
     @param:    this    ENDIAN object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    endian_ToDebugString(
        ENDIAN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* ENDIAN_H */

