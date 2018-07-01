#include "ntddk.h"

BOOLEAN signal = FALSE;
KEVENT Event;
PVOID ThreadOBJ = NULL;

VOID Unload(IN PDRIVER_OBJECT DriverObject) {
	signal = TRUE;					// SIGNAL IS TRUE FOR THREAD TO EXIT
	KeSetEvent(&Event, 0, FALSE);   // TO SET THE THREAD TO SIGNALLED STATE
	KeWaitForSingleObject(ThreadOBJ, Executive, KernelMode, FALSE, NULL);
	ObDereferenceObject(ThreadOBJ);
	DbgPrint("driver unload \r\n");
	PsTerminateSystemThread(STATUS_SUCCESS);                                          // terminate thread when driver unloads
}

VOID exormus(IN PVOID Context) {
	for (;;) {
		if (signal == TRUE)
		{
			break;
		}
		KeWaitForSingleObject(&Event, Executive, KernelMode, 0, NULL);
		DbgPrint("my new thread \r\n");

		//do something
	}

EXIT:
	PsTerminateSystemThread(STATUS_SUCCESS);                                    // terminate thread process if creation is failed

}



NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath) //main function
{	
	NTSTATUS status;
	HANDLE Threadhandle;
	KeInitializeEvent(&Event, SynchronizationEvent, FALSE);

	DriverObject->DriverUnload = Unload;
	status = PsCreateSystemThread(&Threadhandle, 0, NULL, NULL, NULL, exormus, NULL);
	if (!NT_SUCCESS(status)) {
		PsTerminateSystemThread(STATUS_SUCCESS);                                    // terminate thread process if creation is failed
		DbgPrint("thread creation failed\r\n");
	}
	status=	ObReferenceObjectByHandle(Threadhandle, THREAD_ALL_ACCESS, NULL, KernelMode, &ThreadOBJ, NULL);
	if (!NT_SUCCESS(status)) {
		signal = TRUE;
	}
	KeSetEvent(&Event, 0, FALSE);
	ZwClose(Threadhandle);
	return STATUS_SUCCESS;

}
