// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//     32-Bit Index B-Plus Tree Leaf Block (BPT32Leaf) Header
//****************************************************************
/*
 * Program
 *          32-Bit Index B-Plus Tree Leaf Block (BPT32Leaf)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate BPT32Leaf to run things without complications
 *          of interfering with the main BPT32Leaf. A BPT32Leaf may be 
 *          called a BPT32Leaf on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  09/18/2021 Generated
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


#ifndef         BPT32LEAF_H
#define         BPT32LEAF_H


//#define   BPT32LEAF_IS_IMMUTABLE     1
//#define   BPT32LEAF_JSON_SUPPORT     1
//#define   BPT32LEAF_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BPT32Leaf_data_s  BPT32LEAF_DATA;            // Inherits from OBJ
    typedef struct BPT32Leaf_class_data_s BPT32LEAF_CLASS_DATA;   // Inherits from OBJ

    typedef struct BPT32Leaf_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32Leaf_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32LEAF_DATA *);
    } BPT32LEAF_VTBL;

    typedef struct BPT32Leaf_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32Leaf_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32LEAF_DATA *);
    } BPT32LEAF_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BPT32LEAF_SINGLETON
    BPT32LEAF_DATA *     BPT32Leaf_Shared (
        void
    );

    void            BPT32Leaf_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to BPT32Leaf object if successful, otherwise OBJ_NIL.
     */
    BPT32LEAF_DATA *     BPT32Leaf_Alloc (
        void
    );
    
    
    OBJ_ID          BPT32Leaf_Class (
        void
    );
    
    
    BPT32LEAF_DATA *     BPT32Leaf_New (
        void
    );
    
    
#ifdef  BPT32LEAF_JSON_SUPPORT
    BPT32LEAF_DATA *   BPT32Leaf_NewFromJsonString (
        ASTR_DATA       *pString
    );

    BPT32LEAF_DATA *   BPT32Leaf_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     BPT32Leaf_Disable (
        BPT32LEAF_DATA       *this
    );


    ERESULT     BPT32Leaf_Enable (
        BPT32LEAF_DATA       *this
    );

   
    BPT32LEAF_DATA *   BPT32Leaf_Init (
        BPT32LEAF_DATA     *this
    );


    ERESULT     BPT32Leaf_IsEnabled (
        BPT32LEAF_DATA       *this
    );
    
 
#ifdef  BPT32LEAF_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPT32Leaf_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT32Leaf_ToJson (
        BPT32LEAF_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BPT32Leaf_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT32Leaf_ToDebugString (
        BPT32LEAF_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* BPT32LEAF_H */

