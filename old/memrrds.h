// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          MEMRRDS Console Transmit Task (memrrds) Header
//****************************************************************
/*
 * Program
 *			Separate memrrds (memrrds)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate memrrds to run things without complications
 *          of interfering with the main memrrds. A memrrds may be 
 *          called a memrrds on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	01/16/2019 Generated
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
#include        <ioRrdsInterface.h>


#ifndef         MEMRRDS_H
#define         MEMRRDS_H


//#define   MEMRRDS_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct memrrds_data_s	MEMRRDS_DATA;            // Inherits from OBJ
    typedef struct memrrds_class_data_s MEMRRDS_CLASS_DATA;   // Inherits from OBJ

    typedef struct memrrds_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in memrrds_object.c.
        // Properties:
        // Methods:
        ERESULT         (*pClose) (
            OBJ_ID          this,
            bool            fDelete
        );
        ERESULT         (*pCreate) (
            OBJ_ID          this,
            PATH_DATA       *pPath,
            uint16_t        cLRU            // Number of LRU Buffers
        );
        ERESULT         (*pOpen) (
            OBJ_ID          this,
            PATH_DATA       *pPath,
            uint16_t        cLRU            // Number of LRU Buffers
        );
        ERESULT         (*pRead) (
            OBJ_ID          this,
            uint32_t        recordNum,
            uint8_t         *pData
        );
        ERESULT         (*pWrite) (
            OBJ_ID          this,
            uint32_t        recordNum,
            uint8_t         *pData
        );
    } MEMRRDS_VTBL;

    typedef struct memrrds_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in memrrds_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MEMRRDS_DATA *);
    } MEMRRDS_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  MEMRRDS_SINGLETON
    MEMRRDS_DATA *  memrrds_Shared (
        void
    );

    bool            memrrds_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to memrrds object if successful, otherwise OBJ_NIL.
     */
    MEMRRDS_DATA *  memrrds_Alloc (
        void
    );
    
    
    OBJ_ID          memrrds_Class (
        void
    );
    
    
    MEMRRDS_DATA *  memrrds_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        memrrds_getBlockSize (
        MEMRRDS_DATA    *this
    );
    
    
    IORRDS_INTERFACE * memrrds_getIO (
        MEMRRDS_DATA    *this
    );


uint32_t            memrrds_getSize (
        MEMRRDS_DATA    *this
    );
    
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    MEMRRDS_DATA *  memrrds_Init (
        MEMRRDS_DATA    *this
    );


    ERESULT         memrrds_Read(
        MEMRRDS_DATA    *this,
        uint32_t        index,                // [in] Block Index
        uint8_t         *pBuffer              // [out] Buffer of sectorSize bytes
    );
    
    
    ERESULT         memrrds_SetupSizes(
        MEMRRDS_DATA    *this,
        uint32_t        blockSize
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = memrrds_ToDebugString(this,4);
     @endcode 
     @param     this    MEMRRDS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    memrrds_ToDebugString (
        MEMRRDS_DATA    *this,
        int             indent
    );
    
    
    ERESULT         memrrds_Write(
        MEMRRDS_DATA    *this,
        uint32_t        index,                // [in] Block Index
        uint8_t         *pBuffer              // [out] Buffer of sectorSize bytes
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MEMRRDS_H */

