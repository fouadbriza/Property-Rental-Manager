#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <windows.h>
#include "LOG_LLC_BIBLIO.h"
/*-----------------------------------DECLARATION DES MACHINES ABSTRAITES----------------------------------------------------*/

////////////////////////////// Machine Abstraite Pour La Manipulation Des Logement\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


void allocate_logement (ptr_loge *p) {
*p=malloc(sizeof(struct logement));
};

void ass_adr_logement (ptr_loge p,ptr_loge q) { //ass= assigne ; adr=adress
p->next=q;
}

ptr_loge next_logement (ptr_loge p) {
return p->next;
}

void ass_type(ptr_loge p, char val[]) {
strcpy(p->type, val);
}

void ass_superficie(ptr_loge p, float val) {
p->superficie = val;
}

void ass_quartie(ptr_loge p, char val[]) {
strcpy(p->quartier, val);
}

void ass_distance(ptr_loge p, float val) {
p->distance = val;
}

void ass_loyer(ptr_loge p, float val) {
p->loyer = val;


}

int generateure_id_logement () {
return rand() % 99999;
}

char *generateure_id_logement1 (ptr_loge p) { //ID DE FORME "typelogementXXXX"

char *id_genere=malloc(6);
strcpy(id_genere,p->type);
sprintf(id_genere+2,"%d",1000+rand() % 9000);
return id_genere;

}

void ass_id_logement_aleatoire (ptr_loge p) { //ASSIGNE THE ID_LOGEMENT TO LOGEMENT NODE
strcpy(p->id_logement,generateure_id_logement1(p));
}

void free_logement(ptr_loge p){
free(p);
}
float superficie_logement(ptr_loge p){ ///FUNCTION TO RETURN SUPERFICIE OF LOGEMENT
return p->superficie;
}

char* id_logement(ptr_loge p){ ///FUNCTION TO RETURN ID OF LOGEMENT
return p->id_logement;
}

char* type_logement(ptr_loge p){ ///FUNCTION TO RETURN TYPE OF LOGEMENT
return p->type;
}

float superficie_moyenne(char type[]){ ///FUNCTION TO CALCULATE SUPERFICIE MOYENNE OF LOGEMENT

if(strcmp(type,"studio")==0)return 20;
if(strcmp(type,"f2")==0)return 45;
if(strcmp(type,"f3")==0)return 65;
if(strcmp(type,"f4")==0)return 85;
}
float distance_logement(ptr_loge p)
{
    return p->distance;
}

float loyer_logement(ptr_loge p)
{
    return p->loyer;
}

void afficher_logement(ptr_loge head) {
    // AFFICHAGE DE LA LISTE DES LOGEMENTS
    ptr_loge cursor = head;


if (cursor == NULL) {  // CHECK IF THE LIST IS EMPTY
 setColor(4); // RED COLOR FOR EMPTY LIST
 printf("\nAUCUN LOGEMENT TROUVE.\n");
 setColor(7); // RESET COLOR
return;
}

// HEADER FOR THE LIST OF LOGEMENTS
setColor(14); // YELLOW FOR HEADER
printf("\n--- LISTE DES LOGEMENTS ---\n");
setColor(7); // RESET COLOR


while (cursor != NULL) { // LOOP THROUGH ALL LOGEMENTS AND DISPLAY THEIR DETAILS
 // DISPLAY TYPE OF LOGEMENT
 setColor(11); // LIGHT CYAN FOR "TYPE"
 printf("TYPE           : ");
 setColor(7); // RESET COLOR
 printf("%s\n", cursor->type);

        // DISPLAY THE AREA (SUPERFICIE) OF THE LOGEMENT
 setColor(11); // LIGHT CYAN FOR "SUPERFICIE"
 printf("SUPERFICIE     : ");
 setColor(7); // RESET COLOR
 printf("%.2f m*m\n", cursor->superficie);

// DISPLAY THE NEIGHBORHOOD (QUARTIER) OF THE LOGEMENT
 setColor(11); // LIGHT CYAN FOR "QUARTIER"
 printf("QUARTIER       : ");
 setColor(7); // RESET COLOR
 printf("%s\n", cursor->quartier);

// DISPLAY THE DISTANCE TO THE LOGEMENT
 setColor(11); // LIGHT CYAN FOR "DISTANCE"
 printf("DISTANCE       : ");
 setColor(7); // RESET COLOR
 printf("%.2f km\n", cursor->distance);

// DISPLAY THE RENT (LOYER) OF THE LOGEMENT
 setColor(11); // LIGHT CYAN FOR "LOYER"
 printf("LOYER          : ");
 setColor(7); // RESET COLOR
 printf("%.2f DA\n", cursor->loyer);

// DISPLAY THE LOGEMENT ID
 setColor(11); // LIGHT CYAN FOR "ID"
 printf("ID LOGEMENT    : ");
 setColor(7); // RESET COLOR
 printf("%s\n", cursor->id_logement);

// PRINT A SEPARATOR LINE FOR BETTER VISUAL ORGANIZATIO
 printf("----------------------------------------\n");

// MOVE TO THE NEXT LOGEMENT IN THE LIST
 cursor = next_logement(cursor);
}
}
float calc_loyer(char type[]){
    int x=0;
    if(strcasecmp(type,"studio")==0) x=1;
    if(strcasecmp(type,"f2")==0) x=2;
    if(strcasecmp(type,"f3")==0) x=3;
    if(strcasecmp(type,"f4")==0) x=4;


    switch(x){
        case 1:
            return 15000;
        case 2:
            return 20000;
        case 3:   ;
            return 30000;
        case 4:
            return 45000;
    }
}
void initialiser_logement(ptr_loge *t) {

*t = NULL;
ptr_loge p = NULL;
ptr_loge q = NULL;
ptr_loge save=NULL;
allocate_logement(t);
p=*t;

char TYPE[10];
float SUPERFICIE;
float DISTANCE;
char QUARTIE[100];
float LOYER;
char id[6];
char line[256];

int stop = 0;
FILE *fichier = fopen("datafile.txt", "r");
if (fichier == NULL) {
 printf("Erreur d'ouverture du fichier.\n");
 return;
 }


while ((stop == 0) && (fgets(line, sizeof(line), fichier))) {
  if (strcmp(line, "\n") == 0) {
    stop = 1;
    free_logement(p);
    } else {
     sscanf(line,"%s %f %s %f %5s", TYPE, &SUPERFICIE, QUARTIE, &DISTANCE, id);

     ass_type(p, TYPE);

     ass_superficie(p, SUPERFICIE);
     ass_quartie(p, QUARTIE);
     ass_distance(p, DISTANCE);
     ass_loyer(p,calc_loyer(TYPE));
     strcpy(p->id_logement,id);
     save=p;

     allocate_logement(&q);

     ass_adr_logement(p, q);
     p = q;
      }
    }

    ass_adr_logement(save,NULL);
    fclose(fichier);
}

void initialiser_archive_logement (ptr_loge *head) {
*head=NULL;
}




/*---------------------------------------MACHINE ABSTRAITE DE LOCATAIRE------------------------------------------------------------*/





void allocate_locataire(ptr_locataire *p) { //Function to allocate memory for a locataire
*p = malloc(sizeof(struct locataire));
}

void ass_nom(ptr_locataire p, char val[]) {// Function to assign nom  of locataire
strcpy(p->nom,val);
}

void ass_prenom(ptr_locataire p, char val[]) {// Function to assign prenom   of locataire
strcpy(p->prenom, val);
}

void ass_telephone(ptr_locataire p, char val[]) {// Function to assign telephone  of locataire
strcpy(p->telephone, val);
}

void ass_adr_locataire(ptr_locataire p, ptr_locataire q) {// Function to assign address of locataire
p->next = q;
}

char *generateure_id_locataire (ptr_locataire p) {

char *id_finale=malloc(7); //USING DYNAMIC MEMORY TO KEEP THE RESULT SAVED BECAUSE IF NOT IT WILL BE DELETED

//IN THIS FORMAT FirstLetterOfNom/FirstLetterOfPrenom/LastFourDigitsOFPhoneNumber

char first_letter_nom=p->nom[0];

char first_letter_prenom=p->prenom[0];
char last_four_digits_phone_number[5];

strncpy(last_four_digits_phone_number, p->telephone +6 ,4); //starts from digit 6 then reading 4 digits and assingnes them into our string
last_four_digits_phone_number[4]='\0'; //MARKING THE END OF THE STRING BECAUSE strncpy FUNCTION DO NOT DO IT AUTOMATICALY

sprintf(id_finale, "%c%c%s",first_letter_nom,first_letter_prenom,last_four_digits_phone_number);//CONCATINATES ALL THE THREE STRINGS INTO RESULT

return id_finale;
}

char id[6]; //hada houa balak tekhreb fih
void ass_id_locataire (ptr_locataire p) { //ASSIGNE THE ID_LOCATAIRE TO LOCATAIRE NODE

strcpy(id,generateure_id_locataire(p));
strcpy(p->id_locataire,id);
//printf("id:%s",p->id_locataire);

}

ptr_locataire next_locataire(ptr_locataire p) {// Function to next address of logement
return p->next;
}

void Free_locataire(ptr_locataire p){// Function  to free a logement
free(p);
}












void afficher_locataire(ptr_locataire head) {
    // AFFICHAGE DE LA LISTE DES LOCATAIRES
    ptr_locataire cursor = head;

    if (cursor == NULL) {  // CHECK IF THE LIST IS EMPTY
        setColor(4); // RED COLOR FOR EMPTY LIST
        printf("\nAUCUN LOCATAIRE TROUVE.\n");
        setColor(7); // RESET COLOR
        return;
    }

    // HEADER FOR THE LIST OF LOCATAIRES
    setColor(14); // YELLOW FOR HEADER
    printf("\n--- LISTE DES LOCATAIRES ---\n");
    setColor(7); // RESET COLOR

    while (cursor != NULL) { // LOOP THROUGH ALL LOCATAIRES AND DISPLAY THEIR DETAILS
        // DISPLAY NAME OF THE LOCATAIRE
        setColor(11); // LIGHT CYAN FOR "NOM"
        printf("NOM            : ");
        setColor(7); // RESET COLOR
        printf("%s\n", cursor->nom);

        // DISPLAY FIRST NAME (PRENOM) OF THE LOCATAIRE
        setColor(11); // LIGHT CYAN FOR "PRENOM"
        printf("PRENOM         : ");
        setColor(7); // RESET COLOR
        printf("%s\n", cursor->prenom);

        // DISPLAY PHONE NUMBER (TELEPHONE) OF THE LOCATAIRE
        setColor(11); // LIGHT CYAN FOR "TELEPHONE"
        printf("TELEPHONE      : ");
        setColor(7); // RESET COLOR
        printf("%s\n", cursor->telephone);

        // DISPLAY THE LOCATAIRE ID
        setColor(11); // LIGHT CYAN FOR "ID LOCATAIRE"
        printf("ID LOCATAIRE   : ");
        setColor(7); // RESET COLOR
        printf("%s\n", cursor->id_locataire);

        // PRINT A SEPARATOR LINE FOR BETTER VISUAL ORGANIZATION
        printf("----------------------------------------\n");

        // MOVE TO THE NEXT LOCATAIRE IN THE LIST
        cursor = cursor->next;
    }
}









void initialiser_locataire(ptr_locataire *head) {// Function to initialize locataire
    *head = NULL;
    ptr_locataire p = NULL;
    ptr_locataire q = NULL;
    ptr_locataire sav=NULL;
    allocate_locataire(head);
    p=*head;
    char NOM[100];
    char PRENOM[100];
    char TELEPHONE[100];
    char line[255];
    char id_locataire[6];
    int stop = 0;
    FILE *fichier = fopen("datafile.txt", "r");
    if (fichier == NULL) {
    printf("Erreur d'ouverture du fichier.\n");
    return;
    }
     while ((stop == 0) && (fgets(line, sizeof(line), fichier))) {
        if (strcmp(line, "\n") == 0) {
            stop = 1;
        }
     }
stop=0;

    while ((stop == 0) && (fgets(line, sizeof(line), fichier))) {
        if (strcmp(line, "\n") == 0) {
            stop = 1;
            Free_locataire(p);
        } else {
            sscanf(line, "%s %s %s ", NOM, PRENOM, TELEPHONE);
            ass_nom(p, NOM);
            ass_prenom(p, PRENOM);
            ass_telephone(p, TELEPHONE);
            ass_id_locataire(p);
            sav=p;
            allocate_locataire(&q);

            ass_adr_locataire(p, q);
            p = q;

        }
    }

    ass_adr_locataire(sav,NULL);
    fclose(fichier);
}

void initialiser_archive_locataire (ptr_locataire *head) {
*head=NULL;
}


/*------------------------------------------------MACHINE ABSTRAITE LOCATION--------------------------------------------------------*/



ptr_location next_location(ptr_location p) {// Function to next address of location
return p->next;
}

void ass_adr_location(ptr_location p, ptr_location q) {// Function to assign address of location
p->next = q;
}


void allocate_location(ptr_location *p) { //Function to allocate memory for a location
*p = malloc(sizeof(struct location));
}

char *generateure_date() {
    int year,month,day;
    char *date=malloc(11);
year=(2025 +rand() % 2);//generating years min=2025 max=2026
month=1+(rand() % 8);//generating mounths min=1 max=11 ,DIDNT SET IT max=12 because it will make the datefin generating process much simpler
day=1+(rand() % 29);//generating days min=1 max=29 ,DIDNT SET IT max=30 because it will make the datefin generating process much simpler

sprintf(date,"%d/%02d/%02d",year,month,day);//ASSIGNING THEM IN DATE VARIABLE IN FORMAT YYYY/MM/DD
return date;
}
void initialiser_location (ptr_location *headlocation,ptr_loge headlogement,ptr_locataire headlocataire) { /*FUNCTION TO INITIALISE THE LOCATION
                                     LISTE (third liste in the TP) FROM THE LOGEMENT AND LOCATAIRE LISTES BY LINKING EACH LOCATAIRE WITH A LOGEMENT*/


ptr_loge cursor1=next_logement(headlogement);       //INITIALISING CURSORS TO THE NEXT NODE AFTER HEAD
ptr_locataire cursor2=next_locataire(headlocataire);

ptr_location p,q;

int temp;
char datedebut[11];
char datefin[11];

allocate_location(headlocation); //ALLOCATING MEMOY FOR THE HEAD OF THE RESULTING LIST

strcpy((*headlocation)->id_logement,headlogement->id_logement);       //PROCESSING THE HEAD FIRST OUTSIDE THE LOOP
strncpy((*headlocation)->id_locataire, headlocataire->id_locataire,7);




strncpy((*headlocation)->date_debut,generateure_date(),10);//ASSIGNING DATE DEBUT
(*headlocation)->date_debut[10]='\0';             //TO PUT AN END TO THE STRING BECAUSE strncpy DOES NOT DO IT BY DEFAULT

strncpy((*headlocation)->date_fin,(*headlocation)->date_debut,10); //ASSIGNING DATE DEBUT TO DATE FIN THEN MODYFYING IT TO INSURE ITS BIGER THAN DATE DEBUT

(*headlocation)->date_fin[6]=(((*headlocation)->date_fin[6] -'0' +1)%10 )+'0';//CHANGING THE DATE FIN BY ADDING ONE MOUNTH FROM DATE DEBUT
(*headlocation)->date_fin[9]=(((*headlocation)->date_fin[9] -'0' +1)%10 )+'0';//CHANGING THE DATE FIN BY ADDING one DAYS FROM DATE FIN

(*headlocation)->date_fin[10]='\0';     //TO PUT AN END TO THE STRING BECAUSE strncpy DOES NOT DO IT BY DEFAULT

p=*headlocation;



while (cursor1!=NULL && cursor2!=NULL) { //PROCESSING THE REST OF THE NODES
allocate_location(&q); // ALLOCATING MEMORY FOR THE NEW NODE

strcpy(q->id_logement,cursor1->id_logement); //ASSIGNING id_logement FROM LOGEMENT LIST TO THE NEW LIST "location list" (the third list the TP)

strncpy(q->id_locataire, cursor2->id_locataire,6);  //ASSIGNING id_locataire FROM LOCATAIRE LIST TO THE NEW LIST "location list" (the third list the TP)


strncpy(q->date_debut,generateure_date(),10); //ASSIGNING DATE DEBUT
q->date_debut[10]='\0';             //TO PUT AN END TO THE STRING BECAUSE strncpy DOES NOT DO IT BY DEFAULT

strncpy(q->date_fin,q->date_debut,10); //ASSIGNING DATE DEBUT TO DATE FIN THEN MODYFYING IT TO INSURE ITS BIGER THAN DATE DEBUT

q->date_fin[6]=((q->date_fin[6] -'0' +1)%10 +'0');//CHANGING THE DATE FIN BY ADDING ONE MOUNTH FROM DATE DEBUT
q->date_fin[9]=((q->date_fin[9] -'0' +1)%10 +'0');//CHANGING THE DATE FIN BY ADDING one DAYS FROM DATE FIN

q->date_fin[10]='\0';     //TO PUT AN END TO THE STRING BECAUSE strncpy DOES NOT DO IT BY DEFAULT

ass_adr_location(p,q);
p=q;
cursor1=next_logement(cursor1);
cursor2=next_locataire(cursor2);
}
ass_adr_location(q,NULL);
}



void initialiser_archive_location(ptr_location *head) {
    *head = NULL; // CLEARING THE LOCATION LIST
}

void afficher_location(ptr_location head) {
// AFFICHAGE DE LA LISTE DES LOCATIONS
ptr_location cursor = head;

if (cursor == NULL) {  // CHECK IF THE LIST IS EMPTY
 setColor(4); // RED COLOR FOR EMPTY LIST
 printf("\nAUCUNE LOCATION TROUVEE.\n");
 setColor(7); // RESET COLOR
return;
}

// HEADER FOR THE LIST OF LOCATIONS
setColor(14); // YELLOW FOR HEADER
printf("\n--- LISTE DES LOCATIONS ---\n");
setColor(7); // RESET COLOR

while (cursor != NULL) { // LOOP THROUGH ALL LOCATIONS AND DISPLAY THEIR DETAILS

// DISPLAY LOGEMENT ID
 setColor(11); // LIGHT CYAN FOR "ID LOGEMENT"
 printf("ID LOGEMENT    : ");
 setColor(7); // RESET COLOR
 printf("%s\n", cursor->id_logement);

// DISPLAY LOCATAIRE ID
 setColor(11); // LIGHT CYAN FOR "ID LOCATAIRE"
 printf("ID LOCATAIRE   : ");
 setColor(7); // RESET COLOR
 printf("%s\n", cursor->id_locataire);

// DISPLAY START DATE
 setColor(11); // LIGHT CYAN FOR "DATE DEBUT"
 printf("DATE DEBUT     : ");
 setColor(7); // RESET COLOR
 printf("%s\n", cursor->date_debut);

// DISPLAY END DATE
 setColor(11); // LIGHT CYAN FOR "DATE DE FIN"
 printf("DATE DE FIN    : ");
 setColor(7); // RESET COLOR
 printf("%s\n", cursor->date_fin);

// PRINT A SEPARATOR LINE FOR BETTER VISUAL ORGANIZATION
 printf("----------------------------------------\n");

// MOVE TO THE NEXT LOCATION IN THE LIST
cursor = cursor->next;
    }
}


void ass_date_debut(ptr_location p, char date[]) {
    strncpy(p->date_debut, date, 10);
    p->date_debut[10] = '\0'; // ENDING STRING PROPERLY
}
void ass_date_fin(ptr_location p, char date[]) {
    strncpy(p->date_fin, date, 10);
    p->date_fin[10] = '\0'; // ENDING STRING PROPERLY
}

/*-----------------------------------------------------------\\\\FIN////---------------------------------------------------------------*/





///***********************************************************FUNCTIONS PRINCIPAL****************************************************************************//



///-------------------------------------------------->>> QUESTION 2_1 <<<-----------------------------------------------------------------\\\

void ajouter_logement(ptr_loge head) { //ADD A NEW LOGEMENT
    ptr_loge cursor=head;


    // Find the last element of the list
    while (next_logement(cursor) != NULL) {
        cursor= next_logement(cursor);
    }

    ptr_loge p;
    allocate_logement(&p);
    ass_adr_logement(cursor, p);


    printf("Entrer le type de logement: ");
    char type[10];
    scanf("%s", type);
    ass_type(p, type);

    printf("Entrer le quartier de logement (sans espace):");
    char quartier[10];
    scanf("%s",quartier);
    ass_quartie(p,quartier);

    printf("Entrer la superficie: ");
    float superficie;
    scanf("%f", &superficie);
    ass_superficie(p,superficie);

    printf("Entrer la distance: ");
    float distance;
    scanf("%f", &distance);
    ass_distance(p, distance);
    ass_loyer(p,calc_loyer(type));

    ass_id_logement_aleatoire(p);

    ass_adr_logement(p, NULL);
}
void ajouter_locataire(ptr_locataire head) { //ADD A NEW LOCATAIRE
    ptr_locataire cursor = head;

    // Find the last element of the list
    while (next_locataire(cursor) != NULL) {
        cursor = next_locataire(cursor);
    }

    ptr_locataire p;
    allocate_locataire(&p);
    ass_adr_locataire(cursor,p);


    printf("Entrer le nom: ");
    char nom[100];
    scanf("%s", nom);
    ass_nom(p, nom);

    printf("Entrer le prenom:");
    char prenom[100];
    scanf("%s",prenom);
    ass_prenom(p,prenom);

    printf("Entrer le numero telephone: ");
    char telephone[100];
    scanf("%s", telephone);
    ass_telephone(p, telephone);
    ass_adr_locataire(p,NULL);
}
void ajouter_location(ptr_location headlocation,ptr_locataire headlocataire /*pour ajouter apres a liste locataire*/) { //FUNCTION ADD A NEW LOCATION
    ptr_location cursor=headlocation;

 ptr_locataire temp;
 allocate_locataire(&temp);/*WE USED THIS VARRIBALE OF TYPE LOCATAIRE BECAUSE WE ARE GOING TO ALLOCATE TEMPORARY LOCATAIRE NODES TO MAKE THE generateure_id_locataire
    FUNCTION WORK ON THIS TEMP NODE SO THE NODE IS NOT TO LINKIT BUT JUST USED LIKE I DESCRIBED AND THIS DECISION WAS MADE BECAUSE THE generateure_id_locataire
    FUNCTION WAS MADE SUCH AS ITS PARAMETER IS A POINTER TO A NODE SO IT EXSTRACT INFO FROM THE NODE THEN GENERATES THE ID AND SINCE WE WORKED ALLOT WITH
    GENERATEURE FUNCTION ,CHANGING IT WILL CONSUME ALLOT OF TIME AND MAY RESULT IN VERY HARD DEBUGGING PROCESS */

    // Find the last element of the list
    while (next_location(cursor) != NULL) {
        cursor= next_location(cursor);
    }

    ptr_location p;
    allocate_location(&p);

    ass_adr_location(cursor, p); //LINKING THE NEW NODE WITH THE LAST ONE IN THE LIST

    printf("--LES INFORMATIONS DONNE MAINTENANT SERENT A AJOUTER UNE NOUVELLE LOCATION\n\n");
    printf("-Apres donner les informations tu aura le choix de les ajouter AUSSI comme un nouveaux locataire dans la liste des locataire\n\n");
    printf("*CAR ce nest pas LOGIQUE DAJOUTER UNE NOUVELLE LOCATION SANS AJOUTER LE NOUVEAUX LOCATAIRE DANS LA LISTES DES LOCATAIRES\n\n");



    printf("Entrer NOM du locataire (POUR GENERE ID_LOCATAIRE): ");
    char nom[50];
    scanf("%s",nom);
    ass_nom(temp,nom); //ASSIGNING THE NOM TO THE TEMP NODE THAT WE TALKED ABOUT LATER

    printf("Entrer le PRENOM du locataire (POUR GENERE ID_LOCATAIRE):");
    char prenom[50];
    scanf("%s",prenom);
    ass_prenom(temp,prenom); //ASSIGNING THE PRENOM TO TEMP NODE THAT WE TALKED ABOUT LATER

    printf("Entrer le NUMERO DE TELEPHONE (doit etre 10 chifres) (POURE GENERE ID_LOCATAIRE): "); //ASSIGNING PHONE NUMBER TO THE TEMPORARY NODE
    char numero[10];
    scanf("%10s",numero);
    ass_telephone(temp,numero);

    //GENERATING THE ID FROM THAT TEMPORARY NODE THEN ASSIGNING IT TO THE NEW NODE IN LOCATION LIST
    strcpy(p->id_locataire,generateure_id_locataire(temp));
    p->id_locataire[6]='\0';
    strcpy(temp->id_locataire,generateure_id_locataire(temp));//ALSO ASSIGNING IT TO TEMP NODE FOR USE LATER IN LOCATAIRE LIST
    temp->id_locataire[6]='\0';

    printf("Entrer le ID du logement (doit etre depuis la liste des logements): "); //ASSIGNING idlogement TO NODE
    char idlogement[6];

    scanf("%s",idlogement);
    strcpy(p->id_logement,idlogement);
    p->id_logement[6]='\0';

    printf("Entrer la date de debut(YYYY/MM/DD): "); //AFFECTATION DE DATE DE DEBUT
    char datedebut[10];
    scanf("%s", datedebut);
    ass_date_debut(p, datedebut);

   p->date_debut[10]='\0';

    printf("Entrer la date de fin(YYYY/MM/DD): "); //AFFECTATION DE DATE DE FIN
    char datefin[10];
    scanf("%s", datefin);

    ass_date_fin(p, datefin);

   p->date_fin[10]='\0';

    ass_adr_location(p, NULL);

//SECOND PART OF THE FUNCTION WHICH CONSISTS OF ADDING THE NEW LOXATION INFO TO THE LOCATAIRE LIST IF NOT DONE BEFORE

printf("------------------------NOTE: Puisque vous avez ajouter une nouvelle location voullez vous ajouter ce nouveau \nlocataire a la listes des locataires si vous ne l'avez pas deja fait");
printf(" ,oui ou non:");
char avis[3];

start: //LABEL WICH IS GONNA BE ACTIVE UNTIL USER INTERS VALID OPINION (OUI ou NON)
scanf("%s",&avis);

ptr_locataire cursor_locataire = headlocataire; //TO SCAN THE LISTE OF LOCATAIRE UNTIL THE END THEN ADDING THE NEW NODE
if (strcasecmp(avis,"oui")==0) {

    // Find the last element of the list
    while (next_locataire(cursor_locataire) != NULL) {
    cursor_locataire = next_locataire(cursor_locataire);
    }
   ass_adr_locataire(cursor_locataire,temp);
    printf("-------------AJOUT AVEC SUCCES--------------\n");
    ass_adr_locataire(temp,NULL);
}
else { if (strcasecmp(avis,"non")!=0) {
printf("######entrez avis valide######");
goto start;

}
}


}
///-------------------------------------------------->>> QUESTION 2_2 <<<-----------------------------------------------------------------\\\

///POUR ARCHIVE:
void ajouter_logement_archive (ptr_loge node) { //ADD A NEW LOGEMENT TO THE ARCHIVE


    ptr_loge cursor= archive_head_logement;    //VERY IMPORTANT NOTE : archive_head_logement est un variable global

if (cursor!=NULL) { //THE CASE OF A NON EMPTY LIST

    // Find the last element of the list
 while (next_logement(cursor) != NULL) {
 cursor= next_logement(cursor);
    }
ass_adr_logement(cursor, node); // LINKING OUR NODE WITH THE ARCHIVE LIST
}
else {
archive_head_logement=node; //THIS IS THE CASE WERE THE LIST IS EMPTY ,DIRECTLY archive_head_logement WILL BECOME THE NODE
}


ass_adr_logement(node, NULL);
}

void ajouter_locataire_archive (ptr_locataire node) { //ADD A NEW LOGEMENT TO THE ARCHIVE
    ptr_locataire cursor= archive_head_locataire;    //VERY IMPORTANT NOTE : archive_head_locataire est un variable global

if (cursor!=NULL) { //THE CASE OF A NON EMPTY LIST

    // Find the last element of the list
 while (next_locataire(cursor) != NULL) {
 cursor= next_locataire(cursor);
    }
ass_adr_locataire(cursor, node); // LINKING OUR NODE WITH THE ARCHIVE LIST
}
else {
archive_head_locataire=node; //THIS IS THE CASE WERE THE LIST IS EMPTY ,DIRECTLY archive_head_logement WILL BECOME THE NODE
}


ass_adr_locataire(node, NULL);
}

void ajouter_location_archive (ptr_location node) { //ADD A NEW LOCATION TO THE ARCHIVE
    ptr_location cursor= archive_head_location;    //VERY IMPORTANT NOTE : archive_head_location est un variable global


if (cursor!=NULL) { //THE CASE OF A NON EMPTY LIST

    // Find the last element of the list
 while (next_location(cursor) != NULL) {
 cursor= next_location(cursor);
    }
ass_adr_location(cursor, node); // LINKING OUR NODE WITH THE ARCHIVE LIST
}
else {
archive_head_location=node; //THIS IS THE CASE WERE THE LIST IS EMPTY ,DIRECTLY archive_head_logement WILL BECOME THE NODE
}
ass_adr_location(node, NULL);
}
///SUPPRESION:
void  suppression_logement (ptr_loge *head,ptr_loge p) {//DELETE A LOGEMENT BASED ON THE POINTER PROVIDED TO THE FUNCTION
ptr_loge cursor=*head; //GIVING THE CURSOR THE REAL HEAD (CURSOR IS LIKE THE ACTUALE NODE)
ptr_loge previous=NULL; //KEEPING TRACK OF PREVIOUS (THE NODE BEFORE CURSOR)

if (cursor==p) { //THE CASE OF THE REQUIRED NODE IS THE HEAD
*head=next_logement(cursor);
ajouter_logement_archive(cursor); //LINKING THE DELETED NODE TO THE ARCHIVE
}

else {

while (next_logement(cursor)!=NULL && cursor!=p ) { //LOOP TO SKIP ALL THE NODES THAT ARE NOT THE ONE MEANT TO BE DELETED
previous=cursor;
cursor=next_logement(cursor);
}

if (cursor==p) { //IF WE FOUND THE REQUIRED NODE
if (next_logement(cursor)==NULL) { //THE REQUIRED NODE IS THE LAST IN THE LIST
ass_adr_logement(previous,NULL);
ajouter_logement_archive(cursor);

}
else {
 //THE REQUIRED NODE IS IN THE MIDDLE OF THE LIST (WHICH MAKES IT REQUIRE MORE WORK TO DELETE IT)
ass_adr_logement(previous,next_logement(cursor));
ajouter_logement_archive(cursor);
}
}
}
}
void  suppression_locataire (ptr_locataire *head,ptr_locataire p) {//DELETE A LOCATAIRE BASED ON THE POINTER PROVIDED TO THE FUNCTION
ptr_locataire cursor=*head; //GIVING THE CURSOR THE REAL HEAD (CURSOR IS LIKE THE ACTUALE NODE)
ptr_locataire previous=NULL; //KEEPING TRACK OF PREVIOUS (THE NODE BEFORE CURSOR)

if (cursor==p) { //THE CASE OF THE REQUIRED NODE IS THE HEAD
*head=next_locataire(cursor);
ajouter_locataire_archive(cursor);
}

else {

while (next_locataire(cursor)!=NULL && cursor!=p ) { //LOOP TO SKIP ALL THE NODES THAT ARE NOT THE ONE MEANT TO BE DELETED
previous=cursor;
cursor=next_locataire(cursor);
}

if (cursor==p) { //IF WE FOUND THE REQUIRED NODE

if (next_locataire(cursor)==NULL) { //THE REQUIRED NODE IS THE LAST IN THE LIST
ass_adr_locataire(previous,NULL);
ajouter_locataire_archive(cursor);
}
else { //THE REQUIRED NODE IS IN THE MIDDLE OF THE LIST (WHICH MAKES IT REQUIRE MORE WORK TO DELETE IT)
ass_adr_locataire(previous,next_locataire(cursor));
ajouter_locataire_archive(cursor);
}
}
}

}


void suprimer_logement_par_id(ptr_loge *headlogement,char id1[]) {  //DELETE A LOGEMENT USING ITS ID

ptr_loge cursor=*headlogement;

while (cursor!=NULL) {

if (strcmp(cursor->id_logement,id1)==0) { //IF A MATCH IS FOUND

suppression_logement(headlogement,cursor); //DELETE THE NODE AND TRANSFER IT TO THE ARCHIVE
}

cursor=next_logement(cursor);
}

}

void suprimer_locataire_par_id(ptr_locataire *headlocataire,char id2[]) {  //DELETE A LOCATAIRE USING ITS ID

ptr_locataire cursor=*headlocataire;

while (cursor!=NULL) {

if (strcmp(cursor->id_locataire,id2)==0) { //IF A MATCH IS FOUND

suppression_locataire(headlocataire,cursor); //DELETE THE NODE AND TRANSFER IT TO THE ARCHIVE
}

cursor=next_locataire(cursor);
}

}

void suprimer_location_par_id(ptr_location *headlocation,char id3[]) { //DELETE A LOCATION USING ITS ID

ptr_location cursor=*headlocation;

while (cursor!=NULL) {

if (strcmp(cursor->id_logement,id3)==0) { //IF A MATCH IS FOUND

suppression_location(headlocation,cursor); //DELETE THE NODE AND TRANSFER IT TO THE ARCHIVE
}

cursor=next_location(cursor);
}


}

void suppression_avec_type (ptr_loge *head,char type[]) { //FUNCTION TO DELETE LOGEMENT BASED IN THE TYPE OF LOGEMENT
ptr_loge cursor=*head;
ptr_loge savecursor=cursor;
while (cursor!=NULL) {
if (strcasecmp(cursor->type,type)==0) { //strcasecmp COMPARES TWO STRINGS IF THEY ARE EQUAL REGARDLESS ITS UPPERCASE OR LOWERCASE
suppression_logement(head,cursor); /*PASSING THE POINTER OF THE NODE TO BE DELETED USING THE FUNCTION WE MADE BEFOREE WHICH TAKE CARE OF DELETING
                                     AND SETTING THE RELATIONS BETWEEN PREVIOUS AND NEXT NODE */
}
cursor=next_logement(savecursor); //BECAUSE CURSOR POINTS TO NOTHING AFTER DELETION SO WE USE SAVECURSOR AS A BACKUP
savecursor=cursor;
}
}
void  suppression_location (ptr_location *head,ptr_location p) {//DELETE A LOCATION BASED ON THE POINTER PROVIDED TO THE FUNCTION
ptr_location cursor=*head; //GIVING THE CURSOR THE REAL HEAD (CURSOR IS LIKE THE ACTUALE NODE)
ptr_location previous=NULL; //KEEPING TRACK OF PREVIOUS (THE NODE BEFORE CURSOR)

if (cursor==p) { //THE CASE OF THE REQUIRED NODE IS THE HEAD
*head=next_location(cursor);
ajouter_location_archive(cursor); //LINKING THE DELETED NODE TO THE ARCHIVE
}

else {

while (next_location(cursor)!=NULL && cursor!=p ) { //LOOP TO SKIP ALL THE NODES THAT ARE NOT THE ONE MEANT TO BE DELETED
previous=cursor;
cursor=next_location(cursor);
}

if (cursor==p) { //IF WE FOUND THE REQUIRED NODE
if (next_location(cursor)==NULL) { //THE REQUIRED NODE IS THE LAST IN THE LIST
ass_adr_location(previous,NULL);
ajouter_location_archive(cursor);

}
else {
 //THE REQUIRED NODE IS IN THE MIDDLE OF THE LIST (WHICH MAKES IT REQUIRE MORE WORK TO DELETE IT)
ass_adr_location(previous,next_location(cursor));
ajouter_location_archive(cursor);
}
}
}
}
///-------------------------------------------------->>> QUESTION 4 <<<----------------------------------------------------------------
void lister_logement_occupe (ptr_location headlocation,ptr_loge headlogement) { //LISTING ALL OCCUPIED LOGMENTS
//headlocation is needed to get the IDS of the occupied logements and the headlogement is needed to find the logements them selfs

ptr_location cursor1=headlocation;
ptr_loge cursor2=headlogement;
char id[6];
bool exit=false;

while (cursor1!=NULL) { //LOOP TO SCAN THE LOCATION LIST AND GET THE ID OF THE LOCATED LOGEMENT EVERY TIME
strcpy(id,cursor1->id_logement); //SAVING THE ID OF THE LOCATION
exit=false;

  while (cursor2!=NULL && exit!=true) {  //LOOP TO SEARCH FOR THE LOGEMENT USING ITS ID IN THE LOGEMENT LIST


   if (strcmp(cursor2->id_logement,id)==0) {  //comparing the strings

 // DISPLAY TYPE OF LOGEMENT
 setColor(11); // blue
 printf("TYPE           : ");
 setColor(7); // RESET COLOR
 printf("%s\n", cursor2->type);

        // DISPLAY THE AREA (SUPERFICIE) OF THE LOGEMENT
 setColor(11); // blue
 printf("SUPERFICIE     : ");
 setColor(7); // RESET COLOR
 printf("%.2f m*m\n", cursor2->superficie);

// DISPLAY THE NEIGHBORHOOD (QUARTIER) OF THE LOGEMENT
 setColor(11); // blue
 printf("QUARTIER       : ");
 setColor(7); // RESET COLOR
 printf("%s\n", cursor2->quartier);

// DISPLAY THE DISTANCE TO THE LOGEMENT
 setColor(11); //blue
 printf("DISTANCE       : ");
 setColor(7); // RESET COLOR
 printf("%.2f km\n", cursor2->distance);

// DISPLAY THE RENT (LOYER) OF THE LOGEMENT
 setColor(11); // blue
 printf("LOYER          : ");
 setColor(7); // RESET COLOR
 printf("%.2f DA\n", cursor2->loyer);

// DISPLAY THE LOGEMENT ID
 setColor(11); // blue
 printf("ID LOGEMENT    : ");
 setColor(7); // RESET COLOR
 printf("%s\n", cursor2->id_logement);

 printf("----------------------------------------\n");
exit=true;
   }
   cursor2=next_logement(cursor2);
  }
cursor1=next_location(cursor1);
}
}
void logement_libre_date (ptr_location headlocation,ptr_loge headlogement,char date[]) { //SHOWS ALL FREE LOGEMENTS AFTER A DATE
    //DEKHELELHA HEAD TA3 LOCATION BACH THAWS FIH 3LA LES DATES WTDI ID W HEAD TA3 LOGEMENT BACH TEDJBED MENOU LOGEMENT W TANIT DATE
ptr_location cursor1=headlocation;
ptr_loge cursor2=headlogement;
char saveid[6];
bool exit,AtLeastOnce=false;
setColor(10);
printf("\n\n-LES LOGEMENTS LIBRES APRES %s SONT :\n\n",date);
setColor(7);
while (cursor1!=NULL ) {

if (strcmp(date,cursor1->date_fin)>0) { //OUR DATE COMES AFTER THE DATE OF THE END OF THE LOCATION

strcpy(saveid,cursor1->id_logement);//SAVING THE ID OF THIS LOGEMENT TO SEARCH ITS INFORMATIONS IN LOGEMENT LIST
exit=false;

  while (cursor2!=NULL && exit!=true) { //LOOP TO SEARCH FOR THE LOGEMENT USING ITS ID IN THE LOGEMENT LIST
   if (stricmp(cursor2->id_logement,saveid)==0) {

   // DISPLAY TYPE OF LOGEMENT
 setColor(11); // LIGHT CYAN FOR "TYPE"
 printf("TYPE           : ");
 setColor(7); // RESET COLOR
 printf("%s\n", cursor2->type);

        // DISPLAY THE AREA (SUPERFICIE) OF THE LOGEMENT
 setColor(11); // LIGHT CYAN FOR "SUPERFICIE"
 printf("SUPERFICIE     : ");
 setColor(7); // RESET COLOR
 printf("%.2f m*m\n", cursor2->superficie);

// DISPLAY THE NEIGHBORHOOD (QUARTIER) OF THE LOGEMENT
 setColor(11); // LIGHT CYAN FOR "QUARTIER"
 printf("QUARTIER       : ");
 setColor(7); // RESET COLOR
 printf("%s\n", cursor2->quartier);

// DISPLAY THE DISTANCE TO THE LOGEMENT
 setColor(11); // LIGHT CYAN FOR "DISTANCE"
 printf("DISTANCE       : ");
 setColor(7); // RESET COLOR
 printf("%.2f km\n", cursor2->distance);

// DISPLAY THE RENT (LOYER) OF THE LOGEMENT
 setColor(11); // LIGHT CYAN FOR "LOYER"
 printf("LOYER          : ");
 setColor(7); // RESET COLOR
 printf("%.2f DA\n", cursor2->loyer);

// DISPLAY THE LOGEMENT ID
 setColor(11); // LIGHT CYAN FOR "ID"
 printf("ID LOGEMENT    : ");
 setColor(7); // RESET COLOR
 printf("%s\n", cursor2->id_logement);

// PRINT A SEPARATOR LINE FOR BETTER VISUAL ORGANIZATIO
 printf("----------------------------------------\n");


    exit=true;
    AtLeastOnce=true;
   }
   cursor2=next_logement(cursor2);
  }
}


cursor1=next_location(cursor1);
}

if (!AtLeastOnce) {
setColor(12); //red
printf("Desole Pas De Logement libre A Cette Date");
setColor(7); // white
printf("\n\nAppuyer Sur N'importe Quelle Bouton Pour Retourner");

getch(); //WAITING THE USER TO TAP ANY BUTTON
} else printf("\n\nAppuyer Sur N'importe Quelle Bouton Pour Retourner");

}
///-------------------------------------------------->>> QUESTION 5 <<<----------------------------------------------------------------\\\
///SAME CONCEPT IN THE FUNCTION OF STUDIO REPEATS IN THE REST OF THE FUNCTIONS

bool liste_location_studio(ptr_location *headstudio, ptr_location headlocation) { ///FUNCTION TO CREATE A NEW LIST CONTAINING ONLY LOCATIONS STUDIO

bool found=false; ///INDICATING IF WE FOUND AT LEAST ONE ELEMENT
ptr_location cursor1=headlocation; // cursor1 WALKS THROUGH the location list SO WE CAN FIND THE LOCATIONS WITH STUDIO LOGEMENT TYPE
ptr_location q=NULL;
ptr_location p=NULL; // TO KEEP TRACK OF THE PREVIOUS NODE IN THE STUDIO LIST WHEN CREATING IT
int i=1; // TO KNOW IF WE ARE IN THE HEAD CASE OR NOT

while (cursor1!=NULL) {    // LOOP TO SCAN THE LOCATION LIST
if (strncasecmp((cursor1->id_logement),"st",2)==0) { /// COMPARING THE FIRST TWO CHARACTERS FROM id_logement WITH "st"=studio -- BECAUSE WE KNOW
                                                    /// THAT THE FIRST TWO CHARACTERS FROM id_logement REPRESENTS THE LOGEMENT TYPE

allocate_location(&q);   // ALLOCATE MEMORY FOR THE NEW NODE

if (i==1) {    ///THE CASE OF THE FIRST NODE BEING CREATED
*headstudio=q;
}

strcpy(q->id_locataire,cursor1->id_locataire);
strcpy(q->id_logement,cursor1->id_logement);
strcpy(q->date_debut,cursor1->date_debut);
strcpy(q->date_fin,cursor1->date_fin);

if (p!=NULL) {
ass_adr_location(p,q);  // LINKING THE PREVIOUS NODE WITH THE CURRENT NODE
}

p=q;
i++; //TO CHANGE THE i SO WE KNOW THAT WE ARE NOT IN THE FIRST NODE
found=true; ///BECOMES TRUE WHEN CREATING AT LEAST ONE NODE -----WE NEED THIS VARIABLE AS RETURN FROM THE FUNCTION FOR LATER USE-----
}

cursor1=next_location(cursor1); // MOVING TO THE NEXT NODE IN THE LOCATION LIST
}


if (p!=NULL) {
ass_adr_location(p,NULL); // TERMINATING THE LIST
}

return found;
}

bool liste_location_f2(ptr_location *head_f2, ptr_location headlocation) {/// FUNCTION TO CREATE A NEW LIST CONTAINING ONLY LOCATIONS f2

bool found=false;
ptr_location cursor1=headlocation; // cursor1 WALKS THROUGH the location list SO WE CAN FIND THE LOCATIONS WITH f2 LOGEMENT TYPE
ptr_location q=NULL;
ptr_location p=NULL; // TO KEEP TRACK OF THE PREVIOUS NODE IN THE f2 LIST WHEN CREATING IT
int i=1; // TO KNOW IF WE ARE IN THE HEAD CASE OR NOT

while (cursor1!=NULL) {    // LOOP TO SCAN THE LOCATION LIST
if (strncasecmp((cursor1->id_logement),"f2",2)==0) {  /// COMPARING THE FIRST TWO CHARACTERS FROM id_logement WITH "f2" -- BECAUSE WE KNOW
                                                     /// THAT THE FIRST TWO CHARACTERS FROM id_logement REPRESENTS THE LOGEMENT TYPE

allocate_location(&q); // ALLOCATE MEMORY FOR A NEW NODE

if (i==1) {
*head_f2=q;
}

strcpy(q->id_locataire,cursor1->id_locataire);
strcpy(q->id_logement,cursor1->id_logement);
strcpy(q->date_debut,cursor1->date_debut);
strcpy(q->date_fin,cursor1->date_fin);

if (p!=NULL) {
ass_adr_location(p,q);
}

p=q;
i++;
found=true;
}

cursor1=next_location(cursor1); // MOVING TO THE NEXT NODE IN THE LOCATION LIST
}

if (p!=NULL) {
ass_adr_location(p,NULL); // TERMINATING THE LIST
}

return found;
}

bool liste_location_f3(ptr_location *head_f3, ptr_location headlocation) {/// FUNCTION TO CREATE A NEW LIST CONTAINING ONLY LOCATIONS f3

bool found=false;
ptr_location cursor1=headlocation; // cursor1 WALKS THROUGH the location list SO WE CAN FIND THE LOCATIONS WITH f3 LOGEMENT TYPE
ptr_location q=NULL;
ptr_location p=NULL; // TO KEEP TRACK OF THE PREVIOUS NODE IN THE f3 LIST WHEN CREATING IT
int i=1; // TO KNOW IF WE ARE IN THE HEAD CASE OR NOT

while (cursor1!=NULL) { // LOOP TO SCAN THE LOCATION LIST
if (strncasecmp((cursor1->id_logement),"f3",2)==0) {/// COMPARING THE FIRST TWO CHARACTERS FROM id_logement WITH "f3" -- BECAUSE WE KNOW
                                                   /// THAT THE FIRST TWO CHARACTERS FROM id_logement REPRESENTS THE LOGEMENT TYPE

allocate_location(&q); // ALLOCATE MEMORY FOR A NEW NODE

if (i==1) {
*head_f3=q;
}

strcpy(q->id_locataire,cursor1->id_locataire);
strcpy(q->id_logement,cursor1->id_logement);
strcpy(q->date_debut,cursor1->date_debut);
strcpy(q->date_fin,cursor1->date_fin);

if (p!=NULL) {
ass_adr_location(p,q);
}
p=q;
i++;
found=true;
}

cursor1=next_location(cursor1); // MOVING TO THE NEXT NODE IN THE LOCATION LIST
}

if (p!=NULL) {
ass_adr_location(p,NULL); // TERMINATING THE LIST
}
return found;
}

bool liste_location_f4(ptr_location *head_f4, ptr_location headlocation) {/// FUNCTION TO CREATE A NEW LIST CONTAINING ONLY LOCATIONS f4

bool found=false;
ptr_location cursor1=headlocation; // cursor1 WALKS THROUGH the location list SO WE CAN FIND THE LOCATIONS WITH f4 LOGEMENT TYPE
ptr_location q=NULL;
ptr_location p=NULL; // TO KEEP TRACK OF THE PREVIOUS NODE IN THE f4 LIST WHEN CREATING IT
int i=1; // TO KNOW IF WE ARE IN THE HEAD CASE OR NOT

while (cursor1!=NULL) {  // LOOP TO SCAN THE LOCATION LIST
if (strncasecmp((cursor1->id_logement),"f4",2)==0) {/// COMPARING THE FIRST TWO CHARACTERS FROM id_logement WITH "f4" -- BECAUSE WE KNOW
                                                   /// THAT THE FIRST TWO CHARACTERS FROM id_logement REPRESENTS THE LOGEMENT TYPE

allocate_location(&q); // ALLOCATE MEMORY FOR A NEW NODE

if (i==1) {
*head_f4=q;
}

strcpy(q->id_locataire,cursor1->id_locataire);
strcpy(q->id_logement,cursor1->id_logement);
strcpy(q->date_debut,cursor1->date_debut);
strcpy(q->date_fin,cursor1->date_fin);

if (p!=NULL) {
ass_adr_location(p,q);
}

p=q;
i++;
found=true;
}

cursor1=next_location(cursor1); // MOVING TO THE NEXT NODE IN THE LOCATION LIST
}

if (p!=NULL) {
ass_adr_location(p,NULL); // TERMINATING THE LIST
}
return found;
}


/// ******************** question 5-2(merger plusiers list)*******************************************************

void affectation(ptr_location p, ptr_location t)// on utilise cette fonction pour affecter les valeurs
{


strcpy(p->id_logement,t->id_logement);// affecter id_logement
strcpy(p->date_debut,t->date_debut);// affecter la date de debut
strcpy(p->date_fin,t->date_fin); // affecter la date de fin
strcpy(p->id_locataire,t->id_locataire); // affecter id_locataire


}

///**********************************************************************************************************************
void merge_sort(ptr_location head1,ptr_location head2,ptr_location *head_merge,ptr_loge headlogement)
{// cette fonction merger 2 list
ptr_location p1=head1;
ptr_location p2=head2;
p1=head1;
p2=head2;
ptr_location p;
ptr_location tmp;
allocate_location(head_merge);
p=*head_merge;
while((p1 != NULL)&&(p2 != NULL))
{
if (find_loyer_logement(headlogement,p1->id_logement)<find_loyer_logement(headlogement,p2->id_logement))
{
affectation(p,p1);
 p1=next_location(p1);
}
else
{
affectation(p,p2);
 p2=next_location(p2);
}
allocate_location(&tmp);
ass_adr_location(p,tmp);
p=tmp;
}
//----------------------------------------------------------
if(p1==NULL)
{
affectation(p,p2);
p2=next_location(p2);

while(p2!=NULL)
{


allocate_location(&tmp);
ass_adr_location(p,tmp);

p=tmp;
affectation(p,p2);
p2=next_location(p2);
}
ass_adr_location(p,NULL);
}

else
{
//---------------------------------------------------------
affectation(p,p1);
p1=next_location(p1);

while(p1!=NULL)
{


allocate_location(&tmp);
ass_adr_location(p,tmp);

p=tmp;
affectation(p,p1);
p1=next_location(p1);
}
ass_adr_location(p,NULL);
}
}
void merge_tout_sort(ptr_location head1,ptr_location head2,ptr_location head3,ptr_location head4,ptr_location *head_sort,ptr_loge headlogement)
{ // cette fonction merger tous list(chof kkhadmo bhadi pisque hadi tmargihm kamal
merge_sort(head1,head2,head_sort,headlogement);
merge_sort( *head_sort,head3,head_sort,headlogement);
merge_sort(*head_sort,head4,head_sort,headlogement);
}
/// ***********************************sorter  listes avec loyer************************************//

float find_loyer_logement(ptr_loge head, char id[])
{ // cette fonction pour determine loyer d un location avec id_logement
    ptr_loge p = head;
    while (p != NULL) {
        if (strcmp(id_logement(p), id) == 0) {
            return loyer_logement(p);
        }
        p = next_logement(p);
    }
return -1;
}
void swape(ptr_location p,ptr_location t)
{// cette fonction pour swiper les champs de 2 lists
 char c [100];
strcpy(c,p->id_logement);
strcpy(p->id_logement,t->id_logement);
strcpy(t->id_logement,c);
strcpy(c,p->date_debut);
strcpy(p->date_debut,t->date_debut);
strcpy(t->date_debut,c);
strcpy(c,p->date_fin);
strcpy(p->date_fin,t->date_fin);
strcpy(t->date_fin,c);
strcpy(c,p->id_locataire);
strcpy(p->id_locataire,t->id_locataire);
strcpy(t->id_locataire,c);

}


ptr_location min_loyer(ptr_location head_s,ptr_loge headlogement)
{ // cette fonction pour determine l'adress de location que a le plus min loyer
ptr_location p=head_s;
ptr_location sav;
float min=find_loyer_logement(headlogement,p->id_logement);
while(p!=NULL)
{
if (min>find_loyer_logement(headlogement,p->id_logement))
{
min=find_loyer_logement(headlogement,p->id_logement);
sav=p;
}
p=next_location(p);
}
return sav;
}
void sort(ptr_location head_s,ptr_loge headlogement)
{ // cette function pour sorter la liste de location (principe)
ptr_location p=head_s;

while(next_location(p)!= NULL)
{
ptr_location t=min_loyer(p,headlogement);
if(find_loyer_logement(headlogement,p->id_logement)>find_loyer_logement(headlogement,t->id_logement))
{
swape(p,t);

}

p=next_location(p);
}
}

//***********************************************************************************************************************************************

///-------------------------------------------------->>> QUESTION 6 <<<-----------------------------------------------------------------\\\


ptr_locataire find_locataire(ptr_locataire headlocataire, char id[6]) { ///FUNCTION TO RETURN THE CORESPONDING LOCATAIRE FROM THE GIVEN ID
    ptr_locataire p;
    p = headlocataire;

    while (p != NULL) {
        if (strcmp(p->id_locataire, id) == 0) {
            return p;
        }
        p = next_locataire(p);
    }

    return NULL;
}
float  find_superficie_logement(ptr_loge head,char id[])
{
ptr_loge p;
int stop=0;
p=head;
while((p!=NULL)&&(stop==0))
{
 if (strcmp(id_logement(p),id)==0)
 {
  stop= 1;
  return superficie_logement(p);
 }
 p=next_logement(p);
}
}
char* find_type_logement(ptr_loge head,char id[])
{
ptr_loge p;
int stop=0;
p=head;
while((p!=NULL)&&(stop==0))
{
 if (strcmp(id_logement(p),id)==0)
 {
  stop= 1;
  return type_logement(p);
 }
p=next_logement(p);
}
}


void ajouter_nouvelle(ptr_locataire *meme_headlocataire, ptr_locataire p)
{
    if (*meme_headlocataire == NULL)
    {

        allocate_locataire(meme_headlocataire);

        ptr_locataire t = *meme_headlocataire;

        ass_nom(t, p->nom);
        ass_prenom(t, p->prenom);
        ass_telephone(t,p->telephone);
        strcpy(t->id_locataire,p->id_locataire);
        ass_adr_locataire(t, NULL);
    }
    else
    {
        ptr_locataire t = *meme_headlocataire;
        while (next_locataire(t) != NULL)
        {
            t = next_locataire(t);
        }
        ptr_locataire tmp;
        allocate_locataire(&tmp);
        ass_adr_locataire(t, tmp);
        //----------------------------------
        ass_nom(tmp, p->nom);
        ass_prenom(tmp, p->prenom);
        ass_telephone(tmp,p->telephone);
        strcpy(tmp->id_locataire,p->id_locataire);
        ass_adr_locataire(tmp,NULL);
    }
}

void meme_type(ptr_location headlocation, ptr_loge headlogement, ptr_locataire headlocataire, ptr_locataire *head_locataire_meme_type, char type[]) {
    ptr_location p = headlocation;
    ptr_locataire t;

    while (p != NULL) {
        // Check if the type of logement matches and if the superficie is greater than average
        if ((strncmp(find_type_logement(headlogement, p->id_logement), type,2) == 0) &&
            (find_superficie_logement(headlogement, p->id_logement) > superficie_moyenne(type))) {

            // Find the locataire associated with this location
            t = find_locataire(headlocataire, p->id_locataire);

            // If the locataire is valid, add it to the new list
            if (t != NULL) {
                ajouter_nouvelle(head_locataire_meme_type, t);
            }
        }
        // Move to the next location in the list
        p = next_location(p);
    }
}

///-----------------------------------------------------------------------------------------------------------------\\\
///-------------------------------------------------->>> QUESTION 8 <<<-----------------------------------------------------------------\\\




void ajouter_nouveaux_min(ptr_loge *meme_headlocation, ptr_loge p) { // FUNCTION TO ADD NEW LOGEMENT TO THE MIN_DISATNCE LIST FROM QUESTION 8


    if (*meme_headlocation == NULL) { //CASE OF NEW STARTED LIST
        allocate_logement(meme_headlocation);
        ptr_loge t = *meme_headlocation;
        ass_type(t, p->type);
        ass_superficie(t, p->superficie);
        ass_quartie(t, p->quartier);
        ass_distance(t,p->distance);
        ass_loyer(t,p->loyer);
        strcpy(t->id_logement,p->id_logement);
        ass_adr_logement(t, NULL);
    }

    else {   // CASE OF LIST ALREADY GOT STARTED
        ptr_loge t = *meme_headlocation;
        while (next_logement(t) != NULL)
        {
            t = next_logement(t);
        }
        ptr_loge tmp;
        allocate_logement(&tmp);
        ass_adr_logement(t, tmp);
        //----------------------------------
        ass_type(tmp, p->type);
        ass_superficie(tmp, p->superficie);
        ass_quartie(tmp, p->quartier);
        ass_distance(tmp, p->distance);
        ass_loyer(tmp,p->loyer);
        strcpy(tmp->id_logement,p->id_logement);
        ass_adr_logement(tmp, NULL);
    }
}

ptr_loge min_adr_loyer(ptr_loge headlogement) {  /// FUNCTION TO RETURN THE LOGEMENT WITH THE LOWEST PRICE (PLUS PETIT LOYER)
    float min = loyer_logement(headlogement);
    ptr_loge p = headlogement;
    ptr_loge save;

    while (p != NULL)
    {
        if (min > loyer_logement(p))
        {
            min = loyer_logement(p);
            save=p;
        }
        p = next_logement(p);
    }
    save->next=NULL;
    return save;
}

void logement_proche_loyer_minimale(ptr_loge *minheadlogement, ptr_loge headlogement, float distance) { ///FUNCTION TO ADD ALL THE LOGEMENTS WITH LESS (DISTANCE)

    ptr_loge p = headlogement;
    while (p != NULL)
    {
        if (distance_logement(p) < distance)
        {
      ajouter_nouveaux_min(minheadlogement, p);
        }
        p = next_logement(p);
    }
}
///--------------------------------------------------------------------------------------------------------------
///-------------------------------------------------->>> QUESTION 7_1 <<<-----------------------------------------------------------------\\\

void allocate_classer(ptr_classer *p)
{
    *p = malloc(sizeof(struct classer));
}

char* quartie_logement(ptr_loge p)
{
    return p->quartier;
}

char* find_quartie_logement(ptr_loge head, char id[])
{
    ptr_loge p = head;
    while (p != NULL) {
        if (strcmp(id_logement(p), id) == 0) {
            return quartie_logement(p);
        }
        p = next_logement(p);
    }
    return NULL;
}

void nouveaux_list(ptr_classer *headnombre, char q[])
{
    if (*headnombre == NULL) {
        allocate_classer(headnombre);
        ptr_classer t = *headnombre;
        strcpy(t->quartier, q);
        t->nombre = 1;
        t->next = NULL;
    } else {
        ptr_classer p = *headnombre;
        int stop = 0;
        while ((p != NULL)&&(stop==0)) {
            if (strcmp(p->quartier, q) == 0) {
                p->nombre++;
                stop = 1;
            }
            p = p->next;
        }
        if (stop == 0) {
            ptr_classer t = *headnombre;
            while (t->next != NULL) {
                t = t->next;
            }
            ptr_classer tmp;
            allocate_classer(&tmp);
            t->next = tmp;
            strcpy(tmp->quartier, q);
            tmp->nombre = 1;
            tmp->next = NULL;
        }
    }
}

void nombre_logement_loue_par_quartier(ptr_locataire headlocation, ptr_loge headlogement,ptr_location headarchive, ptr_classer *headnombre, char anne[])
{
    ptr_location p = headlocation;
    while (p != NULL) {
        char c[5];
        strncpy(c, p->date_debut, 4);
        c[4] = '\0';
        if (strcmp(c, anne) == 0) {
            nouveaux_list(headnombre, find_quartie_logement(headlogement, p->id_logement));
        }
        p = next_location(p);
    }
     p=headarchive;
     while (p != NULL) {
        char c[5];
        strncpy(c, p->date_debut, 4);
        c[4] = '\0';
        if (strcmp(c, anne) == 0) {
            nouveaux_list(headnombre, find_quartie_logement(headlogement, p->id_logement));
        }
        p = next_location(p);
    }


}
///-------------------------------------------------->>> QUESTION 7_2 <<<-----------------------------------------------------------------\\\


/// WE ARE GOING TO USE THE LISTS FROM QUESTION 5 >>(THE LISTS OF LOCATIONS BY TYPE)<<


/*WE ARE GOING TO CALCULATE THE NUMBER OF LOCATIONS FROM LOCATIONS LISTE OF EACH TYPE >>(MADE IN QUESTION 5)<< AND THE ARCHIVE OF LOCATION
LISTE SO WE TOOK IN CONSIDERATION THE DELETED DATA*/


///WE ARE GOING TO USE THE LENGTH FUNCTION TO GET THE NUMBER OF LOCATIONS OF EACH TYPE FROM ITS SPECIFIED LIST SINCE IT IS THE LENGTH OF THE LIST

int lengthll (ptr_location head) { ///FUNCTION TO CALCULATE THE LENGTH OF A LINKED LIST
int cpt=0;
ptr_location cursor;
cursor=head;
while (cursor != NULL) {
cpt++;
cursor=next_location(cursor);
}
return cpt;
}

int cpt_f4_archive(ptr_location archive_head_location) { ///FUNCTION TO COUNT THE NUMBER OF LOCATIONS WITH f4 TYPE
int cpt=0;
ptr_location cursor=archive_head_location;

while (cursor!=NULL) {

if (strncmp(cursor->id_logement,"f4",2)==0) cpt++;
 cursor=next_location(cursor);
}
return cpt;
}

int cpt_f3_archive(ptr_location archive_head_location) { ///FUNCTION TO COUNT THE NUMBER OF LOCATIONS WITH f3 TYPE
int cpt=0;
ptr_location cursor=archive_head_location;

while (cursor!=NULL) {

if (strncmp(cursor->id_logement,"f3",2)==0) cpt++;
 cursor=next_location(cursor);
}
return cpt;
}

int cpt_f2_archive(ptr_location archive_head_location) { ///FUNCTION TO COUNT THE NUMBER OF LOCATIONS WITH f2 TYPE
int cpt=0;
ptr_location cursor=archive_head_location;

while (cursor!=NULL) {

if (strncmp(cursor->id_logement,"f2",2)==0) cpt++;
 cursor=next_location(cursor);
}
return cpt;
}

int cpt_studio_archive(ptr_location archive_head_location) { ///FUNCTION TO COUNT THE NUMBER OF LOCATIONS WITH studio TYPE
int cpt=0;
ptr_location cursor=archive_head_location;

while (cursor!=NULL) {

if (strncmp(cursor->id_logement,"st",2)==0) cpt++; //st "first two letters of studio"
 cursor=next_location(cursor);
}
return cpt;
}

void nombre_locations_par_type (ptr_location head_f4,ptr_location head_f3,ptr_location head_f2,ptr_location head_studio) { ///PRINCIPAL FUNCTION
int cpt;
//CALCULATING FROM THE LOCATION
printf("nombre de locations STUDIO:%d\n",lengthll(head_studio)+cpt_studio_archive(archive_head_location));
printf("nombre de locations F2:%d\n",(lengthll(head_f2)+cpt_f2_archive(archive_head_location)));
printf("nombre de locations F3:%d\n",(lengthll(head_f3)+cpt_f3_archive(archive_head_location)));
printf("nombre de locations F4:%d\n",(lengthll(head_f4)+cpt_f4_archive(archive_head_location)));
}


bool check_date_valide(char date[]) {

return (date[4]=='/' && date[7]=='/') ;
}





// Fonction pour changer la couleur du texte dans CMD
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void afficher_debut_programe () { //Fenction pour premier affichage quand debut du programe
setColor(12); // ROUGE
    printf(" \nNOTE >>>>>>>>>>>>>>>>>>>>>> ");
    setColor(6); // BLANC
    printf("POUR UN AFFICHAGE CORRECTE UTILISER LE MODE PLEIN ECRANT");
    setColor(12); // ROUGE
    printf(" <<<<<<<<<<<<<<<<<<<<<<<< ");
    setColor(7); // BLANC
    printf("\n\nappuyez sur n'importe quelle bouton pour commencer");
    getch(); // WAITING THE USER TO PRESS ANY KEY

}









void afficher_Banniere_principale() {  // Fonction pour afficher la bannière principale
    system("cls"); // Nettoyer l'écran
    setColor(14); // Jaune
    printf("\n                                                                     ======================================================================================\n");
    setColor(12); // Rouge
    printf("                                                                                                --SYSTEME DE GESTION DE LOCATION-- \n                                                                                                         -IMMOBILIERE-\n");
    setColor(14);
    printf("                                                                     ======================================================================================\n\n");
    setColor(7); // Blanc (remettre par défaut)
}



// Fonction pour afficher une belle bannière
void afficher_Banniere_Note() {
    setColor(14); // Jaune
    printf("\n                                                                     ======================================================================================\n");
    setColor(12); // Rouge
    printf("                                                                                                --SECTION INSTRUCTIONS ET EXPLICATIONS-- \n");
    setColor(14);
    printf("                                                                     ======================================================================================\n\n");
    setColor(7); // Blanc (remettre par défaut)
}



// Fonction pour afficher le menu principal
void afficher_Menu() {
    setColor(14); // JAUNE
    printf("\n===============> ");
    setColor(4); // ROUGE
 printf("REMARQUE IMPORTANTE : Soyez Sur que Toutes Les entres Dans LE Programe Soit en MINISCULE pour garantire le fenctionement correcte du logiciel ");
    setColor(14); // JAUNE
    printf(" <================\n\n\n");
    printf("=> IL YA UN SEULE FICHIER NOME 'datafile.txt' QUI CONTIENT TOUTES LES ENTRE,LE PREMIER PARAGRAPHE PRESENTE LES INFORMATIONS DES LOGEMENTS APRES UNE LIGNE COMMENCE LE DEUXIEME PARAGRAPHE CONTENENT LES INFORMATION DES LOCATAIRE .\n\n");
    setColor(7); // BLANC

    printf("\n--- Menu Principal ---\n\n");
        setColor(8); // GRIS
        printf("0. IMPORTANT: A LIRE AVENT LE DEBUT DU PROGRAME\n");
        setColor(10); // VERT
        printf("1. Ajouter un logement, locataire ou location , Q2_1\n");
        printf("2. Suppression d'un logement, locataire, location , Q2_2\n");
        printf("3. Liste des logements occupes et libre a une date done , Q4 \n");
        printf("4. Locations par type, Tri et fusion , Q5 \n");
        printf("5. Liste des locataires avec criteres specifiques , Q6\n");
        printf("6. Chercher les logements les plus proches et abordables , Q8\n");
        printf("7. Consulter l'historique des logements et locations par annee , Q7 \n");
        setColor(3); //
        printf("8. Consulter les listes\n");
        printf("9. Consulter les listes archives\n");
        setColor(8); // ROUGE
        printf("10. Quitter\n");

        setColor(6); // Orange
        printf("\nEntrez votre choix : ");
        setColor(7); // Blanc
}

void afficher_question_7(ptr_classer headnombre) { // Function to display the list of classer

    printf("\n");
    while (headnombre != NULL) { // scaning the linked list

        printf("Quartier: %-20s | Nombre: %d\n", headnombre->quartier, headnombre->nombre); // Print the quartier and nombre for each node

        // Move to the next node in the list
        headnombre = headnombre->next;
    }
}

void afficher_Sous_Menu_ajout() {
    system("cls"); // Nettoyer l'écran
    setColor(6); // Orange
    printf("\n--- Menu d'ajout ---\n");
    setColor(7); // Blanc
    printf("1. Ajouter un nouveau logement\n");
    printf("2. Ajouter un nouveau locataire\n");
    printf("3. Ajouter une nouvelle location\n");
    setColor(12); // Rouge pour retour
    printf("4. Retour\n");
    setColor(7); // Blanc
    printf("\nEntrez votre choix : ");
}

void afficher_Sous_Menu_supression() {
        system("cls"); // Nettoyer l'écran
        setColor(6); // Orange
        printf("\n--- Menu de suppression ---\n");
        setColor(7); // Blanc
        printf("1. Supprimer un logement\n");
        printf("2. Supprimer un locataire\n");
        printf("3. Supprimer une location\n");
        setColor(12); // Rouge pour retour
        printf("4. Retour\n");
        setColor(7); // Blanc
        printf("\nEntrez votre choix : ");
}


void afficher_Sous_Menu_3() {
        system("cls"); // Nettoyer l'écran
        setColor(6); // Orange
        printf("\n--- Menu de consultation ---\n");
        setColor(7); // Blanc
        printf("1. Afficher les logement occupes\n");
        printf("2. Afficher logement libre a une date\n");
        setColor(12); // Rouge pour retour
        printf("4. Retour\n");
        setColor(7); // Blanc
        printf("\nEntrez votre choix : ");
}


void afficher_Sous_Menu_4() {
        system("cls"); // Nettoyer l'écran
        setColor(6); // Orange
        printf("\n--- Menu 4 ---\n");
        setColor(7); // Blanc

        printf("1. Afficher La Liste Des Locations De Type Studio\n");
        printf("2. Afficher La Liste Des Locations De Type F2\n");
        printf("3. Afficher La Liste Des Locations De Type F3\n");
        printf("4. Afficher La Liste Des Locations De Type F4\n");
        printf("5. Afficher La Liste Des Locations trie et fusione\n");


        setColor(12); // Rouge pour retour
        printf("6. Retour\n");
        setColor(7); // Blanc
        printf("\nEntrez votre choix : ");
}



void afficher_Sous_Menu_5() {
        system("cls"); // Nettoyer l'écran
        setColor(6); // Orange
        printf("\n--- Menu 5 ---\n");
        setColor(7); // Blanc

        printf("1. Afficher La Liste Des Locataires Occupant un Logement de Meme Type et Dont La Superficie Depassant La Superficie Moyenne\n");
        setColor(12); // Rouge pour retour
        printf("2. Retour\n");
        setColor(7); // Blanc
        printf("\nEntrez votre choix : ");
}


void afficher_Sous_Menu_6() {
        system("cls"); // Nettoyer l'écran
        setColor(6); // Orange
        printf("\n--- Menu 6 ---\n");
        setColor(7); // Blanc

        printf("1. Chercher le Logement Le Plus Proche de la commune et ayant un loyer minimal\n");
        setColor(12); // Rouge pour retour
        printf("2. Retour\n");
        setColor(7); // Blanc
        printf("\nEntrez votre choix : ");
}


void afficher_Sous_Menu_7() {
        system("cls"); // Nettoyer l'écran
        setColor(6); // Orange
        printf("\n--- Menu 7 ---\n");
        setColor(7); // Blanc

        printf("1.  nombre de logements qui ont ete loues classee par quartier\n");
        printf("2.  nombre total des locations par type de logement\n");


        setColor(12); // Rouge pour retour
        printf("3. Retour\n");
        setColor(7); // Blanc
        printf("\nEntrez votre choix : ");
}


void afficher_Sous_Menu_8() {

system("cls"); // Nettoyer l'écran
        setColor(6); // Orange
        printf("\n--- Menu 8 ---\n");
        setColor(7); // Blanc

        printf("1. Consulter Liste Logement\n");
        printf("2. Consulter Liste Locataire\n");
        printf("3. Consulter Liste Location\n");

        setColor(12); // Rouge pour retour
        printf("4. Retour\n");
        setColor(7); // Blanc
        printf("\nEntrez votre choix : ");

}


void afficher_Sous_Menu_9() {

system("cls"); // Nettoyer l'écran
        setColor(6); // Orange
        printf("\n--- Menu 9 ---\n");
        setColor(7); // Blanc

        printf("1. Consulter Archive Logement\n");
        printf("2. Consulter Archive Locataire\n");
        printf("3. Consulter Archive Location\n");

        setColor(12); // Rouge pour retour
        printf("4. Retour\n");
        setColor(7); // Blanc
        printf("\nEntrez votre choix : ");

}





// Fonction pour afficher un message d'introduction
void afficher_Introduction() {
    setColor(11); // Bleu clair
    printf("Bienvenue dans le logiciel de gestion de location immobiliere.\n");
    printf("Ce programme permet d'enregistrer et de gerer les logements, les locataires et les locations.\n");
    printf("Utilisez le menu pour naviguer entre les differentes fonctionnalites.\n\n");
    setColor(7); // Blanc (remettre par défaut)
}


void afficher_Notes_Importantes () {  //FENCTION POUR AFFICHAGE QUAND CHOISIRE L'OPTION 0 DANS LE MENU QUI EST SPECIFIQUE POUR AFFICHER DES REMARQUES ET DES INSTRUCTION
system("cls"); // Nettoyer l'écran
                setColor(6); // Orange
                afficher_Banniere_Note();
                printf("---ATTENTION--- : LES DATES DE DEBUT ET DE FIN DES PREMIERES LOCATIONS QUI SONT CHARGE DEPUIS LE FICHIER SONT ALEATOIRES DONC LE RESULTAT VA CHANGER POUR CHAQUE NOUVELLE OUVERTURE DU PROGRAME\n\n\n");

                setColor(14); // Orange

                printf("---ATTENTION--- : TOUTES LES ENTRE DOIVENT ETRE EN MINISCULE PAR EXEMPLE N'ECRIVEZ PAS F4 MAIS f4\n\n\n");

                setColor(11); //BLEU
                printf("=========================================================================================================================================================================================\n\n");
                printf("=========================================================================================================================================================================================\n\n");
                setColor(7); //BLANC

                printf("---ATTENTION--- : LES DEUX PREMIER CHARACHTERS DE id_logement PRESENTENT LE TYPE DE LOGEMENT DONC VOUS DEVEZ REMPLIR UN ID VALIDE DE FORMAT typeXXXX  AVEC TYPE DOIT ETRE :\n _________________________ \n|st=studio                |\n|f2=logement de type f4   |\n|f3=logement de type f3   |\n|f4=logement de type f4   |\n|_________________________|\n\n\n");
                printf("--EXEMPLE :POUR UN LOGEMENT DE TYPE F3 LE id_logement DOIT ETRE : f3XXXX ; avec XXXX un chiffre aléatoire vous êtes libres de l'écrire mais à la suite du programme quand vous ajoutez des logements au cours du programme cette opération sera faite AUTOMATIQUEMENT\n\n");
                printf(" LE type studio est equivalent a st \n\n\n");

                setColor(11); //BLEU
                printf("=========================================================================================================================================================================================\n\n");
                printf("=========================================================================================================================================================================================\n\n");
                setColor(7); //BLANC

                printf("---ATTENTION--- : LE PREMIER CHARACHTER DE id_locataire PRESENTE LA PREMIER LETRE DE SON PRENOM ET LE DEUXIEME CHARACHTER PRESENTE LA PREMIERE LETRE DE SON NOM ET LE RESTE DE ID EST LES 4 DERNIER NOMBRE DE SON NUMERO TELEPHOE DONC LE FORMAT PNXXXX\n\n\n");
                printf("--EXEMPLE :POUR UN LOCATAIRE YAHIAOUI RABAH et son numero 0552473456 id_locataire DOIT ETRE : YR3456\n\n");
                printf("cette opperation sera faite AUTOMATIQUEMENT donc vous etes libre de remplir le fichier car vous n'etes pas oblige dentre le id il sera genere automatiquement\n\n");

                setColor(11); //BLEU
                printf("=========================================================================================================================================================================================\n\n");
                printf("=========================================================================================================================================================================================\n\n");
                setColor(7); //BLANC

                setColor(12); // Rouge pour retour
                printf("1. Retour\n");
                setColor(7); // Blanc
                printf("\nEntrez votre choix : ");

}



void activerModeAnsi() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;

    if (hOut == INVALID_HANDLE_VALUE) return;

    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING (défini en dur)

    SetConsoleMode(hOut, dwMode);
}



void reinitialiser_curseure () { //FUNCTION TO RETURN THE CURSOR TO THE START AND DELETE THE SPECIFIC WRITTING
    //(SON BUT EST DE PERMETRE A L'UTILISATEURE QUAND IL ENTRE AUTRE CHOSE QUN ENTIER QUAND IL CHOISIRA LES CHOIS DANS LE MENU DEFACER LECRANT ET REECRIR
    // EN DEBUTANT A LA MEME PLACE A CHAQUE FOIS )

            printf("\033[3A"); // Retourner 3 lignes en arrière
            printf("\r\033[K\n"); // Effacer la ligne actuelle et passer à la suivante
            printf("\r\033[K\n"); // Effacer la ligne actuelle et passer à la suivante
            printf("\r\033[K\n"); // Effacer la ligne actuelle et passer à la suivante
            printf("\r\033[K\n"); // Effacer la ligne actuelle et passer à la suivante
            printf("\r\033[K\n"); // Effacer la ligne actuelle et passer à la suivante
            printf("\033[6A"); // Retourner 6 lignes en arrière

            printf("\033[22G"); // Déplacer le curseur à la colonne 22
            printf("\033[K"); // Effacer le reste de la ligne



}




int gerer_entre_pas_entier_dans_le_menu () { // Fenction pour Gérer le cas où l'entrée n'est pas un entier
int choix;
char ch;
while ((scanf("%d", &choix)) != 1) {
            setColor(4); // Rouge
            printf("\nOption invalide.");
            setColor(7); // Blanc
            printf("\n\nappuyez sur n'importe quelle bouton pour recommencer A NOUVEAU ");
            while ((ch = getchar()) != '\n' && ch != EOF); // Nettoyer le buffer du scanf
            getch(); // Attendre l'utilisateur pour entrer n'importe quelle touche
            reinitialiser_curseure();


        }

return choix; //RETOURNER LE CHOIX DE LUTILISATEURE
}

///*********************************\\fin//*******************************************//
