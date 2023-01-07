#ifndef UTILISATEUR_H_INCLUDED
#define UTILISATEUR_H_INCLUDED
#include <stdio.h>
#include <gtk/gtk.h>
typedef struct
{
    int jour;
    int mois;
    int annee;
} Date1;
typedef struct Utilisateur
{
    char nom[100];
    char prenom[100];
    char cin[100];
    Date1 DDN;
    char role[100];
    char vote[100];
    char numBV[100];
    char login[100];
    char pass[100];
    char hf[100];
} Utilisateur;

char *nomF;
void ajouter_utilisateur(Utilisateur U);
void afficher_utilisateur(GtkWidget *liste, char *nomF);
void modifier_utilisateur(Utilisateur U);
void supprimer_utilisateur(Utilisateur U);
void chercher_utilisateur(Utilisateur U, char text[100]);
int nbElecteur(Utilisateur U, char *nomF);
void nbre_hom_fem(Utilisateur U, char *nomF, int *nh, int *nf);
void affstat(char val[100], char aff1[300]);
void affstat1(char val[100], char aff2[300]);
void vote_blanc(Utilisateur U, int *nb);
void affstat2(char val[100], char aff3[300]);
Utilisateur login(char text1[100], char text2[100]);

#endif
