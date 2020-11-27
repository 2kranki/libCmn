// vi:nu:et:sts=4 ts=4 sw=4

// Program
//		FClean - Clean up source file(s)
// Programmer
//		Robert M. White
// Purpose
//		FClean processes each file in sequence removing high order bits
//		and unprintable characters.  It was designed to clean up files
//		edited with Wordstar.  It processes each file by reading it a
//		character at time, cleaning the character and writing the char
//		to a temporary file.  When the file is processed, the original
//		file is deleted and the temporary one is renamed to the origin-
//		al name.
//
//		Cleaning is defined as zeroing the high order bit, allowing
//		only printable characters and insuring all lf's are prefixed
//		by a cr.
// History
//	 04/10/2001	    Updated for new IrmwApplication.
//	 05/02/2000	    Updated to utilize RmwInProc01 DLL.
//	 12/11/1995	    Updated for updated RW_Path class.
//	 12/03/1995	    Added Exception Processing from ZIPCHK.CPP.
//	 11/30/1995	    Updated for new Tracing names and Signal Processing.
//	 04/10/1995	    Added some program Tracing and updated for changes in RW_DIRR.
//	 02/01/1995	    Updated to use the new RW_DIRR pattern class.
//	 01/05/1995	    Fixed bug in how switches were scanned off.
//	 12/15/1994	    Converted to Borland C++ for Windows v4.5 and altered to use
//				    C++ Library.
//	 11/06/1992	    Added 16k buffers for the input and output files to speed
//				    file i/o up.  Changed to Large Memory Model and enlarged
//				    stack to 16k.
//	 08/20/1991	    Separated cleaning out to a defined function.  Added
//				    support for Pathnames instead of file names.
//	 06/06/1990	    Fixed to use the DIR_ routines.
//	 05/28/1990	    Added OS/2 support.
//	 12/26/1988	    Added <cr><lf> enforcement on single <lf>.
//	 11/23/1988	    Originally written and debugged.
// Todo
//  --          Add support for Q(quiet) option. 

#include		<cmd_defs.h>
#include		<appl.h>
#include		<Path.h>
#include		<conio.h>
#include		<signal.h>
#ifndef			rmwFileIoH
#	include			<rmwFileIo.h>
#endif
#ifndef			rmwMiscH
#	include			<rmwMisc.h>
#endif
#ifndef			rmwPathH
#endif
#ifndef			rmwStringH
#	include			<rmwString.h>
#endif

//#define			USE_RMWINPROC	1
#undef			USE_RMWINPROC


LOCAL
IrmwApplication	*pAppl = NULL;
LOCAL
IrmwIMallocEx	*pMalloc = NULL;
LOCAL
intu32			g_cRef = 0;				// Global Reference Count
LOCAL
IrmwPath		*pOutputFileName = NULL;
LOCAL
BOOL			fDebug = FALSE;				// DEBUG flag
LOCAL
BOOL			fQuiet = FALSE;				// True = Do not display messages
LOCAL
BOOL			fRecurse = FALSE;			// RECURSE Directories flag
LOCAL
LPWSTR			pWorkFileName = L"FCLeanWork.$$$";
LOCAL
WCHAR			CarriageReturn = L'\r';

// External Subroutine Definitions
#ifdef      __cplusplus
extern "C" {
#endif
rmwRC RMW_APIENTRY	rmwEvents_Construct(
	void			*,
	IUnknown		*
);
rmwRC RMW_APIENTRY	rmwEvents_CreateInstance(
	IUnknown		*,
	REFIID			,
	void			**
);
rmwRC RMW_APIENTRY	rmwEvents_CreationSize(
	intu32			*
);
rmwRC RMW_APIENTRY	rmwEvents_Destruct(
	void			*		
);
#ifdef      __cplusplus
};
#endif


// Internal Function Definitions
#ifdef      __cplusplus
extern "C" {
#endif
rmwRC RMW_APIENTRY	CleanAFile(
	IrmwPath		*
);
#ifdef      __cplusplus
};
#endif
LOCAL
rmwRC RMW_APIENTRY	CleanFiles(
	IrmwPath		*
);
STDAPI			DllLockServer(
	BOOL			fLock
);
LOCAL
void			ProgramHelp(
	void
);
LOCAL
rmwRC RMW_APIENTRY	ScanParms(
	int 			ArgC,
	char			*ArgV[]
);




//********************************************************
//					Clean up a File
//********************************************************

rmwRC RMW_APIENTRY	CleanAFile(
	IrmwPath		*pEntry
)
{
	rmwRC			hRc = rmwRC_OK;
	IrmwFileIo		*pFileIn = NULL;
	IrmwFileIo		*pFileOut = NULL;
	IrmwPath		*pPathOut = NULL;
	IrmwString		*pDriveName = NULL;
	IrmwString		*pDirectoryName = NULL;
	IrmwString		*pFileName = NULL;
	intu32			ActualNo;
	intu32			TotalRead = 0;
	intu32			TotalWrite = 0;
	BYTE			Work;
	BYTE			Save;

	// Do initialization.
	if( NULL == pEntry ) {
		hRc = rmwRC_INVALID_POINTER;
		goto Exit00;
	}
	if( !fQuiet || fDebug ) {
		BSTR			pString = NULL;
		pEntry->lpVtbl->CopyToBStr( pEntry, &pString );
		wprintf( L"\tCleaning %s...\n", pString );
		SysFreeString( pString );
		pString = NULL;
	}

	// Open the input file.
#ifdef	USE_RMWINPROC
	hRc =	RmwInProc_CreateInstance(
							&CLSID_rmwFileIo,
							NULL,
							&IID_rmwFileIo,
							&pFileIn
			);
#else
	hRc =	rmwFileIo_CreateInstance(
							NULL,
							&IID_rmwFileIo,
							&pFileIn
			);
#endif
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileIn Creation", hRc );
	hRc = pFileIn->lpVtbl->put_FileName( pFileIn, pEntry );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileIn Set File Name", hRc );
	hRc = pFileIn->lpVtbl->Open( pFileIn, (RMW_READ_WRITE | RMW_DENY_NONE), 4 );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileIn Open", hRc );

	// Open the output file.
	hRc = pEntry->lpVtbl->Clone( pEntry, &pPathOut );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileOut Path Creation", hRc );
	hRc = pPathOut->lpVtbl->SplitPath( pPathOut, &pDriveName, &pDirectoryName, &pFileName );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileOut SplitPath", hRc );
	hRc = pFileName->lpVtbl->AssignW( pFileName, 0, pWorkFileName );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileOut WorkFileName Assign", hRc );
	hRc = pPathOut->lpVtbl->MakePath( pPathOut, pDriveName, pDirectoryName, pFileName );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileOut MakePath", hRc );
#ifdef	USE_RMWINPROC
	hRc =	RmwInProc_CreateInstance(
							&CLSID_rmwFileIo,
							NULL,
							&IID_rmwFileIo,
							&pFileOut
			);
#else
	hRc =	rmwFileIo_CreateInstance(
							NULL,
							&IID_rmwFileIo,
							&pFileOut
			);
#endif
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileOut Creation", hRc );
	hRc = pFileOut->lpVtbl->put_FileName( pFileOut, pPathOut );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileOut Set File Name", hRc );
	hRc = pFileOut->lpVtbl->Create( pFileOut, TRUE, (RMW_WRITE_ONLY | RMW_DENY_NONE), 4 );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileOut Create", hRc );

	// Concatenate the file.
	Work = 0;
	for( ;; ) {

		// Get the next byte.
		Save = Work;					// Save for \r\n analysis.
		hRc = pFileIn->lpVtbl->Read( pFileIn, &Work, 1, &ActualNo );
		hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileIn Read", hRc );
		if( 1 == ActualNo )
			;
		else
			break;
		++TotalRead;
		Work &= 0x7F;
		if( Work == 0x1A ) 				//*** EOF ***
			break;
		if( (Work >= ' ') && (Work < 0x7F) )
			;
		else if( (Work == '\f' ) || (Work == '\n') || (Work == '\r') || (Work == '\t') )
			;
		else
			continue;

		// Put the byte.
		if( ( Work == '\n' ) && ( Save != '\r' ) ) {
			hRc = pFileIn->lpVtbl->Write( pFileOut, &CarriageReturn, 1, NULL );
			hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileOut Write", hRc );
			++TotalWrite;
		}
		hRc = pFileIn->lpVtbl->Write( pFileIn, &Work, 1, NULL );
		hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileOut Write", hRc );
		++TotalWrite;

	// Loop for all input data.
	}

	// Close the file and do clean up.
	hRc = pFileIn->lpVtbl->Close( pFileIn );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileIn Close", hRc );
	(void)pFileIn->lpVtbl->Release( pFileIn );
	pFileIn = FALSE;
	hRc = pFileOut->lpVtbl->Close( pFileOut );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileOut Close", hRc );
	(void)pFileOut->lpVtbl->Release( pFileOut );
	pFileOut = FALSE;
	if( fDebug )
		goto Exit00;
	hRc = pEntry->lpVtbl->FileDelete( pEntry, TRUE );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileIn Deletion", hRc );
	hRc = pPathOut->lpVtbl->FileRename( pPathOut, pEntry );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"CleanFile() - FileIn Rename", hRc );
	if( !fQuiet || fDebug ) {
		wprintf( L"\t\tTotal Characters Read    = %d\n", TotalRead );
	}
	if( !fQuiet || fDebug ) {
		wprintf( L"\t\tTotal Characters Written = %d\n", TotalWrite );
	}

	// Return to Caller.
	hRc = rmwRC_OK;
Exit00:
	if( pPathOut ) {
		(void)pPathOut->lpVtbl->Release( pPathOut );
		pPathOut = NULL;
	}
	if( pDriveName ) {
		(void)pDriveName->lpVtbl->Release( pDriveName );
		pDriveName = NULL;
	}
	if( pDirectoryName ) {
		(void)pDirectoryName->lpVtbl->Release( pDirectoryName );
		pDirectoryName = NULL;
	}
	if( pFileName ) {
		(void)pFileName->lpVtbl->Release( pFileName );
		pFileName = NULL;
	}
	return( hRc );
}




//**********************************************************
//					C l e a n F i l e s
//**********************************************************

LOCAL
rmwRC RMW_APIENTRY	CleanFiles(
	IrmwPath		*pPath
)
{
	IrmwDiskDirectoryScan
					*pScan = NULL;
	IrmwDiskDirectoryScanEvents
					*pEvents = NULL;
	rmwRC			hRc = rmwRC_OK;

	// Do initialization.
	RMW_TRACEW( (L"CleanFiles()...\n") );
	if( pPath ) {
		(void)pPath->lpVtbl->AddRef( pPath );
	}

	// Create an initial object.
#ifdef	USE_RMWINPROC
	hRc =	RmwInProc_CreateInstance(
							&CLSID_rmwDiskDirectoryScan,
							NULL,
							&IID_rmwDiskDirectoryScan,
							&pScan
			);
#else
	hRc =	rmwDiskDirectoryScan_CreateInstance(
							NULL,
							&IID_rmwDiskDirectoryScan,
							&pScan
			);
#endif
	if( RMW_FAILED(hRc) ) {
		RMW_ABORT( ( "Error - CreateInstance(pScan) failed") );
	}
	hRc = rmwEvents_CreateInstance(
				NULL,
				&IID_rmwDiskDirectoryScanEvents,
				&pEvents
		  );
	if( RMW_FAILED(hRc) ) {
		RMW_ABORT( ( "Error - CreateInstance(pEvents) failed") );
	}
	hRc = pScan->lpVtbl->DiskDirectoryScanEventsAdvise( pScan, pEvents, NULL );
	if( RMW_FAILED(hRc) ) {
		RMW_ABORT( ( "Error - pObj->DirectoryScanEventsAdvise() failed") );
	}

	// Try the object out.
	hRc = pScan->lpVtbl->Run( pScan, pPath, FALSE );
	if( RMW_FAILED(hRc) ) {
		RMW_ABORT( ( "Error - pScan->Run() failed") );
	}

	// Destroy the test objects
	(void)pScan->lpVtbl->Release( pScan );
	pScan = NULL;
	if( pEvents ) {
		(void)pEvents->lpVtbl->Release( pEvents );
		pEvents = NULL;
	}
	if( pPath ) {
		(void)pPath->lpVtbl->Release( pPath );
		pPath = NULL;
	}

	// Return to caller.
	RMW_TRACEW( (L"...Successful Completion!\n") );
	return( hRc );
}




//**********************************************************
//						D l l L o c k S e r v e r
//**********************************************************

STDAPI			DllLockServer(
	BOOL			fLock
)
{

	// Do initialization.

	// Free the object if no longer used.
	if( fLock )
		++g_cRef;
	else
		--g_cRef;

	// Return to caller.
	return( rmwRC_OK );
}




//**********************************************************
//					P r o g r a m H e l p
//**********************************************************

LOCAL
void			ProgramHelp(
	void
)
{
	printf( "FClean - %s %s\n", __DATE__, __TIME__ );
	printf( "Usage: FClean [-h?q]  [[-r] <szPath>]...\n" );
	printf( "Options:\n" );
	printf( "\tszPath is a fully qualified or ambiguous pathname.\n" );
	printf( "Switches:\n" );
	printf( "\t?\t-\tDisplays this help.\n" );
	printf( "\th(help)\t-\tDisplays this help.\n" );
	printf( "\tq(quiet)\t-\tDo not provide any feedback only error messages.\n" );
	printf( "\tr(recurse)\t-\tRecurse through all subdirectories.\n" );
	printf( "Remarks:\n" );
	printf( "\tPressing Ctrl-C immediately terminates the program.\n" );
	printf( "\n" );
}




//**********************************************************
//					S c a n P a r m s
//**********************************************************

LOCAL
rmwRC RMW_APIENTRY	ScanParms(
	int 			ArgC,
	char			*ArgV[]
)
{
	rmwRC			hRc = rmwRC_OK;
	IrmwClo			*pClo = NULL;
	intu32 			Work = 0;

	// Open Argument Processing.
	RMW_TRACEW( (L"ScanParms()...\n") );
	hRc = pAppl->lpVtbl->get_Clo( pAppl, &pClo );
	if( RMW_FAILED(hRc) ) {
		goto Exit00;
	}

	// Scan off Switches.
	for( ;; ) {
		IrmwString		*pOption = NULL;
		IrmwString		*pString = NULL;
		hRc = pClo->lpVtbl->IsMoreSwitches( pClo );
		if( RMW_FAILED(hRc) ) {
			break;
		}
		/* Find some Switches.
		 */
		hRc = pClo->lpVtbl->FindSwitchW( pClo, 1, L"?", NULL );
		if( RMW_SUCCEEDED(hRc) ) {
dohelp:			
            ProgramHelp( );
            hRc = rmwRC_OK;
            goto Exit00;
		}
		hRc = pClo->lpVtbl->FindSwitchW( pClo, 1, L"h", NULL );
		if( RMW_SUCCEEDED(hRc) ) {
            goto dohelp;
        }
		hRc = pClo->lpVtbl->FindSwitchW( pClo, 1, L"q", NULL );
		if( RMW_SUCCEEDED(hRc) ) {
            fQuiet = !fQuiet;
		}
	}

	// Scan the options.
	if( fQuiet )
        ;
    else {
        printf( "FClean - %s %s\n", __DATE__, __TIME__ );
    }
    for( ;; ) {
		IrmwString		*pOption = NULL;
		IrmwString		*pString = NULL;
		hRc = pClo->lpVtbl->IsMoreOptions( pClo );
		if( RMW_FAILED(hRc) ) {
			break;
		}
        fRecurse = FALSE;
		hRc = pClo->lpVtbl->FindSwitchW( pClo, 1, L"r", NULL );
		if( RMW_SUCCEEDED(hRc) ) {
            fRecurse = !fRecurse;
		}
		hRc = pClo->lpVtbl->GetOption( pClo, &pOption, &pString );
		(void)pAppl->lpVtbl->FailOnHRESULT( pAppl, L"IrmwClo::GetOption", hRc );
		{
			IrmwPath		*pWork = NULL;
#ifdef	USE_RMWINPROC
			hRc =	RmwInProc_CreateInstance(
									&CLSID_rmwPath,
									NULL,
									&IID_rmwPath,
									&pWork
					);
#else
			hRc =	rmwPath_CreateInstance(
									NULL,
									&IID_rmwPath,
									&pWork
					);
#endif
			if( RMW_SUCCEEDED(hRc) ) {
				hRc = pWork->lpVtbl->AssignIrmwString( pWork, pOption );
				if( RMW_SUCCEEDED(hRc) ) {
					hRc = CleanFiles( pWork );
					(void)pAppl->lpVtbl->FailOnHRESULT( pAppl, L"ScanParms - CleanFiles() Error", hRc );
				}
				(void)pWork->lpVtbl->Release( pWork );
				pWork = NULL;
			}
		}
//NextOpt:
		if( pOption ) {
			(void)pOption->lpVtbl->Release( pOption );
			pOption = NULL;
		}
		if( pString ) {
			(void)pString->lpVtbl->Release( pString );
			pString = NULL;
		}
	}

	// Return to caller.
	hRc = rmwRC_OK;
Exit00:
	if( pClo ) {
		(void)pClo->lpVtbl->Release( pClo );
		pClo = NULL;
	}
	RMW_TRACEW( (L"...ScanParms returning (0x%08x)\n", hRc) );
	return( hRc );
}




//*******************************************************************
//						Main Program
//*******************************************************************


int 			main(
	int 			cArg,
	char			*ppArgV[]
)
{
	rmwRC			hRc = rmwRC_OK;


	// Do initialization.
#ifdef	SIGINT
	if( signal( SIGINT, SIG_DFL ) == SIG_ERR ) {
		RMW_ABORT( ( "FATAL Error - Couldn't set up Ctrl+c Handler") );
	}
#endif
#ifdef	SIGBREAK
	if( signal( SIGBREAK, SIG_DFL ) == SIG_ERR ) {
		RMW_ABORT( ( "FATAL Error - Couldn't set up Ctrl+Break Handler") );
	}
#endif
	RMW_TRACE_ON( );
	RMW_TRACEW( (L"\n\nFClean --- Main Entry\n") );

	// Initialize the Application.
#ifdef	NDEBUG
#else
//	rmwMem_SetDebug( TRUE );
#endif
#ifdef	USE_RMWINPROC
	hRc =	RmwInProc_CreateInstance(
							&CLSID_rmwApplication,
							NULL,
							&IID_rmwApplication,
							&pAppl
			);
#else
	hRc =	rmwApplication_CreateInstance(
							NULL,
							&IID_rmwApplication,
							&pAppl
			);
#endif
	if( RMW_FAILED(hRc) ) {
		LPWSTR			pMsg = NULL;
		intu32			cMsg = 0;
		cMsg =	FormatMessageW( 
						(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM),
						NULL,
						hRc,
						MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
						(LPWSTR)&pMsg,
						0,
						NULL
				);
    	(void)MessageBoxW(
        				NULL,
        				pMsg,
                        L"IrmwApplication",
				        (MB_OK | MB_ICONSTOP)
        );
		LocalFree( pMsg );
		pMsg = NULL;
        exit( 100 );
    }
	hRc = pAppl->lpVtbl->Init( pAppl, GetModuleHandle( NULL ) );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"IrmwApplication - Init", hRc );
	hRc = pAppl->lpVtbl->get_Malloc( pAppl, &pMalloc );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"IrmwApplication - get_Malloc", hRc );
	RMW_TRACEW( (L"Main::pAppl initialized.") );

	// Scan input parameters and execute requests from them.
	hRc = ScanParms( cArg, ppArgV );
	hRc = pAppl->lpVtbl->FailOnHRESULT( pAppl, L"ScanParms - Error", hRc );

	// Perform OLE2/COM clean up.
	if( pMalloc ) {
		(void)pMalloc->lpVtbl->Release( pMalloc );
		pMalloc = NULL;
	}
	if( pAppl ) {
		(void)pAppl->lpVtbl->Release( pAppl );
		pAppl = NULL;
	}

	/* Return to O/S.
	 */
	return( 0 );
}

