
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	Includes/KmsLib/Windows/FileHandle.h

#pragma once

namespace KmsLib
{
	namespace Windows
	{

		// Class
		/////////////////////////////////////////////////////////////////////

		class FileHandle
		{

		public:

			FileHandle();

			virtual ~FileHandle();

			operator HANDLE ();

			bool	IsOpen() const;

			void Close();

			void Create(const char * aFileName, DWORD aDesiredAccess, DWORD aSharedMode, DWORD aCreationDisposition, DWORD aFlagsAndAttributes);

			unsigned int	Read(void * aOut, unsigned int aOutSize_byte);

			void Write(const void * aIn, unsigned int aInSize_byte);

		protected:

			HANDLE mHandle;

		private:

			FileHandle(const FileHandle &);

			const FileHandle & operator = (const FileHandle &);

		};

		// Public
		/////////////////////////////////////////////////////////////////////

		// Return :
		//  false	= Le fichier est ouvert
		//  true	= Le fichier n'est pas ouvert
		inline bool FileHandle::IsOpen() const
		{
			return (INVALID_HANDLE_VALUE != mHandle);
		}

	}

}
