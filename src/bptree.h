// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          B-Plus Tree (bptree) Header
//****************************************************************
/*
 * Program
 *			B-Plus Tree (bptree)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate bptree to run things without complications
 *          of interfering with the main bptree. A bptree may be 
 *          called a bptree on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal bptree. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	03/05/2017 Generated
 */


/*
 * COPYRIGHT  - (C) Copyright 2016  BY Robert White Services, LLC
 *             This computer software is the proprietary information
 *             of Robert White Services, LLC and is subject to a
 *             License Agreement between the user hereof and Robert
 *             White Services, LLC. All concepts, programs, tech-
 *             niques,  object code  and  source code are the Trade
 *             Secrets of Robert White Services, LLC.
 */





#include        <cmn_defs.h>
#include        <AStr.h>


#ifndef         BPTREE_H
#define         BPTREE_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct bptree_data_s	BPTREE_DATA;    // Inherits from OBJ.

    typedef struct bptree_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in bptree_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPTREE_DATA *);
    } BPTREE_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    BPTREE_DATA *   bptree_Alloc(
    );
    
    
    BPTREE_DATA *   bptree_New(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         bptree_getLastError(
        BPTREE_DATA     *this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     bptree_Disable(
        BPTREE_DATA		*this
    );


    ERESULT     bptree_Enable(
        BPTREE_DATA		*this
    );

   
    BPTREE_DATA *   bptree_Init(
        BPTREE_DATA     *this
    );


    ERESULT     bptree_IsEnabled(
        BPTREE_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = bptree_ToDebugString(this,4);
     @endcode:
     @param:    this    BPTREE object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    bptree_ToDebugString(
        BPTREE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BPTREE_H */

