// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          BPTLEAF Console Transmit Task (bptLeaf) Header
//****************************************************************
/*
 * Program
 *			Separate bptLeaf (bptLeaf)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate bptLeaf to run things without complications
 *          of interfering with the main bptLeaf. A bptLeaf may be 
 *          called a bptLeaf on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	07/08/2018 Generated
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
#include        <bptree.h>


#ifndef         BPTLEAF_H
#define         BPTLEAF_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct bptLeaf_data_s	BPTLEAF_DATA;    // Inherits from OBJ.

    typedef struct bptLeaf_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in bptLeaf_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPTLEAF_DATA *);
    } BPTLEAF_VTBL;



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
     @return    pointer to bptLeaf object if successful, otherwise OBJ_NIL.
     */
    BPTLEAF_DATA *  bptLeaf_Alloc(
        void
    );
    
    
    OBJ_ID          bptLeaf_Class(
        void
    );
    
    
    BPTLEAF_DATA *     bptLeaf_New(
        void
    );
    
    BPTLEAF_DATA *  bptLeaf_NewWithSize(
        uint16_t        size
    );
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        bptLeaf_getSize(
        BPTLEAF_DATA    *this
    );
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         bptLeaf_AddA(
        BPTLEAF_DATA    *this,
        uint16_t        keyLen,
        const
        char            *pKey,
        uint16_t        dataLen,
        uint8_t         *pData
    );


    ERESULT         bptLeaf_FindA(
        BPTLEAF_DATA	*this,
        uint16_t        keyLen,
        const
        char            *pKey
    );

   
    BPTLEAF_DATA *  bptLeaf_Init(
        BPTLEAF_DATA     *this
    );


    ERESULT         bptLeaf_IsEnabled(
        BPTLEAF_DATA	*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = bptLeaf_ToDebugString(this,4);
     @endcode 
     @param     this    BPTLEAF object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    bptLeaf_ToDebugString(
        BPTLEAF_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BPTLEAF_H */

