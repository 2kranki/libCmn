// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 12/19/2019 23:09:03
 */





// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      TINYTEST_ASSERT(condition)
//      TINYTEST_ASSERT_MSG(condition,msg)
//      TINYTEST_EQUAL(expected, actual)
//      TINYTEST_EQUAL_MSG(expected, actual, msg)
//      TINYTEST_FALSE_MSG(condition,msg)
//      TINYTEST_FALSE(condition)
//      TINYTEST_TRUE_MSG(pointer,msg)
//      TINYTEST_TRUE(condition)





#include    <tinytest.h>
#include    <cmn_defs.h>
#include    <trace.h>
#include    <W32Str.h>
#include    <TRegex32_internal.h>


struct {
    bool    fOk;
    char    *pPattern;
    char    *pData;
    int     index;
    int     length;
} test_vector[] =
{
  { true,  "\\d",                       "5",                         0,  1},    //   0
  { true,  "\\w+",                      "hej",                       0,  3},    //   1
  { true,  "\\s",                       "\t \n",                     0,  1},    //   2
  { false, "\\S",                       "\t \n",                     0,  0},    //   3
  { true,  "[\\s]",                     "\t \n",                     0,  1},    //   4
  { false, "[\\S]",                     "\t \n",                     0,  0},    //   5
  { false, "\\D",                       "5",                         0,  0},    //   6
  { false, "\\W+",                      "hej",                       0,  0},    //   7
  { true,  "[0-9]+",                    "12345",                     0,  5},    //   8
  { true,  "\\D",                       "hej",                       0,  1},    //   9
  { false, "\\d",                       "hej",                       0,  0},    //  10
  { true,  "[^\\w]",                    "\\",                        0,  1},    //  11
  { true,  "[\\W]",                     "\\",                        0,  1},    //  12
  { false, "[\\w]",                     "\\",                        0,  0},    //  13
  { true,  "[^\\d]",                    "d",                         0,  1},    //  14
  { false, "[\\d]",                     "d",                         0,  0},    //  15
  { false, "[^\\D]",                    "d",                         0,  0},    //  16
  { true,  "[\\D]",                     "d",                         0,  1},    //  17
  { true,  "^.*\\\\.*$",                "c:\\Tools",                 0,  8},    //  18
  { true,  "^[\\+-]*[\\d]+$",           "+27",                       0,  3},    //  19
  { true,  "[abc]",                     "1c2",                       1,  1},    //  20
  { false, "[abc]",                     "1C2",                       0,  0},    //  21
  { true,  "[1-5]+",                    "0123456789",                1,  5},    //  22
  { true,  "[.2]",                      "1C2",                       2,  1},    //  23
  { true,  "a*$",                       "Xaa",                       1,  2},    //  24
  { true,  "a*$",                       "Xaa",                       1,  2},    //  25
  { true,  "[a-h]+",                    "abcdefghxxx",               0,  8},    //  26
  { false, "[a-h]+",                    "ABCDEFGH",                  0,  0},    //  27
  { true,  "[A-H]+",                    "ABCDEFGH",                  0,  8},    //  28
  { false, "[A-H]+",                    "abcdefgh",                  0,  0},    //  29
  { true,  "[^\\s]+",                   "abc def",                   0,  3},    //  30
  { true,  "[^fc]+",                    "abc def",                   0,  2},    //  31
  { true,  "[^d\\sf]+",                 "abc def",                   0,  3},    //  32
  { true,  "\n",                        "abc\ndef",                  3,  1},    //  33
  { true,  "b.\\s*\n",                  "aa\r\nbb\r\ncc\r\n\r\n",    4,  4},    //  34
  { true,  ".*c",                       "abcabc",                    0,  6},    //  35
  { true,  ".+c",                       "abcabc",                    0,  6},    //  36
  { true,  "[b-z].*",                   "ab",                        1,  1},    //  37
  { true,  "b[k-z]*",                   "ab",                        1,  1},    //  38
  { false, "[0-9]",                     "  - ",                      0,  0},    //  39
  { true,  "[^0-9]",                    "  - ",                      0,  1},    //  40
  { true,  "0|",                        "0|",                        0,  2},    //  41
  { false, "\\d\\d:\\d\\d:\\d\\d",      "0s:00:00",                  0,  0},    //  42
  { false, "\\d\\d:\\d\\d:\\d\\d",      "000:00",                    0,  0},    //  43
  { false, "\\d\\d:\\d\\d:\\d\\d",      "00:0000",                   0,  0},    //  44
  { false, "\\d\\d:\\d\\d:\\d\\d",      "100:0:00",                  0,  0},    //  45
  { false, "\\d\\d:\\d\\d:\\d\\d",      "00:100:00",                 0,  0},    //  46
  { false, "\\d\\d:\\d\\d:\\d\\d",      "0:00:100",                  0,  0},    //  47
  { true,  "\\d\\d?:\\d\\d?:\\d\\d?",   "0:0:0",                     0,  5},    //  48
  { true,  "\\d\\d?:\\d\\d?:\\d\\d?",   "0:00:0",                    0,  6},    //  49
  { true,  "\\d\\d?:\\d\\d?:\\d\\d?",   "0:0:00",                    0,  6},    //  50
  { true,  "\\d\\d?:\\d\\d?:\\d\\d?",   "00:0:0",                    0,  6},    //  51
  { true,  "\\d\\d?:\\d\\d?:\\d\\d?",   "00:00:0",                   0,  7},    //  52
  { true,  "\\d\\d?:\\d\\d?:\\d\\d?",   "00:0:00",                   0,  7},    //  53
  { true,  "\\d\\d?:\\d\\d?:\\d\\d?",   "0:00:00",                   0,  7},    //  54
  { true,  "\\d\\d?:\\d\\d?:\\d\\d?",   "00:00:00",                  0,  8},    //  55
  { true,  "[Hh]ello [Ww]orld\\s*[!]?", "Hello world !",             0,  13},    //  56
  { true,  "[Hh]ello [Ww]orld\\s*[!]?", "hello world !",             0,  13},    //  57
  { true,  "[Hh]ello [Ww]orld\\s*[!]?", "Hello World !",             0,  13},    //  58
  { true,  "[Hh]ello [Ww]orld\\s*[!]?", "Hello world!   ",           0,  12},    //  59
  { true,  "[Hh]ello [Ww]orld\\s*[!]?", "Hello world  !",            0,  14},    //  60
  { true,  "[Hh]ello [Ww]orld\\s*[!]?", "hello World    !",          0,  16},    //  61
  /* Failing test case reported in
      https://github.com/kokke/tiny-regex-c/issues/12
   */
  { false, "\\d\\d?:\\d\\d?:\\d\\d?",   "a:0",                       0,  0},    //  62
/*
  { OK,  "[^\\w][^-1-4]",     ")T"          },
  { OK,  "[^\\w][^-1-4]",     ")^"          },
  { OK,  "[^\\w][^-1-4]",     "*)"          },
  { OK,  "[^\\w][^-1-4]",     "!."          },
  { OK,  "[^\\w][^-1-4]",     " x"          },
  { OK,  "[^\\w][^-1-4]",     "$b"          },
*/
  { true,  ".?bar",                      "real_bar",                 4,  4},    //  63
  { false, ".?bar",                      "real_foo",                 0,  0},    //  64
  { false , "a"                        , "",                         0,  0},    //  65
  { true  , "a*"                       , "",                         0,  0},    //  66
  { false , "[^s][^b]"                 , "a",                        0,  0},    //  67
  { false , "[^\\d]+\\s"               , "e",                        0,  0},    //  68
  { true  , "\\d"                      , "5",                        0,  1},    //  69
  { false , "\\d+"                     , "y",                        0,  0},    //  70
  { true  , "\\w+"                     , "hej",                      0,  3},    //  71
  { true  , "\\s"                      , "\t \n",                    0,  1},    //  72
  { false , "\\S"                      , "\t \n",                    0,  0},    //  73
  { true  , "[\\s]"                    , "\t \n",                    0,  1},    //  74
  { false , "[\\S]"                    , "\t \n",                    0,  0},    //  75
  { false , "\\D"                      , "5",                        0,  0},    //  76
  { false , "\\W+"                     , "hej",                      0,  0},    //  77
  { true  , "[0-9]+"                   , "12345",                    0,  5},    //  78
    { true  , "\\D"                    , "hej",                      0,  1},    //  79
    { false , "\\d"                    , "hej",                      0,  0},    //  80
    { true  , "[^\\w]"                 , "\\",                       0,  1},    //  81
    { true  , "[\\W]"                  , "\\",                       0,  1},    //  82
    { false , "[\\w]"                  , "\\",                       0,  0},    //  83
    { true  , "[^\\d]"                 , "d",                        0,  1},    //  84
    { false , "[\\d]"                  , "d",                        0,  0},    //  85
    { false , "[^\\D]"                 , "d",                        0,  0},    //  86
    { true  , "[\\D]"                  , "d",                        0,  1},    //  87
    { true  , "a+a"                    , "aaa",                      0,  3},    //  88
    { true  , "^.*\\\\.*$"             , "c:\\Tools",                0,  8},    //  89
    { true  , "^[\\+-]*[\\d]+$"        , "+27",                      0,  3},    //  90
    { true  , "[abc]"                  , "1c2",                      1,  1},    //  91
    { false , "[abc]"                  , "1C2",                      0,  0},    //  92
    { true  , "[1-5]+"                 , "0123456789",               1,  5},    //  93
    { true  , "[.2]"                   , "1C2",                      2,  1},    //  94
    { true  , "a*$"                    , "Xaa",                      1,  2},    //  95
    { true  , "[a-h]+"                 , "abcdefghxxx",              0,  8},    //  96
    { false , "[a-h]+"                 , "ABCDEFGH",                 0,  0},    //  97
    { true  , "[A-H]+"                 , "ABCDEFGH",                 0,  8},    //  98
    { false , "[A-H]+"                 , "abcdefgh",                 0,  0},    //  99
    { true  , "[^\\s]+"                , "abc def",                  0,  3},    // 100
    { true  , "[^fc]+"                 , "abc def",                  0,  2},    // 101
    { true  , "[^d\\sf]+"              , "abc def",                  0,  3},    // 102
    { true  , "\n"                     , "abc\ndef",                 3,  1},    // 103
    { true  , "b.\\s*\n"               , "aa\r\nbb\r\ncc\r\n\r\n",   4,  4},    // 104
    { true  , ".*c"                    , "abcabc",                   0,  6},    // 105
    { true  , ".+c"                    , "abcabc",                   0,  6},    // 106
    { true  , "[b-z].*"                , "ab",                       1,  1},    // 107
    { true  , "b[k-z]*"                , "ab",                       1,  1},    // 108
    { false , "[0-9]"                  , "  - ",                     0,  0},    // 109
    { true  , "[^0-9]"                 , "  - ",                     0,  1},    // 110
    { true  , "0|"                     , "0|",                       0,  2},    // 111
    { false , "\\d\\d:\\d\\d:\\d\\d"   , "0s:00:00",                 0,  0},    // 112
    { false , "\\d\\d:\\d\\d:\\d\\d"   , "000:00",                   0,  0},    // 113
    { false , "\\d\\d:\\d\\d:\\d\\d"   , "00:0000",                  0,  0},    // 114
    { false , "\\d\\d:\\d\\d:\\d\\d"   , "100:0:00",                 0,  0},    // 115
    { false , "\\d\\d:\\d\\d:\\d\\d"   , "00:100:00",                0,  0},    // 116
    { false , "\\d\\d:\\d\\d:\\d\\d"   , "0:00:100",                 0,  0},    // 117
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?", "0:0:0",                    0,  5},    // 118
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?", "0:00:0",                   0,  6},    // 119
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?", "0:0:00",                   0,  6},    // 120
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?", "00:0:0",                   0,  6},    // 121
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?", "00:00:0",                  0,  7},    // 122
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?", "00:0:00",                  0,  7},    // 123
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?", "0:00:00",                  0,  7},    // 124
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?", "00:00:00",                 0,  8},    // 125
    { true  , "[Hh]ello [Ww]orld\\s*[!]?", "Hello world !",          0,  13},    // 126
    { true  , "[Hh]ello [Ww]orld\\s*[!]?", "hello world !",          0,  13},    // 127
    { true  , "[Hh]ello [Ww]orld\\s*[!]?", "Hello World !",          0,  13},    // 128
    { true  , "[Hh]ello [Ww]orld\\s*[!]?", "Hello world!   ",        0,  12},    // 129
    { true  , "[Hh]ello [Ww]orld\\s*[!]?", "Hello world    !",       0,  16},    // 130
    { true  , "[Hh]ello [Ww]orld\\s*[!]?", "hello World      !",     0,  18},    // 131
    { false , "\\d\\d?:\\d\\d?:\\d\\d?", "a:0",                      0,  0},    // 132
    { true  , "[^\\w][^-1-4]"          , ")T",                       0,  2},    // 133
    { true  , "[^\\w][^-1-4]"          , ")^",                       0,  2},    // 134
    { true  , "[^\\w][^-1-4]"          , "*)",                       0,  2},    // 135
    { true  , "[^\\w][^-1-4]"          , "!.",                       0,  2},    // 136
    { true  , "[^\\w][^-1-4]"          , " x",                       0,  2},    // 137
    { true  , "[^\\w][^-1-4]"          , "$b",                       0,  2},    // 138
    { true  , ".?bar"                  , "real_bar",                 4,  4},    // 139
    { false , ".?bar"                  , "real_foo",                 0,  0},    // 140
    { false , "X?Y"                    , "Z",                        0,  0},    // 141
    { true  , "\\d+\\w?12"             , "959312",                   0,  6},    // 142
    { true  , "\\d+5"                  , "12345",                    0,  5},    // 143
    { false , "\\d++5"                 , "12345",                    0,  0},    // 144
    { false , "abcd"                   , "aBcD",                     0,  0},    // 145
    { true  , "(?i:abcd)"              , "aBcD",                     0,  4},    // 146 ??
    { false , "..."                    , "\n \n",                    0,  0},    // 147
    { true  , "(?s:...)"               , "\n \n",                    0,  3},    // 148 ??
    { false , "(?s:(?-s:.))"           , "\n",                       0,  0},    // 149
    { true  , "(?is:A.)"               , "a\n",                      0,  2},    // 150 ??
    { false , "(?is:(?-is:.g.))"       , "\nG\n",                    0,  0},    // 151
    { true  , "(?is:(?-is:.g.))"       , "\ng\n",                    0,  3},    // 152 ??
    { false , "abc\\bdef"              , "abcdef",                   0,  0},    // 153
    { true  , "abc\\Bdef"              , "abcdef",                   0,  6},    // 154
    { true  , "\\Bing\\b"              , "joining.",                 4,  3},    // 155
    { false , "\\Bing\\b"              , " ing ",                    0,  0},    // 156
    { false,  "\\Bing\\b"              , "ing",                      0,  0},    // 157
    { false , "\\Bing\\b"              , "bingg",                    0,  0},    // 158
    { true  , "abc\\Rdef"              , "abc\r\ndef",               0,  8},    // 159
    { true  , "abc\\Rdef"              , "abc\ndef",                 0,  7},    // 160
    { false , "abc\n\\Rdef"            , "abc\ndef",                 0,  0},    // 161
    { true  , "abc\r\\Rdef"            , "abc\r\ndef",               0,  8},    // 162
    { true  , "^(a+)a$"                , "aaa",                      0,  3},    // 163
    { true  , "^a(a*)a$"               , "aa",                       0,  2},    // 164
    { true  , "^(a)+a$"                , "aaa",                      0,  3},    // 165 ??
    { true  , "^(Hello){3}(World){1,2}$", "HelloHelloHelloWorld",    0,  20},   // 166 ??
    { true  , "^(is:[ab])+?bc$"        , "aAaAaaAAaaAAAAbAaaAbc",    0,  21},   // 167 ??
    { true  , "(?=.*ghi)abc"           , "abcdefghi",                0,  3},    // 168 ??
    { true  , "(?s=.*END)BEGIN"        , "BEGIN..content..\nEND",    0,  5},    // 169 ??
    { false , "(?s=.*END)BEGIN"        , "BEGIN..content..\n",       0,  0},    // 170
    { false , "(?s!.*END)BEGIN"        , "BEGIN..content..\nEND",    0,  0},    // 171
    { true  , "(?s!.*END)BEGIN"        , "BEGIN..content..\n",       0,  5},    // 172 ??
    { false , "(b*){1}+b"              , "bbbbb",                    0,  0},    // 173
};


const
size_t      ntests = sizeof(test_vector) / sizeof(*test_vector);






int             setUp(
    const
    char            *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int             tearDown(
    const
    char            *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    
    trace_SharedReset( ); 
    if (mem_Dump( ) ) {
        fprintf(
                stderr,
                "\x1b[1m"
                "\x1b[31m"
                "ERROR: "
                "\x1b[0m"
                "Leaked memory areas were found!\n"
        );
        exitCode = 4;
        return 0;
    }
    mem_Release( );
    
    return 1; 
}



void            printResult(
    TREGEX32_DATA   *this,
    int             lineNo,
    const
    char            *pPattern,
    const
    char            *pText,
    int             mCheck,
    int             mLength,
    int             m,
    int             length
)
{
    //ASTR_DATA       *pStr = OBJ_NIL;
    ASTR_DATA       *pPat = OBJ_NIL;
    ASTR_DATA       *pTxt = OBJ_NIL;
    ASTR_DATA       *pPat2 = OBJ_NIL;
    ASTR_DATA       *pTxt2 = OBJ_NIL;
    ASTR_DATA       *pDebug = OBJ_NIL;

    pPat = AStr_NewA(pPattern);
    if (pPat) {
        pPat2 = AStr_ToChrCon(pPat);
    }
    obj_Release(pPat);
    pPat = OBJ_NIL;
    if (OBJ_NIL == pPat2) {
        DEBUG_BREAK();
        return;
    }
    pTxt = AStr_NewA(pText);
    if (pTxt) {
        pTxt2 = AStr_ToChrCon(pTxt);
    }
    obj_Release(pTxt);
    pTxt = OBJ_NIL;
    if (OBJ_NIL == pTxt2) {
        DEBUG_BREAK();
        obj_Release(pPat2);
        pPat2 = OBJ_NIL;
        return;
    }
    
    fprintf(
            stderr,
            "\t%d - (%d,%d) = \"%s\".\"%s\"\n",
            lineNo,
            m,
            length,
            AStr_getData(pPat2),
            AStr_getData(pTxt2)
    );
    
    pDebug = TRegex32_ToDebugString(this, 0);
    if (pDebug) {
        fprintf(stderr, "%s\n", AStr_getData(pDebug));
        obj_Release(pDebug);
        pDebug = OBJ_NIL;
    }
    
    obj_Release(pPat2);
    pPat2 = OBJ_NIL;
    obj_Release(pTxt2);
    pTxt2 = OBJ_NIL;

}



bool            testPattern(
    const
    char            *pPattern,
    const
    char            *pText,
    bool            fShouldSucceed,
    int             mCheck,
    int             mLength
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    TREGEX32_DATA   *pObj = OBJ_NIL;
    bool            fRc = true;
    int             m;
    int             length = 0;
    bool            fDump = true;
    W32STR_DATA     *pPat32 = OBJ_NIL;
    W32STR_DATA     *pTxt32 = OBJ_NIL;

    pObj = TRegex32_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TREGEX32);
        TINYTEST_TRUE( (fRc) );
        
        pPat32 = W32Str_NewA(pPattern);
        TINYTEST_FALSE( (OBJ_NIL == pPat32) );
        pTxt32 = W32Str_NewA(pText);
        TINYTEST_FALSE( (OBJ_NIL == pTxt32) );
        m = TRegex32_Match(
                           pObj,
                           W32Str_getData(pPat32),
                           W32Str_getData(pTxt32),
                           &length
            );
        if (fDump) {
            printResult(pObj, 0, pPattern, pText, mCheck, mLength, m, length);
        }

        if (fShouldSucceed) {
            if (!((m == mCheck) && (length == mLength))) {
                if (!fDump) {
                    printResult(pObj, 0, pPattern, pText, mCheck, mLength, m, length);
                }
                fprintf(
                        stderr,
                        "Error: check:(%d,%d)  found: (%d,%d)\n",
                        mCheck, mLength, m, length
                );
                fRc = false;
            }
        }
        else {
            if (m || mLength) {
                if (!fDump) {
                    printResult(
                                pObj,
                                0,
                                pPattern,
                                pText,
                                mCheck,
                                mLength,
                                m,
                                length
                    );
                }
                fprintf(
                        stderr,
                        "Error: check:(%d,%d)  found: (%d,%d)\n",
                        mCheck, mLength, m, length
                );
                fRc = false;
            }
        }
        
        obj_Release(pPat32);
        pPat32 = OBJ_NIL;
        obj_Release(pTxt32);
        pTxt32 = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return fRc;
}






int             test_TRegex32_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TREGEX32_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TRegex32_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = TRegex32_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TREGEX32);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_TRegex32_Test01(
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    TREGEX32_DATA   *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fRc;
    char*           text;
    char*           pattern;
    int             fShouldSucceed;
    size_t          nfailed = 0;
    size_t          i;
    int             m;
    int             mCheck;
    bool            fDump = true;
    W32STR_DATA     *pPat32 = OBJ_NIL;
    W32STR_DATA     *pTxt32 = OBJ_NIL;
    int             mLength;
    int             length;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TRegex32_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = TRegex32_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TREGEX32);
        TINYTEST_TRUE( (fRc) );
        
        for (i = 0; i < ntests; ++i) {
            pattern = test_vector[i].pPattern;
            text = test_vector[i].pData;
            fShouldSucceed = test_vector[i].fOk;
            mCheck = test_vector[i].index;
            mLength = test_vector[i].length;
            length = 0;

            pPat32 = W32Str_NewA(pattern);
            TINYTEST_FALSE( (OBJ_NIL == pPat32) );
            pTxt32 = W32Str_NewA(text);
            TINYTEST_FALSE( (OBJ_NIL == pTxt32) );
            m = TRegex32_Match(
                               pObj,
                               W32Str_getData(pPat32),
                               W32Str_getData(pTxt32),
                               &length
                );
            if (fDump) {
                printResult(pObj, (int)i, pattern, text, mCheck, mLength, m, length);
            }

            if (fShouldSucceed) {
                if (!((m == mCheck) && (length == mLength))) {
                    if (!fDump) {
                        printResult(pObj, (int)i, pattern, text, mCheck, mLength, m, length);
                    }
                    fprintf(
                            stderr,
                            "Error: %d  check:(%d,%d)  found: (%d,%d)\n",
                            (int)i, mCheck, mLength, m, length
                    );
                    nfailed += 1;
                }
            }
            else {
                if (m || mLength) {
                    if (!fDump) {
                        printResult(
                                    pObj,
                                    (int)i,
                                    pattern,
                                    text,
                                    mCheck,
                                    mLength,
                                    m,
                                    length
                        );
                    }
                    fprintf(
                            stderr,
                            "Error: %d  check:(%d,%d)  found: (%d,%d)\n",
                            (int)i, mCheck, mLength, m, length
                    );
                    nfailed += 1;
                }
            }
            obj_Release(pPat32);
            pPat32 = OBJ_NIL;
            obj_Release(pTxt32);
            pTxt32 = OBJ_NIL;
        }
        fprintf(stderr, "%lu/%lu tests succeeded.\n", ntests - nfailed, ntests);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_TRegex32);
    TINYTEST_ADD_TEST(test_TRegex32_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TRegex32_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_TRegex32);





