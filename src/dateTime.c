// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   dateTime.c
 *	Generated 08/25/2016 08:11:34
 *
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
#include "dateTime_internal.h"
#include <time.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //****************************************************************
    //			Convert from Gregorian Date to Julian
    //****************************************************************
    
    ERESULT         dateTime_FromGregorian(
        int16_t     	iYear,
        int16_t     	iMonth,
        int16_t     	iDay,
        int16_t			*piJulianDay
    )
    {
        ERESULT			eRc = ERESULT_SUCCESS;
        long            T1;
        int32_t			Work = 0;
        
        // Do initialization.
        if( piJulianDay )
            *piJulianDay = 0;
        if( (iDay < 1) || (iDay > 31) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (iMonth < 1) || (iMonth > 12) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        
        // Do the conversion.
        T1 = (iMonth - 14L) / 12L;
        Work = (int32_t)((iDay - 32075L)
                + ((1461L * (iYear + 4800 + T1)) / 4L)
                + (367L * (iMonth - 2L - T1 * 12L) / 12L)
                - (3L * ((iYear + 4900L + T1) / 100L) / 4L));
        
        // Return to caller.
        eRc = ERESULT_SUCCESS;
    Exit00:
        if( piJulianDay )
            *piJulianDay = Work;
        return eRc;
    }
    
    
    
    
    //****************************************************************
    //			Convert from HH:MM:SS to Milliseconds
    //****************************************************************
    
    ERESULT         dateTime_FromHHMMSS(
        int16_t     	Hour,
        int16_t     	Minute,
        int16_t     	Second,
        int16_t			Milli,
        int32_t			*pMilSec
    )
    {
        ERESULT			eRc = ERESULT_SUCCESS;
        int32_t			Work = 0;
        
        // Do initialization.
        if( (Hour < 0) || (Hour > 24) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (Minute < 0) || (Minute > 59) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (Second < 0) || (Second > 59) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (Milli < 0) || (Milli > 999) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        
        // Do the conversion.
        Work += 60 * Hour;
        Work += Minute;
        Work *= 60;
        Work += Second;
        Work *= 1000;
        Work += Milli;
        
        // Return to caller.
        eRc = ERESULT_SUCCESS;
    Exit00:
        if( pMilSec )
            *pMilSec = Work;
        return eRc;
    }
    
    
    
    
    //****************************************************************
    //			Convert from Julian Date to Gregorian
    //****************************************************************
    
    ERESULT         dateTime_ToGregorian(
        int32_t         JulNum,
        int16_t         *pDay,
        int16_t         *pMonth,
        int16_t         *pYear
    )
    {
        ERESULT			eRc = ERESULT_SUCCESS;
        long            t1;
        long            t2;
        long            mo;
        long            yr;
        long			wrk;
        
        // Do initialization.
        
        // Do the conversion.
#ifdef  XXX
        t1 = JulDay + 68569L;
        t2 = (4L * t1) / 146097L;
        t1 = t1 - (((146097L * t2) + 3L) / 4L);
        yr = (4000L * (t1 + 1L)) / 1461001L;
        t1 = t1 - ((1461L * yr) / 4L) + 31L;
        mo = (80L * t1) / 2447L;
        *pDay = (int16_t)(t1 - ((2447L * mo) / 80L));
        t1 = mo / 11L;
        *pMonth = (int16_t)(mo + 2L - (12L * t1));
        *pYear = (int16_t)((100L * (t2 - 49L)) + yr + t1);
#else
        t1 = JulNum + 68569L;
        t2 = 4L * t1 / 146097L;
        t1 = t1 - (146097L * t2 + 3L) / 4L;
        yr = 4000L * (t1 + 1L) / 1461001L;
        t1 = t1 - 1461L * yr / 4L + 31L;
        mo = 80L * t1 / 2447L;
        if( pDay ) {
            wrk  = t1 - ((2447L * mo) / 80L);
            *pDay = (int16_t)wrk;
        }
        t1 = mo / 11L;
        if( pMonth ) {
            wrk    = mo + 2L - 12L * t1;
            *pMonth = (int16_t)wrk;
        }
        if( pYear ) {
            wrk   = 100L * (t2 - 49L) + yr + t1;
            *pYear = (int16_t)wrk;
        }
#endif
        
        // Return to caller.
        return eRc;
    }
    
    
    
    
    //****************************************************************
    //			Convert from Milliseconds to HH:MM:SS
    //****************************************************************
    
    ERESULT         dateTime_ToHHMMSS(
        int32_t         milSec,
        int16_t         *Hour,
        int16_t         *Minute,
        int16_t         *Second,
        int16_t			*Milli
    )
    {
        ERESULT			eRc = ERESULT_SUCCESS;
        int32_t         Work = milSec;
        
        // Do initialization.
        
        // Do the conversion.
        if( Milli )
            *Milli = (int16_t)(Work % 1000);
        Work /= 1000;
        if( Second )
            *Second = (int16_t)(Work % 60);
        Work /= 60;
        if( Minute )
            *Minute = (int16_t)(Work % 60);
        Work /= 60;
        if( Hour )
            *Hour = (int16_t)(Work % 24);
        
        // Return to caller.
        return( eRc );
    }
    
    
    
    //****************************************************************
    //                  Convert to/from uint64
    //****************************************************************
    
    ERESULT         dateTime_FromUInt64(
        uint64_t		time,
        int16_t         *pYear,
        int16_t         *pMonth,
        int16_t         *pDay,
        int16_t     	*pHours,
        int16_t     	*pMins,
        int16_t     	*pSecs,
        int16_t			*pMilli
    )
    {
        ERESULT			eRc = ERESULT_SUCCESS;
        uint32_t        work1 = 0;
        uint32_t        work2 = 0;
        
        // Do initialization.
        work1 = (uint32_t)(time / 1000000000ULL);
        work2 = (uint32_t)(time % 1000000000ULL);
        
        // Do the conversion.
        if( pDay ) {
            *pDay = (int16_t)(work1 % 100);
        }
        work1 /= 100;
        if( pMonth ) {
            *pMonth = (int16_t)(work1 % 100);
        }
        work1 /= 100;
        if( pYear ) {
            *pYear = (int16_t)(work1);
        }
        if( pMilli ) {
            *pMilli = (int16_t)(work2 % 1000);
        }
        work2 /= 1000;
        if( pSecs ) {
            *pSecs = (int16_t)(work2 % 60);
        }
        work2 /= 60;
        if( pMins ) {
            *pMins = (int16_t)(work2 % 60);
        }
        work2 /= 60;
        if( pHours ) {
            *pHours = (int16_t)(work2 % 24);
        }
        
        // Return to caller.
        eRc = ERESULT_SUCCESS;
    //Exit00:
        return eRc;
    }
    
    
    
    ERESULT         dateTime_ToUInt64(
        int16_t         year,
        int16_t         month,
        int16_t         day,
        int16_t     	hours,
        int16_t     	mins,
        int16_t     	secs,
        int16_t			milli,
        uint64_t		*pTime
    )
    {
        ERESULT			eRc = ERESULT_SUCCESS;
        uint32_t        work1 = 0;
        uint32_t        work2 = 0;
        uint64_t		work = 0;
        
        // Do initialization.
        if( (month < 1) || (month > 12) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (day < 1) || (day > 31) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (hours < 0) || (hours > 24) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (mins < 0) || (mins > 59) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (secs < 0) || (secs > 59) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        if( (milli < 0) || (milli > 999) ) {
            eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        
        // Do the conversion.
        work1 += year;
        work1 *= 100;
        work1 += month;
        work1 *= 100;
        work1 += day;
        work2 += 60 * hours;
        work2 += mins;
        work2 *= 60;
        work2 += secs;
        work2 *= 1000;
        work2 += milli;
        
        // Return to caller.
        work = (work1 * 1000000000ULL) + work2;
        eRc = ERESULT_SUCCESS;
    Exit00:
        if( pTime )
            *pTime = work;
        return eRc;
    }
    
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    DATETIME_DATA *     dateTime_Alloc(
    )
    {
        DATETIME_DATA   *this;
        uint32_t        cbSize = sizeof(DATETIME_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    DATETIME_DATA *     dateTime_New(
    )
    {
        DATETIME_DATA       *this;
        
        this = dateTime_Alloc( );
        if (this) {
            this = dateTime_Init(this);
        } 
        return this;
    }



    DATETIME_DATA *     dateTime_NewCurrent(
    )
    {
        DATETIME_DATA       *this;
        time_t              current;
        struct tm           *pTime;
        ERESULT             eRc;
        
        this = dateTime_Alloc( );
        if (this) {
            this = dateTime_Init(this);
            if (this) {
                current = time(NULL);
                pTime = gmtime(&current);
                pTime->tm_year += 1900;
                ++pTime->tm_mon;
                eRc =   dateTime_ToUInt64(
                                    pTime->tm_year,
                                    pTime->tm_mon,
                                    pTime->tm_mday,
                                    pTime->tm_hour,
                                    pTime->tm_min,
                                    pTime->tm_sec,
                                    0,
                                    &this->time
                        );
            }
        }
        return this;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    int16_t         dateTime_getDay(
        DATETIME_DATA   *this
    )
    {
        ERESULT         eRc;
        int16_t         value = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        eRc = dateTime_FromUInt64(this->time, NULL, NULL, &value, NULL, NULL, NULL, NULL);

        return value;
    }

    
    bool            dateTime_setDay(
        DATETIME_DATA   *this,
        int16_t         value
    )
    {
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t     	hour;
        int16_t     	minute;
        int16_t     	second;
        int16_t			milli;

#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if ((value < 1) || (value > 31)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        eRc =   dateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hour,
                                    &minute,
                                    &second,
                                    &milli
                );
        day = value;
        eRc =   dateTime_ToUInt64(
                                    year,
                                    month,
                                    day,
                                    hour,
                                    minute,
                                    second,
                                    milli,
                                    &this->time
                );

        return true;
    }



    int16_t         dateTime_getMonth(
        DATETIME_DATA   *this
    )
    {
        ERESULT         eRc;
        int16_t         value = 0;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        eRc = dateTime_FromUInt64(this->time, NULL, &value, NULL, NULL, NULL, NULL, NULL);
        
        return value;
    }
    
    
    bool            dateTime_setMonth(
        DATETIME_DATA   *this,
        int16_t         value
    )
    {
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t     	hour;
        int16_t     	minute;
        int16_t     	second;
        int16_t			milli;
        
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if ((value < 1) || (value > 12)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        eRc =   dateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hour,
                                    &minute,
                                    &second,
                                    &milli
                                    );
        month = value;
        eRc =   dateTime_ToUInt64(
                                  year,
                                  month,
                                  day,
                                  hour,
                                  minute,
                                  second,
                                  milli,
                                  &this->time
                                  );
        
        return true;
    }
    
    
    
    int16_t         dateTime_getYear(
        DATETIME_DATA   *this
    )
    {
        ERESULT         eRc;
        int16_t         value = 0;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        eRc = dateTime_FromUInt64(this->time, &value, NULL, NULL, NULL, NULL, NULL, NULL);
        
        return value;
    }
    
    
    bool            dateTime_setYear(
        DATETIME_DATA   *this,
        int16_t         value
    )
    {
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t     	hour;
        int16_t     	minute;
        int16_t     	second;
        int16_t			milli;
        
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        eRc =   dateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hour,
                                    &minute,
                                    &second,
                                    &milli
                                    );
        year = value;
        eRc =   dateTime_ToUInt64(
                                  year,
                                  month,
                                  day,
                                  hour,
                                  minute,
                                  second,
                                  milli,
                                  &this->time
                                  );
        
        return true;
    }
    
    
    
    int16_t         dateTime_getHours(
        DATETIME_DATA   *this
    )
    {
        ERESULT         eRc;
        int16_t         value = 0;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        eRc = dateTime_FromUInt64(this->time, NULL, NULL, NULL, &value, NULL, NULL, NULL);
        
        return value;
    }
    
    
    bool            dateTime_setHours(
        DATETIME_DATA   *this,
        int16_t         value
    )
    {
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t     	hour;
        int16_t     	minute;
        int16_t     	second;
        int16_t			milli;
        
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        eRc =   dateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hour,
                                    &minute,
                                    &second,
                                    &milli
                                    );
        hour = value;
        eRc =   dateTime_ToUInt64(
                                  year,
                                  month,
                                  day,
                                  hour,
                                  minute,
                                  second,
                                  milli,
                                  &this->time
                                  );
        
        return true;
    }
    
    
    
    int16_t         dateTime_getMins(
        DATETIME_DATA   *this
    )
    {
        ERESULT         eRc;
        int16_t         value = 0;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        eRc = dateTime_FromUInt64(this->time, NULL, NULL, NULL, NULL, &value, NULL, NULL);
        
        return value;
    }
    
    
    bool            dateTime_setMins(
        DATETIME_DATA   *this,
        int16_t         value
    )
    {
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t     	hour;
        int16_t     	minute;
        int16_t     	second;
        int16_t			milli;
        
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        eRc =   dateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hour,
                                    &minute,
                                    &second,
                                    &milli
                                    );
        minute = value;
        eRc =   dateTime_ToUInt64(
                                  year,
                                  month,
                                  day,
                                  hour,
                                  minute,
                                  second,
                                  milli,
                                  &this->time
                                  );
        
        return true;
    }
    
    
    
    int16_t         dateTime_getSecs(
        DATETIME_DATA   *this
    )
    {
        ERESULT         eRc;
        int16_t         value = 0;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        eRc = dateTime_FromUInt64(this->time, NULL, NULL, NULL, NULL, NULL, &value, NULL);
        
        return value;
    }
    
    
    bool            dateTime_setSecs(
        DATETIME_DATA   *this,
        int16_t         value
    )
    {
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t     	hour;
        int16_t     	minute;
        int16_t     	second;
        int16_t			milli;
        
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        eRc =   dateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hour,
                                    &minute,
                                    &second,
                                    &milli
                                    );
        day = value;
        eRc =   dateTime_ToUInt64(
                                  year,
                                  month,
                                  day,
                                  hour,
                                  minute,
                                  second,
                                  milli,
                                  &this->time
                                  );
        
        return true;
    }
    
    
    
    int16_t         dateTime_getMilli(
        DATETIME_DATA   *this
    )
    {
        ERESULT         eRc;
        int16_t         value = 0;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        eRc = dateTime_FromUInt64(this->time, NULL, NULL, NULL, NULL, NULL, NULL, &value);
        
        return value;
    }
    
    
    bool            dateTime_setMilli(
        DATETIME_DATA   *this,
        int16_t         value
    )
    {
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t     	hour;
        int16_t     	minute;
        int16_t     	second;
        int16_t			milli;
        
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        eRc =   dateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hour,
                                    &minute,
                                    &second,
                                    &milli
                                    );
        milli = value;
        eRc =   dateTime_ToUInt64(
                                  year,
                                  month,
                                  day,
                                  hour,
                                  minute,
                                  second,
                                  milli,
                                  &this->time
                                  );
        
        return true;
    }
    
    
    
    int64_t         dateTime_getTime(
        DATETIME_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->time;
    }
    
    
    bool            dateTime_setTime(
        DATETIME_DATA   *this,
        int64_t         value
    )
    {
        
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->time = value;
        
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         dateTime_Assign(
        DATETIME_DATA		*this,
        DATETIME_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !dateTime_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Copy other data from this object to other.
        pOther->time = this->time;
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    DATETIME_DATA * dateTime_Copy(
        DATETIME_DATA   *this
    )
    {
        DATETIME_DATA   *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = dateTime_New();
        if (pOther) {
            eRc = dateTime_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            dateTime_Dealloc(
        OBJ_ID          objId
    )
    {
        DATETIME_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((DATETIME_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            dateTime_Disable(
        DATETIME_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    bool            dateTime_Enable(
        DATETIME_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    DATETIME_DATA *   dateTime_Init(
        DATETIME_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(DATETIME_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_DATETIME);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_DATETIME); // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&dateTime_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            dateTime_IsEnabled(
        DATETIME_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(this))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          dateTime_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    )
    {
        DATETIME_DATA   *this = objId;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
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
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return dateTime_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pStr);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     dateTime_ToDebugString(
        DATETIME_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t     	hours;
        int16_t     	mins;
        int16_t     	secs;
        int16_t			milli;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        eRc =   dateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hours,
                                    &mins,
                                    &secs,
                                    &milli
                );
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(DateTime) %04d/%2d/%2d %3d:%02d:%02d.%03d ",
                     this,
                     year,
                     month,
                     day,
                     hours,
                     mins,
                     secs,
                     milli
            );
        AStr_AppendA(pStr, str);

        j = snprintf(str, sizeof(str), " %p(DateTime)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    ASTR_DATA *     dateTime_ToString(
        DATETIME_DATA      *this
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t     	hours;
        int16_t     	mins;
        int16_t     	secs;
        int16_t			milli;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        eRc =   dateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hours,
                                    &mins,
                                    &secs,
                                    &milli
                                    );
        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "%2d/%2d/%04d %2d:%02d:%02d.%03d",
                     month,
                     day,
                     year,
                     hours,
                     mins,
                     secs,
                     milli
                     );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    ASTR_DATA *     dateTime_ToJSON(
        DATETIME_DATA      *this
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !dateTime_Validate(this) ) {
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
                     "{\"objectType\":\"%s\", \"time\":%llu",
                     pInfo->pClassName,
                     this->time
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
    bool            dateTime_Validate(
        DATETIME_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_DATETIME) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(DATETIME_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


