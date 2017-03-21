// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          IORCD Console Transmit Task (ioRcd) Header
//****************************************************************
/*
 * Program
 *			Separate ioRcd (ioRcd)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate ioRcd to run things without complications
 *          of interfering with the main ioRcd. A ioRcd may be 
 *          called a ioRcd on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal ioRcd. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	01/12/2017 Generated
 */


/*
 * COPYRIGHT  - (C) Copyright 2016  BY Robert White Services, LLC
 *             This computer software is the proprietary information
 *             of Robert White Services, LLC and is subject to a
 *             License Agreement between the user hereof and Robert
 *             White Services, LLC. All concepts, programs, tech-
 *             niques,  object code  and  source code are the Trade
 *             Secrets of Robert White Services, LLC.
 */





#include        <cmn_defs.h>
#include        <AStr.h>
#include        <path.h>


#ifndef         IORCD_H
#define         IORCD_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ioRcd_data_s	IORCD_DATA;    // Inherits from OBJ.

    typedef struct ioRcd_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ioRcd_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(IORCD_DATA *);
    } IORCD_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    IORCD_DATA *    ioRcd_Alloc(
    );
    
    
    IORCD_DATA *    ioRcd_New(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         ioRcd_getLastError(
        IORCD_DATA      *this
    );


    PATH_DATA *     ioRcd_getPath(
        IORCD_DATA      *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         ioRcd_Disable(
        IORCD_DATA		*this
    );


    ERESULT         ioRcd_Enable(
        IORCD_DATA		*this
    );

   
    IORCD_DATA *    ioRcd_Init(
        IORCD_DATA      *this
    );


    ERESULT         ioRcd_IsEnabled(
        IORCD_DATA		*this
    );
    
 
    /*!
     Read the logical sector from the disk returning its address. The first
     sector of the disk is logical sector 1. The highest logical sector
     number is the number of sectors on the disk.
     Example:
     @code:
     ERESULT      eRc = fat_LogicalSectorRead(pObj, 1, buffer);
     @endcode:
     @param:    this    fat_DATA object pointer
     @param:    lsn     Logical Sector Number (Relative to 1)
     @param:    pBuffer Pointer to a buffer of sector size bytes.
     @return:   If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
     error code.
     */
    ERESULT         ioRcd_LogicalSectorRead(
        IORCD_DATA      *this,
        uint32_t        lsn,            // Relative to 1
        uint8_t         *pBuffer
    );
    
    
    /*!
     Write the logical sector to the disk. The number of bytes written
     will be the disk sector size.
     Example:
     @code:
     ERESULT      eRc = fat_LogicalSectorWrite(pObj,1,pBuffer);
     @endcode:
     @param:    this    fat_DATA object pointer
     @param:    lsn     Logical Sector Number (Relative to 1)
     @param:    pBuffer Pointer to a buffer of sector size bytes.
     @return:   If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
     error code.
     */
    ERESULT         ioRcd_LogicalSectorWrite(
        IORCD_DATA      *this,
        uint32_t        lsn,            // Relative to 1
        uint8_t         *pBuffer
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = ioRcd_ToDebugString(this,4);
     @endcode:
     @param:    this    IORCD object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    ioRcd_ToDebugString(
        IORCD_DATA     *this,
        int            indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* IORCD_H */

