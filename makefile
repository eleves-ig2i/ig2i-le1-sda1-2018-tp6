# commentaire
# Ceci est un fichier texte qui DOIT s'appeller Makefile ou makefile

#Il y a des règles de production. En voici les formats ;
# <CIBLE>: <dependance1> <dep2> ...

all : main.o biblio.o livres.o es.o date.o
	gcc main.o biblio.o livre.o es.o date.o -o main

main.o : main.c biblio.h
	gcc -c main.c -o main.o

biblio.o : biblio.c livre.c
	gcc -c biblio.c -o biblio.o 

livres.o : livre.c livre.h
	gcc -c livre.c -o livre.o

es.o : es.c es.h
	gcc -c es.c -o es.o

date.o : date.c date.h
	gcc -c date.c -o date.o


	
clean :
	rm -rf *.o			# Suppression de tous les fichiers objets

mrproper : clean
	rm -rf main



