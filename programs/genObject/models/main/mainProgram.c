// vi:nu:et:sts=4 ts=4 sw=4

//
//  mainProgram.c
//
//  Created by bob on 7/17/17.
//



//#include        <stdio.h>
#include        <Main_defs.h>
#include        <Main.h>





int             main(
    int             cArgs,
    char            *ppArgV[],
    char            **ppEnv
)
{
    int             iRc = 0;
    MAIN_DATA       *pMain = OBJ_NIL;
    ERESULT	        eRc;
    
    pMain = Main_Shared( );
    if (pMain == OBJ_NIL) {
        fprintf(stderr, "FATAL ERROR - \n");
        exit(EXIT_FAILURE);
    }

    eRc = Main_SetupFromArgV(pMain, cArgs, ppArgV, ppEnv);
    if (ERESULT_FAILED(eRc)) {
        fprintf(stderr, "FATAL - Failed to set up arguments!\n\n\n");
        return 8;
    }
    
    iRc = Main_Exec(pMain);

    //obj_SharedReset( );
    pMain = OBJ_NIL;
    return iRc;
}
