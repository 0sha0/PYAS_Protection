#include <ntifs.h>
#define REG_TAG "rootkit"
NTSTATUS RegistryCallback(
	_In_ PVOID CallbackContext,
	_In_ PVOID Argument1,
	_In_ PVOID Argument2
);
BOOLEAN GetNameForRegistryObject(
	_Out_	 PUNICODE_STRING pRegistryPath,
	_In_	 PUNICODE_STRING pPartialRegistryPath,
	_In_	 PVOID pRegistryObject
);
