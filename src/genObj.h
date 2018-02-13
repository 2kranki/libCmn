// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Generate an Object (genObj) Header
//****************************************************************
/*
 * Program
 *			Generate an Object (genObj)
 * Purpose
 *			This object provides a way of generating a new Object.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/09/2017 Generated
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
#include        <path.h>


#ifndef         GENOBJ_H
#define         GENOBJ_H


#define GENOBJ_CLASSNAME        "ClassName"
#define GENOBJ_SUPERCLASSNAME   "SuperClassName"



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct genObj_data_s	GENOBJ_DATA;    // Inherits from OBJ.

    typedef struct genObj_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in genObj_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GENOBJ_DATA *);
    } GENOBJ_VTBL;



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
     @return    pointer to genObj object if successful, otherwise OBJ_NIL.
     */
    GENOBJ_DATA *     genObj_Alloc(
        void
    );
    
    
    GENOBJ_DATA *     genObj_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     ClassName is the object's class name in lower and upper case
     which is used in the prefix to method names. Internally, an
     upper case only version will be used to create the _DATA
     definitions.
     */
    ASTR_DATA * genObj_getClassName(
        GENOBJ_DATA     *this
    );
    
    bool        genObj_setClassName(
        GENOBJ_DATA *this,
        ASTR_DATA   *pValue
    );
    

    ERESULT     genObj_getLastError(
        GENOBJ_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Generate the Internal Object Header.
     @param     this    GENOBJ object pointer
     @param     pIncludes Pointer to a UTF-8 Character String representing the
                        additional includes that might be needed in the hearder
     @return    If successful, an ASTR_DATA object which contains the internal
                header. Otherwise, OBJ_NIL and an ERESULT_* error code is set
                in Last Error.
     */
    ASTR_DATA *     genObj_GenInternalHeader(
        GENOBJ_DATA     *this,
        const
        char            *pIncludes
    );
    
    
    GENOBJ_DATA *   genObj_Init(
        GENOBJ_DATA     *this
    );


    /*!
     Create a new string from an input text that contains simple bash-like substitution.
     The input text is added to the returned string until a variable name starting with
     "$..." or "${...}" is found.  "..." denotes up to 64 alphanumeric characters that
     make up a variable name.  If the variable name is found in the variable hash, its
     data string is substituted in the output string.  Otherwise, the variable name is
     passed through in the "${...}" form.
     @param     this    GENOBJ object pointer
     @param     pStr    the input text string
     @return    If successful, an AStr object which must be released containing the
                expanded text, otherwise OBJ_NIL and an appropriate ERESULT_* error
                code in Last Error.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     genObj_Substitute(
        GENOBJ_DATA     *this,
        ASTR_DATA       *pStr       // Input String
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = genObj_ToDebugString(this,4);
     @endcode 
     @param     this    GENOBJ object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    genObj_ToDebugString(
        GENOBJ_DATA     *this,
        int             indent
    );
    
    
    /*!
     Add a variable to the Substitution Variables.
     @param     this    GENOBJ object pointer
     @param     pName   Pointer to a UTF-8 Character String representing the
                        variable's symbolic name
     @param     pValue  Pointer to an AStr object representing the
                        variable's substitution value
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         genObj_VarAdd(
        GENOBJ_DATA     *this,
        const
        char            *pName,
        ASTR_DATA       *pValue
    );
    
    ERESULT         genObj_VarAddA(
        GENOBJ_DATA     *this,
        const
        char            *pName,
        const
        char            *pValue
    );
    

    ASTR_DATA *     genObj_VarFind(
        GENOBJ_DATA     *this,
        const
        char            *pName
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* GENOBJ_H */

