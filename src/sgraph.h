// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Simple Graphe (sgraph) Header
//****************************************************************
/*
 * Program
 *			Simple Graph (sgraph)
 * Purpose
 *			This object provides a simple generic graph that can
 *          be used as needed.
 *
 *          The idea for this object came from "Modern Compiler
 *          Implementation in C", Andrew Appel, Cambridge, 1998,
 *          Page 230.  Internally, we use an objArray and one or
 *          two bitMatrix(s) to base the graph on.
 *
 * Remarks
 *	1.      New Nodes may be added to the graph at any time.  However,
 *          nodes may not be deleted.
 *
 * History
 *	08/12/2018 Generated
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


#ifndef         SGRAPH_H
#define         SGRAPH_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct sgraph_data_s	SGRAPH_DATA;    // Inherits from OBJ.

    typedef struct sgraph_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in sgraph_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SGRAPH_DATA *);
    } SGRAPH_VTBL;



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
     @return    pointer to sgraph object if successful, otherwise OBJ_NIL.
     */
    SGRAPH_DATA *     sgraph_Alloc(
        uint16_t    stackSize           // Stack Size in Words
    );
    
    
    OBJ_ID          sgraph_Class(
        void
    );
    
    
    SGRAPH_DATA *     sgraph_New(
        uint16_t    stackSize           // Stack Size in Words
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     sgraph_Disable(
        SGRAPH_DATA		*this
    );


    ERESULT     sgraph_Enable(
        SGRAPH_DATA		*this
    );

   
    SGRAPH_DATA *   sgraph_Init(
        SGRAPH_DATA     *this
    );


    ERESULT     sgraph_IsEnabled(
        SGRAPH_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = sgraph_ToDebugString(this,4);
     @endcode 
     @param     this    SGRAPH object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    sgraph_ToDebugString(
        SGRAPH_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SGRAPH_H */

