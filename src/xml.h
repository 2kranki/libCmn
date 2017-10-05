// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          XML Console Transmit Task (xml) Header
//****************************************************************
/*
 * Program
 *			Separate xml (xml)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate xml to run things without complications
 *          of interfering with the main xml. A xml may be 
 *          called a xml on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal xml. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	10/18/2015 Generated
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


#ifndef         XML_H
#define         XML_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct xml_data_s	XML_DATA;

    typedef struct xml_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fatFCB_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(XML_DATA *);
    } XML_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    XML_DATA *     xml_Alloc(
        void
    );
    
    
    XML_DATA *     xml_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /* Disable() terminates the xml xml.
     */
    bool        xml_Disable(
        XML_DATA		*this
    );


    /* Enable() starts the xml.
     */
    bool        xml_Enable(
        XML_DATA		*this
    );


    bool        xml_IsEnabled(
        XML_DATA		*this
    );
    
    
    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    XML_DATA *   xml_Init(
        XML_DATA     *this
    );


    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     xml_ToDebugString(
        XML_DATA        *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* XML_H */

