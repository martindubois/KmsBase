
# Author   KMS - Martin Dubois, ing.
# Product  KmsBase
# File     KmsLib/makefile

CFLAGS = -g

INCLUDES = -I ../Includes

OUTPUT = ../Libraries/KmsLib.a

SOURCES =	CmdLineParser.cpp		\
			DebugLog.cpp			\
			Dump.cpp				\
			Exception.cpp			\
			File.cpp		        \
			IgnoreList.cpp			\
			Linux/Windows.cpp		\
			MemTester.cpp			\
			RLE.cpp					\
			String.cpp		        \
			TextFile.cpp			\
			ToolBase.cpp			\
			ValueVector.cpp			\
			Walker.cpp

# ===== Rules / Regles =======================================================

.cpp.o:
	g++ -c $(CFLAGS) -o $@ $(INCLUDES) $<

# ===== Macros ===============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Targets / Cibles =====================================================

$(OUTPUT) : $(OBJECTS)
	ar r $@ $^
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
DebugLog.o: ../Includes/KmsLib/Exception.h ../Includes/KmsLib/TextFile.h
Dump.o: ../Includes/KmsLib/Dump.h
Exception.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
Exception.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
File.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
File.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
File.o: ../Includes/KmsLib/File.h
IgnoreList.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
IgnoreList.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
IgnoreList.o: ../Includes/KmsLib/String.h ../Includes/KmsLib/TextFile.h
IgnoreList.o: ../Includes/KmsLib/IgnoreList.h
Linux/Windows.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
Linux/Windows.o: ../Includes/WindowsToLinux.h
Linux/Windows.o: ../Includes/KmsLib/Linux/Windows.h
MemTester.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
MemTester.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/MemTester.h
RLE.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
RLE.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
RLE.o: ../Includes/KmsLib/RLE.h
String.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
String.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/String.h
TextFile.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
TextFile.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
TextFile.o: ../Includes/KmsLib/TextFile.h
ToolBase.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
ToolBase.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
ToolBase.o: ../Includes/KmsLib/File.h ../Includes/KmsLib/ToolBase.h
ValueVector.o: ../Includes/KmsLib/ValueVector.h
Walker.o: ../Includes/KmsBase.h ../Includes/SafeAPI.h
Walker.o: ../Includes/WindowsToLinux.h ../Includes/KmsLib/Exception.h
Walker.o: ../Includes/KmsLib/File.h ../Includes/KmsLib/Linux/Windows.h
Walker.o: ../Includes/KmsLib/Walker.h
