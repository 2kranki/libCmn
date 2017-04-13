//****************************************************************
//			Memory Manager (mem) Class Header
//****************************************************************

// vim: nu:noai:ts=4:sw=4

//Purpose
//			This set of subroutines provide generalized heap memory
// 			management using malloc and free like routines.
//Input
//Output
//Outline
//Remarks
//	1.		These routines are not re-entrant and are meant to be
//			included in each module that they will be used in so that
//			separate memory heaps are maintained per module/dll.
//History
//	01/05/2002	Went back to a Doubly-Linked list since the Hash Table
//				did not really work well.  Will look into a Binary Tree.
//	03/08/2001	Changed to use a Hash Table for debugging instead of
//				a list and added an IMalloc interface.
//	06/29/2000	Added DebugBreak() to error message in _DEBUG mode.
//	06/04/2000	Updated some of the header documentation.
//	07/18/1999	Keyed the debug mode off of NDEBUG instead of _DEBUG.  NDEBUG
//				is much more universal.  Changed debugging mode so that the
//				routines are always available for use.
//	06/19/1999	Added rmwMemStrDupA2W(), rmwMemStrDupW2A(), rmwMemStrCpyA2W()
//				and rmwMemStrCpyW2A() to provide UNICODE conversions.
//	05/02/1999	Updated rmwMemCmp() and rmwMemMove() to move integers then bytes.
//	01/01/1999	Fixed bug in rmwMemCmp().
//	12/20/1998	Fixed bug in rmwMemDebugCalloc() which was storing the
//				wrong size in its header block.
//	02/25/1997	Created from RwMem.hpp and RwMem.cpp.

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



#ifndef			MEM_H
#define			MEM_H			1



#if defined(__APPLE__)
#   include <memOSX.h>
#endif
#if defined(_MSC_VER)
#   include <memMSC.h>
#endif




#endif									// MEM_H
