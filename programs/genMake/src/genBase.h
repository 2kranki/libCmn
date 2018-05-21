// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Generate Portions of a Makefile (genBase) Header
//****************************************************************
/*
 * Program
 *			Generate Portions of a Makefile (genBase)
 * Purpose
 *			This object provides a standardized way of generating
 *          makefiles in various operating system environments.
 *
 * Remarks
 *	1.      This object expects certain predefined constants in the
 *          dictionary.
 *  2.      'make' scans and executes variable definitions before it
 *          executes the make tree.  So, variables should be con-
 *          sidered global.
 *
 * History
 *	04/10/2018 Generated
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
#include        <node.h>
#include        <nodeArray.h>
#include        <nodeHash.h>
#include        <szHash.h>


#ifndef         GENBASE_H
#define         GENBASE_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct genBase_data_s	GENBASE_DATA;    // Inherits from OBJ.

    typedef struct genBase_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in genBase_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GENBASE_DATA *);
    } GENBASE_VTBL;


    typedef enum genBase_type_e {
        GENMAKE_TYPE_UNKNOW=0,
        GENMAKE_TYPE_MACOSX,
        GENMAKE_TYPE_MSC32,
        GENMAKE_TYPE_MSC64,
        GENMAKE_TYPE_PIC32
    } GENMAKE_TYPE;
    
    

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
     @return    pointer to genBase object if successful, otherwise OBJ_NIL.
     */
    GENBASE_DATA *  genBase_Alloc(
        void
    );
    
    
    OBJ_ID          genBase_Class(
        void
    );
    
    
    GENBASE_DATA *  genBase_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    DATETIME_DATA * genBase_getDateTime(
        GENBASE_DATA    *this
    );
    
    bool            genBase_setDateTime(
        GENBASE_DATA    *this,
        DATETIME_DATA   *pValue
    );

    
    SZHASH_DATA *   genBase_getDict(
        GENBASE_DATA    *this
    );
    
    bool            genBase_setDict(
        GENBASE_DATA    *this,
        SZHASH_DATA     *pValue
    );

    
    ERESULT         genBase_setGenerators(
        GENBASE_DATA    *this,
        ERESULT         (*pFinal)(GENBASE_DATA *),
        ERESULT         (*pInitial)(GENBASE_DATA *, ASTR_DATA *, NODEARRAY_DATA  *),
        ERESULT         (*pLibrary)(GENBASE_DATA *),
        ERESULT         (*pObjects)(GENBASE_DATA *, NODEHASH_DATA *, NODEARRAY_DATA  *),
        ERESULT         (*pOsSpecific)(GENBASE_DATA *, NODEHASH_DATA  *),
        ERESULT         (*pPrograms)(GENBASE_DATA *, NODEHASH_DATA  *),
        ERESULT         (*pTests)(GENBASE_DATA *, NODEHASH_DATA *)
    );
    
    
    ERESULT         genBase_getLastError(
        GENBASE_DATA    *this
    );


    ERESULT         genBase_setLibIncludePath(
        GENBASE_DATA    *this,
        PATH_DATA *     (*pLibIncludePath)(
                            GENBASE_DATA *,
                            const char *,
                            const char *,
                            const char *
                        )
    );

    
    ERESULT         genBase_setLibInstalledPath(
        GENBASE_DATA    *this,
        PATH_DATA *     (*pLibInstalledPath)(
                             GENBASE_DATA *,
                             const char *,
                             const char *,
                             const char *
                        )
        );
    
    
    ERESULT         genBase_setLibName(
        GENBASE_DATA    *this,
        ASTR_DATA *     (*pLibName)(
                            GENBASE_DATA *,
                            const char *,
                            const char *
                        )
    );
    
    
    /*!
     See GENMAKE_TYPE above for valid values.
     */
    uint16_t        genBase_getMakeType(
        GENBASE_DATA     *this
    );
    
    bool            genBase_setMakeType(
        GENBASE_DATA    *this,
        uint16_t        value
    );
    
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Library Include paths can be used for different purposes and
     can refer to different types of subdirectories. This requires
     dictionay entries for "LibIncludePath" and "LibIncludePrefix".
     */
    
    ASTR_DATA *     genBase_CFlagsLibIncludePath(
        GENBASE_DATA    *this,
        const
        char            *pName,             // Library Name
        const
        char            *pLibIncludePath,
        const
        char            *pLibNamePrefix
    );


    /*!
     Add the given name and its data to the dictionary.
     */
    
    ERESULT         genBase_DictAdd(
        GENBASE_DATA    *this,
        const
        char            *pName,            
        const
        char            *pData
    );
    
    
    GENBASE_DATA *  genBase_Init(
        GENBASE_DATA    *this
    );


    /*!
     Generate the Library Path given a name, the libraries super
     directory and an optional prefix.  The library super directory
     and optional library prefix name can either be supplied as a
     parameter of the method or they can be provided by the internal
     dictionary.  The dictionary will be accessed for "LibIncludePath"
     or "LibNamePrefix" if their respective method parameter is NULL.
     The diotionary entries for either can be over-ridden by passing
     "" instead of NULL.
     @param     this    object pointer
     @param     pName   library name
     @param     pLibIncludePath Optional directory which contains the
                library.  If NULL, then "LibIncludePath" must
                be present in the dictionary.
     @param     pLibNamePrefix  Optional prefix to the library name
                such as "lib".  If NULL, then "LibNamePrefix"
                will be used if present in the dictionary.
     @return    If successful, an path object which must be released containing the
                library directory path, otherwise OBJ_NIL.
     @warning   Remember to release the returned path object.
     */
    
    PATH_DATA *     genBase_LibIncludePath(
        GENBASE_DATA    *this,
        const
        char            *pName,             // Library Name
        const
        char            *pLibIncludePath,
        const
        char            *pLibNamePrefix
    );
    
 
    /*!
     Generate the Library Path given a name, the libraries super
     directory and an optional prefix.  The library super directory
     and optional library prefix name can either be supplied as a
     parameter of the method or they can be provided by the internal
     dictionary.  The dictionary will be accessed for "LibIncludePath"
     or "LibNamePrefix" if their respective method parameter is NULL.
     The diotionary entries for either can be over-ridden by passing
     "" instead of NULL.
     @param     this    object pointer
     @param     pName   library name
     @param     pLibInstalledPath Optional directory which contains the
                library.  If NULL, then "LibIncludePath" must
                be present in the dictionary.
     @param     pLibNamePrefix  Optional prefix to the library name
                such as "lib".  If NULL, then "LibNamePrefix"
                will be used if present in the dictionary.
     @return    If successful, an path object which must be released containing the
                library directory path, otherwise OBJ_NIL.
     @warning   Remember to release the returned path object.
     */
    
    PATH_DATA *     genBase_LibInstalledPath(
        GENBASE_DATA    *this,
        const
        char            *pName,             // Library Name
        const
        char            *pLibInstalledPath,
        const
        char            *pLibNamePrefix
    );
    
    
    /*!
     Generate the full Library Name given a name and an optional
     prefix.  The library prefix name can either be supplied as a
     parameter of the method or it can be provided by the internal
     dictionary.  The dictionary will be accessed for "LibNamePrefix"
     if the pLibNamePrefix parameter is NULL.  If the dictionary does
     not exist, the prefix is skipped.  The dictionary entry for
     the prefix can be over-ridden by passing "" instead of NULL.
     @param     this    object pointer
     @param     pName   library name
     @param     pLibNamePrefix  Optional prefix to the library name
                such as "lib".  If NULL, then "LibNamePrefix"
                will be used if present in the dictionary.
     @return    If successful, an string object which must be released
                containing the full library name, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    
    ASTR_DATA *     genBase_LibName(
        GENBASE_DATA    *this,
        const
        char            *pName,             // Library Name
        const
        char            *pLibNamePrefix
    );
    
    
    /*!
     Generate instructions to compile a 'C' object consisting of
     the object source and the method source files and sent to
     an appropriate object directory.
     @param     this    object pointer
     @param     pName   object class name
     @param     pSrcDir  Optional Source Directory Path or makefile
                variable such as "SRCDIR".  If NULL, then "SRCDIR"
                will be used.
     @param     pObjDir  Optional Object Direcotry Path or makefile
                variable such as "OBJDIR".  If NULL, then "OBJDIR"
                will be used.
     @return    If successful, an string object which must be released
                containing the makefile instructions, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    
    ASTR_DATA *     genBase_CompileObject(
        GENBASE_DATA    *this,
        const
        char            *pName,             // Object Class Name
        const
        char            *pSrcDir,
        const
        char            *pObjDir
    );
    
    
    /*!
     Generate instructions to compile a routine consisting of
     one source file in one of several languages.
     @param     this    object pointer
     @param     pName   routine file name including extension
     @param     pSrcDir  Optional Source Directory Path or makefile
                        variable such as "SRCDIR".  If NULL, then "SRCDIR"
                        will be used.
     @param     pObjDir  Optional Object Direcotry Path or makefile
                        variable such as "OBJDIR".  If NULL, then "OBJDIR"
                        will be used.
     @return    If successful, an string object which must be released
                containing the makefile instructions, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    
    ASTR_DATA *     genBase_CompileRoutine(
        GENBASE_DATA    *this,
        const
        char            *pName,             // Routine Name including extension
        const
        char            *pSrcDir,
        const
        char            *pObjDir
        );
    
    
    /*!
     Generate the compilation rules for various source types.
     @param     this    object pointer
     @param     pSrcDir  Optional Source Directory Path or makefile
                        variable such as "SRCDIR".  If NULL, then "SRCDIR"
                        will be used.
     @param     pObjDir  Optional Object Direcotry Path or makefile
                        variable such as "OBJDIR".  If NULL, then "OBJDIR"
                        will be used.
     @return    If successful, an string object which must be released
                containing the makefile instructions, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    
    ASTR_DATA *     genBase_CompileRules(
        GENBASE_DATA    *this,
        const
        char            *pSrcDir,
        const
        char            *pObjDir
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = genBase_ToDebugString(this,4);
     @endcode 
     @param     this    GENMAKE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    genBase_ToDebugString(
        GENBASE_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* GENBASE_H */

