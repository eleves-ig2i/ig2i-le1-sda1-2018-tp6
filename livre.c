#include "livre.h"

// Les deux premières fonctions servent à "factoriser" le code de la fonction lire_livre
void lire_dates(T_Emp *emprunteur, T_Date dateref) {
    if( strcmp(emprunteur->nomemprunteur,"Personne")!=0 ) {
  		do {
		    printf("\n Veuillez saisir la date de renvoi correctement.\n");
  		    emprunteur->datedemprunt=dateref;
  		    datescanf(&(emprunteur->datederenvoi),"DATE DE RENVOI");
        }while( ddate(emprunteur->datederenvoi)==0 || drecent(emprunteur->datederenvoi,emprunteur->datedemprunt)!=1);
    }
/* Pour les lignes ci-dessus, il faut que :
- les dates entrées soient cohérentes. (cf ddate)
- la date la plus récente soit la date de renvoi (cf drecent)
*/
}

void lire_auteur_editeur_emprunteur(T_livre *ptrL) {
    lire_chaine( ptrL->auteur, "AUTEUR :");
    lire_editeur( ptrL->editeur);
    lire_chaine( ptrL->emprunteur.nomemprunteur, "EMPRUNTEUR :");
//printf(" verif auteur = %d\n verif editeur = %d\n ",verifnom(ptrL->auteur),verifnom(ptrL->editeur));
}



// Pour la saisie d'un livre
void lire_livre(T_Mode mode,T_livre * ptrL,T_Date dateref) {	//Si mode==1 alors on lit le code, sinon on ne le lit pas.

    if(mode==ajouter_livre || mode==modifier_livre)	lire_titre(ptrL->titre);


    if(mode==ajouter_livre){	//Lorsqu'on veut ajouter le livre à la bibliothèque
	    do{
	    	lire_auteur_editeur_emprunteur(ptrL);
    	}while(verifnom(1,ptrL->auteur)==0 || verifnom(1,ptrL->emprunteur.nomemprunteur)==0 );
    	lire_annee(&(ptrL->annee));
	    lire_code(ptrL->Ccode);  //  la vérification de l'unicité se fait dans biblio.h
 	}
 	
 	
    if(mode==modifier_livre) {	//Lorsqu'on veut modifier le livre
	    do{
	    	lire_auteur_editeur_emprunteur(ptrL);
  	    }while(verifnom(0,ptrL->auteur)==0 || verifnom(0,ptrL->emprunteur.nomemprunteur)==0 );
    }


    if(mode==modif_emprunteur) {    //Lorsqu'on veut modifier que l'emprunteur.
	    do {
	    	lire_chaine(ptrL->emprunteur.nomemprunteur, "EMPRUNTEUR :");
	    } while (verifnom(1, ptrL->emprunteur.nomemprunteur) == 0);
    }
    lire_dates(&(ptrL->emprunteur),dateref);
}





// Pour l'affichage d'un livre
void afficher_livre(const T_livre *ptrL) {
    afficher_chaine(ptrL->titre, "TITRE :");
    afficher_chaine(ptrL->auteur, "AUTEUR :");
    afficher_annee(ptrL->annee);
    afficher_chaine(ptrL->editeur,"EDITEUR :");
    afficher_chaine(ptrL->emprunteur.nomemprunteur,"EMPRUNTEUR :");
    if( strcmp(ptrL->emprunteur.nomemprunteur,"Personne")!=0 ) {
    	dateprintf(ptrL->emprunteur.datedemprunt,"DATE D'EMPRUNT");
	    dateprintf(ptrL->emprunteur.datederenvoi,"DATE DE RENVOI");
    }
    afficher_chaine(ptrL->Ccode, "CODE :");
}

// Pour la modification du livre
void modif_livre(const T_livre new_kq, T_livre *ptrL) {	//new_kq == fiche livre à mettre dans ptrL

    if(strlen(new_kq.titre)!=0) strcpy(ptrL->titre,new_kq.titre);
    if(strlen(new_kq.auteur)!=1) strcpy(ptrL->auteur,new_kq.auteur);
    if(strlen(new_kq.editeur)!=1) strcpy(ptrL->editeur,new_kq.editeur);

    if(strlen(new_kq.emprunteur.nomemprunteur)!=1) {
    	strcpy(ptrL->emprunteur.nomemprunteur,new_kq.emprunteur.nomemprunteur);
	    if(strcmp(new_kq.emprunteur.nomemprunteur,"Personne")!=0) {
	    	datecpy(&(ptrL->emprunteur.datederenvoi),new_kq.emprunteur.datederenvoi);
	    	datecpy(&(ptrL->emprunteur.datedemprunt),new_kq.emprunteur.datedemprunt);
        }
	}
}



// Pour vérifier la saisie du de l'éditeur, de l'auteur ou de l'emprunteur
int verifnom(int mode,const char *prenom) {
int i=0;

    if(mode==1) {
	    if(strlen(prenom)<=MAX-1 && strlen(prenom)>1) {
	    	if( prenom[i]>='A' && prenom[i]<='Z' ) {
	    		i++;
		    	while(prenom[i]!='\0' && ( prenom[i]>='a' && prenom[i]<='z') ) i++;
			}
		}
	    if(prenom[i]=='\0') return 1;
	    else return 0;
	}

    if(mode==0) {		//le prenom peut etre constitué de 1 caractère.
	    if(strlen(prenom)<=MAX-1 && strlen(prenom)>0) {
	    	if(strlen(prenom)==1) return 1;
		    else {
		    	if( prenom[i]>='A' && prenom[i]<='Z' ) {
                    i++;
		    	    while(prenom[i]!='\0' && ( prenom[i]>='a' && prenom[i]<='z') ) i++;
			    }
		    }
		    if(prenom[i]=='\0') return 1;
		    else return 0;
		}
	    else{ return 0;}
	}
}



int afficher_livre_fichier(FILE * fic, const T_livre ptrL  ) {
    //int fprintf(FILE *stream, const char *format, ...);
    fprintf(fic,"TITRE : %s\n", ptrL.titre);
    fprintf(fic,"AUTEUR : %s\n",ptrL.auteur);
    fprintf(fic,"ANNEE DE PARUTION : %d\n",ptrL.annee);
    fprintf(fic,"EDITEUR : %s\n",ptrL.editeur);
    fprintf(fic,"EMPRUNTEUR : %s\n",ptrL.emprunteur.nomemprunteur);
    if( strcmp(ptrL.emprunteur.nomemprunteur,"Personne")!=0 ) {
    	fprintf(fic,"DATE D'EMPRUNT : \n");
	fprintf(fic,"DATE DE RENVOI : \n");
    }
    fprintf(fic,"CODE : %s\n",ptrL.Ccode);
}







