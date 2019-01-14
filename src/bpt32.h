// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          B-Plus 32-Bit Tree (bpt32) Header
//****************************************************************
/*
 * Program
 *			B-Plus 32-Bit Tree (bpt32)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate bpt32 to run things without complications
 *          of interfering with the main bpt32. A bpt32 may be 
 *          called a bpt32 on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	01/12/2019 Generated
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


#ifndef         BPT32_H
#define         BPT32_H


//#define   BPT32_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct bpt32_data_s	BPT32_DATA;            // Inherits from OBJ
    typedef struct bpt32_class_data_s BPT32_CLASS_DATA;   // Inherits from OBJ

    typedef struct bpt32_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in bpt32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32_DATA *);
    } BPT32_VTBL;

    typedef struct bpt32_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in bpt32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32_DATA *);
    } BPT32_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BPT32_SINGLETON
    BPT32_DATA *    bpt32_Shared (
        void
    );

    bool            bpt32_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to bpt32 object if successful, otherwise OBJ_NIL.
     */
    BPT32_DATA *    bpt32_Alloc (
        void
    );
    
    
    OBJ_ID          bpt32_Class (
        void
    );
    
    
    BPT32_DATA *    bpt32_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         bpt32_Add (
        BPT32_DATA      *this,
        uint32_t        key,
        void            *pData
    );
    
    
    ERESULT         bpt32_Disable (
        BPT32_DATA		*this
    );


    ERESULT         bpt32_Find (
        BPT32_DATA      *this,
        uint32_t        key,
        void            *pData
    );
    
    
    BPT32_DATA *    bpt32_Init (
        BPT32_DATA      *this
    );


    ERESULT         bpt32_SetupSizes(
        BPT32_DATA      *this,
        uint32_t        blockSize,
        uint16_t        dataSize         
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = bpt32_ToDebugString(this,4);
     @endcode 
     @param     this    BPT32 object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     bpt32_ToDebugString (
        BPT32_DATA      *this,
        int             indent
    );
    
    
    ERESULT         bpt32_Update (
        BPT32_DATA      *this,
        uint32_t        key,
        void            *pData
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BPT32_H */

