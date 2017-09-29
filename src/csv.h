// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Comma Separated Variable File (csv) Header
//****************************************************************
/*
 * Program
 *				Comma Separated Variable File (csv)
 * Purpose
 *				This object provides a standardized way of handling
 *              a separate csv to run things without complications
 *              of interfering with the main csv. A csv may be 
 *              called a csv on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	06/03/2015 Generated
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


#ifndef         CSV_H
#define         CSV_H


#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct csv_data_s	CSV_DATA;

    typedef struct csv_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in DateTime_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DATETIME_DATA *);
    } CSV_VTBL;
    
    

    /*		* * *  Record Field Descriptor	* * *
     */
#pragma pack(push, 1)
    struct csv_field_s {
        char        name[11];		/* Field Name (ASCIIZ)				*/
        char        type;			/* Field Type						*/
        /*	dBase III/IV Types				*/
        /*		C == Character Data 		*/
        /*		D == Date Data				*/
        /*			 (YYYYMMDD) (8 Chars)	*/
        /*		L == Logical Data (1 Char)	*/
        /*		M == Memo Data (10 Digits)	*/
        /*		N == Numeric Data			*/
        /*	Other Types 					*/
        /*		I == Integer Data			*/
        uint16_t    length;			/* Field Length by Type				*/
        /*	dBase III/IV Types				*/
        /*		C == Data Length (0 - 254)	*/
        /*		D == Always 8				*/
        /*		L == Always 1				*/
        /*		M == Always 10				*/
        /*		N == Number of Digits plus	*/
        /*			 1 for decimal point if */
        /*			 applicable and plus 1	*/
        /*			 for minus sign (max 15)*/
        /*	Other Types 					*/
        /*		I == Always 6				*/
        uint16_t	dec;			/* Location of Decimal Point for	*/
        /* Type 'N' fields (0-9)			*/
    };
#pragma pack(pop)
    typedef struct csv_field_s CSV_FIELD;
    

    /*		* * *  Error Number Equates  * * *
     */
#define CSV_ERROR_BADCB 	1		/* Bad Control Block Passed */
#define CSV_ERROR_IC		ERESULT_USER_START-1	/* Illegal Character */
#define CSV_ERROR_IL		ERESULT_USER_START		/* Illegal Locical Value */
#define CSV_ERROR_IN		ERESULT_USER_START		/* Illegal Numeric Character */
#define CSV_ERROR_IR		ERESULT_USER_START		/* Illegal Record Number */
#define CSV_ERROR_NOMEM 	ERESULT_USER_START		/* No Heap Memory Available */
#define CSV_ERROR_OPEN		ERESULT_USER_START		/* File Open Error */
#define CSV_ERROR_PACK		ERESULT_USER_START		/* Illegal Pack Factor */
#define CSV_ERROR_SEEK		ERESULT_USER_START		/* Seek Error */
#define CSV_ERROR_SL		ERESULT_USER_START		/* Char String is too long */
#define CSV_ERROR_READ		ERESULT_USER_START		/* Read Error */
#define CSV_ERROR_WRITE		ERESULT_USER_START		/* Write Error */
    

    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the csv including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    CSV_DATA *      csv_Alloc(
        uint16_t        stackSize           // Stack Size in Words
    );
    
    
    OBJ_ID          csv_Class(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /* If Quit is set, the csv ends upon
     * completion of its next record. Set-
     * ting this does not end the csv un-
     * less a record is received or we timed
     * out.
     */
    bool            csv_getQuit(
        CSV_DATA        *this
    );

    bool            csv_setQuit(
        CSV_DATA        *this,
        bool            flag
    );


    /* When Skip is set to true, all messages are skpped over
     * and purged from the queue.
     */
    bool            csv_getSkip(
        CSV_DATA        *this
    );

    bool            csv_setSkip(
        CSV_DATA        *this,
        bool            flag
    );


    void *          csv_getTask(
        CSV_DATA        *this
    );


    /* TaskBody() is the primary function run by the separate csv.
     * It is defaulted to running a function that waits for data
     * from the queue and processes it. By overriding this, the
     * csv will perform this routine instead.
     */
    bool			csv_setTaskBody(
        CSV_DATA        *this,
        void            (*function)(void *),
        void            *pData                  // Data passed as void *
    );
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /* Disable() terminates the csv csv.
     */
    bool            csv_Disable(
        CSV_DATA		*this
    );


    /* Enable() starts the csv.
     */
    bool            csv_Enable(
        CSV_DATA		*this
    );


    bool            csv_IsEmpty(
        CSV_DATA     *this
    );


    bool            csv_IsEnabled(
        CSV_DATA		*this
    );
    
    
    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    CSV_DATA *     csv_Init(
        CSV_DATA       *this
    );


    
#ifdef	__cplusplus
}
#endif

#endif	/* CSV_H */

