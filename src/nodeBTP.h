// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODEBTP Console Transmit Task (nodeBTP) Header
//****************************************************************
/*
 * Program
 *			Separate nodeBTP (nodeBTP)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate nodeBTP to run things without complications
 *          of interfering with the main nodeBTP. A nodeBTP may be 
 *          called a nodeBTP on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/22/2018 Generated
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
#include        <nodeLnkP.h>


#ifndef         NODEBTP_H
#define         NODEBTP_H


//#define   NODEBTP_SINGLETON    1

#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct nodeBTP_data_s	NODEBTP_DATA;            // Inherits from OBJ
    typedef struct nodeBTP_class_data_s NODEBTP_CLASS_DATA;   // Inherits from OBJ

    typedef struct nodeBTP_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeBTP_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEBTP_DATA *);
    } NODEBTP_VTBL;

    typedef struct nodeBTP_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeBTP_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEBTP_DATA *);
    } NODEBTP_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEBTP_SINGLETON
    NODEBTP_DATA *     nodeBTP_Shared(
        void
    );

    bool            nodeBTP_SharedReset(
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to nodeBTP object if successful, otherwise OBJ_NIL.
     */
    NODEBTP_DATA *     nodeBTP_Alloc(
        void
    );
    
    
    OBJ_ID          nodeBTP_Class(
        void
    );
    
    
    NODEBTP_DATA *     nodeBTP_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NODELNKP_DATA * nodeBTP_getRoot(
        NODEBTP_DATA    *this
    );
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the given node to the Hash. If duplicates are not allowed, then
     the node's name must not exist in the Hash.  Otherwise, the node will
     be added to the head of the Hash list effectively blocking access to
     other nodes with the same name.  The A versions creates a node from
     the data given before trying to add it to the Hash.
     @param     this        Object Pointer
     @param     pNode       Data Object Pointer
     @param     fReplace    true == replace current entry if it exists,
     otherwise, return ERESULT_DATA_ALREADY_EXISTS
     error.
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
     error code is returned.
     */
    ERESULT         nodeBTP_Add(
        NODEBTP_DATA    *this,
        NODELNKP_DATA   *pNode,
        bool            fReplace
    );
    
    ERESULT         nodeBTP_AddA(
        NODEBTP_DATA    *this,
        int32_t         cls,
        const
        char            *pNameA,            // UTF-8
        OBJ_ID          pData
    );
    
    
    NODEBTP_DATA *   nodeBTP_Init(
        NODEBTP_DATA     *this
    );


    ERESULT     nodeBTP_IsEnabled(
        NODEBTP_DATA		*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = nodeBTP_ToDebugString(this,4);
     @endcode 
     @param     this    NODEBTP object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    nodeBTP_ToDebugString(
        NODEBTP_DATA     *this,
        int             indent
    );
    
    
    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */
    ERESULT         nodeBTP_VisitNodesPostRecurse(
        NODEBTP_DATA     *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );
    
    
    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */
    ERESULT         nodeBTP_VisitNodesInParent(   // Use Parent link (not recursive).
        NODEBTP_DATA     *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,
        void            *pArg3
    );
    
    ERESULT         nodeBTP_VisitNodesInRecurse(
        NODEBTP_DATA     *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );
    
    
    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */
    ERESULT         nodeBTP_VisitNodesPreParent(
        NODEBTP_DATA     *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,
        void            *pArg3
    );
    
    ERESULT         nodeBTP_VisitNodesPreRecurse(
        NODEBTP_DATA     *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEBTP_H */

