#include "reclamation.h"
#include<string.h>
#include<stdio.h>
#include <gtk/gtk.h>
// ----- GESTION DES RECLAMATIONS ------




//Enumerate :

enum
{
    ETYPEREC,
    ELER,
    ENUMBV,
    EIDREC,
    COLUMNS,
};



// Ajouter une reclamation :
int ajouter_reclamation(Reclamation R , char filename [])
{
    FILE * f=fopen(filename, "a");
    if(f!=NULL)
    {
        fprintf(f,"%s %s %s %s %s\n",R.textrec,R.typerec,R.Listelecreclame,R.numBV,R.idrec);
        fclose(f);
        return 1;
    }
    else return 0;
}
// Modifier une reclamation :
int modifier_reclamation(char id[], Reclamation nouv, char * filename)
{
Reclamation R;
    FILE * f=fopen(filename, "r");
    FILE * f2 =fopen("aux.txt", "w");
    if(f==NULL || f2==NULL)
return 0;
else
    {
while(fscanf(f,"%s %s %s %s %s\n",R.textrec,R.typerec,R.Listelecreclame,R.numBV,R.idrec)!=EOF)
{
if(strcmp(R.idrec,id)!=0)
        fprintf(f2,"%s %s %s %s %s\n",R.textrec,R.typerec,R.Listelecreclame,R.numBV,R.idrec);
else

  fprintf(f2,"%s %s %s %s %s\n",nouv.textrec,nouv.typerec,nouv.Listelecreclame,nouv.numBV,nouv.idrec);

}
        fclose(f);
        fclose(f2);
remove(filename);
rename("aux.txt", filename);
        return 1;
    }
  
}

int supprimer_reclamation(char id[], char * filename)
{
Reclamation R;
    FILE * f=fopen(filename, "r");
    FILE * f2 =fopen("aux.txt", "w");
    if(f==NULL || f2==NULL)
return 0;
else
    {
while(fscanf(f,"%s %s %s %s %s\n",R.textrec,R.typerec,R.Listelecreclame,R.numBV,R.idrec)!=EOF)
{
if(strcmp(R.idrec,id)!=0)
        fprintf(f2,"%s %s %s %s %s\n",R.textrec,R.typerec,R.Listelecreclame,R.numBV,R.idrec);

}
        fclose(f);
        fclose(f2);
remove(filename);
rename("aux.txt", filename);
        return 1;
    }
}

Reclamation chercher_reclamation(char id[], char * filename)
{
Reclamation R; int tr=0;
    FILE * f=fopen(filename, "r");
 if(f!=NULL )
    {
while(fscanf(f,"%s %s %s %s %s\n",R.textrec,R.typerec,R.Listelecreclame,R.numBV,R.idrec)!=EOF && tr==0)
{if(strcmp(id,R.idrec)==0)
{
tr=1;
break;
}
}
}
if(tr==0)
strcpy(R.idrec,"-1");
return R;

}




// Treeview aff  :


void afficher_rec(GtkWidget *liste)
{
    GtkCellRenderer *renderer; // afficheur de cellule (Cellule contient un texte, image, case à cocher)
    GtkTreeViewColumn *column; // visualisation des colonnes
    GtkTreeIter iter;          /**/
    GtkListStore *store;       // création du modèle de type liste

    char textrec[100];
    char typerec[20];
    char Listelecreclame[20];
    char numBV[20];
    char idrec[20];
    store = NULL;
    Reclamation r;

    FILE *f;

    store = gtk_tree_view_get_model(liste);
    if (store == NULL)
    {
        
	renderer=gtk_cell_renderer_text_new();                                                               // cellule contenant du texte
        column = gtk_tree_view_column_new_with_attributes("Id de reclamation", renderer, "text", EIDREC, NULL); // création d'une colonne avec du texte
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);                                             // associer la colonne à l'afficheur (GtkTreeView)

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Numéro de BV", renderer, "text", ENUMBV, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Liste electorale recl", renderer, "text", ELER, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type de reclamation", renderer, "text", ETYPEREC, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


        // La liste contient 4 colonnes de type chaine de caractères
    }
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    f = fopen("reclamation.txt", "r");

    if (f == NULL)
    {
        return;
    }
    else
    {
        f = fopen("reclamation.txt", "a+");
        while (fscanf(f, "%s %s %s %s %s\n",r.textrec,r.typerec,r.Listelecreclame,r.numBV,r.idrec) != EOF)
        {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, ETYPEREC, r.typerec, ELER, r.Listelecreclame, ENUMBV, r.numBV, EIDREC, r.idrec);
        }
        fclose(f);
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}



// Treeview aff (rech) :


void afficherrec_rech(GtkWidget *liste,char id[])
{
    GtkCellRenderer *renderer; // afficheur de cellule (Cellule contient un texte, image, case à cocher)
    GtkTreeViewColumn *column; // visualisation des colonnes
    GtkTreeIter iter;          /**/
    GtkListStore *store;       // création du modèle de type liste

    char textrec[100];
    char typerec[20];
    char Listelecreclame[20];
    char numBV[20];
    char idrec[20];
    store = NULL;
    Reclamation r;

    FILE *f;

    store = gtk_tree_view_get_model(liste);
    if (store == NULL)
    {
        
	renderer=gtk_cell_renderer_text_new();                                                               // cellule contenant du texte
        column = gtk_tree_view_column_new_with_attributes("Id de reclamation", renderer, "text", EIDREC, NULL); // création d'une colonne avec du texte
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);                                             // associer la colonne à l'afficheur (GtkTreeView)

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Numéro de BV", renderer, "text", ENUMBV, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Liste electorale", renderer, "text", ELER, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type de reclamation", renderer, "text", ETYPEREC, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


        // La liste contient 4 colonnes de type chaine de caractères
    }
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    f = fopen("reclamation.txt", "r");

    if (f == NULL)
    {
        return;
    }
    else
    {
        f = fopen("reclamation.txt", "a+");
        while (fscanf(f, "%s %s %s %s %s\n",r.textrec,r.typerec,r.Listelecreclame,r.numBV,r.idrec) != EOF)
        {
	if(strcmp(id,r.idrec)==0)
	{
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, EIDREC, r.idrec, ENUMBV, r.numBV, ELER, r.Listelecreclame, ETYPEREC, r.typerec);
        }
	}
        fclose(f);
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}


