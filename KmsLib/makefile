
# Author / Auteur	:	KMS -	Martin Dubois, ing.
# Product / Produit	:	KmsBase
# File / Fichier	:	KmsLib/makefile

CFLAGS = -g

INCLUDES = -I ../Includes -I /opt/AMDAPPSDK-3.0/include

OUTPUT = ../Libraries/KmsLib.a

SOURCES =	CmdLineParser.cpp		\
			DebugLog.cpp			\
			Dump.cpp				\
			Exception.cpp			\
			MemTester.cpp			\
			OpenCL/Buffer.cpp		\
			OpenCL/CommandQueue.cpp	\
			OpenCL/Context.cpp		\
			OpenCL/Kernel.cpp		\
			OpenCL/Program.cpp		\
			RLE.cpp					\
			ToolBase.cpp

# ===== Rules / Regles =======================================================

.cpp.o:
	g++ -c $(CFLAGS) -o $@ $(INCLUDES) $<

# ===== Macros ===============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Targets / Cibles =====================================================

$(OUTPUT) : $(OBJECTS)
	ar ru $@ $^
	ranlib $@

depend:
	makedepend -Y $(INCLUDES) $(SOURCES)
# DO NOT DELETE

DebugLog.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
DebugLog.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/DebugLog.h
DebugLog.o: ../Includes/KmsLib/Exception.h
Exception.o: ../Includes/KmsLib/Exception.h
ToolBase.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
ToolBase.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
ToolBase.o: ../Includes/KmsLib/ToolBase.h
