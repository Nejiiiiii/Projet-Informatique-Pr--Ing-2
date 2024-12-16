CC=gcc
CFLAGS=-Wall -Wextra

all: Division Traitement

Division: Fichier.c/Division.c
	$(CC) $(CFLAGS) -o Division Fichier.c/Division.c
	
Traitement: Fichier.c/Traitement.c Fichier.c/AVL.c 
	$(CC) $(CFLAGS) -o Traitement Fichier.c/Traitement.c Fichier.c/AVL.c -I Fichier.h
	
clean:
	rm -f Division Traitement
