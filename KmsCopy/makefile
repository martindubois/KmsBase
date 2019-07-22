
# Author   KMS - Martin Dubois, ing.
# Product  KmsBase
# File     KmsCopy/makefile

include ../User.mk

LIBRARIES = ../Libraries/KmsLib.a

OUTPUT = ../Binaries/KmsCopy

SOURCES =	KmsCopy.cpp

# ===== Rules / Regles ======================================================

.cpp.o:
	g++ -c $(CFLAGS) -o $@ $(INCLUDES) $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Targets / Cibles ====================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -pthread -o $@ $^

depend:
	makedepend -Y $(INCLUDES) $(SOURCES)

# DO NOT DELETE

KmsCopy.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
KmsCopy.o: ../Includes/WindowsToLinux.h ../Includes/KmsTool.h
KmsCopy.o: ../Common/Version.h
