
#ifndef CXX_FILEPROTECTX64_H
#define CXX_FILEPROTECTX64_H
#include <ntifs.h>
#include <devioctl.h>

typedef struct _OBJECT_TYPE_INITIALIZER
{
    UINT16       Length;
    union
    {
        UINT8        ObjectTypeFlags;
        struct
        {
            UINT8        CaseInsensitive : 1;
            UINT8        UnnamedObjectsOnly : 1;
            UINT8        UseDefaultObject : 1;
            UINT8        SecurityRequired : 1;
            UINT8        MaintainHandleCount : 1;
            UINT8        MaintainTypeList : 1;
            UINT8        SupportsObjectCallbacks : 1;
        };
    };
    ULONG32      ObjectTypeCode;
    ULONG32      InvalidAttributes;
    struct _GENERIC_MAPPING GenericMapping;
    ULONG32      ValidAccessMask;
    ULONG32      RetainAccess;
    enum _POOL_TYPE PoolType;
    ULONG32      DefaultPagedPoolCharge;
    ULONG32      DefaultNonPagedPoolCharge;
    PVOID        DumpProcedure;
    PVOID        OpenProcedure;
    PVOID         CloseProcedure;
    PVOID         DeleteProcedure;
    PVOID         ParseProcedure;
    PVOID        SecurityProcedure;
    PVOID         QueryNameProcedure;
    PVOID         OkayToCloseProcedure;
}OBJECT_TYPE_INITIALIZER, * POBJECT_TYPE_INITIALIZER;

typedef struct _OBJECT_TYPE_TEMP
{
    struct _LIST_ENTRY TypeList;
    struct _UNICODE_STRING Name;
    VOID* DefaultObject;
    UINT8        Index;
    UINT8        _PADDING0_[0x3];
    ULONG32      TotalNumberOfObjects;
    ULONG32      TotalNumberOfHandles;
    ULONG32      HighWaterNumberOfObjects;
    ULONG32      HighWaterNumberOfHandles;
    UINT8        _PADDING1_[0x4];
    struct _OBJECT_TYPE_INITIALIZER TypeInfo;
    ULONG64 TypeLock;
    ULONG32      Key;
    UINT8        _PADDING2_[0x4];
    struct _LIST_ENTRY CallbackList;
}OBJECT_TYPE_TEMP, * POBJECT_TYPE_TEMP;

VOID EnableObType(POBJECT_TYPE ObjectType);
UNICODE_STRING  GetFilePathByFileObject(PVOID FileObject);
OB_PREOP_CALLBACK_STATUS PreCallBack(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION OperationInformation);
NTSTATUS ProtectFileByObRegisterCallbacks();
#endif    


#ifndef CXX_FILEPROTECTX64_H
#include "FileProtectX64.h"
#endif