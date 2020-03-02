// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          OPC360 Console Transmit Task (Opc360) Header
//****************************************************************
/*
 * Program
 *			Separate Opc360 (Opc360)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate Opc360 to run things without complications
 *          of interfering with the main Opc360. A Opc360 may be 
 *          called a Opc360 on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	02/29/2020 Generated
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
#include        <Opcode.h>


#ifndef         OPC360_H
#define         OPC360_H


//#define   OPC360_IS_IMMUTABLE     1
#define   OPC360_JSON_SUPPORT     1
//#define   OPC360_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Opc360_data_s	OPC360_DATA;            // Inherits from OBJ
    typedef struct Opc360_class_data_s OPC360_CLASS_DATA;   // Inherits from OBJ

    typedef struct Opc360_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Opc360_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OPC360_DATA *);
    } OPC360_VTBL;

    typedef struct Opc360_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Opc360_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OPC360_DATA *);
    } OPC360_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  OPC360_SINGLETON
    OPC360_DATA *   Opc360_Shared (
        void
    );

    void            Opc360_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Opc360 object if successful, otherwise OBJ_NIL.
     */
    OPC360_DATA *   Opc360_Alloc (
        void
    );
    
    
    OBJ_ID          Opc360_Class (
        void
    );
    
    
    const
    char *          Opc360_FeatureDesc (
        uint16_t        num
    );

    uint16_t        Opc360_FeatureValue (
        const
        char            *pStrA
    );


    const char *    Opc360_InterruptDesc (
        uint16_t        num
    );

    uint16_t        Opc360_InterruptValue (
        const
        char           *pStrA
    );


    OPC360_DATA *   Opc360_New (
        void
    );
    
    
    OPC360_DATA *   Opc360_NewA (
        const
        char            *pNameA
    );


#ifdef  OPC360_JSON_SUPPORT
    OPC360_DATA *   Opc360_NewFromJsonString (
        ASTR_DATA       *pString
    );

    OPC360_DATA *   Opc360_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


    const
    char *          Opc360_TypeDesc (
        uint16_t        num
    );

    uint16_t        Opc360_TypeValue (
        const
        char            *pStrA
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OPCODE_ENTRY *  Opc360_getEntry (
        OPC360_DATA     *this
    );


    const
    char *          Opc360_getNameA (
        OPC360_DATA     *this
    );


    OPCODE_DATA * Opc360_getOpcode (
        OPC360_DATA     *this
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
        ERESULT eRc = Opc360_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another OPC360 object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Opc360_Assign (
        OPC360_DATA     *this,
        OPC360_DATA     *pOther
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         Opc360_Compare (
        OPC360_DATA     *this,
        OPC360_DATA     *pOther
    );

   
     /*!
      Copy the current object creating a new object.
      Example:
      @code
         Opc360      *pCopy = Opc360_Copy(this);
      @endcode
      @param     this    object pointer
      @return    If successful, a OPC360 object which must be
                 released, otherwise OBJ_NIL.
      @warning   Remember to release the returned object.
      */
     OPC360_DATA *  Opc360_Copy (
         OPC360_DATA    *this
     );


    OPC360_DATA *   Opc360_Init (
        OPC360_DATA     *this
    );


#ifdef  OPC360_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Opc360_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Opc360_ToJson (
        OPC360_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Opc360_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Opc360_ToDebugString (
        OPC360_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OPC360_H */

