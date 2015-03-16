
// Auteur	:	KMS -	Martin Dubois, ing.
// Client	:	TODO
// Projet	:	TODO
// Fichier	:	TODO/TODOInterface.h

#pragma once

// Macro
/////////////////////////////////////////////////////////////////////////////

#ifdef _LINUX_
	#define TODO_INTERFACE_API
#endif // _LINUX_

#ifdef _WINDOWS_
	#ifdef _TODO_INTERFACE_DLL_
		#define TODO_INTERFACE_API _declspec(dllexport)
	#else
		#define TODO_INTERFACE_API _declspec(dllimport)
	#endif // _TODO_INERFACE_DLL_
#endif // _WINDOWS_

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
