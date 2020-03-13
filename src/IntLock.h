// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Internal Lock (IntLock) Header
//****************************************************************
/*
 * Program
 *			Internal Lock (IntLock)
 * Purpose
 *			This object provides a standardized lock for use within
 *          the objects.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	03/13/2020 Generated
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


#ifndef         INTLOCK_H
#define         INTLOCK_H






#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct IntLock_data_s	{
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        pthread_mutex_t mutex;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        struct TN_Mutex mutex;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        CRITICAL_SECTION
                        csSem;
#endif
        volatile
        bool            fLocked;
        volatile
        bool            fAlloc;
    } INTLOCK_DATA;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

   /*!
     Allocate a Lock data area.
     @return    pointer to IntLock Data Area if successful, otherwise 
                OBJ_NIL.
     @warning   The area returned must be freed with IntLock_Free() 
                when it is no longer needed.
     */
    INTLOCK_DATA *  IntLock_Alloc (
        void
    );
    
    
   /*!
     Free a Lock data area. The internal lock will be terminated before
     the area is released. The area will only be freed if the boolean
     variable, fAlloc, is true. This should be called by Lock creator
     when the Lock is no longer needed whether IntLock_Alloc() was
     used to allocate the lock or not. 
     @return    OBJ_NIL
     */
    INTLOCK_DATA *  IntLock_Free (
        INTLOCK_DATA	*this
    );
    
    


    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

   /*!
     Initialize the Lock Data Area with respect to the current operating
     environment.
     @return    pointer to IntLock Data Area if successful, otherwise 
                OBJ_NIL.
     @warning   It is assumed that the IntLock Data Area is initialized
                to binary zeroes on entry to this method.
     */
    INTLOCK_DATA *  IntLock_Init (
        INTLOCK_DATA    *this
    );


    ERESULT         IntLock_IsLocked (
        INTLOCK_DATA	*this
    );

   
    ERESULT         IntLock_Lock (
        INTLOCK_DATA	*this
    );

   
    ERESULT         IntLock_TryLock (
        INTLOCK_DATA	*this
    );

   
    ERESULT         IntLock_Unlock (
        INTLOCK_DATA	*this
    );
    
 

    
#ifdef	__cplusplus
}
#endif

#endif	/* INTLOCK_H */

