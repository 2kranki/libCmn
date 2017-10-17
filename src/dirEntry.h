// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Directory Entry (direntry) Header
//****************************************************************
/*
 * Program
 *				Directory Entry (direntry)
 * Purpose
 *				This object encapsulates Directory Entries from many
 *              different operating system for a common interface.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	06/23/2015 Generated
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
#include        <dateTime.h>
#include        <path.h>
#include        <AStr.h>


#ifndef         DIRENTRY_H
#define         DIRENTRY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct dirEntry_data_s	DIRENTRY_DATA;

    typedef struct dirEntry_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in hjson_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DIRENTRY_DATA *);
    } DIRENTRY_VTBL;
    
    

    typedef enum dirEntry_types_e {
        DIRENTRY_TYPE_UNKNOWN=0,
        DIRENTRY_TYPE_FIFO=1,
        DIRENTRY_TYPE_CHR=2,            // Character Device
        DIRENTRY_TYPE_DIR=4,            // Directory Entry
        DIRENTRY_TYPE_BLK=6,            // Block Device
        DIRENTRY_TYPE_REG=8,            // Regular File
        DIRENTRY_TYPE_LNK=10,           // File Link
        DIRENTRY_TYPE_SOCK=12,          // Network Socket
        DIRENTRY_TYPE_WHT=14            // ???
    } DIRENTRY_TYPES;


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the direntry including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    DIRENTRY_DATA *     dirEntry_Alloc(
        void
    );
    
    
    DIRENTRY_DATA *     dirEntry_NewA(
        PATH_DATA           *pDir,
        const
        char                *pNameStr,
        uint8_t             type
    );
    
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    //---------------------------------------------------------------
    //                  C r e a t i o n  T i m e
    //---------------------------------------------------------------
    
    DATETIME_DATA * dirEntry_getCreationTime(
        DIRENTRY_DATA   *this
    );
    
    bool            dirEntry_setCreationTime(
        DIRENTRY_DATA   *this,
        DATETIME_DATA   *pValue
    );
    

    PATH_DATA *     dirEntry_getDir(
        DIRENTRY_DATA   *this
    );
    
    bool            dirEntry_setDir(
        DIRENTRY_DATA   *this,
        PATH_DATA       *pValue
    );
    
    
    //---------------------------------------------------------------
    //               G e n e r a t i o n  N u m b e r
    //---------------------------------------------------------------
    
    uint32_t        dirEntry_getGenerationNumber(
        DIRENTRY_DATA   *this
    );
    
    bool            dirEntry_setGenerationNumber(
        DIRENTRY_DATA   *this,
        uint32_t        value
    );
    
    
    //---------------------------------------------------------------
    //      L a s t  D a t a  M o d i f i c a t i o n  T i m e
    //---------------------------------------------------------------
    
    DATETIME_DATA * dirEntry_getModifiedTime(
        DIRENTRY_DATA   *this
    );
    
    bool            dirEntry_setModifiedTime(
        DIRENTRY_DATA   *this,
        DATETIME_DATA   *pValue
    );
    
    
    ASTR_DATA *     dirEntry_getName(
        DIRENTRY_DATA   *this
    );
    
    bool            dirEntry_setName(
        DIRENTRY_DATA   *this,
        ASTR_DATA       *pValue
    );
    
    
    //---------------------------------------------------------------
    //        L a s t  S t a t u s  C h a n g e  T i m e
    //---------------------------------------------------------------
    
    DATETIME_DATA * dirEntry_getStatusChangeTime(
        DIRENTRY_DATA   *this
    );
    
    bool            dirEntry_setStatusChangeTime(
        DIRENTRY_DATA   *this,
        DATETIME_DATA   *pValue
    );
    
    
    //---------------------------------------------------------------
    //                             T y p e
    //---------------------------------------------------------------
    
    uint8_t         dirEntry_getType(
        DIRENTRY_DATA   *this
    );

    bool            dirEntry_setType(
        DIRENTRY_DATA   *this,
        uint8_t         value
    );

    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
     ERESULT eRc = dirEntry_Assign(this,pOther);
     @endcode
     @param     this    DIRENTRY object pointer
     @param     pOther  a pointer to another DIRENTRY object
     @return    If successful, ERESULT_SUCCESS otherwise an
     ERESULT_* error
     */
    ERESULT         dirEntry_Assign(
        DIRENTRY_DATA   *this,
        DIRENTRY_DATA   *pOther
    );
    
    
    ERESULT         dirEntry_Compare(
        DIRENTRY_DATA   *this,
        DIRENTRY_DATA   *pOther
    );
    
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
     DIRENTRY_DATA      *pCopy = dirEntry_Copy(this);
     @endcode
     @param     this    DIRENTRY object pointer
     @return    If successful, a DIRENTRY object which must be released,
     otherwise OBJ_NIL.
     @warning   Remember to release the returned the DIRENTRY object.
     */
    DIRENTRY_DATA * dirEntry_Copy(
        DIRENTRY_DATA   *this
    );
    
    
    /*! Set up the remaining data that a directory scan does
         not provide.
     @param     this    DIRENTRY object pointer
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                 error code.
     */
    ERESULT         dirEntry_GetAllData(
        DIRENTRY_DATA   *this
    );
    
    
    DIRENTRY_DATA * dirEntry_Init(
        DIRENTRY_DATA       *this
    );


    /*! Match this entry's file name against a pattern.
     * which may include '?' and '*'.
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error.
     */
    ERESULT         dirEntry_MatchA(
        DIRENTRY_DATA   *this,
        const
        char            *pPattern
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = dirEntry_ToDebugString(this, 4);
     @endcode:
     @param:    this    DIRENTRY object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     dirEntry_ToDebugString(
        DIRENTRY_DATA   *this,
        int             indent
    );

    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DIRENTRY_H */

