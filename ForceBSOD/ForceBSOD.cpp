#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#pragma comment(lib, "ntdll.lib")

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN OldValue);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask,
PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);

void BSOD() {
	BOOLEAN bl;
	ULONG Response;
	RtlAdjustPrivilege(19, TRUE, FALSE, &bl); // Enable SeShutdownPrivilege
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &Response); // Shutdown
}

int main()
{
    std::cout << "You have 5 seconds to close this program or it will force a BSOD crash\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(5000)); // five seconds
	std::cout << "Starting...!\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // one second
	BSOD(); // crash
}