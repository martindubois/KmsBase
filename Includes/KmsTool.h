
// Product  KmsBase

/// \author  KMS - Martin Dubois, ing.
/// \file    Includes/KmsTool.h

// CODE REVIEW  2019-07-15  KMS - Martin Dubois, ing.

#pragma once

// Macros
/////////////////////////////////////////////////////////////////////////////

#if ( ! defined( _DEBUG ) ) || defined( NDEBUG )

    #define KMS_TOOL_BANNER(P,C,V,T)       \
        printf( P " - " C "\n" );          \
        printf( "Version " V " " T "\n" ); \
        printf( "Compiled at " __TIME__ " on " __DATE__ "\n" )

#else

    #define KMS_TOOL_BANNER(P,C,V,T)               \
        printf( P " - " C "\n" );                  \
        printf( "Version " V " " T " (Debug)\n" ); \
        printf( "Compiled at " __TIME__ " on " __DATE__ "\n" );

#endif
