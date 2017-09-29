//****************************************************************
//					C Fixed Array (cfa) Header				
//****************************************************************
// vi: nu:noai:ts=4:sw=4

/*
 * Program
 *				C Fixed Array (cfa) Header				
 * Purpose
 *				These subroutines provide a general purpose set of
 *				routines to create a fixed size indexed C array.
 *				This array consists of two actual arrays. One is the
 *				physical array of the data and the second is a pointer
 *				array where each element contains the address of the
 *				element in the data array.
 * Remarks
 *	1.			None.
 * History
 *	10/07/2014	Created from scratch.
 * References
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




#include        <cmn_defs.h>


#ifndef         CFA_H
#define         CFA_H	1


#ifdef	__cplusplus
extern	"C" {
#endif
    
    
    /****************************************************************
    * * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
    ****************************************************************/


    typedef struct cfa_data_s   CFA_DATA;
    typedef uint32_t            CFA_INDEX;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    
    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    CFA_DATA *      cfa_Alloc(
        void
    );
    
    
    
    OBJ_ID          cfa_Class(
        void
    );
    
    
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------
    
    uint16_t        cfa_getEntrySize(
        CFA_DATA		*this
    );
    
    bool			cfa_putEntrySize(
        CFA_DATA		*this,
        uint16_t        value
    );
    
    
    uint16_t        cfa_getNumEntries(
        CFA_DATA		*this
    );
    
    bool			cfa_putNumEntries(
        CFA_DATA		*this,
        uint16_t        value
    );
    
    
        
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
    /* CFA_Count() returns the current number of used entries.
     * Returns:
     *		Current Number of Entries in Table
     */
    CFA_INDEX       cfa_Count(
        CFA_DATA        *
    );


    void **         cfa_Index(
        CFA_DATA        *
    );


    CFA_DATA *      cfa_Init(
        CFA_DATA        *this,
        uint32_t		cEntries,		// Number of Entries
        uint32_t		entrySize		// Size of an Entry in Bytes
    );




#ifdef	__cplusplus
};
#endif




#endif
