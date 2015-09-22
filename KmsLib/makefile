
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
			Linux/Windows.cpp		\
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

CmdLineParser.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
CmdLineParser.o: ../Includes/WindowsToLinux.h
CmdLineParser.o: ../Includes/KmsLib/CmdLineParser.h
CmdLineParser.o: ../Includes/KmsLib/Exception.h
DebugLog.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
DebugLog.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/DebugLog.h
DebugLog.o: ../Includes/KmsLib/Exception.h
Dump.o: ../Includes/KmsLib/Dump.h
Exception.o: ../Includes/KmsLib/Exception.h
MemTester.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
MemTester.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/MemTester.h
OpenCL/Buffer.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
OpenCL/Buffer.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
OpenCL/Buffer.o: ../Includes/KmsLib/OpenCL/Buffer.h
OpenCL/Buffer.o: /opt/AMDAPPSDK-3.0/include/CL/cl.hpp
OpenCL/Buffer.o: /opt/AMDAPPSDK-3.0/include/CL/opencl.h
OpenCL/Buffer.o: /opt/AMDAPPSDK-3.0/include/CL/cl.h
OpenCL/Buffer.o: /opt/AMDAPPSDK-3.0/include/CL/cl_platform.h
OpenCL/Buffer.o: /opt/AMDAPPSDK-3.0/include/CL/cl_gl.h
OpenCL/Buffer.o: /opt/AMDAPPSDK-3.0/include/CL/cl_gl_ext.h
OpenCL/Buffer.o: /opt/AMDAPPSDK-3.0/include/CL/cl_ext.h
OpenCL/CommandQueue.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
OpenCL/CommandQueue.o: ../Includes/WindowsToLinux.h
OpenCL/CommandQueue.o: ../Includes/KmsLib/Exception.h
OpenCL/CommandQueue.o: ../Includes/KmsLib/OpenCL/CommandQueue.h
OpenCL/CommandQueue.o: /opt/AMDAPPSDK-3.0/include/CL/cl.hpp
OpenCL/CommandQueue.o: /opt/AMDAPPSDK-3.0/include/CL/opencl.h
OpenCL/CommandQueue.o: /opt/AMDAPPSDK-3.0/include/CL/cl.h
OpenCL/CommandQueue.o: /opt/AMDAPPSDK-3.0/include/CL/cl_platform.h
OpenCL/CommandQueue.o: /opt/AMDAPPSDK-3.0/include/CL/cl_gl.h
OpenCL/CommandQueue.o: /opt/AMDAPPSDK-3.0/include/CL/cl_gl_ext.h
OpenCL/CommandQueue.o: /opt/AMDAPPSDK-3.0/include/CL/cl_ext.h
OpenCL/Context.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
OpenCL/Context.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
OpenCL/Context.o: ../Includes/KmsLib/OpenCL/Context.h
OpenCL/Context.o: /opt/AMDAPPSDK-3.0/include/CL/cl.hpp
OpenCL/Context.o: /opt/AMDAPPSDK-3.0/include/CL/opencl.h
OpenCL/Context.o: /opt/AMDAPPSDK-3.0/include/CL/cl.h
OpenCL/Context.o: /opt/AMDAPPSDK-3.0/include/CL/cl_platform.h
OpenCL/Context.o: /opt/AMDAPPSDK-3.0/include/CL/cl_gl.h
OpenCL/Context.o: /opt/AMDAPPSDK-3.0/include/CL/cl_gl_ext.h
OpenCL/Context.o: /opt/AMDAPPSDK-3.0/include/CL/cl_ext.h
OpenCL/Kernel.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
OpenCL/Kernel.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
OpenCL/Kernel.o: ../Includes/KmsLib/OpenCL/Kernel.h
OpenCL/Kernel.o: /opt/AMDAPPSDK-3.0/include/CL/cl.hpp
OpenCL/Kernel.o: /opt/AMDAPPSDK-3.0/include/CL/opencl.h
OpenCL/Kernel.o: /opt/AMDAPPSDK-3.0/include/CL/cl.h
OpenCL/Kernel.o: /opt/AMDAPPSDK-3.0/include/CL/cl_platform.h
OpenCL/Kernel.o: /opt/AMDAPPSDK-3.0/include/CL/cl_gl.h
OpenCL/Kernel.o: /opt/AMDAPPSDK-3.0/include/CL/cl_gl_ext.h
OpenCL/Kernel.o: /opt/AMDAPPSDK-3.0/include/CL/cl_ext.h
OpenCL/Program.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
OpenCL/Program.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
OpenCL/Program.o: ../Includes/KmsLib/OpenCL/Program.h
OpenCL/Program.o: /opt/AMDAPPSDK-3.0/include/CL/cl.hpp
OpenCL/Program.o: /opt/AMDAPPSDK-3.0/include/CL/opencl.h
OpenCL/Program.o: /opt/AMDAPPSDK-3.0/include/CL/cl.h
OpenCL/Program.o: /opt/AMDAPPSDK-3.0/include/CL/cl_platform.h
OpenCL/Program.o: /opt/AMDAPPSDK-3.0/include/CL/cl_gl.h
OpenCL/Program.o: /opt/AMDAPPSDK-3.0/include/CL/cl_gl_ext.h
OpenCL/Program.o: /opt/AMDAPPSDK-3.0/include/CL/cl_ext.h
RLE.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
RLE.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
RLE.o: ../Includes/KmsLib/RLE.h
ToolBase.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
ToolBase.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
ToolBase.o: ../Includes/KmsLib/ToolBase.h
