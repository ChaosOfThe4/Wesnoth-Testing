// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include "pch.h"

DWORD ret_addy = 0x00CCAF95;
DWORD* player_base;
DWORD* game_base;
DWORD* gold;



__declspec(naked) void codecave() {
	//assembly block to push everything onto the stack
	__asm {
		pushad
		call dword ptr ds : [eax + 0x68]
		popad
		call dword ptr ds : [eax + 0x28]
		mov al, 0x01
		jmp ret_addy
	}

}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	DWORD old_protect;//Used for VirtualProtect
	unsigned char* hook_location = (unsigned char*)0x00CCAF90; //Unsigned char* so we can adjust the individual bytes

	if (fdwReason == DLL_PROCESS_ATTACH) {

		VirtualProtect((void*)hook_location, 6, PAGE_EXECUTE_READWRITE, &old_protect); //VirtualProtect to make executable memory writeable also and keep it executable

		*hook_location = 0xE9; //opcode for jmp command in assemlby 
		*(DWORD*)(hook_location + 1) = (DWORD)&codecave - ((DWORD)hook_location + 5); // Caculate the location using the formula: new_location - original_location+5
		//*(hook_location + 5) = 0x90; // Finally, since the original instructions totalled 6 bytes, NOP out the last remaining byte
		MessageBox(0, 0, 0, 0); //Empty error box to show proper injection/DLL loading
	}

	return true;
}

