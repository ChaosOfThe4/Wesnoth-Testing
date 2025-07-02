// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

	void injected_thread() {
		MessageBox(0, 0, 0, 0); //Empty error box to show proper injection/dll loading
		while (true) {
			if (GetAsyncKeyState('M')) { //Gets if 'M' key is pressed
				DWORD* player_base = (DWORD*)0x017EED18; //player base in wesnoth
				DWORD* game_base = (DWORD*)(*player_base + 0xA90); // game base in wesnoth
				DWORD* gold = (DWORD*)(*game_base + 4); //gold location wesnoth
				*gold = 999; //changes gold
			}

			// So our thread doesn't constantly run, we have it pause execution for a millisecond.
			// This allows the processor to schedule other tasks.
			Sleep(1);
		}
	}


	BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
		if (fdwReason == DLL_PROCESS_ATTACH) {
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)injected_thread, NULL, 0, NULL);
		}

		return true;
	}