
// Product / Produit  KmsBase

/// \author  KMS - Martin Dubois, ing.
/// \file    Includes/KmsTool.h

#pragma once

// Macros
/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG

    #define KMS_TOOL_BANNER(P,C,V,T)       \
        printf( P " - " C "\n" );          \
        printf( "Version " V " " T "\n" ); \
        printf( "Compiled at " __TIME__ " on " __DATE__ "\n" )

#else

    #define KMS_TOOL_BANNER(P,C,V,T)              \
        printf( P " - " C "\n" );                 \
        printf( "Version " V " " T "(Debug)\n" ); \
        printf( "Compiled at " __TIME__ " on " __DATE__ "\n" );

#endif // _DEBUG
