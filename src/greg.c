// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   greg.c
 *	Generated 05/14/2015 06:34:33
 *
 * Created on December 30, 2014
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include "greg_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    static
    uint8_t     daysInMonth[12] = {
        31,28,31,30,31,30,31,31,30,30,30,31
    };
    

#ifdef XYZZY
    static
    uint16_t    daysInYear[12] = {
        0,31,59,90,120,151,181,212,243,273,304,334
    };
#endif
    
    

 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    GREG_DATA *     greg_Alloc(
    )
    {
        GREG_DATA       *this;
        uint32_t        cbSize = sizeof(GREG_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    //                     D a y  O f  W e e k
    //---------------------------------------------------------------
    
    uint8_t         greg_DayOfWeek(
        uint16_t        mm,
        uint16_t        dd,
        uint16_t        yyyy
    )
    {
        // wikipedia.org day of week
        return (dd+=mm<3?yyyy--:yyyy-2.23*mm/9+dd+4+yyyy/4-yyyy/100+yyyy/400) % 7;
    }
    
    
    
    //---------------------------------------------------------------
    //                     I s L e a p Y e a r
    //---------------------------------------------------------------
    
    bool            greg_IsLeapYear(
        uint16_t        yyyy
    )
    {
        bool            fRc;
        
        fRc = ((yyyy % 4) == 0);
        if ((yyyy % 100) == 0) {
            if ((yyyy % 400) == 0)
                ;
            else
                fRc = false;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     I s V a l i d
    //---------------------------------------------------------------
    
    bool            greg_IsValid(
        uint16_t        mm,
        uint16_t        dd,
        uint16_t        yyyy
    )
    {
        bool            fLeap = greg_IsLeapYear(yyyy);
        uint16_t        days;
        
        if ((mm >= 1) && (mm <= 12))
            ;
        else
            return false;
        
        days = daysInMonth[mm - 1];
        if ((mm == 2) && fLeap) {
            ++days;
        }

        if ((dd >= 1) && (dd <= days))
            ;
        else
            return false;
        
        // Return to caller.
        return true;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        greg_getPriority(
        GREG_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !greg_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            greg_setPriority(
        GREG_DATA       *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !greg_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        //this->priority = value;
        return true;
    }


    
    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            greg_Dealloc(
        OBJ_ID          objId
    )
    {
        GREG_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !greg_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    GREG_DATA *     greg_Init(
        GREG_DATA       *this
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_GREG );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&greg_Vtbl);
        
        //this->priority  = TNEO_PRIORITY_NORMAL;

    #ifdef NDEBUG
    #else
        if( !greg_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       J u l i a n  D a y
    //---------------------------------------------------------------
    
    uint32_t        greg_JulianDay(
        GREG_DATA		*this
    )
    {
        uint32_t        t1;
        uint32_t        jd;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !greg_Validate(this) ) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        t1 = (this->mm - 14L) / 12L;
        jd = (this->dd - 32075L)
           + ((1461L * (this->yyyy + 4800 + t1)) / 4L)
           + (367L * (this->mm - 2L - t1 * 12L) / 12L)
           - (3L * ((this->yyyy + 4900L + t1) / 100L) / 4L);
        
        // Return to caller.
        return jd;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          greg_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        GREG_DATA       *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !greg_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'T':
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return greg_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     greg_ToJSON(
        GREG_DATA       *this
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !greg_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{\"objectType\":\"%s\", \"day\":%d, \"month\":%d, \"year\":%d",
                     pInfo->pClassName,
                     this->dd,
                     this->mm,
                     this->yyyy
                     );
        AStr_AppendA(pStr, str);
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            greg_Validate(
        GREG_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_GREG) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(GREG_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


