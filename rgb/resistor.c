#include <gtk/gtk.h>
#include <glib.h>
#include <cairo.h>

static GtkWidget *drawing;
static GtkWidget *rscale, *gscale, *bscale;

static gboolean drawing_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	const double red = gtk_range_get_value(GTK_RANGE(rscale));
	const double green = gtk_range_get_value(GTK_RANGE(gscale));
	const double blue = gtk_range_get_value(GTK_RANGE(bscale));

	const int width = gtk_widget_get_allocated_width(widget);
	const int height = gtk_widget_get_allocated_height(widget);

	cairo_rectangle(cr, 0, 0, width, height);
	cairo_set_source_rgba(cr, red / 255, green / 255, blue / 255, 1.0);
	cairo_fill(cr);

	return TRUE;
}

static void scale_change(GtkRange * range, gpointer user_data)
{
	gtk_widget_queue_draw(drawing);
}

static GtkWidget *color_widget(const char *label)
{
	GtkWidget *scale;

	scale = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL, 0, 9, 1);
	gtk_widget_set_vexpand(scale, TRUE);
	gtk_scale_set_digits(GTK_SCALE(scale), 0);
	gtk_scale_set_draw_value(GTK_SCALE(scale), TRUE);
	gtk_scale_set_value_pos(GTK_SCALE(scale), GTK_POS_RIGHT);
	gtk_scale_add_mark(GTK_SCALE(scale), 0, GTK_POS_LEFT, "0");
	gtk_scale_add_mark(GTK_SCALE(scale), 1, GTK_POS_LEFT, "1");
	gtk_scale_add_mark(GTK_SCALE(scale), 2, GTK_POS_LEFT, "2");
	gtk_scale_add_mark(GTK_SCALE(scale), 3, GTK_POS_LEFT, "3");
	gtk_scale_add_mark(GTK_SCALE(scale), 4, GTK_POS_LEFT, "4");
	gtk_scale_add_mark(GTK_SCALE(scale), 5, GTK_POS_LEFT, "5");
	gtk_scale_add_mark(GTK_SCALE(scale), 6, GTK_POS_LEFT, "6");
	gtk_scale_add_mark(GTK_SCALE(scale), 7, GTK_POS_LEFT, "7");
	gtk_scale_add_mark(GTK_SCALE(scale), 8, GTK_POS_LEFT, "8");
	gtk_scale_add_mark(GTK_SCALE(scale), 9, GTK_POS_LEFT, "9");
	gtk_range_set_inverted(GTK_RANGE(scale), TRUE);
	gtk_widget_set_halign(scale, GTK_ALIGN_CENTER);
	gtk_widget_set_size_request(scale, -1, 200);
	gtk_widget_set_margin_start(scale, 4);
	gtk_widget_set_margin_end(scale, 4);
	gtk_widget_set_margin_top(scale, 4);
	gtk_widget_set_margin_bottom(scale, 4);
	g_signal_connect(scale, "value-changed", G_CALLBACK(scale_change), NULL);

	return scale;
}

void app_activate(GtkApplication *app, gpointer data)
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *radio;

	grid = gtk_grid_new();
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 4);
	gtk_grid_set_row_spacing(GTK_GRID(grid), 4);

	radio = NULL;
	static const char *const id_label[] = {
		"Black",
		"Brown",
		"Red",
		"Orange",
		"Yellow",
		"Green",
		"Blue",
		"Violet",
		"Gray",
		"White",
		"Gold",
		"Silver",
		"None"
	};
	for (int i = 0; i < G_N_ELEMENTS(id_label); i++) {
		GtkWidget *label;

		label = gtk_label_new(id_label[i]);
		gtk_grid_attach(GTK_GRID(grid), label, 0, i, 1, 1);
	}

	static const char *const digit[] = {
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9"
	};
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("1st digit"), 1, -1, 1, 1);
	radio = NULL;
	for (int i = 0; i < G_N_ELEMENTS(digit); i++) {
		radio = i == 0 ? gtk_radio_button_new_with_label(NULL, digit[i]) : gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio), digit[i]);
		gtk_grid_attach(GTK_GRID(grid), radio, 1, i, 1, 1);
	}

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("2nd digit"), 2, -1, 1, 1);
	radio = NULL;
	for (int i = 0; i < G_N_ELEMENTS(digit); i++) {
		radio = i == 0 ? gtk_radio_button_new_with_label(NULL, digit[i]) : gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio), digit[i]);
		gtk_grid_attach(GTK_GRID(grid), radio, 2, i, 1, 1);
	}

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("3rd digit"), 3, -1, 1, 1);
	radio = NULL;
	for (int i = 0; i < G_N_ELEMENTS(digit); i++) {
		radio = i == 0 ? gtk_radio_button_new_with_label(NULL, digit[i]) : gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio), digit[i]);
		gtk_grid_attach(GTK_GRID(grid), radio, 3, i, 1, 1);
	}

	static const char *const multiply[] = {
		"1",
		"10",
		"100",
		"1k",
		"10k",
		"100k",
		"1M",
		"10M",
		"100M",
		"1G",
		"0,1",
		"0,01"
	};
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("multiply"), 4, -1, 1, 1);
	radio = NULL;
	for (int i = 0; i < G_N_ELEMENTS(multiply); i++) {
		if (multiply[i] != NULL) {
			radio = i == 0 ? gtk_radio_button_new_with_label(NULL, multiply[i]) : gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio), multiply[i]);
			gtk_grid_attach(GTK_GRID(grid), radio, 4, i, 1, 1);
		}
	}

	static const char *const tolerance[] = {
		"1% (F)",
		"10 (G)",
		NULL,
		NULL,
		NULL,
		"0,5% (D)",
		"0,25% (C)",
		"0,1% (B)",
		"0,05% (A)",
		NULL,
		"5% (J)",
		"10% (K)",
		"20% (M)"
	};
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("tolerance"), 5, -1, 1, 1);
	radio = NULL;
	for (int i = 0; i < G_N_ELEMENTS(tolerance); i++) {
		if (tolerance[i] != NULL) {
			radio = i == 0 ? gtk_radio_button_new_with_label(NULL, tolerance[i]) : gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio), tolerance[i]);
			gtk_grid_attach(GTK_GRID(grid), radio, 5, i, 1, 1);
		}
	}

	static const char *const thermo[] = {
		"100",
		"50",
		"15",
		"25",
		NULL,
		NULL,
		"10",
		"5",
		NULL,
		NULL
	};
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("TCR(ppm/K)"), 6, -1, 1, 1);
	radio = NULL;
	for (int i = 0; i < G_N_ELEMENTS(thermo); i++) {
		if (thermo[i] != NULL) {
			radio = i == 0 ? gtk_radio_button_new_with_label(NULL, thermo[i]) : gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio), thermo[i]);
			gtk_grid_attach(GTK_GRID(grid), radio, 6, i, 1, 1);
		}
	}

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "RGB");
	// gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
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
