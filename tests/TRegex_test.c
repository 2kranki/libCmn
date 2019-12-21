// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 12/19/2019 23:08:58
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
#include    <TRegex_internal.h>



#define OK    1
#define NOK   0

struct {
    int     fOk;
    char    *pPattern;
    char    *pData;
    int     index;
} test_vector[] =
{
  { OK,  "\\d",                       "5",                       0},   //  0
  { OK,  "\\w+",                      "hej",                     0},   //  1
  { OK,  "\\s",                       "\t \n",                   0},   //  2
  { NOK, "\\S",                       "\t \n",                  -1},   //  3
  { OK,  "[\\s]",                     "\t \n",                   0},   //  4
  { NOK, "[\\S]",                     "\t \n",                  -1},   //  5
  { NOK, "\\D",                       "5",                      -1},   //  6
  { NOK, "\\W+",                      "hej",                    -1},   //  7
  { OK,  "[0-9]+",                    "12345",                   0},   //  8
  { OK,  "\\D",                       "hej",                     0},   //  9
  { NOK, "\\d",                       "hej",                    -1},   // 10
  { OK,  "[^\\w]",                    "\\",                      0},   // 11
  { OK,  "[\\W]",                     "\\",                      0},   // 12
  { NOK, "[\\w]",                     "\\",                     -1},   // 13
  { OK,  "[^\\d]",                    "d",                       0},   // 14
  { NOK, "[\\d]",                     "d",                      -1},   // 15
  { NOK, "[^\\D]",                    "d",                      -1},   // 16
  { OK,  "[\\D]",                     "d",                       0},   // 17
  { OK,  "^.*\\\\.*$",                "c:\\Tools",               0},   // 18
  { OK,  "^[\\+-]*[\\d]+$",           "+27",                     0},   // 19
  { OK,  "[abc]",                     "1c2",                     1},   // 20
  { NOK, "[abc]",                     "1C2",                    -1},   // 21
  { OK,  "[1-5]+",                    "0123456789",              1},   // 22
  { OK,  "[.2]",                      "1C2",                     2},   // 23
  { OK,  "a*$",                       "Xaa",                     1},   // 24
  { OK,  "a*$",                       "Xaa",                     1},   // 25
  { OK,  "[a-h]+",                    "abcdefghxxx",             0},   // 26
  { NOK, "[a-h]+",                    "ABCDEFGH",               -1},   // 27
  { OK,  "[A-H]+",                    "ABCDEFGH",                0},   // 28
  { NOK, "[A-H]+",                    "abcdefgh",               -1},   // 29
  { OK,  "[^\\s]+",                   "abc def",                 0},   // 30
  { OK,  "[^fc]+",                    "abc def",                 0},   // 31
  { OK,  "[^d\\sf]+",                 "abc def",                 0},   // 32
  { OK,  "\n",                        "abc\ndef",                3},   // 33
  { OK,  "b.\\s*\n",                  "aa\r\nbb\r\ncc\r\n\r\n",  4},   // 34
  { OK,  ".*c",                       "abcabc",                  0},   // 35
  { OK,  ".+c",                       "abcabc",                  0},   // 36
  { OK,  "[b-z].*",                   "ab",                      1},   // 37
  { OK,  "b[k-z]*",                   "ab",                      1},   // 38
  { NOK, "[0-9]",                     "  - ",                   -1},   // 39
  { OK,  "[^0-9]",                    "  - ",                    0},   // 40
  { OK,  "0|",                        "0|",                      0},   // 41
  { NOK, "\\d\\d:\\d\\d:\\d\\d",      "0s:00:00",               -1},   // 42
  { NOK, "\\d\\d:\\d\\d:\\d\\d",      "000:00",                 -1},   // 43
  { NOK, "\\d\\d:\\d\\d:\\d\\d",      "00:0000",                -1},   // 44
  { NOK, "\\d\\d:\\d\\d:\\d\\d",      "100:0:00",               -1},   // 45
  { NOK, "\\d\\d:\\d\\d:\\d\\d",      "00:100:00",              -1},   // 46
  { NOK, "\\d\\d:\\d\\d:\\d\\d",      "0:00:100",               -1},   // 47
  { OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "0:0:0",                   0},   // 48
  { OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "0:00:0",                  0},   // 49
  { OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "0:0:00",                  0},   // 50
  { OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "00:0:0",                  0},   // 51
  { OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "00:00:0",                 0},   // 52
  { OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "00:0:00",                 0},   // 53
  { OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "0:00:00",                 0},   // 54
  { OK,  "\\d\\d?:\\d\\d?:\\d\\d?",   "00:00:00",                0},   // 55
  { OK,  "[Hh]ello [Ww]orld\\s*[!]?", "Hello world !",           0},   // 56
  { OK,  "[Hh]ello [Ww]orld\\s*[!]?", "hello world !",           0},   // 57
  { OK,  "[Hh]ello [Ww]orld\\s*[!]?", "Hello World !",           0},   // 58
  { OK,  "[Hh]ello [Ww]orld\\s*[!]?", "Hello world!   ",         0},   // 59
  { OK,  "[Hh]ello [Ww]orld\\s*[!]?", "Hello world  !",          0},   // 60
  { OK,  "[Hh]ello [Ww]orld\\s*[!]?", "hello World    !",        0},   // 61
  /* Failing test case reported in
      https://github.com/kokke/tiny-regex-c/issues/12
   */
  { NOK, "\\d\\d?:\\d\\d?:\\d\\d?",   "a:0",                    -1},   // 62
/*
  { OK,  "[^\\w][^-1-4]",     ")T"          },
  { OK,  "[^\\w][^-1-4]",     ")^"          },
  { OK,  "[^\\w][^-1-4]",     "*)"          },
  { OK,  "[^\\w][^-1-4]",     "!."          },
  { OK,  "[^\\w][^-1-4]",     " x"          },
  { OK,  "[^\\w][^-1-4]",     "$b"          },
*/
  { OK,  ".?bar",                      "real_bar",               4},   // 63
  { NOK, ".?bar",                      "real_foo",              -1},   // 64
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






int             test_TRegex_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TREGEX_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TRegex_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = TRegex_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TREGEX);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_TRegex_Test01(
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    TREGEX_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fRc;
    char*           text;
    char*           pattern;
    int             should_fail;
    size_t          nfailed = 0;
    size_t          i;
    int             m;
    int             mCheck;
    bool            fDump = true;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TRegex_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = TRegex_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TREGEX);
        TINYTEST_TRUE( (fRc) );
        
        for (i = 0; i < ntests; ++i) {
            pattern = test_vector[i].pPattern;
            text = test_vector[i].pData;
            should_fail = (test_vector[i].fOk == NOK);
            mCheck = test_vector[i].index;

            m = TRegex_Match(pObj, pattern, text);
            if (fDump) {
                fprintf(stderr, "%d - %d\n", (int)i, m);
                pStr = TRegex_ToStringPattern(pObj);
                if (pStr) {
                    fprintf( stderr, "pattern %s ->\n%s\n", pattern, AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            if (should_fail) {
                if (m != (-1)) {
                    fprintf(
                            stderr,
                            "[%lu/%lu]: pattern '%s' matched '%s' unexpectedly. \n",
                            (i+1), ntests, pattern, text
                    );
                    pStr = TRegex_ToStringPattern(pObj);
                    if (pStr) {
                        fprintf( stderr, "pattern %s ->\n%s\n", pattern, AStr_getData(pStr));
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                    nfailed += 1;
                }
            }
            else {
                if ((m == (-1)) || !(m == mCheck)) {
                    fprintf(
                            stderr,
                            "[%lu/%lu]: pattern '%s' didn't match '%s' as expected. \n",
                            (i+1), ntests, pattern, text
                    );
                    pStr = TRegex_ToStringPattern(pObj);
                    if (pStr) {
                        fprintf( stderr, "pattern %s ->\n%s\n", pattern, AStr_getData(pStr));
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                    nfailed += 1;
                }
            }
        }
        fprintf(stderr, "%lu/%lu tests succeeded.\n", ntests - nfailed, ntests);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_TRegex);
    TINYTEST_ADD_TEST(test_TRegex_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TRegex_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_TRegex);





