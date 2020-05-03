// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          PLIST Console Transmit Task (plist) Header
//****************************************************************
/*
 * Program
 *			Separate plist (plist)
 * Purpose
 *			This object provides a standardized way of parsing
 *          plists which were started in NextStep and continued
 *          on in MacOSX. They are similar to JSON files, but the
 *          formats are different.
 *
 *          Actually, there are multiple formats for plists:
 *          --  old style (which Xcode still uses)
 *          --  xml style
 *          --  binary style
 *          The plutil program supports those styles for input.
 *          For output, it only supports XML, Binary and JSON
 *          formats. Try "plutil --help" for further information.
 *
 * Remarks
 *	1.      N/A
 *
 * History
 *	10/18/2015 Generated
 */


 /***
   "http://www.apple.com/DTDs/PropertyList-1.0.dtd"
  
  plist
        = plistObject
        ;
  
  plistObject
        = (array | data | date | dict | real | integer | string | true | false )
        ;

  array 
        = '(' plistObject {',' plistObject} ')' ';'
        ;
  
  dict
        = '{' key '=' plistObject {',' key '=' plistObject} '}' ';'
        ;
  
  <!--- Primitive types -->
  <!ELEMENT string (#PCDATA)>
  <!ELEMENT data (#PCDATA)> <!-- Contents interpreted as Base-64 encoded -->
  
  date  
        = YYYY '-' MM '-' DD 'T' HH ':' MM ':' SS 'Z'. //a subset of ISO 8601
  
  false
        = 'false'
        ;
  
  true
        = 'true'
        ;
  
  real
        = ("+" | "-")? d+ ("."d*)? ("E" ("+" | "-") d+)? // floating point number
        ;
  
  integer 
        = ("+" | "-")? d+ // a (possibly signed) integer in base 10
        ;
 
 ***/



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

    typedef struct plist_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fatFCB_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CB_DATA *);
    } PLIST_VTBL;
    
    



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
        void
    );
    
    
    PLIST_DATA *     plist_New(
        void
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

