// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Endianess Support (Big/Little) (Endian) Header
//****************************************************************
/*
 * Program
 *          Endianess Support (Big/Little) (Endian)
 * Purpose
 *          This object provides methods to transform numbers from
 *          big endian format to little endian format and vice versa.
 *          See https://en.wikipedia.org/wiki/Endianness for a good
 *          description of endianness.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  10/25/2016 Generated
 *  09/19/2021 Regenerated with new naming
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


#ifndef         ENDIAN_H
#define         ENDIAN_H

#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
#elif defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#else
    #error  Unsupported Environemt!
#endif

//#define   ENDIAN_IS_IMMUTABLE     1
//#define   ENDIAN_JSON_SUPPORT     1
//#define   ENDIAN_SINGLETON        1



#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Endian_data_s  ENDIAN_DATA;            // Inherits from OBJ
    typedef struct Endian_class_data_s ENDIAN_CLASS_DATA;   // Inherits from OBJ

    typedef struct Endian_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Endian_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ENDIAN_DATA *);
    } ENDIAN_VTBL;

    typedef struct Endian_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Endian_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ENDIAN_DATA *);
    } ENDIAN_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  ENDIAN_SINGLETON
    ENDIAN_DATA *   Endian_Shared (
        void
    );

    void            Endian_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Endian object if successful, otherwise OBJ_NIL.
     */
    ENDIAN_DATA *   Endian_Alloc (
        void
    );
    
    
    OBJ_ID          Endian_Class (
        void
    );
    
    
    uint16_t        Endian_GetU16Big(
        void            *pValue
    );

    uint16_t        Endian_GetU16Little(
        void            *pValue
    );


    uint32_t        Endian_GetU24Big(
        void            *pValue
    );

    uint32_t        Endian_GetU24Little(
        void            *pValue
    );


    uint32_t        Endian_GetU32Big(
        void            *pValue
    );

    uint32_t        Endian_GetU32Little(
        void            *pValue
    );


    uint64_t        Endian_GetU64Big(
        void            *pValue
    );

    uint64_t        Endian_GetU64Little(
        void            *pValue
    );


    /*!
     Check if the current environment is Little Endian.
     @return    If the current environment is Little Endian, return true.
                Otherwise, return false.
     */
    bool            Endian_IsLittle(
        void
    );


    ENDIAN_DATA *   Endian_New (
        void
    );
    
    
#ifdef  ENDIAN_JSON_SUPPORT
    ENDIAN_DATA *   Endian_NewFromJsonString (
        ASTR_DATA       *pString
    );

    ENDIAN_DATA *   Endian_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


    ERESULT         Endian_PutU16Big(
        void            *pValue,        // Out
        uint16_t        value           // In
    );

    ERESULT         Endian_PutU16Little(
        void            *pValue,        // Out
        uint16_t        value           // In
    );


    ERESULT         Endian_PutU24Big(
        void            *pValue,        // Out
        uint32_t        value           // In
    );

    ERESULT         Endian_PutU24Little(
        void            *pValue,        // Out
        uint32_t        value           // In
    );


    ERESULT         Endian_PutU32Big(
        void            *pValue,        // Out
        uint32_t        value           // In
    );

    ERESULT         Endian_PutU32Little(
        void            *pValue,        // Out
        uint32_t        value           // In
    );


    ERESULT         Endian_PutU64Big(
        void            *pValue,        // Out
        uint64_t        value           // In
    );

    ERESULT         Endian_PutU64Little(
        void            *pValue,        // Out
        uint64_t        value           // In
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     Endian_Disable (
        ENDIAN_DATA       *this
    );


    ERESULT     Endian_Enable (
        ENDIAN_DATA       *this
    );

   
    ENDIAN_DATA *   Endian_Init (
        ENDIAN_DATA     *this
    );


    ERESULT     Endian_IsEnabled (
        ENDIAN_DATA       *this
    );
    
 
#ifdef  ENDIAN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Endian_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Endian_ToJson (
        ENDIAN_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Endian_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Endian_ToDebugString (
        ENDIAN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* ENDIAN_H */

