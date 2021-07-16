//****************************************************************
//					C Fixed Array (CFA) Functions			
//****************************************************************
// vi: nu:noai:ts=4:sw=4

/*
 * Todo List
 *  ---         Add CFA_Sort() with a comparison exit routine which
 *              points at the Data associated with an Entry.
 *  ---         Add routines to provide a doubly-linked list capability.
 *              See LLD.h for details.
 * Remarks
 *  1.          None
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



/****************************************************************
* * * * * * * * * * * *  data definitions   * * * * * * * * * * *
****************************************************************/

/* Header File Inclusion */
#include        <stdlib.h>
#include        <string.h>
#include        "cfa_internal.h"



#ifdef	__cplusplus
extern	"C" {
#endif
    
    
/* Internal Subroutine Definitions
 */
#ifdef ZZZ_ZZZ
static
BOOL            INT_ExpandArray(
	CFA_CB          *cbp         /* CFA_CB Pointer */
);
static
BOOL            INT_ValidEntry(
	CFA_CB          *cbp,            /* CFA_CB Pointer */
	CFA_INDEX       NumEnt          /* Entry Number */
);
#endif
#ifdef NDEBUG
#else
bool			cfa_Validate(
    CFA_DATA        *cbp
);
#endif





/****************************************************************
* * * * * * * * * * *  Internal Subroutines * * * * * * * * * * *
****************************************************************/


#ifdef ZZZ_ZZZ
/* Expand the current Pointer Array by Inc entries.
 */
static
BOOL            INT_ExpandArray(
	CFA_CB          *cbp
)
{
    CFA_Node        *pWork;
	uint32_t        OldMax;

	// Do initialization.
	if( cbp == NULL )
		return( FALSE );

	/* Expand the Array.
	 */
	OldMax = cbp->Max;
    cbp->Max += cbp->Inc;
	pWork = (CFA_Node *)mem_Calloc( cbp->Max, sizeof(CFA_Node) );
	if( pWork == NULL ) {
		cbp->Max = OldMax;
		return( FALSE );
	}
	if( cbp->pNodes == NULL )
		;
	else {
		memmove( pWork, cbp->pNodes, (OldMax * sizeof(CFA_Node)) );
		free( cbp->pNodes );
	}
	cbp->pNodes = pWork;

	// Return to caller.
	return( TRUE );
}




/* Get Entry Number from Node Ptr.
 */
static
CFA_INDEX       INT_EntryNoFromNode(
	CFA_CB          *cbp,
	CFA_Node        *pNode
)
{
    CFA_INDEX       EntryNo;

	EntryNo = (CFA_INDEX)((pNode - cbp->pNodes) + 1);
    return( EntryNo );
}



/* Point to Node using Entry Number.
 */
static
CFA_Node *      INT_NodeFromEntryNo(
	CFA_CB          *cbp,
	CFA_INDEX       EntryNo
)
{
    CFA_Node        *pNode;

	pNode = &cbp->pNodes[EntryNo-1];
    return( pNode );
}



/* Validate Entry Number.
 */
static
BOOL            INT_ValidEntry(
	CFA_CB          *cbp,
	CFA_INDEX       EntryNo
)
{
	BOOL            rc = FALSE;

	// Perform the validation checks.
	if( cbp && (cbp->cbSize == sizeof(CFA_CB)) )
		;
	else
		return( rc );
	if( (EntryNo <= 0) || (EntryNo > cbp->Max) )
		return( rc );
	rc = TRUE;

	// Return to caller.
	return( rc );
}
#endif


    
    


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    //---------------------------------------------------------------
    //                        A l l o c
    //---------------------------------------------------------------

    CFA_DATA *      cfa_Alloc(
    )
    {
        CFA_DATA        *this;
        
        // Do initialization.
        
        this = (CFA_DATA *)obj_Alloc( sizeof(CFA_DATA) );
        
        // Return to caller.
        return( this );
    }



    

    //===============================================================
    //                      *** Properties ***
    //===============================================================

    uint16_t        cfa_getEntrySize(
        CFA_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cfa_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->entrySize;
    }


    bool			cfa_putEntrySize(
        CFA_DATA		*this,
        uint16_t        value
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cfa_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
        if( 0 == value) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->entrySize = ROUNDUP4(value);
        
        return true;
    }



    uint16_t        cfa_getNumEntries(
        CFA_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cfa_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->cEntries;
    }


    bool			cfa_putNumEntries(
        CFA_DATA		*this,
        uint16_t        value
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !cfa_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
        if( 0 == value) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->cEntries = value;
        
        return true;
    }


    

    //===============================================================
    //                      *** Methods ***
    //===============================================================


    /**********************************************************
                          C o u n t
     **********************************************************/

    CFA_INDEX       cfa_Count(
        CFA_DATA        *this
    )
    {
#ifdef NDEBUG
#else
        if ( !cfa_Validate(this) ) {
            DEBUG_BREAK();
            return -1;
        }
#endif

        return( this->cEntries );
    }



    //**********************************************************
    //					  D e a l l o c
    //**********************************************************
    
    void            cfa_Dealloc(
        OBJ_ID          objId
    )
    {
        CFA_DATA        *this = objId;

        if (NULL == this) {
            return;
        }
#ifdef NDEBUG
#else
        if ( !cfa_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        if (this->ppIndex) {
            mem_Free(this->ppIndex);
            this->ppIndex = NULL;
        }

        obj_Dealloc(this);
        //this = NULL;
    }
    
    
    
    //**********************************************************
    //					  I n d e x
    //**********************************************************

    void **         cfa_Index(
        CFA_DATA        *this
    )
    {
    #ifdef RMW_DEBUG
        if ( !cfa_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
    #endif
        
        return this->ppIndex;
    }




    //**********************************************************
    //						  I n i t
    //**********************************************************/

    CFA_DATA *      cfa_Init(
        CFA_DATA        *this,
        uint32_t		cEntries,		// Number of Entries
        uint32_t		entrySize		// Size of an Entry in Bytes
    )
    {
        uint32_t		dataOffset;
        uint32_t		dataSize;
        uint32_t		indexSize;
        uint32_t        size;
        int				i;

        // Validate the input parameters.
        if (NULL == this) {
            return NULL;
        }
        if( cEntries == 0 ) {
            DEBUG_BREAK();
            return NULL;
        }
        if( entrySize == 0 ) {
            DEBUG_BREAK();
            return NULL;
        }
        
        this = obj_Init(this, sizeof(CFA_DATA), OBJ_IDENT_CFA);
        if (NULL == this) {
            return NULL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&cfa_Vtbl);

        // Initialize the fields.
        this->cEntries = cEntries;
        this->entrySize = entrySize;

        // Calculate size.
        this->actualEntrySize = ROUNDUP4(this->entrySize);
        dataSize = this->cEntries * this->actualEntrySize;
        dataSize = ROUNDUP4(dataSize);
        indexSize = this->cEntries * sizeof(void *);
        indexSize = ROUNDUP4(indexSize);
        dataOffset = indexSize;
        size = indexSize + dataSize;
        
        this->ppIndex = mem_Malloc(size);
        if (NULL == this->ppIndex) {
            return this;
        }
            
        // Set up the index.
        for( i=0; i<this->cEntries; ++i ) {
            this->ppIndex[i] = (uint8_t *)this->ppIndex + (dataOffset + (i * entrySize));
        }
        
        // Return to caller.
        return( this );
    }




    //**********************************************************
    //                    V a l i d a t e
    //**********************************************************

#ifdef NDEBUG
#else
    bool			cfa_Validate(
        CFA_DATA        *this
    )
    {
        
        // Do initialization.
        
        if( this && obj_IsKindOf(this, OBJ_IDENT_CFA) )
            ;
        else
            return false;
        if( (sizeof(CFA_DATA) <= obj_getSize(this)) )
            ;
        else {
            return false;
        }
        
        // Return to caller.
        return true;
    }
#endif



    
    
#ifdef	__cplusplus
};
#endif







