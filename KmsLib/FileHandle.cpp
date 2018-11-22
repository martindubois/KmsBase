
// Author   KMS - Martin Dubois, ing.
// Product  KmsBase
// File     KmsLib/FileHandle.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Windows ============================================================
#include <Windows.h>

// ===== Interface ==========================================================
#include <KmsLib/Exception.h>

#include <KmsLib/FileHandle.h>

namespace KmsLib
{

	// Public
	/////////////////////////////////////////////////////////////////////////

	FileHandle::FileHandle() : mHandle(INVALID_HANDLE_VALUE)
	{
	}

	FileHandle::~FileHandle()
	{
		if (INVALID_HANDLE_VALUE != mHandle)
		{
			Close();
		}
	}

	FileHandle::operator HANDLE ()
	{
		assert(INVALID_HANDLE_VALUE != mHandle);

		return mHandle;
	}

	void FileHandle::Close()
	{
		assert(INVALID_HANDLE_VALUE != mHandle);

		BOOL lRet = ::CloseHandle(mHandle);

		mHandle = INVALID_HANDLE_VALUE;

		if (!lRet)
		{
			// PAS TESTE : Difficile de faire echouer CloseHandle.
			throw Exception(Exception::CODE_CLOSE_HANDLE_ERROR, "CloseHandle(  ) failed",
				NULL, __FILE__, __FUNCTION__, __LINE__, 0);
		}
	}

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

			throw new Exception(Exception::CODE_CREATE_FILE_ERROR, "CreateFile( , , , , , ,  ) failed",
				lMessage, __FILE__, __FUNCTION__, __LINE__, 0 );
		}
	}

	unsigned int FileHandle::Read(void * aOut, unsigned int aOutSize_byte)
	{
		assert(NULL !=	aOut			);
		assert(0	<	aOutSize_byte	);

        assert(INVALID_HANDLE_VALUE != mHandle);

		DWORD lInfo_byte;

		if (!ReadFile(mHandle, aOut, aOutSize_byte, &lInfo_byte, NULL))
		{
			char lMessage[2048];

			sprintf_s(lMessage, sizeof(lMessage), "ReadFile( , , %u bytes, ,  ) failed",
				aOutSize_byte);

			throw new Exception(Exception::CODE_READ_FILE_ERROR, "ReadFile( , , , ,  ) failed",
				lMessage, __FILE__, __FUNCTION__, __LINE__, 0);
		}

		assert(aOutSize_byte >= lInfo_byte);

		return lInfo_byte;
	}

	void FileHandle::Write(const void * aIn, unsigned int aInSize_byte)
	{
		assert(NULL != aIn);
		assert(NULL != aInSize_byte);

		assert(INVALID_HANDLE_VALUE != mHandle);
        
        DWORD lInfo_byte;

		if (!WriteFile(mHandle, aIn, aInSize_byte, &lInfo_byte, NULL))
		{
			char lMessage[2048];

			sprintf_s(lMessage, sizeof(lMessage), "WriteFile( , , %u bytes, ,  ) failed",
				aInSize_byte);

			throw new Exception(Exception::CODE_WRITE_FILE_ERROR, "WriteFile( , , , ,  ) failed",
				lMessage, __FILE__, __FUNCTION__, __LINE__, 0);
		}

		// PAS TESTE : Modifier un fichier complexifierait le test.

        if (aInSize_byte != lInfo_byte)
		{
			char lMessage[2048];

			sprintf_s(lMessage, sizeof(lMessage), "WriteFile did not write all data (To write = %u byte, Written = %u byte)",
				aInSize_byte, lInfo_byte);

			throw new Exception(Exception::CODE_WRITE_FILE_ERROR, "WriteFile did not write all the data",
				lMessage, __FILE__, __FUNCTION__, __LINE__, lInfo_byte);
		}
	}

}
