/* 
 * File:   cmn_defs.h
 *
 * Notes:
 *   1	Before including define the following to customize the config bits for
 *		the development environment needed:
 *		_EXPLORER_16		Microchip Explorer 16 board
 *		_MAX32              Diligent MAX 32 board
 *		_NETWORK_SHIELD     Diligent Network Shield
 *   2  CONFIG properties are generated in cmn.c depending upon how the above
 *      options are set.
 *   3  We assume that you have allocated some space for a heap
 *      (Properties -> ld -> heapsize).
 *
 * Created on September 26, 2014, 3:39 PM
 */

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


//#define         _USE_TNEO         1
//  Define the Compiler Environment
//      __AZTECC__      - Aztec C (Being Removed)
//      __BCDOS__       - Borland C++ for MS/DOS (16-Bit)
//      __BC32__        - Borland C++ for MS/DOS (32-Bit)
//      __BCOS2__       - Borland C++ for OS/2 v2.x (32-Bit)
//      __IBMCS2__      - IBM C++ Set/2
//      __MSVC16__      - Microsoft C++ for MS/DOS (16-Bit)
//      __MSVC32__      - Microsoft C++ for Windows 95/NT (32-Bit)
//      __MSVC64__      - Visual Studio (64-Bit)
//      __WATCOM_C386__ - Watcom C++ (32-Bit)
#if     !defined(__APPLE__) && !defined(__AZTEC_C__) &&\
        !defined(__BC_DOS__) && !defined(__BC_32__) &&\
        !defined(__MSVC16__) && !defined(__MSVC32__) && !defined(__MSVC64__) &&\
        !defined(__WATCOM_C386__)
#   error  No compiler environment specified!!!
#endif


//  Define the Operating Environment of the Programs/Routines
//      DPMI32_ENV  - MS/DOS Extender with Windows NT subset support
//      MACOSX_ENV  - Mac OS X Standard Environment
//      MSDOS_ENV   - MS/DOS Standard Environment
//      OS2_ENV     - OS/2 v1.x Support (Being Removed)
//      OS2V2_ENV   - OS/2 v2.x Support
//      PIC32MX_ENV - Microchip PIC32MX Support
//      PIC32MX_TNEO_ENV - Microchip PIC32MX Support w/ TNEO O/S
//      PIC32MZ_ENV - Microchip PIC32MZ Support
//      WIN16_ENV   - Windows v3.1 with MS/DOS
//      WIN32_ENV   - Win32 Support
//      WIN64_ENV   - Win64 Support
#if     !defined(__DPMI32_ENV__) && !defined(__MSDOS_ENV__) &&\
        !defined(__PIC32MX_ENV__) && !defined(__PIC32MX_TNEO_ENV__) &&\
        !defined(__PIC32MZ_ENV__) &&\
        !defined(__WIN16_ENV__) && !defined(__WIN32_ENV__) && !defined(__WIN64_ENV__) &&\
        !defined(__MACOSX_ENV__)
#   error  No execution environment specified!!!
#endif



#if             defined(__MACOSX_ENV__)
#   include        <dirent.h>
#   include        <errno.h>
#   include        <pthread.h>
#   include        <unistd.h>
#   include        <sys/dirent.h>
#   include        <sys/time.h>
#endif
#if             defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#   define         STRICT
#   include        <windows.h>
#   include        <windowsx.h>
#   include        <signal.h>
#   include        <unistd_win.h>
#endif
#include        <ctype.h>
#include        <fcntl.h>
#include        <stdarg.h>
#include        <stdbool.h>
#include        <stddef.h>
#include        <stdint.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        <time.h>
#include        <wchar.h>
#include        <sys/stat.h>
#include        <sys/types.h>


#include        <str.h>


#ifndef     CMN_DEFS_H
#define     CMN_DEFS_H   1


#ifdef	__cplusplus
extern "C" {
#endif
    
    
    
    
    //****************************************************************
    //* * * * * * * * * * *  Data Definitions  * * * * * * * * * * * *
    //****************************************************************

    typedef struct cmn_data_s   CMN_DATA;

#ifndef         OBJ_IDENTS_ENUM
#define         OBJ_IDENTS_ENUM	1
    typedef enum obj_idents_e {
        OBJ_IDENT_UNKNOWN=0,
        OBJ_IDENT_SHARED,               // Special Inherited Class for Shared Objects
        OBJ_IDENT_SHARED_CLASS,
        OBJ_IDENT_MAIN,                 // Main Program Object       (Used in Programs)
        OBJ_IDENT_MAIN_CLASS,
        OBJ_IDENT_EXEC,                 // Exec Object               (Used in Programs)
        OBJ_IDENT_EXEC_CLASS,
        OBJ_IDENT_APPL,                 // Application Base Object
        OBJ_IDENT_APPL_CLASS,
        OBJ_IDENT_ARRAY,                // Expandable Array
        OBJ_IDENT_ARRAY_CLASS,
        OBJ_IDENT_ASCII,                // ASCII Character Set
        OBJ_IDENT_ASCII_CLASS,
        OBJ_IDENT_ASTR,                 // ASCII/UTF-8 String
        OBJ_IDENT_ASTR_CLASS,
        OBJ_IDENT_ASTRARRAY,            // an Array of ASCII/UTF-8 Strings
        OBJ_IDENT_ASTRARRAY_CLASS,
        OBJ_IDENT_ASTRC,                // ASCII String Constant
        OBJ_IDENT_ASTRC_CLASS,
        OBJ_IDENT_ASTRCREADER,          // ASCII String Constant Reader
        OBJ_IDENT_ASTRCREADER_CLASS,
        OBJ_IDENT_AUDIOCW,              // Morse Code Audio
        OBJ_IDENT_AUDIOCW_CLASS,
        OBJ_IDENT_AUDIOWAV,             // WAV Audio
        OBJ_IDENT_AUDIOWAV_CLASS,
        OBJ_IDENT_BITMATRIX,
        OBJ_IDENT_BITMATRIX_CLASS,
        OBJ_IDENT_BITSET,
        OBJ_IDENT_BITSET_CLASS,
        OBJ_IDENT_BLKDRCDS16,           // Block of variable sized records with
        //                              // an optional fixed sized area
        OBJ_IDENT_BLKDRCDS16_CLASS,
        OBJ_IDENT_BLKIDX16,             // Data Block of variable sized data and
        //                              // an optional fixed sized area
        OBJ_IDENT_BLKIDX16_CLASS,
        OBJ_IDENT_BLKS,                 // A list of Data Blocks
        OBJ_IDENT_BLKS_CLASS,
        OBJ_IDENT_BLOCK16,              // Data Block with an optional fixed sized area
        //                              // and Fixed Sized Data Area
        OBJ_IDENT_BLOCK16_CLASS,
        OBJ_IDENT_BLOCK32,              // Data Block with an optional Fixed Sized Header
        //                              // and Fixed Sized Data Area
        OBJ_IDENT_BLOCK32_CLASS,
        OBJ_IDENT_BLOCKS,               // A list of Data Blocks and Records
        OBJ_IDENT_BLOCKS_CLASS,
        OBJ_IDENT_BPT32IDX,             // B-Plus 32-Bit Tree Index Node
        OBJ_IDENT_BPT32IDX_CLASS,
        OBJ_IDENT_BPT32LF,              // B-Plus 32-Bit Tree Leaf Node
        OBJ_IDENT_BPT32LF_CLASS,
        OBJ_IDENT_BPT32,                // B-Plus 32-Bit Tree
        OBJ_IDENT_BPT32_CLASS,
        OBJ_IDENT_BPTINDEX,             // B-Plus Index Node
        OBJ_IDENT_BPTINDEX_CLASS,
        OBJ_IDENT_BPTLEAF,              // B-Plus Leaf Node
        OBJ_IDENT_BPTLEAF_CLASS,
        OBJ_IDENT_BPTREE,               // B-Plus Tree Index
        OBJ_IDENT_BPTREE_CLASS,
        OBJ_IDENT_BSTR,                 // Basic String
        OBJ_IDENT_BSTR_CLASS,
        OBJ_IDENT_BTP,                  /* Binary Search Tree */
        OBJ_IDENT_BTP_CLASS,
        OBJ_IDENT_CB,                   /* Generic Circular Buffer */
        OBJ_IDENT_CB_CLASS,
        OBJ_IDENT_CB8,                  /* Circular Buffer for 8-bit data */
        OBJ_IDENT_CB16,                 /* Circular Buffer for 16-bit data */
        OBJ_IDENT_CB16_CLASS,
        OBJ_IDENT_CB32,                 /* Circular Buffer for 32-bit data */
        OBJ_IDENT_CB32_CLASS,
        OBJ_IDENT_CFA,                  // C Fixed Array
        OBJ_IDENT_CFA_CLASS,
        OBJ_IDENT_CMDUTL,               // Command Utilities
        OBJ_IDENT_CMDUTL_CLASS,
        OBJ_IDENT_COMPILER,
        OBJ_IDENT_COMPILER_CLASS,
        OBJ_IDENT_CON,                  // Console Object
        OBJ_IDENT_CON_CLASS,
        OBJ_IDENT_CON_FIO,              // Console File I/O Object
        OBJ_IDENT_CON_FIO_CLASS,
        OBJ_IDENT_CONSUMER,
        OBJ_IDENT_CONSUMER_CLASS,
        OBJ_IDENT_CONXMT,
        OBJ_IDENT_CONXMT_CLASS,
        OBJ_IDENT_CRC,                  // CRC Calculations
        OBJ_IDENT_CRC_CLASS,
        OBJ_IDENT_CSV,
        OBJ_IDENT_CSV_CLASS,
        OBJ_IDENT_DATETIME,             // Date & Time
        OBJ_IDENT_DATETIME_CLASS,
        OBJ_IDENT_DBCSV,                // Comma-Delimited Database
        OBJ_IDENT_DBCSV_CLASS,
        OBJ_IDENT_DBF,                  // DBase III/IV
        OBJ_IDENT_DBF_CLASS,
        OBJ_IDENT_DBFIELD,              // DBase III/IV Field
        OBJ_IDENT_DBFIELD_CLASS,
        OBJ_IDENT_DEC,                  // Decimal (Base 10)
        OBJ_IDENT_DEC_CLASS,
        OBJ_IDENT_DIR,
        OBJ_IDENT_DIR_CLASS,
        OBJ_IDENT_DIRENTRY,
        OBJ_IDENT_DIRENTRY_CLASS,
        OBJ_IDENT_DISK,                 // Disk Information/Management
        OBJ_IDENT_DISK_CLASS,
        OBJ_IDENT_DISKS,                // Information/Management of Disks
        OBJ_IDENT_DISKS_CLASS,
        OBJ_IDENT_EBCDIC,               // EBCDIC Character
        OBJ_IDENT_EBCDIC_CLASS,
        OBJ_IDENT_ENDIAN,               // Little/Big Endian Manipulation
        OBJ_IDENT_ENDIAN_CLASS,
        OBJ_IDENT_ENUM,                 // Enumerator Base Class
        OBJ_IDENT_ENUM_CLASS,
        OBJ_IDENT_ERESULT,
        OBJ_IDENT_ERESULT_CLASS,
        OBJ_IDENT_EXECARRAY,            // An Array of Function/Object(s) pairs
        OBJ_IDENT_EXECARRAY_CLASS,
        OBJ_IDENT_FALSE,
        OBJ_IDENT_FALSE_CLASS,
        OBJ_IDENT_FBSI,                 // Fixed Blocked Input Class
        OBJ_IDENT_FBSI_CLASS,
        OBJ_IDENT_FBSO,                 // Fixed Blocked Output Class
        OBJ_IDENT_FBSO_CLASS,
        OBJ_IDENT_FCB,                  // MSDOS/CPM File Control Block
        OBJ_IDENT_FCB_CLASS,
        OBJ_IDENT_FILE,                 // File
        OBJ_IDENT_FILE_CLASS,
        OBJ_IDENT_FILEIO,               // File I/O
        OBJ_IDENT_FILEIO_CLASS,
        OBJ_IDENT_GENOBJ,               // Generate an Object
        OBJ_IDENT_GENOBJ_CLASS,
        OBJ_IDENT_GREG,                 // Gregorian Date
        OBJ_IDENT_GREG_CLASS,
        OBJ_IDENT_HASH32,               // 32-Bit Key Hash Table
        OBJ_IDENT_HASH32_CLASS,
        OBJ_IDENT_HASHTBL,              // Hash Table Base
        OBJ_IDENT_HASHTBL_CLASS,
        OBJ_IDENT_HEX,                  // Hex Input/Output
        OBJ_IDENT_HEX_CLASS,
        OBJ_IDENT_HJSON,                // HJSON (loose JSON) Parser
        OBJ_IDENT_HJSON_CLASS,
        OBJ_IDENT_I32ARRAY,             // Array of int32_t
        OBJ_IDENT_I32ARRAY_CLASS,
        OBJ_IDENT_IOBASE,               // I/O Base Logic
        OBJ_IDENT_IOBASE_CLASS,
        OBJ_IDENT_JSONIN,               // Standardized JSON Input
        OBJ_IDENT_JSONIN_CLASS,
        OBJ_IDENT_JSONOUT,              // Standardized JSON Output
        OBJ_IDENT_JSONOUT_CLASS,
        OBJ_IDENT_JSONPP,               // JSON Pretty Printer
        OBJ_IDENT_JSONPP_CLASS,
        OBJ_IDENT_LEX,                  // Generic Lexical Scanner
        OBJ_IDENT_LEX_CLASS,
        OBJ_IDENT_LEXJ,                 // Simple Lexical Scanner for HJSON
        OBJ_IDENT_LEXJ_CLASS,
        OBJ_IDENT_LEXS,                 // Simple Lexical Scanner for JSON, CSV, etc
        OBJ_IDENT_LEXS_CLASS,
        OBJ_IDENT_LISTDL,               // Generic Doubly-linked List
        OBJ_IDENT_LISTDL_CLASS,
        OBJ_IDENT_LRU,                  // Least Recently Used Caching
        OBJ_IDENT_LRU_CLASS,
        OBJ_IDENT_MD5CHKSUM,            // MD5 Check Sum Calculation
        OBJ_IDENT_MD5CHKSUM_CLASS,
        OBJ_IDENT_MEMFILE,              // Memory-Based File
        OBJ_IDENT_MEMFILE_CLASS,
        OBJ_IDENT_MEMMSC,               // Memory Debug for MS C
        OBJ_IDENT_MEMMSC_CLASS,
        OBJ_IDENT_MEMOSX,               // Memory Debug for OSX
        OBJ_IDENT_MEMOSX_CLASS,
        OBJ_IDENT_MEMRRDS,              // Memory-Based Relative Record Dataset/File
        OBJ_IDENT_MEMRRDS_CLASS,
        OBJ_IDENT_MISC,                 // Miscellaneous Functions
        OBJ_IDENT_MISC_CLASS,
        OBJ_IDENT_MSGBUS,               // Message Broadcast
        OBJ_IDENT_MSGBUS_CLASS,
        OBJ_IDENT_MSGDATA,              // Message Data
        OBJ_IDENT_MSGDATA_CLASS,
        OBJ_IDENT_NAME,
        OBJ_IDENT_NAME_CLASS,
        OBJ_IDENT_NODE,
        OBJ_IDENT_NODE_CLASS,
        OBJ_IDENT_NODEARC,              // An Arc in a Node Graph
        OBJ_IDENT_NODEARC_CLASS,
        OBJ_IDENT_NODEARRAY,            // An Array of Nodes
        OBJ_IDENT_NODEARRAY_CLASS,
        OBJ_IDENT_NODEBTREE,            // A Binary Tree of Nodes
        OBJ_IDENT_NODEBTREE_CLASS,
        OBJ_IDENT_NODEBTP,              // A Binary Tree of Nodes using pointer linkage
        OBJ_IDENT_NODEBTP_CLASS,        //      between nodes
        OBJ_IDENT_NODEENTRY,            // A Node to be used in other containers
        OBJ_IDENT_NODEENTRY_CLASS,
        OBJ_IDENT_NODEENUM,             // Node Enumeration
        OBJ_IDENT_NODEENUM_CLASS,
        OBJ_IDENT_NODEGRAPH,            // Graph of Nodes
        OBJ_IDENT_NODEGRAPH_CLASS,
        OBJ_IDENT_NODEHASH,             // A Hash Table of Nodes
        OBJ_IDENT_NODEHASH_CLASS,
        OBJ_IDENT_NODELINK,             // A Node w/Index Links
        OBJ_IDENT_NODELINK_CLASS,
        OBJ_IDENT_NODELNKP,             // A Node w/Pointer Links
        OBJ_IDENT_NODELNKP_CLASS,
        OBJ_IDENT_NODELIST,             // A List of Nodes
        OBJ_IDENT_NODELIST_CLASS,
        OBJ_IDENT_NODEMATRIX,
        OBJ_IDENT_NODEMATRIX_CLASS,
        OBJ_IDENT_NODESCAN,             // Node Tree Scanner
        OBJ_IDENT_NODESCAN_CLASS,
        OBJ_IDENT_NODETREE,             // A Tree of Nodes using index linkage between
        OBJ_IDENT_NODETREE_CLASS,       // nodes
        OBJ_IDENT_NODETRP,              // A Tree of Nodes using pointer linkage between
        OBJ_IDENT_NODETRP_CLASS,        // nodes
        OBJ_IDENT_NULL,
        OBJ_IDENT_NULL_CLASS,
        OBJ_IDENT_NUMBER,               // Generic Number
        OBJ_IDENT_NUMBER_CLASS,
        OBJ_IDENT_OBJ,
        OBJ_IDENT_OBJ_CLASS,
        OBJ_IDENT_OBJARRAY,             // Array of Objects
        OBJ_IDENT_OBJARRAY_CLASS,
        OBJ_IDENT_OBJCB,                // Circular Buffer of Objects
        OBJ_IDENT_OBJCB_CLASS,
        OBJ_IDENT_OBJENUM,              // Object Enumeration
        OBJ_IDENT_OBJENUM_CLASS,
        OBJ_IDENT_OBJHASH,              // Hash Dictionary of Objects
        OBJ_IDENT_OBJHASH_CLASS,
        OBJ_IDENT_OBJLIST,              // List of Objects
        OBJ_IDENT_OBJLIST_CLASS,
        OBJ_IDENT_OBJMATRIX,            // 2 dimensional array of Objects
        OBJ_IDENT_OBJMATRIX_CLASS,
        OBJ_IDENT_OBJMETHOD,            // Object Method Pointer
        OBJ_IDENT_OBJMETHOD_CLASS,
        OBJ_IDENT_OBJREGISTRY,          // Object Registry
        OBJ_IDENT_OBJREGISTRY_CLASS,
        OBJ_IDENT_OSC,
        OBJ_IDENT_OSC_CLASS,
        OBJ_IDENT_PACKET,
        OBJ_IDENT_PACKET_CLASS,
        OBJ_IDENT_PARSER,
        OBJ_IDENT_PARSER_CLASS,
        OBJ_IDENT_PASSTR,
        OBJ_IDENT_PASSTR_CLASS,
        OBJ_IDENT_PATH,                 // File Path
        OBJ_IDENT_PATH_CLASS,
        OBJ_IDENT_PBXPROJ,              // Xcode pbxproj file parser
        OBJ_IDENT_PBXPROJ_CLASS,
        OBJ_IDENT_PLIST,                // PLIST Parser
        OBJ_IDENT_PLIST_CLASS,
        OBJ_IDENT_PPLEX,                // Preprocessor Lexical Constants
        OBJ_IDENT_PPLEX_CLASS,
        OBJ_IDENT_PPLEX1,               // Preprocessor Lexical Scanner - Phase 1
        OBJ_IDENT_PPLEX1_CLASS,
        OBJ_IDENT_PPLEX2,               // Preprocessor Lexical Scanner - Phase 2
        OBJ_IDENT_PPLEX2_CLASS,
        OBJ_IDENT_PPLEX3,               // Preprocessor Lexical Scanner - Phase 3
        OBJ_IDENT_PPLEX3_CLASS,
        OBJ_IDENT_PRODCONS,             // Producer/Consumer Pattern
        OBJ_IDENT_PRODCONS_CLASS,
        OBJ_IDENT_PROTOCOL,             // Protocol LAYER which uses RECEIVE and TRANSMIT
        OBJ_IDENT_PROTOCOL_CLASS,
        OBJ_IDENT_PRT,
        OBJ_IDENT_PRT_CLASS,
        // The Posix Classes are an attempt to create class that can be used in
        // various O/S's without problems.
        OBJ_IDENT_PSXCOND,              // Posix Condition
        OBJ_IDENT_PSXCOND_CLASS,
        OBJ_IDENT_PSXLOCK,              // Posix Lock
        OBJ_IDENT_PSXEXEC,              // Posix Task Execution
        OBJ_IDENT_PSXEXEC_CLASS,
        OBJ_IDENT_PSXLOCK_CLASS,
        OBJ_IDENT_PSXMUTEX,             // Posix Mutex
        OBJ_IDENT_PSXMUTEX_CLASS,
        OBJ_IDENT_PSXSEM,               // Posix Semaphore
        OBJ_IDENT_PSXSEM_CLASS,
        OBJ_IDENT_PSXTHREAD,            // Posix Thread
        OBJ_IDENT_PSXTHREAD_CLASS,
        OBJ_IDENT_PTRARRAY,             // Generic Array of Pointers
        OBJ_IDENT_PTRARRAY_CLASS,
        OBJ_IDENT_PTRCB,                // Generic Circular Buffer of Pointers
        OBJ_IDENT_PTRCB_CLASS,
        OBJ_IDENT_PTRTBL,
        OBJ_IDENT_PTRTBL_CLASS,
        OBJ_IDENT_RBTREE,               // Generic Red-Black Tree (see rbt_tree.h)
        OBJ_IDENT_RBTREE_CLASS,
        OBJ_IDENT_RECEIVE,              // Protocol Receive Handler
        OBJ_IDENT_RECEIVE_CLASS,
        OBJ_IDENT_RESPONDER,
        OBJ_IDENT_RETRANSBUF,           // Protocol Retransmit Buffer
        OBJ_IDENT_RETRANSBUF_CLASS,
        OBJ_IDENT_RRDS,                 // Relative Record Database
        OBJ_IDENT_RRDS_CLASS,
        OBJ_IDENT_RRDS32,               // Relative Record Database - 32 bit Logical
        //                              //                              Record Number
        OBJ_IDENT_RRDS32_CLASS,
        OBJ_IDENT_SCANNER,              // Tablized Command Processor
        OBJ_IDENT_SCANNER_CLASS,
        OBJ_IDENT_SCANREADER,           // ASCII String Constant Reader
        OBJ_IDENT_SCANREADER_CLASS,
        OBJ_IDENT_SCREEN,               // Terminal Screen Handler
        OBJ_IDENT_SCREEN_CLASS,
        OBJ_IDENT_SGRAPH,               // Simple Graph
        OBJ_IDENT_SGRAPH_CLASS,
        OBJ_IDENT_SIDX,                 // Simple Integer Index
        OBJ_IDENT_SIDX_CLASS,
        OBJ_IDENT_SIDXE,                // Simple Integer Index with extended info
        OBJ_IDENT_SIDXE_CLASS,
        OBJ_IDENT_SRC,
        OBJ_IDENT_SRC_CLASS,
        OBJ_IDENT_SRCERROR,             // Source Error Message
        OBJ_IDENT_SRCERROR_CLASS,
        OBJ_IDENT_SRCERRORS,            // Source Error Messages
        OBJ_IDENT_SRCERRORS_CLASS,
        OBJ_IDENT_SRCFILE,
        OBJ_IDENT_SRCFILE_CLASS,
        OBJ_IDENT_SRCFILES,
        OBJ_IDENT_SRCFILES_CLASS,
        OBJ_IDENT_SRCLOC,               // Source Location (File, Line, Col)
        OBJ_IDENT_SRCLOC_CLASS,
        OBJ_IDENT_SRECORDS,             // S-Record Reader/Writer
        OBJ_IDENT_SRECORDS_CLASS,
        OBJ_IDENT_SYMATTR,              // Symbol Table Attributes
        OBJ_IDENT_SYMATTR_CLASS,
        OBJ_IDENT_SYMENTRY,             // Symbol Table Entry
        OBJ_IDENT_SYMENTRY_CLASS,
        OBJ_IDENT_SYMTABLE,             // Symbol Table
        OBJ_IDENT_SYMTABLE_CLASS,
        OBJ_IDENT_SZDATA,               // Static String with Data
        OBJ_IDENT_SZDATA_CLASS,
        OBJ_IDENT_SZHASH,               // Store void data with a char string key
        OBJ_IDENT_SZHASH_CLASS,
        OBJ_IDENT_SZTBL,                // Static String Table
        OBJ_IDENT_SZTBL_CLASS,
        OBJ_IDENT_TABLE,
        OBJ_IDENT_TABLE_CLASS,
        OBJ_IDENT_TERNARY,              // Ternary Tree
        OBJ_IDENT_TERNARY_CLASS,
        OBJ_IDENT_TEXTIN,               // Text Input Class
        OBJ_IDENT_TEXTIN_CLASS,
        OBJ_IDENT_TEXTOUT,              // Text Output Class
        OBJ_IDENT_TEXTOUT_CLASS,
        OBJ_IDENT_THREAD,               // Separate Threads with own stack
        OBJ_IDENT_THREAD_CLASS,
        OBJ_IDENT_TIMER,
        OBJ_IDENT_TIMER_CLASS,
        OBJ_IDENT_TOKEN,                // Lexical Token
        OBJ_IDENT_TOKEN_CLASS,
        OBJ_IDENT_TOKENC,               // Immutable Lexical Token
        OBJ_IDENT_TOKENC_CLASS,
        OBJ_IDENT_TOKENLIST,            // A List of Lexical Tokens
        OBJ_IDENT_TOKENLIST_CLASS,
        OBJ_IDENT_TRACE,
        OBJ_IDENT_TRACE_CLASS,
        OBJ_IDENT_TRANSMIT,             // Protocol Transmit Handler
        OBJ_IDENT_TRANSMIT_CLASS,
        OBJ_IDENT_TRCTBL,
        OBJ_IDENT_TRCTBL_CLASS,
        OBJ_IDENT_TRIE,
        OBJ_IDENT_TRIE_CLASS,
        OBJ_IDENT_TRIEMP,               // Minimal Prefix Trie
        OBJ_IDENT_TRIEMP_CLASS,
        OBJ_IDENT_TRUE,
        OBJ_IDENT_TRUE_CLASS,
        OBJ_IDENT_U12ARRAY,
        OBJ_IDENT_U12ARRAY_CLASS,
        OBJ_IDENT_U16ARRAY,
        OBJ_IDENT_U16ARRAY_CLASS,
        OBJ_IDENT_U16MATRIX,
        OBJ_IDENT_U16MATRIX_CLASS,
        OBJ_IDENT_U32ARRAY,
        OBJ_IDENT_U32ARRAY_CLASS,
        OBJ_IDENT_U32MATRIX,
        OBJ_IDENT_U32MATRIX_CLASS,
        OBJ_IDENT_U8ARRAY,
        OBJ_IDENT_U8ARRAY_CLASS,
        OBJ_IDENT_UINT128,
        OBJ_IDENT_UINT128_CLASS,
        OBJ_IDENT_UTF8,
        OBJ_IDENT_UTF8_CLASS,
        OBJ_IDENT_UTF8FILE,
        OBJ_IDENT_UTF8FILE_CLASS,
        OBJ_IDENT_VALUE,                // Any type of value
        OBJ_IDENT_VALUE_CLASS,
        OBJ_IDENT_VISITOR,              // Visitor Base Class
        OBJ_IDENT_VISITOR_CLASS,
        OBJ_IDENT_WAV,                  // WAV File
        OBJ_IDENT_WAV_CLASS,
        OBJ_IDENT_W32STR,
        OBJ_IDENT_W32STR_CLASS,
        OBJ_IDENT_W32STRARRAY,          // an Array of Wide Strings
        OBJ_IDENT_W32STRARRAY_CLASS,
        OBJ_IDENT_W32STRC,
        OBJ_IDENT_W32STRC_CLASS,
        OBJ_IDENT_W32_READER,           // UTF-32 Reader
        OBJ_IDENT_W32_READER_CLASS,
        OBJ_IDENT_WISP,                 // A Lisp-like machine
        OBJ_IDENT_WISP_CLASS,
        OBJ_IDENT_XML,
        OBJ_IDENT_XML_CLASS,
        OBJ_IDENT_OTHER_LIBS=8192,
        OBJ_IDENT_CAN_ENTRIES=OBJ_IDENT_OTHER_LIBS,                 // 128 Objects
        OBJ_IDENT_COMPILER_ENTRIES=OBJ_IDENT_CAN_ENTRIES+256,       // 128 Objects
        OBJ_IDENT_DISK_ENTRIES=OBJ_IDENT_COMPILER_ENTRIES+256,      //  64 Objects
        OBJ_IDENT_J1939_ENTRIES=OBJ_IDENT_DISK_ENTRIES+128,         //  64 Objects
        OBJ_IDENT_LL1_ENTRIES=OBJ_IDENT_J1939_ENTRIES+128,          //  64 Objects
        OBJ_IDENT_OS_ENTRIES=OBJ_IDENT_J1939_ENTRIES+128,           // 128 Objects
        OBJ_IDENT_PARSERS_ENTRIES=OBJ_IDENT_OS_ENTRIES+128,         //  64 Objects
        OBJ_IDENT_PIC32_ENTRIES=OBJ_IDENT_PARSERS_ENTRIES+128,      //  64 Objects
        OBJ_IDENT_EMU_ENTRIES=OBJ_IDENT_PIC32_ENTRIES+256,          //  32 Objects
        OBJ_IDENT_TERM_ENTRIES=OBJ_IDENT_EMU_ENTRIES+256,           //  32 Objects
        OBJ_IDENT_USER_ENTRIES=16384
    } OBJ_IDENTS;
#endif
    
    
#define ANSI_COLOR_FORE_BLACK           "\x1b[30m"
#define ANSI_COLOR_FORE_RED             "\x1b[31m"
#define ANSI_COLOR_FORE_GREEN           "\x1b[32m"
#define ANSI_COLOR_FORE_YELLOW          "\x1b[33m"
#define ANSI_COLOR_FORE_BLUE            "\x1b[34m"
#define ANSI_COLOR_FORE_MAGENTA         "\x1b[35m"
#define ANSI_COLOR_FORE_CYAN            "\x1b[36m"
#define ANSI_COLOR_FORE_WHITE           "\x1b[37m"
#define ANSI_COLOR_FORE_BRIGHT_BLACK    "\x1b[1m\x1b[30m"
#define ANSI_COLOR_FORE_BRIGHT_RED      "\x1b[1m\x1b[31m"
#define ANSI_COLOR_FORE_BRIGHT_GREEN    "\x1b[1m\x1b[32m"
#define ANSI_COLOR_FORE_BRIGHT_YELLOW   "\x1b[1m\x1b[33m"
#define ANSI_COLOR_FORE_BRIGHT_BLUE     "\x1b[1m\x1b[34m"
#define ANSI_COLOR_FORE_BRIGHT_MAGENTA  "\x1b[1m\x1b[35m"
#define ANSI_COLOR_FORE_BRIGHT_CYAN     "\x1b[1m\x1b[36m"
#define ANSI_COLOR_FORE_BRIGHT_WHITE    "\x1b[1m\x1b[37m"
#define ANSI_COLOR_RESET                "\x1b[0m"
    
#define W32CHR_T    int32_t



    

    //****************************************************************
    //* * * * * * * * * * *  Function Definitions  * * * * * * * * * *
    //****************************************************************




    //****************************************************************
    //* * * * * * *  Architecture Dependent Definitions  * * * * * * *
    //****************************************************************

#include    "obj.h"


    typedef uint32_t    (*GET_SFR)(void);
    typedef void        (*PUT_SFR)(uint32_t);
    typedef void        (*PUTCLR_SFR)(void);
    typedef void        (*PUTCLRSET_SFR)(uint32_t);

    // Comparison Routine: returns 0 if *p0 == *p1,
    // -n if *p0 < *p1 or +n if *p0 > *p1.
    typedef int         (*P_COMPARE)(void *p0, void *p1);

    typedef void        (*P_VOID_EXIT0)(void);
    typedef void        (*P_VOID_EXIT1)(void *);
    typedef void        (*P_VOID_EXIT2)(void *, void *);
    typedef void        (*P_VOID_EXIT3)(void *, void *, void *);
    typedef void        (*P_VOID_EXIT11)(void *, void *, uint32_t);
    typedef void        (*P_VOID_EXIT12)(void *, bool);
    typedef bool        (*P_BOOL_EXIT1)(void *);
    typedef bool        (*P_BOOL_EXIT2)(void *, void *);
    typedef bool        (*P_BOOL_EXIT3)(void *, void *, void *);
    typedef ERESULT     (*P_ERESULT_EXIT1)(void *);
    typedef ERESULT     (*P_ERESULT_EXIT2)(void *, void *);
    typedef ERESULT     (*P_ERESULT_EXIT3)(void *, void *, void *);
    typedef ERESULT     (*P_ERESULT_EXIT4)(void *, void *, void *, void *);
    typedef ERESULT     (*P_ERESULT_EXIT10)(void *, uint32_t, void *);
    typedef ERESULT     (*P_ERESULT_EXIT11)(void *, void *, uint32_t);
    typedef uint32_t    (*P_U32_EXIT1)(void *);
    typedef uint32_t    (*P_U32_EXIT2_U32)(void *,uint32_t);
    typedef void        (*P_MSGRCV)(void *, uint16_t, uint8_t *);
    typedef void *      (*P_PTR_EXIT1)(void *);
    typedef void *      (*P_VOID_PTR_EXIT1)(void *);



    // All of the scan routines advance the ppCmdStr pointer as they
    // scan the string.

    /* CmdStr is scanned one character at a time into the Output
     * buffer supplied. The scan will go until it hits end of line
     * the end of the string. It will copy at most maxLen characters
     * to the output.
     */
    bool            scanString(
        char			**ppCmdStr,         // NUL terminated string pointer
        uint32_t        maxLen,
        uint32_t		*pScannedLen,       // (returned) Scanned Length
                                            // (not including leading whitespace)
        char			*pOutput            // Output Buffer Pointer
    );

    bool            scanDec32(
        char			**ppCmdStr,         // NUL terminated string pointer
        uint32_t		*pScannedLen,       // (returned,optional) Scanned Length
                                            // (includes leading whitespace)
        uint32_t		*pValue             // (returned,optional) Scanned Number
    );

    bool            scanHex32(
        char			**ppCmdStr,         // NUL terminated string pointer
        uint32_t		*pScannedLen,       // (returned,optional) Scanned Length
        uint32_t		*pValue             // (returned,optional) Scanned Number
    );

    bool            scanWhite(
        char			**ppCmdStr,         // NUL terminated string pointer
        uint32_t		*pScannedLen        // (returned,optional) Scanned Length
    );


    
#define     IS_POWER_OF_2(x)    ((x != 0) && !(x & (x - 1)))
#define     ROUNDUP2(n)         (((n+2-1) >> 1) << 1)
#define     ROUNDUP4(n)         (((n+4-1) >> 2) << 2)
#define     ROUNDUP8(n)         (((n+8-1) >> 3) << 3)
#define     ROUNDUP16(n)        (((n+16-1) >> 4) << 4)
#define     ROUNDUP32(n)        (((n+32-1) >> 5) << 5)


// In C, "long" is defined to be the word size of the computer
// where "int" might be shorter.
#define WORDSIZE sizeof(long)   /* word size in bytes */
#define ROUNDUP_WORD(x) (((x + WORDSIZE - 1) / WORDSIZE) * WORDSIZE)
    

#define     MAKEUINT16(h,l) ((uint16_t)((uint8_t)(l))|((uint8_t)((uint8_t)(h))<<8))
#define     MAKEUINT32(h,l) ((uint32_t)((uint16_t)(l))|((uint32_t)((uint16_t)(h))<<16))
#define     MAKEUINT64(h,l) ((uint64_t)((uint32_t)(l))|((uint64_t)((uint32_t)(h))<<32))
    




    //****************************************************************
    //* * * * * * * * * * *  Function Definitions  * * * * * * * * * *
    //****************************************************************

    //          ** General Exception Handler Functions **
    // cmn_ActivateGeneralExceptionHandler needs to be called at the
    // beginning of the program to activate the handler.
    void            cmn_ActivateGeneralExceptionHandler(void);
    const
    char *          cmn_getLastExceptionReason(void);
    uint32_t        cmn_getLastExceptionAddress(void);



#define WAIT_INFINITE   (-1)

#ifdef	__cplusplus
}
#endif



//****************************************************************
//* * * * * * * * *  Dependent Object Definitions  * * * * * * * *
//****************************************************************

// Some objects are co-dependent which can cause recursive header
// includes. So, we define the objects and their vtbls here.

typedef struct AStr_data_s          ASTR_DATA;
typedef struct AStr_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in AStrC_object.c.
    // Properties:
    // Methods:
    const
    char *      (*pGetData)(ASTR_DATA *);
    uint32_t    (*pGetLength)(ASTR_DATA *);
} ASTR_VTBL;


typedef struct AStrC_data_s         ASTRC_DATA;
typedef struct AStrC_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in AStrC_object.c.
    // Properties:
    // Methods:
    const
    char *      (*pGetData)(ASTRC_DATA *);
    uint32_t    (*pGetLength)(ASTRC_DATA *);
} ASTRC_VTBL;


typedef struct AStrArray_data_s     ASTRARRAY_DATA;
typedef struct AStrArray_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in WStrArray_object.c.
    // Properties:
    // Methods:
    //bool        (*pIsEnabled)(WSTRARRAY_DATA *);
} ASTRARRAY_VTBL;


typedef struct file_data_s	FILE_DATA;
typedef struct file_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in fat16_object.c.
    // Properties:
    // Methods:
    //bool        (*pIsEnabled)(FBSI_DATA *);
} FILE_VTBL;


typedef struct path_data_s          PATH_DATA;
typedef struct path_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in WStrArray_object.c.
    // Properties:
    // Methods:
    //bool        (*pIsEnabled)(WSTRARRAY_DATA *);
} PATH_VTBL;


typedef struct u8Array_data_s	U8ARRAY_DATA;
typedef struct u8Array_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in fileio_object.c.
    // Properties:
    // Methods:
    //bool        (*pIsEnabled)(FILEIO_DATA *);
} U8ARRAY_VTBL;


typedef struct W32Str_data_s        W32STR_DATA;
typedef struct W32Str_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in WStrC_object.c.
    // Properties:
    // Methods:
    const
    W32CHR_T *  (*pGetData)(W32STR_DATA *);
    uint32_t    (*pGetLength)(W32STR_DATA *);
} W32STR_VTBL;


typedef struct W32StrC_data_s       W32STRC_DATA;
typedef struct W32StrC_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in WStrC_object.c.
    // Properties:
    // Methods:
    const
    W32CHR_T *  (*pGetData)(W32STRC_DATA *);
    uint32_t    (*pGetLength)(W32STRC_DATA *);
} W32STRC_VTBL;



#include    <eResult.h>


#if defined(__MACOSX_ENV__)
#	include     <cmn_osx.h>
#   include     <memOSX.h>
#endif
#if defined(__WIN32_ENV__)
#	include     <win32/cmn_win32.h>
#   include     <win32/memWin32.h>
#endif
#if defined(__WIN64_ENV__)
#	include     <win64/cmn_win64.h>
#   include     <win64/memWin64.h>
#endif
#if defined(__PIC32MX_ENV__)
#	include    <pic32mx/cmn_pic32mx.h>
#endif
#if defined( __PIC32MZ_ENV__ )
#	include    <pic32mz/cmn_pic32mz.h>
#endif





#endif	/* CMN_DEFS_H */

