//****************************************************************
//              Doubly-Linked List Subroutines Header
//****************************************************************

// vi: nu:noai:ts=4:sw=4

// Program
//				Doubly-Linked List Subroutines
// Purpose
//				These subroutines provide a general purpose set of Doubly-
//				Linked List Manipulation routines.	The linkage between the
//				nodes is done using pointers.  It is assumed that the
//				caller provides all areas.  No memory allocation
//				will be performed in these routines.  They were
//				designed to be utilized in other routines and for its
//              areas needed to be created/freed by the controlling object.
// Remarks
//	1.			These routines are potentially reentrant.  Protection
//				must be provided if two threads are accessing/updating
//				at the same time.
// History
//	08/21/2006	Updated to use the new C99 stdint.h and compile on MacOSX.
//	01/08/2002	Added Offset of Node Field into its Structure/Record.
//	01/06/2002	Changed so that a current entry is not made internally.
//              Added Count(), Init() & IsValidList().
//	01/05/2002	Created from LLD.h and LLD.c.  Hopefully this will be the
//              last time that I have to code a Doubly-Linked List. ;)
// References
//		"Algorithms+Data Structures=Programs", Nicklaus Wirth, Prentice-Hall,
//			1976
//		"Data Structures and Algorithms", Alfred V. Aho et al, Addison-Wesley,
//			1985
//		"Data Structures using C", Aaron M. Tenenbaum et al, Prentice-Hall,
//			1990
//		"Programs and Data Structures in C", Leendert Ammeraal, John Wiley
//			& Sons, 1987


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



#ifndef         LISTDL_H
#define         LISTDL_H	1

//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************


#ifdef	__cplusplus
extern	"C" {
#endif
    
    
    //                  *** Node Entry ***
    // This control block must be included in each of the nodes that you
    // add to the list and you must point to it whenever requesting any
    // node-based services.
    #pragma pack(push, 1)
    typedef struct listdl_node_s {
        struct listdl_node_s
                        *pNext;
        struct listdl_node_s
                        *pPrev;
    } LISTDL_NODE;
    #pragma pack(pop)


    //                  *** Main Control Block ***
    // This control block must be provided on entry to every function
    // in this system.  It must be initialized to binary zeroes prior
    // to the first call to any functions within this system.
    typedef struct	listdl_data_s {
        LISTDL_NODE     *pHead;
        LISTDL_NODE     *pTail;
        uint32_t        cCount;
        uint32_t		iOffset;
    } LISTDL_DATA;




    //****************************************************************
    //* * * * * * * * * * *  Routine Definitions * * * * * * * * * * *
    //****************************************************************


    // Add2Head() adds a new entry to the Doubly-Linked list as
    // the new Head of the List.
    // Returns:
    //	Record Ptr		=	Successful Completion
    //	NULL        	=	Unsuccessful Completion
    void * 			listdl_Add2Head(
        LISTDL_DATA     *this,
        void			*pRecord
    );


    // Add2Tail() adds a new entry to the Doubly-Linked list as
    // the Last Entry in the List.
    // Returns:
    //	Record Ptr		=	Successful Completion
    //	NULL        	=	Unsuccessful Completion
    void * 			listdl_Add2Tail(
        LISTDL_DATA     *this,
        void			*pRecord
    );


    // AddAfter() adds a new entry to the Doubly-Linked list immediately
    // following the Current Entry.
    // Returns:
    //	Node Ptr		=	Successful Completion
    //	NULL        	=	Unsuccessful Completion
    void * 			listdl_AddAfter(
        LISTDL_DATA     *this,
        void			*pRecord,
        void			*pInsert				// New Record to be added
    );


    // AddBefore() adds a new entry to the Doubly-Linked list immediately
    // preceding the Current Entry.
    // Returns:
    //	Node Ptr		=	Successful Completion
    //	NULL        	=	Unsuccessful Completion
    void * 			listdl_AddBefore(
        LISTDL_DATA     *this,
        void			*pRecord,
        void			*pInsert				// New Record to be added
    );


    // Contains() returns true if the list contains the provided
    // entry in the Doubly-Linked List otherwise false. This is
    // a relatively slow operation since it searches the list from
    // the head.
    bool 			listdl_Contains(
        LISTDL_DATA		*this,
        void			*pRecord				// Node
    );
    
    
    // Count() returns the number of entries in the Doubly-Linked
    // List.
    // Returns:
    //	Number of Nodes
    uint32_t 		listdl_Count(
        LISTDL_DATA     *this
     );


    // listdl_DATALength() returns the size of the Object's Main Area which must
    // be supplied to all functions.
    // List.
    // Returns:
    //	Number of Nodes
    uint32_t 		listdl_DATALength(
        void
    );


    // Delete() deletes the provided entry in the Doubly-Linked
    // List.
    // Returns:
    //	TRUE			=	Successful Completion
    //	FALSE        	=	Unsuccessful Completion
    bool 			listdl_Delete(
        LISTDL_DATA		*this,
         void			*pRecord				// Node already in List or NULL
    );


    // DeleteHead() deletes the head of the chain and returns
    // a ptr to it.
    // List.
    // Returns:
    //	Node Ptr		=	Successful Completion
    //	NULL        	=	Unsuccessful Completion
    void * 			listdl_DeleteHead(
        LISTDL_DATA     *this
    );
        
        
    // DeleteTail() deletes the tail of the chain and returns
    // a ptr to it.
    // List.
    // Returns:
    //	Node Ptr		=	Successful Completion
    //	NULL        	=	Unsuccessful Completion
    void * 			listdl_DeleteTail(
        LISTDL_DATA     *this
    );
        
        
    // Head() returns the first entry in the Doubly-Linked List.
    // The Current Entry is set to the First Entry in the List.
    // Returns:
    void * 			listdl_Head(
        LISTDL_DATA		*this
     );


    /*!
     Index() returns the Ith entry from the Head of the Doubly-Linked
     List.
     @param     index
        index relative to 1 from the Head of the List.
     @result
    	Node Ptr		=	Successful Completion
    	NULL        	=	Unsuccessful Completion
     */
    void * 			listdl_Index(
        LISTDL_DATA		*this,
        int32_t			index					// (relative to 1)
    );


    /*!
     Initialize the main control block to an empty list.
     Example:
     @code:
        bool  fRc = listdl_Init(&freeList, offsetof(LRU_SECTOR,lruList));
     @endcode:
     @param:    this    list control block pointer
     @param:    offset  number of bytes displacement into the list entry to
                        find the LISTDL_NODE.
     @return:   If successful, true. Otherwise, false.
     */
    bool 			listdl_Init(
        LISTDL_DATA		*this,
        uint32_t		offset 					// Offset of Node Field within Structure
    );


    // IsValidList() returns if the List validates.
    // Returns:
    //	TRUE			=	Successful Completion
    //	FALSE        	=	Unsuccessful Completion
    bool 			listdl_IsValidList(
        LISTDL_DATA		*this
     );


    // Move2Head() moves the provided entry in the Doubly-Linked List
    // to the Head of the List.
    // Returns:
    //	TRUE			=	Successful Completion
    //	FALSE        	=	Unsuccessful Completion
    bool 			listdl_Move2Head(
        LISTDL_DATA     *pCB,
        void			*pCurrent
    );
    
    
    // Next() returns the next entry from the current entry in the
    // Doubly-Linked List.	The current pointer is updated to the
    // Next Entry.	If the Current Entry was at the end of the list,
    // then the Head Entry is set to the Current Entry.
    // Returns:
    //	Node Ptr		=	Successful Completion
    //	NULL        	=	Unsuccessful Completion
    void * 			listdl_Next(
        LISTDL_DATA		*this,
         void			*pRecord				// Node already in List or NULL
    );


    // Prev() returns the previous entry from the current entry in the
    // Doubly-Linked List.	The current pointer is updated to the
    // Next Entry.	If the Current Entry was at the end of the list,
    // then the Tail Entry is set to the Current Entry.
    // Returns:
    //	Node Ptr		=	Successful Completion
    //	NULL        	=	Unsuccessful Completion
    void * 			listdl_Prev(
        LISTDL_DATA		*this,
        void			*pRecord				// Node already in List or NULL
    );


    // Sort() sorts the list in order provided by the supplied
    // comparison routine. The comparison routine needs to return
    // 0 if *p0 == *p1, -n if *p0 < *p1 or +n if *p0 > *p1.
    // Returns:
    //	TRUE			=	Successful Completion
    //	FALSE        	=	Unsuccessful Completion
    bool 			listdl_Sort(
        LISTDL_DATA		*this,
        int             (*pCompare)(void *p0, void *p1)
    );
    
    
    // Tail() returns the last entry in the Doubly-Linked List.
    // The Current Entry is set to the Last Entry in the List.
    // Returns:
    //	Node Ptr		=	Successful Completion
    //	NULL        	=	Unsuccessful Completion
    void * 			listdl_Tail(
        LISTDL_DATA		*this
    );
    
    
#ifdef	__cplusplus
};
#endif



#endif
