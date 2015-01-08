
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	KmsDriverLib/Object.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== WDK ================================================================
#include <ntddk.h>
#include <wdf.h>

// ===== KmsBase ============================================================
#include <KmsDriverLib/Object.h>

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
	KmsDriverLib::Object * mThis;
}
ObjectContext;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(ObjectContext, GetObjectContext)

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

// ===== Points d'entrees ===================================================
extern "C"
{
	static EVT_WDF_OBJECT_CONTEXT_CLEANUP		Cleanup;
}

namespace KmsDriverLib
{

	// Public
	/////////////////////////////////////////////////////////////////////////

	// aAttributes : [out]
	void Object::InitializeObjectAttribute(WDF_OBJECT_ATTRIBUTES * aAttributes)
	{
		ASSERT(NULL != aAttributes);

		WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(aAttributes, ObjectContext);

		aAttributes->EvtCleanupCallback = ::Cleanup;
	}

	void * Object::operator new(size_t aSize_byte, unsigned int aTag)
	{
		// TODO :
	}

	// Constructeur par defaut
	Object::Object() : mWdfObject(NULL)
	{
		memset(&mConfig, 0, sizeof(mConfig));
	}

	// aWdfObject : [in,out,keep]
	void Object::Initialize(WDFOBJECT aWdfObject)
	{
		ASSERT(NULL != aWdfObject);

		ASSERT(NULL == mWdfObject);

		mWdfObject = aWdfObject;
	}

	Object::operator WDFOBJECT ()
	{
		ASSERT(NULL != mWdfObject);

		return mWdfObject;
	}
}

// Fonctions statiques
/////////////////////////////////////////////////////////////////////////////

// ===== Points d'entrees ===================================================

void Cleanup(WDFOBJECT aWdfObject)
{
	ASSERT(NULL != aWdfObject);

	ObjectContext * lContext = GetObjectContext(aWdfObject);
	ASSERT(NULL != lContext			);
	ASSERT(NULL != lContext->mThis	);

	lContext->mThis->Cleanup();
}
