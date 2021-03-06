//
//  md5Util.c
//
//  Created by bob on 4/02/18.
//

#include    <cmn_defs.h>
#include    <appl.h>
#include    <dir.h>
#include    <file.h>
#include    <fileio.h>
#include    <hex.h>
#include    <md5ChkSum.h>
#include    <path.h>
#include    <stdint.h>
#include    <stdio.h>
#include    <stdlib.h>


const
char        *pProgramPath = NULL;
int         fDebug = 0;             // -d or --debug or --no-debug
int         fForce = 0;             // -f or --force or --no-force
int         fQuiet = 0;             // -q or --quiet or --no-quiet
int         srcFlag = 0;
int         fNL = 0;

int         cOptions = 0;
const
char        **ppOptions = NULL;

uint8_t     digest[16] = {0};
const
uint32_t    cDigest = 16;
PATH_DATA   *pDigestPath = OBJ_NIL;



void            digestCopy(
    const
    uint8_t         *pDigest
);



int             digestFromFile(
    PATH_DATA       *pPath
)
{
    ERESULT         eRc;
    VALUE_DATA      *pValue = OBJ_NIL;
    PATH_DATA       *pMD5_FileName = OBJ_NIL;
    ASTR_DATA       *pMD5 = OBJ_NIL;

    if (fDebug) {
        fprintf(stdout, "digestFromFile()\n");
        fprintf(stdout, "\tpath = \"%s\"\n", path_getData(pPath));
    }
  
    pMD5 = AStr_NewFromUtf8File(pPath); 
    if (OBJ_NIL == pMD5) {
        fprintf(stderr, "FATAL - Could not read Digest File, %s!\n\n\n",
            path_getData(pPath)
        );
        exit(99);
    }

    eRc = md5ChkSum_ParseDigest(pMD5, &pMD5_FileName, &pValue);
    if (ERESULT_FAILED(eRc)) {
        fprintf(stderr, "FATAL - Error parsing digest from %s!\n\n\n",
            path_getData(pPath)
        );
        exit(99);
    }

    if (pMD5_FileName && pDigestPath) {
        obj_Release(pDigestPath);
    }
    pDigestPath = pMD5_FileName;
    pMD5_FileName = OBJ_NIL;
    digestCopy(value_getData(pValue));
    obj_Release(pValue);
    pValue = OBJ_NIL;

    return 0;
}



void            digestCopy(
    const
    uint8_t         *pDigest
)
{
    uint32_t        i;

    if (fDebug) {
        fprintf(stdout, "digestCopyFrom()\n");
    }
    for (i=0; i<cDigest; ++i) {
        digest[i] = pDigest[i];
    }
}



void            digestZero(
    void
)
{
    uint32_t        i;

    if (fDebug) {
        fprintf(stdout, "digestZero()\n");
    }
    for (i=0; i<cDigest; ++i) {
        digest[i] = 0;
    }
}



void            usage(
    char            *pMsg
)
{
    static
    const
    char        *pProgram = "md5Util";
    if (pMsg) {
        fprintf(stderr, "%s - %s\n", pProgram, pMsg);
    }
    fprintf(
            stderr,
            "Usage: %s [-dl?] input-file; %s ? for help\n",
            pProgram,
            pProgram
    );
    fprintf( stderr, "\tmd5Util performs various functions based upon a provided verb.\n");
    fprintf( stderr, "\t-d,--[no-]debug  Set debug mode\n");
    fprintf( stderr, "\t-f,--[no-]force  Force replacements\n");
    fprintf( stderr, "\t-q,--[no-]quiet  Only set return code\n");
    //fprintf( stderr, "\t-s,--src         Generate JSONs from Source File\n");
    //fprintf( stderr, "\t-l,--nl          Exclude NL tokens\n");
}



int             parseArgs(
    int             argc,
    const
    char            *argv[]
)
{
    int         wrkArgC = argc;
    const
    char        **ppWrkArgV = argv;
    
    // Validate some of the input.
    pProgramPath = argv[0];
    if( wrkArgC <= 1 ) {
        usage( "ERROR - No arguments" );
        exit(99);
    }
    if( wrkArgC == 2 && ppWrkArgV[1][0] == '?' && ppWrkArgV[1][1] == 0) {
        usage("md5Util - Create/Use MD5 File/Directory Checksums");
        exit(1);
    }
    
    // Process the switches.
    for (wrkArgC--,ppWrkArgV++; wrkArgC>0; wrkArgC--,ppWrkArgV++) {
        if (0 == strcmp(*ppWrkArgV, "--debug")) {
            fDebug = 1;
        }
        else if (0 == strcmp(*ppWrkArgV, "--no-debug")) {
            fDebug = 0;
        }
        else if (0 == strcmp(*ppWrkArgV, "--force")) {
            fForce = 1;
        }
        else if (0 == strcmp(*ppWrkArgV, "--no-force")) {
            fForce = 0;
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
                        fDebug = 1;
                        break;
                    case 'f':
                        fForce = 1;
                        break;
                    case 'l':
                        ++fNL;
                        break;
                    case 's':
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



int             createFileCheckSum(
    PATH_DATA       *pPath              // valid file path
)
{
    ERESULT         eRc;
    MD5CHKSUM_DATA	*pChkSum = OBJ_NIL;
    FILEIO_DATA     *pIO = OBJ_NIL;
    size_t          fileSize;
    uint32_t        amtRead;
    uint32_t        bufferSize = 2048;
    uint8_t         *pBuffer = NULL;
    PATH_DATA       *pMD5Path = OBJ_NIL;
    FILE            *pFile = NULL;
    uint32_t        i;
    ASTR_DATA       *pMD5Str = OBJ_NIL;
    
    if (fDebug) {
        fprintf(stdout, "createFileCheckSum()\n");
    }

    pChkSum = md5ChkSum_New( );
    if (OBJ_NIL == pChkSum) {
        fprintf(stderr, "FATAL - Could not create MD5 Check Sum Object!\n\n\n");
        exit(99);
    }
     pBuffer = mem_Malloc(bufferSize);
    if (NULL == pBuffer) {
        fprintf(stderr, "FATAL - Could allocate read buffer!\n\n\n");
        exit(99);
    }

   
    pIO = fileio_New( );
    if (OBJ_NIL == pChkSum) {
        fprintf(stderr, "FATAL - Could not create fileio Object!\n\n\n");
        exit(99);
    }
        
    if (fDebug) {
        fprintf(stdout, "\tpath = \"%s\"\n", path_getData(pPath));
    }
    eRc = fileio_Open(pIO, pPath);
    if (ERESULT_FAILED(eRc)) {
        fprintf(stderr, "FATAL - Could not open file for input!\n\n\n");
        exit(99);
    }

    fileSize = fileio_Size(pIO);
    if (fDebug) {
        fprintf(stderr, "\tFile Size == %zu\n", fileSize);
    }
    
    while(fileSize) {
        eRc = fileio_Read(pIO, bufferSize, pBuffer, &amtRead);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "FATAL - Input File Read Error!\n\n\n");
            exit(99);
        }

        eRc = md5ChkSum_Update(pChkSum, pBuffer, amtRead);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "FATAL - Buffer MD5 Check Sum Calculation Error!\n\n\n");
            exit(99);
        }

        fileSize -= amtRead;
    }

    mem_Free(pBuffer);
    pBuffer = NULL;

    eRc = fileio_Close(pIO, false);
    if (ERESULT_FAILED(eRc)) {
        fprintf(stderr, "FATAL - Error closing input file!\n\n\n");
        exit(99);
    }
    
    obj_Release(pIO);
    pIO = OBJ_NIL;
    
    eRc = md5ChkSum_Finalize(pChkSum, pPath, &pMD5Str);
    if (ERESULT_FAILED(eRc)) {
        fprintf(stderr, "FATAL - MD5 Check Sum Finalization Error!\n\n\n");
        exit(99);
    }

    pMD5Path = path_Copy(pPath);
    if (OBJ_NIL == pMD5Path) {
        fprintf(stderr, "FATAL - Could not create copy of File Path!\n\n\n");
        exit(99);
    }

    eRc = path_AppendExtA(pMD5Path, "md5.txt");
    if (ERESULT_FAILED(eRc)) {
        fprintf(stderr, "FATAL - Failed to make MD5 File Path!\n\n\n");
        exit(99);
    }

    eRc = AStr_ToUtf8File(pMD5Str, pMD5Path);
    if (ERESULT_FAILED(eRc)) {
        fprintf(stderr, "FATAL - Could not create MD5 File: %s!\n\n\n",
            path_getData(pMD5Path)
        );
        exit(99);
    }

    obj_Release(pChkSum);
    pChkSum = OBJ_NIL;
    obj_Release(pMD5Path);
    pMD5Path = OBJ_NIL;
    obj_Release(pMD5Str);
    pMD5Str = OBJ_NIL;
    return 0;
 }




int             main(
    int             argc,
    const
    char            *argv[]
)
{
    APPL_DATA       *pAppl = OBJ_NIL;
    PATH_DATA       *pRef1 = OBJ_NIL;
    PATH_DATA       *pRef2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pVerb = OBJ_NIL;
    int             i;
    int             iRc = 0;
    
    pAppl = appl_New(argc, argv);
    if (OBJ_NIL == pAppl) {
        fprintf(stderr, "FATAL - Unable to create Application Framework!\n\n\n");
        exit(99);
    }
    
    parseArgs(argc, argv);
    if (cOptions == 0) {
        usage("ERROR - Missing verb!");
        exit(99);
    }
    if (fDebug) {
        fprintf(stdout, "//\t--debug\n");
        for (i=0; i<cOptions; ++i) {
            fprintf(stdout, "//\toption[%d] = \"%s\"\n", i, ppOptions[i]);
        }
    }
    
    while (cOptions && !iRc) {
        digestZero( );
        if ((0 == strcmp("create", ppOptions[0])) || (0 == strcmp("c", ppOptions[0]))) {
            if (fDebug) {
                fprintf(stdout, "//\tverb == create\n");
            }
            ++ppOptions; --cOptions;
            if ((cOptions == 0) || (strlen(ppOptions[0]) == 0)) {
                usage("ERROR - Create is missing File or Directory Path");
            }

            pRef1 = path_NewA(ppOptions[0]);
            if (OBJ_NIL == pRef1) {
                fprintf(stderr, "FATAL - Could not create path for input file!\n\n\n");
                exit(99);
            }
            ++ppOptions; --cOptions;

            if (ERESULT_SUCCESSFUL(path_IsFile(pRef1))) {
                iRc = createFileCheckSum(pRef1);
                obj_Release(pRef1);
                pRef1 = OBJ_NIL;
            }
            else if (ERESULT_SUCCESSFUL(path_IsDir(pRef1))) {
                //iRc = createFirCheckSum(pRef1);
                obj_Release(pRef1);
                pRef1 = OBJ_NIL;
            }
            continue;
        }
        if ((0 == strcmp("verify", ppOptions[0])) || (0 == strcmp("v", ppOptions[0]))) {
            if (fDebug) {
                fprintf(stdout, "//\tverb == create\n");
            }
            ++ppOptions; --cOptions;
            if ((cOptions == 0) || (strlen(ppOptions[0]) == 0)) {
                usage("ERROR - Create is missing File or Directory Path");
            }

            pRef1 = path_NewA(ppOptions[0]);
            if (OBJ_NIL == pRef1) {
                fprintf(stderr, "FATAL - Could not create path for input file!\n\n\n");
                exit(99);
            }
            ++ppOptions; --cOptions;

            if (ERESULT_SUCCESSFUL(path_IsFile(pRef1))) {
                //iRc = createFileCheckSum(pRef1);
                obj_Release(pRef1);
                pRef1 = OBJ_NIL;
            }
            else if (ERESULT_SUCCESSFUL(path_IsDir(pRef1))) {
                //iRc = createFirCheckSum(pRef1);
                obj_Release(pRef1);
                pRef1 = OBJ_NIL;
            }
            continue;
        }
    }
        
    return iRc;
}
