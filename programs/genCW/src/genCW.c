// vi:nu:et:sts=4 ts=4 sw=4

//
//  genCW.c
//
//  Created by bob on 3/20/16.
//

#include    <cmn_defs.h>
#include    <AStr.h>
#include    <AudioCW.h>
#include    <Path.h>
#include    <W32Str.h>
#include    <stdint.h>
#include    <stdio.h>
#include    <stdlib.h>


const
char        *pProgram = "genCW";
const
char        *pProgramPath = NULL;
int         fDebug = 0;             // -d or --debug or --no-debug
int         speed = 20;
int         srcFlag = 0;
const
char        *pOutput = NULL;	

int         cOptions = 0;
const
char        **ppOptions = NULL;

int         lines = 1;



void        usage(
    char        *pMsg
)
{
    static
    if (pMsg) {
        fprintf(stderr, "?%s - %s\n", pProgram, pMsg);
    }
    fprintf(
            stderr,
            "Usage: %s [-do] input-text; %s ? for help\n",
            pProgram,
            pProgram
    );
    fprintf( stderr, "\t-d,--[no-]debug  Set debug mode\n");
    fprintf( stderr, "\t-o,--output file-path Generate audio file with name of file-path\n");
}



int         parseArgs(
    int         argc,
    const
    char        *argv[]
)
{
    int         wrkArgC = argc;
    const
    char        **ppWrkArgV = argv;
    
    // Validate some of the input.
    pProgramPath = argv[0];
    if( wrkArgC <= 1 ) {
        usage( "No arguments" );
        exit(99);
    }
    if( wrkArgC == 2 && ppWrkArgV[1][0] == '?' && ppWrkArgV[1][1] == 0) {
        usage("Generate JSON tokens from a source file");
        exit(1);
    }
    
    // Process the switches.
    for (wrkArgC--,ppWrkArgV++; wrkArgC>0; wrkArgC--,ppWrkArgV++) {
        if (0 == strcmp(*ppWrkArgV, "--debug")) {
            ++fDebug;
        }
        else if (0 == strcmp(*ppWrkArgV, "--no-debug")) {
            --fDebug;
        }
        else if (0 == strcmp(*ppWrkArgV, "--output")) {
            if (NULL != *(ppWrkArgV+1)) {
                --wrkArgC;
                ++ppWrkArgV;
                pOutput = *ppWrkArgV;
            }
        }
        else if (0 == strcmp(*ppWrkArgV, "--speed")) {
            if (NULL != *(ppWrkArgV+1)) {
                --wrkArgC;
                ++ppWrkArgV;
                speed = atoi(*ppWrkArgV);
            }
        }
        else if (0 == strcmp(*ppWrkArgV, "--")) {
            --wrkArgC;
            ++ppWrkArgV;
            break;
        }
        else if (**ppWrkArgV == '-') {
            const
            char        *pWrk = *ppWrkArgV + 1;
            while (*pWrk) {
                switch(tolower(*pWrk)) {
                    case 'd':
                        ++fDebug;
                        break;
                    case 'o':
                        if (NULL != *(ppWrkArgV+1)) {
                            --wrkArgC;
                            ++ppWrkArgV;
                            pOutput = *ppWrkArgV;
                        }
                        break;
                    case 's':
                        if (NULL != *(ppWrkArgV+1)) {
                            --wrkArgC;
                            ++ppWrkArgV;
                            speed = atoi(*ppWrkArgV);
                        }
                        break;
                    default:
                        usage( "Unknown flag" );
                        exit(99);
                }
                ++pWrk;
            }
        }
        else
            break;
    }
    
    cOptions = wrkArgC;
    ppOptions = ppWrkArgV;
    
    return 0;
}



void        display_output(
    ASTR_DATA   *pData
)
{
    ASTR_DATA   *pAStr;
    ASTR_DATA   *pAStr2;
    
    pAStr = AStr_Copy(pData);
    if (pAStr) {
        AStr_Trim(pAStr);
        pAStr2 = AStr_ToChrCon(pAStr);
        fprintf(stdout, "/*%5d*/ \"%s\",\n", lines, AStr_getData(pAStr2));
        obj_Release(pAStr2);
        pAStr2 = OBJ_NIL;
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
        ++lines;
    }
    
    
}




void             genCW (
    const
    char            *pStrA,
    const
    char            *pPathA
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    AUDIOCW_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    PATH_DATA       *pPath = OBJ_NIL;
    W32STR_DATA     *pStrW32 = OBJ_NIL;

    if (NULL == pStrA) {
        fprintf(stderr, "ERROR: genCW() NULL generate string!\n\n\n");
        exit(16);
    }
    pStrW32 = W32Str_NewA(pStrA);
    if (OBJ_NIL == pStrW32) {
        fprintf(stderr, "ERROR: Could not create W32 String object!\n\n\n");
        exit(16);
    }

    if (NULL == pPathA) {
        pPathA = "~/gencw.wav";
    }
    pPath = Path_NewA(pPathA);
    if (OBJ_NIL == pPathA) {
        fprintf(stderr, "ERROR: Could not create Output Path object!\n\n\n");
        exit(16);
    }

    pObj = AudioCW_NewWithParms(1, 11025, 8, 740);
    if (pObj) {

        eRc = AudioCW_CalculateTiming(pObj, speed, speed);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR: Could not create calculate timing for %d!\n\n\n", speed);
            exit(16);
        }

        eRc = AudioCW_PutTextW32(pObj, W32Str_getLength(pStrW32), (W32CHR_T *)W32Str_getData(pStrW32) );
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR: Could not create wav data for %s!\n\n\n", pStrA);
            exit(16);
        }

        eRc = AudioCW_WriteToFile(pObj, pPath);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR: Failed to write wav data to %s!\n\n\n", Path_getData(pPath));
            exit(16);
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    } else {
        fprintf(stderr, "ERROR: Could not create AudoCW object!\n\n\n");
        exit(16);
    }

    obj_Release(pPath);
    pPath = OBJ_NIL;
    obj_Release(pStrW32);
    pStrW32 = OBJ_NIL;

}



int         main(
    int         argc,
    const
    char        *argv[]
)
{
    PATH_DATA       *pGmrFile = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    int             i;
    ERESULT         eRc;
    
    parseArgs(argc, argv);
    
    if (cOptions > 0) {
        genCW(ppOptions[0], pOutput);
    }
    else {
        usage("ERROR - Missing input text!");
        exit(99);
    }
        
    return 0;
}
