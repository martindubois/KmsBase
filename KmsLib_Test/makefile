
# Author / Auteur	:	KMS -	Martin Dubois, ing.
# Product / Produit	:	KmsBase
# File / Fichier	:	KmsLib_Test/makefile

CFLAGS = -g

INCLUDES = -I ../Includes

LIBRARIES = ../Libraries/KmsLib.a

OUTPUT = ../Binaries/KmsLib_Test

SOURCES = DebugLog.cpp KmsLib_Test.cpp ToolBase.cpp

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
