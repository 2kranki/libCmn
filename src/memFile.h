// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Memory Based File (memFile) Header
//****************************************************************
/*
 * Program
 *			Memory Based File (memFile)
 * Purpose
 *			This object provides a memory based relative record
 *          file where records are accessed via integer indices
 *          relative to one.
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


#ifndef         MEMFILE_H
#define         MEMFILE_H


//#define   MEMFILE_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct memFile_data_s	MEMFILE_DATA;            // Inherits from OBJ
    typedef struct memFile_class_data_s MEMFILE_CLASS_DATA;   // Inherits from OBJ

    typedef struct memFile_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in memFile_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MEMFILE_DATA *);
    } MEMFILE_VTBL;

    typedef struct memFile_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in memFile_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MEMFILE_DATA *);
    } MEMFILE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  MEMFILE_SINGLETON
    MEMFILE_DATA *  memFile_Shared (
        void
    );

    bool            memFile_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to memFile object if successful, otherwise OBJ_NIL.
     */
    MEMFILE_DATA *  memFile_Alloc (
        void
    );
    
    
    OBJ_ID          memFile_Class (
        void
    );
    
    
    MEMFILE_DATA *  memFile_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        memFile_getBlockSize (
        MEMFILE_DATA    *this
    );


    uint32_t        memFile_getSize (
        MEMFILE_DATA       *this
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    MEMFILE_DATA *  memFile_Init (
        MEMFILE_DATA    *this
    );


    ERESULT         memFile_Read(
        MEMFILE_DATA    *this,
        uint32_t        index,                // [in] Block Index
        uint8_t         *pBuffer              // [out] Buffer of sectorSize bytes
    );
    
 
    ERESULT         memFile_SetupSizes(
        MEMFILE_DATA    *this,
        uint32_t        blockSize
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = memFile_ToDebugString(this,4);
     @endcode 
     @param     this    MEMFILE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    memFile_ToDebugString (
        MEMFILE_DATA    *this,
        int             indent
    );
    
    
    ERESULT         memFile_Write(
        MEMFILE_DATA    *this,
        uint32_t        index,                // [in] Block Index
        uint8_t         *pBuffer              // [out] Buffer of sectorSize bytes
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MEMFILE_H */

