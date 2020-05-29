
/* Do whatever you want with this code.
No warranty implied.*/

#include <psp2/ctrl.h> //used for the controls
#include <psp2/appmgr.h> //used for sceKernelExitProcess
#include <psp2/kernel/threadmgr.h> //used for sceKernelDelayThread
#include <psp2/kernel/processmgr.h> //used for sceKernelExitProcess
#include "debugScreen.h" //used to display things on screen

#define printf(...) psvDebugScreenPrintf(__VA_ARGS__) //Makes every call to printf() be replaced by pscDebugSceenPrintf()

int main(int argc, char* argv[]){
	psvDebugScreenInit(); //Initializes the DebugScreen library.

	printf("\n--- CreepNT Corporation presents ---\n"); 	// Used to display text on the screen
	printf("Hello world ! - An innovative software.\n"); 	// "\n" means "new line"
    	printf("\nPress X to exit.\n");				// See the C standard library "printf" function for more details

    	SceCtrlData pad; //Required structure to hold data from sceCtrlPeekBufferPositive

	while (1) {//Infinite loop
		sceCtrlPeekBufferPositive(0, &pad, 1); //Get the state of all held buttons.
		
		if (pad.buttons == SCE_CTRL_CROSS) //If CROSS is the ONLY pressed button...
			break; //Exit out of the infinite loop
		
		sceKernelDelayThread(200 * 1000); 	//Wait 200ms 
							//(sceKernelDelayThread takes a parameter in microseconds)
							// use (X * 1000) for ms, (X * 1000 * 1000) for seconds
	}

    	sceKernelExitProcess(0); //Exit the process with error code 0 (everything went fine).
    	return 0;
}
