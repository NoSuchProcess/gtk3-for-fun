#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>
#include <cairo.h>

static inline gdouble to_radians(gdouble degrees)
{
	return degrees * G_PI / 180.;
}

static gboolean draw(GtkDrawingArea *drawing, cairo_t *cr, gpointer user_data)
{
	static const GdkRGBA hour_color = (GdkRGBA) { 0.5, 0., 0.5, 1. };
	static const GdkRGBA minute_color = (GdkRGBA) { 0., 0.5, 0.5, 0.75 };
	static const GdkRGBA second_color = (GdkRGBA) { 0.5, 0.5, 0., 0.75 };

	const int width = gtk_widget_get_allocated_width(GTK_WIDGET(drawing));
	const int height = gtk_widget_get_allocated_height(GTK_WIDGET(drawing));
	const int size = MIN(width, height);

	cairo_matrix_t matrix;
	gdouble angle;

	GDateTime *const now = g_date_time_new_now_local();

	cairo_identity_matrix(cr);
	cairo_translate(cr, width / 2., height / 2.);
	cairo_scale(cr, size / 200., size / 200.);
	cairo_get_matrix(cr, &matrix);

	// hours hand
	angle = 30. * (g_date_time_get_hour(now) + g_date_time_get_minute(now) / 60.);
	cairo_rotate(cr, to_radians(angle));
	cairo_move_to(cr, 0., -40.);
	cairo_arc(cr, 0., 0., 8., 0., G_PI);
	cairo_close_path(cr);
	gdk_cairo_set_source_rgba(cr, &hour_color);
	cairo_fill(cr);

	// minutes hand
	angle = 6. * (g_date_time_get_minute(now) + g_date_time_get_second(now) / 60.);
	cairo_set_matrix(cr, &matrix);
	cairo_rotate(cr, to_radians(angle));
	cairo_move_to(cr, 0., -70.);
	cairo_arc(cr, 0., 0., 6., 0., G_PI);
	cairo_close_path(cr);
	gdk_cairo_set_source_rgba(cr, &minute_color);
	cairo_fill(cr);

	// seconds hand
	angle = 6. * g_date_time_get_second(now);
	cairo_set_matrix(cr, &matrix);
	cairo_rotate(cr, to_radians(angle));
	cairo_move_to(cr, 0., -80.);
	cairo_line_to(cr, 0., 0.);
	gdk_cairo_set_source_rgba(cr, &second_color);
	cairo_set_line_width(cr, 1.);
	cairo_stroke(cr);

	// hours ticks
	cairo_set_matrix(cr, &matrix);
	for (int i = 0; i < 12; ++i) {
		cairo_move_to(cr, 88., 0.);
		cairo_line_to(cr, 96., 0.);
		cairo_rotate(cr, to_radians(30.));
	}
	gdk_cairo_set_source_rgba(cr, &hour_color);
	cairo_set_line_width(cr, 3.);
	cairo_stroke(cr);

	// minutes tick
	cairo_set_matrix(cr, &matrix);
	for (int i = 0; i < 60; ++i) {
		if ((i % 5) != 0) {
			cairo_move_to(cr, 92., 0.);
			cairo_line_to(cr, 96., 0.);
		}
		cairo_rotate(cr, to_radians(6.));
	}
	gdk_cairo_set_source_rgba(cr, &minute_color);
	cairo_set_line_width(cr, 1.);
	cairo_stroke(cr);

	g_date_time_unref(now);

	return TRUE;
}

static gboolean tick(gpointer user_data)
{
	gtk_widget_queue_draw(GTK_WIDGET(user_data));

	return G_SOURCE_CONTINUE;
}

static void activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *drawing;

	drawing = gtk_drawing_area_new();
	g_signal_connect(G_OBJECT(drawing), "draw", G_CALLBACK(draw), NULL);

	window = gtk_application_window_new(app);
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
	gtk_window_set_title(GTK_WINDOW(window), "Analog Clock");
	gtk_container_add(GTK_CONTAINER(window), drawing);

	gtk_widget_show_all(window);

	g_timeout_add(100, tick, drawing);
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
