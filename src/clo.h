// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Command Line Options (clo) Header
//****************************************************************
/*
 * Program
 *              Command Line Options (clo)
 * Purpose
 *              These routines process the command line arguments
 *              into Options and Switches.  Both of which can have
 *				String Parameters.  This class is not consistent
 *				with the Unix pseudo standard of using command line
 *				switches.
 *
 *              Switches are those arguments that start with a '-'
 *              or '/' followed by a string.  Options are not prefaced
 *				with any particular characters.  Both should be en-
 *				closed with '"'s if they contain spaces.
 *
 *              String Parameters can be added to a Switch or an Option.
 *              They are denoted by an '=' sign immediately after
 *              the Switch or Option with the parameter following
 *				after the '=' (ie /Debug=1).  There should not be
 *				any spaces on either side of the equal sign, '='.
 *              String parameters should be enclosed in '"'s if they
 *              contain any spaces (ie /Debug="A Horse").
 *
 *              The design of this class is based on the principle that
 *				the command line would be structured in a particular fashion.
 *				Optionally, there would be leading switches that are used
 *				to control the entire execution of the program.  These
 *				would be followed switches applied to options that follow
 *				them.  This grouping of switches and options could then
 *				repeat as often as necessary.  In BNF terms, it would be:
 *
 *				Command_Line -> Program_Switches Switch_Option_Groups
 *								;
 *				Program_Switches -> Switch Program_Switches
 *									|
 *									;
 *				Switch -> ('-' | '/') Name Optional_Parameter
 *						;
 *				Optional_Parameter -> '=' Data
 *									|
 *									;
 *				Switch_Option_Groups -> Switches Options
 *									 ;
 *				Switches -> Switch Switches
 *						  |
 *						  ;
 *				Options -> Name Optional_Parameter Options
 *						 |
 *						 ;
 *
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal clo. A testing unit simply calls
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
#include        <cloOpt.h>
#include        <node.h>


#ifndef         CLO_H
#define         CLO_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct clo_data_s	CLO_DATA;    // Inherits from OBJ.

    typedef struct clo_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in clo_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CLO_DATA *);
    } CLO_VTBL;



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
     @return:   pointer to clo object if successful, otherwise OBJ_NIL.
     */
    CLO_DATA *      clo_Alloc(
        void
    );
    
    
    CLO_DATA *      clo_New(
        uint16_t        cArgs,
        const
        char            **ppArgs
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         clo_getLastError(
        CLO_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         clo_Disable(
        CLO_DATA		*this
    );


    ERESULT         clo_Enable(
        CLO_DATA		*this
    );

   
    CLO_DATA *      clo_Init(
        CLO_DATA        *this,
        uint16_t        cArgs,
        const
        char            **ppArgs
    );


    ERESULT         clo_IsEnabled(
        CLO_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = clo_ToDebugString(this,4);
     @endcode
     @param     this    CLO object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     clo_ToDebugString(
        CLO_DATA        *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* CLO_H */

