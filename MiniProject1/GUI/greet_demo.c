#include <gtk/gtk.h>
#include <string.h>
#include "check.c"

int check_info = 0;

GtkWidget *g_greet_pane;
GtkWidget *g_greet_pane_welcome;
GtkWidget *g_greet_notebook;

GtkWidget *g_fixed_layout_login;
GtkWidget *g_label_login;
GtkWidget *g_btn_login;
GtkWidget *g_btn_exit;
GtkWidget *g_entry_login_username;
GtkWidget *g_entry_login_password;

GtkWidget *g_label_create;
GtkWidget *g_fixed_layout_create;
GtkWidget *g_btn_greet_create_username;
GtkWidget *g_entry_new_username;
GtkWidget *g_entry_new_password;
GtkWidget *g_entry_new_retype_password;
GtkWidget *g_entry_new_mobno;
GtkWidget *g_entry_new_email;
GtkWidget *g_check;
GtkWidget *g_pass_progress;
GtkWidget *g_btn_exit_create;

GtkWidget *g_lbl_user_exists;
GtkWidget *g_lbl_create_success;
GtkWidget *g_lbl_strong;
GtkWidget *g_lbl_weak;
GtkWidget *g_img_user_valid;

GtkWidget *g_lbl_login_user_err;
GtkWidget *g_lbl_login_pass_err;
GtkWidget *g_lbl_login_success;

GtkWidget *g_lbl_retype_err;
GtkWidget *g_img_retype_success;

GtkWidget *popover;
GtkWidget *pop_layout;
GtkWidget *pop_lbl;

int main(int argc, char *argv[]){
	GtkBuilder *builder;
	GtkWidget *window;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "greet.glade", NULL);
	
	window = GTK_WIDGET(gtk_builder_get_object(builder, "greet_main_window"));
    gtk_builder_connect_signals(builder, NULL);
    	
    g_greet_pane = GTK_WIDGET(gtk_builder_get_object(builder, "greet_pane"));
    g_greet_pane_welcome = GTK_WIDGET(gtk_builder_get_object(builder, "greet_pane_welcome"));
    g_greet_notebook = GTK_WIDGET(gtk_builder_get_object(builder, "greet_notebook"));
    	
    //login widgets
    g_label_login = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_greet_login"));
	g_fixed_layout_login = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_layout_login"));
	g_btn_exit = GTK_WIDGET(gtk_builder_get_object(builder, "btn_exit"));
	g_btn_login = GTK_WIDGET(gtk_builder_get_object(builder, "btn_login"));
	g_entry_login_username = GTK_WIDGET(gtk_builder_get_object(builder, "entry_login_username"));
	g_entry_login_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_password"));
	
	//create new account widgets
	g_label_create = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_greet_greet"));
	g_fixed_layout_create = GTK_WIDGET(gtk_builder_get_object(builder, "fixed_create_greet"));
	g_btn_greet_create_username = GTK_WIDGET(gtk_builder_get_object(builder, "btn_greet_create_user"));
	g_entry_new_username = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_username"));
	g_entry_new_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_password"));
	g_entry_new_retype_password = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_retype_password"));
	g_entry_new_mobno = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_mobno"));
	g_entry_new_email = GTK_WIDGET(gtk_builder_get_object(builder, "entry_new_email"));
	g_check = GTK_WIDGET(gtk_builder_get_object(builder, "spin_check"));
	g_pass_progress = GTK_WIDGET(gtk_builder_get_object(builder, "pass_progress"));
	g_btn_exit_create = GTK_WIDGET(gtk_builder_get_object(builder, "btn_exit_create"));
	
	g_lbl_user_exists = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_user_exists"));
	g_lbl_create_success = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_create_success"));
	g_lbl_strong = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_strong"));
	g_lbl_weak = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_weak"));
	g_img_user_valid = GTK_WIDGET(gtk_builder_get_object(builder, "user_does_not_exist"));
	
	popover = GTK_WIDGET(gtk_builder_get_object(builder, "pass_hint"));
	pop_layout = GTK_WIDGET(gtk_builder_get_object(builder, "pass_layout"));
	pop_lbl = GTK_WIDGET(gtk_builder_get_object(builder, "pass_format"));
	
	g_lbl_login_user_err = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_username_err"));
	g_lbl_login_pass_err = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_login_pass_errr"));
	g_lbl_login_success = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_success"));
	
	g_lbl_retype_err = GTK_WIDGET(gtk_builder_get_object(builder, "retype_err"));
	g_img_retype_success = GTK_WIDGET(gtk_builder_get_object(builder, "retype_fail"));
	
	gtk_spinner_start(GTK_SPINNER(g_check));
//	gtk_widget_set_sensitive(g_btn_greet_create_username, FALSE);
	gtk_widget_set_visible(g_lbl_user_exists, FALSE);
	gtk_widget_set_visible(g_lbl_create_success, FALSE);
	gtk_widget_set_visible(g_lbl_weak, FALSE);
	gtk_widget_set_visible(g_lbl_strong, FALSE);
	gtk_widget_set_visible(g_img_user_valid, FALSE);
	
	gtk_widget_set_visible(g_lbl_retype_err, FALSE);
	gtk_widget_set_visible(g_img_retype_success, FALSE);
	
	gtk_widget_set_visible(g_lbl_login_user_err, FALSE);
	gtk_widget_set_visible(g_lbl_login_pass_err, FALSE);
	gtk_widget_set_visible(g_lbl_login_success, FALSE);
	
	g_object_unref(builder);
	gtk_widget_show(window);            
	
    gtk_main();
    	
    return 0;
}	

G_MODULE_EXPORT void on_btn_exit_clicked(){
	gtk_main_quit();
}

G_MODULE_EXPORT void on_btn_login_clicked(GtkWidget *wid,gpointer data){
	gtk_widget_set_visible(g_lbl_login_user_err, FALSE);
	gtk_widget_set_visible(g_lbl_login_pass_err, FALSE);
	gtk_widget_set_visible(g_lbl_login_success, FALSE);
//	gtk_widget_set_sensitive(g_btn_login, FALSE);
	const gchar *username = gtk_entry_get_text(GTK_ENTRY(g_entry_login_username)); 
	const gchar *password = gtk_entry_get_text(GTK_ENTRY(g_entry_login_password));
	if (login(username,password)==1)	{
		gtk_widget_set_visible(g_lbl_login_user_err, TRUE);
	} else if (login(username,password)==2){
		gtk_widget_set_visible(g_lbl_login_pass_err, TRUE);
	} else if (login(username,password)==0){
		gtk_widget_set_visible(g_lbl_login_success, TRUE);
	}
}

G_MODULE_EXPORT void on_btn_greet_create_user_clicked(GtkWidget *wid,gpointer data){
	const gchar *username = gtk_entry_get_text(GTK_ENTRY(g_entry_new_username)); 
	const gchar *password = gtk_entry_get_text(GTK_ENTRY(g_entry_new_password));
	const gchar *repeat_password = gtk_entry_get_text(GTK_ENTRY(g_entry_new_retype_password));
	if(signup(username, password, repeat_password)==3){
		gtk_widget_set_visible(g_lbl_create_success, TRUE);
	}
}

G_MODULE_EXPORT void win_destroy(){
	gtk_main_quit();
}

G_MODULE_EXPORT void on_entry_new_password_changed(GtkWidget *widget, gpointer window){
	gtk_widget_set_visible(g_lbl_strong, FALSE);
	gtk_widget_set_visible(g_lbl_weak, FALSE);
	const gchar *password = gtk_entry_get_text(GTK_ENTRY(g_entry_new_password));
	if (strlen(password)==0){
		gtk_widget_show(popover);
	} else if (strlen(password)<8){
		gtk_widget_hide(popover);
		gtk_progress_bar_set_fraction(g_pass_progress,0.5);
		gtk_widget_set_visible(g_lbl_weak, TRUE);
	} else if (strlen(password)<13){
		gtk_widget_hide(popover);
		gtk_progress_bar_set_fraction(g_pass_progress,1);
		gtk_widget_set_visible(g_lbl_strong, TRUE);

	}
}

G_MODULE_EXPORT void on_btn_exit_create_clicked(){
	gtk_main_quit();
}

G_MODULE_EXPORT void on_entry_new_username_changed(GtkWidget *widget, gpointer window){
	gtk_widget_set_sensitive(g_btn_greet_create_username, TRUE);
	gtk_spinner_start(GTK_SPINNER(g_check));
	gtk_widget_set_visible(g_lbl_user_exists, FALSE);
	gtk_widget_set_visible(g_img_user_valid, FALSE);
	const gchar *username = gtk_entry_get_text(GTK_ENTRY(g_entry_new_username));
	if (strlen(username) == 0) {
		gtk_spinner_start(GTK_SPINNER(g_check));
		gtk_widget_set_sensitive(g_btn_greet_create_username, FALSE);
	}else if (check_user(username)==1){
		gtk_spinner_stop(GTK_SPINNER(g_check));
		gtk_widget_set_visible(g_lbl_user_exists, TRUE);
		gtk_widget_set_sensitive(g_btn_greet_create_username, FALSE);
	} else if (check_user(username)==0){
		gtk_spinner_stop(GTK_SPINNER(g_check));
		gtk_widget_set_visible(g_img_user_valid, TRUE);
	}
}


G_MODULE_EXPORT void on_entry_new_retype_password_changed(GtkWidget *widget, gpointer window){
	gtk_widget_set_sensitive(g_btn_greet_create_username, FALSE);
	gtk_widget_set_visible(g_lbl_retype_err, FALSE);
	gtk_widget_set_visible(g_img_retype_success, FALSE);
	const gchar *password = gtk_entry_get_text(GTK_ENTRY(g_entry_new_password));
	const gchar *repeat_password = gtk_entry_get_text(GTK_ENTRY(g_entry_new_retype_password));
	if (strlen(password) == strlen(repeat_password)){
		gtk_widget_set_sensitive(g_btn_greet_create_username, TRUE);
		gtk_widget_set_visible(g_img_retype_success, TRUE);
	} else {
		gtk_widget_set_sensitive(g_btn_greet_create_username, FALSE);
		gtk_widget_set_visible(g_lbl_retype_err, TRUE);
	}
}	
