
#include "biblio.h"
#include <time.h>

/**********************************************MENUS UTILISES POUR LE MAIN**********************************************/
///////// Menu principal
int menu() {
    int chx;
    printf("\n\n\n Bienvenue dans le programme de gestion de la bibliothèque.\n");
    puts(" 1 - ajouter un livre en bibliotheque");
    puts(" 2 - afficher des caractéristiques de la bibliothèque.");
    puts(" 3 - modifier un livre de la bibliothèque");
    puts(" 4 - rechercher un livre de la bibliothèque");
    puts(" 5 - supprimer un livre de la bibliothèque");
    puts(" 0 - QUITTER");
    scanf("%d",&chx);
    return chx;
}

///////// Menus secondaires
int menu_recherche() {
    int choix;
    printf("\n\n\n\n Bienvenue dans le programme de recherche de la bibliothèque.\n Comment voulez-vous rechercher un livre ?\n");
    puts(" 1 - Titre");
    puts(" 2 - Auteur");
    puts(" 3 - Editeur");
    puts(" 4 - Livres empruntés");
    puts(" 5 - Code");
    puts(" 6 - Emprunteur");
    puts(" 0 - Revenir au menu précédent.");
    scanf("%d",&choix);
    return choix;
}


int menu_supprimer() {
    int chx;
    printf("\n\n\n\n Bienvenue dans le programme de suppression de la bibliothèque.\n Comment voulez-vous rechercher le livre à supprimer ?\n");
    puts(" 1 - En fonction de son numéro d'étagère.");
    puts(" 2 - En fonction de son code.");
    puts(" 0 - Revenir au menu précédent.");
    scanf("%d",&chx);
    return chx;
}


int menu_modifier() {
    int chx;
    printf("\n\n\n\n Bienvenue dans le programme de modification de la bibliothèque.\n Comment voulez-vous modifier le livre concerné ?\n");
    puts(" 1 - Titre, auteur, editeur et/ou emprunteur.");
    puts(" 2 - Emprunteur.");
    puts(" 0 - Revenir au menu précédent.");
    scanf("%d",&chx);
    return chx;
}


int menu_afficher() {
    int chx;
    printf("\n\n\n\n Bienvenue dans le programme d'affichage de la bibliothèque.\n Que voulez-vous afficher ?\n");
    puts(" 1 - La liste des fiches livres de la bibliothèque.");
    puts(" 2 - Les livres d'un emprunteur et les informations correspondant.");
    puts(" 3 - La liste des emprunteurs et les retards.");
    puts(" 0 - Revenir au menu précédent.");
    scanf("%d",&chx);
    return chx;
}
/*******************************************FIN DES MENUS******************************************************************/


/*************************************PROGRAMMES RELATIFS AUX FICHIERS*****************************************************/
void sauvegarde(T_Bibliotheque *ptrB) {
    FILE *fic=NULL; //le type FILE
    int i;
    fic=fopen("baseLivres","w"); // w = le mode = write avec ECRASEMENT
    //fopen renvoie NULL si probleme (disque plein, disque non accessible ...

    if (fic!=NULL) {
	    for(i=1;i<=ptrB->Ctaille;i++) {
		    //fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
		    fwrite(  &(ptrB->Cetagere[i])        ,sizeof(T_livre),1,fic);
        }
	fclose(fic);
	puts("SAUVEGARDE REUSSIE ..............");
	}
    else puts("ECHEC DE SAUVEGARDE  !!!!!  ");
}



void chargement(T_Bibliotheque *ptrB) {
    FILE *fic=NULL; //le type FILE
    int i=1;
    fic=fopen("baseLivres","r"); // r = le mode read
    //fopen renvoie NULL si probleme (disque plein, disque non accessible ...

    if (fic!=NULL) {
	    do {
           fread(  &(ptrB->Cetagere[i]) ,sizeof(T_livre),1,fic);
	    	i++;
        }while(!feof(fic));
	    fclose(fic);

	    ptrB->Ctaille=i-2;
	    puts("\n\nCHARGEMENT  REUSSI ..............");
	}
    else puts("\n\nECHEC DE CHARGEMENT  !!!!!  ");
}
/*****************************FIN DES SOUS PROGRAMMES RELATIFS AUX FICHIERS*************************************************/

void Date_Day(T_Date *date) {
    time_t now = time(NULL);
    struct tm tm_now = *localtime(&now);
    date->day = tm_now.tm_wday;
    date->jour = tm_now.tm_mday;
    date->mois = tm_now.tm_mon + 1;
    date->annee = 1900 + tm_now.tm_year;
            dateprintf(*date,"Date d'aujourd'hui");
}

/*********************************************PROGRAMME PRINCIPAL**********************************************/
int main( )
{
int choix,choix_2,reponse,etagere;	// choix_2 sert pour les menus secondaires; etagere sert pour la modification ou suppression d'un livre
T_Bibliotheque B;
char chaine[MAX_TITRE];		// cette variable sert pour la recherche à partir d'une chaine de caractères. Donc on y alloue la plus grande quantité d'octets nécessaire.
T_Emp emprunteur;	// cette variable sert pour la structure de l'emprunteur avec les dates.
T_Date dateref;     // Pour la date de référence.
T_ListeEmp listedesemprunteurs;	// Pour la liste des emprunteurs (cf fonction afficher_liste_emprunteurs )

Date_Day(&dateref);
	
init(&B); //mise à 0 de Ctaille
chargement(&B);
lister_bibliotheque_dans_fichier(B);
do{
	dateprintf(dateref,"Date d'aujourd'hui");
	choix=menu();
	
	switch(choix) {
	
		case 1 : reponse = ajouter(&B,dateref);
			 if (reponse==1) puts("Ajout reussi !!!");
			 else puts("Bibliotheque pleine !! impossible d ajouter");
			 break;

            // Début du menu afficher
        case 2 : if(B.Ctaille!=0) {
                    do{
                      choix_2=menu_afficher();
                        switch(choix_2) {

                        case 1 : lister_bibliotheque(B);
                            break;

                        case 2 : lire_chaine(chaine, "EMPRUNTEUR :");
                                 reponse = livres_emprunt_pers(dateref,chaine,B);
                                 if (reponse==0) printf("\n Aucun livre n'a été emprunté par %s.\n",chaine);
                                 break;

                        case 3 : if( lister_emprunteur(&listedesemprunteurs,B) ) {
                                 afficher_liste_emprunteur(listedesemprunteurs);
                                 lister_emprunteurs_en_retard(dateref,listedesemprunteurs,B);
                                 }
                                 else printf("\n Bibliothèque vide !");
                                 break;

                        default : choix_2=0;
                        }
                    }while(choix_2!=0);
                 }
                 else {printf("\n La bibliothèque est vide !\n");}
                 break;
		//Fin du menu afficher
		
		//Début du menu modifier
		case 3 : if(B.Ctaille!=0) {
			         do{
                          choix_2=menu_modifier();
			 	          switch(choix_2) {

			 		      case 1 : lire_code(chaine);
			 			           if(modifier(chaine,&B,dateref)) printf("\n Modification réussie !\n");
                                   else printf("\n Code non trouvé ! \n");
			 			           break;
			 			 
			 		      case 2 : lire_code(chaine);
			 			           if(modifier_emprunteur(chaine,&B,dateref)) printf("\n Modification réussie !\n");
			 			           else printf("\n Code non trouvé ! \n");
			 			           break;
			 		
			 		      default : choix_2=0;
			 		      }
			 	     }while(choix_2!=0);
            }
                else{ printf("\n La bibliothèque est vide !\n");}
			    break;
		//Fin du menu modifier
		
		//Début du menu recherche
		case 4 : if(B.Ctaille!=0) {
			        do{
				        choix_2=menu_recherche();
				        switch(choix_2) {
				
					    case 1 : lire_titre(chaine);
					        	 reponse = rechercher_titre(chaine,&B);
						         if (reponse==0) printf("\nAucun\n");
						         printf("\n\n\n");
						         break;

					    case 2 : lire_chaine(chaine, "AUTEUR :");
						         reponse = rechercher_auteur(chaine,&B);
						         if (reponse==0) printf("\nAucun\n");
						         printf("\n\n\n");
						         break;

					    case 3 : lire_chaine(chaine, "EDITEUR :");
						         reponse = rechercher_editeur(chaine,&B);
						         if (reponse==0) printf("\nAucun\n");
						         printf("\n\n\n");
						         break;
						 
					    case 4 : printf("\n  Liste des livres empruntés : ");
					        	 reponse = rechercher_livres_empruntes(&B);
					        	 if (reponse==0) printf("\nAucun\n");
						         printf("\n\n\n");
						         break;

					    case 5 : lire_code(chaine);
                                 reponse=rechercher_code(chaine,&B);
						         if(reponse==0) printf("\nAucun\n");
						         else {
                                     printf("\n\nLIVRE %d\n",reponse);
						    	     afficher_livre( &(B.Cetagere[reponse])  );
							     }
						         break;
						 
					    case 6 : lire_chaine(emprunteur.nomemprunteur, "EMPRUNTEUR :");
						         reponse = rechercher_emprunteur(emprunteur,&B);
						         if (reponse==0) printf("\n Aucun livre n'a été emprunté par %s.\n",chaine);
						         printf("\n\n\n");
						         break;
						 
					    default : choix_2=0;
					    }
			        }while(choix_2!=0);
			    }
                else{ printf("\n La bibliothèque est vide !\n");}
			    break;
		// Fin du menu recherche
		
		// Début du menu supprimer
		case 5 : if(B.Ctaille!=0) {
			        do{
				        choix_2=menu_supprimer();
				        switch(choix_2) {
					
					    case 1 : if(supprimer(etagere,&B)) printf("\n Suppression réussie !\n");
			 			         else printf("\n Bibliothèque vide ! \n");
						         break;

					    case 2 : lire_code(chaine);
					 	         if(supprimerplus(chaine,&B)) printf("\n Suppression réussie !\n");
			 			         else printf("\n Bibliothèque vide ou code non trouvé ! \n");
						        break;
					
					    default : choix_2=0;
					    }
			        }while(choix_2!=0);
			    }
			    else {printf("\n La bibliothèque est vide !\n");}
			    break;
		// Fin du menu supprimer


		default : choix=0;
		}
}while(choix!=0);
    sauvegarde(&B);
}

