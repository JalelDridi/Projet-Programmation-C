#ifndef ELECTION_H_INCLUDED
#define ELECTION_H_INCLUDED
#include <gtk/gtk.h>
// Strucure Date :
typedef struct
{
    char jour[10];
    char mois[10];
    char annee[10];
}Date;
// Structure Gestion des elections :
typedef struct Election
{
    char identifiant[20];
    Date d;
    char nhabit[20];
    char nbcons[20];
    char municip[20];
}Election;
int ajouter_election(Election e , char filename []);
int modifier_election(char id[], Election nouv, char * filename);
int supprimer_election(char id[], char * filename);
Election chercher_election(char id[], char * filename);
//fonctions de calcul pour gestion des elections :
float TPE(char *filename); 
// TREEVIEW :
void afficher_elec(GtkWidget *liste);
void afficherelec_rech(GtkWidget *liste,char idch[]);
void vider(GtkWidget *liste);






#endif // ELECTION_H_INCLUDED
