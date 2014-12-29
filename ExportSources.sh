#!/bin/sh

# Auteur	:	KMS -	Martin Dubois, ing.
# Projet	:	KmsBase
# Fichier	:	ExportSources.sh

echo  Execution de ExportSources.sh $1 ...

# ===== Verification ========================================================

if [ "$1" = "" ] ; then
    echo  ERREUR FATALE : Ligne de commande invalide!
	echo  Usage : ExportSources.sh {Ma.Mi.Bu_Type}
	exit 1
fi

DST=/K/Export/KmsBase/$1
if test ! -d $DST ; then
    echo  ERREUR FATALE : Vous devez exporter les binaires avant les sources!
	exit 2
fi

# ===== Execution ===========================================================

git archive --format=zip master > $DST/$1.zip

# ===== Fin =================================================================

echo  OK!
