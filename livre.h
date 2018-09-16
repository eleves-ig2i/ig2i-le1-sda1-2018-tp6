
#ifndef LIVRE_H_INCLUDED
#define LIVRE_H_INCLUDED

#include "es.h"
#include "date.h"		// Librairie utilisée pour la structure T_Emp

# define MAX 21
# define MAX_TITRE 61
# define MAX_CODE 5

# define K_MaxTit MAX_TITRE
# define K_MaxAut MAX
# define K_MaxEdit MAX
# define K_MaxEmp MAX
# define K_MaxCode MAX_CODE

/*typedef enum T_Jour {lu,ma,me,je,ve,sa,di};		
typedef enum T_Mois  {ja,fe,mar,av,mai,ju,jui,ao,se,oc,no,de};*/
// Les types ci-dessous ne sont pas nécessaires étant donné que la structure T_Date a été définie dans date.h

typedef enum{modifier_livre,ajouter_livre,modif_emprunteur}T_Mode;

typedef struct
{
    char nomemprunteur[21];
    T_Date datedemprunt;
    T_Date datederenvoi;
}T_Emp ;


typedef char T_Titre[K_MaxTit];
typedef char T_Aut[K_MaxAut];
typedef char T_Edit[K_MaxEdit];
typedef char T_Code[K_MaxCode];	// Code de 4 caractères
typedef int T_annee;	// Année de publication du livre

typedef struct
{
T_Titre titre;
T_Aut auteur; 
T_Code Ccode; 
T_Edit editeur; 
T_annee annee; 
T_Emp emprunteur; 

}  T_livre; 

void lire_auteur_editeur_emprunteur(T_livre *);
void lire_dates(T_Emp *, T_Date);
void lire_livre(T_Mode ,T_livre *, T_Date);
void afficher_livre(const T_livre *);
void modif_livre(const T_livre , T_livre *);		//Le code n'est pas modifiable !
int verifnom(int, const char *);		// Renvoie 1 si le char* correspond à un nom, 0 sinon.
int afficher_livre_fichier(FILE * fic, const T_livre ptrL  );


#endif


