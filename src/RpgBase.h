// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Report Program Generator (RPG) Base (RpgBase) Header
//****************************************************************
/*
 * Program
 *          Report Program Generator (RPG) Base (RpgBase)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate RpgBase to run things without complications
 *          of interfering with the main RpgBase. A RpgBase may be 
 *          called a RpgBase on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  03/22/2021 Generated
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
#include        <NodeBT.h>


#ifndef         RPGBASE_H
#define         RPGBASE_H


//#define   RPGBASE_IS_IMMUTABLE     1
#define   RPGBASE_JSON_SUPPORT       1
//#define   RPGBASE_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct RpgBase_data_s  RPGBASE_DATA;            // Inherits from OBJ
    typedef struct RpgBase_class_data_s RPGBASE_CLASS_DATA;   // Inherits from OBJ

    typedef struct RpgBase_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RpgBase_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(RPGBASE_DATA *);
    } RPGBASE_VTBL;

    typedef struct RpgBase_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RpgBase_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(RPGBASE_DATA *);
    } RPGBASE_CLASS_VTBL;


    /*!         Execution Interface
     This object is supplied externally and defines the execution
     interface exit points that will be called at the appropriate
     times in the RPG cycle.
     */
    typedef struct RpgBase_Exec_interface_s RPGBASE_EXEC_INTERFACE;

    typedef struct RpgBase_Exec_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // All methods must be defined to return bool.
        // Properties:
        // Methods:
        // LevelBreakN methods are called when a break for that
        // level occurs or a higher level.
        bool        (*pLevelBreak1)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelBreak2)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelBreak3)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelBreak4)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelBreak5)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelBreak6)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelBreak7)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelBreak8)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelBreak9)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        // LevelCalcN methods performs the calculations for
        // this level that are ?????
        bool        (*pLevelCalc1)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCalc2)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCalc3)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCalc4)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCalc5)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCalc6)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCalc7)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCalc8)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCalc9)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        // LevelCheckN methods check to see if their level break has
        // occurred and return true if so.
        bool        (*pLevelCheck1)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCheck2)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCheck3)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCheck4)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCheck5)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCheck6)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCheck7)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCheck8)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pLevelCheck9)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        // LevelDataN methods stores the data from the current
        // input record for use in checking future level breaks.
        bool        (*pLevelData1)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pLevelData2)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pLevelData3)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pLevelData4)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pLevelData5)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pLevelData6)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pLevelData7)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pLevelData8)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pLevelData9)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
    } RPGBASE_EXEC_VTBL;

#pragma pack(push, 1)
    struct RpgBase_Exec_interface_s    {
        RPGBASE_EXEC_VTBL   *pVtbl;
    };
#pragma pack(pop)

#define Rpg_ExecVtbl(ptr)   ((RPGBASE_EXEC_INTERFACE *)ptr)->pVtbl




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  RPGBASE_SINGLETON
    RPGBASE_DATA *  RpgBase_Shared (
        void
    );

    void            RpgBase_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to RpgBase object if successful, otherwise OBJ_NIL.
     */
    RPGBASE_DATA *  RpgBase_Alloc (
        void
    );
    
    
    OBJ_ID          RpgBase_Class (
        void
    );
    
    
    RPGBASE_DATA *  RpgBase_New (
        void
    );
    
    
#ifdef  RPGBASE_JSON_SUPPORT
    RPGBASE_DATA *  RpgBase_NewFromJsonString (
        ASTR_DATA       *pString
    );

    RPGBASE_DATA *  RpgBase_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! @property   Data Object
     Certain data must be stored in this object. The object defaults
     to a NodeBT object. This can be easily changed. However, it must
     conform to the ??? Interface.
     */
    OBJ_ID          RpgBase_getData (
        RPGBASE_DATA    *this
    );

    bool            RpgBase_setData (
        RPGBASE_DATA    *this,
        OBJ_ID          pValue
    );


    /*! @property   Execution Object
     Certain data must be stored in this object. The object defaults
     to a NodeBT object. This can be easily changed. However, it must
     conform to the ??? Interface.
     */
RPGBASE_EXEC_INTERFACE *  RpgBase_getExec (
        RPGBASE_DATA    *this
    );

    bool            RpgBase_setExec (
        RPGBASE_DATA    *this,
        RPGBASE_EXEC_INTERFACE
                        *pValue
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         RpgBase_Disable (
        RPGBASE_DATA    *this
    );


    ERESULT         RpgBase_Enable (
        RPGBASE_DATA    *this
    );

   
    RPGBASE_DATA *  RpgBase_Init (
        RPGBASE_DATA    *this
    );


    ERESULT         RpgBase_IsEnabled (
        RPGBASE_DATA    *this
    );
    
 
#ifdef  RPGBASE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = RpgBase_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RpgBase_ToJson (
        RPGBASE_DATA    *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = RpgBase_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RpgBase_ToDebugString (
        RPGBASE_DATA    *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* RPGBASE_H */

