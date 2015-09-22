
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
			Linux/Windows.cpp	\
			MemTester.cpp		\
			OpenCL.cpp			\
			Ring.cpp		\
			RLE.cpp				\
			ToolBase.cpp

# ===== Rules / Regles ======================================================

.cpp.o:
	g++ -c $(CFLAGS) -o $@ $(INCLUDES) $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Targets / Cibles ====================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -o $@ $^

depend:
	makedepend -Y $(INCLUDES) $(SOURCES)

# DO NOT DELETE

CmdLineParser.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
CmdLineParser.o: ../Includes/WindowsToLinux.h
CmdLineParser.o: ../Includes/KmsLib/CmdLineParser.h
CmdLineParser.o: ../Includes/KmsLib/Exception.h ../Includes/KmsTest.h
DebugLog.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
DebugLog.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/DebugLog.h
DebugLog.o: ../Includes/KmsLib/Exception.h ../Includes/KmsTest.h
Dump.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
Dump.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Dump.h
Dump.o: ../Includes/KmsTest.h
Exception.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
Exception.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
Exception.o: ../Includes/KmsTest.h
KmsLib_Test.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
KmsLib_Test.o: ../Includes/WindowsToLinux.h ../Includes/KmsTest.h
MemTester.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
MemTester.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/MemTester.h
MemTester.o: ../Includes/KmsTest.h
OpenCL.o: ../Includes/KmsLib/Exception.h ../Includes/KmsLib/OpenCL/Buffer.h
OpenCL.o: /opt/AMDAPPSDK-3.0/include/CL/cl.hpp
OpenCL.o: /opt/AMDAPPSDK-3.0/include/CL/opencl.h
OpenCL.o: /opt/AMDAPPSDK-3.0/include/CL/cl.h
OpenCL.o: /opt/AMDAPPSDK-3.0/include/CL/cl_platform.h
OpenCL.o: /opt/AMDAPPSDK-3.0/include/CL/cl_gl.h
OpenCL.o: /opt/AMDAPPSDK-3.0/include/CL/cl_gl_ext.h
OpenCL.o: /opt/AMDAPPSDK-3.0/include/CL/cl_ext.h
OpenCL.o: ../Includes/KmsLib/OpenCL/CommandQueue.h
OpenCL.o: ../Includes/KmsLib/OpenCL/Context.h
OpenCL.o: ../Includes/KmsLib/OpenCL/Kernel.h
OpenCL.o: ../Includes/KmsLib/OpenCL/Program.h ../Includes/KmsTest.h
OpenCL.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
OpenCL.o: ../Includes/WindowsToLinux.h
Ring.o: ../Includes/KmsTest.h ../Includes/KmsBase.h ../Includes/SafeAPI.h
Ring.o: ../Includes/WindowsToLinux.h ../Includes/Ring.h
RLE.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
RLE.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
RLE.o: ../Includes/KmsLib/RLE.h ../Includes/KmsTest.h
ToolBase.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
ToolBase.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
ToolBase.o: ../Includes/KmsLib/ToolBase.h ../Includes/KmsTest.h
