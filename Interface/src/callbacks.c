#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "election.h"
#include "bv.h"
#include "utilisateur.h"
#include "reclamation.h"
#include "listelectoral.h"
#include "CRUD.h"
#include "tree.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables d'initialisation
///////USER//////////
Utilisateur U1;
Utilisateur U2;
int nh;
int nf;
int nb;
int BIAJ;
int BIMOD;
int BIYN;
char role2[100];
char sexe[100];
guint jr;
guint mr;
guint ar;
guint j1;
guint m1;
guint a1;
//////////BV////////////
BV B1;
int JDAJ;
int JDMOD;
int JDYN;
int JDAR;
int JDMR;
//////////ELECTION////////////
Election E1;
int RAAJ;
int RAMOD;
int RAYN;

//////////RECLAMATION//////////////
Reclamation R1;
int BHAJ;
int BHMOD;
int BHYN;

int RLog;
int Vrob;

/////////LISTE ELECTORALE//////////
listelectoral L1;
int TRAJ;
int TRMOD;
int TRYN;
int TRDA = 0;
int TRDM = 0;
int TRGA = 0;
int TRGM = 0;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gestion des utilisateurs

void on_treeview1_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data)
{
    GtkTreeIter iter;
    gchar *nom;
    gchar *prenom;
    gchar *cin;
    gchar *ddn;
    gchar *role;
    gchar *vote;
    gchar *numBV;
    gchar *login;
    gchar *pass;
    gchar *hf;

    Utilisateur U;

    GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path))
    {
        gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &login, 1, &nom, 2, &prenom, 3, &cin, 4, &hf, 5, &ddn, 6, &pass, 7, &numBV, 8, &vote, 9, &role, -1);

        strcpy(U.login, numBV);
        strcpy(U.nom, login);
        strcpy(U.prenom, nom);
        strcpy(U.cin, prenom);
        strcpy(U.hf, cin);
        strcpy(U.pass, hf);
        strcpy(U.numBV, pass);
        strcpy(U.vote, ddn);
        strcpy(U.role, role);
        U1 = U;
    }
}

void on_BIrechercher_clicked(GtkWidget *button,
                             gpointer user_data)
{
    char id[20];
    Utilisateur U;
    char text[100];
    GtkWidget *treeview1;
    GtkWidget *input;

    input = lookup_widget(button, "BIentryrech");
    strcpy(text, gtk_entry_get_text(GTK_ENTRY(input)));
    treeview1 = lookup_widget(button, "treeview1");
    chercher_utilisateur(U, text);
    afficher_utilisateur(treeview1, "rech.txt");
}

void on_BIquit_clicked(GtkWidget *button,
                       gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "BIwindowG");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_LoginWindow();
    gtk_widget_show(fenetre_4);
}

void on_BIactualiser_clicked(GtkWidget *button,
                             gpointer user_data)
{
    GtkWidget *treevieww;
    treevieww = lookup_widget(button, "treeview1");
    afficher_utilisateur(treevieww, "ajt_ut.txt");
    strcpy(U1.cin, "-1");
}

void on_BIsupprimer_clicked(GtkWidget *button,
                            gpointer user_data)
{
    GtkWidget *fen1;
    if (strcmp(U1.cin, "-1") != 0)
    {
        fen1 = create_BIdialog();
        gtk_widget_show(fen1);
    }
}

void on_BImodifier_clicked(GtkWidget *button,
                           gpointer user_data)
{

    gtk_label_set_text(GTK_ENTRY(lookup_widget(button, "BIlabelidM")), U1.cin);
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "BIentry2M")), U1.nom);
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "BIentry3M")), U1.prenom);
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "BIentry4M")), U1.login);
    gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}

void on_BIStat_clicked(GtkWidget *button,
                       gpointer user_data)
{
}

void on_BIreturn_clicked(GtkWidget *button,
                         gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "BIwindowG");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_AdminWindow();
    gtk_widget_show(fenetre_4);
}

void on_BIcalendarA_day_selected(GtkCalendar *calendar,
                                 gpointer user_data)
{
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &ar, &mr, &jr);
}

void on_BIrobotA_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        BIAJ = 1;
}

void on_BIconfirmerA_clicked(GtkWidget *button,
                             gpointer user_data)
{
    Utilisateur U;
    int CIN1, Ubv, Uv;

    GtkWidget *v;
    GtkWidget *nbv;
    GtkWidget *treeview1;
    GtkWidget *input1, *input2, *input3, *input4, *input5, *combo, *combo2;
    GtkWidget *output1;
    input1 = lookup_widget(button, "BIentry1A");
    input2 = lookup_widget(button, "BIentry2A");
    input3 = lookup_widget(button, "BIentry3A");
    input4 = lookup_widget(button, "BIentry4A");
    input5 = lookup_widget(button, "BIentry5A");
    output1 = lookup_widget(button, "BIlabelmsgA");
    strcpy(U.login, gtk_entry_get_text(GTK_ENTRY(input1)));
    strcpy(U.nom, gtk_entry_get_text(GTK_ENTRY(input2)));
    strcpy(U.prenom, gtk_entry_get_text(GTK_ENTRY(input3)));
    strcpy(U.cin, gtk_entry_get_text(GTK_ENTRY(input4)));

    combo = lookup_widget(button, "BIcombobox1A");
    combo2 = lookup_widget(button, "BIcombobox2A");
    strcpy(U.hf, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo)));
    strcpy(U.role, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo2)));
    U.DDN.jour = jr;
    U.DDN.mois = mr + 1;
    U.DDN.annee = ar;
    strcpy(U.pass, gtk_entry_get_text(GTK_ENTRY(input5)));
    nbv = lookup_widget(button, "BIspinbuttonA");
    Ubv = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(nbv));
    sprintf(U.numBV, "%d", Ubv);
    strcpy(U.vote, "-1");
    if (BIAJ == 1)
    {
        ajouter_utilisateur(U);
        gtk_label_set_text(GTK_LABEL(output1), "Ajout avec succès!");
    }
    else
        gtk_label_set_text(GTK_LABEL(output1), "Echec d'ajout! Veuillez réessayer.");
    BIAJ = 0;
}

void on_BIcalendarM_day_selected(GtkCalendar *calendar,
                                 gpointer user_data)
{
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &ar, &mr, &jr);
}

void on_BIrobotM_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        BIMOD = 1;
}

void on_BIconfirmerM_clicked(GtkWidget *button,
                             gpointer user_data)
{
    Utilisateur U;
    int CIN1, Ubv, Uv;

    GtkWidget *v;
    GtkWidget *nbv;
    GtkWidget *treeview1;
    GtkWidget *input2, *input3, *input4, *input5, *combo, *combo2;
    GtkWidget *output1;
    input2 = lookup_widget(button, "BIentry2M");
    input3 = lookup_widget(button, "BIentry3M");
    input4 = lookup_widget(button, "BIentry4M");
    input5 = lookup_widget(button, "BIentry5M");
    output1 = lookup_widget(button, "BIlabelmsgM");
    strcpy(U.nom, gtk_entry_get_text(GTK_ENTRY(input2)));
    strcpy(U.prenom, gtk_entry_get_text(GTK_ENTRY(input3)));
    strcpy(U.login, gtk_entry_get_text(GTK_ENTRY(input4)));
    strcpy(U.cin, U1.cin);
    combo = lookup_widget(button, "BIcombobox1M");
    combo2 = lookup_widget(button, "BIcombobox2M");
    strcpy(U.hf, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo)));
    strcpy(U.role, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo2)));
    U.DDN.jour = jr;
    U.DDN.mois = mr + 1;
    U.DDN.annee = ar;
    strcpy(U.pass, gtk_entry_get_text(GTK_ENTRY(input5)));
    nbv = lookup_widget(button, "BIspinbuttonM");
    Ubv = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(nbv));
    sprintf(U.numBV, "%d", Ubv);
    strcpy(U.vote, "-1");

    if (BIMOD == 1)
    {
        modifier_utilisateur(U);
        gtk_label_set_text(GTK_LABEL(output1), "Modification avec succès!");
    }
    else
        gtk_label_set_text(GTK_LABEL(output1), "Echec de modification! Veuillez réessayer.");
    BIMOD = 0;
}

void on_BIradiobuttonN_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        BIYN = 0;
}

void on_BIradiobuttonY_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        BIYN = 1;
}

void on_BIokbutton_clicked(GtkWidget *button,
                           gpointer user_data)
{
    if (BIYN == 1)
    {
        supprimer_utilisateur(U1);
    }
    gtk_widget_destroy(lookup_widget(button, "BIdialog"));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gestion des bureaux de vote

void on_treeview2_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data)
{
    GtkWidget *EspaceBV;
    GtkTreeIter iter;
    gchar *IdBV;
    gchar *CapE;
    gchar *del_p;
    gchar *ObsP;
    gchar *IdABV;
    gchar *Salle;
    BV b;
    int id, x;

    GtkTreeModel *model;
    model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path))
    {
        gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &IdBV, 1, &CapE, 2, &del_p, 3, &ObsP, 4, &IdABV, 5, &Salle, -1);
        strcpy(b.idBV, IdBV);
        strcpy(b.cap_el, CapE);
        strcpy(b.del_p, del_p);
        strcpy(b.obs_p, ObsP);
        strcpy(b.idABV, IdABV);
        strcpy(b.num_s, Salle);
        B1 = b;
    }
}

void on_JDreturn_clicked(GtkWidget *button,
                         gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "JDwindowG");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_AdminWindow();
    gtk_widget_show(fenetre_4);
}

void on_JDstat_clicked(GtkWidget *button,
                       gpointer user_data)
{
}

void on_JDmodifier_clicked(GtkWidget *button,
                           gpointer user_data)
{
    gtk_label_set_text(GTK_LABEL(lookup_widget(button, "JDlabelidM")), B1.idBV);
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "JDentry2M")), B1.cap_el);
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "JDentry3M")), B1.idABV);
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "JDcomboboxM")), B1.num_s);
    gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook2")));
}

void on_JDsupprimer_clicked(GtkWidget *button,
                            gpointer user_data)
{
    GtkWidget *fen1;
    if (strcmp(B1.idBV, "-1") != 0)
    {
        fen1 = create_JDdialog();
        gtk_widget_show(fen1);
    }
}

void on_JDactualiser_clicked(GtkWidget *button,
                             gpointer user_data)
{
    GtkWidget *treevieww;
    treevieww = lookup_widget(button, "treeview2");
    afficher_bv(treevieww);
    strcpy(B1.idBV, "-1");
}

void on_JDrechercher_clicked(GtkWidget *button,
                             gpointer user_data)
{
    GtkWidget *entrych;
    GtkWidget *JDtreeview;
    GtkWidget *fenetre_10;

    entrych = lookup_widget(button, "JDentryrech");
    fenetre_10 = lookup_widget(button, "JDwindowG");
    JDtreeview = lookup_widget(fenetre_10, "treeview2");
    afficherrech_bv(gtk_entry_get_text(GTK_ENTRY(entrych)), JDtreeview);
}

void on_JDcheckbuttonA_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        JDAJ = 1;
}

void on_JDconfirmerA_clicked(GtkWidget *button,
                             gpointer user_data)
{
    BV B;
    int op;

    GtkWidget *input1, *input2, *input3, *combo, *obsp;
    GtkWidget *output1;

    input1 = lookup_widget(button, "JDentry1A");
    input2 = lookup_widget(button, "JDentry2A");
    input3 = lookup_widget(button, "JDentry3A");

    output1 = lookup_widget(button, "JDlabelmsgA");

    strcpy(B.idBV, gtk_entry_get_text(GTK_ENTRY(input1)));
    strcpy(B.cap_el, gtk_entry_get_text(GTK_ENTRY(input2)));
    strcpy(B.idABV, gtk_entry_get_text(GTK_ENTRY(input3)));

    combo = lookup_widget(button, "JDcomboboxA");
    strcpy(B.num_s, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo)));

    obsp = lookup_widget(button, "JDspinbuttonA");
    op = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(obsp));
    sprintf(B.obs_p, "%d", op);

    if (JDAR == 1)
        strcpy(B.del_p, "Oui");
    else
        strcpy(B.del_p, "Non");

    if (JDAJ == 1)
    {
        ajouter_bv(B);
        gtk_label_set_text(GTK_LABEL(output1), "Ajout avec succès!");
    }
    else
        gtk_label_set_text(GTK_LABEL(output1), "Echec d'ajout! Veuillez réessayer.");
    JDAJ = 0;
}

void on_JDradiobuttonNA_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        JDAR = 0;
}

void on_JDradiobuttonYA_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        JDAR = 1;
}

void on_JDradiobuttonYM_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        JDMR = 1;
}

void on_JDradiobuttonNM_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        JDMR = 0;
}

void on_JDcheckbuttonM_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        JDMOD = 1;
}

void on_JDconfirmerM_clicked(GtkWidget *button,
                             gpointer user_data)
{
    BV B;
    int op;

    GtkWidget *input2, *input3, *combo, *obsp;
    GtkWidget *output1;

    input2 = lookup_widget(button, "JDentry2M");
    input3 = lookup_widget(button, "JDentry3M");

    output1 = lookup_widget(button, "JDlabelmsgM");

    strcpy(B.cap_el, gtk_entry_get_text(GTK_ENTRY(input2)));
    strcpy(B.idABV, gtk_entry_get_text(GTK_ENTRY(input3)));

    combo = lookup_widget(button, "JDcomboboxM");
    strcpy(B.num_s, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo)));

    obsp = lookup_widget(button, "JDspinbuttonM");
    op = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(obsp));
    sprintf(B.obs_p, "%d", op);
    strcpy(B.idBV, B1.idBV);

    if (JDMR == 1)
        strcpy(B.del_p, "Oui");
    else
        strcpy(B.del_p, "Non");

    if (JDMOD == 1)
    {
        modifier_bv(B1.idBV, B, "bv.txt");
        gtk_label_set_text(GTK_LABEL(output1), "Modification avec succès!");
    }
    else
        gtk_label_set_text(GTK_LABEL(output1), "Echec de la modification! Veuillez réessayer.");
    JDMOD = 0;
}

void on_JDquit_clicked(GtkWidget *button,
                       gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "JDwindowG");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_LoginWindow();
    gtk_widget_show(fenetre_4);
}

void on_JDradiobuttonN_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        JDYN = 0;
}

void on_JDradiobuttonY_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        JDYN = 1;
}

void on_JDokbutton_clicked(GtkWidget *button,
                           gpointer user_data)
{
    if (JDYN == 1)
    {
        supprimer_bv(B1);
        
    }
    gtk_widget_destroy(lookup_widget(button, "JDdialog"));
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gestion des élections

void on_treeview4_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data)
{
    GtkTreeIter iter;
    gchar *IdEl;
    gchar *Jour;
    gchar *Mois;
    gchar *Annee;
    gchar *NbH;
    gchar *NbCons;
    gchar *municip;
    Election e;

    GtkTreeModel *model;
    model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path))
    {
        gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &IdEl, 1, &Jour, 2, &Mois, 3, &Annee, 4, &NbH, 5, &NbCons, 6, &municip, -1);
        strcpy(e.identifiant, IdEl);
        strcpy(e.d.jour, Jour);
        strcpy(e.d.mois, Mois);
        strcpy(e.d.annee, Annee);
        strcpy(e.nhabit, NbH);
        strcpy(e.nbcons, NbCons);
        strcpy(e.municip, municip);
        E1 = e;
    }
}

void on_RAcalendarA_day_selected(GtkCalendar *calendar,
                                 gpointer user_data)
{
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &ar, &mr, &jr);
}

void on_RAcalendarM_day_selected(GtkCalendar *calendar,
                                 gpointer user_data)
{
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &ar, &mr, &jr);
}

void on_RAconfirmerM_clicked(GtkWidget *button,
                             gpointer user_data)
{
    Election E;

    GtkWidget *input2, *input3;
    GtkWidget *output1;

    input2 = lookup_widget(button, "RAspinbuttonM");
    input3 = lookup_widget(button, "RAcomboboxM");

    output1 = lookup_widget(button, "RAlabelmsgM");

    sprintf(E.nhabit, "%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input2)));
    strcpy(E.municip, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input3)));
    //strcpy(E.nbcons, "10");

    if(atoi(E.nhabit)<=5000)
        strcpy(E.nbcons, "10");
    else if(atoi(E.nhabit)>5000 && atoi(E.nhabit)<=10000)
        strcpy(E.nbcons, "12");
    else if(atoi(E.nhabit)>10000 && atoi(E.nhabit)<=25000)
        strcpy(E.nbcons, "16");
    else if(atoi(E.nhabit)>25000 && atoi(E.nhabit)<=50000)
        strcpy(E.nbcons, "22");
    else if(atoi(E.nhabit)>50000 && atoi(E.nhabit)<=100000)
        strcpy(E.nbcons, "30");
    else if(atoi(E.nhabit)>100000 && atoi(E.nhabit)<=500000)
        strcpy(E.nbcons, "40");
    else
        strcpy(E.nbcons, "60");
    strcpy(E.identifiant, E1.identifiant);

    sprintf(E.d.jour, "%d", jr);
    sprintf(E.d.mois, "%d", mr + 1);
    sprintf(E.d.annee, "%d", ar);

    if (RAMOD == 1)
    {
        modifier_election(E1.identifiant, E, "election.txt");
        gtk_label_set_text(GTK_LABEL(output1), "Modification avec succès!");
    }
    else
        gtk_label_set_text(GTK_LABEL(output1), "Echec de modification! Veuillez réessayer.");
    RAMOD = 0;
}

void on_RAconfirmerA_clicked(GtkWidget *button,
                             gpointer user_data)
{
    Election E;

    GtkWidget *input1, *input2, *input3;
    GtkWidget *output1;

    input1 = lookup_widget(button, "RAentry1A");
    input2 = lookup_widget(button, "RAspinbuttonA");
    input3 = lookup_widget(button, "RAcomboboxA");

    output1 = lookup_widget(button, "RAlabelmsgA");

    strcpy(E.identifiant, gtk_entry_get_text(GTK_ENTRY(input1)));
    sprintf(E.nhabit, "%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input2)));
    strcpy(E.municip, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input3)));
    //strcpy(E.nbcons, "10");

    if(atoi(E.nhabit)<=5000)
        strcpy(E.nbcons, "10");
    else if(atoi(E.nhabit)>5000 && atoi(E.nhabit)<=10000)
        strcpy(E.nbcons, "12");
    else if(atoi(E.nhabit)>10000 && atoi(E.nhabit)<=25000)
        strcpy(E.nbcons, "16");
    else if(atoi(E.nhabit)>25000 && atoi(E.nhabit)<=50000)
        strcpy(E.nbcons, "22");
    else if(atoi(E.nhabit)>50000 && atoi(E.nhabit)<=100000)
        strcpy(E.nbcons, "30");
    else if(atoi(E.nhabit)>100000 && atoi(E.nhabit)<=500000)
        strcpy(E.nbcons, "40");
    else
        strcpy(E.nbcons, "60");

    sprintf(E.d.jour, "%d", jr);
    sprintf(E.d.mois, "%d", mr + 1);
    sprintf(E.d.annee, "%d", ar);

    if (RAAJ == 1)
    {
        ajouter_election(E, "election.txt");
        gtk_label_set_text(GTK_LABEL(output1), "Ajout avec success !");
    }
    else
        gtk_label_set_text(GTK_LABEL(output1), "Echec d'ajout! Veuillez réessayer.");
    RAAJ = 0;
}

void on_RArechercher_clicked(GtkWidget *button,
                             gpointer user_data)
{
    GtkWidget *entrych;
    GtkWidget *RAGestElec;
    GtkWidget *fenetre_10;

    entrych = lookup_widget(button, "RAentryrech");
    fenetre_10 = lookup_widget(button, "RAwindowG");
    RAGestElec = lookup_widget(fenetre_10, "treeview4");
    afficherelec_rech(RAGestElec, gtk_entry_get_text(GTK_ENTRY(entrych)));
}

void on_RAsupprimer_clicked(GtkWidget *button,
                            gpointer user_data)
{
    GtkWidget *fen1;
    if (strcmp(E1.identifiant, "-1") != 0)
    {
        fen1 = create_RAdialog();
        gtk_widget_show(fen1);
    }
}

void on_RAactualiser_clicked(GtkWidget *button,
                             gpointer user_data)
{
    GtkWidget *treevieww;
    treevieww = lookup_widget(button, "treeview4");
    afficher_elec(treevieww);
    strcpy(E1.identifiant, "-1");
}

void on_RAmodifier_clicked(GtkWidget *button,
                           gpointer user_data)
{
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "RAcomboboxM")), E1.municip);
    gtk_label_set_text(GTK_LABEL(lookup_widget(button, "RAlabelId")), E1.identifiant);
    gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook6")));
}

void on_RAstat_clicked(GtkWidget *button,
                       gpointer user_data)
{
}

void on_RAquit_clicked(GtkWidget *button,
                       gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "RAwindowG");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_LoginWindow();
    gtk_widget_show(fenetre_4);
}

void on_RAreturn_clicked(GtkWidget *button,
                         gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "RAwindowG");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_AdminWindow();
    gtk_widget_show(fenetre_4);
}

void on_RAradiobuttonY_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        RAYN = 1;
}

void on_RAradiobuttonN_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        RAYN = 0;
}

void on_RAokbutton_clicked(GtkWidget *button,
                           gpointer user_data)
{
    if (RAYN == 1)
    {
        supprimer_election(E1.identifiant, "election.txt");
        
    }
    gtk_widget_destroy(lookup_widget(button, "RAdialog"));
}

void on_RArobotA_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        RAAJ = 1;
}

void on_RArobotM_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        RAMOD = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gestion des listes électorales

void on_treeview5_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data)
{

    GtkWidget *electeur;
    GtkTreeIter iter;
    gchar *identifiant;
    gchar *id;
    gchar *id1;
    gchar *id2;
    gchar *id3;
    gchar *orientation;
    listelectoral L, l;
    GtkTreeModel *model;
    model = gtk_tree_view_get_model(treeview);
    if (gtk_tree_model_get_iter(model, &iter, path))
    {

        gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &identifiant, 1, &id, 2, &orientation, 3, &id1, 4, &id2, 5,&id3 , -1);

        strcpy(L.identifiant, identifiant);
        strcpy(L.id, id);
        strcpy(L.id1, id1);
        strcpy(L.id2, id2);
        strcpy(L.id3, id3);
        strcpy(L.orientation, orientation);
        L1 = L;
    }
}

void on_TRcheckbuttonDA_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        TRDA = 1;
}

void on_TRcheckbuttonGA_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        TRGA = 1;
}

void on_TRrobotA_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        TRAJ = 1;
}

void on_TRconfirmerA_clicked(GtkWidget *button,
                             gpointer user_data)
{
    listelectoral L;

    GtkWidget *input1, *input2, *input3, *input4, *input5;
    GtkWidget *output1;

    input1 = lookup_widget(button, "TRentry1A");
    input2 = lookup_widget(button, "TRentry2A");
    input3 = lookup_widget(button, "TRentry3A");
    input4 = lookup_widget(button, "TRentry4A");
    input5 = lookup_widget(button, "TRentry5A");

    output1 = lookup_widget(button, "TRlabelmsgA");

    strcpy(L.identifiant, gtk_entry_get_text(GTK_ENTRY(input1)));
    strcpy(L.id, gtk_entry_get_text(GTK_ENTRY(input2)));
    strcpy(L.id1, gtk_entry_get_text(GTK_ENTRY(input3)));
    strcpy(L.id2, gtk_entry_get_text(GTK_ENTRY(input4)));
    strcpy(L.id3, gtk_entry_get_text(GTK_ENTRY(input5)));

    if (TRDA == 1 && TRGA != 1)
        strcpy(L.orientation, "Droite");
    else if (TRDA != 1 && TRGA == 1)
        strcpy(L.orientation, "Gauche");
    else
        strcpy(L.orientation, "Centre");

    if (TRAJ == 1)
    {
        ajouter_l("list.txt", L);
        gtk_label_set_text(GTK_LABEL(output1), "Ajout avec succès !");
    }
    else
        gtk_label_set_text(GTK_LABEL(output1), "Echec d'ajout! Veuillez réessayer.");
    TRAJ = 0;
    TRDA = 0;
    TRGA = 0;
}

void on_TRcheckbuttonGM_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        TRGM = 1;
}

void on_TRcheckbuttonDM_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        TRDM = 1;
}

void on_TRconfirmerM_clicked(GtkWidget *button,
                             gpointer user_data)
{
    listelectoral L;

    GtkWidget *input1, *input2, *input3, *input4, *input5;
    GtkWidget *output1;

    input2 = lookup_widget(button, "TRentry2M");
    input3 = lookup_widget(button, "TRentry3M");
    input4 = lookup_widget(button, "TRentry4M");
    input5 = lookup_widget(button, "TRentry5M");

    output1 = lookup_widget(button, "TRlabelmsgM");

    strcpy(L.id, gtk_entry_get_text(GTK_ENTRY(input2)));
    strcpy(L.id1, gtk_entry_get_text(GTK_ENTRY(input3)));
    strcpy(L.id2, gtk_entry_get_text(GTK_ENTRY(input4)));
    strcpy(L.id3, gtk_entry_get_text(GTK_ENTRY(input5)));

    if (TRDM == 1 && TRGM != 1)
        strcpy(L.orientation, "Droite");
    else if (TRDM != 1 && TRGM == 1)
        strcpy(L.orientation, "Gauche");
    else
        strcpy(L.orientation, "Centre");

    if (TRMOD == 1)
    {
        modifier_l("list.txt", L, L1.identifiant);
        gtk_label_set_text(GTK_LABEL(output1), "Modification avec succès !");
    }
    else
        gtk_label_set_text(GTK_LABEL(output1), "Echec de la modification! Veuillez réessayer.");
}

void on_TRrobotM_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        TRMOD = 1;
}

void on_TRreturn_clicked(GtkWidget *button,
                         gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "TRwindowG");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_ElecWindow();
    gtk_widget_show(fenetre_4);
}

void on_TRstat_clicked(GtkWidget *button,
                       gpointer user_data)
{
}

void on_TRmodifier_clicked(GtkWidget *button,
                           gpointer user_data)
{
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "TRentry2M")), L1.id);
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "TRentry3M")), L1.id1);
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "TRentry4M")), L1.id2);
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "TRentry5M")), L1.id3);
    gtk_label_set_text(GTK_LABEL(lookup_widget(button, "TRlabelIdM")), L1.identifiant);
    gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook8")));
}

void on_TRsupprimer_clicked(GtkWidget *button,
                            gpointer user_data)
{
    GtkWidget *fen1;
    if (strcmp(L1.identifiant, "-1") != 0)
    {
        fen1 = create_TRdialog();
        gtk_widget_show(fen1);
    }
}

void on_TRactualiser_clicked(GtkWidget *button,
                             gpointer user_data)
{
    GtkWidget *treevieww;
    treevieww = lookup_widget(button, "treeview5");
    afficher_l(treevieww);
    strcpy(L1.identifiant, "-1");
}

void on_TRrechercher_clicked(GtkWidget *button,
                             gpointer user_data)
{
    GtkWidget *entrych;
    GtkWidget *TRGest;
    GtkWidget *fenetre_10;

    entrych = lookup_widget(button, "TRentryrech");
    fenetre_10 = lookup_widget(button, "TRwindowG");
    TRGest = lookup_widget(fenetre_10, "treeview5");
    afficherrech_l(TRGest, gtk_entry_get_text(GTK_ENTRY(entrych)));
}

void on_TRquit_clicked(GtkWidget *button,
                       gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "TRwindowG");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_LoginWindow();
    gtk_widget_show(fenetre_4);
}

void on_TRradiobuttonY_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        TRYN = 1;
}

void on_TRradiobuttonN_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        TRYN = 0;
}

void on_TRokbutton_clicked(GtkWidget *button,
                           gpointer user_data)
{
    if (TRYN == 1)
    {
        supprimer_l("list.txt",L1.id);
        
    }
    gtk_widget_destroy(lookup_widget(button, "TRdialog"));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gestion des réclamations

void on_treeview7_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data)
{
    GtkTreeIter iter;
    gchar *idrec;
    gchar *numbv;
    gchar *ler;
    gchar *typerec;
    Reclamation r;

    GtkTreeModel *model;
    model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path))
    {
        gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &idrec, 1, &numbv, 2, &ler, 3, &typerec, -1);
        strcpy(r.idrec, typerec);
        strcpy(r.numBV, numbv);
        strcpy(r.Listelecreclame, numbv);
        strcpy(r.typerec, typerec);
        strcpy(r.textrec, "");
        R1 = r;
    }
}

void on_BhconfirmerA_clicked(GtkWidget *button,
                             gpointer user_data)
{
    Reclamation R;

    GtkWidget *input1, *input2, *input3, *input4, *input5;
    GtkWidget *output1;

    input1 = lookup_widget(button, "BHentry1A");
    input2 = lookup_widget(button, "BHcomboboxA");
    input3 = lookup_widget(button, "BHentry2A");
    input4 = lookup_widget(button, "BHentry3A");
    input5 = lookup_widget(button, "BHspinbuttonA");

    output1 = lookup_widget(button, "BHlabelmsgA");

    strcpy(R.idrec, gtk_entry_get_text(GTK_ENTRY(input1)));
    sprintf(R.numBV, "%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input5)));
    strcpy(R.typerec, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input2)));
    strcpy(R.textrec, gtk_entry_get_text(GTK_ENTRY(input3)));
    strcpy(R.Listelecreclame, gtk_entry_get_text(GTK_ENTRY(input4)));

    if (BHAJ == 1)
    {
        ajouter_reclamation(R, "reclamation.txt");
        gtk_label_set_text(GTK_LABEL(output1), "Ajout avec succès !");
    }
    else
        gtk_label_set_text(GTK_LABEL(output1), "Echec d'ajout! Veuillez réessayer.");
    BHAJ = 0;
}

void on_BHrobotA_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        BHAJ = 1;
}

void on_BHrobotM_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        BHMOD = 1;
}

void on_BHconfirmerM_clicked(GtkWidget *button,
                             gpointer user_data)
{
    Reclamation R;

    GtkWidget *input1, *input2, *input3, *input4, *input5;
    GtkWidget *output1;

    input2 = lookup_widget(button, "BHcomboboxM");
    input3 = lookup_widget(button, "BHentry2M");
    input4 = lookup_widget(button, "BHentry3M");
    input5 = lookup_widget(button, "BHspinbuttonM");

    output1 = lookup_widget(button, "BHlabelmsgM");

    sprintf(R.numBV, "%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input5)));
    strcpy(R.typerec, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input2)));
    strcpy(R.textrec, gtk_entry_get_text(GTK_ENTRY(input3)));
    strcpy(R.Listelecreclame, gtk_entry_get_text(GTK_ENTRY(input4)));
    strcpy(R.idrec, R1.idrec);

    if (BHMOD == 1)
    {
        modifier_reclamation(R1.idrec, R, "reclamation.txt");
        gtk_label_set_text(GTK_LABEL(output1), "Modification avec succès!");
    }
    else
        gtk_label_set_text(GTK_LABEL(output1), "Echec de modification! Veuillez réessayer.");
    BHMOD = 0;
}

void on_BHreturn_clicked(GtkWidget *button,
                         gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "BHwindowG");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_LoginWindow();
    gtk_widget_show(fenetre_4);
}

void on_BHstat_clicked(GtkWidget *button,
                       gpointer user_data)
{
}

void on_BHmodifier_clicked(GtkWidget *button,
                           gpointer user_data)
{
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "BHentry2M")), R1.textrec);
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "BHentry3M")), R1.Listelecreclame);
    gtk_label_set_text(GTK_LABEL(lookup_widget(button, "BHlabelIdM")), R1.idrec);
    gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook10")));
}

void on_BHsupprimer_clicked(GtkWidget *button,
                            gpointer user_data)
{
    GtkWidget *fen1;
    if (strcmp(R1.idrec, "-1") != 0)
    {
        fen1 = create_BHdialog();
        gtk_widget_show(fen1);
    }
}

void on_BHactualiser_clicked(GtkWidget *button,
                             gpointer user_data)
{
    GtkWidget *treevieww;
    treevieww = lookup_widget(button, "treeview7");
    afficher_rec(treevieww);
    strcpy(R1.idrec, "-1");
}

void on_BHrechercher_clicked(GtkWidget *button,
                             gpointer user_data)
{
    GtkWidget *entrych;
    GtkWidget *RAGestElec;
    GtkWidget *fenetre_10;

    entrych = lookup_widget(button, "BHentryrech");
    fenetre_10 = lookup_widget(button, "BHwindowG");
    RAGestElec = lookup_widget(fenetre_10, "treeview7");
    afficherrec_rech(RAGestElec, gtk_entry_get_text(GTK_ENTRY(entrych)));
}

void on_BHquit_clicked(GtkWidget *button,
                       gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "BHwindowG");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_LoginWindow();
    gtk_widget_show(fenetre_4);
}

void on_BHradiobuttonN_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        BHYN = 0;
}

void on_BHradiobuttonY_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        BHYN = 1;
}

void on_BHokbutton_clicked(GtkWidget *button,
                           gpointer user_data)
{
    if (BHYN == 1)
    {
        supprimer_reclamation(R1.idrec, "reclamation.txt");
        
    }
    gtk_widget_destroy(lookup_widget(button, "BHdialog"));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Login Window

void on_Loginrobot_toggled(GtkToggleButton *togglebutton,
                           gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        RLog = 1;
}

void on_LoginButton_clicked(GtkWidget *button,
                            gpointer user_data)
{
    GtkWidget *output1;
    GtkWidget *login1;
    GtkWidget *pass;
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    GtkWidget *acceuilw,*p;

    output1 = lookup_widget(button, "Loginlabelrobot");
    login1 = lookup_widget(button, "entry38");
    pass = lookup_widget(button, "entry39");

    if (RLog == 1)
    {
        U2 = login(gtk_entry_get_text(GTK_ENTRY(login1)), gtk_entry_get_text(GTK_ENTRY(pass)));
        if (strcmp(U2.login, "-1") == 0)
        {
            gtk_label_set_text(GTK_LABEL(output1), "Vérifier vos coordonnées!");
        }
        else
        {
            if (strcmp(U2.role, "Administrateur") == 0)
            {
                fenetre_3 = lookup_widget(button, "LoginWindow");
                gtk_widget_destroy(fenetre_3);
                fenetre_4 = create_AdminWindow();
                gtk_widget_show(fenetre_4);
            }
            if (strcmp(U2.role, "Agent_du_BV") == 0)
            {
		acceuilw=lookup_widget(button,"LoginWindow");
		gtk_widget_hide (acceuilw); 
		gestionw = create_gestionw (); 
		p=lookup_widget(gestionw,"treeview2w"); 
		Afficherobservateur(p,"observateur.txt"); 
		gtk_widget_show (gestionw); 
		i=0; 
		j=0;
            }
            if (strcmp(U2.role, "Electeur") == 0)
            {

                fenetre_3 = lookup_widget(button, "LoginWindow");
                gtk_widget_destroy(fenetre_3);
                fenetre_4 = create_ElecWindow();
                gtk_widget_show(fenetre_4);
            }
            if (strcmp(U2.role, "Observateur") == 0)
            {
                fenetre_3 = lookup_widget(button, "LoginWindow");
                gtk_widget_destroy(fenetre_3);
                fenetre_4 = create_BHwindowG();
                gtk_widget_show(fenetre_4);
            }
        }
    }
    else
        gtk_label_set_text(GTK_LABEL(output1), "Case à cocher!");
    RLog = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Admin Window

void on_AdminbuttonGU_clicked(GtkWidget *button,
                              gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "AdminWindow");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_BIwindowG();
    gtk_widget_show(fenetre_4);
}

void on_AdminbuttonGE_clicked(GtkWidget *button,
                              gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "AdminWindow");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_RAwindowG();
    gtk_widget_show(fenetre_4);
}

void on_AdminbuttonGBV_clicked(GtkWidget *button,
                               gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "AdminWindow");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_JDwindowG();
    gtk_widget_show(fenetre_4);
}

void on_Adminquit_clicked(GtkWidget *button,
                          gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "AdminWindow");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_LoginWindow();
    gtk_widget_show(fenetre_4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Elec Window

void on_ElecVoter_clicked(GtkWidget *button,
                          gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "ElecWindow");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_VoteWindow();
    gtk_widget_show(fenetre_4);
}

void on_ElecGLE_clicked(GtkWidget *button,
                        gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "ElecWindow");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_TRwindowG();
    gtk_widget_show(fenetre_4);
}

void on_Elecquit_clicked(GtkWidget *button,
                         gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "ElecWindow");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_LoginWindow();
    gtk_widget_show(fenetre_4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Vote Window

void on_treeviewV_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data)
{

    GtkWidget *electeur;
    GtkTreeIter iter;
    gchar *identifiant;
    gchar *id;
    gchar *id1;
    gchar *id2;
    gchar *id3;
    gchar *orientation;
    listelectoral L, l;
    GtkTreeModel *model;
    model = gtk_tree_view_get_model(treeview);
    if (gtk_tree_model_get_iter(model, &iter, path))
    {

        gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &identifiant, 1, &id, 2, &orientation, 3, &id1, 4, &id2, 5,&id3 , -1);

        strcpy(L.identifiant, identifiant);
        strcpy(L.id, id);
        strcpy(L.id1, id1);
        strcpy(L.id2, id2);
        strcpy(L.id3, id3);
        strcpy(L.orientation, orientation);
        L1 = L;

    }
}

void on_Vvoter_clicked(GtkWidget *button,
                       gpointer user_data)
{
    Utilisateur U;
    GtkWidget *output;
    GtkWidget *output1,*output2,*output3,*output4;
    output = lookup_widget(button, "Vlabelmsg");
    if(Vrob==1)
    {
    if (strcmp(L1.identifiant, "-1") == 0)
    {
	strcpy(U2.vote,"0");
	modifier_utilisateur(U2);
        gtk_label_set_text(output, "Votre vote est compté blanc");
        gtk_widget_show(create_dialog1());
    }
    else
    {
	strcpy(U2.vote,L1.identifiant);
	modifier_utilisateur(U2);
        gtk_label_set_text(output, "Vote ajouté avec succès!");
	output1 = lookup_widget(button, "labelid");
	output2 = lookup_widget(button, "label715");
	output3 = lookup_widget(button, "label716");
	output4 = lookup_widget(button, "label717");
	gtk_label_set_text(GTK_LABEL(output1), L1.identifiant);
	gtk_label_set_text(GTK_LABEL(output2), L1.id1);
	gtk_label_set_text(GTK_LABEL(output3), L1.id2);
	gtk_label_set_text(GTK_LABEL(output4), L1.id);
        gtk_widget_show(create_dialog1());
    }
    }
    else
        gtk_label_set_text(output, "Veuillez confirmer votre vote !");	
}

void on_Vrobot_toggled(GtkToggleButton *togglebutton,
                       gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        Vrob = 1;
}

void on_Vquit_clicked(GtkWidget *button,
                      gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "VoteWindow");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_LoginWindow();
    gtk_widget_show(fenetre_4);
}

void on_Vactualiser_clicked(GtkWidget *button,
                            gpointer user_data)
{
    GtkWidget *treevieww;
    treevieww = lookup_widget(button, "treeviewV");
    afficher_l(treevieww);
    strcpy(L1.identifiant, "-1");
}

void on_Vrechercher_clicked(GtkWidget *button,
                            gpointer user_data)
{
    GtkWidget *entrych;
    GtkWidget *TRGest;
    GtkWidget *fenetre_10;

    entrych = lookup_widget(button, "Ventryrech");
    fenetre_10 = lookup_widget(button, "VoteWindow");
    TRGest = lookup_widget(fenetre_10, "treeviewV");
    afficherrech_l(TRGest, gtk_entry_get_text(GTK_ENTRY(entrych)));
}

void on_Vreturn_clicked(GtkWidget *button,
                        gpointer user_data)
{
    GtkWidget *fenetre_3;
    GtkWidget *fenetre_4;
    fenetre_3 = lookup_widget(button, "VoteWindow");
    gtk_widget_destroy(fenetre_3);
    fenetre_4 = create_ElecWindow();
    gtk_widget_show(fenetre_4);
}

void
on_treeviewCG_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_Statactualiser_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_Statquit_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_Statreturn_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{

}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gestion des observateurs:

GtkTreeSelection *selection1;

void
on_AcceuilGestionw_clicked              (GtkButton       *button,
                                        gpointer         user_data)  
{

GtkWidget *p;
gtk_widget_hide (acceuilw); 
gestionw = create_gestionw (); 
p=lookup_widget(gestionw,"treeview2w");
Afficherobservateur(p,"observateur.txt"); 
gtk_widget_show (gestionw); 
i=0; 
j=0;
}


void
on_Ajouterobservateur_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
observateur o;
GtkWidget *entrylog; 
GtkWidget *entrypass;
GtkWidget *log;
GtkWidget *pass;
GtkWidget *numb;
GtkWidget *saisirnum;


GtkWidget *entrysexew;
GtkWidget *entryIdw;
GtkWidget *entrynatw;

GtkWidget *entrynomw;
GtkWidget *labelIdw;
GtkWidget *labelsexew;
GtkWidget *labelnatw;
GtkWidget *labelDatew;
GtkWidget *labelnomw;
 
GtkWidget *existew;
GtkWidget* successw;
GtkWidget *calw;
int b=1;
int jj1,mm1,aa1;
FILE*f=NULL;

numb=lookup_widget(gestionw,"numb");

saisirnum=lookup_widget(gestionw,"saisirnum");

entryIdw=lookup_widget(gestionw,"entry5w");
//entrysexew=lookup_widget(gestionw,"combobox1w");
entrynatw=lookup_widget(gestionw,"combobox2w");

entrylog=lookup_widget(gestionw,"entrylog");
entrypass=lookup_widget(gestionw,"entrypass");
log=lookup_widget(gestionw,"log");
pass=lookup_widget(gestionw,"pass");


entrynomw=lookup_widget(gestionw,"entry3w");

labelIdw=lookup_widget(gestionw,"label13w");
labelsexew=lookup_widget(gestionw,"label7w");
labelnatw=lookup_widget(gestionw,"label8w");

labelnomw=lookup_widget(gestionw,"label10w");
existew=lookup_widget(gestionw,"label34w");


successw=lookup_widget(gestionw,"label35w");
calw=lookup_widget(gestionw,"yawmia");
        strcpy(o.cin,gtk_entry_get_text(GTK_ENTRY(entryIdw) ) );
        //strcpy(o.sexe,gtk_combo_box_get_active_text(GTK_COMBO_BOX(entrysexew)));
        strcpy(o.nationalite,gtk_combo_box_get_active_text(GTK_COMBO_BOX(entrynatw)));
	 strcpy(o.sexe,sexe);
        strcpy(o.nom,gtk_entry_get_text(GTK_ENTRY(entrynomw) ) );
        strcpy(o.user,gtk_entry_get_text(GTK_ENTRY(entrylog) ) );
        strcpy(o.password,gtk_entry_get_text(GTK_ENTRY(entrypass) ) );
        strcpy(o.appartenance,gtk_entry_get_text(GTK_ENTRY(numb) ) );
    
 gtk_widget_hide (successw);
 gtk_calendar_get_date (GTK_CALENDAR(calw),
                       &aa1,
                       &mm1,
                       &jj1);



 gtk_widget_hide (successw); 



if(strcmp(o.cin,"")==0){  
		  gtk_widget_show (labelIdw); 
b=0;
}
else {
		  gtk_widget_hide(labelIdw); 
}


if(strcmp(o.nationalite,"")==0){
		  gtk_widget_show (labelnatw);
b=0;
}
else {
		  gtk_widget_hide(labelnatw);
}

if(strcmp(o.nom,"")==0){
		  gtk_widget_show (labelnomw);
b=0;
}
else {
		  gtk_widget_hide(labelnomw);
}

if(strcmp(o.user,"")==0){
		  gtk_widget_show (log);
b=0;
}
else {
		  gtk_widget_hide(log);
}

if(strcmp(o.password,"")==0){
		  gtk_widget_show (pass);
b=0;
}
else {
		  gtk_widget_hide(pass);
}



if(strcmp(o.appartenance,"")==0){
		  gtk_widget_show (saisirnum);
b=0;
}
else {
		  gtk_widget_hide(saisirnum);
}




if(b==1){

//existance 

        if(exist_observateur(o.cin)==1)   
        {

				  gtk_widget_show (existew); 
                }
                else {                     gtk_widget_hide (existew); 

       f=fopen("observateur.txt","a+"); 
fprintf(f,"%s %s %s %d/%d/%d %s %s %s %s\n",o.cin,o.sexe,o.nationalite,jj1,mm1+1,aa1,o.nom,o.user,o.password,o.appartenance); 
fclose(f);
     
//ajouter_observateur(o);
                  gtk_widget_show (successw); 


//mise a jour du treeView
        GtkWidget* p=lookup_widget(gestionw,"treeview2w");

        Afficherobservateur(p,"observateur.txt");
}

}
}



void
on_Modifierobservateur_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

      GtkWidget *combobox3w;
        GtkWidget *combobox4w;
     combobox3w=lookup_widget(button,"combobox3w");
     combobox4w=lookup_widget(button,"combobox4w");
       	 observateur o;

        strcpy(o.cin,gtk_label_get_text(GTK_LABEL(lookup_widget(gestionw,"label20w"))));
        
     strcpy(o.sexe,gtk_combo_box_get_active_text(GTK_COMBO_BOX(lookup_widget(gestionw,"combobox3w"))));
     strcpy(o.nationalite,gtk_combo_box_get_active_text(GTK_COMBO_BOX(lookup_widget(gestionw,"combobox4w"))));
        strcpy(o.nom,gtk_entry_get_text(GTK_ENTRY(lookup_widget(gestionw,"entry8w"))));
        strcpy(o.date,gtk_entry_get_text(GTK_ENTRY(lookup_widget(gestionw,"entry9w"))));

   strcpy(o.user,gtk_entry_get_text(GTK_ENTRY(lookup_widget(gestionw,"entrylogm"))));
   strcpy(o.password,gtk_entry_get_text(GTK_ENTRY(lookup_widget(gestionw,"entrypassm"))));



 strcpy(o.appartenance,gtk_entry_get_text(GTK_ENTRY(lookup_widget(gestionw,"numbrm"))));
   
        supprimer_observateur(o.cin);
        ajouter_observateur(o);
//mise ajour du tree view 
        Afficherobservateur(lookup_widget(gestionw,"treeview1"),"observateur.txt");
	gtk_widget_show(lookup_widget(gestionw,"label37w"));
        GtkWidget *p=lookup_widget(gestionw,"treeview2w");
        Afficherobservateur(p,"observateur.txt");
}





void
on_chercherobservateur_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *p1w;
GtkWidget *entryw;
GtkWidget *labelidw;
GtkWidget *nbResultatw;
GtkWidget *messagew;

char cin[30];
char chnb[30];
int b=0,nb; //b=0  entry  cherche vide 
entryw=lookup_widget(gestionw,"entry10w");
labelidw=lookup_widget(gestionw,"label28w");
p1w=lookup_widget(gestionw,"treeview2w");
strcpy(cin,gtk_entry_get_text(GTK_ENTRY(entryw)));

if(strcmp(cin,"")==0){
  gtk_widget_show (labelidw);b=0;
}else{
b=1;
gtk_widget_hide (labelidw);}

if(b==0)
    {return;
    }
    else
    {

nb=Chercherobservateur(p1w,"observateur.txt",cin);

 

sprintf(chnb,"%d",nb);       
nbResultatw=lookup_widget(gestionw,"label27");
messagew=lookup_widget(gestionw,"label26w");
gtk_label_set_text(GTK_LABEL(nbResultatw),chnb);

gtk_widget_show (nbResultatw);
gtk_widget_show (messagew);
}
}


void
on_GestionAcceuilw_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *gestionw,*LoginWindow;
gestionw=lookup_widget(button,"gestionw");
gtk_widget_hide (gestionw); 
LoginWindow = create_LoginWindow ();
gtk_widget_show (LoginWindow);
}




void
on_bmodifier_clickedw                   (GtkButton       *button,
                                        gpointer         user_data)
{
        gchar *cin;
        gchar *sexe;
        gchar *nationalite;
        gchar *date;
        gchar *nom;
 gchar *user;
 gchar *password;
 gchar *appartenance;
  
        GtkTreeModel     *model;
        GtkTreeIter iter;
        if (gtk_tree_selection_get_selected(selection1, &model, &iter))
        {

        gtk_widget_hide(lookup_widget(gestionw,"label37w"));
                gtk_tree_model_get (model,&iter,0,&cin,1,&sexe,2,&nationalite,3,&date,4,&nom,5,&user,6,&password,7,&appartenance,-1);   
       
                gtk_entry_set_text(GTK_ENTRY(lookup_widget(gestionw,"combobox3w")),sexe);
                gtk_entry_set_text(GTK_ENTRY(lookup_widget(gestionw,"combobox4w")),nationalite);
                gtk_entry_set_text(GTK_ENTRY(lookup_widget(gestionw,"entry9w")),date);
                gtk_entry_set_text(GTK_ENTRY(lookup_widget(gestionw,"entry8w")),nom);


		gtk_entry_set_text(GTK_ENTRY(lookup_widget(gestionw,"entrylogm")),user);
		gtk_entry_set_text(GTK_ENTRY(lookup_widget(gestionw,"entrypassm")),password);

		gtk_entry_set_text(GTK_ENTRY(lookup_widget(gestionw,"numbrm")),appartenance);
		


                GtkWidget* msgId=lookup_widget(gestionw,"label20w");
                GtkWidget* msg1=lookup_widget(gestionw,"label36w");
                gtk_label_set_text(GTK_LABEL(msgId),cin);
                gtk_widget_show(msgId);
                gtk_widget_show(msg1);
                gtk_widget_show(lookup_widget(gestionw,"button4w"));
                gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(gestionw,"notebook1w")));
        gtk_entry_set_text(GTK_ENTRY(lookup_widget(gestionw,"entry9w")),date);
        }

}


void
on_bsupprimer_clickedw                  (GtkButton       *button,
                                        gpointer         user_data)
{
    gchar *cin;
    gchar *sexe;
    gchar *nationalite;
    gchar *date;
    gchar *nom;
   gchar *user;
 gchar *password;
 gchar *appartenance;
    GtkTreeModel     *model;
    GtkTreeIter iter;
       if (gtk_tree_selection_get_selected(selection1, &model, &iter))
        {
            gtk_tree_model_get (model,&iter,0,&cin,1,&sexe,2,&nationalite,3,&date,4,&nom,5,&user,6,&password,7,&appartenance,-1);//recuperer les information de la ligne selectionneé
            supprimer_observateur(cin);
            Afficherobservateur(lookup_widget(gestionw,"treeview2w"),"observateur.txt");        
        }
}


void
on_bafficher12w_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
        GtkWidget *p=lookup_widget(gestionw,"treeview2w");
        Afficherobservateur(p,"observateur.txt");
}


void
on_treeview2w_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
    	gchar *cin;
        gchar *sexe;
        gchar *nationalite;
        gchar *date;
        gchar *nom;
        gchar *user;
        gchar *password;
 gchar *appartenance;
        GtkTreeModel     *model;
        GtkTreeIter iter;
        GtkWidget *p=lookup_widget(gestionw,"treeview2w");
        selection1 = gtk_tree_view_get_selection(GTK_TREE_VIEW(p));
       
}












void
on_radiobuttonf_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 strcpy(sexe,"Femelle");
}


void
on_radiobuttonm_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 strcpy(sexe,"Male");

}


void
on_AdminbuttonGO_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *acceuilw,*p;
acceuilw=lookup_widget(button,"AdminWindow");
gtk_widget_hide (acceuilw); 
gestionw = create_gestionw (); 
p=lookup_widget(gestionw,"treeview2w"); 
Afficherobservateur(p,"observateur.txt"); 
gtk_widget_show (gestionw); 
i=0; 
j=0;
}


void
on_AMStat_clicked                      (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget* input;
  GtkWidget* output;
  GtkWidget* output1;
  GtkWidget* output2;
  GtkWidget *statw;
  //GtkWidget *sta;
  observateur o;
 char var[100];
 char var1[100];
 char var2[100];

 int N=0, NT=0, NE=0;
 float TT = 0., TE = 0.;
 statw=lookup_widget(objet_graphique,"statw");
 statw=create_statw();
 gtk_widget_show(statw);
 FILE* f = fopen("observateur.txt", "r");
 while(fscanf(f,"%s %s %s %s %s %s %s %s\n",o.cin,o.sexe,o.nationalite,o.date,o.nom,o.user,o.password,o.appartenance)!=EOF){
	N ++;
   if (strcmp(o.nationalite,"Tunisienne") == 0) NT ++;
   else NE ++;
	}
	fclose(f);
	printf("Nombre des observateurs : %d\n", N);
	printf("Nombre des observateurs tunisiens : %d\n", NT);
	printf("Nombre des observateurs étrangers : %d\n", NE);
	if(N != 0)
	{
		TT = (float)NT / N * 100.;
		TE = 100. - TT;
	}
	/*printf("Taux des observateurs tunisiens : %.2f %% \n", TT);
	printf("Taux des observateurs étrangers : %.2f %% \n", TE);*/
    
 
  sprintf(var,"%d",N);
  sprintf(var1,"%.2f %% \n",TT);
  sprintf(var2,"%.2f %% \n",TE);
 
  output = lookup_widget(statw,"labelnbobst");
  gtk_label_set_text(GTK_LABEL(output),var);
  output1 = lookup_widget(statw,"labeltauxobstun");
  gtk_label_set_text(GTK_LABEL(output1),var1);
  output2 = lookup_widget(statw,"labeltauxobsetrang");
  gtk_label_set_text(GTK_LABEL(output2),var2);

 
  
}


void
on_facebook_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
    char *URL;   
    URL = "xdg-open http://www.facebook.com/isietn";
    system(URL);   
    return 0;
}


void
on_mail_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
    char *URL;   
    URL = "xdg-open http://www.instagram.com/isietn";
    system(URL);   
    return 0;
}


void
on_instagram_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_widget_destroy(lookup_widget(button, "dialog1"));
}

