
# Author / Auteur	KMS	-	Martin Dubois, ing.
# Product / Produit	KmsBase
# File / Fichier	kms.base/tools/chocolateyinstall.ps1


Push-Location $PSScriptRoot\..\content

	call Install.cmd

	$lResult = $?

Pop-Location

if ( -not $lResult )
{
	exit 1
}
