// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Main.c
 *	Generated 04/28/2020 23:01:38
 *
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include        <Main_internal.h>
#include        <SrcErrors.h>
#include        <trace.h>
#include        <stdbool.h>
#include        <stddef.h>
#include        <stdint.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <strings.h>
#include        <pwd.h>
#include        <sys/time.h>
#include        <unistd.h>
#include        <sys/types.h>


ERESULT         Main_SetOutput360(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutput8085(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutput8086(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputAccts(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputAsm(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputCmn(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputDisk(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputEmu(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputFat(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputGraph(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputJson(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputLL1(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputLnk(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputObj(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputPrs(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputTbl(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputTest(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputTrade(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputVid(
    MAIN_DATA       *this,
    const
    char            *pStrA
);
ERESULT         Main_SetOutputWork(
    MAIN_DATA       *this,
    const
    char            *pStrA
);



#ifdef	__cplusplus
extern "C" {
#endif
    

    static
    CMDUTL_OPTION       pPgmOptions[] = {
        {
            "backup",
            'n',
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_BOOL,
            0,
            offsetof(MAIN_DATA, fBackup),
            NULL,
            "Backup output files if they exist"
        },
        {
            "360",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutput360,
            "Output to lib360"
        },
        {
            "8085",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutput8085,
            "Output to lib8085"
        },
        {
            "8086",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutput8086,
            "Output to lib8086"
        },
        {
            "accts",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputAccts,
            "Output to libAccts"
        },
        {
            "asm",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputAsm,
            "Output to libLL1"
        },
        {
            "cmn",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputCmn,
            "Output to libCmn"
        },
        {
            "disk",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputDisk,
            "Output to libDisk"
        },
        {
            "emu",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputEmu,
            "Output to libEmu"
        },
        {
            "graph",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputGraph,
            "Output to libGraph"
        },
        {
            "json",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputJson,
            "Generate _json.c only"
        },
        {
            "ll1",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputLL1,
            "Output to libLL1"
        },
        {
            "lnk",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputLnk,
            "Output to libLnk"
        },
        {
            "mdldir",
            'm',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_PATH,
            0,
            offsetof(MAIN_DATA, pOutputPath),
            NULL,
            "Model Drive+Directory Path"
        },
        {
            "obj",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputObj,
            "Output to libObj"
        },
        {
            "outdir",
            'o',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_PATH,
            0,
            offsetof(MAIN_DATA, pOutputPath),
            NULL,
            "Output Drive+Directory Path"
        },
        {
            "prs",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputPrs,
            "Output to libPrs"
        },
        {
            "tbl",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputTbl,
            "Output to libTbl"
        },
        {
            "test",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputTest,
            "Generate _test.c only"
        },
        {
            "trade",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputTrade,
            "Output to libTrade"
        },
        {
            "vid",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputVid,
            "Output to libVid"
        },
        {
            "work",
            '\0',
            CMDUTL_ARG_OPTION_OPTIONAL,
            CMDUTL_TYPE_EXEC,
            0,
            0,
            (void *)Main_SetOutputWork,
            "Output to libWork"
        },
        {0}
    };



 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    ERESULT         Main_SetOutput360(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/lib360/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutput8085(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/lib8085/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutput8086(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/lib8086/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputAccts(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/libAccts/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputAsm(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/libAsm/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputCmn(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/libCmn/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputDisk(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/libDisk/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputEmu(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/libEmu/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputGraph(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/libGraph/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputJson(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        this->fJson = true;
        this->fObj  = false;
        this->fTest = false;

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputLL1(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/libLL1/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputLnk(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/libLnk/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputObj(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/libObj/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputPrs(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/libPrs/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputTbl(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/libTbl/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputTest(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        this->fJson = false;
        this->fObj  = false;
        this->fTest = true;

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputTrade(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/libTrade/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputVid(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/libVid/");

        // Put code here...

        // Return to caller.
        return eRc;
    }


    ERESULT         Main_SetOutputWork(
        MAIN_DATA       *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.

        Gen_setOutputDrvDirA(this->pGen, "~/git/libWork/");

        // Return to caller.
        return eRc;
    }






    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    MAIN_DATA *     Main_Alloc (
        void
    )
    {
        MAIN_DATA       *this;
        uint32_t        cbSize = sizeof(MAIN_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    MAIN_DATA *     Main_New (
        void
    )
    {
        MAIN_DATA       *this;
        
        this = Main_Alloc( );
        if (this) {
            this = Main_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                    N o d e  C l a s s
    //---------------------------------------------------------------

    NODECLASS_DATA * Main_getClass (
        MAIN_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pClass;
    }


    bool            Main_setClass (
        MAIN_DATA       *this,
        NODECLASS_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pClass) {
            obj_Release(this->pClass);
        }
        this->pClass = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                            D i c t
    //---------------------------------------------------------------

    DICT_DATA *     Main_getDict (
        MAIN_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pDict;
    }


    bool            Main_setDict (
        MAIN_DATA       *this,
        DICT_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pDict) {
            obj_Release(this->pDict);
        }
        this->pDict = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                      G e n e r a t e
    //---------------------------------------------------------------

    GEN_DATA *      Main_getGen (
        MAIN_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pGen;
    }


    bool            Main_setGen (
        MAIN_DATA       *this,
        GEN_DATA        *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pGen) {
            obj_Release(this->pGen);
        }
        this->pGen = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Main_getPriority (
        MAIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Main_setPriority (
        MAIN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Main_getSize (
        MAIN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * Main_getStr (
        MAIN_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        Main_setStr (
        MAIN_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Main_getSuperVtbl (
        MAIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = Main_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another MAIN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Main_Assign (
        MAIN_DATA		*this,
        MAIN_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Main_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //               C r e a t e  I n p u t  P a t h
    //---------------------------------------------------------------

    PATH_DATA *     Main_CheckInputPath (
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        PATH_DATA       *pPath = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        TRC_OBJ(this, "Main_CreateOutputPath(%s)\n", pStr ? AStr_getData(pStr) : "");

        pPath = Path_NewFromAStr(pStr);
        Appl_ErrorFatalOnBool(
                    (OBJ_NIL == pPath),
                    "FATAL - Failed to create path \"from\" \n"
        );
        eRc = Path_Clean(pPath);
        Appl_ErrorFatalOnEresult(
                    eRc,
                    "FATAL - File, %s, does not exist or is not a file!\n",
                    Path_getData(pPath)
        );
        eRc = Path_IsFile(pPath);
        Appl_ErrorFatalOnEresult(
                    eRc,
                    "FATAL - File, %s, does not exist or is not a file!\n",
                    Path_getData(pPath)
        );

        // Return to caller.
        return pPath;
    }



    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Main      *pCopy = Main_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a MAIN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    MAIN_DATA *     Main_Copy (
        MAIN_DATA       *this
    )
    {
        MAIN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef MAIN_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Main_New( );
        if (pOther) {
            eRc = Main_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            Main_Dealloc (
        OBJ_ID          objId
    )
    {
        MAIN_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((MAIN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Main_setClass(this, OBJ_NIL);
        Main_setDict(this, OBJ_NIL);
        Main_setGen(this, OBJ_NIL);
        Main_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Main      *pDeepCopy = Main_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a MAIN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    MAIN_DATA *     Main_DeepyCopy (
        MAIN_DATA       *this
    )
    {
        MAIN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Main_New( );
        if (pOther) {
            eRc = Main_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Main_Disable (
        MAIN_DATA		*this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Main_Enable (
        MAIN_DATA		*this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E x e c
    //---------------------------------------------------------------

    int             Main_Exec (
        MAIN_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        int             iRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        char            *pChrStr;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        eRc = Main_ParseArgsDefault(this);
        if (ERESULT_FAILED(eRc)) {
            Appl_Usage((APPL_DATA *)this, "ERROR - Failed to properly set defaults!");
            exit(8);
        }

        for (;;) {

            fRc = Appl_IsMore((APPL_DATA *)this);
            if (!fRc) {
                break;
            }

            eRc = Appl_ProcessOptions((APPL_DATA *)this);
            if (ERESULT_FAILED(eRc)) {
                Appl_Usage((APPL_DATA *)this, "ERROR - Failed to properly parse command line!");
                exit(8);
            }

            pChrStr = Appl_NextArg((APPL_DATA *)this);
            if (NULL == pChrStr) {
                break;
            }
            pStr = AStr_NewA(pChrStr);
            iRc = Main_ProcessArg(this, pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
            if (iRc) {
                return iRc;
            }
        }

        // Return to caller.
        return 0;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    MAIN_DATA *   Main_Init (
        MAIN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(MAIN_DATA);
        //ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        this = (OBJ_ID)Appl_Init((APPL_DATA *)this);        // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_MAIN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Main_Vtbl);

        this->fJson = true;
        this->fObj = true;
        this->fTest = true;

        this->pDict = Dict_New( );
        if (OBJ_NIL == this->pDict) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        this->pGen = Gen_New( );
        if (OBJ_NIL == this->pGen) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        Gen_setDict(this->pGen, this->pDict);

        Appl_setUsage(
                          (APPL_DATA *)this,
                          this,
                          (void *)Main_UsageDesc,
                          (void *)Main_UsageProgLine,
                          (void *)Main_UsageOptions
        );
        ((APPL_DATA *)this)->iVerbose++;
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Main::sizeof(MAIN_DATA) = %lu\n", 
                sizeof(MAIN_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(MAIN_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Main_IsEnabled (
        MAIN_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //              P a r s e  A r g s  D e f a u l t
    //---------------------------------------------------------------

    /*! Set default values for arguments just prior to them being parsed.
     This is called by Appl_SetupFromArgV() and Appl_SetupFromStr().
     Parsed arguments may replace any value set here.
     @return    If successful, then ERESULT_SUCESS. Otherwise, an ERESULT_*
                error. Note: this is ignored in Appl.
     */
    ERESULT         Main_ParseArgsDefault (
        MAIN_DATA        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        Gen_setOutputDrvDirA(this->pGen, "./");


        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //              P r o c e s s  A r g s
    //---------------------------------------------------------------

    ERESULT         Main_ProcessInit (
        MAIN_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif


        // Return to caller.
        return eRc;
    }


    /*!
     Process each command line argument, parsing the JSON file and
     generating the Makefile.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Main_ProcessArg (
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pInput;
        NODECLASS_DATA  *pClass;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        TRC_OBJ(this, "Main_ProcessArg(%s)\n", pStr ? AStr_getData(pStr) : "");

        if (!Appl_getQuiet((APPL_DATA *)this)) {
            fprintf(stderr, "\tProcessing - %s...\n", AStr_getData(pStr));
        }

        pPath = Main_CheckInputPath(this, pStr);
        Appl_ErrorFatalOnBool(
                    (OBJ_NIL == pPath),
                    "FATAL - Failed to create path \"from\" \n"
        );
        pInput = AStr_NewFromUtf8File(pPath);
        Appl_ErrorFatalOnBool(
                    (OBJ_NIL == pInput),
                    "FATAL - Failed to read data from &s\n",
                    Path_getData(pPath)
        );
        pClass = NodeClass_NewFromJsonString(pInput);
        Appl_ErrorFatalOnBool(
                    (OBJ_NIL == pClass),
                    "FATAL - Failed to read data from &s\n",
                    Path_getData(pPath)
        );
        eRc = NodeClass_CreateDictEntries(pClass, this->pDict);
        Appl_ErrorFatalOnEresult(
                    eRc,
                    "FATAL - Failed to create expansion entries from &s\n",
                    Path_getData(pPath)
        );
        eRc = Gen_SetDefaults(this->pGen);
        Appl_ErrorFatalOnEresult(
                    eRc,
                    "FATAL - Failed to create expansion entries for &s\n",
                    Path_getData(pPath)
        );

        eRc =   Gen_CreateObjectFiles(
                                    this->pGen,
                                    pClass,
                                    this->fJson,
                                    this->fObj,
                                    this->fTest,
                                    !Appl_getQuiet((APPL_DATA *)this)
                );
        Appl_ErrorFatalOnEresult(
                    eRc,
                    "FATAL - Failed to create expansion entries from &s\n",
                    Path_getData(pPath)
        );
        if (!Appl_getQuiet((APPL_DATA *)this)) {
            fprintf(stderr, "\t\tCreated object from %s.\n", Path_getData(pPath));
        }

        // Return to caller.
        obj_Release(pClass);
        pClass = OBJ_NIL;
        obj_Release(pInput);
        pInput = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        return eRc;
    }



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = Main_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Main", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Main_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MAIN_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(MAIN_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Main_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return Main_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Main_Enable;
                        }
                        break;

                    case 'P':
#ifdef  MAIN_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Main_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Main_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Main_ToDebugString;
                        }
#ifdef  MAIN_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Main_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Main_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Main_ToDebugString)
                    return "ToDebugString";
#ifdef  MAIN_JSON_SUPPORT
                if (pData == Main_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                  S e t u p  F r o m  A r g V
    //---------------------------------------------------------------

    ERESULT         Main_SetupFromArgV (
        MAIN_DATA       *this,
        uint16_t        cArgs,
        char            *ppArgV[],
        char            **ppEnv
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = Appl_SetupFromArgV((APPL_DATA *)this, cArgs, ppArgV, ppEnv, pPgmOptions);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Main_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Main_ToDebugString (
        MAIN_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    Main_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                  U s a g e  H e l p
    //---------------------------------------------------------------

    /*!
     Print the program description with a trailing '\n' and leading "  ".
     @param     this        Object Pointer
     @param     pOutput     File to write to
     @param     pPgmPath    Program's Path
     @return    ERESULT_SUCCESS if successful, otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Main_UsageDesc (
        MAIN_DATA       *this,
        FILE            *pOutput,
        PATH_DATA       *pPgmPath
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        fprintf(
                pOutput,
                "  Generate an object given an input json file which defines it.\n"
        );

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    // Note: --debug(-d), --force(-f), --help(-?,-h), --verbose(-v) are already
    //      taken care of in appl_Usage().
    ERESULT         Main_UsageOptions (
        MAIN_DATA       *this,
        FILE            *pOutput
    )
    {
        uint32_t        i = 0;
        //CMDUTL_OPTION   *pPgmOption = pPgmOptions;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        for (i=0; pPgmOptions[i].pLongName || pPgmOptions[i].shortName; i++) {
            char            shortOpt[3] = "";
            char            longOpt[20] = "";
            if (pPgmOptions[i].shortName) {
                shortOpt[0] = '-';
                shortOpt[1] = pPgmOptions[i].shortName;
                shortOpt[2] = '\0';
            }
            if (pPgmOptions[i].pLongName) {
                longOpt[0] = '-';
                longOpt[1] = '-';
                strcpy(longOpt+2, pPgmOptions[i].pLongName);
            }
            fprintf(pOutput, "  %-3s %-20s %s\n", shortOpt, longOpt, pPgmOptions[i].pDesc);
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    /*!
     Print the program usage line with a trailing '\n' and leading "  ".
     @param     this        Object Pointer
     @param     pOutput     File to write to
     @param     pPgmPath    Program's Path
     @param     pNameA      Program's name
     @return    ERESULT_SUCCESS if successful, otherwise, an ERESULT_*
     error code.
     */
    ERESULT         Main_UsageProgLine (
        MAIN_DATA       *this,
        FILE            *pOutput,
        PATH_DATA       *pPgmPath,
        const
        char            *pNameA
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        fprintf(pOutput, "  %s [options] input_path\n", pNameA);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            Main_Validate (
        MAIN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_MAIN))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(MAIN_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


