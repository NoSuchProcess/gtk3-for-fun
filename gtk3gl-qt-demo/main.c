#include <glib.h>
#include <gtk/gtk.h>
#include <epoxy/gl.h>
#include <glmath.h>
#include "shader.h"
#include "vertices.h"

#define SPACING 4

static GtkWidget *area = NULL;
static GLuint vao = 0, vbo = 0;
static GLuint program = 0;

static gdouble rot[3] = { 15., 345., 0. };

static GLuint g_resource_get_shader(GResource *resource, const char *path, GLenum shaderType)
{
	GBytes *bytes;
	gsize size;
	const GLchar *string;
	GLint length;
	GLuint shader;
	GLint status;

	bytes = g_resource_lookup_data(resource, path, G_RESOURCE_LOOKUP_FLAGS_NONE, NULL);
	if (bytes == NULL) {
		return 0;
	}

	string = g_bytes_get_data(bytes, &size);
	length = size;

	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &string, &length);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLchar info[512];

		glGetShaderInfoLog(shader, sizeof info, NULL, info);
		g_error("Error: %s\n", info);
		shader = 0;
	}
	g_bytes_unref(bytes);

	return shader;
}

static void setup_matrices()
{
	GLuint location;

	mat4 world = mat4_identity();
	world = mat4_mul(world, mat4_rotation(to_radians(180 - rot[0]), (vec3) { 1, 0, 0 }));
	world = mat4_mul(world, mat4_rotation(to_radians(rot[1]), (vec3) { 0, 1, 0 }));
	world = mat4_mul(world, mat4_rotation(to_radians(rot[2]), (vec3) { 0, 0, 1 }));

	// Our camera never changes in this example.
	const mat4 camera = mat4_translation((vec3) { 0, 0, -1 });
	const mat4 modelView = mat4_mul(camera, world);
	const mat3 normalMatrix = mat3_normal(world);

	glUseProgram(program);

	location = glGetUniformLocation(program, "mvMatrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, (const GLfloat *) &modelView);
	location = glGetUniformLocation(program, "normalMatrix");
	glUniformMatrix3fv(location, 1, GL_FALSE, (const GLfloat *) &normalMatrix);
	// Light position is fixed.
	location = glGetUniformLocation(program, "lightPos");
	glUniform3f(location, 0, 0, 70.);

	glUseProgram(0);
}

/* OpenGL area */
static void realize(GtkGLArea *area, gpointer user_data)
{
	GLuint vsh, fsh;
	GLint index;

	gtk_gl_area_make_current(area);
	if (gtk_gl_area_get_error(area) != NULL) {
		return;
	}

	/* Program */
	GResource *resource = shader_get_resource();

	vsh = g_resource_get_shader(resource, "/vertex.glsl", GL_VERTEX_SHADER);
	fsh = g_resource_get_shader(resource, "/fragment.glsl", GL_FRAGMENT_SHADER);

	if (vsh != 0 && fsh != 0) {
		GLint status;

		program = glCreateProgram();
		glAttachShader(program, vsh);
		glAttachShader(program, fsh);
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		glDetachShader(program, vsh);
		glDetachShader(program, fsh);

		if (status == GL_FALSE) {
			GLchar info[512];

			glGetProgramInfoLog(program, sizeof info, NULL, info);
			g_error("Error: %s\n", info);
			glDeleteProgram(program);
			program = 0;
		}
	}

	glDeleteShader(vsh);
	glDeleteShader(fsh);

	/* Buffers */
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

	index = glGetAttribLocation(program, "position");
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, sizeof (vertex_t), (const GLvoid *) offsetof(vertex_t, position));
	glEnableVertexAttribArray(index);
	index = glGetAttribLocation(program, "normal");
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, sizeof (vertex_t), (const GLvoid *) offsetof(vertex_t, normal));
	glEnableVertexAttribArray(index);

	setup_matrices();
}

static void unrealize(GtkGLArea *area, gpointer user_data)
{
	gtk_gl_area_make_current(area);
	if (gtk_gl_area_get_error(area) != NULL) {
		return;
	}

	/* Program */
	glDeleteProgram(program);
	program = 0;

	/* Buffers */
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo);
	vbo = 0;

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao);
	vao = 0;
}

static void resize(GtkGLArea *area, gint width, gint height, gpointer user_data)
{
	GLuint location;
	mat4 projMatrix = mat4_perspective(to_radians(45.), (GLfloat) width / (GLfloat) height, 0.01, 100.);

	glUseProgram(program);
	location = glGetUniformLocation(program, "projMatrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, (const GLfloat *) &projMatrix);
	glUseProgram(0);

	gtk_gl_area_queue_render(area);
}

static gboolean render(GtkGLArea *area, GdkGLContext *context, gpointer user_data)
{
	glClearColor(0.2, 0.3, 0.4, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);

	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices_size / sizeof (vertex_t));
	glBindVertexArray(0);
	glUseProgram(0);

	glFlush();

	return TRUE;
}

/* Ranges */
static void on_value_changed(GtkAdjustment *adjustment, gpointer user_data)
{
	gdouble *val = (gdouble *) user_data;

	*val = gtk_adjustment_get_value(adjustment);

	gtk_gl_area_make_current(GTK_GL_AREA(area));
	if (gtk_gl_area_get_error(GTK_GL_AREA(area)) != NULL) {
		return;
	}

	setup_matrices();
	gtk_gl_area_queue_render(GTK_GL_AREA(area));
}

/* Application */
static void activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *grid;

	grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), SPACING);
	gtk_grid_set_column_spacing(GTK_GRID(grid), SPACING);

	area = gtk_gl_area_new();
	gtk_gl_area_set_has_depth_buffer(GTK_GL_AREA(area), TRUE);
	gtk_widget_set_size_request(area, 200, 200);
	g_signal_connect(G_OBJECT(area), "realize", G_CALLBACK(realize), NULL);
	g_signal_connect(G_OBJECT(area), "unrealize", G_CALLBACK(unrealize), NULL);
	g_signal_connect(G_OBJECT(area), "resize", G_CALLBACK(resize), NULL);
	g_signal_connect(G_OBJECT(area), "render", G_CALLBACK(render), NULL);
	gtk_widget_set_hexpand(area, TRUE);
	gtk_widget_set_vexpand(area, TRUE);
	gtk_grid_attach(GTK_GRID(grid), area, 0, 1, 1, 1);

	for (unsigned i = 0; i < 3; ++i) {
		GtkAdjustment *adjustment;
		GtkWidget *scale;

		adjustment = gtk_adjustment_new(rot[i], 0.0, 360.0, 1.0, 15.0, 0.0);
		g_signal_connect(G_OBJECT(adjustment), "value-changed", G_CALLBACK(on_value_changed), &rot[i]);

		scale = gtk_scale_new(GTK_ORIENTATION_VERTICAL, adjustment);
		gtk_scale_set_draw_value(GTK_SCALE(scale), FALSE);
		gtk_range_set_inverted(GTK_RANGE(scale), TRUE);
		gtk_widget_set_vexpand(scale, TRUE);

		gtk_grid_attach(GTK_GRID(grid), scale, i + 1, 1, 1, 1);
	}

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "GTK+ 3 OpenGL Example");
	gtk_container_set_border_width(GTK_CONTAINER(window), SPACING);
	gtk_container_add(GTK_CONTAINER(window), grid);

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
