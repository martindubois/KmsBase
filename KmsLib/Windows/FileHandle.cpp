
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	KmsLib/Windows/FileHandle.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Windows ============================================================
#include <Windows.h>

// ===== Interface ==========================================================
#include <KmsLib/Exception.h>

#include <KmsLib/Windows/FileHandle.h>

namespace KmsLib
{

	namespace Windows
	{

		// Public
		/////////////////////////////////////////////////////////////////////

		// Constructeur par defaut
		FileHandle::FileHandle() : mHandle(INVALID_HANDLE_VALUE)
		{
		}

		// Destructeur
		//
		// Exception : KmsLib::Exception
		FileHandle::~FileHandle()
		{
			if (INVALID_HANDLE_VALUE != mHandle)
			{
				Close();
			}
		}

		// Operateur de convertion
		FileHandle::operator HANDLE ()
		{
			assert(INVALID_HANDLE_VALUE != mHandle);

			return mHandle;
		}

		// Void la documentation de la fonction CloseHandle sur le site de
		// Microsoft.
		//
		// Exception : KmsLib::Exception
		void FileHandle::Close()
		{
			assert(INVALID_HANDLE_VALUE != mHandle);

			BOOL lRet = ::CloseHandle(mHandle);

			mHandle = INVALID_HANDLE_VALUE;

			if (!lRet)
			{
				// PAS TESTE : Difficile de faire echouer CloseHandle.
				throw Exception(Exception::CODE_IO_ERROR, "CloseHandle(  ) failed",
					NULL, __FILE__, __FUNCTION__, __LINE__, reinterpret_cast< unsigned int >( mHandle ));
			}
		}

		// Void la documentation de la fonction CreateFile sur le site de
		// Microsoft.
		//
		// aFileName			: [in]
		// aDesiredAccess		:
		// aSharedMode			:
		// aCreationDisposition	:
		// aFlagsAndAttributes	:
		//
		// Exception : KmsLib::Exception
		void FileHandle::Create(const char * aFileName, DWORD aDesiredAccess, DWORD aSharedMode, DWORD aCreationDisposition, DWORD aFlagsAndAttributes)
		{
			assert(NULL != aFileName);
			assert(0 != aDesiredAccess);

			if (INVALID_HANDLE_VALUE != mHandle)
			{
				Close();
			}

			assert(INVALID_HANDLE_VALUE == mHandle);

			mHandle = CreateFile(aFileName, aDesiredAccess, aSharedMode, NULL, aCreationDisposition, aFlagsAndAttributes, NULL);
			if (INVALID_HANDLE_VALUE == mHandle)
			{
				char lMessage[2048];

				sprintf_s(lMessage, sizeof(lMessage), "CreateFile( \"%s\", 0x%08x, 0x%08x, , 0x%08x, 0x%08x,  ) failed",
					aFileName, aDesiredAccess, aSharedMode, aCreationDisposition, aFlagsAndAttributes);

				throw new Exception(Exception::CODE_IO_ERROR, "CreateFile( , , , , , ,  ) failed",
					lMessage, __FILE__, __FUNCTION__, __LINE__, reinterpret_cast< unsigned int >( aFileName ) );
			}
		}

		// Voir la documentation de la fonction ReadFile sur le site de
		// Microsoft.
		//
		// aOut				: [out]
		// aOutSize_byte	:
		//
		// Exception : KmsLib::Exception
		unsigned int FileHandle::Read(void * aOut, unsigned int aOutSize_byte)
		{
			assert(NULL !=	aOut			);
			assert(0	<	aOutSize_byte	);

			assert(INVALID_HANDLE_VALUE != mHandle);

			DWORD lInfo_byte;

			if (!ReadFile(mHandle, aOut, aOutSize_byte, &lInfo_byte, NULL))
			{
				char lMessage[2048];

				sprintf_s(lMessage, sizeof(lMessage), "ReadFile( 0x%08x, , %u bytes, ,  ) failed",
					reinterpret_cast<unsigned int>(mHandle), aOutSize_byte);

				throw new Exception(Exception::CODE_IO_ERROR, "ReadFile( , , , ,  ) failed",
					lMessage, __FILE__, __FUNCTION__, __LINE__, 0);
			}

			assert(aOutSize_byte >= lInfo_byte);

			return lInfo_byte;
		}

		// Voir la documentation de la fonction WriteFile sur le site de
		// Microsoft.
		//
		// aIn			: [in]
		// aInSize_byte	:
		//
		// Exception : KmsLib::Exception
		void FileHandle::Write(const void * aIn, unsigned int aInSize_byte)
		{
			assert(NULL != aIn);
			assert(NULL != aInSize_byte);

			assert(INVALID_HANDLE_VALUE != mHandle);

			DWORD lInfo_byte;

			if (!WriteFile(mHandle, aIn, aInSize_byte, &lInfo_byte, NULL))
			{
				char lMessage[2048];

				sprintf_s(lMessage, sizeof(lMessage), "WriteFile( 0x%08x, , %u bytes, ,  ) failed",
					reinterpret_cast<unsigned int>(mHandle), aInSize_byte);

				throw new Exception(Exception::CODE_IO_ERROR, "WriteFile( , , , ,  ) failed",
					lMessage, __FILE__, __FUNCTION__, __LINE__, 0);
			}

			// PAS TESTE : Modifier un fichier complexifierait le test.

			if (aInSize_byte != lInfo_byte)
			{
				char lMessage[2048];

				sprintf_s(lMessage, sizeof(lMessage), "WriteFile did not write all data (Handle = 0x%08x, To write = %u byte, Written = %u byte)",
					reinterpret_cast<unsigned int>(mHandle), aInSize_byte, lInfo_byte);

				throw new Exception(Exception::CODE_IO_ERROR, "WriteFile did not write all the data",
					lMessage, __FILE__, __FUNCTION__, __LINE__, lInfo_byte);
			}
		}

	}

}
