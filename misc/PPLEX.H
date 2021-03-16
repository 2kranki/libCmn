// vi:nu:et:sts=4 ts=4 sw=4

/*			PPLex - ANSI C/C++ PreProcessor Lexical Analyzer Header
 *Purpose:
 *			This set of routines break up the input source file into
 *			individual tokens for processing by the preprocessor.
 *History:
 *Remarks:
 */



/****************************************************************
 * * * * * * * * * * *	Common Definitions	* * * * * * * * * * *
 ****************************************************************/

#ifndef PPLEX_H
#define PPLEX_H

/* Lexical Token Definition
 */
typedef struct	LEX_Token {
	int 	Type;				/* Token Type */
	int 	FileNo; 			/* Source Input File Number */
	int 	LineNo; 			/* Source Input Line Number */
	int 	ColNo;				/* Source Input Column Number */
	union { 					/* Source Input Value according to Type */
		char	*Text;				/* Text String */
		long	Integer;			/* Integer */
	}		Val;
}	LEX_Token;
typedef struct LEX_Token *LEX_TokenP;
#define YYSTYPE LEX_Token

#endif



/****************************************************************
 * * * * * * * * * * * *  Common Routines	* * * * * * * * * * *
 ****************************************************************/

void		PPClose(			/* Close Lexical Analyzer */
	void
);
int			PPLex(				/* Get the Next Token */
	void
);
void		PPOpen( 			/* Open Lexical Analyzer */
	char	*FileName
);
int			PPSetClass( 		/* Set Class for a Character */
	char	Chr
);
