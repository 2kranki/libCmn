# Generated file - Edits will be discarded by next generation!
# (11/15/2020 19:37:06.000)

.DEFAULT_GOAL := all
SHELL=/bin/sh

LIBNAM=libCmn
SYS=macos64
TEMP=/tmp
BASE_OBJ = $(TEMP)/$(LIBNAM)
SRCDIR = ./src
TEST_SRC = ./tests
INSTALL_BASE = $(HOME)/Support/lib/$(SYS)
LIB_BASE = $(HOME)/Support/lib/$(SYS)

CFLAGS += -g -Werror -I$(SRCDIR)
ifdef  NDEBUG
CFLAGS += -DNDEBUG
else   #DEBUG
CFLAGS += -D_DEBUG
endif  #NDEBUG
CFLAGS += -D__MACOS64_ENV__
CFLAGS_LIBS = 
CFLAGS_TEST = -I$(TEST_SRC) $(CFLAGS_LIBS) -lcurses -lsqlite3

INSTALL_DIR = $(INSTALL_BASE)/$(LIBNAM)
LIBOBJ = $(BASE_OBJ)/$(SYS)
ifdef  NDEBUG
LIB_FILENAME=$(LIBNAM)R.a
OBJDIR = $(LIBOBJ)/o/r
else   #DEBUG
LIB_FILENAME=$(LIBNAM)D.a
OBJDIR = $(LIBOBJ)/o/d
endif  #NDEBUG
TEST_OBJ = $(OBJDIR)/tests
TEST_BIN = $(OBJDIR)/tests
LIB_PATH = $(LIBOBJ)/$(LIB_FILENAME)

.SUFFIXES:
.SUFFIXES: .asm .c .cpp .o

OBJS =

TESTS =


OBJS += $(OBJDIR)/AStr.o

$(OBJDIR)/AStr.o: $(SRCDIR)/AStr.c $(SRCDIR)/AStr.h $(SRCDIR)/AStr_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/AStrArray.o

$(OBJDIR)/AStrArray.o: $(SRCDIR)/AStrArray.c $(SRCDIR)/AStr.h $(SRCDIR)/AStrArray.h $(SRCDIR)/AStrArray_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/AStrArray_object.o

$(OBJDIR)/AStrArray_object.o: $(SRCDIR)/AStrArray_object.c $(SRCDIR)/AStr.h $(SRCDIR)/AStrArray.h $(SRCDIR)/AStrArray_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/AStrC.o

$(OBJDIR)/AStrC.o: $(SRCDIR)/AStrC.c $(SRCDIR)/AStrC.h $(SRCDIR)/AStrC_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/AStrCArray.o

$(OBJDIR)/AStrCArray.o: $(SRCDIR)/AStrCArray.c $(SRCDIR)/AStrC.h $(SRCDIR)/AStrCArray.h $(SRCDIR)/AStrCArray_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/AStrCArray_object.o

$(OBJDIR)/AStrCArray_object.o: $(SRCDIR)/AStrCArray_object.c $(SRCDIR)/AStrC.h $(SRCDIR)/AStrCArray.h $(SRCDIR)/AStrCArray_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/AStrCReader.o

$(OBJDIR)/AStrCReader.o: $(SRCDIR)/AStrCReader.c $(SRCDIR)/AStrC.h $(SRCDIR)/AStrCReader.h $(SRCDIR)/AStrCReader_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/AStrCReader_object.o

$(OBJDIR)/AStrCReader_object.o: $(SRCDIR)/AStrCReader_object.c $(SRCDIR)/AStrC.h $(SRCDIR)/AStrCReader.h $(SRCDIR)/AStrCReader_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/AStrC_object.o

$(OBJDIR)/AStrC_object.o: $(SRCDIR)/AStrC_object.c $(SRCDIR)/AStrC.h $(SRCDIR)/AStrC_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/AStr_json.o

$(OBJDIR)/AStr_json.o: $(SRCDIR)/AStr_json.c $(SRCDIR)/AStr.h $(SRCDIR)/AStr_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/AStr_object.o

$(OBJDIR)/AStr_object.o: $(SRCDIR)/AStr_object.c $(SRCDIR)/AStr.h $(SRCDIR)/AStr_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Appl.o

$(OBJDIR)/Appl.o: $(SRCDIR)/Appl.c $(SRCDIR)/Appl.h $(SRCDIR)/Appl_internal.h $(SRCDIR)/CmdUtl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Appl_object.o

$(OBJDIR)/Appl_object.o: $(SRCDIR)/Appl_object.c $(SRCDIR)/Appl.h $(SRCDIR)/Appl_internal.h $(SRCDIR)/CmdUtl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/AudioCW.o

$(OBJDIR)/AudioCW.o: $(SRCDIR)/AudioCW.c $(SRCDIR)/AStr.h $(SRCDIR)/AudioCW.h $(SRCDIR)/AudioCW_internal.h $(SRCDIR)/audioWAV.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/AudioCW_object.o

$(OBJDIR)/AudioCW_object.o: $(SRCDIR)/AudioCW_object.c $(SRCDIR)/AStr.h $(SRCDIR)/AudioCW.h $(SRCDIR)/AudioCW_internal.h $(SRCDIR)/audioWAV.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/AudioWAV.o

$(OBJDIR)/AudioWAV.o: $(SRCDIR)/AudioWAV.c $(SRCDIR)/AStr.h $(SRCDIR)/AudioWAV.h $(SRCDIR)/AudioWAV_internal.h $(SRCDIR)/fbso.h $(SRCDIR)/u8Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/AudioWAV_object.o

$(OBJDIR)/AudioWAV_object.o: $(SRCDIR)/AudioWAV_object.c $(SRCDIR)/AStr.h $(SRCDIR)/AudioWAV.h $(SRCDIR)/AudioWAV_internal.h $(SRCDIR)/fbso.h $(SRCDIR)/u8Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/BitMatrix.o

$(OBJDIR)/BitMatrix.o: $(SRCDIR)/BitMatrix.c $(SRCDIR)/AStr.h $(SRCDIR)/BitMatrix.h $(SRCDIR)/BitMatrix_internal.h $(SRCDIR)/BitSet.h $(SRCDIR)/u32Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/BitMatrix_json.o

$(OBJDIR)/BitMatrix_json.o: $(SRCDIR)/BitMatrix_json.c $(SRCDIR)/BitMatrix.h $(SRCDIR)/BitMatrix_internal.h $(SRCDIR)/AStr.h $(SRCDIR)/BitSet.h $(SRCDIR)/u32Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/BitMatrix_object.o

$(OBJDIR)/BitMatrix_object.o: $(SRCDIR)/BitMatrix_object.c $(SRCDIR)/AStr.h $(SRCDIR)/BitMatrix.h $(SRCDIR)/BitMatrix_internal.h $(SRCDIR)/BitSet.h $(SRCDIR)/u32Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/BitSet.o

$(OBJDIR)/BitSet.o: $(SRCDIR)/BitSet.c $(SRCDIR)/BitSet.h $(SRCDIR)/BitSet_internal.h $(SRCDIR)/u32Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/BitSet_object.o

$(OBJDIR)/BitSet_object.o: $(SRCDIR)/BitSet_object.c $(SRCDIR)/BitSet.h $(SRCDIR)/BitSet_internal.h $(SRCDIR)/u32Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/BlkdRcds16.o

$(OBJDIR)/BlkdRcds16.o: $(SRCDIR)/BlkdRcds16.c $(SRCDIR)/BlkdRcds16.h $(SRCDIR)/BlkdRcds16_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/BlkdRcds16_object.o

$(OBJDIR)/BlkdRcds16_object.o: $(SRCDIR)/BlkdRcds16_object.c $(SRCDIR)/BlkdRcds16.h $(SRCDIR)/BlkdRcds16_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Blocks.o

$(OBJDIR)/Blocks.o: $(SRCDIR)/Blocks.c $(SRCDIR)/Blocks.h $(SRCDIR)/Blocks_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Blocks_object.o

$(OBJDIR)/Blocks_object.o: $(SRCDIR)/Blocks_object.c $(SRCDIR)/Blocks.h $(SRCDIR)/Blocks_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/CmdUtl.o

$(OBJDIR)/CmdUtl.o: $(SRCDIR)/CmdUtl.c $(SRCDIR)/AStr.h $(SRCDIR)/CmdUtl.h $(SRCDIR)/CmdUtl_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/CmdUtl_object.o

$(OBJDIR)/CmdUtl_object.o: $(SRCDIR)/CmdUtl_object.c $(SRCDIR)/AStr.h $(SRCDIR)/CmdUtl.h $(SRCDIR)/CmdUtl_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Compiler.o

$(OBJDIR)/Compiler.o: $(SRCDIR)/Compiler.c $(SRCDIR)/Compiler.h $(SRCDIR)/Compiler_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Compiler_object.o

$(OBJDIR)/Compiler_object.o: $(SRCDIR)/Compiler_object.c $(SRCDIR)/Compiler.h $(SRCDIR)/Compiler_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/CsvFile.o

$(OBJDIR)/CsvFile.o: $(SRCDIR)/CsvFile.c $(SRCDIR)/CsvFile.h $(SRCDIR)/CsvFile_internal.h $(SRCDIR)/ObjArray.h $(SRCDIR)/Path.h $(SRCDIR)/srcFile.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/CsvFile_object.o

$(OBJDIR)/CsvFile_object.o: $(SRCDIR)/CsvFile_object.c $(SRCDIR)/CsvFile.h $(SRCDIR)/CsvFile_internal.h $(SRCDIR)/ObjArray.h $(SRCDIR)/Path.h $(SRCDIR)/srcFile.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/DateTime.o

$(OBJDIR)/DateTime.o: $(SRCDIR)/DateTime.c $(SRCDIR)/DateTime.h $(SRCDIR)/DateTime_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/DateTime_json.o

$(OBJDIR)/DateTime_json.o: $(SRCDIR)/DateTime_json.c $(SRCDIR)/DateTime.h $(SRCDIR)/DateTime_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/DateTime_object.o

$(OBJDIR)/DateTime_object.o: $(SRCDIR)/DateTime_object.c $(SRCDIR)/DateTime.h $(SRCDIR)/DateTime_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Dir.o

$(OBJDIR)/Dir.o: $(SRCDIR)/Dir.c $(SRCDIR)/Dir.h $(SRCDIR)/Dir_internal.h $(SRCDIR)/Path.h $(SRCDIR)/dirEntry.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/DirEntry.o

$(OBJDIR)/DirEntry.o: $(SRCDIR)/DirEntry.c $(SRCDIR)/DirEntry.h $(SRCDIR)/DirEntry_internal.h $(SRCDIR)/Path.h $(SRCDIR)/dateTime.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/DirEntry_json.o

$(OBJDIR)/DirEntry_json.o: $(SRCDIR)/DirEntry_json.c $(SRCDIR)/DirEntry.h $(SRCDIR)/DirEntry_internal.h $(SRCDIR)/Path.h $(SRCDIR)/dateTime.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/DirEntry_object.o

$(OBJDIR)/DirEntry_object.o: $(SRCDIR)/DirEntry_object.c $(SRCDIR)/DirEntry.h $(SRCDIR)/DirEntry_internal.h $(SRCDIR)/Path.h $(SRCDIR)/dateTime.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Dir_json.o

$(OBJDIR)/Dir_json.o: $(SRCDIR)/Dir_json.c $(SRCDIR)/Dir.h $(SRCDIR)/Dir_internal.h $(SRCDIR)/Path.h $(SRCDIR)/dirEntry.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Dir_object.o

$(OBJDIR)/Dir_object.o: $(SRCDIR)/Dir_object.c $(SRCDIR)/Dir.h $(SRCDIR)/Dir_internal.h $(SRCDIR)/Path.h $(SRCDIR)/dirEntry.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Ebcdic.o

$(OBJDIR)/Ebcdic.o: $(SRCDIR)/Ebcdic.c $(SRCDIR)/Ebcdic.h $(SRCDIR)/Ebcdic_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Ebcdic_object.o

$(OBJDIR)/Ebcdic_object.o: $(SRCDIR)/Ebcdic_object.c $(SRCDIR)/Ebcdic.h $(SRCDIR)/Ebcdic_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/False.o

$(OBJDIR)/False.o: $(SRCDIR)/False.c $(SRCDIR)/False.h $(SRCDIR)/False_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/False_json.o

$(OBJDIR)/False_json.o: $(SRCDIR)/False_json.c $(SRCDIR)/False.h $(SRCDIR)/False_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/False_object.o

$(OBJDIR)/False_object.o: $(SRCDIR)/False_object.c $(SRCDIR)/False.h $(SRCDIR)/False_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/File.o

$(OBJDIR)/File.o: $(SRCDIR)/File.c $(SRCDIR)/File.h $(SRCDIR)/File_internal.h $(SRCDIR)/u8Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/FileRef.o

$(OBJDIR)/FileRef.o: $(SRCDIR)/FileRef.c $(SRCDIR)/AStrC.h $(SRCDIR)/FileRef.h $(SRCDIR)/FileRef_internal.h $(SRCDIR)/Path.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/FileRef_object.o

$(OBJDIR)/FileRef_object.o: $(SRCDIR)/FileRef_object.c $(SRCDIR)/AStrC.h $(SRCDIR)/FileRef.h $(SRCDIR)/FileRef_internal.h $(SRCDIR)/Path.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/File_object.o

$(OBJDIR)/File_object.o: $(SRCDIR)/File_object.c $(SRCDIR)/File.h $(SRCDIR)/File_internal.h $(SRCDIR)/u8Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/I16Array.o

$(OBJDIR)/I16Array.o: $(SRCDIR)/I16Array.c $(SRCDIR)/I16Array.h $(SRCDIR)/I16Array_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/I16Array_json.o

$(OBJDIR)/I16Array_json.o: $(SRCDIR)/I16Array_json.c $(SRCDIR)/I16Array.h $(SRCDIR)/I16Array_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/I16Array_object.o

$(OBJDIR)/I16Array_object.o: $(SRCDIR)/I16Array_object.c $(SRCDIR)/I16Array.h $(SRCDIR)/I16Array_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/I16Matrix.o

$(OBJDIR)/I16Matrix.o: $(SRCDIR)/I16Matrix.c $(SRCDIR)/I16Array.h $(SRCDIR)/I16Matrix.h $(SRCDIR)/I16Matrix_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/I16Matrix_json.o

$(OBJDIR)/I16Matrix_json.o: $(SRCDIR)/I16Matrix_json.c $(SRCDIR)/I16Matrix.h $(SRCDIR)/I16Matrix_internal.h $(SRCDIR)/I16Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/I16Matrix_object.o

$(OBJDIR)/I16Matrix_object.o: $(SRCDIR)/I16Matrix_object.c $(SRCDIR)/I16Array.h $(SRCDIR)/I16Matrix.h $(SRCDIR)/I16Matrix_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/I32Array.o

$(OBJDIR)/I32Array.o: $(SRCDIR)/I32Array.c $(SRCDIR)/I32Array.h $(SRCDIR)/I32Array_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/I32Array_json.o

$(OBJDIR)/I32Array_json.o: $(SRCDIR)/I32Array_json.c $(SRCDIR)/I32Array.h $(SRCDIR)/I32Array_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/I32Array_object.o

$(OBJDIR)/I32Array_object.o: $(SRCDIR)/I32Array_object.c $(SRCDIR)/I32Array.h $(SRCDIR)/I32Array_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/I32Matrix.o

$(OBJDIR)/I32Matrix.o: $(SRCDIR)/I32Matrix.c $(SRCDIR)/I32Array.h $(SRCDIR)/I32Matrix.h $(SRCDIR)/I32Matrix_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/I32Matrix_json.o

$(OBJDIR)/I32Matrix_json.o: $(SRCDIR)/I32Matrix_json.c $(SRCDIR)/I32Matrix.h $(SRCDIR)/I32Matrix_internal.h $(SRCDIR)/I32Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/I32Matrix_object.o

$(OBJDIR)/I32Matrix_object.o: $(SRCDIR)/I32Matrix_object.c $(SRCDIR)/I32Array.h $(SRCDIR)/I32Matrix.h $(SRCDIR)/I32Matrix_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/IntLock.o

$(OBJDIR)/IntLock.o: $(SRCDIR)/IntLock.c $(SRCDIR)/IntLock.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/JsonIn.o

$(OBJDIR)/JsonIn.o: $(SRCDIR)/JsonIn.c $(SRCDIR)/JsonIn.h $(SRCDIR)/JsonIn_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/JsonIn_object.o

$(OBJDIR)/JsonIn_object.o: $(SRCDIR)/JsonIn_object.c $(SRCDIR)/JsonIn.h $(SRCDIR)/JsonIn_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/JsonOut.o

$(OBJDIR)/JsonOut.o: $(SRCDIR)/JsonOut.c $(SRCDIR)/JsonOut.h $(SRCDIR)/JsonOut_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/JsonOut_object.o

$(OBJDIR)/JsonOut_object.o: $(SRCDIR)/JsonOut_object.c $(SRCDIR)/JsonOut.h $(SRCDIR)/JsonOut_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/JsonPP.o

$(OBJDIR)/JsonPP.o: $(SRCDIR)/JsonPP.c $(SRCDIR)/JsonPP.h $(SRCDIR)/JsonPP_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/JsonPP_object.o

$(OBJDIR)/JsonPP_object.o: $(SRCDIR)/JsonPP_object.c $(SRCDIR)/JsonPP.h $(SRCDIR)/JsonPP_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex.o

$(OBJDIR)/Lex.o: $(SRCDIR)/Lex.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex00.o

$(OBJDIR)/Lex00.o: $(SRCDIR)/Lex00.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex00.h $(SRCDIR)/Lex00_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex00_object.o

$(OBJDIR)/Lex00_object.o: $(SRCDIR)/Lex00_object.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex00.h $(SRCDIR)/Lex00_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex01.o

$(OBJDIR)/Lex01.o: $(SRCDIR)/Lex01.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex01.h $(SRCDIR)/Lex01_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex01_object.o

$(OBJDIR)/Lex01_object.o: $(SRCDIR)/Lex01_object.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex01.h $(SRCDIR)/Lex01_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex02.o

$(OBJDIR)/Lex02.o: $(SRCDIR)/Lex02.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex02.h $(SRCDIR)/Lex02_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex02_object.o

$(OBJDIR)/Lex02_object.o: $(SRCDIR)/Lex02_object.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex02.h $(SRCDIR)/Lex02_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex03.o

$(OBJDIR)/Lex03.o: $(SRCDIR)/Lex03.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex03.h $(SRCDIR)/Lex03_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex03_object.o

$(OBJDIR)/Lex03_object.o: $(SRCDIR)/Lex03_object.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex03.h $(SRCDIR)/Lex03_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex04.o

$(OBJDIR)/Lex04.o: $(SRCDIR)/Lex04.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex04.h $(SRCDIR)/Lex04_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex04_object.o

$(OBJDIR)/Lex04_object.o: $(SRCDIR)/Lex04_object.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex04.h $(SRCDIR)/Lex04_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex05.o

$(OBJDIR)/Lex05.o: $(SRCDIR)/Lex05.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex05.h $(SRCDIR)/Lex05_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex05_object.o

$(OBJDIR)/Lex05_object.o: $(SRCDIR)/Lex05_object.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex05.h $(SRCDIR)/Lex05_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex06.o

$(OBJDIR)/Lex06.o: $(SRCDIR)/Lex06.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex06.h $(SRCDIR)/Lex06_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex06_object.o

$(OBJDIR)/Lex06_object.o: $(SRCDIR)/Lex06_object.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex06.h $(SRCDIR)/Lex06_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex07.o

$(OBJDIR)/Lex07.o: $(SRCDIR)/Lex07.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex07.h $(SRCDIR)/Lex07_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex07_object.o

$(OBJDIR)/Lex07_object.o: $(SRCDIR)/Lex07_object.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex07.h $(SRCDIR)/Lex07_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Lex_object.o

$(OBJDIR)/Lex_object.o: $(SRCDIR)/Lex_object.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/LineIndex.o

$(OBJDIR)/LineIndex.o: $(SRCDIR)/LineIndex.c $(SRCDIR)/LineIndex.h $(SRCDIR)/LineIndex_internal.h $(SRCDIR)/SrcLoc.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/LineIndex_json.o

$(OBJDIR)/LineIndex_json.o: $(SRCDIR)/LineIndex_json.c $(SRCDIR)/LineIndex.h $(SRCDIR)/LineIndex_internal.h $(SRCDIR)/SrcLoc.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/LineIndex_object.o

$(OBJDIR)/LineIndex_object.o: $(SRCDIR)/LineIndex_object.c $(SRCDIR)/LineIndex.h $(SRCDIR)/LineIndex_internal.h $(SRCDIR)/SrcLoc.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/MsgData.o

$(OBJDIR)/MsgData.o: $(SRCDIR)/MsgData.c $(SRCDIR)/MsgData.h $(SRCDIR)/MsgData_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/MsgData_json.o

$(OBJDIR)/MsgData_json.o: $(SRCDIR)/MsgData_json.c $(SRCDIR)/MsgData.h $(SRCDIR)/MsgData_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/MsgData_object.o

$(OBJDIR)/MsgData_object.o: $(SRCDIR)/MsgData_object.c $(SRCDIR)/MsgData.h $(SRCDIR)/MsgData_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Name.o

$(OBJDIR)/Name.o: $(SRCDIR)/Name.c $(SRCDIR)/Name.h $(SRCDIR)/Name_internal.h $(SRCDIR)/str.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Name_json.o

$(OBJDIR)/Name_json.o: $(SRCDIR)/Name_json.c $(SRCDIR)/Name.h $(SRCDIR)/Name_internal.h $(SRCDIR)/str.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Name_object.o

$(OBJDIR)/Name_object.o: $(SRCDIR)/Name_object.c $(SRCDIR)/Name.h $(SRCDIR)/Name_internal.h $(SRCDIR)/str.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Node.o

$(OBJDIR)/Node.o: $(SRCDIR)/Node.c $(SRCDIR)/Name.h $(SRCDIR)/Node.h $(SRCDIR)/NodeBT.h $(SRCDIR)/Node_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeArray.o

$(OBJDIR)/NodeArray.o: $(SRCDIR)/NodeArray.c $(SRCDIR)/NodeArray.h $(SRCDIR)/NodeArray_internal.h $(SRCDIR)/ObjArray.h $(SRCDIR)/node.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeArray_json.o

$(OBJDIR)/NodeArray_json.o: $(SRCDIR)/NodeArray_json.c $(SRCDIR)/NodeArray.h $(SRCDIR)/NodeArray_internal.h $(SRCDIR)/ObjArray.h $(SRCDIR)/node.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeArray_object.o

$(OBJDIR)/NodeArray_object.o: $(SRCDIR)/NodeArray_object.c $(SRCDIR)/NodeArray.h $(SRCDIR)/NodeArray_internal.h $(SRCDIR)/ObjArray.h $(SRCDIR)/node.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeBT.o

$(OBJDIR)/NodeBT.o: $(SRCDIR)/NodeBT.c $(SRCDIR)/Node.h $(SRCDIR)/NodeBT.h $(SRCDIR)/NodeBT_internal.h $(SRCDIR)/rbt_tree.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeBT_json.o

$(OBJDIR)/NodeBT_json.o: $(SRCDIR)/NodeBT_json.c $(SRCDIR)/NodeBT.h $(SRCDIR)/NodeBT_internal.h $(SRCDIR)/Node.h $(SRCDIR)/rbt_tree.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeBT_object.o

$(OBJDIR)/NodeBT_object.o: $(SRCDIR)/NodeBT_object.c $(SRCDIR)/Node.h $(SRCDIR)/NodeBT.h $(SRCDIR)/NodeBT_internal.h $(SRCDIR)/rbt_tree.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeEnum.o

$(OBJDIR)/NodeEnum.o: $(SRCDIR)/NodeEnum.c $(SRCDIR)/Node.h $(SRCDIR)/NodeEnum.h $(SRCDIR)/NodeEnum_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeEnum_object.o

$(OBJDIR)/NodeEnum_object.o: $(SRCDIR)/NodeEnum_object.c $(SRCDIR)/Node.h $(SRCDIR)/NodeEnum.h $(SRCDIR)/NodeEnum_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeHash.o

$(OBJDIR)/NodeHash.o: $(SRCDIR)/NodeHash.c $(SRCDIR)/Node.h $(SRCDIR)/NodeHash.h $(SRCDIR)/NodeHash_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeHash_json.o

$(OBJDIR)/NodeHash_json.o: $(SRCDIR)/NodeHash_json.c $(SRCDIR)/NodeHash.h $(SRCDIR)/NodeHash_internal.h $(SRCDIR)/Node.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeHash_object.o

$(OBJDIR)/NodeHash_object.o: $(SRCDIR)/NodeHash_object.c $(SRCDIR)/Node.h $(SRCDIR)/NodeHash.h $(SRCDIR)/NodeHash_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeLink.o

$(OBJDIR)/NodeLink.o: $(SRCDIR)/NodeLink.c $(SRCDIR)/Name.h $(SRCDIR)/Node.h $(SRCDIR)/NodeLink.h $(SRCDIR)/NodeLink_internal.h $(SRCDIR)/str.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeLink_json.o

$(OBJDIR)/NodeLink_json.o: $(SRCDIR)/NodeLink_json.c $(SRCDIR)/NodeLink.h $(SRCDIR)/NodeLink_internal.h $(SRCDIR)/Name.h $(SRCDIR)/Node.h $(SRCDIR)/str.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeLink_object.o

$(OBJDIR)/NodeLink_object.o: $(SRCDIR)/NodeLink_object.c $(SRCDIR)/Name.h $(SRCDIR)/Node.h $(SRCDIR)/NodeLink.h $(SRCDIR)/NodeLink_internal.h $(SRCDIR)/str.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeList.o

$(OBJDIR)/NodeList.o: $(SRCDIR)/NodeList.c $(SRCDIR)/Node.h $(SRCDIR)/NodeList.h $(SRCDIR)/NodeList_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/str.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeList_json.o

$(OBJDIR)/NodeList_json.o: $(SRCDIR)/NodeList_json.c $(SRCDIR)/NodeList.h $(SRCDIR)/NodeList_internal.h $(SRCDIR)/Node.h $(SRCDIR)/listdl.h $(SRCDIR)/str.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeList_object.o

$(OBJDIR)/NodeList_object.o: $(SRCDIR)/NodeList_object.c $(SRCDIR)/Node.h $(SRCDIR)/NodeList.h $(SRCDIR)/NodeList_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/str.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeScan.o

$(OBJDIR)/NodeScan.o: $(SRCDIR)/NodeScan.c $(SRCDIR)/Node.h $(SRCDIR)/NodeArray.h $(SRCDIR)/NodeScan.h $(SRCDIR)/NodeScan_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeScan_object.o

$(OBJDIR)/NodeScan_object.o: $(SRCDIR)/NodeScan_object.c $(SRCDIR)/Node.h $(SRCDIR)/NodeArray.h $(SRCDIR)/NodeScan.h $(SRCDIR)/NodeScan_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeTree.o

$(OBJDIR)/NodeTree.o: $(SRCDIR)/NodeTree.c $(SRCDIR)/Node.h $(SRCDIR)/NodeHash.h $(SRCDIR)/NodeTree.h $(SRCDIR)/NodeTree_internal.h $(SRCDIR)/ObjList.h $(SRCDIR)/szTbl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeTree_json.o

$(OBJDIR)/NodeTree_json.o: $(SRCDIR)/NodeTree_json.c $(SRCDIR)/NodeTree.h $(SRCDIR)/NodeTree_internal.h $(SRCDIR)/Node.h $(SRCDIR)/NodeHash.h $(SRCDIR)/ObjList.h $(SRCDIR)/szTbl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/NodeTree_object.o

$(OBJDIR)/NodeTree_object.o: $(SRCDIR)/NodeTree_object.c $(SRCDIR)/Node.h $(SRCDIR)/NodeHash.h $(SRCDIR)/NodeTree.h $(SRCDIR)/NodeTree_internal.h $(SRCDIR)/ObjList.h $(SRCDIR)/szTbl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Node_json.o

$(OBJDIR)/Node_json.o: $(SRCDIR)/Node_json.c $(SRCDIR)/Node.h $(SRCDIR)/Node_internal.h $(SRCDIR)/Name.h $(SRCDIR)/NodeBT.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Node_object.o

$(OBJDIR)/Node_object.o: $(SRCDIR)/Node_object.c $(SRCDIR)/Name.h $(SRCDIR)/Node.h $(SRCDIR)/NodeBT.h $(SRCDIR)/Node_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Null.o

$(OBJDIR)/Null.o: $(SRCDIR)/Null.c $(SRCDIR)/Null.h $(SRCDIR)/Null_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Null_json.o

$(OBJDIR)/Null_json.o: $(SRCDIR)/Null_json.c $(SRCDIR)/Null.h $(SRCDIR)/Null_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Null_object.o

$(OBJDIR)/Null_object.o: $(SRCDIR)/Null_object.c $(SRCDIR)/Null.h $(SRCDIR)/Null_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Number.o

$(OBJDIR)/Number.o: $(SRCDIR)/Number.c $(SRCDIR)/Number.h $(SRCDIR)/Number_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Number_json.o

$(OBJDIR)/Number_json.o: $(SRCDIR)/Number_json.c $(SRCDIR)/Number.h $(SRCDIR)/Number_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Number_object.o

$(OBJDIR)/Number_object.o: $(SRCDIR)/Number_object.c $(SRCDIR)/Number.h $(SRCDIR)/Number_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjArray.o

$(OBJDIR)/ObjArray.o: $(SRCDIR)/ObjArray.c $(SRCDIR)/ObjArray.h $(SRCDIR)/ObjArray_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjArray_json.o

$(OBJDIR)/ObjArray_json.o: $(SRCDIR)/ObjArray_json.c $(SRCDIR)/ObjArray.h $(SRCDIR)/ObjArray_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjArray_object.o

$(OBJDIR)/ObjArray_object.o: $(SRCDIR)/ObjArray_object.c $(SRCDIR)/ObjArray.h $(SRCDIR)/ObjArray_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjBT.o

$(OBJDIR)/ObjBT.o: $(SRCDIR)/ObjBT.c $(SRCDIR)/ObjBT.h $(SRCDIR)/ObjBT_internal.h $(SRCDIR)/rbt_tree.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjBT_json.o

$(OBJDIR)/ObjBT_json.o: $(SRCDIR)/ObjBT_json.c $(SRCDIR)/ObjBT.h $(SRCDIR)/ObjBT_internal.h $(SRCDIR)/rbt_tree.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjBT_object.o

$(OBJDIR)/ObjBT_object.o: $(SRCDIR)/ObjBT_object.c $(SRCDIR)/ObjBT.h $(SRCDIR)/ObjBT_internal.h $(SRCDIR)/rbt_tree.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjCb.o

$(OBJDIR)/ObjCb.o: $(SRCDIR)/ObjCb.c $(SRCDIR)/ObjCb.h $(SRCDIR)/ObjCb_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjCb_object.o

$(OBJDIR)/ObjCb_object.o: $(SRCDIR)/ObjCb_object.c $(SRCDIR)/ObjCb.h $(SRCDIR)/ObjCb_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjEnum.o

$(OBJDIR)/ObjEnum.o: $(SRCDIR)/ObjEnum.c $(SRCDIR)/ObjEnum.h $(SRCDIR)/ObjEnum_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjEnum_object.o

$(OBJDIR)/ObjEnum_object.o: $(SRCDIR)/ObjEnum_object.c $(SRCDIR)/ObjEnum.h $(SRCDIR)/ObjEnum_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjHash.o

$(OBJDIR)/ObjHash.o: $(SRCDIR)/ObjHash.c $(SRCDIR)/ObjHash.h $(SRCDIR)/ObjHash_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjHash_json.o

$(OBJDIR)/ObjHash_json.o: $(SRCDIR)/ObjHash_json.c $(SRCDIR)/ObjHash.h $(SRCDIR)/ObjHash_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjHash_object.o

$(OBJDIR)/ObjHash_object.o: $(SRCDIR)/ObjHash_object.c $(SRCDIR)/ObjHash.h $(SRCDIR)/ObjHash_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjList.o

$(OBJDIR)/ObjList.o: $(SRCDIR)/ObjList.c $(SRCDIR)/ObjList.h $(SRCDIR)/ObjList_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjList_json.o

$(OBJDIR)/ObjList_json.o: $(SRCDIR)/ObjList_json.c $(SRCDIR)/ObjList.h $(SRCDIR)/ObjList_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjList_object.o

$(OBJDIR)/ObjList_object.o: $(SRCDIR)/ObjList_object.c $(SRCDIR)/ObjList.h $(SRCDIR)/ObjList_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjMethod.o

$(OBJDIR)/ObjMethod.o: $(SRCDIR)/ObjMethod.c $(SRCDIR)/ObjMethod.h $(SRCDIR)/ObjMethod_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjMethod_json.o

$(OBJDIR)/ObjMethod_json.o: $(SRCDIR)/ObjMethod_json.c $(SRCDIR)/ObjMethod.h $(SRCDIR)/ObjMethod_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjMethod_object.o

$(OBJDIR)/ObjMethod_object.o: $(SRCDIR)/ObjMethod_object.c $(SRCDIR)/ObjMethod.h $(SRCDIR)/ObjMethod_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjVLink.o

$(OBJDIR)/ObjVLink.o: $(SRCDIR)/ObjVLink.c $(SRCDIR)/ObjVLink.h $(SRCDIR)/ObjVLink_internal.h $(SRCDIR)/i32Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjVLink_json.o

$(OBJDIR)/ObjVLink_json.o: $(SRCDIR)/ObjVLink_json.c $(SRCDIR)/ObjVLink.h $(SRCDIR)/ObjVLink_internal.h $(SRCDIR)/i32Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ObjVLink_object.o

$(OBJDIR)/ObjVLink_object.o: $(SRCDIR)/ObjVLink_object.c $(SRCDIR)/ObjVLink.h $(SRCDIR)/ObjVLink_internal.h $(SRCDIR)/i32Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Opcode.o

$(OBJDIR)/Opcode.o: $(SRCDIR)/Opcode.c $(SRCDIR)/Opcode.h $(SRCDIR)/Opcode_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Opcode_json.o

$(OBJDIR)/Opcode_json.o: $(SRCDIR)/Opcode_json.c $(SRCDIR)/Opcode.h $(SRCDIR)/Opcode_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Opcode_object.o

$(OBJDIR)/Opcode_object.o: $(SRCDIR)/Opcode_object.c $(SRCDIR)/Opcode.h $(SRCDIR)/Opcode_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Opcodes.o

$(OBJDIR)/Opcodes.o: $(SRCDIR)/Opcodes.c $(SRCDIR)/Opcode.h $(SRCDIR)/Opcodes.h $(SRCDIR)/Opcodes_internal.h $(SRCDIR)/szBT.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Opcodes_json.o

$(OBJDIR)/Opcodes_json.o: $(SRCDIR)/Opcodes_json.c $(SRCDIR)/Opcodes.h $(SRCDIR)/Opcodes_internal.h $(SRCDIR)/Opcode.h $(SRCDIR)/szBT.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Opcodes_object.o

$(OBJDIR)/Opcodes_object.o: $(SRCDIR)/Opcodes_object.c $(SRCDIR)/Opcode.h $(SRCDIR)/Opcodes.h $(SRCDIR)/Opcodes_internal.h $(SRCDIR)/szBT.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Parser.o

$(OBJDIR)/Parser.o: $(SRCDIR)/Parser.c $(SRCDIR)/Parser.h $(SRCDIR)/Parser_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Parser_object.o

$(OBJDIR)/Parser_object.o: $(SRCDIR)/Parser_object.c $(SRCDIR)/Parser.h $(SRCDIR)/Parser_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Path.o

$(OBJDIR)/Path.o: $(SRCDIR)/Path.c $(SRCDIR)/AStr.h $(SRCDIR)/Path.h $(SRCDIR)/Path_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Path_json.o

$(OBJDIR)/Path_json.o: $(SRCDIR)/Path_json.c $(SRCDIR)/Path.h $(SRCDIR)/Path_internal.h $(SRCDIR)/AStr.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Path_object.o

$(OBJDIR)/Path_object.o: $(SRCDIR)/Path_object.c $(SRCDIR)/AStr.h $(SRCDIR)/Path.h $(SRCDIR)/Path_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/PsxExec.o

$(OBJDIR)/PsxExec.o: $(SRCDIR)/PsxExec.c $(SRCDIR)/PsxExec.h $(SRCDIR)/PsxExec_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/PsxExec_object.o

$(OBJDIR)/PsxExec_object.o: $(SRCDIR)/PsxExec_object.c $(SRCDIR)/PsxExec.h $(SRCDIR)/PsxExec_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SQLite.o

$(OBJDIR)/SQLite.o: $(SRCDIR)/SQLite.c $(SRCDIR)/SQLite.h $(SRCDIR)/SQLite_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SQLiteCurs.o

$(OBJDIR)/SQLiteCurs.o: $(SRCDIR)/SQLiteCurs.c $(SRCDIR)/SQLiteCurs.h $(SRCDIR)/SQLiteCurs_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SQLiteCurs_object.o

$(OBJDIR)/SQLiteCurs_object.o: $(SRCDIR)/SQLiteCurs_object.c $(SRCDIR)/SQLiteCurs.h $(SRCDIR)/SQLiteCurs_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SQLiteStmt.o

$(OBJDIR)/SQLiteStmt.o: $(SRCDIR)/SQLiteStmt.c $(SRCDIR)/SQLiteStmt.h $(SRCDIR)/SQLiteStmt_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SQLiteStmt_object.o

$(OBJDIR)/SQLiteStmt_object.o: $(SRCDIR)/SQLiteStmt_object.c $(SRCDIR)/SQLiteStmt.h $(SRCDIR)/SQLiteStmt_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SQLite_object.o

$(OBJDIR)/SQLite_object.o: $(SRCDIR)/SQLite_object.c $(SRCDIR)/SQLite.h $(SRCDIR)/SQLite_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Scanner.o

$(OBJDIR)/Scanner.o: $(SRCDIR)/Scanner.c $(SRCDIR)/Scanner.h $(SRCDIR)/Scanner_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Scanner_json.o

$(OBJDIR)/Scanner_json.o: $(SRCDIR)/Scanner_json.c $(SRCDIR)/Scanner.h $(SRCDIR)/Scanner_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Scanner_object.o

$(OBJDIR)/Scanner_object.o: $(SRCDIR)/Scanner_object.c $(SRCDIR)/Scanner.h $(SRCDIR)/Scanner_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SqlCol.o

$(OBJDIR)/SqlCol.o: $(SRCDIR)/SqlCol.c $(SRCDIR)/SqlCol.h $(SRCDIR)/SqlCol_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SqlColDef.o

$(OBJDIR)/SqlColDef.o: $(SRCDIR)/SqlColDef.c $(SRCDIR)/SqlColDef.h $(SRCDIR)/SqlColDef_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SqlColDef_json.o

$(OBJDIR)/SqlColDef_json.o: $(SRCDIR)/SqlColDef_json.c $(SRCDIR)/SqlColDef.h $(SRCDIR)/SqlColDef_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SqlColDef_object.o

$(OBJDIR)/SqlColDef_object.o: $(SRCDIR)/SqlColDef_object.c $(SRCDIR)/SqlColDef.h $(SRCDIR)/SqlColDef_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SqlCol_json.o

$(OBJDIR)/SqlCol_json.o: $(SRCDIR)/SqlCol_json.c $(SRCDIR)/SqlCol.h $(SRCDIR)/SqlCol_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SqlCol_object.o

$(OBJDIR)/SqlCol_object.o: $(SRCDIR)/SqlCol_object.c $(SRCDIR)/SqlCol.h $(SRCDIR)/SqlCol_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SqlRowDef.o

$(OBJDIR)/SqlRowDef.o: $(SRCDIR)/SqlRowDef.c $(SRCDIR)/SqlRowDef.h $(SRCDIR)/SqlRowDef_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SqlRowDef_json.o

$(OBJDIR)/SqlRowDef_json.o: $(SRCDIR)/SqlRowDef_json.c $(SRCDIR)/SqlRowDef.h $(SRCDIR)/SqlRowDef_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SqlRowDef_object.o

$(OBJDIR)/SqlRowDef_object.o: $(SRCDIR)/SqlRowDef_object.c $(SRCDIR)/SqlRowDef.h $(SRCDIR)/SqlRowDef_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcError.o

$(OBJDIR)/SrcError.o: $(SRCDIR)/SrcError.c $(SRCDIR)/AStr.h $(SRCDIR)/SrcError.h $(SRCDIR)/SrcError_internal.h $(SRCDIR)/SrcLoc.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcError_json.o

$(OBJDIR)/SrcError_json.o: $(SRCDIR)/SrcError_json.c $(SRCDIR)/SrcError.h $(SRCDIR)/SrcError_internal.h $(SRCDIR)/AStr.h $(SRCDIR)/SrcLoc.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcError_object.o

$(OBJDIR)/SrcError_object.o: $(SRCDIR)/SrcError_object.c $(SRCDIR)/AStr.h $(SRCDIR)/SrcError.h $(SRCDIR)/SrcError_internal.h $(SRCDIR)/SrcLoc.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcErrors.o

$(OBJDIR)/SrcErrors.o: $(SRCDIR)/SrcErrors.c $(SRCDIR)/ObjArray.h $(SRCDIR)/SrcError.h $(SRCDIR)/SrcErrors.h $(SRCDIR)/SrcErrors_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcErrors_json.o

$(OBJDIR)/SrcErrors_json.o: $(SRCDIR)/SrcErrors_json.c $(SRCDIR)/SrcErrors.h $(SRCDIR)/SrcErrors_internal.h $(SRCDIR)/ObjArray.h $(SRCDIR)/SrcError.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcErrors_object.o

$(OBJDIR)/SrcErrors_object.o: $(SRCDIR)/SrcErrors_object.c $(SRCDIR)/ObjArray.h $(SRCDIR)/SrcError.h $(SRCDIR)/SrcErrors.h $(SRCDIR)/SrcErrors_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcFile.o

$(OBJDIR)/SrcFile.o: $(SRCDIR)/SrcFile.c $(SRCDIR)/Path.h $(SRCDIR)/SrcFile.h $(SRCDIR)/SrcFile_internal.h $(SRCDIR)/TextIn.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/ascii.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcFile_object.o

$(OBJDIR)/SrcFile_object.o: $(SRCDIR)/SrcFile_object.c $(SRCDIR)/Path.h $(SRCDIR)/SrcFile.h $(SRCDIR)/SrcFile_internal.h $(SRCDIR)/TextIn.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/ascii.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcFiles.o

$(OBJDIR)/SrcFiles.o: $(SRCDIR)/SrcFiles.c $(SRCDIR)/ObjArray.h $(SRCDIR)/Path.h $(SRCDIR)/SrcFile.h $(SRCDIR)/SrcFiles.h $(SRCDIR)/SrcFiles_internal.h $(SRCDIR)/Token.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcFiles_object.o

$(OBJDIR)/SrcFiles_object.o: $(SRCDIR)/SrcFiles_object.c $(SRCDIR)/ObjArray.h $(SRCDIR)/Path.h $(SRCDIR)/SrcFile.h $(SRCDIR)/SrcFiles.h $(SRCDIR)/SrcFiles_internal.h $(SRCDIR)/Token.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcLoc.o

$(OBJDIR)/SrcLoc.o: $(SRCDIR)/SrcLoc.c $(SRCDIR)/SrcLoc.h $(SRCDIR)/SrcLoc_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcLoc_json.o

$(OBJDIR)/SrcLoc_json.o: $(SRCDIR)/SrcLoc_json.c $(SRCDIR)/SrcLoc.h $(SRCDIR)/SrcLoc_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/SrcLoc_object.o

$(OBJDIR)/SrcLoc_object.o: $(SRCDIR)/SrcLoc_object.c $(SRCDIR)/SrcLoc.h $(SRCDIR)/SrcLoc_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Sym.o

$(OBJDIR)/Sym.o: $(SRCDIR)/Sym.c $(SRCDIR)/Sym.h $(SRCDIR)/Sym_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Sym_json.o

$(OBJDIR)/Sym_json.o: $(SRCDIR)/Sym_json.c $(SRCDIR)/Sym.h $(SRCDIR)/Sym_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Sym_object.o

$(OBJDIR)/Sym_object.o: $(SRCDIR)/Sym_object.c $(SRCDIR)/Sym.h $(SRCDIR)/Sym_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Syms.o

$(OBJDIR)/Syms.o: $(SRCDIR)/Syms.c $(SRCDIR)/NodeBT.h $(SRCDIR)/Sym.h $(SRCDIR)/Syms.h $(SRCDIR)/Syms_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Syms_json.o

$(OBJDIR)/Syms_json.o: $(SRCDIR)/Syms_json.c $(SRCDIR)/Syms.h $(SRCDIR)/Syms_internal.h $(SRCDIR)/NodeBT.h $(SRCDIR)/Sym.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Syms_object.o

$(OBJDIR)/Syms_object.o: $(SRCDIR)/Syms_object.c $(SRCDIR)/NodeBT.h $(SRCDIR)/Sym.h $(SRCDIR)/Syms.h $(SRCDIR)/Syms_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/TRegex.o

$(OBJDIR)/TRegex.o: $(SRCDIR)/TRegex.c $(SRCDIR)/TRegex.h $(SRCDIR)/TRegex_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/TRegex32.o

$(OBJDIR)/TRegex32.o: $(SRCDIR)/TRegex32.c $(SRCDIR)/TRegex32.h $(SRCDIR)/TRegex32_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/TRegex32_object.o

$(OBJDIR)/TRegex32_object.o: $(SRCDIR)/TRegex32_object.c $(SRCDIR)/TRegex32.h $(SRCDIR)/TRegex32_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/TRegex_object.o

$(OBJDIR)/TRegex_object.o: $(SRCDIR)/TRegex_object.c $(SRCDIR)/TRegex.h $(SRCDIR)/TRegex_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/TextIn.o

$(OBJDIR)/TextIn.o: $(SRCDIR)/TextIn.c $(SRCDIR)/TextIn.h $(SRCDIR)/TextIn_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/TextIn_object.o

$(OBJDIR)/TextIn_object.o: $(SRCDIR)/TextIn_object.c $(SRCDIR)/TextIn.h $(SRCDIR)/TextIn_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/TextIns.o

$(OBJDIR)/TextIns.o: $(SRCDIR)/TextIns.c $(SRCDIR)/TextIns.h $(SRCDIR)/TextIns_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/TextIns_object.o

$(OBJDIR)/TextIns_object.o: $(SRCDIR)/TextIns_object.c $(SRCDIR)/TextIns.h $(SRCDIR)/TextIns_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/TextOut.o

$(OBJDIR)/TextOut.o: $(SRCDIR)/TextOut.c $(SRCDIR)/TextOut.h $(SRCDIR)/TextOut_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/TextOut_object.o

$(OBJDIR)/TextOut_object.o: $(SRCDIR)/TextOut_object.c $(SRCDIR)/TextOut.h $(SRCDIR)/TextOut_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Token.o

$(OBJDIR)/Token.o: $(SRCDIR)/Token.c $(SRCDIR)/AStrC.h $(SRCDIR)/SrcLoc.h $(SRCDIR)/Token.h $(SRCDIR)/Token_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/TokenList.o

$(OBJDIR)/TokenList.o: $(SRCDIR)/TokenList.c $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/TokenList_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/TokenList_json.o

$(OBJDIR)/TokenList_json.o: $(SRCDIR)/TokenList_json.c $(SRCDIR)/TokenList.h $(SRCDIR)/TokenList_internal.h $(SRCDIR)/Token.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/TokenList_object.o

$(OBJDIR)/TokenList_object.o: $(SRCDIR)/TokenList_object.c $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/TokenList_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Token_json.o

$(OBJDIR)/Token_json.o: $(SRCDIR)/Token_json.c $(SRCDIR)/Token.h $(SRCDIR)/Token_internal.h $(SRCDIR)/AStrC.h $(SRCDIR)/SrcLoc.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Token_object.o

$(OBJDIR)/Token_object.o: $(SRCDIR)/Token_object.c $(SRCDIR)/AStrC.h $(SRCDIR)/SrcLoc.h $(SRCDIR)/Token.h $(SRCDIR)/Token_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/True.o

$(OBJDIR)/True.o: $(SRCDIR)/True.c $(SRCDIR)/True.h $(SRCDIR)/True_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/True_json.o

$(OBJDIR)/True_json.o: $(SRCDIR)/True_json.c $(SRCDIR)/True.h $(SRCDIR)/True_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/True_object.o

$(OBJDIR)/True_object.o: $(SRCDIR)/True_object.c $(SRCDIR)/True.h $(SRCDIR)/True_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/U16Array.o

$(OBJDIR)/U16Array.o: $(SRCDIR)/U16Array.c $(SRCDIR)/U16Array.h $(SRCDIR)/U16Array_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/U16Array_json.o

$(OBJDIR)/U16Array_json.o: $(SRCDIR)/U16Array_json.c $(SRCDIR)/U16Array.h $(SRCDIR)/U16Array_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/U16Array_object.o

$(OBJDIR)/U16Array_object.o: $(SRCDIR)/U16Array_object.c $(SRCDIR)/U16Array.h $(SRCDIR)/U16Array_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/U16Matrix.o

$(OBJDIR)/U16Matrix.o: $(SRCDIR)/U16Matrix.c $(SRCDIR)/U16Array.h $(SRCDIR)/U16Matrix.h $(SRCDIR)/U16Matrix_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/U16Matrix_json.o

$(OBJDIR)/U16Matrix_json.o: $(SRCDIR)/U16Matrix_json.c $(SRCDIR)/U16Matrix.h $(SRCDIR)/U16Matrix_internal.h $(SRCDIR)/U16Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/U16Matrix_object.o

$(OBJDIR)/U16Matrix_object.o: $(SRCDIR)/U16Matrix_object.c $(SRCDIR)/U16Array.h $(SRCDIR)/U16Matrix.h $(SRCDIR)/U16Matrix_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Uri.o

$(OBJDIR)/Uri.o: $(SRCDIR)/Uri.c $(SRCDIR)/Uri.h $(SRCDIR)/Uri_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Uri_json.o

$(OBJDIR)/Uri_json.o: $(SRCDIR)/Uri_json.c $(SRCDIR)/Uri.h $(SRCDIR)/Uri_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Uri_object.o

$(OBJDIR)/Uri_object.o: $(SRCDIR)/Uri_object.c $(SRCDIR)/Uri.h $(SRCDIR)/Uri_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Value.o

$(OBJDIR)/Value.o: $(SRCDIR)/Value.c $(SRCDIR)/Value.h $(SRCDIR)/Value_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Value_json.o

$(OBJDIR)/Value_json.o: $(SRCDIR)/Value_json.c $(SRCDIR)/Value.h $(SRCDIR)/Value_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Value_object.o

$(OBJDIR)/Value_object.o: $(SRCDIR)/Value_object.c $(SRCDIR)/Value.h $(SRCDIR)/Value_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Visitor.o

$(OBJDIR)/Visitor.o: $(SRCDIR)/Visitor.c $(SRCDIR)/Visitor.h $(SRCDIR)/Visitor_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/Visitor_object.o

$(OBJDIR)/Visitor_object.o: $(SRCDIR)/Visitor_object.c $(SRCDIR)/Visitor.h $(SRCDIR)/Visitor_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/W32Str.o

$(OBJDIR)/W32Str.o: $(SRCDIR)/W32Str.c $(SRCDIR)/W32Str.h $(SRCDIR)/W32Str_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/W32StrC.o

$(OBJDIR)/W32StrC.o: $(SRCDIR)/W32StrC.c $(SRCDIR)/W32StrC.h $(SRCDIR)/W32StrC_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/W32StrC_json.o

$(OBJDIR)/W32StrC_json.o: $(SRCDIR)/W32StrC_json.c $(SRCDIR)/W32StrC.h $(SRCDIR)/W32StrC_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/W32StrC_object.o

$(OBJDIR)/W32StrC_object.o: $(SRCDIR)/W32StrC_object.c $(SRCDIR)/W32StrC.h $(SRCDIR)/W32StrC_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/W32Str_json.o

$(OBJDIR)/W32Str_json.o: $(SRCDIR)/W32Str_json.c $(SRCDIR)/W32Str.h $(SRCDIR)/W32Str_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/W32Str_object.o

$(OBJDIR)/W32Str_object.o: $(SRCDIR)/W32Str_object.c $(SRCDIR)/W32Str.h $(SRCDIR)/W32Str_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/array.o

$(OBJDIR)/array.o: $(SRCDIR)/array.c $(SRCDIR)/array.h $(SRCDIR)/array_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/array_object.o

$(OBJDIR)/array_object.o: $(SRCDIR)/array_object.c $(SRCDIR)/array.h $(SRCDIR)/array_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ascii.o

$(OBJDIR)/ascii.o: $(SRCDIR)/ascii.c $(SRCDIR)/ascii.h $(SRCDIR)/ascii_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ascii_object.o

$(OBJDIR)/ascii_object.o: $(SRCDIR)/ascii_object.c $(SRCDIR)/ascii.h $(SRCDIR)/ascii_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/blks.o

$(OBJDIR)/blks.o: $(SRCDIR)/blks.c $(SRCDIR)/blks.h $(SRCDIR)/blks_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/blks_object.o

$(OBJDIR)/blks_object.o: $(SRCDIR)/blks_object.c $(SRCDIR)/blks.h $(SRCDIR)/blks_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/block16.o

$(OBJDIR)/block16.o: $(SRCDIR)/block16.c $(SRCDIR)/block16.h $(SRCDIR)/block16_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/block16_object.o

$(OBJDIR)/block16_object.o: $(SRCDIR)/block16_object.c $(SRCDIR)/block16.h $(SRCDIR)/block16_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/block32.o

$(OBJDIR)/block32.o: $(SRCDIR)/block32.c $(SRCDIR)/block32.h $(SRCDIR)/block32_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/block32_object.o

$(OBJDIR)/block32_object.o: $(SRCDIR)/block32_object.c $(SRCDIR)/block32.h $(SRCDIR)/block32_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/bpt32.o

$(OBJDIR)/bpt32.o: $(SRCDIR)/bpt32.c $(SRCDIR)/bpt32.h $(SRCDIR)/bpt32_internal.h $(SRCDIR)/bpt32idx.h $(SRCDIR)/bpt32lf.h $(SRCDIR)/rrds.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/bpt32_object.o

$(OBJDIR)/bpt32_object.o: $(SRCDIR)/bpt32_object.c $(SRCDIR)/bpt32.h $(SRCDIR)/bpt32_internal.h $(SRCDIR)/bpt32idx.h $(SRCDIR)/bpt32lf.h $(SRCDIR)/rrds.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/bpt32idx.o

$(OBJDIR)/bpt32idx.o: $(SRCDIR)/bpt32idx.c $(SRCDIR)/bpt32idx.h $(SRCDIR)/bpt32idx_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/bpt32idx_object.o

$(OBJDIR)/bpt32idx_object.o: $(SRCDIR)/bpt32idx_object.c $(SRCDIR)/bpt32idx.h $(SRCDIR)/bpt32idx_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/bpt32lf.o

$(OBJDIR)/bpt32lf.o: $(SRCDIR)/bpt32lf.c $(SRCDIR)/bpt32lf.h $(SRCDIR)/bpt32lf_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/bpt32lf_object.o

$(OBJDIR)/bpt32lf_object.o: $(SRCDIR)/bpt32lf_object.c $(SRCDIR)/bpt32lf.h $(SRCDIR)/bpt32lf_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/cb.o

$(OBJDIR)/cb.o: $(SRCDIR)/cb.c $(SRCDIR)/cb.h $(SRCDIR)/cb_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/cb16.o

$(OBJDIR)/cb16.o: $(SRCDIR)/cb16.c $(SRCDIR)/cb16.h $(SRCDIR)/cb16_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/cb16_object.o

$(OBJDIR)/cb16_object.o: $(SRCDIR)/cb16_object.c $(SRCDIR)/cb16.h $(SRCDIR)/cb16_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/cb32.o

$(OBJDIR)/cb32.o: $(SRCDIR)/cb32.c $(SRCDIR)/cb32.h $(SRCDIR)/cb32_internal.h $(SRCDIR)/psxMutex.h $(SRCDIR)/psxSem.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/cb32_object.o

$(OBJDIR)/cb32_object.o: $(SRCDIR)/cb32_object.c $(SRCDIR)/cb32.h $(SRCDIR)/cb32_internal.h $(SRCDIR)/psxMutex.h $(SRCDIR)/psxSem.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/cb_object.o

$(OBJDIR)/cb_object.o: $(SRCDIR)/cb_object.c $(SRCDIR)/cb.h $(SRCDIR)/cb_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/cfa.o

$(OBJDIR)/cfa.o: $(SRCDIR)/cfa.c $(SRCDIR)/cfa.h $(SRCDIR)/cfa_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/cfa_object.o

$(OBJDIR)/cfa_object.o: $(SRCDIR)/cfa_object.c $(SRCDIR)/cfa.h $(SRCDIR)/cfa_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/cmnMac64.o

$(OBJDIR)/cmnMac64.o: $(SRCDIR)/cmnMac64.c $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/consumer.o

$(OBJDIR)/consumer.o: $(SRCDIR)/consumer.c $(SRCDIR)/consumer.h $(SRCDIR)/consumer_internal.h $(SRCDIR)/psxMutex.h $(SRCDIR)/psxSem.h $(SRCDIR)/psxThread.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/consumer_object.o

$(OBJDIR)/consumer_object.o: $(SRCDIR)/consumer_object.c $(SRCDIR)/consumer.h $(SRCDIR)/consumer_internal.h $(SRCDIR)/psxMutex.h $(SRCDIR)/psxSem.h $(SRCDIR)/psxThread.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/crc.o

$(OBJDIR)/crc.o: $(SRCDIR)/crc.c $(SRCDIR)/crc.h $(SRCDIR)/crc_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/crc_object.o

$(OBJDIR)/crc_object.o: $(SRCDIR)/crc_object.c $(SRCDIR)/crc.h $(SRCDIR)/crc_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/dbField.o

$(OBJDIR)/dbField.o: $(SRCDIR)/dbField.c $(SRCDIR)/dbField.h $(SRCDIR)/dbField_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/dbField_object.o

$(OBJDIR)/dbField_object.o: $(SRCDIR)/dbField_object.c $(SRCDIR)/dbField.h $(SRCDIR)/dbField_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/dbf.o

$(OBJDIR)/dbf.o: $(SRCDIR)/dbf.c $(SRCDIR)/dbf.h $(SRCDIR)/dbf_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/dbf_object.o

$(OBJDIR)/dbf_object.o: $(SRCDIR)/dbf_object.c $(SRCDIR)/dbf.h $(SRCDIR)/dbf_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/dec.o

$(OBJDIR)/dec.o: $(SRCDIR)/dec.c $(SRCDIR)/dec.h $(SRCDIR)/dec_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/dec_json.o

$(OBJDIR)/dec_json.o: $(SRCDIR)/dec_json.c $(SRCDIR)/dec.h $(SRCDIR)/dec_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/dec_object.o

$(OBJDIR)/dec_object.o: $(SRCDIR)/dec_object.c $(SRCDIR)/dec.h $(SRCDIR)/dec_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/disk.o

$(OBJDIR)/disk.o: $(SRCDIR)/disk.c $(SRCDIR)/Path.h $(SRCDIR)/disk.h $(SRCDIR)/disk_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/disk_object.o

$(OBJDIR)/disk_object.o: $(SRCDIR)/disk_object.c $(SRCDIR)/Path.h $(SRCDIR)/disk.h $(SRCDIR)/disk_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/disks.o

$(OBJDIR)/disks.o: $(SRCDIR)/disks.c $(SRCDIR)/Path.h $(SRCDIR)/disks.h $(SRCDIR)/disks_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/disks_object.o

$(OBJDIR)/disks_object.o: $(SRCDIR)/disks_object.c $(SRCDIR)/Path.h $(SRCDIR)/disks.h $(SRCDIR)/disks_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/eResult.o

$(OBJDIR)/eResult.o: $(SRCDIR)/eResult.c $(SRCDIR)/eResult.h $(SRCDIR)/eResult_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/eResult_object.o

$(OBJDIR)/eResult_object.o: $(SRCDIR)/eResult_object.c $(SRCDIR)/eResult.h $(SRCDIR)/eResult_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/endian.o

$(OBJDIR)/endian.o: $(SRCDIR)/endian.c $(SRCDIR)/endian.h $(SRCDIR)/endian_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/endian_object.o

$(OBJDIR)/endian_object.o: $(SRCDIR)/endian_object.c $(SRCDIR)/endian.h $(SRCDIR)/endian_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/enum.o

$(OBJDIR)/enum.o: $(SRCDIR)/enum.c $(SRCDIR)/enum.h $(SRCDIR)/enum_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/enum_object.o

$(OBJDIR)/enum_object.o: $(SRCDIR)/enum_object.c $(SRCDIR)/enum.h $(SRCDIR)/enum_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/execArray.o

$(OBJDIR)/execArray.o: $(SRCDIR)/execArray.c $(SRCDIR)/ObjArray.h $(SRCDIR)/execArray.h $(SRCDIR)/execArray_internal.h $(SRCDIR)/ptrArray.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/execArray_object.o

$(OBJDIR)/execArray_object.o: $(SRCDIR)/execArray_object.c $(SRCDIR)/ObjArray.h $(SRCDIR)/execArray.h $(SRCDIR)/execArray_internal.h $(SRCDIR)/ptrArray.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/fbsi.o

$(OBJDIR)/fbsi.o: $(SRCDIR)/fbsi.c $(SRCDIR)/Path.h $(SRCDIR)/fbsi.h $(SRCDIR)/fbsi_internal.h $(SRCDIR)/u8Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/fbsi_object.o

$(OBJDIR)/fbsi_object.o: $(SRCDIR)/fbsi_object.c $(SRCDIR)/Path.h $(SRCDIR)/fbsi.h $(SRCDIR)/fbsi_internal.h $(SRCDIR)/u8Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/fbso.o

$(OBJDIR)/fbso.o: $(SRCDIR)/fbso.c $(SRCDIR)/Path.h $(SRCDIR)/fbso.h $(SRCDIR)/fbso_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/fbso_object.o

$(OBJDIR)/fbso_object.o: $(SRCDIR)/fbso_object.c $(SRCDIR)/Path.h $(SRCDIR)/fbso.h $(SRCDIR)/fbso_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/fileio.o

$(OBJDIR)/fileio.o: $(SRCDIR)/fileio.c $(SRCDIR)/Path.h $(SRCDIR)/fileio.h $(SRCDIR)/fileio_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/fileio_io.o

$(OBJDIR)/fileio_io.o: $(SRCDIR)/fileio_io.c $(SRCDIR)/fileio.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/fileio_object.o

$(OBJDIR)/fileio_object.o: $(SRCDIR)/fileio_object.c $(SRCDIR)/Path.h $(SRCDIR)/fileio.h $(SRCDIR)/fileio_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/genObj.o

$(OBJDIR)/genObj.o: $(SRCDIR)/genObj.c $(SRCDIR)/genObj.h $(SRCDIR)/genObj_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/genObj_object.o

$(OBJDIR)/genObj_object.o: $(SRCDIR)/genObj_object.c $(SRCDIR)/genObj.h $(SRCDIR)/genObj_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/greg.o

$(OBJDIR)/greg.o: $(SRCDIR)/greg.c $(SRCDIR)/greg.h $(SRCDIR)/greg_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/greg_object.o

$(OBJDIR)/greg_object.o: $(SRCDIR)/greg_object.c $(SRCDIR)/greg.h $(SRCDIR)/greg_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/hash32.o

$(OBJDIR)/hash32.o: $(SRCDIR)/hash32.c $(SRCDIR)/hash32.h $(SRCDIR)/hash32_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/hash32_object.o

$(OBJDIR)/hash32_object.o: $(SRCDIR)/hash32_object.c $(SRCDIR)/hash32.h $(SRCDIR)/hash32_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/hex.o

$(OBJDIR)/hex.o: $(SRCDIR)/hex.c $(SRCDIR)/hex.h $(SRCDIR)/hex_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/hex_json.o

$(OBJDIR)/hex_json.o: $(SRCDIR)/hex_json.c $(SRCDIR)/hex.h $(SRCDIR)/hex_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/hex_object.o

$(OBJDIR)/hex_object.o: $(SRCDIR)/hex_object.c $(SRCDIR)/hex.h $(SRCDIR)/hex_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/hjson.o

$(OBJDIR)/hjson.o: $(SRCDIR)/hjson.c $(SRCDIR)/hjson.h $(SRCDIR)/hjson_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/hjson_object.o

$(OBJDIR)/hjson_object.o: $(SRCDIR)/hjson_object.c $(SRCDIR)/hjson.h $(SRCDIR)/hjson_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/lexj.o

$(OBJDIR)/lexj.o: $(SRCDIR)/lexj.c $(SRCDIR)/lexj.h $(SRCDIR)/lexj_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/lexj_object.o

$(OBJDIR)/lexj_object.o: $(SRCDIR)/lexj_object.c $(SRCDIR)/lexj.h $(SRCDIR)/lexj_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/listdl.o

$(OBJDIR)/listdl.o: $(SRCDIR)/listdl.c $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/lru.o

$(OBJDIR)/lru.o: $(SRCDIR)/lru.c $(SRCDIR)/listdl.h $(SRCDIR)/lru.h $(SRCDIR)/lru_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/lru_object.o

$(OBJDIR)/lru_object.o: $(SRCDIR)/lru_object.c $(SRCDIR)/listdl.h $(SRCDIR)/lru.h $(SRCDIR)/lru_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/md5ChkSum.o

$(OBJDIR)/md5ChkSum.o: $(SRCDIR)/md5ChkSum.c $(SRCDIR)/md5ChkSum.h $(SRCDIR)/md5ChkSum_internal.h $(SRCDIR)/md5_plumb.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/md5ChkSum_object.o

$(OBJDIR)/md5ChkSum_object.o: $(SRCDIR)/md5ChkSum_object.c $(SRCDIR)/md5ChkSum.h $(SRCDIR)/md5ChkSum_internal.h $(SRCDIR)/md5_plumb.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/md5_plumb.o

$(OBJDIR)/md5_plumb.o: $(SRCDIR)/md5_plumb.c $(SRCDIR)/md5_plumb.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/memFile.o

$(OBJDIR)/memFile.o: $(SRCDIR)/memFile.c $(SRCDIR)/memFile.h $(SRCDIR)/memFile_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/memFile_object.o

$(OBJDIR)/memFile_object.o: $(SRCDIR)/memFile_object.c $(SRCDIR)/memFile.h $(SRCDIR)/memFile_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/memMac64.o

$(OBJDIR)/memMac64.o: $(SRCDIR)/memMac64.c $(SRCDIR)/listdl.h $(SRCDIR)/memMac64.h $(SRCDIR)/memMac64_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/memMac64_object.o

$(OBJDIR)/memMac64_object.o: $(SRCDIR)/memMac64_object.c $(SRCDIR)/listdl.h $(SRCDIR)/memMac64.h $(SRCDIR)/memMac64_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/memrrds.o

$(OBJDIR)/memrrds.o: $(SRCDIR)/memrrds.c $(SRCDIR)/memrrds.h $(SRCDIR)/memrrds_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/memrrds_io.o

$(OBJDIR)/memrrds_io.o: $(SRCDIR)/memrrds_io.c $(SRCDIR)/memrrds.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/memrrds_object.o

$(OBJDIR)/memrrds_object.o: $(SRCDIR)/memrrds_object.c $(SRCDIR)/memrrds.h $(SRCDIR)/memrrds_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/misc.o

$(OBJDIR)/misc.o: $(SRCDIR)/misc.c $(SRCDIR)/misc.h $(SRCDIR)/misc_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/misc_object.o

$(OBJDIR)/misc_object.o: $(SRCDIR)/misc_object.c $(SRCDIR)/misc.h $(SRCDIR)/misc_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/msgBus.o

$(OBJDIR)/msgBus.o: $(SRCDIR)/msgBus.c $(SRCDIR)/msgBus.h $(SRCDIR)/msgBus_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/msgBus_object.o

$(OBJDIR)/msgBus_object.o: $(SRCDIR)/msgBus_object.c $(SRCDIR)/msgBus.h $(SRCDIR)/msgBus_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/obj.o

$(OBJDIR)/obj.o: $(SRCDIR)/obj.c $(SRCDIR)/obj.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/objMatrix.o

$(OBJDIR)/objMatrix.o: $(SRCDIR)/objMatrix.c $(SRCDIR)/objMatrix.h $(SRCDIR)/objMatrix_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/objMatrix_object.o

$(OBJDIR)/objMatrix_object.o: $(SRCDIR)/objMatrix_object.c $(SRCDIR)/objMatrix.h $(SRCDIR)/objMatrix_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/prt.o

$(OBJDIR)/prt.o: $(SRCDIR)/prt.c $(SRCDIR)/prt.h $(SRCDIR)/prt_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/prt_object.o

$(OBJDIR)/prt_object.o: $(SRCDIR)/prt_object.c $(SRCDIR)/prt.h $(SRCDIR)/prt_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/psxCond.o

$(OBJDIR)/psxCond.o: $(SRCDIR)/psxCond.c $(SRCDIR)/psxCond.h $(SRCDIR)/psxCond_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/psxCond_object.o

$(OBJDIR)/psxCond_object.o: $(SRCDIR)/psxCond_object.c $(SRCDIR)/psxCond.h $(SRCDIR)/psxCond_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/psxLock.o

$(OBJDIR)/psxLock.o: $(SRCDIR)/psxLock.c $(SRCDIR)/psxLock.h $(SRCDIR)/psxLock_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/psxLock_object.o

$(OBJDIR)/psxLock_object.o: $(SRCDIR)/psxLock_object.c $(SRCDIR)/psxLock.h $(SRCDIR)/psxLock_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/psxMutex.o

$(OBJDIR)/psxMutex.o: $(SRCDIR)/psxMutex.c $(SRCDIR)/psxMutex.h $(SRCDIR)/psxMutex_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/psxMutex_object.o

$(OBJDIR)/psxMutex_object.o: $(SRCDIR)/psxMutex_object.c $(SRCDIR)/psxMutex.h $(SRCDIR)/psxMutex_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/psxSem.o

$(OBJDIR)/psxSem.o: $(SRCDIR)/psxSem.c $(SRCDIR)/psxSem.h $(SRCDIR)/psxSem_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/psxSem_object.o

$(OBJDIR)/psxSem_object.o: $(SRCDIR)/psxSem_object.c $(SRCDIR)/psxSem.h $(SRCDIR)/psxSem_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/psxThread.o

$(OBJDIR)/psxThread.o: $(SRCDIR)/psxThread.c $(SRCDIR)/psxMutex.h $(SRCDIR)/psxSem.h $(SRCDIR)/psxThread.h $(SRCDIR)/psxThread_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/psxThread_object.o

$(OBJDIR)/psxThread_object.o: $(SRCDIR)/psxThread_object.c $(SRCDIR)/psxMutex.h $(SRCDIR)/psxSem.h $(SRCDIR)/psxThread.h $(SRCDIR)/psxThread_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ptrArray.o

$(OBJDIR)/ptrArray.o: $(SRCDIR)/ptrArray.c $(SRCDIR)/ptrArray.h $(SRCDIR)/ptrArray_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/ptrArray_object.o

$(OBJDIR)/ptrArray_object.o: $(SRCDIR)/ptrArray_object.c $(SRCDIR)/ptrArray.h $(SRCDIR)/ptrArray_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/rbt_tree.o

$(OBJDIR)/rbt_tree.o: $(SRCDIR)/rbt_tree.c $(SRCDIR)/rbt_tree.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/rrds.o

$(OBJDIR)/rrds.o: $(SRCDIR)/rrds.c $(SRCDIR)/Path.h $(SRCDIR)/hash32.h $(SRCDIR)/listdl.h $(SRCDIR)/rrds.h $(SRCDIR)/rrds_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/rrds_io.o

$(OBJDIR)/rrds_io.o: $(SRCDIR)/rrds_io.c $(SRCDIR)/rrds.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/rrds_object.o

$(OBJDIR)/rrds_object.o: $(SRCDIR)/rrds_object.c $(SRCDIR)/Path.h $(SRCDIR)/hash32.h $(SRCDIR)/listdl.h $(SRCDIR)/rrds.h $(SRCDIR)/rrds_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/scanReader.o

$(OBJDIR)/scanReader.o: $(SRCDIR)/scanReader.c $(SRCDIR)/scanReader.h $(SRCDIR)/scanReader_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/scanReader_object.o

$(OBJDIR)/scanReader_object.o: $(SRCDIR)/scanReader_object.c $(SRCDIR)/scanReader.h $(SRCDIR)/scanReader_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/screen.o

$(OBJDIR)/screen.o: $(SRCDIR)/screen.c $(SRCDIR)/screen.h $(SRCDIR)/screen_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/screen_object.o

$(OBJDIR)/screen_object.o: $(SRCDIR)/screen_object.c $(SRCDIR)/screen.h $(SRCDIR)/screen_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/shellSortPtrs.o

$(OBJDIR)/shellSortPtrs.o: $(SRCDIR)/shellSortPtrs.c $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/stackTraces.o

$(OBJDIR)/stackTraces.o: $(SRCDIR)/stackTraces.c $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/str.o

$(OBJDIR)/str.o: $(SRCDIR)/str.c $(SRCDIR)/str.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/szBT.o

$(OBJDIR)/szBT.o: $(SRCDIR)/szBT.c $(SRCDIR)/szBT.h $(SRCDIR)/szBT_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/szBT_object.o

$(OBJDIR)/szBT_object.o: $(SRCDIR)/szBT_object.c $(SRCDIR)/szBT.h $(SRCDIR)/szBT_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/szData.o

$(OBJDIR)/szData.o: $(SRCDIR)/szData.c $(SRCDIR)/szData.h $(SRCDIR)/szData_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/szData_json.o

$(OBJDIR)/szData_json.o: $(SRCDIR)/szData_json.c $(SRCDIR)/szData.h $(SRCDIR)/szData_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/szData_object.o

$(OBJDIR)/szData_object.o: $(SRCDIR)/szData_object.c $(SRCDIR)/szData.h $(SRCDIR)/szData_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/szHash.o

$(OBJDIR)/szHash.o: $(SRCDIR)/szHash.c $(SRCDIR)/listdl.h $(SRCDIR)/szHash.h $(SRCDIR)/szHash_internal.h $(SRCDIR)/szTbl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/szHash_object.o

$(OBJDIR)/szHash_object.o: $(SRCDIR)/szHash_object.c $(SRCDIR)/listdl.h $(SRCDIR)/szHash.h $(SRCDIR)/szHash_internal.h $(SRCDIR)/szTbl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/szTbl.o

$(OBJDIR)/szTbl.o: $(SRCDIR)/szTbl.c $(SRCDIR)/ptrArray.h $(SRCDIR)/szHash.h $(SRCDIR)/szTbl.h $(SRCDIR)/szTbl_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/szTbl_json.o

$(OBJDIR)/szTbl_json.o: $(SRCDIR)/szTbl_json.c $(SRCDIR)/szTbl.h $(SRCDIR)/szTbl_internal.h $(SRCDIR)/ptrArray.h $(SRCDIR)/szHash.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/szTbl_object.o

$(OBJDIR)/szTbl_object.o: $(SRCDIR)/szTbl_object.c $(SRCDIR)/ptrArray.h $(SRCDIR)/szHash.h $(SRCDIR)/szTbl.h $(SRCDIR)/szTbl_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/table.o

$(OBJDIR)/table.o: $(SRCDIR)/table.c $(SRCDIR)/listdl.h $(SRCDIR)/table.h $(SRCDIR)/table_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/table_object.o

$(OBJDIR)/table_object.o: $(SRCDIR)/table_object.c $(SRCDIR)/listdl.h $(SRCDIR)/table.h $(SRCDIR)/table_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/timer.o

$(OBJDIR)/timer.o: $(SRCDIR)/timer.c $(SRCDIR)/timer.h $(SRCDIR)/timer_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/timer_object.o

$(OBJDIR)/timer_object.o: $(SRCDIR)/timer_object.c $(SRCDIR)/timer.h $(SRCDIR)/timer_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/trace.o

$(OBJDIR)/trace.o: $(SRCDIR)/trace.c $(SRCDIR)/trace.h $(SRCDIR)/trace_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/trace_object.o

$(OBJDIR)/trace_object.o: $(SRCDIR)/trace_object.c $(SRCDIR)/trace.h $(SRCDIR)/trace_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/u12Array.o

$(OBJDIR)/u12Array.o: $(SRCDIR)/u12Array.c $(SRCDIR)/array.h $(SRCDIR)/u12Array.h $(SRCDIR)/u12Array_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/u12Array_object.o

$(OBJDIR)/u12Array_object.o: $(SRCDIR)/u12Array_object.c $(SRCDIR)/array.h $(SRCDIR)/u12Array.h $(SRCDIR)/u12Array_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/u32Array.o

$(OBJDIR)/u32Array.o: $(SRCDIR)/u32Array.c $(SRCDIR)/array.h $(SRCDIR)/u32Array.h $(SRCDIR)/u32Array_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/u32Array_object.o

$(OBJDIR)/u32Array_object.o: $(SRCDIR)/u32Array_object.c $(SRCDIR)/array.h $(SRCDIR)/u32Array.h $(SRCDIR)/u32Array_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/u32Matrix.o

$(OBJDIR)/u32Matrix.o: $(SRCDIR)/u32Matrix.c $(SRCDIR)/u32Matrix.h $(SRCDIR)/u32Matrix_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/u32Matrix_object.o

$(OBJDIR)/u32Matrix_object.o: $(SRCDIR)/u32Matrix_object.c $(SRCDIR)/u32Matrix.h $(SRCDIR)/u32Matrix_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/u8Array.o

$(OBJDIR)/u8Array.o: $(SRCDIR)/u8Array.c $(SRCDIR)/u8Array.h $(SRCDIR)/u8Array_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/u8Array_json.o

$(OBJDIR)/u8Array_json.o: $(SRCDIR)/u8Array_json.c $(SRCDIR)/u8Array.h $(SRCDIR)/u8Array_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/u8Array_object.o

$(OBJDIR)/u8Array_object.o: $(SRCDIR)/u8Array_object.c $(SRCDIR)/u8Array.h $(SRCDIR)/u8Array_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/u8VlArray.o

$(OBJDIR)/u8VlArray.o: $(SRCDIR)/u8VlArray.c $(SRCDIR)/u8VlArray.h $(SRCDIR)/u8VlArray_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/u8VlArray_json.o

$(OBJDIR)/u8VlArray_json.o: $(SRCDIR)/u8VlArray_json.c $(SRCDIR)/u8VlArray.h $(SRCDIR)/u8VlArray_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/u8VlArray_object.o

$(OBJDIR)/u8VlArray_object.o: $(SRCDIR)/u8VlArray_object.c $(SRCDIR)/u8VlArray.h $(SRCDIR)/u8VlArray_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/uint128.o

$(OBJDIR)/uint128.o: $(SRCDIR)/uint128.c $(SRCDIR)/uint128.h $(SRCDIR)/uint128_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/uint128_object.o

$(OBJDIR)/uint128_object.o: $(SRCDIR)/uint128_object.c $(SRCDIR)/uint128.h $(SRCDIR)/uint128_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/utf8.o

$(OBJDIR)/utf8.o: $(SRCDIR)/utf8.c $(SRCDIR)/utf8.h $(SRCDIR)/utf8_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/utf8_json.o

$(OBJDIR)/utf8_json.o: $(SRCDIR)/utf8_json.c $(SRCDIR)/utf8.h $(SRCDIR)/utf8_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

OBJS += $(OBJDIR)/utf8_object.o

$(OBJDIR)/utf8_object.o: $(SRCDIR)/utf8_object.c $(SRCDIR)/utf8.h $(SRCDIR)/utf8_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) -I$(SRCDIR) $<

TESTS += AStrArray_test

AStrArray_test: $(TEST_SRC)/AStrArray_test.c $(SRCDIR)/AStrArray.h $(SRCDIR)/AStrArray_internal.h $(SRCDIR)/AStr.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += AStrCArray_test

AStrCArray_test: $(TEST_SRC)/AStrCArray_test.c $(SRCDIR)/AStrCArray.h $(SRCDIR)/AStrCArray_internal.h $(SRCDIR)/AStrC.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += AStrCReader_test

AStrCReader_test: $(TEST_SRC)/AStrCReader_test.c $(SRCDIR)/AStrCReader.h $(SRCDIR)/AStrCReader_internal.h $(SRCDIR)/AStrC.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += AStrC_test

AStrC_test: $(TEST_SRC)/AStrC_test.c $(SRCDIR)/AStrC.h $(SRCDIR)/AStrC_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += AStr_test

AStr_test: $(TEST_SRC)/AStr_test.c $(SRCDIR)/AStr.h $(SRCDIR)/AStr_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Appl_test

Appl_test: $(TEST_SRC)/Appl_test.c $(SRCDIR)/Appl.h $(SRCDIR)/Appl_internal.h $(SRCDIR)/CmdUtl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/objTest.c $(TEST_SRC)/objTest_object.c $<
	$(TEST_BIN)/$(@F)

TESTS += AudioCW_test

AudioCW_test: $(TEST_SRC)/AudioCW_test.c $(SRCDIR)/AudioCW.h $(SRCDIR)/AudioCW_internal.h $(SRCDIR)/AStr.h $(SRCDIR)/audioWAV.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += AudioWAV_test

AudioWAV_test: $(TEST_SRC)/AudioWAV_test.c $(SRCDIR)/AudioWAV.h $(SRCDIR)/AudioWAV_internal.h $(SRCDIR)/AStr.h $(SRCDIR)/fbso.h $(SRCDIR)/u8Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += BitMatrix_test

BitMatrix_test: $(TEST_SRC)/BitMatrix_test.c $(SRCDIR)/BitMatrix.h $(SRCDIR)/BitMatrix_internal.h $(SRCDIR)/AStr.h $(SRCDIR)/BitSet.h $(SRCDIR)/u32Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += BitSet_test

BitSet_test: $(TEST_SRC)/BitSet_test.c $(SRCDIR)/BitSet.h $(SRCDIR)/BitSet_internal.h $(SRCDIR)/u32Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += BlkdRcds16_test

BlkdRcds16_test: $(TEST_SRC)/BlkdRcds16_test.c $(SRCDIR)/BlkdRcds16.h $(SRCDIR)/BlkdRcds16_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Blocks_test

Blocks_test: $(TEST_SRC)/Blocks_test.c $(SRCDIR)/Blocks.h $(SRCDIR)/Blocks_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += CmdUtl_test

CmdUtl_test: $(TEST_SRC)/CmdUtl_test.c $(SRCDIR)/CmdUtl.h $(SRCDIR)/CmdUtl_internal.h $(SRCDIR)/AStr.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Compiler_test

Compiler_test: $(TEST_SRC)/Compiler_test.c $(SRCDIR)/Compiler.h $(SRCDIR)/Compiler_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += CsvFile_test

CsvFile_test: $(TEST_SRC)/CsvFile_test.c $(SRCDIR)/CsvFile.h $(SRCDIR)/CsvFile_internal.h $(SRCDIR)/ObjArray.h $(SRCDIR)/Path.h $(SRCDIR)/srcFile.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += DateTime_test

DateTime_test: $(TEST_SRC)/DateTime_test.c $(SRCDIR)/DateTime.h $(SRCDIR)/DateTime_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += DirEntry_test

DirEntry_test: $(TEST_SRC)/DirEntry_test.c $(SRCDIR)/DirEntry.h $(SRCDIR)/DirEntry_internal.h $(SRCDIR)/Path.h $(SRCDIR)/dateTime.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Dir_test

Dir_test: $(TEST_SRC)/Dir_test.c $(SRCDIR)/Dir.h $(SRCDIR)/Dir_internal.h $(SRCDIR)/Path.h $(SRCDIR)/dirEntry.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Ebcdic_test

Ebcdic_test: $(TEST_SRC)/Ebcdic_test.c $(SRCDIR)/Ebcdic.h $(SRCDIR)/Ebcdic_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += False_test

False_test: $(TEST_SRC)/False_test.c $(SRCDIR)/False.h $(SRCDIR)/False_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += FileRef_test

FileRef_test: $(TEST_SRC)/FileRef_test.c $(SRCDIR)/FileRef.h $(SRCDIR)/FileRef_internal.h $(SRCDIR)/AStrC.h $(SRCDIR)/Path.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += File_test

File_test: $(TEST_SRC)/File_test.c $(SRCDIR)/File.h $(SRCDIR)/File_internal.h $(SRCDIR)/u8Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += I16Array_test

I16Array_test: $(TEST_SRC)/I16Array_test.c $(SRCDIR)/I16Array.h $(SRCDIR)/I16Array_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += I16Matrix_test

I16Matrix_test: $(TEST_SRC)/I16Matrix_test.c $(SRCDIR)/I16Matrix.h $(SRCDIR)/I16Matrix_internal.h $(SRCDIR)/I16Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += I32Array_test

I32Array_test: $(TEST_SRC)/I32Array_test.c $(SRCDIR)/I32Array.h $(SRCDIR)/I32Array_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += I32Matrix_test

I32Matrix_test: $(TEST_SRC)/I32Matrix_test.c $(SRCDIR)/I32Matrix.h $(SRCDIR)/I32Matrix_internal.h $(SRCDIR)/I32Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += IntLock_test

IntLock_test: $(TEST_SRC)/IntLock_test.c $(SRCDIR)/IntLock.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += JsonIn_test

JsonIn_test: $(TEST_SRC)/JsonIn_test.c $(SRCDIR)/JsonIn.h $(SRCDIR)/JsonIn_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += JsonOut_test

JsonOut_test: $(TEST_SRC)/JsonOut_test.c $(SRCDIR)/JsonOut.h $(SRCDIR)/JsonOut_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += JsonPP_test

JsonPP_test: $(TEST_SRC)/JsonPP_test.c $(SRCDIR)/JsonPP.h $(SRCDIR)/JsonPP_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Lex00_test

Lex00_test: $(TEST_SRC)/Lex00_test.c $(SRCDIR)/Lex00.h $(SRCDIR)/Lex00_internal.h $(SRCDIR)/Lex.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Lex01_test

Lex01_test: $(TEST_SRC)/Lex01_test.c $(SRCDIR)/Lex01.h $(SRCDIR)/Lex01_internal.h $(SRCDIR)/Lex.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Lex02_test

Lex02_test: $(TEST_SRC)/Lex02_test.c $(SRCDIR)/Lex02.h $(SRCDIR)/Lex02_internal.h $(SRCDIR)/Lex.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Lex03_test

Lex03_test: $(TEST_SRC)/Lex03_test.c $(SRCDIR)/Lex03.h $(SRCDIR)/Lex03_internal.h $(SRCDIR)/Lex.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Lex04_test

Lex04_test: $(TEST_SRC)/Lex04_test.c $(SRCDIR)/Lex04.h $(SRCDIR)/Lex04_internal.h $(SRCDIR)/Lex.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Lex05_test

Lex05_test: $(TEST_SRC)/Lex05_test.c $(SRCDIR)/Lex05.h $(SRCDIR)/Lex05_internal.h $(SRCDIR)/Lex.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Lex06_test

Lex06_test: $(TEST_SRC)/Lex06_test.c $(SRCDIR)/Lex06.h $(SRCDIR)/Lex06_internal.h $(SRCDIR)/Lex.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Lex07_test

Lex07_test: $(TEST_SRC)/Lex07_test.c $(SRCDIR)/Lex07.h $(SRCDIR)/Lex07_internal.h $(SRCDIR)/Lex.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Lex_test

Lex_test: $(TEST_SRC)/Lex_test.c $(SRCDIR)/Lex.h $(SRCDIR)/Lex_internal.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += LineIndex_test

LineIndex_test: $(TEST_SRC)/LineIndex_test.c $(SRCDIR)/LineIndex.h $(SRCDIR)/LineIndex_internal.h $(SRCDIR)/SrcLoc.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += MsgData_test

MsgData_test: $(TEST_SRC)/MsgData_test.c $(SRCDIR)/MsgData.h $(SRCDIR)/MsgData_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Name_test

Name_test: $(TEST_SRC)/Name_test.c $(SRCDIR)/Name.h $(SRCDIR)/Name_internal.h $(SRCDIR)/str.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += NodeArray_test

NodeArray_test: $(TEST_SRC)/NodeArray_test.c $(SRCDIR)/NodeArray.h $(SRCDIR)/NodeArray_internal.h $(SRCDIR)/ObjArray.h $(SRCDIR)/node.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += NodeBT_test

NodeBT_test: $(TEST_SRC)/NodeBT_test.c $(SRCDIR)/NodeBT.h $(SRCDIR)/NodeBT_internal.h $(SRCDIR)/Node.h $(SRCDIR)/rbt_tree.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += NodeEnum_test

NodeEnum_test: $(TEST_SRC)/NodeEnum_test.c $(SRCDIR)/NodeEnum.h $(SRCDIR)/NodeEnum_internal.h $(SRCDIR)/Node.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += NodeHash_test

NodeHash_test: $(TEST_SRC)/NodeHash_test.c $(SRCDIR)/NodeHash.h $(SRCDIR)/NodeHash_internal.h $(SRCDIR)/Node.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += NodeLink_test

NodeLink_test: $(TEST_SRC)/NodeLink_test.c $(SRCDIR)/NodeLink.h $(SRCDIR)/NodeLink_internal.h $(SRCDIR)/Name.h $(SRCDIR)/Node.h $(SRCDIR)/str.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += NodeList_test

NodeList_test: $(TEST_SRC)/NodeList_test.c $(SRCDIR)/NodeList.h $(SRCDIR)/NodeList_internal.h $(SRCDIR)/Node.h $(SRCDIR)/listdl.h $(SRCDIR)/str.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += NodeScan_test

NodeScan_test: $(TEST_SRC)/NodeScan_test.c $(SRCDIR)/NodeScan.h $(SRCDIR)/NodeScan_internal.h $(SRCDIR)/Node.h $(SRCDIR)/NodeArray.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += NodeTree_test

NodeTree_test: $(TEST_SRC)/NodeTree_test.c $(SRCDIR)/NodeTree.h $(SRCDIR)/NodeTree_internal.h $(SRCDIR)/Node.h $(SRCDIR)/NodeHash.h $(SRCDIR)/ObjList.h $(SRCDIR)/szTbl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Node_test

Node_test: $(TEST_SRC)/Node_test.c $(SRCDIR)/Node.h $(SRCDIR)/Node_internal.h $(SRCDIR)/Name.h $(SRCDIR)/NodeBT.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Null_test

Null_test: $(TEST_SRC)/Null_test.c $(SRCDIR)/Null.h $(SRCDIR)/Null_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Number_test

Number_test: $(TEST_SRC)/Number_test.c $(SRCDIR)/Number.h $(SRCDIR)/Number_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += ObjArray_test

ObjArray_test: $(TEST_SRC)/ObjArray_test.c $(SRCDIR)/ObjArray.h $(SRCDIR)/ObjArray_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += ObjBT_test

ObjBT_test: $(TEST_SRC)/ObjBT_test.c $(SRCDIR)/ObjBT.h $(SRCDIR)/ObjBT_internal.h $(SRCDIR)/rbt_tree.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += ObjCb_test

ObjCb_test: $(TEST_SRC)/ObjCb_test.c $(SRCDIR)/ObjCb.h $(SRCDIR)/ObjCb_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/objTest.c $(TEST_SRC)/objTest_object.c $<
	$(TEST_BIN)/$(@F)

TESTS += ObjEnum_test

ObjEnum_test: $(TEST_SRC)/ObjEnum_test.c $(SRCDIR)/ObjEnum.h $(SRCDIR)/ObjEnum_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += ObjHash_test

ObjHash_test: $(TEST_SRC)/ObjHash_test.c $(SRCDIR)/ObjHash.h $(SRCDIR)/ObjHash_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += ObjList_test

ObjList_test: $(TEST_SRC)/ObjList_test.c $(SRCDIR)/ObjList.h $(SRCDIR)/ObjList_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += ObjMethod_test

ObjMethod_test: $(TEST_SRC)/ObjMethod_test.c $(SRCDIR)/ObjMethod.h $(SRCDIR)/ObjMethod_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += ObjVLink_test

ObjVLink_test: $(TEST_SRC)/ObjVLink_test.c $(SRCDIR)/ObjVLink.h $(SRCDIR)/ObjVLink_internal.h $(SRCDIR)/i32Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Opcode_test

Opcode_test: $(TEST_SRC)/Opcode_test.c $(SRCDIR)/Opcode.h $(SRCDIR)/Opcode_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Opcodes_test

Opcodes_test: $(TEST_SRC)/Opcodes_test.c $(SRCDIR)/Opcodes.h $(SRCDIR)/Opcodes_internal.h $(SRCDIR)/Opcode.h $(SRCDIR)/szBT.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Parser_test

Parser_test: $(TEST_SRC)/Parser_test.c $(SRCDIR)/Parser.h $(SRCDIR)/Parser_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Path_test

Path_test: $(TEST_SRC)/Path_test.c $(SRCDIR)/Path.h $(SRCDIR)/Path_internal.h $(SRCDIR)/AStr.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += PsxExec_test

PsxExec_test: $(TEST_SRC)/PsxExec_test.c $(SRCDIR)/PsxExec.h $(SRCDIR)/PsxExec_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += SQLiteCurs_test

SQLiteCurs_test: $(TEST_SRC)/SQLiteCurs_test.c $(SRCDIR)/SQLiteCurs.h $(SRCDIR)/SQLiteCurs_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += SQLiteStmt_test

SQLiteStmt_test: $(TEST_SRC)/SQLiteStmt_test.c $(SRCDIR)/SQLiteStmt.h $(SRCDIR)/SQLiteStmt_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += SQLite_test

SQLite_test: $(TEST_SRC)/SQLite_test.c $(SRCDIR)/SQLite.h $(SRCDIR)/SQLite_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Scanner_test

Scanner_test: $(TEST_SRC)/Scanner_test.c $(SRCDIR)/Scanner.h $(SRCDIR)/Scanner_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += SqlColDef_test

SqlColDef_test: $(TEST_SRC)/SqlColDef_test.c $(SRCDIR)/SqlColDef.h $(SRCDIR)/SqlColDef_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += SqlCol_test

SqlCol_test: $(TEST_SRC)/SqlCol_test.c $(SRCDIR)/SqlCol.h $(SRCDIR)/SqlCol_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += SqlRowDef_test

SqlRowDef_test: $(TEST_SRC)/SqlRowDef_test.c $(SRCDIR)/SqlRowDef.h $(SRCDIR)/SqlRowDef_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += SrcError_test

SrcError_test: $(TEST_SRC)/SrcError_test.c $(SRCDIR)/SrcError.h $(SRCDIR)/SrcError_internal.h $(SRCDIR)/AStr.h $(SRCDIR)/SrcLoc.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += SrcErrors_test

SrcErrors_test: $(TEST_SRC)/SrcErrors_test.c $(SRCDIR)/SrcErrors.h $(SRCDIR)/SrcErrors_internal.h $(SRCDIR)/ObjArray.h $(SRCDIR)/SrcError.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += SrcFile_test

SrcFile_test: $(TEST_SRC)/SrcFile_test.c $(SRCDIR)/SrcFile.h $(SRCDIR)/SrcFile_internal.h $(SRCDIR)/Path.h $(SRCDIR)/TextIn.h $(SRCDIR)/Token.h $(SRCDIR)/TokenList.h $(SRCDIR)/ascii.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += SrcFiles_test

SrcFiles_test: $(TEST_SRC)/SrcFiles_test.c $(SRCDIR)/SrcFiles.h $(SRCDIR)/SrcFiles_internal.h $(SRCDIR)/ObjArray.h $(SRCDIR)/Path.h $(SRCDIR)/SrcFile.h $(SRCDIR)/Token.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += SrcLoc_test

SrcLoc_test: $(TEST_SRC)/SrcLoc_test.c $(SRCDIR)/SrcLoc.h $(SRCDIR)/SrcLoc_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Sym_test

Sym_test: $(TEST_SRC)/Sym_test.c $(SRCDIR)/Sym.h $(SRCDIR)/Sym_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Syms_test

Syms_test: $(TEST_SRC)/Syms_test.c $(SRCDIR)/Syms.h $(SRCDIR)/Syms_internal.h $(SRCDIR)/NodeBT.h $(SRCDIR)/Sym.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += TRegex32_test

TRegex32_test: $(TEST_SRC)/TRegex32_test.c $(SRCDIR)/TRegex32.h $(SRCDIR)/TRegex32_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += TRegex_test

TRegex_test: $(TEST_SRC)/TRegex_test.c $(SRCDIR)/TRegex.h $(SRCDIR)/TRegex_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += TextIn_test

TextIn_test: $(TEST_SRC)/TextIn_test.c $(SRCDIR)/TextIn.h $(SRCDIR)/TextIn_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += TextIns_test

TextIns_test: $(TEST_SRC)/TextIns_test.c $(SRCDIR)/TextIns.h $(SRCDIR)/TextIns_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += TextOut_test

TextOut_test: $(TEST_SRC)/TextOut_test.c $(SRCDIR)/TextOut.h $(SRCDIR)/TextOut_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += TokenList_test

TokenList_test: $(TEST_SRC)/TokenList_test.c $(SRCDIR)/TokenList.h $(SRCDIR)/TokenList_internal.h $(SRCDIR)/Token.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Token_test

Token_test: $(TEST_SRC)/Token_test.c $(SRCDIR)/Token.h $(SRCDIR)/Token_internal.h $(SRCDIR)/AStrC.h $(SRCDIR)/SrcLoc.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += True_test

True_test: $(TEST_SRC)/True_test.c $(SRCDIR)/True.h $(SRCDIR)/True_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += U16Array_test

U16Array_test: $(TEST_SRC)/U16Array_test.c $(SRCDIR)/U16Array.h $(SRCDIR)/U16Array_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += U16Matrix_test

U16Matrix_test: $(TEST_SRC)/U16Matrix_test.c $(SRCDIR)/U16Matrix.h $(SRCDIR)/U16Matrix_internal.h $(SRCDIR)/U16Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Uri_test

Uri_test: $(TEST_SRC)/Uri_test.c $(SRCDIR)/Uri.h $(SRCDIR)/Uri_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Value_test

Value_test: $(TEST_SRC)/Value_test.c $(SRCDIR)/Value.h $(SRCDIR)/Value_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += Visitor_test

Visitor_test: $(TEST_SRC)/Visitor_test.c $(SRCDIR)/Visitor.h $(SRCDIR)/Visitor_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += W32StrC_test

W32StrC_test: $(TEST_SRC)/W32StrC_test.c $(SRCDIR)/W32StrC.h $(SRCDIR)/W32StrC_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += W32Str_test

W32Str_test: $(TEST_SRC)/W32Str_test.c $(SRCDIR)/W32Str.h $(SRCDIR)/W32Str_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += array_test

array_test: $(TEST_SRC)/array_test.c $(SRCDIR)/array.h $(SRCDIR)/array_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += ascii_test

ascii_test: $(TEST_SRC)/ascii_test.c $(SRCDIR)/ascii.h $(SRCDIR)/ascii_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += blks_test

blks_test: $(TEST_SRC)/blks_test.c $(SRCDIR)/blks.h $(SRCDIR)/blks_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += block16_test

block16_test: $(TEST_SRC)/block16_test.c $(SRCDIR)/block16.h $(SRCDIR)/block16_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += block32_test

block32_test: $(TEST_SRC)/block32_test.c $(SRCDIR)/block32.h $(SRCDIR)/block32_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += bpt32_test

bpt32_test: $(TEST_SRC)/bpt32_test.c $(SRCDIR)/bpt32.h $(SRCDIR)/bpt32_internal.h $(SRCDIR)/bpt32idx.h $(SRCDIR)/bpt32lf.h $(SRCDIR)/rrds.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += bpt32lf_test

bpt32lf_test: $(TEST_SRC)/bpt32lf_test.c $(SRCDIR)/bpt32lf.h $(SRCDIR)/bpt32lf_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += cb16_test

cb16_test: $(TEST_SRC)/cb16_test.c $(SRCDIR)/cb16.h $(SRCDIR)/cb16_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += cb32_test

cb32_test: $(TEST_SRC)/cb32_test.c $(SRCDIR)/cb32.h $(SRCDIR)/cb32_internal.h $(SRCDIR)/psxMutex.h $(SRCDIR)/psxSem.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += cb_test

cb_test: $(TEST_SRC)/cb_test.c $(SRCDIR)/cb.h $(SRCDIR)/cb_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/objTest.c $(TEST_SRC)/objTest_object.c $<
	$(TEST_BIN)/$(@F)

TESTS += cfa_test

cfa_test: $(TEST_SRC)/cfa_test.c $(SRCDIR)/cfa.h $(SRCDIR)/cfa_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += consumer_test

consumer_test: $(TEST_SRC)/consumer_test.c $(SRCDIR)/consumer.h $(SRCDIR)/consumer_internal.h $(SRCDIR)/psxMutex.h $(SRCDIR)/psxSem.h $(SRCDIR)/psxThread.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += crc_test

crc_test: $(TEST_SRC)/crc_test.c $(SRCDIR)/crc.h $(SRCDIR)/crc_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += dbField_test

dbField_test: $(TEST_SRC)/dbField_test.c $(SRCDIR)/dbField.h $(SRCDIR)/dbField_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += dbf_test

dbf_test: $(TEST_SRC)/dbf_test.c $(SRCDIR)/dbf.h $(SRCDIR)/dbf_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += dec_test

dec_test: $(TEST_SRC)/dec_test.c $(SRCDIR)/dec.h $(SRCDIR)/dec_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += disk_test

disk_test: $(TEST_SRC)/disk_test.c $(SRCDIR)/disk.h $(SRCDIR)/disk_internal.h $(SRCDIR)/Path.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += disks_test

disks_test: $(TEST_SRC)/disks_test.c $(SRCDIR)/disks.h $(SRCDIR)/disks_internal.h $(SRCDIR)/Path.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += eResult_test

eResult_test: $(TEST_SRC)/eResult_test.c $(SRCDIR)/eResult.h $(SRCDIR)/eResult_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += endian_test

endian_test: $(TEST_SRC)/endian_test.c $(SRCDIR)/endian.h $(SRCDIR)/endian_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += enum_test

enum_test: $(TEST_SRC)/enum_test.c $(SRCDIR)/enum.h $(SRCDIR)/enum_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += execArray_test

execArray_test: $(TEST_SRC)/execArray_test.c $(SRCDIR)/execArray.h $(SRCDIR)/execArray_internal.h $(SRCDIR)/ObjArray.h $(SRCDIR)/ptrArray.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += fbsi_test

fbsi_test: $(TEST_SRC)/fbsi_test.c $(SRCDIR)/fbsi.h $(SRCDIR)/fbsi_internal.h $(SRCDIR)/Path.h $(SRCDIR)/u8Array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += fbso_test

fbso_test: $(TEST_SRC)/fbso_test.c $(SRCDIR)/fbso.h $(SRCDIR)/fbso_internal.h $(SRCDIR)/Path.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += fileio_test

fileio_test: $(TEST_SRC)/fileio_test.c $(SRCDIR)/fileio.h $(SRCDIR)/fileio_internal.h $(SRCDIR)/Path.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += genObj_test

genObj_test: $(TEST_SRC)/genObj_test.c $(SRCDIR)/genObj.h $(SRCDIR)/genObj_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += greg_test

greg_test: $(TEST_SRC)/greg_test.c $(SRCDIR)/greg.h $(SRCDIR)/greg_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += hash32_test

hash32_test: $(TEST_SRC)/hash32_test.c $(SRCDIR)/hash32.h $(SRCDIR)/hash32_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += hex_test

hex_test: $(TEST_SRC)/hex_test.c $(SRCDIR)/hex.h $(SRCDIR)/hex_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += hjson_test

hjson_test: $(TEST_SRC)/hjson_test.c $(SRCDIR)/hjson.h $(SRCDIR)/hjson_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += lexj_test

lexj_test: $(TEST_SRC)/lexj_test.c $(SRCDIR)/lexj.h $(SRCDIR)/lexj_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += listdl_test

listdl_test: $(TEST_SRC)/listdl_test.c $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += lru_test

lru_test: $(TEST_SRC)/lru_test.c $(SRCDIR)/lru.h $(SRCDIR)/lru_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += md5ChkSum_test

md5ChkSum_test: $(TEST_SRC)/md5ChkSum_test.c $(SRCDIR)/md5ChkSum.h $(SRCDIR)/md5ChkSum_internal.h $(SRCDIR)/md5_plumb.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += memFile_test

memFile_test: $(TEST_SRC)/memFile_test.c $(SRCDIR)/memFile.h $(SRCDIR)/memFile_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += memrrds_test

memrrds_test: $(TEST_SRC)/memrrds_test.c $(SRCDIR)/memrrds.h $(SRCDIR)/memrrds_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += misc_test

misc_test: $(TEST_SRC)/misc_test.c $(SRCDIR)/misc.h $(SRCDIR)/misc_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += msgBus_test

msgBus_test: $(TEST_SRC)/msgBus_test.c $(SRCDIR)/msgBus.h $(SRCDIR)/msgBus_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $(TEST_SRC)/objTest.c $(TEST_SRC)/objTest_object.c $<
	$(TEST_BIN)/$(@F)

TESTS += objMatrix_test

objMatrix_test: $(TEST_SRC)/objMatrix_test.c $(SRCDIR)/objMatrix.h $(SRCDIR)/objMatrix_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += prt_test

prt_test: $(TEST_SRC)/prt_test.c $(SRCDIR)/prt.h $(SRCDIR)/prt_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += psxCond_test

psxCond_test: $(TEST_SRC)/psxCond_test.c $(SRCDIR)/psxCond.h $(SRCDIR)/psxCond_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += psxLock_test

psxLock_test: $(TEST_SRC)/psxLock_test.c $(SRCDIR)/psxLock.h $(SRCDIR)/psxLock_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += psxMutex_test

psxMutex_test: $(TEST_SRC)/psxMutex_test.c $(SRCDIR)/psxMutex.h $(SRCDIR)/psxMutex_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += psxSem_test

psxSem_test: $(TEST_SRC)/psxSem_test.c $(SRCDIR)/psxSem.h $(SRCDIR)/psxSem_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += psxThread_test

psxThread_test: $(TEST_SRC)/psxThread_test.c $(SRCDIR)/psxThread.h $(SRCDIR)/psxThread_internal.h $(SRCDIR)/psxMutex.h $(SRCDIR)/psxSem.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += ptrArray_test

ptrArray_test: $(TEST_SRC)/ptrArray_test.c $(SRCDIR)/ptrArray.h $(SRCDIR)/ptrArray_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += rbt_tree_test

rbt_tree_test: $(TEST_SRC)/rbt_tree_test.c $(SRCDIR)/rbt_tree.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += rrds_test

rrds_test: $(TEST_SRC)/rrds_test.c $(SRCDIR)/rrds.h $(SRCDIR)/rrds_internal.h $(SRCDIR)/Path.h $(SRCDIR)/hash32.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += scanReader_test

scanReader_test: $(TEST_SRC)/scanReader_test.c $(SRCDIR)/scanReader.h $(SRCDIR)/scanReader_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += screen_test

screen_test: $(TEST_SRC)/screen_test.c $(SRCDIR)/screen.h $(SRCDIR)/screen_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += str_test

str_test: $(TEST_SRC)/str_test.c $(SRCDIR)/str.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += szBT_test

szBT_test: $(TEST_SRC)/szBT_test.c $(SRCDIR)/szBT.h $(SRCDIR)/szBT_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += szData_test

szData_test: $(TEST_SRC)/szData_test.c $(SRCDIR)/szData.h $(SRCDIR)/szData_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += szHash_test

szHash_test: $(TEST_SRC)/szHash_test.c $(SRCDIR)/szHash.h $(SRCDIR)/szHash_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/szTbl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += szTbl_test

szTbl_test: $(TEST_SRC)/szTbl_test.c $(SRCDIR)/szTbl.h $(SRCDIR)/szTbl_internal.h $(SRCDIR)/ptrArray.h $(SRCDIR)/szHash.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += table_test

table_test: $(TEST_SRC)/table_test.c $(SRCDIR)/table.h $(SRCDIR)/table_internal.h $(SRCDIR)/listdl.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += timer_test

timer_test: $(TEST_SRC)/timer_test.c $(SRCDIR)/timer.h $(SRCDIR)/timer_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += trace_test

trace_test: $(TEST_SRC)/trace_test.c $(SRCDIR)/trace.h $(SRCDIR)/trace_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += u12Array_test

u12Array_test: $(TEST_SRC)/u12Array_test.c $(SRCDIR)/u12Array.h $(SRCDIR)/u12Array_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += u32Array_test

u32Array_test: $(TEST_SRC)/u32Array_test.c $(SRCDIR)/u32Array.h $(SRCDIR)/u32Array_internal.h $(SRCDIR)/array.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += u32Matrix_test

u32Matrix_test: $(TEST_SRC)/u32Matrix_test.c $(SRCDIR)/u32Matrix.h $(SRCDIR)/u32Matrix_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += u8Array_test

u8Array_test: $(TEST_SRC)/u8Array_test.c $(SRCDIR)/u8Array.h $(SRCDIR)/u8Array_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += u8VlArray_test

u8VlArray_test: $(TEST_SRC)/u8VlArray_test.c $(SRCDIR)/u8VlArray.h $(SRCDIR)/u8VlArray_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += uint128_test

uint128_test: $(TEST_SRC)/uint128_test.c $(SRCDIR)/uint128.h $(SRCDIR)/uint128_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)

TESTS += utf8_test

utf8_test: $(TEST_SRC)/utf8_test.c $(SRCDIR)/utf8.h $(SRCDIR)/utf8_internal.h $(SRCDIR)/cmn_defs.h 
	$(CC) $(CFLAGS) $(CFLAGS_TEST) -o $(TEST_BIN)/$(@F) $(OBJS) -I$(TEST_SRC) -I$(SRCDIR) $<
	$(TEST_BIN)/$(@F)



$(LIB_PATH):  $(OBJS)
	-cd $(LIBOBJ) ; [ -d $(LIB_FILENAME) ] && rm $(LIB_FILENAME)
	ar rc $(LIB_PATH) $(OBJS)


.PHONY: test
test: $(TESTS)


.PHONY: check
check: $(TESTS)


.PHONY: clean
clean:
	-cd $(TEMP) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)


.PHONY: install
install:
	-cd $(INSTALL_BASE) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)
	-cd $(INSTALL_BASE) ; [ ! -d $(LIBNAM)/include ] && mkdir -p $(LIBNAM)/include/$(SYS)
	cp $(LIB_PATH) $(INSTALL_DIR)/$(LIBNAM).a
	cp src/*.h $(INSTALL_DIR)/include/
	if [ -d src/$(SYS) ]; then \
		cp src/$(SYS)/*.h $(INSTALL_DIR)/include/$(SYS)/; \
	fi


.PHONY: create_dirs
create_dirs:
	[ ! -d $(OBJDIR) ] && mkdir -p $(OBJDIR)/tests


.PHONY: all
all:  clean create_dirs $(LIB_PATH)


