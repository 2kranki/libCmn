// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Producer side of Producer/Consumer (Producer) Header
//****************************************************************
/*
 * Program
 *          Producer side of Producer/Consumer (Producer)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate Producer to run things without complications
 *          of interfering with the main Producer. A Producer may be 
 *          called a Producer on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  05/04/2021 Generated
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


#ifndef         PRODUCER_H
#define         PRODUCER_H


//#define   PRODUCER_IS_IMMUTABLE     1
//#define   PRODUCER_JSON_SUPPORT     1
//#define   PRODUCER_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Producer_data_s  PRODUCER_DATA;            // Inherits from OBJ
    typedef struct Producer_class_data_s PRODUCER_CLASS_DATA;   // Inherits from OBJ

    typedef struct Producer_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Producer_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PRODUCER_DATA *);
    } PRODUCER_VTBL;

    typedef struct Producer_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Producer_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PRODUCER_DATA *);
    } PRODUCER_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  PRODUCER_SINGLETON
    PRODUCER_DATA *     Producer_Shared (
        void
    );

    void            Producer_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Producer object if successful, otherwise OBJ_NIL.
     */
    PRODUCER_DATA *     Producer_Alloc (
        void
    );
    
    
    OBJ_ID          Producer_Class (
        void
    );
    
    
    PRODUCER_DATA *     Producer_New (
        void
    );
    
    
#ifdef  PRODUCER_JSON_SUPPORT
    PRODUCER_DATA *   Producer_NewFromJsonString (
        ASTR_DATA       *pString
    );

    PRODUCER_DATA *   Producer_NewFromJsonStringA (
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

    ERESULT     Producer_Disable (
        PRODUCER_DATA       *this
    );


    ERESULT     Producer_Enable (
        PRODUCER_DATA       *this
    );

   
    PRODUCER_DATA *   Producer_Init (
        PRODUCER_DATA     *this
    );


    ERESULT     Producer_IsEnabled (
        PRODUCER_DATA       *this
    );
    
 
#ifdef  PRODUCER_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Producer_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Producer_ToJson (
        PRODUCER_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Producer_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Producer_ToDebugString (
        PRODUCER_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* PRODUCER_H */

