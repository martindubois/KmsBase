
// Auteur	:	KMS -	Martin Dubois, ing.
// Client	:	TODO
// Projet	:	TODO
// Fichier	:	TODO/TODOInterface.h

#pragma once

// Macro
/////////////////////////////////////////////////////////////////////////////

#if defined( _KMS_LINUX_ ) || defined( _KMS_OS_X_ )
	#define TODO_INTERFACE_API
#endif // _KMS_LINUX_ || _KMS_OS_X_

#ifdef _KMS_WINDOWS_
	#ifdef _TODO_INTERFACE_DLL_
		#define TODO_INTERFACE_API _declspec(dllexport)
	#else
		#define TODO_INTERFACE_API _declspec(dllimport)
	#endif // _TODO_INERFACE_DLL_
#endif // _KMS_WINDOWS_

// Class
/////////////////////////////////////////////////////////////////////////////

class TODOInterface
{

public:

	typedef enum
	{
		STATUS_SUCCESS	= 0,

		STATUS_QTY = 1
	}
	Status;

	static TODO_INTERFACE_API TODOInterface * Create();

	virtual void Delete();

protected:

	TODOInterface();

	virtual ~TODOInterface();

private:

	TODOInterface(const TODOInterface &);

	const TODOInterface & operator = (const TODOInterface &);

};
