// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Virtual Device Driver (device) Header
//****************************************************************
/*
 * Program
 *			Virtual Device Driver (device)
 * Purpose
 *			This object provides Virtual Device Driver which should
 *          be used as the foundation for writing devices drivers.
 *
 * Remarks
 *	1.      In C, size_t is unsigned.
 *  2.      We chose the ioctl and devctl to have as many parameters
 *          as could be supplied in registers in most systems. There
 *          is no formal specification for ioctl and devctl.
 *
 * History
 *	02/23/2017 Generated
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


#ifndef         DEVICE_H
#define         DEVICE_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct device_data_s	DEVICE_DATA;    // Inherits from OBJ.

    typedef struct device_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in device_object.c.
        // Properties:
        // Methods:
        int             (*pOpen)(DEVICE_DATA *, const char *, int);
        int             (*pClose)(DEVICE_DATA *);
        int             (*pRead)(DEVICE_DATA *, uint8_t *, size_t *, off_t);
        int             (*pWrite)(DEVICE_DATA *, uint8_t *, size_t *, off_t);
        int             (*pIoctl)(DEVICE_DATA *, unsigned long, void *, void *);
        int             (*pDevctl)(DEVICE_DATA *, unsigned long, void *, void *);
    } DEVICE_VTBL;



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
     @return:   pointer to device object if successful, otherwise OBJ_NIL.
     */
    DEVICE_DATA *     device_Alloc(
        uint16_t    stackSize           // Stack Size in Words
    );
    
    
    DEVICE_DATA *     device_New(
        uint16_t    stackSize           // Stack Size in Words
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     device_getLastError(
        DEVICE_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     device_Disable(
        DEVICE_DATA		*this
    );


    ERESULT     device_Enable(
        DEVICE_DATA		*this
    );

   
    DEVICE_DATA *   device_Init(
        DEVICE_DATA     *this
    );


    ERESULT     device_IsEnabled(
        DEVICE_DATA		*this
    );
    
 
    /*!
     Read the logical sector from the disk returning its address. The first
     sector of the disk is logical sector 0. The highest logical sector
     number is the number of sectors on the disk.
     Example:
     @code:
     ERESULT      eRc = fatIO_LogicalSectorRead(pIO, 1, buffer);
     @endcode:
     @param:    this    fat_DATA object pointer
     @param:    lsn     Logical Sector Number (Relative to 0)
     @param:    pBuffer Pointer to a buffer of sector size bytes.
     @return:   If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
     error code.
     */
    int             device_Devctl(
        DEVICE_DATA     *this,
        unsigned long   cmd,
        void            *parm1,
        void            *parm2
    );
    
    
    /*!
     Read the logical sector from the disk returning its address. The first
     sector of the disk is logical sector 0. The highest logical sector
     number is the number of sectors on the disk.
     Example:
     @code:
     ERESULT      eRc = fatIO_LogicalSectorRead(pIO, 1, buffer);
     @endcode:
     @param:    this    fat_DATA object pointer
     @param:    lsn     Logical Sector Number (Relative to 0)
     @param:    pBuffer Pointer to a buffer of sector size bytes.
     @return:   If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
     error code.
     */
    int             device_Ioctl(
        DEVICE_DATA     *this,
        unsigned long   cmd,
        void            *parm1,
        void            *parm2
    );
    
    
    /*!
     Read the logical sector from the disk returning its address. The first
     sector of the disk is logical sector 0. The highest logical sector
     number is the number of sectors on the disk.
     Example:
     @code:
     ERESULT      eRc = fatIO_LogicalSectorRead(pIO, 1, buffer);
     @endcode:
     @param:    this    fat_DATA object pointer
     @param:    lsn     Logical Sector Number (Relative to 0)
     @param:    pBuffer Pointer to a buffer of sector size bytes.
     @return:   If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
     error code.
     */
    int             device_Read(
        DEVICE_DATA     *this,
        uint8_t         *pBuffer,
        size_t          *pLenRead,
        off_t           recordNumber
    );
    
    
    /*!
     Write the logical sector to the disk. The number of bytes written
     will be the disk sector size.
     Example:
     @code:
     ERESULT      eRc = fatIO_LogicalSectorWrite(pIO, 0, pBuffer);
     @endcode:
     @param:    this    fat_DATA object pointer
     @param:    lsn     Logical Sector Number (Relative to 0)
     @param:    pBuffer Pointer to a buffer of sector size bytes.
     @return:   If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
     error code.
     */
    int             device_Write(
        DEVICE_DATA     *this,
        uint8_t         *pBuffer,
        size_t          *pLenWritten,
        off_t           recordNumber
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = device_ToDebugString(this,4);
     @endcode:
     @param:    this    DEVICE object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    device_ToDebugString(
        DEVICE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DEVICE_H */

