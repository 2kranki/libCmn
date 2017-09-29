// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NUMBER Console Transmit Task (number) Header
//****************************************************************
/*
 * Program
 *			Separate number (number)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate number to run things without complications
 *          of interfering with the main number. A number may be 
 *          called a number on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal number. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	10/22/2015 Generated
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


#ifndef         NUMBER_H
#define         NUMBER_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef enum number_type_e {
        NUMBER_TYPE_UNKNOWN=0,
        NUMBER_TYPE_FLOAT,          // Float or Double
        NUMBER_TYPE_INT16,          // int16_t
        NUMBER_TYPE_INT32,          // int32_t
        NUMBER_TYPE_INT64,          // int64_t
        //NUMBER_TYPE_INT128,         // int128_t
        NUMBER_TYPE_UINT16,         // int16_t
        NUMBER_TYPE_UINT32,         // int32_t
        NUMBER_TYPE_UINT64,         // int64_t
        //NUMBER_TYPE_UINT128,        // int128_t
    } NUMBER_TYPE;
    
    
    typedef struct number_data_s	NUMBER_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    NUMBER_DATA *   number_Alloc(
        void
    );
    
    
    NUMBER_DATA *   number_New(
        void
    );

    
    NUMBER_DATA *   number_NewInt32(
        int32_t         value
    );
    
    
    NUMBER_DATA *   number_NewInt64(
        int64_t         value
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        number_getType(
        NUMBER_DATA     *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         number_Assign(
        NUMBER_DATA		*this,
        NUMBER_DATA		*pOther
    );
    
    
    NUMBER_DATA *   number_Copy(
        NUMBER_DATA     *this
    );
    
    
    double          number_Float(
        NUMBER_DATA     *this
    );
    
    
    int16_t         number_I16(
        NUMBER_DATA     *this
    );
    
    
    int32_t         number_I32(
        NUMBER_DATA     *this
    );
    
    
    int64_t         number_I64(
        NUMBER_DATA     *this
    );
    
    
    uint16_t        number_U16(
        NUMBER_DATA     *this
    );
    
    
    uint32_t        number_U32(
        NUMBER_DATA     *this
    );
    
    
    uint64_t        number_U64(
        NUMBER_DATA     *this
    );
    
    
    NUMBER_DATA *   number_Init(
        NUMBER_DATA     *this
    );

    NUMBER_DATA *   number_InitFloat(
        NUMBER_DATA     *this,
        double          flt
    );
    
    NUMBER_DATA *   number_InitI16(
        NUMBER_DATA     *this,
        int16_t         i16
    );
    
    NUMBER_DATA *   number_InitI32(
        NUMBER_DATA     *this,
        int32_t         i32
    );
    
    NUMBER_DATA *   number_InitI64(
        NUMBER_DATA     *this,
        int64_t         i64
    );
    
    NUMBER_DATA *   number_InitU16(
        NUMBER_DATA     *this,
        uint16_t        value
    );
    
    NUMBER_DATA *   number_InitU32(
        NUMBER_DATA     *this,
        uint32_t        value
    );
    
    NUMBER_DATA *   number_InitU64(
        NUMBER_DATA     *this,
        uint64_t        value
    );
    

    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     number_ToDebugString(
        NUMBER_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NUMBER_H */

