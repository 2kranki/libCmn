// vi:nu:et:sts=4 ts=4 sw=4 tw=90

//****************************************************************
//          DEVMGR Console Transmit Task (devMgr) Header
//****************************************************************
/*
 * Program
 *			Separate devMgr (devMgr)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate devMgr to run things without complications
 *          of interfering with the main devMgr. A devMgr may be 
 *          called a devMgr on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal devMgr. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	02/24/2016 Generated
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
#include        <devBase.h>


#ifndef         DEVMGR_H
#define         DEVMGR_H    1
#pragma once


#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    //typedef struct devMgr_data_s	DEVMGR_DATA;    // Inherits from OBJ.
    //      DEVMGR_DATA is defined in devBase.h

    typedef struct devMgr_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in devMgr_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DEVMGR_DATA *);
    } DEVMGR_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    DEVMGR_DATA *     devMgr_Alloc(
    );
    
    
    DEVMGR_DATA *     devMgr_New(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    DEVMGR_DATA *   devMgr_Init(
        DEVMGR_DATA     *this
    );


    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *    devMgr_ToDebugString(
        DEVMGR_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DEVMGR_H */

