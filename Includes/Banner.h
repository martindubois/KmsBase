
// Product / Produit   KmsBase

/// \author   KMS - Martin Dubois, ing.
/// \file     Includes/Banner.h

#pragma  once

// Macro
/////////////////////////////////////////////////////////////////////////////

/// \cond   en
/// \brief  Display banner
/// \param  P  Product
/// \param  C  Component
/// \note   This macro use VERSION_STR and VERSION_TYPE
/// \endcond
/// \cond   fr
/// \brief  Afficher une baniere
/// \param  P  Produit
/// \param  C  Composant
/// \note   Cette macro utilise VERSION_STR et VERSION_TYPE
/// \endcond
#ifdef _DEBUG
    #define  Banner(P, C)                                        \
	    printf(                                                  \
            P " - " C "\n"                                       \
            "Version " VERSION_STR " " VERSION_TYPE " (Debug)\n" \
            "Compiled at " __TIME__ " on " __DATE__ "\n");
#else
    #define  Banner(P, C)                                \
        printf(                                          \
            P " - " C "\n"                               \
            "Version " VERSION_STR " " VERSION_TYPE "\n" \
            "Compiled at " __TIME__ " on " __DATE__ "\n");
#endif // _DEBUG
