// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   bptree_internal.h
 *	Generated 03/05/2017 10:40:41
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



#include    <bptree.h>


#ifndef BPTREE_INTERNAL_H
#define	BPTREE_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct bptree_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    uint16_t        size;		/* maximum number of elements           */
    uint16_t        reserved;
    ASTR_DATA       *pStr;

    volatile
    int32_t         numRead;
    // WARNING - 'elems' must be last element of this structure!
    uint32_t        elems[0];

};
#pragma pack(pop)

    extern
    const
    struct bptree_class_data_s  bptree_ClassObj;

    extern
    const
    BPTREE_VTBL         bptree_Vtbl;


    // Internal Functions
    void            bptree_Dealloc(
        OBJ_ID          objId
    );

    bool            bptree_setLastError(
        BPTREE_DATA     *this,
        ERESULT         value
    );




#ifdef NDEBUG
#else
    bool			bptree_Validate(
        BPTREE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BPTREE_INTERNAL_H */

