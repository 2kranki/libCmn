// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Posix Protected Object Circular Buffer (ObjCb) Header
//****************************************************************
/*
 * Program
 *			Posix Protected Object Circular Buffer (ObjCb)
 * Purpose
 *          These subroutines provide a general purpose set of
 *          routines to provide a Circular (FIFO) Buffer of
 *          size elements. The buffer is designed to work in
 *          multi-tasking environment with a single sender and
 *          receiver. It is not safe for multiple senders or
 *          receivers with proper locking.
 *
 * Remarks
 *    1.    XC32 allows 4 register variables per function call.
 *          So, we will restrict most function calls to 4 or less.
 *
 * References
 *        http://en.wikipedia.org/wiki/Circular_buffer
 *        "Data Structures and Algorithms", Alfred V. Aho et al,
 *            Addison-Wesley, 1985
 *        "Data Structures using C", Aaron M. Tenenbaum et al,
 *            Prentice-Hall, 1990
 *        "Programs and Data Structures in C", Leendert Ammeraal,
 *            John Wiley & Sons, 1987
 *
 * History
 *  12/30/2014  Created from cb8.
 *	02/21/2020  Regenerated
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


#ifndef         OBJCB_H
#define         OBJCB_H


//#define   OBJCB_IS_IMMUTABLE     1
//#define   OBJCB_JSON_SUPPORT     1
//#define   OBJCB_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ObjCb_data_s	OBJCB_DATA;            // Inherits from OBJ
    typedef struct ObjCb_class_data_s OBJCB_CLASS_DATA;   // Inherits from OBJ

    typedef struct ObjCb_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjCb_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJCB_DATA *);
    } OBJCB_VTBL;

    typedef struct ObjCb_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjCb_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJCB_DATA *);
    } OBJCB_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  OBJCB_SINGLETON
    OBJCB_DATA *     ObjCb_Shared (
        void
    );

    void            ObjCb_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ObjCb object if successful, otherwise OBJ_NIL.
     */
    OBJCB_DATA *     ObjCb_Alloc (
        void
    );
    
    
    OBJ_ID          ObjCb_Class (
        void
    );
    
    
    OBJCB_DATA *    ObjCb_New (
        void
    );
    
    
    OBJCB_DATA *    ObjCb_NewWithSize (
        uint32_t        max            // Maximum Number of Elements in Circular Buffer
    );


#ifdef  OBJCB_JSON_SUPPORT
    OBJCB_DATA *   ObjCb_NewFromJsonString (
        ASTR_DATA       *pString
    );

    OBJCB_DATA *   ObjCb_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        ObjCb_getSize (
        OBJCB_DATA      *this
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    uint32_t        ObjCb_Count (
        OBJCB_DATA      *this
    );


    // The object is not released when it is returned. So, the user
    // must do so when they are done with it.
    bool            ObjCb_Get (
        OBJCB_DATA      *this,
        OBJ_ID          *ppValue
    );


    OBJCB_DATA *    ObjCb_Init (
        OBJCB_DATA      *this
    );


    bool            ObjCb_IsEmpty (
        OBJCB_DATA      *this
    );


    bool            ObjCb_IsFull (
        OBJCB_DATA      *this
    );


    /*!
     Pause the buffer flow releasing any tasks waiting to get/put data.
     This is necessary especially just prior to termination since all
     conditions and mutexes must be in an unlocked state.
     @param     this    object pointer
     @return    true if data is available, otherwise false.
     */
    bool            ObjCb_Pause (
        OBJCB_DATA      *this
    );


    // The object is retained when it is added to the circular
    // buffer.
    bool            ObjCb_Put (
        OBJCB_DATA      *this,
        OBJ_ID          pValue
    );


    bool            ObjCb_Resume (
        OBJCB_DATA      *this
    );


    ERESULT         ObjCb_Setup (
        OBJCB_DATA      *this,
        uint32_t        max             // Maximum Number of Objects in Buffer
    );


#ifdef  OBJCB_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ObjCb_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjCb_ToJson (
        OBJCB_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjCb_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    ObjCb_ToDebugString (
        OBJCB_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJCB_H */

