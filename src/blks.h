// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          A List of Memory Blocks (blks) Header
//****************************************************************
/*
 * Program
 *			A List of Memory Blocks (blks)
 * Purpose
 *			This object provides a list of Blocks in Memory which
 *          are accessed via an integer index relative to 1.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	01/13/2019 Generated
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


#ifndef         BLKS_H
#define         BLKS_H


//#define   BLKS_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct blks_data_s	BLKS_DATA;            // Inherits from OBJ
    typedef struct blks_class_data_s BLKS_CLASS_DATA;   // Inherits from OBJ

    typedef struct blks_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in blks_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BLKS_DATA *);
    } BLKS_VTBL;

    typedef struct blks_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in blks_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BLKS_DATA *);
    } BLKS_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BLKS_SINGLETON
    BLKS_DATA *     blks_Shared (
        void
    );

    bool            blks_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to blks object if successful, otherwise OBJ_NIL.
     */
    BLKS_DATA *     blks_Alloc (
        void
    );
    
    
    OBJ_ID          blks_Class (
        void
    );
    
    
    BLKS_DATA *     blks_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        blks_getBlockSize (
        BLKS_DATA       *this
    );
    

    uint32_t        blks_getSize (
        BLKS_DATA       *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add a new block to this list.
     @param     this    object pointer
     @param     ppData  [out] optional pointer to returned data pointer
     @param     pIndex  [out] optional pointer to returned index
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         blks_Add (
        BLKS_DATA       *this,
        uint8_t         **ppData,       // [out] optional pointer to returned data
        uint32_t        *pIndex         // [out] optional pointer to returned index
    );


    /*!
     Find a block in the list by its index.
     @param     this    object pointer
     @param     index   [in] Index for Block (Relative to 1)
     @param     ppData  [out] optional pointer to returned data pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         blks_Get (
        BLKS_DATA       *this,
        uint32_t        index,              // [in] Index (Relative to 1)
        uint8_t         **ppData            // [out] Optional returned data pointer.
    );
    
    
    BLKS_DATA *   blks_Init (
        BLKS_DATA     *this
    );


    ERESULT         blks_SetupSizes(
        BLKS_DATA       *this,
        uint32_t        blockSize
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = blks_ToDebugString(this,4);
     @endcode 
     @param     this    BLKS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    blks_ToDebugString (
        BLKS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BLKS_H */

