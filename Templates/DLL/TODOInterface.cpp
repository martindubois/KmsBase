
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	TODO
// Fichier	:	TODOInterface.cpp

#define _TODO_INTERFACE_DLL_

// Includes
/////////////////////////////////////////////////////////////////////////////

// ====== Local =============================================================
#include "TODO.h"

// Public
/////////////////////////////////////////////////////////////////////////////

// Retour :
//  NULL	= Erreur lors de la creation
//	Autre	= Adresse de l'instance cree
TODO_INTERFACE_API TODOInterface * TODOInterface::Create()
{
	return new TODO();
}

// Cette methode detruit l'instance precedement cree par la methode statique
// Create.
void TODOInterface::Delete()
{
	delete this;
}

// Protected
/////////////////////////////////////////////////////////////////////////////

// Constructeur par defaut
TODOInterface::TODOInterface()
{
}

// Destructeur
TODOInterface::~TODOInterface()
{
}
