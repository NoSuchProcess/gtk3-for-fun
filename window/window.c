#include <gtk/gtk.h>

void app_activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window;

	window = gtk_application_window_new(app);

	gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
	int result;
	GtkApplication *app;

	app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
	g_signal_connect(G_OBJECT(app), "activate", G_CALLBACK(app_activate), NULL);
	result = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return result;
}
