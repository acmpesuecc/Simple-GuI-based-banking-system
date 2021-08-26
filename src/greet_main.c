#include <gtk/gtk.h>
#include "bank.h"

typedef struct {
    //Login Page
    GtkWidget* g_lbl_login_user_err;
    GtkWidget* g_lbl_login_pass_err;
    GtkWidget* g_entry_login_username;
    GtkWidget* g_entry_login_password;

    //New Account Page
    GtkWidget* g_check;
    GtkWidget* g_lbl_user_exists;
    GtkWidget* g_lbl_strong;
    GtkWidget* g_lbl_weak;
    GtkWidget *g_lbl_create_mob_err;
    GtkWidget *g_btn_greet_create_user;
    GtkWidget* popover;
    GtkWidget* g_pass_progress;
    GtkWidget* g_img_user_valid;
    GtkWidget* g_lbl_retype_err;
    GtkWidget* g_img_retype_success;
    GtkWidget *g_entry_new_username;
    GtkWidget *g_entry_new_password;
    GtkWidget *g_entry_new_retype_password;
    GtkWidget *g_entry_new_mobno;
    GtkWidget *g_entry_new_email;

} appWidgets;

int main(int argc, char* argv[]) {
    getFile();
    GtkBuilder* builder;
    GtkWidget* window;

    appWidgets *app_data = g_slice_new(appWidgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("../glade/greet_final.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "greet_main_window"));

    //Login Widgets defined here
    app_data->g_lbl_login_pass_err = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_login_pass_errr"));
    app_data->g_lbl_login_user_err = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_username_err"));
    app_data->g_entry_login_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_password"));
    app_data->g_entry_login_username = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login_username"));

    //New Account widgets here
    app_data->g_check = GTK_WIDGET(gtk_builder_get_object(builder, "spin_check"));
    app_data->g_lbl_user_exists = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_user_exists"));
    app_data->g_lbl_retype_err = GTK_WIDGET(gtk_builder_get_object(builder, "retype_err"));
    app_data->g_lbl_strong = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_strong"));
    app_data->g_lbl_weak = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_weak"));
    app_data->g_lbl_create_mob_err = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_create_mob_err"));
    app_data->g_btn_greet_create_user = GTK_WIDGET(gtk_builder_get_object(builder, "btn_greet_create_user"));
    app_data->g_entry_new_username = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_username"));
    app_data->g_entry_new_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_password"));
    app_data->g_entry_new_retype_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_retype_password"));
    app_data->g_entry_new_email = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_email"));
    app_data->g_entry_new_mobno = GTK_WIDGET(gtk_builder_get_object(builder, "enter_new_mobno"));
    app_data->g_pass_progress = GTK_WIDGET(gtk_builder_get_object(builder, "pass_progress"));
    app_data->g_img_retype_success = GTK_WIDGET(gtk_builder_get_object(builder, "retype_success"));
    app_data->g_img_user_valid = GTK_WIDGET(gtk_builder_get_object(builder, "img_user_valid"));
    app_data->popover = GTK_WIDGET(gtk_builder_get_object(builder, "pass_hint"));
    app_data->g_btn_greet_create_user = GTK_WIDGET(gtk_builder_get_object(builder, "btn_greet_create_user"));

    //Visibility
    gtk_widget_set_visible(app_data->g_lbl_login_user_err, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_login_pass_err, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_weak, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_strong, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_retype_err, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_user_exists, FALSE);
    gtk_widget_set_visible(app_data->g_img_user_valid, FALSE);
    gtk_widget_set_visible(app_data->g_img_retype_success, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_create_mob_err, FALSE);
    gtk_spinner_start(GTK_SPINNER(app_data->g_check));

    //Signal Connect and exit
    gtk_builder_connect_signals(builder, app_data);
    g_object_unref(builder);

    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_show(window);
    gtk_main();

    g_slice_free(appWidgets, app_data);

    return 0;
}

 void win_destroy() {
    gtk_main_quit();
}

 void on_btn_exit_create_clicked() {
    gtk_main_quit();
}

 void on_btn_exit_clicked() {
    gtk_main_quit();
}

void on_entry_new_password_changed (GtkEditable *entry_new_password, appWidgets *app_data){
    gtk_widget_set_visible(app_data->g_lbl_strong, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_weak, FALSE);
    const char *password = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_new_password));
    if (strlen(password)==0){
        gtk_widget_show(app_data->popover);
    } else if (strlen(password)<8){
        gtk_widget_hide(app_data->popover);
        gtk_progress_bar_set_fraction(app_data->g_pass_progress,0.5);
        gtk_widget_set_visible(app_data->g_lbl_weak, TRUE);
    } else if (strlen(password)<13){
        gtk_widget_hide(app_data->popover);
        gtk_progress_bar_set_fraction(app_data->g_pass_progress,1);
        gtk_widget_set_visible(app_data->g_lbl_strong, TRUE);

    }
}

void on_entry_new_retype_password_changed(GtkEditable *entry_new_retype_password, appWidgets *app_data){
    gtk_widget_set_sensitive(app_data->g_btn_greet_create_user, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_retype_err, FALSE);
    gtk_widget_set_visible(app_data->g_img_retype_success, FALSE);
    const char *password = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_new_password));
    const char *repeat_password = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_new_retype_password));
    if (strlen(password) == strlen(repeat_password)){
        gtk_widget_set_sensitive(app_data->g_btn_greet_create_user, TRUE);
        gtk_widget_set_visible(app_data->g_img_retype_success, TRUE);
    } else {
        gtk_widget_set_sensitive(app_data->g_btn_greet_create_user, FALSE);
        gtk_widget_set_visible(app_data->g_lbl_retype_err, TRUE);
    }
}

void on_entry_new_username_changed(GtkEditable *entry_new_username, appWidgets *app_data){
    gtk_widget_set_sensitive(GTK_BUTTON(app_data->g_btn_greet_create_user), FALSE);
    gtk_spinner_start(GTK_SPINNER(app_data->g_check));
    gtk_widget_set_visible(GTK_LABEL(app_data->g_lbl_user_exists), FALSE);
    gtk_widget_set_visible(GTK_IMAGE(app_data->g_img_user_valid), FALSE);
    const char *username = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_new_username));
    if (strlen(username) == 0) {
        gtk_spinner_start(GTK_SPINNER(app_data->g_check));
        gtk_widget_set_sensitive(GTK_BUTTON(app_data->g_btn_greet_create_user), FALSE);
    }else if (find_user(username)==1){
        gtk_spinner_stop(GTK_SPINNER(app_data->g_check));
        gtk_widget_set_visible(GTK_LABEL(app_data->g_lbl_user_exists), TRUE);
        gtk_widget_set_sensitive(GTK_BUTTON(app_data->g_btn_greet_create_user), FALSE);
    } else if (find_user(username)==0){
        gtk_spinner_stop(GTK_SPINNER(app_data->g_check));
        gtk_widget_set_visible(GTK_IMAGE(app_data->g_img_user_valid), TRUE);
    }
}

void on_btn_greet_create_user_clicked (GtkButton *btn_greet_create_user, appWidgets *app_data){
    const char *username = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_new_username));
    const char *password = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_new_password));
    const char *number = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_new_mobno));
    const char *email = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_new_email));
    signup(username, password, number, email);
    putFile();
    getFile();
    int user_index = get_user_index(username);
    dashboard_main(user_index,'\0','\0');
    gtk_main_quit();
}

void on_btn_login_clicked (GtkButton *btn_login, appWidgets *app_data, gpointer *window){
    gtk_widget_set_visible(app_data->g_lbl_login_user_err, FALSE);
    gtk_widget_set_visible(app_data->g_lbl_login_pass_err, FALSE);
    //	gtk_widget_set_sensitive(g_btn_login, FALSE);
    const char *username = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_login_username));
    const char *password = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_login_password));
    if (login(username,password)==1){
        gtk_widget_set_visible(app_data->g_lbl_login_user_err, TRUE);
    } else if (login(username,password)==2){
        gtk_widget_set_visible(app_data->g_lbl_login_pass_err, TRUE);
    } else if (login(username,password)==0){
        getFile();
        int user_index = get_user_index(username);
        dashboard_main(user_index,'\0','\0');
        gtk_main_quit();
    }
}

void on_enter_new_mobno_changed (GtkEditable *enter_new_mobno, appWidgets *app_data){
    const char *number = gtk_entry_get_text(GTK_ENTRY(app_data->g_entry_new_mobno));
    if (strlen(number)==10){
        gtk_widget_set_visible(app_data->g_lbl_create_mob_err, FALSE);
        gtk_widget_set_sensitive(app_data->g_btn_greet_create_user, TRUE);
    } else {
        gtk_widget_set_visible(app_data->g_lbl_create_mob_err, TRUE);
        gtk_widget_set_sensitive(app_data->g_btn_greet_create_user, FALSE);
    }
}