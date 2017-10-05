// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   dbField.c
 *	Generated 07/03/2015 14:12:28
 *
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include "dbField_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    DBFIELD_DATA *     dbField_Alloc(
    )
    {
        DBFIELD_DATA       *cbp;
        uint32_t        cbSize = sizeof(DBFIELD_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        dbField_getPriority(
        DBFIELD_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbField_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            dbField_setPriority(
        DBFIELD_DATA     *cbp,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !dbField_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    uint32_t        dbField_getSize(
        DBFIELD_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !dbField_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        return( 0 );
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            dbField_Dealloc(
        OBJ_ID          objId
    )
    {
        DBFIELD_DATA   *cbp = objId;
        bool            fRc;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !dbField_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        fRc = dbField_Disable( cbp );

        obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            dbField_Disable(
        DBFIELD_DATA		*cbp
    )
    {

        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !dbField_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        // Put code here...

        obj_Disable(cbp);
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    bool            dbField_Enable(
        DBFIELD_DATA		*cbp
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !dbField_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
        obj_Enable(cbp);

        // Put code here...
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    DBFIELD_DATA *   dbField_Init(
        DBFIELD_DATA       *cbp
    )
    {
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        cbp = obj_Init( cbp, obj_getSize(cbp), OBJ_IDENT_DBFIELD );
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        obj_setVtbl(cbp, (OBJ_IUNKNOWN *)&dbField_Vtbl);
        
        //cbp->stackSize = obj_getMisc1(cbp);

    #ifdef NDEBUG
    #else
        if( !dbField_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return cbp;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            dbField_IsEnabled(
        DBFIELD_DATA		*cbp
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbField_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(cbp))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            dbField_Validate(
        DBFIELD_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_DBFIELD) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(DBFIELD_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


