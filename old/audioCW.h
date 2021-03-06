// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Morse Code (CW) Generation (audioCW) Header
//****************************************************************
/*
 * Program
 *			Morse Code (CW) Generation (audioCW)
 * Purpose
 *			This object provides a way of generating WAV files
 *          containing Morse Code (CW).
 *
 * Remarks
 *	1.			All letters, both cases, and numbers are supported.
 *				Period, comma and question mark are supported.	The
 *				following denotes the more important special char-
 *				acters supported:
 *
 *					/ - |DN - _.._.
 *					- - |DU - _...._
 *					= - |BT - _..._
 *					+ - |AR - ._._.
 *					( - |KN - _.__.
 *					~ - |SK - ..._._
 *
 *				All but the '~' are normal.  I used '~' for |SK
 *				because it was not assigned a character and |SK
 *				was not assigned a character.
 *	2.			Spaces, tabs, carriage-returns and line-feeds are
 *				classified as white-space.	When white-space is
 *				encountered in a file, it will generate only one
 *				inter-word pause.  This allows you to space out
 *				your input files as you please, but does not af-
 *				fect the generated CW.
 *
 * History
 *	09/19/2016 Generated
 */


// CW Timing
//				All CW timings are based on the word, PARIS.  When PARIS is sent
//				the number of times denoted by the words per minute, the elapsed
//				time should be exactly one minute.  PARIS in CW is:
//				<Dit><Idg><Dah><Idg><Dah><Idg><Dit><Icg>
//				<Dit><Idg><Dah><Icg>
//				<Dit><Idg><Dah><Idg><Dit><Icg>
//				<Dit><Idg><Dit><Icg>
//				<Dit><Idg><Dit><Idg><Dit><Iwg>
//				On the above:
//					<Dit> is the basic element.
//					<Dah> is the other basic element (normally 3 <Dit>s in time)
//					<Idg> is the Inter-Digit Gap (normally one <Dit> in time)
//					<Icg> is the Inter-Character Gap (normally three <Dit>'s in time)
//					<Iwg> is the Inter-Word Gap (normally 7 <Dit>'s in time)
//				So, PARIS has 10 <Dit>s, 4 <Dah>s which is 22 units of time.  There
//				are 9 <Idg>s, 4 <Icg>s and 1 <Iwg> which is 28 units of time.  The
//				total being 50 units of time.
//				A unit of time for a dit is as follows:
//				WPM				Time(ms)
//				 5				  240
//				10				  120
//				12				  100
//				13				   92
//				15				   80
//				18				   67
//				20				   60
//				25				   48
//				30				   40
//				35				   34
//				40				   30
//				45				   26
//				50				   24
//				55				   21


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


#ifndef         AUDIOCW_H
#define         AUDIOCW_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct audioCW_data_s	AUDIOCW_DATA;    // Inherits from OBJ.

    typedef struct audioCW_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in audioCW_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(AUDIOCW_DATA *);
    } AUDIOCW_VTBL;



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
     @return:   pointer to audioCW object if successful, otherwise OBJ_NIL.
     */
    AUDIOCW_DATA *     audioCW_Alloc(
        void
    );
    
    
    /*!
     Checks the given character to see if it is valid for CW.
     @param     chr     the character to be checked
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* Error Code.
     */
    ERESULT         audioCW_IsValidW32(
        uint32_t        chr
    );
    
    
    AUDIOCW_DATA *     audioCW_New(
        uint8_t         numberOfChannels,
        uint32_t        samplesPerSecond,   // Normally 11025, 22050, 44100
        uint16_t        sampleSize,         // Normally 8, 16, or 32
        uint16_t		freq                // Frequency (20Hz..20,000Hz)
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        audioCW_getTone(
        AUDIOCW_DATA    *this
    );
    
    bool            audioCW_setTone(
        AUDIOCW_DATA    *this,
        uint16_t        value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         audioCW_CalculateTiming(
        AUDIOCW_DATA	*this,
        uint16_t        wpmChar,
        uint16_t        wpmText
    );
    
    
    AUDIOCW_DATA *   audioCW_Init(
        AUDIOCW_DATA     *this,
        uint8_t         numberOfChannels,
        uint32_t        samplesPerSecond,   // Normally 11025, 22050, 44100
        uint16_t        sampleSize,         // Normally 8, 16, or 32
        uint16_t		freq                // Frequency (20Hz..20,000Hz)
    );


    ERESULT         audioCW_PutTextW32(
        AUDIOCW_DATA	*this,
        uint32_t        cData,              // Length of data
        W32CHR_T        *pData
    );
    
    
    ERESULT         audioCW_PutW32(
        AUDIOCW_DATA	*this,
        W32CHR_T        chr
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = audioCW_ToDebugString(this,4);
     @endcode
     @param     this    AUDIOCW object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    audioCW_ToDebugString(
        AUDIOCW_DATA    *this,
        int             indent
    );
    
    
    ERESULT     audioCW_WriteToFile(
        AUDIOCW_DATA    *this,
        PATH_DATA       *pPath
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* AUDIOCW_H */

