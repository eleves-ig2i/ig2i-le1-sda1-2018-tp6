
#include "biblio.h"
#include "livre.h"

// Pour initialiser la bibliothèque
void init (T_Bibliotheque *ptrB) {
	(*ptrB).Ctaille=0;
}


// Pour vérifier l'unicité du nouveau code
int verifcode(T_Bibliotheque B, T_Code new_code) {
int i=1;
while(i!=B.Ctaille+1 && strcmp(B.Cetagere[i].Ccode,new_code)!=0) i++;
if(i==B.Ctaille+1) return 1;	//Le code est bien unique.
else return 0;
}



// Pour ajouter un livre à la bibliothèque
int ajouter(T_Bibliotheque  *ptrB, T_Date dateref) {
if (ptrB->Ctaille<CAPACITE_BIBLIO)// reste t il de la place?
{
	do{	printf("\n Attention ! Le code doit être unique !\n");
		lire_livre(1,&(ptrB->Cetagere[ptrB->Ctaille+1]),dateref);
	}while(verifcode(*ptrB,ptrB->Cetagere[ptrB->Ctaille+1].Ccode)!=1);
	ptrB->Ctaille++;
	return 1;
}
else
{
	return 0;
}
}




// Pour afficher la bibliothèque
int  lister_bibliotheque(const T_Bibliotheque  B) {
int i;

viderbuffer();		// Pour enlever le '\n' contenu dans le buffer		
printf("\n\n\n");
//printf("\n ptrB.Ctaille == %d",B.Ctaille);
if(B.Ctaille==0)
	return 0;
else
{
	for(i=1;i<=B.Ctaille;i++)
	{
		printf("\n\nLIVRE %d\n",i);
		afficher_livre( &(B.Cetagere[i])  );
	}
	getchar();	//Pour faire une pause
	printf("\n\n\n");
	return 1;
}
}




// Pour modifier une fiche livre de la bibliothèque
int modifier(T_Code code, T_Bibliotheque  *ptrB, T_Date dateref) {
int position;


position=rechercher_code(code,ptrB);
if(position>0) {
	printf("\n\n Veuillez saisir les champs de la fiche livre remplaçante.\n Tapez sur entrée directement pour ne pas modifier le titre.\n Entrez un seul caractère pour ne pas modifier les autres champs.");
	lire_livre(modifier_livre,&(ptrB->Cetagere[0]),dateref);
	modif_livre(ptrB->Cetagere[0],&(ptrB->Cetagere[position]));
	return 1;
	}
else{return 0;}
	 	
}


//Modifier la structure d'emprunteur du livre uniquement.
int modifier_emprunteur(T_Code code,T_Bibliotheque *ptrB, T_Date dateref) {
int position;


position=rechercher_code(code,ptrB);
if(position>0) {
	printf("\n\n Veuillez saisir respectivementle nom du nouvel emprunteur, la date d'emprunt et la date de renvoi.");
	lire_livre(modif_emprunteur,&(ptrB->Cetagere[0]),dateref );
	modif_livre(ptrB->Cetagere[0],&(ptrB->Cetagere[position]));
    return 1;
	}
else{return 0;}
}

// Pour supprimer une fiche livre de la bibliothèque en fonction de la position
int supprimer(int position, T_Bibliotheque  *ptrB) {
int i;
if(ptrB->Ctaille!=0) {
	do{
	printf("\n Veuillez saisir une étagère entre 1 et %d.\n ",ptrB->Ctaille);
	scanf("%d",&position);
	}while(position<1 || position>ptrB->Ctaille);
	
	//On souhaite garder l'ordre des fiches livres
	for(i=position;i!=ptrB->Ctaille;i++) modif_livre(ptrB->Cetagere[i+1],&(ptrB->Cetagere[i])); 	
	ptrB->Ctaille--;
	return 1;
	}
else{return 0;}
}


// Pour supprimer une fiche livre de la bibliothèque en fonction du code
int supprimerplus(T_Code code,T_Bibliotheque *ptrB) {
int position,i;

if(ptrB->Ctaille!=0) {
	position=rechercher_code(code,ptrB);
	if(position>0) {		//Si le code a été trouvé
		for(i=position;i!=ptrB->Ctaille;i++) modif_livre(ptrB->Cetagere[i+1],&(ptrB->Cetagere[i])); 	
		ptrB->Ctaille--;
		return 1;
		}
	else{return 0;}
	}
else return 0;
}



////////////////////////////////////////// RECHERCHER ///////////////////////////////////////////////

// En fonction du titre
int rechercher_titre(const T_Titre title, const T_Bibliotheque  *ptrB) {
int i=1,trouve=0;

for(i=1;i!=ptrB->Ctaille+1;i++) {
	if(strcmp(title,ptrB->Cetagere[i].titre)==0) {
		trouve=1;
		printf("\n\nLIVRE %d\n",i);
		afficher_livre( &(ptrB->Cetagere[i])  );
		}
	}
return trouve;	//si trouve==0 alors on a pas trouvé de correspondance.
}



// En fonction de l'auteur
int rechercher_auteur(const T_Aut auteur, const T_Bibliotheque  *ptrB) {
int i,trouve=0;

for(i=1;i!=ptrB->Ctaille+1;i++) {
	if(strcmp(auteur,ptrB->Cetagere[i].auteur)==0) {
		trouve=1;
		printf("\n\nLIVRE %d\n",i);
		afficher_livre( &(ptrB->Cetagere[i])  );
		}
	}
return trouve;	//si trouve==0 alors on a pas trouvé de correspondance.
}



// En fonction de l'editeur
int rechercher_editeur(const T_Edit editeur, const T_Bibliotheque  *ptrB) {
int i,trouve=0;

for(i=1;i!=ptrB->Ctaille+1;i++) {
	if(strcmp(editeur,ptrB->Cetagere[i].editeur)==0) {
		trouve=1;
		printf("\n\nLIVRE %d\n",i);
		afficher_livre( &(ptrB->Cetagere[i])  );
		}
	}
return trouve;	//si trouve==0 alors on a pas trouvé de correspondance.
}



// Tous les livres empruntés
int rechercher_livres_empruntes(const T_Bibliotheque  *ptrB) {
int i, trouve=0;

for(i=1;i!=ptrB->Ctaille+1;i++) {
	if( strcmp("Personne",ptrB->Cetagere[i].emprunteur.nomemprunteur) != 0 ) {	// Un livre non emprunté a "Personne" dans emprunteur
		trouve=1;
		printf("\n\nLIVRE %d\n",i);
		afficher_livre( &(ptrB->Cetagere[i])  );
		}
	}
return trouve;
}


// En fonction du code (technique de la sentinelle)
int rechercher_code(T_Code code, T_Bibliotheque *ptrB) {
int i=ptrB->Ctaille;

strcpy(ptrB->Cetagere[0].Ccode,code);

while( strcmp(ptrB->Cetagere[i].Ccode,ptrB->Cetagere[0].Ccode) ) i--;

return i;
}


// En fonction de l'emprunteur
int rechercher_emprunteur(const T_Emp emprunteur, const T_Bibliotheque  *ptrB) {
int i,trouve=0;

for(i=1;i!=ptrB->Ctaille+1;i++) {
	if(strcmp(emprunteur.nomemprunteur,ptrB->Cetagere[i].emprunteur.nomemprunteur)==0) {
		trouve=1;
		printf("\n\nLIVRE %d\n",i);
		afficher_livre( &(ptrB->Cetagere[i])  );
		}
	}
return trouve;	//si trouve==0 alors on a pas trouvé de correspondance.
}

///////////////////////////////////////////// FIN DES FONCTIONS RECHERCHE ///////////////////////////////////////////

int livres_emprunt_pers(T_Date dateref, const char *nomemprunteur,const T_Bibliotheque B) {
int i;

if( strcmp(nomemprunteur,"Personne")!=0 ) {
	for(i=1;i!=B.Ctaille+1;i++) {
		if(strcmp(nomemprunteur,B.Cetagere[i].emprunteur.nomemprunteur)==0) {
			printf("\n\tCODE LIVRE : %s",B.Cetagere[i].Ccode);
				if( drecent(dateref,B.Cetagere[i].emprunteur.datederenvoi)==2 ) 
				printf(" - A rendre dans %d jours.", dcompare(B.Cetagere[i].emprunteur.datederenvoi,dateref) );
			else if( drecent(dateref,B.Cetagere[i].emprunteur.datederenvoi)==1 )
				   printf(" - Retard de %d jours.",dcompare(dateref,B.Cetagere[i].emprunteur.datederenvoi) );
			     else printf(" - A rendre aujourd'hui.");
			}
		}
	}
else{return 0;}
	
}


/////////////////////////////////////Pour lister les emprunteurs en retards////////////////////////////////////////////
int lister_emprunteur(T_ListeEmp *liste,T_Bibliotheque B) {
    int i,j;
    //On initialise d'abord la liste.
    liste->nb_emprunteur=0;
    strcpy(liste->TableauEmp[0],"Personne");

    if(B.Ctaille!=0) {
        for (i = 1; i <= B.Ctaille; i++) {   //On va faire Ctaille itérations.
            j=0;
            while( j!=liste->nb_emprunteur+1 && strcmp(B.Cetagere[i].emprunteur.nomemprunteur, liste->TableauEmp[j]) !=0 ) j++;
            if(j==liste->nb_emprunteur+1) {
                if(liste->nb_emprunteur != CAPACITE_LISTE_EMP-1) {	
                    (liste->nb_emprunteur)++;
                    strcpy(liste->TableauEmp[j],B.Cetagere[i].emprunteur.nomemprunteur);
                }
                else i=B.Ctaille+1;   // Il ne faut pas dépasser la capacité, pour ne pas avoir d'erreur de segmentation
            }
        }
        return 1;
    }
    else{return 0;}
}


void afficher_liste_emprunteur(T_ListeEmp liste) {
    int i;
    printf("\nLISTE DES EMPRUNTEURS :\n");
    for(i=1;i<=liste.nb_emprunteur;i++ ) printf("\n\t%s",liste.TableauEmp[i]);
    printf("\n\n Nombre d'emprunteurs : %d\n",liste.nb_emprunteur);
    printf("\n________________________\n");
}


void lister_emprunteurs_en_retard(T_Date dateref, T_ListeEmp liste, T_Bibliotheque B) {
    int i,j,retard_personne;
    for(i=1;i<=liste.nb_emprunteur;i++) {
        retard_personne=0;
        printf("\nEmprunteur : %s\n",liste.TableauEmp[i]);
        for(j=1;j<=B.Ctaille;j++) {
            if( strcmp(liste.TableauEmp[i],B.Cetagere[j].emprunteur.nomemprunteur)==0 ) {
                if(drecent(dateref,B.Cetagere[j].emprunteur.datederenvoi) == 1) {
                    printf("\tCODE LIVRE : %s - Retard de %d jours.\n",B.Cetagere[j].Ccode, dcompare(dateref,B.Cetagere[j].emprunteur.datederenvoi));
                    retard_personne=1;
                }
            }
        }
        if(retard_personne==0) printf("\tOK\n");
    }
}

//Pour afficher la liste des fiches livres dans un fichier texte (Bibliotheque.txt)
int lister_bibliotheque_dans_fichier(T_Bibliotheque B) {
FILE *fic;
int i;

viderbuffer();		// Pour enlever le '\n' contenu dans le buffer		
printf("\n\n\n");
if(B.Ctaille==0) return 0;
else {
	fic=fopen("Bibliotheque.txt","w");
	if( fic != NULL ) {
		printf("Ouverture du fichier Bibliotheque.txt réussi.\n");
		for(i=1;i<=B.Ctaille;i++)
		{
			//printf("\n Fiche livre %d en cours d'impression dans le fichier Bibliotheque.txt.\n",i);
			fprintf(fic,"\nLIVRE %d\n",i);
			afficher_livre_fichier(fic, B.Cetagere[i]  );
		}
		getchar();	//Pour faire une pause
		fclose(fic);
		printf("\n\n\n");
		return 1;
		}
	else{ printf("\nOuverture du fichier Bibliotheque impossible...\n"); }
	}
}














