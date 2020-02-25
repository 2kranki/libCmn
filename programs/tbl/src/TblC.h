// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          TBLC Console Transmit Task (TblC) Header
//****************************************************************
/*
 * Program
 *			Separate TblC (TblC)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate TblC to run things without complications
 *          of interfering with the main TblC. A TblC may be 
 *          called a TblC on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	02/22/2020 Generated
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





#include        <Tbl_defs.h>
#include        <AStr.h>


#ifndef         TBLC_H
#define         TBLC_H


//#define   TBLC_IS_IMMUTABLE     1
#define   TBLC_JSON_SUPPORT     1
//#define   TBLC_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct TblC_data_s	TBLC_DATA;            // Inherits from OBJ
    typedef struct TblC_class_data_s TBLC_CLASS_DATA;   // Inherits from OBJ

    typedef struct TblC_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TblC_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TBLC_DATA *);
    } TBLC_VTBL;

    typedef struct TblC_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TblC_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TBLC_DATA *);
    } TBLC_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  TBLC_SINGLETON
    TBLC_DATA *     TblC_Shared (
        void
    );

    void            TblC_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to TblC object if successful, otherwise OBJ_NIL.
     */
    TBLC_DATA *     TblC_Alloc (
        void
    );
    
    
    OBJ_ID          TblC_Class (
        void
    );
    
    
    TBLC_DATA *     TblC_New (
        void
    );
    
    
#ifdef  TBLC_JSON_SUPPORT
    TBLC_DATA *   TblC_NewFromJsonString (
        ASTR_DATA       *pString
    );

    TBLC_DATA *   TblC_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     TblC_Disable (
        TBLC_DATA		*this
    );


    ERESULT     TblC_Enable (
        TBLC_DATA		*this
    );

   
    TBLC_DATA *   TblC_Init (
        TBLC_DATA     *this
    );


    ERESULT     TblC_IsEnabled (
        TBLC_DATA		*this
    );
    
 
#ifdef  TBLC_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = TblC_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     TblC_ToJson (
        TBLC_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = TblC_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    TblC_ToDebugString (
        TBLC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* TBLC_H */

