
// Author / Auteur		KMS	-	Martin Dubois, ing.
// Product / Produit	KmsBase
// File / Fichier		DepCheck_Net/AssemblyInfo.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== .Net ===============================================================
using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

// ===== Common =============================================================
#include "../Common/Version.h"

// Attributes
/////////////////////////////////////////////////////////////////////////////

[assembly:AssemblyTitleAttribute(L"DepCheck_Net")];
[assembly:AssemblyDescriptionAttribute(L"")];
[assembly:AssemblyConfigurationAttribute(L"")];
[assembly:AssemblyCompanyAttribute(L"KMS")];
[assembly:AssemblyProductAttribute(L"KmsBase")];
[assembly:AssemblyCopyrightAttribute(L"Copyright (c)  2015")];
[assembly:AssemblyTrademarkAttribute(L"")];
[assembly:AssemblyCultureAttribute(L"")];

[assembly:AssemblyVersionAttribute(VERSION_STR)];

[assembly:ComVisible(false)];

[assembly:CLSCompliantAttribute(true)];
