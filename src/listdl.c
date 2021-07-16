// vi: nu:noai:ts=4:sw=4

/****************************************************************
 *       Doubly-Linked List (listdl) Support Subroutines        *
 ****************************************************************/

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
* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
****************************************************************/

/* Header File Inclusion */
#include        "listdl.h"


#define			Node2Ptr( Node )	((void *)((uint8_t *)Node - pCB->iOffset))
#define			Ptr2Node( Ptr )		((LISTDL_NODE *)\
									 ((uint8_t *)Ptr + pCB->iOffset))



/****************************************************************
* * * * * * * * * * *  Internal Subroutines * * * * * * * * * * *
****************************************************************/




/****************************************************************
* * * * * * * * * * *  External Subroutines   * * * * * * * * * *
****************************************************************/



/**********************************************************
					A d d 2 H e a d
 **********************************************************/

void * 			listdl_Add2Head(
    LISTDL_DATA     *pCB,
    void			*pData
)
{
    LISTDL_NODE    *pNode;

	// Validate the input parameters.
	if( pData )
		;
	else
		return( NULL );
	pNode = Ptr2Node( pData );

	// Chain it to the top of the list.
	pNode->pNext = pCB->pHead;
	pNode->pPrev = NULL;
	if( NULL == pCB->pHead )
		pCB->pTail = pNode;
	else
		pCB->pHead->pPrev = pNode;
	pCB->pHead = pNode;
	++pCB->cCount;

	// Return to caller.
	return( pData );
}




/**********************************************************
					A d d 2 T a i l
 **********************************************************/

void * 			listdl_Add2Tail(
    LISTDL_DATA     *pCB,
    void			*pData
)
{
    LISTDL_NODE    *pNode;

	// Validate the input parameters.
	if( pData )
		;
	else
		return( NULL );
	pNode = Ptr2Node( pData );

	// Chain it to the bottom of the list.
	pNode->pPrev = pCB->pTail;
	pNode->pNext = NULL;
	if( pCB->pTail == NULL )
		pCB->pHead = pNode;
	else
		pCB->pTail->pNext = pNode;
	pCB->pTail = pNode;
	++pCB->cCount;

	// Return to caller.
	return( pData );
}




/**********************************************************
						A d d A f t e r
 **********************************************************/

void * 			listdl_AddAfter(
    LISTDL_DATA     *pCB,
    void			*pCurrent,
    void			*pData
)
{
    LISTDL_NODE    *pNode;
    LISTDL_NODE    *pNodeNew;
    void			*pRet;

	// Validate the input parameters.
	if( NULL == pData )
		return( NULL );

	// Chain to top of list if appropriate.
	if( NULL == pCurrent ) {
		pRet = listdl_Add2Head( pCB, pData );
		return( pRet );
	}

	// Chain it to the bottom of the list if appropriate.
	pNode = Ptr2Node( pCurrent );
	if( pNode && (pNode->pNext == NULL) ) {
		pRet = listdl_Add2Tail( pCB, pData );
		return( pRet );
	}

	// Insert it into the list.
	pNodeNew = Ptr2Node( pData );
	pNodeNew->pNext = pNode->pNext;
	pNodeNew->pPrev = pNode;
	pNode->pNext = pNodeNew;
	pNodeNew->pNext->pPrev = pNodeNew;
	++pCB->cCount;

	// Return to caller.
	return( pData );
}




/**********************************************************
						A d d B e f o r e
 **********************************************************/

void * 			listdl_AddBefore(
    LISTDL_DATA     *pCB,
    void			*pCurrent,
	void			*pData
)
{
    LISTDL_NODE    *pNode;
    LISTDL_NODE    *pNodeNew;
    void			*pRet;

	// Validate the input parameters.
	if( NULL == pData )
		return( NULL );

	// Chain to top of list if appropriate.
	if( NULL == pCurrent ) {
		pRet = listdl_Add2Head( pCB, pCurrent );
		return( pRet );
	}

	// Chain it to the top of the list if appropriate.
	pNode = Ptr2Node( pCurrent );
	if( pNode && (pNode->pPrev == NULL) ) {
		pRet = listdl_Add2Head( pCB, pData );
		return( pRet );
	}

	// Insert it into the list.
	pNodeNew = Ptr2Node( pData );
	pNodeNew->pNext = pNode;
	pNodeNew->pPrev = pNode->pPrev;
	pNode->pPrev = pNodeNew;
	pNodeNew->pPrev->pNext = pNodeNew;
	++pCB->cCount;

	// Return to caller.
	return( pData );
}




//**********************************************************
//                    C l e a r  N o d e
//**********************************************************

bool             listdl_ClearNode(
    LISTDL_DATA     *pCB,
    void            *pRecord
)
{
    LISTDL_NODE     *pRecordNode;
    
    // Do initialization.
    if( NULL == pRecord ) {
        return false;
    }
    pRecordNode = Ptr2Node( pRecord );
    
    pRecordNode->pNext = NULL;
    pRecordNode->pPrev = NULL;
    
    // Return to caller.
    return true;
}



//**********************************************************
//					C o n t a i n s
//**********************************************************

bool 			listdl_Contains(
    LISTDL_DATA     *pCB,
    void			*pRecord
)
{
    LISTDL_NODE     *pRecordNode;
    LISTDL_NODE     *pCurNode;
    
	// Do initialization.
    if( NULL == pRecord ) {
        return false;
    }
	pRecordNode = Ptr2Node( pRecord );
    
	pCurNode = pCB->pHead;
    while (pCurNode) {
        if (pCurNode == pRecordNode) {
            return true;
        }
        pCurNode = pCurNode->pNext;
    }
    
	// Return to caller.
	return false;
}




/**********************************************************
						C o u n t
 **********************************************************/

uint32_t 		listdl_Count(
	LISTDL_DATA     *pCB
)
{
	uint32_t		iRet;

	// Do initialization.
	iRet = pCB->cCount;

	// Return to caller.
	return( iRet );
}




//**********************************************************
//					D A T A L e n g t h
//**********************************************************

uint32_t		listdl_DATALength(
	void
)
{
	uint32_t		iRc = sizeof(LISTDL_DATA);

	// Do initialization.

	// Return to caller.
	return( iRc );
}




//**********************************************************
//						D e l e t e
//**********************************************************

bool 			listdl_Delete(
    LISTDL_DATA     *pCB,
	void			*pCurrent
)
{
    LISTDL_NODE    *pNode;

	// Do initialization.
    if( NULL == pCurrent ) {
        return false;
    }
	pNode = Ptr2Node( pCurrent );

	// Remove it from the linked list.
	if( pNode->pPrev == NULL ) {  /*** First Element ***/
		pCB->pHead = pNode->pNext;
	}
	else {
		pNode->pPrev->pNext = pNode->pNext;
	}
	if( pNode->pNext == NULL ) {  /*** Last Element ***/
		pCB->pTail = pNode->pPrev;
	}
	else {
		pNode->pNext->pPrev = pNode->pPrev;
	}
	--pCB->cCount;
    pNode->pNext = NULL;
    pNode->pPrev = NULL;

	// Return to caller.
	return true;
}




/**********************************************************
                D e l e t e H e a d
 **********************************************************/

void * 			listdl_DeleteHead(
    LISTDL_DATA     *pCB
)
{
    LISTDL_NODE     *pNode;
    void            *pData;
    
	// Validate the input parameters.
    if( NULL == pCB->pHead )
        return NULL;
	pNode = pCB->pHead;
    
	// Chain it to the top of the list.
    pCB->pHead = pNode->pNext;
	if( pNode->pNext == NULL ) {    /*** Last Element ***/
		pCB->pTail = pNode->pPrev;
	}
	else {
		pNode->pNext->pPrev = pNode->pPrev;
	}
	--pCB->cCount;
    pNode->pNext = NULL;
    pNode->pPrev = NULL;
    
	// Return to caller.
    pData = Node2Ptr(pNode);
	return( pData );
}




/**********************************************************
                    D e l e t e T a i l
 **********************************************************/

void * 			listdl_DeleteTail(
    LISTDL_DATA     *pCB
)
{
    LISTDL_NODE     *pNode;
    void            *pData;
    
	// Validate the input parameters.
    if( NULL == pCB->pTail )
        return NULL;
	pNode = pCB->pTail;
    
	// Chain it to the top of the list.
    pCB->pTail = pNode->pPrev;
	if( pNode->pPrev == NULL ) {    /*** Last Element ***/
		pCB->pHead = NULL;
	}
	else {
		pNode->pPrev->pNext = NULL;
	}
	--pCB->cCount;
    pNode->pNext = NULL;
    pNode->pPrev = NULL;
    
	// Return to caller.
    pData = Node2Ptr(pNode);
	return( pData );
}




/**********************************************************
                        D e q u e u e
 **********************************************************/

void *             listdl_Dequeue(
    LISTDL_DATA     *pCB
)
{
    void            *pRet;
    
    // Validate the input parameters.
    pRet = listdl_DeleteTail(pCB);
    
    // Return to caller.
    return pRet;
}



/**********************************************************
                        E n q u e u e
 **********************************************************/

void *             listdl_Enqueue(
    LISTDL_DATA     *pCB,
    void            *pData
)
{
    void            *pRet;
    
    // Validate the input parameters.
    pRet = listdl_Add2Head(pCB, pData);
    
    // Return to caller.
    return pRet;
}



/**********************************************************
						H e a d
 **********************************************************/

void * 			listdl_Head(
    LISTDL_DATA     *pCB
)
{   
    LISTDL_NODE     *pNode;

	// Do initialization.

	// Set the Current node to the Head of the List.
	if( pCB->pHead && (pCB->cCount > 0) )
		;
	else
		return( NULL );
	pNode = pCB->pHead;

	// Return to caller.
	return( ((uint8_t *)pNode - pCB->iOffset) );
}



/**********************************************************
						I n d e x
 **********************************************************/

void * 			listdl_Index(
    LISTDL_DATA     *pCB,
	int32_t         Index
)
{
    LISTDL_NODE     *pNode = NULL;

	// Do initialization.
	if( Index > 0 )
		;
	else
		return( NULL );

	// Point to the indexed node.
	pNode = pCB->pHead;
	while( pNode && --Index ) {
		pNode = pNode->pNext;
	}
	if( pNode && (pCB->cCount > 0) )
		;
	else
		return( NULL );

	// Return to caller.
	return Node2Ptr(pNode);
}




/**********************************************************
						I n i t
 **********************************************************/

bool 			listdl_Init(
    LISTDL_DATA     *pCB,
	uint32_t		iOffset
)
{

	// Do initialization.

	// Set up the areas.
	pCB->pHead = NULL;
	pCB->pTail = NULL;
    pCB->cCount = 0;
	pCB->iOffset = iOffset;

	// Return to caller.
	return( true );
}




/**********************************************************
					I s V a l i d L i s t
 **********************************************************/

bool 			listdl_IsValidList(
    LISTDL_DATA     *pCB
)
{
    LISTDL_NODE     *pNode = NULL;
	uint32_t		cCount = 0;

	// Do initialization.
	if( (NULL == pCB) )
		return( false );

	// Point to the indexed node.
	pNode = pCB->pHead;
	while( pNode ) {
		if( pNode->pNext ) {
			if( pNode->pNext->pPrev == pNode )
				;
			else
				return( false );
		}
		else {
			if( pNode == pCB->pTail )
				;
			else
				return( false );
		}
		if( pNode->pPrev ) {
			if( pNode->pPrev->pNext == pNode )
				;
			else
				return( false );
		}
		else {
			if( pNode == pCB->pHead )
				;
			else
				return( false );
		}
		pNode = pNode->pNext;
		++cCount;
	}
	if( cCount == pCB->cCount )
		;
	else
		return( false );

	// Return to caller.
	return( true );
}




//**********************************************************
//                  M o v e 2 H e a d
//**********************************************************

bool 			listdl_Move2Head(
    LISTDL_DATA     *pCB,
    void			*pCurrent
)
{
    LISTDL_NODE    *pNode;
    
    // Do initialization.
    if( NULL == pCurrent ) {
        return false;
    }
    pNode = Ptr2Node( pCurrent );
    
    if (pCB->pHead == pNode) {
        return true;
    }
    
    // Remove it from the linked list.
    if( pNode->pPrev == NULL ) {  /*** First Element ***/
        pCB->pHead = pNode->pNext;
    }
    else {
        pNode->pPrev->pNext = pNode->pNext;
    }
    if( pNode->pNext == NULL ) {  /*** Last Element ***/
        pCB->pTail = pNode->pPrev;
    }
    else {
        pNode->pNext->pPrev = pNode->pPrev;
    }
    //--pCB->cCount;
    //pNode->pNext = NULL;
    //pNode->pPrev = NULL;
    
    // Chain it to the head of the list.
    pNode->pNext = pCB->pHead;
    pNode->pPrev = NULL;
    if( NULL == pCB->pHead )
        pCB->pTail = pNode;
    else
        pCB->pHead->pPrev = pNode;
    pCB->pHead = pNode;
    //++pCB->cCount;
    
    // Return to caller.
    return true;
}




/**********************************************************
						N e x t
 **********************************************************/

void * 			listdl_Next(
    LISTDL_DATA     *pCB,
	void			*pCurrent
)
{
    LISTDL_NODE    *pNode;

	// Do initialization.

	// Point to the Next Node.
    if( NULL == pCurrent ) {
		pNode = pCB->pHead;
    }
	else {
		pNode = Ptr2Node(pCurrent);
		pNode = pNode->pNext;
	}
	if( pNode && (pCB->cCount > 0) )
		;
	else
		return( NULL );

	// Return to caller.
	return Node2Ptr(pNode);
}



/**********************************************************
                        P o p
 **********************************************************/

void *             listdl_Pop(
    LISTDL_DATA     *pCB
)
{
    void            *pRet;
    
    // Validate the input parameters.
    pRet = listdl_DeleteHead(pCB);
    
    // Return to caller.
    return pRet;
}



//**********************************************************
//						P r e v
//**********************************************************

void * 			listdl_Prev(
    LISTDL_DATA     *pCB,
	void			*pCurrent
)
{
    LISTDL_NODE     *pNode;

	// Do initialization.

	// Point to the previous node.
    if( NULL == pCurrent ) {
		pNode = pCB->pTail;
    }
	else {
		pNode = Ptr2Node( pCurrent );
		pNode = pNode->pPrev;
	}
	if( pNode && (pCB->cCount > 0) )
		;
	else
		return( NULL );

	// Return to caller.
	return( Node2Ptr( pNode ) );
}



/**********************************************************
                        P u s h
 **********************************************************/

void *             listdl_Push(
    LISTDL_DATA     *pCB,
    void            *pData
)
{
    void            *pRet;
    
    // Validate the input parameters.
    pRet = listdl_Add2Head(pCB, pData);
    
    // Return to caller.
    return pRet;
}



/**********************************************************
                    S h i f t  H e a d
 **********************************************************/

// ShiftHead() shifts the tail to the head and returns the
// new head.
void *             listdl_ShiftHead(
    LISTDL_DATA     *pCB
)
{
    LISTDL_NODE     *pTail;         // Original Values.
    LISTDL_NODE     *pHead;


    // Do initialization.
    if( pCB->pHead && (pCB->cCount > 0) )
        ;
    else
        return NULL;

    // Save current head and tail.
    pHead = pCB->pHead;
    pTail = pCB->pTail;
    
    // Rechain the tail to the head.
    pCB->pTail = pTail->pPrev;
    pCB->pHead = pTail;
    pTail->pPrev->pNext = NULL;
    pHead->pPrev = pTail;
    pTail->pPrev = NULL;
    pTail->pNext = pHead;

    // Return to caller with new head (old tail).
    return ((uint8_t *)pTail - pCB->iOffset);
}



/**********************************************************
                    S h i f t  T a i l
 **********************************************************/

// ShiftTail() shifts the head to the tail and returns the
// new head.
void *             listdl_ShiftTail (
    LISTDL_DATA     *pCB
)
{
    LISTDL_NODE     *pTail;         // Original Values.
    LISTDL_NODE     *pHead;


    // Do initialization.
    if( pCB->pTail && (pCB->cCount > 0) )
        ;
    else
        return NULL;

    // Save current head and tail.
    pHead = pCB->pHead;
    pTail = pCB->pTail;
    
    // Rechain the head to the tail.
    pCB->pHead = pHead->pNext;
    pHead->pNext->pPrev = NULL;
    pCB->pTail = pHead;
    pTail->pNext = pHead;
    pHead->pPrev = pTail;
    pHead->pNext = NULL;

    // Return to caller with new head (old tail).
    return ((uint8_t *)pCB->pHead - pCB->iOffset);
}



/**********************************************************
                        S o r t
 **********************************************************/

// Sort() sorts the list in order provided by the supplied
// comparison routine.
// Returns:
//	TRUE			=	Successful Completion
//	FALSE        	=	Unsuccessful Completion
bool 			listdl_Sort(
    LISTDL_DATA		*pCB,
    int             (*pCompare)(void *, void *)
)
{
    LISTDL_NODE     *pNode0 = NULL;
    LISTDL_NODE     *pNode1 = NULL;
    int             rc;
    uint32_t        i;

/*      Insertion Sort from Wikipedia
 *
 *  for i = 1 to length(A)
 *      j = i
 *      while j > 0 and A[j-1] > A[j]
 *          swap A[j] and A[j-1]
 *          j = j - 1
 *      end while
 *  end for
 */
    
    if (NULL == pCB) {
        return false;
    }
    
    if (pCB->cCount < 2) {
        return true;
    }
    
    for (i=1; i<pCB->cCount; ++i) {
        pNode1 = listdl_Index(pCB, i+1);
        while (pNode1->pPrev) {
            pNode0 = pNode1->pPrev;
            rc = (*pCompare)(Node2Ptr(pNode0), Node2Ptr(pNode1));
            if (rc > 0) {
                if (pNode0->pPrev) {
                    pNode0->pPrev->pNext = pNode1;
                }
                else {
                    pCB->pHead = pNode1;
                }
                if (pNode1->pNext) {
                    pNode1->pNext->pPrev = pNode0;
                }
                else {
                    pCB->pTail = pNode0;
                }
                pNode0->pNext = pNode1->pNext;
                pNode1->pNext = pNode0;
                pNode1->pPrev = pNode0->pPrev;
                pNode0->pPrev = pNode1;
            }
            else
                break;
        }
    }
    
    // Return to caller.
    return true;
}




//**********************************************************
//                        T a i l
//**********************************************************

void * 			listdl_Tail(
    LISTDL_DATA     *pCB
)
{
    LISTDL_NODE     *pNode = NULL;
    
	// Do initialization.
    
	// Set the Current node to the Tail of the List.
	if( pCB->pTail && (pCB->cCount > 0) )
		;
	else
		return( NULL );
	pNode = pCB->pTail;
    
	// Return to caller.
	return( Node2Ptr( pNode ) );
}



//**********************************************************
//                        T o p
//**********************************************************

void *             listdl_Top(
    LISTDL_DATA     *pCB
)
{
    LISTDL_NODE     *pNode = NULL;
    
    // Do initialization.
    
    // Set the Current node to the Tail of the List.
    if( pCB->pHead && (pCB->cCount > 0) )
        ;
    else
        return( NULL );
    pNode = pCB->pHead;
    
    // Return to caller.
    return Node2Ptr(pNode);
}








