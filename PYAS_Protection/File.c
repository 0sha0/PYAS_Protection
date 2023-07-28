#include "Drvier_File.h"

PVOID  CallBackHandle = NULL;
NTSTATUS FileDriverEntry()
{
    ProtectFileByObRegisterCallbacks();
    return STATUS_SUCCESS;
}
NTSTATUS ProtectFileByObRegisterCallbacks()
{
    OB_CALLBACK_REGISTRATION  CallBackReg;
    OB_OPERATION_REGISTRATION OperationReg;
    NTSTATUS  Status;

    EnableObType(*IoFileObjectType);      //�����ļ�����ص�
    memset(&CallBackReg, 0, sizeof(OB_CALLBACK_REGISTRATION));
    CallBackReg.Version = ObGetFilterVersion();
    CallBackReg.OperationRegistrationCount = 1;
    CallBackReg.RegistrationContext = NULL;
    RtlInitUnicodeString(&CallBackReg.Altitude, L"321000");
    memset(&OperationReg, 0, sizeof(OB_OPERATION_REGISTRATION)); //��ʼ���ṹ�����


    OperationReg.ObjectType = IoFileObjectType;
    OperationReg.Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;

    OperationReg.PreOperation = (POB_PRE_OPERATION_CALLBACK)&PreCallBack; //������ע��һ���ص�����ָ��
    CallBackReg.OperationRegistration = &OperationReg; //ע����һ�����   ���ṹ����Ϣ�����ṹ��
    Status = ObRegisterCallbacks(&CallBackReg, &CallBackHandle);
    if (!NT_SUCCESS(Status))
    {
        Status = STATUS_UNSUCCESSFUL;
    }
    else
    {
        Status = STATUS_SUCCESS;
    }
    return Status;
}

OB_PREOP_CALLBACK_STATUS PreCallBack(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION OperationInformation)
{
    UNICODE_STRING uniDosName;
    UNICODE_STRING uniFilePath;
    PFILE_OBJECT FileObject = (PFILE_OBJECT)OperationInformation->Object;
    HANDLE CurrentProcessId = PsGetCurrentProcessId();
    if (OperationInformation->ObjectType != *IoFileObjectType)
    {
        return OB_PREOP_SUCCESS;
    }
    //������Чָ��
    if (FileObject->FileName.Buffer == NULL ||
        !MmIsAddressValid(FileObject->FileName.Buffer) ||
        FileObject->DeviceObject == NULL ||
        !MmIsAddressValid(FileObject->DeviceObject))
    {
        return OB_PREOP_SUCCESS;
    }
    uniFilePath = GetFilePathByFileObject(FileObject);
    if (uniFilePath.Buffer == NULL || uniFilePath.Length == 0)
    {
        return OB_PREOP_SUCCESS;
    }
    if (wcsstr(uniFilePath.Buffer, L"PYAS.exe"))
    {
        if (FileObject->DeleteAccess == TRUE || FileObject->WriteAccess == TRUE)
        {
            if (OperationInformation->Operation == OB_OPERATION_HANDLE_CREATE)
            {
                OperationInformation->Parameters->CreateHandleInformation.DesiredAccess = 0;
            }
            if (OperationInformation->Operation == OB_OPERATION_HANDLE_DUPLICATE)
            {
                OperationInformation->Parameters->DuplicateHandleInformation.DesiredAccess = 0;
            }
        }
    }

    if (wcsstr(uniFilePath.Buffer, L"PYAS.sys"))
    {
        if (FileObject->DeleteAccess == TRUE || FileObject->WriteAccess == TRUE)
        {
            if (OperationInformation->Operation == OB_OPERATION_HANDLE_CREATE)
            {
                OperationInformation->Parameters->CreateHandleInformation.DesiredAccess = 0;
            }
            if (OperationInformation->Operation == OB_OPERATION_HANDLE_DUPLICATE)
            {
                OperationInformation->Parameters->DuplicateHandleInformation.DesiredAccess = 0;
            }
        }
    }

    RtlVolumeDeviceToDosName(FileObject->DeviceObject, &uniDosName);
    DbgPrint("PID : %ld File : %wZ  %wZ\r\n", (ULONG64)CurrentProcessId, &uniDosName, &uniFilePath);
    return OB_PREOP_SUCCESS;
}
UNICODE_STRING GetFilePathByFileObject(PVOID FileObject)
{
    POBJECT_NAME_INFORMATION ObjetNameInfor;
    if (NT_SUCCESS(IoQueryFileDosDeviceName((PFILE_OBJECT)FileObject, &ObjetNameInfor)))
    {
        return ObjetNameInfor->Name;
    }
}
VOID EnableObType(POBJECT_TYPE ObjectType)
{
    POBJECT_TYPE_TEMP  ObjectTypeTemp = (POBJECT_TYPE_TEMP)ObjectType;
    ObjectTypeTemp->TypeInfo.SupportsObjectCallbacks = 1;
}
VOID FileUnloadDriver()
{
    if (CallBackHandle != NULL)
    {
        ObUnRegisterCallbacks(CallBackHandle);
    }
    DbgPrint("UnloadDriver\r\n");
}
