//
//  main.c
//
//  Created by bob on 7/17/17.
//



//#include        <stdio.h>
#include        <genMake.h>
#include        <main.h>





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

    pMain = main_New( );
    if (pMain == OBJ_NIL) {
        fprintf(stderr, "FATAL ERROR - \n");
        exit(EXIT_FAILURE);
    }
    
    eRc = main_SetupFromArgV(pMain, cArgs, ppArgV, ppEnv);
    if (ERESULT_FAILED(eRc)) {
        fprintf(stderr, "FATAL - Failed to set up arguments!\n\n\n");
        return 8;
    }
    
    iRc = main_Exec(pMain);

    //obj_Release(pMain);
    pMain = OBJ_NIL;
    return iRc;
}
