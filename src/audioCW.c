// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   audioCW.c
 *	Generated 09/19/2016 20:11:01
 *
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include    "audioCW_internal.h"
#include    "WStr.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    
    const
    char            *cwCharElements[128] = {
        /* 00-07 */	"", "", "", "", "", "", "", "",
        /* 08-0F */ "", "", "", "", "", "", "", "",
        /* 10-17 */ "", "", "", "", "", "", "", "",
        /* 18-1F */ "", "", "", "", "", "", "", "",
        //          ' '  '!'  '"'        '#'  '$'         '%'  '&'  ''''
        /* 20-27 */ "", "", ".-..-.", "", "...-..-", "", "", ".-----.",
        //          '('       ')'        '*'  '+'       ','        '='        '.'        '/'
        /* 28-2F */ "-.--.", "-.--.-", "", ".-.-.", "--..--", "-....-", ".-.-.-", "-..-.",
        //          '0'       '1'       '2'       '3'       '4'       '5'       '6'       '7'
        /* 30-37 */ "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...",
        //          '8'       '9'       ':'        ';'        '<'  '='       '>'  '?'
        /* 38-3F */ "---..", "----.", "---...", "-.-.-.", "", "-...-", "", "..--..",
        //          '@'  'A'    'B'     'C'     'D'  'E'   'F'    'G'
        /* 40-47 */ "", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
        //          'H'      'I'    'J'      'K'     'L'      'M'    'N'    'O'
        /* 48-4F */ "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
        //          'P'      'Q'      'R'     'S'     'T'   'U'     'V'      'W'
        /* 50-57 */ ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
        //          'X'      'Y'      'Z'      '['  '\'  ']'  '^'  '_'
        /* 58-5F */ "-..-", "-.--", "--..", "", "", "", "", "..--.-",
        //          '`'  'a'    'b'      'c'      'd'     'e'   'f'      'g'
        /* 60-67 */ "", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
        //          'h'      'i'    'j'      'k'     'l'      'm'    'n'    'o'
        /* 68-6F */ "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
        //          'p'      'q'      'r'     's'     't'   'u'     'v'      'w'
        /* 70-77 */ ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
        //          'x'      'y'      'z'   '{' '|' '}'  '~'     DEL
        /* 78-7F */ "-..-", "-.--", "--..", "", "", "", "...-.-", ""
    };
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            audioCW_task_body(
        void            *pData
    )
    {
        //AUDIOCW_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    AUDIOCW_DATA *  audioCW_Alloc(
    )
    {
        AUDIOCW_DATA    *this;
        uint32_t        cbSize = sizeof(AUDIOCW_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ERESULT         audioCW_IsValidW32(
        uint32_t        chr
    )
    {
        const
        char            *pStr;
        
        if (chr <= 0x7F) {
        }
        else {
            return ERESULT_INVALID_PARAMETER;
        }
        pStr = cwCharElements[chr & 0x7F];
        if (strlen(pStr)) {
        }
        else {
            return ERESULT_INVALID_PARAMETER;
        }
     
        return ERESULT_SUCCESS;
    }
    
    
    
    AUDIOCW_DATA *     audioCW_New(
        uint8_t         numberOfChannels,
        uint32_t        samplesPerSecond,   // Normally 11025, 22050, 44100
        uint16_t        sampleSize,         // Normally 8, 16, or 32
        uint16_t		freq                // Frequency (20Hz..20,000Hz)
    )
    {
        AUDIOCW_DATA       *this;
        
        this = audioCW_Alloc( );
        if (this) {
            this =  audioCW_Init(
                            this,
                            numberOfChannels,
                            samplesPerSecond,
                            sampleSize,
                            freq
                    );
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         audioCW_getLastError(
        AUDIOCW_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !audioCW_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        return this->eRc;
    }



    uint16_t        audioCW_getFreq(
        AUDIOCW_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !audioCW_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->freq;
    }

    bool            audioCW_setFreq(
        AUDIOCW_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !audioCW_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->freq = value;

        return true;
    }



    AUDIOWAV_DATA * audioCW_getWave(
        AUDIOCW_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !audioCW_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pWave;
    }
    
    
    bool            audioCW_setWave(
        AUDIOCW_DATA    *this,
        AUDIOWAV_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !audioCW_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pWave) {
            obj_Release(this->pWave);
        }
        this->pWave = pValue;
        
        return true;
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
        ERESULT eRc = audioCW__Assign(this,pOther);
     @endcode
     @param     this    AUDIOCW object pointer
     @param     pOther  a pointer to another AUDIOCW object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         audioCW_Assign(
        AUDIOCW_DATA		*this,
        AUDIOCW_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !audioCW_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( !audioCW_Validate(pOther) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

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
        
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        //goto eom;

        // Return to caller.
        //this->eRc = ERESULT_SUCCESS;
        this->eRc = ERESULT_NOT_IMPLEMENTED; // <-- Remove this!
    //eom:
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //               C a l c u l a t e  T i m i n g
    //---------------------------------------------------------------
    
    ERESULT         audioCW_CalculateTiming(
        AUDIOCW_DATA	*this,
        uint16_t        wpmChar,
        uint16_t        wpmText
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !audioCW_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        if( (wpmChar < 5) || (wpmChar > 55) ) {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
        if( (wpmText < 5) || (wpmText > 55) ) {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
        if( wpmChar < wpmText ) {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
        this->wpmChar = wpmChar;
        this->wpmText = wpmText;
        
        // Calculate the Dit Time in milliseconds.
        //	timeDit = ((60 * 1000) + (60 - 1)) / (50 * ditWpm);	// 60sec -> milliseconds w/roundup
        //	timeDit = 60059 / (50 * ditWpm );
        this->timeDit = 1201 / wpmChar;
        
        // Calculate the Dah Time in milliseconds.
        this->timeDah = 3 * this->timeDit;
        
        // Calculate the Inter Gaps.
        this->timeIdg = this->timeDit;
        this->timeFrn = ((60000 * wpmChar) - (37200 * wpmText)) / (wpmChar * wpmText);
        this->timeIcg = (3 * this->timeFrn) / 19;
        this->timeIwg = (7 * this->timeFrn) / 19;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        audioCW      *pCopy = audioCW_Copy(this);
     @endcode
     @param     this    AUDIOCW object pointer
     @return    If successful, a AUDIOCW object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the AUDIOCW object.
     */
    AUDIOCW_DATA *  audioCW_Copy(
        AUDIOCW_DATA    *this
    )
    {
        AUDIOCW_DATA    *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !audioCW_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther =    audioCW_New(
                        audioWAV_getNumberOfChannels(this->pWave),
                        audioWAV_getSamplesPerSec(this->pWave),
                        audioWAV_getSampleSize(this->pWave),
                        this->freq
                    );
        if (pOther) {
            eRc = audioCW_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        this->eRc = ERESULT_SUCCESS;
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            audioCW_Dealloc(
        OBJ_ID          objId
    )
    {
        AUDIOCW_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !audioCW_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((AUDIOCW_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        audioCW_setWave(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    AUDIOCW_DATA *   audioCW_Init(
        AUDIOCW_DATA    *this,
        uint8_t         numberOfChannels,
        uint32_t        samplesPerSecond,   // Normally 11025, 22050, 44100
        uint16_t        sampleSize,         // Normally 8, 16, or 32
        uint16_t		freq                // Frequency (20Hz..20,000Hz)
    )
    {
        uint32_t        cbSize = sizeof(AUDIOCW_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_AUDIOCW);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_AUDIOCW);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&audioCW_Vtbl);
        
        this->pWave = audioWAV_New(numberOfChannels, samplesPerSecond, sampleSize);
        if (OBJ_NIL == this->pWave) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->freq = freq;

    #ifdef NDEBUG
    #else
        if( !audioCW_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      P u t  T e x t
    //---------------------------------------------------------------
    
    ERESULT         audioCW_PutTextW32(
        AUDIOCW_DATA	*this,
        uint32_t        cData,
        W32CHR_T        *pData
    )
    {
        uint32_t        i;
        uint32_t        len;
        uint32_t        cRepeat = 0;
        uint32_t        state = 1;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !audioCW_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        if (pData == OBJ_NIL) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
        len = cData;
        if (cData == 0) {
            len = WStr_StrLen(pData);
        }

        for (i=0; i<len; ++i) {
            switch (state) {
                case 1:
                    if (pData[i] == L'@') {
                        state = 2;
                        cRepeat = 0;
                    }
                    else {
                        audioCW_PutW32(this, pData[i]);
                    }
                    break;
                    
                case 2:
                    if ((pData[i] >= L'0') && (pData[i] <= L'9')) {
                        cRepeat *= 10;
                        cRepeat += pData[i] - L'0';
                        state = 2;
                    }
                    else {
                        while (cRepeat--) {
                            audioCW_PutW32(this, pData[i]);
                        }
                        state = 1;
                    }
                    break;
                    
            }
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P u t W
    //---------------------------------------------------------------
    
    ERESULT         audioCW_PutW32(
        AUDIOCW_DATA	*this,
        W32CHR_T        chr
    )
    {
        uint32_t        work;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !audioCW_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        // Add the element to the WaveOut.
        switch( chr ) {
            case	L' ':				// Space Characters
            case	L'\n':
            case	L'\r':
            case	L'\t':
                chr = L' ';
                if( chr == this->lastChar ) {
                    break;
                }
                if (L' ' == this->lastChar) {
                    work = this->timeIwg;
                }
                else {
                    work = this->timeIwg - this->timeIdg - this->timeIcg;
                }
                this->eRc = audioWAV_AppendSilence(this->pWave, work);
                break;
            default:
            {
                const
                char		    *nextElement = cwCharElements[chr & 0x7F];
                for( ; *nextElement; ++nextElement ) {
                    if ('.' == *nextElement) {
                        this->eRc = audioWAV_AppendSineWave(
                                            this->pWave,
                                            this->freq,
                                            this->timeDit
                                    );
                    }
                    else if ('-' == *nextElement) {
                        this->eRc = audioWAV_AppendSineWave(
                                            this->pWave,
                                            this->freq,
                                            this->timeDah
                                    );
                    }
                    if( !ERESULT_FAILED(this->eRc) ) {
                        this->eRc = audioWAV_AppendSilence(
                                                this->pWave,
                                                this->timeIdg
                                    );
                    }
                }
            }
                break;
        }
        if( !ERESULT_FAILED(this->eRc) ) {
            this->eRc = audioWAV_AppendSilence(
                                    this->pWave,
                                    (this->timeIcg - this->timeIdg)
                        );
        }
        this->lastChar = chr;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
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
    ASTR_DATA *     audioCW_ToDebugString(
        AUDIOCW_DATA    *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(audioCW) \n",
                     this
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(audioCW)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            audioCW_Validate(
        AUDIOCW_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_AUDIOCW) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(AUDIOCW_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                    W r i t e  T o  F i l e
    //---------------------------------------------------------------
    
    ERESULT         audioCW_WriteToFile(
        AUDIOCW_DATA    *this,
        PATH_DATA       *pPath
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !audioCW_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        this->eRc = audioWAV_WriteToFile(this->pWave, pPath);
        
        // Return to caller.
        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


