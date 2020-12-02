// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Source Difference Finder (SrcDiff) Header
//****************************************************************
/*
 * Program
 *          Source Difference Finder (SrcDiff)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate SrcDiff to run things without complications
 *          of interfering with the main SrcDiff. A SrcDiff may be 
 *          called a SrcDiff on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  12/01/2020 Generated
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


#ifndef         SRCDIFF_H
#define         SRCDIFF_H


//#define   SRCDIFF_IS_IMMUTABLE     1
//#define   SRCDIFF_JSON_SUPPORT     1
//#define   SRCDIFF_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SrcDiff_data_s  SRCDIFF_DATA;            // Inherits from OBJ
    typedef struct SrcDiff_class_data_s SRCDIFF_CLASS_DATA;   // Inherits from OBJ

    typedef struct SrcDiff_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcDiff_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCDIFF_DATA *);
    } SRCDIFF_VTBL;

    typedef struct SrcDiff_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcDiff_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCDIFF_DATA *);
    } SRCDIFF_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SRCDIFF_SINGLETON
    SRCDIFF_DATA *     SrcDiff_Shared (
        void
    );

    void            SrcDiff_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SrcDiff object if successful, otherwise OBJ_NIL.
     */
    SRCDIFF_DATA *     SrcDiff_Alloc (
        void
    );
    
    
    OBJ_ID          SrcDiff_Class (
        void
    );
    
    
    SRCDIFF_DATA *     SrcDiff_New (
        void
    );
    
    
#ifdef  SRCDIFF_JSON_SUPPORT
    SRCDIFF_DATA *   SrcDiff_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SRCDIFF_DATA *   SrcDiff_NewFromJsonStringA (
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

    ERESULT     SrcDiff_Disable (
        SRCDIFF_DATA       *this
    );


    ERESULT     SrcDiff_Enable (
        SRCDIFF_DATA       *this
    );

   
    SRCDIFF_DATA *   SrcDiff_Init (
        SRCDIFF_DATA     *this
    );


    ERESULT     SrcDiff_IsEnabled (
        SRCDIFF_DATA       *this
    );
    
 
#ifdef  SRCDIFF_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SrcDiff_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcDiff_ToJson (
        SRCDIFF_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SrcDiff_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcDiff_ToDebugString (
        SRCDIFF_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* SRCDIFF_H */

