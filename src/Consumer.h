// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//      Consumer side of Producer/Consumer (Consumer) Header
//****************************************************************
/*
 * Program
 *          Consumer side of Producer/Consumer (Consumer)
 * Purpose
 *          This object provides the Consumer side of the Producer/
 *          Consumer programming pattern. This object starts the
 *          Consumer process in a separate thread that can be con-
 *          trolled with this object. All data sent to the Consumer
 *          must be packaged as an object, because that is all that
 *          it understands.
 *
 *          It is assumed that this object is always setup with the
 *          proper support objects and methods since it does nothing
 *          by itself but absorb the objects sent to it.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  05/04/2021 Generated
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


#ifndef         CONSUMER_H
#define         CONSUMER_H


//#define   CONSUMER_IS_IMMUTABLE     1
//#define   CONSUMER_JSON_SUPPORT     1
//#define   CONSUMER_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Consumer_data_s  CONSUMER_DATA;            // Inherits from OBJ
    typedef struct Consumer_class_data_s CONSUMER_CLASS_DATA;   // Inherits from OBJ

    typedef struct Consumer_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Consumer_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CONSUMER_DATA *);
    } CONSUMER_VTBL;

    typedef struct Consumer_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Consumer_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CONSUMER_DATA *);
    } CONSUMER_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  CONSUMER_SINGLETON
    CONSUMER_DATA * Consumer_Shared (
        void
    );

    void            Consumer_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Consumer object if successful, otherwise OBJ_NIL.
     */
    CONSUMER_DATA * Consumer_Alloc (
        void
    );
    
    
    OBJ_ID          Consumer_Class (
        void
    );
    
    
    CONSUMER_DATA * Consumer_New (
        void
    );
    
    
#ifdef  CONSUMER_JSON_SUPPORT
    CONSUMER_DATA * Consumer_NewFromJsonString (
        ASTR_DATA       *pString
    );

    CONSUMER_DATA * Consumer_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /* CalcWait() calculates the wait time that should be
     * used when waiting for a new record from the input
     * queue. If no routine is provided, then 100ms is used.
     */
    bool            Consumer_setCalcWait(
        CONSUMER_DATA   *this,
        uint32_t        (*pCalcWait)(
                            void *              // Calculate Method (pObj)
                        ),
        OBJ_ID          *pCalcWaitObj           // Calculate Method's Object
    );


    /*! @property   other   Used to store any object the user wants. Generally,
                            this object would be related somehow to the Consumer
                            object, but does not have to be.
     */
    OBJ_ID          Consumer_getOther (
        CONSUMER_DATA   *this
    );

    bool            Consumer_setOther (
        CONSUMER_DATA   *this,
        OBJ_ID          pValue
    );


    /* Service() handles the output object from the Consumer queue
     * and must release it when it is done with the object.
     */
    bool            Consumer_setService(
        CONSUMER_DATA   *this,
        int             (*pService)(OBJ_ID, OBJ_ID),
        OBJ_ID          *pServiceObj            // Service Method's Object
    );


    uint32_t        Consumer_getWait(
        CONSUMER_DATA   *this
    );

    bool            Consumer_setWait(
        CONSUMER_DATA   *this,
        uint32_t        value
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         Consumer_Disable (
        CONSUMER_DATA   *this
    );


    ERESULT         Consumer_Enable (
        CONSUMER_DATA   *this
    );

   
    CONSUMER_DATA * Consumer_Init (
        CONSUMER_DATA   *this
    );


    ERESULT         Consumer_IsEnabled (
        CONSUMER_DATA   *this
    );
    
 
#ifdef  CONSUMER_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Consumer_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Consumer_ToJson (
        CONSUMER_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Consumer_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Consumer_ToDebugString (
        CONSUMER_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* CONSUMER_H */
