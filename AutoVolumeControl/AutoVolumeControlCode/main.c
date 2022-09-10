#include <stdio.h>

#include "main_functions.h"
#include "user_functions.h"
#include "tests.h"

int main()
{
    #ifdef DEBUG
    Tests();
    #else
        printf("AutoVolumeControl\n");
        printf("\n");
        /*     startWD();
        */    
        /*  while(1)
            { */ 
        ProgramRun(NULL);
            /* } */
        /*     stopWD();
        */    
    #endif
    return 0;
}