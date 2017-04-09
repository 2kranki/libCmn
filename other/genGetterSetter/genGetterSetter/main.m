//
//  main.m
//  genGetterSetter
//
//  Created by bob on 4/8/17.
//


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


#import     <Foundation/Foundation.h>
#include    <cmn_defs.h>
#include    <AStr.h>
#include    <dbCsv.h>
#include    <path.h>
#include    <trace.h>


//===============================================================
//                          D a t a
//===============================================================

typedef struct options_s {
    int             fDebug;
    int             fQuiet;
    int             verbose;
    int             fGenHeader;
    int             fSPN;
    const
    char            *pArg1;
    const
    char            *pArg2;
    const
    char            *pArg3;
    const
    char            *pArg4;
} OPTIONS;


static
OPTIONS         options = {0};
static
ASTR_DATA       *pObjName = OBJ_NIL;
static
ASTR_DATA       *pObjData = OBJ_NIL;        // Upper case of ObjName
static
ASTR_DATA		*pProgramName = OBJ_NIL;
static
OBJARRAY_DATA   *pRecords = OBJ_NIL;





//===============================================================
//                      F u n c t i o n s
//===============================================================

bool            genBody(
    ASTR_DATA       *pStrType,
    ASTR_DATA       *pStrName,
    ASTR_DATA       *pStrDesc
);

bool            genHeader(
    ASTR_DATA       *pStrType,
    ASTR_DATA       *pStrName,
    ASTR_DATA       *pStrDesc
);

bool            parseArgs(
    int             argc,
    const
    char            *argv[],
    OPTIONS         *pOptions
);

bool            readCSV(
    const
    char            *pFilePath
);

void			show_usage(
    const
    char            *pMsg
);



//---------------------------------------------------------------
//                     g e n  B o d y
//---------------------------------------------------------------

bool            genBody(
    ASTR_DATA       *pStrType,
    ASTR_DATA       *pStrName,
    ASTR_DATA       *pStrDesc
)
{
    const
    char            *pFieldType = AStr_getData(pStrType);
    const
    char            *pFieldName = AStr_getData(pStrName);
    const
    char            *pDescription = AStr_getData(pStrDesc);
    bool            fObj = false;

    if (AStr_CompareRightA(pStrType, "_DATA *") == ERESULT_SUCCESS_EQUAL) {
        fObj = true;
    }
    if (strlen(pDescription)) {
        fprintf(stdout, "\t// %s\n", pDescription);
    }
    if (options.fSPN) {
        fprintf(stdout, "\t%s\t\t\t%s_getSpn%s(\n",
                pFieldType,
                AStr_getData(pObjName),
                pFieldName
        );
    }
    else {
        fprintf(stdout, "\t%s\t\t\t%s_get%s(\n",
                pFieldType,
                AStr_getData(pObjName),
                pFieldName
        );
    }
    fprintf(stdout, "\t\t%s_DATA\t*this\n", AStr_getData(pObjData));
    fprintf(stdout, "\t)\n{\n\n");
    fprintf(stdout, "\t#ifdef NDEBUG\n");
    fprintf(stdout, "\t#else\n");
    fprintf(stdout, "\t\tif (%s_Validate(this)) {\n", AStr_getData(pObjName));
    fprintf(stdout, "\t\tDEBUG_BREAK();\n");
    if (fObj) {
        fprintf(stdout, "\t\treturn OBJ_NIL;\n");
    }
    else {
        fprintf(stdout, "\t\treturn 0;\n");
    }
    fprintf(stdout, "\t}\n\t#endif\n\n");
    if (options.fSPN) {
        fprintf(stdout, "\t\treturn this->spn%s;\n", pFieldName);
    }
    else {
        fprintf(stdout, "\t\treturn this->%s;\n", pFieldName);
    }
    fprintf(stdout, "\t}\n\n\n");

    if (options.fSPN) {
        fprintf(stdout, "\tbool\t\t\t%s_setSpn%s(\n",
                AStr_getData(pObjName),
                pFieldName
                );
    }
    else {
        fprintf(stdout, "\tbool\t\t\t%s_set%s(\n",
                AStr_getData(pObjName),
                pFieldName
                );
    }
    fprintf(stdout, "\t\t%s_DATA\t*this,\n", AStr_getData(pObjData));
    fprintf(stdout, "\t\t%s\t\t\tvalue\n", pFieldType);
    fprintf(stdout, "\t)\n{\n\n");
    fprintf(stdout, "\t#ifdef NDEBUG\n");
    fprintf(stdout, "\t#else\n");
    fprintf(stdout, "\t\tif (%s_Validate(this)) {\n", AStr_getData(pObjName));
    fprintf(stdout, "\t\tDEBUG_BREAK();\n");
    if (fObj) {
        fprintf(stdout, "\t\t\treturn OBJ_NIL;\n");
    }
    else {
        fprintf(stdout, "\t\t\treturn 0;\n");
    }
    fprintf(stdout, "\t\t}\n\t#endif\n\n");
    if (fObj) {
        fprintf(stdout, "\t\tobj_Retain(value);\n");
        if (options.fSPN) {
            fprintf(stdout, "\t\tif (this->spn%s) {\n", pFieldName);
            fprintf(stdout, "\t\t\tobj_Release(this->spn%s);\n", pFieldName);
            fprintf(stdout, "\t\t\t//this->spn%s = OBJ_NIL;\n\t\t}\n", pFieldName);
        }
        else {
            fprintf(stdout, "\t\tif (this->%s) {\n", pFieldName);
            fprintf(stdout, "\t\t\tobj_Release(this->%s);\n", pFieldName);
            fprintf(stdout, "\t\t\t//this->%s = OBJ_NIL;\n\t\t}\n", pFieldName);
        }
    }
    if (options.fSPN) {
        fprintf(stdout, "\t\tthis->spn%s = value;\n", pFieldName);
    }
    else {
        fprintf(stdout, "\t\tthis->%s = value;\n", pFieldName);
    }
    fprintf(stdout, "\n\t\treturn true;\n\t}\n\n\n\n");
    
    return true;
}



//---------------------------------------------------------------
//                     g e n  H e a d e r
//---------------------------------------------------------------

bool            genHeader(
    ASTR_DATA       *pStrType,
    ASTR_DATA       *pStrName,
    ASTR_DATA       *pStrDesc
)
{
    const
    char            *pFieldType = AStr_getData(pStrType);
    const
    char            *pFieldName = AStr_getData(pStrName);
    const
    char            *pDescription = pStrDesc ? AStr_getData(pStrDesc) : OBJ_NIL;

    if (strlen(pDescription)) {
        fprintf(stdout, "\t// %s\n", pDescription);
    }
    if (options.fSPN) {
        fprintf(stdout, "\t%s\t\t\t\t%s_getSpn%s(\n",
                pFieldType,
                AStr_getData(pObjName),
                pFieldName
                );
    }
    else {
        fprintf(stdout, "\t%s\t\t\t\t%s_get%s(\n",
                pFieldType,
                AStr_getData(pObjName),
                pFieldName
                );
    }
    fprintf(stdout, "\t\t%s_DATA\t*this\n", AStr_getData(pObjData));
    fprintf(stdout, "\t);\n\n");
    if (options.fSPN) {
        fprintf(stdout, "\tbool\t\t\t\t%s_setSpn%s(\n",
                AStr_getData(pObjName),
                pFieldName
                );
    }
    else {
        fprintf(stdout, "\tbool\t\t\t\t%s_set%s(\n",
                AStr_getData(pObjName),
                pFieldName
                );
    }
    fprintf(stdout, "\t\t%s_DATA\t*this,\n", AStr_getData(pObjData));
    fprintf(stdout, "\t\t%s\t\t\tvalue\n", pFieldType);
    fprintf(stdout, "\t);\n\n\n");
    
    return true;
}



//---------------------------------------------------------------
//                     p a r s e  A r g s
//---------------------------------------------------------------

bool            parseArgs(
    int             argc,
    const
    char            *argv[],
    OPTIONS         *pOptions
)
{
    int             offset;
    int             len;
    char            wrkstr[64];
    
    pProgramName = AStr_NewA(argv[0]);
    if (OBJ_NIL == pProgramName) {
        return false;
    }
    
    /* Setup input parameters.
     */
    for( argc--,argv++; argc>0; argc--,argv++ ) {
        if (0 == strcmp(*argv, "--debug")) {
            ++pOptions->fDebug;
        }
        else if (0 == strcmp(*argv, "--help")) {
            show_usage(NULL);
        }
        else if (0 == strcmp(*argv, "--quiet")) {
            ++pOptions->fQuiet;
        }
        else if (0 == strcmp(*argv, "--verbose")) {
            ++pOptions->verbose;
        }
        else if (0 == strcmp(*argv, "--header")) {
            ++pOptions->fGenHeader;
        }
        else if (0 == strcmp(*argv, "--spn")) {
            ++pOptions->fSPN;
        }
        else if (0 == strncmp(*argv, "--name", 6)) {
            wrkstr[0] = '\0';
            len = (int)strlen(*argv) - 6;
            offset = 6;
            if ('=' == *(*argv + offset)) {
                ++offset;
                --len;
            }
            if ('"' == *(*argv + offset)) {
                ++offset;
                len -= 2;
            }
            if (len > 63) {
                len =  63;
                fprintf(stderr, "WARNING - name is too long! Limiting length to 63!\n");
            }
            strncat(wrkstr, (*argv + offset), len);
            if (len) {
                pObjName = AStr_NewA(wrkstr);
                if (OBJ_NIL == pObjName) {
                    show_usage("invalid name");
                }
                pObjData = AStr_ToUpper(pObjName);
                if (pObjData) {
                }
                else {
                    show_usage("invalid data name");
                }
            }
        }
        else if( (**argv == '-') ) {
            while( *++(*argv) ) {
                switch( tolower( **argv	) ) {
                    case '-':
                        //FIXME: Parse "--xyzzy" style options
                        break;
                    case 'd':
                        ++pOptions->fDebug;
                        break;
                    case '?':
                    case 'h':
                        show_usage(NULL);
                        break;
                    case 'n':
                        ++(*argv);
                        if (*argv[0] == '=') {
                            ++(*argv);
                        }
                        pObjName = AStr_NewA(*argv);
                        if (OBJ_NIL == pObjName) {
                            show_usage("invalid name");
                        }
                        pObjData = AStr_ToUpper(pObjName);
                        if (pObjData) {
                        }
                        else {
                            show_usage("invalid data name");
                        }
                        ++argv;
                        --argc;
                        break;
                    case 'q':
                        ++pOptions->fDebug;
                        break;
                    case 's':
                        ++pOptions->fGenHeader;
                        break;
                    case 'v':
                        ++pOptions->verbose;
                        break;
                    default:
                        fprintf( stderr, "Fatal - illegal option - %c\n", **argv );
                        show_usage(NULL);
                }
            }
        }
        else
            break;
    }
    /* NOW THE ARGV[0] CONTAINS THE FIRST NON-OPTION ARGUMENT,
     * WHILE ARGC CONTAINS THE NUMBER OF ARGUMENTS LEFT.  SO
     * WE HAVE AVAILABLE ARGV[0] -- ARGV[ARGC-1].
     */
    if (argc > 0) {
        pOptions->pArg1 = argv[0];
        ++argv;
        --argc;
    }
    if (argc > 0) {
        pOptions->pArg2 = argv[0];
        ++argv;
        --argc;
    }
    if (argc > 0) {
        pOptions->pArg3 = argv[0];
        ++argv;
        --argc;
    }
    if (argc > 0) {
        pOptions->pArg4 = argv[0];
        ++argv;
        --argc;
    }
    
    
    return true;
}



//---------------------------------------------------------------
//                      p r i n t  C S V
//---------------------------------------------------------------

bool            printCSV(
)
{
    uint32_t        i;
    uint32_t        iMax;
    //uint32_t        j;
    uint32_t        jMax;
    OBJARRAY_DATA   *pEntry;
    ASTR_DATA       *pStrType;
    ASTR_DATA       *pStrName;
    ASTR_DATA       *pStrDesc;
    bool            fRc;
    
    if (pRecords) {
    }
    else {
        fprintf(stderr, "FATAL ERROR - Input pasred array!");
        exit(99);
    }
    
    iMax = objArray_getSize(pRecords);
    for (i=0; i<iMax; ++i) {
        pEntry = objArray_Get(pRecords, i+1);
        if (pEntry) {
            if (obj_getIdent(pEntry) == OBJ_IDENT_OBJARRAY) {
                jMax = objArray_getSize(pEntry);
                if (jMax >= 2) {
                    pStrType = objArray_Get(pEntry, 1);
                    pStrName = objArray_Get(pEntry, 2);
                    if (jMax > 2) {
                        pStrDesc = objArray_Get(pEntry, 3);
                    }
                    else {
                        pStrDesc = OBJ_NIL;
                    }
                    if (options.fGenHeader) {
                        fRc =   genHeader(
                                          pStrType,
                                          pStrName,
                                          pStrDesc
                                );
                    }
                    else {
                        fRc =   genBody(
                                        pStrType,
                                        pStrName,
                                        pStrDesc
                                );
                    }
                }
            }
            else {
                DEBUG_BREAK();
            }
        }
    }
    
    return true;
}




//---------------------------------------------------------------
//                      r e a d  C S V
//---------------------------------------------------------------

bool            readCSV(
    const
    char            *pFilePath
)
{
    DBCSV_DATA      *pCsv = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    
    if (pFilePath) {
        pPath = path_NewA(pFilePath);
        if (pPath) {
            pCsv = dbCsv_NewFile(pPath, 4);
            if (pCsv == OBJ_NIL) {
                fprintf(stderr, "FATAL ERROR - Missing input file path!");
                exit(99);
            }
        }
    }
    else {
        fprintf(stderr, "FATAL ERROR - Missing input file path!");
        exit(99);
    }
    
    //obj_setFlags(pCsv, (obj_getFlags(pCsv) | OBJ_FLAG_TRACE));
    pRecords = dbCsv_ParseFile(pCsv);
    if (pRecords == OBJ_NIL) {
        fprintf(stderr, "FATAL ERROR - dbCsv_ParseFile() failed!");
        exit(99);
    }
    
    if (options.fDebug) {
        ASTR_DATA           *pStr;
        pStr = objArray_ToDebugString(pRecords, 0);
        if (pStr) {
            fprintf(stderr, "%s\n",AStr_getData(pStr));
            obj_Release(pStr);
        }
    }
    
    return true;
}




//------------------------------------------------------------------
//             show_usage - Print program usage informatio.
//------------------------------------------------------------------

void			show_usage(
    const
    char            *pErrMsg
)
{
    fprintf(stderr, "usage: %s\n", AStr_getData(pProgramName));
    if (pErrMsg) {
        fprintf(stderr, "FATAL - %s!\n", pErrMsg);
    }
    fprintf(
            stderr,
            "%s(%s) - Generate Getters/Setters for inclusion into programs\n",
            AStr_getData(pProgramName),
            __DATE__
    );
    fprintf(stderr, "%s [-d][-v]* input_csv_path\n", AStr_getData(pProgramName) );
    fprintf(stderr, "Options:\n" );
    fprintf(stderr, "\t-d\t--debug\tDebug Mode\n" );
    fprintf(stderr, "\t-h\t--help\tDisplay this help\n" );
    fprintf(stderr, "\t-q\t--quiet\tMinimize message ouput\n" );
    fprintf(stderr, "\t-s\t--header\tGenerate .h inclusion instead of .c\n" );
    fprintf(
            stderr,
            "\t-v\t--Verbose\tmay be entered more than once for even more verbosity\n\n"
    );
    fprintf(stderr, "#field_type,field_name,field_description\n" );
    fprintf(stderr, "The input csv file has a minimum of 2 fields. The first is the\n" );
    fprintf(stderr, "field type such as 'uint8_t'. If it is a pointer, the '*' must\n" );
    fprintf(stderr, "be included. So, it would have to be quoted. The second field is\n" );
    fprintf(stderr, "field name. A third field being a description is optional.\n\n\n" );
    fprintf(stderr, "\n\n\n" );
    exit(EXIT_FAILURE);
}



//===============================================================
//                          M a i n
//===============================================================

int             main(
    int             argc,
    const
    char *          argv[]
)
{
    bool            fRc;
    
    @autoreleasepool {
        fRc = parseArgs(argc, argv, &options);
        if (!fRc) {
            show_usage(NULL);
        }
        if (options.pArg1 == NULL) {
            show_usage("Missing Input File Path");
        }
        
        fRc = readCSV(options.pArg1);
        if (!fRc) {
            fprintf(stderr, "FATAL ERROR - Could not parse csv file!");
            exit(99);
        }
        fRc = printCSV();
        if (!fRc) {
            fprintf(stderr, "FATAL ERROR - Could not print csv file!");
            exit(99);
        }
    }
    return 0;
}
