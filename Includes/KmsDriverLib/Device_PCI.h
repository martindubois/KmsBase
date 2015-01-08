
// Auteur	:	KMS -	Martin Dubois, ing.
// Project	:	KmsBase
// Fichier	:	Includes/KmsDriverLib/Device_PCI.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== KmsDriverLib =======================================================
#include <KmsDriverLib/Device.h>

namespace KmsDriverLib
{

	// Class
	/////////////////////////////////////////////////////////////////////////

	class Device_PCI : public Device
	{

	public:

		Device_PCI();

		// ===== Device =====================================================

		virtual NTSTATUS	PrepareHardware(WDFCMRESLIST aResourcesRaw, WDFCMRESLIST aResourcesTranslated);
		virtual NTSTATUS	ReleaseHardware(WDFCMRESLIST aResourcesTranslated);

	protected:

		typedef struct
		{
			PHYSICAL_ADDRESS	mPhysicalAddress;
			volatile void     * mSystemAddress	;
			unsigned int		mSize_byte		;
		}
		BaseAddressRegisterInfo;

		const BaseAddressRegisterInfo & GetBaseAddressRegisterInfo	(unsigned int aIndex) const;
		unsigned int					GetBaseAddressRegisterQty	() const;

	private:

		BaseAddressRegisterInfo mBARs[6];
		unsigned int			mBARQty;

	};

}
