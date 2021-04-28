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
#include        <Value.h>


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


    /*!                 Record Interface
     This object is supplied externally and defines the data
     interface for each "record" of information. Primarily,
     this interface provides reading and writing of each "record"
     as well as access to the individual fields within the "record"
     by name. A "record" is defined as a grouping of related fields
     where a field represents one piece of data.
     */
    typedef struct RpgBase_record_interface_s RPGBASE_RECORD_INTERFACE;

    typedef struct RpgBase_record_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RpgBase_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(RPGBASE_DATA *);
        void *          (*pDataGet)(
                                    RPGBASE_RECORD_INTERFACE *this,
                                    const
                                    char        *pName
                        );
        ERESULT         (*pDataUpdate)(
                                    RPGBASE_RECORD_INTERFACE *this,
                                    const
                                    char        *pName,
                                    void        *pData
                        );
        ERESULT         (*pAdd)(RPGBASE_RECORD_INTERFACE *this, void *);
        ERESULT         (*pDelete)(RPGBASE_RECORD_INTERFACE *this);
        ERESULT         (*pUpdate)(RPGBASE_RECORD_INTERFACE *this, void *);
    } RPGBASE_RECORD_VTBL;


    /*!             Execution Interface
     This object is supplied externally and defines the execution
     interface exit points that will be called at the appropriate
     times in the RPG cycle.

     It is based on levels, 1 being the highest. Each level should
     be thought of as a unit and is conditioned on a particular
     field of data.

     Dtl entries are executed with eacch new record. Sum entries
     are for grand totals. Note that Dtl and Sum entries are not
     included in all the groupings.
     */
    typedef struct RpgBase_Exec_interface_s RPGBASE_EXEC_INTERFACE;

    typedef struct RpgBase_Exec_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // All methods must be defined to return bool.
        // Properties:
        // Methods:
        // Break methods are called when a break for that level occurs
        // or a higher level.
        bool        (*pL1Break)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL2Break)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL3Break)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL4Break)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL5Break)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL6Break)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL7Break)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL8Break)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL9Break)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        // LNCalc methods performs the calculations for
        // this level that are ?????
        bool        (*pL1Calc)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL2Calc)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL3Calc)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL4Calc)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL5Calc)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL6Calc)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL7Calc)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL8Calc)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL9Calc)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pDtlCalc)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pSumCalc)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        // LNCheck methods check to see if their level break has
        // occurred and return true if so.  They are not responsible
        // for saving the level data since that occurs later in the
        // RPG cycle.
        bool        (*pL1Check)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL2Check)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL3Check)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL4Check)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL5Check)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL6Check)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL7Check)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL8Check)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL9Check)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        // LNData methods stores the data from the current
        // input record for use in checking future level breaks.
        bool        (*pL1Data)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL2Data)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL3Data)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL4Data)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL5Data)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL6Data)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL7Data)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL8Data)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pL9Data)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pDtlData)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        bool        (*pSumData)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *, void *pRecord);
        // LNZero methods establishes or zeroes the accumulation data
        // which is used at the given level.
        bool        (*pL1Zero)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL2Zero)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL3Zero)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL4Zero)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL5Zero)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL6Zero)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL7Zero)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL8Zero)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL9Zero)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pDtlZero)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pSumZero)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        // LNOut methods performs the output for the particular level.
        bool        (*pL1Out)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL2Out)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL3Out)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL4Out)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL5Out)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL6Out)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL7Out)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL8Out)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pL9Out)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pDtlOut)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
        bool        (*pSumOut)(RPGBASE_EXEC_INTERFACE *, RPGBASE_DATA *);
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

