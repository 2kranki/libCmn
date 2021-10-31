// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Variable Length Records within 16-bit sized Block (BlockV16) Header
//****************************************************************
/*
 * Program
 *          Variable Length Records within 16-bit sized Block (BlockV16)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate BlockV16 to run things without complications
 *          of interfering with the main BlockV16. A BlockV16 may be 
 *          called a BlockV16 on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  10/22/2021 Generated
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


#ifndef         BLOCKV16_H
#define         BLOCKV16_H


//#define   BLOCKV16_IS_IMMUTABLE     1
//#define   BLOCKV16_JSON_SUPPORT     1
//#define   BLOCKV16_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BlockV16_data_s  BLOCKV16_DATA;            // Inherits from OBJ
    typedef struct BlockV16_class_data_s BLOCKV16_CLASS_DATA;   // Inherits from OBJ

    typedef struct BlockV16_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BlockV16_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BLOCKV16_DATA *);
    } BLOCKV16_VTBL;

    typedef struct BlockV16_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BlockV16_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BLOCKV16_DATA *);
    } BLOCKV16_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BLOCKV16_SINGLETON
    BLOCKV16_DATA *     BlockV16_Shared (
        void
    );

    void            BlockV16_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to BlockV16 object if successful, otherwise OBJ_NIL.
     */
    BLOCKV16_DATA *     BlockV16_Alloc (
        void
    );
    
    
    OBJ_ID          BlockV16_Class (
        void
    );
    
    
    BLOCKV16_DATA *     BlockV16_New (
        void
    );
    
    
#ifdef  BLOCKV16_JSON_SUPPORT
    BLOCKV16_DATA *   BlockV16_NewFromJsonString (
        ASTR_DATA       *pString
    );

    BLOCKV16_DATA *   BlockV16_NewFromJsonStringA (
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

    ERESULT     BlockV16_Disable (
        BLOCKV16_DATA       *this
    );


    ERESULT     BlockV16_Enable (
        BLOCKV16_DATA       *this
    );

   
    BLOCKV16_DATA *   BlockV16_Init (
        BLOCKV16_DATA     *this
    );


    ERESULT     BlockV16_IsEnabled (
        BLOCKV16_DATA       *this
    );
    
 
#ifdef  BLOCKV16_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BlockV16_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BlockV16_ToJson (
        BLOCKV16_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BlockV16_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BlockV16_ToDebugString (
        BLOCKV16_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* BLOCKV16_H */

