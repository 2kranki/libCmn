// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Visitor Base Class (visitor) Header
//****************************************************************
/*
 * Program
 *			Visitor Base Class (visitor)
 * Purpose
 *			This object provides the base for developing the Visitor
 *          Pattern as described in the GOF book using a double
 *          dispatch mechanism.
 *
 * Remarks
 *	1.      You should implement methods in the inheriting class that
 *          are named "Visit_" concatenated with the class name or name
 *          that should be dispatched.  That method name must also
 *          be added to the QueryInfo method of the inheriting object.
 *          The method must be defined as:
 *              ERESULT    Vist_xyzzy(OBJ_ID this, OBJ_ID pObj);
 *  2.      The Accept() method in the other object will be defined
 *          as follows:
 *              ERESULT    Accept(OBJ_ID this, OBJ_ID visitor);
 *          It must create the method name that will be called in
 *          character format and then call the QueryInfo method
 *          of the visitor to get the function to actually call.
 *
 * History
 *	02/03/2018 Generated
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


#ifndef         VISITOR_H
#define         VISITOR_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct visitor_data_s	VISITOR_DATA;    // Inherits from OBJ.

    typedef struct visitor_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in visitor_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(VISITOR_DATA *);
    } VISITOR_VTBL;



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
     @return    pointer to visitor object if successful, otherwise OBJ_NIL.
     */
    VISITOR_DATA *     visitor_Alloc(
        void
    );
    
    
    OBJ_ID          visitor_Class(
        void
    );
    
    
    VISITOR_DATA *     visitor_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     visitor_getLastError(
        VISITOR_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     visitor_Disable(
        VISITOR_DATA		*this
    );


    ERESULT     visitor_Enable(
        VISITOR_DATA		*this
    );

   
    VISITOR_DATA *   visitor_Init(
        VISITOR_DATA     *this
    );


    ERESULT     visitor_IsEnabled(
        VISITOR_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = visitor_ToDebugString(this,4);
     @endcode 
     @param     this    VISITOR object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    visitor_ToDebugString(
        VISITOR_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* VISITOR_H */

