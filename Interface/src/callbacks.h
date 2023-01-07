#include <gtk/gtk.h>
  GtkWidget *acceuilw;
  GtkWidget *gestionw;
typedef struct observateur observateur ;
struct observateur{
char cin[30];
char sexe[30];
char nationalite[30];
char date[30];
char nom[30];
char user[30];
char password[30];
char appartenance[30];
};
int i,j;
void on_treeview1_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data);

void on_BIrechercher_clicked(GtkWidget *button,
                             gpointer user_data);

void on_BIquit_clicked(GtkWidget *button,
                       gpointer user_data);

void on_BIactualiser_clicked(GtkWidget *button,
                             gpointer user_data);

void on_BIsupprimer_clicked(GtkWidget *button,
                            gpointer user_data);

void on_BImodifier_clicked(GtkWidget *button,
                           gpointer user_data);

void on_BIStat_clicked(GtkWidget *button,
                       gpointer user_data);

void on_BIreturn_clicked(GtkWidget *button,
                         gpointer user_data);

void on_BIcalendarA_day_selected(GtkCalendar *calendar,
                                 gpointer user_data);

void on_BIrobotA_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data);

void on_BIconfirmerA_clicked(GtkWidget *button,
                             gpointer user_data);

void on_BIcalendarM_day_selected(GtkCalendar *calendar,
                                 gpointer user_data);

void on_BIrobotM_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data);

void on_BIconfirmerM_clicked(GtkWidget *button,
                             gpointer user_data);

void on_label31_show(GtkWidget *widget,
                     gpointer user_data);

void on_JDreturn_clicked(GtkWidget *button,
                         gpointer user_data);

void on_JDstat_clicked(GtkWidget *button,
                       gpointer user_data);

void on_JDmodifier_clicked(GtkWidget *button,
                           gpointer user_data);

void on_JDsupprimer_clicked(GtkWidget *button,
                            gpointer user_data);

void on_JDactualiser_clicked(GtkWidget *button,
                             gpointer user_data);

void on_JDrechercher_clicked(GtkWidget *button,
                             gpointer user_data);

void on_JDcheckbuttonA_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data);

void on_JDconfirmerA_clicked(GtkWidget *button,
                             gpointer user_data);

void on_JDradiobuttonNA_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data);

void on_JDradiobuttonYA_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data);

void on_JDradiobuttonYM_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data);

void on_JDradiobuttonNM_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data);

void on_JDcheckbuttonM_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data);

void on_JDconfirmerM_clicked(GtkWidget *button,
                             gpointer user_data);

void on_JDquit_clicked(GtkWidget *button,
                       gpointer user_data);

void on_BIradiobuttonN_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data);

void on_BIradiobuttonY_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data);

void on_BIokbutton_clicked(GtkWidget *button,
                           gpointer user_data);

void on_JDradiobuttonN_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data);

void on_JDradiobuttonY_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data);

void on_JDokbutton_clicked(GtkWidget *button,
                           gpointer user_data);

void on_AMtreeview_row_activated(GtkTreeView *treeview,
                                 GtkTreePath *path,
                                 GtkTreeViewColumn *column,
                                 gpointer user_data);

void on_AMreturn_clicked(GtkWidget *button,
                         gpointer user_data);

void on_AMquit_clicked(GtkWidget *button,
                       gpointer user_data);

void on_AMrechercher_clicked(GtkWidget *button,
                             gpointer user_data);

void on_AMactualiser_clicked(GtkWidget *button,
                             gpointer user_data);

void on_AMsupprimer_clicked(GtkWidget *button,
                            gpointer user_data);

void on_AMmodifier_clicked(GtkWidget *button,
                           gpointer user_data);



void on_AMcalendarA_day_selected(GtkCalendar *calendar,
                                 gpointer user_data);

void on_AMrobotA_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data);

void on_AMradiobuttonAH_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data);

void on_AMradiobuttonAF_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data);

void on_AMconfirmerA_clicked(GtkWidget *button,
                             gpointer user_data);

void on_AMradiobuttonMH_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data);

void on_AMradiobuttonMF_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data);

void on_AMrobotM_clicked(GtkWidget *button,
                         gpointer user_data);

void on_AMconfirmerM_clicked(GtkWidget *button,
                             gpointer user_data);

void on_AMradiobuttonN_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data);

void on_AMradiobuttonY_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data);

void on_AMokbutton_clicked(GtkWidget *button,
                           gpointer user_data);

void on_treeview2_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data);

void on_RAcalendarA_day_selected(GtkCalendar *calendar,
                                 gpointer user_data);

void on_RAcalendarM_day_selected(GtkCalendar *calendar,
                                 gpointer user_data);

void on_RArobotM_clicked(GtkWidget *button,
                         gpointer user_data);

void on_RAconfirmerM_clicked(GtkWidget *button,
                             gpointer user_data);
void on_RAconfirmerA_clicked(GtkWidget *button,
                             gpointer user_data);

void on_RArechercher_clicked(GtkWidget *button,
                             gpointer user_data);

void on_RAsupprimer_clicked(GtkWidget *button,
                            gpointer user_data);

void on_RAactualiser_clicked(GtkWidget *button,
                             gpointer user_data);

void on_RAmodifier_clicked(GtkWidget *button,
                           gpointer user_data);

void on_RAstat_clicked(GtkWidget *button,
                       gpointer user_data);

void on_RAquit_clicked(GtkWidget *button,
                       gpointer user_data);

void on_RAreturn_clicked(GtkWidget *button,
                         gpointer user_data);

void on_RAradiobuttonY_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data);

void on_RAradiobuttonN_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data);

void on_RAokbutton_clicked(GtkWidget *button,
                           gpointer user_data);

void on_treeview3_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data);

void on_treeview4_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data);

void on_RArobotA_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data);

void on_RArobotM_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data);

void on_treeview5_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data);

void on_TRcheckbuttonDA_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data);

void on_TRcheckbuttonGA_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data);

void on_TRrobotA_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data);

void on_TRconfirmerA_clicked(GtkWidget *button,
                             gpointer user_data);

void on_TRcheckbuttonGM_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data);

void on_TRcheckbuttonDM_toggled(GtkToggleButton *togglebutton,
                                gpointer user_data);

void on_TRconfirmerM_clicked(GtkWidget *button,
                             gpointer user_data);

void on_TRrobotM_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data);

void on_TRreturn_clicked(GtkWidget *button,
                         gpointer user_data);

void on_TRstat_clicked(GtkWidget *button,
                       gpointer user_data);

void on_TRmodifier_clicked(GtkWidget *button,
                           gpointer user_data);

void on_TRsupprimer_clicked(GtkWidget *button,
                            gpointer user_data);

void on_TRactualiser_clicked(GtkWidget *button,
                             gpointer user_data);

void on_TRrechercher_clicked(GtkWidget *button,
                             gpointer user_data);

void on_TRquit_clicked(GtkWidget *button,
                       gpointer user_data);

void on_TRradiobuttonY_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data);

void on_TRradiobuttonN_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data);

void on_TRokbutton_clicked(GtkWidget *button,
                           gpointer user_data);

void on_treeview7_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data);

void on_BhconfirmerA_clicked(GtkWidget *button,
                             gpointer user_data);

void on_BHrobotA_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data);

void on_BHrobotM_toggled(GtkToggleButton *togglebutton,
                         gpointer user_data);

void on_BHconfirmerM_clicked(GtkWidget *button,
                             gpointer user_data);

void on_BHreturn_clicked(GtkWidget *button,
                         gpointer user_data);

void on_BHstat_clicked(GtkWidget *button,
                       gpointer user_data);

void on_BHmodifier_clicked(GtkWidget *button,
                           gpointer user_data);

void on_BHsupprimer_clicked(GtkWidget *button,
                            gpointer user_data);

void on_BHactualiser_clicked(GtkWidget *button,
                             gpointer user_data);

void on_BHrechercher_clicked(GtkWidget *button,
                             gpointer user_data);

void on_BHquit_clicked(GtkWidget *button,
                       gpointer user_data);

void on_BHradiobuttonN_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data);

void on_BHradiobuttonY_toggled(GtkToggleButton *togglebutton,
                               gpointer user_data);

void on_BHokbutton_clicked(GtkWidget *button,
                           gpointer user_data);

void on_Loginrobot_toggled(GtkToggleButton *togglebutton,
                           gpointer user_data);

void on_LoginButton_clicked(GtkWidget *button,
                            gpointer user_data);

void on_AdminbuttonGU_clicked(GtkWidget *button,
                              gpointer user_data);

void on_AdminbuttonGE_clicked(GtkWidget *button,
                              gpointer user_data);

void on_AdminbuttonGBV_clicked(GtkWidget *button,
                               gpointer user_data);

void on_Adminquit_clicked(GtkWidget *button,
                          gpointer user_data);

void on_ElecVoter_clicked(GtkWidget *button,
                          gpointer user_data);

void on_ElecGLE_clicked(GtkWidget *button,
                        gpointer user_data);

void on_Elecquit_clicked(GtkWidget *button,
                         gpointer user_data);

void on_treeviewV_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data);

void on_Vvoter_clicked(GtkWidget *button,
                       gpointer user_data);

void on_Vrobot_toggled(GtkToggleButton *togglebutton,
                       gpointer user_data);

void on_Vquit_clicked(GtkWidget *button,
                      gpointer user_data);

void on_Vactualiser_clicked(GtkWidget *button,
                            gpointer user_data);

void on_Vrechercher_clicked(GtkWidget *button,
                            gpointer user_data);

void on_Vreturn_clicked(GtkWidget *button,
                        gpointer user_data);



void
on_treeviewCG_row_activated            (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_Statactualiser_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_Statquit_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_Statreturn_clicked                  (GtkButton       *button,
                                        gpointer         user_data);



void
on_AcceuilGestionw_clicked              (GtkButton       *button,
                                        gpointer         user_data);


void
on_GestionAcceuilw_clicked              (GtkButton       *button,
                                        gpointer         user_data);


void
on_bmodifier_clickedw                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_bsupprimer_clickedw                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_bafficher12w_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview2w_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);





void
on_button_calcule_clicked              (GtkButton       *button,
                                        gpointer         user_data);


void
on_Ajouterobservateur_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_Modifierobservateur_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_chercherobservateur_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobuttonf_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonm_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_AdminbuttonGO_clicked               (GtkButton       *button,
                                        gpointer         user_data);


void
on_AMStat_clicked                      (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_facebook_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_mail_clicked                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_instagram_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void set_window_background(gchar *__imgPath__);
