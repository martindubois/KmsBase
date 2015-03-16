
# Author / Auteur	:	KMS -	Martin Dubois, ing.
# Product / Produit	:	KmsBase
# File / Fichier	:	Templates/Test/makefile

CFLAGS = -g

INCLUDES = -I ../../Includes

OUTPUT = ../../Binaries/TODO_Test

SOURCES = TODO.cpp TODO_Test.cpp

# ===== Rules / Regles =======================================================

.cpp.o:
	g++ -c $(CFLAGS) $(INCLUDES) $<

# ===== Macros ===============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Targets / Cibles =====================================================

$(OUTPUT) : $(OBJECTS)
	g++ -o $@ $^

depend:
	makedepend -Y $(INCLUDES) $(SOURCES)
# DO NOT DELETE

TODO.o: ../../Includes/KmsTest.h
TODO_Test.o: ../../Includes/KmsTest.h
