#ifndef RECLAMATION_H_INCLUDED
#define RECLAMATION_H_INCLUDED

#include <gtk/gtk.h>
typedef struct Reclamation
{
    char textrec[100];
    char typerec[20];
    char Listelecreclame[20];
    char numBV[20];
    char idrec[20];
}Reclamation;
int ajouter_reclamation(Reclamation r , char filename []);
int modifier_reclamation(char id[], Reclamation nouv, char * filename);
int supprimer_reclamation(char id[], char * filename);
Reclamation chercher_reclamation(char id[], char * filename);
// treeview :
void afficher_rec(GtkWidget *liste);
void afficherrec_rech(GtkWidget *liste,char id[]);

#endif // RECLAMATION_H_INCLUDED
