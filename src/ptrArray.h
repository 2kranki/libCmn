// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Array of Pointers (ptrArray) Header
//****************************************************************
/*
 * Program
 *			Array of Pointers (ptrArray)
 * Purpose
 *			This object provides an Array of Pointers.  It only looks
 *          at the pointers as data to be stored in a table. It does
 *          not actually do anything with the pointers themselves.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	07/02/2015 Generated
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
#include        <enum.h>


#ifndef         PTRARRAY_H
#define         PTRARRAY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ptrArray_data_s	PTRARRAY_DATA;

    typedef ERESULT         (*PTR_COMPARE)(void *p0, void *p1);
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    PTRARRAY_DATA * ptrArray_Alloc(
    );
    
    
    PTRARRAY_DATA * ptrArray_New(
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        ptrArray_getSize(
        PTRARRAY_DATA   *this
    );

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         ptrArray_AppendData(
        PTRARRAY_DATA	*this,
        void            *pData,
        uint32_t        *pIndex
    );
    
    
    void *          ptrArray_Delete(
        PTRARRAY_DATA   *this,
        uint32_t        index       // Relative to 1
    );
    
    
    void *          ptrArray_DeleteFirst(
        PTRARRAY_DATA	*this
    );


    void *          ptrArray_DeleteLast(
        PTRARRAY_DATA	*this
    );


    void *          ptrArray_GetData(
        PTRARRAY_DATA   *this,
        uint32_t        index       // Relative to 1
    );
    
    
    /*!
     Create an Enumerator that will enumerate through all the pointers.
     @return:   If successful, valid enumerator. Otherwise, OBJ_NIL.
                error code.
     @warning:  Remember to release the returned Enumeration object and
                the Pointer Array should not be altered while the enumerator
                exists.
     */
    ERESULT         ptrArray_Enum(
        PTRARRAY_DATA   *this,
        ENUM_DATA       **ppEnum
    );
    
    
    PTRARRAY_DATA * ptrArray_Init(
        PTRARRAY_DATA   *this
    );


    ERESULT         ptrArray_InsertData(
        PTRARRAY_DATA	*this,
        uint32_t        index,
        void            *pData
    );
    
    
    ERESULT         ptrArray_Sort(
        PTRARRAY_DATA	*this,
        PTR_COMPARE     pCompare
    );
    
    
    // Visit() visits each entry in the table in order from 1 to N.
    // The visit routine needs to return true to continue the visiting
    // or false to break it off.
    // Returns:
    //	TRUE			=	Successful Completion
    //	FALSE        	=	Unsuccessful Completion
    ERESULT 		ptrArray_Visit(
        PTRARRAY_DATA   *this,
        P_VOIDEXIT2_BE  pVisitor,
        void            *pObj       // 1st parm to pVisitor
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* PTRARRAY_H */

