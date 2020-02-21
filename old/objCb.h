// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Circular Buffer (cb) Support  Header
//****************************************************************
/*
 * Program
 *				Circular Buffer (cb) Subroutines
 * Purpose
 *				These subroutines provide a general purpose set of
 *				routines to provide a Circular (FIFO) Buffer of
 *              size elements. The buffer is designed to work in
 *				multi-tasking environment with a single sender and
 *              receiver. It is not safe for multiple senders or
 *              receivers with proper locking.
 *
 *
 * Remarks
 *	1.			XC32 allows 4 register variables per function call.
 *	            So, we will restrict most function calls to 4 or less.
 *
 * History
 *	12/30/2014	Created from cb8.
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




#include        <cmn_defs.h>


#ifndef         OBJCB_H
#define         OBJCB_H



#ifdef	__cplusplus
extern "C" {
#endif
    
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

    typedef struct objCb_data_s	OBJCB_DATA;

    typedef struct objCb_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fatFCB_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CB_DATA *);
    } OBJCB_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    OBJCB_DATA *    objCb_Alloc(
        uint16_t        size            // Number of Elements in Buffer
    );
    
    
    OBJCB_DATA *    objCb_New(
        uint16_t        size            // Number of Elements in Buffer
    );
    
    
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        objCb_getSize(
        OBJCB_DATA      *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    uint16_t        objCb_Count(
        OBJCB_DATA      *this
    );
        
    
    // The object is not released when it is returned. So, the user
    // must do so when they are done with it.
    bool            objCb_Get(
        OBJCB_DATA      *this,
        OBJ_ID          *ppValue
    );


    bool            objCb_isEmpty(
        OBJCB_DATA      *this
    );


    bool            objCb_isFull(
        OBJCB_DATA      *this
    );


    OBJCB_DATA *    objCb_Init(
        OBJCB_DATA      *this
    );


    /*!
     Pause the buffer flow releasing any tasks waiting to get/put data.
     This is necessary especially just prior to termination since all
     conditions and mutexes must be in an unlocked state.
     */
    bool            objCb_Pause(
        OBJCB_DATA      *this
    );
    
    
    // The object is retained when it is added to the circular
    // buffer.
    bool            objCb_Put(
        OBJCB_DATA      *this,
        OBJ_ID          pValue
    );


    bool            objCb_Resume(
        OBJCB_DATA      *this
    );
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* OBJCB_H */

