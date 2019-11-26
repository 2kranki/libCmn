// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          GENMAC Console Transmit Task (GenMac) Header
//****************************************************************
/*
 * Program
 *			Separate GenMac (GenMac)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate GenMac to run things without complications
 *          of interfering with the main GenMac. A GenMac may be 
 *          called a GenMac on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/23/2019 Generated
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


#ifndef         GENMAC_H
#define         GENMAC_H


//#define   GENMAC_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct GenMac_data_s	GENMAC_DATA;            // Inherits from OBJ
    typedef struct GenMac_class_data_s GENMAC_CLASS_DATA;   // Inherits from OBJ

    typedef struct GenMac_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in GenMac_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GENMAC_DATA *);
    } GENMAC_VTBL;

    typedef struct GenMac_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in GenMac_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GENMAC_DATA *);
    } GENMAC_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  GENMAC_SINGLETON
    GENMAC_DATA *     GenMac_Shared (
        void
    );

    bool            GenMac_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to GenMac object if successful, otherwise OBJ_NIL.
     */
    GENMAC_DATA *     GenMac_Alloc (
        void
    );
    
    
    OBJ_ID          GenMac_Class (
        void
    );
    
    
    GENMAC_DATA *     GenMac_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     GenMac_Disable (
        GENMAC_DATA		*this
    );


    ERESULT     GenMac_Enable (
        GENMAC_DATA		*this
    );

   
    GENMAC_DATA *   GenMac_Init (
        GENMAC_DATA     *this
    );


    ERESULT     GenMac_IsEnabled (
        GENMAC_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = GenMac_ToDebugString(this,4);
     @endcode 
     @param     this    GENMAC object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    GenMac_ToDebugString (
        GENMAC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* GENMAC_H */

