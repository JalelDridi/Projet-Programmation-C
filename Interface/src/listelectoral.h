#ifndef LISTEELEC_H_INCLUDED
#define LISTEELEC_H_INCLUDED
#include <gtk/gtk.h>

typedef struct listelectoral
{

    char identifiant[20], id[20], id1[20], id2[20], id3[20];
    char orientation[20];

} listelectoral;
typedef struct Date
{
    int jour;
    int mois;
    int annee;
} Date2;
/*typedef struct Utilisateur
{
    char nom[100];
    char prenom[100];
    int cin;
    Date DDN;
    char role[100];
    char vote[20];
    int numBV;
    char login[100];
    char pass[100];
    char hf[100];
}Utilisateur;*/

int ajouter_l(char *fichier, listelectoral L);
int modifier_l(char *fichier, listelectoral nouv, char Identifiant[]);
int supprimer_l(char *fichier, char Identifiant[]);
void afficher_l(GtkWidget *liste);
void vider_l(GtkWidget *liste);
void supp_l(listelectoral L);
void afficherrech_l(GtkWidget *liste, char ID[]);
void afficher_v(GtkWidget *liste);
//
// fonctions de calcul
/*void nbv (char * filename, char* fichier , char msg[], int i , int * bv);
int L_ordre( char *fichierListeElectorale,int T[], char * votefile);*/

#endif // LISTEELEC_H_INCLUDED
