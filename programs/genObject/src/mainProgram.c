//
//  main.c
//
//  Created by bob on 7/17/17.
//



//#include        <stdio.h>
#include        <genObject_defs.h>
#include        <Main.h>





int             main(
    int             cArgs,
    char            *ppArgV[],
    char            **ppEnv
)
{
    int             iRc = 0;
    MAIN_DATA       *pMain = OBJ_NIL;
    ERESULT         eRc;
    
#ifdef XYZZY
    fprintf(stderr, "\n\nEnvironment Variables:\n");
    while (*ppEnv) {
        fprintf(stderr, "\t%s\n", *ppEnv);
        ++ppEnv;
    }
    fprintf(stderr, "\n\n");
#endif

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
