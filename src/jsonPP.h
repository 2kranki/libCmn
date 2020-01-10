// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          JSONPP Console Transmit Task (jsonPP) Header
//****************************************************************
/*
 * Program
 *			Separate jsonPP (jsonPP)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate jsonPP to run things without complications
 *          of interfering with the main jsonPP. A jsonPP may be 
 *          called a jsonPP on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	08/27/2019 Generated
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
#include        <node.h>
#include        <NodeArray.h>
#include        <nodeHash.h>


#ifndef         JSONPP_H
#define         JSONPP_H


//#define   JSONPP_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct jsonPP_data_s	JSONPP_DATA;            // Inherits from OBJ
    typedef struct jsonPP_class_data_s JSONPP_CLASS_DATA;   // Inherits from OBJ

    typedef struct jsonPP_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in jsonPP_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(JSONPP_DATA *);
    } JSONPP_VTBL;

    typedef struct jsonPP_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in jsonPP_object.c.
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
    JSONPP_DATA *     jsonPP_Shared (
        void
    );

    bool            jsonPP_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to jsonPP object if successful, otherwise OBJ_NIL.
     */
    JSONPP_DATA *   jsonPP_Alloc (
        void
    );
    
    
    OBJ_ID          jsonPP_Class (
        void
    );
    
    
    JSONPP_DATA *   jsonPP_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        jsonPP_getIndent (
        JSONPP_DATA     *this
    );
    
    bool            jsonPP_setIndent (
        JSONPP_DATA     *this,
        uint32_t        value
    );

    
    ASTR_DATA *     jsonPP_getStr (
        JSONPP_DATA     *this
    );
    
    bool            jsonPP_setStr (
        JSONPP_DATA     *this,
        ASTR_DATA       *pValue
    );

    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    JSONPP_DATA *   jsonPP_Init (
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
    ERESULT         jsonPP_PrettyPrint(
        JSONPP_DATA     *this,
        NODE_DATA       *pNodes,
        uint32_t        indent,
        ASTR_DATA       **ppStr
    );
    
        
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = jsonPP_ToDebugString(this,4);
     @endcode 
     @param     this    JSONPP object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    jsonPP_ToDebugString (
        JSONPP_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* JSONPP_H */

