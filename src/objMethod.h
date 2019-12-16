// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Object Method Pointer (ObjMethod) Header
//****************************************************************
/*
 * Program
 *			Object Method Pointer (ObjMethod)
 * Purpose
 *          This object provides a standardized way of passing
 *          an object and method which can be written to a JSON
 *          string and relinked later.
 *
 *          The method must be defined within the QueryInfo method
 *          of the object.  The object's info must be registered
 *          with objRegistry (to be done).
 *
 * Remarks
 *	1.      None
 *
 * History
 *  10/28/2017 Generated
 *	12/15/2019 Reenerated
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


#ifndef         OBJMETHOD_H
#define         OBJMETHOD_H


//#define   OBJMETHOD_JSON_SUPPORT 1
//#define   OBJMETHOD_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ObjMethod_data_s	OBJMETHOD_DATA;            // Inherits from OBJ
    typedef struct ObjMethod_class_data_s OBJMETHOD_CLASS_DATA;   // Inherits from OBJ

    typedef struct ObjMethod_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjMethod_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJMETHOD_DATA *);
    } OBJMETHOD_VTBL;

    typedef struct ObjMethod_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjMethod_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJMETHOD_DATA *);
    } OBJMETHOD_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  OBJMETHOD_SINGLETON
    OBJMETHOD_DATA * ObjMethod_Shared (
        void
    );

    bool            ObjMethod_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ObjMethod object if successful, otherwise OBJ_NIL.
     */
    OBJMETHOD_DATA * ObjMethod_Alloc (
        void
    );
    
    
    OBJ_ID          ObjMethod_Class (
        void
    );
    
    
    OBJMETHOD_DATA * ObjMethod_New (
        void
    );
    
    
    /*!
     Create a new objMethod object from an object pointer and its method name.
     @param     pObject Pointer to the object
     @param     pMethodA UTF-8 method name which must be included in the objects's
                 QueryInfo method.
     @return    If successful, a new object, otherwise OBJ_NIL.
     */
    OBJMETHOD_DATA * ObjMethod_NewObjectA(
        OBJ_ID          pObject,
        const
        char            *pMethodA
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ASTR_DATA *     ObjMethod_getDesc(
        OBJMETHOD_DATA  *this
    );

    bool            ObjMethod_setDesc(
        OBJMETHOD_DATA  *this,
        ASTR_DATA       *pValue
    );


    void *          ObjMethod_getMethod(
        OBJMETHOD_DATA  *this
    );


    ASTR_DATA *     ObjMethod_getMethodName(
        OBJMETHOD_DATA  *this
    );


    OBJ_ID          ObjMethod_getObject(
        OBJMETHOD_DATA  *this
    );


    ASTR_DATA *     ObjMethod_getObjectName(
        OBJMETHOD_DATA  *this
    );


    uint32_t        ObjMethod_getUser32(
        OBJMETHOD_DATA  *this
    );

    bool            ObjMethod_setUser32(
        OBJMETHOD_DATA  *this,
        uint32_t        value
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    OBJMETHOD_DATA * ObjMethod_Init (
        OBJMETHOD_DATA  *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjMethod_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    ObjMethod_ToDebugString (
        OBJMETHOD_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJMETHOD_H */

