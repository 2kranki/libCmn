// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          AUDIOWAV Console Transmit Task (audioWAV) Header
//****************************************************************
/*
 * Program
 *			Separate audioWAV (audioWAV)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate audioWAV to run things without complications
 *          of interfering with the main audioWAV. A audioWAV may be 
 *          called a audioWAV on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal audioWAV. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	09/19/2016 Generated
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


#ifndef         AUDIOWAV_H
#define         AUDIOWAV_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct audioWAV_data_s	AUDIOWAV_DATA;    // Inherits from OBJ.

    typedef struct audioWAV_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in audioWAV_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(AUDIOWAV_DATA *);
    } AUDIOWAV_VTBL;



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
     @return:   pointer to audioWAV object if successful, otherwise OBJ_NIL.
     */
    AUDIOWAV_DATA *     audioWAV_Alloc(
        void
    );
    
    
    AUDIOWAV_DATA *     audioWAV_New(
        void
    );
    
    AUDIOWAV_DATA *     audioWAV_NewWithParameters(
        uint8_t         numberOfChannels,
        uint32_t        samplesPerSecond,   // Normally 11025, 22050, 44100
        uint16_t        sampleSize          // Normally 8, 16, or 32
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     audioWAV_getLastError(
        AUDIOWAV_DATA		*this
    );


    uint16_t        audioWAV_getNumberOfChannels(
        AUDIOWAV_DATA   *this
    );
    
    
    uint32_t        audioWAV_getSamplesPerSec(
        AUDIOWAV_DATA   *this
    );
    
    
    uint16_t        audioWAV_getSampleSize(
        AUDIOWAV_DATA   *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         audioWAV_Append(
        AUDIOWAV_DATA	*this,
        AUDIOWAV_DATA	*pOther
    );
    
    
    ERESULT         audioWAV_AppendFrame(
        AUDIOWAV_DATA   *this,
        int32_t         leftFront,
        int32_t         rightFront,
        int32_t         center,
        int32_t         leftRear,
        int32_t         rightRear,
        int32_t         surround
    );
    
    
    ERESULT         audioWAV_AppendSilence(
        AUDIOWAV_DATA	*this,
        uint32_t		nMilli              // Number of Milliseconds
    );
    
    
    ERESULT         audioWAV_AppendSineWave(
        AUDIOWAV_DATA	*this,
        uint16_t		cFreq,              // Frequency (20Hz..20,000Hz)
        uint32_t		cMilli              // Number of Milliseconds
    );
    
    
    AUDIOWAV_DATA * audioWAV_Init(
        AUDIOWAV_DATA   *this
    );
    
    
    AUDIOWAV_DATA *   audioWAV_InitWithParameters(
        AUDIOWAV_DATA     *this,
        uint8_t         numberOfChannels,
        uint32_t        samplesPerSecond,   // Normally 11025, 22050, 44100
        uint16_t        sampleSize          // Normally 8, 16, or 32
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = audioWAV_ToDebugString(this,4);
     @endcode
     @param     this    AUDIOWAV object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    audioWAV_ToDebugString(
        AUDIOWAV_DATA     *this,
        int             indent
    );
    
    
    ERESULT     audioWAV_WriteToFile(
        AUDIOWAV_DATA	*this,
        PATH_DATA       *pPath
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* AUDIOWAV_H */

