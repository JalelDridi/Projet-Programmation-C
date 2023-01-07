#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "listelectoral.h"

enum
{
    EIDENTIFIANT,
    EID,
    EORIENTATION,
    EID1,
    EID2,
    EID3,
    COLUMNS
};
int ajouter_l(char *fichier, listelectoral L)
{
    FILE *f = fopen(fichier, "a");
    if (f != NULL)
    {

        fprintf(f, "%s %s %s %s %s %s\n", L.identifiant, L.id, L.orientation, L.id1, L.id2, L.id3);

        fclose(f);
        return 1;
    }
    else
        return 0;
}

int modifier_l(char *fichier, listelectoral nouv, char Identifiant[])
{
    int tr = 0;

    listelectoral L;

    FILE *f = fopen(fichier, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL)
    {
        while (fscanf(f, "%s %s %s %s %s %s\n", L.identifiant, L.id, L.orientation, L.id1, L.id2, L.id3) != EOF)
        {
            if (strcmp(Identifiant, L.identifiant) != 0)
            {
                fprintf(f2, "%s %s %s %s %s %s\n", L.identifiant, L.id, L.orientation, L.id1, L.id2, L.id3);
            }
            else
            {
                fprintf(f2, "%s %s %s %s %s %s\n", L.identifiant, nouv.id, nouv.orientation, nouv.id1, nouv.id2, nouv.id3);
                tr = 1;
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove(fichier);
    rename("nouv.txt", fichier);
    return tr;
}

int supprimer_l(char *fichier, char Identifiant[])
{
    int tr = 0;
    listelectoral L;

    FILE *f = fopen(fichier, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL)
    {
        while (fscanf(f, "%s %s %s %s %s %s\n", L.identifiant, L.id, L.orientation, L.id1, L.id2, L.id3) != EOF)
        {
            if (strcmp(Identifiant, L.id) != 0)

            {
                fprintf(f2, "%s %s %s %s %s %s\n", L.identifiant, L.id, L.orientation, L.id1, L.id2, L.id3);
            }
            else
                tr = 1;
        }
    }
    fclose(f);
    fclose(f2);
    remove(fichier);
    rename("nouv.txt", fichier);
    return tr;
}

void afficher_l(GtkWidget *liste)
{
    GtkCellRenderer *renderer; // afficheur de cellule (Cellule contient un texte, image, case à cocher)
    GtkTreeViewColumn *column; // visualisation des colonnes
    GtkTreeIter iter;          /**/
    GtkListStore *store;       // création du modèle de type liste

    char identifiant[20], id[20], id1[20], id2[20], id3[20];
    char orientation[20];
    store = NULL;
    listelectoral L1;

    FILE *f;

    store = gtk_tree_view_get_model(liste);
    if (store == NULL)
    {

        renderer = gtk_cell_renderer_text_new();                                                                       // cellule contenant du texte
        column = gtk_tree_view_column_new_with_attributes("Numéro de la liste", renderer, "text", EIDENTIFIANT, NULL); // création d'une colonne avec du texte
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);                                                     // associer la colonne à l'afficheur (GtkTreeView)

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Identifiant T", renderer, "text", EID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Orientation", renderer, "text", EORIENTATION, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Identifiant C1", renderer, "text", EID1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Identifiant C2", renderer, "text", EID2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Identifiant C3", renderer, "text", EID3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    }
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    f = fopen("list.txt", "r");

    if (f == NULL)
    {
        return;
    }
    else
    {
        f = fopen("list.txt", "a+");
        while (fscanf(f, "%s %s %s %s %s %s\n", L1.identifiant, L1.id, L1.orientation, L1.id1, L1.id2, L1.id3) != EOF)
        {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, EIDENTIFIANT, L1.identifiant, EID, L1.id, EORIENTATION, L1.orientation, EID1, L1.id1, EID2, L1.id2, EID3, L1.id3);
        }
        fclose(f);
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}

void afficher_v(GtkWidget *liste)
{
    GtkCellRenderer *renderer; // afficheur de cellule (Cellule contient un texte, image, case à cocher)
    GtkTreeViewColumn *column; // visualisation des colonnes
    GtkTreeIter iter;          /**/
    GtkListStore *store;       // création du modèle de type liste

    char identifiant[20], id[20], id1[20], id2[20], id3[20];
    char orientation[20];
    store = NULL;
    listelectoral L1;

    FILE *f;

    store = gtk_tree_view_get_model(liste);
    if (store == NULL)
    {

        renderer = gtk_cell_renderer_text_new();                                                                       // cellule contenant du texte
        column = gtk_tree_view_column_new_with_attributes("Numéro de la liste", renderer, "text", EIDENTIFIANT, NULL); // création d'une colonne avec du texte
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);                                                     // associer la colonne à l'afficheur (GtkTreeView)

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Orientation", renderer, "text", EORIENTATION, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING);
    f = fopen("list.txt", "r");

    if (f == NULL)
    {
        return;
    }
    else
    {
        f = fopen("list.txt", "a+");
        while (fscanf(f, "%s %s %s %s %s %s\n", L1.identifiant, L1.id, L1.orientation, L1.id1, L1.id2, L1.id3) != EOF)
        {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, EIDENTIFIANT, L1.identifiant, EORIENTATION, L1.orientation);
        }
        fclose(f);
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}

void supp_l(listelectoral L)
{

    char identifiant[20], id[20], id1[20], id2[20], id3[20];
    char orientation[20];
    FILE *f, *g;

    f = fopen("list.txt", "r");
    g = fopen("l.txt", "w");
    if (f == NULL || g == NULL)
    {
        return;
    }
    else
    {
        while (fscanf(f, "%s %s %s %s %s %s\n", L.identifiant, L.id, L.orientation, L.id1, L.id2, L.id3) != EOF)
        {

            if (strcmp(identifiant, L.identifiant) != 0 || strcmp(id, L.id) != 0 || strcmp(id1, L.id1) != 0 || strcmp(id2, L.id2) != 0 || strcmp(id3, L.id3) != 0 || strcmp(orientation, L.orientation) != 0)

            {
                fprintf(g, "%s %s %s %s %s %s\n", identifiant, id, orientation, id1, id2, id3);
            }
        }

        fclose(f);
        fclose(g);
        remove("list.txt");
        rename("l.txt", "list.txt");
    }
}

void afficherrech_l(GtkWidget *liste, char ID[])
{
    GtkCellRenderer *renderer; // afficheur de cellule (Cellule contient un texte, image, case à cocher)
    GtkTreeViewColumn *column; // visualisation des colonnes
    GtkTreeIter iter;          /**/
    GtkListStore *store;       // création du modèle de type liste

    char identifiant[20], id[20], id1[20], id2[20], id3[20];
    char orientation[20];
    store = NULL;
    listelectoral L1;

    FILE *f;

    store = gtk_tree_view_get_model(liste);
    if (store == NULL)
    {

        renderer = gtk_cell_renderer_text_new();                                                                // cellule contenant du texte
        column = gtk_tree_view_column_new_with_attributes("identifiant", renderer, "text", EIDENTIFIANT, NULL); // création d'une colonne avec du texte
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);                                              // associer la colonne à l'afficheur (GtkTreeView)

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID T", renderer, "text", EID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("orientation", renderer, "text", EORIENTATION, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("id1", renderer, "text", EID1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("id2", renderer, "text", EID2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("id3", renderer, "text", EID3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

    }
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    f = fopen("list.txt", "r");

    if (f == NULL)
    {
        return;
    }
    else
    {
        f = fopen("list.txt", "a+");
        while (fscanf(f, "%s %s %s %s %s %s\n", L1.identifiant, L1.id, L1.orientation, L1.id1, L1.id2, L1.id3) != EOF)
        {
            if (strcmp(ID, L1.identifiant) == 0)
                gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, EIDENTIFIANT, L1.identifiant, EID, L1.id, EORIENTATION, L1.orientation, EID1, L1.id1, EID2, L1.id2, EID3, L1.id3);
        }
        fclose(f);
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}

/*
void nbv(char *filename , char *fichier, char msg[],int T_nbv[])
{


 int i,j,N, T_nbv[40];
 char T_id[20],k[20];
listelectoral L;
Utilisateur U;
N=0;
FILE * f=fopen(fichier, "r");
FILE * f1=fopen(filename, "r");
i=0;
if (f!= NULL )
{ while (fscanf(f,"%s %s %s %s %s %s \n",L.identifiant,L.id,L.orientation,L.id1,L.id2,L.id3)!=EOF)
    { i++;
    }
N=i;

for (j=0;j<N;j++)
{ T_nbv[j]=0;}

j=0;
if (f1!= NULL )
{ while(fscanf(f1,"%s %s %d %d/%d/%d %s %s %d %s %s %s \n ",U.nom,U.prenom,&U.cin,&U.DDN.jour,&U.DDN.mois,&U.DDN.annee,U.role,U.vote,&U.numBV,U.login,U.pass,U.hf)!=EOF)

{  if (strcmp("0",U.vote)!=0 && strcmp("-1",U.vote)!=0  )



            {
             T_nbv[int(U.vote)]++;


             }

       }

}

for (j=0;j<N;j++)
{

strcat(msg,T_id[i]);
sprintf(k, "%d",T_nbv[j]);
strcat(msg,k);
strcat(msg,"n/");



}

fclose(f);
fclose(f1);
}
}
}*/
/*
int L_ordre( char *fichier, int T_nbv[])
{
listelectoral L;

int x,c,i,j,s,max;

FILE * f=fopen(fichier, "r");
FILE * f2=fopen("ordonne.txt", "a");
i=0;
if (f!= NULL )
   { while (fscanf(f,"%d %d %s %d %d %d \n",&L.identifiant,&L.id,L.orientation,&L.id1,&L.id2,&L.id3)!=EOF)
            {    T[i]=L.identifiant;
                 i++;
    }

}


x=nbv(filname,fichier);

for(i=0;i<x-1;i++)
{ max=i;
 for(j=i+1;j<x;j++)
    {
        if (T_nbv[i]<T_nbv[j])
           {  max=j;
          }
              c=T_nbv[i];
              T_nbv[i]=T_nbv[j];
              T_nbv[j]=c;
               s=T[i];
              T[i]=T[j];
              T[j]=s;



     }
}

for(i=0;i<x;i++)
{
   if(f2!=NULL)
     {

        fprintf(f2,"%d \n",T[i]);

      }
}
fclose(f2);
return(x);
}*/

/*void nbv(char *filename , char *fichier, char msg[],int i,int *bv)
{


 int j,N;
 char K[20];
char M[10];


Utilisateur U;
N=0;
FILE * f1=fopen(filename, "r");



while(fscanf(f1,"%s %s %d %d %d %d %s %s %d %s %s %s \n ",U.nom,U.prenom,&U.cin,&U.DDN.jour,&U.DDN.mois,&U.DDN.annee,U.role,U.vote,&U.numBV,U.login,U.pass,U.hf)!=EOF)

{

                        sprintf(M, "%d",i);
                if (strcmp(M,U.vote)==0 )
                        {N++;}




}
*bv=N;
sprintf(K, "%d",N);
strcat(msg,K);






}*/
