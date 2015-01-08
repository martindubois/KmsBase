
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	Includes/KmsDriverLib/Device.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== KmsDriverLib =======================================================
#include <KmsDriverLib/Object.h>

namespace KmsDriverLib
{

	// Points d'entrees
	/////////////////////////////////////////////////////////////////////////

	extern "C"
	{
		static EVT_WDF_OBJECT_CONTEXT_CLEANUP		Cleanup			;
		static EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL	DeviceControl	;
		static EVT_WDF_DEVICE_D0_ENTRY				EnterD0			;
		static EVT_WDF_DEVICE_D0_EXIT				ExitD0			;
		static EVT_WDF_DEVICE_PREPARE_HARDWARE		PrepareHardware	;
		static EVT_WDF_DEVICE_RELEASE_HARDWARE		ReleaseHardware	;
	}

	// Class
	/////////////////////////////////////////////////////////////////////////

	class Device : public Object
	{

	public:

		Device();

		virtual NTSTATUS	Initialize(WDFDEVICE_INIT * aInit);

		operator WDFDEVICE ();

		virtual void		Cleanup			();
		virtual void		DeviceControl	(WDFQUEUE aQueue, WDFREQUEST aRequest, size_t aOutSize_byte, size_t aInSize_byte, ULONG aCode);
		virtual NTSTATUS	EnterD0			(WDF_POWER_DEVICE_STATE aState aPreviousState	);
		virtual NTSTATUS	ExitD0			(WDF_POWER_DEVICE_STATE aTargerState			);
		virtual NTSTATUS	PrepareHardware	(WDFCMRESLIST aResourcesRaw, WDFCMRESLIST aResourcesTranslated);
		virtual NTSTATUS	ReleaseHardware	(WDFCMRESLIST aResourcesTranslated);

	protected:

		WDFDEVICE	mWdfDevice;

	private:

	};

}