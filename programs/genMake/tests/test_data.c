/*
 *	Generated 07/17/2017 14:59:49
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


static
const
char    *pGoodJson01 =
    "{\n"
        "\"library\":{\n"
            "\"name\":\"Cmn\",\n"
            "\"deps\":null,\n"
            "\"headers\":null,\n"
        "}\n,"
        "\"objects\": {\n"
            "\"AStr\":{\"deps\":[\"libCmn.h\"], \"json\":true, \"test\":true},\n"
        "},\n"
        "\"routines\": [\n"
                "\"dllist.c\",\n"
        "],\n"
    "}\n";


static
const
char    *pGoodJsonObject1 = "{\n"
            "\"AStr\":{"
                "\"deps\":[\"cmn\",\"array\"],"
                "\"json\":true,"
                "\"test\":true"
            "}\n"
        "}\n";








