
# Author / Auteur	:	KMS -	Martin Dubois, ing.
# Product / Produit	:	KmsBase
# File / Fichier	:	Templates/DLL

CFLAGS = -fpic -g

INCLUDES = -I ../../Includes

OUTPUT = ../../Binaries/TODO.so

SOURCES = TODO.cpp TODOInterface.cpp

# ===== Rules / Regles =======================================================

.cpp.o:
	g++ -c $(CFLAGS) $(INCLUDES) $<

# ===== Macros ===============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Targets / Cibles =====================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -shared -o $@ $^

depend:
	makedepend -Y $(INCLUDES) $(SOURCES)
# DO NOT DELETE

TODO.o: TODO.h TODOInterface.h
TODOInterface.o: TODO.h TODOInterface.h
