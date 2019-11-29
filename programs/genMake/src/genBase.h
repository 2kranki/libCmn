// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          GENBASE Console Transmit Task (GenBase) Header
//****************************************************************
/*
 * Program
 *			Separate GenBase (GenBase)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate GenBase to run things without complications
 *          of interfering with the main GenBase. A GenBase may be 
 *          called a GenBase on other O/S's.
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





#include        <genMake.h>
#include        <AStr.h>
#include        <textOut.h>
#include        <NodeRtnA.h>
#include        <NodeTstA.h>


#ifndef         GENBASE_H
#define         GENBASE_H


//#define   GENBASE_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct GenBase_data_s	GENBASE_DATA;            // Inherits from OBJ
    typedef struct GenBase_class_data_s GENBASE_CLASS_DATA;   // Inherits from OBJ

    typedef struct GenBase_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in GenBase_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GENBASE_DATA *);
    } GENBASE_VTBL;

    typedef struct GenBase_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in GenBase_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GENBASE_DATA *);
    } GENBASE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  GENBASE_SINGLETON
    GENBASE_DATA *  GenBase_Shared (
        void
    );

    bool            GenBase_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to GenBase object if successful, otherwise OBJ_NIL.
     */
    GENBASE_DATA *  GenBase_Alloc (
        void
    );
    
    
    OBJ_ID          GenBase_Class (
        void
    );
    
    
    GENBASE_DATA *  GenBase_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: Output is where all the output will be written.
    */
    TEXTOUT_DATA *  GenBase_getOutput (
        GENBASE_DATA    *this
    );

    bool            GenBase_setOutput (
        GENBASE_DATA    *this,
        TEXTOUT_DATA    *pValue
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         GenBase_Disable (
        GENBASE_DATA    *this
    );


    ERESULT         GenBase_Enable (
        GENBASE_DATA	*this
    );

   
    GENBASE_DATA *  GenBase_Init (
        GENBASE_DATA    *this
    );


    ERESULT         GenBase_IsEnabled (
        GENBASE_DATA    *this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = GenBase_ToDebugString(this,4);
     @endcode 
     @param     this    GENBASE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     GenBase_ToDebugString (
        GENBASE_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* GENBASE_H */

