// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          DBPRS Console Transmit Task (dbPrs) Header
//****************************************************************
/*
 * Program
 *			Separate dbPrs (dbPrs)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate dbPrs to run things without complications
 *          of interfering with the main dbPrs. A dbPrs may be 
 *          called a dbPrs on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/30/2018 Generated
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





#include        <genObject.h>
#include        <AStr.h>
#include        <genBase.h>
#include        <jsonIn.h>
#include        <node.h>


#ifndef         DBPRS_H
#define         DBPRS_H


//#define   DBPRS_SINGLETON    1
#define     PROPERTY_STR_OWNED 1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct dbPrs_data_s	DBPRS_DATA;            // Inherits from OBJ
    typedef struct dbPrs_class_data_s DBPRS_CLASS_DATA;   // Inherits from OBJ

    typedef struct dbPrs_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in dbPrs_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DBPRS_DATA *);
    } DBPRS_VTBL;

    typedef struct dbPrs_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in dbPrs_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DBPRS_DATA *);
    } DBPRS_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  DBPRS_SINGLETON
    DBPRS_DATA *     dbPrs_Shared(
        void
    );

    bool            dbPrs_SharedReset(
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to dbPrs object if successful, otherwise OBJ_NIL.
     */
    DBPRS_DATA *     dbPrs_Alloc(
        void
    );
    
    
    OBJ_ID          dbPrs_Class(
        void
    );
    
    
    DBPRS_DATA *     dbPrs_New(
        void
    );
    
    
    DBPRS_DATA *    dbPrs_NewWithDictAndGen(
        NODEBTP_DATA    *pDict,
        GENBASE_DATA    *pGen
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NODEBTP_DATA *  dbPrs_getDict(
        DBPRS_DATA      *this
    );
    
    bool            dbPrs_setDict(
        DBPRS_DATA      *this,
        NODEBTP_DATA    *pValue
    );
    
    
    GENBASE_DATA *  dbPrs_getGen(
        DBPRS_DATA     *this
    );
    
    bool            dbPrs_setGen(
        DBPRS_DATA      *this,
        GENBASE_DATA    *pValue
    );
    
    
    JSONIN_DATA *   dbPrs_getJson(
        DBPRS_DATA     *this
    );
    
    bool            dbPrs_setJson(
        DBPRS_DATA      *this,
        JSONIN_DATA     *pValue
    );
    
    
    NODE_DATA *     dbPrs_getNodes(
        DBPRS_DATA     *this
    );
    
    bool            dbPrs_setNodes(
        DBPRS_DATA      *this,
        NODE_DATA       *pValue
    );
    
    
    ASTR_DATA *     dbPrs_getStr(
        DBPRS_DATA     *this
    );
    
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         dbPrs_Finalize (
        DBPRS_DATA		*this
    );


    DBPRS_DATA *    dbPrs_Init (
        DBPRS_DATA     *this
    );


    ERESULT         dbPrs_ParseInputFile (
        DBPRS_DATA      *this,
        PATH_DATA       *pPath
    );
    
    
    ERESULT         dbPrs_ParseInputStr (
        DBPRS_DATA      *this,
        const
        char            *pStr
    );

    
    /*!
     Parse an object and generate its components
     Node Grammar:
     object     : string                // Object's Name
                | node ':' objectData   // Node's Name == Object's Name
                ;
     
     objectData : '{' object_Hash '}'
                | '[' deps ']'
                | "null"
                ;
     object_Hash:
     "deps"     : '[' deps ']'
                ;
     // Generate JSON object compile or not
     "json"     : "true"
                | "null"    // Same as "true"
                | "false" (default)
                ;
     // Generate Test compile and execution or not
     // (optionally with extra compilation source files)
     "test"     : "true" (default)
                | "false"
                | '[' source files ']'
                | '{' test_Hash '}'
                ;
     test_Hash  :
        "deps"  : '[' deps ']'
                ;
        "srcs"  : '[' deps ']'
                ;
     // Additional Dependency Files must be in the same directory
     // as the primary file that it is associated with.
     deps       : dependencies_file_name [',' deps]
                ;
     // Additional Source Files must be in the same directory
     // as the primary file that it is associated with.
     srcs       : source_file_name [',' srcs]
                ;
     
     @param     this    Object Pointer
     @param     pNode   Object Node Pointer
     @return    If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ERESULT         dbPrs_ParseObject (
        DBPRS_DATA      *this,
        NODE_DATA       *pNode
    );
    
    
    /*!
     Parse an object and generate its components
     Node Grammar:
     objects    : '{' objects_Hash '}'
                ;
     object_Hash : objectNode (',' object_Hash)
                ;
     Note: See ParseObject() for definition of objectNode.
     @param     this    Object Pointer
     @param     pHash   Node Hash Pointer
     @return    If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ERESULT         dbPrs_ParseObjects (
        DBPRS_DATA      *this,
        NODEHASH_DATA   *pHash
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = dbPrs_ToDebugString(this,4);
     @endcode 
     @param     this    DBPRS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    dbPrs_ToDebugString (
        DBPRS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DBPRS_H */

