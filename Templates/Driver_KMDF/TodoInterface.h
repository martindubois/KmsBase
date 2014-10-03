
// Auteur	:	KMS -	Martin Dubois, ing.
// Client	:	TODO
// Projet	:	TODO
// Fichiers	:	TODO/TODOInterface.h

#pragma once

// Constantes
/////////////////////////////////////////////////////////////////////////////

// {1690EC14-97C6-4A4B-9122-04B1DB5F3EE2}
static const GUID TODO_INTERFACE	= { 0x1690ec14, 0x97c6, 0x4a4b, { 0x91, 0x22, 0x04, 0xb1, 0xdb, 0x5f, 0x3e, 0xe2 } };
// TODO : Changer le GUID

#define TODO_IOCTL_TODO	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
// TODO : Changer le FILE_DEVICE_..., si necessaire
// TODO : Ajouter d'autre code, si necessaire
