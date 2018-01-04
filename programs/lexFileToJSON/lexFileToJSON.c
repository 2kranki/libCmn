//
//  lexFileToJSON.c
//
//  Created by bob on 3/20/16.
//

#include    "cmn.h"
#include    "pplex.h"
#include    "pplex2.h"
#include    <stdint.h>
#include    <stdio.h>
#include    <stdlib.h>


const
char        *pProgramPath = NULL;
int         fDebug = 0;             // -d or --debug or --no-debug
int         srcFlag = 0;

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
    fprintf( stderr, "\t-n               Set the nFlag\n");
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
    WSTR_DATA       *pWStr;
    
    pWStr = AStr_ToWStr(pData);
    if (pWStr) {
        WStr_Trim(pWStr);
        WStr_EscapeForC(pWStr);
        fprintf(stdout, "\"%ls\",\n", WStr_getData(pWStr));
        obj_Release(pWStr);
        pWStr = OBJ_NIL;
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
    BOOL            fRc;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pJSON = OBJ_NIL;
    
    parseArgs(argc, argv);
    
    if (cOptions > 1) {
        pGmrFile = path_NewA(ppOptions[0]);
        if (pGmrFile) {
            pSrc = srcFile_Alloc();
            pSrc = srcFile_InitFile(pSrc, pGmrFile, 4, true, false);
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
                    fRc = pplex2_setKwdSelection(pLex,PPLEX_KWDS_LL1);
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
