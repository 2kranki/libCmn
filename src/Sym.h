// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SYM Console Transmit Task (Sym) Header
//****************************************************************
/*
 * Program
 *			Separate Sym (Sym)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate Sym to run things without complications
 *          of interfering with the main Sym. A Sym may be 
 *          called a Sym on other O/S's.
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





#include        <cmn_defs.h>
#include        <AStr.h>
#include        <Node.h>


#ifndef         SYM_H
#define         SYM_H


//#define   SYM_IS_IMMUTABLE     1
#define   SYM_JSON_SUPPORT     1
//#define   SYM_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Sym_data_s	SYM_DATA;            // Inherits from OBJ
    typedef struct Sym_class_data_s SYM_CLASS_DATA;   // Inherits from OBJ

    typedef struct Sym_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Sym_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SYM_DATA *);
    } SYM_VTBL;

    typedef struct Sym_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Sym_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SYM_DATA *);
    } SYM_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SYM_SINGLETON
    SYM_DATA *     Sym_Shared (
        void
    );

    void           Sym_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Sym object if successful, otherwise OBJ_NIL.
     */
    SYM_DATA *      Sym_Alloc (
        void
    );
    
    
    OBJ_ID          Sym_Class (
        void
    );
    
    
    SYM_DATA *      Sym_New (
        void
    );
    
    
#ifdef  SYM_JSON_SUPPORT
    SYM_DATA *      Sym_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SYM_DATA *      Sym_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


    SYM_DATA *     Sym_NewWithUTF8AndClass(
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: Value is Absolute
     */
    bool            Sym_getAbs (
        SYM_DATA        *this
    );

    bool            Sym_setAbs (
        SYM_DATA        *this,
        bool            value
    );


    /*! Property: Value is Relocatable
     */
    bool            Sym_getAbs (
        SYM_DATA        *this
    );

    bool            Sym_setAbs (
        SYM_DATA        *this,
        bool            value
    );


    NODE_DATA *     Sym_getNode (
        SYM_DATA        *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    SYM_DATA *      Sym_Init (
        SYM_DATA        *this
    );


#ifdef  SYM_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Sym_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Sym_ToJson (
        SYM_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Sym_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Sym_ToDebugString (
        SYM_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SYM_H */

