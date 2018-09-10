// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          JSON Input Parsing Support (jsonIn) Header
//****************************************************************
/*
 * Program
 *			JSON Input Parsing Support (jsonIn)
 * Purpose
 *			This object provides a standardized way of parsing an
 *          HJSON node tree. The support routines help the individual
 *          object's JSON parser to successfully create objects
 *          from HJSON node trees.
 *
 *          In particular, it is capable of properly parsing
 *          sub-objects within the HSON tree as well as general
 *          parsing of objects that are unknown to begin with.
 *
 * Remarks
 *	1.      The ParseObject() method requires that all classes
 *          to be parsed by it must be previously defined.
 *  2.      Warning - Using this object will require memory for
 *          all object methods being called by ParseObject().
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
    
    
    /*!
     Find a named node in the JSON Hash Node tree.
     @param     this    Object Pointer
     @param     pSectionA Name of Node to be looked for
     @param     pTypeA  Name of Data Node ("array", "false", "hash",
                        "integer", "null", or "true")
     @param     ppData  Pointer to Data Object Pointer to be returned if
                        ERESULT_SUCCESS is returned.
     @return    If successful, ERESULT_SUCCESS and an integer value in *pInt
     if pInt is non-null, otherwise, ERESULT_* error code.
     */
    ERESULT         jsonIn_FindNodeInHashA(
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        const
        char            *pTypeA,
        OBJ_ID          *ppData
    );
    
    
    /*!
     Find a named node array in the JSON Hash Node tree.
     @param     this    Object Pointer
     @param     pSectionA Name of integer value (required)
     @param     ppArray Pointer to a node array pointer where data is to be returned if
                        ERESULT_SUCCESS is returned.
     @return    If successful, ERESULT_SUCCESS and a node array pointer in *ppArray
                if ppArray is non-null.  Otherwise, ERESULT_* error code.
     */
    ERESULT         jsonIn_FindArrayNodeInHashA(
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        NODEARRAY_DATA  **ppArray
    );
    
    
    /*!
     Find a named integer value in the JSON Hash Node tree.
     @param     this    Object Pointer
     @param     pSectionA Name of integer value (required)
     @param     pInt    integer pointer where data is to be returned too if
                        succesful ERESULT is returned.
     @return    If successful, ERESULT_SUCCESS and an integer value in *pInt
                if pInt is non-null, otherwise, ERESULT_* error code.
     */
    ERESULT         jsonIn_FindIntegerNodeInHashA(
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        int64_t         *pInt
    );
    
    
    ERESULT         jsonIn_FindNullNodeInHashA(
        JSONIN_DATA     *this,
        const
        char            *pSectionA
    );
    
    
    /*!
     Find a named string value in the JSON Hash Node tree.
     @param     this    Object Pointer
     @param     pSectionA Name of integer value (required)
     @param     ppStr   Pointer to a string pointer to be returned if
                        ERESULT_SUCCESS is returned and this pointer
                        is non-null.
     @return    If successful, ERESULT_SUCCESS and an sting value in *ppStr
                if ppStr is non-null. Otherwise, an ERESULT_* error code.
     */
    ERESULT         jsonIn_FindStringNodeInHashA(
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        ASTR_DATA       **ppStr
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
    
    
    /*!
     Parse an object from the current JSON Node tree using the object's
     class to call the specific JSON Input parsers for that class.
     @param     this    JSONIN object pointer
     @return    If successful, a new object pointer and the last error is
                set to ERESULT_SUCCESS, otherwise, OBJ_NIL and the last
                error is set to an ERESULT_* error code
     */
    OBJ_ID          jsonIn_ParseObject(
        JSONIN_DATA     *this
    );
    
    
    /*!
     Restore the JSON Node Tree that was saved from a prior call to the method,
     SubobjectInHash().
     @param     this    JSONIN object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise, ERESULT_* error code
     */
    ERESULT         jsonIn_SubobjectEnd(
        JSONIN_DATA     *this
    );
    
    
    /*!
     Set up the parser to process a JSON Hash Node tree by:
     *  Pushing the current JSON tree on the internal stack.
     *  Setting up the given JSON Hash Node as the parser input.
     @param     this    Object Pointer
     @param     pHash   JSON Hash Node (required)
     @return    If successful, ERESULT_SUCCESS, otherwise, ERESULT_* error code.
     @warning   The SubobjectEnd() method should be called once the sub-object
                is parsed.
     */
    ERESULT         jsonIn_SubobjectFromHash(
        JSONIN_DATA     *this,
        NODEHASH_DATA   *pHash
    );
    
    
    /*!
     Set up the parser to process a sub-object of the JSON Node tree by:
     *  Pushing the current JSON tree on the internal stack.
     *  Setting up the found section as the parser input.
     @param     this    JSONIN object pointer
     @param     pSect   Section Name String (required)
     @return    If successful, ERESULT_SUCCESS, otherwise, ERESULT_* error code.
     @warning   The SubobjectEnd() method should be called once the sub-object
                is parsed.
     */
    ERESULT         jsonIn_SubobjectInHash(
        JSONIN_DATA     *this,
        const
        char            *pSect
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

