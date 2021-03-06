
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   KmsBase
// File      KmsVersion/Tests/Master_00.txt

// TEST INFO KmsVersion
//           Report an error when the master header file contains a badly formated version.

#define VERSION_MAJOR         (0)
#define VERSION_MINOR         (0)
#define VERSION_BUILD         (0)
#define VERSION_COMPATIBILITY (0)

#define VERSION_RC   0,0,0
#define VERSION_STR  "0.0.0.0"
#define VERSION_STR0 "0.0.0.0\0"

#define VERSION_TYPE "Error"
