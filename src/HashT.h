// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Generic Hash Table (HashT) Header
//****************************************************************
/*
 * Program
 *          Generic Hash Table (HashT)
 * Purpose
 *          This object provides a generic scoped hash table. Scope
 *          0 is automatically created at object creation and
 *          optionally is the only scope needed.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  12/12/2021 Generated
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


#ifndef         HASHT_H
#define         HASHT_H


//#define   HASHT_IS_IMMUTABLE     1
//#define   HASHT_JSON_SUPPORT     1
//#define   HASHT_SINGLETON        1
//#define       HASHT_LOG   1


#ifdef   HASHT_LOG
#include        <logInterface.h>
#endif



#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct HashT_data_s  HASHT_DATA;          // Inherits from BLOCKS
    typedef struct HashT_class_data_s HASHT_CLASS_DATA;  // Inherits from OBJ

    typedef struct HashT_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //HashT_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in HashT_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(HASHT_DATA *);
    } HASHT_VTBL;

    typedef struct HashT_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in HashT_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(HASHT_DATA *);
    } HASHT_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  HASHT_SINGLETON
    HASHT_DATA *     HashT_Shared (
        void
    );

    void            HashT_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to HashT object if successful, otherwise OBJ_NIL.
     */
    HASHT_DATA *     HashT_Alloc (
        void
    );
    
    
    OBJ_ID          HashT_Class (
        void
    );
    
    
    HASHT_DATA *     HashT_New (
        void
    );
    
    
#ifdef  HASHT_JSON_SUPPORT
    HASHT_DATA *   HashT_NewFromJsonString (
        ASTR_DATA       *pString
    );

    HASHT_DATA *   HashT_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
    * The delete exit is called whenever an active record is to be
    * freed allowing any clean up to be performed.
    */
    bool            HashT_setDeleteExit (
        HASHT_DATA      *this,
        P_ERESULT_EXIT3 pDelete,
        OBJ_ID          pObj,           // Used as first parameter of scan method
        void            *pArg3          // Used as third parameter of scan method
    );


#ifdef HASHT_LOG
    /*! @property   Logging
        Allows information and warning messages to be issued for this
        object. Messages will be skipped if Log is not set.
     */
    bool            HashT_setLog (
        HASHT_DATA    *this,
        OBJ_ID          pObj
    );
#endif


    uint32_t        HashT_getNumScopes (
        HASHT_DATA       *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the given data to the table in the current scope.
     @param     this    object pointer
     @param     hash    required Hash code for data
     @param     pData   required data pointer which must have dataSize bytes
                        available
     @param     pIndex  optional pointer to return the index of the new hash
                        table entry.  This index is unique and will not change.
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         HashT_Add (
        HASHT_DATA      *this,
        uint32_t        hash,
        void            *pData,
        uint32_t        *pIndex
    );

    /*!
     Add the given data to the table in the given scope.
     @param     this    object pointer
     @param     scope   required scope level relative to 0
     @param     hash    required Hash code for data
     @param     pData   required data pointer which must have dataSize bytes
                        available
     @param     pIndex  optional pointer to return the index of the new hash
                        table entry.  This index is unique and will not change.
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         HashT_AddInScope (
        HASHT_DATA      *this,
        uint32_t        scope,
        uint32_t        hash,
        void            *pData,
        uint32_t        *pIndex
    );


    ERESULT     HashT_Enable (
        HASHT_DATA       *this
    );

   
    HASHT_DATA *   HashT_Init (
        HASHT_DATA     *this
    );


    ERESULT     HashT_IsEnabled (
        HASHT_DATA       *this
    );
    
 
    /*!
     Perform initial setup of the hash table.
     @param     this        object pointer
     @param     dataSize    Size in bytes of the data
     @param     cHash       Number of Buckets in the Hash Table.
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         HashT_Setup (
        HASHT_DATA      *this,
        uint16_t        dataSize,
        uint16_t        cHash           // [in] Hash Table Size
    );


#ifdef  HASHT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = HashT_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     HashT_ToJson (
        HASHT_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = HashT_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     HashT_ToDebugString (
        HASHT_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* HASHT_H */

