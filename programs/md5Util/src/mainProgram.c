//
//  main.c
//
//  Created by bob on 7/17/17.
//



//#include        <stdio.h>
#include        <md5Util.h>
#include        <main.h>





int             main(
    int             cArgs,
    const
    char            *ppArgv[]
)
{
    int             iRc = 0;
    MAIN_DATA       *pMain = OBJ_NIL;
    
    pMain = main_New(cArgs, ppArgv);
    if (pMain == OBJ_NIL) {
        fprintf(stderr, "FATAL ERROR - \n");
        exit(EXIT_FAILURE);
    }

    obj_Release(pMain);
    pMain = OBJ_NIL;
    return iRc;
}
