#ifndef LOG_LLC_BIBLIO_H_INCLUDED
#define LOG_LLC_BIBLIO_H_INCLUDED
/*-------------------------------------DÉCLARATION DES STRUCTURES—-----------------------------*/

// Structure pour un logement

typedef struct logement {

char type[2];      //Studio,F2, F3, F4
float superficie;    // Superficie en m²
char quartier[50];  // Nom de quartier
float distance;       // Distance en Km du quartier a la commune
float loyer;
char id_logement[6];      //ID DE LA FORME "typelogementXXXX"
struct logement *next;   //next one in the list
}logement ;
typedef struct logement *ptr_loge;
// Structure pour un locataire

struct locataire {
char nom[50];
char prenom[50];
 char telephone[15];
 char id_locataire[6]; //WILL BE MADE IN THIS FORMAT FirstLetterOfNom/FirstLetterOfPrenom/LastFourDigitsOFPhoneNumber
struct locataire *next;  //next one in the list
} ;
typedef struct locataire *ptr_locataire;

//structure pour la location

struct location {
char  id_locataire[7];   //Identifiant du Locataire
char  id_logement[7];  //Identifiant du Logement
char  date_debut[11];  // Date de debut (format: JJ/MM/AAAA)
char  date_fin[11];   // Date de Fin (format: JJ/MM/AAAA)
struct location *next;  //next one in the list
};
typedef struct location *ptr_location;
// structure temporaire pour question 7
struct classer{
char quartier [100];
int nombre;
struct classer *next;
};
typedef struct classer *ptr_classer;
/*____________VARIABLES GLAUBAUX QUI PRESENTES LES TETES DES LISTES ARCHIVES___________________________________________*/
ptr_loge archive_head_logement;
ptr_locataire archive_head_locataire;
ptr_location archive_head_location;
/*______________________________________________________________________________________________________________________*/
char id[6];
//****************************************************************************************************

/*---------------------------------------------------------------------------------------—-----------------------------*/
/*-----------------------------------DECLARATION DES MACHINES ABSTRAITES----------------------------------------------------*/

////////////////////////////// Machine Abstraite Pour La Manipulation Des Logement\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
void allocate_logement (ptr_loge *p);
void ass_adr_logement (ptr_loge p,ptr_loge q); //ass= assigne ; adr=adress
ptr_loge next_logement (ptr_loge p);
void ass_type(ptr_loge p, char val[]);
void ass_superficie(ptr_loge p, float val);
void ass_quartie(ptr_loge p, char val[]);
void ass_distance(ptr_loge p, float val);
void ass_loyer(ptr_loge p, float val);
int generateure_id_logement ();
char *generateure_id_logement1 (ptr_loge p); //ID DE FORME "typelogementXXXX"
void ass_id_logement_aleatoire (ptr_loge p); //ASSIGNE THE ID_LOGEMENT TO LOGEMENT NODE
void free_logement(ptr_loge p);
float superficie_logement(ptr_loge p);
char* id_logement(ptr_loge p);
char* type_logement(ptr_loge p);
float superficie_moyen(char type[]);
float distance_logement(ptr_loge p);
float loyer_logement(ptr_loge p);


void afficher_logement(ptr_loge head); //AFFICHAGE DE LA LISTE DES LOGEMENT
float calc_loyer(char type[]);
void initialiser_logement(ptr_loge *t);
void initialiser_archive_logement (ptr_loge *head);
/*---------------------------------------MACHINE ABSTRAITE DE LOCATAIRE------------------------------------------------------------*/
void allocate_locataire(ptr_locataire *p);  //Function to allocate memory for a locataire
void ass_nom(ptr_locataire p, char val[]);// Function to assign nom  of locataire
void ass_prenom(ptr_locataire p, char val[]); // Function to assign prenom   of locataire
void ass_telephone(ptr_locataire p, char val[]); // Function to assign telephone  of locataire
void ass_adr_locataire(ptr_locataire p, ptr_locataire q);// Function to assign address of locataire
char *generateure_id_locataire (ptr_locataire p) ;
void ass_id_locataire (ptr_locataire p); //ASSIGNE THE ID_LOCATAIRE TO LOCATAIRE NODE
ptr_locataire next_locataire(ptr_locataire p);// Function to next address of logement
void Free_locataire(ptr_locataire p);// Function  to free a logement
void afficher_locataire(ptr_locataire head);//afficherll= afficher LINKED LIST
void initialiser_locataire(ptr_locataire *head); // Function to initialize locataire
void initialiser_archive_locataire (ptr_locataire *head);
/*------------------------------------------------MACHINE ABSTRAITE LOCATION--------------------------------------------------------*/
ptr_location next_location(ptr_location p);// Function to next address of location
void ass_adr_location(ptr_location p, ptr_location q) ;// Function to assign address of location
void allocate_location(ptr_location *p) ; //Function to allocate memory for a location
char *generateure_date();
void initialiser_location (ptr_location *headlocation,ptr_loge headlogement,ptr_locataire headlocataire); /*FUNCTION TO INITIALISE THE LOCATION
                                     LISTE (third liste in the TP) FROM THE LOGEMENT AND LOCATAIRE LISTES BY LINKING EACH LOCATAIRE WITH A LOGEMENT*/
void initialiser_archive_location(ptr_location *head) ;
void afficher_location(ptr_location head);// Function to display the location linked list
void ass_date_debut(ptr_location p, char date[]);
void ass_date_fin(ptr_location p, char date[]);
/*-----------------------------------------------------------\\\\FIN////---------------------------------------------------------------*/
//***********************************************************FUNCTIONS PRINCIPAL****************************************************************************//


void ajouter_logement(ptr_loge head);//ADD A NEW LOGEMENT
void ajouter_locataire(ptr_locataire head); //ADD A NEW LOCATAIRE
void ajouter_location(ptr_location head,ptr_locataire headlocataire /*pour ajouter apres a liste locataire*/); //FUNCTION ADD A NEW LOCATION
void ajouter_logement_archive (ptr_loge node); //ADD A NEW LOGEMENT TO THE ARCHIVE
void ajouter_locataire_archive (ptr_locataire node); //ADD A NEW LOGEMENT TO THE ARCHIVE
void ajouter_location_archive (ptr_location node) ; //ADD A NEW LOCATION TO THE ARCHIVE
void  supression_logement (ptr_loge *head,ptr_loge p) ;//DELETE A LOGEMENT BASED ON THE POINTER PROVIDED TO THE FUNCTION
void  supression_locataire (ptr_locataire *head,ptr_locataire p);//DELETE A LOCATAIRE BASED ON THE POINTER PROVIDED TO THE FUNCTION

void suprimer_logement_par_id(ptr_loge *headlogement,char id1[]);//DELETE A LOGEMENT USING ITS ID
void suprimer_locataire_par_id(ptr_locataire *headlocataire,char id2[]); //DELETE A LOCATAIRE USING ITS ID
void suprimer_location_par_id(ptr_location *headlocation,char id3[]); //DELETE A LOCATAIRE USING ITS ID

void supression_avec_type (ptr_loge *head,char type[]); //FUNCTION TO DELETE LOGEMENT BASED IN THE TYPE OF LOGEMENT
void  supression_location (ptr_location *head,ptr_location p);//DELETE A LOCATION BASED ON THE POINTER PROVIDED TO THE FUNCTION
void lister_logement_occupe (ptr_location headlocation,ptr_loge headlogement);/*LISTING ALL OCCUPIED LOGMENTS
headlocation is needed to get the IDS of the occupied logements and the headlogement is needed to find the logements them selfs*/
void logement_libre_date (ptr_location headlocation,ptr_loge headlogement,char date[]); //SHOWS ALL FREE LOGEMENTS AFTER A DATE
    //DEKHELELHA HEAD TA3 LOCATION BACH THAWS FIH 3LA LES DATES WTDI ID W HEAD TA3 LOGEMENT BACH TEDJBED MENOU LOGEMENT W TANIT DATE


//**************************************************question 5*****************************************************************************

bool liste_location_studio(ptr_location *headstudio, ptr_location headlocation) ;
// FUNCTION TO CREATE A NEW LIST CONTAINING ONLY LOCATIONS STUDIO
bool liste_location_f2(ptr_location *head_f2, ptr_location headlocation) ;
// FUNCTION TO CREATE A NEW LIST CONTAINING ONLY LOCATIONS f2
bool liste_location_f3(ptr_location *head_f3, ptr_location headlocation) ;
// FUNCTION TO CREATE A NEW LIST CONTAINING ONLY LOCATIONS f3
bool liste_location_f4(ptr_location *head_f4, ptr_location headlocation) ;
// FUNCTION TO CREATE A NEW LIST CONTAINING ONLY LOCATIONS f4

void affectation(ptr_location p, ptr_location t);
void merge_sort(ptr_location head1,ptr_location head2,ptr_location *head_merge,ptr_loge headlogement);
void merge_tout_sort(ptr_location head1,ptr_location head2,ptr_location head3,ptr_location head4,ptr_location *head_sort,ptr_loge headlogement);
/// ***********************************sort by loyer************************************//

float find_loyer_logement(ptr_loge head, char id[]);
void swape(ptr_location p,ptr_location t);
ptr_location min_loyer(ptr_location head_s,ptr_loge headlogement);
void sorte(ptr_location head_s,ptr_loge headlogement);
//*******************************question 6*************************************************
ptr_locataire find_locataire(ptr_locataire headlocataire, char id[6]) ;
float  find_superficie_logement(ptr_loge head,char id[]);
char* find_type_logement(ptr_loge head,char id[]);
void ajouter_nouvelle(ptr_locataire *meme_headlocataire, ptr_locataire p);
void meme_type(ptr_location headlocation, ptr_loge headlogement, ptr_locataire headlocataire, ptr_locataire *head_locataire_meme_type, char type[]) ;
//---------------------------------------------------------------------------------


//******************************** question8******************************************

void ajouter_nouveaux_min(ptr_loge *meme_headlocation, ptr_loge p);
ptr_loge min_adr_loyer(ptr_loge headlogement);
void logement_proche_loyer_minimale(ptr_loge *minheadlogement, ptr_loge headlogement, float distance);
//***************************************************************************
//--------------------------question 7_1--------------------------------------
void allocate_classer(ptr_classer *p);
char* quartie_logement(ptr_loge p);
char* find_quartie_logement(ptr_loge head, char id[]);
void nouveaux_list(ptr_classer *headnombre, char q[]);
void nombre_logement_loue_par_quartier(ptr_locataire headlocation, ptr_loge headlogement,ptr_location headarchive, ptr_classer *headnombre, char anne[]);
//-------------------------------------------------->>> QUESTION 7_2 <<<-----------------------------------------------------------------
int lengthll (ptr_location head);
int cpt_f4_archive(ptr_location archive_head_location);
int cpt_f3_archive(ptr_location archive_head_location);
int cpt_f2_archive(ptr_location archive_head_location);
int cpt_studio_archive(ptr_location archive_head_location);
void nombre_locations_par_type (ptr_location head_f4,ptr_location head_f3,ptr_location head_f2,ptr_location head_studio);
bool check_date_valide(char date[]);
void setColor(int color);
void afficher_debut_programe ();
void afficher_Banniere_principale();
void afficher_Banniere_Note();
void afficher_Menu();
void afficher_question_7(ptr_classer headnombre);
void afficher_Sous_Menu_ajout();
void afficher_Sous_Menu_supression();
void afficher_Sous_Menu_3();
void afficher_Sous_Menu_4();
void afficher_Sous_Menu_5();
void afficher_Sous_Menu_6();
void afficher_Sous_Menu_7();
void afficher_Sous_Menu_8();
void afficher_Sous_Menu_9();
void afficher_Introduction();
void afficher_Notes_Importantes ();
void activerModeAnsi();
void reinitialiser_curseure ();
int gerer_entre_pas_entier_dans_le_menu ();

//*********************************\\fin//*******************************************//
#endif // LOG_LLC_BIBLIO_H_INCLUDED



