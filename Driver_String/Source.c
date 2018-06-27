#include "ntddk.h"

VOID Unload(IN PDRIVER_OBJECT DriverObject) {
	DbgPrint("driver unload \n");

}
NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath) //main function
{	
	UNICODE_STRING string1 = RTL_CONSTANT_STRING(L"HELLO DRIVER");      // W CHAR STRING CREATED USING RTL INITIALIZER
	DbgPrint("%wZ", &string1);                                          // string printed
	UNICODE_STRING string2 = { 0 };
	RtlInitUnicodeString(&string2, L"HELLO DRIVER");
	UNICODE_STRING string3;
	WCHAR strbuf[120];
	string3.Buffer = strbuf;
	string3.Length = string3.MaximumLength = wcslen(L"HELLO DRIVER") * sizeof(WCHAR);   
	// What is the buffer array
	// doubt--- parameter of wcslen can be array itself??? 
	wcscpy(string3.Buffer, L"HELLO DRIVER");
	
	
	WCHAR BUff[60] = { 0 };												// for copying the string
	UNICODE_STRING sourcestring = {L"DHRUV"};
	UNICODE_STRING deststring = { 0 };
	deststring.Buffer = BUff;
	deststring.Length = deststring.MaximumLength = 60;
	RtlCopyUnicodeString(&deststring, &sourcestring);
	DbgPrint("%wZ", &deststring);
	
	// upper case
	RtlUpcaseUnicodeString(&deststring, &sourcestring, TRUE);
	DbgPrint("%wZ", &deststring);
	RtlFreeUnicodeString(&deststring);
	DriverObject->DriverUnload = Unload;
	DbgPrint("hello driver \r\n");  //printf
	return STATUS_SUCCESS;

}