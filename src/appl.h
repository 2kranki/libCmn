// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          APPL Console Transmit Task (appl) Header
//****************************************************************
/*
 * Program
 *			Separate appl (appl)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate appl to run things without complications
 *          of interfering with the main appl. A appl may be 
 *          called a appl on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal appl. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	06/05/2017 Generated
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
#include        <node.h>


#ifndef         APPL_H
#define         APPL_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct appl_data_s	APPL_DATA;    // Inherits from OBJ.

    typedef struct appl_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in appl_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(APPL_DATA *);
    } APPL_VTBL;



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
     @return:   pointer to appl object if successful, otherwise OBJ_NIL.
     */
    APPL_DATA *     appl_Alloc(
    );
    
    
    APPL_DATA *     appl_New(
        uint16_t    cArgs,
        const
        char        *pArgs[]
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            appl_getDebug(
        APPL_DATA     *this
    );
    
    
    bool            appl_getForce(
        APPL_DATA     *this
    );
    
    
    ERESULT         appl_getLastError(
        APPL_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         appl_AddProperty(
        APPL_DATA       *this,
        NODE_DATA       *pData
    );
    
    
    ERESULT         appl_Disable(
        APPL_DATA		*this
    );


    ERESULT         appl_Enable(
        APPL_DATA		*this
    );

   
    APPL_DATA *     appl_Init(
        APPL_DATA       *this,
        uint16_t        cArgs,
        const
        char            **pArgs
    );


    ERESULT         appl_IsEnabled(
        APPL_DATA		*this
    );
    
 
    uint16_t        appl_NumberOfProperties(
        APPL_DATA       *this
    );
    
    
    NODE_DATA *     appl_Property(
        APPL_DATA       *this,
        const
        char            *pName
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = appl_ToDebugString(this,4);
     @endcode:
     @param:    this    APPL object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     appl_ToDebugString(
        APPL_DATA       *this,
        int             indent
    );
    
    
    void            appl_Usage(
        APPL_DATA       *this,
        char            *pMsg,
        ...
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* APPL_H */

