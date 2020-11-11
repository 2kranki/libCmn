// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   DateTime.c
 *	Generated 01/29/2020 13:34:28
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
#include        <DateTime_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //****************************************************************
    //            Convert from Gregorian Date to Julian
    //****************************************************************

    ERESULT         DateTime_FromGregorian(
        int16_t         iYear,
        int16_t         iMonth,
        int16_t         iDay,
        int16_t            *piJulianDay
    )
    {
        ERESULT            eRc = ERESULT_SUCCESS;
        long            T1;
        int32_t            Work = 0;

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
    //            Convert from HH:MM:SS to Milliseconds
    //****************************************************************

    ERESULT         DateTime_FromHHMMSS(
        int16_t         Hour,
        int16_t         Minute,
        int16_t         Second,
        int16_t            Milli,
        int32_t            *pMilSec
    )
    {
        ERESULT            eRc = ERESULT_SUCCESS;
        int32_t            Work = 0;

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
    //            Convert from Julian Date to Gregorian
    //****************************************************************

    ERESULT         DateTime_ToGregorian(
        int32_t         JulNum,
        int16_t         *pDay,
        int16_t         *pMonth,
        int16_t         *pYear
    )
    {
        ERESULT            eRc = ERESULT_SUCCESS;
        long            t1;
        long            t2;
        long            mo;
        long            yr;
        long            wrk;

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
    //            Convert from Milliseconds to HH:MM:SS
    //****************************************************************

    ERESULT         DateTime_ToHHMMSS(
        int32_t         milSec,
        int16_t         *Hour,
        int16_t         *Minute,
        int16_t         *Second,
        int16_t            *Milli
    )
    {
        ERESULT            eRc = ERESULT_SUCCESS;
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

    ERESULT         DateTime_FromUInt64(
        uint64_t        time,
        int16_t         *pYear,
        int16_t         *pMonth,
        int16_t         *pDay,
        int16_t         *pHours,
        int16_t         *pMins,
        int16_t         *pSecs,
        int16_t            *pMilli
    )
    {
        ERESULT            eRc = ERESULT_SUCCESS;
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



    ERESULT         DateTime_ToUInt64(
        int16_t         year,
        int16_t         month,
        int16_t         day,
        int16_t         hours,
        int16_t         mins,
        int16_t         secs,
        int16_t            milli,
        uint64_t        *pTime
    )
    {
        ERESULT            eRc = ERESULT_SUCCESS;
        uint32_t        work1 = 0;
        uint32_t        work2 = 0;
        uint64_t        work = 0;

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

    DATETIME_DATA *     DateTime_Alloc (
        void
    )
    {
        DATETIME_DATA       *this;
        uint32_t        cbSize = sizeof(DATETIME_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    DATETIME_DATA *     DateTime_New (
        void
    )
    {
        DATETIME_DATA       *this;
        
        this = DateTime_Alloc( );
        if (this) {
            this = DateTime_Init(this);
        } 
        return this;
    }


    DATETIME_DATA *     DateTime_NewCurrent(
    )
    {
        DATETIME_DATA       *this;
        time_t              current;
        struct tm           *pTime;
        ERESULT             eRc;

        this = DateTime_Alloc( );
        if (this) {
            this = DateTime_Init(this);
            if (this) {
                current = time(NULL);
                pTime = gmtime(&current);
                pTime->tm_year += 1900;
                ++pTime->tm_mon;
                eRc =   DateTime_ToUInt64(
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



    DATETIME_DATA *     DateTime_NewFromTimeT(
        const
        time_t              time
    )
    {
        DATETIME_DATA       *this;
        struct tm           *pTime;
        ERESULT             eRc;
        struct tm           tmWork;

        this = DateTime_Alloc( );
        if (this) {
            this = DateTime_Init(this);
            if (this) {
                pTime = gmtime_r(&time, &tmWork);
                pTime->tm_year += 1900;
                ++pTime->tm_mon;
                eRc =   DateTime_ToUInt64(
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

        int16_t         DateTime_getDay(
            DATETIME_DATA   *this
        )
        {
            ERESULT         eRc;
            int16_t         value = 0;

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return 0;
            }
    #endif

            eRc = DateTime_FromUInt64(this->time, NULL, NULL, &value, NULL, NULL, NULL, NULL);

            return value;
        }


        bool            DateTime_setDay(
            DATETIME_DATA   *this,
            int16_t         value
        )
        {
            ERESULT         eRc;
            int16_t         year;
            int16_t         month;
            int16_t         day;
            int16_t         hour;
            int16_t         minute;
            int16_t         second;
            int16_t            milli;

    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return false;
            }
            if ((value < 1) || (value > 31)) {
                DEBUG_BREAK();
                return false;
            }
    #endif

            eRc =   DateTime_FromUInt64(
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
            eRc =   DateTime_ToUInt64(
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



        int16_t         DateTime_getMonth(
            DATETIME_DATA   *this
        )
        {
            ERESULT         eRc;
            int16_t         value = 0;

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return 0;
            }
    #endif

            eRc = DateTime_FromUInt64(this->time, NULL, &value, NULL, NULL, NULL, NULL, NULL);

            return value;
        }


        bool            DateTime_setMonth(
            DATETIME_DATA   *this,
            int16_t         value
        )
        {
            ERESULT         eRc;
            int16_t         year;
            int16_t         month;
            int16_t         day;
            int16_t         hour;
            int16_t         minute;
            int16_t         second;
            int16_t            milli;

    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return false;
            }
            if ((value < 1) || (value > 12)) {
                DEBUG_BREAK();
                return false;
            }
    #endif

            eRc =   DateTime_FromUInt64(
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
            eRc =   DateTime_ToUInt64(
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



        int16_t         DateTime_getYear(
            DATETIME_DATA   *this
        )
        {
            ERESULT         eRc;
            int16_t         value = 0;

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return 0;
            }
    #endif

            eRc = DateTime_FromUInt64(this->time, &value, NULL, NULL, NULL, NULL, NULL, NULL);

            return value;
        }


        bool            DateTime_setYear(
            DATETIME_DATA   *this,
            int16_t         value
        )
        {
            ERESULT         eRc;
            int16_t         year;
            int16_t         month;
            int16_t         day;
            int16_t         hour;
            int16_t         minute;
            int16_t         second;
            int16_t            milli;

    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return false;
            }
    #endif

            eRc =   DateTime_FromUInt64(
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
            eRc =   DateTime_ToUInt64(
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



        int16_t         DateTime_getHours(
            DATETIME_DATA   *this
        )
        {
            ERESULT         eRc;
            int16_t         value = 0;

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return 0;
            }
    #endif

            eRc = DateTime_FromUInt64(this->time, NULL, NULL, NULL, &value, NULL, NULL, NULL);

            return value;
        }


        bool            DateTime_setHours(
            DATETIME_DATA   *this,
            int16_t         value
        )
        {
            ERESULT         eRc;
            int16_t         year;
            int16_t         month;
            int16_t         day;
            int16_t         hour;
            int16_t         minute;
            int16_t         second;
            int16_t            milli;

    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return false;
            }
    #endif

            eRc =   DateTime_FromUInt64(
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
            eRc =   DateTime_ToUInt64(
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



        int16_t         DateTime_getMins(
            DATETIME_DATA   *this
        )
        {
            ERESULT         eRc;
            int16_t         value = 0;

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return 0;
            }
    #endif

            eRc = DateTime_FromUInt64(this->time, NULL, NULL, NULL, NULL, &value, NULL, NULL);

            return value;
        }


        bool            DateTime_setMins(
            DATETIME_DATA   *this,
            int16_t         value
        )
        {
            ERESULT         eRc;
            int16_t         year;
            int16_t         month;
            int16_t         day;
            int16_t         hour;
            int16_t         minute;
            int16_t         second;
            int16_t            milli;

    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return false;
            }
    #endif

            eRc =   DateTime_FromUInt64(
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
            eRc =   DateTime_ToUInt64(
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



        int16_t         DateTime_getSecs(
            DATETIME_DATA   *this
        )
        {
            ERESULT         eRc;
            int16_t         value = 0;

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return 0;
            }
    #endif

            eRc = DateTime_FromUInt64(this->time, NULL, NULL, NULL, NULL, NULL, &value, NULL);

            return value;
        }


        bool            DateTime_setSecs(
            DATETIME_DATA   *this,
            int16_t         value
        )
        {
            ERESULT         eRc;
            int16_t         year;
            int16_t         month;
            int16_t         day;
            int16_t         hour;
            int16_t         minute;
            int16_t         second;
            int16_t            milli;

    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return false;
            }
    #endif

            eRc =   DateTime_FromUInt64(
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
            eRc =   DateTime_ToUInt64(
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



        int16_t         DateTime_getMilli(
            DATETIME_DATA   *this
        )
        {
            ERESULT         eRc;
            int16_t         value = 0;

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return 0;
            }
    #endif

            eRc = DateTime_FromUInt64(this->time, NULL, NULL, NULL, NULL, NULL, NULL, &value);

            return value;
        }


        bool            DateTime_setMilli(
            DATETIME_DATA   *this,
            int16_t         value
        )
        {
            ERESULT         eRc;
            int16_t         year;
            int16_t         month;
            int16_t         day;
            int16_t         hour;
            int16_t         minute;
            int16_t         second;
            int16_t            milli;

    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return false;
            }
    #endif

            eRc =   DateTime_FromUInt64(
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
            eRc =   DateTime_ToUInt64(
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



        int64_t         DateTime_getTime(
            DATETIME_DATA   *this
        )
        {

            // Validate the input parameters.
    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return 0;
            }
    #endif

            return this->time;
        }


        bool            DateTime_setTime(
            DATETIME_DATA   *this,
            int64_t         value
        )
        {

    #ifdef NDEBUG
    #else
            if( !DateTime_Validate(this) ) {
                DEBUG_BREAK();
                return false;
            }
    #endif

            this->time = value;

            return true;
        }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        DateTime_getSize (
        DATETIME_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  DateTime_getSuperVtbl (
        DATETIME_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!DateTime_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = DateTime_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another DATETIME object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         DateTime_Assign (
        DATETIME_DATA		*this,
        DATETIME_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!DateTime_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!DateTime_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        pOther->time = this->time;
        
        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             DateTime_Compare (
        DATETIME_DATA   *this,
        DATETIME_DATA   *pOther
    )
    {
        int             i = 0;
#ifdef  xyzzy
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!DateTime_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!DateTime_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        i = (int)(this->time - pOther->time);
        if (i < 0)
            i = -1;
        else if (i > 0)
            i = 1;

        return i;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        DateTime      *pCopy = DateTime_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a DATETIME object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    DATETIME_DATA *     DateTime_Copy (
        DATETIME_DATA       *this
    )
    {
        DATETIME_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!DateTime_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef DATETIME_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = DateTime_New( );
        if (pOther) {
            eRc = DateTime_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            DateTime_Dealloc (
        OBJ_ID          objId
    )
    {
        DATETIME_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!DateTime_Validate(this)) {
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
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        DateTime      *pDeepCopy = DateTime_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a DATETIME object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    DATETIME_DATA *     DateTime_DeepyCopy (
        DATETIME_DATA       *this
    )
    {
        DATETIME_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!DateTime_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = DateTime_New( );
        if (pOther) {
            eRc = DateTime_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         DateTime_Disable (
        DATETIME_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!DateTime_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         DateTime_Enable (
        DATETIME_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!DateTime_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    DATETIME_DATA *   DateTime_Init (
        DATETIME_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(DATETIME_DATA);
        //ERESULT         eRc;
        
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_DATETIME);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&DateTime_Vtbl);
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!DateTime_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
        fprintf(
                stderr, 
                "DateTime::sizeof(DATETIME_DATA) = %lu\n", 
                sizeof(DATETIME_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(DATETIME_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         DateTime_IsEnabled (
        DATETIME_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!DateTime_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = DateTime_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "DateTime", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          DateTime_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        DATETIME_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!DateTime_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(DATETIME_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)DateTime_Class();
                break;
                
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'S':
                    if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                        return &this->pSuperVtbl;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return DateTime_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return DateTime_Enable;
                        }
                        break;

#ifdef  DATETIME_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return DateTime_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return DateTime_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return DateTime_ToDebugString;
                        }
#ifdef  DATETIME_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return DateTime_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == DateTime_ToDebugString)
                    return "ToDebugString";
#ifdef  DATETIME_JSON_SUPPORT
                if (pData == DateTime_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = DateTime_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     DateTime_ToDebugString (
        DATETIME_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t         hours;
        int16_t         mins;
        int16_t         secs;
        int16_t         milli;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!DateTime_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    DateTime_getSize(this),
                    obj_getRetainCount(this)
            );

        eRc =   DateTime_FromUInt64(
                                    this->time,
                                    &year,
                                    &month,
                                    &day,
                                    &hours,
                                    &mins,
                                    &secs,
                                    &milli
                );
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "\t%04d/%2d/%2d %3d:%02d:%02d.%03d\n",
                    year,
                    month,
                    day,
                    hours,
                    mins,
                    secs,
                    milli
            );

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    ASTR_DATA *     DateTime_ToFileString(
        DATETIME_DATA      *this
    )
    {
        ASTR_DATA       *pStr;
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t         hours;
        int16_t         mins;
        int16_t         secs;
        int16_t            milli;

#ifdef NDEBUG
#else
        if( !DateTime_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        eRc =   DateTime_FromUInt64(
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
        AStr_AppendPrint(
                         pStr,
                         "%04d.%02d.%02d_%02d.%02d.%02d.%03d",
                         year,
                         month,
                         day,
                         hours,
                         mins,
                         secs,
                         milli
                         );

        return pStr;
    }



    ASTR_DATA *     DateTime_ToString(
        DATETIME_DATA      *this
    )
    {
        ASTR_DATA       *pStr;
        ERESULT         eRc;
        int16_t         year;
        int16_t         month;
        int16_t         day;
        int16_t         hours;
        int16_t         mins;
        int16_t         secs;
        int16_t            milli;

#ifdef NDEBUG
#else
        if( !DateTime_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        eRc =   DateTime_FromUInt64(
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
        AStr_AppendPrint(
                     pStr,
                     "%2d/%2d/%04d %2d:%02d:%02d.%03d",
                     month,
                     day,
                     year,
                     hours,
                     mins,
                     secs,
                     milli
        );

        return pStr;
    }




    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            DateTime_Validate (
        DATETIME_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_DATETIME))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(DATETIME_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


