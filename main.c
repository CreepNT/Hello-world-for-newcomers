
/* do what the fuck you want with this software 
No warranty implied. */

//I think those headers are useless tbh
#include <stdio.h>
#include <taihen.h>
#include <psp2/kernel/processmgr.h> 
//Ignore those headers

#include <psp2/ctrl.h> //used for the controls
#include <psp2/appmgr.h> //used for sceKernelExitProcess
#include "debugScreen.h"

#define printf(...) psvDebugScreenPrintf(__VA_ARGS__) //Makes every call to printf() be replaced by pscDebugSceenPrintf()

int main(int argc, char* argv[]){
	psvDebugScreenInit(); //Initializes the DebugScreen library.

	printf("\n--- CreepNT Corporation presents ---\n"); //Used to display text on the screen
	printf("Hello world ! - An innovative software.\n"); // "\n" means "new line"
    	printf("\nPress X to start.\n");

    	SceCtrlData pad; //Required structure to hold data from sceCtrlPeekBufferPositive

	while (1) {//infinite loop
		sceCtrlPeekBufferPositive(0, &pad, 1); //Get the state of all held buttons.
		if (pad.buttons == SCE_CTRL_CROSS) //If CROSS is the ONLY pressed button...
			break; //Exit out of the infinite loop
		sceKernelDelayThread(200 * 1000); //Wait 200ms (sceKernelDelayThread takes a parameter in microseconds)
	}

    	sceKernelExitProcess(0);
    	return 0;
}
