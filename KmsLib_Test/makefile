
# Author / Auteur	:	KMS -	Martin Dubois, ing.
# Product / Produit	:	KmsBase
# File / Fichier	:	KmsLib_Test/makefile

CFLAGS = -g

INCLUDES = -I ../Includes -I /opt/AMDAPPSDK-3.0/include

LIBRARIES = ../Libraries/KmsLib.a /opt/AMDAPPSDK-3.0/lib/x86_64/libOpenCL.so

OUTPUT = ../Binaries/KmsLib_Test

SOURCES =	CmdLineParser.cpp	\
			DebugLog.cpp		\
			Dump.cpp			\
			Exception.cpp		\
			KmsLib_Test.cpp		\
			MemTester.cpp		\
			OpenCL.cpp			\
			RLE.cpp				\
			ToolBase.cpp

# ===== Rules / Regles =======================================================

.cpp.o:
	g++ -c $(CFLAGS) $(INCLUDES) $<

# ===== Macros ===============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Targets / Cibles =====================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -o $@ $^

depend:
	makedepend -Y $(INCLUDES) $(SOURCES)

# DO NOT DELETE

DebugLog.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
DebugLog.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/DebugLog.h
DebugLog.o: ../Includes/KmsLib/Exception.h ../Includes/KmsTest.h
KmsLib_Test.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
KmsLib_Test.o: ../Includes/WindowsToLinux.h ../Includes/KmsTest.h
ToolBase.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
ToolBase.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
ToolBase.o: ../Includes/KmsLib/ToolBase.h ../Includes/KmsTest.h
