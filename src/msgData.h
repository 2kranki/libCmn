// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          MSGDATA Console Transmit Task (MsgData) Header
//****************************************************************
/*
 * Program
 *			Separate MsgData (MsgData)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate MsgData to run things without complications
 *          of interfering with the main MsgData. A MsgData may be 
 *          called a MsgData on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/31/2019 Generated
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
#include        <value.h>


#ifndef         MSGDATA_H
#define         MSGDATA_H


#define   MSGDATA_JSON_SUPPORT 1
//#define   MSGDATA_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct MsgData_data_s	MSGDATA_DATA;            // Inherits from OBJ
    typedef struct MsgData_class_data_s MSGDATA_CLASS_DATA;   // Inherits from OBJ

    typedef struct MsgData_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in MsgData_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MSGDATA_DATA *);
    } MSGDATA_VTBL;

    typedef struct MsgData_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in MsgData_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MSGDATA_DATA *);
    } MSGDATA_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  MSGDATA_SINGLETON
    MSGDATA_DATA *  MsgData_Shared (
        void
    );

    void            MsgData_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to MsgData object if successful, otherwise OBJ_NIL.
     */
    MSGDATA_DATA *  MsgData_Alloc (
        void
    );
    
    
    OBJ_ID          MsgData_Class (
        void
    );
    
    
    MSGDATA_DATA *  MsgData_New (
        void
    );
    
    
    MSGDATA_DATA *  MsgData_NewWithData (
        uint32_t        origin,
        uint32_t        dest,
        uint32_t        size,
        void            *pData
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    void *          MsgData_getData (
        MSGDATA_DATA    *this
    );


    uint32_t        MsgData_getDestination (
        MSGDATA_DATA    *this
    );


    uint32_t        MsgData_getNum32 (
        MSGDATA_DATA    *this
    );

    bool            MsgData_setNum32 (
        MSGDATA_DATA    *this,
        uint32_t        value
    );


    uint32_t        MsgData_getOrigin (
        MSGDATA_DATA     *this
    );


    uint32_t        MsgData_getSize (
        MSGDATA_DATA    *this
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
        ERESULT eRc = MsgData_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another MSGDATA object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         MsgData_Assign (
        MSGDATA_DATA    *this,
        MSGDATA_DATA    *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        MsgData      *pCopy = MsgData_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a MSGDATA object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    MSGDATA_DATA *  MsgData_Copy (
        MSGDATA_DATA    *this
    );

   
    MSGDATA_DATA *  MsgData_Init (
        MSGDATA_DATA    *this
    );


    ERESULT         MsgData_IsEnabled (
        MSGDATA_DATA	*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = MsgData_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     MsgData_ToDebugString (
        MSGDATA_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MSGDATA_H */

