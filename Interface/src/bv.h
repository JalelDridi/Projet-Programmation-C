#include <gtk/gtk.h>

typedef struct Bureau_de_vote
{

    char idBV[10];
    char cap_el[10];
    char del_p[10];
    char obs_p[100];
    char idABV[10];
    char num_s[5];

} BV;

int ajouter_bv(BV b);
int modifier_bv(char idbv[], BV nouv, char *filename);
void supprimer_bv(BV b);
BV chercher_bv(char idbv[], char *filename);
int NEBV(char *nomFichier1, char *nomFichier2, int *t_nebv);
void afficher_bv(GtkWidget *liste);
void afficherrech_bv(char idbv[], GtkWidget *liste);
void vider_bv(GtkWidget *liste);
