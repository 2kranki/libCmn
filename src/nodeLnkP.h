// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODELNKP Console Transmit Task (nodeLnkP) Header
//****************************************************************
/*
 * Program
 *			Separate nodeLnkP (nodeLnkP)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate nodeLnkP to run things without complications
 *          of interfering with the main nodeLnkP. A nodeLnkP may be 
 *          called a nodeLnkP on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/19/2018 Generated
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
#include        <node.h>


#ifndef         NODELNKP_H
#define         NODELNKP_H


//#define   NODELNKP_SINGLETON    1

#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // NODELNKP_DATA is defined in node.h

    typedef struct nodeLnkP_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeLnkP_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODELNKP_DATA *);
    } NODELNKP_VTBL;

    typedef struct nodeLnkP_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeLnkP_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODELNKP_DATA *);
    } NODELNKP_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODELNKP_SINGLETON
    NODELNKP_DATA *     nodeLnkP_Shared(
        void
    );

    bool            nodeLnkP_SharedReset(
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to nodeLnkP object if successful, otherwise OBJ_NIL.
     */
    NODELNKP_DATA * nodeLnkP_Alloc(
        void
    );
    
    
    OBJ_ID          nodeLnkP_Class(
        void
    );
    
    
    NODELNKP_DATA * nodeLnkP_New(
        void
    );
    
    NODELNKP_DATA * nodeLnkP_NewWithUTF8AndClass(
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    );
    
    NODELNKP_DATA * nodeLnkP_NewWithUTF8ConAndClass(
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    );
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    int16_t         nodeLnkP_getBalance(
        NODELNKP_DATA   *this
    );
    
    bool            nodeLnkP_setBalance(
        NODELNKP_DATA   *this,
        int16_t         value
    );

    
    uint32_t        nodeLnkP_getIndex(
        NODELNKP_DATA   *this
    );
    
    bool            nodeLnkP_setIndex(
        NODELNKP_DATA   *this,
        uint32_t        value
    );

    
    NODELNKP_DATA * nodeLnkP_getLeftLink(
        NODELNKP_DATA   *this
    );
    
    bool            nodeLnkP_setLeftLink(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pValue
    );
    

    NODELNKP_DATA * nodeLnkP_getLeftThread(
        NODELNKP_DATA   *this
    );
    
    bool            nodeLnkP_setLeftThread(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pValue
    );
    
    
    NODELNKP_DATA * nodeLnkP_getMiddle(
        NODELNKP_DATA   *this
    );
    
    bool            nodeLnkP_setMiddle(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pValue
    );
    
    
    NAME_DATA *     nodeLnkP_getName(
        NODELNKP_DATA   *this
    );

    
    /*!
     @return    If successful, a UTF-8 string which must be freed
     with mem_Free(), otherwise NULL.
     */
    char *          nodeLnkP_getNameUTF8(
        NODELNKP_DATA   *this
    );
    

    NODELNKP_DATA * nodeLnkP_getParent(
        NODELNKP_DATA   *this
    );
    
    bool            nodeLnkP_setParent(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pValue
    );
    

    /*!
     The red property can be used by red-black trees.
     */
    bool            nodeLnkP_getRed(
        NODELNKP_DATA   *this
    );
    
    bool            nodeLnkP_setRed(
        NODELNKP_DATA   *this,
        bool            fValue
    );
    

    bool            nodeLnkP_getRightChild(
        NODELNKP_DATA   *this
    );
    
    NODELNKP_DATA * nodeLnkP_getRightLink(
        NODELNKP_DATA   *this
    );
    
    bool            nodeLnkP_setRightLink(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pValue
    );
    
    
    NODELNKP_DATA * nodeLnkP_getRightThread(
        NODELNKP_DATA   *this
    );
    
    bool            nodeLnkP_setRightThread(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pValue
    );
    
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         nodeLnkP_Compare(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pOther
    );

    ERESULT         nodeLnkP_CompareA(
        NODELNKP_DATA   *this,
        int32_t         cls,
        const
        char            *pNameA
    );
    

    /*!
     Copy all the link properties from this object to the other object.  This
     does not copy the node properties.
     @param     this    object pointer
     @param     pOther  object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_* error
                code.
     */
    ERESULT         nodeLnkP_CopyProperties(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pOther
    );
    
    
    NODELNKP_DATA * nodeLnkP_Init(
        NODELNKP_DATA   *this
    );


    bool            nodeLnkP_IsLeftLink(
        NODELNKP_DATA   *this
    );
    
    
    bool            nodeLnkP_IsRightChild(
        NODELNKP_DATA   *this
    );
    
 
    bool            nodeLnkP_IsRightLink(
        NODELNKP_DATA   *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = nodeLnkP_ToDebugString(this,4);
     @endcode 
     @param     this    NODELNKP object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     nodeLnkP_ToDebugString(
        NODELNKP_DATA   *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODELNKP_H */

