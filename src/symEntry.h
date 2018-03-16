// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SYMENTRY Console Transmit Task (symEntry) Header
//****************************************************************
/*
 * Program
 *			Separate symEntry (symEntry)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate symEntry to run things without complications
 *          of interfering with the main symEntry. A symEntry may be 
 *          called a symEntry on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal symEntry. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	03/27/2017 Generated
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
#include        <name.h>
#include        <symAttr.h>
#include        <visitor.h>



#ifndef         SYMENTRY_H
#define         SYMENTRY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct symEntry_data_s	SYMENTRY_DATA;    // Inherits from OBJ.

    typedef struct symEntry_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in symEntry_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SYMENTRY_DATA *);
    } SYMENTRY_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    SYMENTRY_DATA *     symEntry_Alloc(
        void
    );
    
    
    OBJ_ID              symEntry_Class(
        void
    );
    
    
    SYMENTRY_DATA *     symEntry_New(
        NAME_DATA           *pName,
        OBJ_ID              pData
    );
    
    SYMENTRY_DATA *     symEntry_NewA(
        const
        char                *pName,
        int32_t             class
    );
    
    

    SYMENTRY_DATA *     symEntry_NewWithUTF8(
        const
        char                *pName,
        OBJ_ID              pData
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    SYMATTR_DATA *  symEntry_getAttr(
        SYMENTRY_DATA    *this
    );
    
    bool            symEntry_setAttr(
        SYMENTRY_DATA   *this,
        SYMATTR_DATA    *pValue
    );
    
    
    int32_t         symEntry_getClass(
        SYMENTRY_DATA   *this
    );
    
    bool            symEntry_setClass(
        SYMENTRY_DATA   *this,
        int32_t         value
    );
    
    
    uint16_t        symEntry_getFlags16(
        SYMENTRY_DATA	*this
    );
    
    bool            symEntry_setFlags16(
        SYMENTRY_DATA	*this,
        uint16_t        value
    );
    
    
    ERESULT         symEntry_getLastError(
        SYMENTRY_DATA	*this
    );


    const
    char *          symEntry_getName(
        SYMENTRY_DATA   *this
    );
    
    
    uint16_t        symEntry_getMisc16ua(
        SYMENTRY_DATA	*this
    );
    
    bool            symEntry_setMisc16ua(
        SYMENTRY_DATA	*this,
        uint16_t        value
    );
    
    
    uint16_t        symEntry_getMisc16ub(
        SYMENTRY_DATA	*this
    );
    
    bool            symEntry_setMisc16ub(
        SYMENTRY_DATA	*this,
        uint16_t        value
    );
    
    
    uint32_t        symEntry_getMisc32ua(
        SYMENTRY_DATA	*this
    );
    
    bool            symEntry_setMisc32ua(
        SYMENTRY_DATA	*this,
        uint32_t        value
    );
    
    
    uint32_t        symEntry_getMisc32ub(
        SYMENTRY_DATA	*this
    );
    
    bool            symEntry_setMisc32ub(
        SYMENTRY_DATA	*this,
        uint32_t        value
    );
    
    
    OBJ_ID          symEntry_getObject(
        SYMENTRY_DATA    *this
    );
    
    bool            symEntry_setObject(
        SYMENTRY_DATA   *this,
        OBJ_ID          pValue
    );
    
    
    uint32_t        symEntry_getToken(
        SYMENTRY_DATA    *this
    );
    
    
    int32_t         symEntry_getType(
        SYMENTRY_DATA	*this
    );
    
    bool            symEntry_setType(
        SYMENTRY_DATA	*this,
        int32_t         value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    SYMENTRY_DATA *   symEntry_Init(
        SYMENTRY_DATA   *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = symEntry_ToDebugString(this,4);
     @endcode
     @param     this    SYMENTRY object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *    symEntry_ToDebugString(
        SYMENTRY_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SYMENTRY_H */

