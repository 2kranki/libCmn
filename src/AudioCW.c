// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   AudioCW.c
 *  Generated 06/28/2020 10:01:55
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
#include        <AudioCW_internal.h>
#include        <trace.h>
#include        <W32Str.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    

    const
    char            *cwCharElements[128] = {
        /* 00-07 */    "", "", "", "", "", "", "", "",
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
    void            AudioCW_task_body (
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

    AUDIOCW_DATA *     AudioCW_Alloc (
        void
    )
    {
        AUDIOCW_DATA       *this;
        uint32_t        cbSize = sizeof(AUDIOCW_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ERESULT         AudioCW_IsValidW32 (
        W32CHR_T        chr
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



    AUDIOCW_DATA *  AudioCW_New (
        void
    )
    {
        AUDIOCW_DATA    *this;
        
        this = AudioCW_Alloc( );
        if (this) {
            this = AudioCW_Init(this);
        } 
        return this;
    }


    AUDIOCW_DATA *  AudioCW_NewWithParms (
        uint8_t         numberOfChannels,
        uint32_t        samplesPerSecond,   // Normally 11025, 22050, 44100
        uint16_t        sampleSize,         // Normally 8, 16, or 32
        uint16_t        freq                // Frequency (20Hz..20,000Hz)
    )
    {
        AUDIOCW_DATA    *this;
        ERESULT         eRc;

        this = AudioCW_New( );
        if (this) {
            eRc =  AudioCW_Setup(
                            this,
                            numberOfChannels,
                            samplesPerSecond,
                            sampleSize,
                            freq
                    );
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                       F r e q u e n c y
    //---------------------------------------------------------------
    
    uint16_t        AudioCW_getFreq (
        AUDIOCW_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return this->freq;
    }


    bool            AudioCW_setFreq (
        AUDIOCW_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->freq = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        AudioCW_getSize (
        AUDIOCW_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  AudioCW_getSuperVtbl (
        AUDIOCW_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          W a v e
    //---------------------------------------------------------------

    AUDIOWAV_DATA * AudioCW_getWave (
        AUDIOCW_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pWave;
    }


    bool        AudioCW_setWave (
        AUDIOCW_DATA    *this,
        AUDIOWAV_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
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
        ERESULT eRc = AudioCW_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another AUDIOCW object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         AudioCW_Assign (
        AUDIOCW_DATA       *this,
        AUDIOCW_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!AudioCW_Validate(pOther)) {
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
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //               C a l c u l a t e  T i m i n g
    //---------------------------------------------------------------

    ERESULT         AudioCW_CalculateTiming (
        AUDIOCW_DATA    *this,
        uint16_t        wpmChar,
        uint16_t        wpmText
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !AudioCW_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if( (wpmChar < 5) || (wpmChar > 55) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if( (wpmText < 5) || (wpmText > 55) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if( wpmChar < wpmText ) {
            return ERESULT_INVALID_PARAMETER;
        }
        this->wpmChar = wpmChar;
        this->wpmText = wpmText;

        // Calculate the Dit Time in milliseconds.
        //    timeDit = ((60 * 1000) + (60 - 1)) / (50 * ditWpm);    // 60sec -> milliseconds w/roundup
        //    timeDit = 60059 / (50 * ditWpm );
        this->timeDit = 1201 / wpmChar;

        // Calculate the Dah Time in milliseconds.
        this->timeDah = 3 * this->timeDit;

        // Calculate the Inter Gaps.
        this->timeIdg = this->timeDit;
        this->timeFrn = ((60000 * wpmChar) - (37200 * wpmText)) / (wpmChar * wpmText);
        this->timeIcg = (3 * this->timeFrn) / 19;
        this->timeIwg = (7 * this->timeFrn) / 19;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         AudioCW_Compare (
        AUDIOCW_DATA     *this,
        AUDIOCW_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!AudioCW_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        AudioCW      *pCopy = AudioCW_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a AUDIOCW object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    AUDIOCW_DATA *     AudioCW_Copy (
        AUDIOCW_DATA       *this
    )
    {
        AUDIOCW_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef AUDIOCW_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = AudioCW_New( );
        if (pOther) {
            eRc = AudioCW_Assign(this, pOther);
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

    void            AudioCW_Dealloc (
        OBJ_ID          objId
    )
    {
        AUDIOCW_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((AUDIOCW_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        AudioCW_setWave(this, OBJ_NIL);

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
        AudioCW      *pDeepCopy = AudioCW_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a AUDIOCW object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    AUDIOCW_DATA *     AudioCW_DeepyCopy (
        AUDIOCW_DATA       *this
    )
    {
        AUDIOCW_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = AudioCW_New( );
        if (pOther) {
            eRc = AudioCW_Assign(this, pOther);
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
    ERESULT         AudioCW_Disable (
        AUDIOCW_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return eRc;
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
    ERESULT         AudioCW_Enable (
        AUDIOCW_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    AUDIOCW_DATA *   AudioCW_Init (
        AUDIOCW_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(AUDIOCW_DATA);
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_AUDIOCW);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&AudioCW_Vtbl);
        
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
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "AudioCW::sizeof(AUDIOCW_DATA) = %lu\n", 
                sizeof(AUDIOCW_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(AUDIOCW_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         AudioCW_IsEnabled (
        AUDIOCW_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
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
    //                          P u t
    //---------------------------------------------------------------

    ERESULT         AudioCW_PutTextW32 (
        AUDIOCW_DATA    *this,
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
        if( !AudioCW_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (pData == OBJ_NIL) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        len = cData;
        if (cData == 0) {
            len = W32Str_StrLen(pData);
        }

        for (i=0; i<len; ++i) {
            switch (state) {
                case 1:
                    if (pData[i] == L'@') {
                        state = 2;
                        cRepeat = 0;
                    }
                    else {
                        AudioCW_PutW32(this, pData[i]);
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
                            AudioCW_PutW32(this, pData[i]);
                        }
                        state = 1;
                    }
                    break;

            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    ERESULT         AudioCW_PutW32 (
        AUDIOCW_DATA    *this,
        W32CHR_T        chr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        work;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !AudioCW_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Add the element to the WaveOut.
        switch( chr ) {
            case    L' ':                // Space Characters
            case    L'\n':
            case    L'\r':
            case    L'\t':
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
                eRc = AudioWAV_AppendSilence(this->pWave, work);
                break;
            default:
            {
                const
                char            *nextElement = cwCharElements[chr & 0x7F];
                for( ; *nextElement; ++nextElement ) {
                    if ('.' == *nextElement) {
                        eRc = AudioWAV_AppendSineWave(
                                            this->pWave,
                                            this->freq,
                                            this->timeDit
                                    );
                    }
                    else if ('-' == *nextElement) {
                        eRc = AudioWAV_AppendSineWave(
                                            this->pWave,
                                            this->freq,
                                            this->timeDah
                                    );
                    }
                    if( !ERESULT_FAILED(eRc) ) {
                        eRc = AudioWAV_AppendSilence(
                                                this->pWave,
                                                this->timeIdg
                                    );
                    }
                }
            }
                break;
        }
        if( !ERESULT_FAILED(eRc) ) {
            eRc = AudioWAV_AppendSilence(
                                    this->pWave,
                                    (this->timeIcg - this->timeIdg)
                        );
        }
        this->lastChar = chr;

        // Return to caller.
        return eRc;
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
        void        *pMethod = AudioCW_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "AudioCW", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          AudioCW_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        AUDIOCW_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(AUDIOCW_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)AudioCW_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return AudioCW_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return AudioCW_Enable;
                        }
                        break;

                    case 'P':
#ifdef  AUDIOCW_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return AudioCW_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return AudioCW_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return AudioCW_ToDebugString;
                        }
#ifdef  AUDIOCW_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return AudioCW_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return AudioCW_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == AudioCW_ToDebugString)
                    return "ToDebugString";
#ifdef  AUDIOCW_JSON_SUPPORT
                if (pData == AudioCW_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e t u p
    //---------------------------------------------------------------

    ERESULT         AudioCW_Setup (
        AUDIOCW_DATA    *this,
        uint8_t         numberOfChannels,
        uint32_t        samplesPerSecond,   // Normally 11025, 22050, 44100
        uint16_t        sampleSize,         // Normally 8, 16, or 32
        uint16_t        freq                // Frequency (20Hz..20,000Hz)
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        this->pWave =   AudioWAV_NewWithParms(
                                        numberOfChannels,
                                        samplesPerSecond,
                                        sampleSize
                        );
        if (OBJ_NIL == this->pWave) {
            DEBUG_BREAK();
            obj_Release(this);
            return ERESULT_OUT_OF_MEMORY;
        }
        this->freq = freq;

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = AudioCW_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     AudioCW_ToDebugString (
        AUDIOCW_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AudioCW_Validate(this)) {
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
                    AudioCW_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            ASTR_DATA       *pWrkStr = OBJ_NIL;
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
#endif
        
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
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            AudioCW_Validate (
        AUDIOCW_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_AUDIOCW))
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


        if (!(obj_getSize(this) >= sizeof(AUDIOCW_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                    W r i t e  T o  F i l e
    //---------------------------------------------------------------

    ERESULT         AudioCW_WriteToFile (
        AUDIOCW_DATA    *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !AudioCW_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = AudioWAV_WriteToFile(this->pWave, pPath);

        // Return to caller.
        //this->eRc = ERESULT_SUCCESS;
        return eRc;
    }




    
#ifdef  __cplusplus
}
#endif


