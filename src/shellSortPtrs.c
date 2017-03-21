/*	* * *  Bubble Sort Routine	* * *	*/
/* Purpose
 *		This routine sorts a pointer array using the simple
 *		Shell Sort Algorithm into an ascending sequence.
 * History
 *	11/15/93	Added Borland C++ for OS/2 support.
 *	02/03/93	Created from scratch.
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


/* Header File Inclusion */
#include	<stddef.h>
#include	<stdint.h>



/****************************************************************
 *					Internally Used Subroutines 				*
 ****************************************************************/






/****************************************************************
 *					Externally Used Subroutines 				*
 ****************************************************************/



/*	* * *  Shell Sort a Pointer Array	* * *
 * This routine performs a Shell Sort on a provided
 * pointer array into ascending sequence.
 */
void		ShellSortPtrs(
	void		**pBase,	/* Beginning of Array Ptr */
	size_t		Num,		/* Number of Elements in Array */
	int 		(*pCompare)(void *, void * )
)
{
	size_t		i;
	size_t		j;
	size_t		h;
	int			rc;
	uint8_t		*WrkPtr1;
	uint8_t		*WrkPtr2;
	void		*pBaseSave;

	/* Validate input parameters.
	 */
	if( (pBase == NULL) || (pCompare == NULL) )
		return;
	if( Num <= 0 )
		return;

	/* Sort the array.
	 */
	for( h=1; h<=(Num/9); h=(3*h)+1 )
		;
	for( ; h>0; h/= 3 ) {
		for( i=h+1; i<=Num; ++i ) {
			j = i - h;
			while( j > 0 ) {
				WrkPtr1 = (uint8_t *)pBase[j-1];
				WrkPtr2 = (uint8_t *)pBase[j+h-1];
				rc = (*pCompare)( (void *)WrkPtr1, (void *)WrkPtr2 );
				if( rc > 0 ) {
					pBaseSave    = pBase[j-1];
					pBase[j-1]   = pBase[j+h-1];
					pBase[j+h-1] = pBaseSave;
					j -= h;
				}
				else
					j = 0;
			}
		}
	}

	/* Return to caller.
	 */
}











#ifdef	TEST_PROG
/**********************************************************
				  T E S T	P R O G R A M
 **********************************************************/

#include	<signal.h>

/* Other variables */
int 		Tbl1[8] = { 25, 57, 48, 37, 12, 92, 86, 33 };
int 		N12 = 12;
int 		N25 = 25;
int 		N33 = 33;
int 		N37 = 37;
int 		N48 = 48;
int 		N57 = 57;
int 		N86 = 86;
int 		N92 = 92;
int 		ntm = 15;
int 		*Tbl2[8] = { &N25, &N57, &N48, &N37, &N12, &N92, &N86, &N33 };
BOOL		trace = FALSE;



void ctrlc_handler(
	int 	x
)
{
	printf( "Aborted...\n" );
	exit( 1 );
}



int IntCompare(
	void	*I1,
	void	*I2
)
{
	return( *(int *)I1 - *(int *)I2 );
}



int 	main(
	int 	argc,
	char	**argv
)
{
	int 		i;
	int 		Num;
	char		c;
	char		*cp;
	BOOL		itf;

	/* Do initialization.
	 */
	if( signal( SIGINT, ctrlc_handler ) == SIG_ERR ) {
		fprintf( stderr, "FATAL - Couldn't set up Ctrl+C Handler...\n" );
		exit( 1 );
	}

	/* Process the command line.
	 */
	 while( (--argc > 0) && ((*++argv)[0] == '-') ) {
	 	while( c = *++argv[0] ) {
	 		switch( tolower( c ) ) {
			case 'n':
				ntm = atoi( ++argv[0] );
				*(argv[0]+1) = '\0';
				break;
			case 't':
				trace = ~trace;
				break;
	 		default:
	 			;
	 		}
	 	}
	 }

	/* Search Table 1 for each entry.
	 */
	Num = sizeof(Tbl2)/sizeof(int *);
	printf( "Table Dump Before Sort.\n" );
	for( i=0; i<Num; ++i ) {
		printf( "\tTable(%d) = %d\n", i, *Tbl2[i] );
	}
	ShellSortPtr(
			(void **)Tbl2,
			Num,
			IntCompare
	);
	printf( "Sorted Table Dump.\n" );
	for( i=0; i<Num; ++i ) {
		printf( "\tTable(%d) = %d\n", i, *Tbl2[i] );
	}

	/* Return to caller.
	 */
	return( 0 );
}


#endif
