#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <windows.h>
#include "LOG_LLC_BIBLIO.h"

int main() {
    int choix, choixSousMenu;
    activerModeAnsi(); // Active les couleurs ANSI

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;

    if (hOut != INVALID_HANDLE_VALUE && GetConsoleMode(hOut, &dwMode)) {
        SetConsoleMode(hOut, dwMode | 0x0004); // 0x0004 = ENABLE_VIRTUAL_TERMINAL_PROCESSING
    };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    srand(time(NULL)); // TO MAKE ALL USED RANDOM IN THE PROGRAM WORK PROPERLY SIMILAR TO RANDOMIZE IN PASCAL
    bool a=false,b=false,c=false,d=false,e=false; //VARIABLES NEEDED FOR SOME CHECKS
    char date[11]; //VARIABLE HOLDS DATE FROM USER
    char type[2]; //pour indiquer le type logement
    char ch; // ch pour entrer valide ou pas
    char anne[4];//VARRIABLE HOLDS YEAR FROM USER
    char id1[6],id2[6],id3[6];
    int avis; //VARRIABLE HOLDS THE USER CHOICE
    float distance; //VARRIABLE THAT HOLDS DISTANCE FROM THE USER
    ptr_loge headlogement;
    ptr_loge aa;
    ptr_locataire headlocataire;
    ptr_location headlocation;
    ptr_locataire meme_headlocataire = NULL;
    ptr_loge min_head_logement = NULL;
    ptr_classer headnombre = NULL;
    ptr_location head_studio;
    ptr_location head_f2;
    ptr_location head_f3;
    ptr_location head_f4;
    ptr_location head_sort;
    ptr_locataire head_locataire_meme_type=NULL;

    /*______-INITIALISATION DES LISTES DES ARCHIVES :_______________________________________________________________________________*/
    initialiser_archive_logement(&archive_head_logement);
    initialiser_archive_locataire(&archive_head_locataire);
    initialiser_archive_location(&archive_head_location);

    /*______________________________________________________________________________________________________________________________*/

    /*______-INITIALISATION DES LISTES "logement et locataire" depuis le fichier test.txt :_________________________________________*/
    initialiser_logement(&headlogement);
    initialiser_locataire(&headlocataire);
    initialiser_location(&headlocation, headlogement, headlocataire);
    /*______________________________________________________________________________________________________________________________*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    afficher_debut_programe(); //Fenction pour premier affichage quand debut du programe

    do {

        afficher_Banniere_principale();

        afficher_Introduction();

        afficher_Menu(); //FENCTION POUR AFFICHER LE MENU PRINCIPALE

        choix=gerer_entre_pas_entier_dans_le_menu(); // FENCTION POUR GERER LE CAS D'ENTRE N'EST PAS UN ENTIER

        system("cls"); // Nettoyer l'écran

        // Menu principal
        if (choix == 0) {  ///Option pour afficher des notes importantes
            do {

                afficher_Notes_Importantes();

                choixSousMenu= gerer_entre_pas_entier_dans_le_menu(); // FENCTION POUR GERER LE CAS D'ENTRE N'EST PAS UN ENTIER

                system("cls"); // Nettoyer l'écran avant d'exécuter l'action

               } while (choixSousMenu != 1); // Retour au menu principal

        }

        else if (choix== 1) {  ///  Ajouter un logement, locataire ou location , Q2_1

    do {

        afficher_Sous_Menu_ajout(); //FENCTION POUR AFFICHER LE SOUS MENU D'AJOUT

        choixSousMenu= gerer_entre_pas_entier_dans_le_menu(); // FENCTION POUR GERER LE CAS D'ENTRE N'EST PAS UN ENTIER

        system("cls"); // Nettoyer l'écran

        if (choixSousMenu == 1) {
            setColor(14); // Jaune
            printf("\n[Enregistrement d'un nouveau logement]\n");
            setColor(7); // Blanc
            ajouter_logement(headlogement); //FENCTION POUR AJOUTER UN NOUVEAU LOGEMENT A LA LISTE DES LOGEMENT

            setColor(10); //GREEN
            printf("Ajout Avec Succes , Apuyer sur n'importe quelle touche pour continuer");
            setColor(7); //WHITE
            getch(); //ATTENDRE L'UTILISATEURE POUR APPUYER SUR N'IMPORTE QUELLE BOUTON
        }
        else if (choixSousMenu == 2) {
            setColor(14); // Jaune
            printf("\n[Enregistrement d'un nouveau locataire]\n");
            setColor(7); // Blanc
            ajouter_locataire(headlocataire); //FENCTION POUR AJOUTER UN NOUVEAU LOCATAIRE A LA LISTE DES LOCATAIRES

            setColor(10); //GREEN
            printf("Ajout Avec Succes , Apuyer sur n'importe quelle touche pour continuer");
            setColor(7); //WHITE
            getch(); //ATTENDRE L'UTILISATEURE POUR APPUYER SUR N'IMPORTE QUELLE BOUTON

            }
        else if (choixSousMenu == 3) {
            setColor(14); // Jaune
            printf("\n[Enregistrement d'une nouvelle location]\n");
            setColor(7); // Blanc
            ajouter_location(headlocation,headlocataire); //FENCTION POUR AJOUTER UNE NOUVELLE LOCATION A LA LISTE DES LOCATIONS

            setColor(10); //GREEN
            printf("Ajout Avec Succes , Apuyer sur n'importe quelle touche pour continuer");
            setColor(7); //WHITE
            getch(); //ATTENDRE L'UTILISATEURE POUR APPUYER SUR N'IMPORTE QUELLE BOUTON

        }
        else if (choixSousMenu == 4) {
            setColor(12); // Rouge
            printf("\nRetour au menu principal...\n");
            setColor(7); // Blanc
        }
        else {
            setColor(4); // Rouge
            printf("\nOption invalide, veuillez réessayer.\n");
            setColor(7); // Blanc
        }
    } while (choixSousMenu != 4);  // Retour au menu principal
}

        else if (choix== 2) {  /// Suppression d'un logement, locataire, location , Q2_2
    do {


        afficher_Sous_Menu_supression();  //FENCTION POUR AFFICHER LE SOUS MENU DE SUPRESSION

        choixSousMenu= gerer_entre_pas_entier_dans_le_menu(); // FENCTION POUR GERER LE CAS D'ENTRE N'EST PAS UN ENTIER

        system("cls"); // Nettoyer l'écran

        if (choixSousMenu == 1) {
            setColor(10); //VERT
            printf("\n\nVoicie La Liste Des Logement (POUR CHOISIR QUELLE LOGEMENT A SUPPRIMER):  ");

            afficher_logement(headlogement);
            printf("Quelle Logement Voulez Vous Suprimmer (Entre Son ID) :  ");
            scanf("%s",id1);

            suprimer_logement_par_id(&headlogement,id1);
            setColor(10); //GREEN
            printf("SUPRESION Avec Succes , VOULEZ VOUS CONSULTER LA LISTE (si oui tapez 1, si non tapez 0) ? : ");

            scanf("%d",&avis);
            if (avis==1) {
            afficher_logement(headlogement);
            getch(); //attendre l'utilisateure a tapper une touche

            } else {

            setColor(10); //GREEN
            printf("\nApuyer sur n'importe quelle touche pour continuer");
            setColor(7); //WHITE
            getch(); //attendre l'utilisateure a tapper une touche

            }

        }
        else if (choixSousMenu == 2) {

            setColor(10); //VERT
            printf("\n\nVoicie La Liste Des Locataires (POUR CHOISIR QUELLE LOCATAIRE A SUPPRIMER):\n\n ");

            afficher_locataire(headlocataire);
            printf("Quelle Locataire Voulez Vous Suprimmer (Entre Son ID) :  ");
            scanf("%s",id2);

            suprimer_locataire_par_id(&headlocataire,id2);
            setColor(10); //GREEN
            printf("SUPRESION Avec Succes , VOULEZ VOUS CONSULTER LA LISTE (si oui tapez 1, si non tapez 0) ? : ");

            scanf("%d",&avis);
            if (avis==1) {
            afficher_locataire(headlocataire);
            getch(); //attendre l'utilisateure a tapper une touche

            } else {

            setColor(10); //GREEN
            printf("\nApuyer sur n'importe quelle touche pour continuer");
            setColor(7); //WHITE
            getch(); //attendre l'utilisateure a tapper une touche
            }

        }
        else if (choixSousMenu == 3) {


          setColor(10); //VERT
            printf("\n\nVoicie La Liste Des Locations (POUR CHOISIR QUELLE LOCATION A SUPPRIMER):\n\n ");

            afficher_location(headlocation);
            printf("Quelle Location Voulez Vous Suprimmer (Entre Son id_logement -Present dans la premiere ligne-) :  ");
            scanf("%s",id3);

            suprimer_location_par_id(&headlocation,id3);
            setColor(10); //GREEN
            printf("SUPRESION Avec Succes , VOULEZ VOUS CONSULTER LA LISTE (si oui tapez 1, si non tapez 0) ? : ");

            scanf("%d",&avis);
            if (avis==1) {
            afficher_location(headlocation);
            getch(); //attendre l'utilisateure a tapper une touche

            } else {

            setColor(10); //GREEN
            printf("\nApuyer sur n'importe quelle touche pour continuer");
            setColor(7); //WHITE
            getch(); //attendre l'utilisateure a tapper une touche

            }
        }

        else if (choixSousMenu == 4) {
            setColor(12); // Rouge
            printf("\nRetour au menu principal...\n");
            setColor(7); // Blanc
        }
        else {
            setColor(4); // Rouge
            printf("\nOption invalide, veuillez réessayer.\n");
            setColor(7); // Blanc
        }

    } while (choixSousMenu != 4);  // Retour au menu principal
}

        else if (choix== 3) {   ///  Liste des logements occupes et libre a une date done , Q4


            do {

        afficher_Sous_Menu_3(); //FENCTION POUR AFFICHER LE SOUS MENU DE L'OPTION 3

        choixSousMenu= gerer_entre_pas_entier_dans_le_menu(); // FENCTION POUR GERER LE CAS D'ENTRE N'EST PAS UN ENTIER

        system("cls"); // Nettoyer l'écran

        if (choixSousMenu == 1) {
            setColor(14); // Jaune
            printf("\n[Affichage des logements occupes]\n");
            setColor(7); // Blanc
            lister_logement_occupe(headlocation,headlogement); //FENCTION POUR afficher les logements occupes
            printf("Appuyer Sur N'importe Quelle Bouton Pour Retourner");
            getch();
        }
        else if (choixSousMenu == 2) {
            setColor(14); // Jaune
            printf("\nEntrer la date (doit etre sous format YYYY/MM/DD) : ");
            scanf("%s",date);

            if (check_date_valide(date)) {

            setColor(7); // Blanc
            logement_libre_date(headlocation,headlogement,date); //FENCTION POUR AFFICHER LES LOGEMENTS LIBRES A UNE DATE DONEE
            getch();

            } else {
            setColor(4); // ROUGE
            printf("Format non Valide\n\n");
            setColor(7); // Blanc

            printf("Appuyer Sur N'importe Quelle Bouton Pour Retourner");

            getch(); //FUNCTION TO WAIT THE USER TO TAP ANY BUTTON


            }
        }

        else if (choixSousMenu == 4) {
            setColor(12); // Rouge
            printf("\nRetour au menu principal...\n");
            setColor(7); // Blanc
        }
        else {
            setColor(4); // Rouge
            printf("\nOption invalide, veuillez réessayer.\n");
            setColor(7); // Blanc
        }
    } while (choixSousMenu != 4);  // Retour au menu principal
}

        else if (choix== 4) {  ///  Locations par type, Tri et fusion , Q5

       do {

           afficher_Sous_Menu_4();  //FENCTION POUR AFFICHER LE SOUS MENU DE SUPRESSION

        choixSousMenu= gerer_entre_pas_entier_dans_le_menu(); // FENCTION POUR GERER LE CAS D'ENTRE N'EST PAS UN ENTIER

        system("cls"); // Nettoyer l'écran

        if (choixSousMenu == 1) {
            setColor(14); // Jaune
            printf("\nLISTE DES LOCATIONS DE TYPE STUDIO\n\n");
            setColor(7); // Blanc

            if (liste_location_studio(&head_studio,headlocation)) {  //SI IL EXISTE AU MOIN UN ELEMENT DANS LA NOUVELLE LISTE ON LAFFICHE
             afficher_location(head_studio) ;
             a=true;

            } else {
            printf("La Liste n'est Pas Creé Car il n'ya pas des Locations Avec Des Logements De Type Studio");

            }
            printf("\n\nAppuyer Sur N'importe Quelle Bouton Pour Retourne...");

            getch(); //ATTENDRE LUTILISATEURE A TAPER NIMPORTE QUELLE BOUTON


        }
        else if (choixSousMenu == 2) {


        setColor(14); // Jaune
            printf("\nLISTE DES LOCATIONS DE TYPE F2\n\n");
            setColor(7); // Blanc
            if (liste_location_f2(&head_f2,headlocation)) { //SI IL EXISTE AU MOIN UN ELEMENT DANS LA NOUVELLE LISTE ON LAFFICHE
             afficher_location(head_f2) ;
              b=true;
            } else {
            printf("La Liste n'est Pas Creé Car il n'ya pas des Locations Avec Des Logements De Type F2");

            }
            printf("\n\nAppuyer Sur N'importe Quelle Bouton Pour Retourne...");
            getch(); //ATTENDRE LUTILISATEURE A TAPER NIMPORTE QUELLE BOUTON

        }
        else if (choixSousMenu == 3) {


           setColor(14); // Jaune
            printf("\nLISTE DES LOCATIONS DE TYPE F3\n\n");
            setColor(7); // Blanc
            if (liste_location_f3(&head_f3,headlocation)) { //SI IL EXISTE AU MOIN UN ELEMENT DANS LA NOUVELLE LISTE ON LAFFICHE
             afficher_location(head_f3) ;
             c=true;
            } else {
            printf("La Liste n'est Pas Creé Car il n'ya pas des Locations Avec Des Logements De Type F3");

            }

            printf("\n\nAppuyer Sur N'importe Quelle Bouton Pour Retourne...");
            getch(); //ATTENDRE LUTILISATEURE A TAPER NIMPORTE QUELLE BOUTON



        }
        else if (choixSousMenu == 4) {


           setColor(14); // Jaune
            printf("\nLISTE DES LOCATIONS DE TYPE F4\n\n");
            setColor(7); // Blanc
            if (liste_location_f4(&head_f4,headlocation)) { //SI IL EXISTE AU MOIN UN ELEMENT DANS LA NOUVELLE LISTE ON LAFFICHE
             afficher_location(head_f4) ;
             d=true;
            } else {
            printf("La Liste n'est Pas Creé Car il n'ya pas des Locations Avec Des Logements De Type F4");

            }

            printf("\n\nAppuyer Sur N'importe Quelle Bouton Pour Retourne...");
            getch(); //ATTENDRE LUTILISATEURE A TAPER NIMPORTE QUELLE BOUTON

        }
        else if (choixSousMenu==5) {
             if (a && b && c && d) {
             merge_tout_sort(head_studio,head_f2,head_f3,head_f4,&head_sort,headlogement) ;
             afficher_location(head_sort);
               getch();
             }  else {
             setColor(4); //RED
             printf("\n\nTu ne peut pas choisir cette option ,il faut que tu choisis toutes les options precedentes afin de creer toute les LISTES necessaire");
             setColor(7);
             }

             printf("\n\nAppuyer Sur N'importe Quelle Bouton Pour Retourne...");
             getch();
        }

        else if (choixSousMenu == 6) {
            setColor(12); // Rouge
            printf("\nRetour au menu principal...\n");
            setColor(7); // Blanc
        }
        else {
            setColor(4); // Rouge
            printf("\nOption invalide, veuillez reessayer.\n");
            setColor(7); // Blanc
            getch();
        }
         } while (choixSousMenu != 6);  // Retour au menu principal

        }

        else if (choix== 5) {  ///  Liste des locataires avec criteres specifiques , Q6



            do {

            afficher_Sous_Menu_5();//FENCTION POUR AFFICHER LE SOUS MENU DE L'OPTION 5


        choixSousMenu= gerer_entre_pas_entier_dans_le_menu(); // FENCTION POUR GERER LE CAS D'ENTRE N'EST PAS UN ENTIER

        system("cls"); // Nettoyer l'écran

        if (choixSousMenu == 1) {
            setColor(14); // Jaune
            printf("\nVeuillez Entrer Le Type de Logement Que vous Voulez voir ses Locataires (si studio cette fois ecriver studio pas 'st'): \n");
            setColor(7); // Blanc

            scanf("%s",type);

            if (stricmp(type,"studio")==0 || stricmp(type,"f2")==0 || stricmp(type,"f3")==0 || stricmp(type,"f4")==0 )  {

               meme_type(headlocation,headlogement,headlocataire,&head_locataire_meme_type,type);

               if (head_locataire_meme_type==NULL) {//IF NOT FOUND
                printf("Aucune correspendence trouve\n") ;

                } else {
                afficher_locataire(head_locataire_meme_type);
                head_locataire_meme_type=NULL;//REINITIALISER LA LISTE POUR AUTRE USAGE
                }

            } else { //SI L'ENTRE NEST PAS VALIDE
             printf("\nVeuillez entrer un type valide\n\n") ;
            }

            printf("Appuyer Sur N'importe Quelle Bouton Pour Retourner");
            getch();
        }

        else if (choixSousMenu == 2) {
            setColor(12); // Rouge
            printf("\nRetour au menu principal...\n");
            setColor(7); // Blanc
        }

         else {
            setColor(4); // Rouge
            printf("\nOption invalide, veuillez reessayer.\n");
            setColor(7); // Blanc
            getch();
        }


            } while (choixSousMenu != 2);  // Retour au menu principal


        }

        else if (choix== 6) {  ///  Chercher les logements les plus proches et abordables , Q8

          do {

            afficher_Sous_Menu_6();//FENCTION POUR AFFICHER LE SOUS MENU DE L'OPTION 5
            choixSousMenu= gerer_entre_pas_entier_dans_le_menu(); // FENCTION POUR GERER LE CAS D'ENTRE N'EST PAS UN ENTIER



        if (choixSousMenu == 1) {

             setColor(10); //VERT
             printf("\nVeuillez entrer la disatnce Maximale : ") ;
             scanf("%f",&distance);

             logement_proche_loyer_minimale(&min_head_logement,headlogement,distance); //LES LOGEMENTS QUI SATISFAITS LA CONDITION DISTANCE
             if (min_head_logement==NULL) {
             setColor(4); //ROUGE
             printf("\nPas De Logements qui satisfait cette Distance");

             } else {
              setColor(3); //JAUNE
              printf("\nLe Logement Avec Le Plus bas Prix dentre eux est :\n");
              afficher_logement(min_adr_loyer(min_head_logement)); // LE LOGEMENT AVEC LE PLUS PETIT PRIX D'ENTRE EUX
              min_head_logement=NULL; // INIITIALSER LA LISTE
              printf("\n\nAppuyer Sur N'importe Quelle Bouton Pour Retourner");

             }
           getch();

        }

        else if (choixSousMenu == 2) {
            setColor(12); // Rouge
            printf("\nRetour au menu principal...\n");
            setColor(7); // Blanc
        }

         else {
            setColor(4); // Rouge
            printf("\nOption invalide, veuillez reessayer.\n");
            setColor(7); // Blanc
            getch();
        }


            } while (choixSousMenu != 2);  // Retour au menu principal

        }

        else if (choix== 7) {  ///  Consulter l'historique des logements et locations par annee , Q7

           do {

            afficher_Sous_Menu_7();//FENCTION POUR AFFICHER LE SOUS MENU DE L'OPTION 5
            choixSousMenu= gerer_entre_pas_entier_dans_le_menu(); // FENCTION POUR GERER LE CAS D'ENTRE N'EST PAS UN ENTIER

        if (choixSousMenu == 1) {


           printf("Veuillez entrer l'anne ou vous voulez consulter : ");
           scanf("%s",anne);
           nombre_logement_loue_par_quartier(headlocation,headlogement,archive_head_location,&headnombre, anne); //

           if (headnombre==NULL) {
         setColor(4); //RED
        printf("\n\nPas De Location Disponible Pour cette annee");
         setColor(7); //WHITE
         getch(); //WAITING THE USER TO TAP ANY KEY

           } else {
            printf("\n\n");
            afficher_question_7(headnombre);
            headnombre=NULL; // INIITIALSER LA LISTE
            printf("\n\nAppuyer Sur N'importe Quelle Bouton Pour Retourner");
            getch(); //WAITING THE USER TO TAP ANY KEY
           }
        }

        else if (choixSousMenu == 2) {

            liste_location_studio(&head_studio,headlocation); //INITIALISER LA LISTE STUDIO
            liste_location_f2(&head_f2,headlocation); //INITIALISER LA LISTE F2
            liste_location_f3(&head_f3,headlocation); //INITIALISER LA LISTE F3
            liste_location_f4(&head_f4,headlocation); //INITIALISER LA LISTE F4

            nombre_locations_par_type(head_f4,head_f3,head_f2,head_studio);
            getch(); //WAITING THE USER TO TAP ANY KEY

        }

         else if (choixSousMenu == 3) {
          setColor(12); // Rouge
          printf("\nRetour au menu principal...\n");
          setColor(7); // Blanc

         }
         else {
            setColor(4); // Rouge
            printf("\nOption invalide, veuillez reessayer.\n");
            setColor(7); // Blanc
            getch();
        }


            } while (choixSousMenu != 3);  // Retour au menu principal










        }

        else if (choix==8) {  /// Consulter les listes


        do {
         afficher_Sous_Menu_8();  //FENCTION POUR AFFICHER LE SOUS MENU DE SUPRESSION

        choixSousMenu= gerer_entre_pas_entier_dans_le_menu(); // FENCTION POUR GERER LE CAS D'ENTRE N'EST PAS UN ENTIER

        system("cls"); // Nettoyer l'écran

        if (choixSousMenu == 1) {
            setColor(10); //VERT
            printf("\n\nVoicie La Liste LOGEMENT:\n\n ");

            afficher_logement(headlogement);
            setColor(10); //VERT
            printf("\n\nAppuyer sur n'importe quelle tocuhe pour retourner\n\n ");
            getch(); //attendre l'utilisateure a tapper une touche

        }
        else if (choixSousMenu == 2) {

            setColor(10); //VERT
            printf("\n\nVoicie La Liste LOCATAIRE:\n\n ");

            afficher_locataire(headlocataire);
            setColor(10); //VERT
            printf("\n\nAppuyer sur n'importe quelle tocuhe pour retourner\n\n ");
            getch(); //attendre l'utilisateure a tapper une touche

            }

        else if (choixSousMenu == 3) {

            setColor(10); //VERT
            printf("\n\nVoicie La Liste LOCATION:\n\n ");

            afficher_location(headlocation);
            setColor(10); //VERT
            printf("\n\nAppuyer sur n'importe quelle tocuhe pour retourner\n\n ");
            getch(); //attendre l'utilisateure a tapper une touche

            }

         else if (choixSousMenu == 4) {
          setColor(12); // Rouge
          printf("\nRetour au menu principal...\n");
          setColor(7); // Blanc

         }

        else {

            setColor(4); // Rouge
            printf("\nOption invalide, veuillez reessayer.\n");
            setColor(7); // Blanc
            getch();
            }

        } while (choixSousMenu!=4);


        }

        else if(choix== 9) { /// Consulter les listes archives

   do {
         afficher_Sous_Menu_9();  //FENCTION POUR AFFICHER LE SOUS MENU DE SUPRESSION

        choixSousMenu= gerer_entre_pas_entier_dans_le_menu(); // FENCTION POUR GERER LE CAS D'ENTRE N'EST PAS UN ENTIER

        system("cls"); // Nettoyer l'écran

        if (choixSousMenu == 1) {
            setColor(10); //VERT
            printf("\n\nVoicie La Liste ARCHIVE LOGEMENT:\n\n ");

            afficher_logement(archive_head_logement);
            setColor(10); //VERT
            printf("\n\nAppuyer sur n'importe quelle tocuhe pour retourner\n\n ");
            getch(); //attendre l'utilisateure a tapper une touche

        }
        else if (choixSousMenu == 2) {

            setColor(10); //VERT
            printf("\n\nVoicie La Liste ARCHIVE LOCATAIRE:\n\n ");

            afficher_locataire(archive_head_locataire);

            setColor(10); //VERT
            printf("\n\nAppuyer sur n'importe quelle tocuhe pour retourner\n\n ");
            getch(); //attendre l'utilisateure a tapper une touche

            }

        else if (choixSousMenu == 3) {

            setColor(10); //VERT
            printf("\n\nVoicie La Liste ARCHIVE LOCATION:\n\n ");

            afficher_location(archive_head_location);
            setColor(10); //VERT
            printf("\n\nAppuyer sur n'importe quelle tocuhe pour retourner\n\n ");
            getch(); //attendre l'utilisateure a tapper une touche

            }

          else if (choixSousMenu == 4) {
          setColor(12); // Rouge
          printf("\nRetour au menu principal...\n");
          setColor(7); // Blanc

         }

        else {

            setColor(4); // Rouge
            printf("\nOption invalide, veuillez reessayer.\n");
            setColor(7); // Blanc
            getch();
            }

        } while (choixSousMenu!=4);

        }

        else if (choix== 10) {  // Quitter
            setColor(12); // Rouge
            printf("\nAu revoir !\n");
            setColor(7); // Blanc
        }

        else {
                afficher_logement(headlogement);
        getch();
            setColor(4); // Rouge
            printf("\nOption invalide, veuillez réessayer.\n");
            setColor(7); // Blanc
        }

    } while (choix != 10); // Quitter le programme

    return 0;
}



