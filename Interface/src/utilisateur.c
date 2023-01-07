#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilisateur.h"
#include <gtk/gtk.h>
Utilisateur U;

enum
{
  NOM,
  PRENOM,
  CIN,
  EDDN,
  ROLE,
  VOTE,
  NUMBV,
  LOGIN,
  PASS,
  HF,
  COLUMNS,
};

void ajouter_utilisateur(Utilisateur U)
{
  FILE *f = NULL;
  f = fopen("ajt_ut.txt", "a+");

  if (f != NULL)
  {

    fprintf(f, "%s %s %s %s %s %d/%d/%d %s %s %s %s\n ", U.login, U.nom, U.prenom, U.cin, U.hf, U.DDN.jour, U.DDN.mois, U.DDN.annee, U.pass, U.numBV, U.vote, U.role);
    fclose(f);
  }
}

void afficher_utilisateur(GtkWidget *liste, char *nomF)
{
  /*int i=0;
  FILE *f3=NULL;
  f3=fopen(nomF,"r");
  if(f3!=NULL)*/
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkTreeIter iter;
  GtkListStore *store;
  // Utilisateur U;
  char nom[20];
  char prenom[20];
  char cin[20];
  char DDN[20];
  char role[20];
  char vote[20];
  char numBV[20];
  char login[20];
  char pass[20];
  char hf[20];
  store = NULL;
  FILE *f;

  store = gtk_tree_view_get_model(liste);

  if (store == NULL)
  {

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("login", renderer, "text", LOGIN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", NOM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text", PRENOM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("cin", renderer, "text", CIN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("hf", renderer, "text", HF, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("DDN", renderer, "text", EDDN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("pass", renderer, "text", PASS, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("numBV", renderer, "text", NUMBV, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("vote", renderer, "text", VOTE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("role", renderer, "text", ROLE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
  }

  store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

  f = fopen(/*"ajt_ut.txt"*/ nomF, "r");
  if (f == NULL)
  {

    return;
  }

  else
  {
    f = fopen(nomF, "a+");
    while (fscanf(f, "%s %s %s %s %s %s %s %s %s %s\n", login, nom, prenom, cin, hf, DDN, pass, numBV, vote, role) != EOF)
    {

      gtk_list_store_append(store, &iter);
      gtk_list_store_set(store, &iter, LOGIN, login, NOM, nom, PRENOM, prenom, CIN, cin, HF, hf, EDDN, DDN, PASS, pass, NUMBV, numBV, VOTE, vote, ROLE, role, -1);
    }
    fclose(f);

    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
  }
}

void modifier_utilisateur(Utilisateur U)
{
  int j11, m11, a11;
  char nom[100];
  char prenom[100];
  char cin[100];
  // char DDN[20];
  char role[100];
  char vote[100];
  char numBV[100];
  char login[100];
  char pass[100];
  char hf[100];

  FILE *f1 = NULL, *f2 = NULL;

  f1 = fopen("ajt_ut.txt", "r");
  f2 = fopen("modif_ut.txt", "w+");

  while (fscanf(f1, "%s %s %s %s %s %d/%d/%d %s %s %s %s\n", login, nom, prenom, cin, hf, &j11, &m11, &a11, pass, numBV, vote, role) != EOF)
  {
    if (strcmp(U.cin, cin) == 0)
    {
      fprintf(f2, "%s %s %s %s %s %d/%d/%d %s %s %s %s\n", U.login, U.nom, U.prenom, U.cin, U.hf, U.DDN.jour, U.DDN.mois, U.DDN.annee, U.pass, U.numBV, U.vote, U.role);
    }
    else
    {
      fprintf(f2, "%s %s %s %s %s %d/%d/%d %s %s %s %s\n", login, nom, prenom, cin, hf, j11, m11, a11, pass, numBV, vote, role);
    }
  }
  fclose(f1);
  fclose(f2);
  remove("ajt_ut.txt");
  rename("modif_ut.txt", "ajt_ut.txt");
}

void supprimer_utilisateur(Utilisateur U)
{

  char nom[100];
  char prenom[100];
  char cin[100];
  char ddn[100];
  char role[100];
  char vote[100];
  char numBV[100];
  char login[100];
  char pass[100];
  char hf[100];
  FILE *f, *g;
  f = fopen("ajt_ut.txt", "r");
  g = fopen("supp.txt", "w");

  if (f == NULL)
  {
    return;
  }
  else
  {

    while (fscanf(f, "%s %s %s %s %s %s %s %s %s %s\n", login, nom, prenom, cin, hf, ddn, pass, numBV, vote, role) != EOF)
    {
      if (strcmp(U.cin, cin) != 0)
        fprintf(g, "%s %s %s %s %s %s %s %s %s %s\n", login, nom, prenom, cin, hf, ddn, pass, numBV, vote, role);
    }

    fclose(f);
    fclose(g);
    remove("ajt_ut.txt");
    rename("supp.txt", "ajt_ut.txt");
  }
}

void chercher_utilisateur(Utilisateur U, char text[100])
{
  char date[100];
  FILE *f4 = NULL;
  FILE *ff = NULL;
  remove("rech.txt");
  f4 = fopen("ajt_ut.txt", "r");
  ff = fopen("rech.txt", "a+");

  if (f4 == NULL /* || ff == NULL*/)
  {
    return;
  }

  else
  {

    while (fscanf(f4, "%s %s %s %s %s %d/%d/%d %s %s %s %s\n", U.login, U.nom, U.prenom, U.cin, U.hf, &U.DDN.jour, &U.DDN.mois, &U.DDN.annee, U.pass, U.numBV, U.vote, U.role) != EOF)
    {
      if (strcmp(text, U.cin) == 0 || strcmp(text, U.login) == 0 || strcmp(text, U.nom) == 0 || strcmp(text, U.prenom) == 0)

        fprintf(ff, "%s %s %s %s %s %d/%d/%d %s %s %s %s\n", U.login, U.nom, U.prenom, U.cin, U.hf, U.DDN.jour, U.DDN.mois, U.DDN.annee, U.pass, U.numBV, U.vote, U.role);
    }

    fclose(f4);
    fclose(ff);
  }
}

Utilisateur login(char text1[100], char text2[100])
{
  char date[100];
  int tr = 0;
  Utilisateur U;
  FILE *f4 = NULL;
  f4 = fopen("ajt_ut.txt", "r");

  if (f4 == NULL /* || ff == NULL*/)
  {
    return;
  }

  else
  {

    while (fscanf(f4, "%s %s %s %s %s %d/%d/%d %s %s %s %s\n", U.login, U.nom, U.prenom, U.cin, U.hf, &U.DDN.jour, &U.DDN.mois, &U.DDN.annee, U.pass, U.numBV, U.vote, U.role) != EOF)
    {
      if (strcmp(text1, U.login) == 0 && strcmp(text2, U.pass) == 0)
      {
        tr = 1;
        break;
      }
    }
    if (tr == 0)
    {
      strcpy(U.login, "-1");
    }
    return U;

    fclose(f4);
  }
}

int nbElecteur(Utilisateur U, char *nomF)
{

  int nb = 0;
  FILE *ff = NULL;
  ff = fopen(nomF, "r");
  while (fscanf(ff, "%s %s %s %s %s %d/%d/%d %s %s %s %s\n", U.login, U.nom, U.prenom, U.cin, U.hf, &U.DDN.jour, &U.DDN.mois, &U.DDN.annee, U.pass, U.numBV, U.vote, U.role) != EOF)
  {
    nb = nb + 1;
  }
  fclose(ff);
  return (nb);
}

void nbre_hom_fem(Utilisateur U, char *nomF, int *nh, int *nf)
{

  *nh = 0;
  *nf = 0;
  FILE *f5 = NULL;
  f5 = fopen(nomF, "r");

  while (fscanf(f5, "%s %s %s %s %s %d/%d/%d %s %s %s %s\n", U.login, U.nom, U.prenom, U.cin, U.hf, &U.DDN.jour, &U.DDN.mois, &U.DDN.annee, U.pass, U.numBV, U.vote, U.role) != EOF)

  {
    if (strcmp(U.hf, "Homme") == 0)
    {
      *nh = *nh + 1;
    }
    else if (strcmp(U.hf, "Femme") == 0)
    {
      *nf = *nf + 1;
    }
    //*nh=(*nh/nbElecteur(U,nomF))*100;
    //*nf=(*nf/nbElecteur(U,nomF))*100;
  }

  fclose(f5);
}

void vote_blanc(Utilisateur U, int *nb)
{
  *nb = 0;
  FILE *f6 = NULL;
  f6 = fopen("ajt_ut.txt", "r");
  while (fscanf(f6, "%s %s %s %s %s %d/%d/%d %s %s %s %s\n", U.login, U.nom, U.prenom, U.cin, U.hf, &U.DDN.jour, &U.DDN.mois, &U.DDN.annee, U.pass, U.numBV, U.vote, U.role) != EOF)
  {
    if (strcmp(U.vote, "0") == 0)
    {
      *nb = *nb + 1;
    }
  }

  fclose(f6);
}

void affstat(char val[], char aff1[])
{
  strcpy(aff1, "le nombre d'hommes est :  ");
  strcat(aff1, val);
}

void affstat1(char val[], char aff2[])
{
  strcpy(aff2, "le nombre des femmes est :  ");
  strcat(aff2, val);
}

void affstat2(char val[], char aff3[])
{
  strcpy(aff3, "le nombre des votes blancs est :  ");
  strcat(aff3, val);
}

/*void vider(GtkWidget *liste)
{

  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkTreeIter iter;
  GtkListStore *store;
  // Utilisateur U;
  char nom[20];
  char prenom[20];
  char cin[20];
  char DDN[20];
  char role[20];
  char vote[20];
  char numBV[20];
  char login[20];
  char pass[20];
  char hf[20];
  store = NULL;
  FILE *f;

  store = gtk_tree_view_get_model(liste);

  if (store == NULL)
  {

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("login", renderer, "text", LOGIN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", NOM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text", PRENOM, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("cin", renderer, "text", CIN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("hf", renderer, "text", HF, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("DDN", renderer, "text", EDDN, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("pass", renderer, "text", PASS, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("numBV", renderer, "text", NUMBV, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("vote", renderer, "text", VOTE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("role", renderer, "text", ROLE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
  }
  store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

  gtk_list_store_append(store, &iter);
  gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
}*/
