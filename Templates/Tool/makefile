
# Author   KMS - Martin Dubois, ing.
# Product  KmsBase
# File     Templates/TODO_Tool/makefile

CFLAGS = -g

INCLUDES = -I ../../Includes

LIBRARIES = ../../Libraries/KmsLib.a

OUTPUT = ../../Binaries/TODO_Tool

SOURCES = TODO_Tool.cpp

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

TODO_Tool.o: ../../Includes/KmsTool.h ../../Includes/KmsLib/ToolBase.h
TODO_Tool.o: ../../Includes/KmsLib/Exception.h
