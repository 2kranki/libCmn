// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/* 
 * File:   trctbl_internal.h
 * Author: bob
 *
 * Notes:
 *   1	Before including define the following to customize the config bits for
 *		the development environment needed:
 *		_EXPLORER_16		Microchip Explorer 16 board
 *		_MAX32              Diligent MAX 32 board
 *		_NETWORK_SHIELD     Diligent Network Shield
 *
 * Created on December 26, 2014
 */

/*
 * COPYRIGHT  - (C) Copyright 2015  BY Robert White Services, LLC
 *             This computer software is the proprietary information
 *             of Robert White Services, LLC and is subject to a
 *             License Agreement between the user hereof and Robert
 *             White Services, LLC. All concepts, programs, tech-
 *             niques,  object code  and  source code are the Trade
 *             Secrets of Robert White Services, LLC.
 */






#ifndef TRCTBL_INTERNAL_H
#define	TRCTBL_INTERNAL_H


#include    <cmn_defs.h>
#include    <trctbl.h>


#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push,1)
    struct trctbl_data_s	{
        /* Warning - OBJ_DATA must be first in this object!
         */
        OBJ_DATA        super;
#define TRCTBL_FLAG_LOCKED      4
#define TRCTBL_FLAG_IGNORE      5   /* Ignore any adds or puts */
        
        // Common Data
#ifdef USE_PIC32
        struct TN_Mutex lock;
#endif

        uint16_t        size;
        uint16_t        end;
        uint32_t        numWritten;
        TRCTBL_ENTRY    entries[0];

    };
#pragma pack()


    extern
    const
    OBJ_IUNKNOWN    trctbl_Vtbl;

    
    

// Internal Functions
#ifdef RMW_DEBUG
bool			trctbl_Validate(
	TRCTBL_DATA       *cbp
);
#endif

    void            trctbl_Dealloc(
        OBJ_ID          objId
    );
    


#ifdef	__cplusplus
}
#endif

#endif	/* TRCTBL_INTERNAL_H */

