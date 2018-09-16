#include "es.h"

// Pour lire le titre d'un livre 
char * lire_titre(char *titre) {
    getchar();
    printf("\n TITRE : ");
    fgets(titre,60,stdin);		//insère automatiquement le caractère '\n'  juste avant '\0'
    titre[strlen(titre)-1]='\0';	//On remplace '\n' par '\0'
    return titre;
}

// Pour l'editeur d'un livre
char * lire_editeur(char *editeur) {
    printf(" EDITEUR : ");
    fgets(editeur,20,stdin);
    editeur[strlen(editeur)-1]='\0';
    return editeur;
}

// Pour lire le code d'un livre
char * lire_code(char *code) {
    printf("CODE : ");
    scanf("%4s",code);
    viderbuffer();
    return code;
}


// Pour la saisie de l'auteur et de l'emprunteur (la vérification se fait dans livre.c)
char * lire_chaine(char *chaine , const char * nomChamp) {
    if(strcmp(nomChamp,"EMPRUNTEUR :")==0) printf(" Ecrire 'Personne' si le livre n'est pas emprunté. ");
    printf(" %s ",nomChamp);
    scanf("%20s",chaine);
    viderbuffer();
return chaine;
}




void afficher_chaine(const char *valeur, const char *nomChamp) {
    printf("%s %s\n",nomChamp,valeur);
}

// Pour vider le buffer de sortie
void viderbuffer()
{
int c=0;
while(c!='\n'&&c!=EOF)	c=getchar();
}



int *lire_annee(int *year) {		
    do{
        printf("ANNEE DE PARUTION : ");
        scanf("%d",year);
        viderbuffer();
        }while(*year<=0 || *year>2018);
    return year;
}


void afficher_annee(int year) {
    printf("ANNEE DE PARUTION : %d\n",year);
}
