// vi: nu:noai:ts=4:sw=4

//****************************************************************
//					C Object (obj) Header				
//****************************************************************

/*
 * Program
 *				C Object (obj) Header
 * Purpose
 *				These subroutines provide a general purpose set of
 *				routines to create a retain counted C object. It
 *              may also be the initial object for single in-
 *              heritance since C supports this.
 * Remarks
 *	1.			Each Dealloc must call its super's Dealloc for the
 *              Dealloc chain to operate properly. There is no way
 *              currently to calculate the Dealloc. So, it must be
 *              hard coded. The Top-most Dealloc should be set in
 *              this object as the Dealloc method which starts the
 *              Dealloc chain.
 *  2.          The class objects are defined as const. So, you can
 *              not have class variables without removing the const.
 *  3.          The class objects are not set up to inherit from
 *              their base classes. They only inherit from OBJ
 *              currently. There is only one slot for a Vtbl ptr
 *              currently.
 * History
 *	02/11/2015	Created from scratch.
 *  09/14/2015  Changed obj_Dealloc to not free objects not alloc'd
 *              by the obj_Alloc.
 * References
 *		"Data Structures using C", Aaron M. Tenenbaum et al,
 *			Prentice-Hall, 1990
 *		"Programs and Data Structures in C", Leendert Ammeraal,
 *			John Wiley & Sons, 1987
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
#include        <uuid/uuid.h>

#ifndef         OBJ_H
#define         OBJ_H	1


#ifdef	__cplusplus
extern	"C" {
#endif
    
#ifndef ERESULT_DEFN
    typedef int32_t ERESULT;
#define ERESULT_DEFN 1
#endif
    
    
/****************************************************************
* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
****************************************************************/


    typedef void *  OBJ_PTR;
    typedef void *  OBJ_ID;
#define             OBJ_NIL ((OBJ_ID)0)
    typedef struct obj_iunknown_s  OBJ_IUNKNOWN;
    typedef struct obj_info_s  OBJ_INFO;
    typedef struct obj_prop_s  OBJ_PROP;            // Property
    typedef void (*DEALLOC_METHOD)(void *);
    
    typedef struct obj_data_s   OBJ_DATA;   /* One Interface */

    typedef ERESULT     (*P_OBJ_ASSIGN)(OBJ_ID, OBJ_ID);
    typedef int         (*P_OBJ_COMPARE)(OBJ_ID, OBJ_ID);
    // @return    0 if this == other
    //           <0 if this < other
    //           >0 if this > other
    typedef ERESULT     (*P_OBJ_EXEC)(OBJ_ID);
    typedef OBJ_ID      (*P_OBJ_COPY)(OBJ_ID);
    typedef OBJ_ID      (*P_OBJ_DEEPCOPY)(OBJ_ID);
    typedef bool        (*P_OBJ_DISABLE)(OBJ_ID);
    typedef bool        (*P_OBJ_ENABLE)(OBJ_ID);
    typedef uint32_t    (*P_OBJ_HASH)(OBJ_ID);
    typedef OBJ_ID      (*P_OBJ_PTR)(OBJ_ID);
    typedef OBJ_ID      (*P_OBJ_TOSTRING)(OBJ_ID, int);
    typedef void *      (*P_OBJ_QUERYINFO)(OBJ_ID, uint32_t, void *);


    
#pragma pack(push, 1)
    struct obj_data_s {
        const
        OBJ_IUNKNOWN    *pVtbl;
        uint16_t        cbSize;         /* Total Control Block Size */
        uint16_t        cbFlags;        /* Control Flags */
#define OBJ_FLAG_ALLOC      0               /* Object was allocated in obj_Alloc(). */
#define OBJ_FLAG_INIT       1               /* Object is initialized. */
#define OBJ_FLAG_ENABLED    2               /* Object is enabled. */
#define OBJ_FLAG_TRACE      3               /* Object tracing */
#define OBJ_FLAG_RO         4               /* Object is Read-Only (ie immutable). */
#define OBJ_FLAG_COM        5               /* Object is COM compatible. */
// Reserved 5-7
#define OBJ_FLAG_USER1      8               /* First User Useable flag */
#define OBJ_FLAG_USER2      9
#define OBJ_FLAG_USER3      10
#define OBJ_FLAG_USER4      11
#define OBJ_FLAG_USER5      12
#define OBJ_FLAG_USER6      13
#define OBJ_FLAG_USER7      14
#define OBJ_FLAG_USER8      15              /* Last User Useable flag */
        uint32_t		cbRetainCount;
        union {
            uint32_t        cbMisc;
            struct {
                uint16_t        cbMisc1;
                uint16_t        cbMisc2;
            };
        };
    };
#pragma pack(pop)

    extern
    const
    OBJ_DATA        obj_ClassObj;
    

#pragma pack(push, 1)
    struct obj_info_s {
        const
        char            *pClassName;
        const
        char            *pClassDesc;        // Class Description
        OBJ_DATA        *pClassObject;
        OBJ_DATA        *pClassSuperObject;
        OBJ_IUNKNOWN    *pDefaultVtbls;     // Default Object VTBL
        uint32_t        defaultObjectSize;  // Default Object Size for objects
        //                                  // created (non-class)
    };
#pragma pack(pop)
    
    
    // Object Property Definition
#pragma pack(push, 1)
    struct obj_prop_s {
        const
        char            *pName;             // Name
        const
        char            *pInternal;         // Internal Name (if object, use p${titled.pName})
        const
        char            *pExternal;         // External Name (used for JSON/HJSON, etc)
        const
        char            *pDesc;             // Description
        const
        char            *pType;             // Type (if object, use ${object.upper}_DATA)
        const
        char            *pInit;             // Initialization Code
        const
        char            *pVis;              // Visibility - public,private,read-only,ro,none
        const
        char            *pBase;             // Base Structure/Pointer
        uint32_t        offset;             // Offset into Base
        // If property is part of a combined field, we can generate a mask and shift
        // amount to add, extract or delete the property from the combined field.
        uint32_t        sizeInBits;         // Size of property in bits if integer
        uint32_t        shiftAmt;           // Amount to shift right to put in lowest bits
        uint8_t         fObject;            // true == object
        uint8_t         filler8[3];
    };
#pragma pack(pop)
    
    

//#pragma pack(push, 1)
    struct obj_iunknown_s {
        const
        OBJ_INFO    *pInfo;                 // (Optional for Now)
        bool        (*pIsKindOf)(uint16_t);
        OBJ_ID      (*pRetain)(OBJ_ID);
        OBJ_ID      (*pRelease)(OBJ_ID);
        void        (*pDealloc)(OBJ_ID);
        // Return the Class Object for this object. If the object is already
        // a Class Object, then it simply returns itself. The Info address
        // then allows you to find Super objects if needed.
        OBJ_ID      (*pClassObject)(void);
        uint16_t    (*pWhoAmI)(void);
        // Everything before this is required and does not need to be
        // tested to see if it exists.  Everything after this must be
        // tested to see if it exists, because it may not be implemented
        // (ie NULL).
        // ------- Beginning of Methods likely to be in all objects -------
        // Query an object for specific data including object size,
        // method name(s) in character format, etc.  See obj_QueryInfoType_e
        // for more information.
        void *      (*pQueryInfo)(OBJ_ID, uint32_t, void *);
        OBJ_ID      (*pToDebugString)(OBJ_ID, int);
        // ------- End of Methods likely to be in all objects -------
        bool        (*pEnable)(OBJ_ID);
        bool        (*pDisable)(OBJ_ID);
        // Assigns data within 1st object to 2nd object.
        ERESULT     (*pAssign)(OBJ_ID, OBJ_ID);  // P_OBJ_ASSIGN
        // Compares 1st object to 2nd object.
        // Returns:
        //          ERESULT_SUCCESS_LESS_THAN        1st <  2nd
        //          ERESULT_SUCCESS_EQUAL            1st == 2nd
        //          ERESULT_SUCCESS_GREATER_THAN     1st >  2nd
        int         (*pCompare)(OBJ_ID, OBJ_ID); // P_OBJ_COMPARE
        // Creates a new copy of the object. If the object is
        // immmutable (ie can not be changed) then it just returns
        // a retained self. Objects within this object will simply
        // be retained.
        OBJ_ID      (*pCopy)(OBJ_ID);           // P_OBJ_COPY
        // Creates a new copy of the object. If the object is
        // immmutable (ie can not be changed) then it just returns
        // a retained self. Objects within this object will be
        // recreated in a new object unless they are read-only.
        OBJ_ID      (*pDeepCopy)(OBJ_ID);       // P_OBJ_DEEPCOPY
        // Creates hash of this object.
        uint32_t    (*pHash)(OBJ_ID);           // P_OBJ_HASH
    };
//#pragma pack(pop)
    
    
//#pragma pack(push, 1)
struct obj_iunknown_com_s {
    // The first three methods are consistant with Microsoft's
    // COM iUnknown.
    ERESULT     (*pQueryInterface)(const uuid_t *, void **);
    uint32_t    (*pAddRef)(OBJ_ID);
    uint32_t    (*pRelease)(OBJ_ID);
    const
    OBJ_INFO    *pInfo;                 // (Optional for Now)
    bool        (*pIsKindOf)(uint16_t);
    void        (*pDealloc)(OBJ_ID);
    // Return the Class Object for this object. If the object is already
    // a Class Object, then it simply returns itself. The Info address
    // then allows you to find Super objects if needed.
    OBJ_ID      (*pClassObject)(void);
    uint16_t    (*pWhoAmI)(void);
    // Everything before this is required and does not need to be
    // tested to see if it exists.  Everything after this must be
    // tested to see if it exists, because it may not be implemented
    // (ie NULL).
    // ------- Beginning of Methods likely to be in all objects -------
    // Query an object for specific data including object size,
    // method name(s) in character format, etc.  See obj_QueryInfoType_e
    // for more information.
    void *      (*pQueryInfo)(OBJ_ID, uint32_t, void *);
    OBJ_ID      (*pToDebugString)(OBJ_ID, int);
    // ------- End of Methods likely to be in all objects -------
    bool        (*pEnable)(OBJ_ID);
    bool        (*pDisable)(OBJ_ID);
    // Assigns data within 1st object to 2nd object.
    ERESULT     (*pAssign)(OBJ_ID, OBJ_ID);  // P_OBJ_ASSIGN
    // Compares 1st object to 2nd object.
    // Returns:
    //          ERESULT_SUCCESS_LESS_THAN        1st <  2nd
    //          ERESULT_SUCCESS_EQUAL            1st == 2nd
    //          ERESULT_SUCCESS_GREATER_THAN     1st >  2nd
    int         (*pCompare)(OBJ_ID, OBJ_ID); // P_OBJ_COMPARE
    // Creates a new copy of the object. If the object is
    // immmutable (ie can not be changed) then it just returns
    // a retained self. Objects within this object will simply
    // be retained.
    OBJ_ID      (*pCopy)(OBJ_ID);           // P_OBJ_COPY
    // Creates a new copy of the object. If the object is
    // immmutable (ie can not be changed) then it just returns
    // a retained self. Objects within this object will be
    // recreated in a new object unless they are read-only.
    OBJ_ID      (*pDeepCopy)(OBJ_ID);       // P_OBJ_DEEPCOPY
    // Creates hash of this object.
    uint32_t    (*pHash)(OBJ_ID);           // P_OBJ_HASH
};
//#pragma pack(pop)


    typedef enum obj_QueryInfoType_e {
        OBJ_QUERYINFO_TYPE_UNKNOWN=0,
        OBJ_QUERYINFO_TYPE_OBJECT_SIZE,     // Return size of object
        OBJ_QUERYINFO_TYPE_CLASS_OBJECT,    // Return class object
        OBJ_QUERYINFO_TYPE_DATA_PTR,        // If the given string matches a data name,
        //                                  // return a pointer to the data
        OBJ_QUERYINFO_TYPE_INFO,            // Return class info structure
        OBJ_QUERYINFO_TYPE_METHOD,          // Search for a Method by using the string
        //                                  // which is the method name without object prefix
        OBJ_QUERYINFO_TYPE_PTR,             // Search for a Method by using its address and
        //                                  // returning a string which represents the method
    } OBJ_QUERYINFO_TYPE;




#define OBJ_INIT_SHARED(this, cbSize)\
    if (!(obj_getFlags(this) & OBJ_FLAG_INIT)) {        \
        memset(this, 0, cbSize);                        \
        obj_setVtbl(this, obj_StaticVtblShared());      \
        obj_setSize(this, cbSize);                      \
        obj_setRetainCount(this, -1);                   \
        obj_setFlags(this, OBJ_FLAG_INIT);              \
    }



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    
    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    // Note:
    //  --  In the following routines, we use OBJ_ID instead of
    //      OBJ_DATA *this to simplify having to cast on every call.
    //      OBJ_ID is defined as "void *" which does not require any
    //      casting.
    
    /* Alloc() allocates the memory for the object, zeroes it and
     * sets up initial parameters for it.
     */
    OBJ_ID          obj_Alloc(
        uint16_t        size
    );
    
   
    OBJ_ID          obj_BaseClass(
        void
    );
    

    P_OBJ_ASSIGN    obj_getAssign(
        OBJ_ID          objId
    );


    P_OBJ_COMPARE   obj_getCompare(
        OBJ_ID          objId
    );


    P_OBJ_COPY      obj_getCopy(
        OBJ_ID          objId
    );


    /*! Get the class object for any object.
     */
    OBJ_ID          obj_getClass(
        OBJ_ID          objId
    );


    OBJ_ID          obj_ClassSuper(
        OBJ_ID          objId
    );
    

    bool            obj_IsKindOf(
        OBJ_ID          objId,
        uint16_t        type
    );

    
    bool            obj_ClassEnable(
        OBJ_ID          objId
    );
    
    
    bool            obj_ClassDisable(
        OBJ_ID          objId
    );
    

    const
    OBJ_IUNKNOWN *  obj_StaticVtbl(
        void
    );


    const
    OBJ_IUNKNOWN *  obj_StaticVtblShared(
        void
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------
    
    bool            obj_IsEnabled(
        OBJ_ID          objId
    );

    
    uint16_t        obj_getFlags(
        OBJ_ID          objId
    );

    bool			obj_setFlags(
        OBJ_ID          objId,
        uint16_t        value
    );
    

    const
    OBJ_INFO *      obj_getInfo(
        OBJ_ID          objId
    );
    
   
    uint32_t        obj_getMisc(
        OBJ_ID          objId
    );
    
    bool			obj_setMisc(
        OBJ_ID          objId,
        uint32_t        value
    );
    
    
    uint16_t        obj_getMisc1(
        OBJ_ID          objId
    );
    
    bool			obj_setMisc1(
        OBJ_ID          objId,
        uint16_t        value
    );
    
    
    uint16_t        obj_getMisc2(
        OBJ_ID          objId
    );
    
    bool			obj_setMisc2(
        OBJ_ID          objId,
        uint16_t        value
    );
    
    
    bool            obj_IsReadOnly(
        OBJ_ID          objId
    );
    
    
    uint16_t        obj_getRetainCount(
        OBJ_ID          objId
    );
    
    bool			obj_setRetainCount(
        OBJ_ID          objId,
        uint16_t        value
    );
    
    
    uint16_t        obj_getSize(
        OBJ_ID          objId
    );
    
    bool			obj_setSize(
        OBJ_ID          objId,
        uint16_t        value
    );
    
    
    OBJ_ID          obj_getSuper(
        OBJ_ID          objId
    );
    
    
    uint16_t        obj_getType(
        OBJ_ID          objId
    );
    
    
    OBJ_IUNKNOWN *	obj_getVtbl(
        OBJ_ID          objId
    );
    
    
    bool			obj_setVtbl(
        OBJ_ID          objId,
        const
        OBJ_IUNKNOWN    *pValue
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
#ifdef OBJ_COM_SUPPORT
    uint32_t        obj_AddRef(
        OBJ_ID          objId
    );
#endif


    void            obj_Dealloc(
        OBJ_ID          objId
    );
    
    
    /* OBJ_Disable() frees the allocated arrays.
     * Returns:
     *		TRUE = Successful completion otherwise FALSE
     */
    bool            obj_Disable(
        OBJ_ID          objId
    );
    
    
    /* obj_Enable() is used to activate an object if needed.
     * This method simply sets the 'enabled' flag.
     * Returns:
     *		TRUE = Successful Completion, otherwise FALSE
     */
    bool            obj_Enable(
        OBJ_ID          objId
    );


    /* obj_IsA() compares the given object identifier against
     * WhoAmI() returns.
     * Returns:
     *		TRUE == Match, otherwise FALSE
     */
    bool            obj_IsA(
        OBJ_ID          objId,
        uint16_t        type
    );
    
    
    bool            obj_IsFlag(
        OBJ_ID          objId,
        uint16_t        flag        // Index (not a mask)
    //                              //  0..3 are for OBJ use
    //                              //  4..15 are for user's use
    //                              //  WARNING: Be careful that user flag use
    //                              //          does not overlap when inheriting
    //                              //          from another object
    );
    
    
    bool            obj_Flag(
        OBJ_ID          objId,
        uint16_t        flag        // Index (not a mask)
    //                              //  0..3 are for OBJ use
    //                              //  4..15 are for user's use
    //                              //  WARNING: Be careful that user flag use
    //                              //          does not overlap when inheriting
    //                              //          from another object
    );
    
    
    bool            obj_FlagOff(
        OBJ_ID          objId,
        uint16_t        flag        // Index (not a mask)
    //                              //  0..3 are for OBJ use
    //                              //  4..15 are for user's use
    //                              //  WARNING: Be careful that user flag use
    //                              //          does not overlap when inheriting
    //                              //          from another object
    );
    
    
    bool            obj_FlagOn(
        OBJ_ID          objId,
        uint16_t        flag        // Index (not a mask)
    //                              //  0..3 are for OBJ use
    //                              //  4..15 are for user's use
    //                              //  WARNING: Be careful that user flag use
    //                              //          does not overlap when inheriting
    //                              //          from another object
    );
    
    
    bool            obj_FlagSet(
        OBJ_ID          objId,
        uint16_t        flag,       // Index (not a mask)
    //                              //  0..3 are for OBJ use
    //                              //  4..15 are for user's use
    //                              //  WARNING: Be careful that user flag use
    //                              //          does not overlap when inheriting
    //                              //          from another object
        bool            fValue
    );


    /* obj_IsKindOf() compares the given object identifier against
     * the objects in IsKindOf() which should represent the object
     * inheritance chain.
     * Returns:
     */
    bool            obj_IsKindOf(
        OBJ_ID          objId,
        uint16_t        type
    );
    
    
    /* obj_Init() initializes this object. If we find upon
     * entry that if the area passed has an identifier of
     * OBJ_ID_OBJ and the size is the same, then we will
     * assume that the area was gotten with obj_Alloc();
     */
    OBJ_ID          obj_Init(
        OBJ_ID          objId,
        uint16_t        size,
        uint16_t        objectIdentifier
    );


    void *          obj_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
#ifdef OBJ_COM_SUPPORT
    uint32_t        obj_Release(
        OBJ_ID          objId
    );

    uint32_t        obj_ReleaseNull(
        OBJ_ID          objId
    );
    
    uint32_t        obj_ReleaseStandard(
        OBJ_ID          objId
    );
#else
    OBJ_ID          obj_Release(
        OBJ_ID          objId
    );

    OBJ_ID          obj_ReleaseNull(
        OBJ_ID          objId
    );

    OBJ_ID          obj_ReleaseStandard(
        OBJ_ID          objId
    );
#endif
    
    
    OBJ_ID          obj_Retain(
        OBJ_ID          objId
    );
    
    OBJ_ID          obj_RetainNull(
        OBJ_ID          objId
    );
    
    OBJ_ID          obj_RetainStandard(
        OBJ_ID          objId
    );
    
    
    OBJ_ID          obj_ToDebugString(
        OBJ_ID          objId,
        int             indent
    );

    
    bool            obj_Trace(
        OBJ_ID          objId
    );
    
    
    bool            obj_TraceSet(
        OBJ_ID          objId,
        bool            fValue
    );
    
    
    
    
#ifdef	__cplusplus
};
#endif




#endif
