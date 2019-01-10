// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                      Main Program Header
//****************************************************************
/*
 * Program
 *			Main Program Header
 * Purpose
 *			This header supplies the constants and macros needed
 *			by the main program and all its objects.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/10/2018 Generated
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
#include        <appl.h>
#include        <AStr.h>
#include        <path.h>


#ifndef         MAIN_PROGRAM_H
#define         MAIN_PROGRAM_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef enum main_idents_e {
        OBJ_IDENT_BASE=OBJ_IDENT_USER_ENTRIES,
        // MAIN_IDENT_MAIN,                 // Defined in libCmn
        // MAIN_IDENT_MAIN_CLASS,
    } MAIN_IDENTS;
    

   
#define outBaseID       "outBase"       /* Base Directory for output */
#define srcFileID       "srcFile"       /* Input Source File Path */
#define srcBaseID       "srcBase"       /* Input Source Base Directory */

    
    
    

    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_PROGRAM_H */

