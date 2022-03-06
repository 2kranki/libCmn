// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Ansi Escape Sequences (Ansi) Header
//****************************************************************
/*
 * Program
 *          Ansi Escape Sequences (Ansi)
 * Purpose
 *          This object provides ANSI Escape Sequence support for
 *          use in terminal applications.
 *
 * Remarks
 *  1.      All references to "Keyboard" are actually referring to
 *          to stdin.
 *  1.      See "man 4 termios" on MacOS for a description of the
 *          keyboard flags.
 *  2.      Keyboard status is saved on entry to this object and
 *          is reset upon deallocation. KeyboardReset() should be
 *          executed if this object is not deallocated at program
 *          termination.
 *
 * History
 *  02/20/2022 Generated
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


#ifndef         ANSI_H
#define         ANSI_H


//#define   _IS_IMMUTABLE     1
//#define   _JSON_SUPPORT     1
//#define   _SINGLETON        1
//#define       ANSI_MSGS   1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Ansi_data_s  ANSI_DATA;              // Inherits from OBJ
    typedef struct Ansi_class_data_s ANSI_CLASS_DATA;   // Inherits from OBJ

    typedef struct Ansi_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //Ansi_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Ansi_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ANSI_DATA *);
    } ANSI_VTBL;

    typedef struct Ansi_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Ansi_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ANSI_DATA *);
    } ANSI_CLASS_VTBL;


    typedef enum Ansi_Background_e {
        ANSI_BACKGROUND_BLACK=40,
        ANSI_BACKGROUND_RED,
        ANSI_BACKGROUND_GREEN,
        ANSI_BACKGROUND_YELLOW,
        ANSI_BACKGROUND_BLUE,
        ANSI_BACKGROUND_MAGENTA,
        ANSI_BACKGROUND_CYAN,
        ANSI_BACKGROUND_WHITE
    } ANSI_BACKGROUND;
    typedef enum Ansi_Foreground_e {
        ANSI_FOREGROUND_BLACK=30,
        ANSI_FOREGROUND_RED,
        ANSI_FOREGROUND_GREEN,
        ANSI_FOREGROUND_YELLOW,
        ANSI_FOREGROUND_BLUE,
        ANSI_FOREGROUND_MAGENTA,
        ANSI_FOREGROUND_CYAN,
        ANSI_FOREGROUND_WHITE
    } ANSI_FOREGROUND;


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  ANSI_SINGLETON
    ANSI_DATA *     Ansi_Shared (
        void
    );

    void            Ansi_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Ansi object if successful, otherwise OBJ_NIL.
     */
    ANSI_DATA *     Ansi_Alloc (
        void
    );
    
    
    OBJ_ID          Ansi_Class (
        void
    );
    
    
    ANSI_DATA *     Ansi_New (
        void
    );
    
    
#ifdef  ANSI_JSON_SUPPORT
    ANSI_DATA *   Ansi_NewFromJsonString (
        ASTR_DATA       *pString
    );

    ANSI_DATA *   Ansi_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        Ansi_getCols (
        ANSI_DATA     *this
    );


#ifdef ANSI_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            Ansi_setMsgs (
        ANSI_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    uint16_t        Ansi_getRows (
        ANSI_DATA     *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         Ansi_ClearLine (
        ANSI_DATA       *this
    );

    ERESULT         Ansi_ClearScreen (
        ANSI_DATA       *this
    );

    ERESULT         Ansi_ClearToBeginOfLine (
        ANSI_DATA       *this
    );

    ERESULT         Ansi_ClearToBottom (
        ANSI_DATA       *this
    );

    ERESULT         Ansi_ClearToEndOfLine (
        ANSI_DATA       *this
    );

    ERESULT         Ansi_ClearToTop (
        ANSI_DATA       *this
    );


    ERESULT         Ansi_ColorSet (
        ANSI_DATA       *this,
        uint16_t        oolor,
        bool            fBright
    );


    ERESULT         Ansi_CursorDown (
        ANSI_DATA       *this,
        uint16_t        rows
    );

    ERESULT         Ansi_CursorLeft (
        ANSI_DATA       *this,
        uint16_t        cols
    );

    ERESULT         Ansi_CursorMove (
        ANSI_DATA       *this,
        uint16_t        y,                          // Row
        uint16_t        x                           // Column
    );

    ERESULT         Ansi_CursorRight (
        ANSI_DATA       *this,
        uint16_t        cols
    );

    ERESULT         Ansi_CursorUp (
        ANSI_DATA       *this,
        uint16_t        rows
    );


    ANSI_DATA *     Ansi_Init (
        ANSI_DATA       *this
    );


    /*!
     Wait for and get the next input character from stdin.
     @param     this    object pointer
     @return    next input characcter or EOF(-1)
     */
    int             Ansi_KeyboardGet (
        ANSI_DATA       *this
    );

    /*!
     Check to see if there is a new next input character from stdin.
     @param     this    object pointer
     @return    true if a character is ready, otherwise false.
     */
    bool            Ansi_KeyboardHit (
        ANSI_DATA       *this
    );

    /*!
     KeyboardMode sets the mode to be used by stdin. ECHO determines if the keyboard
     is to echo characters inputted on stdout. RAW mode removes line editing and
     simply returns each character. BREAK turns on or off the various signal interrupts
     such as SIGBREAK.
     @param     this    object pointer
     @param     fEcho   Sets whether characters are to be echoed to stdout as received
                        or not.
     @param     fRaw    Sets whether characters are to be diretly passeed back to the
                        program or not. Raw mode means that characters are passed bacck
                        without interpretation. If not in raw mode, the input can be edited
                        using VI like commands and is passed when the line is completed.
     @param     fBreak  Sets whether characters are to be diretly passeed back to the
                        program or not. If not in raw mode, the input can be edited
                        using VI like commands.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error.
     */
    ERESULT         Ansi_KeyboardMode (
        ANSI_DATA       *this,
        bool            fEcho,
        bool            fRaw,
        bool            fBreak
    );

    bool            Ansi_KeyboardIsBreak (
        ANSI_DATA       *this
    );

    bool            Ansi_KeyboardIsEcho (
        ANSI_DATA       *this
    );

    bool            Ansi_KeyboardIsRaw (
        ANSI_DATA       *this
    );

    bool            Ansi_KeyboardIsTTY (
        ANSI_DATA       *this
    );

    bool            Ansi_KeyboardIsUTF8 (
        ANSI_DATA       *this
    );

    ERESULT         Ansi_KeyboardReset (
        ANSI_DATA       *this
    );


#ifdef  ANSI_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Ansi_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Ansi_ToJson (
        ANSI_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Ansi_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Ansi_ToDebugString (
        ANSI_DATA     *this,
        int             indent
    );
    
    
    /*!
     Get the terminal's window size in characters. You can retrieve the
     results using Ansi_getCols() and Ansi_getRows().
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Ansi_WinSize (
        ANSI_DATA       *this
    );

    
#ifdef  __cplusplus
}
#endif

#endif  /* ANSI_H */

