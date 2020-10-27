// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Disk File Management (File) Header
//****************************************************************
/*
 * Program
 *          Disk File Management (File)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate File to run things without complications
 *          of interfering with the main File. A File may be 
 *          called a File on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  10/27/2020 Generated
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
#include        <u8Array.h>


#ifndef         FILE_H
#define         FILE_H


//#define   FILE_IS_IMMUTABLE     1
//#define   FILE_JSON_SUPPORT     1
//#define   FILE_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct File_data_s  FILE_DATA;            // Inherits from OBJ
    typedef struct File_class_data_s FILE_CLASS_DATA;   // Inherits from OBJ

    typedef struct File_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in File_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(FILE_DATA *);
    } FILE_VTBL;

    typedef struct File_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in File_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(FILE_DATA *);
    } FILE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  FILE_SINGLETON
    FILE_DATA *     File_Shared (
        void
    );

    void            File_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to File object if successful, otherwise OBJ_NIL.
     */
    FILE_DATA *     File_Alloc (
        void
    );
    
    
    OBJ_ID          File_Class (
        void
    );
    
    
    ERESULT         File_DeleteA(
        const
        char            *pPath
    );


    FILE_DATA *     File_New (
        void
    );
    
    
#ifdef  FILE_JSON_SUPPORT
    FILE_DATA *   File_NewFromJsonString (
        ASTR_DATA       *pString
    );

    FILE_DATA *   File_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


    ERESULT         File_RenameA(
        const
        char            *pPathOldA,
        const
        char            *pPathNewA
    );


    int64_t         File_SizeA(
        const
        char            *pPath
    );


    ERESULT         File_ToArrayA(
        const
        char            *pPath,
        U8ARRAY_DATA    **ppArray
    );


    ERESULT         File_ToBufferA(
        const
        char            *pPath,
        uint8_t         **ppBuffer
    );


    /*!
     If the file path is present, update its last used date/time.  If the
     file path is not present, create it with no data.
     @param     pPathA  UTF-8 file path pointer
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         File_TouchA(
        const
        char            *pPathA
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     File_Disable (
        FILE_DATA       *this
    );


    ERESULT     File_Enable (
        FILE_DATA       *this
    );

   
    FILE_DATA *   File_Init (
        FILE_DATA     *this
    );


    ERESULT     File_IsEnabled (
        FILE_DATA       *this
    );
    
 
#ifdef  FILE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = File_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     File_ToJson (
        FILE_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = File_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     File_ToDebugString (
        FILE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* FILE_H */

