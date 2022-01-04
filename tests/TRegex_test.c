// vi:nu:et:sts=4 ts=4 sw=4
//****************************************************************
//                      Test Object Program
//****************************************************************
/*
 * Program
 *          Test Object Program
 * Purpose
 *          This program tests a particular object given certain
 *          parameters.
 *
 * Remarks
 *  1.      This relies on the fact that we can add to the Test
 *          Object by simply coding methods that use the Test
 *          Object.
 *
 * History
 *  08/29/2021 Generated
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




/*
 TestForFail(error_sttring)         <= Tests eRc for failure
 TestForFalse(test, error_sttring)
 TestForNotNull(test, error)
 TestForNull(test, error)
 TestForSuccess(error)              <= Tests eRc for success
 TestForTrue(test, error)
 */





#include    <test_defs.h>
#include    <Test_internal.h>
#include    <trace.h>
#include    <TRegex_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



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
  { false , "a"                        , "",                       0,  0},    //  65
  { true  , "a*"                       , "",                       0,  0},    //  66
  { false , "[^s][^b]"                 , "a",                      0,  0},    //  67
  { false , "[^\\d]+\\s"               , "e",                      0,  0},    //  68
  { true  , "\\d"                      , "5",                      0,  1},    //  69
  { false , "\\d+"                     , "y",                      0,  0},    //  70
  { true  , "\\w+"                     , "hej",                    0,  3},    //  71
  { true  , "\\s"                      , "\t \n",                  0,  1},    //  72
  { false , "\\S"                      , "\t \n",                  0,  0},    //  73
  { true  , "[\\s]"                    , "\t \n",                  0,  1},    //  74
  { false , "[\\S]"                    , "\t \n",                  0,  0},    //  75
  { false , "\\D"                      , "5",                      0,  0},    //  76
  { false , "\\W+"                     , "hej",                    0,  0},    //  77
  { true  , "[0-9]+"                   , "12345",                  0,  5},    //  78
    { true  , "\\D"                      , "hej",                    0,  1},    //  79
    { false , "\\d"                      , "hej",                    0,  0},    //  80
    { true  , "[^\\w]"                   , "\\",                     0,  1},    //  81
    { true  , "[\\W]"                    , "\\",                     0,  1},    //  82
    { false , "[\\w]"                    , "\\",                     0,  0},    //  83
    { true  , "[^\\d]"                   , "d",                      0,  1},    //  84
    { false , "[\\d]"                    , "d",                      0,  0},    //  85
    { false , "[^\\D]"                   , "d",                      0,  0},    //  86
    { true  , "[\\D]"                    , "d",                      0,  1},    //  87
    { true  , "a+a"                      , "aaa",                    0,  3},    //  88
    { true  , "^.*\\\\.*$"               , "c:\\Tools",              0,  8},    //  89
    { true  , "^[\\+-]*[\\d]+$"          , "+27",                    0,  3},    //  90
    { true  , "[abc]"                    , "1c2",                    1,  1},    //  91
    { false , "[abc]"                    , "1C2",                    0,  0},    //  92
    { true  , "[1-5]+"                   , "0123456789",             1,  5},    //  93
    { true  , "[.2]"                     , "1C2",                    2,  1},    //  94
    { true  , "a*$"                      , "Xaa",                    1,  2},    //  95
    { true  , "[a-h]+"                   , "abcdefghxxx",            0,  8},    //  96
    { false , "[a-h]+"                   , "ABCDEFGH",               0,  0},    //  97
    { true  , "[A-H]+"                   , "ABCDEFGH",               0,  8},    //  98
    { false , "[A-H]+"                   , "abcdefgh",               0,  0},    //  99
    { true  , "[^\\s]+"                  , "abc def",                0,  3},    // 100
    { true  , "[^fc]+"                   , "abc def",                0,  2},    // 101
    { true  , "[^d\\sf]+"                , "abc def",                0,  3},    // 102
    { true  , "\n"                       , "abc\ndef",               3,  1},    // 103
    { true  , "b.\\s*\n"                 , "aa\r\nbb\r\ncc\r\n\r\n", 4,  4},    // 104
    { true  , ".*c"                      , "abcabc",                 0,  6},    // 105
    { true  , ".+c"                      , "abcabc",                 0,  6},    // 106
    { true  , "[b-z].*"                  , "ab",                     1,  1},    // 107
    { true  , "b[k-z]*"                  , "ab",                     1,  1},    // 108
    { false , "[0-9]"                    , "  - ",                   0,  0},    // 109
    { true  , "[^0-9]"                   , "  - ",                   0,  1},    // 110
    { true  , "0|"                       , "0|",                     0,  2},    // 111
    { false , "\\d\\d:\\d\\d:\\d\\d"     , "0s:00:00",               0,  0},    // 112
    { false , "\\d\\d:\\d\\d:\\d\\d"     , "000:00",                 0,  0},    // 113
    { false , "\\d\\d:\\d\\d:\\d\\d"     , "00:0000",                0,  0},    // 114
    { false , "\\d\\d:\\d\\d:\\d\\d"     , "100:0:00",               0,  0},    // 115
    { false , "\\d\\d:\\d\\d:\\d\\d"     , "00:100:00",              0,  0},    // 116
    { false , "\\d\\d:\\d\\d:\\d\\d"     , "0:00:100",               0,  0},    // 117
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?"  , "0:0:0",                  0,  5},    // 118
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?"  , "0:00:0",                 0,  6},    // 119
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?"  , "0:0:00",                 0,  6},    // 120
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?"  , "00:0:0",                 0,  6},    // 121
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?"  , "00:00:0",                0,  7},    // 122
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?"  , "00:0:00",                0,  7},    // 123
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?"  , "0:00:00",                0,  7},    // 124
    { true  , "\\d\\d?:\\d\\d?:\\d\\d?"  , "00:00:00",               0,  8},    // 125
    { true  , "[Hh]ello [Ww]orld\\s*[!]?", "Hello world !",          0,  13},    // 126
    { true  , "[Hh]ello [Ww]orld\\s*[!]?", "hello world !",          0,  13},    // 127
    { true  , "[Hh]ello [Ww]orld\\s*[!]?", "Hello World !",          0,  13},    // 128
    { true  , "[Hh]ello [Ww]orld\\s*[!]?", "Hello world!   ",        0,  12},    // 129
    { true  , "[Hh]ello [Ww]orld\\s*[!]?", "Hello world    !",       0,  16},    // 130
    { true  , "[Hh]ello [Ww]orld\\s*[!]?", "hello World      !",     0,  18},    // 131
    { false , "\\d\\d?:\\d\\d?:\\d\\d?"  , "a:0",                    0,  0},    // 132
    { true  , "[^\\w][^-1-4]"            , ")T",                     0,  2},    // 133
    { true  , "[^\\w][^-1-4]"            , ")^",                     0,  2},    // 134
    { true  , "[^\\w][^-1-4]"            , "*)",                     0,  2},    // 135
    { true  , "[^\\w][^-1-4]"            , "!.",                     0,  2},    // 136
    { true  , "[^\\w][^-1-4]"            , " x",                     0,  2},    // 137
    { true  , "[^\\w][^-1-4]"            , "$b",                     0,  2},    // 138
    { true  , ".?bar"                    , "real_bar",               4,  4},    // 139
    { false , ".?bar"                    , "real_foo",               0,  0},    // 140
    { false , "X?Y"                      , "Z",                      0,  0},    // 141
    { true  , "\\d+\\w?12"               , "959312",                 0,  6},    // 142
    { true  , "\\d+5"                    , "12345",                  0,  5},    // 143
    { false , "\\d++5"                   , "12345",                  0,  0},    // 144
    { false , "abcd"                     , "aBcD",                   0,  0},    // 145
    { true  , "(?i:abcd)"                , "aBcD",                   0,  4},    // 146 ??
    { false , "..."                      , "\n \n",                  0,  0},    // 147
    { true  , "(?s:...)"                 , "\n \n",                  0,  3},    // 148 ??
    { false , "(?s:(?-s:.))"             , "\n",                     0,  0},    // 149
    { true  , "(?is:A.)"                 , "a\n",                    0,  2},    // 150 ??
    { false , "(?is:(?-is:.g.))"         , "\nG\n",                  0,  0},    // 151
    { true  , "(?is:(?-is:.g.))"         , "\ng\n",                  0,  3},    // 152 ??
    { false , "abc\\bdef"                , "abcdef",                 0,  0},    // 153
    { true  , "abc\\Bdef"                , "abcdef",                 0,  6},    // 154
    { true  , "\\Bing\\b"                , "joining.",               4,  3},    // 155
    { false , "\\Bing\\b"                , " ing ",                  0,  0},    // 156
    { false,  "\\Bing\\b"                , "ing",                    0,  0},    // 157
    { false , "\\Bing\\b"                , "bingg",                  0,  0},    // 158
    { true  , "abc\\Rdef"                , "abc\r\ndef",             0,  8},    // 159
    { true  , "abc\\Rdef"                , "abc\ndef",               0,  7},    // 160
    { false , "abc\n\\Rdef"              , "abc\ndef",               0,  0},    // 161
    { true  , "abc\r\\Rdef"              , "abc\r\ndef",             0,  8},    // 162
    { true  , "^(a+)a$"                  , "aaa",                    0,  3},    // 163
    { true  , "^a(a*)a$"                 , "aa",                     0,  2},    // 164
    { true  , "^(a)+a$"                  , "aaa",                    0,  3},    // 165 ??
    { true  , "^(Hello){3}(World){1,2}$" , "HelloHelloHelloWorld",   0,  20},   // 166 ??
    { true  , "^(is:[ab])+?bc$"          , "aAaAaaAAaaAAAAbAaaAbc",  0,  21},   // 167 ??
    { true  , "(?=.*ghi)abc"             , "abcdefghi",              0,  3},    // 168 ??
    { true  , "(?s=.*END)BEGIN"          , "BEGIN..content..\nEND",  0,  5},    // 169 ??
    { false , "(?s=.*END)BEGIN"          , "BEGIN..content..\n",     0,  0},    // 170
    { false , "(?s!.*END)BEGIN"          , "BEGIN..content..\nEND",  0,  0},    // 171
    { true  , "(?s!.*END)BEGIN"          , "BEGIN..content..\n",     0,  5},    // 172 ??
    { false , "(b*){1}+b"                , "bbbbb",                  0,  0},    // 173
};


const
size_t      ntests = sizeof(test_vector) / sizeof(*test_vector);




void            printResult(
    TREGEX_DATA     *this,
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

    if (pPattern && pText)
        ;
    else {
        return;
    }
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
#ifdef XYZZY
    pStr = TRegex_ToStringPattern(this);
    if (pStr) {
        fprintf(
                stderr,
                "\t\tpattern %s ->\n%s\n",
                AStr_getData(pPat2),
                AStr_getData(pStr)
        );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
#endif
    obj_Release(pPat2);
    pPat2 = OBJ_NIL;
    obj_Release(pTxt2);
    pTxt2 = OBJ_NIL;

}





ERESULT         Test_TRegex_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TREGEX_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TRegex_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = TRegex_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TREGEX);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   TREGEX_MSGS
        TRegex_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_TRegex_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TREGEX_DATA       *pObj1 = OBJ_NIL;
    TREGEX_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(TREGEX_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = TRegex_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_TREGEX);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   TREGEX_MSGS
        TRegex_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = TRegex_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = TRegex_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TREGEX);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = TRegex_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = TRegex_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TREGEX);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = TRegex_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(TREGEX_JSON_SUPPORT) && defined(XYZZY)
        pStr = TRegex_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = TRegex_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TREGEX);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = TRegex_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_TRegex_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TREGEX_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TRegex_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TREGEX);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   TREGEX_LOG
        TRegex_setLog(pObj, this);
#endif
                
        {
            ASTR_DATA       *pStr = TRegex_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_TRegex_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TREGEX_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TRegex_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TREGEX);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   TREGEX_LOG
        TRegex_setLog(pObj, this);
#endif
                
        {
            ASTR_DATA       *pStr = TRegex_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_TRegex_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TREGEX_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    char*           pTxt;
    char*           pPat;
    bool            fShouldSucceed;
    int             nfailed = 0;
    int             i;
    int             m;
    int             mCheck;
    int             mLength;
    bool            fDump = true;
    int             length = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TRegex_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TREGEX);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   TREGEX_LOG
        TRegex_setLog(pObj, this);
#endif
                
        for (i = 0; i < ntests; ++i) {
            pPat = test_vector[i].pPattern;
            pTxt = test_vector[i].pData;
            fShouldSucceed = test_vector[i].fOk;
            mCheck = test_vector[i].index;
            mLength = test_vector[i].length;
            length = 0;

            if (fDump) {
                fprintf(stderr, "%2d TRegex_Match(\"%s\",\"%s\")\n", i, pPat, pTxt);
            }
            m = TRegex_Match(pObj, pPat, pTxt, &length);
            fprintf(
                    stderr,
                    "%2d TRegex_Match(\"%s\",\"%s\") - %s!\n",
                    i,
                    pPat,
                    pTxt,
                    (m < 0) ? "FAILED" : "Completed"
            );
            if (fDump) {
                printResult(pObj, i, pPat, pTxt, mCheck, mLength, m, length);
            }

            if (fShouldSucceed) {
                if (!((m == mCheck) && (length == mLength))) {
                    if (!fDump) {
                        printResult(pObj, i, pPat, pTxt, mCheck, mLength, m, length);
                    }
                    fprintf(
                            stderr,
                            "Error: %d  check:(%d,%d)  found: (%d,%d)\n",
                            i, mCheck, mLength, m, length
                    );
                    nfailed += 1;
                }
            }
            else {
                if (m || mLength) {
                    if (!fDump) {
                        printResult(pObj, i, pPat, pTxt, mCheck, mLength, m, length);
                    }
                    fprintf(
                            stderr,
                            "Error: %d  check:(%d,%d)  found: (%d,%d)\n",
                            i, mCheck, mLength, m, length
                    );
                    nfailed += 1;
                }
            }
        }
        fprintf(stderr, "%lu/%lu tests succeeded.\n", ntests - nfailed, ntests);

        {
            ASTR_DATA       *pStr = TRegex_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_TRegex_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TREGEX_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    char            *pPat1 = ".?bar";
    char            *pTxt1 = "real_bar";
    char            *pTxt2 = "bar_real";
    char            *pTxt3 = "real_real_bar";
    char            *pTxt4 = "real_bar_real";
    int             m;
    int             length;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TRegex_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TREGEX);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   TREGEX_LOG
        TRegex_setLog(pObj, this);
#endif
                
        eRc = TRegex_Compile(pObj, pPat1);
        TestForSuccess("");

        m = TRegex_MatchP(pObj, pTxt1, &length);
        fprintf(stderr, "\t                 01234567890123456789\n");
        fprintf(stderr, "\t(%d,%d) = \"%s\".\"%s\"\n", m, length, pPat1, pTxt1);
        TestForTrue((4 == m), "");
        TestForTrue((4 == length), "");

        m = TRegex_MatchP(pObj, pTxt2, &length);
        fprintf(stderr, "\t(%d,%d) = \"%s\".\"%s\"\n", m, length, pPat1, pTxt2);
        TestForTrue((0 == m), "");
        TestForTrue((3 == length), "");

        m = TRegex_MatchP(pObj, pTxt3, &length);
        fprintf(stderr, "\t(%d,%d) = \"%s\".\"%s\"\n", m, length, pPat1, pTxt3);
        TestForTrue((9 == m), "");
        TestForTrue((4 == length), "");

        m = TRegex_Match(pObj, pPat1, pTxt4, &length);
        fprintf(stderr, "\t(%d,%d) = \"%s\".\"%s\"\n", m, length, pPat1, pTxt4);
        TestForTrue((4 == m), "");
        TestForTrue((4 == length), "");

        {
            ASTR_DATA       *pStr = TRegex_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}




int     main (
    int         cArgs,
    const
    char        *ppArgs[],
    const
    char        *ppEnv[]
)
{
    ERESULT     eRc;
    TEST_DATA   test = {0};
    TEST_DATA   *pTest = OBJ_NIL;
    int         i;
    const
    char        *pTestNameA = NULL;

    pTest = Test_Init(&test);
    if (OBJ_NIL == pTest) {
        fprintf(
                stderr,
                "\x1b[1m\x1b[31mFATAL\x1b[0m: Could not create Test object!\n\n\n"
        );
        exit(201);
    }

    // Scan args.
    for (i=0; i<cArgs; i++) {
        if (0 == strcmp("--no_int3", ppArgs[i])) {
            Test_setAllowInt3(pTest, false);
        }
    }

    // Execute tests.
    TestExec("OpenClose", Test_TRegex_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_TRegex_Copy01, NULL, NULL);
    TestExec("Test01", Test_TRegex_Test01, NULL, NULL);
    TestExec("Test02", Test_TRegex_Test02, NULL, NULL);
    TestExec("Test03", Test_TRegex_Test03, NULL, NULL);
    TestExec("Test04", Test_TRegex_Test04, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    fprintf(stderr, "Tests completed successfully.\n");
    return 0;
}



