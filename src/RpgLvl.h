// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Rpg Level Handler (RpgLvl) Header
//****************************************************************
/*
 * Program
 *          Rpg Level Handler (RpgLvl)
 * Purpose
 *          This object provides a base for each level in the Report
 *          Program Generatorr (RPG) system. It is designed to be
 *          inherited.  The inheriting class would provide data
 *          storage and support specific level support for the level
 *          that it was created for. There are 9 levels with 1 being
 *          the most important and 9 being the least.  There is
 *          also a detail and summary levels which are required.
 *          See RPGBASE_LEVELS in RpgBase.h.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  05/23/2021 Generated
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
#include        <RpgBase.h>


#ifndef         RPGLVL_H
#define         RPGLVL_H


//#define   RPGLVL_IS_IMMUTABLE     1
#define   RPGLVL_JSON_SUPPORT       1
//#define   RPGLVL_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // RPGLVL_DATA is defined in RpgBase.h
    typedef struct RpgLvl_class_data_s RPGLVL_CLASS_DATA;   // Inherits from OBJ

    // RPGLVL_VTBL is defined in RpgBase.h

    typedef struct RpgLvl_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    } RPGLVL_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  RPGLVL_SINGLETON
    RPGLVL_DATA *     RpgLvl_Shared (
        void
    );

    void            RpgLvl_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to RpgLvl object if successful, otherwise OBJ_NIL.
     */
    RPGLVL_DATA *     RpgLvl_Alloc (
        void
    );
    
    
    OBJ_ID          RpgLvl_Class (
        void
    );
    
    
    RPGLVL_DATA *   RpgLvl_New (
        void
    );
    
    
    RPGLVL_DATA *   RpgLvl_NewLevel (
        uint16_t        value
    );


#ifdef  RPGLVL_JSON_SUPPORT
    RPGLVL_DATA *   RpgLvl_NewFromJsonString (
        ASTR_DATA       *pString
    );

    RPGLVL_DATA *   RpgLvl_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        RpgLvl_getLevel (
        RPGLVL_DATA     *this
    );

    bool            RpgLvl_setLevel (
        RPGLVL_DATA     *this,
        uint16_t        value
    );

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     RpgLvl_Disable (
        RPGLVL_DATA       *this
    );


    ERESULT     RpgLvl_Enable (
        RPGLVL_DATA       *this
    );

   
    RPGLVL_DATA *   RpgLvl_Init (
        RPGLVL_DATA     *this
    );


    ERESULT     RpgLvl_IsEnabled (
        RPGLVL_DATA       *this
    );
    
 
#ifdef  RPGLVL_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = RpgLvl_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RpgLvl_ToJson (
        RPGLVL_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = RpgLvl_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RpgLvl_ToDebugString (
        RPGLVL_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* RPGLVL_H */

