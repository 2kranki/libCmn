// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          A Lisp-like machine (wisp) Header
//****************************************************************
/*
 * Program
 *			A Lisp-like machine (wisp)
 * Purpose
 *			This object provides most of what is needed to have
 *          functional Lisp system.  It is based on the description
 *          of Wisp in "Implementing Software for Non-Numeric
 *          Applications" by William M. Waite, Prentice-Hall,
 *          1973.
 *
 *          I created this so that I could experiment with some
 *          of the things mentioned in the book.  Right now,
 *          this will not be a full implementation.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	08/04/2018 Generated
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
#include        <u32Array.h>


#ifndef         WISP_H
#define         WISP_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct wisp_data_s	WISP_DATA;    // Inherits from OBJ.

    typedef struct wisp_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in wisp_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(WISP_DATA *);
    } WISP_VTBL;



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
     @return    pointer to wisp object if successful, otherwise OBJ_NIL.
     */
    WISP_DATA *     wisp_Alloc(
        void
    );
    
    
    OBJ_ID          wisp_Class(
        void
    );
    
    
    WISP_DATA *     wisp_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        wisp_getSize(
        WISP_DATA       *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Construct a memory word from the two expression and append it to
     the end of memory optionally returning the index to the word.
     @param     this    object pointer
     @param     e1      expression 1 which becomes the CAR.
     @param     e2      expression 2 which becomes the CDR.
     @param     pIndex  optional returned index to memory word
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         wisp_Cons(
        WISP_DATA       *this,
        uint32_t        e1,
        uint32_t        e2,
        uint32_t        *pIndex             // [out] Optional Word Index
    );

   
    bool            wisp_GetAtom(
        WISP_DATA       *this,
        uint32_t        index
    );
    
    
    bool            wisp_GetBP(
        WISP_DATA       *this,
        uint32_t        index
    );
    
    
    uint32_t        wisp_GetCAR(
        WISP_DATA       *this,
        uint32_t        index
    );
    
    
    uint32_t        wisp_GetCDR(
        WISP_DATA       *this,
        uint32_t        index
    );
    
    
    WISP_DATA *     wisp_Init(
        WISP_DATA       *this
    );


    ERESULT         wisp_SetAtom(
        WISP_DATA       *this,
        uint32_t        index,
        bool            fValue
    );
    
 
    ERESULT         wisp_SetBP(
        WISP_DATA       *this,
        uint32_t        index,
        bool            fValue
    );
    
    
    ERESULT         wisp_SetCAR(
        WISP_DATA       *this,
        uint32_t        index,
        uint32_t        value
    );
    
    
    ERESULT         wisp_SetCDR(
        WISP_DATA       *this,
        uint32_t        index,
        uint32_t        value
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = wisp_ToDebugString(this,4);
     @endcode 
     @param     this    WISP object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    wisp_ToDebugString(
        WISP_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* WISP_H */

