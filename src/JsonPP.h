// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Pretty Print a JSON Structure (JsonPP) Header
//****************************************************************
/*
 * Program
 *			Pretty Print a JSON Structure (JsonPP)
 * Purpose
 *			This object pretty prints a JSON structure.
 *
 * Remarks
 *	1.      None
 *
 * History
 *  08/27/2019 Generated
 *	01/25/2020 Regenerated
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
#include        <NodeArray.h>
#include        <NodeHash.h>


#ifndef         JSONPP_H
#define         JSONPP_H


//#define   JSONPP_IS_CONSTANT      1
//#define   JSONPP_JSON_SUPPORT     1
//#define   JSONPP_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct JsonPP_data_s	JSONPP_DATA;            // Inherits from OBJ
    typedef struct JsonPP_class_data_s JSONPP_CLASS_DATA;   // Inherits from OBJ

    typedef struct JsonPP_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in JsonPP_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(JSONPP_DATA *);
    } JSONPP_VTBL;

    typedef struct JsonPP_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in JsonPP_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(JSONPP_DATA *);
    } JSONPP_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  JSONPP_SINGLETON
    JSONPP_DATA *   JsonPP_Shared (
        void
    );

    void            JsonPP_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to JsonPP object if successful, otherwise OBJ_NIL.
     */
    JSONPP_DATA *   JsonPP_Alloc (
        void
    );
    
    
    OBJ_ID          JsonPP_Class (
        void
    );
    
    
    JSONPP_DATA *   JsonPP_New (
        void
    );
    
    
#ifdef  JSONPP_JSON_SUPPORT
    JSONPP_DATA *   JsonPP_NewFromJsonString(
        ASTR_DATA       *pString
    );

    JSONPP_DATA *   JsonPP_NewFromJsonStringA(
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        JsonPP_getIndent (
        JSONPP_DATA     *this
    );

    bool            JsonPP_setIndent (
        JSONPP_DATA     *this,
        uint32_t        value
    );


    ASTR_DATA *     JsonPP_getStr (
        JSONPP_DATA     *this
    );

    bool            JsonPP_setStr (
        JSONPP_DATA     *this,
        ASTR_DATA       *pValue
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     JsonPP_Disable (
        JSONPP_DATA		*this
    );


    ERESULT     JsonPP_Enable (
        JSONPP_DATA		*this
    );

   
    JSONPP_DATA *   JsonPP_Init (
        JSONPP_DATA     *this
    );


    /*!
     Pretty print the given JSON Node Hash returning a formated string
     @param     this    object pointer
     @param     pNodes  Node pointer for highest level hash in JSON Tree
     @param     indent  starting number of characters to indent every line of
                output, can be 0. The default indent amount will be added to this
                when appropriate for proper indentation.
     @param     ppStr   (Optional) pointer to an ASTR_DATA * which will contain
                        the pretty printed JSON if successful.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error code.
     @warning   Remember to release the returned AStr object if returned.
     */
    ERESULT         JsonPP_PrettyPrint (
        JSONPP_DATA     *this,
        NODE_DATA       *pNodes,
        uint32_t        indent,
        ASTR_DATA       **ppStr
    );


#ifdef  JSONPP_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = JsonPP_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     JsonPP_ToJson(
        JSONPP_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = JsonPP_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    JsonPP_ToDebugString (
        JSONPP_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* JSONPP_H */

