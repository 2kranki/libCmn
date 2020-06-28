// vi:nu:et:sts=4 ts=4 sw=4

//
//  genCW.c
//
//  Created by bob on 3/20/16.
//

#include    <cmn_defs.h>
#include    <audioCW.h>
#include    <srcFile.h>
#include    <stdint.h>
#include    <stdio.h>
#include    <stdlib.h>


const
char        *pProgramPath = NULL;
int         fDebug = 0;             // -d or --debug or --no-debug
int         jsonFlag = 0;
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
    const
    char        *pProgram = "genCW";
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
            if (NULL != *(ppWrkArgV+1) {
                --wrkArgC;
                ++ppWrkArgV;
                pOutput = ppWrkArgV;
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
                        if (NULL != *(ppWrkArgV+1) {
                            --wrkArgC;
                            ++ppWrkArgV;
                            pOutput = ppWrkArgV;
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




int         main(
    int         argc,
    const
    char        *argv[]
)
{
    PPLEX_DATA      *pLex = OBJ_NIL;
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    PATH_DATA       *pGmrFile = OBJ_NIL;
    bool            fRc;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr = OBJ_NIL;
    int             i;
    ERESULT         eRc;
    
    parseArgs(argc, argv);
    
    if (cOptions > 0) {
        if (srcFlag) {
            fprintf(stdout, "//\t--src\n");
        }
        for (i=0; i<cOptions; ++i) {
            fprintf(stdout, "//\tfiles = \"%s\"\n", ppOptions[i]);
        }
        pGmrFile = Path_NewA(ppOptions[0]);
        Path_Clean(pGmrFile);
        if (pGmrFile) {
            if (srcFlag) {
                pSrc = srcFile_NewFromPath(pGmrFile, 1, 4);
                BREAK_NULL(pSrc);
                for (;;) {
                    pToken = srcFile_InputLookAhead(pSrc, 1);
                    if (jsonFlag) {
                        pStr = Token_ToJson(pToken);
                        display_output(pStr);
                    }
                    else {
                        pStr = Token_ToDebugString(pToken, 0);
                        display_output(pStr);
                    }
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                    if (Token_getClass(pToken) == -1) {
                        break;
                    }
                    pToken = srcFile_InputAdvance(pSrc, 1);
                }
                obj_Release(pSrc);
                pSrc = OBJ_NIL;
            }
            else {
                pLex = pplex_New(4);
                BREAK_NULL(pLex);
                pplex_setReturnNL(pLex, fNL ? true : false);
                pplex_setReturnWS(pLex, fWS ? true : false);
                eRc = pplex_CreateLexers((PPLEX_DATA *)pLex, false, true);
                BREAK_TRUE(ERESULT_FAILED(eRc));
                eRc = pplex_CreateSourceFromPath(pLex, pGmrFile);
                BREAK_TRUE(ERESULT_FAILED(eRc));
                fRc = pplex_setLang(pLex, lexType);
                BREAK_FALSE(fRc);
                for (;;) {
                    pToken = lex_InputLookAhead((LEX_DATA *)pLex, 1);
                    if (jsonFlag) {
                        pStr = Token_ToJson(pToken);
                        display_output(pStr);
                    }
                    else {
                        pStr = Token_ToDebugString(pToken, 0);
                        display_output(pStr);
                    }
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                    if (Token_getClass(pToken) == -1) {
                        break;
                    }
                    pToken = lex_InputAdvance((LEX_DATA *)pLex, 1);
                    
                }
            }
        }
        
    }
    else {
        usage("ERROR - Missing input file name!");
        exit(99);
    }
        
    return 0;
}
