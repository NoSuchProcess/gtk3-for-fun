#include <glib.h>
#include <gtk/gtk.h>
#include <cairo.h>

static inline gdouble to_radians(gdouble degrees)
{
	return degrees * G_PI / 180.;
}

static gboolean draw(GtkDrawingArea *area, cairo_t *cr, gpointer user_data)
{
	cairo_matrix_t matrix;
	const int width = gtk_widget_get_allocated_width(GTK_WIDGET(area));
	const int height = gtk_widget_get_allocated_height(GTK_WIDGET(area));
	const int side = MIN(width, height);
	GDateTime *current = g_date_time_new_now_local();
	gdouble angle;

	cairo_identity_matrix(cr);
	cairo_translate(cr, width / 2., height / 2.);
	cairo_scale(cr, side / 200., side / 200.);
	cairo_get_matrix(cr, &matrix);

	// hour hand
	angle = 30. * (g_date_time_get_hour(current) + g_date_time_get_minute(current) / 60.);
	cairo_rotate(cr, to_radians(angle));
	cairo_move_to(cr, 7., 8.);
	cairo_line_to(cr, -7., 8.);
	cairo_line_to(cr, 0., -40.);
	cairo_close_path(cr);
	cairo_set_source_rgba(cr, 0.5, 0., 0.5, 1.);
	cairo_fill(cr);

	// minute hand
	cairo_set_matrix(cr, &matrix);
	angle = 6. * (g_date_time_get_minute(current) + g_date_time_get_second(current) / 60.);
	cairo_rotate(cr, to_radians(angle));
	cairo_move_to(cr, 7., 8.);
	cairo_line_to(cr, -7., 8.);
	cairo_line_to(cr, 0., -70.);
	cairo_close_path(cr);
	cairo_set_source_rgba(cr, 0., 0.5, 0.5, 0.75);
	cairo_fill(cr);

	// seconds hand
	cairo_set_matrix(cr, &matrix);
	angle = 6. * g_date_time_get_second(current);
	cairo_rotate(cr, to_radians(angle));
	cairo_move_to(cr, 0., 0.);
	cairo_line_to(cr, 0., -80.);
	cairo_set_source_rgba(cr, 0.5, 0.5, 0., 0.75);
	cairo_set_line_width(cr, 1.);
	cairo_stroke(cr);

	// hour ticks
	cairo_set_matrix(cr, &matrix);
	for (int i = 0; i < 12; ++i) {
		cairo_move_to(cr, 88., 0.);
		cairo_line_to(cr, 96., 0.);
		cairo_rotate(cr, to_radians(30.));
	}
	cairo_set_source_rgba(cr, 0.5, 0., 0.5, 1.);
	cairo_set_line_width(cr, 3.);
	cairo_stroke(cr);

	// minute ticks
	cairo_set_matrix(cr, &matrix);
	for (int i = 0; i < 60; ++i) {
		if ((i % 5) != 0) {
			cairo_move_to(cr, 92., 0.);
			cairo_line_to(cr, 96., 0.);
		}
		cairo_rotate(cr, to_radians(6.));
	}
	cairo_set_source_rgba(cr, 0., 0.5, 0.5, 0.75);
	cairo_set_line_width(cr, 1.);
	cairo_stroke(cr);

	g_date_time_unref(current);

	return TRUE;
}

static gboolean tick(gpointer user_data)
{
	gtk_widget_queue_draw(GTK_WIDGET(user_data));

	return TRUE;
}

static void activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *drawing_area;

	drawing_area = gtk_drawing_area_new();
	g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw), NULL);

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Analog Clock");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
	gtk_container_add(GTK_CONTAINER(window), drawing_area);
	g_timeout_add(1000, tick, drawing_area);

	gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
	int result;
	GtkApplication *app;

	app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
	g_signal_connect(G_OBJECT(app), "activate", G_CALLBACK(activate), NULL);
	result = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(G_OBJECT(app));

	return result;
}
