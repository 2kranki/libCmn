// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   ioRcd_internal.h
 *	Generated 01/12/2017 00:06:08
 *
 * Notes:
 *  --	N/A
 *
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



#include    <ioRcd.h>


#ifndef IORCD_INTERNAL_H
#define	IORCD_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct ioRcd_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    PATH_DATA       *pPath;

};
#pragma pack(pop)

    extern
    const
    struct ioRcd_class_data_s  ioRcd_ClassObj;

    extern
    const
    IORCD_VTBL         ioRcd_Vtbl;


    // Internal Functions
    void            ioRcd_Dealloc(
        OBJ_ID          objId
    );

    bool            ioRcd_setLastError(
        IORCD_DATA     *this,
        ERESULT         value
    );




#ifdef NDEBUG
#else
    bool			ioRcd_Validate(
        IORCD_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* IORCD_INTERNAL_H */

