#include <glib.h>
#include <shader_compile.h>

GLuint shader_compile(GLuint type, const GLchar *source, GLint length)
{
	GLuint shader;
	GLint success;

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, &length);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLchar message[512];

		glGetShaderInfoLog(shader, sizeof message, NULL, message);
		g_error("Compile error: %s\n", message);
		glDeleteShader(shader);
		shader = 0;
	}
	return shader;
}
