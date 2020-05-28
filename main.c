
/* do what the fuck you want with this software 
No warranty implied. */
#include <stdio.h>
#include <taihen.h>
#include <psp2/ctrl.h>
#include <psp2/appmgr.h>
#include <psp2/io/fcntl.h>
#include <psp2/kernel/processmgr.h>
#include "debugScreen.h"

#define printf(...) psvDebugScreenPrintf(__VA_ARGS__)

int main(int argc, char* argv[]){
    SceCtrlButtons buttons;

	psvDebugScreenInit();

	printf("\n--- CreepNT Corporation presents ---\n");
	printf("Hello world ! - An innovative software.\n");
    printf("\nPress X to start.\n");

    SceCtrlData pad;

	while (1) {
		sceCtrlPeekBufferPositive(0, &pad, 1);
		if (pad.buttons == SCE_CTRL_CROSS)
			break;
		sceKernelDelayThread(200 * 1000);
	}

    sceKernelExitProcess(0);
    return 0;
}