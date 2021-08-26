#include <gtk/gtk.h>

GtkWidget  *g_notebook_widget;
GtkWidget  *g_btn_login;
GtkWidget  *g_exit_btn;
GtkWidget  *g_username_entry;
GtkWidget  *g_password_entry;
GtkWidget  *g_img1;
GtkWidget  *g_log_label;
GtkWidget  *g_img2;
GtkWidget  *g_create_label;

int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;

	
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "try.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    gtk_builder_connect_signals(builder, NULL);

	g_notebook_widget = GTK_WIDGET(gtk_builder_get_object(builder, "notebook_widget"));
	g_btn_login = GTK_WIDGET(gtk_builder_get_object(builder, "btn_login"));
	g_exit_btn = GTK_WIDGET(gtk_builder_get_object(builder, "exit_btn"));
	g_username_entry = GTK_WIDGET(gtk_builder_get_object(builder, "username_entry"));
	g_password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "password_entry"));
	g_img1 = GTK_WIDGET(gtk_builder_get_object(builder, "img1"));
	g_img2 = GTK_WIDGET(gtk_builder_get_object(builder, "img2"));
	g_create_label = GTK_WIDGET(gtk_builder_get_object(builder, "create_label"));
	g_log_label = GTK_WIDGET(gtk_builder_get_object(builder, "log_label"));

	g_object_unref(builder);
    gtk_widget_show(window);                
    gtk_main();

    return 0;
}

G_MODULE_EXPORT void on_window_destroy(){
    gtk_main_quit();
}

G_MODULE_EXPORT void on_exit_btn_clicked(){
	gtk_main_quit();
}