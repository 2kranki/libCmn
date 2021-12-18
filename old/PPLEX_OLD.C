// vi:nu:et:sts=4 ts=4 sw=4

/*			PPLex - ANSI C/C++ Preprocessor Lexical Analyzer Routines
 *Purpose:
 *			This program analyzes the input stream converting it
 *			into tokens which are used by the preprocessor and
 *			compiler.  The lexical tokens are as defined by the
 *			Ansi C/C++ definition.	The source input is provided
 *			by the Common Source Input Routines.
 *Input:
 *Output:
 *Outline:
 *History:
 *Remarks:
 */



/****************************************************************
 * * * * * * * * * * *	Common Definitions	* * * * * * * * * * *
 ****************************************************************/

/*	* * *  Common Definitions  * * *	*/
#define		PPLEX
#include	"cc.h"
#include	"cmnsrc.h"
#include	"ccprs.h"			/* Parse Terminal Definitions */
#include	"pplex.h"			/* PreProcessor Lexical Analyzer Definitions */



/****************************************************************
 * * * * * * * * * * * *  Scanner Variables	* * * * * * * * * * *
 ****************************************************************/


#if 	YYDEBUG
LOCAL int	yydebug = 0;
LOCAL int	yydebugsrc = 0;
#endif


/*
 *			* * Current Token Variables * *
 * These variables are public and are the means of getting
 * information about the token just scanned.
 */
static char		tokstr[256];	/* token string */
static char		*yytext;
static int		yyleng = 0;
LOCAL SRC_CharP	CurChr;
LEX_Token		CurTok;


/*	* * * Character Class Table * * *
 */
LOCAL int chrcls[128] = {
	1,1,1,1,1,1,1,1,1,
	2,								/* Horizontal Tab */
	2,								/* Line Feed */
	2,								/* Vertical Tab */
	2,								/* Form Feed */
	2,								/* Carriage Return */
	1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,
	1,1,
	2,								/* space */
	3,								/* ! */
	4,								/* " */
	5,								/* # */
	6,								/* $ */
	7,								/* % */
	8,								/* & */
	9,								/* ' */
	10,								/* ( */
	11,								/* ) */
	12,								/* * */
	13,								/* + */
	14,								/* , */
	15,								/* - */
	16,								/* . */
	17,								/* / */
	18,18,18,18,18,18,18,18,18,18,	/* 0-9 */
	19,								/* : */
	20,								/* ; */
	21,								/* < */
	22,								/* = */
	23,								/* > */
	24,								/* ? */
	25,								/* @ */
	26,26,26,26,26,26,26,26,26,26,	/* A-Z */
	26,26,26,26,26,26,26,26,26,26,
	26,26,26,26,26,26,
	27,								/* [ */
	28,								/* \ */
	29,								/* ] */
	30,								/* ^ */
	31,								/* _ */
	32,								/* ` */
	26,26,26,26,26,26,26,26,26,26,	/* a-z */
	26,26,26,26,26,26,26,26,26,26,
	26,26,26,26,26,26,
	33,								/* { */
	34,								/* | */
	35,								/* } */
	36,								/* ~ */
	37								/* del (used for EOF) */
};



/*	* * * Ansi C Key Word Table * * *
 */
LOCAL struct C_Key_Word {
	int 	value;					/* Lexical Scan Value */
	char	*kwd;					/* Key Word */
} C_KwdTbl[40] = {
	{ KWD_ASM, "_asm" },
	{ KWD_CDECL, "_cdecl" },
	{ KWD_EMIT, "_emit" },
	{ KWD_ENTRY, "_entry" },
	{ KWD_FAR, "_far" },
	{ KWD_FORTRAN, "_fortran" },
	{ KWD_NEAR, "_near" },
	{ KWD_PASCAL, "_pascal" },
	{ KWD_AUTO, "auto" },
	{ KWD_BREAK, "break" },
	{ KWD_CASE, "case" },
	{ KWD_CHAR, "char" },
	{ KWD_CONST, "const" },
	{ KWD_CONTINUE, "continue" },
	{ KWD_DEFAULT, "default" },
	{ KWD_DO, "do" },
	{ KWD_DOUBLE, "double" },
	{ KWD_ELSE, "else" },
	{ KWD_ENUM, "enum" },
	{ KWD_EXTERN, "extern" },
	{ KWD_FLOAT, "float" },
	{ KWD_FOR, "for" },
	{ KWD_GOTO, "goto" },
	{ KWD_IF, "if" },
	{ KWD_INT, "int" },
	{ KWD_LONG, "long" },
	{ KWD_REGISTER, "register" },
	{ KWD_RETURN, "return" },
	{ KWD_SHORT, "short" },
	{ KWD_SIGNED, "signed" },
	{ KWD_SIZEOF, "sizeof" },
	{ KWD_STATIC, "static" },
	{ KWD_STRUCT, "struct" },
	{ KWD_SWITCH, "switch" },
	{ KWD_TYPEDEF, "typedef" },
	{ KWD_UNION, "union" },
	{ KWD_UNSIGNED, "unsigned" },
	{ KWD_VOID, "void" },
	{ KWD_VOLATILE, "volatile" },
	{ KWD_WHILE, "while" }
};





LOCAL int		C_KwdCmp(
	struct C_Key_Word *ent1,
	struct C_Key_Word *ent2
);
LOCAL void		PPGetChar(
	void
);
LOCAL BOOL		yyconchr(
	int 			*num
);
LOCAL BOOL		yyhexchr(
	int 			*num
);
LOCAL BOOL		yyoctchr(
	int 			*num
);







/*****************************************************************
 * * * * * * * * * *  Internal Procedures  * * * * * * * * * * * *
 *****************************************************************/


/*>>>>>>>>>>>>>>>  Compare Key Words  <<<<<<<<<<<<<<<<<<
 * This routine is responsible for comparing an identifer to
 * a key word table entry.
 */

LOCAL int		C_KwdCmp(
	struct C_Key_Word *ent1,
	struct C_Key_Word *ent2
)
{
	REG int			i;

	i = strcmp( ent1->kwd, ent2->kwd );
	return( i );
}





/****************************************************************
 * PPGetTri - Get the next character with preprocessing 		*
 ****************************************************************/

/* This routine is responsible for removing comments, consolidating
 * tri-graphs and providing continued lines.  Comments are allowed
 * to be nested and are passed upwards as one blank.  Tri-graphs are
 * consolidated into the character that they represent.	Continued
 * lines are passed as if the line-end did not occur.
 */

LOCAL void		PPGetChar(
	void
)
{
	REG int			i;
	LOCAL SRC_Char	BgnChr;
	LOCAL SRC_Char	SavChr;
	SRC_CharP		WrkChr;

	/* Set up the next character.
	 */
NxtChr:
	WrkChr = SRC_GetChar( );
	BgnChr = *WrkChr;
	CurChr = &BgnChr;

	/* Scan off the next token.
	 */
	switch( WrkChr->Cls ) {
	case 2 :						/*** WhiteSpace ***/
		if( BgnChr.Chr == '\n' )
			break;
		BgnChr.Chr = ' ';
		do {
			WrkChr = SRC_GetChar( );
		} while( (WrkChr->Cls == 2) && (WrkChr->Chr != '\n') );
		SRC_UnGetChar( WrkChr );
		break;
	case 17 :		/*** '/' ***/
		WrkChr = SRC_GetChar( );
		if( WrkChr->Cls == 17 ) {	/***Comment***/
			do {
				WrkChr = SRC_GetChar( );
			} while( (WrkChr->Chr != '\n') );
			BgnChr.Chr = '\n';
			BgnChr.Cls = 2;
		}
		if( WrkChr->Cls == 12 ) {	/***Comment***/
			WrkChr = SRC_GetChar( );
			for( i=1; i; ) {
				while( WrkChr->Cls!=12 && WrkChr->Cls!=17 && WrkChr->Cls!=37 ) {
					WrkChr = SRC_GetChar( );
				}
				if( WrkChr->Cls == 17 ) {
					WrkChr = SRC_GetChar( );
					if( WrkChr->Cls == 12 ) {
						++i;
						WrkChr = SRC_GetChar( );
					}
					continue;
				}
				WrkChr = SRC_GetChar( );
				if( WrkChr->Cls==17 || WrkChr->Cls==37 ) {
					WrkChr = SRC_GetChar( );
					--i;
				}
			}
			BgnChr.Chr = ' ';
			BgnChr.Cls = 2;
		}
		else {
			SRC_UnGetChar( WrkChr );
		}
		break;
	case 24 :						/*** '?' ***/
		WrkChr = SRC_GetChar( );
		if( WrkChr->Chr == '?' ) {
			SavChr = *WrkChr;
			WrkChr = SRC_GetChar( );
			if( WrkChr->Chr == '(' ) {
				BgnChr.Chr = '[';
				BgnChr.Cls = 27;
			}
			else if( WrkChr->Chr == '/' ) {
				BgnChr.Chr = '\\';
				BgnChr.Cls = 28;
				WrkChr = SRC_GetChar( );
				if( WrkChr->Chr == '\n' )
					goto NxtChr;
				else {
					SRC_UnGetChar( WrkChr );
				}
			}
			else if( WrkChr->Chr == ')' ) {
				BgnChr.Chr = ']';
				BgnChr.Cls = 29;
			}
			else if( WrkChr->Chr == '\'' ) {
				BgnChr.Chr = '^';
				BgnChr.Cls = 30;
			}
			else if( WrkChr->Chr == '<' ) {
				BgnChr.Chr = '{';
				BgnChr.Cls = 33;
			}
			else if( WrkChr->Chr == '!' ) {
				BgnChr.Chr = '|';
				BgnChr.Cls = 34;
			}
			else if( WrkChr->Chr == '>' ) {
				BgnChr.Chr = '}';
				BgnChr.Cls = 35;
			}
			else if( WrkChr->Chr == '-' ) {
				BgnChr.Chr = '~';
				BgnChr.Cls = 36;
			}
			else if( WrkChr->Chr == '=' ) {
				BgnChr.Chr = '#';
				BgnChr.Cls = 5;
			}
			else {
//				yyerror( "Invalid Trigraph Sequence\n" );
				SRC_UnGetChar( WrkChr );
				SRC_UnGetChar( &SavChr );
			}
		}
		else {
			SRC_UnGetChar( WrkChr );
		}
		break;
	case 28 :		/*** '\' ***/
		WrkChr = SRC_GetChar( );
		if( WrkChr->Chr == '\n' )
			goto NxtChr;
		else {
			SRC_UnGetChar( WrkChr );
		}
		break;
	default:
		break;
	}

	/* Return to caller.
	 */
#if 	YYDEBUG
	if( yydebugsrc ) {
		if( CurChr->Chr == 127 )
			printf( "PPGetChar:  EOF  " );
		else if( (CurChr->Chr >= ' ') && (CurChr->Chr < 127) )
			printf( "PPGetChar:  c='%c'/%02x  cls=%d  ", CurChr->Chr,
					CurChr->Chr, CurChr->Cls );
		else
			printf( "PPGetChar:  c=%02x  cls=%d  ", CurChr->Chr,
					CurChr->Cls );
		printf( "lin = %d  col = %d\n", CurChr->LineNo, CurChr->ColNo );
	}
#endif
}





/*>>>>>>>>>>>>>>>  Get a Constant Character	 <<<<<<<<<<<<<<<<<<
 * This routine is responsible for getting the next character
 * for a constant, either single-byte or multi-byte.
 */

LOCAL BOOL		yyconchr(
	int 			*num
)
{
	REG int			i;
	REG int			c;
	REG BOOL		rc = FALSE;
	static int		state = 0;		/* State Machine
									 * 0 = Regular Character
									 * 1 = After 1st Character in
									 *		multi-byte hexadecimal
									 *		sequence
									 */
	/* Handle the state machine.
	 */
	switch( state ) {
	case	0:
next_byte:
		if( CurChr->Chr == '\\' ) {
			PPGetChar( );
			switch( CurChr->Chr ) {
			case	'a':		/*** Alert ***/
				*num = 0x07;
				break;
			case	'b':		/*** Backspace ***/
				*num = 0x08;
				break;
			case	'f':		/*** Form Feed ***/
				*num = 0x0C;
				break;
			case	'n':		/*** Newline ***/
				*num = 0x0A;
				break;
			case	'r':		/*** Carriage Return ***/
				*num = 0x0D;
				break;
			case	't':		/*** Horizontal Tab ***/
				*num = 0x09;
				break;
			case	'v':		/*** Vertical Tab ***/
				*num = 0x0B;
				break;
			case	'x':		/*** Hexadecimal Character ***/
				PPGetChar( );
				if( yyhexchr( num ) ) {
					state = 1;
					return( TRUE );
				}
				else {
					state = 0;
//					yyerror( "Expected Hexadecimal Character Escape Sequence\n" );
					return( FALSE );
				}
				break;
			case	'\n':		/*** New Line ***/
				PPGetChar( );
				goto next_byte;
				break;
			case	'\\':		/*** Backslash ***/
			case	'\'':		/*** Single Quote ***/
			case	'\"':		/*** Double Quote ***/
			case	'?':		/*** Question Mark ***/
				*num = CurChr->Chr;
				break;
			case	'0':		/*** Octal Number ***/
			case	'1':
			case	'2':
			case	'3':
			case	'4':
			case	'5':
			case	'6':
			case	'7':
				if( yyoctchr( num ) ) {
					return( TRUE );
				}
				else {
					return( FALSE );
				}
				break;
			}
		}
		else if( (CurChr->Chr == '\"') || (CurChr->Chr == '\n') ) {
			return( rc );
		}
		else {
			*num = CurChr->Chr;
			PPGetChar( );
		}
		rc = TRUE;
	case	1:
		if( yyhexchr( num ) ) {
			state = 1;
			return( TRUE );
		}
		else {
			state = 0;
			return( FALSE );
		}
	}

	/* Return to caller.
	 */
	return( rc );
}





/*>>>>>>>>>>>>>>>  Get a Hexadecimal Character	 <<<<<<<<<<<<<<<<<<
 * This routine is responsible for getting the next hexadecimal character
 * for a constant, either single-byte or multi-byte.
 */

LOCAL BOOL		yyhexchr(
	int 			*num
)
{
	REG int			i;
	REG BOOL		rc = FALSE;

	if( (CurChr->Chr >= '0') && (CurChr->Chr <= '9') ) {
		i = CurChr->Chr - '0';
		rc = TRUE;
	}
	else if( ((CurChr->Chr >= 'a') && (CurChr->Chr <= 'f'))
		 ||  ((CurChr->Chr >= 'A') && (CurChr->Chr <= 'F')) ) {
		i = CurChr->Chr - 'A' + 10;
		rc = TRUE;
	}
	else {
		SRC_UnGetChar( CurChr );
		goto no_more;
	}
	PPGetChar( );
	if( (CurChr->Chr >= '0') && (CurChr->Chr <= '9') ) {
		i <<= 4;
		i += CurChr->Chr - '0';
//		rc = TRUE;
	}
	else if( ((CurChr->Chr >= 'a') && (CurChr->Chr <= 'f'))
		 ||  ((CurChr->Chr >= 'A') && (CurChr->Chr <= 'F')) ) {
		i <<= 4;
		i += CurChr->Chr - 'A' + 10;
//		rc = TRUE;
	}
	else {
		SRC_UnGetChar( CurChr );
		goto no_more;
	}
no_more:
	;

	/* Return to caller.
	 */
	*num = i;
	return( rc );
}





/*>>>>>>>>>>>>>>>  Get an Octal Character	 <<<<<<<<<<<<<<<<<<
 * This routine is responsible for getting the next octal character
 * for a constant, either single-byte or multi-byte.
 */

LOCAL BOOL		yyoctchr(
	int 			*num
)
{
	REG int			i;
	REG BOOL		rc = FALSE;

	i = 0;
	if( (CurChr->Chr >= '0') && (CurChr->Chr <= '7') ) {
		i += CurChr->Chr - '0';
		rc = TRUE;
	}
	else {
		SRC_UnGetChar( CurChr );
		goto no_more;
	}
	PPGetChar( );
	if( (CurChr->Chr >= '0') && (CurChr->Chr <= '7') ) {
		i <<= 3;
		i += CurChr->Chr - '0';
//		rc = TRUE;
	}
	else {
		SRC_UnGetChar( CurChr );
		goto no_more;
	}
	PPGetChar( );
	if( (CurChr->Chr >= '0') && (CurChr->Chr <= '7') ) {
		i <<= 3;
		i += CurChr->Chr - '0';
//		rc = TRUE;
	}
	else {
		SRC_UnGetChar( CurChr );
		goto no_more;
	}
no_more:
	;

	/* Return to caller.
	 */
	*num = i;
	return( rc );
}





/*****************************************************************
 * * * * * * * * * *  External Procedures  * * * * * * * * * * * *
 *****************************************************************/


/*>>>>>>>>>>>>>>>  Shut Down PPLex()	 <<<<<<<<<<<<<<<<<<
 * This routine is responsible for closing down PPLex() so that it
 * can be used for multiple files no matter what the prior scanning
 * was like.
 */

void		PPClose(
	void
)
{
	REG int			i;

	/* Close the source files.
	 */
	SRC_CloseFile( );
	SRC_Close( );

	/* Return to caller.
	 */
}









/*>>>>>>>>>>>>>>>>>>>>	 Get the Next Token  <<<<<<<<<<<<<<<<<<
 *This routine is responsible for getting the next token from
 *the source file.
 */

int			PPLex(
	void
)
{
	REG int		i;
	REG int		lltype;
	int 		ColNo;
	struct C_Key_Word *kwe;
	struct C_Key_Word dum;
	int 		num;


	/* Loop until we have a token.
	 */
	for(;;) {

		/* Read first character for next token and start it.
		 */
		PPGetChar( );
		CurTok.FileNo = CurChr->FileNo;
		CurTok.LineNo = CurChr->LineNo;
		CurTok.ColNo  = CurChr->ColNo;
		CurTok.Val.Text	= tokstr;
		yytext = tokstr;
		tokstr[0] = CurChr->Chr;	/* Data */
		tokstr[1] = '\0';

		/* Scan off the next token.
		 */
		lltype = CurChr->Chr;
		switch( CurChr->Cls ) {
		case 2 :					/*** WhiteSpace ***/
			do {
				PPGetChar( );
			} while( CurChr->Cls == 2 );
			SRC_UnGetChar( CurChr );
			break;
		case 3 :					/*** '!' ***/
			PPGetChar( );
			if( CurChr->Chr == '=' ) {
				lltype = NE_OP;
				PPGetChar( );
				break;
			}
			else
				SRC_UnGetChar( CurChr );
			break;
		case 4 :					/*** '"' ***/
			lltype = STRING_LITERAL;
			i = 0;
			PPGetChar( );
			while( yyconchr( &num ) ) {
				if( i < sizeof(tokstr) ) {
					yytext[i++] = (char)num;
				}
				yytext[i] = '\0';
			}
			PPGetChar( );
			if( CurChr->Chr == '"' )
				break;
			else {
//				yyerror( "String Literal not terminated properly" );
			}
			break;
		case 5 :					/*** '#' ***/
			break;
		case 7 :					/*** '%' ***/
			PPGetChar( );
			if( CurChr->Chr == '=' ) {
				lltype = MOD_ASSIGN;
				break;
			}
			else
				SRC_UnGetChar( CurChr );
			break;
		case 8 :					/*** '&' ***/
			PPGetChar( );
			if( CurChr->Chr == '&' ) {
				lltype = AND_OP;
				PPGetChar( );
				break;
			}
			else if( CurChr->Chr == '=' ) {
				lltype = AND_ASSIGN;
				PPGetChar( );
				break;
			}
			else
				SRC_UnGetChar( CurChr );
			break;
		case 9 :					/*** '''' ***/
			lltype = CONSTANT;
			i = 0;
			for(;;) {
				yytext[i] = '\0';
				PPGetChar( );
				if( CurChr->Cls == 9 ) {
					PPGetChar( );
					if( CurChr->Cls == 9 )
						;
					else {
						break;
					}
				}
				if( i<sizeof(tokstr) ) {
					yytext[i++] = CurChr->Chr;
				}
			}
			break;
		case 10 :					/*** '(' ***/
		case 11 :					/*** ')' ***/
			break;
		case 12 :					/*** '*' ***/
			PPGetChar( );
			if( CurChr->Chr == '=' ) {
				lltype = MUL_ASSIGN;
				break;
			}
			else
				SRC_UnGetChar( CurChr );
			break;
		case 13 :					/*** '+' ***/
			PPGetChar( );
			if( CurChr->Chr == '+' ) {
				lltype = INC_OP;
				break;
			}
			else if( CurChr->Chr == '=' ) {
				lltype = ADD_ASSIGN;
				break;
			}
			else
				SRC_UnGetChar( CurChr );
			break;
		case 14 :					/*** ',' ***/
			break;
		case 15 :					/*** '-' ***/
			PPGetChar( );
			if( CurChr->Chr == '>' ) {
				lltype = PTR_OP;
				break;
			}
			else if( CurChr->Chr == '-' ) {
				lltype = DEC_OP;
				break;
			}
			else if( CurChr->Chr == '=' ) {
				lltype = SUB_ASSIGN;
				PPGetChar( );
				break;
			}
			else
				SRC_UnGetChar( CurChr );
			break;
		case 16 :					/*** '.' ***/
			PPGetChar( );
			if( CurChr->Chr == '.' ) {
				lltype = RANGE;
				PPGetChar( );
				if( CurChr->Chr == '.' ) {
					lltype = ELIPSIS;
					break;
				}
				else
					SRC_UnGetChar( CurChr );
				break;
			}
			else
				SRC_UnGetChar( CurChr );
			break;
		case 17 :					/*** '/' ***/
			PPGetChar( );
			if( CurChr->Cls == 12 ) {	/***Comment***/
#if 	YYDEBUG
				if( yydebug )
					printf( "pplex:  comment begin lvl=1\n" );
#endif
				PPGetChar( );
				for( i=1; i; ) {
					while( CurChr->Cls!=12 && CurChr->Cls!=17 && CurChr->Cls!=37 ) {
						PPGetChar( );
					}
					if( CurChr->Cls == 17 ) {
						PPGetChar( );
						if( CurChr->Cls == 12 ) {
							++i;
#if 	YYDEBUG
							if( yydebug )
								printf( "pplex:  comment begin lvl=%d\n", i );
#endif
							PPGetChar( );
						}
						continue;
					}
					PPGetChar( );
					if( CurChr->Cls==17 || CurChr->Cls==37 ) {
#if 	YYDEBUG
						if( yydebug )
							printf( "pplex:  comment end lvl=%d\n", i );
#endif
						PPGetChar( );
						--i;
					}
				}
				continue;
			}
			else if( CurChr->Chr == '=' ) {
				lltype = DIV_ASSIGN;
				break;
			}
			else
				SRC_UnGetChar( CurChr );
			break;
		case 18 :					/*** '0'-'9' ***/
			lltype = CONSTANT;
			i = 1;
			for(;;) {
				yytext[i] = '\0';
				PPGetChar( );
				if( CurChr->Cls==18 )
					;
				else {
					SRC_UnGetChar( CurChr );
					break;
				}
				if( i < sizeof(tokstr) ) {
					yytext[i++] = CurChr->Chr;
				}
			}
			break;
		case 19 :					/*** ':' ***/
			break;
		case 20 :					/*** ';' ***/
			break;
		case 21 :					/*** '<' ***/
			PPGetChar( );
			if( CurChr->Chr == '<' ) {
				lltype = LEFT_OP;
				PPGetChar( );
				if( CurChr->Chr == '=' ) {
					lltype = LEFT_ASSIGN;
				}
				else
					SRC_UnGetChar( CurChr );
				break;
			}
			else if( CurChr->Chr == '=' ) {
				lltype = LE_OP;
				break;
			}
			else
				SRC_UnGetChar( CurChr );
			break;
		case 22 :					/*** '=' ***/
			PPGetChar( );
			if( CurChr->Chr == '=' ) {
				lltype = EQ_OP;
				break;
			}
			else
				SRC_UnGetChar( CurChr );
			break;
		case 23 :					/*** '>' ***/
			PPGetChar( );
			if( CurChr->Chr == '>' ) {
				lltype = RIGHT_OP;
				PPGetChar( );
				if( CurChr->Chr == '=' ) {
					lltype = RIGHT_ASSIGN;
				}
				else
					SRC_UnGetChar( CurChr );
				break;
			}
			else if( CurChr->Chr == '=' ) {
				lltype = GE_OP;
				break;
			}
			else
				SRC_UnGetChar( CurChr );
			break;
		case 24 :					/*** '?' ***/
			PPGetChar( );
			if( CurChr->Chr == '=' ) {
				lltype = GE_OP;
				break;
			}
			else {
				SRC_UnGetChar( CurChr );
			}
			break;
		case 26 :					/*** 'A'-'Z' and 'a'-'z' ***/
		case 31 :					/*** '_' ***/
			lltype = IDENTIFIER;
			i = 1;
			for(;;) {
				yytext[i] = '\0';
				PPGetChar( );
				if( (CurChr->Cls == 18) || (CurChr->Cls == 26) ||
					(CurChr->Cls == 31) )
					;
				else {
					SRC_UnGetChar( CurChr );
					break;
				}
				if( i<sizeof(tokstr) ) {
					yytext[i++] = CurChr->Chr;
				}
			}
			dum.kwd = yytext;
			kwe = (struct C_Key_Word *)bsearch(
						&dum,
						C_KwdTbl,
						sizeof(C_KwdTbl)/sizeof(struct C_Key_Word),
						sizeof(struct C_Key_Word),
						C_KwdCmp
					);
			if( kwe )
				lltype = kwe->value;
			break;
		case 27 :					/*** '[' ***/
		case 29 :					/*** ']' ***/
			break;
		case 30 :					/*** '^' ***/
			PPGetChar( );
			if( CurChr->Chr == '=' ) {
				lltype = XOR_ASSIGN;
				break;
			}
			else
				SRC_UnGetChar( CurChr );
			break;
		case 33 :					/*** '{' ***/
			break;
		case 34 :					/*** '|' ***/
			PPGetChar( );
			if( CurChr->Chr == '|' ) {
				lltype = OR_OP;
				break;
			}
			else if( CurChr->Chr == '=' ) {
				lltype = OR_ASSIGN;
				break;
			}
			else
				SRC_UnGetChar( CurChr );
			break;
		case 35 :					/*** '}' ***/
			break;
		case 37 :					/*** eof ***/
			lltype = 0;
			yytext[0] = '\0';
			break;
		default:
			printf( "char = %c 0x%02X\n", CurChr->Chr, CurChr->Chr );
			yyerror( "Invalid Character" );
			continue;
		}

		/* Return Token to caller.
		 */
		break;

	/* End of FOR Loop
	 */
	}
	yyleng = strlen( yytext );
	CurTok.Type = lltype;

	/* Return to caller.
	 */
#if 	YYDEBUG
	if( yydebug ) {
		printf( "PPLex: pos=(%d,%d,%d)  len=%d  type=%d  token=%s\n",
				CurTok.FileNo, CurTok.LineNo, CurTok.ColNo,
				yyleng,
				CurTok.Type,
				yytext
		);
	}
#endif
	return( lltype );
}



/********************************************************************/
/*			PPOpen - Initialize the Preprocessor Lexical Analyzer	*/
/********************************************************************/
/* This routine is responsible for initializing yylex() so that it
 * can be used for multiple files no matter what the prior scanning
 * was like.
 */

void		PPOpen(
	char		*FileName
)
{
	REG int			i;
#if 	YYDEBUG
	REG char		*yys;
#endif

	/* Set up debug mode if appropriate.
	 */
#if 	YYDEBUG
	if( yys = getenv("PPLEX_DEBUG") ) {
		if( *yys == '0' )
            yydebug = 0;
		else if( (*yys >= '1') && (*yys <= '9') )
			yydebug = *yys - '0';
    }
	if( yys = getenv("PPSRC_DEBUG") ) {
		if( *yys == '0' )
			yydebugsrc = 0;
		else if( (*yys >= '1') && (*yys <= '9') )
			yydebugsrc = *yys - '0';
    }
#endif

	/* Open the source file.
	 */
	SRC_Open( NULL, NULL, PPSetClass );
	SRC_OpenFile( FileName, 4, SRC_OPEN_TAB );

	/* Return to caller.
	 */
}




/********************************************************************/
/*			PPSetClass - Set a Character's Class                	*/
/********************************************************************/
/* This routine returns the character class for the provided character.
 */
int			PPSetClass(
	char		Chr
)
{
	REG int		i;

	/* Get the next input character.
	 */
	Chr &= 0x7F;
	if( (Chr >= 0) && (Chr < 128) )
		i = chrcls[Chr];
	else
		i = 0;

	/* Return to caller.
	 */
	return( i );
}
