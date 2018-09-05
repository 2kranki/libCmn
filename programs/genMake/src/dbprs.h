// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          JSON Database Parser (dbprs) Header
//****************************************************************
/*
 * Program
 *			JSON Database Parser (dbprs)
 * Purpose
 *			This object parses the JSON Database and its component
 *          sections.  It then calls the appropriate generation
 *          routines to generate the output.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	09/04/2018 Generated
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





#include        <genMake.h>
#include        <AStr.h>
#include        <genBase.h>
#include        <node.h>


#ifndef         DBPRS_H
#define         DBPRS_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct dbprs_data_s	DBPRS_DATA;    // Inherits from OBJ.

    typedef struct dbprs_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in dbprs_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DBPRS_DATA *);
    } DBPRS_VTBL;



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
     @return    pointer to dbprs object if successful, otherwise OBJ_NIL.
     */
    DBPRS_DATA *    dbprs_Alloc(
        void
    );
    
    
    OBJ_ID          dbprs_Class(
        void
    );
    
    
    DBPRS_DATA *    dbprs_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    GENBASE_DATA *  dbprs_getGen(
        DBPRS_DATA     *this
    );
    
    bool            dbprs_setGen(
        DBPRS_DATA      *this,
        GENBASE_DATA    *pValue
    );

    
    NODE_DATA *     dbprs_getNodes(
        DBPRS_DATA     *this
    );
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    DBPRS_DATA *    dbprs_Init(
        DBPRS_DATA     *this
    );


    ERESULT         dbprs_ParseInputFile(
        DBPRS_DATA      *this,
        PATH_DATA       *pPath
    );
    
    
    ERESULT         dbprs_ParseInputStr(
        DBPRS_DATA      *this,
        const
        char            *pStr
    );
    
    
    /*!
     Parse an object and generate its components
     Node Grammar:
        object = object_Hash | object_Array;
        object_Array = JSON_Array of header dependencies
        object_Hash = JSON Hash of:
            "deps" : JSON_Array of header dependencies
            "json" : "true" or "false" (default) // Generate JSON object compile or not
            "test" : "true" (default) or "false" // Generate Test compile and execution
                                                 // or not
     @param     this    DBPRS object pointer
     @param     pNode   Object Node Pointer
     @return    If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ERESULT         dbprs_ParseObject(
        DBPRS_DATA      *this,
        NODE_DATA       *pNode
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = dbprs_ToDebugString(this,4);
     @endcode 
     @param     this    DBPRS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    dbprs_ToDebugString(
        DBPRS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DBPRS_H */

