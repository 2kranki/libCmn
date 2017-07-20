//
//  main.c
//  genMake
//
//  Created by bob on 5/10/17.
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



#include <cmn_defs.h>
#include <ascii.h>
#include <dateTime.h>
#include <hjson.h>
#include <node.h>
#include <nodeArray.h>
#include <nodeHash.h>




void			show_usage(
);


typedef enum make_type_e {
    MAKETYPE_UNKNOW=0,
    MAKETYPE_MACOSX,
    MAKETYPE_MSC32,
    MAKETYPE_MSC64
} MAKETYPE;



typedef     struct args_s {
    const
    char            *pProgramPath;
    int             fDebug;             // -d or --debug or --no-debug
    int             fForce;             // --force or --no-force
    MAKETYPE        makeType;           // --MSC
    int             fNL;
    int             fWS;
    int             lexSelect;
    const
    char            *pInFilePath;      // ("-f" | "--file")<string> or ("-f" | "--file") <string>
    FILE            *pInput;
    int             mFlag;
    int             nFlag;
    const
    char            *pOutFilePath;     // ("-o" | "--out")<string> or ("-o" | "--out") <string>
    FILE            *pOutput;
    const
    char            *pR;                // -r=<string> or -r <string>
    
    int             cOptions;
    const
    char            **ppOptions;
    
    NODE_DATA       *pNodes;
    DATETIME_DATA   *pDateTime;
} ARGS;




ARGS args = {
    NULL,           // Program Path
    0,              // fDebug
    0,              // fForce
    MAKETYPE_MACOSX, // makeType
    0,              // fNL
    0,              // fWS
    0,              // Lex Select
    NULL,           // pInputFilePath
    NULL,           // Input File
    0,              // mFlag
    0,              // nFlag
    NULL,           // pOutFile
    NULL,           // Output File
    NULL,           // pR
    0,              // cOptions
    NULL,           // ppOptions
    
    OBJ_NIL,
    OBJ_NIL
};







//------------------------------------------------------------------
//             genMakeFile - Generate the Make File.
//------------------------------------------------------------------

void            genMakeFile_initial(
    ARGS            *pResults,
    ASTR_DATA       *pName,
    NODEARRAY_DATA  *pLibDeps
)
{
    NODE_DATA       *pNode;
    ASTR_DATA       *pStr;
    int             i;
    int             iMax;
    
    BREAK_NULL(pResults);
    
    switch (pResults->makeType) {
            
        case MAKETYPE_MACOSX:
            fprintf(pResults->pOutput, "# Generated file do not edit!\n");
            pStr = dateTime_ToString(pResults->pDateTime);
            fprintf(pResults->pOutput, "# (%s)\n\n", AStr_getData(pStr));
            obj_Release(pStr);
            fprintf(pResults->pOutput, "\n");
            //fprintf(pResults->pOutput, "CC=clang\n");
            fprintf(pResults->pOutput, "LIBNAM=%s\n", AStr_getData(pName));
            fprintf(pResults->pOutput, "SYS=macosx\n");
            fprintf(pResults->pOutput, "TEMP=/tmp\n");
            fprintf(pResults->pOutput, "BASEDIR = $(TEMP)/$(LIBNAM)\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "CFLAGS_LIBS = \n");
            fprintf(pResults->pOutput, "CFLAGS += -g -Isrc -Isrc/$(SYS)\n");
            if (pLibDeps) {
                iMax = nodeArray_getSize(pLibDeps);
                for (i=0; i<iMax; ++i) {
                    pNode = nodeArray_Get(pLibDeps, i+1);
                    if (pNode) {
                        pStr = node_getData(pNode);
                        fprintf(
                                pResults->pOutput,
                                "CFLAGS += -I../lib%s/src -I../lib%s/src/$(SYS)\n",
                                AStr_getData(pStr),
                                AStr_getData(pStr)
                        );
                        fprintf(
                                pResults->pOutput,
                                "CFLAGS_LIBS += -l%s -L$(HOME)/Support/lib/$(SYS)/lib%s\n",
                                AStr_getData(pStr),
                                AStr_getData(pStr)
                        );
                        obj_Release(pStr);
                    }
                }
            }
            fprintf(pResults->pOutput,"CFLAGS += -D__MACOSX_ENV__\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "INSTALL_BASE = $(HOME)/Support/lib/$(SYS)\n");
            fprintf(pResults->pOutput, "INSTALLDIR = $(INSTALL_BASE)/$(LIBNAM)\n");
            fprintf(pResults->pOutput, "LIBDIR = $(BASEDIR)/$(SYS)\n");
            fprintf(pResults->pOutput, "SRCDIR = ./src\n");
            fprintf(pResults->pOutput, "SRCSYSDIR = ./src/$(SYS)\n");
            fprintf(pResults->pOutput, "ifdef  NDEBUG\n");
            fprintf(pResults->pOutput, "CFLAGS += -DNDEBUG \n");
            fprintf(pResults->pOutput, "LIB_FILENAME=$(LIBNAM)R.a\n");
            fprintf(pResults->pOutput, "OBJDIR = $(LIBDIR)/o/r\n");
            fprintf(pResults->pOutput, "else   #DEBUG\n");
            fprintf(pResults->pOutput, "CFLAGS += -D_DEBUG \n");
            fprintf(pResults->pOutput, "LIB_FILENAME=$(LIBNAM)D.a\n");
            fprintf(pResults->pOutput, "OBJDIR = $(LIBDIR)/o/d\n");
            fprintf(pResults->pOutput, "endif  #NDEBUG\n");
            fprintf(pResults->pOutput, "LIBPATH = $(LIBDIR)/$(LIB_FILENAME)\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, ".SUFFIXES:\n");
            fprintf(pResults->pOutput, ".SUFFIXES: .asm .c .o\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            break;
            
        case MAKETYPE_MSC32:
            fprintf(pResults->pOutput, "# Generated file do not edit!\n");
            pStr = dateTime_ToString(pResults->pDateTime);
            fprintf(pResults->pOutput, "# (%s)\n\n", AStr_getData(pStr));
            obj_Release(pStr);
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "LIBNAM=%s\n", AStr_getData(pName));
            fprintf(pResults->pOutput, "SYS=win32\n");
            fprintf(
                    pResults->pOutput,
                    "INSTALL_BASE = $(HOMEDRIVE)$(HOMEPATH)\\Support\\lib\\$(SYS)\n"
            );
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "LIBS = \n");
            fprintf(pResults->pOutput, "CFLAGS = $(CFLAGS) /Isrc /Isrc\\$(SYS)\n");
            if (pLibDeps) {
                iMax = nodeArray_getSize(pLibDeps);
                for (i=0; i<iMax; ++i) {
                    pNode = nodeArray_Get(pLibDeps, i+1);
                    if (pNode) {
                        pStr = node_getData(pNode);
                        fprintf(
                                pResults->pOutput,
                                "CFLAGS = $(CFLAGS) /I..\\lib%s\\src "
                                "/I..\\lib%s\\src\\$(SYS)\n",
                                AStr_getData(pStr),
                                AStr_getData(pStr)
                                );
                        fprintf(
                                pResults->pOutput,
                                "LIBS = $(LIBS) "
                                "$(INSTALL_BASE)\\lib%s\\lib%s.lib\n",
                                AStr_getData(pStr),
                                AStr_getData(pStr)
                        );
                        obj_Release(pStr);
                    }
                }
            }
            fprintf(pResults->pOutput,"CFLAGS = $(CFLAGS) /D__MSVC32__ /D__WIN32_ENV__\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "INSTALLDIR = $(INSTALL_BASE)\\$(LIBNAM)\n");
            fprintf(pResults->pOutput, "!IFDEF  NDEBUG\n");
            fprintf(pResults->pOutput, "CFLAGS = $(CFLAGS) /DNDEBUG\n");
            fprintf(pResults->pOutput, "LIB_FILENAME=$(LIBNAM)R.lib\n");
            fprintf(pResults->pOutput, "OBJDIR = $(TEMP)\\$(SYS)\\Release\n");
            fprintf(pResults->pOutput, "LRFNAM = $(LIBNAM)_$(SYS)_r.lbc\n");
            fprintf(pResults->pOutput, "!ELSE   #DEBUG\n");
            fprintf(pResults->pOutput, "CFLAGS = $(CFLAGS) /D_DEBUG\n");
            fprintf(pResults->pOutput, "LIB_FILENAME=$(LIBNAM)D.lib\n");
            fprintf(pResults->pOutput, "OBJDIR = $(TEMP)\\$(SYS)\\Debug\n");
            fprintf(pResults->pOutput, "LRFNAM = $(LIBNAM)_$(SYS)_d.lbc\n");
            fprintf(pResults->pOutput, "!ENDIF  #NDEBUG\n");
            fprintf(pResults->pOutput, "LIBPATH = $(OBJDIR)\\$(LIB_FILENAME)\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, ".SUFFIXES:\n");
            fprintf(pResults->pOutput, ".SUFFIXES: .asm .c .cpp .obj\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            break;
            
        default:
            break;
    }
    
}



void            genMakeFile_objects(
    ARGS            *pResults,
    NODEHASH_DATA   *pObjects,
    NODEARRAY_DATA  *pRoutines
)
{
    ERESULT         eRc;
    NODE_DATA       *pNode;
    NODEARRAY_DATA  *pArray =  OBJ_NIL;
    ASTR_DATA       *pStr;
    int             i;
    int             iMax;
    const
    char            *pName;
    
    BREAK_NULL(pResults);
    
    switch (pResults->makeType) {
            
        case MAKETYPE_MACOSX:
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "OBJS =\n");
            if (pObjects) {
                eRc = nodeHash_Nodes(pObjects, &pArray);
                if (ERESULT_FAILED(eRc)) {
                }
                else {
                    BREAK_FALSE((obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)));
                    iMax = nodeArray_getSize(pArray);
                    for (i=0; i<iMax; ++i) {
                        pNode = nodeArray_Get(pArray, i+1);
                        if (pNode) {
                            pName = node_getNameUTF8(pNode);
                            fprintf(
                                    pResults->pOutput,
                                    "OBJS += $(OBJDIR)/%s.o $(OBJDIR)/%s_object.o\n",
                                    pName,
                                    pName
                            );
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "$(OBJDIR)/%s.o: $(SRCDIR)/%s.c\n",
                                    pName,
                                    pName
                            );
                            fprintf(pResults->pOutput,
                                    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $<\n");
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput,
                                    "$(OBJDIR)/%s_object.o: $(SRCDIR)/%s_object.c\n",
                                    pName,
                                    pName
                                    );
                            fprintf(pResults->pOutput,
                                    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $<\n");
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\n");
                            mem_Free((void *)pName);
                        }
                    }
                }
            }
            if (pRoutines) {
                iMax = nodeArray_getSize(pRoutines);
                for (i=0; i<iMax; ++i) {
                    pNode = nodeArray_Get(pRoutines, i+1);
                    if (pNode) {
                        ASTR_DATA       *pWrk;
                        pStr = node_getData(pNode);
                        pWrk = AStr_Copy(pStr);
                        if (AStr_CompareRightA(pWrk, ".c") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                            fprintf(pResults->pOutput,
                                    "$(OBJDIR)/%s.o: $(SRCDIR)/%s\n",
                                    AStr_getData(pWrk),
                                    AStr_getData(pStr)
                            );
                            fprintf(pResults->pOutput,
                                    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $<\n"
                            );
                            fprintf(pResults->pOutput, "\n");
                        }
                        else if (AStr_CompareRightA(pWrk, ".asm") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 4));
                            fprintf(pResults->pOutput,
                                    "$(OBJDIR)/%s.o: $(SRCDIR)/%s\n",
                                    AStr_getData(pWrk),
                                    AStr_getData(pStr)
                            );
                            fprintf(pResults->pOutput,
                                    "\t$(AS) $(AFLAGS) -c -o $(OBJDIR)/$(@F) $<\n"
                            );
                            fprintf(pResults->pOutput, "\n");
                        }
                        else if (AStr_CompareRightA(pWrk, ".s") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                            fprintf(pResults->pOutput,
                                    "$(OBJDIR)/%s.o: $(SRCDIR)/%s\n",
                                    AStr_getData(pWrk),
                                    AStr_getData(pStr)
                            );
                            fprintf(pResults->pOutput,
                                    "\t$(AS) $(AFLAGS) -o $(OBJDIR)/$(@F) $<\n"
                            );
                            fprintf(pResults->pOutput, "\n");
                        }
                        else if (AStr_CompareRightA(pWrk, ".cpp") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 4));
                            fprintf(pResults->pOutput,
                                    "$(OBJDIR)/%s.o: $(SRCDIR)/%s\n",
                                    AStr_getData(pWrk),
                                    AStr_getData(pStr)
                                    );
                            fprintf(pResults->pOutput,
                                    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $<\n"
                                    );
                            fprintf(pResults->pOutput, "\n");
                        }
                        fprintf(pResults->pOutput, "\n");
                        fprintf(pResults->pOutput, "\n");
                        fprintf(
                                pResults->pOutput,
                                "OBJS += $(OBJDIR)/%s.o\n",
                                AStr_getData(pWrk)
                        );
                        
                        obj_Release(pWrk);
                    }
                }
            }
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            break;
            
        case MAKETYPE_MSC32:
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "OBJS =\n");
            if (pObjects) {
                eRc = nodeHash_Nodes(pObjects, &pArray);
                if (ERESULT_FAILED(eRc)) {
                }
                else {
                    iMax = nodeArray_getSize(pArray);
                    for (i=0; i<iMax; ++i) {
                        pNode = nodeArray_Get(pArray, i+1);
                        if (pNode) {
                            pName = node_getNameUTF8(pNode);
                            fprintf(
                                    pResults->pOutput,
                                    "OBJS = $(OBJS) $(OBJDIR)\\%s.obj $(OBJDIR)\\%s_object.obj\n",
                                    pName,
                                    pName
                            );
                            mem_Free((void *)pName);
                        }
                    }
                }
            }
            if (pRoutines) {
                iMax = nodeArray_getSize(pRoutines);
                for (i=0; i<iMax; ++i) {
                    pNode = nodeArray_Get(pRoutines, i+1);
                    if (pNode) {
                        ASTR_DATA       *pWrk;
                        pStr = node_getData(pNode);
                        pWrk = AStr_Copy(pStr);
                        if (AStr_CompareRightA(pWrk, ".c") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                        }
                        else if (AStr_CompareRightA(pWrk, ".asm") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 4));
                        }
                        else if (AStr_CompareRightA(pWrk, ".s") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                        }
                        else if (AStr_CompareRightA(pWrk, ".cpp") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 4));
                        }
                        fprintf(
                                pResults->pOutput,
                                "OBJS = $(OBJS) $(OBJDIR)\\%s.obj\n",
                                AStr_getData(pWrk)
                        );
                        
                        obj_Release(pWrk);
                    }
                }
            }
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "{src}.asm{$(OBJDIR)}.obj:\n");
            fprintf(pResults->pOutput, "\t$(AS) $(AFLAGS) /c /Fo$(OBJDIR)\\$(@F) $<\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "{src}.c{$(OBJDIR)}.obj:\n");
            fprintf(pResults->pOutput, "\t$(CC) $(CFLAGS) /c /Fo$(OBJDIR)\\$(@F) $<\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "{src\\$(SYS)}.asm{$(OBJDIR)}.obj:\n");
            fprintf(pResults->pOutput, "\t$(AS) $(AFLAGS) /c /Fo$(OBJDIR)\\$(@F) $<\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "{src\\$(SYS)}.c{$(OBJDIR)}.obj:\n");
            fprintf(pResults->pOutput, "\t$(CC) $(CFLAGS) /c /Fo$(OBJDIR)\\$(@F) $<\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            break;
            
        default:
            break;
    }
    
}



void            genMakeFile_macosx(
    ARGS            *pResults,
    NODEHASH_DATA   *pObjects
)
{
    ERESULT         eRc;
    NAME_DATA       *pName;
    NODE_DATA       *pNode;
    NODEARRAY_DATA  *pArray =  OBJ_NIL;
    int             i;
    int             iMax;
    ASTR_DATA       *pStr;
    ASTR_DATA       *pWrk;
    
    BREAK_NULL(pResults);
    
    switch (pResults->makeType) {
            
        case MAKETYPE_MACOSX:
            if (pObjects) {
                eRc = nodeHash_Nodes(pObjects, &pArray);
                if (ERESULT_FAILED(eRc)) {
                }
                else {
                    iMax = nodeArray_getSize(pArray);
                    for (i=0; i<iMax; ++i) {
                        pNode = nodeArray_Get(pArray, i+1);
                        if (pNode) {
                            pName = node_getName(pNode);
                            pStr = name_getStrA(pName);
                            pWrk = AStr_Copy(pStr);
                            if (AStr_CompareRightA(pWrk, ".c") == ERESULT_SUCCESS_EQUAL) {
                                AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                            }
                            else if (AStr_CompareRightA(pWrk, ".asm") == ERESULT_SUCCESS_EQUAL) {
                                AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 4));
                            }
                            else if (AStr_CompareRightA(pWrk, ".s") == ERESULT_SUCCESS_EQUAL) {
                                AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                            }
                            else if (AStr_CompareRightA(pWrk, ".cpp") == ERESULT_SUCCESS_EQUAL) {
                                AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 4));
                            }
                            fprintf(
                                    pResults->pOutput,
                                    "OBJS += $(OBJDIR)/%s.o\n",
                                    AStr_getData(pWrk)
                            );
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput,
                                    "$(OBJDIR)/%s.o: src/$(SYS)/%s\n",
                                    AStr_getData(pWrk),
                                    AStr_getData(pStr)
                            );
                            if (AStr_CompareRightA(pStr, ".c") == ERESULT_SUCCESS_EQUAL) {
                                fprintf(pResults->pOutput,
                                        "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) "
                                        "src/$(SYS)/%s\n",
                                        AStr_getData(pStr)
                                );
                            }
                            else if (AStr_CompareRightA(pStr, ".asm") == ERESULT_SUCCESS_EQUAL) {
                                fprintf(pResults->pOutput,
                                        "\t$(AS) $(AFLAGS) -o $(OBJDIR)/$(@F) "
                                        "src/$(SYS)/%s\n",
                                        AStr_getData(pStr)
                                );
                            }
                            else if (AStr_CompareRightA(pStr, ".s") == ERESULT_SUCCESS_EQUAL) {
                                fprintf(pResults->pOutput,
                                        "\t$(AS) $(AFLAGS) -o $(OBJDIR)/$(@F) "
                                        "src/$(SYS)/%s\n",
                                        AStr_getData(pStr)
                                );
                            }
                            else if (AStr_CompareRightA(pStr, ".cpp") == ERESULT_SUCCESS_EQUAL) {
                                fprintf(pResults->pOutput,
                                        "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) "
                                        "src/$(SYS)/%s\n",
                                        AStr_getData(pStr)
                                );
                            }
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\n");
                            obj_Release(pWrk);
                            pWrk = OBJ_NIL;
                            obj_Release(pStr);
                            pStr = OBJ_NIL;
                        }
                    }
                }
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
            }
            break;
            
        default:
            break;
    }
    
}



void            genMakeFile_win32(
    ARGS            *pResults,
    NODEHASH_DATA   *pObjects
)
{
    ERESULT         eRc;
    NAME_DATA       *pName;
    NODE_DATA       *pNode;
    NODEARRAY_DATA  *pArray =  OBJ_NIL;
    int             i;
    int             iMax;
    ASTR_DATA       *pStr;
    ASTR_DATA       *pWrk;
    
    BREAK_NULL(pResults);
    
    switch (pResults->makeType) {
            
        case MAKETYPE_MSC32:
            if (pObjects) {
                eRc = nodeHash_Nodes(pObjects, &pArray);
                if (ERESULT_FAILED(eRc)) {
                }
                else {
                    iMax = nodeArray_getSize(pArray);
                    for (i=0; i<iMax; ++i) {
                        pNode = nodeArray_Get(pArray, i+1);
                        if (pNode) {
                            pName = node_getName(pNode);
                            pStr = name_getStrA(pName);
                            pWrk = AStr_Copy(pStr);
                            if (AStr_CompareRightA(pWrk, ".c") == ERESULT_SUCCESS_EQUAL) {
                                AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                            }
                            else if (AStr_CompareRightA(pWrk, ".asm") == ERESULT_SUCCESS_EQUAL) {
                                AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 4));
                            }
                            else if (AStr_CompareRightA(pWrk, ".s") == ERESULT_SUCCESS_EQUAL) {
                                AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                            }
                            else if (AStr_CompareRightA(pWrk, ".cpp") == ERESULT_SUCCESS_EQUAL) {
                                AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 4));
                            }
                            fprintf(
                                    pResults->pOutput,
                                    "OBJS = $(OBJS) $(OBJDIR)\\%s.obj\n\n",
                                    AStr_getData(pWrk)
                            );
                            fprintf(pResults->pOutput,
                                    "$(OBJDIR)\\%s.obj:\n",
                                    AStr_getData(pWrk)
                            );
                            if (AStr_CompareRightA(pStr, ".c") == ERESULT_SUCCESS_EQUAL) {
                                fprintf(pResults->pOutput,
                                        "\t$(CC) $(CFLAGS) /c /Fo$(OBJDIR)\\$(@F) "
                                        "src\\$(SYS)\\%s\n",
                                        AStr_getData(pStr)
                                );
                            }
                            else if (AStr_CompareRightA(pStr, ".asm") == ERESULT_SUCCESS_EQUAL) {
                                fprintf(pResults->pOutput,
                                        "\t$(AS) $(AFLAGS) /c /Fo$(OBJDIR)\\$(@F) "
                                        "src\\$(SYS)\\%s\n",
                                        AStr_getData(pStr)
                                );
                            }
                            else if (AStr_CompareRightA(pStr, ".s") == ERESULT_SUCCESS_EQUAL) {
                                fprintf(pResults->pOutput,
                                        "\t$(AS) $(AFLAGS) /c /Fo$(OBJDIR)\\$(@F) "
                                        "src\\$(SYS)\\%s\n",
                                        AStr_getData(pStr)
                                );
                            }
                            else if (AStr_CompareRightA(pStr, ".cpp") == ERESULT_SUCCESS_EQUAL) {
                                fprintf(pResults->pOutput,
                                        "\t$(CC) $(CFLAGS) /c /Fo$(OBJDIR)\\$(@F) "
                                        "src\\$(SYS)\\%s\n",
                                        AStr_getData(pStr)
                                );
                            }
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\n");
                            obj_Release(pWrk);
                            pWrk = OBJ_NIL;
                            obj_Release(pStr);
                            pStr = OBJ_NIL;
                        }
                    }
                }
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
            }
            break;
            
        default:
            break;
    }
    
}



void            genMakeFile_library(
    ARGS            *pResults
)
{
    
    BREAK_NULL(pResults);
    
    switch (pResults->makeType) {
            
        case MAKETYPE_MACOSX:
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "$(LIBPATH):  $(OBJS)\n");
            fprintf(pResults->pOutput,
                    "\t-cd $(LIBDIR) ; [ -d $(LIB_FILENAME) ] && rm $(LIB_FILENAME)\n"
            );
            fprintf(pResults->pOutput, "\tar rc $(LIBPATH) $(OBJS)\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            break;
            
        case MAKETYPE_MSC32:
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "$(LIBPATH):  $(OBJS)\n");
            fprintf(pResults->pOutput, "\tcd $(OBJDIR)\n");
            fprintf(pResults->pOutput, "\tif exist $(LIB_FILENAME) del $(LIB_FILENAME)\n");
            fprintf(pResults->pOutput, "\tlib /OUT:$(LIB_FILENAME) @<<$(LRFNAM)\n");
            fprintf(pResults->pOutput, "$(OBJS: =  )\n");
            fprintf(pResults->pOutput, "<<NOKEEP\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            break;
            
        default:
            break;
    }
    
}



void            genMakeFile_programs(
    ARGS            *pResults,
    NODEHASH_DATA   *pTests
)
{
    ERESULT         eRc;
    NODE_DATA       *pNode;
    NODEARRAY_DATA  *pArray =  OBJ_NIL;
    NODEARRAY_DATA  *pDeps =  OBJ_NIL;
    NODE_DATA       *pDep;
    ASTR_DATA       *pStr;
    ASTR_DATA       *pPgmWrk;
    int             i;
    int             iMax;
    int             j;
    int             jMax;
    
    BREAK_NULL(pResults);
    BREAK_FALSE((obj_IsKindOf(pTests, OBJ_IDENT_NODEHASH)));
    
    switch (pResults->makeType) {
            
        case MAKETYPE_MACOSX:
            if (pTests) {
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "PROGS =\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                eRc = nodeHash_Nodes(pTests, &pArray);
                if (ERESULT_FAILED(eRc)) {
                }
                else {
                    BREAK_FALSE((obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)));
                    iMax = nodeArray_getSize(pArray);
                    for (i=0; i<iMax; ++i) {
                        pNode = nodeArray_Get(pArray, i+1);
                        if (pNode) {
                            ASTR_DATA       *pWrk;
                            BREAK_FALSE((obj_IsKindOf(pNode, OBJ_IDENT_NODE)));
                            pStr = name_getStrA(node_getName(pNode));
                            pWrk = AStr_Copy(pStr);
                            if (AStr_CompareRightA(pWrk, ".c") == ERESULT_SUCCESS_EQUAL) {
                                AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                            }
                            pPgmWrk = AStr_Copy(pWrk);
                            fprintf(pResults->pOutput, "PROGS += %s\n", AStr_getData(pWrk));
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "%s:\n", AStr_getData(pWrk));
                            fprintf(pResults->pOutput,
                                    "\t$(CC) "
                                    "$(CFLAGS) "
                                    "$(CFLAGS_LIBS) "
                                    "-L$(LIBDIR) "
                                    "-Iprograms/%s "
                                    "$(LIBPATH) "
                                    "-o $(OBJDIR)/$(@F) "
                                    "programs/%s/%s ",
                                    AStr_getData(pWrk),
                                    AStr_getData(pWrk),
                                    AStr_getData(pStr)
                            );
                            pDep = node_getData(pNode);
                            if (pDep) {
                                BREAK_FALSE((obj_IsKindOf(pDep, OBJ_IDENT_NODE)));
                                pDeps = node_getData(pDep);
                            }
                            else {
                                pDeps = OBJ_NIL;
                            }
                            if (pDeps && obj_IsKindOf(pDeps, OBJ_IDENT_NODEARRAY)) {
                                jMax = nodeArray_getSize(pDeps);
                                for (j=0; j<jMax; ++j) {
                                    pNode = nodeArray_Get(pDeps, j+1);
                                    if (pNode) {
                                        ASTR_DATA       *pWrk;
                                        pWrk = node_getData(pNode);
                                        if (pWrk && obj_IsKindOf(pWrk, OBJ_IDENT_ASTR)) {
                                            fprintf(pResults->pOutput,
                                                    "programs/%s/%s ",
                                                    AStr_getData(pPgmWrk),
                                                    AStr_getData(pWrk)
                                                    );
                                        }
                                    }
                                }
                                obj_Release(pDeps);
                                pDeps = OBJ_NIL;
                                obj_Release(pPgmWrk);
                                pPgmWrk = OBJ_NIL;
                            }
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\techo $(OBJDIR)/$(@F)\n");
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\n");
                            
                            obj_Release(pWrk);
                        }
                    }
                    obj_Release(pArray);
                    pArray = OBJ_NIL;
                }
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, ".PHONY: programs\n");
                fprintf(pResults->pOutput, "programs:  $(PROGS)\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
            }
            break;
            
        case MAKETYPE_MSC32:
            if (pTests) {
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "PROGS =\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                eRc = nodeHash_Nodes(pTests, &pArray);
                if (ERESULT_FAILED(eRc)) {
                }
                else {
                    BREAK_FALSE((obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)));
                    iMax = nodeArray_getSize(pArray);
                    for (i=0; i<iMax; ++i) {
                        pNode = nodeArray_Get(pArray, i+1);
                        if (pNode) {
                            ASTR_DATA       *pWrk;
                            BREAK_FALSE((obj_IsKindOf(pNode, OBJ_IDENT_NODE)));
                            pStr = name_getStrA(node_getName(pNode));
                            BREAK_FALSE((obj_IsKindOf(pStr, OBJ_IDENT_ASTR)));
                            pWrk = AStr_Copy(pStr);
                            if (AStr_CompareRightA(pWrk, ".c") == ERESULT_SUCCESS_EQUAL) {
                                AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                            }
                            pPgmWrk = AStr_Copy(pWrk);
                            fprintf(
                                    pResults->pOutput,
                                    "PROGS = $(PROGS) %s\n",
                                    AStr_getData(pWrk)
                                    );
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "%s:\n", AStr_getData(pWrk));
                            fprintf(pResults->pOutput,
                                    "\t$(CC) $(CFLAGS) /Iprograms\\%s "
                                    "programs\\%s\\%s ",
                                    AStr_getData(pWrk),
                                    AStr_getData(pWrk),
                                    AStr_getData(pStr)
                            );
                            pDep = node_getData(pNode);
                            if (pDep) {
                                BREAK_FALSE((obj_IsKindOf(pDep, OBJ_IDENT_NODE)));
                                pDeps = node_getData(pDep);
                            }
                            else {
                                pDeps = OBJ_NIL;
                            }
                            if (pDeps && obj_IsKindOf(pDeps, OBJ_IDENT_NODEARRAY)) {
                                jMax = nodeArray_getSize(pDeps);
                                for (j=0; j<jMax; ++j) {
                                    pNode = nodeArray_Get(pDeps, j+1);
                                    if (pNode) {
                                        ASTR_DATA       *pWrk;
                                        pWrk = node_getData(pNode);
                                        if (pWrk && obj_IsKindOf(pWrk, OBJ_IDENT_ASTR)) {
                                            fprintf(pResults->pOutput,
                                                    "programs\\%s\\%s ",
                                                    AStr_getData(pPgmWrk),
                                                    AStr_getData(pWrk)
                                                    );
                                        }
                                    }
                                }
                                obj_Release(pDeps);
                                pDeps = OBJ_NIL;
                            }
                            fprintf(pResults->pOutput,
                                    "/link "
                                    "/out:$(OBJDIR)\\$(@F).exe "
                                    "$(LIBPATH) $(LIBS) "
                                    );
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\tdel *.obj\n");
                            fprintf(pResults->pOutput, "\t$(OBJDIR)\\$(@F).exe\n");
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\n");
                            
                            obj_Release(pWrk);
                            obj_Release(pPgmWrk);
                            pPgmWrk = OBJ_NIL;
                        }
                    }
                    obj_Release(pArray);
                    pArray = OBJ_NIL;
                }
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "programs:  $(PROGS)\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
            }
            break;
            
        default:
            break;
    }
    
}



void            genMakeFile_tests(
    ARGS            *pResults,
    NODEHASH_DATA   *pTests
)
{
    ERESULT         eRc;
    NODE_DATA       *pNode;
    NODEARRAY_DATA  *pArray =  OBJ_NIL;
    NODEARRAY_DATA  *pDeps =  OBJ_NIL;
    NODE_DATA       *pDep;
    ASTR_DATA       *pStr;
    int             i;
    int             iMax;
    int             j;
    int             jMax;
    
    BREAK_NULL(pResults);
    BREAK_FALSE((obj_IsKindOf(pTests, OBJ_IDENT_NODEHASH)));
    
    switch (pResults->makeType) {
            
        case MAKETYPE_MACOSX:
            if (pTests) {
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "TESTS =\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                eRc = nodeHash_Nodes(pTests, &pArray);
                if (ERESULT_FAILED(eRc)) {
                }
                else {
                    BREAK_FALSE((obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)));
                    iMax = nodeArray_getSize(pArray);
                    for (i=0; i<iMax; ++i) {
                        pNode = nodeArray_Get(pArray, i+1);
                        if (pNode) {
                            ASTR_DATA       *pWrk;
                            BREAK_FALSE((obj_IsKindOf(pNode, OBJ_IDENT_NODE)));
                            pStr = name_getStrA(node_getName(pNode));
                            pWrk = AStr_Copy(pStr);
                            if (AStr_CompareRightA(pWrk, ".c") == ERESULT_SUCCESS_EQUAL) {
                                AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                            }
                            fprintf(pResults->pOutput, "TESTS += %s\n", AStr_getData(pWrk));
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "%s:\n", AStr_getData(pWrk));
                            fprintf(pResults->pOutput,
                                    "\t$(CC) "
                                    "$(CFLAGS) "
                                    "$(CFLAGS_LIBS) "
                                    "-L$(LIBDIR) "
                                    "-Itests "
                                    "$(LIBPATH) "
                                    "-o $(OBJDIR)/$(@F) "
                                    "tests/%s ",
                                    AStr_getData(pStr)
                            );
                            pDep = node_getData(pNode);
                            if (pDep) {
                                BREAK_FALSE((obj_IsKindOf(pDep, OBJ_IDENT_NODE)));
                                pDeps = node_getData(pDep);
                            }
                            else {
                                pDeps = OBJ_NIL;
                            }
                            if (pDeps && obj_IsKindOf(pDeps, OBJ_IDENT_NODEARRAY)) {
                                jMax = nodeArray_getSize(pDeps);
                                for (j=0; j<jMax; ++j) {
                                    pNode = nodeArray_Get(pDeps, j+1);
                                    if (pNode) {
                                        ASTR_DATA       *pWrk;
                                        pWrk = node_getData(pNode);
                                        if (pWrk && obj_IsKindOf(pWrk, OBJ_IDENT_ASTR)) {
                                            fprintf(pResults->pOutput,
                                                    "tests/%s ",
                                                    AStr_getData(pWrk)
                                            );
                                        }
                                    }
                                }
                                obj_Release(pDeps);
                                pDeps = OBJ_NIL;
                           }
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\t$(OBJDIR)/$(@F)\n");
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\n");
                            
                            obj_Release(pWrk);
                        }
                    }
                    obj_Release(pArray);
                    pArray = OBJ_NIL;
                }
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, ".PHONY: test\n");
                fprintf(pResults->pOutput, "test:  $(TESTS)\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
            }
            break;
            
        case MAKETYPE_MSC32:
            if (pTests) {
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "TESTS =\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                eRc = nodeHash_Nodes(pTests, &pArray);
                if (ERESULT_FAILED(eRc)) {
                }
                else {
                    BREAK_FALSE((obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)));
                    iMax = nodeArray_getSize(pArray);
                    for (i=0; i<iMax; ++i) {
                        pNode = nodeArray_Get(pArray, i+1);
                        if (pNode) {
                            ASTR_DATA       *pWrk;
                            BREAK_FALSE((obj_IsKindOf(pNode, OBJ_IDENT_NODE)));
                            pStr = name_getStrA(node_getName(pNode));
                            BREAK_FALSE((obj_IsKindOf(pStr, OBJ_IDENT_ASTR)));
                            pWrk = AStr_Copy(pStr);
                            if (AStr_CompareRightA(pWrk, ".c") == ERESULT_SUCCESS_EQUAL) {
                                AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                            }
                            fprintf(
                                    pResults->pOutput,
                                    "TESTS = $(TESTS) %s\n",
                                    AStr_getData(pWrk)
                            );
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "%s:\n", AStr_getData(pWrk));
                            fprintf(pResults->pOutput,
                                    "\t$(CC) $(CFLAGS) /Itests "
                                    "tests\\%s ",
                                    AStr_getData(pStr)
                            );
                            pDep = node_getData(pNode);
                            if (pDep) {
                                BREAK_FALSE((obj_IsKindOf(pDep, OBJ_IDENT_NODE)));
                                pDeps = node_getData(pDep);
                            }
                            else {
                                pDeps = OBJ_NIL;
                            }
                            if (pDeps && obj_IsKindOf(pDeps, OBJ_IDENT_NODEARRAY)) {
                                jMax = nodeArray_getSize(pDeps);
                                for (j=0; j<jMax; ++j) {
                                    pNode = nodeArray_Get(pDeps, j+1);
                                    if (pNode) {
                                        ASTR_DATA       *pWrk;
                                        pWrk = node_getData(pNode);
                                        if (pWrk && obj_IsKindOf(pWrk, OBJ_IDENT_ASTR)) {
                                            fprintf(pResults->pOutput,
                                                    "tests\\%s ",
                                                    AStr_getData(pWrk)
                                                    );
                                        }
                                    }
                                }
                                obj_Release(pDeps);
                                pDeps = OBJ_NIL;
                            }
                            fprintf(pResults->pOutput,
                                    "/link "
                                    "/out:$(OBJDIR)\\$(@F).exe "
                                    "$(LIBPATH) $(LIBS) "
                            );
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\tdel *.obj\n");
                            fprintf(pResults->pOutput, "\t$(OBJDIR)\\$(@F).exe\n");
                            fprintf(pResults->pOutput, "\n");
                            fprintf(pResults->pOutput, "\n");
                            
                            obj_Release(pWrk);
                        }
                    }
                    obj_Release(pArray);
                    pArray = OBJ_NIL;
                }
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "test:  $(TESTS)\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
                fprintf(pResults->pOutput, "\n");
            }
            break;
            
        default:
            break;
    }
    
}



void            genMakeFile_final(
    ARGS            *pResults
)
{
    
    BREAK_NULL(pResults);
    
    switch (pResults->makeType) {
            
        case MAKETYPE_MACOSX:
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, ".PHONY: clean\n");
            fprintf(pResults->pOutput, "clean:\n");
            fprintf(
                    pResults->pOutput,
                    "\t-cd $(TEMP) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n"
            );
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, ".PHONY: install\n");
            fprintf(pResults->pOutput, "install:\n");
            fprintf(
                pResults->pOutput,
                "\t-cd $(INSTALL_BASE) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n"
            );
            fprintf(
                pResults->pOutput,
                "\t-cd $(INSTALL_BASE) ; "
                "[ ! -d $(LIBNAM)/include ] && mkdir -p $(LIBNAM)/include\n"
            );
            fprintf(pResults->pOutput, "\tcp $(LIBPATH) $(INSTALLDIR)/$(LIBNAM).a\n");
            fprintf(pResults->pOutput, "\tcp src/*.h $(INSTALLDIR)/include/\n");
            fprintf(pResults->pOutput, "\tif [ -d src/$(SYS) ]; then \\\n");
            fprintf(pResults->pOutput, "\t\tcp src/$(SYS)/*.h $(INSTALLDIR)/include/; \\\n");
            fprintf(pResults->pOutput, "\tfi\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, ".PHONY: create_dirs\n");
            fprintf(pResults->pOutput, "create_dirs:\n");
            fprintf(pResults->pOutput, "\t[ ! -d $(OBJDIR) ] && mkdir -p $(OBJDIR)\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, ".PHONY: all\n");
            fprintf(pResults->pOutput, "all:  clean create_dirs $(LIBPATH)\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            break;
            
        case MAKETYPE_MSC32:
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "clean:\n");
            fprintf(pResults->pOutput, "\tif exist $(OBJDIR) rmdir /S /Q $(OBJDIR)\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "create_dirs:\n");
            fprintf(pResults->pOutput, "\tif not exist $(OBJDIR) mkdir $(OBJDIR)\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "all:  clean create_dirs $(LIBPATH)\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "install:\n");
            fprintf(
                    pResults->pOutput,
                    "\tpushd $(INSTALL_BASE) & "
                    "if exist $(LIBNAM) rmdir /S /Q $(LIBNAM) & "
                    "popd"
                    "\n"
            );
            fprintf(
                    pResults->pOutput,
                    "\tpushd $(INSTALL_BASE) & "
                    "mkdir $(LIBNAM)\\include & "
                    "popd"
                    "\n"
            );
            fprintf(pResults->pOutput, "\tcopy $(LIBPATH) $(INSTALLDIR)\\$(LIBNAM).lib\n");
            fprintf(pResults->pOutput, "\tcopy src\\*.h $(INSTALLDIR)\\include\n");
            fprintf(
                    pResults->pOutput,
                    "\tif exist src\\$(SYS) "
                    "copy src\\$(SYS)\\*.h $(INSTALLDIR)\\include\n"
            );
            fprintf(pResults->pOutput, "\n");
            fprintf(pResults->pOutput, "\n");
            break;
            
        default:
            break;
    }
    
}



int             genMakeFile(
    ARGS            *pResults
)
{
    ERESULT         eRc;
    NODE_DATA       *pNode;
    NODEARRAY_DATA  *pLibDeps = OBJ_NIL;
    NODEHASH_DATA   *pPrimaryHash;
    NODEHASH_DATA   *pObjects;
    NODEHASH_DATA   *pPrograms = OBJ_NIL;
    NODEARRAY_DATA  *pRoutines = OBJ_NIL;
    NODEHASH_DATA   *pTests = OBJ_NIL;
    NODEHASH_DATA   *pMacosx = OBJ_NIL;
    NODEHASH_DATA   *pWin32 = OBJ_NIL;
    ASTR_DATA       *pName = OBJ_NIL;
    
    BREAK_NULL(pResults);
    BREAK_NULL(pResults->pNodes);

    pPrimaryHash = node_getData(pResults->pNodes);
    BREAK_FALSE((obj_IsKindOf(pPrimaryHash, OBJ_IDENT_NODEHASH)));
    if (pPrimaryHash) {
        eRc = nodeHash_FindA(pPrimaryHash, "name", &pNode);
        if (ERESULT_FAILED(eRc)) {
        }
        else {
            pNode = node_getData(pNode);
            pName = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pName, OBJ_IDENT_ASTR)));
        }
        eRc = nodeHash_FindA(pPrimaryHash, "lib_deps", &pNode);
        if (ERESULT_FAILED(eRc)) {
        }
        else {
            pNode = node_getData(pNode);
            pLibDeps = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pLibDeps, OBJ_IDENT_NODEARRAY)));
        }
        eRc = nodeHash_FindA(pPrimaryHash, "objects", &pNode);
        if (ERESULT_FAILED(eRc)) {
        }
        else {
            pNode = node_getData(pNode);
            pObjects = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pObjects, OBJ_IDENT_NODEHASH)));
        }
        eRc = nodeHash_FindA(pPrimaryHash, "routines", &pNode);
        if (ERESULT_FAILED(eRc)) {
        }
        else {
            pNode = node_getData(pNode);
            pRoutines = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pRoutines, OBJ_IDENT_NODEARRAY)));
        }
        eRc = nodeHash_FindA(pPrimaryHash, "programs", &pNode);
        if (ERESULT_FAILED(eRc)) {
        }
        else {
            pNode = node_getData(pNode);
            pPrograms = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pPrograms, OBJ_IDENT_NODEHASH)));
        }
        eRc = nodeHash_FindA(pPrimaryHash, "tests", &pNode);
        if (ERESULT_FAILED(eRc)) {
        }
        else {
            pNode = node_getData(pNode);
            pTests = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pTests, OBJ_IDENT_NODEHASH)));
        }
        eRc = nodeHash_FindA(pPrimaryHash, "macosx", &pNode);
        if (ERESULT_FAILED(eRc)) {
        }
        else {
            pNode = node_getData(pNode);
            pMacosx = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pMacosx, OBJ_IDENT_NODEHASH)));
        }
        eRc = nodeHash_FindA(pPrimaryHash, "win32", &pNode);
        if (ERESULT_FAILED(eRc)) {
        }
        else {
            pNode = node_getData(pNode);
            pWin32 = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pWin32, OBJ_IDENT_NODEHASH)));
        }
    }

    genMakeFile_initial(pResults, pName, pLibDeps);
    genMakeFile_objects(pResults, pObjects, pRoutines);
    switch (pResults->makeType) {
            
        case MAKETYPE_MACOSX:
            if (pMacosx) {
                genMakeFile_macosx(pResults, pMacosx);
            }
           break;
            
        case MAKETYPE_MSC32:
            if (pWin32) {
                genMakeFile_win32(pResults, pWin32);
            }
            break;
            
        default:
            break;
    }
    genMakeFile_library(pResults);
    if (pPrograms) {
        genMakeFile_programs(pResults, pPrograms);
    }
    genMakeFile_tests(pResults, pTests);
    genMakeFile_final(pResults);
    
    return 0;
}




//------------------------------------------------------------------
//             parseArgs - Parse the command line arguments.
//------------------------------------------------------------------

int         parseArgs(
    int         argc,
    const
    char        *argv[],
    ARGS        *pResults
)
{
    int         wrkArgC = argc;
    const
    char        **ppWrkArgV = argv;
    int         i;
    
    BREAK_NULL(pResults);
    if (pResults && pResults->fDebug) {
        fprintf(stdout, "parseArgs args(%d):\n", wrkArgC);
        for (i=0; i<wrkArgC; ++i) {
            fprintf(stdout, "arg[%d]=\"%s\"\n", i, ppWrkArgV[i]);
        }
        fprintf(stdout, "\n");
    }
    if (NULL == pResults) {
        return -1;
    }
    
    // Validate some of the input.
    pResults->pProgramPath = argv[0];
    if( wrkArgC <= 1 ) {
        show_usage( "No arguments" );
    }
    if( wrkArgC == 2 && ppWrkArgV[1][0] == '?' && ppWrkArgV[1][1] == 0) {
        //help( documentation );
        //help( patdoc );
        return 1;
    }
    
    // Process the switches.
    for (wrkArgC--,ppWrkArgV++; wrkArgC>0; wrkArgC--,ppWrkArgV++) {
        if (0 == strcmp(*ppWrkArgV, "--debug")) {
            ++pResults->fDebug;
        }
        else if (0 == strcmp(*ppWrkArgV, "--no-debug")) {
            --pResults->fDebug;
        }
        else if (0 == strncmp(*ppWrkArgV, "--file", 6)) {
            if (*(*ppWrkArgV+6) == '\0') {
                ++ppWrkArgV;
                --wrkArgC;
                if (wrkArgC <= 0) {
                    show_usage("ERROR: --file is missing the path!\n");
                    return 99;
                }
                pResults->pInFilePath = strdup(*ppWrkArgV);
            }
            else {
                pResults->pInFilePath = strdup(*ppWrkArgV+6);
            }
        }
        else if (0 == strcmp(*ppWrkArgV, "--force")) {
            ++pResults->fForce;
        }
        else if (0 == strcmp(*ppWrkArgV, "--no-force")) {
            --pResults->fForce;
        }
        else if (0 == strcmp(*ppWrkArgV, "--macosx")) {
            pResults->makeType = MAKETYPE_MACOSX;
        }
        else if (0 == strcmp(*ppWrkArgV, "--msc32")) {
            pResults->makeType = MAKETYPE_MSC32;
        }
        else if (0 == strcmp(*ppWrkArgV, "--msc64")) {
            pResults->makeType = MAKETYPE_MSC64;
        }
        else if (0 == strcmp(*ppWrkArgV, "--nl")) {
            pResults->fNL = 1;
        }
        else if (0 == strcmp(*ppWrkArgV, "--no-nl")) {
            pResults->fNL = 0;
        }
        else if (0 == strncmp(*ppWrkArgV, "--out", 6)) {
            if (*(*ppWrkArgV+6) == '\0') {
                ++ppWrkArgV;
                --wrkArgC;
                if (wrkArgC <= 0) {
                    show_usage("ERROR: --out is missing the path!\n");
                    return 99;
                }
                pResults->pOutFilePath = strdup(*ppWrkArgV);
            }
            else {
                pResults->pOutFilePath = strdup(*ppWrkArgV+6);
            }
        }
        else if (0 == strcmp(*ppWrkArgV, "--ws")) {
            pResults->fWS = 1;
        }
        else if (0 == strcmp(*ppWrkArgV, "--no-ws")) {
            pResults->fWS = 0;
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
                switch(ascii_toLowerA(*pWrk)) {
                    case 'd':
                        ++pResults->fDebug;
                        break;
                    case 'f':
                        ++pWrk;
                        if (*pWrk == '\0') {
                            ++ppWrkArgV;
                            --wrkArgC;
                            if (wrkArgC <= 0) {
                                show_usage("ERROR: --file is missing the path!\n");
                                return 99;
                            }
                            pResults->pInFilePath = strdup(*ppWrkArgV);
                        }
                        else {
                            pResults->pInFilePath = strdup(*ppWrkArgV);
                        }
                        pWrk = "";
                        continue;
                        break;
                    case 'm':
                        ++pResults->mFlag;
                        break;
                    case 'n':
                        ++pResults->nFlag;
                        break;
                    case 'o':
                        ++pWrk;
                        if (*pWrk == '\0') {
                            ++ppWrkArgV;
                            --wrkArgC;
                            if (wrkArgC <= 0) {
                                show_usage("ERROR: --out is missing the path!\n");
                                return 99;
                            }
                            pResults->pOutFilePath = strdup(*ppWrkArgV);
                        }
                        else {
                            pResults->pOutFilePath = strdup(*ppWrkArgV);
                        }
                        pWrk = "";
                        continue;
                        break;
                    case 'r':       // -r<string> or -r=<string> or -r <string>
                        ++pWrk;
                        if (*pWrk == '=') {
                            ++pWrk;
                            if (*pWrk == '\0') {
                                show_usage("ERROR: -r is missing its string!\n");
                                return 99;
                            }
                            else {
                                pResults->pR = strdup(pWrk);
                            }
                            pWrk = "";
                            continue;
                        }
                        else if (*pWrk == '\0') {
                            ++ppWrkArgV;
                            --wrkArgC;
                            if (wrkArgC <= 0) {
                                show_usage("ERROR: -r is missing its string!\n");
                                return 99;
                            }
                            pResults->pR = strdup(*ppWrkArgV);
                        }
                        else {
                            if (*pWrk == '\0') {
                                show_usage("ERROR: -r is missing its string!\n");
                                return 99;
                            }
                            else {
                                pResults->pR = strdup(pWrk);
                            }
                            pWrk = "";
                            continue;
                        }
                        break;
                    default:
                        show_usage( "Unknown flag" );
                }
                ++pWrk;
            }
        }
        else
            break;
    }
    
    
    if (wrkArgC && (NULL == pResults->pInFilePath)) {
        --wrkArgC;
        pResults->pInFilePath = strdup(*ppWrkArgV++);
        
    }
    pResults->cOptions = wrkArgC;
    pResults->ppOptions = ppWrkArgV;

    if (pResults->pInFilePath) {
        pResults->pInput = fopen(pResults->pInFilePath, "r");
        if (NULL == pResults->pInput) {
            fprintf(stderr, "ERROR - Could not open input file, %s!",
                    pResults->pInFilePath);
            show_usage(NULL);
        }
    }
    if (NULL == pResults->pInput) {
        pResults->pInput = stdin;
    }
    
    if (pResults->pOutFilePath) {
        pResults->pOutput = fopen(pResults->pOutFilePath, "w");
        if (NULL == pResults->pOutput) {
            fprintf(stderr, "ERROR - Could not open output file, %s!",
                    pResults->pOutFilePath);
            show_usage(NULL);
        }
    }
    if (NULL == pResults->pOutput) {
        if (pResults->fDebug) {
            pResults->pOutput = stderr;
        }
        else {
            pResults->pOutput = stdout;
        }
    }
    pResults->pDateTime = dateTime_NewCurrent();
    
    return 0;
}



//------------------------------------------------------------------
//             parseJsonFile - Parse the JSON File
//------------------------------------------------------------------

int         parseJsonFile(
    ARGS        *pResults
)
{
    //ERESULT         eRc;
    HJSON_DATA      *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    //NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode;
    //NODE_DATA       *pNode;
    //NODEARRAY_DATA  *pArray;
    
    BREAK_NULL(pResults);
    
    pObj = hjson_NewFromFile( pResults->pInput, 4 );
    if (pObj) {
        
        if  (pResults->fDebug) {
            obj_TraceSet(pObj, true);
        }
        pFileNode = hjson_ParseFile(pObj);
        if (pFileNode) {
            pResults->pNodes = pFileNode;
            if (pResults->fDebug) {
                pStr = node_ToDebugString(pFileNode, 0);
                fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        
        //obj_Release(pFileNode);
        //pFileNode = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 0;
}



//------------------------------------------------------------------
//             show_usage - Print program usage informatio.
//------------------------------------------------------------------

void			show_usage(
    const
    char            *pMsg
)
{
    
    if (pMsg) {
        fprintf(stderr, "ERROR - %s!\n\n", pMsg);
    }
    fprintf(stderr, "genMake: Generate a make or nmake file given an input json file\n");
    fprintf(stderr, "usage: %s [options] input_path\n", args.pProgramPath);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  --debug              Set Debug Mode\n");
    fprintf(stderr, "  --macosx             Generate MacOSX nmake file (default)\n");
    fprintf(stderr, "  --msc32              Generate MSC Win32 nmake file\n");
    fprintf(stderr, "  --msc64              Generate MSC Win64 nmake file\n");
    fprintf(stderr, "  (--out | -o) path    Output the generated data to <path>\n");
    fprintf(stderr, "\n\n\n");
    fflush(stderr);
    exit(4);
}



void			test_fileno(
    FILE            *pFile
)
{
    struct stat     statBuffer;
    int             iFileNo;
    int             iRc;
    
    iFileNo = fileno(pFile);
    fprintf(stderr, "stdin fileno: %d\n", iFileNo);
    
    iRc = fstat(iFileNo, &statBuffer);
    if (0 == iRc) {
        fprintf(stderr, "st_dev: %d\n", statBuffer.st_dev);
        fprintf(stderr, "st_ino: %llu\n", statBuffer.st_ino);
        fprintf(stderr, "st_mode: %d\n", statBuffer.st_mode);
        fprintf(stderr, "st_nlink: %d\n", statBuffer.st_nlink);
        fprintf(stderr, "st_uid: %d\n", statBuffer.st_uid);
        fprintf(stderr, "st_gid: %d\n", statBuffer.st_gid);
        fprintf(stderr, "st_rdev: %d\n", statBuffer.st_rdev);
        fprintf(stderr, "st_size: %lld\n", statBuffer.st_size);
        fprintf(stderr, "st_blocks: %lld\n", statBuffer.st_blocks);
        fprintf(stderr, "st_blksize: %d\n", statBuffer.st_blksize);
        fprintf(stderr, "st_flags: %d\n", statBuffer.st_flags);
        fprintf(stderr, "st_gen: %d\n", statBuffer.st_gen);

        switch (statBuffer.st_mode & S_IFMT) {

            case S_IFBLK:
                fprintf(stderr, "fmt: block\n");
                break;
                
            case S_IFCHR:
                fprintf(stderr, "fmt: char\n");
                break;
                
            case S_IFIFO:
                fprintf(stderr, "fmt: fifo\n");
                break;
                
            case S_IFREG:
                fprintf(stderr, "fmt: regular\n");
                break;
                
            case S_IFDIR:
                fprintf(stderr, "fmt: dir\n");
                break;
                
            case S_IFLNK:
                fprintf(stderr, "fmt: link\n");
                break;
                
            case S_IFSOCK:
                fprintf(stderr, "fmt: socket\n");
                break;
                
            default:
                break;
        }
    }
    else {
        fprintf(stderr, "fstat rc: %d\n", iRc);
    }
    fprintf(stderr, "\n\n");
    
}



//******************************************************************
//							M A I N
//******************************************************************

int             main(
    int             argc,
    const
    char            *argv[]
    )
{
    int             iRc = 0;
    
    //test_fileno(stdin);
    //test_fileno(stdout);
    //test_fileno(stderr);
    
    iRc = parseArgs(argc, argv, &args);
    if (iRc) {
        exit(iRc);
    }
    
    iRc = parseJsonFile(&args);

    iRc = genMakeFile(&args);
    
    return iRc;
}
