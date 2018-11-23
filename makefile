
# Author   KMS - Martin Dubois, ing.
# Product  KmsBase
# File     makefile

# ===== Targers / Cible ================================================

all:	Binaries/KmsLib_Test Binaries/TODO.so Binaries/TODO_Test Binaries/TODO_Tool Libraries/KmsLib.a

clean:
	rm -f Binaries/*
	rm -f KmsLib/*.o
	rm -f KmsLib_Test/*.o
	rm -f Libraries/*.a
	rm -f Linux_Windows_Test0.txt
	rm -f Templates/DLL/*.o
	rm -f Templates/Test/*.o
	rm -f Templates/Tool/*.o

depend:
	cd KmsLib; make depend
	cd KmsLib_Test; make depend
	cd Templates/DLL; make depend
	cd Templates/Test; make depend
	cd Templates/Tool; make depend

prep:
	mkdir Binaries
	mkdir Export
	mkdir Libraries

test: Binaries/KmsLib_Test Libraries/KmsLib.a
	Binaries/KmsLib_Test
	
Binaries/KmsLib_Test: Libraries/KmsLib.a FORCE
	cd KmsLib_Test;	make
	
Binaries/TODO.so:
	cd Templates/DLL; make
	
Binaries/TODO_Test:
	cd Templates/Test; make
	
Binaries/TODO_Tool:
	cd Templates/Tool; make
	
Libraries/KmsLib.a: FORCE
	cd KmsLib; make

FORCE:
