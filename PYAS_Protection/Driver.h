
#include<ntifs.h>
#if _WIN64
//64λLDR_DATA_TABLE_ENTRY�ṹ��,�����ƹ�MmVerifyCallbackFunction����
typedef struct _LDR_DATA_TABLE_ENTRY64
{
	LIST_ENTRY64    InLoadOrderLinks;
	LIST_ENTRY64    InMemoryOrderLinks;
	LIST_ENTRY64    InInitializationOrderLinks;
	PVOID            DllBase;
	PVOID            EntryPoint;
	ULONG            SizeOfImage;
	UNICODE_STRING    FullDllName;
	UNICODE_STRING     BaseDllName;
	ULONG            Flags;
	USHORT            LoadCount;
	USHORT            TlsIndex;
	PVOID            SectionPointer;
	ULONG            CheckSum;
	PVOID            LoadedImports;
	PVOID            EntryPointActivationContext;
	PVOID            PatchInformation;
	LIST_ENTRY64    ForwarderLinks;
	LIST_ENTRY64    ServiceTagLinks;
	LIST_ENTRY64    StaticLinks;
	PVOID            ContextInformation;
	ULONG64            OriginalBase;
	LARGE_INTEGER    LoadTime;
} LDR_DATA_TABLE_ENTRY64, * PLDR_DATA_TABLE_ENTRY64;
#else
typedef struct _LDR_DATA_TABLE_ENTRY32
{
	LIST_ENTRY32    InLoadOrderLinks;
	LIST_ENTRY32    InMemoryOrderLinks;
	LIST_ENTRY32    InInitializationOrderLinks;
	PVOID            DllBase;
	PVOID            EntryPoint;
	ULONG            SizeOfImage;
	UNICODE_STRING    FullDllName;
	UNICODE_STRING     BaseDllName;
	ULONG            Flags;
	USHORT            LoadCount;
	USHORT            TlsIndex;
	PVOID            SectionPointer;
	ULONG            CheckSum;
	PVOID            LoadedImports;
	PVOID            EntryPointActivationContext;
	PVOID            PatchInformation;
	LIST_ENTRY32    ForwarderLinks;
	LIST_ENTRY32    ServiceTagLinks;
	LIST_ENTRY32    StaticLinks;
	PVOID            ContextInformation;
	ULONG32          OriginalBase;
	LARGE_INTEGER    LoadTime;
} LDR_DATA_TABLE_ENTRY32, * PLDR_DATA_TABLE_ENTRY32;
#endif

NTSTATUS DriverEntry
(
	_In_ PDRIVER_OBJECT PDO,
	_In_ PUNICODE_STRING STR
);

NTSTATUS DriverUnload
(
	_In_ PDRIVER_OBJECT pdo
);
NTSTATUS ProcessDriverEntry();
NTSTATUS ProcessDriverUnload();
NTSTATUS FileDriverEntry();
VOID FileUnloadDriver();
NTSTATUS RegeditDriverEntry();
NTSTATUS RegeditUnloadDriver();