
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	KmsLib_Test/Dump.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <KmsBase.h>

// ===== Windows ============================================================
#ifdef _KMS_WINDOWS_
	#include <Windows.h>
#endif // _KMS_WINDOWS_

// ===== Interface ==========================================================
#ifdef _KMS_LINUX_
	#include <KmsLib/Linux/Windows.h>
#endif // _KMS_LINUX_

#include <KmsTest.h>

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(Windows_Base)

	KMS_TEST_ASSERT( !	CopyFile( "DoNotExist"						, "Linux_Windows_Test0.txt", false	) );
	KMS_TEST_ASSERT(	CopyFile( "KmsLib_Test/Linux/Windows.cpp"	, "Linux_Windows_Test0.txt", false	) );
	KMS_TEST_ASSERT( !	CopyFile( "KmsLib_Test/Linux/Windows.cpp"	, "Linux_Windows_Test0.txt", true	) );

	WIN32_FIND_DATA lData	;
	HANDLE			lHandle	;

	lHandle = FindFirstFile( "DoNotExist", & lData );
	KMS_TEST_ASSERT( INVALID_HANDLE_VALUE == lHandle );

	lHandle = FindFirstFile( "KmsLib_Test", & lData );
	KMS_TEST_ASSERT( INVALID_HANDLE_VALUE != lHandle );

	KMS_TEST_ASSERT( 0 == strcmp( "KmsLib_Test", lData.cFileName )				);
	KMS_TEST_ASSERT( 0 != ( lData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )	);

	KMS_TEST_ASSERT( ! FindNextFile( lHandle, & lData ) );

	KMS_TEST_ASSERT( FindClose( lHandle ) );

	lHandle = FindFirstFile( "KmsLib_Test/Linux/?*.cpp", & lData );
	KMS_TEST_ASSERT( INVALID_HANDLE_VALUE != lHandle );

	KMS_TEST_ASSERT( 0 == strcmp( "Windows.cpp", lData.cFileName )				);
	KMS_TEST_ASSERT( 0 == (lData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )	);

	KMS_TEST_ASSERT( ! FindNextFile( lHandle, & lData ) );

	KMS_TEST_ASSERT( FindClose( lHandle ) );

	KMS_TEST_ASSERT( !	MoveFile( "DoNotExist", "Linux_Windows_Test0.txt" ) );

KMS_TEST_END

