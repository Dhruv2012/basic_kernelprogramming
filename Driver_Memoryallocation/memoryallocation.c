#include "ntddk.h"
#define Mytag 'dhruv'
VOID Unload(IN PDRIVER_OBJECT DriverObject) {
	DbgPrint("driver unload \n");

}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath) //main function
{
	UNICODE_STRING sourcestring = RTL_CONSTANT_STRING(L"memory allocation begins");
	UNICODE_STRING deststring = { 0 };
	ULONG length;
	DriverObject->DriverUnload = Unload;
	//DbgPrint("hello driver \r\n");  //printf
	length = sourcestring.Length;
	deststring.Buffer=(PCHAR)ExAllocatePoolWithTag(NonPagedPool, length, Mytag);   // MEMORY ALLOCATION-PAGED OR NONPAGED
	RtlZeroMemory(deststring.Buffer, length);
	
	if (NULL != deststring.Buffer)                                                  // SUCCESSFUL MEMORY ALLOCATION
	{
		deststring.Length = deststring.MaximumLength = length;
		RtlCopyMemory(deststring.Buffer, sourcestring.Buffer, length);     
		RtlMoveMemory(deststring.Buffer, sourcestring.Buffer, length);              // if addresses overlap
		/*
		
		
		TROBLESHOOTING LEFT IN CHANGING THE POOL HEADER MEMORY PART-2
		
		*/
		DbgPrint("the string is %wZ \r\n", &deststring);
		ExFreePool(deststring.Buffer);

	}
	return STATUS_SUCCESS;

}