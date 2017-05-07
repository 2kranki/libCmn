// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          DEVBASE Console Transmit Task (devBase) Header
//****************************************************************
/*
 * Program
 *			Separate devBase (devBase)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate devBase to run things without complications
 *          of interfering with the main devBase. A devBase may be 
 *          called a devBase on other O/S's.
 *
 * Remarks
 *	1.      Any object inheriting from this object must comply with
 *          DEVBASE_VTBL_INTERNAL, this object relies on that fact.
 *
 * History
 *	02/23/2016 Generated
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


#ifndef         DEVBASE_H
#define         DEVBASE_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

    // Forward Declare some needed objects.
    typedef struct devMgr_data_s	DEVMGR_DATA;

    // CLR, SET and INV are atomic. Only 1 bit will be written to the
    // sfr for CLR, SET and INV; 0 bits will be ignored.
    typedef struct sfr_cluster_s	{
        volatile
        uint32_t        *pBase;             // Read Write
        uint32_t        *pBase_CLR;         // Write Only
        uint32_t        *pBase_SET;         // Write Only
        uint32_t        *pBase_INV;         // Write Only
    } SFR_CLUSTER;


    typedef struct devBase_data_s	DEVBASE_DATA;    // Inherits from OBJ.

    typedef struct devBase_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in devBase_object.c.
        // Properties:
        // Methods:
        ERESULT     (*pGetc)(DEVBASE_DATA *);
        ERESULT     (*pIoctl)(
                        DEVBASE_DATA	*this,
                        uint32_t        request,
                        void            *pParm1,
                        void            *pParm2
                    );
        ERESULT     (*pPutc)(DEVBASE_DATA *,int32_t);
        ERESULT     (*pRead)(DEVBASE_DATA *,uint32_t,void *,uint32_t *);
        ERESULT     (*pStart)(DEVBASE_DATA *, void *);
        ERESULT     (*pStop)(DEVBASE_DATA *, void *);
        ERESULT     (*pWrite)(DEVBASE_DATA *,uint32_t,void *,uint32_t *);
    } DEVBASE_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    DEVBASE_DATA *     devBase_Alloc(
    );
    
    
    DEVBASE_DATA *     devBase_New(
        DEVMGR_DATA     *pMgr
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    DEVMGR_DATA *   devBase_getMgr(
        DEVBASE_DATA    *this
    );

    bool            devBase_setMgr(
        DEVBASE_DATA    *this,
        DEVMGR_DATA     *pValue
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    DEVBASE_DATA *  devBase_Init(
        DEVBASE_DATA    *this,
        DEVMGR_DATA     *pMgr
    );


    /*!
     Read one character from the driver. Whether the driver blocks or
     not is up to the driver.
     @return:   If successful, the character,
                otherwise any of the ERESULT error codes. 
                Note: All the error codes are negative.
     */
    ERESULT         devBase_Getc(
        DEVBASE_DATA	*this
    );
    
    
    /*!
     Modify the driver in some way. ioctl() is implemented
     according to the needs of the driver and documented in
     the specific driver's header.
     Note: The number of parameters is restricted, so that
     all the parameters can be passed in registers on the
     PIC32 ($a0-$a3). You can use part of the request by
     adding data in the higher level bits and having the
     base device mask them off when looking at the request
     code assuming that it is less than uint32_t.
     @return:   If successful, ERESULT_SUCCESSFUL_COMPLETION, 
                otherwise any of the ERESULT error codes.
     */
    ERESULT         devBase_Ioctl(
        DEVBASE_DATA	*this,
        uint32_t        request,
        void            *pParm1,
        void            *pParm2
    );
    
    
    /*!
     Write one character to the driver. Whether the driver blocks or
     not is up to the driver.
     @return:   If successful, ERESULT_SUCCESSFUL_COMPLETION,
                otherwise any of the ERESULT error codes.
     */
    ERESULT         devBase_Putc(
        DEVBASE_DATA	*this,
        int32_t         data
    );
    
    
    /*!
     Read data from the driver. Whether the driver blocks or
     not is up to the driver. 
     @return:   If successful, ERESULT_SUCCESSFUL_COMPLETION,
                otherwise any of the ERESULT error codes.
     */
    ERESULT         devBase_Read(
        DEVBASE_DATA	*this,
        uint32_t        amt,
        void            *pData,
        uint32_t        *pAmtRead
    );
    
    
    /*!
     Start the driver. The driver is free to handle I/O
     after the start has been issued.
     @return:   If successful, ERESULT_SUCCESSFUL_COMPLETION,
                otherwise any of the ERESULT error codes.
     */
    ERESULT         devBase_Start(
        DEVBASE_DATA	*this,
        void            *pData
    );
    
    
    /*!
     Disable/stop the driver. This method shuts down the device to its
     original start state and only returns after the driver is
     completely shut down. Stop() must leave the driver in a
     state that allows Start to restart the driver.
     @return:   none
     */
    ERESULT         devBase_Stop(
        DEVBASE_DATA	*this,
        void            *pData
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *    devBase_ToDebugString(
        DEVBASE_DATA     *this,
        int             indent
    );
    
    
    /*!
     Write data to the driver. Whether the driver blocks or
     not is up to the driver.
     @return:   If successful, ERESULT_SUCCESSFUL_COMPLETION,
                otherwise any of the ERESULT error codes.
     */
    ERESULT         devBase_Write(
        DEVBASE_DATA	*this,
        uint32_t        amt,
        void            *pData,
        uint32_t        *pAmtWritten
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DEVBASE_H */

