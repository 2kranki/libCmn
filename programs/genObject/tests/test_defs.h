// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   test_defs.h
 *
 *
 * Created on November 12, 2017
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


#ifndef     TEST_DEFS_H
#define     TEST_DEFS_H   1


#ifdef	__cplusplus
extern "C" {
#endif
    

#define TEST_FILES_DIR   "${HOME}/git/libCmn/programs/genObject/tests/files"
#define TEST_MODELS_DIR  "${HOME}/git/libCmn/programs/genObject/models"

    
    //****************************************************************
    //* * * * * * * * * * *  Data Definitions  * * * * * * * * * * * *
    //****************************************************************


    

    typedef struct cmn_data_s   CMN_DATA;

    typedef enum obj_idents_test_e {
        OBJ_IDENT_TESTS=OBJ_IDENT_USER_ENTRIES,
        OBJ_IDENT_OBJTEST,              // Test Object
        OBJ_IDENT_OBJTEST_CLASS,
    } OBJ_IDENTS_TEST;
    
    


#endif	/* TEST_DEFS_H */

