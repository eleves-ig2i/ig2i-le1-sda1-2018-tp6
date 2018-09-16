#ifndef CHAMP_H
#define CHAMP_H

#include <stdio.h>
#include <string.h>


// Traitements de niveau 3
// Servent a la gestion des champs d'un livre

char * lire_titre(char *);	// Pour les chaines de 60 caractères max
char * lire_code(char *);	// Pour les chaines de 4 caractères max
char * lire_editeur(char *);
char * lire_chaine(char *, const char *);	// Pour les chaines de 20 caractères max
void viderbuffer();

void afficher_chaine(const char *, const char *);

int *lire_annee(int *);
void afficher_annee(int);


#endif

