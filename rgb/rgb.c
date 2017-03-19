#include <gtk/gtk.h>
#include <glib.h>
#include <cairo.h>

static GtkWidget *drawing;
static GtkWidget *rscale, *gscale, *bscale, *ascale;

static gboolean drawing_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	const double red = gtk_range_get_value(GTK_RANGE(rscale));
	const double green = gtk_range_get_value(GTK_RANGE(gscale));
	const double blue = gtk_range_get_value(GTK_RANGE(bscale));
	const double alpha = gtk_range_get_value(GTK_RANGE(ascale));

	const int width = gtk_widget_get_allocated_width(widget);
	const int height = gtk_widget_get_allocated_height(widget);

	cairo_rectangle(cr, 0, 0, width / 5, height);
	cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 1.0);
	cairo_fill(cr);
	cairo_rectangle(cr, width / 5, 0, width / 5, height);
	cairo_set_source_rgba(cr, 0.75, 0.75, 0.75, 1.0);
	cairo_fill(cr);
	cairo_rectangle(cr, width * 2 / 5, 0, width / 5, height);
	cairo_set_source_rgba(cr, 0.50, 0.50, 0.50, 1.0);
	cairo_fill(cr);
	cairo_rectangle(cr, width * 3 / 5, 0, width / 5, height);
	cairo_set_source_rgba(cr, 0.25, 0.25, 0.25, 1.0);
	cairo_fill(cr);
	cairo_rectangle(cr, width * 4 / 5, 0, width / 5, height);
	cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1.0);
	cairo_fill(cr);

	cairo_rectangle(cr, 0, 0, width, height);
	cairo_set_source_rgba(cr, red / 255, green / 255, blue / 255, alpha / 255);
	cairo_fill(cr);

	return TRUE;
}

static void scale_change(GtkRange * range, gpointer user_data)
{
	gtk_widget_queue_draw(drawing);
}

static GtkWidget *color_widget(const char *label, GtkWidget **scale_widget, double preset)
{
	GtkWidget *frame;
	GtkWidget *scale;

	scale = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL, 0, 255, 1);
	gtk_range_set_value(GTK_RANGE(scale), preset);
	gtk_widget_set_vexpand(scale, TRUE);
	gtk_scale_set_digits(GTK_SCALE(scale), 0);
	gtk_scale_set_draw_value(GTK_SCALE(scale), TRUE);
	gtk_scale_set_value_pos(GTK_SCALE(scale), GTK_POS_RIGHT);
	gtk_scale_add_mark(GTK_SCALE(scale), 0, GTK_POS_LEFT, "0");
	gtk_scale_add_mark(GTK_SCALE(scale), 127, GTK_POS_LEFT, "127");
	gtk_scale_add_mark(GTK_SCALE(scale), 255, GTK_POS_LEFT, "255");
	gtk_range_set_inverted(GTK_RANGE(scale), TRUE);
	gtk_widget_set_halign(scale, GTK_ALIGN_CENTER);
	gtk_widget_set_size_request(scale, -1, 200);
	gtk_widget_set_margin_start(scale, 4);
	gtk_widget_set_margin_end(scale, 4);
	gtk_widget_set_margin_top(scale, 4);
	gtk_widget_set_margin_bottom(scale, 4);
	g_signal_connect(scale, "value-changed", G_CALLBACK(scale_change), NULL);

	frame = gtk_frame_new(label);
	gtk_frame_set_label_align(GTK_FRAME(frame), 0.5, 0.5);
	gtk_container_add(GTK_CONTAINER(frame), scale);

	*scale_widget = scale;
	return frame;
}

void app_activate(GtkApplication *app, gpointer data)
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *frame;

	grid = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 4);
	gtk_grid_set_row_spacing(GTK_GRID(grid), 4);

	frame = color_widget("Red", &rscale, 0);
	gtk_grid_attach(GTK_GRID(grid), frame, 0, 0, 1, 1);
	frame = color_widget("Green", &gscale, 0);
	gtk_grid_attach(GTK_GRID(grid), frame, 1, 0, 1, 1);
	frame = color_widget("Blue", &bscale, 0);
	gtk_grid_attach(GTK_GRID(grid), frame, 2, 0, 1, 1);
	frame = color_widget("Alpha", &ascale, 255);
	gtk_grid_attach(GTK_GRID(grid), frame, 3, 0, 1, 1);

	drawing = gtk_drawing_area_new();
	gtk_widget_set_size_request(drawing, -1, 100);
	g_signal_connect(drawing, "draw", G_CALLBACK(drawing_draw), NULL);
	gtk_grid_attach(GTK_GRID(grid), drawing, 0, 1, 4, 1);

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "RGB");
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_container_set_border_width(GTK_CONTAINER(window), 4);
	gtk_container_add(GTK_CONTAINER(window), grid);
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
