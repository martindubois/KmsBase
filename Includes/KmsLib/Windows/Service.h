
// Author / Auteur	:	KMS -	Martin Dubois, ing.
// Project / Projet	:	KmsBase
// File / Fichier	:	Includes/KmsLib/Windows/Service.h

#pragma once

namespace KmsLib
{
	namespace Windows
	{

		// Class
		/////////////////////////////////////////////////////////////////////

		class Service
		{

		public:

			Service(const char * aServiceName);

			~Service();

			bool	IsEnabled	();
			bool	IsInstalled	();
			bool	IsRunning	();

			bool			GetDelayedAutoStart	();
			unsigned int	GetStartType		();

			void	SetDelayedAutoStart	(bool			aValue);
			void	SetStartType		(unsigned int	aValue);

			void	Create	(const char * aDisplayName, const char * aBinary);
			void	Delete	();
			void	Start	();

			void	Disable	();
			void	Enable	();

		private:

			void	ConnectAndOpenIfNeeded	();
			void	ConnectIfNeeded			();

			void	Connect	();
			void	Control	(DWORD aControl);
			void	Open	();
			void	Stop	();
			void	Wait	(DWORD aPending, DWORD aFinal);

			void	UpdateConfig	();
			void	UpdateStatus	();

			QUERY_SERVICE_CONFIG  * mConfig				;
			unsigned int            mConfigSize_byte	;
			SC_HANDLE				mHandle				;
			SC_HANDLE				mManager			;
			const char			  * mName				;
			SERVICE_STATUS_PROCESS	mStatus				;

		};

	}
}
