#include <stdio.h>
#include <string.h>
#include "bv.h"
#include <gtk/gtk.h>

enum
{
    EIDBV,
    ECAPE,
    EDELP,
    EOBSP,
    EIDABV,
    ENUMS,
    COLUMNS,
};

int ajouter_bv(BV b)
{
    FILE *f = fopen("bv.txt", "a+");
    if (f != NULL)
    {
        fprintf(f, "%s %s %s %s %s %s\n", b.idBV, b.cap_el, b.del_p, b.obs_p, b.idABV, b.num_s);
        fclose(f);
        return 1;
    }
    else
        return 0;
}

void afficher_bv(GtkWidget *liste)
{
    GtkCellRenderer *renderer; // afficheur de cellule (Cellule contient un texte, image, case à cocher)
    GtkTreeViewColumn *column; // visualisation des colonnes
    GtkTreeIter iter;          /**/
    GtkListStore *store;       // création du modèle de type liste

    char idBV[10];
    char cap_el[10];
    char del_p[10];
    char obs_p[100];
    char idABV[10];
    char num_s[5];
    store = NULL;
    BV b;

    FILE *f;

    store = gtk_tree_view_get_model(liste);
    if (store == NULL)
    {

        renderer = gtk_cell_renderer_text_new();                                                               // cellule contenant du texte
        column = gtk_tree_view_column_new_with_attributes("Id Bureau de Vote", renderer, "text", EIDBV, NULL); // création d'une colonne avec du texte
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);                                             // associer la colonne à l'afficheur (GtkTreeView)

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Capacité des électeurs", renderer, "text", ECAPE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Délégués présents", renderer, "text", EDELP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Observateurs présents", renderer, "text", EOBSP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Id Agent du BV", renderer, "text", EIDABV, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Numéro de la Salle", renderer, "text", ENUMS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // La liste contient 7 colonnes de type chaine de caractères
    }
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    f = fopen("bv.txt", "r");

    if (f == NULL)
    {
        return;
    }
    else
    {
        f = fopen("bv.txt", "a+");
        while (fscanf(f, "%s %s %s %s %s %s\n", b.idBV, b.cap_el, b.del_p, b.obs_p, b.idABV, b.num_s) != EOF)
        {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, EIDBV, b.idBV, ECAPE, b.cap_el, EDELP, b.del_p, EOBSP, b.obs_p, EIDABV, b.idABV, ENUMS, b.num_s);
        }
        fclose(f);
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}

void supprimer_bv(BV b)
{
    char idBV[10];
    char cap_el[10];
    char del_p[10];
    char obs_p[100];
    char idABV[10];
    char num_s[5];

    FILE *f, *g;

    f = fopen("bv.txt", "r");
    g = fopen("dump.txt", "w");

    if (f == NULL || g == NULL)
    {
        return;
    }
    else
    {
        while (fscanf(f, "%s %s %s %s %s %s\n", idBV, cap_el, del_p, obs_p, idABV, num_s) != EOF)
        {
            if (strcmp(b.idBV, idBV) != 0)
                fprintf(g, "%s %s %s %s %s %s\n", idBV, cap_el, del_p, obs_p, idABV, num_s);
        }
        fclose(f);
        fclose(g);
        remove("bv.txt");
        rename("dump.txt", "bv.txt");
    }
}

void vider_bv(GtkWidget *liste)
{
    GtkCellRenderer *renderer; // afficheur de cellule (Cellule contient un texte, image, case à cocher)
    GtkTreeViewColumn *column; // visualisation des colonnes
    GtkTreeIter iter;          /**/
    GtkListStore *store;       // création du modèle de type liste

    char idBV[10];
    char cap_el[10];
    char liste_el[100];
    char del_p[10];
    char obs_p[100];
    char idABV[10];
    char num_s[5];
    store = NULL;

    FILE *f;

    store = gtk_tree_view_get_model(liste);
    if (store == NULL)
    {

        renderer = gtk_cell_renderer_text_new();                                                               // cellule contenant du texte
        column = gtk_tree_view_column_new_with_attributes("Id Bureau de Vote", renderer, "text", EIDBV, NULL); // création d'une colonne avec du texte
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);                                             // associer la colonne à l'afficheur (GtkTreeView)

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Capacité des électeurs", renderer, "text", ECAPE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Délégués présents", renderer, "text", EDELP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Observateurs présents", renderer, "text", EOBSP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Id Agent du BV", renderer, "text", EIDABV, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Numéro de la Salle", renderer, "text", ENUMS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // La liste contient 6 colonnes de type chaine de caractères
    }
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    gtk_list_store_append(store, &iter);
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

void afficherrech_bv(char idbv[], GtkWidget *liste)
{
    GtkCellRenderer *renderer; // afficheur de cellule (Cellule contient un texte, image, case à cocher)
    GtkTreeViewColumn *column; // visualisation des colonnes
    GtkTreeIter iter;          /**/
    GtkListStore *store;       // création du modèle de type liste

    char idBV[10];
    char cap_el[10];
    char liste_el[100];
    char del_p[10];
    char obs_p[100];
    char idABV[10];
    char num_s[5];
    store = NULL;
    BV b;

    FILE *f;

    store = gtk_tree_view_get_model(liste);
    if (store == NULL)
    {

        renderer = gtk_cell_renderer_text_new();                                                               // cellule contenant du texte
        column = gtk_tree_view_column_new_with_attributes("Id Bureau de Vote", renderer, "text", EIDBV, NULL); // création d'une colonne avec du texte
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);                                             // associer la colonne à l'afficheur (GtkTreeView)

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Capacité des électeurs", renderer, "text", ECAPE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Délégués présents", renderer, "text", EDELP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Observateurs présents", renderer, "text", EOBSP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Id Agent du BV", renderer, "text", EIDABV, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Numéro de la Salle", renderer, "text", ENUMS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // La liste contient 7 colonnes de type chaine de caractères
    }
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    f = fopen("bv.txt", "r");

    if (f == NULL)
    {
        return;
    }
    else
    {
        f = fopen("bv.txt", "a+");
        while (fscanf(f, "%s %s %s %s %s %s\n", b.idBV, b.cap_el, b.del_p, b.obs_p, b.idABV, b.num_s) != EOF)
        {
            if (strcmp(idbv, b.idBV) == 0)
            {
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter, EIDBV, b.idBV, ECAPE, b.cap_el, EDELP, b.del_p, EOBSP, b.obs_p, EIDABV, b.idABV, ENUMS, b.num_s);
            }
        }
        fclose(f);
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}

int modifier_bv(char idbv[], BV nouv, char *filename)
{
    BV b;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("aux.txt", "w");
    if (f == NULL || f2 == NULL)
        return 0;
    else
    {
        while (fscanf(f, "%s %s %s %s %s %s\n", b.idBV, b.cap_el, b.del_p, b.obs_p, b.idABV, b.num_s) != EOF)
        {
            if (strcmp(b.idBV, idbv) != 0)
                fprintf(f2, "%s %s %s %s %s %s\n", b.idBV, b.cap_el, b.del_p, b.obs_p, b.idABV, b.num_s);
            else
                fprintf(f2, "%s %s %s %s %s %s\n", nouv.idBV, nouv.cap_el, nouv.del_p, nouv.obs_p, nouv.idABV, nouv.num_s);
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("aux.txt", filename);
        return 1;
    }
}

/*int Supprimer(int id, char *filename)
{
    BV b;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("aux.txt", "w");
    if (f == NULL || f2 == NULL)
        return 0;
    else
    {
        while (fscanf(f, "%s %s %s %s %s %s %s\n", b.idBV, b.cap_el, b.liste_el, b.del_p, b.obs_p, b.idABV, b.num_s) != EOF)
        {
            if (b.idBV != id)
                fprintf(f2, "%s %s %s %s %s %s %s\n", b.idBV, b.cap_el, b.liste_el, b.del_p, b.obs_p, b.idABV, b.num_s);
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("aux.txt", filename);
        return 1;
    }
}*/

BV chercher_bv(char idbv[], char *filename)
{
    BV b;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL)
    {
        while (fscanf(f, "%s %s %s %s %s %s\n", b.idBV, b.cap_el, b.del_p, b.obs_p, b.idABV, b.num_s) != EOF && tr == 0)
        {
            if (strcmp(idbv, b.idBV) == 0)
                tr = 1;
            fprintf(f, "%s %s %s %s %s %s\n", b.idBV, b.cap_el, b.del_p, b.obs_p, b.idABV, b.num_s);
        }
    }
    if (tr == 0)
        strcpy(b.idBV, "-1");
    return b;
}

/*int NEBV(char *nomFichier1, char *nomFichier2, int *t_nebv)
{
    BV b;
    FILE *f = fopen(nomFichier1, "r");
    FILE *f2 = fopen(nomFichier2, "r");
    int t_idBV[20];
    int i = 0, n = 20, j;

    if (f != NULL)
    {
        while (fscanf(f, "%s %s %s %s %s %s %s\n", b.idBV, b.cap_el, b.liste_el, b.del_p, b.obs_p, b.idABV, b.num_s) != EOF && i < n)
        {
            t_idBV[i] = b.idBV;
            i++;
        }
    }
    printf("\nLe tableau d'identifiants des BV:\n ");
    for (j = 0; j < i; j++)
        printf("%s\t", t_idBV[j]);

    return i;
}*/
