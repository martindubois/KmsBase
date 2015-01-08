
// Auteur	:	KMS -	Martin Dubois, ing.
// Project	:	KmsBase
// Fichier	:	Includes/KmsDriverLib/Object.h

#pragma once

namespace KmsDriverLib
{

	// Class
	/////////////////////////////////////////////////////////////////////////

	class Object
	{

	public:

		static void InitializeObjectAttribute(WDF_OBJECT_ATTRIBUTES * aAttributes);

		typedef struct
		{
			const wchar_t * mPrefix	;
			unsigned int	mTag	;
		}
		ObjectConfig;

		void	operator delete (void * aObject);
		void  * operator new	(size_t aSize_byte, unsigned int aTag);

		Object();

		void Initialize(WDFOBJECT aWdfObject);

		operator WDFOBJECT ();

		const ObjectConfig & GetObjectConfig() const;

		void SetObjectConfig(const Object * aObject);
		void SetObjectConfig(const ObjectConfig & aConfig);
		void SetObjectConfig(const wchar_t * aPrefix, unsigned int aTag);

		virtual ~Object();

		virtual void	Cleanup();

	protected:

		ObjectConfig	mConfig		;
		WDFOBJECT		mWdfObject	;

	private:

	};

}
