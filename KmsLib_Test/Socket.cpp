
// Author / Auteur		KMS -	Martin Dubois, ing.
// Product / Produit	KmsBase
// File / Fichier		KmsLib_Test/Socket.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== KmsBase ============================================================
#include <KmsLib/Exception.h>
#include <KmsTest.h>

#include <KmsLib/Socket.h>

// Test
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(Socket_Base)

	char lBuffer[32];

	unsigned int lSize_byte;

	KmsLib::Socket lS0;

	KMS_TEST_ASSERT(NULL	!= lS0.GetInternal		());
	KMS_TEST_ASSERT(0		== lS0.GetLocalAddress	());
	KMS_TEST_ASSERT(0		== lS0.GetLocalPort		());

	try
	{
		lS0.CreateBindAndListen();
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_NETWORK_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	KmsLib::Socket::Thread_Init();

	KmsLib::Socket lS1;

	lS1.Create();

	try
	{
		KmsLib::Socket lS2(lS1.Accept());
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_NETWORK_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	try
	{
		lSize_byte = lS1.Receive(lBuffer, sizeof(lBuffer));
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_NETWORK_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	try
	{
		lS1.Send(lBuffer, sizeof(lBuffer));
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_NETWORK_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	KmsLib::Socket lS3;

	lS3.CreateBindAndListen();

	KMS_TEST_ASSERT(0 != lS3.GetLocalPort());

	try
	{
		lS3.BindAndListen();
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_NETWORK_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	KmsLib::Socket lS4;

	lS4.Create();

	KMS_TEST_ASSERT(!lS4.Connect(0x08080808, 80));

	// www.kms-quebec.com = 192.99.5.135
	// KMS_TEST_ASSERT(lS4.Connect(0x870563c0, 80));

	KmsLib::Socket::Thread_Cleanup();

	try
	{
		KmsLib::Socket::Thread_Cleanup();
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_NETWORK_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

KMS_TEST_END
