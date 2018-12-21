// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Simple Index Extended (sidxe) Header
//****************************************************************
/*
 * Program
 *			Simple Index Extended (sidxe)
 * Purpose
 *          This object provides a simple index into some other
 *          set of objects. It stores an index amount and an
 *          offset in its table. When a value is needed, the
 *          closest value and offset will be returned. The index
 *          is of a fixed size with a starting interval between
 *          entries. When the index becomes full, the interval
 *          is doubled and every other entry is removed.
 *
 *          Normally, you would call addIndex() every time that
 *          you read a line or process something. The index will
 *          automatically adjust when it gets full. It just makes
 *          it easier to get to some point in a file or process
 *          if that is needed.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/18/2018 Generated
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
#include        <srcLoc.h>




#ifndef         SIDXE_H
#define         SIDXE_H


//#define   SIDXE_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct sidxe_data_s	SIDXE_DATA;            // Inherits from OBJ
    typedef struct sidxe_class_data_s SIDXE_CLASS_DATA;   // Inherits from OBJ

    typedef struct sidxe_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in sidxe_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SIDXE_DATA *);
    } SIDXE_VTBL;

    typedef struct sidxe_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in sidxe_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SIDXE_DATA *);
    } SIDXE_CLASS_VTBL;


    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SIDXE_SINGLETON
    SIDXE_DATA *    sidxe_Shared (
        void
    );

    bool            sidxe_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to sidxe object if successful, otherwise OBJ_NIL.
     */
    SIDXE_DATA *    sidxe_Alloc (
        void
    );
    
    
    OBJ_ID          sidxe_Class (
        void
    );
    
    
    SIDXE_DATA *    sidxe_New (
        void
    );
    
    SIDXE_DATA *    sidxe_NewWithMax (
        uint16_t        max
    );
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        sidxe_getInterval (
        SIDXE_DATA      *this
    );
    
    
    uint16_t        sidxe_getMax (
        SIDXE_DATA      *this
    );
    
    bool            sidxe_setMax (
        SIDXE_DATA      *this,
        uint16_t        value
    );

    
    uint32_t        sidxe_getSize (
        SIDXE_DATA      *this
    );
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         sidxe_Add (
        SIDXE_DATA      *this,
        SRCLOC          *pLoc
    );
    
    
    ERESULT         sidxe_FindLineNo (
        SIDXE_DATA      *this,
        uint32_t        lineNo,
        SRCLOC          *pLoc
    );
    
    
    SIDXE_DATA *   sidxe_Init (
        SIDXE_DATA     *this
    );


    /*!
     Reset the index as if it was just created with no data.
     @param     this    object pointer
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         sidxe_Reset (
        SIDXE_DATA      *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = sidxe_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    sidxe_ToDebugString (
        SIDXE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SIDXE_H */

