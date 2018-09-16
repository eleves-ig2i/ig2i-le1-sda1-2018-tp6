#ifndef BIBLIO__H_INCLUDED
#define BIBLIO__H_INCLUDED

#include "livre.h"

#define CAPACITE_BIBLIO 100
#define CAPACITE_LISTE_EMP 10        // Pour 9 personnes
# define K_MaxLivres CAPACITE_BIBLIO+1
// +1 pour la sentinelle (case 0)
// les livres seront rang�es entre la case 1 et la case CAPACITE_BIBLIO

// Pour la structure bibliotheque
typedef T_livre T_TableauDeLivres[K_MaxLivres];
typedef  struct {
    T_TableauDeLivres Cetagere;
    int Ctaille ;
} T_Bibliotheque;


// Pour la structure listant les emprunteurs
typedef char emprunteur[21];
typedef struct {
    emprunteur TableauEmp[CAPACITE_LISTE_EMP];
    int nb_emprunteur;
}T_ListeEmp;

// Gestion d'une bibliotheque de livre
void init (T_Bibliotheque *);		//Pour initialiser la bibliothèque à 0 livre

int verifcode(T_Bibliotheque , T_Code );	 // Pour vérifier l'unicité du code du nouveau livre
int ajouter(T_Bibliotheque  *, T_Date);		//Pour ajouter une fiche livre dans la bibliothèque

int rechercher_titre(const T_Titre, const T_Bibliotheque  *);	//Affiche les livres contenant le titre
int rechercher_auteur(const T_Aut, const T_Bibliotheque  *);	//Affiche les livres contenant l'auteur
int rechercher_editeur(const char *, const T_Bibliotheque  *);	// ...
int rechercher_emprunteur(const T_Emp , const T_Bibliotheque  *);	//...
int rechercher_livres_empruntes(const T_Bibliotheque  *);	//Affiche tous les livres empruntés
int rechercher_code(T_Code , T_Bibliotheque *);

int supprimer(int, T_Bibliotheque  *);		// supprimer la fiche livre qui est situé en (int)eme position)
int supprimerplus(T_Code ,T_Bibliotheque *);	// supprimer la fiche livre caractérisé par le code (T_Code)

int modifier(T_Code ,T_Bibliotheque  *, T_Date); 	// modifier la fiche livre qui a pour code (T_Code)
int modifier_emprunteur(T_Code , T_Bibliotheque *, T_Date );	//Modifier la structure d'emprunteur du livre uniquement.

int lister_bibliotheque(const T_Bibliotheque  );	// liste toute la bibliothèque
int livres_emprunt_pers(T_Date , const char* ,const T_Bibliotheque);	//Affiche les codes des livres empruntés par T_Emp emprunteur, et affiche le nombre de jours restant avant la date de renvoi du livre (ou le nombre de jours de retard)

int lister_emprunteur(T_ListeEmp *,T_Bibliotheque);
void afficher_liste_emprunteur(T_ListeEmp);
void lister_emprunteurs_en_retard(T_Date,T_ListeEmp,T_Bibliotheque);

int lister_bibliotheque_dans_fichier(T_Bibliotheque);


#endif // BIBLIO__H_INCLUDED




