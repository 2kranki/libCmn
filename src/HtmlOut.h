// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  HTML Output Helper (HtmlOut) Header
//****************************************************************
/*
 * Program
 *          HTML Output Helper (HtmlOut)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate HtmlOut to run things without complications
 *          of interfering with the main HtmlOut. A HtmlOut may be 
 *          called a HtmlOut on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  03/30/2021 Generated
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
#include        <TextOut.h>


#ifndef         HTMLOUT_H
#define         HTMLOUT_H


//#define   HTMLOUT_IS_IMMUTABLE     1
//#define   HTMLOUT_JSON_SUPPORT     1
//#define   HTMLOUT_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct HtmlOut_data_s  HTMLOUT_DATA;            // Inherits from OBJ
    typedef struct HtmlOut_class_data_s HTMLOUT_CLASS_DATA;   // Inherits from OBJ

    typedef struct HtmlOut_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in HtmlOut_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(HTMLOUT_DATA *);
    } HTMLOUT_VTBL;

    typedef struct HtmlOut_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in HtmlOut_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(HTMLOUT_DATA *);
    } HTMLOUT_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  HTMLOUT_SINGLETON
    HTMLOUT_DATA *     HtmlOut_Shared (
        void
    );

    void            HtmlOut_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to HtmlOut object if successful, otherwise OBJ_NIL.
     */
    HTMLOUT_DATA *     HtmlOut_Alloc (
        void
    );
    
    
    OBJ_ID          HtmlOut_Class (
        void
    );
    
    
    HTMLOUT_DATA *     HtmlOut_New (
        void
    );
    
    
#ifdef  HTMLOUT_JSON_SUPPORT
    HTMLOUT_DATA *   HtmlOut_NewFromJsonString (
        ASTR_DATA       *pString
    );

    HTMLOUT_DATA *   HtmlOut_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


    /*!
     Generate text with color.
     @param     pColorA   Color Text
     @param     pTextA    Text to be displayed in the given color
     @return    If successful, an AStr object which must be released containing the
                text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     HtmlOut_ColorToStr (
        const
        char            *pColorA,
        const
        char            *pTextA
    );


    /*!
     Generate a <a></a> reference.
     @param     pHRefA    HREF Text
     @param     pNameA    Name Text to be displayed
     @return    If successful, an AStr object which must be released containing the
                text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     HtmlOut_RefToStr (
        const
        char            *pHRefA,
        const
        char            *pNameA
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    TEXTOUT_DATA *  HtmlOut_getOut (
        HTMLOUT_DATA    *this
    );


    bool            HtmlOut_getWS (
        HTMLOUT_DATA    *this
    );

    bool            HtmlOut_setWS (
        HTMLOUT_DATA    *this,
        bool            fValue
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Generate text with color.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         HtmlOut_Color (
        HTMLOUT_DATA    *this,
        const
        char            *pColorA,
        const
        char            *pTextA
    );


/*!
     Generate a number.
     @param     this    object pointer
     @param     dbl     floating point number
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         HtmlOut_Dbl (
        HTMLOUT_DATA    *this,
        double          dbl
    );


    ERESULT         HtmlOut_Disable (
        HTMLOUT_DATA    *this
    );


    ERESULT         HtmlOut_Enable (
        HTMLOUT_DATA    *this
    );

   
    HTMLOUT_DATA *  HtmlOut_Init (
        HTMLOUT_DATA    *this
    );


    ERESULT         HtmlOut_IsEnabled (
        HTMLOUT_DATA    *this
    );
    
 
    /*!
     Generate a <a></a> reference.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         HtmlOut_Ref (
        HTMLOUT_DATA    *this,
        const
        char            *pHRefA,
        const
        char            *pNameA
    );


    /*!
     Generate the paragraph separator (ie 3 blank lines).
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         HtmlOut_Sep (
        HTMLOUT_DATA    *this
    );


    /*!
     Generate the table starting definition.
     @param     this        object pointer
     @param     pCaptionA   optional caption to be included
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         HtmlOut_TableBegin (
        HTMLOUT_DATA    *this,
        const
        char            *pCaptionA
    );


    /*!
     Generate the end of a table
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         HtmlOut_TableEnd (
        HTMLOUT_DATA    *this
    );


    /*!
     Generate the beginning of a row. The normal usage is:
            TableRow()
            TableRowData()      <= 1 per column in table
            TableRowEnd()
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         HtmlOut_TableRow (
        HTMLOUT_DATA    *this
    );


    ERESULT         HtmlOut_TableRowData(
        HTMLOUT_DATA    *this,
        const
        char            *pStyle,
        const
        char            *pTextA
    );


    ERESULT         HtmlOut_TableRowEnd(
        HTMLOUT_DATA    *this
    );


#ifdef  HTMLOUT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = HtmlOut_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     HtmlOut_ToJson (
        HTMLOUT_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = HtmlOut_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     HtmlOut_ToDebugString (
        HTMLOUT_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* HTMLOUT_H */

