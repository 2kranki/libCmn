// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Object Method Pointer (objMethod) Header
//****************************************************************
/*
 * Program
 *			Object Method Pointer (objMethod)
 * Purpose
 *			This object provides a standardized way of passing
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
 *	10/28/2017 Generated
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



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct objMethod_data_s	OBJMETHOD_DATA;    // Inherits from OBJ.

    typedef struct objMethod_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in objMethod_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJMETHOD_DATA *);
    } OBJMETHOD_VTBL;



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
     @return    pointer to objMethod object if successful, otherwise OBJ_NIL.
     */
    OBJMETHOD_DATA * objMethod_Alloc(
        void
    );
    
    
    OBJMETHOD_DATA * objMethod_New(
        void
    );
    
    /*!
     Create a new objMethod object from an object pointer and its method name.
     @param:    pObject Pointer to the object
     @param:    pMethodA UTF-8 method name which must be included in the objects's
                 QueryInfo method.
     @return:   If successful, a new object, otherwise OBJ_NIL.
     */
    OBJMETHOD_DATA * objMethod_NewObjectA(
        OBJ_ID          pObject,
        const
        char            *pMethodA
    );
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ASTR_DATA *     objMethod_getDesc(
        OBJMETHOD_DATA  *this
    );
    
    bool            objMethod_setDesc(
        OBJMETHOD_DATA  *this,
        ASTR_DATA       *pValue
    );
    

    ERESULT         objMethod_getLastError(
        OBJMETHOD_DATA	*this
    );


    void *          objMethod_getMethod(
        OBJMETHOD_DATA  *this
    );
    
    
    ASTR_DATA *     objMethod_getMethodName(
        OBJMETHOD_DATA  *this
    );
    
    
    OBJ_ID          objMethod_getObject(
        OBJMETHOD_DATA  *this
    );
    
    
    ASTR_DATA *     objMethod_getObjectName(
        OBJMETHOD_DATA  *this
    );
    
    
    uint32_t        objMethod_getUser32(
        OBJMETHOD_DATA  *this
    );
    
    bool            objMethod_setUser32(
        OBJMETHOD_DATA  *this,
        uint32_t        value
    );
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    OBJMETHOD_DATA * objMethod_Init(
        OBJMETHOD_DATA  *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = objMethod_ToDebugString(this,4);
     @endcode 
     @param     this    OBJMETHOD object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     objMethod_ToDebugString(
        OBJMETHOD_DATA  *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* OBJMETHOD_H */

