// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          DBFIELD Console Transmit Task (dbField) Header
//****************************************************************
/*
 * Program
 *				Separate dbField (dbField)
 * Purpose
 *				This object provides a standardized way of handling
 *              a separate dbField to run things without complications
 *              of interfering with the main dbField. A dbField may be 
 *              called a dbField on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal dbField. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	07/03/2015 Generated
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


#ifndef         DBFIELD_H
#define         DBFIELD_H



typedef enum dbField_types_e  {
    DBFIELD_TYPE_UNDEFINED=0,
    DBFIELD_TYPE_BLOB,
    DBFIELD_TYPE_BOOL,
    DBFIELD_TYPE_CHAR,
    DBFIELD_TYPE_DATE,
    DBFIELD_TYPE_FILLER,
    DBFIELD_TYPE_INTEGER,
    DBFIELD_TYPE_NUMBER,
    DBFIELD_TYPE_REAL,
    DBFIELD_TYPE_TEXT,
    DBFIELD_TYPE_VARCHAR            // Same as TEXT
} DBFIELD_TYPES;


typedef enum dbField_flags_e  {
    DBFIELD_FLAG_UNIQUE=0x0001,
    DBFIELD_FLAG_NOT_NULL=0x0002,
    DBFIELD_FLAG_AUTO_INC=0x0004,
    DBFIELD_FLAG_PRIM_KEY=0x0008,
    DBFIELD_FLAG_NO_TRAIL=0x0010,   // Remove Trailing White Space
} DBFIELD_FLAGS;


typedef struct dbfield_s {
    const
    char                *pName;
    const
    char                *pDescription;
    const
    char                type;               // see DBFIELD_TYPES
    uint8_t             keySequence;
    //                          0 == not a key column
    //                          1+ == column is part of the key in order
    //                                specified by this number
    int8_t              decimalPlaces;      // for DBFIELD_TYPE_REAL
    int8_t              rsvd;
    int32_t             length;
    //                          For DBFIELD_TYPE_TEXT and DBFIELD_TYPE_VARCHAR,
    //                          a length of 0 just means that it is variable.
    uint32_t            minimumLength;      // For use with TEXT, CHAR or VARCHAR
    int32_t             flags;              // see DBFIELD_FLAGS
    char                *pDefaultValue;     // Value to be placed inside DEFAULT( )
    char                *pCheckExpression;  // Value to be placed inside CHECK( )
    char                *pReferences;       // xxx
} DBFIELD_STRUCT;






#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct dbField_data_s	DBFIELD_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    DBFIELD_DATA *  dbField_Alloc(
        void
    );
    
    
    OBJ_ID          dbField_Class(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /* Disable() terminates the dbField dbField.
     */
    bool            dbField_Disable(
        DBFIELD_DATA		*this
    );


    /* Enable() starts the dbField.
     */
    bool            dbField_Enable(
        DBFIELD_DATA		*this
    );


    bool            dbField_IsEnabled(
        DBFIELD_DATA		*this
    );
    
    
    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    DBFIELD_DATA *     dbField_Init(
        DBFIELD_DATA       *this
    );


    
#ifdef	__cplusplus
}
#endif

#endif	/* DBFIELD_H */

