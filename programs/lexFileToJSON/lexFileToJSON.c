//
//  lexFileToJSON.c
//
//  Created by bob on 3/20/16.
//

#include    "cmn_defs.h"
#include    "pplex.h"
#include    "pplex2.h"
#include    <stdint.h>
#include    <stdio.h>
#include    <stdlib.h>


const
char        *pProgramPath = NULL;
int         fDebug = 0;             // -d or --debug or --no-debug
int         srcFlag = 0;
int         fNL = 0;

int         cOptions = 0;
const
char        **ppOptions = NULL;



void        usage(
    char        *pMsg
)
{
    static
    const
    char        *pProgram = "lexFileToJSON";
    if (pMsg) {
        fprintf(stderr, "?%s - %s\n", pProgram, pMsg);
    }
    fprintf(
            stderr,
            "Usage: %s [-dl] input-file; %s ? for help\n",
            pProgram,
            pProgram
    );
    fprintf( stderr, "\t-d,--[no-]debug  Set debug mode\n");
    fprintf( stderr, "\t-s,--src         Generate JSONs from Source File\n");
    fprintf( stderr, "\t--nl             Exclude NL tokens\n");
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
        else if (0 == strcmp(*ppWrkArgV, "--src")) {
            ++srcFlag;
        }
        else if (0 == strcmp(*ppWrkArgV, "--nl")) {
            ++fNL;
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
                    case 'l':
                        ++srcFlag;
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
        fprintf(stdout, "\"%s\",\n", AStr_getData(pAStr2));
        obj_Release(pAStr2);
        pAStr2 = OBJ_NIL;
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
    }
    
    
}




int         main(
    int         argc,
    const
    char        *argv[]
)
{
    PPLEX2_DATA     *pLex = OBJ_NIL;
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    PATH_DATA       *pGmrFile = OBJ_NIL;
    bool            fRc;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pJSON = OBJ_NIL;
    int             i;
    
    parseArgs(argc, argv);
    
    if (cOptions > 0) {
        for (i=0; i<cOptions; ++i) {
            fprintf(stderr, "\toption = \"%s\"\n", ppOptions[i]);
        }
        pGmrFile = path_NewA(ppOptions[0]);
        if (pGmrFile) {
            pSrc = srcFile_NewFromPath(pGmrFile, 1, 4, true, fNL);
            if (pSrc) {
                srcFile_setStripCR(pSrc, true);
                if (srcFlag) {
                    for (;;) {
                        pToken = srcFile_InputLookAhead(pSrc, 1);
                        pJSON = token_ToJSON(pToken);
                        display_output(pJSON);
                        obj_Release(pJSON);
                        pJSON = OBJ_NIL;
                        if (token_getClass(pToken) == -1) {
                            break;
                        }
                        pToken = srcFile_InputAdvance(pSrc, 1);
                        
                    }
                }
                else {
                    pLex = pplex2_New(2);
                    fRc = pplex2_setKwdSelection(pLex, PPLEX_LANG_LL1);
                    BREAK_FALSE(fRc);
                    fRc =   lex_setSourceFunction(
                                                  (LEX_DATA *)pLex,
                                                  (void *)srcFile_InputAdvance,
                                                  (void *)srcFile_InputLookAhead,
                                                  pSrc
                                                  );
                    BREAK_FALSE(fRc);
                    for (;;) {
                        pToken = lex_InputLookAhead((LEX_DATA *)pLex, 1);
                        pJSON = token_ToJSON(pToken);
                        display_output(pJSON);
                        obj_Release(pJSON);
                        pJSON = OBJ_NIL;
                        if (token_getClass(pToken) == -1) {
                            break;
                        }
                        pToken = lex_InputAdvance((LEX_DATA *)pLex, 1);
                        
                    }
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
