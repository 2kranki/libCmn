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
 *	1.      None
 *
 * History
 *	11/04/2018 Generated
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
#include        <node.h>


#ifndef         SYMENTRY_H
#define         SYMENTRY_H


//#define   SYMENTRY_SINGLETON    1

#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct symEntry_data_s	SYMENTRY_DATA;            // Inherits from OBJ
    typedef struct symEntry_class_data_s SYMENTRY_CLASS_DATA;   // Inherits from OBJ

    typedef struct symEntry_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in symEntry_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SYMENTRY_DATA *);
    } SYMENTRY_VTBL;

    typedef struct symEntry_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in symEntry_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SYMENTRY_DATA *);
    } SYMENTRY_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SYMENTRY_SINGLETON
    SYMENTRY_DATA * symEntry_Shared(
        void
    );

    bool            symEntry_SharedReset(
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to symEntry object if successful, otherwise OBJ_NIL.
     */
    SYMENTRY_DATA * symEntry_Alloc(
        void
    );
    
    
    OBJ_ID          symEntry_Class(
        void
    );
    
    
    SYMENTRY_DATA * symEntry_New(
        void
    );
    
    
    SYMENTRY_DATA * symEntry_NewWithUTF8AndClass (
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    );
    
    
    SYMENTRY_DATA * gmrNode_NewWithUTF8ConAndClass(
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    );
    
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        symEntry_getAlign (
        SYMENTRY_DATA   *this
    );
    
    bool            symEntry_setAlign (
        SYMENTRY_DATA   *this,
        uint16_t        value
    );

    
    int32_t         symEntry_getClass(
        SYMENTRY_DATA   *this
    );
    
    
    uint16_t        symEntry_getDup (
        SYMENTRY_DATA   *this
    );
    
    bool            symEntry_setDup (
        SYMENTRY_DATA   *this,
        uint16_t        value
    );
    
    
    uint32_t        symEntry_getIndex(
        SYMENTRY_DATA   *this
    );
    
    bool            symEntry_setIndex(
        SYMENTRY_DATA   *this,
        uint32_t        value
    );

    
    uint16_t        symEntry_getLength (
        SYMENTRY_DATA   *this
    );
    
    bool            symEntry_setLength (
        SYMENTRY_DATA   *this,
        uint16_t        value
    );

    
    int16_t         symEntry_getLevel(
        SYMENTRY_DATA   *this
    );
    
    
    NODE_DATA *     symEntry_getNode(
        SYMENTRY_DATA   *this
    );
    
    
    NODELINK_DATA * symEntry_getNodeLink(
        SYMENTRY_DATA   *this
    );
    
    
    int32_t         symEntry_getType(
        SYMENTRY_DATA   *this
    );
    
    bool            symEntry_setType(
        SYMENTRY_DATA   *this,
        int32_t         value
    );
    
    
    uint32_t        symEntry_getValue (
        SYMENTRY_DATA   *this
    );
    
    bool            symEntry_setValue (
        SYMENTRY_DATA   *this,
        uint16_t        value
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     symEntry_Disable(
        SYMENTRY_DATA		*this
    );


    ERESULT     symEntry_Enable(
        SYMENTRY_DATA		*this
    );

   
    SYMENTRY_DATA *   symEntry_Init(
        SYMENTRY_DATA     *this
    );


    ERESULT     symEntry_IsEnabled(
        SYMENTRY_DATA		*this
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
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    symEntry_ToDebugString(
        SYMENTRY_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SYMENTRY_H */

