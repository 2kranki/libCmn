/*
 *	Generated 06/05/2017 21:57:10
 */





// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      TINYTEST_ASSERT(condition)
//      TINYTEST_ASSERT_MSG(condition,msg)
//      TINYTEST_EQUAL(expected, actual)
//      TINYTEST_EQUAL_MSG(expected, actual, msg)
//      TINYTEST_FALSE_MSG(condition,msg)
//      TINYTEST_FALSE(condition)
//      TINYTEST_TRUE_MSG(pointer,msg)
//      TINYTEST_TRUE(condition)





#include    <tinytest.h>
#include    <cmn_defs.h>
#include    <trace.h>
#include    <csv_internal.h>



int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int         tearDown(
    const
    char        *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    
    trace_SharedReset( ); 
    if (mem_Dump( ) ) {
        fprintf(
                stderr,
                "\x1b[1m"
                "\x1b[31m"
                "ERROR: "
                "\x1b[0m"
                "Leaked memory areas were found!\n"
        );
        exitCode = 4;
        return 0;
    }
    mem_Release( );
    
    return 1; 
}






int         test_csv_OpenClose(
    const
    char        *pTestName
)
{
    CSV_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = csv_Alloc(0);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = csv_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_csv);
  TINYTEST_ADD_TEST(test_csv_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_csv);




#ifdef  TEST_PROG
#include    <clo.h>
#include    <signal.h>

#define num_fld     6
#define num_rcd     5

/* Other variables */
int         ntm = num_rcd;
int         ntn = 0;

CSV_FIELD   nt[num_fld] = {
	/* 1234567890 */
	{ "Character", 'C', 10, 0 },
	{ "Character", 'C', 10, 0 },
	{ "Date", 'D', 8, 0 },
	{ "Logical", 'L', 1, 0 },
	{ "Memo", 'M', 10, 0 },
	{ "Numeric", 'N', 10, 2 }
};

#pragma pack(4)
struct  rcd {
	char    chr1[11];
	char    chr2[11];
	long    date;
	short   logical;
	long    memo;
	double  number;
} rcd1;
#pragma pack()


#pragma     argsused
void CDECL      ctrlc_handler(
                              int             x
                              )
{
	printf( "Aborted...\n" );
	exit( 1 );
}




void            main(
                     int             ArgC,
                     char            **ArgV
                     )
{
	csv_CBP         cbp;
	CLO_CBP         CloCbp;
	int             i;
	short           align = 4;
	char            c;
	bool            deltst = false;
	bool            fixed = false;
	bool            trace = false;
	ERESULT          rc;
    
	/* Do initialization.
	 */
	if( signal( SIGINT, ctrlc_handler ) == SIG_ERR ) {
		fprintf( stderr, "FATAL - Couldn't set up Ctrl+C Handler...\n" );
		exit( 1 );
	}
    
	/* Process the command line.
	 */
	CloCbp = CLO_Open( ArgC, ArgV, NULL );
	while( CloCbp && CLO_IsMoreSwitches(CloCbp) ) {
		if( CLO_IsSwitch( CloCbp, 'd' ) )
			deltst = ~deltst;
		if( CLO_IsSwitch( CloCbp, 'f' ) )
			fixed = ~fixed;
		if( CLO_IsNumberSwitch( CloCbp, 'n', &i ) )
			ntm = i;
		if( CLO_IsSwitch( CloCbp, 't' ) )
			trace = ~trace;
    }
	if( CloCbp )
		CloCbp = CLO_Close( CloCbp );
    
	/* Create a file.
	 */
	printf( "Creating the initial %s file.\n",
           (fixed ? "fixed" : "variable")
           );
	rc = csv_Create(
                    "test.clf",
                    (uint16_t)(fixed ? 32 : 0),
                    0,
                    false,
                    num_fld,
                    align,
                    nt,
                    &cbp
                    );
	if( rc ) {
		printf( "Error - Create failed - %d\n", rc );
		exit( 1 );
	}
	for( i = 0; i < ntm; i++ ) {
		/* Create the record fields from the record number.
		 */
		sprintf( rcd1.chr1, "Rcd %d", i + 1 );
		sprintf( rcd1.chr2, "Rcd,%d", i + 1 );
		rcd1.date = i + 1;
		if( i & 1 )
			rcd1.logical = true;
		else
			rcd1.logical = false;
		rcd1.memo = i + 1;
		rcd1.number = i + 1;
		/* Write the record.
		 */
		rc = csv_Write( cbp, (short)(i+1), &rcd1 );
		if( rc ) {
			printf( "Error - Writing %d  #%d\n", i, rc );
			break;
		}
		printf( "...Wrote %d\n", i );
	}
	rc = csv_Close( &cbp );
	if( rc ) {
		printf( "Error - Close failed - %d\n", rc );
		exit( 1 );
	}
	printf( "...%d records were written.\n", ntm );
    
    
	/* Read the file back in.
	 */
	printf( "Reading the initial file.\n" );
	rc = csv_Open(
                  "test.clf",
                  (uint16_t)(fixed ? 32 : 0),
                  0,
                  false,
                  num_fld,
                  align,
                  nt,
                  &cbp
                  );
	if( rc ) {
		printf( "Error - Open failed - %d\n", rc );
		exit( 1 );
	}
	for( i=0; ; ++i ) {
		/* Read a record.
		 */
		rc = csv_Read( cbp, (short)(i+1), &rcd1 );
		if( rc ) {
			if( rc == csv_ERROR_EOF )
				break;
			printf( "Read Error #%d\n", rc );
			break;
		}
		/* Display the record.
		 */
		printf( "...Read %d  ", i );
		printf( "chr1=%s  chr2=%s  date=%ld  logical=%d  memo=%ld  num=%lf\n",
               rcd1.chr1,
               rcd1.chr2,
               rcd1.date,
               rcd1.logical,
               rcd1.memo,
               rcd1.number
               );
	}
	rc = csv_Close( &cbp );
	if( rc ) {
		printf( "Error - Close failed - %d\n", rc );
		exit( 1 );
	}
	printf( "...%d records were read.\n", i );
    
    
	/* Now append records to the end of the file if stream.
	 */
	if( fixed )
		;
	else {
		printf( "Appending to the initial file.\n" );
		rc = csv_Open(
                      "test.clf",
                      (uint16_t)(fixed ? 32 : 0),
                      0,
                      false,
                      num_fld,
                      align,
                      nt,
                      &cbp
                      );
		if( rc ) {
			printf( "Error - Open failed - %d\n", rc );
			exit( 1 );
		}
		/* Read till end of file.
		 */
		for( ;; ) {
			/* Write the record.
			 */
			rc = csv_Read( cbp, (short)(i+1), &rcd1 );
			if( rc ) {
				if( rc == csv_ERROR_EOF )
					break;
				printf( "Read Error #%d\n", rc );
				break;
			}
			printf( "...Read %d  ", i );
			printf( "\n" );
		}
		/* Add more records.
		 */
		for( i = 0; i < ntm; i++ ) {
			/* Create the record fields from the record number.
			 */
			sprintf( rcd1.chr1, "Rcd %d", i + 10 );
			sprintf( rcd1.chr2, "Rcd,%d", i + 10 );
			rcd1.date = i + 10;
			if( i & 1 )
				rcd1.logical = true;
			else
				rcd1.logical = false;
			rcd1.memo = i + 10;
			rcd1.number = i + 10;
			/* Write the record.
			 */
			rc = csv_Write( cbp, (short)(i+10), &rcd1 );
			if( rc ) {
				printf( "Error - Writing %d  #%d\n", i+10, rc );
				break;
			}
			printf( "...Wrote %d\n", i+10 );
		}
		rc = csv_Close( &cbp );
		if( rc ) {
			printf( "Error - Close failed - %d\n", rc );
			exit( 1 );
		}
	}
    
    
	/* Read the file back in again.
	 */
	printf( "Reading the file again.\n" );
	rc = csv_Open(
                  "test.clf",
                  (uint16_t)(fixed ? 32 : 0),
                  0,
                  false,
                  num_fld,
                  align,
                  nt,
                  &cbp
                  );
	if( rc ) {
		printf( "Error - Open failed - %d\n", rc );
		exit( 1 );
	}
	for( i=0; ; ++i ) {
		/* Read a record.
		 */
		rc = csv_Read( cbp, (short)(i+1), &rcd1 );
		if( rc ) {
			if( rc == csv_ERROR_EOF )
				break;
			printf( "Read Error #%d\n", rc );
			break;
		}
		/* Display the record.
		 */
		printf( "...Read %d  ", i );
		printf( "chr1=%s  chr2=%s  date=%ld  logical=%d  memo=%ld  num=%lf\n",
               rcd1.chr1, rcd1.chr2, rcd1.date,
               rcd1.logical, rcd1.memo, rcd1.number );
	}
	rc = csv_Close( &cbp );
	if( rc ) {
		printf( "Error - Close failed - %d\n", rc );
		exit( 1 );
	}
	printf( "...%d records were read.\n", i );
    
    
	/* Return to caller.
	 */
	MEM_Dump( );
}


#endif




