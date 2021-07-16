// vi:nu:et:sts=4 ts=4 sw=4 tw=90

//****************************************************************
//              Trace Table (trctbl) Support  Header
//****************************************************************
/*
 * Program
 *				Trace Table (trctbl) Subroutines
 * Purpose
 *				These subroutines provide a general purpose set of
 *				routines to provide a Circular (FIFO) Buffer of
 *              uint32_t elements. The buffer is designed to work in
 *				multi-tasking environment with a single sender and
 *              receiver. It is not safe for multiple senders or
 *              receivers.
 *
 *
 * Remarks
 *	1.			XC32 allows 4 register variables per function call.
 *	            So, we will restrict most function calls to 4 or less.
 *	2.			Since sizeof(uint32_t) == sizeof(WORD) == sizeof(void *)
 *              you can store pointers in the buffer by casting to/from
 *              uint32_t.
 *
 * History
 *	12/26/2014	Created from scratch.
 * References
 *      http://en.wikipedia.org/wiki/Circular_buffer
 *		"Data Structures and Algorithms", Alfred V. Aho et al,
 *			Addison-Wesley, 1985
 *		"Data Structures using C", Aaron M. Tenenbaum et al,
 *			Prentice-Hall, 1990
 *		"Programs and Data Structures in C", Leendert Ammeraal,
 *			John Wiley & Sons, 1987
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




#ifndef         TRCTBL_H
#define         TRCTBL_H


#include        <cmn_defs.h>



#ifdef	__cplusplus
extern "C" {
#endif
    
    


    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

    typedef struct trctbl_data_s	TRCTBL_DATA;

    typedef enum subsys_codes_e {
        SUBSYS_UNKNOWN=0,
        SUBSYS_CAN,
        SUBSYS_CON,
        SUBSYS_I2C,
        SUBSYS_MON,
        SUBSYS_RTCC,
        SUBSYS_SPI,
        SUBSYS_UART
    } SUBSYS_CODES;



    typedef struct trctbl_entry_s {
        union {
            struct {
                uint16_t        ident;
                uint8_t         subsys;
                uint8_t         misc8;
                uint16_t        misc16;
                uint16_t        timeStamp;
            };
            struct {
                uint32_t        data0;
                uint32_t        data1;
            };
        };
    } TRCTBL_ENTRY;


    
    
    
    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    /* Alloc() allocates an area large enough for 'size' trace table
     * entries. The size should be passed to Init() without change.
     */
    TRCTBL_DATA *	trctbl_Alloc(
        uint16_t        size
    );

    
    void            trctbl_resetShared(
        void
    );
    
    
    const
    char *          trctbl_SubsysDesc(
        SUBSYS_CODES    code
    );
    
    
    TRCTBL_DATA *   trctbl_SharedObject(
        void
    );
    
    
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        trctbl_getSize(
        TRCTBL_DATA       *cbp
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    void            trctbl_Add(
        TRCTBL_DATA     *cbp,
        uint16_t        ident,
        uint8_t         subsys,
        uint8_t         misc8_1,
        uint16_t        misc16
    );
    
    
    bool            trctbl_Get(
        TRCTBL_DATA     *cbp,
        uint16_t        index,
        TRCTBL_ENTRY    *pEntry
    );


    TRCTBL_DATA *   trctbl_Init(
        TRCTBL_DATA     *cbp,
        uint16_t        size            // Size of Table in TRCTBL_ENTRYs
    );


    void            trctbl_Lock(
        TRCTBL_DATA     *cbp
    );
    
    
    void            trctbl_Put(
        TRCTBL_DATA     *cbp,
        TRCTBL_ENTRY    *pEntry
    );


    void            trctbl_Unlock(
        TRCTBL_DATA     *cbp
    );
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* TRCTBL_H */

