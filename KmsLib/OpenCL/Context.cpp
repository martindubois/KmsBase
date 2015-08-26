
// Author / Auteur		:	KMS	-	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	KmsLib/OpenCL/Context.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Includes ===========================================================
#include <KmsLib/Exception.h>
#include <KmsLib/OpenCL/Context.h>

namespace KmsLib
{
	namespace OpenCL
	{

		// Public
		/////////////////////////////////////////////////////////////////////

		Context::Context(const VECTOR_CLASS<cl::Device> & aDevices, cl_context_properties * aProperties, void(__stdcall * aNotify)(const char *, const void *, size_t, void *), void * aData)
		{
			assert(NULL != (&aDevices));

			cl_int lRet;

			(*dynamic_cast<cl::Context *>(this)) = cl::Context(aDevices, aProperties, aNotify, aData, &lRet);

			if (CL_SUCCESS != lRet)
			{
				char lMsg[1024];

				sprintf_s(lMsg, "cl::Context::Context( , 0x%08x, 0x%08x, 0x%08x,  ) failed indicating %d",
					reinterpret_cast<unsigned int>( aProperties ), reinterpret_cast<unsigned int>(aNotify), reinterpret_cast<unsigned int>(aData), lRet);

				throw new Exception(Exception::CODE_OPEN_CL_ERROR, "cl::Context::Context( , , , ,  ) failed",
					lMsg, __FILE__, __FUNCTION__, __LINE__, lRet);
			}
		}

		Context::Context(cl_device_type aDeviceType, cl_context_properties * aProperties, void(__stdcall * aNotify)(const char *, const void *, size_t, void *), void * aData)
		{
			cl_int lRet;

			(* dynamic_cast<cl::Context *>(this)) = cl::Context(aDeviceType, NULL, NULL, NULL, &lRet);
			if (CL_SUCCESS != lRet)
			{
				char lMsg[1024];

				sprintf_s(lMsg, "cl::Context::Context( 0x%08x, , , ,  ) failed returning %d", aDeviceType, lRet);

				throw new Exception(Exception::CODE_OPEN_CL_ERROR, "cl::Context::Context( , , , ,  ) failed",
					lMsg, __FILE__, __FUNCTION__, __LINE__, lRet);
			}
		}

		void Context::GetInfo(cl_context_info aName, cl_uint * aOut)
		{
			assert(NULL != aOut);

			cl_int lRet = getInfo(aName, aOut);
			if (CL_SUCCESS != lRet)
			{
				char lMsg[1024];

				sprintf_s(lMsg, "cl::Context::getInfo( 0x%08x,  ) failed returning %d", aName, lRet);

				throw new Exception(Exception::CODE_OPEN_CL_ERROR, "cl::Context::getInfo( ,  ) failed",
					lMsg, __FILE__, __FUNCTION__, __LINE__, lRet);
			}
		}

		void Context::GetInfo(cl_context_info aName, VECTOR_CLASS<cl::Device> * aOut)
		{
			assert(NULL != aOut);

			cl_int lRet = getInfo(aName, aOut);
			if (CL_SUCCESS != lRet)
			{
				char lMsg[1024];

				sprintf_s(lMsg, "cl::Context::getInfo( 0x%08x,  ) failed returning %d", aName, lRet);

				throw new Exception(Exception::CODE_OPEN_CL_ERROR, "cl::Context::getInfo( ,  ) failed",
					lMsg, __FILE__, __FUNCTION__, __LINE__, lRet);
			}
		}
	}
}