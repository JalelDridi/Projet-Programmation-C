#include "election.h"
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
//   ------GESTION DES ELECTIONS-------

// Enumerate :

enum
{
    EIDEL,
    EJR,
    EMS,
    EANN,
    ENH,
    ENBCONS,
    EMUNICIP,
    COLUMNS,
};

// Ajouter une election :
int ajouter_election(Election E, char filename[])
{
    FILE *f = fopen(filename, "a");
    if (f != NULL)
    {
        fprintf(f, "%s %s %s %s %s %s %s\n", E.identifiant, E.d.jour, E.d.mois, E.d.annee, E.nhabit, E.nbcons, E.municip);
        fclose(f);
        return 1;
    }
    else
        return 0;
}
// Modifier une election :
int modifier_election(char id[], Election nouv, char *filename)
{
    Election E;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("aux.txt", "w");
    if (f == NULL || f2 == NULL)
        return 0;
    else
    {
        while (fscanf(f, "%s %s %s %s %s %s %s\n", E.identifiant, E.d.jour, E.d.mois, E.d.annee, E.nhabit, E.nbcons, E.municip) != EOF)
        {
            if (strcmp(id, E.identifiant) != 0)
                fprintf(f2, "%s %s %s %s %s %s %s\n", E.identifiant, E.d.jour, E.d.mois, E.d.annee, E.nhabit, E.nbcons, E.municip);
            else
                fprintf(f2, "%s %s %s %s %s %s %s\n", nouv.identifiant, nouv.d.jour, nouv.d.mois, nouv.d.annee, nouv.nhabit, nouv.nbcons, nouv.municip);
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("aux.txt", filename);
        return 1;
    }
}
// Supprimer une election :
int supprimer_election(char id[], char *filename)
{
    Election E;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("aux.txt", "w");
    if (f == NULL || f2 == NULL)
        return 0;
    else
    {
        while (fscanf(f, "%s %s %s %s %s %s %s\n", E.identifiant, E.d.jour, E.d.mois, E.d.annee, E.nhabit, E.nbcons, E.municip) != EOF)
        {
            if (strcmp(id, E.identifiant) != 0)
                fprintf(f2, "%s %s %s %s %s %s %s\n", E.identifiant, E.d.jour, E.d.mois, E.d.annee, E.nhabit, E.nbcons, E.municip);
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("aux.txt", filename);
        return 1;
    }
}
// Chercher une election :
Election chercher_election(char id[], char *filename)
{
    Election E;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL)
    {
        while (fscanf(f, "%s %s %s %s %s %s %s\n", E.identifiant, E.d.jour, E.d.mois, E.d.annee, E.nhabit, E.nbcons, E.municip) != EOF && tr == 0)
        {
            if (strcmp(id, E.identifiant) == 0)
            {
                tr = 1;
                break;
            }
        }
    }
    if (tr == 0)
        strcpy(E.identifiant, "-1");
    return E;
}

// Afficher (treeview) :

void afficher_elec(GtkWidget *liste)
{
    GtkCellRenderer *renderer; // afficheur de cellule (Cellule contient un texte, image, case à cocher)
    GtkTreeViewColumn *column; // visualisation des colonnes
    GtkTreeIter iter;          /**/
    GtkListStore *store;       // création du modèle de type liste

    char identifiant[20];
    char jour[20];
    char mois[20];
    char annee[20];
    char nhabit[20];
    char nbcons[20];
    char municip[20];
    store = NULL;
    Election E;

    FILE *f;

    store = gtk_tree_view_get_model(liste);
    if (store == NULL)
    {

        renderer = gtk_cell_renderer_text_new();                                                         // cellule contenant du texte
        column = gtk_tree_view_column_new_with_attributes("Id election", renderer, "text", EIDEL, NULL); // création d'une colonne avec du texte
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);                                       // associer la colonne à l'afficheur (GtkTreeView)

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text", EJR, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text", EMS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Annee", renderer, "text", EANN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nb habit", renderer, "text", ENH, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nb cons", renderer, "text", ENBCONS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Municipalité", renderer, "text", EMUNICIP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // La liste contient 7 colonnes de type chaine de caractères
    }
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    f = fopen("election.txt", "r");

    if (f == NULL)
    {
        return;
    }
    else
    {
        f = fopen("election.txt", "a+");
        while (fscanf(f, "%s %s %s %s %s %s %s\n", E.identifiant, E.d.jour, E.d.mois, E.d.annee, E.nhabit, E.nbcons, E.municip) != EOF)
        {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, EIDEL, E.identifiant, EJR, E.d.jour, EMS, E.d.mois, EANN, E.d.annee, ENH, E.nhabit, ENBCONS, E.nbcons, EMUNICIP, E.municip);
        }
        fclose(f);
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}

// Vider treeview :

void vider(GtkWidget *liste)
{
    GtkCellRenderer *renderer; // afficheur de cellule (Cellule contient un texte, image, case à cocher)
    GtkTreeViewColumn *column; // visualisation des colonnes
    GtkTreeIter iter;          /**/
    GtkListStore *store;       // création du modèle de type liste

    char identifiant[20];
    char jour[20];
    char mois[20];
    char annee[20];
    char nhabit[20];
    char nbcons[20];
    char municip[20];
    store = NULL;
    Election e;

    FILE *f;

    store = gtk_tree_view_get_model(liste);
    if (store == NULL)
    {

        renderer = gtk_cell_renderer_text_new();                                                         // cellule contenant du texte
        column = gtk_tree_view_column_new_with_attributes("Id election", renderer, "text", EIDEL, NULL); // création d'une colonne avec du texte
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);                                       // associer la colonne à l'afficheur (GtkTreeView)

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text", EJR, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text", EMS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Annee", renderer, "text", EANN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nb habit", renderer, "text", ENH, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nb cons", renderer, "text", ENBCONS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Municipalité", renderer, "text", EMUNICIP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // La liste contient 7 colonnes de type chaine de caractères
    }
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
}

// Afficher le resultat recherché :

void afficherelec_rech(GtkWidget *liste, char idch[])

{
    GtkCellRenderer *renderer; // afficheur de cellule (Cellule contient un texte, image, case à cocher)
    GtkTreeViewColumn *column; // visualisation des colonnes
    GtkTreeIter iter;          /**/
    GtkListStore *store;       // création du modèle de type liste

    char identifiant[20];
    char jour[20];
    char mois[20];
    char annee[20];
    char nhabit[20];
    char nbcons[20];
    char municip[20];
    store = NULL;
    Election E;

    FILE *f;

    store = gtk_tree_view_get_model(liste);
    if (store == NULL)
    {

        renderer = gtk_cell_renderer_text_new();                                                         // cellule contenant du texte
        column = gtk_tree_view_column_new_with_attributes("Id election", renderer, "text", EIDEL, NULL); // création d'une colonne avec du texte
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);                                       // associer la colonne à l'afficheur (GtkTreeView)

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text", EJR, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text", EMS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Annee", renderer, "text", EANN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nb habit", renderer, "text", ENH, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nb cons", renderer, "text", ENBCONS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Municipalité", renderer, "text", EMUNICIP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // La liste contient 7 colonnes de type chaine de caractères
    }
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    f = fopen("election.txt", "r");

    if (f == NULL)
    {
        return;
    }
    else
    {
        f = fopen("election.txt", "a+");
        while (fscanf(f, "%s %s %s %s %s %s %s\n", E.identifiant, E.d.jour, E.d.mois, E.d.annee, E.nhabit, E.nbcons, E.municip) != EOF)
        {
            if (strcmp(E.identifiant, idch) == 0)
            {
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter, EIDEL, E.identifiant, EJR, E.d.jour, EMS, E.d.mois, EANN, E.d.annee, ENH, E.nhabit, ENBCONS, E.nbcons, EMUNICIP, E.municip);
            }
        }
        fclose(f);
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}
