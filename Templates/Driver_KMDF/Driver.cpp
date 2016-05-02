
// Auteur	KMS -	Martin Dubois, ing.
// Client	TODO
// Produit	TODO
// Fichier	TODO/Driver.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== WDK ================================================================
#include <ntddk.h>
#include <wdf.h>

// ===== Local ==============================================================
#include "Device.h"
#include "Project.h"

// Declaration des points d'entrees
/////////////////////////////////////////////////////////////////////////////

extern "C"
{
	EVT_WDF_DRIVER_DEVICE_ADD	AddDevice	;
	DRIVER_INITIALIZE			DriverEntry	;
}

#pragma alloc_text( INIT, DriverEntry	)
#pragma alloc_text( PAGE, AddDevice		)

// Points d'entrees
/////////////////////////////////////////////////////////////////////////////

NTSTATUS AddDevice( WDFDRIVER aDriver, PWDFDEVICE_INIT aDeviceInit )
{
	(void)(aDriver		);
	(void)(aDeviceInit	);

	DbgPrint(PREFIX __FUNCTION__ "( ,  )\n" );

	NTSTATUS lResult = Device_Create( aDeviceInit );

	return lResult;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT aDriverObject, PUNICODE_STRING aRegistryPath)
{
	ASSERT(NULL != aDriverObject);
	ASSERT(NULL != aRegistryPath);

	DbgPrint(PREFIX __FUNCTION__ "( , \"%S\" )\n",
		aRegistryPath->Buffer);

	WDF_DRIVER_CONFIG lConfig;

	WDF_DRIVER_CONFIG_INIT(&lConfig, AddDevice);

	WDF_OBJECT_ATTRIBUTES lAttr;

	WDF_OBJECT_ATTRIBUTES_INIT(&lAttr);

	// TODO :	Si necessaire, initialiser le membre EvtCleanupCallback de
	//			lAttr.

	WDFDRIVER lDriver;

	NTSTATUS lResult = WdfDriverCreate(aDriverObject, aRegistryPath, &lAttr, &lConfig, &lDriver);

	return lResult;
}
