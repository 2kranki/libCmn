// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          JSONIN Console Transmit Task (jsonIn) Header
//****************************************************************
/*
 * Program
 *			Separate jsonIn (jsonIn)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate jsonIn to run things without complications
 *          of interfering with the main jsonIn. A jsonIn may be 
 *          called a jsonIn on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/21/2017 Generated
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
#include        <nodeHash.h>


#ifndef         JSONIN_H
#define         JSONIN_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct jsonIn_data_s	JSONIN_DATA;    // Inherits from OBJ.

    typedef struct jsonIn_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in jsonIn_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(JSONIN_DATA *);
    } JSONIN_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to jsonIn object if successful, otherwise OBJ_NIL.
     */
    JSONIN_DATA *   jsonIn_Alloc(
        void
    );
    
    
    OBJ_ID          jsonIn_Class(
        void
    );
    
    
    JSONIN_DATA *   jsonIn_New(
        void
    );
    
    JSONIN_DATA *   jsonIn_NewFromHash(
        NODEHASH_DATA   *pHash
    );
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NODE_DATA *     jsonIn_getFileNode(
        JSONIN_DATA     *this
    );
    
    
    NODEHASH_DATA * jsonIn_getHash(
        JSONIN_DATA     *this
    );
    
    
    ERESULT     jsonIn_getLastError(
        JSONIN_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         jsonIn_ConfirmObjectType(
        JSONIN_DATA     *this,
        const
        char            *pType
    );
    
    
    NODE_DATA *     jsonIn_FindNodeInHash(
        JSONIN_DATA     *this,
        const
        char            *pSection,
        const
        char            *pType
    );
    
    
    int64_t         jsonIn_FindIntegerNodeInHash(
        JSONIN_DATA     *this,
        const
        char            *pSection
    );
    
    
    bool            jsonIn_FindNullNodeInHash(
        JSONIN_DATA     *this,
        const
        char            *pSection
    );
    
    
    ASTR_DATA *     jsonIn_FindStringNodeInHash(
        JSONIN_DATA     *this,
        const
        char            *pSection
    );
    
    
    JSONIN_DATA *   jsonIn_Init(
        JSONIN_DATA     *this
    );


    /*!
     Parse the given input string using the HJSON parser and set up
     the returned node structure to be analyzed by other methods
     in this object.
     @param     this    JSONIN object pointer
     @param     pStr    pointer to AStr input string (required)
     @return    If successful, ERESULT_SUCCESS, otherwise, ERESULT_* error code
     */
    ERESULT         jsonIn_ParseAStr(
        JSONIN_DATA     *this,
        ASTR_DATA       *pStr
    );
    
    
    NODEHASH_DATA * jsonIn_SubobjectInHash(
        JSONIN_DATA     *this,
        const
        char            *pSection
    );
    
    
    bool            jsonIn_SubobjectEnd(
        JSONIN_DATA     *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = jsonIn_ToDebugString(this,4);
     @endcode 
     @param     this    JSONIN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    jsonIn_ToDebugString(
        JSONIN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* JSONIN_H */

