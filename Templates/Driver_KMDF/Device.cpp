
// Auteur	:	KMS -	Martin Dubois, ing.
// Client	:	TODO
// Projet	:	TODO
// Fichier	:	TODO/Device.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== WDK ================================================================
#include <ntddk.h>
#include <wdf.h>

// ===== Common =============================================================
#include "./TodoInterface.h"
// TODO : Changer le chemin

// ===== Local ==============================================================
#include "Device.h"
#include "Project.h"

#pragma alloc_text(PAGE, Device_Create)

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
	// TODO : Ajouter les champs necessaire;

	unsigned char * mReserved0[4096];
}
DeviceContext;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DeviceContext, GetDeviceContext)

// Declaration des fonctions statique
/////////////////////////////////////////////////////////////////////////////

// ===== Points d'entree ====================================================

extern "C"
{
	static EVT_WDF_OBJECT_CONTEXT_CLEANUP		Cleanup			;
	static EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL	DeviceControl	;
	static EVT_WDF_DEVICE_D0_ENTRY				EnterD0			;
	static EVT_WDF_DEVICE_D0_EXIT				ExitD0			;
	static EVT_WDF_DEVICE_PREPARE_HARDWARE		PrepareHardware	;
	static EVT_WDF_DEVICE_RELEASE_HARDWARE		ReleaseHardware	;

	// TODO : Ajouter d'autre gestionnaire d'evennement, si necessaire.
}

#pragma alloc_text( PAGE, Cleanup )

// Fonctions
/////////////////////////////////////////////////////////////////////////////

// aDeviceInit	: [in,out]
//
// Retour :
//  STATUS_SUCCESS
NTSTATUS Device_Create( PWDFDEVICE_INIT aDeviceInit )
{
	DbgPrint(PREFIX __FUNCTION__ "( 0x%08x )\n", reinterpret_cast< ULONG >(aDeviceInit));

	WDF_PNPPOWER_EVENT_CALLBACKS lPnpPower;

	WDF_PNPPOWER_EVENT_CALLBACKS_INIT(&lPnpPower);

	lPnpPower.EvtDeviceD0Entry			= EnterD0			;
	lPnpPower.EvtDeviceD0Exit			= ExitD0			;
	lPnpPower.EvtDevicePrepareHardware	= PrepareHardware	;
	lPnpPower.EvtDeviceReleaseHardware	= ReleaseHardware	;

	// TODO : Initialiser les autre membres de lPnpPower si necessaire

	WdfDeviceInitSetPnpPowerEventCallbacks(aDeviceInit, &lPnpPower);

	WdfDeviceInitSetIoType(aDeviceInit, WdfDeviceIoBuffered);
	// TODO : Changer le type d'IO si necessaire

	WDF_OBJECT_ATTRIBUTES lAttr;

	WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&lAttr, DeviceContext);

	lAttr.EvtCleanupCallback	= Cleanup;

	lAttr.SynchronizationScope	= WdfSynchronizationScopeDevice;

	WDFDEVICE lDevice;

	NTSTATUS lResult = WdfDeviceCreate(&aDeviceInit, &lAttr, &lDevice);
	if (NT_SUCCESS(lResult))
	{
		DeviceContext * lThis = GetDeviceContext(lDevice);

		memset(lThis, 0, sizeof(DeviceContext));

		// TODO : Initialiser le context

		// TODO : Initialiser un objet WDFINTERRUPT, si necessaire

		// TODO :	Specifier les requis d'allignement pour les buffer DMA,
		//			si necessaire

		WDF_IO_QUEUE_CONFIG lConfig;

		WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&lConfig, WdfIoQueueDispatchSequential);
		// TODO : Changer le type de queue au besoin

		lConfig.EvtIoDeviceControl = DeviceControl;

		// TODO : Initializer les autres membre de lConfig, si necessaire

		WDFQUEUE lQueue;

		lResult = WdfIoQueueCreate(lDevice, &lConfig, WDF_NO_OBJECT_ATTRIBUTES, &lQueue);
		if (NT_SUCCESS(lResult))
		{
			lResult = WdfDeviceCreateDeviceInterface(lDevice, & TODO_INTERFACE, NULL);
			if (!NT_SUCCESS(lResult))
			{
				DbgPrint(PREFIX __FUNCTION__ " - WdfDeviceCreateDeviceInterface( 0x%08x, ,  ) failed returning 0x%08x\n",
					reinterpret_cast< ULONG >(lDevice), lResult);
			}
		}
		else
		{
			DbgPrint(PREFIX __FUNCTION__ " - WdfQueueCreate( 0x%08x, , ,  ) failed returning 0x%08x\n",
				reinterpret_cast< ULONG >( lDevice ), lResult);
		}
	}
	else
	{
		DbgPrint(PREFIX __FUNCTION__ " - WdfDeviceCreate( , ,  ) failed returning 0x%08x\n", lResult );
	}

	return lResult;
}

// Fonctions statiques
/////////////////////////////////////////////////////////////////////////////

// ===== Points d'entrees ===================================================

VOID Cleanup(WDFOBJECT aDevice)
{
	DbgPrint(PREFIX __FUNCTION__ "( 0x%08x )\n", reinterpret_cast< ULONG >(aDevice));

	(void)(aDevice);

	// TODO :
}

VOID DeviceControl( WDFQUEUE aQueue, WDFREQUEST aRequest, size_t aOutSize_byte, size_t aInSize_byte, ULONG aCode )
{
	DbgPrint(PREFIX __FUNCTION__ "( 0x%08x, 0x%08x, %u bytes, %u bytes, 0x%08x )\n",
		reinterpret_cast<ULONG>(aQueue), reinterpret_cast<ULONG>(aRequest), aOutSize_byte, aInSize_byte, aCode);

	ASSERT(NULL != aQueue);

	(void)(aRequest			);
	(void)(aOutSize_byte	);
	(void)(aInSize_byte		);
	(void)(aCode			);

	DeviceContext * lThis = GetDeviceContext(WdfIoQueueGetDevice(aQueue));
	ASSERT(NULL != lThis);

	(void)(lThis); // TODO : Retirer cette ligne

	switch (aCode)
	{
	case TODO_IOCTL_TODO :

		// TODO :

		break;

	default:
		WdfRequestComplete(aRequest, STATUS_INVALID_DEVICE_REQUEST);
	}
}

NTSTATUS EnterD0( WDFDEVICE aDevice, WDF_POWER_DEVICE_STATE aPreviousState )
{
	DbgPrint(PREFIX __FUNCTION__ "( 0x%08x, 0x%08x )\n", reinterpret_cast<ULONG>(aDevice), aPreviousState);

	ASSERT(NULL != aDevice);

	(void)(aPreviousState	);

	DeviceContext * lThis = GetDeviceContext(aDevice);
	ASSERT(NULL != lThis);

	(void)(lThis); // TODO : Retirer cette ligne

	// TODO :

	return STATUS_SUCCESS;
}

NTSTATUS ExitD0( WDFDEVICE aDevice, WDF_POWER_DEVICE_STATE aTargetState )
{
	DbgPrint(PREFIX __FUNCTION__ "( 0x%08x, 0x%08x )\n", reinterpret_cast<ULONG>(aDevice), aTargetState);

	ASSERT(NULL != aDevice);

	(void)(aTargetState	);

	DeviceContext * lThis = GetDeviceContext(aDevice);
	ASSERT(NULL != lThis);

	(void)(lThis); // TODO : Retirer cette ligne

	// TODO :

	return STATUS_SUCCESS;
}

NTSTATUS PrepareHardware( WDFDEVICE aDevice, WDFCMRESLIST aRessourcesRaw, WDFCMRESLIST aRessourcesTranslated )
{
	DbgPrint(PREFIX __FUNCTION__ "( 0x%08x, 0x%08x, 0x%08x )\n",
		reinterpret_cast<ULONG>(aDevice), reinterpret_cast<ULONG>(aRessourcesRaw), reinterpret_cast<ULONG>(aRessourcesTranslated));

	ASSERT(NULL != aDevice);

	(void)(aRessourcesRaw			);
	(void)(aRessourcesTranslated	);

	DeviceContext * lThis = GetDeviceContext(aDevice);
	ASSERT(NULL != lThis);

	(void)(lThis); // TODO : Retirer cette ligne

	// TODO :
	
	return STATUS_SUCCESS;
}

NTSTATUS ReleaseHardware( WDFDEVICE aDevice, WDFCMRESLIST aRessourcesTranslated )
{
	DbgPrint(PREFIX __FUNCTION__ "( 0x%08x, 0x%08x )\n",
		reinterpret_cast<ULONG>(aDevice), reinterpret_cast<ULONG>(aRessourcesTranslated));

	ASSERT(NULL != aDevice);

	(void)(aRessourcesTranslated	);

	DeviceContext * lThis = GetDeviceContext(aDevice);
	ASSERT(NULL != lThis);

	(void)(lThis); // TODO : Retirer cette ligne

	// TODO :

	return STATUS_SUCCESS;
}