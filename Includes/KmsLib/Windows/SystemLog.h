
// Author / Auteur	:	Kms -	Martin Dubois, ing
// Project / Projet	:	KmsBase
// File / Fichier	:	Includes/KmsLib/Windows/SystemLog.h

#pragma once

namespace KmsLib
{
	namespace Windows
	{

		// Class / Classe
		/////////////////////////////////////////////////////////////////////

		class SystemLog
		{

		public:

			SystemLog(const char * aLogName, const char * aSourceName);

			~SystemLog();

			bool	IsConfigured()	const;

			void	Configure	(const char * aMessageFile);
			void	Unconfigure	();

			void	LogEvent	(WORD aType, WORD aCategory, DWORD aEventId, WORD aStringCount, DWORD aDataSize_byte, LPCTSTR * aString, LPVOID aData);

		private:

			void	Deregister	();
			void	Register	();

			HANDLE			mHandle		;
			const char	  * mLogName	;
			const char    * mSourceName	;

		};
	}
}
