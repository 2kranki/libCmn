// vi: nu:noai:ts=4:sw=4

//****************************************************************
//					C Object (obj) Header				
//****************************************************************

/*
 * Program
 *				C Object (obj) Header
 * Purpose
 *				These subroutines provide a general purpose set of
 *				routines to create a retain counted C object. It
 *              may also be the initial object for single in-
 *              heritance since C supports this.
 * Remarks
 *	1.			Each Dealloc must call its super's Dealloc for the
 *              Dealloc chain to operate properly. There is no way
 *              currently to calculate the Dealloc. So, it must be
 *              hard coded. The Top-most Dealloc should be set in
 *              this object as the Dealloc method which starts the
 *              Dealloc chain.
 *  2.          The class objects are defined as const. So, you can
 *              not have class variables without removing the const.
 *  3.          The class objects are not set up to inherit from
 *              their base classes. They only inherit from OBJ
 *              currently. There is only one slot for a Vtbl ptr
 *              currently.
 * History
 *	02/11/2015	Created from scratch.
 *  09/14/2015  Changed obj_Dealloc to not free objects not alloc'd
 *              by the obj_Alloc.
 * References
 *		"Data Structures using C", Aaron M. Tenenbaum et al,
 *			Prentice-Hall, 1990
 *		"Programs and Data Structures in C", Leendert Ammeraal,
 *			John Wiley & Sons, 1987
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



#include        <cmn_defs.h>

#ifndef         OBJ_H
#define         OBJ_H	1


#ifdef	__cplusplus
extern	"C" {
#endif
    
#ifndef ERESULT_DEFN
    typedef int32_t ERESULT;
#define ERESULT_DEFN 1
#endif
    
    
/****************************************************************
* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
****************************************************************/

#ifndef         OBJ_IDENTS_ENUM
#define         OBJ_IDENTS_ENUM	1
    typedef enum obj_idents_e {
        OBJ_IDENT_UNKNOWN=0,
        OBJ_IDENT_BASE,
        OBJ_IDENT_APP32_CLASS,
        OBJ_IDENT_ARRAYEXPAND,          // Expandable Array
        OBJ_IDENT_ARRAYEXPAND_CLASS,
        OBJ_IDENT_ASCII,                // ASCII Character Set
        OBJ_IDENT_ASCII_CLASS,
        OBJ_IDENT_ASTR,                 // ASCII String
        OBJ_IDENT_ASTR_CLASS,
        OBJ_IDENT_ASTRARRAY,            // an Array of ASCII Strings
        OBJ_IDENT_ASTRARRAY_CLASS,
        OBJ_IDENT_ASTRC,                // ASCII String Constant
        OBJ_IDENT_ASTRC_CLASS,
        OBJ_IDENT_AUDIOCW,              // Morse Code Audio
        OBJ_IDENT_AUDIOCW_CLASS,
        OBJ_IDENT_AUDIOWAV,             // WAV Audio
        OBJ_IDENT_AUDIOWAV_CLASS,
        OBJ_IDENT_BITMATRIX,
        OBJ_IDENT_BITMATRIX_CLASS,
        OBJ_IDENT_BITSET,
        OBJ_IDENT_BITSET_CLASS,
        OBJ_IDENT_BLK16,                // Data Block with an optional fixed sized area
        OBJ_IDENT_BLK16_CLASS,
        OBJ_IDENT_BLKDRCDS16,           // Block of variable sized records with
        //                              // an optional fixed sized area
        OBJ_IDENT_BLKDRCDS16_CLASS,
        OBJ_IDENT_BLKIDX16,             // Data Block of variable sized data and
        //                              // an optional fixed sized area
        OBJ_IDENT_BLKIDX16_CLASS,
        OBJ_IDENT_BLOCK,                // Data Block with Fixed Sized Header and
        //                              // Fixed Sized Data Area
        OBJ_IDENT_BLOCK_CLASS,
        OBJ_IDENT_BLOCKS,               // A list of Data Blocks
        OBJ_IDENT_BLOCKS_CLASS,
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
        OBJ_IDENT_CON,                  // Console Object
        OBJ_IDENT_CON_CLASS,
        OBJ_IDENT_CON_FIO,              // Console File I/O Object
        OBJ_IDENT_CON_FIO_CLASS,
        OBJ_IDENT_CONSUMER,
        OBJ_IDENT_CONSUMER_CLASS,
        OBJ_IDENT_CONXMT,
        OBJ_IDENT_CONXMT_CLASS,
        OBJ_IDENT_CSV,
        OBJ_IDENT_CSV_CLASS,
        OBJ_IDENT_DATETIME,             // Date & Time
        OBJ_IDENT_DATETIME_CLASS,
        OBJ_IDENT_DBCSV,                // Comma-Delimited Database
        OBJ_IDENT_DBCSV_CLASS,
        OBJ_IDENT_DBF,                  // DBase III/IV Field
        OBJ_IDENT_DBF_CLASS,
        OBJ_IDENT_DBFIELD,
        OBJ_IDENT_DBFIELD_CLASS,
        OBJ_IDENT_DEC,                  // Decimal (Base 10)
        OBJ_IDENT_DEC_CLASS,
        OBJ_IDENT_DEVBASE,              // Device Driver Base/Lower Object
        OBJ_IDENT_DEVBASE_CLASS,
        OBJ_IDENT_DEVICE,               // Device Virtual Object
        OBJ_IDENT_DEVICE_CLASS,
        OBJ_IDENT_DEVMGR,               // Device Manager
        OBJ_IDENT_DEVMGR_CLASS,
        OBJ_IDENT_DIR,
        OBJ_IDENT_DIR_CLASS,
        OBJ_IDENT_DIRENTRY,
        OBJ_IDENT_DIRENTRY_CLASS,
        OBJ_IDENT_EBCDIC,               // EBCDIC Character
        OBJ_IDENT_EBCDIC_CLASS,
        OBJ_IDENT_ENDIAN,               // Little/Big Endian Manipulation
        OBJ_IDENT_ENDIAN_CLASS,
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
        OBJ_IDENT_GREG,                 // Gregorian Date
        OBJ_IDENT_GREG_CLASS,
        OBJ_IDENT_HASH32,
        OBJ_IDENT_HASH32_CLASS,
        OBJ_IDENT_HEX,                  // Hex Input/Output
        OBJ_IDENT_HEX_CLASS,
        OBJ_IDENT_HISTBASE,             // ???
        OBJ_IDENT_HISTBASE_CLASS,
        OBJ_IDENT_IOMGR,                // I/O Manager
        OBJ_IDENT_IOMGR_CLASS,
        OBJ_IDENT_IORCD,                // Record I/O
        OBJ_IDENT_IORCD_CLASS,
        OBJ_IDENT_JSON,                 // JSON Parser
        OBJ_IDENT_JSON_CLASS,
        OBJ_IDENT_LEX,                  // Generic Lexical Scanner
        OBJ_IDENT_LEX_CLASS,
        OBJ_IDENT_LISTDL,               // Generic Doubly-linked List
        OBJ_IDENT_LISTDL_CLASS,
        OBJ_IDENT_LRU,                  // Least Recently Used Caching
        OBJ_IDENT_LRU_CLASS,
        OBJ_IDENT_MEMMSC,               // Memory Debug for MS C
        OBJ_IDENT_MEMMSC_CLASS,
        OBJ_IDENT_MEMOSX,               // Memory Debug for OSX
        OBJ_IDENT_MEMOSX_CLASS,
        OBJ_IDENT_MISC,                 // Miscellaneous Functions
        OBJ_IDENT_MISC_CLASS,
        OBJ_IDENT_NAME,
        OBJ_IDENT_NAME_CLASS,
        OBJ_IDENT_NODE,
        OBJ_IDENT_NODE_CLASS,
        OBJ_IDENT_NODEARC,              // An Arc in a Node Graph
        OBJ_IDENT_NODEARC_CLASS,
        OBJ_IDENT_NODEARRAY,            // An Array of Nodes
        OBJ_IDENT_NODEARRAY_CLASS,
        OBJ_IDENT_NODEATREE,             // A Tree of Nodes using an Array internally
        OBJ_IDENT_NODEATREE_CLASS,
        OBJ_IDENT_NODEENTRY,            // A Node to be used in other containers
        OBJ_IDENT_NODEENTRY_CLASS,
        OBJ_IDENT_NODEGRAPH,            // Graph of Nodes
        OBJ_IDENT_NODEGRAPH_CLASS,
        OBJ_IDENT_NODEHASH,             // A Hash Table of Nodes
        OBJ_IDENT_NODEHASH_CLASS,
        OBJ_IDENT_NODELIST,             // A List of Nodes
        OBJ_IDENT_NODELIST_CLASS,
        OBJ_IDENT_NODEMATRIX,
        OBJ_IDENT_NODEMATRIX_CLASS,
        OBJ_IDENT_NODESCAN,             // Node Tree Scanner
        OBJ_IDENT_NODESCAN_CLASS,
        OBJ_IDENT_NODETREE,             // A Tree of Nodes
        OBJ_IDENT_NODETREE_CLASS,
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
        OBJ_IDENT_OBJHASH,              // Hash Dictionary of Objects
        OBJ_IDENT_OBJHASH_CLASS,
        OBJ_IDENT_OBJLIST,              // List of Objects
        OBJ_IDENT_OBJLIST_CLASS,
        OBJ_IDENT_OBJMATRIX,            // 2 dimensional array of Objects
        OBJ_IDENT_OBJMATRIX_CLASS,
        OBJ_IDENT_OSC,
        OBJ_IDENT_OSC_CLASS,
        OBJ_IDENT_PACKET,
        OBJ_IDENT_PACKET_CLASS,
        OBJ_IDENT_PASSTR,
        OBJ_IDENT_PASSTR_CLASS,
        OBJ_IDENT_PATH,                 // File Path
        OBJ_IDENT_PATH_CLASS,
        OBJ_IDENT_PBXPROJ,              // Xcode pbxproj file parser
        OBJ_IDENT_PBXPROJ_CLASS,
        OBJ_IDENT_PLIST,                // PLIST Parser
        OBJ_IDENT_PLIST_CLASS,
        OBJ_IDENT_PRODCONS,             // Producer/Consumer Pattern
        OBJ_IDENT_PRODCONS_CLASS,
        OBJ_IDENT_PROTOCOL,             // Protocol LAYER which uses RECEIVE and TRANSMIT
        OBJ_IDENT_PROTOCOL_CLASS,
        OBJ_IDENT_PRT,
        OBJ_IDENT_PRT_CLASS,
        OBJ_IDENT_PSXCOND,              // Posix Condition
        OBJ_IDENT_PSXCOND_CLASS,
        OBJ_IDENT_PSXMUTEX,             // Posix Mutex
        OBJ_IDENT_PSXMUTEX_CLASS,
        OBJ_IDENT_PSXSEM,               // Posix Semaphore
        OBJ_IDENT_PSXSEM_CLASS,
        OBJ_IDENT_PSXTHREAD,            // Posix Thread
        OBJ_IDENT_PSXTHREAD_CLASS,
        OBJ_IDENT_PTRARRAY,             // Generic Array of Pointers
        OBJ_IDENT_PTRARRAY_CLASS,
        OBJ_IDENT_PTRTBL,
        OBJ_IDENT_PTRTBL_CLASS,
        OBJ_IDENT_PWR2ARRAY,            // An Array of elements that have a size
        //                              // which is a power of 2
        OBJ_IDENT_PWR2ARRAY_CLASS,
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
        OBJ_IDENT_SIDX,                 // Simple Integer Index
        OBJ_IDENT_SIDX_CLASS,
        OBJ_IDENT_SRC,
        OBJ_IDENT_SRC_CLASS,
        OBJ_IDENT_SRCFILE,
        OBJ_IDENT_SRCFILE_CLASS,
        OBJ_IDENT_SRCFILES,
        OBJ_IDENT_SRCFILES_CLASS,
        OBJ_IDENT_SRCLOC,               // Source Location (File, Line, Col)
        OBJ_IDENT_SRCLOC_CLASS,
        OBJ_IDENT_SZSTRARRAY,           // An Array of szStr's
        OBJ_IDENT_SZSTRARRAY_CLASS,
        OBJ_IDENT_SZHASH,               // Store void data with a char string key
        OBJ_IDENT_SZHASH_CLASS,
        OBJ_IDENT_SZSTR,
        OBJ_IDENT_SZSTR_CLASS,
        OBJ_IDENT_SZTBL,                // Static String Table
        OBJ_IDENT_SZTBL_CLASS,
        OBJ_IDENT_TABLE,
        OBJ_IDENT_TABLE_CLASS,
        OBJ_IDENT_TERNARY,              // Ternary Tree
        OBJ_IDENT_TERNARY_CLASS,
        OBJ_IDENT_THREAD,               // Separate Threads with own stack
        OBJ_IDENT_THREAD_CLASS,
        OBJ_IDENT_TIMER,
        OBJ_IDENT_TIMER_CLASS,
        OBJ_IDENT_TOKEN,                // Lexical Token
        OBJ_IDENT_TOKEN_CLASS,
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
        OBJ_IDENT_U8ARRAY,
        OBJ_IDENT_U8ARRAY_CLASS,
        OBJ_IDENT_UINT128,
        OBJ_IDENT_UINT128_CLASS,
        OBJ_IDENT_UTF8,
        OBJ_IDENT_UTF8_CLASS,
        OBJ_IDENT_WAV,                  // WAV File
        OBJ_IDENT_WAV_CLASS,
        OBJ_IDENT_WSTR,
        OBJ_IDENT_WSTR_CLASS,
        OBJ_IDENT_WSTRARRAY,            // an Array of Wide Strings
        OBJ_IDENT_WSTRARRAY_CLASS,
        OBJ_IDENT_WSTRC,
        OBJ_IDENT_WSTRC_CLASS,
        OBJ_IDENT_XML,
        OBJ_IDENT_XML_CLASS,
        OBJ_IDENT_OTHER_LIBS=8192,
        OBJ_IDENT_CAN_ENTRIES=OBJ_IDENT_OTHER_LIBS,                 // 128 Objects
        OBJ_IDENT_COMPILER_ENTRIES=OBJ_IDENT_CAN_ENTRIES+256,       // 128 Objects
        OBJ_IDENT_DISK_ENTRIES=OBJ_IDENT_COMPILER_ENTRIES+256,      //  64 Objects
        OBJ_IDENT_J1939_ENTRIES=OBJ_IDENT_DISK_ENTRIES+128,         //  64 Objects
        OBJ_IDENT_LL1_ENTRIES=OBJ_IDENT_J1939_ENTRIES+128,          //  64 Objects
        OBJ_IDENT_PARSERS_ENTRIES=OBJ_IDENT_LL1_ENTRIES+128,        //  64 Objects
        OBJ_IDENT_PIC32_ENTRIES=OBJ_IDENT_PARSERS_ENTRIES+128,      //  64 Objects
        OBJ_IDENT_PREXX_ENTRIES=OBJ_IDENT_PIC32_ENTRIES+128,        // 128 Objects
        OBJ_IDENT_EMU_ENTRIES=OBJ_IDENT_PREXX_ENTRIES+256,          //  32 Objects
        OBJ_IDENT_USER_ENTRIES=16384
   } OBJ_IDENTS;
#endif


    typedef void *  OBJ_PTR;
    typedef void *  OBJ_ID;
#define             OBJ_NIL ((OBJ_ID)0)
    typedef struct obj_iunknown_s  OBJ_IUNKNOWN;
    typedef struct obj_info_s  OBJ_INFO;
    typedef void (*DEALLOC_METHOD)(void *);
    
    typedef struct obj_data_s OBJ_DATA;     /* One Interface */

    typedef ERESULT     (*P_OBJ_ASSIGN)(OBJ_ID,OBJ_ID);
    typedef ERESULT     (*P_OBJ_COMPARE)(OBJ_ID,OBJ_ID);
    typedef OBJ_ID      (*P_OBJ_COPY)(OBJ_ID);
    typedef bool        (*P_OBJ_DISABLE)(OBJ_ID);
    typedef bool        (*P_OBJ_ENABLE)(OBJ_ID);
    typedef uint32_t    (*P_OBJ_HASH)(OBJ_ID);
    typedef OBJ_ID      (*P_OBJ_PTR)(OBJ_ID);
    typedef OBJ_ID      (*P_OBJ_TOSTRING)(OBJ_ID,int);


    
#pragma pack(push, 1)
    struct obj_data_s {
        const
        OBJ_IUNKNOWN    *pVtbl;
        uint16_t        cbSize;         /* Total Control Block Size */
        uint16_t		cbIdent;        /* enum obj_ids_e values */
        uint16_t        cbFlags;        /* Control Flags */
#define OBJ_FLAG_ALLOC      0               /* Object was allocated in obj_Alloc(). */
#define OBJ_FLAG_INIT       1               /* Object is initialized. */
#define OBJ_FLAG_ENABLED    2               /* Object is enabled. */
#define OBJ_FLAG_TRACE      3               /* Object tracing */
#define OBJ_FLAG_USER1      4               /* First User Useable flag */
#define OBJ_FLAG_USER2      5
#define OBJ_FLAG_USER3      6
#define OBJ_FLAG_USER4      7
#define OBJ_FLAG_USER5      8
#define OBJ_FLAG_USER6      9
#define OBJ_FLAG_USER7      10
#define OBJ_FLAG_USER8      11
#define OBJ_FLAG_USER9      12
#define OBJ_FLAG_USER10     13
#define OBJ_FLAG_USER11     14
#define OBJ_FLAG_USER12     15              /* Last User Useable flag */

        uint16_t		cbRetainCount;
        union {
            uint32_t        cbMisc;
            struct {
                uint16_t        cbMisc1;
                uint16_t        cbMisc2;
            };
        };
    };
#pragma pack(pop)

    extern
    const
    OBJ_DATA        obj_ClassObj;
    

#pragma pack(push, 1)
    struct obj_info_s {
        const
        char            *pClassName;
        const
        char            *pClassDesc;        // Class Description
        OBJ_DATA        *pClassObject;
        OBJ_DATA        *pClassSuperObject;
        OBJ_IUNKNOWN    *pDefaultVtbls;     // Default Object VTBL
    };
#pragma pack(pop)
    
    
    
//#pragma pack(push, 1)
    struct obj_iunknown_s {
        const
        OBJ_INFO    *pInfo;                 // (Optional for Now)
        bool        (*pIsKindOf)(uint16_t);
        OBJ_ID      (*pRetain)(OBJ_ID);
        OBJ_ID      (*pRelease)(OBJ_ID);
        void        (*pDealloc)(OBJ_ID);
        OBJ_ID      (*pClassObject)();
        uint16_t    (*pWhoAmI)();
        // Everything before this is required and does not need to be
        // tested to see if it exists.  Everything after this must be
        // tested to see if it exists, because it may not be implemented.
        bool        (*pEnable)(OBJ_ID);
        bool        (*pDisable)(OBJ_ID);
        OBJ_ID      (*pToDebugString)(OBJ_ID,int);
        ERESULT     (*pAssign)(OBJ_ID,OBJ_ID);  // P_OBJ_ASSIGN
        // Assigns 1st object to 2nd object.
        ERESULT     (*pCompare)(OBJ_ID,OBJ_ID); // P_OBJ_COMPARE
        // Compares 1st object to 2nd object.
        // Returns:
        //          ERESULT_SUCCESS_LESS_THAN        1st <  2nd
        //          ERESULT_SUCCESS_EQUAL            1st == 2nd
        //          ERESULT_SUCCESS_GREATER_THAN     1st >  2nd
        OBJ_ID      (*pCopy)(OBJ_ID);           // P_OBJ_PTR
        // Creates a new copy of the object. If the object is
        // immmutable (ie can not be changed) then it just returns
        // a retained self.
        uint32_t    (*pHash)(OBJ_ID);           // P_OBJ_HASH
        // Creates hash of this object.
    };
//#pragma pack(pop)
    
    
#define OBJ_INIT_SHARED(cbp,cbSize)\
    if (!(obj_getFlags(cbp) & OBJ_FLAG_INIT)) {\
        memset(cbp, 0, cbSize);\
        obj_setVtbl(cbp,obj_StaticVtblShared());\
        obj_setSize(cbp, cbSize);\
        obj_setIdent(cbp, OBJ_IDENT_OBJ);\
        obj_setRetainCount(cbp, -1);\
        obj_setFlags(cbp, OBJ_FLAG_INIT);\
    }



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/

    
    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------
    
    // Note:
    //  --  In the following routines, we use OBJ_ID instead of
    //      OBJ_DATA *this to simplify having to cast on every call.
    //      OBJ_ID is defined as "void *" which does not require any
    //      casting.
    
    /* Alloc() allocates the memory for the object, zeroes it and
     * sets up initial parameters for it.
     */
    OBJ_ID          obj_Alloc(
        uint16_t        size
    );
    
   
    OBJ_ID          obj_Class(
    );
    
    
    OBJ_ID          obj_ClassSuper(
        OBJ_ID          objId
    );
    

#ifdef XYZZY
    bool            obj_IsKindOf(
        uint16_t        classID
    );
#endif
    
    
    bool            obj_ClassEnable(
        OBJ_ID          objId
    );
    
    
    bool            obj_ClassDisable(
        OBJ_ID          objId
    );
    

    const
    OBJ_IUNKNOWN *  obj_StaticVtbl(
    );


    const
    OBJ_IUNKNOWN *  obj_StaticVtblShared(
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------
    
    bool            obj_IsEnabled(
        OBJ_ID          objId
    );

    
    uint16_t        obj_getFlags(
        OBJ_ID          objId
    );

    bool			obj_setFlags(
        OBJ_ID          objId,
        uint16_t        value
    );
    
    
    uint16_t        obj_getIdent(
        OBJ_ID          objId
    );
    
    bool			obj_setIdent(
        OBJ_ID          objId,
        uint16_t        value
    );

   
    const
    OBJ_INFO *      obj_getInfo(
        OBJ_ID          objId
    );
    
    
    uint32_t        obj_getMisc(
        OBJ_ID          objId
    );
    
    bool			obj_setMisc(
        OBJ_ID          objId,
        uint32_t        value
    );
    
    
    uint16_t        obj_getMisc1(
        OBJ_ID          objId
    );
    
    bool			obj_setMisc1(
        OBJ_ID          objId,
        uint16_t        value
    );
    
    
    uint16_t        obj_getMisc2(
        OBJ_ID          objId
    );
    
    bool			obj_setMisc2(
        OBJ_ID          objId,
        uint16_t        value
    );
    
    
    uint16_t        obj_getRetainCount(
        OBJ_ID          objId
    );
    
    bool			obj_setRetainCount(
        OBJ_ID          objId,
        uint16_t        value
    );
    
    
    uint16_t        obj_getSize(
        OBJ_ID          objId
    );
    
    bool			obj_setSize(
        OBJ_ID          objId,
        uint16_t        value
    );
    
    
    OBJ_ID          obj_getSuper(
        OBJ_ID          objId
    );
    
    
    uint16_t        obj_getType(
        OBJ_ID          objId
    );
    
    
    OBJ_IUNKNOWN *	obj_getVtbl(
        OBJ_ID          objId
    );
    
    
    bool			obj_setVtbl(
        OBJ_ID          objId,
        const
        OBJ_IUNKNOWN    *pValue
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------
    
    void            obj_Dealloc(
        OBJ_ID          objId
    );
    
    
    /* OBJ_Disable() frees the allocated arrays.
     * Returns:
     *		TRUE = Successful completion otherwise FALSE
     */
    bool            obj_Disable(
        OBJ_ID          objId
    );
    
    
    /* OBJ_Enable() is used to activate an object if needed.
     * This method simply sets the 'enabled' flag.
     * Returns:
     *		TRUE = Successful Completion, otherwise FALSE
     */
    bool            obj_Enable(
        OBJ_ID          objId
    );
    

    bool            obj_IsA(
        OBJ_ID          objId,
        uint16_t        type
    );
    
    
    bool            obj_IsFlag(
        OBJ_ID          objId,
        uint16_t        flag        // Index (not a mask)
    //                              //  0..3 are for OBJ use
    //                              //  4..15 are for user's use
    //                              //  WARNING: Be careful that user flag use
    //                              //          does not overlap when inheriting
    //                              //          from another object
    );
    
    
    bool            obj_Flag(
        OBJ_ID          objId,
        uint16_t        flag        // Index (not a mask)
    //                              //  0..3 are for OBJ use
    //                              //  4..15 are for user's use
    //                              //  WARNING: Be careful that user flag use
    //                              //          does not overlap when inheriting
    //                              //          from another object
    );
    
    
    bool            obj_FlagOff(
        OBJ_ID          objId,
        uint16_t        flag        // Index (not a mask)
    //                              //  0..3 are for OBJ use
    //                              //  4..15 are for user's use
    //                              //  WARNING: Be careful that user flag use
    //                              //          does not overlap when inheriting
    //                              //          from another object
    );
    
    
    bool            obj_FlagOn(
        OBJ_ID          objId,
        uint16_t        flag        // Index (not a mask)
    //                              //  0..3 are for OBJ use
    //                              //  4..15 are for user's use
    //                              //  WARNING: Be careful that user flag use
    //                              //          does not overlap when inheriting
    //                              //          from another object
    );
    
    
    bool            obj_FlagSet(
        OBJ_ID          objId,
        uint16_t        flag,       // Index (not a mask)
    //                              //  0..3 are for OBJ use
    //                              //  4..15 are for user's use
    //                              //  WARNING: Be careful that user flag use
    //                              //          does not overlap when inheriting
    //                              //          from another object
        bool            fValue
    );
    
    
    bool            obj_IsKindOf(
        OBJ_ID          objId,
        uint16_t        type
    );
    
    
    /* obj_Init() initializes this object. If we find upon
     * entry that if the area passed has an identifier of
     * OBJ_ID_OBJ and the size is the same, then we will
     * assume that the area was gotten with obj_Alloc();
     */
    OBJ_ID          obj_Init(
        OBJ_ID          objId,
        uint16_t        size,
        uint16_t        objectIdentifier
    );


    OBJ_ID          obj_Release(
        OBJ_ID          objId
    );

    OBJ_ID          obj_ReleaseNull(
        OBJ_ID          objId
    );
    
    OBJ_ID          obj_ReleaseStandard(
        OBJ_ID          objId
    );
    
    
    OBJ_ID          obj_Retain(
        OBJ_ID          objId
    );
    
    OBJ_ID          obj_RetainNull(
        OBJ_ID          objId
    );
    
    OBJ_ID          obj_RetainStandard(
        OBJ_ID          objId
    );
    
    
    OBJ_ID          obj_ToDebugString(
        OBJ_ID          objId,
        int             indent
    );

    
    bool            obj_Trace(
        OBJ_ID          objId
    );
    
    
    bool            obj_TraceSet(
        OBJ_ID          objId,
        bool            fValue
    );
    
    
    
    
#ifdef	__cplusplus
};
#endif




#endif
