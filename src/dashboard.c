#include <gtk/gtk.h>
#include <string.h>
#include "bank.h"

extern struct customer s[100];

typedef struct {  //Home Tab
    // All home_bal widgets
    GtkWidget *g_lbl_home_bal;
    GtkWidget *g_lbl_home_acc_id;

    // All home_details widgets
    GtkWidget *g_lbl_home_lastlogin;
    GtkWidget *g_lbl_home_name;
    GtkWidget *g_lbl_home_email;
    GtkWidget *g_lbl_home_mob_no;
    GtkWidget *g_lbl_home_upi_handler;
    GtkWidget *g_lbl_home_upi_passcode;

    //Add funds tab
    GtkWidget *g_lbl_add_bal;
    GtkWidget *g_lbl_add_success;
    GtkWidget *g_lbl_add_fail;
    GtkWidget *g_entry_add_amt;
    GtkWidget *g_btn_add_funds;
    GtkWidget *g_entry_add_pass1;

    //UPI tab
    // All Upi pin widgets
    GtkWidget *g_lbl_pass_no_match;
    GtkWidget *g_lbl_pass_set;
    GtkWidget *g_lbl_pass_set_fail;
    GtkWidget *g_lbl_upi_warning;
    GtkWidget *g_entry_upi_pass;
    GtkWidget *g_entry_upi_repass;
    GtkWidget *g_switch_upi;
    GtkWidget *g_upi_img_ok;
    //All upi info widgets
    GtkWidget *g_lbl_upi_passcode1;
    GtkWidget *g_lbl_upi_handler;

    //Account Mod widgets
    // All acc_details widgets
    GtkWidget *g_lbl_name_holder;
    GtkWidget *g_lbl_email_holder;
    GtkWidget *g_lbl_mobile_holder;
    GtkWidget *g_lbl_curr_pass_incorrect;
    GtkWidget *g_lbl_new_set_successful;
    GtkWidget *g_lbl_new_set_fail;
    GtkWidget *g_lbl_mod_mob_err;
    GtkWidget *g_entry_new_email;
    GtkWidget *g_entry_new_mobile;
    GtkWidget *g_entry_new_password;
    GtkWidget *g_entry_password_mod;
    GtkWidget *g_check_email;
    GtkWidget *g_check_no;
    GtkWidget *g_check_pass;
    GtkWidget *g_btn_change_info;

    //Withdraw Widgets
    GtkWidget *g_lbl_withd_bal;
    GtkWidget *g_lbl_withd_success;
    GtkWidget *g_lbl_withd_fail;
    GtkWidget *g_lbl_withd_amt_err;
    GtkWidget *g_lbl_withd_pass_err;
    GtkWidget *g_lbl_withd_upi_pass_err;
    GtkWidget *g_lbl_withd_upi_rec_err;
    GtkWidget *g_lbl_withd_accid_err;
    GtkWidget *g_radio_cred;
    GtkWidget *g_radio_neft;
    GtkWidget *g_radio_upi;
    GtkWidget *g_entry_withd_amt;
    GtkWidget *g_entry_withd_accid;
    GtkWidget *g_entry_withd_upir;
    GtkWidget *g_entry_withd_upipass;
    GtkWidget *g_entry_withd_pass;

} appWidgets;

int user_index;

int dashboard_main(int index, int argc, char *argv[]){
    getFile();
    user_index = index;
    GtkBuilder* builder;
    GtkWidget* window2;

    appWidgets  *app_data = g_slice_new(appWidgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("../glade/dashboard.glade");
    window2 = GTK_WIDGET(gtk_builder_get_object(builder, "dashboard_main"));

    //Home widgets defied here
    app_data->g_lbl_home_acc_id = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_home_acc_id"));
    app_data->g_lbl_home_bal = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_home_balance"));
    app_data->g_lbl_home_email = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_home_email"));
    app_data->g_lbl_home_upi_passcode = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_home_upi_passcode"));
    app_data->g_lbl_home_upi_handler = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_home_upi_handler"));
    app_data->g_lbl_home_lastlogin = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_home_lastlogin"));
    app_data->g_lbl_home_mob_no = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_home_mob_no"));
    app_data->g_lbl_home_name = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_home_name"));

    //Add Funds widgets defined here
    app_data->g_btn_add_funds = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_funds"));
    app_data->g_entry_add_amt = GTK_WIDGET(gtk_builder_get_object(builder, "entry_add_amt"));
    app_data->g_entry_add_pass1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry_add_pass1"));
    app_data->g_lbl_add_bal = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_add_bal"));
    app_data->g_lbl_add_success = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_add_success"));
    app_data->g_lbl_add_fail = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_add_fail"));

    //UPI widgets defined here
    app_data->g_lbl_pass_no_match = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_pass_no_match"));
    app_data->g_lbl_pass_set = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_pass_set"));
    app_data->g_lbl_pass_set_fail = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_pass_set_fail"));
    app_data->g_lbl_upi_warning = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_upi_warning"));
    app_data->g_upi_img_ok = GTK_WIDGET(gtk_builder_get_object(builder, "img_upi_ok"));
    app_data->g_lbl_upi_handler = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_upi_handler"));
    app_data->g_lbl_upi_passcode1 = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_upi_passcode1"));
    app_data->g_entry_upi_pass = GTK_WIDGET(gtk_builder_get_object(builder, "entry_upi_pass"));
    app_data->g_entry_upi_repass = GTK_WIDGET(gtk_builder_get_object(builder, "entry_upi_repass"));

    //Account Details (modify) defined here
    app_data->g_lbl_name_holder = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_name"));
    app_data->g_lbl_mobile_holder = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_mobile"));
    app_data->g_lbl_email_holder = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_email"));
    app_data->g_lbl_curr_pass_incorrect = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_pass_incorrect"));
    app_data->g_lbl_new_set_fail = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_acc_fail"));
    app_data->g_lbl_mod_mob_err = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_mod_mob_err"));
    app_data->g_lbl_new_set_successful = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_acc_success"));
    app_data->g_entry_new_email = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_email"));
    app_data->g_entry_new_mobile = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_mobile"));
    app_data->g_entry_new_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_password"));
    app_data->g_entry_password_mod = GTK_WIDGET(gtk_builder_get_object(builder, "ent_pass"));
    app_data->g_check_pass = GTK_WIDGET(gtk_builder_get_object(builder, "check_no1"));
    app_data->g_check_no = GTK_WIDGET(gtk_builder_get_object(builder, "check_no"));
    app_data->g_check_email = GTK_WIDGET(gtk_builder_get_object(builder, "check_email"));
    app_data->g_btn_change_info = GTK_WIDGET(gtk_builder_get_object(builder, "btn_change_info"));

    //Withdraw widgets defined here
    app_data->g_lbl_withd_success = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_witd_success"));
    app_data->g_lbl_withd_fail = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_withd_fail"));
    app_data->g_lbl_withd_bal = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_withd_bal"));
    app_data->g_lbl_withd_accid_err = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_withd_accid_err"));
    app_data->g_lbl_withd_amt_err = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_withd_no_amt"));
    app_data->g_lbl_withd_pass_err = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_withd_pass_err"));
    app_data->g_lbl_withd_upi_pass_err = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_withd_upi_pass_err"));
    app_data->g_lbl_withd_upi_rec_err = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_withd_upi_rec_fail"));
    app_data->g_entry_withd_accid = GTK_WIDGET(gtk_builder_get_object(builder, "ent_witd_accid"));
    app_data->g_entry_withd_upipass = GTK_WIDGET(gtk_builder_get_object(builder, "entry_withd_upi_pass"));
    app_data->g_entry_withd_upir = GTK_WIDGET(gtk_builder_get_object(builder, "entry_withd_upir"));
    app_data->g_entry_withd_amt = GTK_WIDGET(gtk_builder_get_object(builder, "entry_withd_amt"));
    app_data->g_entry_withd_pass = GTK_WIDGET(gtk_builder_get_object(builder, "entry_withd_pass"));
    app_data->g_radio_upi = GTK_WIDGET(gtk_builder_get_object(builder, "rad_upi"));
    app_data->g_radio_neft = GTK_WIDGET(gtk_builder_get_object(builder, "rad_neft"));
    app_data->g_radio_cred = GTK_WIDGET(gtk_builder_get_object(builder, "rad_cred_deb"));

    gchar *bal;
    gchar *upi_pass;
    bal = g_strdup_printf("%d", s[index].balance);
    upi_pass = g_strdup_printf("%d", s[index].upiPass);

    //Home Data set
    gtk_label_set_text(app_data->g_lbl_home_name,s[index].userName);
    gtk_label_set_text(app_data->g_lbl_home_email,s[index].email);
    gtk_label_set_text(app_data->g_lbl_home_mob_no,s[index].mob_no);
    gtk_label_set_text(app_data->g_lbl_home_upi_handler,s[index].upiId);
    gtk_label_set_text(app_data->g_lbl_home_upi_passcode,upi_pass);
    gtk_label_set_text(app_data->g_lbl_home_lastlogin,s[index].last_login);
    gtk_label_set_text(app_data->g_lbl_home_acc_id,s[index].accNo);
    gtk_label_set_text(app_data->g_lbl_home_bal,bal);

    //Add Funds data set
    gtk_label_set_label(app_data->g_lbl_add_bal,bal);

    //UPI Data set
    gtk_label_set_text(app_data->g_lbl_upi_handler,s[index].upiId);
    gtk_label_set_text(app_data->g_lbl_upi_passcode1,upi_pass);

    //Account Details (modify) data set
    gtk_label_set_text(app_data->g_lbl_name_holder,s[index].userName);
    gtk_label_set_text(app_data->g_lbl_email_holder,s[index].email);
    gtk_label_set_text(app_data->g_lbl_mobile_holder,s[index].mob_no);

    //Withdraw data set
    gtk_label_set_text(app_data->g_lbl_withd_bal, bal);

    //Visibility
    gtk_widget_set_visible(app_data->g_upi_img_ok, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_pass_no_match, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_pass_set, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_pass_set_fail, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_add_success, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_add_fail, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_curr_pass_incorrect, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_new_set_successful, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_new_set_fail, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_withd_success, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_withd_fail, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_withd_pass_err, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_withd_accid_err, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_withd_amt_err, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_withd_upi_pass_err, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_withd_upi_rec_err, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_mod_mob_err, FALSE);
    /*
    gtk_widget_set_sensitive(GTK_ENTRY(app_data->g_entry_withd_upir), FALSE);
    gtk_widget_set_sensitive(GTK_ENTRY(app_data->g_entry_withd_upipass), FALSE);
    gtk_widget_set_sensitive(GTK_ENTRY(app_data->g_entry_withd_accid), FALSE);
    */
    //For UPI
    if (s[user_index].upiPass == 0){
        gtk_widget_set_visible(app_data->g_lbl_upi_warning, TRUE);
    } else {
        gtk_widget_set_visible(app_data->g_lbl_upi_warning, FALSE);
    }

    //Signal Connect and exit
    gtk_builder_connect_signals(builder, app_data);
    g_object_unref(builder);

    gtk_window_set_resizable(GTK_WINDOW(window2), FALSE);
    gtk_widget_show(window2);
    gtk_main();

    g_slice_free(appWidgets, app_data);
    g_free(bal);

    return 0;
}
void on_dashboard_main_destroy(){
    gtk_main_quit();
}
void on_btn_dashboard_exit_clicked (GtkButton *btn_exit, gpointer window){
    gtk_main_quit();
}

// UPI PI-PIN Update function
void on_btn_update_upi_clicked (GtkButton *btn_update_upi, appWidgets *app_data){
    getFile();
    gchar *upi_pass;
    if (s[user_index].upiPass == 0){
        gtk_widget_set_visible(app_data->g_lbl_upi_warning, TRUE);
    } else {
        gtk_widget_set_visible(app_data->g_lbl_upi_warning, FALSE);
    }
    gtk_widget_set_visible(app_data->g_upi_img_ok, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_pass_no_match, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_pass_set, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_pass_set_fail, FALSE);
    const char *password = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_upi_pass));
    const char *repeat_password = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_upi_repass));
    if (strcmp(password, repeat_password) == 0){
        if (set_upi_pass(user_index, password) == 1){
            gtk_widget_set_visible(app_data->g_lbl_pass_set, TRUE);
            upi_pass = g_strdup_printf("%d", s[user_index].upiPass);
            gtk_label_set_text(app_data->g_lbl_upi_passcode1,upi_pass);
            putFile();
        } else {
            gtk_widget_set_visible(app_data->g_lbl_pass_set_fail, TRUE);
        }
    } else {
        gtk_widget_set_visible(app_data->g_lbl_pass_no_match, TRUE);
    }
}

// Funds add function
void on_btn_add_funds_clicked (GtkButton *btn_add_funds, appWidgets *app_data){
    getFile();
    gchar *bal2;
    gtk_widget_set_visible(app_data->g_lbl_add_success, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_add_fail, FALSE);
    const char *amount = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_add_amt));
    const char *password = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_add_pass1));
    if (pass_check(user_index, password)==1){
        deposit(user_index, amount);
        putFile();
        getFile();
        bal2 = g_strdup_printf("%d", s[user_index].balance);
        gtk_label_set_text(app_data->g_lbl_home_bal,bal2);
        gtk_label_set_text(app_data->g_lbl_add_bal,bal2);
        gtk_label_set_text(app_data->g_lbl_withd_bal,bal2);
        gtk_widget_set_visible(app_data->g_lbl_add_success, TRUE);
    } else {
        gtk_widget_set_visible(app_data->g_lbl_add_fail, TRUE);
    }
}

// Account Modifications Function
void on_btn_change_info_clicked (GtkButton *btn_change_info, appWidgets *app_data){
    getFile();
    gtk_widget_set_visible(app_data->g_lbl_curr_pass_incorrect, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_new_set_successful, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_new_set_fail, FALSE);
    const char *email = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_new_email));
    const char *mobile_no = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_new_mobile));
    const char *new_password = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_new_password));
    const char *password = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_password_mod));
    if (pass_check(user_index, password)==1){
        modify_details(user_index, new_password, mobile_no, email);
        putFile();
        getFile();
        gtk_label_set_text(app_data->g_lbl_name_holder,s[user_index].userName);
        gtk_label_set_text(app_data->g_lbl_email_holder,s[user_index].email);
        gtk_label_set_text(app_data->g_lbl_mobile_holder,s[user_index].mob_no);
        gtk_label_set_text(app_data->g_lbl_home_name,s[user_index].userName);
        gtk_label_set_text(app_data->g_lbl_home_email,s[user_index].email);
        gtk_label_set_text(app_data->g_lbl_upi_handler,s[user_index].upiId);
        gtk_label_set_text(app_data->g_lbl_home_mob_no,s[user_index].mob_no);
        gtk_label_set_text(app_data->g_lbl_home_upi_handler,s[user_index].upiId);
        gtk_widget_set_visible(app_data->g_lbl_new_set_successful, TRUE);
    } else {
        gtk_widget_set_visible(app_data->g_lbl_curr_pass_incorrect, TRUE);
        gtk_widget_set_visible(app_data->g_lbl_new_set_fail, TRUE);
    }
}

//Withdraw Function
void on_btn_withdraw_clicked (GtkButton *btn_withdraw, appWidgets *app_data){
    gchar *bal2;
    gtk_widget_set_visible(app_data->g_lbl_withd_success, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_withd_fail, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_withd_pass_err, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_withd_accid_err, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_withd_amt_err, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_withd_upi_pass_err, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_withd_upi_rec_err, FALSE);
    const char *amount = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_withd_amt));
    const char *acc_id = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_withd_accid));
    const char *upi_pass = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_withd_upipass));
    const char *upi_rec = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_withd_upir));
    const char *password = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_withd_pass));
    if (strlen(password)==0){
        gtk_widget_set_visible(app_data->g_lbl_withd_pass_err, TRUE);
        gtk_widget_set_visible(app_data->g_lbl_withd_fail, TRUE);
    }
    if (strlen(amount)==0){
        gtk_widget_set_visible(app_data->g_lbl_withd_amt_err, FALSE);
    } else if (pass_check(user_index, password)==1){
        getFile();
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_data->g_radio_cred))){
            getFile();
            withdraw(user_index, amount);
            bal2 = g_strdup_printf("%d", s[user_index].balance);
            gtk_label_set_text(app_data->g_lbl_withd_bal, bal2);
            gtk_label_set_text(app_data->g_lbl_add_bal, bal2);
            gtk_label_set_text(app_data->g_lbl_home_bal, bal2);
            gtk_widget_set_visible(app_data->g_lbl_withd_success, TRUE);
            g_free(bal2);
            putFile();
        } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_data->g_radio_neft))){
            getFile();
            int opr_neft = neft_withdraw(user_index, amount, acc_id);
            if (opr_neft == 0){
                bal2 = g_strdup_printf("%d", s[user_index].balance);
                gtk_label_set_text(app_data->g_lbl_withd_bal, bal2);
                gtk_label_set_text(app_data->g_lbl_add_bal, bal2);
                gtk_label_set_text(app_data->g_lbl_home_bal, bal2);
                gtk_widget_set_visible(app_data->g_lbl_withd_success, TRUE);
                g_free(bal2);
                putFile();
            } else if (opr_neft == 1){
                gtk_widget_set_visible(app_data->g_lbl_withd_accid_err, TRUE);
                gtk_widget_set_visible(app_data->g_lbl_withd_fail, TRUE);
            }
        } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_data->g_radio_upi))) {
            getFile();
            int opr_upi = upi_transfer(user_index, upi_pass, amount, upi_rec);
            if (opr_upi == 1){
                bal2 = g_strdup_printf("%d", s[user_index].balance);
                gtk_label_set_text(app_data->g_lbl_withd_bal, bal2);
                gtk_label_set_text(app_data->g_lbl_add_bal, bal2);
                gtk_label_set_text(app_data->g_lbl_home_bal, bal2);
                gtk_widget_set_visible(app_data->g_lbl_withd_success, TRUE);
                g_free(bal2);
                putFile();
            } else if (opr_upi == 2){
                gtk_widget_set_visible(app_data->g_lbl_withd_upi_rec_err, TRUE);
                gtk_widget_set_visible(app_data->g_lbl_withd_fail, TRUE);
            } else if (opr_upi == 0){
                gtk_widget_set_visible(app_data->g_lbl_withd_upi_pass_err, TRUE);
                gtk_widget_set_visible(app_data->g_lbl_withd_fail, TRUE);
            }
        } else {
            gtk_widget_set_visible(app_data->g_lbl_withd_fail, TRUE);
        }
    } else {
        gtk_widget_set_visible(app_data->g_lbl_withd_fail, TRUE);
    }
}

void on_rad_cred_deb_toggled(GtkToggleButton *togglebutton, appWidgets *app_data){
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_data->g_radio_cred))){
        gtk_widget_set_sensitive(GTK_ENTRY(app_data->g_entry_withd_upir), FALSE);
        gtk_widget_set_sensitive(GTK_ENTRY(app_data->g_entry_withd_upipass), FALSE);
        gtk_widget_set_sensitive(GTK_ENTRY(app_data->g_entry_withd_accid), FALSE);
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_data->g_radio_neft))) {
        gtk_widget_set_sensitive(GTK_ENTRY(app_data->g_entry_withd_accid), TRUE);
        gtk_widget_set_sensitive(GTK_ENTRY(app_data->g_entry_withd_upir), FALSE);
        gtk_widget_set_sensitive(GTK_ENTRY(app_data->g_entry_withd_upipass), FALSE);
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(app_data->g_radio_upi))) {
    gtk_widget_set_sensitive(GTK_ENTRY(app_data->g_entry_withd_accid), FALSE);
        gtk_widget_set_sensitive(GTK_ENTRY(app_data->g_entry_withd_upir), TRUE);
        gtk_widget_set_sensitive(GTK_ENTRY(app_data->g_entry_withd_upipass), TRUE);
    }
}

void on_entry_new_mobile_changed (GtkEditable *entry_new_mobile, appWidgets *app_data){
    const char *number = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_new_mobile));
    if (strlen(number)!=10){
        gtk_widget_set_visible(app_data->g_lbl_mod_mob_err, TRUE);
        gtk_widget_set_sensitive(app_data->g_btn_change_info, FALSE);
    } else if (strlen(number)!=0){
        gtk_widget_set_visible(app_data->g_lbl_mod_mob_err, FALSE);
        gtk_widget_set_sensitive(app_data->g_btn_change_info, TRUE);
    } else{
        gtk_widget_set_visible(app_data->g_lbl_mod_mob_err, FALSE);
        gtk_widget_set_sensitive(app_data->g_btn_change_info, TRUE);
    }
}