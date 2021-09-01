// vi:nu:et:sts=4 ts=4 sw=4
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
            "\"libDeps\":null,\n"
            "\"headers\":null,\n"
        "}\n,"
        "\"objects\": [\n"
            "{name:\"AStr\", \"json\":true},\n"
            "{name:\"appl\"},\n"
        "],\n"
        "\"routines\": [\n"
                "{name:\"dllist.c\"}\n"
        "],\n"
    "}\n";

static
const
char    *pGoodJson02 =
    "{\n"
        "\"program\":{\n"
            "\"name\":\"genMake\",\n"
            "\"deps\":[\"Cmd\"]\n"
        "}\n,"
        "\"objects\": [\n"
            "{name:\"AStr\", \"srcDeps\":[\"libCmn.h\"], \"json\":true},\n"
            "{name:\"appl\", \"srcDeps\":[\"libCmn.h\"]},\n"
        "],\n"
        "\"routines\": [\n"
                "{name:\"dllist.c\"}\n"
        "],\n"
    "}\n";


static
const
char    *pGoodJsonObject1 = 
		"{\n"
            		"name:\"AStr\", "
                	"\"libDeps\":[\"cmn\",\"array\"],"
                	"\"json\":true,"
        	"}\n";








