#include "Driver.h"
// 绕过签名检查
BOOLEAN BypassCheckSign(PDRIVER_OBJECT pDriverObject)
{
#ifdef _WIN64
	typedef struct _KLDR_DATA_TABLE_ENTRY
	{
		LIST_ENTRY listEntry;
		ULONG64 __Undefined1;
		ULONG64 __Undefined2;
		ULONG64 __Undefined3;
		ULONG64 NonPagedDebugInfo;
		ULONG64 DllBase;
		ULONG64 EntryPoint;
		ULONG SizeOfImage;
		UNICODE_STRING path;
		UNICODE_STRING name;
		ULONG   Flags;
		USHORT  LoadCount;
		USHORT  __Undefined5;
		ULONG64 __Undefined6;
		ULONG   CheckSum;
		ULONG   __padding1;
		ULONG   TimeDateStamp;
		ULONG   __padding2;
	} KLDR_DATA_TABLE_ENTRY, * PKLDR_DATA_TABLE_ENTRY;
#else
	typedef struct _KLDR_DATA_TABLE_ENTRY
	{
		LIST_ENTRY listEntry;
		ULONG unknown1;
		ULONG unknown2;
		ULONG unknown3;
		ULONG unknown4;
		ULONG unknown5;
		ULONG unknown6;
		ULONG unknown7;
		UNICODE_STRING path;
		UNICODE_STRING name;
		ULONG   Flags;
	} KLDR_DATA_TABLE_ENTRY, * PKLDR_DATA_TABLE_ENTRY;
#endif

	PKLDR_DATA_TABLE_ENTRY pLdrData = (PKLDR_DATA_TABLE_ENTRY)pDriverObject->DriverSection;
	pLdrData->Flags = pLdrData->Flags | 0x20;

	return TRUE;
}
NTSTATUS DriverEntry(
	_In_ PDRIVER_OBJECT pDriverObj,
	_In_ PUNICODE_STRING pRegistryString
)
{
	BypassCheckSign(pDriverObj);
#if _WIN64
	NTSTATUS status = STATUS_SUCCESS;
	PLDR_DATA_TABLE_ENTRY64 ldr;

	pDriverObj->DriverUnload = DriverUnload;
	//绕过MmVerifyCallbackFunction。
	ldr = (PLDR_DATA_TABLE_ENTRY64)pDriverObj->DriverSection;
	ldr->Flags |= 0x20;
	ProcessDriverEntry();
	FileDriverEntry();
	RegeditDriverEntry();
#else
	NTSTATUS status = STATUS_SUCCESS;
	PLDR_DATA_TABLE_ENTRY32 ldr;

	pDriverObj->DriverUnload = DriverUnload;
	//绕过MmVerifyCallbackFunction。
	ldr = (PLDR_DATA_TABLE_ENTRY32)pDriverObj->DriverSection;
	ldr->Flags |= 0x20;
	ProcessDriverEntry();
	FileDriverEntry();
	RegeditDriverEntry();
#endif

	return STATUS_SUCCESS;
}
NTSTATUS DriverUnload(_In_ PDRIVER_OBJECT pDriverObj)
{
	UNREFERENCED_PARAMETER(pDriverObj);
	ProcessDriverUnload();
	FileUnloadDriver();
	RegeditUnloadDriver();
	return STATUS_SUCCESS;
}