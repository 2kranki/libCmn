// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          PLIST Console Transmit Task (plist) Header
//****************************************************************
/*
 * Program
 *			Separate plist (plist)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate plist to run things without complications
 *          of interfering with the main plist. A plist may be 
 *          called a plist on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal plist. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	10/18/2015 Generated
 */


 /***
   "http://www.apple.com/DTDs/PropertyList-1.0.dtd"
  
  <!ENTITY % plistObject "(array | data | date | dict | real | integer | string | true | false )" >
  <!ELEMENT plist %plistObject;>
  <!ATTLIST plist version CDATA "1.0" >
  
  <!-- Collections -->
  <!ELEMENT array (%plistObject;)*>
  <!ELEMENT dict (key, %plistObject;)*>
  <!ELEMENT key (#PCDATA)>
  
  <!--- Primitive types -->
  <!ELEMENT string (#PCDATA)>
  <!ELEMENT data (#PCDATA)> <!-- Contents interpreted as Base-64 encoded -->
  <!ELEMENT date (#PCDATA)> <!-- Contents should conform to a subset of ISO 8601 
                                (in particular,
                                    YYYY '-' MM '-' DD 'T' HH ':' MM ':' SS 'Z'.
                                Smaller units may be omitted with a loss of precision) -->
  
  <!-- Numerical primitives -->
  <!ELEMENT true EMPTY>  <!-- Boolean constant true -->
  <!ELEMENT false EMPTY> <!-- Boolean constant false -->
  <!ELEMENT real (#PCDATA)> <!-- Contents should represent a floating point number 
                                    matching ("+" | "-")? d+ ("."d*)? ("E" ("+" | "-") d+)? 
                                    where d is a digit 0-9.  -->
  <!ELEMENT integer (#PCDATA)> <!-- Contents should represent a (possibly signed) integer 
                                    number in base 10 -->  ***/



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


#ifndef         PLIST_H
#define         PLIST_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct plist_data_s	PLIST_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the plist including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    PLIST_DATA *     plist_Alloc(
    );
    
    
    PLIST_DATA *     plist_New(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /* Disable() terminates the plist plist.
     */
    bool            plist_Disable(
        PLIST_DATA		*this
    );


    /* Enable() starts the plist.
     */
    bool            plist_Enable(
        PLIST_DATA		*this
    );


    bool            plist_IsEnabled(
        PLIST_DATA      *this
    );
    
    
    PLIST_DATA *    plist_Init(
        PLIST_DATA      *this
    );


    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     plist_ToDebugString(
        PLIST_DATA      *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* PLIST_H */

